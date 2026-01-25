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
/**        \file  Sd.c
 *        \brief  Service Discovery source file
 *
 *      \details  Vector static code implementation for AUTOSAR Service Discovery (SD) module.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define SD_SOURCE

/**********************************************************************************************************************
 *  LOCAL MISRA / PCLINT JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4558 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4522, 4424, 4432, 4332, 4342, 4393 EOF */ /* MD_Sd_Enum_4522_4424_4432_4332_4342_4393 */

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use an include guard. */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Sd_Priv.h"
#include "Det.h"
#include "BswM_Sd.h"
#include "vstdlib.h"

#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
# include "EcuM_Error.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of Sd header file. */
#if((SD_SW_MAJOR_VERSION != (0x09u)) || (SD_SW_MINOR_VERSION != (0x03u)) || (SD_SW_PATCH_VERSION != (0x01u)))
# error "Vendor specific version numbers of Sd.c and Sd.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#if !defined (SD_LOCAL)                                                                                                 /* COV_SD_COMPATIBILITY */
# define SD_LOCAL static
#endif

#if !defined (SD_LOCAL_INLINE)                                                                                          /* COV_SD_COMPATIBILITY */
# define SD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
#define SD_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

SD_LOCAL VAR(Sd_StateType, SD_VAR_ZERO_INIT) Sd_State = SD_UNINIT;
SD_LOCAL VAR(uint8, SD_VAR_ZERO_INIT) Sd_RxIndicationCount = 0;
SD_LOCAL VAR(boolean, SD_VAR_ZERO_INIT) Sd_TxPathLocked = FALSE;

#define SD_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define SD_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

SD_LOCAL VAR(Sd_ExtendedTimeType, SD_VAR_ZERO_INIT) Sd_TimeMsSinceStart = {0u, 0u};

#define SD_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define SD_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

P2CONST(Sd_ConfigType, SD_VAR_ZERO_INIT, SD_PBCFG) Sd_ConfigDataPtr = NULL_PTR;

#define SD_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define SD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Sd_UtilClient_ClientServiceSetStateRequested()
 *********************************************************************************************************************/
/*! \brief          Configures the client as requested.
 *  \details        -
 *  \param[in]      ClientIdx   Index of the client.
 *                              [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ClientServiceSetStateRequested(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_UtilClient_ClientServiceSetStateReleased()
 *********************************************************************************************************************/
/*! \brief          Configures the client as released.
 *  \details        -
 *  \param[in]      ClientIdx   Index of the client.
 *                              [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ClientServiceSetStateReleased(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_Init_General()
 *********************************************************************************************************************/
/*! \brief          Initializes all general variable data.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_General(void);

/**********************************************************************************************************************
 *  Sd_Init_Instance()
 *********************************************************************************************************************/
/*! \brief          Initializes all variable data of the instances.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Instance(void);

/**********************************************************************************************************************
 *  Sd_Init_Server()
 *********************************************************************************************************************/
/*! \brief          Initializes all variable data of the servers.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Server(void);

/**********************************************************************************************************************
 *  Sd_Init_Client()
 *********************************************************************************************************************/
/*! \brief          Initializes all variable data of the clients.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Client(void);

/**********************************************************************************************************************
 *  Sd_Init_ClientCeg()
 *********************************************************************************************************************/
/*! \brief          Initializes all variable data of the consumed eventgroups.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ClientCeg(void);

/**********************************************************************************************************************
 *  Sd_CloseAllSocketsOfInstance()
 *********************************************************************************************************************/
/*! \brief          Closes all used sockets of an Sd instance.
 *  \details        Function is called to re-initialize a Sd instance, all sockets are closed with Abort = TRUE.
 *  \param[in]      InstanceIdx             Index of instance which shall be initialized.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_CloseAllSocketsOfInstance(Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Init_ReInitialize()
 *********************************************************************************************************************/
/*! \brief          Initializes all communication state dependent data.
 *  \details        Re-initializes data if the module state was changed by a call of Sd_Init() or
 *                  Sd_LocalIpAddrAssignmentChg().
 *  \param[in]      InstanceIdx             Index of instance which shall be initialized.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitialize(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeServers()
 *********************************************************************************************************************/
/*! \brief          Initializes the communication configuration of all servers of the given instance.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which shall be initialized.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeServers(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeEventHandler()
 *********************************************************************************************************************/
/*! \brief          Initializes the communication configuration of all event handlers of the given server.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeEventHandler(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_Process()
 *********************************************************************************************************************/
/*! \brief          Executes the server state machine.
 *  \details        Is called by the MainFunction and processes the state of the server.
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_Process(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessNotReady()
 *********************************************************************************************************************/
/*! \brief          Handles the server state machine of the down phases.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessNotReady(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessInitialWait()
 *********************************************************************************************************************/
/*! \brief          Handles the server state machine of the initial wait phase.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessInitialWait(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessRepetition()
 *********************************************************************************************************************/
/*! \brief          Handles the server state machine of the repetition phase.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessRepetition(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessMain()
 *********************************************************************************************************************/
/*! \brief          Handles the server state machine of the main phase.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessMain(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessEventHandlerStateMachine()
 *********************************************************************************************************************/
/*! \brief          Handles the event handler state machines of the given server.
 *  \details        -
 *  \param[in]      ServerIdx               Index of the server to execute state machine.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessEventHandlerStateMachine(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_UpdateEventHandlerState()
 *********************************************************************************************************************/
/*! \brief          Updates the state of the event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_UpdateEventHandlerState(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_UpdateEventHandlerClients()
 *********************************************************************************************************************/
/*! \brief          Updates the state of all subscribed clients of an event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_UpdateEventHandlerClients(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerSwitchMulticast()
 *********************************************************************************************************************/
/*! \brief          Switches the event handler from unicast to multicast transmission mode.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerSwitchMulticast(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerSwitchUnicast()
 *********************************************************************************************************************/
/*! \brief          Switches the event handler from multicast to unicast transmission mode.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerSwitchUnicast(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerCheckSubscribed()
 *********************************************************************************************************************/
/*! \brief          Checks if the eventhandler is still requested by remote clients and changes its state accordingly.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerCheckSubscribed(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_DisableRouting()
 *********************************************************************************************************************/
/*! \brief          Disables routing for server methods and events.
 *  \details        Disables all routing groups of the event handler and resets the activation count for all server
 *                  socket connections.
 *  \param[in]      EventHandlerIdx         Index of the event handler.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_DisableRouting(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntry()
 *********************************************************************************************************************/
/*! \brief          Processes the attached server Entry Option.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Index of the entry which shall be processed.
 *  \param[in]      InstanceIdx             Index of instance which received the message.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntry(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntryFind()
 *********************************************************************************************************************/
/*! \brief          Reads and processes the attached FindService entry.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntryFind(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribe()
 *********************************************************************************************************************/
/*! \brief          Reads and processes the attached SubscribeEventgroup entry.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntrySubscribe(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_SearchEventHandler()
 *********************************************************************************************************************/
/*! \brief          Searches the event handler with the matching ID.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \return         ID of the matching event handler.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfEventHandlerType, SD_CODE) Sd_RxServer_SearchEventHandler(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_CheckConfigOptionByCbk()
 *********************************************************************************************************************/
/*! \brief          Triggers a user callout in order to validate the received configuration options.
 *  \details        -
 *  \param[in]      ServerIdx                   Corresponding server index.
 *                                              [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      RxPduId                     Receiving PDU-ID.
 *  \param[in]      RxEntryType                 Type of received entry.
 *  \param[in]      RxConfigOptionPtrArrayPtr   Configured configuration option pointer list.
 *  \return         SD_OPTIONS_OK               Message was accepted and shall be processed.
 *  \return         SD_OPTIONS_NOT_OK           Message was not accepted and shall be rejected/ignored.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_CheckConfigOptionByCbk(
  Sd_SizeOfServerType ServerIdx,
  PduIdType RxPduId,
  Sd_EntryType RxEntryType,
  SD_P2CONST(Sd_ConfigOptionStringType) RxConfigOptionPtrArrayPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionArray()
 *********************************************************************************************************************/
/*! \brief          Processes the attached option array.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Option array is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid option array, this SD message is not valid.
 *  \return         SD_OPTIONS_WRONG_SUBNET Option is not topological correct (wrong subnet).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionArray(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionRun()
 *********************************************************************************************************************/
/*! \brief          Processes the attached server options run.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Start index of the Option.
 *  \param[in]      NrOfOptions             Number of successive attached Options in the run.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx <= Sd_GetSizeOfEventHandler()]
 *                                          [invalid: Sd_GetSizeOfEventHandler()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Option is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid option, this SD message is not valid.
 *  \return         SD_OPTIONS_WRONG_SUBNET Option is not topological correct (wrong subnet).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionRun(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  uint8 NrOfOptions,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionSubscribe()
 *********************************************************************************************************************/
/*! \brief          Processes the attached (Stop)SubscribeEventgroup option.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Start index of the Option.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Option is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid option, this SD message is not valid.
 *  \return         SD_OPTIONS_WRONG_SUBNET Option is not topological correct (wrong subnet).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionSubscribe(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribeInternal()
 *********************************************************************************************************************/
/*! \brief          Completes processing of the received subscription and saves all required elements.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         E_OK                    Option is valid.
 *  \return         E_NOT_OK                Invalid Option, this SD message is not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_ProcessEntrySubscribeInternal(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribeSaveParameters()
 *********************************************************************************************************************/
/*! \brief          Save all mandatory parameters of the received message for further processing.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      ClientListIdx           Client index which triggered the event.
 *                                          [range: ClientListIdx < Sd_GetSizeOfClientList()]
 *  \param[out]     AttachedOptionsPtr      Structure containing all attached options.
 *  \return         E_OK                    Option is valid.
 *  \return         E_NOT_OK                Invalid Option, this SD message is not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_ProcessEntrySubscribeSaveParameters(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_EventServer_Process()
 *********************************************************************************************************************/
/*! \brief          Processes all pending server events.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance to process.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_Process(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_DiscardEvent()
 *********************************************************************************************************************/
/*! \brief          Determines if currently processed RxEvent can be discarded.
 *  \details        If a following entry in the RxEvent queue will revert
 *                  the state of a CEG of a client back to the current state,
 *                  the currently processed entry of the RxEvent queue can be discarded.
 *
 *  \param[in]      InstanceIdx             Corresponding instance index.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *                  CurrentRxEventIdx       Index of RxEvent which is currently being processed.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         TRUE                    Current RxEvent can be discarded.
 *  \return         FALSE                   Current RxEvent must not be discarded.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_DiscardEvent(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType CurrentRxEventIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_ProcessEvent()
 *********************************************************************************************************************/
/*! \brief          Processes the pending server event.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \param[in,out]  PendingStopSubscribePtr Information if a StopSubscribeEventgroup entry is pending and has to be
 *                                          processed first.
 *  \return         TRUE                    The entry has to be kept for later processing.
 *  \return         FALSE                   The entry is processed and can be removed from the queue.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_ProcessEvent(
  Sd_SizeOfRxEventType RxEventIdx,
  SD_P2VAR(boolean) PendingStopSubscribePtr);

/**********************************************************************************************************************
 *  Sd_StateServer_Update()
 *********************************************************************************************************************/
/*! \brief          Updates state machine of the server and sets timer event for the next main function cycle.
 *  \details        -
 *  \param[in]      ServerIdx               Server index to set the value and timer event.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      NewState                New state of the server service state machine.
 *  \param[in]      ResetTimeToTriggerSend  Indicates if the state machine has to be executed.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_Update(
  Sd_SizeOfServerType ServerIdx,
  Sd_ServerStateMachineType NewState,
  boolean ResetTimeToTriggerSend);

/**********************************************************************************************************************
 *  Sd_UtilServer_UpdateEventHandlerStateMachine()
 *********************************************************************************************************************/
/*! \brief          Updates state machine of the event handler and sets a timer event for the next main function cycle.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Event handler to set the value and timer event.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      NewState                New state of the event handler state machine.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_UpdateEventHandlerStateMachine(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_EventHandlerStateMachineType NewState);

/**********************************************************************************************************************
 *  Sd_UtilServer_UpdateEventHandlerRequestState()
 *********************************************************************************************************************/
/*! \brief          Updates the request state of the event handler.
 *  \details        Updates the request state of the event handler, triggers a state machine execution and informs the
 *                  BswM about the state change.
 *  \param[in]      EventHandlerIdx         Event handler to set the value and timer event.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      NewState                New state of the event handler state machine.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_UpdateEventHandlerRequestState(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_EventHandlerCurrentStateType NewState);

/**********************************************************************************************************************
 *  Sd_RxServer_AddEventToRingBuffer()
 *********************************************************************************************************************/
/*! \brief          Adds an received event to the ring buffer.
 *  \details        -
 *  \param[in]      InstanceIdx             Relevant instance index.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      ClientListIdx           Client index which triggered the event.
 *                                          [range: ClientListIdx < Sd_GetSizeOfClientList()]
 *  \param[in]      Event                   Event to process.
 *                                          [allowed: SD_SERVER_EVENT_EVENTGROUP_[STOP_]SUBSCRIBE[_REBOOT][_MULTI]]
 *  \return         E_OK                    Event successfully saved.
 *  \return         E_NOT_OK                Not able to save event for further processing.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_AddEventToRingBuffer(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  Sd_ServerEventgroupEventType Event);

/**********************************************************************************************************************
 *  Sd_EventServer_GetFirstIdx()
 *********************************************************************************************************************/
/*! \brief          Gets index of first queued RxEvent.
 *  \details        The event will NOT be removed from the queue.
 *  \param[in]      InstanceIdx             Corresponding instance index.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[out]     EventIdxPtr             Index of first queued RxEvent.
 *                                          [range: RxEventIdx <= Sd_GetSizeOfRxEvent()]
 *                                          [invalid: Sd_GetSizeOfRxEvent()]
 *  \return         E_OK                    Event read and ready to process.
 *  \return         E_NOT_OK                No pending event to process.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_GetFirstIdx(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2VAR(Sd_SizeOfRxEventType) EventIdxPtr);

/**********************************************************************************************************************
 *  Sd_EventServer_RemoveFirst()
 *********************************************************************************************************************/
/*! \brief          Removes the first element of the RxEvent queue.
 *  \details        Handles also wrap around of the buffer and removes the saved endpoint information if not used by
 *                  other elements.
 *  \param[in]      InstanceIdx             Corresponding instance index for which the first event should be removed.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            Expects the ringbuffer to contain at least one element.
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_RemoveFirst(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
*  Sd_EventServer_GetFollowingIdx()
*********************************************************************************************************************/
/*! \brief          Gets the index of a following entry of an entry in the the RxEvent queue.
 *  \details        -
 *  \param[in]      InstanceIdx             Corresponding instance index.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *                  RxEventIdx              Index of a valid RxEvent queue entry for which the index of the next
 *                                          entry shall be determined.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         Index to the next RxEvent. If there is no following event Sd_GetSizeOfRxEvent().
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfRxEventType, SD_CODE) Sd_EventServer_GetFollowingIdx(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_SaveEndpoint()
 *********************************************************************************************************************/
/*! \brief          Searches for an unused slot and saves the address pointed by InAddrPtr.
 *  \details        -
 *  \param[in]      InstanceIdx                 Index of instance which handles this address.
 *                                              [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      InAddrPtr                   Pointer to address which shall be saved.
 *                                              [constraint: IP address has to be a valid IPv4/IPv6 address]
 *  \param[in]      Type                        Type of the endpoint address.
 *  \param[out]     OutEndpointStorageIdxPtr    Reference to the saved endpoint index.
 *                                              [range: OutEndpointStorageIdx <= Sd_GetSizeOfEndpointStorage()]
 *                                              [invalid: Sd_GetSizeOfEndpointStorage()]
 *  \return         E_OK                        Endpoint address saved.
 *  \return         E_NOT_OK                    Unable to save the endpoint address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_SaveEndpoint(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_SockAddrContainerType) InAddrPtr,
  Sd_EndpointType Type,
  SD_P2VAR(Sd_SizeOfEndpointStorageType) OutEndpointStorageIdxPtr);

/**********************************************************************************************************************
 *  Sd_EventServer_RemoveEndpoint()
 *********************************************************************************************************************/
/*! \brief          Removes the saved endpoint address.
 *  \details        -
 *  \param[in,out]  EndpointStorageIdx      Index of the saved endpoint to be removed.
 *                                          [range: EndpointStorageIdx <= Sd_GetSizeOfEndpointStorage()]
 *                                          [invalid: Sd_GetSizeOfEndpointStorage()]
 *  \return         TRUE                    Endpoint is not referenced by an additional client.
 *  \return         FALSE                   Endpoint is referenced by another client and still required.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_RemoveEndpoint(
  Sd_SizeOfEndpointStorageType EndpointStorageIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_Subscription()
 *********************************************************************************************************************/
/*! \brief          Processes the subscription of a remote client.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_Subscription(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitial()
 *********************************************************************************************************************/
/*! \brief          Processes the initial subscription of a remote client.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         E_OK                    Remote client successfully subscribed.
 *  \return         E_NOT_OK                Not able to subscribe remote client.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitial(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_IsTriggerTransmitEnabled()
 *********************************************************************************************************************/
/*! \brief          Checks if the EventHandler associated with the RxEvent needs notification transmission.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         TRUE                    EventHandler is configured for triggered/notification event transmission.
 *  \return         FALSE                   EventHandler is not configured for triggered/notification event transmission.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_IsTriggerTransmitEnabled(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitialTcp()
 *********************************************************************************************************************/
/*! \brief          Configures the remote client for TCP.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         E_OK                    Remote client successfully configured.
 *  \return         E_NOT_OK                Not able to configure remote client.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitialTcp(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitialUdp()
 *********************************************************************************************************************/
/*! \brief          Configures the remote client for UDP.
 *  \details        -
 *  \param[in]      RxEventIdx              Index of the received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         E_OK                    Remote client successfully configured.
 *  \return         E_NOT_OK                Not able to configure remote client.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitialUdp(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_RxServer_AddClientToList()
 *********************************************************************************************************************/
/*! \brief          Adds a client to the client list of the event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      AddressStorageIdx       Remote IP address index of the client.
 *                                          [range: AddressStorageIdx < Sd_GetSizeOfAddressStorage()]
 *  \return         Index of the saved client.
 *                  [invalid: Sd_GetSizeOfClientList()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfClientListType, SD_CODE) Sd_RxServer_AddClientToList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_RemoveClientsFromEventHandler()
 *********************************************************************************************************************/
/*! \brief          Removes all clients of the event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_RemoveClientsFromEventHandler(
  Sd_SizeOfEventHandlerType EventHandlerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_SetDown()
 *********************************************************************************************************************/
/*! \brief          Sets the requested state of the server service to down.
 *  \details        -
 *  \param[in]      ServerIdx               Corresponding server service index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different server.
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_SetDown(Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_SetAvailable()
 *********************************************************************************************************************/
/*! \brief          Sets the requested state of the server service to available.
 *  \details        -
 *  \param[in]      ServerIdx               Corresponding server service index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE for different server.
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_SetAvailable(Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_RemoveClientFromList()
 *********************************************************************************************************************/
/*! \brief          Removes a client from the client list of the event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      ClientListIdx           Client index which should be removed.
 *                                          [range: ClientListIdx < Sd_GetSizeOfClientList()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_RemoveClientFromList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_UnconfigureClientComPaths()
 *********************************************************************************************************************/
/*! \brief          Unconfigures the client communication paths.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      ClientListIdx           Client index which should be removed.
 *                                          [range: ClientListIdx < Sd_GetSizeOfClientList()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_UnconfigureClientComPaths(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_ReleaseEventHandlers()
 *********************************************************************************************************************/
/*! \brief          Releases all eventhandlers of the server.
 *  \details        -
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_ReleaseEventHandlers(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_CloseTcpAndPreconfiguredSoCons()
 *********************************************************************************************************************/
/*! \brief          Closes all TCP socket and preconfigured UDP connections of the server.
 *  \details        -
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      Abort                   Indicates if the socket connections shall be aborted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_CloseTcpAndPreconfiguredSoCons(
  Sd_SizeOfServerType ServerIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  Sd_UtilServer_DisableMethodRouting()
 *********************************************************************************************************************/
/*! \brief          Disables the routing of provided methods.
 *  \details        -
 *  \param[in]      ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_DisableMethodRouting(
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_LocalIpAddrAssignmentChgReset()
 *********************************************************************************************************************/
/*! \brief          Resets all dynamic server data in the case of a local IP address assignment change.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which has to be reset.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_LocalIpAddrAssignmentChgReset(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_GetSoConActivationMapIdx()
 *********************************************************************************************************************/
/*! \brief          Returns the activation map index for the requested SoConId.
 *  \details        The activation map allows it to handle multiple instances of a remote client.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      SoConId                 Requested socket connection ID.
 *  \return         Found SoConActivationMap index.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_SizeOfSoConActivationMapType, SD_CODE) Sd_UtilServer_GetSoConActivationMapIdx(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_UtilServer_IncreaseActivationCount()
 *********************************************************************************************************************/
/*! \brief          Increases the activation count for the requested SoConId.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      SoConId                 Requested socket connection ID.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_IncreaseActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_UtilServer_DecreaseActivationCount()
 *********************************************************************************************************************/
/*! \brief          Decreases the activation count for the requested SoConId.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      SoConId                 Requested socket connection ID.
 *  \return         TRUE                    The activation count was decreased to zero.
 *  \return         FALSE                   The activation count was not decreased to zero.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_UtilServer_DecreaseActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_UtilServer_ResetActivationCount()
 *********************************************************************************************************************/
/*! \brief          Resets the activation count for the requested SoConId.
 *  \details        -
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      SoConId                 Requested socket connection ID.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_ResetActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_RxServer_FindClientInList()
 *********************************************************************************************************************/
/*! \brief          Searches for a client in the client-list of the event handler.
 *  \details        -
 *  \param[in]      EventHandlerIdx             Corresponding event handler index.
 *                                              [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      RxMessageInfoPtr            Information about the received message.
 *  \param[in]      AttachedOptionsPtr          Structure containing all attached options.
 *                                              [NULL_PTR is allowed if a reboot was detected and the RebootDetected
 *                                              flag of RxMessageInfoPtr is set.]
 *  \param[in]      CreateNewClientIfNotFound   Flag indicating if a new client shall be created if no corresponding
 *                                              client could be found.
 *  \return         Found client index.
 *                  [invalid: >= Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_SizeOfClientListType, SD_CODE) Sd_RxServer_FindClientInList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr,
  boolean CreateNewClientIfNotFound);

/**********************************************************************************************************************
 *  Sd_RxServer_CheckAttachedEndpointOptions()
 *********************************************************************************************************************/
/*! \brief          Checks the attached endpoint options.
 *  \details        Compares the received endpoint address with the configured one.
 *  \param[in]      EventHandlerIdx         Corresponding event handler index.
 *                                          [range: EventHandlerIdx < Sd_GetSizeOfEventHandler()]
 *  \param[in]      ClientListIdx           Corresponding client index.
 *                                          [range: ClientListIdx < Sd_GetSizeOfClientList()]
 *  \param[in]      AttachedOptionsPtr      Structure containing all attached options.
 *  \return         TRUE                    Attached endpoint options are valid.
 *  \return         FALSE                   Attached endpoint options are invalid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_RxServer_CheckAttachedEndpointOptions(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_CheckAttachedEndpointOption()
 *********************************************************************************************************************/
/*! \brief          Checks the attached UDP or TCP endpoint option.
 *  \details        Checks if the configured remote address is equivalent to the received endpoint address.
 *  \param[in]      SoConId                 Configured socket connection ID.
 *  \param[in]      EndpointStorageIdx      Index of the saved endpoint.
 *                                          [range: EndpointStorageIdx <= Sd_GetSizeOfEndpointStorage()]
 *                                          [invalid: Sd_GetSizeOfEndpointStorage()]
 *  \param[in]      EndpointPtr             UDP or TCP endpoint address of the entry.
 *  \return         TRUE                    Attached endpoint option is valid.
 *  \return         FALSE                   Attached endpoint option is invalid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_RxServer_CheckAttachedEndpointOption(
  SoAd_SoConIdType SoConId,
  Sd_SizeOfEndpointStorageType EndpointStorageIdx,
  SD_P2CONST(Sd_SockAddrContainerType) EndpointPtr);

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Process()
 *********************************************************************************************************************/
/*! \brief          Processes all pending trigger transmit requests.
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_Process(void);

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Trigger()
 *********************************************************************************************************************/
/*! \brief          Triggers the transmission of initial events.
 *  \details        -
 *  \param[in]      TriggerTransmitIdx      Index of the trigger transmit event.
 *                                          [range: TriggerTransmitIdx < Sd_GetSizeOfTriggerTransmit()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_Trigger(
  Sd_SizeOfTriggerTransmitType TriggerTransmitIdx);

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Add()
 *********************************************************************************************************************/
/*! \brief          Adds an trigger transmit request to the ring buffer.
 *  \details        The trigger transmit request will be processed during the next main function.
 *  \param[in]      RxEventIdx              Event index which caused the trigger transmit.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \return         E_OK                    Information if the event could be saved.
 *  \return         E_NOT_OK                Not able to save trigger transmit request.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_TriggerTransmit_Add(
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_ReadFirst()
 *********************************************************************************************************************/
/*! \brief          Reads the first event from the trigger transmit ring buffer.
 *  \details        The event will NOT be removed from the buffer.
 *  \param[out]     TriggerTransmitIdxPtr   Trigger transmit index.
 *  \return         E_OK                    Event successfully read and ready for processing.
 *  \return         E_NOT_OK                No more pending trigger transmit events.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_TriggerTransmit_ReadFirst(
  SD_P2VAR(Sd_SizeOfTriggerTransmitType) TriggerTransmitIdxPtr);

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_RemoveFirst()
 *********************************************************************************************************************/
/*! \brief          Removes the first element from the ring buffer.
 *  \details        -
 *  \pre            Ring buffer has to contain at least one element.
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_RemoveFirst(void);

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeClients()
 *********************************************************************************************************************/
/*! \brief          Initializes the communication configuration of all clients of the given instance.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which shall be initialized.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeClients(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeConsumedEventgroups()
 *********************************************************************************************************************/
/*! \brief          Initializes the communication configuration of all consumed eventgroups of the given client.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeConsumedEventgroups(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_Process()
 *********************************************************************************************************************/
/*! \brief          Processes the state of the client service.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_Process(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessStateMachine()
 *********************************************************************************************************************/
/*! \brief          Processes the state machine of the client service.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessStateMachine(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_HandleReboot()
 *********************************************************************************************************************/
/*! \brief          Check if a reboot of the remote server was detected and handle state accordingly.
 *  \details        -
 *  \param[in]      ClientIdx               Client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleReboot(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_HandleRequestState()
 *********************************************************************************************************************/
/*! \brief          Check if the client is still requested and handle the request state accordingly.
 *  \details        -
 *  \param[in]      ClientIdx               Client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleRequestState(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_HandleRetrySubscription()
 *********************************************************************************************************************/
/*! \brief          Handle the counter of the retry subscription feature.
 *  \details        Triggers DET runtime error if amount of retries exceeds configured value.
 *  \param[in]      ClientIdx               Client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleRetrySubscription(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_CheckIfRetryActive()
 *********************************************************************************************************************/
/*! \brief          Checks if at least one consumed eventgroup of the client performs subscription retries.
 *  \details        -
 *  \param[in]      ClientIdx               Client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \return         TRUE                    At least one eventgroup is in retry subscription state.
 *  \return         FALSE                   No eventgroup of the client performs retries.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_CheckIfRetryActive(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessInitial()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the initial state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessInitial(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessNotRequestedNotSeen()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the not requested, not seen state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessNotRequestedNotSeen(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessNotRequestedSeen()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the not requested, seen state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessNotRequestedSeen(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessRequestedNotReady()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the not ready state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessRequestedNotReady(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessSearchingInitial()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the searching initial wait state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessSearchingInitial(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessSearchingRepetition()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the searching repetition state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessSearchingRepetition(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessLeaveSearching()
 *********************************************************************************************************************/
/*! \brief          Checks if the searching state can be left and triggers the state change.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessLeaveSearching(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessLeaveSearchingRcvOffer()
 *********************************************************************************************************************/
/*! \brief          Handles the reception of an OfferService message in the searching phase.
 *  \details        -
 *  \param[in]      ClientIdx               Client index which received the OfferService message.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessLeaveSearchingRcvOffer(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessReady()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the ready state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessReady(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessReadyEventReceived()
 *********************************************************************************************************************/
/*! \brief          Processes the received OfferService or StopOfferService message.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessReadyEventReceived(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessStopped()
 *********************************************************************************************************************/
/*! \brief          Handles the client state machine of the stopped state.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to execute state machine.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessStopped(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCeg()
 *********************************************************************************************************************/
/*! \brief          Handles all consumed eventgroup state maches of the client.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCeg(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegReset()
 *********************************************************************************************************************/
/*! \brief          Resets the consumed eventgroup if the client service is not ready anymore.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegReset(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegState()
 *********************************************************************************************************************/
/*! \brief          Handles the consumed eventgroup state machine.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegState(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegUnsubscribed()
 *********************************************************************************************************************/
/*! \brief          Handles the consumed eventgroup state machine while being unsubscribed.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegUnsubscribed(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSent()
 *********************************************************************************************************************/
/*! \brief          Handles the consumed eventgroup state machine while waiting for a response.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSent(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSentRxAck()
 *********************************************************************************************************************/
/*! \brief          Processes the received SubscribeEventgroupAck message.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSentRxAck(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSentRxOffer()
 *********************************************************************************************************************/
/*! \brief          Processes the received OfferService message while waiting for the SubscribeEventgroupAck message.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSentRxOffer(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegSubscribed()
 *********************************************************************************************************************/
/*! \brief          Handles the consumed eventgroup state machine while being Subscribed.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegSubscribed(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_Configure()
 *********************************************************************************************************************/
/*! \brief          Configures the client on service level.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \return         E_OK                    All socket connections and routing groups updated.
 *  \return         E_NOT_OK                Unable to update all socket connections and routing groups.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_Configure(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_ConfigureMethod()
 *********************************************************************************************************************/
/*! \brief          Configures the socket connection and routing group for the client service method.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in,out]  MethodSoConIdPtr        Socket connection IF of the corresponding method.
 *  \param[in]      ServiceStartSoConId     Socket connection ID used by the service.
 *  \param[in]      ServerEndpointAddrPtr   Server endpoint address.
 *  \return         E_OK                    Socket connection and routing group updated.
 *  \return         E_NOT_OK                Unable to update socket connection and routing group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_ConfigureMethod(
  Sd_SizeOfClientType ClientIdx,
  SD_P2VAR(SoAd_SoConIdType) MethodSoConIdPtr,
  SoAd_SoConIdType ServiceStartSoConId,
  SD_P2CONST(Sd_SockAddrContainerType) ServerEndpointAddrPtr);

/**********************************************************************************************************************
 *  Sd_StateClient_Unconfigure()
 *********************************************************************************************************************/
/*! \brief          Unconfigures all socket connections and routing groups for the client service.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in]      ResetEndpointInfo       Specifies if unicast as well as multicast endpoint address shall be reset.
 *  \param[in]      UnconfigureCegs         Specifies if ConsumedEventgroups shall be unconfigured immediatly (TRUE)
 *                                          Or marked for unconfiguration (FALSE)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_StateClient_Unconfigure(
  Sd_SizeOfClientType ClientIdx,
  boolean ResetEndpointInfo,
  boolean UnconfigureCegs);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroup()
 *********************************************************************************************************************/
/*! \brief          Updates all socket connections and routing groups of the eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    All socket connections and routing groups updated.
 *  \return         E_NOT_OK                Unable to update all socket connections and routing groups.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroup(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupTcp()
 *********************************************************************************************************************/
/*! \brief          Updates the TCP configuration of the eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    Socket connection and routing group updated.
 *  \return         E_NOT_OK                Unable to update the socket connection and routing group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupTcp(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupUdp()
 *********************************************************************************************************************/
/*! \brief          Updates the UDP configuration of the eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    Socket connection and routing group updated.
 *  \return         E_NOT_OK                Unable to update the socket connection and routing group.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupUdp(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

#if(SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON == STD_ON)
/**********************************************************************************************************************
 *  Sd_StateClient_CheckMulticastSoConRemoteAddress()
 *********************************************************************************************************************/
/*! \brief          Checks the configured remote address of the multicast socket.
 *  \details        If the received unicast remote address of the server is different from the configured value, the
 *                  configuration is reset.
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK
 *  \return         E_NOT_OK
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_CheckMulticastSoConRemoteAddress(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);
#endif

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceived()
 *********************************************************************************************************************/
/*! \brief          Updates the configuration based on the received SubscribeEventgroupAck.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    All socket connections and routing groups updated.
 *  \return         E_NOT_OK                Unable to update all socket connections and routing groups.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceived(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceivedInitial()
 *********************************************************************************************************************/
/*! \brief          Handles the initial multicast configuration of the consumed eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    Configured the consumed eventgroup for multicast.
 *  \return         E_NOT_OK                Unable to configure the consumed eventgroup for multicast.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceivedInitial(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceivedRenew()
 *********************************************************************************************************************/
/*! \brief          Renews the multicast configuration of the consumed eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \return         E_OK                    Renewed the multicast configuration of the consumed eventgroup.
 *  \return         E_NOT_OK                Unable to renew the multicast configuration of the consumed eventgroup.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceivedRenew(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoCon()
 *********************************************************************************************************************/
/*! \brief          Searches for the socket connection with the best local and remote address match.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[out]     MulticastSoConIdPtr     Best matching socket connection ID.
 *  \param[out]     MatchTypePtr            Match types of the local and remote address.
 *  \return         E_OK                    Matching/suitable socket connection found.
 *  \return         E_NOT_OK                No suitable socket connection found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoCon(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2VAR(Sd_SizeOfMulticastSoConIdType) MulticastSoConIdPtr,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) MatchTypePtr);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState()
 *********************************************************************************************************************/
/*! \brief          Calculates the state of the given address.
 *  \details        The state describes if port or address is set to a unique value or defines ANY value.
 *  \param[in]      AddrPtr                 Address which is used for state calculation.
 *  \return         addrState               State of the given address.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(uint8, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState(
  SD_P2CONST(Sd_SockAddrContainerType) AddrPtr);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchType()
 *********************************************************************************************************************/
/*! \brief          Calculates the local match type of the given multicast socket connection.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      MulticastSoConIdIdx     Multicast socket connection ID of.
 *                                          [range: MulticastSoConIdx < Sd_GetSizeOfMulticastSoCon()]
 *  \param[out]     LocalMatchTypePtr       Match types of the local address.
 *  \return         E_OK                    Match type calculated.
 *  \return         E_NOT_OK                Not able to calculate match type.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchType(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_SizeOfMulticastSoConIdType MulticastSoConIdIdx,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) LocalMatchTypePtr);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchType()
 *********************************************************************************************************************/
/*! \brief          Calculates the remote match type of the given multicast socket connection.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      MulticastSoConIdIdx     Multicast socket connection ID of.
 *                                          [range: MulticastSoConIdx < Sd_GetSizeOfMulticastSoCon()]
 *  \param[out]     RemoteMatchTypePtr      Match types of the remote IP address.
 *  \return         E_OK                    Match type calculated.
 *  \return         E_NOT_OK                Not able to calculate match type.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchType(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_SizeOfMulticastSoConIdType MulticastSoConIdIdx,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) RemoteMatchTypePtr);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchPrio()
 *********************************************************************************************************************/
/*! \brief          Calculates the local match priority of the given multicast socket connection.
 *  \details        -
 *  \param[in]      MatchTypePtr            Match types of the local address.
 *  \param[in,out]  LocalMatchPrioPtr       Match priority of the local address.
 *  \param[in,out]  RemoteMatchPrioPtr      Match priority of the remote address.
 *  \return         TRUE                    Found local match.
 *  \return         FALSE                   Local address does not match.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchPrio(
  SD_P2CONST(Sd_LocalRemoteMatchTypeType) MatchTypePtr,
  SD_P2VAR(uint8) LocalMatchPrioPtr,
  SD_P2VAR(uint8) RemoteMatchPrioPtr);

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchPrio()
 *********************************************************************************************************************/
/*! \brief          Calculates the remote match priority of the given multicast socket connection.
 *  \details        -
 *  \param[in]      MatchTypePtr            Match types of the remote address.
 *  \param[in,out]  RemoteMatchPrioPtr      Match priority of the remote address.
 *  \return         TRUE                    Found local match.
 *  \return         FALSE                   Local address does not match.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchPrio(
  SD_P2CONST(Sd_LocalRemoteMatchTypeType) MatchTypePtr,
  SD_P2VAR(uint8) RemoteMatchPrioPtr);

/**********************************************************************************************************************
 *  Sd_StateClient_ReleaseCeg()
 *********************************************************************************************************************/
/*! \brief          Unconfigures the consumed eventgroup and informs the BswM if required.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ReleaseCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_StateClient_Update()
 *********************************************************************************************************************/
/*! \brief          Updates state machine of the client and sets a timer event for the next main function cycle.
 *  \details        -
 *  \param[in]      ClientIdx               Client index to set the value and timer event.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in]      NewState                New state of the client service state machine.
 *  \param[in]      ResetTimeToTriggerSend  Set TimeToTriggerSend to the invalid value.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_Update(
  Sd_SizeOfClientType ClientIdx,
  Sd_ClientStateMachineType NewState,
  boolean ResetTimeToTriggerSend);

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateCeg()
 *********************************************************************************************************************/
/*! \brief          Updates state machine of the consumed eventgroup.
 *  \details        Sets a timer event for the next main function cycle.
 *  \param[in]      ConsumedEventgroupIdx   Consumed eventgroup index to set the value and timer event.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      NewState                New state of the consumed eventgroup state machine.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_UpdateCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_ConsumedEventGroupStateMachineType NewState);

/**********************************************************************************************************************
 *  Sd_StateClient_UnconfigureCeg()
 *********************************************************************************************************************/
/*! \brief          Unconfigures all socket connections and routing groups of the consumed eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Consumed eventgroup index to unconfigure.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      AbortFlag               Forces abort of socket connections.
 *  \param[in]      ResetEndpointInfo       Specifies if the multicast endpoint address shall be reset.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_StateClient_UnconfigureCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean AbortFlag,
  boolean ResetEndpointInfo);

/**********************************************************************************************************************
 *  Sd_StateClient_LocalIpAlreadyConfigured()
 *********************************************************************************************************************/
/*! \brief          Check if the requested multicast IP address is already configured at another socket.
 *  \details        -
 *  \param[in]      MulticastAddressPtr     Requested multicast IP address.
 *  \return         TRUE                    Matching/suitable socket connection found.
 *  \return         FALSE                   No suitable socket connection found.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_LocalIpAlreadyConfigured(
  SD_P2CONST(Sd_SockAddrContainerType) MulticastAddressPtr);

/**********************************************************************************************************************
 *  Sd_StateClient_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Requests the given address as local IP address.
 *  \details        -
 *  \param[in]      SoConId                 Socket connection ID which shall be configured.
 *  \param[in]      MulticastAddrPtr        Multicast address which shall be configured as local address.
 *  \param[in]      PerformRequest          Indicating if the address shall be configured or the request counter incremented.
 *  \return         E_OK                    Request successfully processed.
 *  \return         E_NOT_OK                Not able to configure the local address.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_RequestIpAddrAssignment(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) MulticastAddrPtr,
  boolean PerformRequest);

/**********************************************************************************************************************
 *  Sd_StateClient_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*! \brief          Releases the local IP address
 *  \details        The local address is not released, if it is still required by another client.
 *  \param[in]      SoConId                 Socket connection ID which is configured with the local address.
 *  \return         E_OK                    Local address was successfully released.
 *  \return         E_NOT_OK                Not able to release local address.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_ReleaseIpAddrAssignment(
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_StateClient_EntryListContainsSubscribe()
 *********************************************************************************************************************/
/*! \brief          Checks if a SubscribeEventgroup message is still pending.
 *  \details        -
 *  \param[in,out]  ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_EntryListContainsSubscribe(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntry()
 *********************************************************************************************************************/
/*! \brief          Processes the attached client entry option.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Index of the entry which shall be processed.
 *  \param[in]      InstanceIdx             Index of the instance which received the message.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntry(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryOffer()
 *********************************************************************************************************************/
/*! \brief          Processes the received OfferService entry.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryOffer(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryOfferOptionRuns()
 *********************************************************************************************************************/
/*! \brief          Processes the options run of the received OfferService entry.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Message was accepted and shall be processed.
 *  \return         SD_OPTIONS_NOT_OK       Message was not accepted and shall be rejected/ignored.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_ProcessEntryOfferOptionRuns(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryAcknowledge()
 *********************************************************************************************************************/
/*! \brief          Processes the attached SubscribeEventgroupAck entry.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      IndexOfEntry            Start index of the Entry-Option.
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryAcknowledge(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_RxClient_CheckConfigOptionByCbk()
 *********************************************************************************************************************/
/*! \brief          Triggers a user callout in order to validate the received configuration options.
 *  \details        If no user callout is configured, the options are accepted.
 *  \param[in]      ClientIdx                   Corresponding client index.
 *                                              [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in]      RxPduId                     Receiving PDU-ID.
 *  \param[in]      RxEntryType                 Type of received entry.
 *  \param[in]      RxConfigOptionPtrArrayPtr   Configured configuration option pointer list.
 *  \return         SD_OPTIONS_OK               Message was accepted and shall be processed.
 *  \return         SD_OPTIONS_NOT_OK           Message was not accepted and shall be rejected/ignored.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_CheckConfigOptionByCbk(
  Sd_SizeOfClientType ClientIdx,
  PduIdType RxPduId,
  Sd_EntryType RxEntryType,
  SD_P2CONST(Sd_ConfigOptionStringType) RxConfigOptionPtrArrayPtr);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryAcknowledgeSave()
 *********************************************************************************************************************/
/*! \brief          Processes the attached SubscribeEventgroupAck entry.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx    Corresponding consumed eventgroup index.
 *                                           [range: ConsumedEventgroupIdx <= Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      MulticastEndpointAddrPtr Received multicast endpoint.
 *  \param[in]      RxTTL                    TTL of the received acknowledge.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryAcknowledgeSave(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2CONST(Sd_SockAddrContainerType) MulticastEndpointAddrPtr,
  uint32 RxTTL);

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessOptionRun()
 *********************************************************************************************************************/
/*! \brief          Processes the attached client option run.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Start index of the Option.
 *  \param[in]      NrOfOptions             Number of succeeding Options which are attached to the Entry-Option.
 *  \param[in]      EMalformedMsgId         DEM error id for malformed messages.
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx <= Sd_GetSizeOfConsumedEventgroup()]
 *                                          [invalid: Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Option array is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid option array, this SD message is not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_ProcessOptionRun(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  uint8 NrOfOptions,
  Sd_Dem_EventIdType EMalformedMsgId,
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_Rx_GetReceivingInstance()
 *********************************************************************************************************************/
/*! \brief          Searches for the instance the message was directed to.
 *  \details        -
 *  \param[in]      RxPduId                 ID of the received I-PDU.
 *  \param[out]     InstanceIdxPtr          Index of instance which matches the I-PDU.
 *                                          [range: InstanceIdx <= Sd_GetSizeOfInstance()]
 *                                          [invalid: Sd_GetSizeOfInstance()]
 *  \param[out]     RxSoConIdPtr            Socket connection ID which was used for reception.
 *  \param[out]     MulticastMessagePtr     Indicates if the message was received via unicast or multicast.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_GetReceivingInstance(
  PduIdType RxPduId,
  SD_P2VAR(Sd_SizeOfInstanceType) InstanceIdxPtr,
  SD_P2VAR(SoAd_SoConIdType) RxSoConIdPtr,
  SD_P2VAR(boolean) MulticastMessagePtr);

/**********************************************************************************************************************
 *  Sd_Util_GetClientServiceId()
 *********************************************************************************************************************/
 /*! \brief         Function returns the ServiceId of a client at position ClientIdx.
 *  \details        -
 *  \param[in]      Idx                     Index of the Sd_Client[] array.
 *  \return         ServiceId of the client at the position ClientIdx.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(uint16, SD_CODE) Sd_Util_GetClientServiceId(
  uint16 Idx);

/**********************************************************************************************************************
 *  Sd_Util_GetServerServiceId()
 *********************************************************************************************************************/
 /*! \brief         Function returns the ServiceId of a server at position ServerIdx.
 *  \details        -
 *  \param[in]      Idx                     Index of the Sd_Server[] array.
 *  \return         ServiceId of the server at the position ServerIdx.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(uint16, SD_CODE) Sd_Util_GetServerServiceId(
  uint16 Idx);

/**********************************************************************************************************************
 *  Sd_Util_GetServices()
 *********************************************************************************************************************/
/*! \brief          Searches for all services with the given ServiceId within the given range.
 *  \details        The function ServiceIdAccessFuncPtr has to be valid to access indices of the following
 *                  range: [(*ServiceStartIdxPtr) .. (*ServiceEndIdxPtr)[
 *  \param[in]      ServiceId               Relevant ServiceId.
 *  \param[in]      ServiceIdAccessFuncPtr  Function which can be used to read the ServiceId at a given location.
 *  \param[in,out]  ServiceStartIdxPtr      Start index for relevant entries.
 *  \param[in,out]  ServiceEndIdxPtr        End index for relevant entries.
 *                                          Note: The ServiceEndIdx value defines the first invalid index.
 *                                          [range: 1 <= ServiceEndIdxPtr <= Sd_GetSizeOf...()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           The ServiceStartIdx and ServiceEndIdx values share the same logic as the StartIdx and EndIdx values
 *                  generated by ComStackLib. Hence, these values can be used as input parameters.
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_GetServices(
  uint16 ServiceId,
  Sd_ServiceIdGetterFctType ServiceIdAccessFuncPtr,
  SD_P2VAR(uint16) ServiceStartIdxPtr,
  SD_P2VAR(uint16) ServiceEndIdxPtr);

/**********************************************************************************************************************
 *  Sd_Rx_SaveAddr()
 *********************************************************************************************************************/
/*! \brief          Saves the address pointed by InAddrPtr.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which handles this address.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      InAddrPtr               Address which shall be saved.
 *  \return         Index of the saved address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfAddressStorageType, SD_CODE) Sd_Rx_SaveAddr(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_SockAddrContainerType) InAddrPtr);

/**********************************************************************************************************************
 *  Sd_Rx_IndexOptionArray()
 *********************************************************************************************************************/
/*! \brief          Reads all attached options and generates an index in order to ease the access of individual options.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_IndexOptionArray(
  SD_P2CONST(PduInfoType) PduInfoPtr);

/**********************************************************************************************************************
 *  Sd_Rx_CheckOption()
 *********************************************************************************************************************/
/*! \brief          Checks if the option is feasible.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      OptionIndex             Start index of the option.
 *  \param[in]      OptionArrayLength       Length of the options array.
 *  \param[out]     CoveredOptionLengthPtr  Covered length of the option.
 *  \return         E_OK                    Option is valid.
 *  \return         E_NOT_OK                Option is invalid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_CheckOption(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint16 OptionIndex,
  uint32 OptionArrayLength,
  SD_P2VAR(uint16) CoveredOptionLengthPtr);

/**********************************************************************************************************************
 *  Sd_Rx_CheckRemoteReboot()
 *********************************************************************************************************************/
/*! \brief          Checks if the remote service has rebooted and handles the reboot.
 *  \details        -
 *  \param[in,out]  RxMessageInfoPtr        Information about the received message.
 *  \param[in]      SdHeaderPtr             Header information.
 *  \param[in]      InstanceIdx             Index of instance which handles this address.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_CheckRemoteReboot(
  SD_P2VAR(Sd_RxMessageInfoType) RxMessageInfoPtr,
  SD_P2CONST(Sd_HeaderType) SdHeaderPtr,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Rx_GetSdEndpointOption()
 *********************************************************************************************************************/
/*! \brief          Checks if an SD endpoint option was attached to the message and extracts it.
 *  \details        -
 *  \param[in]      RxSoConId               Socket connection ID to obtain the subnet.
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[out]     SdEndpointAddressPtr    Pointer to a structure where the SD endpoint address shall be stored.
 *  \return         E_OK                    SD endpoint is valid or no option is attached.
 *  \return         E_NOT_OK                The attached SD endpoint option is invalid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_GetSdEndpointOption(
  SoAd_SoConIdType RxSoConId,
  SD_P2CONST(PduInfoType) PduInfoPtr,
  SD_P2VAR(Sd_SockAddrContainerType) SdEndpointAddressPtr);

/**********************************************************************************************************************
 *  Sd_Rx_GetEndpointOptionParameters()
 *********************************************************************************************************************/
/*! \brief          Reads the parameters of the received endpoint options.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Index of the Option.
 *  \param[in]      ReadMulticastEndpoints  Specifies if unicast or multicast endpoints are allowed and shall be read.
 *  \param[in]      FamilyTypePtr           Address family.
 *  \param[in]      L4ProtocolTypePtr       L4 protocol type of the option.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Rx_GetEndpointOptionParameters(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  boolean ReadMulticastEndpoints,
  SD_P2VAR(Sd_FamilyType) FamilyTypePtr,
  SD_P2VAR(Sd_L4ProtocolType) L4ProtocolTypePtr);

/**********************************************************************************************************************
 *  Sd_Rx_ReadEndpointOptions()
 *********************************************************************************************************************/
/*! \brief          Reads the received endpoint options.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Index of the Option.
 *  \param[in]      FamilyType              Address family.
 *  \param[in]      L4ProtocolType          L4 protocol type of the option.
 *  \param[in,out]  AttachedOptionsPtr      Structure containing all attached options.
 *  \return         SD_OPTIONS_OK           Endpoint is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid Endpoint.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_ReadEndpointOptions(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  Sd_FamilyType FamilyType,
  Sd_L4ProtocolType L4ProtocolType,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_Rx_ReadEndpointOption()
 *********************************************************************************************************************/
/*! \brief          Reads the received endpoint option.
 *  \details        -
 *  \param[in]      FamilyType              Address family.
 *  \param[in]      DataPtr                 Data pointer to the received payload.
 *  \param[in]      DataIndex               Index of the option.
 *  \param[out]     EndpointAddrPtr         Reference where the endpoint address shall be stored.
 *  \return         SD_OPTIONS_OK           Endpoint is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid Endpoint.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_ReadEndpointOption(
  Sd_FamilyType FamilyType,
  SD_P2CONST(uint8) DataPtr,
  uint16 DataIndex,
  SD_P2VAR(Sd_SockAddrContainerType) EndpointAddrPtr);

/**********************************************************************************************************************
 *  Sd_Rx_CheckConfigOption()
 **********************************************************************************************************************/
/*! \brief          Checks the received configuration option.
 *  \details        -
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[in]      IndexOfOption           Index of the Option.
 *  \param[in,out]  ConfigOptionPtrArrayPtr Pointer to the Configuration Option Pointer Array.
 *  \return         SD_OPTIONS_OK           Configuration option is valid.
 *  \return         SD_OPTIONS_NOT_OK       Invalid configuration option.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 **********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckConfigOption(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  SD_P2VAR(Sd_ConfigOptionStringType) ConfigOptionPtrArrayPtr);

/**********************************************************************************************************************
 *  Sd_Rx_FillConfigOptionPtrArray()
 **********************************************************************************************************************/
/*! \brief          Adds information to the configuration option pointer array.
 *  \details        Adds the hostname and capability record configuration options to the configuration
 *                  option pointer array.
 *  \param[in,out]  ConfigOptionPtrArrayPtr   Pointer to the Configuration Option Pointer Array.
 *  \param[in]      InstanceCapabilityIdx     Capability record index of the instance.
 *  \param[in]      ServiceCapabilityIdx      Capability record index of the service.
 *  \param[in]      ServiceCapabilityInvIdx   Invalid capability record index of the service.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 **********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_FillConfigOptionPtrArray(
  SD_P2VAR(Sd_ConfigOptionStringType) ConfigOptionPtrArrayPtr,
  Sd_SizeOfCapabilityRecordType InstanceCapabilityIdx,
  Sd_SizeOfCapabilityRecordType ServiceCapabilityIdx,
  Sd_SizeOfCapabilityRecordType ServiceCapabilityInvIdx);

/**********************************************************************************************************************
 *  Sd_State_HandleRunMode()
 *********************************************************************************************************************/
/*! \brief          Handles the run mode of the given instance.
 *  \details        The RUN_MODE of the instance considers the state of the initialization as well as the IP address
 *                  assignment state.
 *  \param[in]      InstanceIdx             Index of instance to process.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_State_HandleRunMode(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_State_Process()
 *********************************************************************************************************************/
/*! \brief          Processes all state machines of clients and servers.
 *  \details        State machines are only executed if the corresponding timer is exceeded.
 *  \param[in]      InstanceIdx             Index of instance to process.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_State_Process(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Rx_ProcessHeader()
 *********************************************************************************************************************/
/*! \brief          Validates the message header and reads the header fields.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance to process.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      PduInfoPtr              Contains the length (SduLength) of the received I-PDU and a pointer to a
 *                                          buffer (SduDataPtr) containing the I-PDU.
 *  \param[out]     SdHeaderPtr             Pointer where to store the header.
 *  \return         E_OK                    Header is valid.
 *  \return         E_NOT_OK                Invalid Header, SD message is not valid.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_ProcessHeader(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(PduInfoType) PduInfoPtr,
  SD_P2VAR(Sd_HeaderType) SdHeaderPtr);

/**********************************************************************************************************************
 *  Sd_Rx_ProcessEntryArray()
 *********************************************************************************************************************/
/*! \brief          Processes all attached entries of the message.
 *  \details        -
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \param[in]      InstanceIdx             Index of instance to process.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_ProcessEntryArray(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Rx_HandleRemoteReboot()
 *********************************************************************************************************************/
/*! \brief          Handles the remote reboot.
 *  \details        Searches all client and server services which are affected by the reboot of the
 *                  remote service and handles the reboot.
 *  \param[in]      InstanceIdx             Index of the instance which received the message.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Rx_HandleRemoteReboot(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_HandleRemoteRebootUdp()
 *********************************************************************************************************************/
/*! \brief          Handles the UDP socket connections of the rebooted remote client.
 *  \details        Closes and reopens all socket connections which correspond to the rebooted client.
 *  \param[in]      ServerIdx               Index of the instance which received the message.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_RxServer_HandleRemoteRebootUdp(
  Sd_SizeOfServerType ServerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr);

/**********************************************************************************************************************
 *  Sd_RxServer_HandleRemoteRebootTcp()
 *********************************************************************************************************************/
/*! \brief          Handles the TCP socket connections of the rebooted remote client.
 *  \details        Closes and reopens all socket connections which correspond to the rebooted client.
 *  \param[in]      ServerIdx               Index of the instance which received the message.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      RxMessageInfoPtr        Information about the received message.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_RxServer_HandleRemoteRebootTcp(
  Sd_SizeOfServerType ServerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_ProcessPendingMessages()
 *********************************************************************************************************************/
/*! \brief          Processes all pending messages which are ready to transmit (TimeToTriggerSend).
 *  \details        If there is a ready message, also all pending messages with the same destination address
                    will be transmitted.
 *  \param[in]      InstanceIdx             Index of instance which shall be processed.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      ForceTransmission       If set to TRUE, the TimeToSend is ignored in order to transmit all pending
 *                                          messages directly.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_ProcessPendingMessages(
  Sd_SizeOfInstanceType InstanceIdx,
  boolean ForceTransmission);

/**********************************************************************************************************************
 *  Sd_Tx_CheckIfMessageReadyForTransmission()
 *********************************************************************************************************************/
/*! \brief          Checks if there is a message which is ready for transmission.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which shall be processed.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      ForceTransmission       If set to TRUE, the TimeToSend is ignored in order to transmit all pending
 *                                          messages directly.
 *  \return         Destination index of the address storage array.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfAddressStorageType, SD_CODE) Sd_Tx_CheckIfMessageReadyForTransmission(
  Sd_SizeOfInstanceType InstanceIdx,
  boolean ForceTransmission);

/**********************************************************************************************************************
 *  Sd_Tx_GetNextEntryToSend()
 *********************************************************************************************************************/
/*! \brief          Gets next entry which is ready to be sent to the specified address.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which shall be processed.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      AddressStorageIdx       Address storage index defining the destination to transmit messages.
 *                                          [range: AddressStorageIdx < Sd_GetSizeOfAddressStorage()]
 *  \return         Index of entry to SendEntryList.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Tx_GetNextEntryToSend(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx);

/**********************************************************************************************************************
 *  Sd_Tx_CheckIfEntryShallBeSkipped()
 *********************************************************************************************************************/
/*! \brief          Checks if the referenced entry is ready for transmission.
 *  \details        Otherwise the transmission of the entry has to be postponed.
 *  \param[in]      InstanceIdx             Index of instance which shall be processed.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      SendEntryIdx            Entry index to transmit.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \return         TRUE                    Entry is not ready for transmission, skip it.
 *  \return         FALSE                   Entry is ready for transmission.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Tx_CheckIfEntryShallBeSkipped(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfSendEntryType SendEntryIdx);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeMessage()
 *********************************************************************************************************************/
/*! \brief          Serializes pending entries to a single SD message and triggers the transmission.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which triggers transmission.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      AddressStorageIdx       Address with ready SendEntries to be serialized.
 *                                          [range: 0 < Sd_GetSizeOfAddressStorage() - 1]
 *  \return         Number of successfully serialized entries.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Tx_SerializeMessage(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeHeader()
 *********************************************************************************************************************/
/*! \brief          Serializes the header information of the Sd message.
 *  \details        -
 *  \param[in]      AddressStorageIdx       Address storage index defining the destination to transmit messages.
 *                                          [range: AddressStorageIdx < Sd_GetSizeOfAddressStorage()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_SerializeHeader(
  Sd_SizeOfAddressStorageType AddressStorageIdx);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeRelatedOptions()
 *********************************************************************************************************************/
/*! \brief          Serializes all options of the referenced entry to the payload.
 *  \details        -
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[out]     EntryToOptionMapPtr     Information about the entry to option mapping.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \return         TRUE                    Buffer was too small to serialize related options.
 *  \return         FALSE                   All related options were serialized to the payload.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeRelatedOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEntryAndOptions()
 *********************************************************************************************************************/
/*! \brief          Serializes the referenced entry and corresponding options to the payload.
 *  \details        -
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[in]      PayloadEntryIdx         Payload start index to serialize entry to.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \return         TRUE                    Buffer was too small to serialize related options.
 *  \return         FALSE                   All related options were serialized to the payload.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeEntryAndOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfPayloadType PayloadEntryIdx,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_GetRelevantEndpointOptions()
 *********************************************************************************************************************/
/*! \brief          Analyzes which endpoint options have to be attached to the message.
 *  \details        -
 *  \param[in]      SendEntryIdx              Index of entry to send.
 *                                            [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[out]     SockAddrContainerUdpPtr   Reference to the relevant UDP address.
 *  \param[out]     SockAddrContainerTcpPtr   Reference to the relevant TCP address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_GetRelevantEndpointOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_SockAddrContainerType) SockAddrContainerUdpPtr,
  SD_P2VAR(Sd_SockAddrContainerType) SockAddrContainerTcpPtr);

/**********************************************************************************************************************
 *  Sd_Tx_GetRelevantConfigOptions()
 *********************************************************************************************************************/
/*! \brief          Analyzes if a configuration option has to be attached at the message.
 *  \details        -
 *  \param[in]      SendEntryIdx                  Index of entry to send.
 *                                                [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[out]     HostnameStartIdxPtr           Start index of hostname.
 *  \param[out]     HostnameEndIdxPtr             End index of hostname.
 *  \param[out]     CapabilityRecordStartIdxPtr   Start index of capability record.
 *  \param[out]     CapabilityRecordEndIdxPtr     End index of capability record.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_GetRelevantConfigOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) HostnameStartIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) HostnameEndIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) CapabilityRecordStartIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) CapabilityRecordEndIdxPtr);

/**********************************************************************************************************************
 *  Sd_Tx_CheckForDuplicateOption()
 *********************************************************************************************************************/
/*! \brief          Checks the payload for duplicated options.
 *  \details        Reads the serialized payload and checks if the option which was serializes after the end of the
 *                  options array can be deduplicated.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_CheckForDuplicateOption(
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_DeduplicateOption()
 *********************************************************************************************************************/
/*! \brief          Tries to deduplicate the option.
 *  \details        Not all possible combinations of options can be deduplicated, because all relevant options of the
 *                  message have to be referenced by the two option runs.
 *  \param[in,out]  EntryToOptionMapPtr     Information about the entry to option mapping.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \param[in]      RemainingOption         Indicates if the current option is the last one which has to be processed.
 *  \return         TRUE                    Option was deduplicated.
 *  \return         FALSE                   Algorithm was not able to deduplicate option.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Tx_DeduplicateOption(
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr,
  boolean RemainingOption);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEndpointOptions()
 *********************************************************************************************************************/
/*! \brief          Serializes all required endpoint options to the payload.
 *  \details        -
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[in,out]  EntryToOptionMapPtr     Information about the entry to option mapping.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeEndpointOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEndpointOption()
 *********************************************************************************************************************/
/*! \brief          Serializes an endpoint option to the payload.
 *  \details        -
 *  \param[in]      SendEntryType           Entry type which is serialized.
 *  \param[in]      LocalIpAddrPtr          Address which shall be copied to the endpoint option.
 *  \param[in]      L4Proto                 Which L4-Protocol (UDP/TCP) has the option.
 *  \param[in]      PayloadOffset           Start offset for the option.
 *  \return         The length of the serialized option.
 *                  [invalid: SD_INV_OPTION_LENGTH if buffer is too small]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(uint16, SD_CODE) Sd_Tx_SerializeEndpointOption(
  Sd_EntryType SendEntryType,
  SD_P2CONST(Sd_SockAddrContainerType) LocalIpAddrPtr,
  Sd_L4ProtocolType L4Proto,
  uint16 PayloadOffset);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeConfigurationOptions()
 *********************************************************************************************************************/
/*! \brief          Serializes all required configuration options to the payload.
 *  \details        -
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[in,out]  EntryToOptionMapPtr     Information about the entry to option mapping.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeConfigurationOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr);

/**********************************************************************************************************************
 *  Sd_Tx_SerializeConfigurationOption()
 *********************************************************************************************************************/
/*! \brief          Serializes a configuration option to the payload.
 *  \details        -
 *  \param[in]      ConfigurationOptionStartIdx   Start index of configuration option.
 *  \param[in]      ConfigurationOptionEndIdx     End index of configuration option.
 *  \param[in]      PayloadOffset                 Start offset for the option.
 *  \return         The length of the serialized option.
 *                  [invalid: SD_INV_OPTION_LENGTH if buffer is too small]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(uint16, SD_CODE) Sd_Tx_SerializeConfigurationOption(
  Sd_SizeOfCapabilityRecordType ConfigurationOptionStartIdx,
  Sd_SizeOfCapabilityRecordType ConfigurationOptionEndIdx,
  uint16 PayloadOffset);

/**********************************************************************************************************************
 *  Sd_Tx_UseNewSerializedOption()
 *********************************************************************************************************************/
/*! \brief          Updates the entry to option mapping in order to reference the new serialized option.
 *  \details        -
 *  \param[in,out]  EntryToOptionMapPtr     Information about the entry to option mapping.
 *  \param[in,out]  OptionArrayInfoPtr      Information about the options array.
 *  \param[in]      NewOptionSize           Size of new serialized option.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_UseNewSerializedOption(
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr,
  uint16 NewOptionSize);

/**********************************************************************************************************************
 *  Sd_UtilClient_CloseAllMulticastSoCons()
 *********************************************************************************************************************/
/*! \brief          Closes all multicast socket connections of the eventgroup.
 *  \details        -
 *  \param[in]      ConsumedEventgroupIdx   Corresponding consumed eventgroup index.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      Abort                   Indicates if the socket connections shall be aborted.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_CloseAllMulticastSoCons(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean Abort);

/**********************************************************************************************************************
 *  Sd_UtilClient_ResetDynamicVariables()
 *********************************************************************************************************************/
/*! \brief          Reset all dynamic variables of the given client.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ResetDynamicVariables(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_UtilClient_LocalIpAddrAssignmentChgReset()
 *********************************************************************************************************************/
/*! \brief          Resets all dynamic client data in the case of a local IP address assignment change.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance which has to be reset.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilClient_LocalIpAddrAssignmentChgReset(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_UtilClient_SetCurrentStateInformBswm()
 *********************************************************************************************************************/
/*! \brief          Updates the current state of the client and informs the BswM.
 *  \details        -
 *  \param[in]      ClientIdx               Corresponding client index.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \param[in]      State                   New state of the client.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_SetCurrentStateInformBswm(
  Sd_SizeOfClientType ClientIdx,
  Sd_ClientServiceCurrentStateType State);

/**********************************************************************************************************************
 *  Sd_Util_SetTcpSoConMode()
 *********************************************************************************************************************/
/*! \brief          Saves the current mode of the socket connection.
 *  \details        -
 *  \param[in]      SoConId                 Socket connection ID specifying the socket connection with the mode change.
 *  \param[in]      Mode                    New socket connection mode.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTcpSoConMode(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode);

/**********************************************************************************************************************
 *  Sd_Util_GetTcpSoConMode()
 *********************************************************************************************************************/
/*! \brief          Returns the current mode of the socket connection.
 *  \details        -
 *  \param[in]      SoConId                 Socket connection ID specifying the socket connection.
 *  \return         Mode of the socket connection.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_SoConModeType, SD_CODE) Sd_Util_GetTcpSoConMode(
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_Util_ResetSessionIds()
 *********************************************************************************************************************/
/*! \brief          Resets all used SessionIDs of the given instance.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance to reset SessionIDs.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetSessionIds(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_GetEmptySendEntry()
 *********************************************************************************************************************/
/*! \brief          Searches for an unused slot in the SendEntriesList and return the entry.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of the instance handling the event.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \return         Index of the empty Slot.
 *                  [range: Sd_GetSendEntryStartIdxOfInstance(InstanceIdx) <= return < Sd_GetSendEntryEndIdxOfInstance(InstanceIdx)]
 *                  [invalid: Sd_GetSendEntryEndIdxOfInstance(InstanceIdx)]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Util_GetEmptySendEntry(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_RemoveSendEntryFromList()
 *********************************************************************************************************************/
/*! \brief          Removes the referenced entry from the linked list of send entries.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of the instance handling the event.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      RemoveEntryIdx          Entry index to remove.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_RemoveSendEntryFromList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfSendEntryType RemoveEntryIdx);

/**********************************************************************************************************************
 *  Sd_Util_CheckSendEntryListFullAndTransmit()
 *********************************************************************************************************************/
/*! \brief          Check if the list of pending send entries is full and trigger a transmission.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of the instance with pending send entries.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_CheckSendEntryListFullAndTransmit(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_AddFindEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds a FindService message to the list of send entries.
 *  \details        -
 *  \param[in,out]  ClientIdx               Client index searching for service.
 *                                          [range: ClientIdx < Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddFindEntryToList(
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_Util_AddMulticastOfferEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds an OfferService message via multicast to the list of send entries.
 *  \details        -
 *  \param[in,out]  ServerIdx               Server index offering its availability.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      StopOffer               TRUE  = StopOfferService message.
                                            FALSE = OfferService message.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddMulticastOfferEntryToList(
  Sd_SizeOfServerType ServerIdx,
  boolean StopOffer);

/**********************************************************************************************************************
 *  Sd_Util_AddUnicastOfferEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds an OfferService message via unicast to the list of send entries.
 *  \details        -
 *  \param[in,out]  ServerIdx               Corresponding server index.
 *                                          [range: ServerIdx < Sd_GetSizeOfServer()]
 *  \param[in]      SavedAddressStorageIdx  Destination address index.
 *                                          [range: AddressStorageIdx < Sd_GetSizeOfAddressStorage()]
 *  \param[in]      TransmissionOffset      Timing offset when the message shall be transmitted.
                                            (Random delay for responses to multicast messages.)
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddUnicastOfferEntryToList(
  Sd_SizeOfServerType ServerIdx,
  Sd_SizeOfAddressStorageType SavedAddressStorageIdx,
  uint32 TransmissionOffset);

/**********************************************************************************************************************
 *  Sd_Util_AddSubscribeEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds a SubscribeEventgroup message to the list of send entries.
 *  \details        -
 *  \param[in,out]  ConsumedEventgroupIdx   Consumed eventgroup index which triggers the subscription.
 *                                          [range: ConsumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup()]
 *  \param[in]      Subscribe               TRUE  = SubscribeEventgroup message.
                                            FALSE = StopSubscribeEventgroup message.
 *  \param[in]      TransmissionOffset      Timing offset when the message shall be transmitted.
                                            (Random delay for responses to multicast messages.)
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddSubscribeEntryToList(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean Subscribe,
  uint32 TransmissionOffset);

/**********************************************************************************************************************
 *  Sd_Util_AddEventGroupAckEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds a SubscribeEventgroupAck message to the list of send entries.
 *  \details        -
 *  \param[in,out]  InstanceIdx             Index of instance handling the event.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      RxEventIdx              Received event.
 *                                          [range: RxEventIdx < Sd_GetSizeOfRxEvent()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddEventGroupAckEntryToList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType RxEventIdx);

/**********************************************************************************************************************
 *  Sd_Util_AddEventGroupNackEntryToList()
 *********************************************************************************************************************/
/*! \brief          Adds a SubscribeEventgroupNack message to the list of send entries.
 *  \details        -
 *  \param[in,out]  InstanceIdx             Index of instance where the NACK-Message should be handled.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      ServerIdx               Server service.
 *                                          [range: ServerIdx <= Sd_GetSizeOfServer()]
 *                                          [invalid: Sd_GetSizeOfServer()]
 *  \param[in]      ServiceId               ServiceId of the rejected SubscribeEventgroup Message.
 *  \param[in]      InstanceId              InstanceId of the rejected SubscribeEventgroup Message.
 *  \param[in]      MajorVersion            MajorVersion of the rejected SubscribeEventgroup Message.
 *  \param[in]      ReservedField           ReservedField of the rejected SubscribeEventgroup Message.
 *  \param[in]      EventHandlerId          EventHandlerId of the rejected SubscribeEventgroup Message.
 *  \param[in]      AddressStorageIdx       Destination address index.
 *                                          [range: AddressStorageIdx < Sd_GetSizeOfAddressStorage()]
 *  \param[in]      ServerTimerIdx          Index of the server timer used for calculation of the additional delay.
 *                                          [range: ServerTimerIdx <= Sd_GetSizeOfServerTimer()]
 *                                          [invalid: Sd_GetSizeOfServerTimer()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddEventGroupNackEntryToList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfServerType ServerIdx,
  uint16 ServiceId,
  uint16 InstanceId,
  uint8 MajorVersion,
  uint16 ReservedField,
  uint16 EventHandlerId,
  Sd_SizeOfAddressStorageType AddressStorageIdx,
  Sd_SizeOfServerTimerType ServerTimerIdx);

/**********************************************************************************************************************
 *  Sd_UtilServer_ConfigureEntry()
 *********************************************************************************************************************/
/*! \brief          Initialize all server based parameters of the send entry.
 *  \details        Unused parameters will be initialized with invalid values.
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[in]      ServerIdx               Server service.
 *                                          [range: ServerIdx <= Sd_GetSizeOfServer()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_ConfigureEntry(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfServerType ServerIdx);

/**********************************************************************************************************************
 *  Sd_UtilClient_ConfigureEntry()
 *********************************************************************************************************************/
/*! \brief          Initialize all client based parameters of the send entry.
 *  \details        Unused parameters will be initialized with invalid values.
 *  \param[in]      SendEntryIdx            Index of entry to send.
 *                                          [range: SendEntryIdx < Sd_GetSizeOfSendEntry()]
 *  \param[in]      ClientIdx               Client service.
 *                                          [range: ClientIdx <= Sd_GetSizeOfClient()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilClient_ConfigureEntry(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfClientType ClientIdx);

/**********************************************************************************************************************
 *  Sd_Util_CopySockAddr()
 *********************************************************************************************************************/
/*! \brief          Copies socket addr (incl. family, port, IP-addr) from source to target.
 *  \details        -
 *  \param[in,out]  TgtSockPtr              Target socket address.
 *  \param[in]      SrcSockPtr              Source socket address.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_CopySockAddr(
  SD_P2VAR(Sd_SockAddrContainerType) TgtSockPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SrcSockPtr);

/**********************************************************************************************************************
 *  Sd_Util_CompareSockAddrIp()
 *********************************************************************************************************************/
/*! \brief          Checks if IP addresses of the sockets are equal.
 *  \details        -
 *  \param[in]      SockAPtr                Target socket address.
 *  \param[in]      SockBPtr                Source socket address.
 *  \param[in]      AddrState               State of the source socket address.
 *  \return         SD_MATCH_FALSE          IP addresses are not identical.
 *  \return         SD_MATCH_TRUE           IP addresses are identical.
 *  \return         SD_MATCH_ANY            IP addresses match because of ANY state.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           The caller has to ensure that SockAPtr and/or SockBPtr point to valid addresses with
 *                  family != SOAD_AF_INVALID.
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_MatchType, SD_CODE) Sd_Util_CompareSockAddrIp(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 AddrState);

/**********************************************************************************************************************
 *  Sd_Util_CompareSockAddrPort()
 *********************************************************************************************************************/
/*! \brief          Checks if the ports of the sockets are equal.
 *  \details        -
 *  \param[in]      SockAPtr                Target socket address.
 *  \param[in]      SockBPtr                Source socket address.
 *  \param[in]      AddrState               State of the source socket address.
 *  \return         SD_MATCH_FALSE          Ports are not identical.
 *  \return         SD_MATCH_TRUE           Ports are identical.
 *  \return         SD_MATCH_ANY            IP addresses match because of ANY state.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           The caller has to ensure that SockAPtr and/or SockBPtr point to valid addresses with
 *                  family != SOAD_AF_INVALID.
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_MatchType, SD_CODE) Sd_Util_CompareSockAddrPort(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 AddrState);

/**********************************************************************************************************************
 *  Sd_Util_SockAddrIsEqual()
 *********************************************************************************************************************/
/*! \brief          Checks if IP addresses and ports of the sockets are equal.
 *  \details        -
 *  \param[in]      SockAPtr                Target socket address.
 *  \param[in]      SockBPtr                Source socket address.
 *  \return         TRUE                    IP addresses and ports are equal.
 *  \return         FALSE                   IP addresses and/or ports are not equal.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Util_SockAddrIsEqual(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr);

/**********************************************************************************************************************
 *  Sd_Rx_CheckSubnets()
 *********************************************************************************************************************/
/*! \brief          Checks if the attached endpoint options are within the same subnet.
 *  \details        Endpoints which are not within the configured subnet are ignored.
 *  \param[in]      UdpSoConIdx             Index of UDP socket connection to compare to.
 *                                          [range: UdpSoConIdx <= Sd_GetSizeOfUdpSoCon()]
 *                                          [invalid: Sd_GetSizeOfUdpSoCon()]
 *  \param[in]      TcpSoConIdIdx           Index of TCP socket connection to compare to.
 *                                          [range: TcpSoConIdIdx <= Sd_GetSizeOfTcpSoConId()]
 *                                          [invalid: Sd_GetSizeOfTcpSoConId()]
 *  \param[in,out]  AttachedOptionsPtr      Structure containing the attached options which shall be checked.
 *  \return         SD_OPTIONS_OK           Local address could be read.
 *  \return         SD_OPTIONS_NOT_OK       Failed to read the local address.
 *  \return         SD_OPTIONS_WRONG_SUBNET Option is not topological correct (wrong subnet).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckSubnets(
  Sd_SizeOfUdpSoConType UdpSoConIdx,
  Sd_SizeOfTcpSoConIdType TcpSoConIdIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr);

/**********************************************************************************************************************
 *  Sd_Rx_CheckSubnet()
 *********************************************************************************************************************/
/*! \brief          Checks if the endpoint address is within the same subnet as the given socket connection.
 *  \details        -
 *  \param[in]      SoConId                 Index of UDP socket connection to compare to.
 *  \param[in,out]  EndpointAddrPtr         IP address pointer of the received endpoint.
 *  \return         SD_OPTIONS_OK           Option is within the given subnet.
 *  \return         SD_OPTIONS_NOT_OK       Failed to read the local address.
 *  \return         SD_OPTIONS_WRONG_SUBNET Option is not topological correct (wrong subnet).
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckSubnet(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) EndpointAddrPtr);

/**********************************************************************************************************************
 *  Sd_Rx_SockAddrWithinSubnet()
 *********************************************************************************************************************/
/*! \brief          Checks if both IP addresses are within the same subnet.
 *  \details        -
 *  \param[in]      SockAPtr                Socket address A.
 *  \param[in]      SockBPtr                Socket address B.
 *  \param[in]      NetmaskCidr             Net mask in CIDR notation.
 *  \return         TRUE                    IP addresses are within the same subnet.
 *  \return         FALSE                   IP addresses are not within the same subnet.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Rx_SockAddrWithinSubnet(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 NetmaskCidr);

/**********************************************************************************************************************
 *  Sd_Util_ReportDemEvent()
 *********************************************************************************************************************/
/*! \brief          Reports the configured DEM event.
 *  \details        -
 *  \param[in]      EventId                 Configured event ID.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ReportDemEvent(
  Sd_Dem_EventIdType EventId);

/**********************************************************************************************************************
 *  Sd_Util_GetRandomNrInRange()
 *********************************************************************************************************************/
/*! \brief          Returns a random value.
 *  \details        The value is within the range: MinValue <= Random <= MaxValue.
 *  \param[in]      MinValue                Minimal allowed value.
 *  \param[in]      MaxValue                Maximal allowed value.
 *  \return         Random number.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(uint32, SD_CODE) Sd_Util_GetRandomNrInRange(
  uint32 MinValue,
  uint32 MaxValue);

/**********************************************************************************************************************
 *  Sd_Util_GetRandomNrInRangeForResponse()
 *********************************************************************************************************************/
/*! \brief          Returns a random value which can be used to delay a response message.
 *  \details        The function uses the information if it is called from InterruptContext or not in order to adjust
 *                  the MinValue and/or the MaxValue of the range, because the system time is only updated in context
 *                  of the main function.
 *  \param[in]      MinValue                Minimal allowed value.
 *                                          [MinValue has to be multiple of SD_MAIN_FCT_CYCLE_TIME_MS]
 *  \param[in]      MaxValue                Maximal allowed value.
 *                                          [MaxValue has to be multiple of SD_MAIN_FCT_CYCLE_TIME_MS]
 *  \param[in]      InterruptContext        Specifies if the function is called from context of message reception or context
 *                                          of MainFunction.
 *  \return         Random number.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(uint32, SD_CODE) Sd_Util_GetRandomNrInRangeForResponse(
  uint32 MinValue,
  uint32 MaxValue,
  boolean InterruptContext);

/**********************************************************************************************************************
 *  Sd_Util_CheckIfTimerExceeded()
 *********************************************************************************************************************/
/*! \brief          Checks if the timer is already exceeded.
 *  \details        -
 *  \param[in]      Timer                   Timer to be checked.
 *  \param[in]      EqualIsExceeded         If set to TRUE, the timer is also indicated as exceeded if it is equal to the
 *                                          current time.
 *                                          [EqualIsExceeded == TRUE is not allowed for comparison of TTL values.]
 *  \return         TRUE                    Timer is exceeded.
 *  \return         FALSE                   Timer is not exceeded.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           If the timer of TTL values is checked, the EqualIsExceeded flag has to be set to FALSE.
 *********************************************************************************************************************/
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Util_CheckIfTimerExceeded(
  Sd_ExtendedTimeType Timer,
  boolean EqualIsExceeded);

/**********************************************************************************************************************
 *  Sd_Util_TriggerStateMachineRun()
 *********************************************************************************************************************/
/*! \brief          Triggers a state machine execution at the next MainFunction.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_TriggerStateMachineRun(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_SetNextStateMachineRun()
 *********************************************************************************************************************/
/*! \brief          Triggers a state machine execution at the point in time given by the timer parameter.
 *  \details        -
 *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \param[in]      Timer                   Time to trigger next state machine execution.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetNextStateMachineRun(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_ExtendedTimeType Timer);

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffsetWithTrigger()
 *********************************************************************************************************************/
/*! \brief          Updates the timer to the actual time plus the given offset.
 *  \details        Function also triggers an execution of all state machines of the given instance if the
 *                  timer expires.
 *  \param[in,out]  TimerPtr                Timer to Update.
 *  \param[in]      OffsetMs                Offset when the timer shall expire. [MSEC]
 *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           This function cannot be used to handle received TTL values because of the limited size of the
 *                  OffsetMs parameter.
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffsetWithTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetMs,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffsetSecWithTrigger()
 *********************************************************************************************************************/
/*! \brief          Updates the timer to the actual time plus the given offset.
 *  \details        Function also triggers an execution of all state machines of the given instance if the
 *                  timer expires.
 *  \param[in,out]  TimerPtr                Timer to Update.
 *  \param[in]      OffsetSec               Offset when the timer shall expire. [SEC]
 *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           This function should be used to handle received TTL values.
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffsetSecWithTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetSec,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffset()
 *********************************************************************************************************************/
/*! \brief          Updates the timer to the actual time plus the given offset.
 *  \details        -
 *  \param[in,out]  TimerPtr                Timer to Update.
 *  \param[in]      OffsetMs                Offset when the timer shall expire.  [MSEC]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           This function cannot be used to handle received TTL values because of the limited size of the
 *                  OffsetMs parameter.
 *********************************************************************************************************************/
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffset(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetMs);

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToZero()
 *********************************************************************************************************************/
/*! \brief          Resets the given timer to zero.
 *  \details        -
 *  \param[in,out]  TimerPtr                Timer to reset.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToZero(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr);

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToZeroTrigger()
 *********************************************************************************************************************/
/*! \brief          Resets the given timer to zero.
 *  \details        Function also triggers an execution of all state machines of the given instance.
 *  \param[in,out]  TimerPtr                Timer to Update.
 *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
 *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToZeroTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToInvalid()
 *********************************************************************************************************************/
/*! \brief          Resets the given timer to the invalid value.
 *  \details        -
 *  \param[in,out]  TimerPtr                Timer to reset.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToInvalid(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr);

/**********************************************************************************************************************
 *  Sd_Util_DisableRouting()
 *********************************************************************************************************************/
/*! \brief          Calls SoAd to disable a RoutingGroup if routing for this group is not disabled already.
 *  \details        -
 *  \param[in]      RoutingGroupIdx         The index to Sd_RoutingGroup.
 *                                          [range: RoutingGroupIdx < Sd_GetSizeOfRoutingGroup()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_DisableRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx);

/**********************************************************************************************************************
 *  Sd_Util_DisableSpecificRouting()
 *********************************************************************************************************************/
/*! \brief          Calls SoAd to disable one specific routing of a RoutingGroup.
 *  \details        -
 *  \param[in]      RoutingGroupIdx         The index to Sd_RoutingGroup.
 *                                          [range: RoutingGroupIdx < Sd_GetSizeOfRoutingGroup()]
 *                  SoConId                 The SocketConnection Id for which the routing shall be disabled.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_DisableSpecificRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_Util_EnableRouting()
 *********************************************************************************************************************/
/*! \brief          Calls SoAd to enable a RoutingGroup if routing for this group is not enabled already.
 *  \details        -
 *  \param[in]      RoutingGroupIdx         The index to Sd_RoutingGroup.
 *                                          [range: RoutingGroupIdx < Sd_GetSizeOfRoutingGroup()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_EnableRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx);

/**********************************************************************************************************************
 *  Sd_Util_EnableSpecificRouting()
 *********************************************************************************************************************/
/*! \brief          Calls SoAd to enable one specific routing of a RoutingGroup.
 *  \details        -
 *  \param[in]      RoutingGroupIdx         The index to Sd_RoutingGroup.
 *                                          [range: RoutingGroupIdx < Sd_GetSizeOfRoutingGroup()]
 *                  SoConId                 The SocketConnection Id for which the routing shall be enabled.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_EnableSpecificRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx,
  SoAd_SoConIdType SoConId);

/**********************************************************************************************************************
 *  Sd_Util_SetAllStateMachineExecutionFlags()
 *********************************************************************************************************************/
 /*! \brief          Sets state machine execution flags for all server and client services.
  *  \details        -
  *  \param[in]      InstanceIdx             Index of instance to trigger state machine execution.
  *                                          [range: InstanceIdx < Sd_GetSizeOfInstance()]
  *  \pre            -
  *  \context        TASK|ISR2
  *  \reentrant      FALSE
  *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_SetAllStateMachineExecutionFlags(
  Sd_SizeOfInstanceType InstanceIdx);

/**********************************************************************************************************************
 *  Sd_Util_Write32Bit()
 *********************************************************************************************************************/
/*! \brief          Write the 32 bit value to the given buffer.
 *  \details        -
 *  \param[in,out]  BufferPtr               Buffer to write to.
 *                                          Ensure that the buffer contains at least four additional elements.
 *  \param[in]      Value                   Value to write to the buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write32Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint32 Value);

/**********************************************************************************************************************
 *  Sd_Util_Write24Bit()
 *********************************************************************************************************************/
/*! \brief          Write the 24 bit value to the given buffer. (Lower three bytes of the 32 bit value.)
 *  \details        -
 *  \param[in,out]  BufferPtr               Buffer to write to.
 *                                          Ensure that the buffer contains at least three additional elements.
 *  \param[in]      Value                   Value to write to the buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write24Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint32 Value);

/**********************************************************************************************************************
 *  Sd_Util_Write16Bit()
 *********************************************************************************************************************/
/*! \brief          Write the 16 bit value to the given buffer.
 *  \details        -
 *  \param[in,out]  BufferPtr               Buffer to write to.
 *                                          Ensure that the buffer contains at least two additional elements.
 *  \param[in]      Value                   Value to write to the buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write16Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint16 Value);

/**********************************************************************************************************************
 *  Sd_Util_Write8Bit()
 *********************************************************************************************************************/
/*! \brief          Write the 8 bit value to the given buffer.
 *  \details        -
 *  \param[in,out]  BufferPtr               Buffer to write to.
 *                                          Ensure that the buffer contains at least one additional elements.
 *  \param[in]      Value                   Value to write to the buffer.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write8Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint8 Value);

/**********************************************************************************************************************
 *  Sd_SoAd_GetLocalAddrWithNetmask()
 *********************************************************************************************************************/
/*! \brief          Read the local address and the configured netmask of the socket connection.
 *  \details        If the local address can not be read or the family type is unknown, the family type is set to
 *                  the invalid value.
 *  \param[in]      SoConId                 Socket connection ID.
 *  \param[out]     LocalAddrPtr            Address container for local address.
 *  \param[out]     NetmaskPtr              Pointer to network mask in CIDR notation.
 *  \return         E_OK                    Local address successfully read with valid family type.
 *  \return         E_NOT_OK                Failed to read local address or address has unknown family type.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetLocalAddrWithNetmask(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) LocalAddrPtr,
  SD_P2VAR(uint8) NetmaskPtr);

/**********************************************************************************************************************
 *  Sd_SoAd_GetLocalAddr()
 *********************************************************************************************************************/
/*! \brief          Read the local address of the socket connection.
 *  \details        If the local address can not be read or the family type is unknown, the family type is set to
 *                  the invalid value.
 *  \param[in]      SoConId                 Socket connection ID.
 *  \param[out]     LocalAddrPtr            Address container for local address.
 *  \return         E_OK                    Local address successfully read with valid family type.
 *  \return         E_NOT_OK                Failed to read local address or address has unknown family type.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetLocalAddr(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) LocalAddrPtr);

/**********************************************************************************************************************
 *  Sd_SoAd_GetRemoteAddr()
 *********************************************************************************************************************/
/*! \brief          Read the remote address of the socket connection.
 *  \details        If the remote address can not be read or the family type is unknown, the family type is set to
 *                  the invalid value.
 *  \param[in]      SoConId                 Socket connection ID.
 *  \param[out]     IpAddrPtr               Address container for remote address.
 *  \return         E_OK                    Remote address successfully read with valid family type.
 *  \return         E_NOT_OK                Failed to read remote address or address has unknown family type.
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetRemoteAddr(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) IpAddrPtr);

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sd_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module state to uninitialized. */
  Sd_State = SD_UNINIT;

  /* #20 Initialize local data. */
  Sd_ConfigDataPtr = NULL_PTR;
  Sd_RxIndicationCount = 0u;
  Sd_TimeMsSinceStart.Seconds = 0u;
  Sd_TimeMsSinceStart.Milliseconds = 0u;
}

/**********************************************************************************************************************
 *  Sd_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_Init(
  P2CONST(Sd_ConfigType, AUTOMATIC, SD_INIT_DATA) ConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;

  Sd_ConfigDataPtr = ConfigPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(ConfigPtr == NULL_PTR)
  {
# if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
    EcuM_BswErrorHook(SD_MODULE_ID, ECUM_BSWERROR_NULLPTR);
# endif
    errorId = SD_E_PARAM_POINTER;
  }
# if(SD_FINALMAGICNUMBER == STD_ON)
  else if(Sd_GetFinalMagicNumber() != SD_FINAL_MAGIC_NUMBER)
  {
#  if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)                                          /* COV_SD_VAR_DEPENDENT_SWITCH */
    EcuM_BswErrorHook(SD_MODULE_ID, ECUM_BSWERROR_MAGICNUMBER);
#  endif
    errorId = SD_E_PARAM_CONFIG;
  }
# endif
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize general data. */
    Sd_Init_General();

    /* #30 Initialize instance data. */
    Sd_Init_Instance();

    /* #40 Initialize server data. */
    Sd_Init_Server();

    /* #50 Initialize client data. */
    Sd_Init_Client();

    /* #60 Set the state to initialized. */
    Sd_State = SD_INIT;
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_INIT, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
}

/**********************************************************************************************************************
 *  Sd_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  Sd_SizeOfInstanceType instanceIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of runtime parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Update the time since start of the Sd_Init() function. */
    Sd_Util_SetTimerOffset(&Sd_TimeMsSinceStart, SD_MAIN_FCT_CYCLE_TIME_MS);                                            /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #30 Iterate over all instances. */
    for(instanceIdx = 0u; instanceIdx < Sd_GetSizeOfInstance(); instanceIdx++)
    {
      /* #300 Handle the run mode of the current instance. */
      Sd_State_HandleRunMode(instanceIdx);

      /* #301 Process pending server events. */
      Sd_EventServer_Process(instanceIdx);

      /* #302 Process pending state machine executions. */
      Sd_State_Process(instanceIdx);

      /* #303 Process pending messages. Serialize message and trigger transmission. */
      Sd_Tx_ProcessPendingMessages(instanceIdx, FALSE);
    }

    /* #40 Process pending trigger transmit requests. */
    Sd_TriggerTransmit_Process();
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_MAIN_FUNCTION, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
}

#if(SD_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  Sd_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SD_APPL_VAR) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                     /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = SD_E_PARAM_POINTER;
  }
  else
# endif /* SD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Set VersionInfo structure with corresponding macros. */
    VersionInfoPtr->vendorID = (SD_VENDOR_ID);                                                                          /* SBSW_SD_GETVERSION_PARAM */
    VersionInfoPtr->moduleID = (SD_MODULE_ID);                                                                          /* SBSW_SD_GETVERSION_PARAM */
    VersionInfoPtr->sw_major_version = (uint8)(SD_SW_MAJOR_VERSION);                                                    /* SBSW_SD_GETVERSION_PARAM */
    VersionInfoPtr->sw_minor_version = (uint8)(SD_SW_MINOR_VERSION);                                                    /* SBSW_SD_GETVERSION_PARAM */
    VersionInfoPtr->sw_patch_version = (uint8)(SD_SW_PATCH_VERSION);                                                    /* SBSW_SD_GETVERSION_PARAM */
  }

  /* ----- Development Error Report --------------------------------------- */
# if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_GET_VERSION_INFO, errorId);
  }
# else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
# endif /* SD_DEV_ERROR_REPORT == STD_ON */
}
#endif

/**********************************************************************************************************************
 *  Sd_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, SD_APPL_DATA) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  Std_ReturnType retVal;
  Sd_SizeOfInstanceType instanceIdx;
  Sd_HeaderType sdHeader;
  Sd_RxMessageInfoType messageInfo;
  SoAd_SoConIdType rxSoConId = 0u;
  Sd_SockAddrContainerType remoteAddr;

  /* Increment RxIndication counter in order to be able to distinguish received packets. Overflows are expected. */
  Sd_RxIndicationCount++;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if(PduInfoPtr == NULL_PTR)
  {
    errorId = SD_E_PARAM_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    messageInfo.PduInfoPtr = PduInfoPtr;
    messageInfo.RebootDetected = FALSE;
    messageInfo.MulticastMessage = FALSE;

    /* #20 Find the corresponding instance. */
    Sd_Rx_GetReceivingInstance(RxPduId, &instanceIdx, &rxSoConId, &messageInfo.MulticastMessage);                       /* SBSW_SD_REFERENCE_OF_VARIABLE */

    if(instanceIdx < Sd_GetSizeOfInstance())
    {
      /* #30 The correct instance was found, read and validate message header. */
      if(Sd_Rx_ProcessHeader(instanceIdx, PduInfoPtr, &sdHeader) == E_OK)                                               /* SBSW_SD_PUBLIC_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      {
        /* #31 Generate an index of all attached options to be able to address them directly. */
        Sd_Rx_IndexOptionArray(PduInfoPtr);                                                                             /* SBSW_SD_PUBLIC_API_POINTER */

        /* #32 Check if an SD endpoint option was attached and save it. */
        retVal = Sd_Rx_GetSdEndpointOption(Sd_GetUnicastRxSoConIdOfInstance(instanceIdx), PduInfoPtr, &remoteAddr);     /* SBSW_SD_PUBLIC_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

        if(remoteAddr.family == SOAD_AF_INVALID)
        {
          /* #320 No valid SD endpoint was attached, use the remote address of the sender. */
          /* PRQA S 0310 1 */ /* MD_Sd_11.4_0310 */
          retVal |= SoAd_GetRcvRemoteAddr(rxSoConId, (SD_P2VAR(SoAd_SockAddrType))(&remoteAddr));                       /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */
        }

        if(retVal == E_OK)
        {
          /* #330 Save the remote address. */
          messageInfo.AddressStorageIdx = Sd_Rx_SaveAddr(instanceIdx, &remoteAddr);                                     /* SBSW_SD_REFERENCE_OF_VARIABLE */

          if(messageInfo.AddressStorageIdx < Sd_GetSizeOfAddressStorage())
          {
            /* #3300 Check if the remote service has rebooted. */
            Sd_Rx_CheckRemoteReboot(&messageInfo, &sdHeader, instanceIdx);                                              /* SBSW_SD_REFERENCE_OF_VARIABLE */

            /* #3301 Process attached entries. */
            Sd_Rx_ProcessEntryArray(&messageInfo, instanceIdx);                                                         /* SBSW_SD_REFERENCE_OF_VARIABLE */
          }
          else
          {
            /* #3302 Remote address could not be saved (and a DET error was reported).
             *       Discard the received message. */
          }
        }
      }
    }
#if(SD_DEV_ERROR_REPORT == STD_ON)
    else
    {
      /* #40 No instance is configured for the given RxPduId. Raise an error. */
      errorId = SD_E_INV_ID;
    }
#endif
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #50 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_RX_INDICATION, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* PRQA S 6050, 6080 */ /* MD_Sd_STCAL_6050, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_LocalIpAddrAssignmentChg(
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  Sd_SizeOfInstanceType instanceIdx;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if((State != SOAD_IPADDR_STATE_ASSIGNED) &&
    (State != SOAD_IPADDR_STATE_ONHOLD) &&
    (State != SOAD_IPADDR_STATE_UNASSIGNED))
  {
    errorId = SD_E_INV_MODE;
  }
  else if(SoConId == SOAD_INV_SO_CON_ID)
  {
    errorId = SD_E_INV_ID;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Iterate over all instances in order to find the corresponding instance. */
    for(instanceIdx = 0u; instanceIdx < Sd_GetSizeOfInstance(); instanceIdx++)
    {
      /* #200 Check if the change occurred at the TxSoCon. */
      if (Sd_GetTxSoConIdOfInstance(instanceIdx) == SoConId)
      {
        /* #2000 Save the state of the IP address. */
        Sd_SetStateOfInstanceDyn(instanceIdx, (Sd_ServiceInstanceStateType)State);                                      /* SBSW_SD_CSL01 */
        Sd_Util_SetAllStateMachineExecutionFlags(instanceIdx);
        Sd_Util_TriggerStateMachineRun(instanceIdx);

        if (State == SOAD_IPADDR_STATE_ASSIGNED)
        {
          /* #20000 Save the event that a new IP address was assigned.
          *        The event will be processed in the MainFunction. */
          if(Sd_GetRunModeOfInstanceDyn(instanceIdx) != SD_RUN_MODE_RUNNING_NO_IP)
          {
            Sd_SetRunModeOfInstanceDyn(instanceIdx, SD_RUN_MODE_NEW_IP_ASSIGNED);                                       /* SBSW_SD_CSL02 */
          }
          else
          {
            Sd_SetRunModeOfInstanceDyn(instanceIdx, SD_RUN_MODE_RUNNING);                                               /* SBSW_SD_CSL02 */
          }
        }
        else  /* State != SOAD_IPADDR_STATE_ASSIGNED */
        {
          /* #20001 Save the event that the local IP address was un-assigned.
           *        The event will be processed in the MainFunction. */
          Sd_SetRunModeOfInstanceDyn(instanceIdx, SD_RUN_MODE_IP_UNASSIGNED);                                           /* SBSW_SD_CSL02 */
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_SoConModeChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_SoConModeChg(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if((Mode != SOAD_SOCON_ONLINE) && (Mode != SOAD_SOCON_RECONNECT) && (Mode != SOAD_SOCON_OFFLINE))
  {
    errorId = SD_E_INV_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Save the current mode of the socket connection. */
    Sd_Util_SetTcpSoConMode(SoConId, Mode);
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #30 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SOCONMODE_CHG, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
}

/**********************************************************************************************************************
 *  Sd_ServerServiceSetState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SD_CODE) Sd_ServerServiceSetState(
  uint16 SdServerServiceHandleId,
  Sd_ServerServiceSetStateType ServerServiceState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if((ServerServiceState != SD_SERVER_SERVICE_DOWN) && (ServerServiceState != SD_SERVER_SERVICE_AVAILABLE))
  {
    errorId = SD_E_INV_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Check if the SdServerServiceHandleId is valid. */
    if(SdServerServiceHandleId < Sd_GetSizeOfServerMap())
    {
#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
      if(!Sd_IsInvalidHndOfServerMap(SdServerServiceHandleId))
#endif
      {
        Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfServerMap(SdServerServiceHandleId);

        /* #1000 Verify that server is not member of any service group. */
        if(Sd_IsServiceGroupMemberOfServer(serverIdx) == FALSE)
        {
          /* #10000 Set requested state. */
          if(ServerServiceState == SD_SERVER_SERVICE_DOWN)
          {
            Sd_UtilServer_SetDown(serverIdx);
          }
          else
          {
            Sd_UtilServer_SetAvailable(serverIdx);
          }

          retVal = E_OK;
        }
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #20 Check if the handle ID has an invalid/unknown value. */
  if((errorId == SD_E_NO_ERROR) && (retVal == E_NOT_OK))
  {
    errorId = SD_E_INV_ID;
  }

  /* #30 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SERVER_SERVICE_SET_STATE, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_ClientServiceSetState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SD_CODE) Sd_ClientServiceSetState(
  uint16 ClientServiceHandleId,
  Sd_ClientServiceSetStateType ClientServiceState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if((ClientServiceState != SD_CLIENT_SERVICE_RELEASED) && (ClientServiceState != SD_CLIENT_SERVICE_REQUESTED))
  {
    errorId = SD_E_INV_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Check if the ClientServiceHandleId is valid. */
    if(ClientServiceHandleId < Sd_GetSizeOfClientMap())
    {
#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
      if(!Sd_IsInvalidHndOfClientMap(ClientServiceHandleId))
#endif
      {
        Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfClientMap(ClientServiceHandleId);

        /* #1000 Verify that client is not member of any service group. */
        if(Sd_IsServiceGroupMemberOfClient(clientIdx) == FALSE)
        {
          retVal = E_OK;

          /* #10000 Check the requested state and forward the request to the corresponding subfunction. */
          if(ClientServiceState == SD_CLIENT_SERVICE_REQUESTED)
          {
            Sd_UtilClient_ClientServiceSetStateRequested(clientIdx);
          }
          else
          {
            Sd_UtilClient_ClientServiceSetStateReleased(clientIdx);
          }
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #20 Check if the handle ID has an invalid/unknown value. */
  if((errorId == SD_E_NO_ERROR) && (retVal == E_NOT_OK))
  {
    errorId = SD_E_INV_ID;
  }

  /* #30 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_CLIENT_SERVICE_SET_STATE, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_ServiceGroupStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_ServiceGroupStart(uint16 ServiceGroupHandleId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ServiceGroupMemberIterType memberIdx;
  Sd_SizeOfServiceGroupType serviceGroupIdx;
  Sd_SizeOfServerType serverIdx;
  Sd_SizeOfClientType clientIdx;
  uint8 errorId = SD_E_INV_ID;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Check if the ServiceGroupHandleId is valid. */
    if(ServiceGroupHandleId < Sd_GetSizeOfServiceGroupMap())
    {
#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
      if(!Sd_IsInvalidHndOfServiceGroupMap(ServiceGroupHandleId))
#endif
      {
        serviceGroupIdx = Sd_GetServiceGroupIdxOfServiceGroupMap(ServiceGroupHandleId);

        /* #1000 Iterate over all members of the service group. */
        for(memberIdx = Sd_GetServiceGroupMemberStartIdxOfServiceGroup(serviceGroupIdx);
          memberIdx < Sd_GetServiceGroupMemberEndIdxOfServiceGroup(serviceGroupIdx);
          memberIdx++)
        {
          serverIdx = Sd_GetServerIdxOfServiceGroupMember(memberIdx);
          clientIdx = Sd_GetClientIdxOfServiceGroupMember(memberIdx);

          /* #10000 Set the state of the service instance to AVAILABLE/REQUESTED. */
          if(serverIdx != SD_NO_SERVERIDXOFSERVICEGROUPMEMBER)
          {
            /* #100000 Set state to AVAILABLE in case of server and inc request counter. */
            Sd_UtilServer_SetAvailable(serverIdx);
            Sd_IncServiceGroupReqCounterOfServerDyn(serverIdx);                                                           /* SBSW_SD_CSL03 */
          }
          else
          {
            /* #100001 Set state to REQUESTED in case of client and inc request counter. */
            Sd_UtilClient_ClientServiceSetStateRequested(clientIdx);
            Sd_IncServiceGroupReqCounterOfClientDyn(clientIdx);                                                           /* SBSW_SD_CSL03 */
          }
        }

        errorId = SD_E_NO_ERROR;
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SERVICE_GROUP_START, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_ServiceGroupStop()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SD_CODE) Sd_ServiceGroupStop(uint16 ServiceGroupHandleId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ServiceGroupMemberIterType memberIdx;
  Sd_SizeOfServiceGroupType serviceGroupIdx;
  Sd_SizeOfServerType serverIdx;
  Sd_SizeOfClientType clientIdx;
  uint8 errorId = SD_E_INV_ID;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #100 Check if the ServiceGroupHandleId is valid. */
    if(ServiceGroupHandleId < Sd_GetSizeOfServiceGroupMap())
    {
#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
      if(!Sd_IsInvalidHndOfServiceGroupMap(ServiceGroupHandleId))
#endif
      {
        serviceGroupIdx = Sd_GetServiceGroupIdxOfServiceGroupMap(ServiceGroupHandleId);

        /* #1000 Iterate over all members of the service group. */
        for(memberIdx = Sd_GetServiceGroupMemberStartIdxOfServiceGroup(serviceGroupIdx);
          memberIdx < Sd_GetServiceGroupMemberEndIdxOfServiceGroup(serviceGroupIdx);
          memberIdx++)
        {
          serverIdx = Sd_GetServerIdxOfServiceGroupMember(memberIdx);
          clientIdx = Sd_GetClientIdxOfServiceGroupMember(memberIdx);

          /* #10000 Set the state of the service instance to DOWN/RELEASED. */
          if(serverIdx != SD_NO_SERVERIDXOFSERVICEGROUPMEMBER)
          {
            /* #100000 Set state to DOWN if request counter is zero (server). */
            if(Sd_GetServiceGroupReqCounterOfServerDyn(serverIdx) != 0u)
            {
              Sd_DecServiceGroupReqCounterOfServerDyn(serverIdx);                                                         /* SBSW_SD_CSL03 */
              
              if(Sd_GetServiceGroupReqCounterOfServerDyn(serverIdx) == 0u)
              {
                Sd_UtilServer_SetDown(serverIdx);
              }
            }
          }
          else
          {
            /* #100001 Set state to RELEASED if request counter is zero (client). */
            if(Sd_GetServiceGroupReqCounterOfClientDyn(clientIdx) != 0u)
            {
              Sd_DecServiceGroupReqCounterOfClientDyn(clientIdx);                                                         /* SBSW_SD_CSL03 */
              
              if(Sd_GetServiceGroupReqCounterOfClientDyn(clientIdx) == 0u)
              {
                Sd_UtilClient_ClientServiceSetStateReleased(clientIdx);
              }
            }
          }
        }

        errorId = SD_E_NO_ERROR;
      }
    }
  }
  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SERVICE_GROUP_STOP, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_ConsumedEventGroupSetState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SD_CODE) Sd_ConsumedEventGroupSetState(
  uint16 SdConsumedEventGroupHandleId,
  Sd_ConsumedEventGroupSetStateType ConsumedEventGroupState)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SD_E_NO_ERROR;
  boolean invalidId = TRUE;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if(SD_DEV_ERROR_DETECT == STD_ON)                                                                                      /* COV_SD_SAFE_BSW */
  /* #10 Check plausibility of input parameters. */
  if(Sd_State == SD_UNINIT)
  {
    errorId = SD_E_NOT_INITIALIZED;
  }
  else if((ConsumedEventGroupState != SD_CONSUMED_EVENTGROUP_RELEASED) && (ConsumedEventGroupState != SD_CONSUMED_EVENTGROUP_REQUESTED))
  {
    errorId = SD_E_INV_MODE;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check if the SdConsumedEventGroupHandleId is valid. */
    if(SdConsumedEventGroupHandleId < Sd_GetSizeOfConsumedEventgroupMap())
    {
#if(SD_CONFIGURATION_VARIANT == SD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)
      if(!Sd_IsInvalidHndOfConsumedEventgroupMap(SdConsumedEventGroupHandleId))
#endif
      {
        Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx =
          Sd_GetConsumedEventgroupIdxOfConsumedEventgroupMap(SdConsumedEventGroupHandleId);
        Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(consumedEventgroupIdx);

#if(SD_DEV_ERROR_REPORT == STD_ON)
        invalidId = FALSE;
#endif

        /* #30 Check if the consumed eventgroup is requested while the corresponding client service instance is not requested. */
        if((ConsumedEventGroupState == SD_CONSUMED_EVENTGROUP_REQUESTED) &&
          (Sd_GetStateSwcOfClientDyn(clientIdx) != SD_CLIENT_SERVICE_REQUESTED))
        {
          /* #300 Do not update the state because of the actual state of the client. */
        }
        /* #40 Otherwise, process the consumed eventgroup request. */
        else
        {
          /* #400 Check if the state of the consumed eventgroup was changed to requested. */
          if((ConsumedEventGroupState == SD_CONSUMED_EVENTGROUP_REQUESTED) &&
            (Sd_GetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_RELEASED))
          {
            /* #4000 Trigger a subscription of the consumed eventgroup and reset the retry subscription counter. */
            Sd_SetTriggerSubscriptionOfConsumedEventgroupDyn(consumedEventgroupIdx, TRUE);                              /* SBSW_SD_CSL03 */
            Sd_SetRetryCounterOfClientDyn(clientIdx, 1u);                                                               /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
          }

          /* #401 Update the state. */
          Sd_SetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx, ConsumedEventGroupState);              /* SBSW_SD_CSL03 */
          Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                             /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
          Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(clientIdx));
          retVal = E_OK;
        }
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if(SD_DEV_ERROR_REPORT == STD_ON)
  /* #50 Check if the handle ID has an invalid/unknown value. */
  if((errorId == SD_E_NO_ERROR) && (invalidId == TRUE))
  {
    errorId = SD_E_INV_ID;
  }

  /* #60 Report default errors if any occurred. */
  if(errorId != SD_E_NO_ERROR)
  {
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_CONSUMED_EVENTGROUP_SET_STATE, errorId);
  }
#else
  SD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
  SD_DUMMY_STATEMENT(invalidId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sd_UtilClient_ClientServiceSetStateRequested()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ClientServiceSetStateRequested(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is released. */
  if(Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_RELEASED)
  {
    /* #100 Check if the remote server was not yet seen. */
    if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimerTTLOfClientDyn(ClientIdx), TRUE))
    {
      /* #1000 Update the state and reset the TimeToTriggerSend. */
      Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT, TRUE);
    }
    /* 200 Otherwise, if it was already seen. */
    else
    {
      /* #2000 Configure the client for consumed methods. */
      if(Sd_StateClient_Configure(ClientIdx) == E_OK)
      {
        /* #20000 Enter the main phase and inform the BswM. */
        Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SERVICE_READY, FALSE);
        Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_AVAILABLE);
      }
    }
  }

  /* #20 Update the state. */
  Sd_SetStateSwcOfClientDyn(ClientIdx, SD_CLIENT_SERVICE_REQUESTED);                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                 /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_HANDLE_ID_INDIRECTION */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(ClientIdx));
}

/**********************************************************************************************************************
 *  Sd_UtilClient_ClientServiceSetStateReleased()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ClientServiceSetStateReleased(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfMethodType methodIdx = Sd_GetMethodIdxOfClient(ClientIdx);
  Sd_ConsumedEventgroupIterType consumedEventgroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is configured for consumed methods. */
  if((methodIdx != SD_NO_METHODIDXOFCLIENT) &&
    (Sd_IsTcpConfiguredOfMethod(methodIdx) || Sd_IsUdpConfiguredOfMethod(methodIdx)))
  {
    /* #100 Disable routing of consumed methods. */
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(methodIdx));

    if(Sd_GetMethodTcpSoConIdOfClientDyn(ClientIdx) != SOAD_INV_SO_CON_ID)
    {
      /* #101 Unconfigure TCP for consumed methods. */
      (void)SoAd_CloseSoCon(Sd_GetMethodTcpSoConIdOfClientDyn(ClientIdx), FALSE);
      Sd_SetMethodTcpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    if(Sd_GetMethodUdpSoConIdOfClientDyn(ClientIdx) != SOAD_INV_SO_CON_ID)
    {
      /* #102 Unconfigure UDP for consumed methods. */
      (void)SoAd_CloseSoCon(Sd_GetMethodUdpSoConIdOfClientDyn(ClientIdx), FALSE);
      Sd_SetMethodUdpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #20 Pass the RELEASED state to all eventgroups. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    (void)Sd_ConsumedEventGroupSetState((uint16)Sd_GetHandleIdOfConsumedEventgroup(consumedEventgroupIdx),
      SD_CONSUMED_EVENTGROUP_RELEASED);
  }

  /* #30 Update the state. */
  Sd_SetStateSwcOfClientDyn(ClientIdx, SD_CLIENT_SERVICE_RELEASED);                                               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                 /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_HANDLE_ID_INDIRECTION */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(ClientIdx));
}

/**********************************************************************************************************************
 *  Sd_Init_General()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_General(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_TcpSoConModeMapIterType soConModeMapIdx;
  Sd_RxEventIterType rxEventIdx;
  Sd_SendEntryIterType sendEntryIdx;
  Sd_AddressStorageIterType addressStorageIdx;
  Sd_InstanceIterType instanceIdx;
  Sd_RoutingGroupDynIterType routingGroupIdx;
  Sd_CommonInitialDelayIterType commonInitialDelayIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the socket connection mode map. */
  for(soConModeMapIdx = 0u; soConModeMapIdx < Sd_GetSizeOfTcpSoConModeMap(); soConModeMapIdx++)
  {
    Sd_SetTcpSoConModeMap(soConModeMapIdx, SD_SOCON_MODE_OFFLINE);                                                      /* SBSW_SD_CSL01 */
  }

  /* #20 Initialize the RxEvent list. */
  for(rxEventIdx = 0u; rxEventIdx < Sd_GetSizeOfRxEvent(); rxEventIdx++)
  {
    Sd_SetClientListIdxOfRxEvent(rxEventIdx, Sd_GetSizeOfClientList());                                                 /* SBSW_SD_CSL01 */
    Sd_SetEventHandlerIdxOfRxEvent(rxEventIdx, Sd_GetSizeOfEventHandler());                                             /* SBSW_SD_CSL01 */
    Sd_SetEventOfRxEvent(rxEventIdx, SD_SERVER_EVENT_EVENTGROUP_NONE);                                                  /* SBSW_SD_CSL01 */
  }

  /* #30 Initialize the option index and lock for the TxPath. */
  Sd_SetNrOfOptions(0u);                                                                                                /* SBSW_SD_CSL_VAR_ELEM */
  Sd_TxPathLocked = FALSE;

  /* #40 Initialize the sendentry list. */
  for(sendEntryIdx = 0u; sendEntryIdx < Sd_GetSizeOfSendEntry(); sendEntryIdx++)
  {
    Sd_SetValidOfSendEntry(sendEntryIdx, FALSE);                                                                        /* SBSW_SD_CSL01 */
    Sd_SetSendEntryNextIdxOfSendEntry(sendEntryIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                                 /* SBSW_SD_CSL01 */
  }

  /* #50 Initialize the address storage array. */
  for(addressStorageIdx = 0u; addressStorageIdx < Sd_GetSizeOfAddressStorage(); addressStorageIdx++)
  {
    /* Session id of 0 is not allowed -> unused/invalid address. */
    Sd_SetSessionIdCounterOfAddressStorage(addressStorageIdx, 0u);                                                      /* SBSW_SD_CSL01 */
    Sd_SetFlagsOfAddressStorage(addressStorageIdx, SD_FLAGS_REBOOT_MASK | SD_FLAGS_UNICAST_MASK);                       /* SBSW_SD_CSL01 */
    Sd_SetRxUnicastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                                    /* SBSW_SD_CSL01 */
    Sd_SetRxMulticastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                                  /* SBSW_SD_CSL01 */
    Sd_SetRxUnicastFlagsOfAddressStorage(addressStorageIdx, SD_FLAGS_REBOOT_MASK);                                      /* SBSW_SD_CSL01 */
    Sd_SetRxMulticastFlagsOfAddressStorage(addressStorageIdx, SD_FLAGS_REBOOT_MASK);                                    /* SBSW_SD_CSL01 */
    Sd_SetSendEntryNrPendingIdxOfAddressStorage(addressStorageIdx, 0u);                                                 /* SBSW_SD_CSL01 */
  }

  /* #60 Set the session ID of the SD multicast address. The address will be set during Sd_Init_ReInitialize(). */
  for(instanceIdx = 0u; instanceIdx < Sd_GetSizeOfInstance(); instanceIdx++)
  {
    Sd_SetSessionIdCounterOfAddressStorage(Sd_GetAddressStorageStartIdxOfInstance(instanceIdx), 1u);                    /* SBSW_SD_CSL03 */
  }

  /* #70 Initialize the status of the SoAd RoutingGroups to unknown. */
  for(routingGroupIdx = 0u; routingGroupIdx < Sd_GetSizeOfRoutingGroupDyn(); routingGroupIdx++)
  {
    Sd_SetStatusOfRoutingGroupDyn(routingGroupIdx, SD_ROUTINGGROUP_STATUS_UNKNOWN);                                     /* SBSW_SD_CSL01 */
  }

  /* #80 Set all common initial delays to invalid. */
  for(commonInitialDelayIdx = 0; commonInitialDelayIdx < Sd_GetSizeOfCommonInitialDelay(); commonInitialDelayIdx++)
  {
    Sd_SetCommonInitialDelay(commonInitialDelayIdx, SD_INV_TIMER_VALUE_32BIT);                                          /* SBSW_SD_CSL01 */
  }
} /* PRQA S 6010 */ /* MD_Sd_STPTH_6010 */

/**********************************************************************************************************************
 *  Sd_Init_Instance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Instance(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all instances. */
  for(instanceIdx = 0u; instanceIdx < Sd_GetSizeOfInstance(); instanceIdx++)
  {
    /* #20 Trigger an initial run of the state machines. */
    Sd_Util_TriggerStateMachineRun(instanceIdx);

    /* #30 Initialize the dynamic data structures. */
    Sd_Util_ResetTimerToZero(Sd_GetAddrNextStateMachineRunOfInstanceDyn(instanceIdx));                                  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_SAME_SIZE */

    if(Sd_State == SD_UNINIT)
    {
      /* #40 The link state is only changed at the initial run after a reboot. */
      Sd_SetStateOfInstanceDyn(instanceIdx, SD_INSTANCE_DOWN);                                                          /* SBSW_SD_CSL02 */
      Sd_SetRunModeOfInstanceDyn(instanceIdx, SD_RUN_MODE_INITIAL_RUN);                                                 /* SBSW_SD_CSL02 */
    }

    /* #50 Initialize the RX event list. */
    Sd_SetRxEventListFullOfInstanceDyn(instanceIdx, FALSE);                                                             /* SBSW_SD_CSL02 */
    Sd_SetRxEventStartIdxOfInstanceDyn(instanceIdx, Sd_GetRxEventStartIdxOfInstance(instanceIdx));                      /* SBSW_SD_CSL02 */
    Sd_SetRxEventEndIdxOfInstanceDyn(instanceIdx, Sd_GetRxEventStartIdxOfInstance(instanceIdx));                        /* SBSW_SD_CSL02 */

    /* #60 Initialize the send entries list. */
    Sd_SetSendEntryNrPendingIdxOfInstanceDyn(instanceIdx, 0u);                                                          /* SBSW_SD_CSL02 */

    Sd_SetSendEntryStartIdxOfInstanceDyn(instanceIdx, SD_NO_SENDENTRYSTARTIDXOFINSTANCEDYN);                            /* SBSW_SD_CSL02 */
    Sd_SetSendEntryEndIdxOfInstanceDyn(instanceIdx, SD_NO_SENDENTRYENDIDXOFINSTANCEDYN);                                /* SBSW_SD_CSL02 */
  }
}

/**********************************************************************************************************************
 *  Sd_Init_Server()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Server(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ServerIterType serverIdx;
  Sd_SizeOfEventHandlerType eventHandlerIdx;
  Sd_ClientListIterType clientListIdx;
  Sd_SoConActivationMapIterType soConActivationMapIdx;
  Sd_TriggerTransmitIterType triggerTransmitIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the servers. */
  for(serverIdx = 0u; serverIdx < Sd_GetSizeOfServer(); serverIdx++)
  {
    /* #100 Set the initial state of the server. */
    if(Sd_IsAutoAvailableOfServer(serverIdx))
    {
      Sd_SetStateSwcOfServerDyn(serverIdx, SD_SERVER_SERVICE_AVAILABLE);                                                /* SBSW_SD_CSL02 */
    }
    else
    {
      Sd_SetStateSwcOfServerDyn(serverIdx, SD_SERVER_SERVICE_DOWN);                                                     /* SBSW_SD_CSL02 */
    }

    /* #101 Initialize all dynamic variables. */
    Sd_SetStateMachineOfServerDyn(serverIdx, SD_SERVER_STATE_NONE);                                                     /* SBSW_SD_CSL02 */
    Sd_SetServiceGroupReqCounterOfServerDyn(serverIdx, 0u);                                                             /* SBSW_SD_CSL02 */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                   /* SBSW_SD_CSL02 */
    Sd_SetInitialOfferRepetitionRunOfServerDyn(serverIdx, 0u);                                                          /* SBSW_SD_CSL02 */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfServerDyn(serverIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_SAME_SIZE */
  }

  /* #20 Initialize the event handlers. */
  for(eventHandlerIdx = 0u; eventHandlerIdx < Sd_GetSizeOfEventHandler(); eventHandlerIdx++)
  {
    /* #200 Initialize all dynamic variables. */
    Sd_SetStateMachineOfEventHandlerDyn(eventHandlerIdx, SD_EVENT_HANDLER_STATE_NONE);                                  /* SBSW_SD_CSL02 */
    Sd_SetNrOfClientsOfEventHandlerDyn(eventHandlerIdx, 0u);                                                            /* SBSW_SD_CSL02 */
    Sd_UtilServer_UpdateEventHandlerRequestState(eventHandlerIdx, SD_EVENT_HANDLER_RELEASED);
  }

  /* #30 Initialize the client list. */
  for(clientListIdx = 0u; clientListIdx < Sd_GetSizeOfClientList(); clientListIdx++)
  {
    Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                                /* SBSW_SD_CSL01 */
    Sd_SetNrOfReferencesOfClientList(clientListIdx, 0u);                                                                /* SBSW_SD_CSL01 */
  }

  /* #40 Initialize the socket connection activation map. */
  for(soConActivationMapIdx = 0u; soConActivationMapIdx < Sd_GetSizeOfSoConActivationMap(); soConActivationMapIdx++)
  {
    Sd_SetNrOfActivationsOfSoConActivationMap(soConActivationMapIdx, 0u);                                               /* SBSW_SD_CSL01 */
    Sd_SetSoConIdOfSoConActivationMap(soConActivationMapIdx, SOAD_INV_SO_CON_ID);                                       /* SBSW_SD_CSL01 */
  }

  /* #50 Initialize the trigger transmit control structures. */
  Sd_SetTriggerTransmitFull(FALSE);                                                                                     /* SBSW_SD_CSL_VAR_ELEM */
  Sd_SetTriggerTransmitStartIdx(0u);                                                                                    /* SBSW_SD_CSL_VAR_ELEM */
  Sd_SetTriggerTransmitEndIdx(0u);                                                                                      /* SBSW_SD_CSL_VAR_ELEM */

  for(triggerTransmitIdx = 0u; triggerTransmitIdx < Sd_GetSizeOfTriggerTransmit(); triggerTransmitIdx++)
  {
    /* #500 Initialize the trigger transmit list. */
    Sd_SetClientListIdxOfTriggerTransmit(triggerTransmitIdx, Sd_GetSizeOfClientList()); /* Invalid value. */            /* SBSW_SD_CSL01 */
    Sd_SetEventHandlerIdxOfTriggerTransmit(triggerTransmitIdx, Sd_GetSizeOfEventHandler()); /* Invalid value. */        /* SBSW_SD_CSL01 */
    Sd_SetStateOfTriggerTransmit(triggerTransmitIdx, SD_TRIGGER_TRANSMIT_STATE_INVALID);                                /* SBSW_SD_CSL01 */
  }
}

/**********************************************************************************************************************
 *  Sd_Init_Client()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_Client(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx;
  Sd_RequestCntIterType requestCntIdx;
  Sd_PortSetIterType portSetIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the clients. */
  for(clientIdx = 0u; clientIdx < Sd_GetSizeOfClient(); clientIdx++)
  {
    /* #100 Inform the BswM if the Sd_Init() is called while being in the initial wait phase. */
    if((Sd_State == SD_INIT) && (Sd_GetStateMachineOfClientDyn(clientIdx) == SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT))
    {
      Sd_ConsumedEventgroupIterType consumedEventgroupIdx;

      /* #1000 Inform the BswM about the state of the client service and all consumed eventgroups. */
      Sd_UtilClient_SetCurrentStateInformBswm(clientIdx, SD_CLIENT_SERVICE_DOWN);

      for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(clientIdx);
        consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(clientIdx);
        consumedEventgroupIdx++)
      {
        BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(consumedEventgroupIdx),
          SD_CONSUMED_EVENTGROUP_DOWN);
      }
    }

    /* #101 Set the initial state of the clients. */
    if(Sd_IsAutoRequireOfClient(clientIdx))
    {
      Sd_SetStateSwcOfClientDyn(clientIdx, SD_CLIENT_SERVICE_REQUESTED);                                                /* SBSW_SD_CSL02 */
    }
    else
    {
      Sd_SetStateSwcOfClientDyn(clientIdx, SD_CLIENT_SERVICE_RELEASED);                                                 /* SBSW_SD_CSL02 */
    }

    /* #102 Initialize all dynamic variables. */
    Sd_UtilClient_ResetDynamicVariables(clientIdx);
    Sd_SetServiceGroupReqCounterOfClientDyn(clientIdx, 0u);                                                             /* SBSW_SD_CSL02 */
  }

  /* #20 Initialize all consumed eventgroups. */
  Sd_Init_ClientCeg();

  /* #30 Initialize the Request Count and Port Set flag for dynamic multicast addresses. */
  for(requestCntIdx = 0u; requestCntIdx < Sd_GetSizeOfRequestCnt(); requestCntIdx++)
  {
    Sd_SetRequestCnt(requestCntIdx, 0u);                                                                                /* SBSW_SD_CSL01 */
  }

  for(portSetIdx = 0u; portSetIdx < Sd_GetSizeOfPortSet(); portSetIdx++)
  {
    Sd_SetPortSet(portSetIdx, FALSE);                                                                                   /* SBSW_SD_CSL01 */
  }
}

/**********************************************************************************************************************
 *  Sd_Init_ClientCeg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ClientCeg(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ConsumedEventgroupIterType consumedEventgroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all consumed eventgroups. */
  for(consumedEventgroupIdx = 0u; consumedEventgroupIdx < Sd_GetSizeOfConsumedEventgroup(); consumedEventgroupIdx++)
  {
    /* #100 Set the initial state of the consumed eventgroups. */
    if(Sd_IsAutoRequireOfConsumedEventgroup(consumedEventgroupIdx))
    {
      Sd_SetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_REQUESTED);         /* SBSW_SD_CSL02 */
    }
    else
    {
      Sd_SetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_RELEASED);          /* SBSW_SD_CSL02 */
    }

    /* #101 Initialize all dynamic variables. */
    Sd_SetCurrentStateOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_DOWN);                      /* SBSW_SD_CSL02 */
    Sd_SetEventOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                         /* SBSW_SD_CSL02 */
    Sd_SetSoConMarkedForClosureOfConsumedEventgroupDyn(consumedEventgroupIdx, FALSE);                                   /* SBSW_SD_CSL02 */
    Sd_SetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED);        /* SBSW_SD_CSL02 */
    Sd_Util_ResetTimerToZero(Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx));                         /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_SAME_SIZE */
    Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(consumedEventgroupIdx, 0u);                                            /* SBSW_SD_CSL02 */
    Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                           /* SBSW_SD_CSL02 */
    Sd_SetUdpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                                 /* SBSW_SD_CSL02 */
    Sd_SetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                                 /* SBSW_SD_CSL02 */
    Sd_SetTriggerSubscriptionOfConsumedEventgroupDyn(consumedEventgroupIdx, FALSE);                                     /* SBSW_SD_CSL02 */

    if(Sd_IsMulticastEndpointAddrUsedOfConsumedEventgroup(consumedEventgroupIdx))
    {
      Sd_MulticastEndpointAddrIdxOfConsumedEventgroupType multicastEndpointAddrIdx =
        Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(consumedEventgroupIdx);

      (Sd_GetAddrMulticastEndpointAddr(multicastEndpointAddrIdx))->family = SOAD_AF_INVALID;                            /* SBSW_SD_CSL03 */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_CloseAllSocketsOfInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_CloseAllSocketsOfInstance(Sd_SizeOfInstanceType InstanceIdx)
{
  Sd_TcpSoConIdIterType tcpSoConIdIdx;
  Sd_UdpSoConIterType udpSoConIdx;

  /* #10 Close the TCP socket connections of the instance. */
  for(tcpSoConIdIdx = Sd_GetTcpSoConIdStartIdxOfInstance(InstanceIdx); tcpSoConIdIdx < Sd_GetTcpSoConIdEndIdxOfInstance(InstanceIdx); tcpSoConIdIdx++)
  {
    (void)SoAd_CloseSoCon(Sd_GetTcpSoConId(tcpSoConIdIdx), TRUE);
  }

  /* #20 Close the UDP socket connections of the instance. */
  for(udpSoConIdx = Sd_GetUdpSoConStartIdxOfInstance(InstanceIdx); udpSoConIdx < Sd_GetUdpSoConEndIdxOfInstance(InstanceIdx); udpSoConIdx++)
  {
    (void)SoAd_CloseSoCon(Sd_GetIdOfUdpSoCon(udpSoConIdx), TRUE);
  }
}

/**********************************************************************************************************************
 *  Sd_Init_ReInitialize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitialize(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_EndpointStorageIterType endpointStorageIdx;
  Sd_SockAddrContainerType localAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear the list of endpoint entries. */
  for(endpointStorageIdx = 0u; endpointStorageIdx < Sd_GetSizeOfEndpointStorage(); endpointStorageIdx++)
  {
    Sd_SetNrOfReferencesOfEndpointStorage(endpointStorageIdx, 0u);                                                      /* SBSW_SD_CSL01 */
    Sd_SetTypeOfEndpointStorage(endpointStorageIdx, SD_ENDPOINT_TYPE_INVALID);                                          /* SBSW_SD_CSL01 */
    (Sd_GetAddrAddrOfEndpointStorage(endpointStorageIdx))->family = SOAD_AF_INVALID;                                    /* SBSW_SD_CSL01 */
  }

  /* #20 Get the Sd multicast address. */
  localAddr.family = SOAD_AF_INVALID;
  retVal = Sd_SoAd_GetLocalAddr(Sd_GetMulticastRxSoConIdOfInstance(InstanceIdx), &localAddr);                           /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(retVal == E_OK)
  {
    /* #200 Save the multicast address and initialize the SessionID counter. */
    Sd_Util_CopySockAddr(
      Sd_GetAddrAddrOfAddressStorage(Sd_GetAddressStorageStartIdxOfInstance(InstanceIdx)), &localAddr);                 /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    Sd_Util_ResetSessionIds(InstanceIdx);

    /* #201 Set the SoAd remote address of the Rx and Tx socket connections to multicast in order to initialize (open) the socket. */
    /* PRQA S 0310 1 */ /* MD_Sd_11.4_0310 */
    (void)SoAd_SetRemoteAddr(Sd_GetTxSoConIdOfInstance(InstanceIdx), (SD_P2VAR(SoAd_SockAddrType))&localAddr);          /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */
    (void)SoAd_OpenSoCon(Sd_GetTxSoConIdOfInstance(InstanceIdx));

    /* PRQA S 0310 1 */ /* MD_Sd_11.4_0310 */
    (void)SoAd_SetRemoteAddr(Sd_GetMulticastRxSoConIdOfInstance(InstanceIdx), (SD_P2VAR(SoAd_SockAddrType))&localAddr); /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */
    (void)SoAd_OpenSoCon(Sd_GetMulticastRxSoConIdOfInstance(InstanceIdx));

    /* #202 Initialize all server data. */
    Sd_Init_ReInitializeServers(InstanceIdx);

    /* #203 Initialize all client data. */
    Sd_Init_ReInitializeClients(InstanceIdx);

    /* #204 Close all sockets of this instance. */
    Sd_CloseAllSocketsOfInstance(InstanceIdx);
  }
} /* PRQA S 6050 */ /* MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  SERVER FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeServers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeServers(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfServerType serverIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all server to update and process the state machine. */
  for(serverIdx = Sd_GetServerStartIdxOfInstance(InstanceIdx);
    serverIdx < Sd_GetServerEndIdxOfInstance(InstanceIdx);
    serverIdx++)
  {
    /* #100 Initialize all event handlers of the server. */
    Sd_Init_ReInitializeEventHandler(serverIdx);

    /* #101 Disable routing for provided methods. */
    Sd_UtilServer_DisableMethodRouting(serverIdx);

    /* #102 Set Flag for executing state machine of server. */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
  }
}

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeEventHandler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeEventHandler(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerType eventHandlerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all event handlers, disable the RoutingGroups and close the socket connections. */
  for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(ServerIdx);
    eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(ServerIdx);
    eventHandlerIdx++)
  {
    Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx;
    Sd_ClientListIterType clientListIdx;

    /* #100 Reset multicast event handler configuration. */
    eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(eventHandlerIdx);
    if(eventHandlerMulticastIdx != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)
    {
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(eventHandlerMulticastIdx));
      (void)SoAd_CloseSoCon(Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx), TRUE);
    }

    /* #101 Disable routing of UDP and TCP event handler and reset activation count. */
    Sd_UtilServer_DisableRouting(eventHandlerIdx);

    /* #102 Clear the list of subscribed clients. */
    Sd_SetNrOfClientsOfEventHandlerDyn(eventHandlerIdx, 0u);                                                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(eventHandlerIdx);
      clientListIdx < Sd_GetClientListEndIdxOfEventHandler(eventHandlerIdx);
      clientListIdx++)
    {
      Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_Process()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_Process(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle the state machine within the ready block. */
  switch(Sd_GetStateMachineOfServerDyn(ServerIdx))
  {
    case SD_SERVER_STATE_NONE:
    case SD_SERVER_STATE_NOT_READY:
      Sd_StateServer_ProcessNotReady(ServerIdx);
      break;

    case SD_SERVER_STATE_READY_INITIAL_WAIT:
      Sd_StateServer_ProcessInitialWait(ServerIdx);
      break;

    case SD_SERVER_STATE_READY_REPETITION:
      Sd_StateServer_ProcessRepetition(ServerIdx);
      break;

    case SD_SERVER_STATE_READY_MAIN_PHASE:
      Sd_StateServer_ProcessMain(ServerIdx);
      break;

    default: /* COV_SD_MISRA */
      /* Undefined state. */
      break;
  }

  /* #20 Check if the state machine is within the ready block and a condition to leave the block is fulfilled. */
  if(((Sd_GetStateOfInstanceDyn(instanceIdx) != SD_INSTANCE_UP_AND_CONFIGURED) ||
    (Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_DOWN)) &&
    ((Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_READY_INITIAL_WAIT) ||
    (Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_READY_REPETITION) ||
    (Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_READY_MAIN_PHASE)))
  {
    /* #200 Send a StopOfferService message only if the SD is still running. */
    if(Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED)
    {
      /* Send a StopOfferService message. */
      Sd_Util_AddMulticastOfferEntryToList(ServerIdx, TRUE);
    }

    /* #201 Leave the ready-state and reset the TimeToTriggerSend. */
    Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_NOT_READY, TRUE);
  }

  /* #30 Run the state machine, handling all event handlers of the server instance. */
  Sd_StateServer_ProcessEventHandlerStateMachine(ServerIdx);

  /* #40 Update the time for the next state machine run. */
  Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx));
} /* PRQA S 6050 */ /* MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessNotReady()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessNotReady(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if it is the initial run of the server state machine. */
  if(Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_NONE)
  {
    /* #100 First run of the state machine. Update state. */
    if((Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED) &&
      (Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_AVAILABLE))
    {
      Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_READY_INITIAL_WAIT, FALSE);
    }
    else
    {
      Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_NOT_READY, FALSE);
    }
  }
  else /* Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_NOT_READY */
  {
    /* #101 Otherwise, check if the server is requested and the instance is up and configured. */
    if((Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED) &&
      (Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_AVAILABLE))
    {
      /* #1010 Update the state and reset the TimeToTriggerSend. */
      Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_READY_INITIAL_WAIT, TRUE);
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessInitialWait()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessInitialWait(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetServerTimerIdxOfServer(ServerIdx);
  Sd_TcpSoConIdIterType tcpSoConIdIdx;
  Sd_UdpSoConIterType udpSoConIdx;
  uint32 additionalOffset;
  Sd_CommonInitialDelayIdxOfServerType commonDelayIdx = Sd_GetCommonInitialDelayIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the current state of the instance is not UP_AND_CONFIGURED. */
  if(Sd_GetStateOfInstanceDyn(instanceIdx) != SD_INSTANCE_UP_AND_CONFIGURED)
  {
    /* #100 Instance is not up and configured. Update state. */
    Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_NOT_READY, FALSE);
  }
  /* #20 Otherwise, check if this is the first run of the wait state.*/
  else if(Sd_CheckIfTimerIsInvalid(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx)))
  {
    /* #200 Instance is up and configured. First run of the wait state. */
    Sd_EventHandlerIterType eventHandlerIdx;

    /* #201 Open the multicast socket connections. */
    for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(ServerIdx);
      eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(ServerIdx);
      eventHandlerIdx++)
    {
      Sd_EventHandlerMulticastIterType eventHandlerMulticastIdx;
      eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(eventHandlerIdx);

      if(eventHandlerMulticastIdx != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)
      {
        (void)SoAd_OpenSoCon(Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx));
      }
    }

    /* #202 Open the TCP socket connections in order to allow incoming connections.
     *      (UDP socket connections will be configured and opened if a client subscribes.) */
    for(tcpSoConIdIdx = Sd_GetTcpSoConIdStartIdxOfServer(ServerIdx);
      tcpSoConIdIdx < Sd_GetTcpSoConIdEndIdxOfServer(ServerIdx);
      tcpSoConIdIdx++)
    {
      (void)SoAd_OpenSoCon(Sd_GetTcpSoConId(tcpSoConIdIdx));
    }

    /* #203 If sockets with preconfigured remote addresses exist, open them to allow provided method calls. */
    for(udpSoConIdx = Sd_GetUdpSoConStartIdxOfServer(ServerIdx);
      udpSoConIdx < Sd_GetUdpSoConEndIdxOfServer(ServerIdx);
      udpSoConIdx++)
    {
      if(Sd_IsPreconfiguredOfUdpSoCon(udpSoConIdx) == TRUE)
      {
        (void)SoAd_OpenSoCon(Sd_GetIdOfUdpSoCon(udpSoConIdx));
      }
    }

    if(Sd_GetMethodIdxOfServer(ServerIdx) != SD_NO_METHODIDXOFSERVER)
    {
      /* #204 Enable the routing group for the provided method. */
      (void)Sd_Util_EnableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(Sd_GetMethodIdxOfServer(ServerIdx)));
    }

    /* #205 Get random delay if a common delay shall not be used or the common delay has not been determined yet. */
    if((commonDelayIdx == SD_NO_COMMONINITIALDELAYIDXOFSERVER) ||
      (Sd_GetCommonInitialDelay(commonDelayIdx) == SD_INV_TIMER_VALUE_32BIT))
    {
      additionalOffset = Sd_Util_GetRandomNrInRange(
        Sd_GetInitialOfferDelayMinOfServerTimer(serverTimerIdx),
        Sd_GetInitialOfferDelayMaxOfServerTimer(serverTimerIdx));

      if(commonDelayIdx != SD_NO_COMMONINITIALDELAYIDXOFSERVER)
      {
        Sd_SetCommonInitialDelay(commonDelayIdx, additionalOffset);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }
    }
    /* #206 Common delay shall be used and it has been set already, use it. */
    else
    {
      additionalOffset = Sd_GetCommonInitialDelay(commonDelayIdx);
    }

    /* #207 Set Timer and mark server for execution of state machine. */
    Sd_Util_SetTimerOffsetWithTrigger(
      Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx), additionalOffset, instanceIdx);                                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  /* #30 Otherwise this is a succeeding run of the wait state. */
  else
  {
    /* #300 Check if the timer is exceeded. */
    if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx), TRUE))
    {
      /* #3000 Update the state and reset the TimeToTriggerSend. */
      Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_READY_REPETITION, TRUE);

      /* #3001 Send an OfferService message. */
      Sd_Util_AddMulticastOfferEntryToList(ServerIdx, FALSE);

      /* #3002 Reset common delay. */
      if(commonDelayIdx != SD_NO_COMMONINITIALDELAYIDXOFSERVER)
      {
        Sd_SetCommonInitialDelay(commonDelayIdx, SD_INV_TIMER_VALUE_32BIT);                                             /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }
    }

    /* #301 Mark server for execution of state machine. */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
} /* PRQA S 6010, 6030 */ /* MD_Sd_STPTH_6010, MD_MSR_STCYC */

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessRepetition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessRepetition(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetServerTimerIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the repetition phase is entered the first time.*/
  if(Sd_GetInitialOfferRepetitionsMaxOfServerTimer(serverTimerIdx) == 0u)
  {
    /* #100 Go to the main state if there is no repetition phase configured.
     *      Update the state and reset the TimeToTriggerSend.*/
    Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_READY_MAIN_PHASE, TRUE);
  }
  else if(Sd_CheckIfTimerIsInvalid(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx)))
  {
    /* #200 Otherwise if this is the initial run of the repetition phase.
     *      Reset the repetition counter, initialize the timer and mark server for execution of state machine. */
    Sd_SetInitialOfferRepetitionRunOfServerDyn(ServerIdx, 0u);                                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_Util_SetTimerOffsetWithTrigger(
      Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx),
      (uint32)Sd_GetInitialOfferRepetitionBaseDelayOfServerTimer(serverTimerIdx) - SD_MAIN_FCT_CYCLE_TIME_MS,
      instanceIdx);                                                                                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  else
  {
    /* No further state transitions available. */
  }

  /* #30 Succeeding runs of the repetition phase, Timer has expired. */
  if((TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx), TRUE)) &&
    (Sd_GetInitialOfferRepetitionsMaxOfServerTimer(serverTimerIdx) > Sd_GetInitialOfferRepetitionRunOfServerDyn(ServerIdx)) &&
    (Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_READY_REPETITION))
  {
    /* #300 Send an OfferService message and wait for the next repetition. */
    Sd_Util_AddMulticastOfferEntryToList(ServerIdx, FALSE);
    Sd_IncInitialOfferRepetitionRunOfServerDyn(ServerIdx);                                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    if(Sd_GetInitialOfferRepetitionsMaxOfServerTimer(serverTimerIdx) == Sd_GetInitialOfferRepetitionRunOfServerDyn(ServerIdx))
    {
      /* #301 Update the state and reset the TimeToTriggerSend. */
      Sd_StateServer_Update(ServerIdx, SD_SERVER_STATE_READY_MAIN_PHASE, TRUE);
    }
    else
    {
      /* #302 Wind up the timer and mark server for execution of state machine. */
      Sd_Util_SetTimerOffsetWithTrigger(Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx),
        (uint32)((((uint32)(1u)) << Sd_GetInitialOfferRepetitionRunOfServerDyn(ServerIdx)) * Sd_GetInitialOfferRepetitionBaseDelayOfServerTimer(serverTimerIdx)),
        instanceIdx);                                                                                                   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
  /* #40 Timer has not expired yet, request execution of state machine to wait for expiration.  */
  else
  {
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessMain()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessMain(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetServerTimerIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Mark server for execution of state machine. */
  Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Check if the server shall offer the current service instance. */
  if(Sd_GetOfferCyclicDelayOfServerTimer(serverTimerIdx) != 0u)
  {
    /* #200 Check if initial run of the main phase. */
    if(Sd_CheckIfTimerIsInvalid(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx)))
    {
      /* #2000 Set timer to send the first offer message after the configured OfferCyclicDelay. */
      Sd_Util_SetTimerOffsetWithTrigger(
        Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx),
        (uint32)Sd_GetOfferCyclicDelayOfServerTimer(serverTimerIdx) - SD_MAIN_FCT_CYCLE_TIME_MS,
        instanceIdx);                                                                                                   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    }

    /* #201 Check if timer is expired. */
    if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToTriggerSendOfServerDyn(ServerIdx), TRUE))
    {
      /* #2010 Send an OfferService message. */
      Sd_Util_AddMulticastOfferEntryToList(ServerIdx, FALSE);

      /* #2011 Wind up the timer. */
      Sd_Util_SetTimerOffsetWithTrigger(Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx),
        Sd_GetOfferCyclicDelayOfServerTimer(serverTimerIdx), instanceIdx);                                              /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    }
  }
  else
  {
    /* No offer messages are transmitted for this service. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_ProcessEventHandlerStateMachine()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_ProcessEventHandlerStateMachine(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerType eventHandlerIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle all event handlers of the server. */
  for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(ServerIdx);
    eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(ServerIdx);
    eventHandlerIdx++)
  {
    /* #100 Update the state of the event handler. */
    Sd_StateServer_UpdateEventHandlerState(eventHandlerIdx);

    /* #200 Update the state of all subscribed clients. */
    Sd_StateServer_UpdateEventHandlerClients(eventHandlerIdx);

    /* #300 Switch to multicast if this functionality is configured and the corresponding amount of subscribed clients is reached. */
    if(Sd_EventHandlerUsesMulticast(eventHandlerIdx) &&
      (Sd_GetMulticastThresholdOfEventHandler(eventHandlerIdx) <= Sd_GetNrOfClientsOfEventHandlerDyn(eventHandlerIdx)) &&
      (Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_UNICAST_SUBSCRIPTION))
    {
      Sd_StateServer_EventHandlerSwitchMulticast(eventHandlerIdx);
    }

    /* #400 Switch back to unicast if this functionality is configured and the multicast threshold is not reached. */
    if(Sd_EventHandlerUsesUdp(eventHandlerIdx) &&
      (Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION) &&
      (Sd_GetMulticastThresholdOfEventHandler(eventHandlerIdx) > Sd_GetNrOfClientsOfEventHandlerDyn(eventHandlerIdx)))
    {
      Sd_StateServer_EventHandlerSwitchUnicast(eventHandlerIdx);
    }

    /* #500 Check if the event handler is still requested. */
    Sd_StateServer_EventHandlerCheckSubscribed(eventHandlerIdx);
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_UpdateEventHandlerState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_UpdateEventHandlerState(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the event handler is processed for the first time. */
  if(Sd_GetStateMachineOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_STATE_NONE)
  {
    /* #100 First run of the state machine. Update the event handler state based on the server state. */
    if(Sd_GetStateSwcOfServerDyn(serverIdx) == SD_SERVER_SERVICE_DOWN)
    {
      Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_SERVICE_DOWN);
    }
    else
    {
      Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_NOT_SUBSCRIBED);
    }
  }
  /* #20 Otherwise, check if the corresponding server was switched to down state. */
  else if(Sd_GetStateMachineOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_STATE_SERVICE_DOWN)
  {
    /* #200 Set event hander to down if it is currently available. */
    if(Sd_GetStateSwcOfServerDyn(serverIdx) == SD_SERVER_SERVICE_AVAILABLE)
    {
      Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_NOT_SUBSCRIBED);
    }
  }
  /* #30 Otherwise, nothing to do. */
  else
  {
    /* All other states are handled within the context of a client. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_UpdateEventHandlerClients()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_UpdateEventHandlerClients(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(serverIdx);
  Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(EventHandlerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all registered clients of an eventgroup. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    if(Sd_GetClientStateOfClientList(clientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_SUBSCRIBED)
    {
      /* #100 Check if the client is still subscribed. */
      if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetSubscribedUntilOfClientList(clientListIdx), FALSE))
      {
        /* #1000 The client has unsubscribed or a timeout occurred. Unconfigure and remove the client. */
        Sd_UtilServer_RemoveClientFromList(EventHandlerIdx, clientListIdx);

        /* #1001 Check if the client was subscribed for a multicast eventgroup and was the last subscribed client. */
        if(Sd_EventHandlerUsesMulticast(EventHandlerIdx) && (Sd_GetNrOfClientsOfEventHandlerDyn(EventHandlerIdx) == 0u))
        {
          /* #10010 Disable the multicast routing of the event handler. */
          (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(eventHandlerMulticastIdx),
            Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx));
        }
      }

      /* #200 Update the timer for the next state machine run. */
      Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetSubscribedUntilOfClientList(clientListIdx));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerSwitchMulticast()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerSwitchMulticast(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;
  Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(EventHandlerIdx);
  SoAd_SoConIdType assignedSoConId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enable the routing for the multicast socket connection. */
  (void)Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(eventHandlerMulticastIdx),
    Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx));

  /* #20 Iterate over all registered clients of an eventgroup in order to disable the unicast routing groups. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    if(Sd_GetClientStateOfClientList(clientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_SUBSCRIBED)
    {
      assignedSoConId = Sd_GetAssignedUdpSoConIdOfClientList(clientListIdx);

      if((assignedSoConId != SOAD_INV_SO_CON_ID) &&
        (Sd_GetMulticastThresholdOfEventHandler(EventHandlerIdx) != 1u))
      {
        Sd_UtilServer_ResetActivationCount(EventHandlerIdx, assignedSoConId);

        /* #200 Disable the routing for the unicast socket connection. */
        (void)Sd_Util_DisableSpecificRouting(
          (Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(Sd_GetEventHandlerUdpIdxOfEventHandler(EventHandlerIdx)),
          assignedSoConId);
      }
    }
  }

  /* #30 Update the state. */
  Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION);
}

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerSwitchUnicast()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerSwitchUnicast(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;
  Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(EventHandlerIdx);
  SoAd_SoConIdType assignedSoConId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all registered clients of an eventgroup in order to enable the unicast routing groups. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    if(Sd_GetClientStateOfClientList(clientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_SUBSCRIBED)
    {
      assignedSoConId = Sd_GetAssignedUdpSoConIdOfClientList(clientListIdx);

      /* #100 Enable the unicast routing group and increase the activation counter. */
      (void)Sd_Util_EnableSpecificRouting(
        (Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(Sd_GetEventHandlerUdpIdxOfEventHandler(EventHandlerIdx)),
        assignedSoConId);
      Sd_UtilServer_IncreaseActivationCount(EventHandlerIdx, assignedSoConId);
    }
  }

  /* #20 Disable the routing for the multicast socket connection. */
  (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(eventHandlerMulticastIdx),
    Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx));

  /* #30 Update the state. */
  Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_UNICAST_SUBSCRIPTION);
}

/**********************************************************************************************************************
 *  Sd_StateServer_EventHandlerCheckSubscribed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_EventHandlerCheckSubscribed(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the event handler has no subscribed clients, but is still in a subscribed state. */
  if((Sd_GetNrOfClientsOfEventHandlerDyn(EventHandlerIdx) == 0u) &&
    ((Sd_GetStateMachineOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION) ||
    (Sd_GetStateMachineOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_STATE_UNICAST_SUBSCRIPTION)))
  {
    /* #100 Check if the event handler was requested. */
    if(Sd_GetRequestStateOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_REQUESTED)
    {
      /* #1000 Set the state of the event handler to released and inform the BswM. */
      Sd_UtilServer_UpdateEventHandlerRequestState(EventHandlerIdx, SD_EVENT_HANDLER_RELEASED);
    }

    /* #101 Disable the multicast socket connection routing. */
    if(Sd_GetStateMachineOfEventHandlerDyn(EventHandlerIdx) == SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION)
    {
      eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(EventHandlerIdx);
      (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(Sd_GetEventHandlerMulticastIdxOfEventHandler(EventHandlerIdx)),
        Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx));
    }

    /* #102 Disable routing of UDP and TCP routing groups and reset activation count. */
    Sd_UtilServer_DisableRouting(EventHandlerIdx);

    /* #103 Update the state of the event handler. */
    Sd_UtilServer_UpdateEventHandlerStateMachine(EventHandlerIdx, SD_EVENT_HANDLER_STATE_NOT_SUBSCRIBED);
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_DisableRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_DisableRouting(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerTcpType eventHandlerTcpIdx;
  Sd_SizeOfEventHandlerUdpType eventHandlerUdpIdx;
  Sd_SoConActivationMapIterType soConActivationMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Disable routing of TCP event handler. */
  eventHandlerTcpIdx = Sd_GetEventHandlerTcpIdxOfEventHandler(EventHandlerIdx);
  if(eventHandlerTcpIdx != SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER)
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerTcp(eventHandlerTcpIdx));
  }

  /* #20 Disable routing of UDP event handler. */
  eventHandlerUdpIdx = Sd_GetEventHandlerUdpIdxOfEventHandler(EventHandlerIdx);
  if(eventHandlerUdpIdx != SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER)
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(eventHandlerUdpIdx));
  }

  /* #30 Reset the number of activations. */
  for(soConActivationMapIdx = Sd_GetSoConActivationMapStartIdxOfEventHandler(EventHandlerIdx);
    soConActivationMapIdx < Sd_GetSoConActivationMapEndIdxOfEventHandler(EventHandlerIdx);
    soConActivationMapIdx++)
  {
    Sd_SetNrOfActivationsOfSoConActivationMap(soConActivationMapIdx, 0u);                                               /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntry(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfServerType serverIdx;
  uint16 serverStartIdx, serverEndIdx;
  Sd_EntryType rxEntryType;
  uint16 rxServiceId;
  uint16 rxInstanceId;
  uint8 rxMajorVersion;
  uint16 rxReservedField;
  uint32 rxMinorVersion;
  uint16 rxEventGroupId;
  boolean foundService = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the header fields of the entry. */
  SD_GET_ENTRY_TYPE(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry, rxEntryType);
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_SERVICEID_OFFSET, rxServiceId);
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INSTANCEID_OFFSET, rxInstanceId);
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_MAJORVERSION_OFFSET, rxMajorVersion);

  /* #20 Get all services with the corresponding ServiceId */
  serverStartIdx = (uint16)Sd_GetServerStartIdxOfInstance(InstanceIdx);
  serverEndIdx = (uint16)Sd_GetServerEndIdxOfInstance(InstanceIdx);

  /* #30 Check if the ServiceId is wildcard. */
  if(rxServiceId != SD_ENTRY_WILDCARD_SERVICE_ID)
  {
    /* #300 ServiceId is no wildcard. Search for the matching server(s). */
    Sd_Util_GetServices(rxServiceId, Sd_Util_GetServerServiceId, &serverStartIdx, &serverEndIdx);                       /* SBSW_SD_REFERENCE_OF_VARIABLE */
  }
  else if(rxEntryType != SD_ENTRY_FIND_SERVICE)
  {
    /* #310 Wildcard ServiceId is only allowed for FindService messages. Do not process entry. */
    serverEndIdx = serverStartIdx;
  }
  else
  {
    /* #320 Received FindService entry with wildcard ServiceId. Process all servers of the instance. */
  }

  /* #40 Differentiate between entry types. */
  if(rxEntryType == SD_ENTRY_FIND_SERVICE)
  {
    /* #400 For FindService entries: Iterate over all matching servers to find the one corresponding to the entry. */
    for(serverIdx = (Sd_SizeOfServerType)serverStartIdx; serverIdx < (Sd_SizeOfServerType)serverEndIdx; serverIdx++)
    {
      SD_GET_UINT32(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY1_MINORVERSION_OFFSET, rxMinorVersion);

      /* #4000 Check if the InstanceId, MajorVersion and MinorVersion matches.
       *       Wildcards are allowed for FindService entries (format type 1). */
      if(((rxInstanceId == Sd_GetInstanceIdOfServer(serverIdx)) || (rxInstanceId == SD_ENTRY_WILDCARD_INSTANCE_ID)) &&
        ((rxMajorVersion == Sd_GetMajorVersionOfServer(serverIdx)) || (rxMajorVersion == SD_ENTRY_WILDCARD_MAJOR_VERSION)) &&
        ((rxMinorVersion == Sd_GetMinorVersionOfServer(serverIdx)) || (rxMinorVersion == SD_ENTRY_WILDCARD_MINOR_VERSION)))
      {
        /* #40000 Process the received FindService message. */
        Sd_RxServer_ProcessEntryFind(RxMessageInfoPtr, IndexOfEntry, serverIdx);                                        /* SBSW_SD_PASSING_API_POINTER */
      }
    }
  }
  else
  {
    /* #410 For (Stop)SubscribeEventgroup entries: Iterate over all matching servers to find the one corresponding to the entry. */
    for(serverIdx = (Sd_SizeOfServerType)serverStartIdx; serverIdx < (Sd_SizeOfServerType)serverEndIdx; serverIdx++)
    {
      /* #4100 Check if the InstanceId, MajorVersion and MinorVersion matches.
       *       Wildcards are not allowed for (Stop)SubscribeEventgroup entries (format type 2). */
      if((rxInstanceId == Sd_GetInstanceIdOfServer(serverIdx)) &&
        (rxMajorVersion == Sd_GetMajorVersionOfServer(serverIdx)))
      {
        /* #41000 Found the corresponding service instance. */
        foundService = TRUE;

        /* #41001 Process the received SubscribeEventgroup message. */
        Sd_RxServer_ProcessEntrySubscribe(RxMessageInfoPtr, IndexOfEntry, serverIdx);                                   /* SBSW_SD_PASSING_API_POINTER */

        if(rxServiceId != SD_SERVICE_ID_OTHERSERV)
        {
          break;
        }
      }
    }

    /* #420 Send a negative acknowledgement if the ServiceId or the InstanceId are unknown. */
    if((Sd_GetServerStartIdxOfInstance(InstanceIdx) != Sd_GetServerEndIdxOfInstance(InstanceIdx)) &&
      (foundService == FALSE))
    {
      SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_RESERVEDCOUNTER_OFFSET, rxReservedField);
      SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_EVENTGROUPID_OFFSET, rxEventGroupId);

      Sd_Util_AddEventGroupNackEntryToList(InstanceIdx, Sd_GetSizeOfServer(), rxServiceId, rxInstanceId, rxMajorVersion,
        rxReservedField, rxEventGroupId, RxMessageInfoPtr->AddressStorageIdx, Sd_GetSizeOfServerTimer());
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntryFind()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntryFind(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 1 */ /* MD_Sd_Rule-2.2_2981 */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_NOT_OK;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetServerTimerIdxOfServer(ServerIdx);
  Sd_ConfigOptionStringType rxConfigOptionPtrArray[Sd_GetMaxNrOptionsPerEntry() + 1u];
  Sd_AttachedOptionsType attachedOptions;
  uint32 rxTTL;
  uint32 randDelay = 0u;
  uint8 index1stOption, index2ndOption;
  uint8 nr1stOptions, nr2ndOptions;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0314 1 */ /* MD_Sd_Dir-1.1_0314 */
  IpBase_Fill((SD_P2VAR(void))rxConfigOptionPtrArray, 0u, sizeof(rxConfigOptionPtrArray));                              /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_IPBASE_FILL */
  attachedOptions.EndpointAddrUdp.family = SOAD_AF_INVALID;
  attachedOptions.EndpointAddrTcp.family = SOAD_AF_INVALID;
  attachedOptions.ConfigOptionPtrArrayPtr = rxConfigOptionPtrArray;

  /* #10 Read header of FindService entry. */
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX1_OFFSET, index1stOption);
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX2_OFFSET, index2ndOption);
  SD_GET_NROFOPT(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry, nr1stOptions, nr2ndOptions);
  SD_GET_UINT24(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_TTL_OFFSET, rxTTL);

  /* #20 Check if the FindService messages has to be ignored. */
  if((Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_DOWN) ||
    (Sd_GetStateMachineOfServerDyn(ServerIdx) == SD_SERVER_STATE_READY_INITIAL_WAIT)||
    (rxTTL == 0u))
  {
    /* #200 Ignore FindService messages if the server service is not available, during the initial wait phase, or with a TTL == 0 */
  }
  /* #30 Otherwise, process the FindService.*/
  else
  {
    /* #300 Process the corresponding option array(s).
     *      Configuration options are allowed, endpoint options shall be ignored. */

    /* #301 Check if a first option run is available.*/
    if(nr1stOptions != 0u)
    {
      /* #3010 Process first option run. */
      optionsRetVal = Sd_RxServer_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index1stOption, nr1stOptions,
        Sd_GetSizeOfEventHandler(), &attachedOptions);                                                                  /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    }

    /* #400 Check if a second option run is available.*/
    if((nr2ndOptions != 0u) && ((nr1stOptions == 0u) || (optionsRetVal == SD_OPTIONS_OK)))
    {
      /* #4000 Process second option run. */
      optionsRetVal = Sd_RxServer_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index2ndOption, nr2ndOptions,
        Sd_GetSizeOfEventHandler(), &attachedOptions);                                                                  /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    }
    /* #500 Otherwise, check if both option runs are empty.*/
    else if((nr1stOptions == 0u) && (nr2ndOptions == 0u))                                                               /* PRQA S 2995 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
    {
      /* #5000 Find messages without any attached option are also allowed. */
      optionsRetVal = SD_OPTIONS_OK;
    }
    /* #600 Otherwise, nothing to process.*/
    else
    {
      /* #6000 Entry does not contain a second option run. Keep result of first option run. */
    }

    /* #700 Process the find entry. */
    if((optionsRetVal == SD_OPTIONS_OK) && (Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED))
    {
      /* #7000 Check the attached configuration options by a user callout. */
      optionsRetVal = Sd_RxServer_CheckConfigOptionByCbk(
        ServerIdx,
        (RxMessageInfoPtr->MulticastMessage == TRUE) ? Sd_GetMulticastRxPduIdOfInstance(instanceIdx) : Sd_GetUnicastRxPduIdOfInstance(instanceIdx),
        SD_ENTRY_FIND_SERVICE,
        rxConfigOptionPtrArray);                                                                                        /* SBSW_SD_REFERENCE_OF_VARIABLE */

      if(optionsRetVal == SD_OPTIONS_OK)
      {
        /* #70000 Check if the FindService message was transmitted by multicast or unicast. */
        if(RxMessageInfoPtr->MulticastMessage == TRUE)
        {
          /* Add a random delay to the response message. */
          randDelay = Sd_Util_GetRandomNrInRangeForResponse(Sd_GetRequestResponseMinDelayOfServerTimer(serverTimerIdx),
            Sd_GetRequestResponseMaxDelayOfServerTimer(serverTimerIdx), TRUE);
        }

        /* #70001 Add a unicast OfferService message to the list of sendentries. */
        Sd_Util_AddUnicastOfferEntryToList(ServerIdx, RxMessageInfoPtr->AddressStorageIdx, randDelay);
      }
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxServer_ProcessEntrySubscribe(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfEventHandlerType eventHandlerIdx;
  Sd_ConfigOptionStringType rxConfigOptionPtrArray[Sd_GetMaxNrOptionsPerEntry() + 1u];
  Sd_AttachedOptionsType attachedOptions;
  uint16 rxServiceId, rxInstanceId;
  uint16 rxReservedField;
  uint16 rxEventGroupId;
  uint8 rxMajorVersion;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0314 1 */ /* MD_Sd_Dir-1.1_0314 */
  IpBase_Fill((SD_P2VAR(void))rxConfigOptionPtrArray, 0u, sizeof(rxConfigOptionPtrArray));                              /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_IPBASE_FILL */
  attachedOptions.EndpointAddrUdp.family = SOAD_AF_INVALID;
  attachedOptions.EndpointAddrTcp.family = SOAD_AF_INVALID;
  attachedOptions.ConfigOptionPtrArrayPtr = rxConfigOptionPtrArray;

  /* #10 Search for the matching event handler to process the SubscribeEventgroup message. */
  eventHandlerIdx = Sd_RxServer_SearchEventHandler(RxMessageInfoPtr, IndexOfEntry, ServerIdx);                          /* SBSW_SD_PASSING_API_POINTER */

  /* #20 Check if a matching event handler was found and the state of the corresponding server is available. */
  if((eventHandlerIdx < Sd_GetSizeOfEventHandler()) &&
    (Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_AVAILABLE))
  {
    /* #200 Process the attached option array. */
    optionsRetVal = Sd_RxServer_ProcessOptionArray(
      RxMessageInfoPtr->PduInfoPtr, IndexOfEntry, eventHandlerIdx, &attachedOptions);                                   /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #201 Check if the options array is valid and all required endpoint options are present. */
    if(optionsRetVal == SD_OPTIONS_OK)
    {
      /* #2010 Check the attached configuration options by a user callout. */
      optionsRetVal = Sd_RxServer_CheckConfigOptionByCbk(
        ServerIdx,
        (RxMessageInfoPtr->MulticastMessage == TRUE) ? Sd_GetMulticastRxPduIdOfInstance(instanceIdx) : Sd_GetUnicastRxPduIdOfInstance(instanceIdx),
        SD_ENTRY_SUBSCRIBE_EVENTGROUP,
        rxConfigOptionPtrArray);                                                                                        /* SBSW_SD_REFERENCE_OF_VARIABLE */

      if(optionsRetVal == SD_OPTIONS_OK)
      {
        /* #20100 Save all required elements of the subscription. */
        retVal = Sd_RxServer_ProcessEntrySubscribeInternal(
          eventHandlerIdx, RxMessageInfoPtr, IndexOfEntry, &attachedOptions);                                           /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      }
    }
  }
  /* #30 Otherwise the service instance is not ready or there is no matching event handler. */
  else
  {
    /* #300 Leave retVal at value E_NOT_OK. This will trigger a transmission of a SubscribeEventgroupNack message. */
  }

  /* #40 Send a NACK if we were not able to process the SUBSCRIBE, if no endpoint option was attached or if the eventgroup was not configured. */
  /* PRQA S 2996 2 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
  if((optionsRetVal != SD_OPTIONS_WRONG_SUBNET) &&
    ((retVal != E_OK) || (eventHandlerIdx == Sd_GetSizeOfEventHandler())))
  {
    Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetSizeOfServerTimer();

    SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_SERVICEID_OFFSET, rxServiceId);
    SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INSTANCEID_OFFSET, rxInstanceId);
    SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_MAJORVERSION_OFFSET, rxMajorVersion);
    SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_RESERVEDCOUNTER_OFFSET, rxReservedField);
    SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_EVENTGROUPID_OFFSET, rxEventGroupId);

    if(RxMessageInfoPtr->MulticastMessage == TRUE)
    {
      /* #400 Add additional delay to NACK message. */
      if(eventHandlerIdx < Sd_GetSizeOfEventHandler())
      {
        serverTimerIdx = Sd_GetServerTimerIdxOfEventHandler(eventHandlerIdx);
      }
      else
      {
        serverTimerIdx = Sd_GetServerTimerIdxOfServer(ServerIdx);
      }
    }

    Sd_Util_AddEventGroupNackEntryToList(instanceIdx, ServerIdx, rxServiceId, rxInstanceId, rxMajorVersion,
      rxReservedField, rxEventGroupId, RxMessageInfoPtr->AddressStorageIdx, serverTimerIdx);
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_SearchEventHandler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfEventHandlerType, SD_CODE) Sd_RxServer_SearchEventHandler(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerType eventHandlerIdx;
  uint16 rxEventGroupId;
  boolean foundEventHandler = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the eventgroup ID from the SD header. */
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_EVENTGROUPID_OFFSET, rxEventGroupId);

  /* #20 Iterate trough each event handler to find the corresponding one. */
  for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(ServerIdx);
    eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(ServerIdx);
    eventHandlerIdx++)
  {
    if(Sd_GetEventGroupIdOfEventHandler(eventHandlerIdx) == rxEventGroupId)
    {
      /* #200 Found the corresponding event handler. Stop searching. */
      foundEventHandler = TRUE;
      break;
    }
  }

  /* #30 Set the eventHandlerIdx to an invalid value if no matching event handler was found. */
  if(foundEventHandler == FALSE)
  {
    eventHandlerIdx = Sd_GetSizeOfEventHandler();
  }

  return eventHandlerIdx;
}

/**********************************************************************************************************************
 *  Sd_RxServer_CheckConfigOptionByCbk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_CheckConfigOptionByCbk(
  Sd_SizeOfServerType ServerIdx,
  PduIdType RxPduId,
  Sd_EntryType RxEntryType,
  SD_P2CONST(Sd_ConfigOptionStringType) RxConfigOptionPtrArrayPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the attached configuration options by a user callout. */
  if(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfServer(ServerIdx) != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER)
  {
    Sd_ConfigOptionStringType configOptionPtrArray[3u] = { NULL_PTR, NULL_PTR, NULL_PTR };

    /* #100 Add configuration options of hostname and capability records to the configuration option pointer array. */
    Sd_Rx_FillConfigOptionPtrArray(configOptionPtrArray,
      Sd_GetCapabilityRecordStartIdxOfInstance(Sd_GetInstanceIdxOfServer(ServerIdx)),
      Sd_GetCapabilityRecordStartIdxOfServer(ServerIdx),
      SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER);                                                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Call application to verify configuration options of received message. */
    if(TRUE != Sd_GetCapabilityRecordFunctionCalloutPtr(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfServer(ServerIdx))(
      RxPduId,
      (uint8)RxEntryType,
      Sd_GetServiceIdOfServer(ServerIdx),
      Sd_GetInstanceIdOfServer(ServerIdx),
      Sd_GetMajorVersionOfServer(ServerIdx),
      Sd_GetMinorVersionOfServer(ServerIdx),
      RxConfigOptionPtrArrayPtr,
      configOptionPtrArray))                                                                                            /* SBSW_SD_FUNCTION_PTR_CALL */
    {
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionArray()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionArray(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_NOT_OK;
  uint8 index1stOption, index2ndOption;
  uint8 nr1stOptions, nr2ndOptions;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the referenced options from the entry. */
  SD_GET_UINT8(PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX1_OFFSET, index1stOption);
  SD_GET_UINT8(PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX2_OFFSET, index2ndOption);
  SD_GET_NROFOPT(PduInfoPtr, IndexOfEntry, nr1stOptions, nr2ndOptions);

  /* #20 Process the corresponding option array(s) and read the data of the attached endpoints. */

  /* #30 Check if a first option run is available.*/
  if(nr1stOptions != 0u)
  {
    /* #300 Process first option run. */
    optionsRetVal = Sd_RxServer_ProcessOptionRun(PduInfoPtr, index1stOption, nr1stOptions,
      EventHandlerIdx, AttachedOptionsPtr);                                                                             /* SBSW_SD_PASSING_API_POINTER */
  }

  /* #40 Check if a second option run is available.*/
  if((nr2ndOptions != 0u) && ((nr1stOptions == 0u) || (optionsRetVal == SD_OPTIONS_OK)))
  {
    /* #400 Process second option run. */
    optionsRetVal = Sd_RxServer_ProcessOptionRun(PduInfoPtr, index2ndOption, nr2ndOptions,
      EventHandlerIdx, AttachedOptionsPtr);                                                                             /* SBSW_SD_PASSING_API_POINTER */
  }
  /* #50 Otherwise, check if both option runs are empty.*/
  else if((nr1stOptions == 0u) && (nr2ndOptions == 0u))                                                                 /* PRQA S 2995 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
  {
    if(Sd_EventHandlerUsesMulticast(EventHandlerIdx))
    {
      /* #500 If the EventGroup is configured for multicast, allow the subscription without any attached endpoint option. */
      optionsRetVal = SD_OPTIONS_OK;
    }
  }
  /* #60 Otherwise, nothing to process.*/
  else
  {
    /* #600 Entry does not contain a second option run. Keep result of first run. */
  }

  /* #70 Check if all required endpoint options are present. */
  if((optionsRetVal == SD_OPTIONS_OK) &&
    ((Sd_EventHandlerUsesUdp(EventHandlerIdx) && (AttachedOptionsPtr->EndpointAddrUdp.family == SOAD_AF_INVALID)) ||
    (Sd_EventHandlerUsesTcp(EventHandlerIdx) && (AttachedOptionsPtr->EndpointAddrTcp.family == SOAD_AF_INVALID))))
  {
    /* #700 Not all required endpoint options are present. Reject message. */
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionRun()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionRun(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  uint8 NrOfOptions,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  uint8 currentOptionIndex = IndexOfOption;
  Sd_OptionType optionType;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Stop processing of the message if the header indexes more options than attached
   *     or if the size of the options array is exceeded. */
  if(Sd_GetNrOfOptions() < ((Sd_NrOfOptionsType)IndexOfOption + (Sd_NrOfOptionsType)NrOfOptions))
  {
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  /* #20 Process consecutive options. */
  while((optionsRetVal == SD_OPTIONS_OK) && ((IndexOfOption + NrOfOptions) > currentOptionIndex))
  {
    /* #200 Read the option information. */
    SD_GET_OPTION_TYPE(PduInfoPtr, Sd_GetOptionIndex(currentOptionIndex), optionType);

    /* #201 Differentiate between service- and eventgroup entry. */
    if(EventHandlerIdx == Sd_GetSizeOfEventHandler())
    {
      /* #2010 Received FindService message. */

      if(optionType == SD_OPTION_CONFIGURATION)
      {
        /* #20100 Check if configuration option is valid. */
        optionsRetVal = Sd_Rx_CheckConfigOption(
          PduInfoPtr, currentOptionIndex, AttachedOptionsPtr->ConfigOptionPtrArrayPtr);                                 /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_ATTACHED_OPTIONS_PTR */
      }
      else
      {
        /* #20101 Endpoint or unknown options are not allowed for FindService entries and shall be ignored. */
      }
    }
    else
    {
      /* #2011 Received (Stop)SubscribeEventgroup message. Trigger processing. */
      optionsRetVal = Sd_RxServer_ProcessOptionSubscribe(
        PduInfoPtr, currentOptionIndex, EventHandlerIdx, AttachedOptionsPtr);                                           /* SBSW_SD_PASSING_API_POINTER */
    }

    currentOptionIndex++;
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessOptionSubscribe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxServer_ProcessOptionSubscribe(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  uint8 currentOption = IndexOfOption;
  Sd_OptionType optionType;
  Sd_L4ProtocolType optionL4Proto = SD_L4PROTOCOL_NONE;
  uint16 addrType = SOAD_AF_INVALID;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the option information. */
  SD_GET_OPTION_TYPE(PduInfoPtr, Sd_GetOptionIndex(IndexOfOption), optionType);

  /* #20 Differentiate between configuration option or endpoint option. */
  if(optionType == SD_OPTION_CONFIGURATION)
  {
    /* #200 Configuration option: Check if valid. */
    optionsRetVal = Sd_Rx_CheckConfigOption(PduInfoPtr, currentOption, AttachedOptionsPtr->ConfigOptionPtrArrayPtr);    /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_ATTACHED_OPTIONS_PTR */
  }
  else
  {
    /* #201 Endpoint option: Read the type values. */
    Sd_Rx_GetEndpointOptionParameters(PduInfoPtr, IndexOfOption, FALSE, &addrType, &optionL4Proto);                     /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #202 Check if a valid endpoint option was attached. */
    if(addrType != SOAD_AF_INVALID)
    {
      /* #2020 Read the attached endpoint option. */
      optionsRetVal = Sd_Rx_ReadEndpointOptions(PduInfoPtr, currentOption, addrType, optionL4Proto, AttachedOptionsPtr); /* SBSW_SD_PASSING_API_POINTER */

      if(optionsRetVal == SD_OPTIONS_OK)
      {
        Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);

        /* #20200 Check if the attached endpoint addresses are part of the subnet. */
        optionsRetVal = Sd_Rx_CheckSubnets(
          Sd_IsEventHandlerUdpUsedOfEventHandler(EventHandlerIdx) ? Sd_GetUdpSoConStartIdxOfServer(serverIdx) : Sd_GetSizeOfUdpSoCon(),
          Sd_IsEventHandlerTcpUsedOfEventHandler(EventHandlerIdx) ? Sd_GetTcpSoConIdStartIdxOfServer(serverIdx) : Sd_GetSizeOfTcpSoConId(),
          AttachedOptionsPtr);                                                                                          /* SBSW_SD_PASSING_API_POINTER */
      }
    }
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribeInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_ProcessEntrySubscribeInternal(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  Sd_SizeOfClientListType clientListIdx;
  uint32 rxTTL;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the TTL of the received SubscribeEventgroup message to identify a StopSubscribeEventgroup entry. */
  SD_GET_UINT24(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_TTL_OFFSET, rxTTL);

  /* #20 Search the client in the list of subscribed clients, or create a new entry if not found.
   *     An unknown client will not be added to the list if it transmitted a StopSubscribeEventgroup entry. */
  clientListIdx = Sd_RxServer_FindClientInList(EventHandlerIdx, RxMessageInfoPtr, AttachedOptionsPtr,
    (rxTTL == 0u) ? FALSE : TRUE);                                                                                      /* SBSW_SD_PASSING_API_POINTER */

  if(clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx))
  {
    /* #200 If the client is valid, save all parameters and endpoints.
     *      The processing will be done in the next main function cycle. */
    retVal = Sd_RxServer_ProcessEntrySubscribeSaveParameters(RxMessageInfoPtr, IndexOfEntry,
      EventHandlerIdx, clientListIdx, AttachedOptionsPtr);                                                              /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #201 Check if all required parameters of the event could be saved. */
    if(retVal == E_NOT_OK)
    {
      /* #2010 Not able to save all required parameters. */
      if(Sd_GetNrOfReferencesOfClientList(clientListIdx) == 0u)
      {
        /* #20100 Remove the client from list. */
        Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                            /* SBSW_SD_CSL01 */
      }
    }
  }
  else
  {
    /* #210 Otherwise, the client is not valid. Check if it transmitted a StopSubscribeEventgroup entry. */
    if(rxTTL == 0u)
    {
      /* #2100 Unknown client transmitted a StopSubscribeEventgroup entry. Ignore this entry. */
      retVal = E_OK;
    }
    else
    {
      /* #2101 Otherwise, the maximum amount of clients is reached. Not able to process this request. */
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_ProcessEntrySubscribeSaveParameters()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_ProcessEntrySubscribeSaveParameters(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(serverIdx);
  uint32 rxTTL;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the TTL reserved field and counter of the received SubscribeEventgroup message. */
  SD_GET_UINT24(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_TTL_OFFSET, rxTTL);
  Sd_SetRequestedTTLOfClientList(ClientListIdx, rxTTL);                                                                 /* SBSW_SD_API_ARGUMENT_IDX */
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr,                                                                           /* SBSW_SD_API_ARGUMENT_IDX */
    IndexOfEntry + SD_ENTRY2_RESERVEDCOUNTER_OFFSET, *Sd_GetAddrRxReservedOfClientList(ClientListIdx));

  SD_BEGIN_CRITICAL_SECTION();

  /* #20 Save all attached endpoints, the processing will be done in the next main function cycle. */
  if(Sd_EventHandlerUsesUdp(EventHandlerIdx))
  {
    /* #200 Save the received UDP endpoint. */
    Sd_EndpointStorageUdpIdxOfClientListType endpointStorageIdx = Sd_GetEndpointStorageUdpIdxOfClientList(ClientListIdx);

    retVal = Sd_RxServer_SaveEndpoint(instanceIdx, &AttachedOptionsPtr->EndpointAddrUdp,
      SD_ENDPOINT_TYPE_UDP, &endpointStorageIdx);                                                                       /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    Sd_SetEndpointStorageUdpIdxOfClientList(ClientListIdx, endpointStorageIdx);                                         /* SBSW_SD_API_ARGUMENT_IDX */
  }

  if(Sd_EventHandlerUsesTcp(EventHandlerIdx))
  {
    /* #201 Save the received TCP endpoint. */
    Sd_EndpointStorageTcpIdxOfClientListType endpointStorageIdx = Sd_GetEndpointStorageTcpIdxOfClientList(ClientListIdx);

    retVal |= Sd_RxServer_SaveEndpoint(instanceIdx, &AttachedOptionsPtr->EndpointAddrTcp,
      SD_ENDPOINT_TYPE_TCP, &endpointStorageIdx);                                                                       /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    Sd_SetEndpointStorageTcpIdxOfClientList(ClientListIdx, endpointStorageIdx);                                         /* SBSW_SD_API_ARGUMENT_IDX */
  }

  /* #30 Check if the endpoints could be saved. */
  if(retVal == E_OK)
  {
    /* #300 Save the received (Stop)SubscribeEventgroup message as event. */
    Sd_ServerEventgroupEventType eventFlag = SD_SERVER_EVENT_EVENTGROUP_NONE;

    if(RxMessageInfoPtr->MulticastMessage == TRUE)
    {
      eventFlag = (Sd_ServerEventgroupEventType)(eventFlag | SD_SERVER_EVENT_EVENTGROUP_MULTICAST_FLAG); /*lint !e655 */
    }

    if(RxMessageInfoPtr->RebootDetected == TRUE)
    {
      eventFlag = (Sd_ServerEventgroupEventType)(eventFlag | SD_SERVER_EVENT_EVENTGROUP_REBOOT_FLAG); /*lint !e655 */
    }

    if(rxTTL == 0u)
    {
      /* SD_ENTRY_STOP_SUBSCRIBE_EVENTGROUP */
      retVal = Sd_RxServer_AddEventToRingBuffer(instanceIdx,
        EventHandlerIdx, ClientListIdx,
        (Sd_ServerEventgroupEventType)(SD_SERVER_EVENT_EVENTGROUP_STOP_SUBSCRIBE | eventFlag)); /*lint !e655 */
    }
    else
    {
      /* SD_ENTRY_SUBSCRIBE_EVENTGROUP */
      retVal = Sd_RxServer_AddEventToRingBuffer(instanceIdx,
        EventHandlerIdx, ClientListIdx,
        (Sd_ServerEventgroupEventType)(SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE | eventFlag)); /*lint !e655 */
    }
  }

  SD_END_CRITICAL_SECTION();

  Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
  Sd_Util_TriggerStateMachineRun(instanceIdx);

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_EventServer_Process()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_Process(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfRxEventType rxEventIdx;
  Sd_SizeOfEventHandlerType eventHandlerIdx;
  boolean pendingStopSubscribe = FALSE, keepEntry;
  boolean discardEvent;
  Sd_QueueProcessLimitOfInstanceType entriesToProcessLeft;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine maximum number of entries to process in one cycle. */
  entriesToProcessLeft = Sd_GetQueueProcessLimitOfInstance(InstanceIdx);

  /* #20 Process pending events for event handler. */
  while((TRUE == Sd_EventServer_GetFirstIdx(InstanceIdx, &rxEventIdx)) && (entriesToProcessLeft > 0u))                    /* SBSW_SD_REFERENCE_OF_VARIABLE */
  {
    eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(rxEventIdx);

    /* #200 Check that the event handler as well as the remote client are in valid states. */
    if((Sd_GetClientStateOfClientList(Sd_GetClientListIdxOfRxEvent(rxEventIdx)) != SD_EVENT_HANDLER_CLIENT_STATE_INVALID) &&
      ((Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_NOT_SUBSCRIBED) ||
      (Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_UNICAST_SUBSCRIPTION) ||
      (Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION)))
    {
      /* #2000 Check if event needs to be discarded. */
      discardEvent = Sd_EventServer_DiscardEvent(InstanceIdx, rxEventIdx);

      if(discardEvent == FALSE)
      {
        /* #20000 Process the pending event. */
        keepEntry = Sd_EventServer_ProcessEvent(rxEventIdx, &pendingStopSubscribe);                                       /* SBSW_SD_REFERENCE_OF_VARIABLE */

        if(keepEntry == TRUE)
        {
          /* #20001 Do not remove the entry from the list in order to process it in the next MainFunction cycle.
           *       Stop processing of remaining entries. */
          break;
        }
      }
      /* #3000 If StopSubscribe-Subscribe sequence and StopSubscribe has been discarded,
               check if notifications have to be sent. */
      /* PRQA S 3415 3 */ /* MD_Sd_12.4_3415 */
      else if((Sd_GetEventOfRxEvent(rxEventIdx) == SD_SERVER_EVENT_EVENTGROUP_STOP_SUBSCRIBE) &&
              (Sd_EventServer_IsTriggerTransmitEnabled(rxEventIdx) == TRUE))
      {
          /* #30000 Notifications needed, save the request in the trigger transmit list. */
          (void)Sd_TriggerTransmit_Add(rxEventIdx);
      }
      else
      {
        /* Nothing to do */
      }
    }

    /* #201 Remove the processed event from the buffer. */
    Sd_EventServer_RemoveFirst(InstanceIdx);
    entriesToProcessLeft--;
  }
}

/**********************************************************************************************************************
*  Sd_EventServer_DiscardEvent()
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
*/
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_DiscardEvent(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType CurrentRxEventIdx)
{
  Sd_ServerEventgroupEventType currentEventType;
  Sd_ServerEventgroupEventType revertEventType;
  Sd_SizeOfRxEventType nextEventIdx;
  boolean discardCurrentEvent = FALSE;

  /* #10 Get event type of current event which is being processed. */
  currentEventType = Sd_GetEventOfRxEvent(CurrentRxEventIdx);

  /* #20 Never discard events with set reboot flag. */
  if((currentEventType & SD_SERVER_EVENT_EVENTGROUP_REBOOT_FLAG) == 0) /*lint !e655 */
  {
    /* #30 Remove multicast flag since it is not relevant for this functionality. */
    currentEventType = (Sd_ServerEventgroupEventType)(currentEventType & (Sd_ServerEventgroupEventType)(~SD_SERVER_EVENT_EVENTGROUP_MULTICAST_FLAG)); /*lint !e655 */

    /* #40 Determine event type which would revert the state of the CEG to the current state. */
    if(currentEventType == SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE)
    {
      revertEventType = SD_SERVER_EVENT_EVENTGROUP_STOP_SUBSCRIBE;
    }
    else
    {
      revertEventType = SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE;
    }

    /* #50 Get index of following event in queue. */
    nextEventIdx = Sd_EventServer_GetFollowingIdx(InstanceIdx, CurrentRxEventIdx);

    /* #60 Iterate over all following events in the queue. */
    while(nextEventIdx != Sd_GetSizeOfRxEvent())
    {
      /* #600 If a following event will nullify the currently processed event, the currently processed event can be discarded. */
      if(((Sd_GetEventOfRxEvent(nextEventIdx) & ((Sd_ServerEventgroupEventType)(~SD_SERVER_EVENT_EVENTGROUP_MULTICAST_FLAG))) == revertEventType) && /*lint !e655 */
        (Sd_GetClientListIdxOfRxEvent(nextEventIdx) == Sd_GetClientListIdxOfRxEvent(CurrentRxEventIdx)))
      {
        discardCurrentEvent = TRUE;
        break;
      }

      nextEventIdx = Sd_EventServer_GetFollowingIdx(InstanceIdx, nextEventIdx);
    }
  }

  return discardCurrentEvent;
}

/**********************************************************************************************************************
 *  Sd_EventServer_ProcessEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_ProcessEvent(
  Sd_SizeOfRxEventType RxEventIdx,
  SD_P2VAR(boolean) PendingStopSubscribePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean keepEntry = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  Sd_ServerEventgroupEventType eventType = Sd_GetEventOfRxEvent(RxEventIdx);

  /* #10 Check the type of the received entry. */
  if((eventType == SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE) ||
    (eventType == SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE_MULTI))
  {
    /* #100 SubscribeEventgroup: Check if there was a pending StopSubscribeEventgroup event which has to be processed first. */
    if(*PendingStopSubscribePtr == TRUE)
    {
      /* #1000 There is a pending StopSubscribeEventgroup which has to be handled during the next run of the SoAd_MainFunction().
       *       Resume processing of the subscription in the next MainFunction cycle. */
      keepEntry = TRUE;
    }
    else
    {
      /* #1001 Otherwise, process subscription of remote client. */
      Sd_EventServer_Subscription(RxEventIdx);
    }
  }
  else if((eventType == SD_SERVER_EVENT_EVENTGROUP_STOP_SUBSCRIBE) ||
    (eventType == SD_SERVER_EVENT_EVENTGROUP_STOP_SUBSCRIBE_MULTI))
  {
    /* #101 StopSubscribeEventgroup: Subscription was stopped, remove the client. */
    Sd_UtilServer_RemoveClientFromList(Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx), Sd_GetClientListIdxOfRxEvent(RxEventIdx));
    *PendingStopSubscribePtr = TRUE;                                                                                    /* SBSW_SD_VALID_API_POINTER */
  }
  else /* The event is a SubscribeEventgroup or StopSubscribeEventgroup entry and the REBOOT flag is set. */
  {
    /* #102 Reboot detected: Remove the REBOOT flag from the entry,
     *      but keep the entry in the list in order to process it in the next MainFunction cycle */
    Sd_SetEventOfRxEvent(RxEventIdx,                                                                                    /* SBSW_SD_RXEVENT_IDX */
      (Sd_ServerEventgroupEventType)(eventType ^ SD_SERVER_EVENT_EVENTGROUP_REBOOT_FLAG)); /*lint !e655 */

    keepEntry = TRUE;
  }

  return keepEntry;
}

/**********************************************************************************************************************
 *  Sd_StateServer_Update()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateServer_Update(
  Sd_SizeOfServerType ServerIdx,
  Sd_ServerStateMachineType NewState,
  boolean ResetTimeToTriggerSend)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the new state of the state machine. */
  Sd_SetStateMachineOfServerDyn(ServerIdx, NewState);                                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Mark server service for state machine execution and set a timer event. */
  Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfServer(ServerIdx));

  if(ResetTimeToTriggerSend == TRUE)
  {
    /* #200 Reset the TimeToTriggerSend. */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfServerDyn(ServerIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_UpdateEventHandlerStateMachine()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_UpdateEventHandlerStateMachine(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_EventHandlerStateMachineType NewState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ServerIdxOfEventHandlerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the new state of the state machine. */
  Sd_SetStateMachineOfEventHandlerDyn(EventHandlerIdx, NewState);                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Mark server service for state machine execution and set a timer event. */
  Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfServer(serverIdx));
}

/**********************************************************************************************************************
 *  Sd_UtilServer_UpdateEventHandlerRequestState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_UpdateEventHandlerRequestState(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_EventHandlerCurrentStateType NewState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ServerIdxOfEventHandlerType serverIdx = Sd_GetServerIdxOfEventHandler(EventHandlerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the request state to the new value. */
  Sd_SetRequestStateOfEventHandlerDyn(EventHandlerIdx, NewState);                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Trigger state machine execution for the next MainFunction cycle. */
  Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfServer(serverIdx));

  /* #30 Inform the BswM about the new request state. */
  BswM_Sd_EventHandlerCurrentState(Sd_GetHandleIdOfEventHandler(EventHandlerIdx), NewState);
}

/**********************************************************************************************************************
 *  Sd_RxServer_AddEventToRingBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_AddEventToRingBuffer(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  Sd_ServerEventgroupEventType Event)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType eventSaved = E_NOT_OK;
  Sd_SizeOfRxEventType rxEventIdx;
  Sd_SizeOfEndpointStorageType endpointStorageIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ring buffer is full. */
  if(!Sd_IsRxEventListFullOfInstanceDyn(InstanceIdx))
  {
    SD_BEGIN_CRITICAL_SECTION();
    eventSaved = E_OK;

    /* #100 Save the received event. */
    rxEventIdx = Sd_GetRxEventEndIdxOfInstanceDyn(InstanceIdx);
    Sd_SetEventHandlerIdxOfRxEvent(rxEventIdx, EventHandlerIdx);                                                        /* SBSW_SD_RXEVENT_IDX */
    Sd_SetClientListIdxOfRxEvent(rxEventIdx, ClientListIdx);                                                            /* SBSW_SD_RXEVENT_IDX */
    Sd_SetEventOfRxEvent(rxEventIdx, Event);                                                                            /* SBSW_SD_RXEVENT_IDX */

    /* #101 Update the entry of the client list. */
    Sd_IncNrOfReferencesOfClientList(ClientListIdx);                                                                    /* SBSW_SD_API_ARGUMENT_IDX */

    endpointStorageIdx = Sd_GetEndpointStorageTcpIdxOfClientList(ClientListIdx);
    if(endpointStorageIdx < Sd_GetSizeOfEndpointStorage())
    {
      Sd_IncNrOfReferencesOfEndpointStorage(endpointStorageIdx);                                                        /* SBSW_SD_CSL01 */
    }

    endpointStorageIdx = Sd_GetEndpointStorageUdpIdxOfClientList(ClientListIdx);
    if(endpointStorageIdx < Sd_GetSizeOfEndpointStorage())
    {
      Sd_IncNrOfReferencesOfEndpointStorage(endpointStorageIdx);                                                        /* SBSW_SD_CSL01 */
    }

    /* #102 Increment the ring buffer end index. */
    Sd_IncRxEventEndIdxOfInstanceDyn(InstanceIdx);                                                                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    /* #103 Handle wrap around. */
    if(Sd_GetRxEventEndIdxOfInstanceDyn(InstanceIdx) >= Sd_GetRxEventEndIdxOfInstance(InstanceIdx))
    {
      Sd_SetRxEventEndIdxOfInstanceDyn(InstanceIdx, Sd_GetRxEventStartIdxOfInstance(InstanceIdx));                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    /* #104 Check if the ring buffer is full. */
    if(Sd_GetRxEventEndIdxOfInstanceDyn(InstanceIdx) == Sd_GetRxEventStartIdxOfInstanceDyn(InstanceIdx))
    {
      Sd_SetRxEventListFullOfInstanceDyn(InstanceIdx, TRUE);                                                            /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    SD_END_CRITICAL_SECTION();
  }
  else
  {
    /* #105 The ring buffer is full. Not able to save the event. */
  }

  return eventSaved;
}

/**********************************************************************************************************************
 *  Sd_EventServer_GetFirstIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_GetFirstIdx(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2VAR(Sd_SizeOfRxEventType) EventIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean eventRead = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ring buffer contains an element. */
  if((Sd_GetRxEventStartIdxOfInstanceDyn(InstanceIdx) != Sd_GetRxEventEndIdxOfInstanceDyn(InstanceIdx)) ||
    Sd_IsRxEventListFullOfInstanceDyn(InstanceIdx))
  {
    /* #100 Read the first element from of the buffer. */
    *EventIdxPtr = Sd_GetRxEventStartIdxOfInstanceDyn(InstanceIdx);                                                     /* SBSW_SD_VALID_API_POINTER */
    eventRead = TRUE;
  }
  else
  {
    /* The buffer contains no elements. */
    *EventIdxPtr = Sd_GetSizeOfRxEvent();                                                                               /* SBSW_SD_VALID_API_POINTER */
  }

  return eventRead;
}

/**********************************************************************************************************************
 *  Sd_EventServer_RemoveFirst()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_RemoveFirst(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(Sd_GetRxEventStartIdxOfInstanceDyn(InstanceIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Remove the references of the saved client and the endpoints. */

  Sd_DecNrOfReferencesOfClientList(clientListIdx);                                                                      /* SBSW_SD_RXEVENT_MEMBER */

  if(Sd_GetNrOfReferencesOfClientList(clientListIdx) == 0u)
  {
    /* #100 The client is not referenced by another event. Remove it from the list. */
    Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                                /* SBSW_SD_RXEVENT_MEMBER */
  }

  /* #20 Remove the TCP endpoint. */
  if(Sd_EventServer_RemoveEndpoint(Sd_GetEndpointStorageTcpIdxOfClientList(clientListIdx)) == FALSE)
  {
    /* #200 Clear reference because the endpoint is not used by another instance. */
    Sd_SetEndpointStorageTcpIdxOfClientList(clientListIdx, Sd_GetSizeOfEndpointStorage());                              /* SBSW_SD_RXEVENT_MEMBER */
  }

  /* #30 Remove UDP endpoint. */
  if(Sd_EventServer_RemoveEndpoint(Sd_GetEndpointStorageUdpIdxOfClientList(clientListIdx)) == FALSE)
  {
    /* #300 Clear reference because the endpoint is not used by another instance. */
    Sd_SetEndpointStorageUdpIdxOfClientList(clientListIdx, Sd_GetSizeOfEndpointStorage());                              /* SBSW_SD_RXEVENT_MEMBER */
  }

  SD_BEGIN_CRITICAL_SECTION();

  /* #40 Remove the first element of the buffer. */
  Sd_IncRxEventStartIdxOfInstanceDyn(InstanceIdx);                                                                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #50 Handle wrap around. */
  if(Sd_GetRxEventStartIdxOfInstanceDyn(InstanceIdx) >= Sd_GetRxEventEndIdxOfInstance(InstanceIdx))
  {
    Sd_SetRxEventStartIdxOfInstanceDyn(InstanceIdx, Sd_GetRxEventStartIdxOfInstance(InstanceIdx));                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  /* #60 Check if the full flag has to be removed. */
  if(Sd_IsRxEventListFullOfInstanceDyn(InstanceIdx))
  {
    Sd_SetRxEventListFullOfInstanceDyn(InstanceIdx, FALSE);                                                             /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_EventServer_GetFollowingIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfRxEventType, SD_CODE) Sd_EventServer_GetFollowingIdx(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType RxEventIdx)
{
  Sd_SizeOfRxEventType nextRxEventIdx;

  /* #10 Increase queue index and observe wrap around */
  nextRxEventIdx = RxEventIdx + 1u;
  if(nextRxEventIdx == Sd_GetRxEventEndIdxOfInstance(InstanceIdx))
  {
    nextRxEventIdx = Sd_GetRxEventStartIdxOfInstance(InstanceIdx);
  }

  /* #20 Set to invalid value if there is no next element */
  if(nextRxEventIdx == Sd_GetRxEventEndIdxOfInstanceDyn(InstanceIdx))
  {
    nextRxEventIdx = Sd_GetSizeOfRxEvent();
  }

  return nextRxEventIdx;
}

/**********************************************************************************************************************
 *  Sd_RxServer_SaveEndpoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_RxServer_SaveEndpoint(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_SockAddrContainerType) InAddrPtr,
  Sd_EndpointType Type,
  SD_P2VAR(Sd_SizeOfEndpointStorageType) OutEndpointStorageIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  Sd_SizeOfEndpointStorageType endpointStorageIdx;
  boolean saveAddr = TRUE;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Set invalid endpoint index. Will be overwritten if endpoint could be saved. */
  *OutEndpointStorageIdxPtr = Sd_GetSizeOfEndpointStorage();                                                            /* SBSW_SD_VALID_API_POINTER */

  /* #20 Check if the address is already saved. */
  for(endpointStorageIdx = Sd_GetEndpointStorageStartIdxOfInstance(InstanceIdx);
    endpointStorageIdx < Sd_GetEndpointStorageEndIdxOfInstance(InstanceIdx);
    endpointStorageIdx++)
  {
    /* PRQA S 3415 3 */ /* MD_Sd_12.4_3415 */
    if((Sd_GetNrOfReferencesOfEndpointStorage(endpointStorageIdx) != 0u) &&
      (Sd_GetTypeOfEndpointStorage(endpointStorageIdx) == Type) &&
      (Sd_Util_SockAddrIsEqual(Sd_GetAddrAddrOfEndpointStorage(endpointStorageIdx), InAddrPtr) == TRUE))                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */
    {
      /* #2000 The address is already saved. Save index of address. */
      saveAddr = FALSE;
      retVal = E_OK;
      *OutEndpointStorageIdxPtr = endpointStorageIdx;                                                                   /* SBSW_SD_VALID_API_POINTER */
      break;
    }
  }

  if(saveAddr == TRUE)
  {
    /* #300 If the address has to be saved, search for the next free slot. */
    for(endpointStorageIdx = Sd_GetEndpointStorageStartIdxOfInstance(InstanceIdx);
      endpointStorageIdx < Sd_GetEndpointStorageEndIdxOfInstance(InstanceIdx);
      endpointStorageIdx++)
    {
      if(Sd_GetTypeOfEndpointStorage(endpointStorageIdx) == SD_ENDPOINT_TYPE_INVALID)
      {
        /* #3000 Save the address and type of the endpoint. */
        Sd_Util_CopySockAddr(Sd_GetAddrAddrOfEndpointStorage(endpointStorageIdx), InAddrPtr);                           /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */
        Sd_SetTypeOfEndpointStorage(endpointStorageIdx, Type);                                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        retVal = E_OK;
        *OutEndpointStorageIdxPtr = endpointStorageIdx;                                                                 /* SBSW_SD_VALID_API_POINTER */
        break;
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_EventServer_RemoveEndpoint()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_RemoveEndpoint(
  Sd_SizeOfEndpointStorageType EndpointStorageIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean stillReferenced = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the endpoint is valid. */
  if(EndpointStorageIdx < Sd_GetSizeOfEndpointStorage())
  {
    /* #100 Decrement number of references. */
    Sd_DecNrOfReferencesOfEndpointStorage(EndpointStorageIdx);                                                          /* SBSW_SD_CSL01 */

    /* #101 Remove endpoint if not used anymore. */
    if(Sd_GetNrOfReferencesOfEndpointStorage(EndpointStorageIdx) == 0u)
    {
      (Sd_GetAddrAddrOfEndpointStorage(EndpointStorageIdx))->family = SOAD_AF_INVALID;                                  /* SBSW_SD_CSL01 */
      Sd_SetTypeOfEndpointStorage(EndpointStorageIdx, SD_ENDPOINT_TYPE_INVALID);                                        /* SBSW_SD_CSL01 */
      stillReferenced = FALSE;
    }
  }

  return stillReferenced;
}

/**********************************************************************************************************************
 *  Sd_EventServer_Subscription()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_EventServer_Subscription(
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(eventHandlerIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(serverIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is already subscribed. */
  if(Sd_GetClientStateOfClientList(clientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_UNSUBSCRIBED)
  {
    /* #100 The client subscribed for the first time. */
    retVal = Sd_EventServer_SubscriptionInitial(RxEventIdx);
  }

  /* #20 Check if the configuration was successful. */
  if(retVal == E_OK)
  {
    /* #200 Subscription was successful.
     *      Update the client configuration. */
    Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrSubscribedUntilOfClientList(clientListIdx),
      Sd_GetRequestedTTLOfClientList(clientListIdx), Sd_GetInstanceIdxOfServer(serverIdx));                             /* SBSW_SD_REFERENCE_RXEVENT_MEMBER */

    /* #201 Send a SubscribeEventgroupAck message and update the state. */
    Sd_Util_AddEventGroupAckEntryToList(instanceIdx, RxEventIdx);

    if(Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_STATE_NOT_SUBSCRIBED)
    {
      /* #2010 Set the state of the event handler to requested and inform the BswM. */
      Sd_UtilServer_UpdateEventHandlerRequestState(eventHandlerIdx, SD_EVENT_HANDLER_REQUESTED);
      Sd_UtilServer_UpdateEventHandlerStateMachine(eventHandlerIdx, SD_EVENT_HANDLER_STATE_UNICAST_SUBSCRIPTION);
    }
  }
  else
  {
    Sd_SizeOfServerTimerType serverTimerIdx = Sd_GetSizeOfServerTimer();

    /* #202 Subscription was NOT successful. (Not able to configure all mandatory endpoints.) */

    if(Sd_GetEventOfRxEvent(RxEventIdx) == SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE_MULTI)
    {
      /* #2020 Add a random delay to the response message. */
      serverTimerIdx = Sd_GetServerTimerIdxOfEventHandler(eventHandlerIdx);
    }

    /* #203 Send a SubscribeEventgroupNegativeAcknowledge message. */
    Sd_Util_AddEventGroupNackEntryToList(instanceIdx, serverIdx,
      Sd_GetServiceIdOfServer(serverIdx),
      Sd_GetInstanceIdOfServer(serverIdx),
      Sd_GetMajorVersionOfServer(serverIdx),
      Sd_GetRxReservedOfClientList(clientListIdx),
      Sd_GetEventGroupIdOfEventHandler(eventHandlerIdx),
      Sd_GetAddressStorageIdxOfClientList(clientListIdx),
      serverTimerIdx);

    /* #204 Undo the configuration of the client and remove the client from the list. */
    Sd_UtilServer_RemoveClientFromList(eventHandlerIdx, clientListIdx);
  }
}

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitial()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitial(
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The event handler uses TCP. Update the configuration. */
  if(Sd_EventHandlerUsesTcp(eventHandlerIdx))
  {
    retVal = Sd_EventServer_SubscriptionInitialTcp(RxEventIdx);
  }

  /* #20 The event handler uses UDP. Update the configuration. */
  /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
  if(Sd_EventHandlerUsesUdp(eventHandlerIdx) && (retVal == E_OK))
  {
    retVal = Sd_EventServer_SubscriptionInitialUdp(RxEventIdx);
  }

  /* #30 Check if the event handler is configured for trigger transmit. */
  /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
  if((retVal == E_OK) && (Sd_EventServer_IsTriggerTransmitEnabled(RxEventIdx) == TRUE))
  {
    /* #300 The client subscribed the first time, save the request in the trigger transmit list. */
    (void)Sd_TriggerTransmit_Add(RxEventIdx);
  }

  if(retVal == E_OK)
  {
    /* #400 The client subscribed successfully. */
    Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_SUBSCRIBED);                             /* SBSW_SD_RXEVENT_MEMBER */
    Sd_IncNrOfReferencesOfClientList(clientListIdx);                                                                    /* SBSW_SD_RXEVENT_MEMBER */
    Sd_IncNrOfClientsOfEventHandlerDyn(eventHandlerIdx);                                                                /* SBSW_SD_RXEVENT_MEMBER */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_EventServer_IsTriggerTransmitEnabled()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
  */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_EventServer_IsTriggerTransmitEnabled(Sd_SizeOfRxEventType RxEventIdx)
{
  boolean retVal = FALSE;

  /* #10 Get Index of TCP and UDP EventHandler associated with this RxEvent. */
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfEventHandlerTcpType eventHandlerTcpIdx = Sd_GetEventHandlerTcpIdxOfEventHandler(eventHandlerIdx);
  Sd_SizeOfEventHandlerUdpType eventHandlerUdpIdx = Sd_GetEventHandlerUdpIdxOfEventHandler(eventHandlerIdx);

  /* #20 Check if TCP EventHandler is configured for triggered transmission. */
  if((eventHandlerTcpIdx != SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER) &&
    (Sd_GetRoutingGroupTriggerIdxOfEventHandlerTcp(eventHandlerTcpIdx) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP))
  {
    retVal = TRUE;
  }

  /* #30 Check if UDP EventHandler is configured for triggered transmission. */
  if((eventHandlerUdpIdx != SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER) &&
    (Sd_GetRoutingGroupTriggerIdxOfEventHandlerUdp(eventHandlerUdpIdx) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP))
  {
    retVal = TRUE;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitialTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitialTcp(
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(eventHandlerIdx);
  SoAd_SoConIdType assignedSoConId = SOAD_INV_SO_CON_ID;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client has already established a TCP connection. */
  /* PRQA S 0310 3 */ /* MD_Sd_11.4_0310 */
  retVal = SoAd_SetUniqueRemoteAddr(Sd_GetTcpSoConId(Sd_GetTcpSoConIdStartIdxOfServer(serverIdx)),
    (SD_P2VAR(SoAd_SockAddrType))Sd_GetAddrAddrOfEndpointStorage(Sd_GetEndpointStorageTcpIdxOfClientList(clientListIdx)),
    &assignedSoConId);                                                                                                  /* SBSW_SD_REFERENCE_RXEVENT_MEMBER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */

  if(retVal == E_OK)
  {
    /* #100 Check if the socket connection is online. */
    if(SD_SOCON_MODE_ONLINE == Sd_Util_GetTcpSoConMode(assignedSoConId))
    {
      Sd_SizeOfEventHandlerTcpType eventHandlerTcpIdx = Sd_GetEventHandlerTcpIdxOfEventHandler(eventHandlerIdx);

      /* #1000 The client TCP IP address is already configured, enable the TCP routing group. */
      retVal = Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerTcp(eventHandlerTcpIdx),
        assignedSoConId);
      Sd_UtilServer_IncreaseActivationCount(eventHandlerIdx, assignedSoConId);

      /* #1001 Save the state of the client. */
      Sd_SetAssignedTcpSoConIdOfClientList(clientListIdx, assignedSoConId);                                             /* SBSW_SD_RXEVENT_MEMBER */
    }
  }

  /* #20 Check if the subscription was successful. */
  if(Sd_GetAssignedTcpSoConIdOfClientList(clientListIdx) == SOAD_INV_SO_CON_ID)
  {
    /* #200 Reject the subscription. */
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_EventServer_SubscriptionInitialUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_EventServer_SubscriptionInitialUdp(
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);
  Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(eventHandlerIdx);
  SoAd_SoConIdType assignedSoConId = SOAD_INV_SO_CON_ID;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Configure a socket connection with the client endpoint address. */
  /* PRQA S 0310 4 */ /* MD_Sd_11.4_0310 */
  retVal = SoAd_SetUniqueRemoteAddr(
    Sd_GetIdOfUdpSoCon(Sd_GetUdpSoConStartIdxOfServer(serverIdx)),
    (SD_P2VAR(SoAd_SockAddrType))Sd_GetAddrAddrOfEndpointStorage(Sd_GetEndpointStorageUdpIdxOfClientList(clientListIdx)),
    &assignedSoConId);                                                                                                  /* SBSW_SD_REFERENCE_RXEVENT_MEMBER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */

  if(retVal == E_OK)
  {
    Sd_SizeOfEventHandlerUdpType eventHandlerUdpIdx = Sd_GetEventHandlerUdpIdxOfEventHandler(eventHandlerIdx);

    /* #100 Each event handler which requires the socket connection opens it in order to indicate the dependency. */
    retVal = SoAd_OpenSoCon(assignedSoConId);

    /* #101 Enable the unicast routing if the event handler is not in the multicast subscription state. */
    if((Sd_GetStateMachineOfEventHandlerDyn(eventHandlerIdx) != SD_EVENT_HANDLER_STATE_MULTICAST_SUBSCRIPTION) &&
      (Sd_GetMulticastThresholdOfEventHandler(eventHandlerIdx) != 1u))
    {
      retVal |= Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(eventHandlerUdpIdx),
        assignedSoConId);
      Sd_UtilServer_IncreaseActivationCount(eventHandlerIdx, assignedSoConId);
    }

    Sd_SetAssignedUdpSoConIdOfClientList(clientListIdx, assignedSoConId);                                               /* SBSW_SD_RXEVENT_MEMBER */
  }

  /* #20 Check if we were able to add the client to the system. */
  if(Sd_GetAssignedUdpSoConIdOfClientList(clientListIdx) == SOAD_INV_SO_CON_ID)
  {
    /* #200 The client address could not be configured, reject the subscription. */
    Sd_Util_ReportDemEvent(Sd_GetEOutOfResIdOfInstance(Sd_GetInstanceIdxOfServer(serverIdx)));
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_RxServer_AddClientToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfClientListType, SD_CODE) Sd_RxServer_AddClientToList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;
  boolean foundFreeSlot = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search for the next free slot in client list. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    if(Sd_GetClientStateOfClientList(clientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_INVALID)
    {
      /* #20 Save client information. */
      foundFreeSlot = TRUE;
      Sd_SetAddressStorageIdxOfClientList(clientListIdx, AddressStorageIdx);                                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetAssignedTcpSoConIdOfClientList(clientListIdx, SOAD_INV_SO_CON_ID);                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetAssignedUdpSoConIdOfClientList(clientListIdx, SOAD_INV_SO_CON_ID);                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_UNSUBSCRIBED);                         /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetNrOfReferencesOfClientList(clientListIdx, 0u);                                                              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetRequestedTTLOfClientList(clientListIdx, 0u);                                                                /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetRxReservedOfClientList(clientListIdx, 0u);                                                                  /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetEndpointStorageTcpIdxOfClientList(clientListIdx, Sd_GetSizeOfEndpointStorage());                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetEndpointStorageUdpIdxOfClientList(clientListIdx, Sd_GetSizeOfEndpointStorage());                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_Util_ResetTimerToZero(Sd_GetAddrSubscribedUntilOfClientList(clientListIdx));                                   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */
      break;
    }
  }

  if(foundFreeSlot == FALSE)
  {
    /* #30 No free slot found. Return invalid ClientList index. */
    /* The amount of manageable clients corresponds to the amount of configured socket connections for this event handler. */
    clientListIdx = Sd_GetSizeOfClientList();
#if(SD_DEV_ERROR_REPORT == STD_ON)
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_ADD_CLIENT_TO_LIST, SD_E_CLIENT_LIST_FULL);
#endif /* SD_DEV_ERROR_REPORT == STD_ON */
  }

  return clientListIdx;
}

/**********************************************************************************************************************
 *  Sd_UtilServer_SetDown()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_SetDown(Sd_SizeOfServerType ServerIdx)
{
  if(Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_AVAILABLE)
  {
    /* #10 Set the state of all associated event handlers. */
    Sd_UtilServer_ReleaseEventHandlers(ServerIdx);

    /* #20 Close all TCP socket connections of the server. */
    Sd_UtilServer_CloseTcpAndPreconfiguredSoCons(ServerIdx, FALSE);

    /* #30 Disable the routing for provided methods. */
    Sd_UtilServer_DisableMethodRouting(ServerIdx);

    /* #40 Update the state. */
    Sd_SetStateSwcOfServerDyn(ServerIdx, SD_SERVER_SERVICE_DOWN);                                                   /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                               /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfServer(ServerIdx));
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_SetAvailable()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_SetAvailable(Sd_SizeOfServerType ServerIdx)
{
  /* #10 Only set to available if server state is down. */
  if(Sd_GetStateSwcOfServerDyn(ServerIdx) == SD_SERVER_SERVICE_DOWN)
  {
    /* #20 Update the state. */
    Sd_SetStateSwcOfServerDyn(ServerIdx, SD_SERVER_SERVICE_AVAILABLE);                                              /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_SetStateMachineExecutionRequestedOfServerDyn(ServerIdx, TRUE);                                               /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfServer(ServerIdx));
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_RemoveClientsFromEventHandler()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_RemoveClientsFromEventHandler(
  Sd_SizeOfEventHandlerType EventHandlerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all clients of the event handler. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    /* #100 Check if the client is in a valid state. */
    if(Sd_GetClientStateOfClientList(clientListIdx) != SD_EVENT_HANDLER_CLIENT_STATE_INVALID)
    {
      /* #1000 Remove the client from the list. */
      Sd_UtilServer_RemoveClientFromList(EventHandlerIdx, clientListIdx);
    }
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_RemoveClientFromList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_RemoveClientFromList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Undo the configuration of the client communication paths. */
  Sd_UtilServer_UnconfigureClientComPaths(EventHandlerIdx, ClientListIdx);

  /* #20 Check if this client is subscribed for the event handler. */
  if(Sd_GetClientStateOfClientList(ClientListIdx) == SD_EVENT_HANDLER_CLIENT_STATE_SUBSCRIBED)
  {
    /* #200 Decrement the amount of subscribed clients. */
    if(Sd_GetNrOfClientsOfEventHandlerDyn(EventHandlerIdx) != 0u)
    {
      Sd_DecNrOfClientsOfEventHandlerDyn(EventHandlerIdx);                                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    /* #201 Check if the client is referenced from a pending event. */
    if(Sd_GetNrOfReferencesOfClientList(ClientListIdx) != 0u)
    {
      /* #2010 Decrement the reference counter. */
      Sd_DecNrOfReferencesOfClientList(ClientListIdx);                                                                  /* SBSW_SD_API_ARGUMENT_IDX */
    }
  }

  /* #30 Check if the client is still referenced by other events. */
  if(Sd_GetNrOfReferencesOfClientList(ClientListIdx) == 0u)
  {
    /* #300 If the client is not referenced by another event. Remove it from the list. */
    Sd_SetClientStateOfClientList(ClientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                                /* SBSW_SD_API_ARGUMENT_IDX */
  }
  else
  {
    /* #301 Otherwise, if the client is referenced, keep the information in the list. */
    Sd_SetClientStateOfClientList(ClientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_UNSUBSCRIBED);                           /* SBSW_SD_API_ARGUMENT_IDX */
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_UnconfigureClientComPaths()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_UnconfigureClientComPaths(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SoConIdType assignedUdpSoConId, assignedTcpSoConId;

  /* ----- Implementation ----------------------------------------------- */
  assignedTcpSoConId = Sd_GetAssignedTcpSoConIdOfClientList(ClientListIdx);
  assignedUdpSoConId = Sd_GetAssignedUdpSoConIdOfClientList(ClientListIdx);

  /* #10 Check if the client is configured for TCP. */
  if(assignedTcpSoConId != SOAD_INV_SO_CON_ID)
  {
    /* #100 Decrement the activation counter. */
    if(Sd_UtilServer_DecreaseActivationCount(EventHandlerIdx, assignedTcpSoConId) == TRUE)
    {
      /* #1000 Deactivate the routing group if no other instance of the client is active. */
      (void)Sd_Util_DisableSpecificRouting(
        (Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerTcp(Sd_GetEventHandlerTcpIdxOfEventHandler(EventHandlerIdx)),
        assignedTcpSoConId);
    }

    Sd_SetAssignedTcpSoConIdOfClientList(ClientListIdx, SOAD_INV_SO_CON_ID);                                            /* SBSW_SD_API_ARGUMENT_IDX */
  }

  /* #20 Check if the client is configured for UDP. */
  if(assignedUdpSoConId != SOAD_INV_SO_CON_ID)
  {
    /* #200 Decrement the activation counter. */
    if(Sd_UtilServer_DecreaseActivationCount(EventHandlerIdx, assignedUdpSoConId) == TRUE)
    {
      /* #2000 Deactivate the routing group if no other instance of the client is active. */
      (void)Sd_Util_DisableSpecificRouting(
        (Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(Sd_GetEventHandlerUdpIdxOfEventHandler(EventHandlerIdx)),
        assignedUdpSoConId);
    }

    /* #201 Close the socket connection. (The OpenCount is handled by SoAd). */
    (void)SoAd_CloseSoCon(assignedUdpSoConId, FALSE);
    Sd_SetAssignedUdpSoConIdOfClientList(ClientListIdx, SOAD_INV_SO_CON_ID);                                            /* SBSW_SD_API_ARGUMENT_IDX */
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_ReleaseEventHandlers()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_ReleaseEventHandlers(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerType eventHandlerIdx;
  Sd_SizeOfEventHandlerMulticastType eventHandlerMulticastIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the state of all associated event handlers. */
  for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(ServerIdx);
    eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(ServerIdx);
    eventHandlerIdx++)
  {
    /* #100 Inform BswM if event handler was requested. */
    if(Sd_GetRequestStateOfEventHandlerDyn(eventHandlerIdx) == SD_EVENT_HANDLER_REQUESTED)
    {
      Sd_UtilServer_UpdateEventHandlerRequestState(eventHandlerIdx, SD_EVENT_HANDLER_RELEASED);
    }

    /* #101 Remove all clients from the event handler. */
    Sd_UtilServer_RemoveClientsFromEventHandler(eventHandlerIdx);

    /* #102 Disable all referenced routing groups and reset the socket connections. */
    eventHandlerMulticastIdx = Sd_GetEventHandlerMulticastIdxOfEventHandler(eventHandlerIdx);
    if(eventHandlerMulticastIdx != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)
    {
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(eventHandlerMulticastIdx));
      (void)SoAd_CloseSoCon(Sd_GetSoConIdOfEventHandlerMulticast(eventHandlerMulticastIdx), FALSE);
    }

    /* #103 Disable routing of UDP and TCP routing groups and reset activation count. */
    Sd_UtilServer_DisableRouting(eventHandlerIdx);
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_CloseTcpAndPreconfiguredSoCons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_CloseTcpAndPreconfiguredSoCons(
  Sd_SizeOfServerType ServerIdx,
  boolean Abort)
{
  /* ----- Local Variables ------------------------------F---------------- */
  Sd_TcpSoConIdIterType tcpSoConIdIdx;
  Sd_UdpSoConIterType udpSoConIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Close all TCP socket connections of the server. */
  for(tcpSoConIdIdx = Sd_GetTcpSoConIdStartIdxOfServer(ServerIdx);
    tcpSoConIdIdx < Sd_GetTcpSoConIdEndIdxOfServer(ServerIdx);
    tcpSoConIdIdx++)
  {
    (void)SoAd_CloseSoCon(Sd_GetTcpSoConId(tcpSoConIdIdx), Abort);
  }

  /* #20 Close all UDP socket connections with preconfigured remote address. */
  for(udpSoConIdx = Sd_GetUdpSoConStartIdxOfServer(ServerIdx);
    udpSoConIdx < Sd_GetUdpSoConEndIdxOfServer(ServerIdx);
    udpSoConIdx++)
  {
    if(Sd_IsPreconfiguredOfUdpSoCon(udpSoConIdx) == TRUE)
    {
      (void)SoAd_CloseSoCon(Sd_GetIdOfUdpSoCon(udpSoConIdx), Abort);
    }
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_DisableMethodRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_DisableMethodRouting(
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the server provides methods. */
  if(Sd_GetMethodIdxOfServer(ServerIdx) != SD_NO_METHODIDXOFSERVER)
  {
    /* #100 Disable the routing group for the server methods. */
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(Sd_GetMethodIdxOfServer(ServerIdx)));
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_LocalIpAddrAssignmentChgReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_LocalIpAddrAssignmentChgReset(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfServerType serverIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset state of all server services. */
  for(serverIdx = Sd_GetServerStartIdxOfInstance(InstanceIdx);
    serverIdx < Sd_GetServerEndIdxOfInstance(InstanceIdx);
    serverIdx++)
  {
    Sd_SizeOfEventHandlerType eventHandlerIdx;

    /* #100 Reset state of all dependent event handler. */
    for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(serverIdx);
      eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(serverIdx);
      eventHandlerIdx++)
    {
      Sd_SizeOfClientListType clientListIdx;

      /* #1000 Reset dynamic variables. */
      Sd_UtilServer_UpdateEventHandlerStateMachine(eventHandlerIdx, SD_EVENT_HANDLER_STATE_NONE);
      Sd_SetNrOfClientsOfEventHandlerDyn(eventHandlerIdx, 0u);                                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

      /* #1001 Reset all clients. */
      for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(eventHandlerIdx);
        clientListIdx < Sd_GetClientListEndIdxOfEventHandler(eventHandlerIdx);
        clientListIdx++)
      {
        Sd_SetClientStateOfClientList(clientListIdx, SD_EVENT_HANDLER_CLIENT_STATE_INVALID);                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }

      /* #1002 Inform the BswM about the state of all event handlers. */
      Sd_UtilServer_UpdateEventHandlerRequestState(eventHandlerIdx, SD_EVENT_HANDLER_RELEASED);
    }

    /* #101 Reset the dynamic variables. */
    Sd_SetInitialOfferRepetitionRunOfServerDyn(serverIdx, 0u);                                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfServerDyn(serverIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_GetSoConActivationMapIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_SizeOfSoConActivationMapType, SD_CODE) Sd_UtilServer_GetSoConActivationMapIdx(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSoConActivationMapType iterIdx;
  Sd_SizeOfSoConActivationMapType soConActivationMapIdx = Sd_GetSizeOfSoConActivationMap();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the socket connection is already saved in the map. */
  for(iterIdx = Sd_GetSoConActivationMapStartIdxOfEventHandler(EventHandlerIdx);
    iterIdx < Sd_GetSoConActivationMapEndIdxOfEventHandler(EventHandlerIdx);
    iterIdx++)
  {
    if(Sd_GetSoConIdOfSoConActivationMap(iterIdx) == SoConId)
    {
      soConActivationMapIdx = iterIdx;
      break;
    }
  }

  /* #20 Requested socket connection was not saved. */
  if(soConActivationMapIdx == Sd_GetSizeOfSoConActivationMap())
  {
    /* #200 Search for an unused slot to save the socket connection. */
    for(iterIdx = Sd_GetSoConActivationMapStartIdxOfEventHandler(EventHandlerIdx);
      iterIdx < Sd_GetSoConActivationMapEndIdxOfEventHandler(EventHandlerIdx);
      iterIdx++)
    {
      /* Check if the entry is unused. */
      if(Sd_GetSoConIdOfSoConActivationMap(iterIdx) == SOAD_INV_SO_CON_ID)
      {
        /* #2000 Save the new socket connection. */
        Sd_SetSoConIdOfSoConActivationMap(iterIdx, SoConId);                                                            /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetNrOfActivationsOfSoConActivationMap(iterIdx, 0u);                                                         /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        soConActivationMapIdx = iterIdx;
        break;
      }
    }
  }

  return soConActivationMapIdx;
}

/**********************************************************************************************************************
 *  Sd_UtilServer_IncreaseActivationCount()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_IncreaseActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSoConActivationMapType soConActivationMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the activation map entry of the SoConId. */
  soConActivationMapIdx = Sd_UtilServer_GetSoConActivationMapIdx(EventHandlerIdx, SoConId);

  if(soConActivationMapIdx < Sd_GetSizeOfSoConActivationMap())
  {
    /* #100 Increase the activation count. */
    Sd_IncNrOfActivationsOfSoConActivationMap(soConActivationMapIdx);                                                   /* SBSW_SD_CSL01 */
  }
}

/**********************************************************************************************************************
 *  Sd_UtilServer_DecreaseActivationCount()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_UtilServer_DecreaseActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSoConActivationMapType soConActivationMapIdx;
  boolean activationCountIsZero = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the activation map entry of the SoConId. */
  soConActivationMapIdx = Sd_UtilServer_GetSoConActivationMapIdx(EventHandlerIdx, SoConId);

  if(soConActivationMapIdx < Sd_GetSizeOfSoConActivationMap())
  {
    if(Sd_GetNrOfActivationsOfSoConActivationMap(soConActivationMapIdx) != 0u)
    {
      /* #100 Decrease the activation count. */
      Sd_DecNrOfActivationsOfSoConActivationMap(soConActivationMapIdx);                                                 /* SBSW_SD_CSL01 */

      /* #101 Check if the activation count was decreased to zero. */
      if(Sd_GetNrOfActivationsOfSoConActivationMap(soConActivationMapIdx) == 0u)
      {
        activationCountIsZero = TRUE;
      }
    }
  }

  return activationCountIsZero;
}

/**********************************************************************************************************************
 *  Sd_UtilServer_ResetActivationCount()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilServer_ResetActivationCount(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSoConActivationMapType soConActivationMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the activation map entry of the SoConId. */
  soConActivationMapIdx = Sd_UtilServer_GetSoConActivationMapIdx(EventHandlerIdx, SoConId);

  if(soConActivationMapIdx < Sd_GetSizeOfSoConActivationMap())
  {
    /* #100 Reset the activation count. */
    Sd_SetNrOfActivationsOfSoConActivationMap(soConActivationMapIdx, 0u);                                               /* SBSW_SD_CSL01 */
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_FindClientInList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_SizeOfClientListType, SD_CODE) Sd_RxServer_FindClientInList(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr,
  boolean CreateNewClientIfNotFound)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientListType clientListIdx;
  boolean matchingClient = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is part of the list. */
  for(clientListIdx = Sd_GetClientListStartIdxOfEventHandler(EventHandlerIdx);
    clientListIdx < Sd_GetClientListEndIdxOfEventHandler(EventHandlerIdx);
    clientListIdx++)
  {
    if((Sd_GetClientStateOfClientList(clientListIdx) != SD_EVENT_HANDLER_CLIENT_STATE_INVALID) &&
      (Sd_GetAddressStorageIdxOfClientList(clientListIdx) == RxMessageInfoPtr->AddressStorageIdx))
    {
      /* #100 Found the corresponding remote address. Check if a remote reboot was detected. */
      if(RxMessageInfoPtr->RebootDetected == TRUE)
      {
        /* #1000 Client has rebooted.
         *       Set the SubscribedUntil time to 0 in order to remove the client in the next main function cycle. */
        Sd_SetStateMachineExecutionRequestedOfServerDyn(Sd_GetServerIdxOfEventHandler(EventHandlerIdx), TRUE);          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
        Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrSubscribedUntilOfClientList(clientListIdx),
          Sd_GetInstanceIdxOfServer(Sd_GetServerIdxOfEventHandler(EventHandlerIdx)));                                   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */
      }
      else
      {
        /* #1001 No reboot detected. Check if the attached endpoints have changed. */
        matchingClient = Sd_RxServer_CheckAttachedEndpointOptions(EventHandlerIdx, clientListIdx, AttachedOptionsPtr);  /* SBSW_SD_PASSED_API_POINTER_NOT_NULL */

        if(matchingClient == TRUE)
        {
          /* Client matches the attached endpoint options. */
          break;
        }
      }
    }
  }

  if((matchingClient == TRUE) || (CreateNewClientIfNotFound == FALSE))
  {
    /* #200 Matching client was found, or new client shall not be created. */
  }
  else
  {
    /* #201 The client was not found and is not subscribed. Add the client to the list. */
    clientListIdx = Sd_RxServer_AddClientToList(EventHandlerIdx, RxMessageInfoPtr->AddressStorageIdx);
  }

  return clientListIdx;
}

/**********************************************************************************************************************
 *  Sd_RxServer_CheckAttachedEndpointOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_RxServer_CheckAttachedEndpointOptions(
  Sd_SizeOfEventHandlerType EventHandlerIdx,
  Sd_SizeOfClientListType ClientListIdx,
  SD_P2CONST(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean tcpMatch, udpMatch;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the event handler uses TCP. */
  if(Sd_EventHandlerUsesTcp(EventHandlerIdx))
  {
    /* #100 Check the attached TCP endpoint. */
    tcpMatch = Sd_RxServer_CheckAttachedEndpointOption(Sd_GetAssignedTcpSoConIdOfClientList(ClientListIdx),
      Sd_GetEndpointStorageTcpIdxOfClientList(ClientListIdx), &AttachedOptionsPtr->EndpointAddrTcp);                    /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
  }
  else
  {
    /* #101 Ignore TCP endpoint if event handler is not configured for TCP. */
    tcpMatch = TRUE;
  }

  /* #20 Check if the event handler uses UDP. */
  if(Sd_EventHandlerUsesUdp(EventHandlerIdx))
  {
    /* #200 Check the attached UDP endpoint. */
    udpMatch = Sd_RxServer_CheckAttachedEndpointOption(Sd_GetAssignedUdpSoConIdOfClientList(ClientListIdx),
      Sd_GetEndpointStorageUdpIdxOfClientList(ClientListIdx), &AttachedOptionsPtr->EndpointAddrUdp);                    /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
  }
  else
  {
    /* #201 Ignore UDP endpoint if event handler is not configured for UDP. */
    udpMatch = TRUE;
  }

  return (boolean)((tcpMatch == TRUE) && (udpMatch == TRUE));
}

/**********************************************************************************************************************
 *  Sd_RxServer_CheckAttachedEndpointOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_RxServer_CheckAttachedEndpointOption(
  SoAd_SoConIdType SoConId,
  Sd_SizeOfEndpointStorageType EndpointStorageIdx,
  SD_P2CONST(Sd_SockAddrContainerType) EndpointPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  boolean endpointMatch;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is already configured with a valid socket connection. */
  if(SoConId != SOAD_INV_SO_CON_ID)
  {
    Sd_SockAddrContainerType remoteAddr;

    /* #100 Check the configured remote address against the endpoint information. */
    endpointMatch = FALSE;

    retVal = Sd_SoAd_GetRemoteAddr(SoConId, &remoteAddr);                                                               /* SBSW_SD_REFERENCE_OF_VARIABLE */

    if(retVal == E_OK)
    {
      if(TRUE == Sd_Util_SockAddrIsEqual(&remoteAddr, EndpointPtr))                                                     /* SBSW_SD_REFERENCE_OF_VARIABLE */
      {
        endpointMatch = TRUE;
      }
    }
  }
  else
  {
    /* #101 The client is not (yet) configured, but has a temporary endpoint. Check it. */
    endpointMatch = FALSE;

    if(TRUE == Sd_Util_SockAddrIsEqual(
      Sd_GetAddrAddrOfEndpointStorage(EndpointStorageIdx), EndpointPtr))                                                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT */
    {
      endpointMatch = TRUE;
    }
  }

  return endpointMatch;
}

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Process()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_Process(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfTriggerTransmitType triggerTransmitIdx = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read all pending trigger transmit requests. */
  while(TRUE == Sd_TriggerTransmit_ReadFirst(&triggerTransmitIdx))                                                      /* SBSW_SD_REFERENCE_OF_VARIABLE */
  {
    /* #100 Check if the transmit shall be triggered now or during the next main function execution. */
    if(Sd_GetStateOfTriggerTransmit(triggerTransmitIdx) == SD_TRIGGER_TRANSMIT_STATE_NOW)
    {
      /* #1000 Trigger transmission of initial events. */
      Sd_TriggerTransmit_Trigger(triggerTransmitIdx);

      /* #1001 Remove the trigger transmit request. */
      Sd_TriggerTransmit_RemoveFirst();
    }
    else  /* SD_TRIGGER_TRANSMIT_STATE_NOW != Sd_GetStateOfTriggerTransmit(triggerTransmitIdx) */
    {
      /* #1002 Postpone the transmission to the next main function execution. */
      Sd_SetStateOfTriggerTransmit(triggerTransmitIdx, SD_TRIGGER_TRANSMIT_STATE_NOW);                                  /* SBSW_SD_TRIGGER_TRANSMIT_IDX */
      break;
    }
  }
}

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Trigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_Trigger(
  Sd_SizeOfTriggerTransmitType TriggerTransmitIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfTriggerTransmit(TriggerTransmitIdx);
  Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfTriggerTransmit(TriggerTransmitIdx);
  SoAd_SoConIdType soConId;

  /* ----- Implementation ----------------------------------------------- */
  soConId = Sd_GetAssignedTcpSoConIdOfClientList(clientListIdx);

  /* #10 Check if the event handler is configured for TCP. */
  if(soConId != SOAD_INV_SO_CON_ID)
  {
    /* #100 Check if the trigger transmission is configured for TCP. */
    if(Sd_GetRoutingGroupTriggerIdxOfEventHandlerTcp(Sd_GetEventHandlerTcpIdxOfEventHandler(eventHandlerIdx)) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP)
    {
      /* #1000 Trigger the initial transmission for TCP. */
      (void)SoAd_IfSpecificRoutingGroupTransmit(Sd_GetRoutingGroup(Sd_GetRoutingGroupTriggerIdxOfEventHandlerTcp(Sd_GetEventHandlerTcpIdxOfEventHandler(eventHandlerIdx))), soConId);
    }
  }

  soConId = Sd_GetAssignedUdpSoConIdOfClientList(clientListIdx);

  /* #20 Check if the event handler is configured for UDP. */
  if(soConId != SOAD_INV_SO_CON_ID)
  {
    /* #200 Check if the trigger transmission is configured for UDP. */
    if(Sd_GetRoutingGroupTriggerIdxOfEventHandlerUdp(Sd_GetEventHandlerUdpIdxOfEventHandler(eventHandlerIdx)) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP)
    {
      /* #2000 Trigger the initial transmission for UDP. */
      (void)SoAd_IfSpecificRoutingGroupTransmit(Sd_GetRoutingGroup(Sd_GetRoutingGroupTriggerIdxOfEventHandlerUdp(Sd_GetEventHandlerUdpIdxOfEventHandler(eventHandlerIdx))), soConId);
    }
  }
}

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_Add()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_TriggerTransmit_Add(
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType requestSaved = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ring buffer is full. */
  if(!Sd_IsTriggerTransmitFull())
  {
    /* #100 Save the requested trigger transmit. */
    Sd_SetClientListIdxOfTriggerTransmit(                                                                               /* SBSW_SD_TRIGGER_TRANSMIT_IDX */
      Sd_GetTriggerTransmitEndIdx(), Sd_GetClientListIdxOfRxEvent(RxEventIdx));
    Sd_SetEventHandlerIdxOfTriggerTransmit(                                                                             /* SBSW_SD_TRIGGER_TRANSMIT_IDX */
      Sd_GetTriggerTransmitEndIdx(), Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx));
    Sd_SetStateOfTriggerTransmit(                                                                                       /* SBSW_SD_TRIGGER_TRANSMIT_IDX */
      Sd_GetTriggerTransmitEndIdx(), SD_TRIGGER_TRANSMIT_STATE_NEXT_CYCLE);

    Sd_IncTriggerTransmitEndIdx();                                                                                      /* SBSW_SD_CSL_VAR_ELEM */
    requestSaved = E_OK;

    /* #101 Handle wrap around. */
    if(Sd_GetTriggerTransmitEndIdx() >= Sd_GetSizeOfTriggerTransmit())
    {
      Sd_SetTriggerTransmitEndIdx(0u);                                                                                  /* SBSW_SD_CSL_VAR_ELEM */
    }

    /* #102 Check if the ring buffer is full. */
    if(Sd_GetTriggerTransmitEndIdx() == Sd_GetTriggerTransmitStartIdx())
    {
      Sd_SetTriggerTransmitFull(TRUE);                                                                                  /* SBSW_SD_CSL_VAR_ELEM */
    }
  }
  else
  {
    /* #103 The ring buffer is full. Not able to save the event. */
  }

  return requestSaved;
}

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_ReadFirst()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_TriggerTransmit_ReadFirst(
  SD_P2VAR(Sd_SizeOfTriggerTransmitType) TriggerTransmitIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean eventRead = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the ring buffer contains an element. */
  if((Sd_GetTriggerTransmitStartIdx() != Sd_GetTriggerTransmitEndIdx()) ||
    Sd_IsTriggerTransmitFull())
  {
    /* #100 Read the first element from of the buffer. */
    *TriggerTransmitIdxPtr =  Sd_GetTriggerTransmitStartIdx();                                                          /* SBSW_SD_VALID_API_POINTER */
    eventRead = TRUE;
  }
  else
  {
    /* #101 The buffer contains no elements. */
  }

  return eventRead;
}

/**********************************************************************************************************************
 *  Sd_TriggerTransmit_RemoveFirst()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_TriggerTransmit_RemoveFirst(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 The ring buffer will always contain at least one element. */

  Sd_SetStateOfTriggerTransmit(                                                                                         /* SBSW_SD_TRIGGER_TRANSMIT_IDX */
    Sd_GetTriggerTransmitStartIdx(), SD_TRIGGER_TRANSMIT_STATE_INVALID);

  /* #20 Remove the first element of the buffer. */
  Sd_IncTriggerTransmitStartIdx();                                                                                      /* SBSW_SD_CSL_VAR_ELEM */

  /* #30 Handle wrap around. */
  if(Sd_GetTriggerTransmitStartIdx() >= Sd_GetSizeOfTriggerTransmit())
  {
    Sd_SetTriggerTransmitStartIdx(0u);                                                                                  /* SBSW_SD_CSL_VAR_ELEM */
  }

  /* #40 Check if the full flag has to be removed. */
  if(Sd_IsTriggerTransmitFull())
  {
    Sd_SetTriggerTransmitFull(FALSE);                                                                                   /* SBSW_SD_CSL_VAR_ELEM */
  }
}

/**********************************************************************************************************************
 *  CLIENT FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeClients()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeClients(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all clients to update and process the state machine. */
  for(clientIdx = Sd_GetClientStartIdxOfInstance(InstanceIdx);
    clientIdx < Sd_GetClientEndIdxOfInstance(InstanceIdx);
    clientIdx++)
  {
    /* #100 Reinitialize all consumed eventgroups of the client. */
    Sd_Init_ReInitializeConsumedEventgroups(clientIdx);

    /* #101 Mark all clients for state machine execution. */
    Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    /* #102 Disable routing for method socket connection. */
    if(Sd_GetMethodIdxOfClient(clientIdx) != SD_NO_METHODIDXOFCLIENT)
    {
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(Sd_GetMethodIdxOfClient(clientIdx)));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Init_ReInitializeConsumedEventgroups()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Init_ReInitializeConsumedEventgroups(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all eventgroups of the client, disable the routing and close multicast socket connections. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    /* #100 Check if the consumed eventgroup is configured for multicast. */
    if(Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(consumedEventgroupIdx) != SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP)
    {
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(consumedEventgroupIdx));

      /* #1000 Close all multicast socket connections of the client. */
      Sd_UtilClient_CloseAllMulticastSoCons(consumedEventgroupIdx, TRUE);
    }

    /* #101 Check if the consumed eventgroup is configured for TCP. */
    if(Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(consumedEventgroupIdx) != SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP)
    {
      /* #1010 Disable TCP routing. */
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(consumedEventgroupIdx));
    }

    /* #102 Check if the consumed eventgroup is configured for UDP. */
    if(Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(consumedEventgroupIdx) != SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP)
    {
      /* #1020 Disable UDP routing. */
      (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(consumedEventgroupIdx));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_Process()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_Process(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */

  /* Copy received event to client. */
  SD_BEGIN_CRITICAL_SECTION();
  Sd_SetEventMainOfClientDyn(ClientIdx, Sd_GetEventRxOfClientDyn(ClientIdx));                                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetEventRxOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  SD_END_CRITICAL_SECTION();

  /* #10 Execute client state machine. */
  Sd_StateClient_ProcessStateMachine(ClientIdx);

  /* #20 Run the state machine for consumed eventgroups of the client instance. */
  Sd_StateClient_ProcessCeg(ClientIdx);

  /* #30 Check if a reboot was detected. */
  Sd_StateClient_HandleReboot(ClientIdx);

  /* #40 Check if the client is still requested. */
  Sd_StateClient_HandleRequestState(ClientIdx);

  /* #50 Handle the retry subscription functionality. */
  Sd_StateClient_HandleRetrySubscription(ClientIdx);

  /* #60 Update the time for the next state machine run. */
  if(!Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfClientDyn(ClientIdx)))
  {
    Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetTimerTTLOfClientDyn(ClientIdx));
  }

  Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetTimeToTriggerSendOfClientDyn(ClientIdx));
} /* PRQA S 6050 */ /* MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessStateMachine()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessStateMachine(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute client state machine. */
  switch(Sd_GetStateMachineOfClientDyn(ClientIdx))
  {
    case SD_CLIENT_STATE_NONE:
      /* #100 Initial run of the state machine. */
      Sd_StateClient_ProcessInitial(ClientIdx);
      break;

    case SD_CLIENT_STATE_NOT_REQUESTED_NOT_SEEN:
      /* 101 Not requested, not seen state machine. */
      Sd_StateClient_ProcessNotRequestedNotSeen(ClientIdx);
      break;

    case SD_CLIENT_STATE_NOT_REQUESTED_SEEN:
      /* 102 Not requested, seen state machine. */
      Sd_StateClient_ProcessNotRequestedSeen(ClientIdx);
      break;

    case SD_CLIENT_STATE_REQUESTED_BUT_NOT_READY:
      /* #103 Not ready state machine. */
      Sd_StateClient_ProcessRequestedNotReady(ClientIdx);
      break;

    case SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT:
      /* #104 Searching initial wait state machine. */
      Sd_StateClient_ProcessSearchingInitial(ClientIdx);
      break;

    case SD_CLIENT_STATE_SEARCHING_REPETITION:
      /* #105 Searching repetition state machine. */
      Sd_StateClient_ProcessSearchingRepetition(ClientIdx);
      break;

    case SD_CLIENT_STATE_SERVICE_READY:
      /* #106 Ready state machine. */
      Sd_StateClient_ProcessReady(ClientIdx);
      break;

    case SD_CLIENT_STATE_STOPPED:
      /* #107 Stopped state machine. */
      Sd_StateClient_ProcessStopped(ClientIdx);
      break;

    default: /* COV_SD_MISRA */
      /* #108 Undefined state. */
      break;
  }
} /* PRQA S 6050 */ /* MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  Sd_StateClient_HandleReboot()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleReboot(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a reboot was detected. */
  if(Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_MULTI)
  {
    /* #100 Reboot detected by multicast OfferService.
     *      Set event to multicast OfferService if no StopOfferService was received meanwhile. */
    SD_BEGIN_CRITICAL_SECTION();
    if(Sd_GetEventRxOfClientDyn(ClientIdx) != SD_CLIENT_EVENT_SERVICE_STOP_OFFER)
    {
      Sd_SetEventRxOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_OFFER_MULTI);                                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
    SD_END_CRITICAL_SECTION();

    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_Util_TriggerStateMachineRun(instanceIdx);
  }
  else if(Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_UNI)
  {
    /* #101 Reboot detected by unicast OfferService.
     *      Set event to unicast OfferService if no StopOfferService was received meanwhile. */
    SD_BEGIN_CRITICAL_SECTION();

    if(Sd_GetEventRxOfClientDyn(ClientIdx) != SD_CLIENT_EVENT_SERVICE_STOP_OFFER)
    {
      Sd_SetEventRxOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_OFFER_UNI);                                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
    SD_END_CRITICAL_SECTION();

    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_Util_TriggerStateMachineRun(instanceIdx);
  }
  else
  {
    /* #102 No reboot detected - reset the event. */
    Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_HandleRequestState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleRequestState(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is not requested anymore. */
  if((Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_RELEASED) &&
    ((Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_REQUESTED_BUT_NOT_READY) ||
    (Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_SERVICE_READY) ||
    (Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_STOPPED)))
  {
    /* #100 Enter the down phase and indicate the state. */
    Sd_SetCurrentStateOfClientDyn(ClientIdx, SD_CLIENT_SERVICE_DOWN);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    if(Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_SERVICE_READY)
    {
      BswM_Sd_ClientServiceCurrentState(Sd_GetHandleIdOfClient(ClientIdx), SD_CLIENT_SERVICE_DOWN);
    }

    /* #101 The client is not requested, change the state. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_NOT_REQUESTED_NOT_SEEN, FALSE);
    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

    Sd_StateClient_Unconfigure(ClientIdx, TRUE, FALSE);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_HandleRequestState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_HandleRetrySubscription(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the retry subscription feature is configured. */
  if(Sd_GetRetryMaxOfInstance(instanceIdx) != 0u)
  {
    /* #100 Check if the client is in the main phase and the retry subscription timer is expired. */
    /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
    if((Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_SERVICE_READY) &&
      (TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetRetryTimerOfClientDyn(ClientIdx), TRUE)))
    {
      /* #1000 Check if no eventgroups of the client perform subscription retries. */
      if(Sd_StateClient_CheckIfRetryActive(ClientIdx) == FALSE)
      {
        /* 10000 Cancel the retry timer. */
        Sd_Util_ResetTimerToInvalid(Sd_GetAddrRetryTimerOfClientDyn(ClientIdx));                                        /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      }
      /* #1001 Otherwise, check if the maximal amount of retries is not yet reached. */
      else if(Sd_GetRetryCounterOfClientDyn(ClientIdx) <= Sd_GetRetryMaxOfInstance(instanceIdx))
      {
        /* #10010 Increment the retry subscription counter. */
        /* Overflow in case of RetryMax is configured to 0xFF (retry forever) is expected. */
        Sd_IncRetryCounterOfClientDyn(ClientIdx);                                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      }
      /* #1002 Otherwise, do not trigger additional retries. */
      else
      {
        /* #10020 Invalidate the retry subscription timer and report a DET runtime error. */
        Sd_Util_ResetTimerToInvalid(Sd_GetAddrRetryTimerOfClientDyn(ClientIdx));                                        /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
        (void)Det_ReportRuntimeError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_HANDLERETRYSUBSCRIPTION, SD_E_COUNT_OF_RETRY_SUBSCRIPTION_EXCEEDED);
      }
    }

    /* #101 Update the time for the next state machine run. */
    Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetRetryTimerOfClientDyn(ClientIdx));
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_CheckIfRetryActive()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_CheckIfRetryActive(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;
  boolean retryActive = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check all eventgroups of the client service instance. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    /* #100 Check if the consumed eventgroup performs subscription retries. */
    if((Sd_GetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT) ||
      (Sd_GetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER) ||
      (Sd_GetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_RECONFIGURE))
    {
      retryActive = TRUE;
      break;
    }
  }

  return retryActive;
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessInitial()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessInitial(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initial run of the state machine. */
  if(Sd_GetStateSwcOfClientDyn(ClientIdx) != SD_CLIENT_SERVICE_REQUESTED)
  {
    /* #100 Update the state if the client is not requested. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_NOT_REQUESTED_NOT_SEEN, FALSE);
  }
  else if((Sd_GetStateOfInstanceDyn(instanceIdx) != SD_INSTANCE_UP_AND_CONFIGURED) /* &&
    (Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_REQUESTED) */ )
  {
    /* #101 Update the state if the instance is not ready. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_REQUESTED_BUT_NOT_READY, FALSE);
  }
  else  /* (Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_REQUESTED) && */
        /* (Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED) */
  {
    /* #102 Otherwise, update the state and reset the TimeToTriggerSend. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT, TRUE);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessNotRequestedNotSeen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessNotRequestedNotSeen(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 OfferService message received for the first time. Update the configuration. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx),
      Sd_GetOfferedTTLOfClientDyn(ClientIdx), instanceIdx);                                                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_NOT_REQUESTED_SEEN, FALSE);

    /* #100 Reset the event. */
    Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessNotRequestedSeen()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessNotRequestedSeen(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the remote server was already seen. Update the state. */
  /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
  if((Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_DOWN) ||
    (TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimerTTLOfClientDyn(ClientIdx), FALSE)) ||
    ((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER)) /*lint !e655 */
  {
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_NOT_REQUESTED_NOT_SEEN, FALSE);
    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_SetCurrentStateOfClientDyn(ClientIdx, SD_CLIENT_SERVICE_DOWN);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    /* #100 Check if a StopOffer was received or a reboot detected. */
    if(Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER)
    {
      /* #1000 StopOffer - Reset the event. */
      Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
  /* #20 Otherwise, if an OfferService was received. */
  else if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #200 Reset the timer and the event. */
    Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx),
      Sd_GetOfferedTTLOfClientDyn(ClientIdx), instanceIdx);                                                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  /* #30 Otherwise, if the client is requested. */
  else if(Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_REQUESTED)
  {
    /* #300 Client was set to requested: Configure the client for consumed methods. */
    if(Sd_StateClient_Configure(ClientIdx) == E_OK)
    {
      /* #3000 Enter the main phase and inform the BswM. */
      Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SERVICE_READY, FALSE);
      Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_AVAILABLE);
    }
  }
  /* #40 Otherwise, do not advance state and set marker for state machine execution to stay in this state. */
  else
  {
    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessRequestedNotReady()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessRequestedNotReady(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  if(Sd_GetStateOfInstanceDyn(instanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED)
  {
    /* #10 Update the state and reset the TimeToTriggerSend. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT, TRUE);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessSearchingInitial()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessSearchingInitial(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfClientTimerType clientTimerIdx = Sd_GetClientTimerIdxOfClient(ClientIdx);
  Sd_CommonInitialDelayIdxOfClientType commonDelayIdx = Sd_GetCommonInitialDelayIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check state of the wait phase. */
  if(Sd_CheckIfTimerIsInvalid(Sd_GetTimeToTriggerSendOfClientDyn(ClientIdx)))
  {
    uint32 additionalDelay;

    /* #100 Get random delay if a common delay shall not be used or the common delay has not been determined yet. */
    if((commonDelayIdx == SD_NO_COMMONINITIALDELAYIDXOFCLIENT) ||
      (Sd_GetCommonInitialDelay(commonDelayIdx) == SD_INV_TIMER_VALUE_32BIT))
    {
      additionalDelay = Sd_Util_GetRandomNrInRange(
        Sd_GetInitialFindDelayMinOfClientTimer(clientTimerIdx),
        Sd_GetInitialFindDelayMaxOfClientTimer(clientTimerIdx));

      if(commonDelayIdx != SD_NO_COMMONINITIALDELAYIDXOFCLIENT)
      {
        Sd_SetCommonInitialDelay(commonDelayIdx, additionalDelay);                                                      /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }
    }
    /* #101 Common delay shall be used and it has been set already, use it. */
    else
    {
      additionalDelay = Sd_GetCommonInitialDelay(commonDelayIdx);
    }

    /* #102 Set Timer and mark client for execution of state machine. */
    Sd_Util_SetTimerOffsetWithTrigger(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx), additionalDelay, instanceIdx); /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  else if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToTriggerSendOfClientDyn(ClientIdx), TRUE))
  {
    /* #103 Wait phase timer is exceeded. Update the state and reset the TimeToTriggerSend. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SEARCHING_REPETITION, TRUE);
    Sd_SetRepetitionRunOfClientDyn(ClientIdx, 0u);                                                                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    /* #104 Send a FindService message. */
    Sd_Util_AddFindEntryToList(ClientIdx);

    /* #105 Reset common delay. */
    if(commonDelayIdx != SD_NO_COMMONINITIALDELAYIDXOFCLIENT)
    {
      Sd_SetCommonInitialDelay(commonDelayIdx, SD_INV_TIMER_VALUE_32BIT);                                               /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    }
  }
  else
  {
    /* #106 Wait phase timer is not exceeded. Wait for next execution. */
    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  /* #20 Check conditions to leave the "Search for Service" block. */
  Sd_StateClient_ProcessLeaveSearching(ClientIdx);
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessSearchingRepetition()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessSearchingRepetition(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfClientTimerType clientTimerIdx = Sd_GetClientTimerIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Mark client for execution of state machine. */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Check if the repetition phase was entered the first time. */
  if((Sd_CheckIfTimerIsInvalid(Sd_GetTimeToTriggerSendOfClientDyn(ClientIdx))) &&
    (Sd_GetInitialFindRepetitionsMaxOfClientTimer(clientTimerIdx) > 0u) && (Sd_GetRepetitionRunOfClientDyn(ClientIdx) == 0u))
  {
    /* #200 Wind up the timer. */
    Sd_Util_SetTimerOffsetWithTrigger(
      Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx),
      (uint32)Sd_GetInitialFindRepetitionBaseDelayOfClientTimer(clientTimerIdx) - SD_MAIN_FCT_CYCLE_TIME_MS,
      instanceIdx);                                                                                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #30 Succeeding runs of the repetition phase. */
  if((TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToTriggerSendOfClientDyn(ClientIdx), TRUE)) &&
    (Sd_GetRepetitionRunOfClientDyn(ClientIdx) < Sd_GetInitialFindRepetitionsMaxOfClientTimer(clientTimerIdx)))
  {
    /* #300 Send a FindService message if timer is expired. */
    Sd_Util_AddFindEntryToList(ClientIdx);
    Sd_IncRepetitionRunOfClientDyn(ClientIdx);                                                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    /* #301 Wind up the timer. */
    Sd_Util_SetTimerOffsetWithTrigger(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx),
      (uint32)((((uint32)(1u)) << Sd_GetRepetitionRunOfClientDyn(ClientIdx)) * Sd_GetInitialFindRepetitionBaseDelayOfClientTimer(clientTimerIdx)),
      instanceIdx);                                                                                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }
  else if(Sd_GetRepetitionRunOfClientDyn(ClientIdx) == Sd_GetInitialFindRepetitionsMaxOfClientTimer(clientTimerIdx))
  {
    /* #302 End the searching repetition phase, if the amount of repetitions is reached. */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_IncRepetitionRunOfClientDyn(ClientIdx);                                                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  else
  {
    /* #303 Stay in repetition phase if timer is not yet expired. */
  }

  /* #40 Check conditions to leave the "Search for Service" block. */
  Sd_StateClient_ProcessLeaveSearching(ClientIdx);
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessLeaveSearching()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessLeaveSearching(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the remote server was seen. */
  if(!Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfClientDyn(ClientIdx)))
  {
    /* #100 Reset the TTL. */
    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #20 Check if the instance is no more active. */
  if(Sd_GetStateOfInstanceDyn(instanceIdx) != SD_INSTANCE_UP_AND_CONFIGURED)
  {
    Sd_ConsumedEventgroupIterType consumedEventgroupIdx;

    /* #200 Update the state and reset the TimeToTriggerSend. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_REQUESTED_BUT_NOT_READY, TRUE);

    /* #201 Inform the BswM about the change of the client service instance and all associated eventgroups. */
    Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_DOWN);

    for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
      consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
      consumedEventgroupIdx++)
    {
      BswM_Sd_ConsumedEventGroupCurrentState(
        Sd_GetHandleIdOfConsumedEventgroup(consumedEventgroupIdx), SD_CONSUMED_EVENTGROUP_DOWN);
    }
  }

  /* #30 Check if the client was released. */
  if(Sd_GetStateSwcOfClientDyn(ClientIdx) == SD_CLIENT_SERVICE_RELEASED)
  {
    /* #300 The client service is not requested, change the state. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_NOT_REQUESTED_NOT_SEEN, FALSE);
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #40 Check if an OfferService message was received. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #400 Process the received OfferService message. */
    Sd_StateClient_ProcessLeaveSearchingRcvOffer(ClientIdx);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessLeaveSearchingRcvOffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessLeaveSearchingRcvOffer(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the timer with the offered TTL. */
  Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx),
    Sd_GetOfferedTTLOfClientDyn(ClientIdx), instanceIdx);                                                               /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

  /* #20 Configure the client according to the received OfferService message. */
  if(Sd_StateClient_Configure(ClientIdx) == E_OK)
  {
    /* #200 Enter the main phase and inform the BswM. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SERVICE_READY, TRUE);
    Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_AVAILABLE);

    /* #201 The event is not reset because it is needed during processing of the eventgroups. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessReady()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessReady(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Mark client for execution of state machine. */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Check if an OfferService or StopOfferService message was received. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) != SD_CLIENT_EVENT_SERVICE_NONE) /*lint !e655 */
  {
    /* #200 Process the received message. */
    Sd_StateClient_ProcessReadyEventReceived(ClientIdx);
  }
  /* #30 Otherwise, check if the TTL timer is expired. */
  else if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimerTTLOfClientDyn(ClientIdx), FALSE))
  {
    /* #300 The TTL of server expired, unconfigure all connections. */
    Sd_StateClient_Unconfigure(ClientIdx, TRUE, TRUE);

    /* #301 Update the state and reset the TimeToTriggerSend. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SEARCHING_INITIAL_WAIT, TRUE);
    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

    /* #302 Report the status of the client service. */
    Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_DOWN);
  }
  /* #40 Otherwise, nothing to do. */
  else
  {
    /* Wait till the Timer is expired. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessReadyEventReceived()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessReadyEventReceived(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if an OfferService or StopOfferService message was received. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #100 Received an OfferService message. Configure the client. */
    if(Sd_StateClient_Configure(ClientIdx) == E_OK)
    {
      /* #1000 On success, update the timer. */
      Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx),
        Sd_GetOfferedTTLOfClientDyn(ClientIdx), instanceIdx);                                                           /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

      /* #1001 The event is not reset because it is needed during processing of the eventgroups. */
    }
    else
    {
      /* #1002 If failed, the server has changed the attached endpoint addresses. */

      /* #1003 Send a FindService message. */
      Sd_Util_AddFindEntryToList(ClientIdx);

      /* #1004 Cancel the timer and reset the event. */
      Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_STOPPED, FALSE);
      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                           /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

      /* #1005 Report the status of the client service. */
      Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_DOWN);
    }
  }
  else
  {
    /* #101 Received StopOfferService message. Cancel the timer and update state machine. */
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_STOPPED, FALSE);
    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), instanceIdx);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

    /* #102 Report the status of the client service. */
    Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_DOWN);

    Sd_StateClient_Unconfigure(ClientIdx, TRUE, TRUE);

    /* #103 Check if a StopOffer was received or a reboot detected. */
    if(Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER)
    {
      /* #1030 StopOffer - Reset the event. */
      Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessStopped()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessStopped(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if an OfferService message was received. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #100 Update the timer. */
    Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx),
      Sd_GetOfferedTTLOfClientDyn(ClientIdx), instanceIdx);                                                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

    if(Sd_StateClient_Configure(ClientIdx) == E_OK)
    {
      /* #1000 Enter the main phase and inform the BswM. */
      Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_SERVICE_READY, FALSE);
      Sd_UtilClient_SetCurrentStateInformBswm(ClientIdx, SD_CLIENT_SERVICE_AVAILABLE);
    }
  }

  /* #20 Change the state if the connection is lost. */
  if(Sd_GetStateOfInstanceDyn(instanceIdx) != SD_INSTANCE_UP_AND_CONFIGURED)
  {
    Sd_StateClient_Update(ClientIdx, SD_CLIENT_STATE_REQUESTED_BUT_NOT_READY, FALSE);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCeg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCeg(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Handle all eventgroups of the client service instance. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    /* #100 Check if the service is ready. */
    if(Sd_GetStateMachineOfClientDyn(ClientIdx) == SD_CLIENT_STATE_SERVICE_READY)
    {
      /* #1000 Unconfigure consumed eventgroup if eventgroup has been flagged for unconfiguration. */
      if (Sd_IsSoConMarkedForClosureOfConsumedEventgroupDyn(consumedEventgroupIdx))
      {
        Sd_StateClient_UnconfigureCeg(consumedEventgroupIdx, FALSE, TRUE);
      }
      /* #1001 Otherwise execute the state machine of the consumed eventgroup. */
      else
      {
        Sd_StateClient_ProcessCegState(consumedEventgroupIdx);
      }

      /* #1002 Check if the TTL expired or the eventgroup was set from requested to released. */
      /*lint -e655 */
      if(((TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx), FALSE)) &&
        (!Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx))) &&
        ((Sd_GetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx) & SD_CONSUMED_EVENTGROUP_STATE_MASK) != SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED)) ||
        (((Sd_GetStateMachineOfConsumedEventgroupDyn(consumedEventgroupIdx) & SD_CONSUMED_EVENTGROUP_STATE_MASK) != SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED) &&
        (Sd_GetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_RELEASED)) ||
        (Sd_GetEventOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CLIENT_EVENT_EVENTGROUP_NACK)) /*lint +e655 */
      {
        /* #10020 Unconfigure consumed eventgroup. */
        Sd_StateClient_ReleaseCeg(consumedEventgroupIdx);
      }
    }
    else
    {
      /* #1003 The service instance is not ready. Reset the state of the consumed eventgroup. */
      Sd_StateClient_ProcessCegReset(consumedEventgroupIdx);
    }

    if(!Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx)))
    {
      /* #1004 Update the time for the next state machine run. */
      Sd_Util_SetNextStateMachineRun(instanceIdx, Sd_GetTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegReset(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The service instance is not ready. Reset the state of the eventgroup. Do not trigger the state machine execution. */
  Sd_SetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED);          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Report the state of all consumed eventgroups to BswM if the service was changed to down. */
  if(!Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx)))
  {
    if(Sd_GetCurrentStateOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SD_CONSUMED_EVENTGROUP_DOWN)
    {
      BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(ConsumedEventgroupIdx),
        SD_CONSUMED_EVENTGROUP_DOWN);
      Sd_SetCurrentStateOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_DOWN);                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx), instanceIdx);     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #30 Clear the SoAd configuration of the eventgroup. */
  Sd_StateClient_UnconfigureCeg(ConsumedEventgroupIdx, FALSE, TRUE);
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegState(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Execute the state machine of the consumed eventgroup based on the current state. */
  switch(Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx))
  {
    case SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED:
    case SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED_AFTER_MULTI_OFFER_NACK:
      /* #100 Execute state machine if in state unsubscribed. */
      Sd_StateClient_ProcessCegUnsubscribed(ConsumedEventgroupIdx);
      break;

    case SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT:
    case SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER:
    case SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_RECONFIGURE:
      /* #101 Execute state machine if in state registration sent. */
      Sd_StateClient_ProcessCegRegistrationSent(ConsumedEventgroupIdx);
      break;

    case SD_CONSUMED_EVENTGROUP_STATE_SUBSCRIBED:
      /* #102 Execute state machine if in state subscribed. */
      Sd_StateClient_ProcessCegSubscribed(ConsumedEventgroupIdx);
      break;

    default:                                                                                                            /* COV_SD_MISRA */
      /* #103 Undefined state. */
      break;
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegUnsubscribed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegUnsubscribed(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(clientIdx);
  Sd_SizeOfClientTimerType clientTimerIdx = Sd_GetClientTimerIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  uint32 randDelay;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the eventgroup is requested */
  /*lint -e655 */
  if((Sd_GetServiceModeRequestOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_REQUESTED) &&
    (((Sd_GetEventMainOfClientDyn(clientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) ||
    (Sd_IsTriggerSubscriptionOfConsumedEventgroupDyn(ConsumedEventgroupIdx)))) /*lint +e655 */
  {
    retVal = Sd_StateClient_UpdateEventGroup(ConsumedEventgroupIdx);

    if(retVal == E_OK)
    {
      /* #100 Check if the OfferService message was transmitted by multicast or unicast.
       *      Messages received via multicast will be answered with an additional delay. */
      if(Sd_GetEventMainOfClientDyn(clientIdx) == SD_CLIENT_EVENT_SERVICE_OFFER_MULTI)
      {
        /* Calculate a random delay after which the response message will be transmitted. */
        randDelay = Sd_Util_GetRandomNrInRangeForResponse(
          Sd_GetRequestResponseMinDelayOfClientTimer(clientTimerIdx),
          Sd_GetRequestResponseMaxDelayOfClientTimer(clientTimerIdx),
          FALSE);

        /* #1000 Check if the reception of this multicast OfferService entry should trigger the transmission of a
         *       StopSubscribeEventgroup-SubscribeEventgroup sequence. */
        if(Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED_AFTER_MULTI_OFFER_NACK)
        {
          /* #10000 Add a StopSubscribeEventgroup entry to the TX queue. */
          Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, FALSE, randDelay);
        }

        Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER);
      }
      else
      {
        randDelay = 0u;
        Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT);
      }

      /* #101 Add a SubscribeEventgroup entry to the TX queue. */
      Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, TRUE, randDelay);

      /* #102 Enable the unicast PDU routings in order to prevent the race condition discussed in RFC 68309. */
      if(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
      {
        (void)Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx),
          Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx));
      }
      if(Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
      {
        (void)Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx),
          Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx));
      }

      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx), instanceIdx);   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      Sd_SetTriggerSubscriptionOfConsumedEventgroupDyn(ConsumedEventgroupIdx, FALSE);                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSent(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(clientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if an acknowledge was received. */
  if(Sd_GetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CLIENT_EVENT_EVENTGROUP_ACK)
  {
    /* #100 Process the acknowledge. */
    Sd_StateClient_ProcessCegRegistrationSentRxAck(ConsumedEventgroupIdx);
  }
  /* #20 Otherwise, check if an OfferService was received.*/
  else if((Sd_GetEventMainOfClientDyn(clientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #200 Process the OfferService message. */
    if(Sd_StateClient_UpdateEventGroup(ConsumedEventgroupIdx) == E_OK)
    {
      Sd_StateClient_ProcessCegRegistrationSentRxOffer(ConsumedEventgroupIdx);
    }
  }
  /* #30 Otherwise, check if the subscription has to be retried. */
  /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
  else if((Sd_GetRetryCounterOfClientDyn(clientIdx) <= Sd_GetRetryMaxOfInstance(instanceIdx)) &&
    (TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetRetryTimerOfClientDyn(clientIdx), TRUE)))
  {
    /* #300 Retry subscription by transmission of StopSubscribeEventgroup and SubscribeEventgroup message. */
    Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, FALSE, 0u);
    Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, TRUE, 0u);
  }
  /* #40 Otherwise, no relevant message received and no retry has to be triggered. */
  else
  {
    /* #400 Wait for response from server or till TTL or retry timer expires. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSentRxAck()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSentRxAck(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(clientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The server acknowledged the subscription, update the socket connections. */
  Std_ReturnType retVal = Sd_StateClient_UpdateEventGroupAckReceived(ConsumedEventgroupIdx);

  if(retVal == E_OK)
  {
    /* #100 Inform the BswM if the eventgroup was subscribed for the first time. */
    if(Sd_CheckIfTimerIsZero(Sd_GetTimerTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx)))
    {
      /* Inform the BswM. */
      BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(ConsumedEventgroupIdx),
        SD_CONSUMED_EVENTGROUP_AVAILABLE);
      Sd_SetCurrentStateOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_AVAILABLE);               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    /* #101 Start the timers, update the state and reset the event. */
    Sd_Util_SetTimerOffsetSecWithTrigger(Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx),
      Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(ConsumedEventgroupIdx),
      instanceIdx);                                                                                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
    Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_SUBSCRIBED);
    Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  else
  {
    /* #102 The multicast socket connection could not be configured. */
    if(Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_RECONFIGURE)
    {
      /* #1020 If the multicast endpoint was changed, the Sd will try to configure it in the next cycle.
       *       The SD_CLIENT_EVENT_EVENTGROUP_ACK event is not removed. */
      Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_RECONFIGURE);
    }
    else
    {
      /* #1021 Otherwise, inform the BswM, update the state and remove event. */
      BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(ConsumedEventgroupIdx),
        SD_CONSUMED_EVENTGROUP_DOWN);
      Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED);
      Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegRegistrationSentRxOffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegRegistrationSentRxOffer(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfClientTimerType clientTimerIdx = Sd_GetClientTimerIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  uint32 randDelay;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the previous subscribe message is already transmitted, or still pending because of a missing TCP connection. */
  if(TRUE == Sd_StateClient_EntryListContainsSubscribe(ConsumedEventgroupIdx))
  {
    /* #100 There is already a SubscribeEventgroup message pending.
     *      Do not trigger the StopSubscribeEventgroup - SubscribeEventgroup message. */
  }
  else
  {
    /* #101 Check if the OfferService message was transmitted by multicast or unicast. */
    if(Sd_GetEventMainOfClientDyn(clientIdx) == SD_CLIENT_EVENT_SERVICE_OFFER_MULTI)
    {
      /* #1010 Add a random delay to the response message. */
      randDelay = Sd_Util_GetRandomNrInRangeForResponse(Sd_GetRequestResponseMinDelayOfClientTimer(clientTimerIdx),
        Sd_GetRequestResponseMaxDelayOfClientTimer(clientTimerIdx), FALSE);

      if(Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER)
      {
        /* #10100 Send out a StopSubscribeEventgroup followed by a SubscribeEventgroup message. */
        Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, FALSE, randDelay);
      }

      Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER);
    }
    else  /* Sd_GetEventMainOfClientDyn(clientIdx) == SD_CLIENT_EVENT_SERVICE_OFFER_UNI */
    {
      /* #1011 The response can be transmitted without additional delay. */
      randDelay = 0u;
      Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT);
    }

    /* #102 Send out a SubscribeEventgroup message. */
    Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, TRUE, randDelay);
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_ProcessCegSubscribed()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ProcessCegSubscribed(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfClientTimerType clientTimerIdx = Sd_GetClientTimerIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  uint32 randDelay;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If an OfferService message was received. */
  if((Sd_GetEventMainOfClientDyn(clientIdx) & SD_CLIENT_EVENT_TYPE_MASK) == SD_CLIENT_EVENT_SERVICE_OFFER) /*lint !e655 */
  {
    /* #100 Update the consumed eventgroup based on the OfferService. */
    retVal = Sd_StateClient_UpdateEventGroup(ConsumedEventgroupIdx);

    if(retVal == E_OK)
    {
      /* #1000 If the OfferService message was transmitted by multicast. */
      if(Sd_GetEventMainOfClientDyn(clientIdx) == SD_CLIENT_EVENT_SERVICE_OFFER_MULTI)
      {
        /* #10000 Calculate a random delay after which the response message will be transmitted. */
        randDelay = Sd_Util_GetRandomNrInRangeForResponse(Sd_GetRequestResponseMinDelayOfClientTimer(clientTimerIdx),
          Sd_GetRequestResponseMaxDelayOfClientTimer(clientTimerIdx), FALSE);

        /* #10001 Update the state of the consumed eventgroup. */
        Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER);
      }
      /* #2000 Otherwise, if the OfferService was transmitted via unicast.*/
      else
      {
        /* #20000 Do not add a random delay to the response message. */
        randDelay = 0u;

        /* #20001 Update the state of the consumed eventgroup. */
        Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT);
      }

      /* #300 Send a subscribe eventgroup message and init the mechanism waiting for the ACK. */
      Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, TRUE, randDelay);
    }
    else
    {
      Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
    }
  }
  /* #40 Otherwise, if the client was set to released. */
  else if(Sd_GetStateSwcOfClientDyn(clientIdx) == SD_CLIENT_SERVICE_RELEASED)
  {
    /* #400 Send a StopSubscribe message and inform the BswM. */
    Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, FALSE, 0u);
    BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(ConsumedEventgroupIdx),
      SD_CONSUMED_EVENTGROUP_DOWN);
    Sd_SetCurrentStateOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_DOWN);                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_SetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED);        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  /* #50 Otherwise, do not perform any actions. */
  else
  {
    /* Timer is not yet expired. */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_Configure()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_Configure(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfMethodType methodIdx = Sd_GetMethodIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client configures a consumed method using TCP. */
  if((methodIdx != SD_NO_METHODIDXOFCLIENT) && Sd_IsTcpConfiguredOfMethod(methodIdx))
  {
    /* #100 Configure the TCP socket connection. */
    retVal = Sd_StateClient_ConfigureMethod(ClientIdx, Sd_GetAddrMethodTcpSoConIdOfClientDyn(ClientIdx),
      Sd_GetTcpSoConId(Sd_GetTcpSoConIdStartIdxOfClient(ClientIdx)),
      Sd_GetAddrServerTcpEndpointAddrOfClientDyn(ClientIdx));                                                           /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #20 Check if the client configures a consumed method using UDP. */
  if((methodIdx != SD_NO_METHODIDXOFCLIENT) && Sd_IsUdpConfiguredOfMethod(methodIdx))
  {
    /* #200 Configure the UDP socket connection. */
    retVal = Sd_StateClient_ConfigureMethod(ClientIdx, Sd_GetAddrMethodUdpSoConIdOfClientDyn(ClientIdx),
      Sd_GetIdOfUdpSoCon(Sd_GetUdpSoConStartIdxOfClient(ClientIdx)),
      Sd_GetAddrServerUdpEndpointAddrOfClientDyn(ClientIdx));                                                           /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #30 Check if the consumed method configuration has failed. */
  if(retVal == E_NOT_OK)
  {
    /* #300 Unconfigure the client and trigger execution of MainFunction in order to perform retry. */
    Sd_StateClient_Unconfigure(ClientIdx, FALSE, TRUE);
    Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_Util_TriggerStateMachineRun(instanceIdx);
  }
  /* #40 Otherwise, check if the client is configured for subscription retry. */
  else if((Sd_GetOfferedTTLOfClientDyn(ClientIdx) == SD_TTL_INFINITE) &&
    (Sd_GetRetryMaxOfInstance(instanceIdx) != 0u))
  {
    /* #400 Reset the retry subscription counter. */
    Sd_SetRetryCounterOfClientDyn(ClientIdx, 1u);                                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }
  /* #50 Otherwise, do not use the retry subscription functionality. */
  else
  {
    /* #500 Reset retry subscription counter and timer values. */
    Sd_SetRetryCounterOfClientDyn(ClientIdx, 0u);                                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrRetryTimerOfClientDyn(ClientIdx));                                            /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_ConfigureMethod()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_ConfigureMethod(
  Sd_SizeOfClientType ClientIdx,
  SD_P2VAR(SoAd_SoConIdType) MethodSoConIdPtr,
  SoAd_SoConIdType ServiceStartSoConId,
  SD_P2CONST(Sd_SockAddrContainerType) ServerEndpointAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfMethodType methodIdx = Sd_GetMethodIdxOfClient(ClientIdx);
  Sd_SockAddrContainerType remoteAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client is already configured for consumed methods. */
  if(*MethodSoConIdPtr == SOAD_INV_SO_CON_ID)
  {
    /* #100 Configure a socket connection with the corresponding remote address. */
    /* PRQA S 0310 3 */ /* MD_Sd_11.4_0310 */
    /* PRQA S 0311 2 */ /* MD_Sd_11.5_0311 */
    retVal = SoAd_SetUniqueRemoteAddr(ServiceStartSoConId,
      (SD_P2VAR(SoAd_SockAddrType))ServerEndpointAddrPtr, MethodSoConIdPtr);                                            /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_SOCK_ADDR_CAST */ /* SBSW_SD_CAST_TO_VAR */

    if((retVal == E_OK) && (*MethodSoConIdPtr != SOAD_INV_SO_CON_ID))
    {
      /* #1000 Each entity which requires the socket connection opens it in order to indicate the dependency. */
      retVal = SoAd_OpenSoCon(*MethodSoConIdPtr);
      retVal |= Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(methodIdx), *MethodSoConIdPtr);
    }
    else
    {
      *MethodSoConIdPtr = SOAD_INV_SO_CON_ID;                                                                           /* SBSW_SD_VALID_API_POINTER */
    }
  }
  else
  {
    /* #101 The socket connection is already configured. Check if the server endpoint address has changed. */

    retVal = Sd_SoAd_GetRemoteAddr(*MethodSoConIdPtr, &remoteAddr);                                                     /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* PRQA S 3415 1 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_NOT_OK) || (FALSE == Sd_Util_SockAddrIsEqual(ServerEndpointAddrPtr, &remoteAddr)))                  /* SBSW_SD_REFERENCE_OF_VARIABLE */
    {
      /* #1010 The attached endpoint has changed. Close the currently configured connection and mark the service as not available. */
      (void)SoAd_CloseSoCon(*MethodSoConIdPtr, FALSE);
      (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(methodIdx), *MethodSoConIdPtr);
      *MethodSoConIdPtr = SOAD_INV_SO_CON_ID;                                                                           /* SBSW_SD_VALID_API_POINTER */
      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx), Sd_GetInstanceIdxOfClient(ClientIdx));  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      retVal = E_NOT_OK;
    }
  }

  return retVal;
} /* PRQA S 6050 */ /* MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  Sd_StateClient_Unconfigure()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_StateClient_Unconfigure(
  Sd_SizeOfClientType ClientIdx,
  boolean ResetEndpointInfo,
  boolean UnconfigureCegs)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean abortFlag = FALSE, tmpResetEndpointInfo = ResetEndpointInfo;
  Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;
  Sd_SizeOfMethodType methodIdx = Sd_GetMethodIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the renewal was triggered by reboot detection. */
  if((Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_MULTI) ||
    (Sd_GetEventMainOfClientDyn(ClientIdx) == SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_UNI))
  {
    /* #100 Do not remove the server endpoint addresses. These will be used during the next cycle to reestablish connections.
     *      Abort existing TCP connections because remote server has rebooted. */
    abortFlag = TRUE;
    tmpResetEndpointInfo = FALSE;
  }

  if(tmpResetEndpointInfo == TRUE)
  {
    /* #101 Remove the saved endpoint addresses. */
    (Sd_GetAddrServerTcpEndpointAddrOfClientDyn(ClientIdx))->family = SOAD_AF_INVALID;                                  /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    (Sd_GetAddrServerUdpEndpointAddrOfClientDyn(ClientIdx))->family = SOAD_AF_INVALID;                                  /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  /* #20 Reset retry subscription counter and timer values. */
  Sd_SetRetryCounterOfClientDyn(ClientIdx, 0u);                                                                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_ResetTimerToInvalid(Sd_GetAddrRetryTimerOfClientDyn(ClientIdx));                                              /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

  /* #30 Iterate over all eventgroups, disable the routing groups and close the socket connections. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    if(UnconfigureCegs == TRUE)
    {
      Sd_StateClient_UnconfigureCeg(consumedEventgroupIdx, abortFlag, tmpResetEndpointInfo);
    }
    else
    {
      Sd_SetSoConMarkedForClosureOfConsumedEventgroupDyn(consumedEventgroupIdx, TRUE);                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #40 Disable the SoAd routing groups for methods and close the socket connections. */
  if((methodIdx != SD_NO_METHODIDXOFCLIENT) &&
    ((Sd_IsTcpConfiguredOfMethod(methodIdx)) || (Sd_IsUdpConfiguredOfMethod(methodIdx))))
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupActRefIdxOfMethod(methodIdx));

    if(Sd_GetMethodTcpSoConIdOfClientDyn(ClientIdx) != SOAD_INV_SO_CON_ID)
    {
      /* #400 Unconfigure TCP for consumed methods. */
      (void)SoAd_CloseSoCon(Sd_GetMethodTcpSoConIdOfClientDyn(ClientIdx), abortFlag);
      Sd_SetMethodTcpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }

    if(Sd_GetMethodUdpSoConIdOfClientDyn(ClientIdx) != SOAD_INV_SO_CON_ID)
    {
      /* #401 Unconfigure UDP for consumed methods. */
      (void)SoAd_CloseSoCon(Sd_GetMethodUdpSoConIdOfClientDyn(ClientIdx), abortFlag);
      Sd_SetMethodUdpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroup()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroup(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the consumed eventgroup is configured for TCP. */
  if(Sd_ConsumedEventGroupUsesTcp(ConsumedEventgroupIdx))
  {
    /* #100 Update the TCP configuration. */
    retVal = Sd_StateClient_UpdateEventGroupTcp(ConsumedEventgroupIdx);
  }

  /* #20 Check if the consumed eventgroup is configured for UDP. */
  if(Sd_ConsumedEventGroupUsesUdp(ConsumedEventgroupIdx))
  {
    /* #200 Update the UDP configuration. */
    retVal |= Sd_StateClient_UpdateEventGroupUdp(ConsumedEventgroupIdx);
  }

#if(SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON == STD_ON)
  /* #30 Check the configured remote address of the multicast socket connection if the consumed eventgroup is not
   *     configured for UDP unicast, but multicast only. */
  if((!Sd_ConsumedEventGroupUsesUdp(ConsumedEventgroupIdx)) && Sd_ConsumedEventGroupUsesMulticast(ConsumedEventgroupIdx))
  {
    retVal |= Sd_StateClient_CheckMulticastSoConRemoteAddress(ConsumedEventgroupIdx);
  }
#endif

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupTcp(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  SoAd_SoConIdType soConId;
  SoAd_SoConIdType assignedSoConId = SOAD_INV_SO_CON_ID;
  Sd_SockAddrContainerType remoteAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the endpoint address has changed. */
  soConId = Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx);
  if(soConId != SOAD_INV_SO_CON_ID)
  {
    retVal = Sd_SoAd_GetRemoteAddr(soConId, &remoteAddr);                                                               /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_OK) &&
      (FALSE == Sd_Util_SockAddrIsEqual(Sd_GetAddrServerTcpEndpointAddrOfClientDyn(clientIdx), &remoteAddr)))           /* SBSW_SD_REFERENCE_OF_VARIABLE */
    {
      /* #1000 The attached endpoint has changed. Close the currently configured connection and mark the service as not available. */
      (void)SoAd_CloseSoCon(soConId, FALSE);
      Sd_SetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(clientIdx), Sd_GetInstanceIdxOfClient(clientIdx));  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
      retVal = E_NOT_OK;
    }
  }
  else
  {
    /* #101 Otherwise, try to establish a connection to the server. */
    /* PRQA S 0310 3 */ /* MD_Sd_11.4_0310 */
    retVal = SoAd_SetUniqueRemoteAddr(Sd_GetTcpSoConId(Sd_GetTcpSoConIdStartIdxOfClient(clientIdx)),
      (SD_P2VAR(SoAd_SockAddrType))Sd_GetAddrServerTcpEndpointAddrOfClientDyn(clientIdx),
      &assignedSoConId);                                                                                                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */ /* SBSW_SD_SOCK_ADDR_CAST */

    if(retVal == E_OK)
    {
      /* #1010 The requested IP address could be set or is already set. */

      /* #1011 Each EventGroup which requires the socket connection opens it in order to indicate the dependency. */
      retVal = SoAd_OpenSoCon(assignedSoConId);

      /* #1012 Save the socket connection ID which is used for this EventGroup. */
      Sd_SetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, assignedSoConId);                                  /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #20 Check if the server endpoint address could be saved. */
  if(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SOAD_INV_SO_CON_ID)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupUdp(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  SoAd_SoConIdType soConId;
  SoAd_SoConIdType assignedSoConId = SOAD_INV_SO_CON_ID;
  Sd_SockAddrContainerType remoteAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the endpoint address has changed. */
  soConId = Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx);
  if(soConId != SOAD_INV_SO_CON_ID)
  {
    retVal = Sd_SoAd_GetRemoteAddr(soConId, &remoteAddr);                                                               /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_OK) &&
      (FALSE == Sd_Util_SockAddrIsEqual(Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx), &remoteAddr)))           /* SBSW_SD_REFERENCE_OF_VARIABLE */
    {
      /* #1000 The attached endpoint has changed.
       *       Close the currently configured connection and mark the service as not available. */
      (void)SoAd_CloseSoCon(soConId, FALSE);
      Sd_SetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(clientIdx), Sd_GetInstanceIdxOfClient(clientIdx));  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
      Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      retVal = E_NOT_OK;
    }
  }
  else
  {
    /* #101 Otherwise, check if a socket connection is already configured with the correct server IP address or configure a new one. */
    /* PRQA S 0310 3 */ /* MD_Sd_11.4_0310 */
    retVal = SoAd_SetUniqueRemoteAddr(Sd_GetIdOfUdpSoCon(Sd_GetUdpSoConStartIdxOfClient(clientIdx)),
      (SD_P2VAR(SoAd_SockAddrType))Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx),
      &assignedSoConId);                                                                                                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */ /* SBSW_SD_SOCK_ADDR_CAST */

    if(retVal == E_OK)
    {
      /* #1010 The requested IP address could be set or is already set. */

      /* #1011 Each EventGroup which requires the socket connection opens it in order to indicate the dependency. */
      retVal = SoAd_OpenSoCon(assignedSoConId);

      /* #1012 Save the socket connection ID which is used for this EventGroup. */
      Sd_SetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, assignedSoConId);                                  /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #20 Check if the server endpoint address could be saved. */
  if(Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SOAD_INV_SO_CON_ID)
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}

#if(SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON == STD_ON)
/**********************************************************************************************************************
 *  Sd_StateClient_CheckMulticastSoConRemoteAddress()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_CheckMulticastSoConRemoteAddress(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  SoAd_SoConIdType soConId = Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx);
  Sd_SockAddrContainerType ipAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the multicast socket connection is configured. */
  if(soConId != SOAD_INV_SO_CON_ID)
  {
    /* #100 Check if the offered UDP unicast endpoint has changed. */
    retVal = Sd_SoAd_GetRemoteAddr(soConId, &ipAddr);                                                                   /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* PRQA S 3415 1 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_NOT_OK) || (FALSE == Sd_Util_SockAddrIsEqual(Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx), &ipAddr))) /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
    {
      /* #1000 The remote endpoint address has changed, reset the configuration. */
      (void)Sd_StateClient_ReleaseIpAddrAssignment(soConId);
      (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx), soConId);
      (void)SoAd_CloseSoCon(soConId, FALSE);
      Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_Util_ResetTimerToZeroTrigger(Sd_GetAddrTimerTTLOfClientDyn(clientIdx), Sd_GetInstanceIdxOfClient(clientIdx));  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

      retVal = E_NOT_OK;
    }
  }

  return retVal;
}
#endif

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceived()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceived(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the multicast configuration. */
  if(Sd_ConsumedEventGroupUsesMulticast(ConsumedEventgroupIdx))
  {
    /* #100 Check if the client is already configured for multicast reception. */
    if(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
    {
      /* #1000 If yes: Check the the new endpoint option matches the current configuration. */
      retVal = Sd_StateClient_UpdateEventGroupAckReceivedRenew(ConsumedEventgroupIdx);
    }
    else
    {
      /* #1001 Otherwise, configure consumed eventgroup for multicast. */
      retVal = Sd_StateClient_UpdateEventGroupAckReceivedInitial(ConsumedEventgroupIdx);
    }

    if(retVal == E_OK)
    {
      /* #1002 Enable the multicast PDU routing. */
      if(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
      {
        retVal = Sd_Util_EnableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx),
          Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx));
      }
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceivedInitial()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceivedInitial(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfMulticastSoConIdType multicastSoConIdIdx;
  Sd_LocalRemoteMatchTypeType matchType;
  SD_P2VAR(Sd_SockAddrContainerType) multicastEndpointAddrPtr =
    Sd_GetAddrMulticastEndpointAddr(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(ConsumedEventgroupIdx));

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check all available socket connections and find the one which matches best to the server. */
  retVal = Sd_StateClient_FindBestMatchLocalRemoteSoCon(ConsumedEventgroupIdx, &multicastSoConIdIdx, &matchType);       /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(retVal == E_OK)
  {
    /* #100 Configure the local address according to the server multicast endpoint. */
    if((matchType.LocalIpMatchType != SD_MATCH_TRUE) || (matchType.LocalPortMatchType != SD_MATCH_TRUE))
    {
      /* #1000 Check if the local IP address is already configured. */
      /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
      if((matchType.LocalIpMatchType != SD_MATCH_TRUE) &&
        (TRUE == Sd_StateClient_LocalIpAlreadyConfigured(multicastEndpointAddrPtr)))                                    /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
      {
        /* #10000 The requested multicast IP address is already configured at another socket. */
        retVal = E_NOT_OK;
      }
      else
      {
        /* #10001 Otherwise, request the local address according to the endpoint. */
        retVal = Sd_StateClient_RequestIpAddrAssignment(
          Sd_GetMulticastSoConId(multicastSoConIdIdx), multicastEndpointAddrPtr, TRUE);                                 /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
      }
    }
    else
    {
      /* #1001 The local address is already configured. Increment the request counter. */
      retVal = Sd_StateClient_RequestIpAddrAssignment(
        Sd_GetMulticastSoConId(multicastSoConIdIdx), multicastEndpointAddrPtr, FALSE);                                  /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
    }

    if(retVal == E_OK)
    {
#if(SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON == STD_ON)
      /* #1002 Check if the remote address has to be configured. */
      if((matchType.RemoteIpMatchType != SD_MATCH_TRUE) || (matchType.RemotePortMatchType != SD_MATCH_TRUE))
      {
        Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);

        /* #10020 Configure the remote address according to the server unicast endpoint. */
        /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
        retVal = SoAd_SetRemoteAddr(Sd_GetMulticastSoConId(multicastSoConIdIdx),
          (SD_P2VAR(SoAd_SockAddrType))Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx));                          /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */ /* SBSW_SD_SOCK_ADDR_CAST */
      }
#endif

      /* #1003 Open the socket connection. Each EventGroup which requires the socket connection opens it in order to indicate the dependency. */
      /* PRQA S 2986 1 */ /* MD_Sd_Rule-2.2_2986 */
      retVal |= SoAd_OpenSoCon(Sd_GetMulticastSoConId(multicastSoConIdIdx));

      /* #1004 Save the socket connection ID which is used for this EventGroup. */
      Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, Sd_GetMulticastSoConId(multicastSoConIdIdx)); /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #20 Check if the server endpoint address could be saved. */
  if(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SOAD_INV_SO_CON_ID)
  {
    retVal = E_NOT_OK;

    /* #200 Accept the acknowledge if no multicast endpoint was transmitted, but the unicast configuration was successful. */
    if((multicastEndpointAddrPtr->family == SOAD_AF_INVALID) &&
      (Sd_ConsumedEventGroupUsesUdp(ConsumedEventgroupIdx) &&
      (Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)))
    {
      retVal = E_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateEventGroupAckReceivedRenew()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_UpdateEventGroupAckReceivedRenew(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  SoAd_SoConIdType soConId = Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx);

  /* ----- Implementation ----------------------------------------------- */
  Sd_SockAddrContainerType localAddr;

  /* #10 Get the local address. */
  retVal = Sd_SoAd_GetLocalAddr(soConId, &localAddr);                                                                   /* SBSW_SD_REFERENCE_OF_VARIABLE */

  /* #20 Check if the local endpoint address has changed. */
  /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
  if((retVal == E_OK) && (FALSE == Sd_Util_SockAddrIsEqual(
    Sd_GetAddrMulticastEndpointAddr(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(ConsumedEventgroupIdx)), &localAddr))) /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */
  {
    /* #200 The attached endpoint has changed. Unconfigure the local address. */
    (void)Sd_StateClient_ReleaseIpAddrAssignment(soConId);

    (void)Sd_Util_DisableSpecificRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx), soConId);
    (void)SoAd_CloseSoCon(soConId, FALSE);
    Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoCon()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoCon(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2VAR(Sd_SizeOfMulticastSoConIdType) MulticastSoConIdPtr,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) MatchTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfMulticastSoConIdType tmpMulticastSoConIdIdx, bestMulticastSoConIdIdx = Sd_GetSizeOfMulticastSoConId();
  uint8 localMatchPrio = 0u, remoteMatchPrio = 0u;
  Sd_LocalRemoteMatchTypeType bestMatchType;

  /* ----- Implementation ----------------------------------------------- */
  MatchTypePtr->LocalIpMatchType = SD_MATCH_FALSE;                                                                      /* SBSW_SD_VALID_API_POINTER */
  MatchTypePtr->LocalPortMatchType = SD_MATCH_FALSE;                                                                    /* SBSW_SD_VALID_API_POINTER */
  MatchTypePtr->RemoteIpMatchType = SD_MATCH_FALSE;                                                                     /* SBSW_SD_VALID_API_POINTER */
  MatchTypePtr->RemotePortMatchType = SD_MATCH_FALSE;                                                                   /* SBSW_SD_VALID_API_POINTER */
  bestMatchType = *MatchTypePtr;

  /* #10 Calculate the match priority for all configured multicast socket connections. */
  for(tmpMulticastSoConIdIdx = Sd_GetMulticastSoConIdStartIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
    tmpMulticastSoConIdIdx < Sd_GetMulticastSoConIdEndIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
    tmpMulticastSoConIdIdx++)
  {
    /* #100 Calculate the match type of the local address. */
    retVal = Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchType(
      ConsumedEventgroupIdx, tmpMulticastSoConIdIdx, MatchTypePtr);                                                     /* SBSW_SD_PASSING_API_POINTER */

    /* #101 Calculate the match type of the remote address. */
    retVal |= Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchType(
      ConsumedEventgroupIdx, tmpMulticastSoConIdIdx, MatchTypePtr);                                                     /* SBSW_SD_PASSING_API_POINTER */

    /* #102 Check if the socket connection can be (re)configured to the expected values. */
    if((retVal == E_OK) &&
      (MatchTypePtr->LocalIpMatchType != SD_MATCH_FALSE) && (MatchTypePtr->LocalPortMatchType != SD_MATCH_FALSE) &&
      (MatchTypePtr->RemoteIpMatchType != SD_MATCH_FALSE) && (MatchTypePtr->RemotePortMatchType != SD_MATCH_FALSE))
    {
      /* #1020 The socket connection can be (re)configured. Check the priority of the local and remote match. */
      /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
      if((Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchPrio(MatchTypePtr, &localMatchPrio, &remoteMatchPrio) == TRUE) &&
        (Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchPrio(MatchTypePtr, &remoteMatchPrio) == TRUE))      /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      {
        /* #10200 Found better matching socket connection. */
        bestMulticastSoConIdIdx = tmpMulticastSoConIdIdx;
        bestMatchType = *MatchTypePtr;
      }
    }
  }

  /* #20 Check if a feasible socket connection was found. */
  if((localMatchPrio != 0u) && (remoteMatchPrio != 0u))
  {
    /* #200 Found a feasible socket connection, update values. */
    *MulticastSoConIdPtr = bestMulticastSoConIdIdx;                                                                     /* SBSW_SD_VALID_API_POINTER */
    *MatchTypePtr = bestMatchType;                                                                                      /* SBSW_SD_VALID_API_POINTER */
    retVal = E_OK;
  }
  else
  {
    /* #201 No socket connection found which matches the given IP address. */
    *MulticastSoConIdPtr = Sd_GetSizeOfMulticastSoConId();                                                              /* SBSW_SD_VALID_API_POINTER */
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(uint8, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState(
  SD_P2CONST(Sd_SockAddrContainerType) AddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 addrState;

  /* #10 Calculate the state of the port. */
  if(AddrPtr->port == SOAD_PORT_ANY)
  {
    addrState = SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_PORT;
  }
  else
  {
    addrState = SOAD_SOCON_IP_SET_PORT_SET & SOAD_SOCON_MASK_PORT;
  }

  /* #20 Calculate the state of the address. */
  if(AddrPtr->family == SOAD_AF_INET)
  {
    if(AddrPtr->data[0u] == SOAD_IPADDR_ANY)
    {
      addrState = (uint8)(addrState | (SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_IPADDR));
    }
    else
    {
      addrState = (uint8)(addrState | (SOAD_SOCON_IP_SET_PORT_SET & SOAD_SOCON_MASK_IPADDR));
    }
  }
  else /* AddrPtr->family == SOAD_AF_INET6) */
  {
    if((AddrPtr->data[0u] == SOAD_IPADDR_ANY) && (AddrPtr->data[1u] == SOAD_IPADDR_ANY) &&
      (AddrPtr->data[2u] == SOAD_IPADDR_ANY) && (AddrPtr->data[3u] == SOAD_IPADDR_ANY))
    {
      addrState = (uint8)(addrState | (SOAD_SOCON_IP_ANY_PORT_ANY & SOAD_SOCON_MASK_IPADDR));
    }
    else
    {
      addrState = (uint8)(addrState | (SOAD_SOCON_IP_SET_PORT_SET & SOAD_SOCON_MASK_IPADDR));
    }
  }

  return addrState;
}

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchType(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_SizeOfMulticastSoConIdType MulticastSoConIdIdx,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) LocalMatchTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SockAddrContainerType localAddr;
  uint8 localAddrState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the configured local IP address. */
  retVal = Sd_SoAd_GetLocalAddr(Sd_GetMulticastSoConId(MulticastSoConIdIdx), &localAddr);                               /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(retVal == E_OK)
  {
    SD_P2CONST(Sd_SockAddrContainerType) multicastEndpointAddrPtr =
      Sd_GetAddrMulticastEndpointAddr(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(ConsumedEventgroupIdx));

    /* #100 Calculate the state of the local address. */
    localAddrState = Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState(&localAddr);                             /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Compare the local address with the configured value and calculate a match type. */
    LocalMatchTypePtr->LocalIpMatchType = Sd_Util_CompareSockAddrIp(
      multicastEndpointAddrPtr, &localAddr, localAddrState);                                                            /* SBSW_SD_VALID_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    LocalMatchTypePtr->LocalPortMatchType = Sd_Util_CompareSockAddrPort(
      multicastEndpointAddrPtr, &localAddr, localAddrState);                                                            /* SBSW_SD_VALID_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchType(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_SizeOfMulticastSoConIdType MulticastSoConIdIdx,
  SD_P2VAR(Sd_LocalRemoteMatchTypeType) RemoteMatchTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SockAddrContainerType remoteAddr;
  uint8 remoteAddrState;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the configured remote IP address. */
  retVal = Sd_SoAd_GetRemoteAddr(Sd_GetMulticastSoConId(MulticastSoConIdIdx), &remoteAddr);                             /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(retVal == E_OK)
  {
    /* #100 Calculate the state of the remote address. */
    remoteAddrState = Sd_StateClient_FindBestMatchLocalRemoteSoConCalcAddrState(&remoteAddr);                           /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Compare the remote address with the configured value and calculate a match type. */
    RemoteMatchTypePtr->RemoteIpMatchType = Sd_Util_CompareSockAddrIp(
      Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx), &remoteAddr, remoteAddrState);                             /* SBSW_SD_VALID_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    RemoteMatchTypePtr->RemotePortMatchType = Sd_Util_CompareSockAddrPort(
      Sd_GetAddrServerUdpEndpointAddrOfClientDyn(clientIdx), &remoteAddr, remoteAddrState);                             /* SBSW_SD_VALID_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchPrio()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcLocalMatchPrio(
  SD_P2CONST(Sd_LocalRemoteMatchTypeType) MatchTypePtr,
  SD_P2VAR(uint8) LocalMatchPrioPtr,
  SD_P2VAR(uint8) RemoteMatchPrioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean localMatch = FALSE;
  uint8 initialLocalMatchPrio = *LocalMatchPrioPtr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the match priority for the local IP address. */
  if((MatchTypePtr->LocalIpMatchType == SD_MATCH_TRUE) && (MatchTypePtr->LocalPortMatchType == SD_MATCH_TRUE))
  {
    *LocalMatchPrioPtr = 4u;                                                                                            /* SBSW_SD_VALID_API_POINTER */
    localMatch = TRUE;
  }
  else if((MatchTypePtr->LocalIpMatchType == SD_MATCH_TRUE) && (MatchTypePtr->LocalPortMatchType == SD_MATCH_ANY))
  {
    if(*LocalMatchPrioPtr <= 3u)
    {
      *LocalMatchPrioPtr = 3u;                                                                                          /* SBSW_SD_VALID_API_POINTER */
      localMatch = TRUE;
    }
  }
  else if((MatchTypePtr->LocalIpMatchType == SD_MATCH_ANY) && (MatchTypePtr->LocalPortMatchType == SD_MATCH_TRUE))
  {
    if(*LocalMatchPrioPtr <= 2u)
    {
      *LocalMatchPrioPtr = 2u;                                                                                          /* SBSW_SD_VALID_API_POINTER */
      localMatch = TRUE;
    }
  }
  else if((MatchTypePtr->LocalIpMatchType == SD_MATCH_ANY) && (MatchTypePtr->LocalPortMatchType == SD_MATCH_ANY))
  {
    if(*LocalMatchPrioPtr <= 1u)
    {
      *LocalMatchPrioPtr = 1u;                                                                                          /* SBSW_SD_VALID_API_POINTER */
      localMatch = TRUE;
    }
  }
  else
  {
    /* The socket connections do not match. */
  }

  /* #20 Check if the priority of the local match could be improved. */
  if(*LocalMatchPrioPtr > initialLocalMatchPrio)
  {
    /* #200 Reset the remote priority in order to calculate it again for the new socket connection. */
    *RemoteMatchPrioPtr = 0u;                                                                                           /* SBSW_SD_VALID_API_POINTER */
  }

  return localMatch;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchPrio()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_FindBestMatchLocalRemoteSoConCalcRemoteMatchPrio(
  SD_P2CONST(Sd_LocalRemoteMatchTypeType) MatchTypePtr,
  SD_P2VAR(uint8) RemoteMatchPrioPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean betterMatchFound = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Calculate the match priority for the remote IP address. */
  if((MatchTypePtr->RemoteIpMatchType == SD_MATCH_TRUE) && (MatchTypePtr->RemotePortMatchType == SD_MATCH_TRUE))
  {
    *RemoteMatchPrioPtr = 4u;                                                                                           /* SBSW_SD_VALID_API_POINTER */
    betterMatchFound = TRUE;
  }
  else if((MatchTypePtr->RemoteIpMatchType == SD_MATCH_TRUE) && (MatchTypePtr->RemotePortMatchType == SD_MATCH_ANY))
  {
    if(*RemoteMatchPrioPtr < 3u)
    {
      *RemoteMatchPrioPtr = 3u;                                                                                         /* SBSW_SD_VALID_API_POINTER */
      betterMatchFound = TRUE;
    }
  }
  else if((MatchTypePtr->RemoteIpMatchType == SD_MATCH_ANY) && (MatchTypePtr->RemotePortMatchType == SD_MATCH_TRUE))
  {
    if(*RemoteMatchPrioPtr < 2u)
    {
      *RemoteMatchPrioPtr = 2u;                                                                                         /* SBSW_SD_VALID_API_POINTER */
      betterMatchFound = TRUE;
    }
  }
  else if((MatchTypePtr->RemoteIpMatchType == SD_MATCH_ANY) && (MatchTypePtr->RemotePortMatchType == SD_MATCH_ANY))
  {
    if(*RemoteMatchPrioPtr < 1u)
    {
      *RemoteMatchPrioPtr = 1u;                                                                                         /* SBSW_SD_VALID_API_POINTER */
      betterMatchFound = TRUE;
    }
  }
  else
  {
    /* The socket connections do not match. */
  }

  return betterMatchFound;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_StateClient_ReleaseCeg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_ReleaseCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(clientIdx);
  Sd_ConsumedEventGroupStateMachineType consumedEventgroupState = SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED;

  /* ----- Implementation ----------------------------------------------- */

  /* #20 Check if the consumed eventgroup was released by BswM. */
  /*lint -e655 */
  if(((Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx) & SD_CONSUMED_EVENTGROUP_STATE_MASK) != SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED) &&
    (Sd_GetServiceModeRequestOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_RELEASED)) /*lint +e655 */
  {
    /* #200 The eventgroup was set from requested to released, send a StopSubscribe message. */
    Sd_Util_AddSubscribeEntryToList(ConsumedEventgroupIdx, FALSE, 0u);
  }
  /* #30 Otherwise, inform the BswM about the state change. */
  else
  {
    BswM_Sd_ConsumedEventGroupCurrentState(Sd_GetHandleIdOfConsumedEventgroup(ConsumedEventgroupIdx),
      SD_CONSUMED_EVENTGROUP_DOWN);

    /* #300 Check if the consumed eventgroup is released because of the reception of a SubscribeEventgroupNack entry. */
    if(Sd_GetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CLIENT_EVENT_EVENTGROUP_NACK)
    {
      /* #3000 Report DEM if a NACK was received. */
      Sd_Util_ReportDemEvent(Sd_GetENackRecvIdOfInstance(instanceIdx));
      Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

      /* #3001 Check if the next received multicast OfferService should lead to the transmission of a
       *       StopSubscribeEventgroup-SubscribeEventgroup sequence. */
      if(Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT_MULTI_OFFER)
      {
        consumedEventgroupState = SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED_AFTER_MULTI_OFFER_NACK;
      }
    }
    /* #301 Otherwise, the timer of the consumed eventgroup expired. */
    else
    {
      /* #3010 Trigger a subscription. */
      Sd_SetTriggerSubscriptionOfConsumedEventgroupDyn(ConsumedEventgroupIdx, TRUE);                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  /* #40 Reset the state of the eventgroup. */
  Sd_SetSoConMarkedForClosureOfConsumedEventgroupDyn(ConsumedEventgroupIdx, TRUE);                                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_StateClient_UpdateCeg(ConsumedEventgroupIdx, consumedEventgroupState);
  Sd_SetCurrentStateOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_DOWN);                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
}

/**********************************************************************************************************************
 *  Sd_StateClient_Update()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_Update(
  Sd_SizeOfClientType ClientIdx,
  Sd_ClientStateMachineType NewState,
  boolean ResetTimeToTriggerSend)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the new state of the state machine. */
  Sd_SetStateMachineOfClientDyn(ClientIdx, NewState);                                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Set a timer event and mark state machine of client for execution. */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(ClientIdx));

  if(ResetTimeToTriggerSend == TRUE)
  {
    /* #200 Reset the TimeToTriggerSend. */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                     /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }
}

/**********************************************************************************************************************
 *  Sd_StateClient_UpdateCeg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_StateClient_UpdateCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  Sd_ConsumedEventGroupStateMachineType NewState)
{
  Sd_ClientIdxOfConsumedEventgroupType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the new state of the state machine. */
  Sd_SetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx, NewState);                                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Set a timer event and mark state machine of client for execution. */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(clientIdx));
}

/**********************************************************************************************************************
 *  Sd_StateClient_UnconfigureCeg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_StateClient_UnconfigureCeg(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean AbortFlag,
  boolean ResetEndpointInfo)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Unconfigure TCP configuration. */
  if(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx));
    (void)SoAd_CloseSoCon(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx), AbortFlag);
    Sd_SetTcpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  /* #20 Unconfigure UDP configuration. */
  if(Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx));
    (void)SoAd_CloseSoCon(Sd_GetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx), AbortFlag);
    Sd_SetUdpSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  /* #30 Unconfigure multicast configuration. */
  if(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
  {
    (void)Sd_Util_DisableRouting((Sd_SizeOfRoutingGroupType)Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(ConsumedEventgroupIdx));
    (void)Sd_StateClient_ReleaseIpAddrAssignment(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx));
    (void)SoAd_CloseSoCon(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx),
#if(SD_SET_REM_ADDR_OF_CLIENT_RX_MULTICAST_SOCON == STD_ON)
      AbortFlag);
#else
      FALSE);
#endif
    Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SOAD_INV_SO_CON_ID);                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  if(Sd_IsMulticastEndpointAddrUsedOfConsumedEventgroup(ConsumedEventgroupIdx) && (ResetEndpointInfo == TRUE))
  {
    (Sd_GetAddrMulticastEndpointAddr(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(ConsumedEventgroupIdx)))->family = SOAD_AF_INVALID; /* SBSW_SD_API_ARGUMENT_IDX */
  }

  Sd_SetSoConMarkedForClosureOfConsumedEventgroupDyn(ConsumedEventgroupIdx, FALSE);                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
}

/**********************************************************************************************************************
 *  Sd_StateClient_LocalIpAlreadyConfigured()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_LocalIpAlreadyConfigured(
  SD_P2CONST(Sd_SockAddrContainerType) MulticastAddressPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_IpAddrRequestIterType ipAddressRequestIdx;
  Std_ReturnType retVal;
  Sd_SockAddrContainerType localAddr;
  boolean localIpConfigured = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  for(ipAddressRequestIdx = 0u; ipAddressRequestIdx < Sd_GetSizeOfIpAddrRequest(); ipAddressRequestIdx++)
  {
    /* #10 Get the configured local IP address. */
    retVal = Sd_SoAd_GetLocalAddr(Sd_GetSoConIdOfIpAddrRequest(ipAddressRequestIdx), &localAddr);                       /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #20 Check if the local address is already configured. */
    /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_OK) &&
      (Sd_Util_CompareSockAddrIp(&localAddr, MulticastAddressPtr, SOAD_SOCON_IP_SET_PORT_SET) == SD_MATCH_TRUE))        /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_PASSING_API_POINTER */
    {
      /* #200 The multicast IP address is already configured. */
      localIpConfigured = TRUE;
      break;
    }
  }

  return localIpConfigured;
}

/**********************************************************************************************************************
 *  Sd_StateClient_RequestIpAddrAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_RequestIpAddrAssignment(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) MulticastAddrPtr,
  boolean PerformRequest)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  Sd_SizeOfIpAddrRequestType ipAddrRequestIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the corresponding local IP address request count. */
  for(ipAddrRequestIdx = 0u; ipAddrRequestIdx < Sd_GetSizeOfIpAddrRequest(); ipAddrRequestIdx++)
  {
    if(Sd_GetSoConIdOfIpAddrRequest(ipAddrRequestIdx) == SoConId)
    {
      retVal = E_OK;

      /* #100 Check if the IP address is already requested. */
      if(((!Sd_IsPortSet(Sd_GetPortSetIdxOfIpAddrRequest(ipAddrRequestIdx))) ||
        (Sd_GetRequestCnt(Sd_GetRequestCntIdxOfIpAddrRequest(ipAddrRequestIdx)) == 0u)) &&
        (PerformRequest == TRUE))
      {
        /* #1000 The multicast address and port have to be requested. */
        Sd_SockAddrContainerType defaultRouter;

        /* Create an unspecified address for the default router and net mask. */
        uint8 netmaskCidr = 0u;
        defaultRouter.family = MulticastAddrPtr->family;
        defaultRouter.data[0u] = 0u;                                                                                    /* SBSW_SD_IP_ADDR_SIZE */
        defaultRouter.data[1u] = 0u;                                                                                    /* SBSW_SD_IP_ADDR_SIZE */
        defaultRouter.data[2u] = 0u;                                                                                    /* SBSW_SD_IP_ADDR_SIZE */
        defaultRouter.data[3u] = 0u;                                                                                    /* SBSW_SD_IP_ADDR_SIZE */
        defaultRouter.port = 0u;

        /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
        retVal = SoAd_RequestIpAddrAssignment(SoConId, SOAD_IPADDR_ASSIGNMENT_STATIC,
          (SD_P2VAR(SoAd_SockAddrType))MulticastAddrPtr, netmaskCidr, (SD_P2VAR(SoAd_SockAddrType))&defaultRouter);     /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */
      }

      if(retVal == E_OK)
      {
        /* #1001 Increment the request counter. */
        Sd_IncRequestCnt(Sd_GetRequestCntIdxOfIpAddrRequest(ipAddrRequestIdx));                                         /* SBSW_SD_CSL03 */
        Sd_SetPortSet(Sd_GetPortSetIdxOfIpAddrRequest(ipAddrRequestIdx), TRUE);                                         /* SBSW_SD_CSL03 */
      }

      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_ReleaseIpAddrAssignment()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Std_ReturnType, SD_CODE) Sd_StateClient_ReleaseIpAddrAssignment(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  Sd_SizeOfIpAddrRequestType ipAddrRequestIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search for the request count of the given socket connection index. */
  for(ipAddrRequestIdx = 0u; ipAddrRequestIdx < Sd_GetSizeOfIpAddrRequest(); ipAddrRequestIdx++)
  {
    if(Sd_GetSoConIdOfIpAddrRequest(ipAddrRequestIdx) == SoConId)
    {
      retVal = E_OK;

      /* #100 Check if the IP address is also assigned by another client. */
      if(Sd_GetRequestCnt(Sd_GetRequestCntIdxOfIpAddrRequest(ipAddrRequestIdx)) == 1u)
      {
        if(!Sd_IsStaticIpConfigurationOfIpAddrRequest(ipAddrRequestIdx))
        {
          /* #1000 The multicast address is only requested by a single client. Release the request. */
          retVal = SoAd_ReleaseIpAddrAssignment(SoConId);
        }
      }

      /* #101 Reset the port set configuration. */
      if(!Sd_IsStaticPortConfigurationOfIpAddrRequest(ipAddrRequestIdx))
      {
        Sd_SetPortSet(Sd_GetPortSetIdxOfIpAddrRequest(ipAddrRequestIdx), FALSE);                                        /* SBSW_SD_CSL03 */
      }

      /* #102 Decrement the request counter. (Even if the SoAd_ReleaseIpAddrAssignment fails). */
      Sd_DecRequestCnt(Sd_GetRequestCntIdxOfIpAddrRequest(ipAddrRequestIdx));                                           /* SBSW_SD_CSL03 */

      break;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_StateClient_EntryListContainsSubscribe()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_StateClient_EntryListContainsSubscribe(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SendEntryIterType sendEntryIdx;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx));
  boolean ContainsSubscribe = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check all possible entries. */
  for(sendEntryIdx = Sd_GetSendEntryStartIdxOfInstanceDyn(instanceIdx);
    sendEntryIdx != SD_NO_SENDENTRYENDIDXOFINSTANCEDYN;
    sendEntryIdx = Sd_GetSendEntryNextIdxOfSendEntry(sendEntryIdx))
  {
    /* #100 Check if the entry is a Subscribe-Entry for the given ConsumedEventGroup. */
    if((Sd_GetEntryTypeOfSendEntry(sendEntryIdx) == SD_ENTRY_SUBSCRIBE_EVENTGROUP) &&
      (ConsumedEventgroupIdx == Sd_GetConsumedEventgroupIdxOfSendEntry(sendEntryIdx)))
    {
      ContainsSubscribe = TRUE;
      break;
    }
  }

  return ContainsSubscribe;
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntry(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx;
  uint16 clientStartIdx, clientEndIdx;
  Sd_EntryType rxEntryType;
  uint16 rxServiceId;
  uint16 rxInstanceId;
  uint8 rxMajorVersion;
  uint32 rxMinorVersion;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the header fields of the entry. */
  SD_GET_ENTRY_TYPE(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry /* + SD_ENTRY_TYPE_OFFSET */, rxEntryType);
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_SERVICEID_OFFSET, rxServiceId);
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INSTANCEID_OFFSET, rxInstanceId);
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_MAJORVERSION_OFFSET, rxMajorVersion);

  /* #20 Get all services with the corresponding ServiceId */
  clientStartIdx = (uint16)Sd_GetClientStartIdxOfInstance(InstanceIdx);
  clientEndIdx = (uint16)Sd_GetClientEndIdxOfInstance(InstanceIdx);

  /* #30 Search for the matching client(s). */
  Sd_Util_GetServices(rxServiceId, Sd_Util_GetClientServiceId, &clientStartIdx, &clientEndIdx);                         /* SBSW_SD_REFERENCE_OF_VARIABLE */

  /* #40 Iterate over all matching clients to find the one corresponding to the entry. */
  for(clientIdx = (Sd_SizeOfClientType)clientStartIdx; clientIdx < (Sd_SizeOfClientType)clientEndIdx; clientIdx++)
  {
    /* #400 Check if the InstanceId and MajorVersion match. */
    if((rxInstanceId == Sd_GetInstanceIdOfClient(clientIdx)) &&
      (rxMajorVersion == Sd_GetMajorVersionOfClient(clientIdx)))
    {
      /* #4000 Differentiate between entry format type 1 or 2 */
      if(rxEntryType == SD_ENTRY_OFFER_SERVICE)
      {
        /* #40000 Entry format type 1 - OfferService.
         *        Process the entry even if the service is not available. */

        SD_GET_UINT32(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY1_MINORVERSION_OFFSET, rxMinorVersion);

        /* #40001 Check the minor version fits to the configuration. */
        if((rxMinorVersion == Sd_GetMinorVersionOfClient(clientIdx)) || Sd_IsMinorVersionWildcardOfClient(clientIdx))
        {
          /* #400010 Process the received OfferService entry. */
          Sd_RxClient_ProcessEntryOffer(RxMessageInfoPtr, IndexOfEntry, clientIdx);                                     /* SBSW_SD_PASSING_API_POINTER */
        }
      }
      else
      {
        /* #40002 Entry format type 2 - SubscribeEventgroup(N)Ack.
         *        Process the acknowledge only if no reboot of the remote server was detected. */
        if(RxMessageInfoPtr->RebootDetected != TRUE)
        {
          Sd_RxClient_ProcessEntryAcknowledge(RxMessageInfoPtr, IndexOfEntry, clientIdx);                               /* SBSW_SD_PASSING_API_POINTER */
        }
      }
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryOffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryOffer(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_AttachedOptionsType attachedOptions;
  Sd_ConfigOptionStringType rxConfigOptionPtrArray[Sd_GetMaxNrOptionsPerEntry() + 1u];

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0314 1 */ /* MD_Sd_Dir-1.1_0314 */
  IpBase_Fill((SD_P2VAR(void))rxConfigOptionPtrArray, 0u, sizeof(rxConfigOptionPtrArray));                              /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_IPBASE_FILL */
  attachedOptions.EndpointAddrUdp.family = SOAD_AF_INVALID;
  attachedOptions.EndpointAddrTcp.family = SOAD_AF_INVALID;
  attachedOptions.ConfigOptionPtrArrayPtr = rxConfigOptionPtrArray;

  /* #10 Process the endpoints of the OfferService message. */
  optionsRetVal = Sd_RxClient_ProcessEntryOfferOptionRuns(RxMessageInfoPtr, IndexOfEntry, ClientIdx, &attachedOptions); /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(optionsRetVal == SD_OPTIONS_OK)
  {
    /* #200 Check if the attached endpoint addresses are part of the subnet. */
    optionsRetVal = Sd_Rx_CheckSubnets(
      Sd_IsUdpSoConUsedOfClient(ClientIdx) ? Sd_GetUdpSoConStartIdxOfClient(ClientIdx) : Sd_GetSizeOfUdpSoCon(),
      Sd_IsTcpSoConIdUsedOfClient(ClientIdx) ? Sd_GetTcpSoConIdStartIdxOfClient(ClientIdx) : Sd_GetSizeOfTcpSoConId(),
      &attachedOptions);                                                                                                /* SBSW_SD_REFERENCE_OF_VARIABLE */
  }

  if(optionsRetVal == SD_OPTIONS_OK)
  {
    /* #300 Check the attached configuration options by a user callout. */
    optionsRetVal = Sd_RxClient_CheckConfigOptionByCbk(
      ClientIdx,
      (RxMessageInfoPtr->MulticastMessage == TRUE) ? Sd_GetMulticastRxPduIdOfInstance(instanceIdx) : Sd_GetUnicastRxPduIdOfInstance(instanceIdx),
      SD_ENTRY_OFFER_SERVICE,
      rxConfigOptionPtrArray);                                                                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */
  }

  if(optionsRetVal == SD_OPTIONS_OK)
  {
    /* #400 Save the address of the server. */
    Sd_SetAddressStorageServerIdxOfClientDyn(ClientIdx, RxMessageInfoPtr->AddressStorageIdx);                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    /* #401 Check the TTL of the received entry. */
    if(Sd_GetOfferedTTLOfClientDyn(ClientIdx) == 0u)
    {
      /* #4010 Received SD_ENTRY_STOP_OFFER_SERVICE message. Save the event. */
      Sd_SetEventRxOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_STOP_OFFER);                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_Util_TriggerStateMachineRun(instanceIdx);
    }
    else
    {
      /* #4011 Received SD_ENTRY_OFFER_SERVICE message. */

      /* #4012 Save the attached endpoint options. */
      Sd_Util_CopySockAddr(Sd_GetAddrServerUdpEndpointAddrOfClientDyn(ClientIdx), &attachedOptions.EndpointAddrUdp);    /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      Sd_Util_CopySockAddr(Sd_GetAddrServerTcpEndpointAddrOfClientDyn(ClientIdx), &attachedOptions.EndpointAddrTcp);    /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

      /* #4013 Check if a reboot occurred. */
      if(RxMessageInfoPtr->RebootDetected == TRUE)
      {
        /* #40130 Handle reboot as StopOffer -> Offer sequence. */
        Sd_SetEventRxOfClientDyn(ClientIdx, (RxMessageInfoPtr->MulticastMessage == TRUE) ?                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
          SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_MULTI : SD_CLIENT_EVENT_SERVICE_STOP_OFFER_OFFER_UNI);
      }
      else
      {
        /* #40131 Otherwise, save the received OfferService message as event. */
        Sd_SetEventRxOfClientDyn(ClientIdx, (RxMessageInfoPtr->MulticastMessage == TRUE) ?                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
          SD_CLIENT_EVENT_SERVICE_OFFER_MULTI : SD_CLIENT_EVENT_SERVICE_OFFER_UNI);
      }

      Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_Util_TriggerStateMachineRun(instanceIdx);
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryOfferOptionRuns()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_ProcessEntryOfferOptionRuns(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_NOT_OK;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  uint32 rxTTL;
  uint8 index1stOption, index2ndOption;
  uint8 nr1stOptions, nr2ndOptions;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Parse OfferService entry. */
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX1_OFFSET, index1stOption);
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX2_OFFSET, index2ndOption);
  SD_GET_NROFOPT(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry, nr1stOptions, nr2ndOptions);
  SD_GET_UINT24(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_TTL_OFFSET, rxTTL);

  /* #20 Save the offered TTL of the server. */
  Sd_SetOfferedTTLOfClientDyn(ClientIdx, rxTTL);                                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #30 Process the corresponding option array.
   *     Check if all attached endpoint options are valid and there exist no conflicts. */

   /* #40 Check if a first option run is available.*/
  if(nr1stOptions != 0u)
  {
    /* #400 Process first option run. */
    optionsRetVal = Sd_RxClient_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index1stOption, nr1stOptions,
      Sd_GetEMalformedMsgIdOfInstance(instanceIdx), Sd_GetSizeOfConsumedEventgroup(), AttachedOptionsPtr);              /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_PASSING_API_POINTER */
  }

  /* #50 Check if a second option run is available.*/
  if((nr2ndOptions != 0u) && ((nr1stOptions == 0u) || (optionsRetVal == SD_OPTIONS_OK)))
  {
    /* #500 Process second option run. */
    optionsRetVal = Sd_RxClient_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index2ndOption, nr2ndOptions,
      Sd_GetEMalformedMsgIdOfInstance(instanceIdx), Sd_GetSizeOfConsumedEventgroup(), AttachedOptionsPtr);              /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_PASSING_API_POINTER */
  }
  /* #60 Otherwise, check if both option runs are empty and the entry is a StopOfferService entry.*/
  else if((nr1stOptions == 0u) && (nr2ndOptions == 0u) && (rxTTL == 0u))                                               /* PRQA S 2995 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
  {
    /* #600 In case no first or second option run exists, only SD_ENTRY_STOP_OFFER_SERVICE messages are allowed. */
    optionsRetVal = SD_OPTIONS_OK;
  }
  /* #70 Otherwise, nothing to process.*/
  else
  {
    /* #700 Entry does not contain a second option run. Keep result of first option run. */
  }

  /* #80 Check if all required endpoint options are present. */
  if((optionsRetVal == SD_OPTIONS_OK) &&
    ((Sd_IsUdpSoConUsedOfClient(ClientIdx) && (AttachedOptionsPtr->EndpointAddrUdp.family == SOAD_AF_INVALID)) ||
    (Sd_IsTcpSoConIdUsedOfClient(ClientIdx) && (AttachedOptionsPtr->EndpointAddrTcp.family == SOAD_AF_INVALID))))
  {
    /* #800 Not all required endpoint options are present. Reject message. */
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryAcknowledge()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryAcknowledge(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  uint16 IndexOfEntry,
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 1 */ /* MD_Sd_Rule-2.2_2981 */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_NOT_OK;
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;
  Sd_ConfigOptionStringType rxConfigOptionPtrArray[Sd_GetMaxNrOptionsPerEntry() + 1u];
  Sd_AttachedOptionsType attachedOptions;
  uint32 rxTTL;
  uint16 rxEventGroupId;
  uint8 index1stOption, index2ndOption;
  uint8 nr1stOptions, nr2ndOptions;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 0314 1 */ /* MD_Sd_Dir-1.1_0314 */
  IpBase_Fill((SD_P2VAR(void))rxConfigOptionPtrArray, 0u, sizeof(rxConfigOptionPtrArray));                              /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_IPBASE_FILL */
  attachedOptions.EndpointAddrUdp.family = SOAD_AF_INVALID;
  attachedOptions.EndpointAddrTcp.family = SOAD_AF_INVALID;
  attachedOptions.ConfigOptionPtrArrayPtr = rxConfigOptionPtrArray;

  /* #10 Parse SubscribeEventgroupAck entry. */
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX1_OFFSET, index1stOption);
  SD_GET_UINT8(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_INDEX2_OFFSET, index2ndOption);
  SD_GET_NROFOPT(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry, nr1stOptions, nr2ndOptions);
  SD_GET_UINT24(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY_TTL_OFFSET, rxTTL);
  SD_GET_UINT16(RxMessageInfoPtr->PduInfoPtr, IndexOfEntry + SD_ENTRY2_EVENTGROUPID_OFFSET, rxEventGroupId);

  /* #20 Iterate trough each eventgroup to find the corresponding one. */
  for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(ClientIdx);
    consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(ClientIdx);
    consumedEventgroupIdx++)
  {
    if((rxEventGroupId == Sd_GetEventGroupIdOfConsumedEventgroup(consumedEventgroupIdx)) &&
      (Sd_GetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_REQUESTED))
    {
      /* #200 Found the corresponding eventgroup, update the acknowledged TTL. */
      Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(consumedEventgroupIdx, rxTTL);                                       /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

      /* #201 Process the corresponding option array.
       *      Check if all attached endpoint options are valid and there exist no conflicts. */

      /* #202 Check if a first option run is available.*/
      if(nr1stOptions != 0u)
      {
        /* #2020 Process first option run. */
        optionsRetVal = Sd_RxClient_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index1stOption, nr1stOptions,
          Sd_GetEMalformedMsgIdOfInstance(instanceIdx), consumedEventgroupIdx, &attachedOptions);                       /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      }

      /* #300 Check if a second option run is available.*/
      if((nr2ndOptions != 0u) && ((nr1stOptions == 0u) || (optionsRetVal == SD_OPTIONS_OK)))
      {
        /* #3000 Process second option run. */
        optionsRetVal = Sd_RxClient_ProcessOptionRun(RxMessageInfoPtr->PduInfoPtr, index2ndOption, nr2ndOptions,
          Sd_GetEMalformedMsgIdOfInstance(instanceIdx), consumedEventgroupIdx, &attachedOptions);                       /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
      }
      /* #400 Otherwise, check if both option runs are empty.*/
      else if((nr1stOptions == 0u) && (nr2ndOptions == 0u))                                                             /* PRQA S 2995 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
      {
        /* #4000 In case no first or second option run exists, only SD_ENTRY_SUBSCRIBE_EVENTGROUP_(N)ACK messages are allowed. */
        optionsRetVal = SD_OPTIONS_OK;
      }
      /* #500 Otherwise, nothing to process.*/
      else
      {
        /* #5000 No second option run present. Keep result of first option run. */
      }

      /* #600 Check if all required endpoint options are present. */
      if((optionsRetVal == SD_OPTIONS_OK) &&
        (attachedOptions.EndpointAddrUdp.family == SOAD_AF_INVALID) &&
        Sd_ConsumedEventGroupUsesMulticast(consumedEventgroupIdx) &&
        (!Sd_ConsumedEventGroupUsesUdp(consumedEventgroupIdx)))
      {
        /* #6000 Missing multicast endpoint is not allowed for pure multicast consumed eventgroups. Ignore message. */
        optionsRetVal = SD_OPTIONS_NOT_OK;
      }

      if(optionsRetVal == SD_OPTIONS_OK)
      {
        /* #7000 Check the attached configuration options by a user callout. */
        optionsRetVal = Sd_RxClient_CheckConfigOptionByCbk(
          ClientIdx,
          (RxMessageInfoPtr->MulticastMessage == TRUE) ? Sd_GetMulticastRxPduIdOfInstance(instanceIdx) : Sd_GetUnicastRxPduIdOfInstance(instanceIdx),
          SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK,
          rxConfigOptionPtrArray);                                                                                      /* SBSW_SD_REFERENCE_OF_VARIABLE */
      }

      if(optionsRetVal == SD_OPTIONS_OK)
      {
        /* #8000 The attached options are valid. Save the received event. */
        Sd_RxClient_ProcessEntryAcknowledgeSave(consumedEventgroupIdx, &attachedOptions.EndpointAddrUdp, rxTTL);        /* SBSW_SD_REFERENCE_OF_VARIABLE */
      }

      /* #900 Found the corresponding eventgroup, stop searching. */
      break;
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxClient_CheckConfigOptionByCbk()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_CheckConfigOptionByCbk(
  Sd_SizeOfClientType ClientIdx,
  PduIdType RxPduId,
  Sd_EntryType RxEntryType,
  SD_P2CONST(Sd_ConfigOptionStringType) RxConfigOptionPtrArrayPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the client contains a configured user callout for checking capability records. */
  if(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfClient(ClientIdx) != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT)
  {
    Sd_ConfigOptionStringType configOptionPtrArray[3u] = { NULL_PTR, NULL_PTR, NULL_PTR };

    /* #100 Add configuration options of hostname and capability records to the configuration option pointer array. */
    Sd_Rx_FillConfigOptionPtrArray(configOptionPtrArray,
      Sd_GetCapabilityRecordStartIdxOfInstance(Sd_GetInstanceIdxOfClient(ClientIdx)),
      Sd_GetCapabilityRecordStartIdxOfClient(ClientIdx),
      SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT);                                                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Call application to verify configuration options of received message. */
    if(TRUE != Sd_GetCapabilityRecordFunctionCalloutPtr(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfClient(ClientIdx))(
      RxPduId,
      (uint8)RxEntryType,
      Sd_GetServiceIdOfClient(ClientIdx),
      Sd_GetInstanceIdOfClient(ClientIdx),
      Sd_GetMajorVersionOfClient(ClientIdx),
      Sd_GetMinorVersionOfClient(ClientIdx),
      RxConfigOptionPtrArrayPtr,
      configOptionPtrArray))                                                                                            /* SBSW_SD_FUNCTION_PTR_CALL */
    {
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessEntryAcknowledgeSave()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_RxClient_ProcessEntryAcknowledgeSave(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2CONST(Sd_SockAddrContainerType) MulticastEndpointAddrPtr,
  uint32 RxTTL)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Save the attached endpoint option. */
  if(Sd_IsMulticastEndpointAddrUsedOfConsumedEventgroup(ConsumedEventgroupIdx))
  {
    Sd_Util_CopySockAddr(
      Sd_GetAddrMulticastEndpointAddr(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(ConsumedEventgroupIdx)),
      MulticastEndpointAddrPtr);                                                                                        /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  }

  /* #20 Check the TTL of the received subscription in order to differentiate ACK and NACK entries. */
  if(RxTTL == 0u)
  {
    /* #200 Received SD_ENTRY_SUBSCRIBE_EVENTGROUP_NACK. Save the event. */
    Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NACK);                         /* SBSW_SD_API_ARGUMENT_IDX */

    /* #201 Save the RxIndicationCount of the current frame. */
    Sd_SetRxIndicationCountOfConsumedEventgroupDyn(ConsumedEventgroupIdx, Sd_RxIndicationCount);                        /* SBSW_SD_API_ARGUMENT_IDX */
  }
  else
  {
    /* #202 Received SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK message. */

    /* #203 Check if there is no pending event,
     *      or if the pending event is a SubscribeEventgroupNack entry received in the same message. */
    if((Sd_GetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CLIENT_EVENT_EVENTGROUP_NONE) ||
      ((Sd_GetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == SD_CLIENT_EVENT_EVENTGROUP_NACK) &&
      (Sd_GetRxIndicationCountOfConsumedEventgroupDyn(ConsumedEventgroupIdx) == Sd_RxIndicationCount)))
    {
      Sd_ConsumedEventGroupStateMachineType consumedEventgroupState =
        Sd_GetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx);

      /* #2030 Check if the consumed eventgroup expects an ACK message. */
      if((consumedEventgroupState & SD_CONSUMED_EVENTGROUP_STATE_MASK) != SD_CONSUMED_EVENTGROUP_STATE_UNSUBSCRIBED) /*lint !e655 */
      {
        /* #20300 Save the event. */
        Sd_SetEventOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_ACK);                      /* SBSW_SD_API_ARGUMENT_IDX */

        /* #20301 Change the state of the consumed eventgroup to REGISTRATION_SENT.
         *        This will trigger processing of the ACK in the next MainFunction. */
        Sd_SetStateMachineOfConsumedEventgroupDyn(ConsumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_STATE_REGISTRATION_SENT); /* SBSW_SD_API_ARGUMENT_IDX */
      }
    }
  }

  /* #30 Trigger execution of state machines. */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx), TRUE);    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
  Sd_Util_TriggerStateMachineRun(Sd_GetInstanceIdxOfClient(Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx)));
}

/**********************************************************************************************************************
 *  Sd_RxClient_ProcessOptionRun()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_RxClient_ProcessOptionRun(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  uint8 NrOfOptions,
  Sd_Dem_EventIdType EMalformedMsgId,
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  uint8 currentOption = IndexOfOption;
  Sd_OptionType optionType;
  Sd_L4ProtocolType optionL4Proto = SD_L4PROTOCOL_NONE;
  uint16 addrType;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Stop processing of the message if the header indexes more options than attached. */
  if(Sd_GetNrOfOptions() < ((Sd_NrOfOptionsType)IndexOfOption + (Sd_NrOfOptionsType)NrOfOptions))
  {
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  /* #20 Process consecutive options. */
  while((optionsRetVal == SD_OPTIONS_OK) && ((IndexOfOption + NrOfOptions) > currentOption))
  {
    addrType = SOAD_AF_INVALID;

    /* #200 Read the option information. */
    SD_GET_OPTION_TYPE(PduInfoPtr, Sd_GetOptionIndex(currentOption), optionType);

    /* #201 Differentiate between configuration and endpoint option. */
    if(optionType == SD_OPTION_CONFIGURATION)
    {
      /* #2010 Configuration option: Check if the option is valid. */
      optionsRetVal = Sd_Rx_CheckConfigOption(
        PduInfoPtr, currentOption, AttachedOptionsPtr->ConfigOptionPtrArrayPtr); /*lint !e655 */                        /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_ATTACHED_OPTIONS_PTR */
    }
    else
    {
      /* #2011 Endpoint option: Read the type values of the options.
       *       Multicast endpoint options are only allowed for SubscribeEventgroup(N)Ack messages. */
      Sd_Rx_GetEndpointOptionParameters(PduInfoPtr, currentOption,
        (boolean)((ConsumedEventgroupIdx == Sd_GetSizeOfConsumedEventgroup()) ? FALSE : TRUE),
        &addrType, &optionL4Proto);                                                                                     /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    }

    /* #202 Read the endpoint options. */
    optionsRetVal |= Sd_Rx_ReadEndpointOptions(
      PduInfoPtr, currentOption, addrType, optionL4Proto, AttachedOptionsPtr); /*lint !e655 */                          /* SBSW_SD_PASSING_API_POINTER */

    currentOption++;
  }

  if(optionsRetVal != SD_OPTIONS_OK)
  {
    /* #203 Report an error if the endpoint configuration was not correct. */
    Sd_Util_ReportDemEvent(EMalformedMsgId);
  }

  return optionsRetVal;
} /* PRQA S 6060 */ /* MD_Sd_STPAR_6060 */

/**********************************************************************************************************************
 *  SHARED FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Sd_Rx_GetReceivingInstance()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_GetReceivingInstance(
  PduIdType RxPduId,
  SD_P2VAR(Sd_SizeOfInstanceType) InstanceIdxPtr,
  SD_P2VAR(SoAd_SoConIdType) RxSoConIdPtr,
  SD_P2VAR(boolean) MulticastMessagePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType tmpInstanceIdx;

  /* ----- Implementation ----------------------------------------------- */
  *InstanceIdxPtr = Sd_GetSizeOfInstance();                                                                             /* SBSW_SD_VALID_API_POINTER */

  /* #10 Search for the corresponding instance. */
  for(tmpInstanceIdx = 0u; tmpInstanceIdx < Sd_GetSizeOfInstance(); tmpInstanceIdx++)
  {
    /* #100 Check if the message was received by the multicast or the unicast RxPdu. */
    if(Sd_GetUnicastRxPduIdOfInstance(tmpInstanceIdx) == RxPduId)
    {
      /* #1000 Message was received by the unicast PDU. */
      *MulticastMessagePtr = FALSE;                                                                                     /* SBSW_SD_VALID_API_POINTER */
      *RxSoConIdPtr = Sd_GetUnicastRxSoConIdOfInstance(tmpInstanceIdx);                                                 /* SBSW_SD_VALID_API_POINTER */
      *InstanceIdxPtr = tmpInstanceIdx;                                                                                 /* SBSW_SD_VALID_API_POINTER */
    }
    else if(Sd_GetMulticastRxPduIdOfInstance(tmpInstanceIdx) == RxPduId)
    {
      /* #1001 Message was received by the multicast PDU. */
      *MulticastMessagePtr = TRUE;                                                                                      /* SBSW_SD_VALID_API_POINTER */
      *RxSoConIdPtr = Sd_GetMulticastRxSoConIdOfInstance(tmpInstanceIdx);                                               /* SBSW_SD_VALID_API_POINTER */
      *InstanceIdxPtr = tmpInstanceIdx;                                                                                 /* SBSW_SD_VALID_API_POINTER */
    }
    else
    {
      /* #1002 The message was received by another instance. Keep searching. */
    }

    /* #101 Stop searching as soon as the receiving instance has been found. */
    if(*InstanceIdxPtr != Sd_GetSizeOfInstance())
    {
      break;
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Util_GetClientServiceId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(uint16, SD_CODE) Sd_Util_GetClientServiceId(
  uint16 Idx)
{
  /* #10 Return the ServiceId of the client. */
  return Sd_GetServiceIdOfClient(Idx);
}

/**********************************************************************************************************************
 *  Sd_Util_GetServerServiceId()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(uint16, SD_CODE) Sd_Util_GetServerServiceId(
  uint16 Idx)
{
  /* #10 Return the ServiceId of the server. */
  return Sd_GetServiceIdOfServer(Idx);
}

/**********************************************************************************************************************
 *  Sd_Util_GetServices()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_GetServices(
  uint16 ServiceId,
  Sd_ServiceIdGetterFctType ServiceIdAccessFuncPtr,
  SD_P2VAR(uint16) ServiceStartIdxPtr,
  SD_P2VAR(uint16) ServiceEndIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 low, high, initialEndIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Save range to search for service. */
  low = *ServiceStartIdxPtr;
  high = (uint16)((*ServiceEndIdxPtr) - 1u);
  initialEndIdx = *ServiceEndIdxPtr;

  /* #20 Invalidate the start and end idx values. */
  *ServiceEndIdxPtr = *ServiceStartIdxPtr;                                                                              /* SBSW_SD_VALID_API_POINTER */

  /* #30 Search for the first service with the given ServiceId. */
  while(low < high)
  {
    uint16 mid = low + ((uint16)(high - low) / 2u);
    uint16 midServiceId = ServiceIdAccessFuncPtr(mid);                                                                  /* SBSW_SD_FUNCTION_PTR_CALL_STATIC */

    if(midServiceId < ServiceId)
    {
      /* Increase the lower limit. */
      low = mid + 1u;
    }
    else if(midServiceId > ServiceId)
    {
      /* Reduce the upper limit. */
      high = (mid != 0u) ? (uint16)(mid - 1u) : 0u;
    }
    else
    {
      /* Found the correct ServiceId. */

      if(low != mid)
      {
        /* Search for the first occurrence. */
        high = mid;
      }
      else
      {
        /* ServiceId matches and full range is scanned. */
        high = mid;
        break;
      }
    }
  }

  /* #40 Check if a matching service was found. */
  if(low == high)
  {
    uint16 tmpIdx = low;

    *ServiceStartIdxPtr = low;                                                                                          /* SBSW_SD_VALID_API_POINTER */
    *ServiceEndIdxPtr = low;                                                                                            /* SBSW_SD_VALID_API_POINTER */

    /* #400 Check how many matching services exist and update the EndIdx. */
    /* PRQA S 3415 1 */ /* MD_Sd_12.4_3415 */
    while((*ServiceEndIdxPtr < initialEndIdx) && (ServiceId == ServiceIdAccessFuncPtr(tmpIdx)))                         /* SBSW_SD_FUNCTION_PTR_CALL_STATIC */
    {
      tmpIdx++;
      (*ServiceEndIdxPtr)++;                                                                                            /* SBSW_SD_VALID_API_POINTER */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_SaveAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfAddressStorageType, SD_CODE) Sd_Rx_SaveAddr(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_SockAddrContainerType) InAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfAddressStorageType addressStorageIdx, savedAddressStorageIdx = Sd_GetSizeOfAddressStorage();

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the address is already saved. */
  for(addressStorageIdx = Sd_GetAddressStorageStartIdxOfInstance(InstanceIdx);
    addressStorageIdx < Sd_GetAddressStorageEndIdxOfInstance(InstanceIdx);
    addressStorageIdx++)
  {
    if((Sd_Util_SockAddrIsEqual(Sd_GetAddrAddrOfAddressStorage(addressStorageIdx), InAddrPtr) == TRUE) &&
      (Sd_GetSessionIdCounterOfAddressStorage(addressStorageIdx) != 0u))                                                /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */ /* SBSW_SD_PASSING_API_POINTER */
    {
      /* #100 The address is already saved. Save index of the address. */
      savedAddressStorageIdx = addressStorageIdx;
      break;
    }
  }

  /* #20 Check if the address has to be saved. */
  if(savedAddressStorageIdx == Sd_GetSizeOfAddressStorage())
  {
    /* #200 Search for the next free slot and save the address. */
    for(addressStorageIdx = Sd_GetAddressStorageStartIdxOfInstance(InstanceIdx);
      addressStorageIdx < Sd_GetAddressStorageEndIdxOfInstance(InstanceIdx);
      addressStorageIdx++)
    {
      if(Sd_GetSessionIdCounterOfAddressStorage(addressStorageIdx) == 0u)
      {
        /* #2000 Save the address and set the session counter to 1. */
        Sd_Util_CopySockAddr(Sd_GetAddrAddrOfAddressStorage(addressStorageIdx), InAddrPtr);                             /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */ /* SBSW_SD_PASSING_API_POINTER */
        Sd_SetSessionIdCounterOfAddressStorage(addressStorageIdx, 1u);                                                  /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetRxUnicastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                                /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetRxMulticastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetRxUnicastFlagsOfAddressStorage(addressStorageIdx, SD_FLAGS_REBOOT_MASK);                                  /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetRxMulticastFlagsOfAddressStorage(addressStorageIdx, SD_FLAGS_REBOOT_MASK);                                /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        savedAddressStorageIdx = addressStorageIdx;
        break;
      }
    }
  }

  if(savedAddressStorageIdx == Sd_GetSizeOfAddressStorage())
  {
    /* #201 Not able to save the additional address.
     *      The amount of manageable destination addresses is configured in Sd/SdConfig/SdInstance/SdMaxNrDestAddr. */
#if(SD_DEV_ERROR_REPORT == STD_ON)
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_RX_INDICATION, SD_E_ADDR_LIST_FULL);
#endif
  }

  return savedAddressStorageIdx;
}

/**********************************************************************************************************************
 *  Sd_Rx_IndexOptionArray()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_IndexOptionArray(
  SD_P2CONST(PduInfoType) PduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  uint32 lengthEntriesArray, lengthOfOptionsArray;
  uint16 lengthOfOption, tmpIndex, startIndexOptionsArray;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Clear the option index. */
  Sd_SetNrOfOptions(0u);                                                                                                /* SBSW_SD_CSL_VAR_ELEM */

  /* #20 read length of the entries and options array. */
  SD_GET_UINT32(PduInfoPtr, SD_HEADER_LENGTH, lengthEntriesArray);
  tmpIndex = (uint16)(SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + lengthEntriesArray);

  SD_GET_UINT32(PduInfoPtr, tmpIndex, lengthOfOptionsArray);
  tmpIndex += SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE;

  startIndexOptionsArray = tmpIndex;

  /* #30 Iterate through all options and generate an index. */
  while((tmpIndex < (startIndexOptionsArray + lengthOfOptionsArray)) && (retVal == E_OK))
  {
    /* #300 Read the option and check if it is valid. */
    retVal = Sd_Rx_CheckOption(PduInfoPtr, tmpIndex, lengthOfOptionsArray, &lengthOfOption);                            /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

    if(retVal == E_OK)
    {
      /* #3000 The option is valid. Check if it could be saved in the OptionIndex. */
      if(Sd_GetNrOfOptions() < Sd_GetSizeOfOptionIndex())
      {
        /* #30000 Add the option to the index. */
        Sd_SetOptionIndex(Sd_GetNrOfOptions(), tmpIndex);                                                               /* SBSW_SD_CSL01 */
        Sd_IncNrOfOptions();                                                                                            /* SBSW_SD_CSL_VAR_ELEM */
        tmpIndex  +=  SD_OPTION_LENGTH_SIZE + SD_OPTION_TYPE_SIZE + lengthOfOption;
      }
      else
      {
        /* #30001 The Sd_OptionIndex is full. Stop reading further options. */
        retVal = E_NOT_OK;
      }
    }
    else
    {
      /* #3001 The option is not valid. Stop processing. */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_CheckOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_CheckOption(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint16 OptionIndex,
  uint32 OptionArrayLength,
  SD_P2VAR(uint16) CoveredOptionLengthPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_OptionType optionType;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the length and the type field are part of the payload. */
  if(PduInfoPtr->SduLength >= (OptionIndex + SD_OPTION_LENGTH_SIZE + SD_OPTION_TYPE_SIZE))
  {
    /* #100 Read the length and the type of the option. */
    SD_GET_UINT16(PduInfoPtr, OptionIndex, *CoveredOptionLengthPtr);                                                    /* SBSW_SD_VALID_API_POINTER */
    SD_GET_OPTION_TYPE(PduInfoPtr, OptionIndex, optionType);

    /* #101 Check if the length of the option is feasible. */
    if((uint16)(SD_OPTION_LENGTH_SIZE + SD_OPTION_TYPE_SIZE + *CoveredOptionLengthPtr) <= OptionArrayLength)
    {
      /* #1010 Check the length of IPv4 endpoint or multicast endpoint options. */
      if(((optionType == SD_OPTION_IPV4_ENDPOINT) ||
        (optionType == SD_OPTION_IPV4_MULTICAST) ||
        (optionType == SD_OPTION_IPV4_SD_ENDPOINT)) &&
        (*CoveredOptionLengthPtr != SD_OPTION_IPV4_COVERED_LENGTH))
      {
        retVal = E_NOT_OK;
      }

      /* #1011 Check the length of IPv6 endpoint or multicast endpoint options. */
      if(((optionType == SD_OPTION_IPV6_ENDPOINT) ||
        (optionType == SD_OPTION_IPV6_MULTICAST) ||
        (optionType == SD_OPTION_IPV6_SD_ENDPOINT)) &&
        (*CoveredOptionLengthPtr != SD_OPTION_IPV6_COVERED_LENGTH))
      {
        retVal = E_NOT_OK;
      }
    }
    else
    {
      retVal = E_NOT_OK;
    }
  }
  else
  {
    *CoveredOptionLengthPtr = 0u;                                                                                       /* SBSW_SD_VALID_API_POINTER */
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_CheckRemoteReboot()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_CheckRemoteReboot(
  SD_P2VAR(Sd_RxMessageInfoType) RxMessageInfoPtr,
  SD_P2CONST(Sd_HeaderType) SdHeaderPtr,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfAddressStorageType addressStorageIdx = RxMessageInfoPtr->AddressStorageIdx;

  /* ----- Implementation ----------------------------------------------- */
  RxMessageInfoPtr->RebootDetected = FALSE;                                                                             /* SBSW_SD_VALID_API_POINTER */

  /* #10 Check if the message was received via unicast or multicast. */
  if(RxMessageInfoPtr->MulticastMessage == TRUE)
  {
    /* #100 Multicast: Check if the device has rebooted. */
    if(((Sd_GetRxMulticastSessionIdOfAddressStorage(addressStorageIdx) > SdHeaderPtr->SessionID) ||
      ((Sd_GetRxMulticastFlagsOfAddressStorage(addressStorageIdx) & SD_FLAGS_REBOOT_MASK) == 0u)) &&
      ((SdHeaderPtr->Flags & SD_FLAGS_REBOOT_MASK) != 0u))
    {
      /* #1000 The remote device has rebooted. */
      RxMessageInfoPtr->RebootDetected = TRUE;                                                                          /* SBSW_SD_VALID_API_POINTER */
      Sd_Rx_HandleRemoteReboot(InstanceIdx, RxMessageInfoPtr);                                                          /* SBSW_SD_PASSING_API_POINTER */

      /* #1001 Reset the unicast Session ID in order to detect the reboot only once. */
      Sd_SetRxUnicastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                                  /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
    }

    /* #101 Update the Session ID and Flags field for multicast messages. */
    Sd_SetRxMulticastSessionIdOfAddressStorage(addressStorageIdx, SdHeaderPtr->SessionID);                              /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
    Sd_SetRxMulticastFlagsOfAddressStorage(addressStorageIdx, SdHeaderPtr->Flags);                                      /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
  }
  else
  {
    /* #102 Unicast: Check if the device has rebooted. */
    if(((Sd_GetRxUnicastSessionIdOfAddressStorage(addressStorageIdx) > SdHeaderPtr->SessionID) ||
      ((Sd_GetRxUnicastFlagsOfAddressStorage(addressStorageIdx) & SD_FLAGS_REBOOT_MASK) == 0u)) &&
      ((SdHeaderPtr->Flags & SD_FLAGS_REBOOT_MASK) != 0u))
    {
      /* #1020 The remote device has rebooted. */
      RxMessageInfoPtr->RebootDetected = TRUE;                                                                          /* SBSW_SD_VALID_API_POINTER */
      Sd_Rx_HandleRemoteReboot(InstanceIdx, RxMessageInfoPtr);                                                          /* SBSW_SD_PASSING_API_POINTER */

      /* #1021 Reset the multicast Session ID in order to detect the reboot only once. */
      Sd_SetRxMulticastSessionIdOfAddressStorage(addressStorageIdx, 0u);                                                /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
    }

    /* #103 Update the Session ID and Flags field for unicast messages. */
    Sd_SetRxUnicastSessionIdOfAddressStorage(addressStorageIdx, SdHeaderPtr->SessionID);                                /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
    Sd_SetRxUnicastFlagsOfAddressStorage(addressStorageIdx, SdHeaderPtr->Flags);                                        /* SBSW_SD_RX_ADDRESS_STORAGE_IDX */
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_GetSdEndpointOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_GetSdEndpointOption(
  SoAd_SoConIdType RxSoConId,
  SD_P2CONST(PduInfoType) PduInfoPtr,
  SD_P2VAR(Sd_SockAddrContainerType) SdEndpointAddressPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  boolean sdEndpointOptionPresent = FALSE;
  uint16 optionIndex = 0u;
  Sd_OptionType optionType;

  /* ----- Implementation ----------------------------------------------- */
  SdEndpointAddressPtr->family = SOAD_AF_INVALID;                                                                       /* SBSW_SD_VALID_API_POINTER */

  /* #10 Check if an SD endpoint option is attached and save it. */
  while(optionIndex < Sd_GetNrOfOptions())
  {
    /* #100 Get the option type. */
    SD_GET_OPTION_TYPE(PduInfoPtr, Sd_GetOptionIndex(optionIndex), optionType);

    if(optionType == SD_OPTION_IPV4_SD_ENDPOINT)
    {
      /* #1000 Read the address transported in the IPv4 SD endpoint option. */
      optionsRetVal = Sd_Rx_ReadEndpointOption(SOAD_AF_INET, PduInfoPtr->SduDataPtr,
        Sd_GetOptionIndex(optionIndex), SdEndpointAddressPtr);                                                          /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_PASSING_API_POINTER */

      /* #1001 Only the first SD endpoint option shall be processed. (All further SD endpoint options shall be ignored.) */
      sdEndpointOptionPresent = TRUE;
    }
    else if(optionType == SD_OPTION_IPV6_SD_ENDPOINT)
    {
      /* #1002 Read the address transported in the IPv6 SD endpoint option. */
      optionsRetVal = Sd_Rx_ReadEndpointOption(SOAD_AF_INET6, PduInfoPtr->SduDataPtr,
        Sd_GetOptionIndex(optionIndex), SdEndpointAddressPtr);                                                          /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_PASSING_API_POINTER */

      /* #1003 Only the first SD endpoint option shall be processed. (All further SD endpoint options shall be ignored.) */
      sdEndpointOptionPresent = TRUE;
    }
    else
    {
      /* #101 No IPv4 or IPv6 SD endpoint option. Keep searching. */
    }

    /* #102 Check if a valid SD endpoint option was found. */
    if(sdEndpointOptionPresent == TRUE)
    {
      Sd_SockAddrContainerType localAddr;
      uint8 netmaskCidr = 0u;

      /* #103 Get the local IP address and the subnet mask. */
      retVal = Sd_SoAd_GetLocalAddrWithNetmask(RxSoConId, &localAddr, &netmaskCidr);                                    /* SBSW_SD_REFERENCE_OF_VARIABLE */

      /* #104 Check if the SD endpoint address is part of the subnet. */
      /* PRQA S 3415 2 */ /* MD_Sd_12.4_3415 */
      if((retVal == E_OK) && (optionsRetVal == SD_OPTIONS_OK) &&
        (TRUE == Sd_Rx_SockAddrWithinSubnet(&localAddr, SdEndpointAddressPtr, netmaskCidr)))                            /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_PASSING_API_POINTER */
      {
        /* #1040 First valid SD endpoint option successfully read. */
      }
      else
      {
        /* #1041 The endpoint references an IP address outside the configured subnet, do not consider this endpoint option. */
        SdEndpointAddressPtr->family = SOAD_AF_INVALID;                                                                 /* SBSW_SD_VALID_API_POINTER */
        retVal = E_NOT_OK;
      }

      break;
    }

    optionIndex++;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_GetEndpointOptionParameters()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Rx_GetEndpointOptionParameters(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  boolean ReadMulticastEndpoints,
  SD_P2VAR(Sd_FamilyType) FamilyTypePtr,
  SD_P2VAR(Sd_L4ProtocolType) L4ProtocolTypePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionType optionType;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Read the option type information. */
  SD_GET_OPTION_TYPE(PduInfoPtr, Sd_GetOptionIndex(IndexOfOption), optionType);

  /* #20 Read endpoint option information. */
  if(((optionType == SD_OPTION_IPV4_MULTICAST) && (ReadMulticastEndpoints == TRUE)) ||
    ((optionType == SD_OPTION_IPV4_ENDPOINT) && (ReadMulticastEndpoints == FALSE)))
  {
    SD_GET_L4PROTOCOL_IPV4_TYPE(PduInfoPtr, Sd_GetOptionIndex(IndexOfOption), *L4ProtocolTypePtr);                      /* SBSW_SD_VALID_API_POINTER */
    *FamilyTypePtr = SOAD_AF_INET;                                                                                      /* SBSW_SD_VALID_API_POINTER */
  }
  else if(((optionType == SD_OPTION_IPV6_MULTICAST) && (ReadMulticastEndpoints == TRUE)) ||
    ((optionType == SD_OPTION_IPV6_ENDPOINT) && (ReadMulticastEndpoints == FALSE)))
  {
    SD_GET_L4PROTOCOL_IPV6_TYPE(PduInfoPtr, Sd_GetOptionIndex(IndexOfOption), *L4ProtocolTypePtr);                      /* SBSW_SD_VALID_API_POINTER */
    *FamilyTypePtr = SOAD_AF_INET6;                                                                                     /* SBSW_SD_VALID_API_POINTER */
  }
  else
  {
    /* #200 Ignore unknown and unexpected (ReadMulticastEndpoints) options. */
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_ReadEndpointOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_ReadEndpointOptions(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  Sd_FamilyType FamilyType,
  Sd_L4ProtocolType L4ProtocolType,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if an endpoint option was attached */
  if(FamilyType != SOAD_AF_INVALID)
  {
    /* #100 Differentiate between UDP and TCP endpoints. */
    if((L4ProtocolType == SD_L4PROTOCOL_UDP) && (AttachedOptionsPtr->EndpointAddrUdp.family == SOAD_AF_INVALID))
    {
      /* #1000 Read the UDP address transported in the endpoint. */
      optionsRetVal = Sd_Rx_ReadEndpointOption(FamilyType, PduInfoPtr->SduDataPtr, Sd_GetOptionIndex(IndexOfOption),
        &AttachedOptionsPtr->EndpointAddrUdp);                                                                          /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
    }
    else if((L4ProtocolType == SD_L4PROTOCOL_TCP) && (AttachedOptionsPtr->EndpointAddrTcp.family == SOAD_AF_INVALID))
    {
      /* #1001 Read the TCP address transported in the endpoint. */
      optionsRetVal = Sd_Rx_ReadEndpointOption(FamilyType, PduInfoPtr->SduDataPtr, Sd_GetOptionIndex(IndexOfOption),
        &AttachedOptionsPtr->EndpointAddrTcp);                                                                          /* SBSW_SD_PDU_INFO_PTR */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
    }
    else
    {
      /* #1002 Reject subscription because of an undefined protocol type or because the entry references multiple endpoint options of the same type. */
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_ReadEndpointOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_ReadEndpointOption(
  Sd_FamilyType FamilyType,
  SD_P2CONST(uint8) DataPtr,
  uint16 DataIndex,
  SD_P2VAR(Sd_SockAddrContainerType) EndpointAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  EndpointAddrPtr->family = FamilyType;                                                                                 /* SBSW_SD_VALID_API_POINTER */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Data is saved in Network Byte Order. */

  if(FamilyType == SOAD_AF_INET)
  {
    /* #100 Save IPv4 endpoint option. */
    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(EndpointAddrPtr->data, &DataPtr[DataIndex + SD_OPTION_IPV4_ADDRESS_OFFSET], SD_OPTION_IPV4_ADDRESS_SIZE);   /* SBSW_SD_SOCK_ADDR_SIZE */ /* SBSW_SD_RX_MESSAGE_SIZE */

    if(EndpointAddrPtr->data[0u] == 0u)
    {
      /* #1000 Mark the endpoint address as invalid if no definite address is defined. */
      EndpointAddrPtr->family = SOAD_AF_INVALID;                                                                        /* SBSW_SD_VALID_API_POINTER */
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }

    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(&EndpointAddrPtr->port,                                                                                     /* SBSW_SD_SOCK_ADDR_SIZE */ /* SBSW_SD_RX_MESSAGE_SIZE */
      &DataPtr[DataIndex + SD_OPTION_IPV4_PORTNUMBER_OFFSET], SD_OPTION_IPV4_PORTNUMBER_SIZE);
  }
  else /* SOAD_AF_INET6 == FamilyType. */
  {
    /* #101 Save IPv6 endpoint option. */
    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(EndpointAddrPtr->data, &DataPtr[DataIndex + SD_OPTION_IPV6_ADDRESS_OFFSET], SD_OPTION_IPV6_ADDRESS_SIZE);   /* SBSW_SD_SOCK_ADDR_SIZE */ /* SBSW_SD_RX_MESSAGE_SIZE */

    if((EndpointAddrPtr->data[0u] | EndpointAddrPtr->data[1u] | EndpointAddrPtr->data[2u] | EndpointAddrPtr->data[3u]) == 0u)
    {
      /* #1010 Mark the endpoint address as invalid if no definite address is defined. */
      EndpointAddrPtr->family = SOAD_AF_INVALID;                                                                        /* SBSW_SD_VALID_API_POINTER */
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }

    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(&EndpointAddrPtr->port,                                                                                     /* SBSW_SD_SOCK_ADDR_SIZE */ /* SBSW_SD_RX_MESSAGE_SIZE */
      &DataPtr[DataIndex + SD_OPTION_IPV6_PORTNUMBER_OFFSET], SD_OPTION_IPV6_PORTNUMBER_SIZE);
  }

  if(EndpointAddrPtr->port == SD_TCPIP_PORT_ANY)
  {
    /* #102 Mark the endpoint address as invalid if no definite port is defined. */
    EndpointAddrPtr->family = SOAD_AF_INVALID;                                                                          /* SBSW_SD_VALID_API_POINTER */
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_CheckConfigOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckConfigOption(
  SD_P2CONST(PduInfoType) PduInfoPtr,
  uint8 IndexOfOption,
  SD_P2VAR(Sd_ConfigOptionStringType) ConfigOptionPtrArrayPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  boolean correctTermination = FALSE;
  uint8 itemLength;
  uint16 lengthOfOption, reservedIndex, tmpIndex;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get configuration option header. */
  SD_GET_UINT16(PduInfoPtr, Sd_GetOptionIndex(IndexOfOption), lengthOfOption);

  /* #20 Skip Reserved Field. */
  reservedIndex = Sd_GetOptionIndex(IndexOfOption) + SD_OPTION_LENGTH_SIZE + SD_OPTION_TYPE_SIZE;
  tmpIndex = SD_OPTION_RESERVED_SIZE;

  /* #30 Check configuration string. */
  while((lengthOfOption > tmpIndex) && (optionsRetVal == SD_OPTIONS_OK))
  {
    /* #300 Get length of capability string. */
    SD_GET_UINT8(PduInfoPtr, reservedIndex + tmpIndex, itemLength);
    tmpIndex++;

    /* #301 Check if the current byte defines the termination of the capability string. */
    if(itemLength == 0u)
    {
      /* #3010 Termination of capability string. Exit loop. */
      correctTermination = TRUE;
      break;
    }

    /* #302 Check if the length of the item exceeds the length of the entire option. */
    if(lengthOfOption >= (itemLength + tmpIndex))
    {
      tmpIndex += itemLength;
    }
    else
    {
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }
  }

  /* #40 Check if the option was terminated correctly. */
  if(correctTermination == TRUE)
  {
    Sd_SizeOfOptionIndexType optionIdx;

    /* #400 Save reference to the configuration string in the list of configuration options. */
    for(optionIdx = 0u; optionIdx < Sd_GetMaxNrOptionsPerEntry(); optionIdx++)
    {
      if(ConfigOptionPtrArrayPtr[optionIdx] == NULL_PTR)
      {
        ConfigOptionPtrArrayPtr[optionIdx] = &PduInfoPtr->SduDataPtr[reservedIndex + SD_OPTION_RESERVED_SIZE];          /* SBSW_SD_CONFIG_OPTION_PTR_ARRAY_SIZE */
        break;
      }
    }

    /* #401 Check if the number of attached options exceeds number defined in BSWMD configuration parameter SdMaxNrOptionsPerMsg. */
    if(optionIdx == Sd_GetMaxNrOptionsPerEntry())
    {
      optionsRetVal = SD_OPTIONS_NOT_OK;
    }
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_FillConfigOptionPtrArray()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_FillConfigOptionPtrArray(
  SD_P2VAR(Sd_ConfigOptionStringType) ConfigOptionPtrArrayPtr,
  Sd_SizeOfCapabilityRecordType InstanceCapabilityIdx,
  Sd_SizeOfCapabilityRecordType ServiceCapabilityIdx,
  Sd_SizeOfCapabilityRecordType ServiceCapabilityInvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 configOptionIdx = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add hostname configuration option if configured. */
  if(InstanceCapabilityIdx != SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE)
  {
    ConfigOptionPtrArrayPtr[configOptionIdx] = Sd_GetAddrCapabilityRecord(InstanceCapabilityIdx);                       /* SBSW_SD_FIXED_SIZE_OF_CONFIGOPTIONPTRARRAY */
    configOptionIdx++;
  }

  /* #20 Add configuration option of service level if configured. */
  if(ServiceCapabilityIdx != ServiceCapabilityInvIdx)
  {
    ConfigOptionPtrArrayPtr[configOptionIdx] = Sd_GetAddrCapabilityRecord(ServiceCapabilityIdx);                        /* SBSW_SD_FIXED_SIZE_OF_CONFIGOPTIONPTRARRAY */
  }
}

/**********************************************************************************************************************
 *  Sd_State_HandleRunMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_State_HandleRunMode(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SendEntryIterType sendEntryIdx;
  Sd_AddressStorageIterType addStorageIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the run mode of the current instance. */
  switch(Sd_GetRunModeOfInstanceDyn(InstanceIdx))
  {
    case SD_RUN_MODE_INITIAL_RUN:
    case SD_RUN_MODE_NEW_IP_ASSIGNED:
      /* #100 The module was re-initialized by a call of Sd_Init() or Sd_LocalIpAddrAssignmentChg(). */
      Sd_Init_ReInitialize(InstanceIdx);

      if(Sd_GetRunModeOfInstanceDyn(InstanceIdx) == SD_RUN_MODE_INITIAL_RUN)
      {
        Sd_SetRunModeOfInstanceDyn(InstanceIdx, SD_RUN_MODE_RUNNING_NO_IP);                                             /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      }
      else
      {
        Sd_SetRunModeOfInstanceDyn(InstanceIdx, SD_RUN_MODE_RUNNING);                                                   /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      }
      break;

    case SD_RUN_MODE_IP_UNASSIGNED:
      /* #101 The IP assignment of the local SD address was removed. */

      /* #102 Reset the state of all client and server services. */
      Sd_UtilClient_LocalIpAddrAssignmentChgReset(InstanceIdx);
      Sd_UtilServer_LocalIpAddrAssignmentChgReset(InstanceIdx);

      /* #103 Clear the list of pending send entries. */
      SD_BEGIN_CRITICAL_SECTION();

      for(sendEntryIdx = Sd_GetSendEntryStartIdxOfInstance(InstanceIdx);
        sendEntryIdx < Sd_GetSendEntryEndIdxOfInstance(InstanceIdx);
        sendEntryIdx++)
      {
        Sd_SetValidOfSendEntry(sendEntryIdx, FALSE);                                                                    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        Sd_SetSendEntryNextIdxOfSendEntry(sendEntryIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                             /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }

      /* #104 Clear number of pending SendEntries for each destination address. */
      for(addStorageIdx = Sd_GetAddressStorageStartIdxOfInstance(InstanceIdx);
        addStorageIdx < Sd_GetAddressStorageEndIdxOfInstance(InstanceIdx);
        addStorageIdx++)
      {
        Sd_SetSendEntryNrPendingIdxOfAddressStorage(addStorageIdx, 0u);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }

      Sd_SetSendEntryStartIdxOfInstanceDyn(InstanceIdx, SD_NO_SENDENTRYSTARTIDXOFINSTANCEDYN);                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_SetSendEntryEndIdxOfInstanceDyn(InstanceIdx, SD_NO_SENDENTRYENDIDXOFINSTANCEDYN);                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      Sd_SetSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx, 0u);                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      SD_END_CRITICAL_SECTION();

      /* #105 Update the run mode of the instance. */
      Sd_SetRunModeOfInstanceDyn(InstanceIdx, SD_RUN_MODE_WAIT_IP_ASSIGNMENT);                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      break;

    default:
      /* #106 The instance is in state SD_RUN_MODE_RUNNING, SD_RUN_MODE_RUNNING_NO_IP or SD_RUN_MODE_WAIT_IP_ASSIGNMENT. Nothing to do. */
      break;
  }
}

/**********************************************************************************************************************
 *  Sd_State_Process()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_State_Process(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the state machines have to be triggered because of a pending timer event. */
  if(TRUE == Sd_Util_CheckIfTimerExceeded(Sd_GetNextStateMachineRunOfInstanceDyn(InstanceIdx), TRUE))
  {
    Sd_SizeOfServerType serverIdx;
    Sd_SizeOfClientType clientIdx;

    /* #100 Reset the timer. */
    Sd_Util_ResetTimerToInvalid(Sd_GetAddrNextStateMachineRunOfInstanceDyn(InstanceIdx));                               /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */

    /* #101 Iterate over all server state machines of the instance. */
    for(serverIdx = Sd_GetServerStartIdxOfInstance(InstanceIdx);
      serverIdx < Sd_GetServerEndIdxOfInstance(InstanceIdx);
      serverIdx++)
    {
      /* #1010 Only execute state machine if requested for server. */
      SD_BEGIN_CRITICAL_SECTION();
      if(Sd_IsStateMachineExecutionRequestedOfServerDyn(serverIdx))
      {
        Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, FALSE);                                              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        SD_END_CRITICAL_SECTION();
        Sd_StateServer_Process(serverIdx);
      }
      else
      {
        SD_END_CRITICAL_SECTION();
      }
    }

    /* #102 Iterate over all client state machines of the instance. */
    for(clientIdx = Sd_GetClientStartIdxOfInstance(InstanceIdx);
      clientIdx < Sd_GetClientEndIdxOfInstance(InstanceIdx);
      clientIdx++)
    {
      SD_BEGIN_CRITICAL_SECTION();
      /* #1020 Only execute state machine if requested for client. */
      if(Sd_IsStateMachineExecutionRequestedOfClientDyn(clientIdx))
      {
        Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, FALSE);                                              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
        SD_END_CRITICAL_SECTION();
        Sd_StateClient_Process(clientIdx);
      }
      else
      {
        SD_END_CRITICAL_SECTION();
      }
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_ProcessHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Rx_ProcessHeader(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(PduInfoType) PduInfoPtr,
  SD_P2VAR(Sd_HeaderType) SdHeaderPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 1 */ /* MD_Sd_Rule-2.2_2981 */
  uint32 lengthEntriesArray, lengthOptionsArray= 0u;
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Drop message if it does not include a complete SD header as well as the length field for entries and options. */
  if(PduInfoPtr->SduLength >= (SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE))
  {
    retVal = E_OK;

    /* #100 Read the header, message ID and Length field of the SD header will be handled by the SoAd. */
    SD_GET_UINT16(PduInfoPtr, SD_HEADER_CLIENTID_OFFSET, SdHeaderPtr->ClientID);                                        /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT16(PduInfoPtr, SD_HEADER_SESSIONID_OFFSET, SdHeaderPtr->SessionID);                                      /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT8(PduInfoPtr, SD_HEADER_PROTOCOLVERSION_OFFSET, SdHeaderPtr->ProtocolVersion);                           /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT8(PduInfoPtr, SD_HEADER_INTERFACEVERSION_OFFSET, SdHeaderPtr->InterfaceVersion);                         /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT8(PduInfoPtr, SD_HEADER_MESSAGETYPE_OFFSET, SdHeaderPtr->MessageType);                                   /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT8(PduInfoPtr, SD_HEADER_RETURNCODE_OFFSET, SdHeaderPtr->ReturnCode);                                     /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT8(PduInfoPtr, SD_HEADER_FLAGS_OFFSET, SdHeaderPtr->Flags);                                               /* SBSW_SD_VALID_API_POINTER */
    SD_GET_UINT24(PduInfoPtr, SD_HEADER_RESERVED_OFFSET, SdHeaderPtr->Reserved);                                        /* SBSW_SD_VALID_API_POINTER */

    /* #101 Check the predefined fields of the header. */
    if((SdHeaderPtr->ProtocolVersion != SD_HEADER_PROTOCOL_VERSION) ||
      (SdHeaderPtr->InterfaceVersion != SD_HEADER_INTERFACE_VERSION) ||
      (SdHeaderPtr->MessageType != SD_HEADER_MESSAGE_TYPE) ||
      (SdHeaderPtr->ReturnCode != SD_HEADER_RETURN_CODE))
    {
      /* #1010 The header is not compliant with the statically defined values. */
      retVal = E_NOT_OK;
    }
    else if(0u == (SdHeaderPtr->Flags & SD_FLAGS_UNICAST_MASK))
    {
      /* #1011 If unicast flag is not set, ignore message. */
      retVal = E_NOT_OK;
    }
    else
    {
      /* #1012 Predefined header fields are ok. Process the received SD payload data. */
      SD_GET_UINT32(PduInfoPtr, SD_HEADER_LENGTH, lengthEntriesArray);

      /* #1013 Check if the entries array fits into the payload. */
      if(PduInfoPtr->SduLength >=
        (SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + lengthEntriesArray + SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE))
      {
        SD_GET_UINT32(PduInfoPtr, SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE +
          lengthEntriesArray, lengthOptionsArray);
      }
      else
      {
        /* #10130 The entries array exceeds the payload. */
        retVal = E_NOT_OK;
      }

      /* #1014 Check if the payload can contain all mentioned entry and option arrays. */
      if((retVal == E_OK) &&
        (PduInfoPtr->SduLength >= (SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + lengthEntriesArray +
        SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE + lengthOptionsArray)))
      {
        /* #10140 Header fields of message are valid. */
        retVal = E_OK;
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
  }

  if(retVal != E_OK)
  {
    /* #102 The message is malformed. */
    Sd_Util_ReportDemEvent(Sd_GetEMalformedMsgIdOfInstance(InstanceIdx));
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_ProcessEntryArray()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Rx_ProcessEntryArray(
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 indexEntry;
  uint32 lengthEntriesArray;

  /* ----- Implementation ----------------------------------------------- */
  SD_GET_UINT32(RxMessageInfoPtr->PduInfoPtr, SD_HEADER_LENGTH, lengthEntriesArray);
  indexEntry = SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE;

  /* #10 Iterate through all entries of the array. */
  while(((uint32)indexEntry + SD_ENTRY_SIZE) <= (SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + lengthEntriesArray))
  {
    /* #100 Process the current entry and all associated options. */
    Sd_EntryType rxEntryType;
    SD_GET_ENTRY_TYPE(RxMessageInfoPtr->PduInfoPtr, indexEntry, rxEntryType);

    /* #101 Check if the entry has to be processed by a server or client service. */
    if((rxEntryType == SD_ENTRY_FIND_SERVICE) || (rxEntryType == SD_ENTRY_SUBSCRIBE_EVENTGROUP))
    {
      /* #1010 Entry has to be processed by a server. */
      Sd_RxServer_ProcessEntry(RxMessageInfoPtr, indexEntry, InstanceIdx);                                              /* SBSW_SD_PASSING_API_POINTER */
    }
    else if((rxEntryType == SD_ENTRY_OFFER_SERVICE) || (rxEntryType == SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK))
    {
      /* #1011 Entry has to be processed by a client. */
      Sd_RxClient_ProcessEntry(RxMessageInfoPtr, indexEntry, InstanceIdx);                                              /* SBSW_SD_PASSING_API_POINTER */
    }
    else
    {
      /* #1012 Ignore entry with unknown type. */
    }

    /* #102 The length of all entry arrays (format type 1 and format type 2) is 16 bytes. */
    indexEntry += SD_ENTRY_SIZE;
  }
}

/**********************************************************************************************************************
 *  Sd_Rx_HandleRemoteReboot()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Rx_HandleRemoteReboot(
  Sd_SizeOfInstanceType InstanceIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_ClientIterType clientIdx;
  Sd_SizeOfServerType serverIdx;
  Sd_SizeOfEventHandlerType eventHandlerIdx;

  /* ----- Implementation ----------------------------------------------- */
    /* #10 Search for all clients which are affected by the remote reboot. */
  for(clientIdx = Sd_GetClientStartIdxOfInstance(InstanceIdx);
    clientIdx < Sd_GetClientEndIdxOfInstance(InstanceIdx);
    clientIdx++)
  {
    /* #100 Check if the client is affected by the reboot of the remote service. */
    if(RxMessageInfoPtr->AddressStorageIdx == Sd_GetAddressStorageServerIdxOfClientDyn(clientIdx))
    {
      /* #1000 Save reboot of remote server as if a StopOfferService message was received. */
      Sd_SetEventRxOfClientDyn(clientIdx, SD_CLIENT_EVENT_SERVICE_STOP_OFFER);                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                 /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    }
  }

  /* #20 Search for all server which are affected by the remote reboot. */
  for(serverIdx = Sd_GetServerStartIdxOfInstance(InstanceIdx);
    serverIdx < Sd_GetServerEndIdxOfInstance(InstanceIdx);
    serverIdx++)
  {
    /* #200 Close all UDP socket connections used on service level. */
    Sd_RxServer_HandleRemoteRebootUdp(serverIdx, RxMessageInfoPtr);                                                     /* SBSW_SD_PASSING_API_POINTER */

    /* #201 Close all TCP socket connections used on service level. */
    Sd_RxServer_HandleRemoteRebootTcp(serverIdx, RxMessageInfoPtr);                                                     /* SBSW_SD_PASSING_API_POINTER */

    /* #202 Check if the remote service was subscribed before. */
    for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(serverIdx);
      eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(serverIdx);
      eventHandlerIdx++)
    {
      /* #2020 Set the TTL of all matching clients to 0 in order to remove the clients during the next main function. */
      (void)Sd_RxServer_FindClientInList(eventHandlerIdx, RxMessageInfoPtr, NULL_PTR, FALSE);                           /* SBSW_SD_FUNCTION_CALL_NULL_PTR */
    }
  }

  /* #30 Trigger execution of the state machines in order to process the detected remote reboot. */
  Sd_Util_TriggerStateMachineRun(InstanceIdx);
}

/**********************************************************************************************************************
 *  Sd_RxServer_HandleRemoteRebootTcp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_RxServer_HandleRemoteRebootTcp(
  Sd_SizeOfServerType ServerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_TcpSoConIdIterType tcpSoConIdIdx;
  Sd_SockAddrContainerType tmpAddr;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all TCP socket connections. */
  for(tcpSoConIdIdx = Sd_GetTcpSoConIdStartIdxOfServer(ServerIdx);
    tcpSoConIdIdx < Sd_GetTcpSoConIdEndIdxOfServer(ServerIdx);
    tcpSoConIdIdx++)
  {
    /* #100 Get Remote Address of TCP socket connection. */
    retVal = Sd_SoAd_GetRemoteAddr(Sd_GetTcpSoConId(tcpSoConIdIdx), &tmpAddr);                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Check if the saved remote address is equivalent to the remote address of the rebooted service. */
    /* PRQA S 3415 3 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_OK) &&
      (SD_MATCH_TRUE == Sd_Util_CompareSockAddrIp(
        Sd_GetAddrAddrOfAddressStorage(RxMessageInfoPtr->AddressStorageIdx), &tmpAddr, 0u)))                            /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    {
      /* #1010 Socket connection was used for the rebooted remote client, close and reopen it. */
      (void)SoAd_CloseSoCon(Sd_GetTcpSoConId(tcpSoConIdIdx), TRUE);
      (void)SoAd_OpenSoCon(Sd_GetTcpSoConId(tcpSoConIdIdx));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_RxServer_HandleRemoteRebootUdp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_RxServer_HandleRemoteRebootUdp(
  Sd_SizeOfServerType ServerIdx,
  SD_P2CONST(Sd_RxMessageInfoType) RxMessageInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_UdpSoConIterType udpSoConIdx;
  Sd_SockAddrContainerType tmpAddr;
  boolean abortParameter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all UDP socket connections. */
  for(udpSoConIdx = Sd_GetUdpSoConStartIdxOfServer(ServerIdx);
    udpSoConIdx < Sd_GetUdpSoConEndIdxOfServer(ServerIdx);
    udpSoConIdx++)
  {
    /* #100 Get Remote Address of socket connection. */
    retVal = Sd_SoAd_GetRemoteAddr(Sd_GetIdOfUdpSoCon(udpSoConIdx), &tmpAddr);                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #101 Check if the saved remote address is equivalent to the remote address of the rebooted service. */
    /* PRQA S 3415 3 */ /* MD_Sd_12.4_3415 */
    if((retVal == E_OK) &&
      (SD_MATCH_TRUE == Sd_Util_CompareSockAddrIp(
        Sd_GetAddrAddrOfAddressStorage(RxMessageInfoPtr->AddressStorageIdx), &tmpAddr, 0u)))                            /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */ /* SBSW_SD_REFERENCE_OF_VARIABLE */
    {
      /* #1010 Do not abort if remote address of socket is preconfigured. */
      if(Sd_IsPreconfiguredOfUdpSoCon(udpSoConIdx) == TRUE)
      {
        abortParameter = FALSE;
      }
      else
      {
        abortParameter = TRUE;
      }

      /* #1011 Socket connection was used for the rebooted remote client, close and reopen it. */
      (void)SoAd_CloseSoCon(Sd_GetIdOfUdpSoCon(udpSoConIdx), abortParameter);
      (void)SoAd_OpenSoCon(Sd_GetIdOfUdpSoCon(udpSoConIdx));
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Tx_ProcessPendingMessages()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_ProcessPendingMessages(
  Sd_SizeOfInstanceType InstanceIdx,
  boolean ForceTransmission)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean tmpForceTransmission = ForceTransmission;
  Sd_SizeOfSendEntryType iteration;
  Sd_SizeOfAddressStorageType addressStorageIdx;
  Sd_SizeOfSendEntryType sentEntries;

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();
  /* #10 Skip transmission if TxPath is locked by other context. */
  if(Sd_TxPathLocked == FALSE)
  {
    Sd_TxPathLocked = TRUE;

    /* #100 Iterate until all messages are transmitted, but maximally SendEntryNrPendingIdx-times. */
    iteration = Sd_GetSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx);

    /* #101 Check if the list with pending send entries is full. */
    if(Sd_GetSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx) >=
      (Sd_GetSendEntryEndIdxOfInstance(InstanceIdx) - Sd_GetSendEntryStartIdxOfInstance(InstanceIdx)))
    {
      /* #1010 The send entry list is full, force transmission. */
      tmpForceTransmission = TRUE;
    }

    SD_END_CRITICAL_SECTION();

    /* #200 Serialize SdMessages until there are no entries left to send. */
    while((iteration != 0u) && (Sd_GetSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx) != 0u))
    {
      iteration--;

      /* #201 Get address storage index of next entry which is ready for transmission. */
      addressStorageIdx = Sd_Tx_CheckIfMessageReadyForTransmission(InstanceIdx, tmpForceTransmission);

      /* #202 Check if entries for a destination are ready for transmission. */
      if(addressStorageIdx < Sd_GetSizeOfAddressStorage())
      {
        sentEntries = 1;
        /* #2020 Generate one SdMessage and transmit it if there are pending send entries and the instance is up. */
        while((sentEntries != 0u) && (Sd_GetStateOfInstanceDyn(InstanceIdx) == SD_INSTANCE_UP_AND_CONFIGURED))
        {
          sentEntries = Sd_Tx_SerializeMessage(InstanceIdx, addressStorageIdx);
        }
      }
    }

    SD_BEGIN_CRITICAL_SECTION();
    Sd_TxPathLocked = FALSE;
    SD_END_CRITICAL_SECTION();
  }
  else
  {
    SD_END_CRITICAL_SECTION();
  }
}

/**********************************************************************************************************************
 *  Sd_Tx_CheckIfMessageReadyForTransmission()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfAddressStorageType, SD_CODE) Sd_Tx_CheckIfMessageReadyForTransmission(
  Sd_SizeOfInstanceType InstanceIdx,
  boolean ForceTransmission)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType sendEntryIdx;
  Sd_SizeOfAddressStorageType validAddressStorageIdx = Sd_GetSizeOfAddressStorage();

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Iterate over the list of send entries and search for a message which is ready to transmit. */
  for(sendEntryIdx = Sd_GetSendEntryStartIdxOfInstanceDyn(InstanceIdx);
    sendEntryIdx != SD_NO_SENDENTRYENDIDXOFINSTANCEDYN;
    sendEntryIdx = Sd_GetSendEntryNextIdxOfSendEntry(sendEntryIdx))
  {
    /* #100 Check if message is ready for transmission. */
    if((Sd_Util_CheckIfTimerExceeded(Sd_GetTimeToSendOfSendEntry(sendEntryIdx), TRUE) == TRUE) ||
      (ForceTransmission == TRUE))
    {
      /* #1000 Check if the transmission of the message shall be skipped (and processed in a subsequent call). */
      if(Sd_Tx_CheckIfEntryShallBeSkipped(InstanceIdx, sendEntryIdx) == FALSE)
      {
        /* #10000 Found message which is ready for transmission. */
        validAddressStorageIdx = Sd_GetAddressStorageIdxOfSendEntry(sendEntryIdx);
        break;
      }
    }
  }

  SD_END_CRITICAL_SECTION();
  return validAddressStorageIdx;
}

/**********************************************************************************************************************
 *  Sd_Tx_GetNextEntryToSend()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Tx_GetNextEntryToSend(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType sendEntryIdx;

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Iterate over all send entries. */
  for(sendEntryIdx = Sd_GetSendEntryStartIdxOfInstanceDyn(InstanceIdx);
    sendEntryIdx != SD_NO_SENDENTRYENDIDXOFINSTANCEDYN;
    sendEntryIdx = Sd_GetSendEntryNextIdxOfSendEntry(sendEntryIdx))
  {
    /* #100 Check if the pending entry is addressed to the identical destination. */
    if(Sd_GetAddressStorageIdxOfSendEntry(sendEntryIdx) == AddressStorageIdx)
    {
      /* #1000 Check if the entry shall be transmitted. */
      if(Sd_Tx_CheckIfEntryShallBeSkipped(InstanceIdx, sendEntryIdx) == FALSE)
      {
        /* #10000 Check if the entry is a subscription configured with retry functionality. */
        if((Sd_GetEntryTypeOfSendEntry(sendEntryIdx) == SD_ENTRY_SUBSCRIBE_EVENTGROUP) &&
          (Sd_GetOfferedTTLOfClientDyn(Sd_GetClientIdxOfSendEntry(sendEntryIdx)) == SD_TTL_INFINITE) &&
          (Sd_GetRetryMaxOfInstance(InstanceIdx) != 0u))
        {
          /* #100000 Set the retry subscription timer for the time of the next retry. */
          Sd_Util_SetTimerOffsetWithTrigger(Sd_GetAddrRetryTimerOfClientDyn(Sd_GetClientIdxOfSendEntry(sendEntryIdx)),  /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX_INDIRECTION_SAME_SIZE */
            Sd_GetRetryDelayOfInstance(InstanceIdx), InstanceIdx);
          Sd_SetStateMachineExecutionRequestedOfClientDyn(Sd_GetClientIdxOfSendEntry(sendEntryIdx), TRUE);              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
        }

        break;
      }
    }
  }

  SD_END_CRITICAL_SECTION();
  return sendEntryIdx;
}

/**********************************************************************************************************************
 *  Sd_Tx_CheckIfEntryShallBeSkipped()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Tx_CheckIfEntryShallBeSkipped(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfSendEntryType SendEntryIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean skipEntry = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the selected entry is a (Stop)Subscribe entry. */
  if(((Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_SUBSCRIBE_EVENTGROUP) ||
    (Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_STOP_SUBSCRIBE_EVENTGROUP)))
  {
    Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx = Sd_GetConsumedEventgroupIdxOfSendEntry(SendEntryIdx);
    Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(consumedEventgroupIdx);

    /* #100 Check if the TCP connection is established. */
    /* PRQA S 3415 3 */ /* MD_Sd_12.4_3415 */
    if(Sd_ConsumedEventGroupUsesTcp(consumedEventgroupIdx) &&
      (Sd_GetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx) != SOAD_INV_SO_CON_ID) &&
      (Sd_Util_GetTcpSoConMode(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx)) != SD_SOCON_MODE_ONLINE))
    {
      /* #1000 The TCP connection is not established. Skip the transmission of this message. */
      skipEntry = TRUE;
    }

    /* #101 Check if the client service and/or eventgroup is still requested. */
    if(((Sd_GetStateSwcOfClientDyn(clientIdx) == SD_CLIENT_SERVICE_RELEASED) ||
      (Sd_GetServiceModeRequestOfConsumedEventgroupDyn(consumedEventgroupIdx) == SD_CONSUMED_EVENTGROUP_RELEASED) ||
      (Sd_GetCurrentStateOfClientDyn(clientIdx) == SD_CLIENT_SERVICE_DOWN)) &&
      (Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_SUBSCRIBE_EVENTGROUP))
    {
      /* #1010 The eventgroup is not requested or not available any more. Remove the message. */
      Sd_Util_RemoveSendEntryFromList(InstanceIdx, SendEntryIdx);
      skipEntry = TRUE;
    }
  }
  /* #20 Check if the entry corresponds to a server which is not available. */
  else if(((Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_OFFER_SERVICE) ||
    (Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK)) &&
    (Sd_GetStateSwcOfServerDyn(Sd_GetServerIdxOfSendEntry(SendEntryIdx)) == SD_SERVER_SERVICE_DOWN))
  {
    /* #200 The server is not available any more. Remove the message. */
    Sd_Util_RemoveSendEntryFromList(InstanceIdx, SendEntryIdx);
    skipEntry = TRUE;
  }
  else
  {
    /* #300 Otherwise, the entry shall not be skipped. */
  }

  return skipEntry;
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeMessage()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Tx_SerializeMessage(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfAddressStorageType AddressStorageIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType numSerializedEntries = 0u;
  Std_ReturnType retValSoad;
  boolean bufferTooSmall = FALSE;
  Sd_SizeOfPayloadType sizeEntriesArray;
  PduInfoType pduInfo;
  Sd_SizeOfSendEntryType sendEntryIdx;
  Sd_SizeOfSendEntryType maxNumberOfEntriesToSerialize;
  uint32 sizeOfOptionsArray;
  Sd_SizeOfPayloadType payloadEntryIdx = 0u;   /* PRQA S 2981 */ /* MD_Sd_Rule-2.2_2981 */
  Sd_OptionArrayInfoType optionArrayInfo;
  Sd_SizeOfPayloadType optionArrayEndIdxPrev;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Determine a reasonable maximum number of entries to be serialized depending on the max payload. */
  /* NOTE: Sd_GetSizeOfPayload() is enforced to be >=48 by the generator. */
  maxNumberOfEntriesToSerialize = (Sd_SizeOfSendEntryType)((Sd_GetSizeOfPayload() - (Sd_GetSizeOfPayload() / 4u)) / SD_ENTRY_SIZE);

  /* #20 Correct if number of entries in queue is smaller than maximum value. Calculate reserved space for EntriesArray.  */
  if(maxNumberOfEntriesToSerialize > Sd_GetSendEntryNrPendingIdxOfAddressStorage(AddressStorageIdx))
  {
    maxNumberOfEntriesToSerialize = Sd_GetSendEntryNrPendingIdxOfAddressStorage(AddressStorageIdx);
  }
  sizeEntriesArray = (Sd_SizeOfPayloadType)maxNumberOfEntriesToSerialize * SD_ENTRY_SIZE;

  /* #30 Get next entry to send and set offset to entry and option array. */
  sendEntryIdx = Sd_Tx_GetNextEntryToSend(InstanceIdx, AddressStorageIdx);
  payloadEntryIdx = SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE;
  optionArrayInfo.ArrayStartIdx = (uint16)payloadEntryIdx + (uint16)sizeEntriesArray + SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE;
  optionArrayInfo.ArrayEndIdx = optionArrayInfo.ArrayStartIdx;
  optionArrayEndIdxPrev = (Sd_SizeOfPayloadType)optionArrayInfo.ArrayEndIdx;
  optionArrayInfo.FreeOptionIndex = 0u;

  /* #40 Iterate over ready to send entries and serialize entries as well as options. */
  while((sendEntryIdx != SD_NO_SENDENTRYENDIDXOFINSTANCEDYN) && (numSerializedEntries < maxNumberOfEntriesToSerialize))
  {
    /* #400 Serialize the entry with all corresponding options. */
    bufferTooSmall = Sd_Tx_SerializeEntryAndOptions(sendEntryIdx, payloadEntryIdx, &optionArrayInfo);                   /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #401 Stop processing if TxBuffer is too small for next entry. */
    if(bufferTooSmall == TRUE)
    {
      break;
    }

    /* #402 Remove sent entry from queue and get next entry ready to send. */
    payloadEntryIdx += SD_ENTRY_SIZE;
    numSerializedEntries++;
    optionArrayEndIdxPrev = (Sd_SizeOfPayloadType)optionArrayInfo.ArrayEndIdx;
    Sd_Util_RemoveSendEntryFromList(InstanceIdx, sendEntryIdx);
    sendEntryIdx = Sd_Tx_GetNextEntryToSend(InstanceIdx, AddressStorageIdx);
  }

  /* #50 Check if at least one entry has been serialized completely. */
  if((numSerializedEntries != 0u) && ((bufferTooSmall == TRUE) || (numSerializedEntries != maxNumberOfEntriesToSerialize)))
  {
    /* #500 Calculate length of gap between Entries and OptionArray. */
    Sd_SizeOfPayloadType unusedEntryArrayLength = (((Sd_SizeOfPayloadType)maxNumberOfEntriesToSerialize) - (Sd_SizeOfPayloadType)numSerializedEntries) * SD_ENTRY_SIZE;

    /* #501 Copy Options Array after EntriesArray so already serialized entries can be sent.  */
    /* NOTE: Usually MemCpy functions must not be used if source and target memory area are overlapping!
     *       But since the target memory area is located a multiple of 16 Bytes before the source memory area, MemCpy can be used here.
     */
     /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(Sd_GetAddrPayload(optionArrayInfo.ArrayStartIdx - unusedEntryArrayLength), /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */
      Sd_GetAddrPayload(optionArrayInfo.ArrayStartIdx),
      ((uint32)optionArrayEndIdxPrev - optionArrayInfo.ArrayStartIdx));

    /* #502 Correct size of entries and start/end address of Options Array. */
    sizeEntriesArray -= unusedEntryArrayLength;
    optionArrayInfo.ArrayStartIdx -= (uint16)unusedEntryArrayLength;
    optionArrayInfo.ArrayEndIdx = (uint16)optionArrayEndIdxPrev - (uint16)unusedEntryArrayLength;
    bufferTooSmall = FALSE;
  }

  /* #60 Continue if payload contains usable data. */
  if((numSerializedEntries != 0u) && (bufferTooSmall == FALSE))
  {
    /* #600 Write the header of the SD message. */
    Sd_Tx_SerializeHeader(AddressStorageIdx);

    /* #601 Write the length of the entries array field. */
    Sd_Util_Write32Bit(Sd_GetAddrPayload(SD_HEADER_LENGTH), sizeEntriesArray);                                          /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* #602 Set the length of the options array. */
    sizeOfOptionsArray = (uint32)optionArrayInfo.ArrayEndIdx - (uint32)optionArrayInfo.ArrayStartIdx;
    Sd_Util_Write32Bit(
      Sd_GetAddrPayload(optionArrayInfo.ArrayStartIdx - SD_HEADER_LENGTHOFENTRIESARRAY_SIZE), sizeOfOptionsArray);    /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
    retValSoad = SoAd_SetRemoteAddr(Sd_GetTxSoConIdOfInstance(InstanceIdx),
      (SD_P2VAR(SoAd_SockAddrType))(Sd_GetAddrAddrOfAddressStorage(AddressStorageIdx)));                              /* SBSW_SD_TX_ADDRESS_STORAGE_IDX */ /* SBSW_SD_SOCK_ADDR_CAST */

    /* #603 Send the message. (Return value of SoAd_IfTransmit() is ignored.) */
    if(retValSoad == E_OK)
    {
      pduInfo.SduDataPtr = Sd_GetAddrPayload(0u);
      pduInfo.SduLength =  (PduLengthType)optionArrayInfo.ArrayEndIdx;

      (void)SoAd_IfTransmit(Sd_GetTxPduIdOfInstance(InstanceIdx), &pduInfo);                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */
    }

    /* #604 Increment SessionId for each transmitted message. */
    if(Sd_GetSessionIdCounterOfAddressStorage(AddressStorageIdx) == 0xFFFFu)
    {
      /* #6040 The SessionId should start with the value 1. */
      Sd_SetSessionIdCounterOfAddressStorage(AddressStorageIdx, 1u);                                                  /* SBSW_SD_TX_ADDRESS_STORAGE_IDX */
      /* #6041 Reset the reboot flag if the SessionId wraps around. */
      Sd_SetFlagsOfAddressStorage(AddressStorageIdx,                                                                  /* SBSW_SD_TX_ADDRESS_STORAGE_IDX */
        (uint8)(Sd_GetFlagsOfAddressStorage(AddressStorageIdx) & (~SD_FLAGS_REBOOT_MASK)));
    }
    else
    {
      Sd_IncSessionIdCounterOfAddressStorage(AddressStorageIdx);                                                      /* SBSW_SD_TX_ADDRESS_STORAGE_IDX */
    }
  }
  else if((numSerializedEntries == 0u) && (bufferTooSmall == FALSE))
  {
    /* No more entries to send */
  }
  /* #70 The configured Sd_Payload buffer is too small to contain the first entry which shall be serialized. */
  /* Buffer size is configured in Sd/SdConfig/SdInstance/SdInstanceTxPdu/SdTxPduRef or Sd/SdGeneral/SdTxBufferSize. */
  else
  {
#if(SD_DEV_ERROR_REPORT == STD_ON)
    /* #700 Report error. */
    (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SERIALIZE_PENDING_MESSAGES, SD_E_TX_BUFFER_FULL);
#endif
    /* #701 Remove Entry and set return value to one to avoid that entry which cannot be serialized blocks the queue. */
    Sd_Util_RemoveSendEntryFromList(InstanceIdx, sendEntryIdx);
    numSerializedEntries = 1u;
  }

  return numSerializedEntries;
} /* PRQA S 6010, 6050 */ /* MD_Sd_STPTH_6010, MD_Sd_STCAL_6050 */

/**********************************************************************************************************************
 *  Sd_Tx_SerializeHeader()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_SerializeHeader(
  Sd_SizeOfAddressStorageType AddressStorageIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Fill the header of the SD message. */
  /* #20 The Session ID of the header is used as a counter.
   *     All unicast as well as multicast messages have their own counter. */
  Sd_Util_Write16Bit(Sd_GetAddrPayload(SD_HEADER_CLIENTID_OFFSET), SD_HEADER_CLIENTID);                                 /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write16Bit(
    Sd_GetAddrPayload(SD_HEADER_SESSIONID_OFFSET), Sd_GetSessionIdCounterOfAddressStorage(AddressStorageIdx));          /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write8Bit(Sd_GetAddrPayload(SD_HEADER_PROTOCOLVERSION_OFFSET), SD_HEADER_PROTOCOLVERSION);                    /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write8Bit(Sd_GetAddrPayload(SD_HEADER_INTERFACEVERSION_OFFSET), SD_HEADER_INTERFACEVERSION);                  /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write8Bit(Sd_GetAddrPayload(SD_HEADER_MESSAGETYPE_OFFSET), SD_HEADER_MESSAGETYPE);                            /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write8Bit(Sd_GetAddrPayload(SD_HEADER_RETURNCODE_OFFSET), SD_HEADER_RETURNCODE);                              /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write8Bit(Sd_GetAddrPayload(SD_HEADER_FLAGS_OFFSET), Sd_GetFlagsOfAddressStorage(AddressStorageIdx));         /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
  Sd_Util_Write24Bit(Sd_GetAddrPayload(SD_HEADER_RESERVED_OFFSET), SD_HEADER_RESERVED);                                 /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeRelatedOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeRelatedOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean bufferTooSmall;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the control structures which map the options. */
  EntryToOptionMapPtr->Index1st = SD_INV_OPTION_INDEX;                                                                  /* SBSW_SD_VALID_API_POINTER */
  EntryToOptionMapPtr->Index2nd = SD_INV_OPTION_INDEX;                                                                  /* SBSW_SD_VALID_API_POINTER */
  EntryToOptionMapPtr->Nr1stOptions = 0u;                                                                               /* SBSW_SD_VALID_API_POINTER */
  EntryToOptionMapPtr->Nr2ndOptions = 0u;                                                                               /* SBSW_SD_VALID_API_POINTER */

  /* #20 Serialize all endpoint options into the message. */
  bufferTooSmall = Sd_Tx_SerializeEndpointOptions(SendEntryIdx, EntryToOptionMapPtr, OptionArrayInfoPtr);               /* SBSW_SD_PASSING_API_POINTER */

  if(bufferTooSmall == FALSE)
  {
    /* #200 Serialize all configuration options into the message. */
    bufferTooSmall = Sd_Tx_SerializeConfigurationOptions(SendEntryIdx, EntryToOptionMapPtr, OptionArrayInfoPtr);        /* SBSW_SD_PASSING_API_POINTER */
  }

  if(EntryToOptionMapPtr->Index1st == SD_INV_OPTION_INDEX)
  {
    /* #201 1st option run not used, clear all values. */
    EntryToOptionMapPtr->Index1st = 0u;                                                                                 /* SBSW_SD_VALID_API_POINTER */
    EntryToOptionMapPtr->Nr1stOptions = 0u;                                                                             /* SBSW_SD_VALID_API_POINTER */
  }

  if(EntryToOptionMapPtr->Index2nd == SD_INV_OPTION_INDEX)
  {
    /* #202 2nd option run not used, clear all values. */
    EntryToOptionMapPtr->Index2nd = 0u;                                                                                 /* SBSW_SD_VALID_API_POINTER */
    EntryToOptionMapPtr->Nr2ndOptions = 0u;                                                                             /* SBSW_SD_VALID_API_POINTER */
  }

  return bufferTooSmall;
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEntryAndOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeEntryAndOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfPayloadType PayloadEntryIdx,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_EntryType entryType;
  boolean bufferTooSmall;
  uint32 usedTtl;
  Sd_EntryToOptionMapType entryToOptionMap;

  /* ----- Implementation ----------------------------------------------- */
  entryType = Sd_GetEntryTypeOfSendEntry(SendEntryIdx);

  /* #10 Serialize first all related options of the entry. */
  bufferTooSmall = Sd_Tx_SerializeRelatedOptions(SendEntryIdx, &entryToOptionMap, OptionArrayInfoPtr);                  /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_PASSING_API_POINTER */

  /* #20 Check if all options fit to the payload. */
  if(bufferTooSmall == FALSE)
  {
    /* #200 Serialize the entry itself. */

    /* Fill the type field. The first bit of the Sd_EntryType is only used internally to differentiate STOP/NACK entries. */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadEntryIdx /* + SD_ENTRY_TYPE_OFFSET */),
      (uint8)(entryType & SD_ENTRY_TYPE_MASK)); /*lint !e655 */                                                         /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Write the option index and number of options. */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_INDEX1_OFFSET), entryToOptionMap.Index1st);          /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_INDEX2_OFFSET), entryToOptionMap.Index2nd);          /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_NROFOPTS_OFFSET),
      (uint8)(entryToOptionMap.Nr1stOptions << 4u) | entryToOptionMap.Nr2ndOptions);                                    /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Write Service and Instance IDs. */
    Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_SERVICEID_OFFSET),
      Sd_GetServiceIdOfSendEntry(SendEntryIdx));                                                                        /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
    Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_INSTANCEID_OFFSET),
      Sd_GetInstanceIdOfSendEntry(SendEntryIdx));                                                                       /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Determine the correct TTL. */
    switch(entryType)
    {
      case SD_ENTRY_FIND_SERVICE:
        usedTtl = Sd_GetTTLOfClientTimer(Sd_GetClientTimerIdxOfClient(Sd_GetClientIdxOfSendEntry(SendEntryIdx)));
        break;

      case SD_ENTRY_SUBSCRIBE_EVENTGROUP:
        usedTtl = Sd_GetTTLOfClientTimer(Sd_GetClientTimerIdxOfConsumedEventgroup(Sd_GetConsumedEventgroupIdxOfSendEntry(SendEntryIdx)));
        break;

      case SD_ENTRY_OFFER_SERVICE:
        usedTtl = Sd_GetTTLOfServerTimer(Sd_GetServerTimerIdxOfServer(Sd_GetServerIdxOfSendEntry(SendEntryIdx)));
        break;

      case SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK:
        usedTtl = Sd_GetRequestedTTLOfClientList(Sd_GetClientListIdxOfSendEntry(SendEntryIdx));
        break;

      default:
        /* STOP/NACK entry with TTL = 0 */
        usedTtl = 0u;
        break;
    }

    /* Write Major Version. */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY_MAJORVERSION_OFFSET),
      Sd_GetMajorVersionOfSendEntry(SendEntryIdx));                                                                     /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Write TTL . */
    Sd_Util_Write24Bit(Sd_GetAddrPayload((PayloadEntryIdx +  SD_ENTRY_TTL_OFFSET)), usedTtl);                           /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Write the Minor Version for send entries of format type 1 or the eventgroup ID for a format type 2 entry. */
    switch(entryType)
    {
      case SD_ENTRY_FIND_SERVICE:
        Sd_Util_Write32Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY1_MINORVERSION_OFFSET),
          Sd_GetMinorVersionOfClient(Sd_GetClientIdxOfSendEntry(SendEntryIdx)));                                        /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        break;

      case SD_ENTRY_SUBSCRIBE_EVENTGROUP:
      case SD_ENTRY_STOP_SUBSCRIBE_EVENTGROUP:
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY2_RESERVEDCOUNTER_OFFSET), 0u);                  /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY2_EVENTGROUPID_OFFSET),
          Sd_GetEventGroupIdOfConsumedEventgroup(Sd_GetConsumedEventgroupIdxOfSendEntry(SendEntryIdx)));                /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        break;

      case SD_ENTRY_OFFER_SERVICE:
      case SD_ENTRY_STOP_OFFER_SERVICE:
        Sd_Util_Write32Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY1_MINORVERSION_OFFSET),
          Sd_GetMinorVersionOfServer(Sd_GetServerIdxOfSendEntry(SendEntryIdx)));                                        /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        break;

      case SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK:
      case SD_ENTRY_SUBSCRIBE_EVENTGROUP_NACK:
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY2_RESERVEDCOUNTER_OFFSET),
          Sd_GetReservedFieldOfSendEntry(SendEntryIdx));                                                                /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadEntryIdx + SD_ENTRY2_EVENTGROUPID_OFFSET),
          Sd_GetEventHandlerIdOfSendEntry(SendEntryIdx));                                                               /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */
        break;

      default: /* COV_SD_INV_STATE */
        /* Nothing to do. */
        break;
    }
  }

  return bufferTooSmall;
}

/**********************************************************************************************************************
 *  Sd_Tx_GetRelevantEndpointOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_GetRelevantEndpointOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_SockAddrContainerType) SockAddrContainerUdpPtr,
  SD_P2VAR(Sd_SockAddrContainerType) SockAddrContainerTcpPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  SockAddrContainerUdpPtr->family = SOAD_AF_INVALID;                                                                    /* SBSW_SD_VALID_API_POINTER */
  SockAddrContainerTcpPtr->family = SOAD_AF_INVALID;                                                                    /* SBSW_SD_VALID_API_POINTER */

  /* #10 Check which type of entry shall be transmitted. */
  switch(Sd_GetEntryTypeOfSendEntry(SendEntryIdx))
  {
    case SD_ENTRY_FIND_SERVICE:
    case SD_ENTRY_SUBSCRIBE_EVENTGROUP_NACK:
      /* #100 FindService and SubscribeEventgroupNack entries do not allow any endpoint options. */
      break;

    case SD_ENTRY_OFFER_SERVICE:
    case SD_ENTRY_STOP_OFFER_SERVICE:
      {
        Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfSendEntry(SendEntryIdx);

        /* #101 (Stop)OfferService entries require unicast endpoint options.
         *      Check if the service is configured for UDP and save the address. */
        if(Sd_GetUdpSoConStartIdxOfServer(serverIdx) != SD_NO_UDPSOCONSTARTIDXOFSERVER)
        {
          (void)Sd_SoAd_GetLocalAddr(
            Sd_GetIdOfUdpSoCon(Sd_GetUdpSoConStartIdxOfServer(serverIdx)), SockAddrContainerUdpPtr);                    /* SBSW_SD_PASSING_API_POINTER */
        }

        if(SockAddrContainerUdpPtr->family == SOAD_AF_INVALID)
        {
          Sd_SizeOfEventHandlerType eventHandlerIdx;

          /* #1010 Check if the service contains an event handler which is configured for multicast. */
          for(eventHandlerIdx = Sd_GetEventHandlerStartIdxOfServer(serverIdx);
            eventHandlerIdx < Sd_GetEventHandlerEndIdxOfServer(serverIdx);
            eventHandlerIdx++)
          {
            if(Sd_EventHandlerUsesMulticast(eventHandlerIdx))
            {
              (void)Sd_SoAd_GetLocalAddr(
                Sd_GetSoConIdOfEventHandlerMulticast(Sd_GetEventHandlerMulticastIdxOfEventHandler(eventHandlerIdx)),
                SockAddrContainerUdpPtr);                                                                               /* SBSW_SD_PASSING_API_POINTER */

              break;
            }
          }
        }

        /* #102 Check if the service is configured for TCP and save the address. */
        if(Sd_GetTcpSoConIdStartIdxOfServer(serverIdx) != SD_NO_TCPSOCONIDSTARTIDXOFSERVER)
        {
          (void)Sd_SoAd_GetLocalAddr(
            Sd_GetTcpSoConId(Sd_GetTcpSoConIdStartIdxOfServer(serverIdx)), SockAddrContainerTcpPtr);                    /* SBSW_SD_PASSING_API_POINTER */
        }
      }
      break;

    case SD_ENTRY_SUBSCRIBE_EVENTGROUP:
    case SD_ENTRY_STOP_SUBSCRIBE_EVENTGROUP:
      {
        Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx = Sd_GetConsumedEventgroupIdxOfSendEntry(SendEntryIdx);

        /* #103 (Stop)SubscribeEventgroup entries allow unicast endpoint options.
         *      Check if the service is configured for UDP and save the address. */
        if(Sd_GetUdpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
        {
          (void)Sd_SoAd_GetLocalAddr(
            Sd_GetUdpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx), SockAddrContainerUdpPtr);                   /* SBSW_SD_PASSING_API_POINTER */
        }

        /* #104 Check if the service is configured for TCP and save the address. */
        if(Sd_GetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx) != SOAD_INV_SO_CON_ID)
        {
          (void)Sd_SoAd_GetLocalAddr(
            Sd_GetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx), SockAddrContainerTcpPtr);                   /* SBSW_SD_PASSING_API_POINTER */
        }
      }
      break;

    case SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK:
      {
        Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfSendEntry(SendEntryIdx);

        /* #105 SubscribeEventgroupAck entries allow multicast endpoint options.
         *      Check if the event handler is configured for multicast. */
        if(Sd_EventHandlerUsesMulticast(eventHandlerIdx))
        {
          /* #1050 Get the attached multicast endpoint. */
          (void)Sd_SoAd_GetRemoteAddr(
            Sd_GetSoConIdOfEventHandlerMulticast(Sd_GetEventHandlerMulticastIdxOfEventHandler(eventHandlerIdx)),
            SockAddrContainerUdpPtr);                                                                                   /* SBSW_SD_PASSING_API_POINTER */
        }
      }
      break;

    default: /* COV_SD_INV_STATE */
      /* #106 Undefined EntryType. */
      break;
  }
} /* PRQA S 6030 */ /* MD_MSR_STCYC */

/**********************************************************************************************************************
 *  Sd_Tx_GetRelevantConfigOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_GetRelevantConfigOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) HostnameStartIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) HostnameEndIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) CapabilityRecordStartIdxPtr,
  SD_P2VAR(Sd_SizeOfCapabilityRecordType) CapabilityRecordEndIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize start and end values. */
  *HostnameStartIdxPtr = SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE;                                                      /* SBSW_SD_VALID_API_POINTER */
  *HostnameEndIdxPtr = SD_NO_CAPABILITYRECORDENDIDXOFINSTANCE;                                                          /* SBSW_SD_VALID_API_POINTER */
  *CapabilityRecordStartIdxPtr = SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER;                                                /* SBSW_SD_VALID_API_POINTER */
  *CapabilityRecordEndIdxPtr = SD_NO_CAPABILITYRECORDENDIDXOFSERVER;                                                    /* SBSW_SD_VALID_API_POINTER */

  /* #20 Check if the entry might contain configuration options. */
  if((Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_FIND_SERVICE) ||
    (Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_OFFER_SERVICE) ||
    (Sd_GetEntryTypeOfSendEntry(SendEntryIdx) == SD_ENTRY_STOP_OFFER_SERVICE) ||
    (Sd_GetServiceIdOfSendEntry(SendEntryIdx) == SD_SERVICE_ID_OTHERSERV))
  {
    /* #200 Update the hostname start and end indexes. */
    *HostnameStartIdxPtr = Sd_GetCapabilityRecordStartIdxOfInstance(Sd_GetInstanceIdxOfSendEntry(SendEntryIdx));        /* SBSW_SD_VALID_API_POINTER */
    *HostnameEndIdxPtr = Sd_GetCapabilityRecordEndIdxOfInstance(Sd_GetInstanceIdxOfSendEntry(SendEntryIdx));            /* SBSW_SD_VALID_API_POINTER */

    /* #201 Update the capability record start and end indexes. */
    if(Sd_GetServerIdxOfSendEntry(SendEntryIdx) != Sd_GetSizeOfServer())
    {
      *CapabilityRecordStartIdxPtr = Sd_GetCapabilityRecordStartIdxOfServer(Sd_GetServerIdxOfSendEntry(SendEntryIdx));  /* SBSW_SD_VALID_API_POINTER */
      *CapabilityRecordEndIdxPtr = Sd_GetCapabilityRecordEndIdxOfServer(Sd_GetServerIdxOfSendEntry(SendEntryIdx));      /* SBSW_SD_VALID_API_POINTER */
    }
    else
    {
      *CapabilityRecordStartIdxPtr = Sd_GetCapabilityRecordStartIdxOfClient(Sd_GetClientIdxOfSendEntry(SendEntryIdx));  /* SBSW_SD_VALID_API_POINTER */
      *CapabilityRecordEndIdxPtr = Sd_GetCapabilityRecordEndIdxOfClient(Sd_GetClientIdxOfSendEntry(SendEntryIdx));      /* SBSW_SD_VALID_API_POINTER */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Tx_CheckForDuplicateOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Tx_CheckForDuplicateOption(
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isDuplicateOption = FALSE;
  uint16 tmpPayloadIdx = OptionArrayInfoPtr->ArrayStartIdx, optionOffset, optionLength;
  uint8 lastDeduplicateAbleOptionIndex = SD_INV_OPTION_INDEX;

  /* ----- Implementation ----------------------------------------------- */
  OptionArrayInfoPtr->DeduplicatedOptionIndex = SD_INV_OPTION_INDEX;                                                    /* SBSW_SD_VALID_API_POINTER */

  /* #10 Check if the payload contains the new option which was serialized after the end of the options array. */
  while(tmpPayloadIdx < OptionArrayInfoPtr->ArrayEndIdx)
  {
    /* #100 Read length of next option. */
    IPBASE_GET_UINT16(Sd_GetAddrPayload(0u), tmpPayloadIdx, optionLength);                                              /* SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES */

    /* Consider entire option. */
    optionLength += SD_OPTION_NOT_COVERED_FIELDS;

    optionOffset = 0u;
    OptionArrayInfoPtr->DeduplicatedOptionIndex++;                                                                      /* SBSW_SD_VALID_API_POINTER */
    isDuplicateOption = TRUE;

    /* #101 Compare all bytes of the already serialized option. */
    while(optionOffset < optionLength)
    {
      /* #1010 Check if the current option is equivalent to the option that has been serialized already. */
      if(Sd_GetPayload(tmpPayloadIdx + optionOffset) != Sd_GetPayload(OptionArrayInfoPtr->ArrayEndIdx + optionOffset))
      {
        /* #10100 Option does not match and cannot be used for deduplication. Skip option. */
        isDuplicateOption = FALSE;
        break;
      }

      optionOffset++;
    }

    if(isDuplicateOption == TRUE)
    {
      /* #1011 Save option for possible deduplication. Repeat searching in order to find the last matching option. */
      lastDeduplicateAbleOptionIndex = OptionArrayInfoPtr->DeduplicatedOptionIndex;
    }

    tmpPayloadIdx += optionLength;
  }

  /* #20 Check if the last serialized option can be reused for deduplication. */
  if(isDuplicateOption == TRUE)
  {
    /* #200 Return the last option. The struct member DeduplicatedOptionIndex is already set to the correct value. */
  }
  /* #30 Otherwise, if another option can be used for deduplication. */
  else if(lastDeduplicateAbleOptionIndex != SD_INV_OPTION_INDEX)
  {
    /* #300 Return the last matching option. */
    OptionArrayInfoPtr->DeduplicatedOptionIndex = lastDeduplicateAbleOptionIndex;                                       /* SBSW_SD_VALID_API_POINTER */
  }
  /* #40 Otherwise, no matching option was found.*/
  else
  {
    /* #400 Set the DeduplicatedOptionIndex to invalid. */
    OptionArrayInfoPtr->DeduplicatedOptionIndex = SD_INV_OPTION_INDEX;                                                  /* SBSW_SD_VALID_API_POINTER */
  }
}

/**********************************************************************************************************************
 *  Sd_Tx_DeduplicateOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Tx_DeduplicateOption(
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr,
  boolean RemainingOption)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean ableToDeduplicateOption = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the new option was already serialized to the payload. */
  Sd_Tx_CheckForDuplicateOption(OptionArrayInfoPtr);                                                                    /* SBSW_SD_PASSING_API_POINTER */

  if(OptionArrayInfoPtr->DeduplicatedOptionIndex != SD_INV_OPTION_INDEX)
  {
    ableToDeduplicateOption = TRUE;

    /* #100 Option was already serialized to the payload. Check if it can be deduplicated. */

    if(EntryToOptionMapPtr->Nr1stOptions == 0u)
    {
      /* #1000 Use first option run to index the option. */
      EntryToOptionMapPtr->Index1st = OptionArrayInfoPtr->DeduplicatedOptionIndex;                                      /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr1stOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if((EntryToOptionMapPtr->Index1st + EntryToOptionMapPtr->Nr1stOptions) == OptionArrayInfoPtr->DeduplicatedOptionIndex)
    {
      /* #1001 Extend first option run at the end to index new option. */
      EntryToOptionMapPtr->Nr1stOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if((EntryToOptionMapPtr->Index1st - 1u) == OptionArrayInfoPtr->DeduplicatedOptionIndex)
    {
      /* #1002 Extend first option run at the beginning to index new option. */
      EntryToOptionMapPtr->Index1st--;                                                                                  /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr1stOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if((RemainingOption == FALSE) && (EntryToOptionMapPtr->Nr2ndOptions == 0u))
    {
      /* #1003 Use second option run to index the option because there are no more pending options. */
      EntryToOptionMapPtr->Index2nd = OptionArrayInfoPtr->DeduplicatedOptionIndex;                                      /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr2ndOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if(OptionArrayInfoPtr->FreeOptionIndex == (OptionArrayInfoPtr->DeduplicatedOptionIndex + 1u))
    {
      /* #1004 Use second option run to index the option because the found option is the last one in the array. */
      EntryToOptionMapPtr->Index2nd = OptionArrayInfoPtr->DeduplicatedOptionIndex;                                      /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr2ndOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if(OptionArrayInfoPtr->FreeOptionIndex == (EntryToOptionMapPtr->Index1st + EntryToOptionMapPtr->Nr1stOptions))
    {
      /* #1005 Use second option run to index the option because the last option of the array is indexed by the current entry. */
      EntryToOptionMapPtr->Index2nd = OptionArrayInfoPtr->DeduplicatedOptionIndex;                                      /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr2ndOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if((EntryToOptionMapPtr->Nr2ndOptions != 0u) && ((EntryToOptionMapPtr->Index2nd + EntryToOptionMapPtr->Nr2ndOptions) == OptionArrayInfoPtr->DeduplicatedOptionIndex))
    {
      /* #1006 Extend second option run at the end to index new option. */
      EntryToOptionMapPtr->Nr2ndOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else if((EntryToOptionMapPtr->Nr2ndOptions != 0u) && ((EntryToOptionMapPtr->Index2nd - 1u) == OptionArrayInfoPtr->DeduplicatedOptionIndex))
    {
      /* #1007 Extend second option run at the beginning to index new option. */
      EntryToOptionMapPtr->Index2nd--;                                                                                  /* SBSW_SD_VALID_API_POINTER */
      EntryToOptionMapPtr->Nr2ndOptions++;                                                                              /* SBSW_SD_VALID_API_POINTER */
    }
    else
    {
      /* #1008 Option can not be deduplicated. */
      ableToDeduplicateOption = FALSE;
      OptionArrayInfoPtr->DeduplicatedOptionIndex = SD_INV_OPTION_INDEX;                                                /* SBSW_SD_VALID_API_POINTER */
    }
  }

  return ableToDeduplicateOption;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEndpointOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeEndpointOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SockAddrContainerType sockAddrContainerUdp, sockAddrContainerTcp;
  Sd_SizeOfCapabilityRecordType hostnameStartIdx, hostnameEndIdx;
  Sd_SizeOfCapabilityRecordType capabilityRecordStartIdx, capabilityRecordEndIdx;
  boolean bufferTooSmall = FALSE, configOptionPresent = FALSE;
  uint16 additionalOptionSize;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get relevant configuration options. */
  Sd_Tx_GetRelevantConfigOptions(SendEntryIdx, &hostnameStartIdx, &hostnameEndIdx,
    &capabilityRecordStartIdx, &capabilityRecordEndIdx);                                                                /* SBSW_SD_REFERENCE_OF_VARIABLE */

  /* #20 Check if a configuration option has to be added. */
  if((hostnameStartIdx != hostnameEndIdx) || (capabilityRecordStartIdx != capabilityRecordEndIdx))
  {
    configOptionPresent = TRUE;
  }

  /* #30 Get relevant endpoint options. */
  Sd_Tx_GetRelevantEndpointOptions(SendEntryIdx, &sockAddrContainerUdp, &sockAddrContainerTcp);                         /* SBSW_SD_REFERENCE_OF_VARIABLE */

  /* #40 Serialize UDP endpoint option. */
  if(sockAddrContainerUdp.family != SOAD_AF_INVALID)
  {
    /* #400 Serialize option to the end of the options array. */
    additionalOptionSize = Sd_Tx_SerializeEndpointOption(Sd_GetEntryTypeOfSendEntry(SendEntryIdx),
      &sockAddrContainerUdp, SD_L4PROTOCOL_UDP, OptionArrayInfoPtr->ArrayEndIdx);                                       /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #401 Check if the option could be serialized. */
    if(additionalOptionSize != SD_INV_OPTION_LENGTH)
    {
      /* #4010 Check if the option was already serialized to the payload and can be deduplicated. */
      if(FALSE == Sd_Tx_DeduplicateOption(EntryToOptionMapPtr, OptionArrayInfoPtr, TRUE))                               /* SBSW_SD_PASSING_API_POINTER */
      {
        /* #40100 Use the option, which was already serialized to the end of the payload. */
        Sd_Tx_UseNewSerializedOption(EntryToOptionMapPtr, OptionArrayInfoPtr, additionalOptionSize);                    /* SBSW_SD_PASSING_API_POINTER */
      }
    }
    else
    {
      bufferTooSmall = TRUE;
    }
  }

  /* #50 Serialize TCP endpoint option. */
  if((sockAddrContainerTcp.family != SOAD_AF_INVALID) && (bufferTooSmall == FALSE))
  {
    /* #500 Serialize option to the end of the payload. */
    additionalOptionSize = Sd_Tx_SerializeEndpointOption(Sd_GetEntryTypeOfSendEntry(SendEntryIdx),
      &sockAddrContainerTcp, SD_L4PROTOCOL_TCP, OptionArrayInfoPtr->ArrayEndIdx);                                       /* SBSW_SD_REFERENCE_OF_VARIABLE */

    /* #501 Check if the option could be serialized. */
    if(additionalOptionSize != SD_INV_OPTION_LENGTH)
    {
      /* #5010 Check if option was already serialized to the payload and can be deduplicated. */
      if(FALSE == Sd_Tx_DeduplicateOption(EntryToOptionMapPtr, OptionArrayInfoPtr, configOptionPresent))                /* SBSW_SD_PASSING_API_POINTER */
      {
        /* #50100 Use option which was serialized to the end of the payload. */
        Sd_Tx_UseNewSerializedOption(EntryToOptionMapPtr, OptionArrayInfoPtr, additionalOptionSize);                    /* SBSW_SD_PASSING_API_POINTER */
      }
    }
    else
    {
      bufferTooSmall = TRUE;
    }
  }

  return bufferTooSmall;
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeEndpointOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(uint16, SD_CODE) Sd_Tx_SerializeEndpointOption(
  Sd_EntryType SendEntryType,
  SD_P2CONST(Sd_SockAddrContainerType) LocalIpAddrPtr,
  Sd_L4ProtocolType L4Proto,
  uint16 PayloadOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionType optionType = SD_OPTION_IPV4_ENDPOINT;
  uint16 optionLength;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check family type of option. */
  if(LocalIpAddrPtr->family == SOAD_AF_INET6)
  {
    optionType = SD_OPTION_IPV6_ENDPOINT;
  }

  /* #20 Check if a multicast endpoint has to be added. */
  if(SendEntryType == SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK)
  {
    optionType = (Sd_OptionType)(optionType | SD_OPTION_MULTICAST_MASK); /*lint !e655 */
  }

  /* #30 Differentiate the option type. */
  switch(optionType)
  {
    /* #300 For IPv4 endpoint.*/
    case SD_OPTION_IPV4_ENDPOINT:
    case SD_OPTION_IPV4_MULTICAST:
      /* #3000 Check if the endpoint size exceeds the size of the payload buffer. */
      if(((Sd_SizeOfPayloadType)PayloadOffset + SD_OPTION_IPV4_SIZE) >= Sd_GetSizeOfPayload())
      {
        /* #30000 Stop processing of the endpoint option. */
        optionLength = SD_INV_OPTION_LENGTH;
      }
      /* #3001 Otherwise, serialize all fields of the IPv4 endpoint option. */
      else
      {
        /* Set the length field. */
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadOffset /* + SD_OPTION_LENGTH_OFFSET */), SD_OPTION_IPV4_COVERED_LENGTH); /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */
        optionLength = SD_OPTION_IPV4_SIZE;

        /* Set the type field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_TYPE_OFFSET), (uint8)optionType);                 /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the first reserved field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_RESERVED_OFFSET), 0u);                            /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the IP address. */
        /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
        Sd_Copy(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV4_ADDRESS_OFFSET),                                       /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
          LocalIpAddrPtr->data, SD_OPTION_IPV4_ADDRESS_SIZE);

        /* Set the second reserved field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV4_RESERVED_OFFSET), 0u);                       /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the L4-Proto field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV4_L4PROTO_OFFSET), (uint8)L4Proto);            /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the port number. */
        /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
        Sd_Copy(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV4_PORTNUMBER_OFFSET),                                    /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
          &LocalIpAddrPtr->port, SD_OPTION_IPV4_PORTNUMBER_SIZE);
      }
      break;

    /* #301 For IPv6 endpoint.*/
    case SD_OPTION_IPV6_ENDPOINT:
    case SD_OPTION_IPV6_MULTICAST:
      /* #3010 Check if the endpoint size exceeds the size of the payload buffer. */
      if(((Sd_SizeOfPayloadType)PayloadOffset + SD_OPTION_IPV6_SIZE) >= Sd_GetSizeOfPayload())
      {
        /* #30100 Stop processing of the endpoint option. */
        optionLength = SD_INV_OPTION_LENGTH;
      }
      /* #3011 Otherwise, serialize all fields of the IPv6 endpoint option. */
      else
      {
        /* Set the length field. */
        Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadOffset /* + SD_OPTION_LENGTH_OFFSET */), SD_OPTION_IPV6_COVERED_LENGTH); /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */
        optionLength = SD_OPTION_IPV6_SIZE;

        /* Set the type field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_TYPE_OFFSET), (uint8)optionType);                 /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the first reserved field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_RESERVED_OFFSET), 0u);                            /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the IP address. */
        /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
        Sd_Copy(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV6_ADDRESS_OFFSET),                                       /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
          LocalIpAddrPtr->data, SD_OPTION_IPV6_ADDRESS_SIZE);

        /* Set the second reserved field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV6_RESERVED_OFFSET), 0u);                       /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the L4-Proto field. */
        Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV6_L4PROTO_OFFSET), (uint8)L4Proto);            /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

        /* Set the port number. */
        /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
        Sd_Copy(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_IPV6_PORTNUMBER_OFFSET),                                    /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
          &LocalIpAddrPtr->port, SD_OPTION_IPV6_PORTNUMBER_SIZE);
      }
      break;

    /* #302 Undefined OptionType. */
    default: /* COV_SD_INV_STATE */
      /* #3020 Do not process the option. */
      optionLength = 0u;
      break;
  }

  return optionLength;
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeConfigurationOptions()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(boolean, SD_CODE) Sd_Tx_SerializeConfigurationOptions(
  Sd_SizeOfSendEntryType SendEntryIdx,
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfCapabilityRecordType hostnameStartIdx, hostnameEndIdx;
  Sd_SizeOfCapabilityRecordType capabilityRecordStartIdx, capabilityRecordEndIdx;
  boolean bufferTooSmall = FALSE;
  uint16 additionalOptionSize;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get relevant configuration options. */
  Sd_Tx_GetRelevantConfigOptions(SendEntryIdx, &hostnameStartIdx, &hostnameEndIdx,
    &capabilityRecordStartIdx, &capabilityRecordEndIdx);                                                                /* SBSW_SD_REFERENCE_OF_VARIABLE */

  /* #20 Check if hostname has to be added as configuration option. */
  if(hostnameStartIdx != hostnameEndIdx)
  {
    /* #200 Build and attach the configuration option. */
    additionalOptionSize = Sd_Tx_SerializeConfigurationOption(hostnameStartIdx, hostnameEndIdx,
      OptionArrayInfoPtr->ArrayEndIdx);

    /* #201 Check if the option could be serialized. */
    if(additionalOptionSize != SD_INV_OPTION_LENGTH)
    {
      /* #2010 Check if option was already serialized to the payload and can be deduplicated. */
      if(FALSE == Sd_Tx_DeduplicateOption(EntryToOptionMapPtr, OptionArrayInfoPtr,
        (boolean)(capabilityRecordStartIdx != capabilityRecordEndIdx)))                                                 /* SBSW_SD_PASSING_API_POINTER */
      {
        /* #20100 Use option which was serialized to the end of the payload. */
        Sd_Tx_UseNewSerializedOption(EntryToOptionMapPtr, OptionArrayInfoPtr, additionalOptionSize);                    /* SBSW_SD_PASSING_API_POINTER */
      }
    }
    else
    {
      bufferTooSmall = TRUE;
    }
  }

  /* #30 Check if capability records have to be added as configuration option. */
  if(capabilityRecordStartIdx != capabilityRecordEndIdx)
  {
    /* #300 Build and attach the configuration option. */
    additionalOptionSize = Sd_Tx_SerializeConfigurationOption(capabilityRecordStartIdx, capabilityRecordEndIdx,
      OptionArrayInfoPtr->ArrayEndIdx);

    /* #301 Check if the option could be serialized. */
    if(additionalOptionSize != SD_INV_OPTION_LENGTH)
    {
      /* #3010 Check if option was already serialized to the payload and can be deduplicated. */
      if(FALSE == Sd_Tx_DeduplicateOption(EntryToOptionMapPtr, OptionArrayInfoPtr, FALSE))                              /* SBSW_SD_PASSING_API_POINTER */
      {
        /* #30100 Use option which was serialized to the end of the payload. */
        Sd_Tx_UseNewSerializedOption(EntryToOptionMapPtr, OptionArrayInfoPtr, additionalOptionSize);                    /* SBSW_SD_PASSING_API_POINTER */
      }
    }
    else
    {
      bufferTooSmall = TRUE;
    }
  }

  return bufferTooSmall;
}

/**********************************************************************************************************************
 *  Sd_Tx_SerializeConfigurationOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(uint16, SD_CODE) Sd_Tx_SerializeConfigurationOption(
  Sd_SizeOfCapabilityRecordType ConfigurationOptionStartIdx,
  Sd_SizeOfCapabilityRecordType ConfigurationOptionEndIdx,
  uint16 PayloadOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfCapabilityRecordType configurationOptionLength = ConfigurationOptionEndIdx - ConfigurationOptionStartIdx;
  uint16 writtenBytes;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the configuration option fits into the buffer. */
  if(((Sd_SizeOfPayloadType)PayloadOffset + SD_OPTION_CONFIG_FIXED_HEADER_SIZE + configurationOptionLength) <= Sd_GetSizeOfPayload())
  {
    /* #100 Set the type field. */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_TYPE_OFFSET), SD_OPTION_CONFIGURATION);               /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

    /* #101 Set the reserved field. */
    Sd_Util_Write8Bit(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_RESERVED_OFFSET), 0u);                                /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */

    /* #102 Add the configuration option. */
    /* PRQA S 0314 1 */ /* MD_MSR_VStdLibCopy */
    Sd_Copy(Sd_GetAddrPayload(PayloadOffset + SD_OPTION_CONFIG_STRING_OFFSET),                                          /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */ /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION */
      Sd_GetAddrCapabilityRecord(ConfigurationOptionStartIdx), configurationOptionLength);

    /* #103 Set the length of the capability record. */
    writtenBytes = (uint16)(SD_OPTION_CONFIG_STRING_OFFSET + (uint16)configurationOptionLength);
    Sd_Util_Write16Bit(Sd_GetAddrPayload(PayloadOffset /* + SD_OPTION_LENGTH_OFFSET */),
      (uint16)(writtenBytes - SD_OPTION_NOT_COVERED_FIELDS));                                                           /* SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY */
  }
  /* #20 Otherwise, buffer too small. */
  else
  {
    /* #200 Invalidate the length information of the written bytes. */
    writtenBytes = SD_INV_OPTION_LENGTH;
  }

  return writtenBytes;
}

/**********************************************************************************************************************
 *  Sd_Tx_UseNewSerializedOption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Tx_UseNewSerializedOption(
  SD_P2VAR(Sd_EntryToOptionMapType) EntryToOptionMapPtr,
  SD_P2VAR(Sd_OptionArrayInfoType) OptionArrayInfoPtr,
  uint16 NewOptionSize)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Use option which was serialized to the end of the payload.
   *     Check if the option can be referenced by the first or the second option run. */

  if(EntryToOptionMapPtr->Nr1stOptions == 0u)
  {
    /* #100 Use first option run to index the option. */
    EntryToOptionMapPtr->Index1st = OptionArrayInfoPtr->FreeOptionIndex;                                                /* SBSW_SD_VALID_API_POINTER */
    EntryToOptionMapPtr->Nr1stOptions++;                                                                                /* SBSW_SD_VALID_API_POINTER */
  }
  else if(OptionArrayInfoPtr->FreeOptionIndex == (EntryToOptionMapPtr->Index1st + EntryToOptionMapPtr->Nr1stOptions))
  {
    /* #101 Extend first option run at the end to index new option. */
    EntryToOptionMapPtr->Nr1stOptions++;                                                                                /* SBSW_SD_VALID_API_POINTER */
  }
  else if(EntryToOptionMapPtr->Nr2ndOptions == 0u)
  {
    /* #102 Use second option run to index the option. */
    EntryToOptionMapPtr->Index2nd = OptionArrayInfoPtr->FreeOptionIndex;                                                /* SBSW_SD_VALID_API_POINTER */
    EntryToOptionMapPtr->Nr2ndOptions++;                                                                                /* SBSW_SD_VALID_API_POINTER */
  }
  else /* (OptionArrayInfoPtr->FreeOptionIndex == (EntryToOptionMapPtr->Index2nd + EntryToOptionMapPtr->Nr2ndOptions) */
  {
    /* #103 Extend second option run at the end to index new option. */
    EntryToOptionMapPtr->Nr2ndOptions++;                                                                                /* SBSW_SD_VALID_API_POINTER */
  }

  OptionArrayInfoPtr->FreeOptionIndex++;                                                                                /* SBSW_SD_VALID_API_POINTER */
  OptionArrayInfoPtr->ArrayEndIdx += NewOptionSize;                                                                     /* SBSW_SD_VALID_API_POINTER */
}

/**********************************************************************************************************************
 *  Sd_UtilClient_CloseAllMulticastSoCons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_CloseAllMulticastSoCons(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_MulticastSoConIdIterType multicastSoConIdIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Close all multicast socket connections of the client. */
  for(multicastSoConIdIdx = Sd_GetMulticastSoConIdStartIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
    multicastSoConIdIdx < Sd_GetMulticastSoConIdEndIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
    multicastSoConIdIdx++)
  {
    (void)SoAd_CloseSoCon(Sd_GetMulticastSoConId(multicastSoConIdIdx), Abort);
  }
}

/**********************************************************************************************************************
 *  Sd_UtilClient_ResetDynamicVariables()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_ResetDynamicVariables(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset dynamic variables. */
  Sd_SetStateMachineOfClientDyn(ClientIdx, SD_CLIENT_STATE_NONE);                                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetStateMachineExecutionRequestedOfClientDyn(ClientIdx, TRUE);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetEventRxOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetEventMainOfClientDyn(ClientIdx, SD_CLIENT_EVENT_SERVICE_NONE);                                                  /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetAddressStorageServerIdxOfClientDyn(ClientIdx, Sd_GetSizeOfAddressStorage());                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  (Sd_GetAddrServerTcpEndpointAddrOfClientDyn(ClientIdx))->family = SOAD_AF_INVALID;                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  (Sd_GetAddrServerUdpEndpointAddrOfClientDyn(ClientIdx))->family = SOAD_AF_INVALID;                                    /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetMethodUdpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetMethodTcpSoConIdOfClientDyn(ClientIdx, SOAD_INV_SO_CON_ID);                                                     /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_SetOfferedTTLOfClientDyn(ClientIdx, 0u);                                                                           /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_ResetTimerToZero(Sd_GetAddrTimerTTLOfClientDyn(ClientIdx));                                                   /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  Sd_Util_ResetTimerToInvalid(Sd_GetAddrTimeToTriggerSendOfClientDyn(ClientIdx));                                       /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  Sd_SetRepetitionRunOfClientDyn(ClientIdx, 0u);                                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  Sd_Util_ResetTimerToInvalid(Sd_GetAddrRetryTimerOfClientDyn(ClientIdx));                                              /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE */
  Sd_SetRetryCounterOfClientDyn(ClientIdx, 0u);                                                                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
}

/**********************************************************************************************************************
 *  Sd_UtilClient_LocalIpAddrAssignmentChgReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilClient_LocalIpAddrAssignmentChgReset(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset dynamic variables of all clients with and all consumed event groups. */
  for(clientIdx = Sd_GetClientStartIdxOfInstance(InstanceIdx);
    clientIdx < Sd_GetClientEndIdxOfInstance(InstanceIdx);
    clientIdx++)
  {
    Sd_SizeOfConsumedEventgroupType consumedEventgroupIdx;

    for(consumedEventgroupIdx = Sd_GetConsumedEventgroupStartIdxOfClient(clientIdx);
      consumedEventgroupIdx < Sd_GetConsumedEventgroupEndIdxOfClient(clientIdx);
      consumedEventgroupIdx++)
    {
      /* #1000 Release the multicast IP address of the consumed eventgroup. */
      (void)Sd_StateClient_ReleaseIpAddrAssignment(Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx));

      /* #1001 Reset dynamic variables of the consumed eventgroup. */
      Sd_SetEventOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CLIENT_EVENT_EVENTGROUP_NONE);                       /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(consumedEventgroupIdx, 0u);                                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_Util_ResetTimerToZero(Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(consumedEventgroupIdx));                       /* SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE */

      Sd_SetTcpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                               /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_SetUdpSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                               /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(consumedEventgroupIdx, SOAD_INV_SO_CON_ID);                         /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */

      if(Sd_IsMulticastEndpointAddrUsedOfConsumedEventgroup(consumedEventgroupIdx))
      {
        Sd_MulticastEndpointAddrIdxOfConsumedEventgroupType multicastEndpointAddrIdx =
          Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(consumedEventgroupIdx);

        (Sd_GetAddrMulticastEndpointAddr(multicastEndpointAddrIdx))->family = SOAD_AF_INVALID;                          /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      }

      /* #1002 Inform the BswM about the state of the consumed eventgroups. */
      BswM_Sd_ConsumedEventGroupCurrentState(
        Sd_GetHandleIdOfConsumedEventgroup(consumedEventgroupIdx), SD_CONSUMED_EVENTGROUP_DOWN);
      Sd_SetCurrentStateOfConsumedEventgroupDyn(consumedEventgroupIdx, SD_CONSUMED_EVENTGROUP_DOWN);                    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
    }

    /* #200 Reset dynamic variables of the client. */
    Sd_UtilClient_ResetDynamicVariables(clientIdx);

    /* #201 Inform the BswM about the state of the client service instance. */
    Sd_UtilClient_SetCurrentStateInformBswm(clientIdx, SD_CLIENT_SERVICE_DOWN);
  }
}

/**********************************************************************************************************************
 *  Sd_UtilClient_SetCurrentStateInformBswm()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_UtilClient_SetCurrentStateInformBswm(
  Sd_SizeOfClientType ClientIdx,
  Sd_ClientServiceCurrentStateType State)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the current state of the client. */
  Sd_SetCurrentStateOfClientDyn(ClientIdx, State);                                                                      /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  /* #20 Inform the BswM about the state of the client service instance. */
  BswM_Sd_ClientServiceCurrentState(Sd_GetHandleIdOfClient(ClientIdx), State);
}

/**********************************************************************************************************************
 *  Sd_Util_SetTcpSoConMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTcpSoConMode(
  SoAd_SoConIdType SoConId,
  SoAd_SoConModeType Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_TcpSoConIdIterType soConIdIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search for the SoConId. */
  for(soConIdIdx = 0u; soConIdIdx < Sd_GetSizeOfTcpSoConId(); soConIdIdx++)
  {
    if(SoConId == Sd_GetTcpSoConId(soConIdIdx))
    {
      /* #100 Found the socket connection. Save mode of the connection. */
      Sd_SetTcpSoConModeMap(soConIdIdx, (Sd_SoConModeType)Mode);                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
      break;
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Util_GetTcpSoConMode()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_SoConModeType, SD_CODE) Sd_Util_GetTcpSoConMode(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SoConModeType tmpSoConMode = SD_SOCON_MODE_OFFLINE;
  Sd_TcpSoConIdIterType soConIdIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Search for the SoConId. */
  for(soConIdIdx = 0u; soConIdIdx < Sd_GetSizeOfTcpSoConId(); soConIdIdx++)
  {
    if(SoConId == Sd_GetTcpSoConId(soConIdIdx))
    {
      /* #100 Found the socket connection. Return the actual mode. */
      tmpSoConMode = Sd_GetTcpSoConModeMap(soConIdIdx);
      break;
    }
  }

  return tmpSoConMode;
}

/**********************************************************************************************************************
 *  Sd_Util_ResetSessionIds()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetSessionIds(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfAddressStorageType addressStorageIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over the address storage. */
  for(addressStorageIdx = Sd_GetAddressStorageStartIdxOfInstance(InstanceIdx);
    addressStorageIdx < Sd_GetAddressStorageEndIdxOfInstance(InstanceIdx);
    addressStorageIdx++)
  {
    /* #100 Check if the address is in use. */
    if(Sd_GetSessionIdCounterOfAddressStorage(addressStorageIdx) != 0u)
    {
      /* #1000 Reset the SessionID of this address. */
      Sd_SetSessionIdCounterOfAddressStorage(addressStorageIdx, 1u);                                                    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    }
  }
}

/**********************************************************************************************************************
 *  Sd_Util_GetEmptySendEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_SizeOfSendEntryType, SD_CODE) Sd_Util_GetEmptySendEntry(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType tmpEntryIdx, emptyIdx;

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  emptyIdx = Sd_GetSendEntryEndIdxOfInstance(InstanceIdx);
  tmpEntryIdx = Sd_GetSendEntryStartIdxOfInstanceDyn(InstanceIdx);

  /* #10 Check if the list of send entries is empty. */
  if(tmpEntryIdx == SD_NO_SENDENTRYSTARTIDXOFINSTANCEDYN)
  {
    /* #100 Send entry list is empty. Choose the first element. */
    emptyIdx = Sd_GetSendEntryStartIdxOfInstance(InstanceIdx);
    Sd_SetValidOfSendEntry(emptyIdx, TRUE);                                                                             /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    Sd_SetSendEntryNextIdxOfSendEntry(emptyIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
    Sd_IncSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx);                                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_SetSendEntryStartIdxOfInstanceDyn(InstanceIdx, emptyIdx);                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_SetSendEntryEndIdxOfInstanceDyn(InstanceIdx, emptyIdx);                                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

    SD_END_CRITICAL_SECTION();
  }
  else
  {
    /* #101 Otherwise, search for a free slot. */
    for(tmpEntryIdx = Sd_GetSendEntryStartIdxOfInstance(InstanceIdx);
      tmpEntryIdx < Sd_GetSendEntryEndIdxOfInstance(InstanceIdx);
      tmpEntryIdx++)
    {
      if(!Sd_IsValidOfSendEntry(tmpEntryIdx))
      {
        /* #10100 Found an empty slot. */
        emptyIdx = tmpEntryIdx;
        break;
      }
    }

    /* #102 Check if an empty slot was found. */
    if(emptyIdx != Sd_GetSendEntryEndIdxOfInstance(InstanceIdx))
    {
      /* #1021 Found an empty slot, save the new send entry. */
      Sd_SetValidOfSendEntry(emptyIdx, TRUE);                                                                           /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_SetSendEntryNextIdxOfSendEntry(emptyIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
      Sd_IncSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx);                                                            /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

      /* #1022 Update the linked list. */
      Sd_SetSendEntryNextIdxOfSendEntry(Sd_GetSendEntryEndIdxOfInstanceDyn(InstanceIdx), emptyIdx);                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */
      Sd_SetSendEntryEndIdxOfInstanceDyn(InstanceIdx, emptyIdx);                                                        /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

      SD_END_CRITICAL_SECTION();
    }
    else
    {
      SD_END_CRITICAL_SECTION();

      /* #1023 Otherwise, not able to save additional send entry. Trigger DET error. */
#if(SD_DEV_ERROR_REPORT == STD_ON)
      (void)Det_ReportError(SD_MODULE_ID, SD_INSTANCE_ID, SD_SID_SAVE_SENDENTRY_IN_LIST, SD_E_SEND_ENTRY_LIST_FULL);
#endif
    }
  }

  return emptyIdx;
}

/**********************************************************************************************************************
 *  Sd_Util_RemoveSendEntryFromList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_RemoveSendEntryFromList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfSendEntryType RemoveEntryIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType tmpEntryIdx;

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Check if the entry to be removed is the first entry of the linked list. */
  if(Sd_GetSendEntryStartIdxOfInstanceDyn(InstanceIdx) == RemoveEntryIdx)
  {
    /* #100 Invalidate the entry. */
    /* PRQA S 2853 5 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
    Sd_SetSendEntryStartIdxOfInstanceDyn(InstanceIdx, Sd_GetSendEntryNextIdxOfSendEntry(RemoveEntryIdx));               /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_SetValidOfSendEntry(RemoveEntryIdx, FALSE);                                                                      /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_SetSendEntryNextIdxOfSendEntry(RemoveEntryIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                               /* SBSW_SD_API_ARGUMENT_IDX */
    Sd_DecSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx);                                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    Sd_DecSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageIdxOfSendEntry(RemoveEntryIdx));                    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    /* #101 Check if the entry to remove is also the last entry of the linked list. */
    if(Sd_GetSendEntryEndIdxOfInstanceDyn(InstanceIdx) == RemoveEntryIdx)
    {
      /* #1010 The list is empty, update the end index. */
      Sd_SetSendEntryEndIdxOfInstanceDyn(InstanceIdx, SD_NO_SENDENTRYENDIDXOFINSTANCEDYN);                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }
  else
  {
    /* #102 Otherwise, search the predecessor of the RemoveEntryIdx. */
    for(tmpEntryIdx = Sd_GetSendEntryStartIdxOfInstance(InstanceIdx);
      tmpEntryIdx < Sd_GetSendEntryEndIdxOfInstance(InstanceIdx);
      tmpEntryIdx++)
    {
      if(Sd_GetSendEntryNextIdxOfSendEntry(tmpEntryIdx) == RemoveEntryIdx)
      {
        /* #1020 Update the next entry index of the predecessor. */
        /* PRQA S 2853 1 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
        Sd_SetSendEntryNextIdxOfSendEntry(tmpEntryIdx, Sd_GetSendEntryNextIdxOfSendEntry(RemoveEntryIdx));              /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE */

        /* #1021 Invalidate the entry. */
        /* PRQA S 2853 4 */ /* MD_Sd_FalsePositive_2995_2996_2853 */
        Sd_SetValidOfSendEntry(RemoveEntryIdx, FALSE);                                                                  /* SBSW_SD_API_ARGUMENT_IDX */
        Sd_SetSendEntryNextIdxOfSendEntry(RemoveEntryIdx, SD_NO_SENDENTRYNEXTIDXOFSENDENTRY);                           /* SBSW_SD_API_ARGUMENT_IDX */
        Sd_DecSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx);                                                          /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
        Sd_DecSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageIdxOfSendEntry(RemoveEntryIdx));                /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

        /* #1022 Check if the entry to remove is the last entry of the linked list. */
        if(Sd_GetSendEntryEndIdxOfInstanceDyn(InstanceIdx) == RemoveEntryIdx)
        {
          /* #10220 Update the end index of the list. */
          Sd_SetSendEntryEndIdxOfInstanceDyn(InstanceIdx, tmpEntryIdx);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
        }

        break;
      }
    }
  }

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_CheckSendEntryListFullAndTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_CheckSendEntryListFullAndTransmit(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the list with pending send entries is full. */
  if(Sd_GetSendEntryNrPendingIdxOfInstanceDyn(InstanceIdx) >=
    (Sd_GetSendEntryEndIdxOfInstance(InstanceIdx) - Sd_GetSendEntryStartIdxOfInstance(InstanceIdx)))
  {
    /* #100 The send entry list is full, trigger a transmission. */
    Sd_Tx_ProcessPendingMessages(InstanceIdx, TRUE);
  }
}

/**********************************************************************************************************************
 *  Sd_Util_AddFindEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddFindEntryToList(
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(instanceIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* Currently the specification does not support sending FindService entries using unicast. */
  /* #10 Check if the send entry list contains a free slot. */
  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(instanceIdx))
  {
    /* #100 Save all information relevant for SD_ENTRY_FIND_SERVICE entry. */

    Sd_UtilClient_ConfigureEntry(sendEntryIdx, ClientIdx);

    Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_FIND_SERVICE);                                                    /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, Sd_GetAddressStorageStartIdxOfInstance(instanceIdx));              /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageStartIdxOfInstance(instanceIdx));                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    Sd_Util_ResetTimerToZero(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx));                                            /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(instanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_AddMulticastOfferEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddMulticastOfferEntryToList(
  Sd_SizeOfServerType ServerIdx,
  boolean StopOffer)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(instanceIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the send entry list contains a free slot. */
  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(instanceIdx))
  {
    /* #100 Save all information relevant for multicast SD_ENTRY_(STOP)_OFFER_SERVICE entry. */

    Sd_UtilServer_ConfigureEntry(sendEntryIdx, ServerIdx);

    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, Sd_GetAddressStorageStartIdxOfInstance(instanceIdx));              /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageStartIdxOfInstance(instanceIdx));                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    if(StopOffer == FALSE)
    {
      Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_OFFER_SERVICE);                                                 /* SBSW_SD_SEND_ENTRY_IDX */
    }
    else
    {
      Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_STOP_OFFER_SERVICE);                                            /* SBSW_SD_SEND_ENTRY_IDX */
    }

    Sd_SetEventHandlerIdOfSendEntry(sendEntryIdx, 0u);                                      /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetReservedFieldOfSendEntry(sendEntryIdx, 0u);                                       /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_Util_ResetTimerToZero(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx));                                            /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(instanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_AddUnicastOfferEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddUnicastOfferEntryToList(
  Sd_SizeOfServerType ServerIdx,
  Sd_SizeOfAddressStorageType SavedAddressStorageIdx,
  uint32 TransmissionOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(instanceIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the send entry list contains a free slot. */
  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(instanceIdx))
  {
    /* #100 Save all information relevant for unicast SD_ENTRY_OFFER_SERVICE entry. */

    Sd_UtilServer_ConfigureEntry(sendEntryIdx, ServerIdx);

    Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_OFFER_SERVICE);                                                   /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, SavedAddressStorageIdx);                                           /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(SavedAddressStorageIdx);                                                /* SBSW_SD_API_ARGUMENT_IDX */

    Sd_SetEventHandlerIdOfSendEntry(sendEntryIdx, 0u);                                      /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetReservedFieldOfSendEntry(sendEntryIdx, 0u);                                       /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_Util_SetTimerOffset(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx), TransmissionOffset);                          /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(instanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_AddSubscribeEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddSubscribeEntryToList(
  Sd_SizeOfConsumedEventgroupType ConsumedEventgroupIdx,
  boolean Subscribe,
  uint32 TransmissionOffset)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfClientType clientIdx = Sd_GetClientIdxOfConsumedEventgroup(ConsumedEventgroupIdx);
  Sd_SizeOfInstanceType instanceIdx = Sd_GetInstanceIdxOfClient(clientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the send entry list contains a free slot. */
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(instanceIdx);

  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(instanceIdx))
  {
    /* #100 Save all information relevant for SD_ENTRY_(STOP)_SUBSCRIBE_EVENTGROUP entry. */
    Sd_UtilClient_ConfigureEntry(sendEntryIdx, clientIdx);

    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, Sd_GetAddressStorageServerIdxOfClientDyn(clientIdx));              /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageServerIdxOfClientDyn(clientIdx));                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    if(Subscribe == TRUE)
    {
      Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_SUBSCRIBE_EVENTGROUP);                                          /* SBSW_SD_SEND_ENTRY_IDX */
    }
    else
    {
      Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_STOP_SUBSCRIBE_EVENTGROUP);                                     /* SBSW_SD_SEND_ENTRY_IDX */
    }

    Sd_SetConsumedEventgroupIdxOfSendEntry(sendEntryIdx, ConsumedEventgroupIdx);                                        /* SBSW_SD_SEND_ENTRY_IDX */

    Sd_SetEventHandlerIdOfSendEntry(sendEntryIdx, Sd_GetEventGroupIdOfConsumedEventgroup(ConsumedEventgroupIdx));       /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_Util_SetTimerOffset(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx), TransmissionOffset);                          /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(instanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_AddEventGroupAckEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddEventGroupAckEntryToList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfRxEventType RxEventIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(InstanceIdx);
  uint32 AdditionalDelay = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the send entry list contains a free slot. */
  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(InstanceIdx))
  {
    /* #100 Save all information relevant for SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK entry. */
    Sd_SizeOfEventHandlerType eventHandlerIdx = Sd_GetEventHandlerIdxOfRxEvent(RxEventIdx);
    Sd_SizeOfServerType serverIdx = Sd_GetServerIdxOfEventHandler(eventHandlerIdx);
    Sd_SizeOfClientListType clientListIdx = Sd_GetClientListIdxOfRxEvent(RxEventIdx);

    Sd_UtilServer_ConfigureEntry(sendEntryIdx, serverIdx);

    /* Update the entry list. */
    Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_SUBSCRIBE_EVENTGROUP_ACK);                                        /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, Sd_GetAddressStorageIdxOfClientList(clientListIdx));               /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(Sd_GetAddressStorageIdxOfClientList(clientListIdx));                    /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    Sd_SetEventHandlerIdxOfSendEntry(sendEntryIdx, eventHandlerIdx);                                                    /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetClientListIdxOfSendEntry(sendEntryIdx, clientListIdx);                                                        /* SBSW_SD_SEND_ENTRY_IDX */

    Sd_SetEventHandlerIdOfSendEntry(sendEntryIdx, Sd_GetEventGroupIdOfEventHandler(eventHandlerIdx));                   /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetReservedFieldOfSendEntry(sendEntryIdx, Sd_GetRxReservedOfClientList(clientListIdx));                          /* SBSW_SD_SEND_ENTRY_IDX */

    if(Sd_GetEventOfRxEvent(RxEventIdx) == SD_SERVER_EVENT_EVENTGROUP_SUBSCRIBE_MULTI)
    {
      AdditionalDelay = Sd_Util_GetRandomNrInRangeForResponse(
        Sd_GetRequestResponseMinDelayOfServerTimer(Sd_GetServerTimerIdxOfEventHandler(eventHandlerIdx)),
        Sd_GetRequestResponseMaxDelayOfServerTimer(Sd_GetServerTimerIdxOfEventHandler(eventHandlerIdx)),
        FALSE);
    }

    Sd_Util_SetTimerOffset(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx), AdditionalDelay);                             /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(InstanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_AddEventGroupNackEntryToList()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_AddEventGroupNackEntryToList(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_SizeOfServerType ServerIdx,
  uint16 ServiceId,
  uint16 InstanceId,
  uint8 MajorVersion,
  uint16 ReservedField,
  uint16 EventHandlerId,
  Sd_SizeOfAddressStorageType AddressStorageIdx,
  Sd_SizeOfServerTimerType ServerTimerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfSendEntryType sendEntryIdx = Sd_Util_GetEmptySendEntry(InstanceIdx);
  uint32 additionalDelay = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the send entry list contains a free slot. */
  if(sendEntryIdx != Sd_GetSendEntryEndIdxOfInstance(InstanceIdx))
  {
    /* #100 Save all information relevant for SD_ENTRY_SUBSCRIBE_EVENTGROUP_NACK entry. */
    Sd_SetEntryTypeOfSendEntry(sendEntryIdx, SD_ENTRY_SUBSCRIBE_EVENTGROUP_NACK);                                       /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetAddressStorageIdxOfSendEntry(sendEntryIdx, AddressStorageIdx);                                                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_IncSendEntryNrPendingIdxOfAddressStorage(AddressStorageIdx);                                                     /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */

    Sd_SetInstanceIdxOfSendEntry(sendEntryIdx, InstanceIdx);                                                            /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetClientIdxOfSendEntry(sendEntryIdx, Sd_GetSizeOfClient());                         /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetConsumedEventgroupIdxOfSendEntry(sendEntryIdx, Sd_GetSizeOfConsumedEventgroup()); /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetServerIdxOfSendEntry(sendEntryIdx, ServerIdx);                                                                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetEventHandlerIdxOfSendEntry(sendEntryIdx, Sd_GetSizeOfEventHandler());             /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetClientListIdxOfSendEntry(sendEntryIdx, Sd_GetSizeOfClientList());                 /* UNUSED */                /* SBSW_SD_SEND_ENTRY_IDX */

    Sd_SetServiceIdOfSendEntry(sendEntryIdx, ServiceId);                                                                /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetInstanceIdOfSendEntry(sendEntryIdx, InstanceId);                                                              /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetMajorVersionOfSendEntry(sendEntryIdx, MajorVersion);                                                          /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetEventHandlerIdOfSendEntry(sendEntryIdx, EventHandlerId);                                                      /* SBSW_SD_SEND_ENTRY_IDX */
    Sd_SetReservedFieldOfSendEntry(sendEntryIdx, ReservedField);                                                        /* SBSW_SD_SEND_ENTRY_IDX */

    if(ServerTimerIdx != Sd_GetSizeOfServerTimer())
    {
      additionalDelay = Sd_Util_GetRandomNrInRangeForResponse(
        Sd_GetRequestResponseMinDelayOfServerTimer(ServerTimerIdx),
        Sd_GetRequestResponseMaxDelayOfServerTimer(ServerTimerIdx), TRUE);
    }

    Sd_Util_SetTimerOffset(Sd_GetAddrTimeToSendOfSendEntry(sendEntryIdx), additionalDelay);                             /* SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX */
  }

  /* #20 Check if the list of send entries is full and trigger a transmission. */
  Sd_Util_CheckSendEntryListFullAndTransmit(InstanceIdx);
} /* PRQA S 6060 */ /* MD_Sd_STPAR_6060 */

/**********************************************************************************************************************
 *  Sd_UtilServer_ConfigureEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilServer_ConfigureEntry(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfServerType ServerIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_InstanceIdxOfServerType instanceIdx = Sd_GetInstanceIdxOfServer(ServerIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all used parameters of the send entry element. */
  Sd_SetInstanceIdxOfSendEntry(SendEntryIdx, instanceIdx);                                                              /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetServerIdxOfSendEntry(SendEntryIdx, ServerIdx);                                                                  /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetServiceIdOfSendEntry(SendEntryIdx, Sd_GetServiceIdOfServer(ServerIdx));                                         /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetInstanceIdOfSendEntry(SendEntryIdx, Sd_GetInstanceIdOfServer(ServerIdx));                                       /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetMajorVersionOfSendEntry(SendEntryIdx, Sd_GetMajorVersionOfServer(ServerIdx));                                   /* SBSW_SD_SEND_ENTRY_IDX */

  /* #20 Initialize all unused parameters of the send entry element with invalid values. */
  Sd_SetClientIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfClient());                                   /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetConsumedEventgroupIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfConsumedEventgroup());           /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetEventHandlerIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfEventHandler());                       /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetClientListIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfClientList());                           /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetEventHandlerIdOfSendEntry(SendEntryIdx, 0u);                                                /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetReservedFieldOfSendEntry(SendEntryIdx, 0u);                                                 /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
}

/**********************************************************************************************************************
 *  Sd_UtilClient_ConfigureEntry()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_UtilClient_ConfigureEntry(
  Sd_SizeOfSendEntryType SendEntryIdx,
  Sd_SizeOfClientType ClientIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_InstanceIdxOfClientType instanceIdx = Sd_GetInstanceIdxOfClient(ClientIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize all used parameters of the send entry element. */
  Sd_SetInstanceIdxOfSendEntry(SendEntryIdx, instanceIdx);                                                              /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetClientIdxOfSendEntry(SendEntryIdx, ClientIdx);                                                                  /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetServiceIdOfSendEntry(SendEntryIdx, Sd_GetServiceIdOfClient(ClientIdx));                                         /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetInstanceIdOfSendEntry(SendEntryIdx, Sd_GetInstanceIdOfClient(ClientIdx));                                       /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetMajorVersionOfSendEntry(SendEntryIdx, Sd_GetMajorVersionOfClient(ClientIdx));                                   /* SBSW_SD_SEND_ENTRY_IDX */

  /* #20 Initialize all unused parameters of the send entry element with invalid values. */
  Sd_SetServerIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfServer());                                   /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetEventHandlerIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfEventHandler());                       /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetClientListIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfClientList());                           /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetConsumedEventgroupIdxOfSendEntry(SendEntryIdx, Sd_GetSizeOfConsumedEventgroup());           /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */

  Sd_SetEventHandlerIdOfSendEntry(SendEntryIdx, 0u);                                                /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
  Sd_SetReservedFieldOfSendEntry(SendEntryIdx, 0u);                                                 /* UNUSED */        /* SBSW_SD_SEND_ENTRY_IDX */
}

/**********************************************************************************************************************
 *  Sd_Util_CopySockAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_CopySockAddr(
  SD_P2VAR(Sd_SockAddrContainerType) TgtSockPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SrcSockPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Copy the socket address. */
  /* PRQA S 0310 1 */ /* MD_Sd_11.4_0310 */
  retVal = IpBase_CopySockAddr((SD_P2VAR(IpBase_SockAddrType))TgtSockPtr, (SD_P2CONST(IpBase_SockAddrType))SrcSockPtr); /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_SOCK_ADDR_CAST */

  if(retVal == E_NOT_OK)
  {
    /* #100 Source address is invalid, set the target address as invalid. */
    TgtSockPtr->family = SOAD_AF_INVALID;                                                                               /* SBSW_SD_VALID_API_POINTER */
  }
}

/**********************************************************************************************************************
 *  Sd_Util_CompareSockAddrIp()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_MatchType, SD_CODE) Sd_Util_CompareSockAddrIp(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 AddrState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_MatchType matchType = SD_MATCH_FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check family type of both socket addresses. */
  if(SockAPtr->family == SockBPtr->family)
  {
    /* #100 Check if the address state defines ANY possible IP address. */
    if((AddrState & SOAD_SOCON_MASK_IPADDR & SOAD_SOCON_MASK_ANY) != 0u)
    {
      matchType = SD_MATCH_ANY;
    }
    else
    {
      /* #1000 Otherwise, check if the IP addresses are equal. */
      /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
      if(TRUE == IpBase_SockIpAddrIsEqual(
        (SD_P2CONST(IpBase_SockAddrType))SockAPtr, (SD_P2CONST(IpBase_SockAddrType))SockBPtr))                          /* SBSW_SD_PASSING_API_POINTER */
      {
        matchType = SD_MATCH_TRUE;
      }
    }
  }

  return matchType;
}

/**********************************************************************************************************************
 *  Sd_Util_CompareSockAddrPort()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_MatchType, SD_CODE) Sd_Util_CompareSockAddrPort(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 AddrState)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_MatchType matchType = SD_MATCH_FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check family type of both socket addresses. */
  if(SockAPtr->family == SockBPtr->family)
  {
    /* #100 Check if the address state defines ANY possible port. */
    if(((AddrState & SOAD_SOCON_MASK_PORT) & SOAD_SOCON_MASK_ANY) > 0u)
    {
      matchType = SD_MATCH_ANY;
    }
    else
    {
      /* #1000 Otherwise, check if the ports are equal. */
      /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
      if(TRUE == IpBase_SockPortIsEqual(
        (SD_P2CONST(IpBase_SockAddrType))SockAPtr, (SD_P2CONST(IpBase_SockAddrType))SockBPtr))                          /* SBSW_SD_PASSING_API_POINTER */
      {
        matchType = SD_MATCH_TRUE;
      }
    }
  }

  return matchType;
}

/**********************************************************************************************************************
 *  Sd_Util_SockAddrIsEqual()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Util_SockAddrIsEqual(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean equal = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check family and the IP addresses. */
  /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
  if(TRUE == IpBase_SockIpAddrIsEqual(
    (SD_P2CONST(IpBase_SockAddrType))SockAPtr, (SD_P2CONST(IpBase_SockAddrType))SockBPtr))                              /* SBSW_SD_PASSING_API_POINTER */
  {
    /* #100 Check the Ports. */
    /* PRQA S 0310 2 */ /* MD_Sd_11.4_0310 */
    if(TRUE == IpBase_SockPortIsEqual(
      (SD_P2CONST(IpBase_SockAddrType))SockAPtr, (SD_P2CONST(IpBase_SockAddrType))SockBPtr))                            /* SBSW_SD_PASSING_API_POINTER */
    {
      equal = TRUE;
    }
  }

  return equal;
}

/**********************************************************************************************************************
 *  Sd_Rx_CheckSubnets()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckSubnets(
  Sd_SizeOfUdpSoConType UdpSoConIdx,
  Sd_SizeOfTcpSoConIdType TcpSoConIdIdx,
  SD_P2VAR(Sd_AttachedOptionsType) AttachedOptionsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the service is configured for UDP and a UDP endpoint option was received. */
  if((UdpSoConIdx != Sd_GetSizeOfUdpSoCon()) && (AttachedOptionsPtr->EndpointAddrUdp.family != SOAD_AF_INVALID))
  {
    /* #100 Check if the attached UDP endpoint address is part of the subnet. */
    optionsRetVal = Sd_Rx_CheckSubnet(Sd_GetIdOfUdpSoCon(UdpSoConIdx), &AttachedOptionsPtr->EndpointAddrUdp);           /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
  }

  /* #20 Check if the service is configured for TCP and a TCP endpoint option was received. */
  if((optionsRetVal == SD_OPTIONS_OK) &&
    (TcpSoConIdIdx != Sd_GetSizeOfTcpSoConId()) && (AttachedOptionsPtr->EndpointAddrTcp.family != SOAD_AF_INVALID))
  {
    /* #200 Check if the attached TCP endpoint address is part of the subnet. */
    optionsRetVal = Sd_Rx_CheckSubnet(Sd_GetTcpSoConId(TcpSoConIdIdx), &AttachedOptionsPtr->EndpointAddrTcp);           /* SBSW_SD_REFERENCE_OF_POINTER_ELEMENT */
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_CheckSubnet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(Sd_OptionsReturnType, SD_CODE) Sd_Rx_CheckSubnet(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) EndpointAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_OptionsReturnType optionsRetVal = SD_OPTIONS_OK;
  Sd_SockAddrContainerType localAddr;
  uint8 netmaskCidr = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the local IP address and the subnet mask. */
  retVal = Sd_SoAd_GetLocalAddrWithNetmask(SoConId, &localAddr, &netmaskCidr);                                          /* SBSW_SD_REFERENCE_OF_VARIABLE */

  if(retVal == E_OK)
  {
    /* #100 Check if the endpoint address is part of the subnet. */
    if(TRUE != Sd_Rx_SockAddrWithinSubnet(&localAddr, EndpointAddrPtr, netmaskCidr))                                    /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_PASSING_API_POINTER */
    {
      /* #1000 The endpoint references an IP address outside the configured subnet, do not consider this endpoint. */
      EndpointAddrPtr->family = SOAD_AF_INVALID;                                                                        /* SBSW_SD_VALID_API_POINTER */
      optionsRetVal = SD_OPTIONS_WRONG_SUBNET;
    }
  }
  else
  {
    /* #200 Failed to read the local address. Consider option as invalid. */
    optionsRetVal = SD_OPTIONS_NOT_OK;
  }

  return optionsRetVal;
}

/**********************************************************************************************************************
 *  Sd_Rx_SockAddrWithinSubnet()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Rx_SockAddrWithinSubnet(
  SD_P2CONST(Sd_SockAddrContainerType) SockAPtr,
  SD_P2CONST(Sd_SockAddrContainerType) SockBPtr,
  uint8 NetmaskCidr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean sameSubnet = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the family type of both addresses are identical. */
  if(SockAPtr->family == SockBPtr->family)
  {
    if(NetmaskCidr == 0u)
    {
      /* #1000 This check considers the special case in which a 32 bit value would be shifted for 32 bits.
       *       This special case would lead to an undefined result. */
      sameSubnet = TRUE;
    }
    else
    {
      /* #1001 Check IPv4 addresses. The net mask can be in the range [1 .. 32]. */
      if((SockAPtr->family == SOAD_AF_INET) && (NetmaskCidr <= 32u))
      {
        uint32 AddrA, AddrB;

        /* #10010 Generate a copy of the IP addresses in network byte order. */
        AddrA = IPBASE_SWAP32(SockAPtr->data[0u]);
        AddrB = IPBASE_SWAP32(SockBPtr->data[0u]);

        /* #10011 Shift to remove the variable parts of the IP address. */
        AddrA >>= (32u - NetmaskCidr);
        AddrB >>= (32u - NetmaskCidr);

        /* #10012 Compare the remaining par of the addresses. */
        if(AddrA == AddrB)
        {
          sameSubnet = TRUE;
        }
      }
      /* #1002 Check IPv6 addresses. The net mask can be in the range [1 .. 128]. */
      else if((SockAPtr->family == SOAD_AF_INET6) && (NetmaskCidr <= 128u))
      {
        uint32 AddrA[4u], AddrB[4u];

        /* #10020 Generate a copy of the IP addresses in network byte order. */
        AddrA[0u] = IPBASE_SWAP32(SockAPtr->data[0u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrA[1u] = IPBASE_SWAP32(SockAPtr->data[1u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrA[2u] = IPBASE_SWAP32(SockAPtr->data[2u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrA[3u] = IPBASE_SWAP32(SockAPtr->data[3u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrB[0u] = IPBASE_SWAP32(SockBPtr->data[0u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrB[1u] = IPBASE_SWAP32(SockBPtr->data[1u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrB[2u] = IPBASE_SWAP32(SockBPtr->data[2u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */
        AddrB[3u] = IPBASE_SWAP32(SockBPtr->data[3u]);                                                                  /* SBSW_SD_IP_ADDR_SIZE */

        /* #10021 Shift to remove the variable parts of the IP address. */
        if(NetmaskCidr < 32u)
        {
          AddrA[3u] >>= (32u - NetmaskCidr);                                                                            /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[3u] >>= (32u - NetmaskCidr);                                                                            /* SBSW_SD_IP_ADDR_SIZE */
        }
        else if(NetmaskCidr < 64u)
        {
          if(NetmaskCidr != 32u)
          {
            AddrA[2u] >>= (64u - NetmaskCidr);                                                                          /* SBSW_SD_IP_ADDR_SIZE */
            AddrB[2u] >>= (64u - NetmaskCidr);                                                                          /* SBSW_SD_IP_ADDR_SIZE */
          }
          AddrA[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
        }
        else if(NetmaskCidr < 96u)
        {
          if(NetmaskCidr != 64u)
          {
            AddrA[1u] >>= (96u - NetmaskCidr);                                                                          /* SBSW_SD_IP_ADDR_SIZE */
            AddrB[1u] >>= (96u - NetmaskCidr);                                                                          /* SBSW_SD_IP_ADDR_SIZE */
          }
          AddrA[2u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrA[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[2u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
        }
        else if(NetmaskCidr < 128u)
        {
          if(NetmaskCidr != 96u)
          {
            AddrA[0u] >>= (128u - NetmaskCidr);                                                                         /* SBSW_SD_IP_ADDR_SIZE */
            AddrB[0u] >>= (128u - NetmaskCidr);                                                                         /* SBSW_SD_IP_ADDR_SIZE */
          }
          AddrA[1u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrA[2u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrA[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[1u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[2u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
          AddrB[3u] = 0u;                                                                                               /* SBSW_SD_IP_ADDR_SIZE */
        }
        else
        {
          /* #100210 Net mask is too big, check if both addresses are identical. */
        }

        /* #10022 Compare both IP addresses. */
        if((AddrA[0u] == AddrB[0u]) &&
          (AddrA[1u] == AddrB[1u]) &&
          (AddrA[2u] == AddrB[2u]) &&
          (AddrA[3u] == AddrB[3u]))
        {
          sameSubnet = TRUE;
        }
      }
      else
      {
        /* #10023 The family is undefined or the net mask is out of range. */
      }
    }
  }

  return sameSubnet;
} /* PRQA S 6030, 6080 */ /* MD_MSR_STCYC, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  Sd_Util_ReportDemEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ReportDemEvent(
  Sd_Dem_EventIdType EventId)
{
  /* ----- Implementation ----------------------------------------------- */
#if(SD_DEM_EVENTS_CONFIGURED == STD_ON)
  /* #10 Check if the DEM event is configured. */
  if(EventId != 0u)
  {
    /* #100 Report DEM event. */
    Dem_ReportErrorStatus(EventId, DEM_EVENT_STATUS_FAILED);
  }
#else
  SD_DUMMY_STATEMENT(EventId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint -e{438} */
#endif
}

/**********************************************************************************************************************
 *  Sd_Util_GetRandomNrInRange()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(uint32, SD_CODE) Sd_Util_GetRandomNrInRange(
  uint32 MinValue,
  uint32 MaxValue)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 randNo;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if a random number has to be calculated */
  if(MinValue == MaxValue)
  {
    /* #100 No need to calculate a random number. */
    randNo = MinValue;
  }
  else
  {
    /* #101 Calculate a random number in the range:  MinValue <= RandInRange <= MaxValue. */
    randNo = (Sd_ExternalRandomNumberFct() % ((MaxValue + 1u) - MinValue)) + MinValue;
  }

  return randNo;
}

/**********************************************************************************************************************
 *  Sd_Util_GetRandomNrInRangeForResponse()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(uint32, SD_CODE) Sd_Util_GetRandomNrInRangeForResponse(
  uint32 MinValue,
  uint32 MaxValue,
  boolean InterruptContext)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 tmpMinValue = MinValue, tmpMaxValue = MaxValue;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the context the function is called from. */
  if(InterruptContext == TRUE)
  {
    /* #100 Response is generated in context of message transmission. */

    if((MinValue != 0u) && (MinValue != MaxValue))
    {
      /* #1000 Increase the lower bound in order to consider the elapsed time between the last MainFunction and the RxIndication. */
      tmpMinValue += SD_MAIN_FCT_CYCLE_TIME_MS;
    }
  }
  else
  {
    /* #101 Response is generated in context of MainFunction. */

    if(MaxValue != 0u)
    {
      /* #1010 Decrease the upper bound in order to consider the elapsed time between the last MainFunction and the RxIndication. */
      if(MinValue == MaxValue)
      {
        tmpMinValue -= SD_MAIN_FCT_CYCLE_TIME_MS;
      }

      tmpMaxValue -= SD_MAIN_FCT_CYCLE_TIME_MS;
    }
  }

  return Sd_Util_GetRandomNrInRange(tmpMinValue, tmpMaxValue);
}

/**********************************************************************************************************************
 *  Sd_Util_CheckIfTimerExceeded()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(boolean, SD_CODE) Sd_Util_CheckIfTimerExceeded(
  Sd_ExtendedTimeType Timer,
  boolean EqualIsExceeded)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean exceeded = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Check if the seconds are exceeded. */
  if(Sd_TimeMsSinceStart.Seconds > Timer.Seconds)
  {
    exceeded = TRUE;
  }
  else if(Timer.Seconds == Sd_TimeMsSinceStart.Seconds)
  {
    /* #100 Seconds are identical. Check milliseconds. */
    if(Sd_TimeMsSinceStart.Milliseconds > Timer.Milliseconds)
    {
      exceeded = TRUE;
    }
    else if((EqualIsExceeded == TRUE) && (Timer.Milliseconds == Sd_TimeMsSinceStart.Milliseconds))
    {
      exceeded = TRUE;
    }
    else
    {
      /* #1000 Milliseconds are not exceeded. */
    }
  }
  else
  {
    /* #101 Seconds are not exceeded. */
  }

  SD_END_CRITICAL_SECTION();

  return exceeded;
}

/**********************************************************************************************************************
 *  Sd_Util_TriggerStateMachineRun()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_TriggerStateMachineRun(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Set next state machine execution time to 0 in order to trigger execution in the next MainFunction. */
  (Sd_GetAddrNextStateMachineRunOfInstanceDyn(InstanceIdx))->Seconds = 0u;                                              /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  (Sd_GetAddrNextStateMachineRunOfInstanceDyn(InstanceIdx))->Milliseconds = 0u;                                         /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_SetNextStateMachineRun()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetNextStateMachineRun(
  Sd_SizeOfInstanceType InstanceIdx,
  Sd_ExtendedTimeType Timer)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Check if the next state machine execution is scheduled later than the given time.
   *     If so, it has to be re-scheduled to an earlier point in time. */
  if((Sd_GetNextStateMachineRunOfInstanceDyn(InstanceIdx).Seconds > Timer.Seconds) ||
    ((Sd_GetNextStateMachineRunOfInstanceDyn(InstanceIdx).Seconds == Timer.Seconds) &&
    (Sd_GetNextStateMachineRunOfInstanceDyn(InstanceIdx).Milliseconds > Timer.Milliseconds)))
  {
    /* #100 Set next state machine execution time to the given time. */
    (Sd_GetAddrNextStateMachineRunOfInstanceDyn(InstanceIdx))->Seconds      = Timer.Seconds;                            /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    (Sd_GetAddrNextStateMachineRunOfInstanceDyn(InstanceIdx))->Milliseconds = Timer.Milliseconds;                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  }

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffsetWithTrigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffsetWithTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetMs,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Update the timer. */
  Sd_Util_SetTimerOffset(TimerPtr, OffsetMs);                                                                           /* SBSW_SD_PASSING_API_POINTER */

  /* #20 Trigger state machine execution based on the given offset. */
  Sd_Util_SetNextStateMachineRun(InstanceIdx, *TimerPtr);
}

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffsetSecWithTrigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffsetSecWithTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetSec,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Check if the TTL shall be considered valid till the next reboot. */
  if(OffsetSec == SD_TTL_INFINITE)
  {
    /* #200 Set the timer value to infinite. This timer will never expire. */
    TimerPtr->Seconds = SD_TIMER_SEC_INFINITE;                                                                          /* SBSW_SD_VALID_API_POINTER */
    TimerPtr->Milliseconds = SD_TIMER_MSEC_INFINITE;                                                                    /* SBSW_SD_VALID_API_POINTER */
  }
  else
  {
    /* #300 Otherwise, update the timer with the given offset. */
    TimerPtr->Seconds = Sd_TimeMsSinceStart.Seconds + (OffsetSec);                                                      /* SBSW_SD_VALID_API_POINTER */
    TimerPtr->Milliseconds = Sd_TimeMsSinceStart.Milliseconds;                                                          /* SBSW_SD_VALID_API_POINTER */

    /* #301 Trigger state machine execution based on the given offset. */
    Sd_Util_SetNextStateMachineRun(InstanceIdx, *TimerPtr);
  }

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_SetTimerOffset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL FUNC(void, SD_CODE) Sd_Util_SetTimerOffset(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  uint32 OffsetMs)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Update the timer with the given offset.
   *     The timer value is saved in separated variables for seconds and milliseconds. */
  TimerPtr->Seconds      = Sd_TimeMsSinceStart.Seconds      + (OffsetMs / 1000u);                                       /* SBSW_SD_VALID_API_POINTER */
  TimerPtr->Milliseconds = Sd_TimeMsSinceStart.Milliseconds + (uint16)(OffsetMs % 1000u);                               /* SBSW_SD_VALID_API_POINTER */

  /* #20 Handle the case if the amount of milliseconds exceeds one second. */
  TimerPtr->Seconds      = TimerPtr->Seconds                + ((uint32)TimerPtr->Milliseconds / 1000u);                 /* SBSW_SD_VALID_API_POINTER */
  TimerPtr->Milliseconds = TimerPtr->Milliseconds           % 1000u;                                                    /* SBSW_SD_VALID_API_POINTER */

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToZero()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToZero(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Reset the timer. */
  TimerPtr->Seconds = 0u;                                                                                               /* SBSW_SD_VALID_API_POINTER */
  TimerPtr->Milliseconds = 0u;                                                                                          /* SBSW_SD_VALID_API_POINTER */

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToZeroTrigger()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToZeroTrigger(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr,
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the timer. */
  Sd_Util_ResetTimerToZero(TimerPtr);                                                                                   /* SBSW_SD_PASSING_API_POINTER */

  /* #20 Trigger state machine execution. */
  Sd_Util_TriggerStateMachineRun(InstanceIdx);
}

/**********************************************************************************************************************
 *  Sd_Util_ResetTimerToInvalid()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_ResetTimerToInvalid(
  SD_P2VAR(Sd_ExtendedTimeType) TimerPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  SD_BEGIN_CRITICAL_SECTION();

  /* #10 Set the timer values to invalid. */
  TimerPtr->Seconds = SD_INV_TIMER_VALUE_32BIT;                                                                         /* SBSW_SD_VALID_API_POINTER */
  TimerPtr->Milliseconds = SD_INV_TIMER_VALUE_16BIT;                                                                    /* SBSW_SD_VALID_API_POINTER */

  SD_END_CRITICAL_SECTION();
}

/**********************************************************************************************************************
 *  Sd_Util_DisableRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_DisableRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if RoutingGroup is already disabled. */
  if(Sd_GetStatusOfRoutingGroupDyn(RoutingGroupIdx) != SD_ROUTINGGROUP_STATUS_DISABLED)
  {
    /* #100 Disable Routing for RoutingGroup if RoutingGroup is not already disabled. */
    retVal = SoAd_DisableRouting(Sd_GetRoutingGroup(RoutingGroupIdx));

    /* #101 Update internal status of RoutingGroup if Routing could be disabled. */
    if(retVal == E_OK)
    {
      Sd_SetStatusOfRoutingGroupDyn(RoutingGroupIdx, SD_ROUTINGGROUP_STATUS_DISABLED);                                            /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_Util_DisableSpecificRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_DisableSpecificRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set internal status of RoutingGroup to unknown because only a specific routing is disabled. */
  Sd_SetStatusOfRoutingGroupDyn(RoutingGroupIdx, SD_ROUTINGGROUP_STATUS_UNKNOWN);                                                 /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  /* #20 Disable specific routing and return result of operation. */
  return SoAd_DisableSpecificRouting(Sd_GetRoutingGroup(RoutingGroupIdx), SoConId);
}

/**********************************************************************************************************************
 *  Sd_Util_EnableRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_EnableRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if RoutingGroup is already enabled. */
  if(Sd_GetStatusOfRoutingGroupDyn(RoutingGroupIdx) != SD_ROUTINGGROUP_STATUS_ENABLED)
  {
    /* #100 Enable Routing for RoutingGroup if RoutingGroup is not already enabled. */
    retVal = SoAd_EnableRouting(Sd_GetRoutingGroup(RoutingGroupIdx));

    /* #101 Update internal status of RoutingGroup if Routing could be enabled. */
    if(retVal == E_OK)
    {
      Sd_SetStatusOfRoutingGroupDyn(RoutingGroupIdx, SD_ROUTINGGROUP_STATUS_ENABLED);                                             /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_Util_EnableSpecificRouting()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_Util_EnableSpecificRouting(Sd_SizeOfRoutingGroupType RoutingGroupIdx,
  SoAd_SoConIdType SoConId)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set internal status of RoutingGroup to unknown because only a specific routing is enabled. */
  Sd_SetStatusOfRoutingGroupDyn(RoutingGroupIdx, SD_ROUTINGGROUP_STATUS_UNKNOWN);                                       /* SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE */
  /* #20 Enable specific routing and return result of operation. */
  return SoAd_EnableSpecificRouting(Sd_GetRoutingGroup(RoutingGroupIdx), SoConId);
}

/**********************************************************************************************************************
 *  Sd_Util_SetAllStateMachineExecutionFlags()
 *********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
  */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_SetAllStateMachineExecutionFlags(
  Sd_SizeOfInstanceType InstanceIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Sd_SizeOfServerType serverIdx;
  Sd_SizeOfClientType clientIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all state machine execution flags for the server services. */
  for(serverIdx = Sd_GetServerStartIdxOfInstance(InstanceIdx);
    serverIdx < Sd_GetServerEndIdxOfInstance(InstanceIdx);
    serverIdx++)
  {
    Sd_SetStateMachineExecutionRequestedOfServerDyn(serverIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
  }

  /* #20 Set all state machine execution flags for the client services. */
  for(clientIdx = Sd_GetClientStartIdxOfInstance(InstanceIdx);
    clientIdx < Sd_GetClientEndIdxOfInstance(InstanceIdx);
    clientIdx++)
  {
    Sd_SetStateMachineExecutionRequestedOfClientDyn(clientIdx, TRUE);                                                   /* SBSW_SD_API_ARGUMENT_IDX_INDIRECTION */
  }
}

/**********************************************************************************************************************
 *  Sd_Util_Write32Bit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write32Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint32 Value)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write next 4 bytes to the array. */
  BufferPtr[0u] = (uint8)((uint32_least)(Value) >> 24u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[1u] = (uint8)((uint32_least)(Value) >> 16u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[2u] = (uint8)((uint32_least)(Value) >>  8u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[3u] = (uint8)((uint32_least)(Value));                                                                       /* SBSW_SD_WRITE_PAYLOAD */
}

/**********************************************************************************************************************
 *  Sd_Util_Write24Bit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write24Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint32 Value)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write next 3 bytes to the array. */
  BufferPtr[0u] = (uint8)((uint32_least)(Value) >> 16u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[1u] = (uint8)((uint32_least)(Value) >>  8u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[2u] = (uint8)((uint32_least)(Value));                                                                       /* SBSW_SD_WRITE_PAYLOAD */
}

/**********************************************************************************************************************
 *  Sd_Util_Write16Bit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write16Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint16 Value)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write next 2 bytes to the array. */
  BufferPtr[0u] = (uint8)((uint16_least)(Value) >>  8u);                                                                /* SBSW_SD_WRITE_PAYLOAD */
  BufferPtr[1u] = (uint8)((uint16_least)(Value));                                                                       /* SBSW_SD_WRITE_PAYLOAD */
}

/**********************************************************************************************************************
 *  Sd_Util_Write8Bit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(void, SD_CODE) Sd_Util_Write8Bit(
  SD_P2VAR(uint8) BufferPtr,
  uint8 Value)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write next byte to the array. */
  BufferPtr[0u] = (uint8)(Value);                                                                                       /* SBSW_SD_WRITE_PAYLOAD */
}

/**********************************************************************************************************************
 *  Sd_SoAd_GetLocalAddrWithNetmask()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetLocalAddrWithNetmask(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) LocalAddrPtr,
  SD_P2VAR(uint8) NetmaskPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  Sd_SockAddrContainerType defaultRouter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Request the local address from the SoAd module. */
  /* PRQA S 0310 5 */ /* MD_Sd_11.4_0310 */
  retVal = SoAd_GetLocalAddr(
    SoConId,
    (SD_P2VAR(SoAd_SockAddrType))LocalAddrPtr,
    NetmaskPtr,
    (SD_P2VAR(SoAd_SockAddrType))&defaultRouter);                                                                       /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */ /* SBSW_SD_SOCK_ADDR_CAST */

  /* #20 Check if the request was successful and the family type is known. */
  if((retVal == E_NOT_OK) ||
    ((LocalAddrPtr->family != SOAD_AF_INET) && (LocalAddrPtr->family != SOAD_AF_INET6)))
  {
    /* #200 Invalidate the family type and return E_NOT_OK because the request failed. */
    LocalAddrPtr->family = SOAD_AF_INVALID;                                                                             /* SBSW_SD_VALID_API_POINTER */
    retVal = E_NOT_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_SoAd_GetLocalAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetLocalAddr(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) LocalAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 netmask;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Request the local address. */
  retVal = Sd_SoAd_GetLocalAddrWithNetmask(SoConId, LocalAddrPtr, &netmask);                                            /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_REFERENCE_OF_VARIABLE */

  return retVal;
}

/**********************************************************************************************************************
 *  Sd_SoAd_GetRemoteAddr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SD_LOCAL_INLINE FUNC(Std_ReturnType, SD_CODE) Sd_SoAd_GetRemoteAddr(
  SoAd_SoConIdType SoConId,
  SD_P2VAR(Sd_SockAddrContainerType) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get the remote address from the SoAd module. */
  /* PRQA S 0310 3 */ /* MD_Sd_11.4_0310 */
  retVal = SoAd_GetRemoteAddr(
    SoConId,
    (SD_P2VAR(SoAd_SockAddrType))IpAddrPtr);                                                                            /* SBSW_SD_PASSING_API_POINTER */ /* SBSW_SD_SOCK_ADDR_CAST */

  /* #20 Check if the returned family type is known. */
  if((retVal == E_NOT_OK) ||
    ((IpAddrPtr->family != SOAD_AF_INET) && (IpAddrPtr->family != SOAD_AF_INET6)))
  {
    /* #200 Invalidate the family type and return E_NOT_OK because the request failed. */
    IpAddrPtr->family = SOAD_AF_INVALID;                                                                                /* SBSW_SD_VALID_API_POINTER */
    retVal = E_NOT_OK;
  }

  return retVal;
}

#define SD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:

  MD_Sd_11.4_0310:
    Reason:     Pointer casts are standard proceeding in TcpIp address data handling. (Rule 0310, 3305)
    Risk:       None
    Prevention: Covered by code review.

  MD_Sd_11.5_0311:
    Reason:     Function requires variable input parameter instead of const input parameter. (Rule 0311)
    Risk:       Changes made inside the function are not realized
    Prevention: Covered by code review.

  MD_Sd_12.4_3415:
    Reason:     Function does not change any value and has therefore no side effects. (Rule 3415)
    Risk:       Changes made inside the function are not realized
    Prevention: Covered by code review.

  MD_Sd_Rule-2.2_2981:
    Reason:     Redundant initialization. The value of this object is never used before being modified.
    Risk:       None
    Prevention: No prevention necessary.

  MD_Sd_Rule-2.2_2986:
    Reason:     Redundant operation. The value of the result is always that of the right-hand operand.
    Risk:       None
    Prevention: No prevention necessary.

  MD_Sd_Dir-1.1_0314:
    Reason:     The memset functions from the vstdlib have a void pointer as a function parameter. (See MD_MSR_VStdLibCopy for copy functions.)
    Risk:       No risk, because the underlying uint8 pointer type is known.
    Prevention: No prevention necessary.

  MD_Sd_Enum_4522_4424_4432_4332_4342_4393:
    Reason:     Enumerations are not used in a type safe way.
                This applies for the following rules:
                  Rule-10.1_4522: An expression of 'essentially enum' type is being used as the right-hand operand of this bitwise operator (|).
                  Rule-10.3_4424: An expression of 'essentially enum' type is being converted to unsigned type on assignment.
                  Rule-10.3_4432: An expression of 'essentially signed' type is being converted to enum type on assignment.
                  Rule-10.5_4332: An expression of 'essentially signed' type is being cast to enum type.
                  Rule-10.5_4342: An expression of 'essentially unsigned' type is being cast to enum type.
                  Rule-10.8_4393: A composite expression of 'essentially signed' type is being cast to a different type category.
    Risk:       The type safety of enumeration data types is not ensured, which may lead to unexpected behavior.
    Prevention: Covered by code review.

  MD_Sd_FalsePositive_2995_2996_2853:
    Reason:     Tooling detects errors that do not exist:
                Rule-2.2_2995:  The result of this logical operation is always 'true'.
                Rule-2.2_2996:  The result of this logical operation is always 'false'.
                Rule-3.1_2853:  Suspicious: Implicit conversion to a signed integer type of insufficient size.
    Risk:       Potential issue may be not detected.
    Prevention: Covered by code review.

  MD_Sd_STPTH_6010:
    Reason:     Path count too high, function is hard to understand.
    Risk:       Maintainability and testability might become too complex.
    Prevention: Covered by code review.

  MD_Sd_STCAL_6050:
    Reason:     Deeper nesting of functions increases call stack usage and runtime.
    Risk:       Understandability and testability might become too complex due to fan-out to many functions.
    Prevention: Covered by code review.

  MD_Sd_STPAR_6060:
    Reason:     Function handles specific task in the overall component behavior. This requires multiple input
                parameters.
    Risk:       Stack usage and runtime too high for target uC.
    Prevention: Not applicable.
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_SD_CSL01
    \DESCRIPTION      Access of array element with index generated by ComStackLib.
    \COUNTERMEASURE   \N  Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_SD_CSL02
    \DESCRIPTION      Access of array element with index checked against size of different array.
                      (Arrays Xyz[] and XyzDyn[] depend on ComStackLib size relation.)
    \COUNTERMEASURE   \N  Qualified use-case CSL02 of ComStackLib

  \ID SBSW_SD_CSL03
    \DESCRIPTION      Access of array element with index modelled by indirection.
    \COUNTERMEASURE   \N  Qualified use-case CSL03 of ComStackLib

  \ID SBSW_SD_CSL_VAR_ELEM
    \DESCRIPTION      Pointer write access of variable element modelled by ComStackLib.
    \COUNTERMEASURE   \N  Access macro is generated by ComStackLib and therefore qualified.

  \ID SBSW_SD_GETVERSION_PARAM
    \DESCRIPTION      The Sd_GetVersionInfo writes to the 'versioninfo' pointer parameter. It is checked against NULL,
                      but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE   \N  Pointers passed to public Sd APIs point to a valid memory range.
                          A general countermeasure is included in the safety manual.

  \ID SBSW_SD_PUBLIC_API_POINTER
    \DESCRIPTION      The function forwards the input pointer. It is checked against NULL_PTR,
                      but this does not guarantee that the referenced memory is valid.
    \COUNTERMEASURE   \N  Pointers passed to public Sd APIs point to a valid memory range.
                          A general countermeasure is included in the safety manual.

  \ID SBSW_SD_VALID_API_POINTER
    \DESCRIPTION      Write access to element which is passed as function argument.
    \COUNTERMEASURE   \N  It is assumed, that the input pointer is valid and the function only writes members of the
                          pointed struct.

  \ID SBSW_SD_PASSING_API_POINTER
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  Pointer was passed as function argument and is used to call sub-function. The validity of the
                          pointer is ensured by the caller. If not otherwise specified, each pointer has to point to
                          valid data != NULL_PTR.

  \ID SBSW_SD_PASSED_API_POINTER_NOT_NULL
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \R  The pointer is checked against NULL_PTR.

  \ID SBSW_SD_FUNCTION_CALL_NULL_PTR
    \DESCRIPTION      NULL_PTR is passed as function argument.
    \COUNTERMEASURE   \N  NULL_PTR is an allowed value to identify special use-case.
                          The pointer value is checked against NULL_PTR within the called function.

  \ID SBSW_SD_REFERENCE_OF_VARIABLE
    \DESCRIPTION      Pointer to variable is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a variable respectively a struct member of a variable
                          by the address operator.

  \ID SBSW_SD_REFERENCE_OF_POINTER_ELEMENT
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a member of a struct passed as reference function
                          argument. The validity of the function argument is ensured by the caller.

  \ID SBSW_SD_PDU_INFO_PTR
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  The PduInfoPtr is a pointer which is passed via the public API Sd_RxIndication().
                          It is checked against NULL_PTR and saved in the Sd_RxMessageInfoType structure.
                          The pointed structure contains a member SduDataPtr which is also assumed to be valid.
                          Pointers passed to public Sd APIs point to a valid memory range.
                          A general countermeasure is included in the safety manual.

  \ID SBSW_SD_RX_ADDRESS_STORAGE_IDX
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The AddressStorageIdx index is determined during reception of a message within
                          Sd_Rx_SaveAddr(). The index is obtained by qualified use-case CSL01 of ComStackLib within
                          Sd_RxIndication().

  \ID SBSW_SD_SEND_ENTRY_IDX
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The index is determined by the Sd_Util_GetEmptySendEntry() function.
                          The valid range of the index is ensured by this function and defined at the function
                          declaration.

  \ID SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element with an index qualified by
                          SBSW_SD_SEND_ENTRY_IDX.

  \ID SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX_INDIRECTION_SAME_SIZE
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element with an index which is obtained by
                          execution of same size relation (CSL02), indirection (CSL03) and qualified
                          SBSW_SD_REFERENCE_USING_SEND_ENTRY_IDX.

  \ID SBSW_SD_CONFIG_OPTION_PTR_ARRAY_SIZE
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The ConfigOptionPtrArray array has a size of (Sd_GetMaxNrOptionsPerEntry() + 1).
                          The write access of element with index is checked with qualified use-case CSL01 of
                          ComStackLib.

  \ID SBSW_SD_FIXED_SIZE_OF_CONFIGOPTIONPTRARRAY
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The ConfigOptionPtrArrayPtr passed as function argument points to an array of fixed size 3.
                          Within the function Sd_Rx_FillConfigOptionPtrArray(), it is ensures that maximally the
                          indexes 0 and 1 of the array are modified inside the function.

  \ID SBSW_SD_ATTACHED_OPTIONS_PTR
    \DESCRIPTION      Pointer is passed as function argument.
    \COUNTERMEASURE   \N  The ConfigOptionPtrArrayPtr element of the Sd_AttachedOptionsType structure points to a local
                          array of size (Sd_GetMaxNrOptionsPerEntry() + 1).
                          The assignment is done directly after creation of the structure.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element which is obtained by qualified
                          use-case CSL01 of ComStackLib.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_SAME_SIZE
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element which is obtained by same size Relation.
                          (Qualified use-case CSL02 of ComStackLib.)

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element with index given as function argument.
                          The valid range of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_SAME_SIZE
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element with index.
                          The index is obtained by same size relation of function argument.
                          (Qualified use-case CSL02 of ComStackLib).
                          The valid range of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is obtained by referencing an array element with index.
                          The index is obtained by indirection of function argument.
                          (Qualified use-case CSL03 of ComStackLib).
                          The valid range of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_OUTER_INDEX_INDIRECTION_SAME_SIZE
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element by index.
                          The index is obtained by indirection and same size relation of function argument.
                          (Qualified use-cases CSL03 and CSL02 of ComStackLib). The valid range of the function argument
                          is defined at the function declaration and has to be ensured by the calling function.

  \ID SBSW_SD_REFERENCE_OF_ARRAY_ELEMENT_HANDLE_ID_INDIRECTION
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \R  Pointer is obtained by referencing an array element with index.
                          The index is obtained by indirection of HandleID given as function argument.
                          (Qualified use-case CSL03 of ComStackLib).
                          A previous runtime check ensures that the HandleID is smaller than the size of the array.

  \ID SBSW_SD_API_ARGUMENT_IDX
    \DESCRIPTION      Access of array element with index given as function argument is not checked for validity.
    \COUNTERMEASURE   \N  The valid range of the function argument is defined at the function declaration and has to be
                          ensured by the calling function.

  \ID SBSW_SD_API_ARGUMENT_IDX_SAME_SIZE
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  Index is obtained by same size relation (qualified use-case CSL02 of ComStackLib) of function
                          argument. The valid range of the function argument is defined at the function declaration and
                          has to be ensured by the calling function.

  \ID SBSW_SD_API_ARGUMENT_IDX_INDIRECTION
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) of function
                          argument. The valid range of the function argument is defined at the function declaration and
                          has to be ensured by the calling function.
                          If the indirection is not valid in case of an optional 0:1 indirection (value of index is SD_NO_*),
                          the index must not be used.

  \ID SBSW_SD_API_ARGUMENT_IDX_INDIRECTION_SAME_SIZE
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  Index is obtained by indirection (qualified use-case CSL03 of ComStackLib) and same size
                          relation (qualified use-case CSL02 of ComStackLib) of function argument. The valid range of
                          the function argument is either defined at the function declaration and has to be ensured by the
                          calling function or is checked within the function.

  \ID SBSW_SD_FUNCTION_PTR_CALL
    \DESCRIPTION      Calling a function pointer without checking the reference.
    \COUNTERMEASURE   \R  It is checked, that the corresponding service has a function pointer configured.
                          The index is obtained by indirection of function argument.
                          (Qualified use-case CSL03 of ComStackLib). The valid range of the function argument is defined
                          at the function declaration and has to be ensured by the calling function.

  \ID SBSW_SD_FUNCTION_PTR_CALL_STATIC
    \DESCRIPTION      Calling a function pointer without checking the reference.
    \COUNTERMEASURE   \N  The function pointer is passed as function argument. Its correctness has to be ensured by the
                          calling function.

  \ID SBSW_SD_IP_ADDR_SIZE
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  IPv6 addresses are saved in an array with fixed size of 4.
                          The used indices are constant and smaller as the array size.

  \ID SBSW_SD_RXEVENT_IDX
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  All RxEvents are saved in a ring buffer in the Sd_RxEvent[] array.
                          The value RxEventEndIdxOfInstanceDyn is an index into a RAM data structure which is used to
                          implement a ring buffer. The value is initialized before used and checked to stay in correct
                          range after any update. The check for correctness is done via modelled relation according to
                          CSL03.

  \ID SBSW_SD_RXEVENT_MEMBER
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The index is taken from ring buffer element. Ring buffer implementation assures that only
                          elements are read which have been written with correct values before. The index to read from
                          the ring buffer is initialized before usage and checked to stay in correct range with any
                          change, similar to the write index as stated in SBSW_SD_RXEVENT_IDX. Correctness of the index
                          values written to the ring buffer element is assured by CSL01, CSL02 or CSL03. All parts of a
                          ring buffer entry are written at once.

  \ID SBSW_SD_REFERENCE_RXEVENT_MEMBER
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing an array element by index.
                          The index is obtained by using a member of the RxEvent structure which is qualified by
                          SBSW_SD_RXEVENT_MEMBER.

  \ID SBSW_SD_REFERENCE_MESSAGE_SIZE_WITH_ENTRIES
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \R  The size of the Sd_Payload[] array is enforced to be >=48Bytes by the Generator, which
                          is sufficient for the entire header (SD_HEADER_LENGTH), the maximum length of all SD entries which
                          shall be serialized (maxNumberOfEntriesToSerialize * SD_ENTRY_SIZE) and the corresponding length fields
                          (SD_HEADER_LENGTHOFENTRIESARRAY_SIZE + SD_HEADER_LENGTHOFOPTIONSARRAY_SIZE).
                          maxNumberOfEntriesToSerialize is determined at the beginning of Sd_Tx_SerializeMessage() function,
                          This check ensures, that the corresponding pointer does not exceed the size of the
                          Sd_Payload[] array.
                          If the entries are written in context of the Sd_Tx_SerializeEntryAndOptions() function, the
                          offset of the actual entry is given as PayloadEntryIdx parameter. The function ensures that
                          only the next SD_ENTRY_SIZE subsequent bytes are written.
                          The calling function Sd_Tx_SerializeMessage() ensures that the value of
                          PayloadEntryIdx does not exceed the memory range reserved for the serialization of entries.
                          [range PayloadEntryIdx: (SD_HEADER_LENGTH + SD_HEADER_LENGTHOFENTRIESARRAY_SIZE) ..
                            ((maxNumberOfEntriesToSerialize - 1) * SD_ENTRY_SIZE)]

  \ID SBSW_SD_REFERENCE_MESSAGE_SIZE_OPTION_OR_ENTRY
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \R  The size of the Sd_Payload[] array is checked for each entry/option which is serialized.
                          This check ensures, that the corresponding pointer does not exceed the size of the
                          Sd_Payload[] array.

  \ID SBSW_SD_SOCK_ADDR_SIZE
    \DESCRIPTION      Pointer to struct element is passed as function argument.
    \COUNTERMEASURE   \N  Pointer is generated by referencing a member of a struct passed as function argument. The
                          validity of the function argument is ensured by the caller.
                          The size of the pointed struct members ensure the following requirements:
                          - sizeof(data) >= max(SD_OPTION_IPV4_ADDRESS_SIZE, SD_OPTION_IPV6_ADDRESS_SIZE)
                          - sizeof(port) >= max(SD_OPTION_IPV4_PORTNUMBER_SIZE, SD_OPTION_IPV6_PORTNUMBER_SIZE)

  \ID SBSW_SD_RX_MESSAGE_SIZE
    \DESCRIPTION      Pointer to array element is passed as function argument.
    \COUNTERMEASURE   \R  The size of each received message is checked to be valid by Sd_Rx_ProcessHeader() function.
                          These checks ensure that the given entries and options array lengths are valid.
                          Hence, the payload pointer point to valid bytes of the received message.

  \ID SBSW_SD_WRITE_PAYLOAD
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The Sd_Util_Write<8|16|24|32>Bit() functions access the element given by the pointer as well
                          as the succeeding element(s). The validity of the pointer and the minimal amount of valid
                          remaining elements is defined at the function description and has to be satisfied by the
                          caller.

  \ID SBSW_SD_TX_ADDRESS_STORAGE_IDX
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  Each valid send entry references its destination address (AddressStorageIdx).
                          This index is always set to an existing value if a send entry is saved
                          (Sd_Util_Add<Xyz>EntryToList()).

  \ID SBSW_SD_TRIGGER_TRANSMIT_IDX
    \DESCRIPTION      Access of array element with index is not checked for validity.
    \COUNTERMEASURE   \N  The list of trigger transmit requests is managed in a ring-buffer with start and end indices
                          and a full-flag. The list is modified by Sd_TriggerTransmit_<Xyz>() functions. There it is
                          ensured that the corresponding indices are always valid.

  \ID SBSW_SD_SOCK_ADDR_CAST
    \DESCRIPTION      Type cast of pointer may change the amount of memory the called function writes to.
    \COUNTERMEASURE   \N  The SockAddr structures for IPv4 and IPv6 addresses have a different structure and size.
                          In order to allow passing both address types via the same API to functions, the pointer to the
                          structure is type casted to a generic type (*_SockAddrType) which contains only the domain
                          information of the address and results in a typecast to a smaller structure.
                          The called function has to interpret the domain information and will type cast to the
                          corresponding type.
                          The size of the casted structure (Sd_SockAddrContainerType) is sufficient to store both
                          address types.

  \ID SBSW_SD_IPBASE_FILL
    \DESCRIPTION      Type cast of pointer may change the amount of memory the called function writes to.
    \COUNTERMEASURE   \N  The size of the corresponding element as well as the offset are given as additional function
                          arguments. Thereby the offset is set to 0 and the size calculated by sizeof() operator.

  \ID SBSW_SD_CAST_TO_VAR
    \DESCRIPTION      Pointer to const data is casted to pointer to variable data.
    \COUNTERMEASURE   \N  The AUTOSAR 4.2.1 API SoAd_SetUniqueRemoteAddr() is defined with var "RemoteAddrPtr" pointer,
                          although the pointed data will not be modified within this function.

SBSW_JUSTIFICATION_END */

/* START_COVERAGE_JUSTIFICATION

  \ID COV_SD_COMPATIBILITY
    \ACCEPT   TX
    \ACCEPT   XF
    \REASON   [COV_MSR_COMPATIBILITY]

  \ID COV_SD_VAR_DEPENDENT_SWITCH
    \ACCEPT TX
    \REASON The nested switch depends on a previous switch.

  \ID COV_SD_MISRA
    \ACCEPT XX
    \REASON [MSR_COV_MISRA]

  \ID COV_SD_INV_STATE
    \ACCEPT XX
    \REASON [COV_MSR_INV_STATE]

  \ID COV_SD_SAFE_BSW
    \ACCEPT TX
    \REASON In SafeBSW use-case SD_DEV_ERROR_DETECT has to be configured to STD_ON.

END_COVERAGE_JUSTIFICATION */

/**********************************************************************************************************************
 *  END OF FILE: Sd.c
 *********************************************************************************************************************/
