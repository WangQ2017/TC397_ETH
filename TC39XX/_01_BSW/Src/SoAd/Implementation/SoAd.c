/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor module.
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

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd.h"
#include "SoAd_Priv.h"
#include "SoAd_Cbk.h"
#include "SoAd_EventQueue.h"
#include "SoAd_TimeoutList.h"
#include "SoAd_TcpIp.h"
#include "SoAd_SoCon.h"
#include "SoAd_RouteGrp.h"
#include "SoAd_Tx.h"
#include "SoAd_Rx.h"
#include "SoAd_Measure.h"

#include "IpBase.h"
#if ( SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE == SOAD_CONFIGURATION_VARIANT )
# include "EcuM_Error.h"
#endif /* SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE == SOAD_CONFIGURATION_VARIANT */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of SoAd header file */
#if ( (SOAD_SW_MAJOR_VERSION != 16u) \
    || (SOAD_SW_MINOR_VERSION != 5u) \
    || (SOAD_SW_PATCH_VERSION != 1u) )
# error "Vendor specific version numbers of SoAd.c and SoAd.h are inconsistent"
#endif /* (SOAD_SW_MAJOR_VERSION != 16u) \
    || (SOAD_SW_MINOR_VERSION != 5u) \
    || (SOAD_SW_PATCH_VERSION != 1u) */

/* Check configuration variant for building the library */
#if ( (defined(V_EXTENDED_BUILD_LIB_CHECK)) && (SOAD_CONFIGURATION_VARIANT_PRECOMPILE == SOAD_CONFIGURATION_VARIANT) )
# error "SoAd.c: Switch configuration variant to link-time or post-build for library build!"
#endif /* (defined(V_EXTENDED_BUILD_LIB_CHECK)) &&
  (SOAD_CONFIGURATION_VARIANT_PRECOMPILE == SOAD_CONFIGURATION_VARIANT) */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif /* !defined (SOAD_LOCAL) */

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif /* !defined (SOAD_LOCAL_INLINE) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Indicates the counter for shutdown finished timeout to switch to shutdown state if sockets could not be closed. */
SOAD_LOCAL VAR(uint16, SOAD_VAR_NOINIT) SoAd_ShutdownFinishedCnt;

#define SOAD_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define SOAD_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Pointer to the post-build configuration. */
P2CONST(SoAd_ConfigType, AUTOMATIC, SOAD_PBCFG) SoAd_ConfigDataPtr = NULL_PTR;

#define SOAD_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

#define SOAD_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Counts the main function cycles (with wrap around) to handle timeouts for the timeout lists. */
VAR(uint32, SOAD_VAR_NOINIT) SoAd_GlobalCounter;

#define SOAD_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

#define SOAD_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/*! Indicates current state of the module state machine (Valid values: SOAD_STATE_*). */
VAR(SoAd_StateType, SOAD_VAR_ZERO_INIT) SoAd_State = SOAD_STATE_UNINIT;

#define SOAD_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/**********************************************************************************************************************
  SoAd_HandleShutdown()
**********************************************************************************************************************/
/*! \brief      Handles shutdown in main function context.
 *  \details    -
 *  \pre        Module is in state SOAD_STATE_SHUTDOWN_IN_PROGRESSS.
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_HandleShutdown(void);

/**********************************************************************************************************************
  SoAd_FinishShutdown()
**********************************************************************************************************************/
/*! \brief      Sets the module to shutdown state and calls the user notification if configured.
 *  \details    -
 *  \pre        Module is in state SOAD_STATE_SHUTDOWN_IN_PROGRESSS.
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_FinishShutdown(void);

/**********************************************************************************************************************
  SoAd_CallShutdownFinishCallbacks()
**********************************************************************************************************************/
/*! \brief      Calls all configured shutdown finished callbacks.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_CallShutdownFinishCallbacks(void);

#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
  SoAd_CheckIpAddrAssignmentType()
**********************************************************************************************************************/
/*! \brief      Checks value range of variables of type SoAd_IpAddrAssignmentType.
 *  \details    -
 *  \pre        -
 *  \param[in]  Type          IP address type.
 *  \return     E_OK          Type is in valid range.
 *  \return     E_NOT_OK      Type is invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *  \config     SOAD_DEV_ERROR_DETECT
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckIpAddrAssignmentType(
  SoAd_IpAddrAssignmentType Type);
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_HandleShutdown()
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
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_HandleShutdown(void)
{
  /* #10 Check if any socket is opened. */
  if ( SoAd_SoCon_GetNumberOfOpenSocks() > 0u )
  {
    /* #20 Decrement shutdown finish counter. */
    SoAd_ShutdownFinishedCnt--;

    /* #30 Check if timeout occurred. */
    if ( SoAd_ShutdownFinishedCnt == 0u )
    {
      /* #300 Close all sockets. */
      SoAd_SoCon_CloseAllSockets();

      /* #301 Finish shutdown. */
      SoAd_FinishShutdown();
    }
    /* #31 Close socket connections softly otherwise. */
    else
    {
      /* #310 Check if all socket connections are closed and trigger closing. */
      if ( SoAd_SoCon_CloseAllSoCons() == TRUE )
      {
        /* #311 Close all UDP sockets which are used to open socket connection on reception. */
        SoAd_SoCon_CloseAllSockets();

        /* #312 Finish shutdown. */
        SoAd_FinishShutdown();
      }
    }
  }
  /* #11 Finish shutdown otherwise. */
  else
  {
    SoAd_FinishShutdown();
  }
} /* SoAd_HandleShutdown() */

/**********************************************************************************************************************
 *  SoAd_FinishShutdown()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_FinishShutdown(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset timeout. */
  SoAd_ShutdownFinishedCnt = 0u;

  /* #20 Set to shutdown state. */
  SoAd_State = SOAD_STATE_SHUTDOWN;

  /* #30 Notify user about shutdown. */
  SoAd_CallShutdownFinishCallbacks();
} /* SoAd_FinishShutdown() */

/**********************************************************************************************************************
 *  SoAd_CallShutdownFinishCallbacks()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_CallShutdownFinishCallbacks(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_ShutdownFinishedCbkIterType cbkIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all configured callbacks and call them. */
  for ( cbkIter = 0u; cbkIter < SoAd_GetSizeOfShutdownFinishedCbk(); cbkIter++ )
  {
    if ( SoAd_GetShutdownFinishedCbk(cbkIter) != NULL_PTR )
    {
      SoAd_GetShutdownFinishedCbk(cbkIter)();                                                                          /* SBSW_SOAD_FUNCTION_PTR */
    }
  }
} /* SoAd_CallShutdownFinishCallbacks() */

#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 *  SoAd_CheckIpAddrAssignmentType()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(Std_ReturnType, SOAD_CODE) SoAd_CheckIpAddrAssignmentType(
  SoAd_IpAddrAssignmentType Type)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if IP address assignment type is in valid range. */
  if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_DHCP) ||
    (Type == SOAD_IPADDR_ASSIGNMENT_LINKLOCAL) ||  /* PRQA S 2996 */ /* MD_SoAd_MacroRedundantCheck */
    (Type == SOAD_IPADDR_ASSIGNMENT_IPV6_ROUTER) )
  {
    retVal = E_OK;
  }

  return retVal;
} /* SoAd_CheckIpAddrAssignmentType() */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_InitMemory(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set module state to uninit. */
  SoAd_State = SOAD_STATE_UNINIT;

  /* #20 Reset configuration pointer. */
  SoAd_ConfigDataPtr = NULL_PTR;
} /* SoAd_InitMemory() */

/**********************************************************************************************************************
 *  SoAd_Init()
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
FUNC(void, SOAD_CODE) SoAd_Init(
  P2CONST(SoAd_ConfigType, AUTOMATIC, SOAD_CONST) SoAdConfigPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameter. */
  if ( SoAdConfigPtr == NULL_PTR )
  {
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    EcuM_BswErrorHook((uint16) SOAD_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    errorId = SOAD_E_INIT_FAILED;
  }
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
  else if ( SoAdConfigPtr->FinalMagicNumberOfPBConfig != SOAD_FINAL_MAGIC_NUMBER )
  {
    EcuM_BswErrorHook((uint16) SOAD_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
    errorId =  SOAD_E_INIT_FAILED;
  }
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Initialize configuration pointer. */
    SoAd_ConfigDataPtr = SoAdConfigPtr;

    /* #30 Initialize global data. */
    SoAd_GlobalCounter = 0u;
    SoAd_ShutdownFinishedCnt = 0u;

    /* #40 Initialize event queues. */
    SoAd_EventQueue_Init();

    /* #50 Initialize timeout lists. */
    SoAd_TimeoutList_Init();

    /* #60 Initialize Socket API specific structs. */
    SoAd_TcpIp_Init();

    /* #70 Initialize local address structs. */
    SoAd_SoCon_InitLocalAddr();

    /* #80 Initialize socket connection structs. */
    SoAd_SoCon_InitSoCon();
    SoAd_SoCon_InitSocket();

    /* #90 Initialize routing group structs. */
    SoAd_RouteGrp_Init();

    /* #100 Initialize Tx structs. */
    SoAd_Tx_Init();

    /* #110 Initialize measurement data. (if enabled) */
#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
    SoAd_Measure_Init();
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

    /* #120 Set module state to initialized. */
    SoAd_State = SOAD_STATE_INIT;
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #130 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_INIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_Init() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  SoAd_IfTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType          retVal = E_NOT_OK;
#else
  Std_ReturnType          retVal;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                   errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAdSrcPduId >= SoAd_GetSizeOfTxPduIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(SoAdSrcPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId)) == SOAD_UL_API_TP )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAdSrcPduInfoPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  /* Check trigger transmit with meta data use case:
   * If trigger transmit and meta data is enabled data pointer with meta data must be provided. */
  else if ( (SoAd_GetIfTriggerTransmitModeOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId)) !=
      SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE) &&
    (SoAd_IsMetaDataTxEnabledOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId)) == TRUE) &&
    (SoAdSrcPduInfoPtr->SduDataPtr == NULL_PTR) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  /* Check trigger transmit use case:
   * If no data pointer is provided trigger transmit is required. */
  else if ( (SoAdSrcPduInfoPtr->SduDataPtr == NULL_PTR) &&
    (SoAd_GetIfTriggerTransmitModeOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId)) ==
      SOAD_IF_TRIGGER_TRANSMIT_MODE_NONE) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    pduRouteIdx = SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId);

    /* #30 Trigger transmission of PDU. */
    retVal = SoAd_Tx_IfTransmit(pduRouteIdx, SoAdSrcPduInfoPtr, &errorId);                                             /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfTransmit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_IfRoutingGroupTransmit()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  Std_ReturnType          retVal = E_NOT_OK;
  uint8                   errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( !SoAd_IsTxTriggerableOfRouteGrp(SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id)) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check initialization state to reject request in case of shutdown. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);

      /* #40 Set transmission request for all related PduRouteDests. */
      SoAd_RouteGrp_SetIfTransmit(routeGrpIdx);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_ROUT_GROUP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfRoutingGroupTransmit() */

/**********************************************************************************************************************
 *  SoAd_IfSpecificRoutingGroupTransmit()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_IfSpecificRoutingGroupTransmit(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  SoAd_SizeOfSoConType    soConIdx;
  uint8                   errorId = SOAD_E_NO_ERROR;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( !SoAd_IsTxTriggerableOfRouteGrp(SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id)) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check initialization state to reject request in case of shutdown. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Set transmission request for the related PduRouteDest. */
      retVal = SoAd_RouteGrp_SetIfSpecificTransmit(routeGrpIdx, soConIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_IF_SPEC_ROUT_GROUP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_IfSpecificRoutingGroupTransmit() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_TpTransmit()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpTransmit(
  PduIdType SoAdSrcPduId,
  P2CONST(PduInfoType, AUTOMATIC, SOAD_APPL_DATA) SoAdSrcPduInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx;
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType          retVal = E_NOT_OK;
#else
  Std_ReturnType          retVal;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8                   errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoAdSrcPduId >= SoAd_GetSizeOfTxPduIdMap() )
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(SoAdSrcPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId)) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAdSrcPduInfoPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    pduRouteIdx = SoAd_GetPduRouteIdxOfTxPduIdMap(SoAdSrcPduId);

    /* #30 Request transmission of PDU. */
    retVal = SoAd_Tx_TpTransmit(pduRouteIdx, SoAdSrcPduInfoPtr);                                                       /* SBSW_SOAD_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpTransmit() */

/**********************************************************************************************************************
 *  SoAd_Shutdown()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Shutdown(void)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType  retVal = E_NOT_OK;
#else
  Std_ReturnType  retVal;
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8           errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    switch (SoAd_State)
    {
      /* #20 Handle shutdown request in case module is initialized. */
      case SOAD_STATE_INIT:
      {
        /* #200 Return that shutdown is in progress if any socket is opened (continue shutdown in main function). */
        if ( SoAd_SoCon_GetNumberOfOpenSocks() != 0u )
        {
          SoAd_ShutdownFinishedCnt = SOAD_SHUTDOWN_FINISHED_WAIT;
          SoAd_State = SOAD_STATE_SHUTDOWN_IN_PROGRESSS;
          retVal = SOAD_E_INPROGRESS;
        }
        /* #201 Return that shutdown is finished and notify user if all sockets are closed. */
        else
        {
          SoAd_State = SOAD_STATE_SHUTDOWN;
          SoAd_CallShutdownFinishCallbacks();
          retVal = E_OK;
        }
        break;
      }
      /* #21 Return corresponding state in case shutdown is in progress. */
      case SOAD_STATE_SHUTDOWN_IN_PROGRESSS:
      {
        retVal = SOAD_E_INPROGRESS;
        break;
      }
      /* #22 Return corresponding state in case shutdown is finished. */
      default: /* SOAD_STATE_SHUTDOWN */
      {
        retVal = E_OK;
        break;
      }
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_SHUTDOWN, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_Shutdown() */

/**********************************************************************************************************************
 *  SoAd_TpCancelTransmit()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelTransmit(
  PduIdType PduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType pduRouteIdx;
  Std_ReturnType          retVal = E_NOT_OK;
  uint8                   errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (PduId >= SoAd_GetSizeOfTxPduIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(PduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(PduId)) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      pduRouteIdx = SoAd_GetPduRouteIdxOfTxPduIdMap(PduId);

      /* #40 Store cancellation request. */
      retVal = SoAd_Tx_TpCancelTransmit(pduRouteIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_CANCEL_TRANSMIT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpCancelTransmit() */

/**********************************************************************************************************************
 *  SoAd_TpCancelReceive()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TpCancelReceive(
  PduIdType PduId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketRouteType  sockRouteIdx;
  uint8                       errorId = SOAD_E_NO_ERROR;
  Std_ReturnType              retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (PduId >= SoAd_GetSizeOfRxPduIdIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRxPduIdIdMap(PduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoAd_GetUpperLayerApiOfSocketRoute(SoAd_GetSocketRouteIdxOfSocketRouteDest(
    SoAd_GetSocketRouteDestIdxOfRxPduIdIdMap(PduId))) == SOAD_UL_API_IF )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      sockRouteIdx = SoAd_GetSocketRouteIdxOfSocketRouteDest(SoAd_GetSocketRouteDestIdxOfRxPduIdIdMap(PduId));

      /* #40 Store cancellation request. */
      retVal = SoAd_Rx_TpCancelReceive(sockRouteIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TP_CANCEL_RECEIVE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TpCancelReceive() */

/**********************************************************************************************************************
 *  SoAd_GetSoConId()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetSoConId(
  PduIdType TxPduId,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) SoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfPduRouteType     pduRouteIdx;
  SoAd_SizeOfPduRouteDestType pduRouteDestIdx;
  SoAd_SizeOfSoConType        soConIdx;
  Std_ReturnType              retVal = E_NOT_OK;
  uint8                       errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (TxPduId >= SoAd_GetSizeOfTxPduIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfTxPduIdMap(TxPduId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( (SoAd_GetPduRouteDestEndIdxOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(TxPduId)) -
      SoAd_GetPduRouteDestStartIdxOfPduRoute(SoAd_GetPduRouteIdxOfTxPduIdMap(TxPduId))) != 1u )
  {
    errorId = SOAD_E_INV_PDUID;
  }
  else if ( SoConIdPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Return corresponding socket connection identifier. */
      pduRouteIdx = SoAd_GetPduRouteIdxOfTxPduIdMap(TxPduId);
      pduRouteDestIdx = SoAd_GetPduRouteDestStartIdxOfPduRoute(pduRouteIdx);
      soConIdx = SoAd_GetSoConIdxOfPduRouteDest(pduRouteDestIdx);

      *SoConIdPtr = SoAd_GetSoConIdOfSoCon(soConIdx);                                                                  /* SBSW_SOAD_POINTER_WRITE */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_SO_CON_ID, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetSoConId() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_OpenSoCon()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_OpenSoCon(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId))) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Store open request. */
      retVal = SoAd_SoCon_RequestOpenSoCon(soConIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_OPEN_SO_CON, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_OpenSoCon() */

/**********************************************************************************************************************
 *  SoAd_CloseSoCon()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_CloseSoCon(
  SoAd_SoConIdType SoConId,
  boolean Abort)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter 'SoConId'. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId))) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Store close request. */
      retVal = SoAd_SoCon_RequestCloseSoCon(soConIdx, Abort);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_CLOSE_SO_CON, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_CloseSoCon() */

/**********************************************************************************************************************
 *  SoAd_RequestIpAddrAssignment()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_RequestIpAddrAssignment(
  SoAd_SoConIdType SoConId,
  SoAd_IpAddrAssignmentType Type,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalIpAddrPtr,
  uint8 Netmask,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter 'SoConId'. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  /* #30 Check plausibility of input parameter 'Type'. */
  else if ( SoAd_CheckIpAddrAssignmentType(Type) == E_NOT_OK )
  {
    errorId = SOAD_E_INV_ARG;
  }
  /* #40 Check plausibility of input parameter 'LocalIpAddrPtr' dependent on 'Type'. */
  else if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) && (LocalIpAddrPtr == NULL_PTR) )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (Type == SOAD_IPADDR_ASSIGNMENT_STATIC) &&
    (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfSoConGrp(
      SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId)))) !=
        LocalIpAddrPtr->domain) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #50 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #60 Handle IP address assignment request. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      retVal = SoAd_TcpIp_RequestIpAddrAssignment(
        soConIdx,
        Type,
        LocalIpAddrPtr,
        Netmask,
        DefaultRouterPtr);                                                                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #70 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_REQ_IP_ADDR_ASSIGN, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_RequestIpAddrAssignment() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_ReleaseIpAddrAssignment()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReleaseIpAddrAssignment(
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Handle IP address assignment release request. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      retVal = SoAd_TcpIp_ReleaseIpAddrAssignment(soConIdx);
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_RLS_IP_ADDR_ASSIGN, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReleaseIpAddrAssignment() */

/**********************************************************************************************************************
 *  SoAd_GetLocalAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetLocalAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) LocalAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) NetmaskPtr,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) DefaultRouterPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( LocalAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( NetmaskPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( DefaultRouterPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Get local IP address. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      SoAd_TcpIp_GetIpAddr(soConIdx, LocalAddrPtr, NetmaskPtr, DefaultRouterPtr);                                      /* SBSW_SOAD_POINTER_FORWARD */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_LOCAL_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetLocalAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_GetPhysAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetPhysAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( PhysAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Get physical address. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      retVal = SoAd_TcpIp_GetPhysAddr(soConIdx, PhysAddrPtr);                                                          /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_PHYS_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetPhysAddr() */

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Return remote address if it contains at least wildcards. */
      retVal = SoAd_SoCon_CheckAndGetRemoteAddr(soConIdx, IpAddrPtr);                                                  /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRemoteAddr() */

/**********************************************************************************************************************
 *  SoAd_GetRemoteAddrState()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRemoteAddrState(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr,
  P2VAR(SoAd_RemAddrStateType, AUTOMATIC, SOAD_APPL_VAR) RemAddrState)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( RemAddrState == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Return remote address state. */
      SoAd_SoCon_GetRemoteAddrState(soConIdx, IpAddrPtr, RemAddrState);                                                /* SBSW_SOAD_POINTER_FORWARD */

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_REMOTE_ADDR_STATE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRemoteAddrState() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_GetRcvRemoteAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetRcvRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) IpAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( !SoAd_IsRcvRemAddrUsedOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId)) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( IpAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Try to return received remote address. */
      retVal = SoAd_SoCon_CheckAndGetRcvRemoteAddr(soConIdx, IpAddrPtr);                                               /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_RCV_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_GetRcvRemoteAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_EnableRouting()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableRouting(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  uint8                   errorId = SOAD_E_NO_ERROR;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsMultiInstanceOnGrpOfRouteGrp(SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id)) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);

      /* #40 Enable routing group on all related socket connections. */
      SoAd_RouteGrp_SetRoutingGroupState(routeGrpIdx, TRUE);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_ENABLE_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_EnableRouting() */

/**********************************************************************************************************************
 *  SoAd_EnableSpecificRouting()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EnableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx;
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  uint8                   errorId = SOAD_E_NO_ERROR;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Enable routing group on all related PduRouteDests and SocketRoutes on the specified socket connection. */
      retVal = SoAd_RouteGrp_SetSpecificRoutingGroupState(routeGrpIdx, soConIdx, TRUE);

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
      /* #50 Check if routing group could not be enabled since specified socket connection is not related. */
      if ( retVal == E_NOT_OK )
      {
        errorId = SOAD_E_INV_ARG;
      }
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_ENABLE_SPECIFIC_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_EnableSpecificRouting() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_DisableRouting()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableRouting(
  SoAd_RoutingGroupIdType id)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  uint8                   errorId = SOAD_E_NO_ERROR;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of input parameter. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);

      /* #40 Disable routing group on all dependent socket connections. */
      SoAd_RouteGrp_SetRoutingGroupState(routeGrpIdx, FALSE);

      retVal = E_OK;
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DISABLE_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_DisableRouting() */

/**********************************************************************************************************************
 *  SoAd_DisableSpecificRouting()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_DisableSpecificRouting(
  SoAd_RoutingGroupIdType id,
  SoAd_SoConIdType SoConId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType    soConIdx;
  SoAd_SizeOfRouteGrpType routeGrpIdx;
  uint8                   errorId = SOAD_E_NO_ERROR;
  Std_ReturnType          retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (id >= SoAd_GetSizeOfRouteGrpIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfRouteGrpIdMap(id)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      routeGrpIdx = SoAd_GetRouteGrpIdxOfRouteGrpIdMap(id);
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Disable routing group on all related PduRouteDests and SocketRoutes on the specified socket connection. */
      retVal = SoAd_RouteGrp_SetSpecificRoutingGroupState(routeGrpIdx, soConIdx, FALSE);

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
      /* #50 Check if routing group could not be disabled since specified socket connection is not related. */
      if ( retVal == E_NOT_OK )
      {
        errorId = SOAD_E_INV_ARG;
      }
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #60 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DISABLE_SPECIFIC_ROUTING, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_DisableSpecificRouting() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_SetRemoteAddr()
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
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  uint8                 errorId = SOAD_E_NO_ERROR;
  Std_ReturnType        retVal = E_NOT_OK;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_IsSockAutoSoConSetupOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId))) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_GetDomainOfLocalAddr(
    SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId)))) !=
      RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Try to set remote address. */
      retVal = SoAd_SoCon_SetRemoteAddr(soConIdx, RemoteAddrPtr);                                                      /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_SET_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_SetRemoteAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_SetUniqueRemoteAddr()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_SetUniqueRemoteAddr(
  SoAd_SoConIdType SoConId,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(SoAd_SoConIdType, AUTOMATIC, SOAD_APPL_VAR) AssignedSoConIdPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_GetDomainOfLocalAddr(
    SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConIdxOfSoConMap(SoConId)))) !=
      RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( AssignedSoConIdPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check module state. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      /* #40 Try to set remote address and return the assigned socket connection. */
      retVal = SoAd_SoCon_SetUniqueRemoteAddr(soConIdx, RemoteAddrPtr, AssignedSoConIdPtr);                            /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_SET_UNI_REMOTE_ADDR, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_SetUniqueRemoteAddr() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_ReadDhcpHostNameOption()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) data)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( length == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( data == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Handle read DHCP hostname option request. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      retVal = SoAd_TcpIp_ReadDhcpHostNameOption(soConIdx, length, data);                                              /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_READ_DHCP_HOST_NAME_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReadDhcpHostNameOption() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_WriteDhcpHostNameOption()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpHostNameOption(
  SoAd_SoConIdType SoConId,
  uint8 length,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) data)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSoConType  soConIdx;
  Std_ReturnType        retVal = E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (SoConId >= SoAd_GetSizeOfSoConMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfSoConMap(SoConId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( data == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Handle write DHCP hostname option request. */
      soConIdx = SoAd_GetSoConIdxOfSoConMap(SoConId);

      retVal = SoAd_TcpIp_WriteDhcpHostNameOption(soConIdx, length, data);                                             /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_WRITE_DHCP_HOST_NAME_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_WriteDhcpHostNameOption() */

/**********************************************************************************************************************
 *  SoAd_ReadDhcpOption()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ReadDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) DataLengthPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8           errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId)) == SOAD_AF_INET) &&
    (Option > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataLengthPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId)) == SOAD_AF_INET) &&
    (*DataLengthPtr > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Read requested DHCP option. */
      retVal = SoAd_TcpIp_ReadDhcpOption(IpAddrId, Option, DataLengthPtr, DataPtr);                                    /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_READ_DHCP_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_ReadDhcpOption() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_WriteDhcpOption()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_WriteDhcpOption(
  SoAd_LocalAddrIdType IpAddrId,
  uint16 Option,
  uint16 DataLength,
  P2CONST(uint8, AUTOMATIC, SOAD_APPL_VAR) DataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal = E_NOT_OK;
  uint8           errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId)) == SOAD_AF_INET) &&
    (Option > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (SoAd_GetDomainOfLocalAddr(SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId)) == SOAD_AF_INET) &&
    (DataLength > SOAD_MAX_UINT_8) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( DataPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is initialized. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #40 Write requested DHCP option. */
      retVal = SoAd_TcpIp_WriteDhcpOption(IpAddrId, Option, DataLength, DataPtr);                                      /* SBSW_SOAD_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_WRITE_DHCP_OPT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_WriteDhcpOption() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#if ( SOAD_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, SOAD_APPL_VAR) versioninfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check plausibility of input parameter. */
  if ( versioninfo == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON  */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Return version info. */
    versioninfo->vendorID = (SOAD_VENDOR_ID);                                                                          /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->moduleID = (SOAD_MODULE_ID);                                                                          /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_major_version = (SOAD_SW_MAJOR_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_minor_version = (SOAD_SW_MINOR_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
    versioninfo->sw_patch_version = (SOAD_SW_PATCH_VERSION);                                                           /* SBSW_SOAD_POINTER_WRITE */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #30 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_VERSION_INFO, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON  */
} /* SoAd_GetVersionInfo() */
#endif /* SOAD_VERSION_INFO_API == STD_ON */

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_GetAndResetMeasurementData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_GetAndResetMeasurementData(
  SoAd_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  Std_ReturnType retVal = E_NOT_OK;
# else
  Std_ReturnType retVal;
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  uint8          errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  /* Do not check 'MeasurementDataPtr' since it can be NULL_PTR. */
  /* No DET error check is expected for the parameter MeasurementIdx. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* PRQA S 2992,2996,2880 4 */ /* MD_SoAd_BooleanValueRangeCheck */
  else if( (MeasurementResetNeeded != TRUE) &&
    (MeasurementResetNeeded != FALSE) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Try to get and reset measurement data. */
    retVal = SoAd_Measure_GetAndReset(MeasurementIdx, MeasurementResetNeeded, MeasurementDataPtr);                     /* SBSW_SOAD_POINTER_AND_NULL_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_GET_RESET_MEASURE_DATA, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId);
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */

  return retVal;
} /* SoAd_GetAndResetMeasurementData() */
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

/**********************************************************************************************************************
 *  SoAd_MainFunctionRx()
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
FUNC(void, SOAD_CODE) SoAd_MainFunctionRx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check if component is initialized. */
    if ( SoAd_State == SOAD_STATE_INIT )
    {
      /* #30 Handle reception on sockets (socket states are checked additionally). */
      SoAd_TcpIp_MainFunctionRx();

      /* #40 Handle TP reception. */
      SoAd_Rx_HandleReception(&errorId);                                                                               /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_RX, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionRx() */

/**********************************************************************************************************************
 *  SoAd_MainFunctionState()
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
FUNC(void, SOAD_CODE) SoAd_MainFunctionState(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Check if component is not in state shutdown. */
    if ( SoAd_State != SOAD_STATE_SHUTDOWN )
    {
      /* #30 Handle shutdown if shutdown is in progress. */
      if ( SoAd_State == SOAD_STATE_SHUTDOWN_IN_PROGRESSS )
      {
        SoAd_HandleShutdown();
      }
      /* #31 Handle socket states otherwise. */
      else
      {
        SoAd_TcpIp_MainFunctionState();
      }

      /* #40 Check if UDP alive supervision timeout is configured. */
      if ( SoAd_HasTimeoutListUdpAlive() )
      {
        /* #400 Handle UDP alive supervision timeout. */
        SoAd_SoCon_HandleUdpAliveTimeout();
      }

      /* #50 Handle socket connection states. */
      SoAd_SoCon_HandleSoConStates();
    }
    /* #60 Handle global timer counter. */
    /* Has to be handled at the end of this main function since timeouts for transmission (nPdu) are set in this
       context which would be overwritten in each call to this main function and no transmission would be performed in
       context of the transmission main function. */
    SoAd_GlobalCounter++;
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #70 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_STATE, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionState() */

/**********************************************************************************************************************
 *  SoAd_MainFunctionTx()
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
FUNC(void, SOAD_CODE) SoAd_MainFunctionTx(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if component is not in state shutdown. */
    if ( SoAd_State != SOAD_STATE_SHUTDOWN )
    {
      /* #40 Handle PDU transmission. */
      SoAd_Tx_HandleTransmission();

      /* #50 Handle socket transmission. */
      SoAd_TcpIp_MainFunctionTx();

      /* #60 Handle routing group transmission. */
      SoAd_RouteGrp_HandleIfTransmit(&errorId);                                                                        /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */

      /* #70 Handle transmission confirmation. */
      SoAd_Tx_HandleConfirmation();
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #80 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION_TX, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunctionTx() */

#if ( SOAD_SINGLE_MAIN_FUNCTION == STD_ON )
/**********************************************************************************************************************
 *  SoAd_MainFunction()
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
FUNC(void, SOAD_CODE) SoAd_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  else
# endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call main function for reception (socket states are checked additionally). */
    SoAd_MainFunctionRx();

    /* #30 Call main function for states. */
    SoAd_MainFunctionState();

    /* #40 Call main function for transmission (if enabled). */
    SoAd_MainFunctionTx();
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #50 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_MAIN_FUNCTION, errorId);
  }
# else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_MainFunction() */
#endif /* SOAD_SINGLE_MAIN_FUNCTION == STD_ON */

/**********************************************************************************************************************
 *  SoAd_RxIndication()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_MSR_Rule8.13 */
FUNC(void, SOAD_CODE) SoAd_RxIndication(
  SoAd_SocketIdType SocketId,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = 0u;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( SoAd_GetDomainOfLocalAddr(
    SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) !=
      RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( BufPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( Length == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Forward received data segment to handle reception. */
    SoAd_Rx_RxIndication(sockIdx, RemoteAddrPtr, BufPtr, Length, &errorId);                                            /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_RX_INDICATION, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_RxIndication() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_CopyTxData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(BufReq_ReturnType, SOAD_CODE) SoAd_CopyTxData(
  SoAd_SocketIdType SocketId,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
#if ( SOAD_TX_DYN_LEN == STD_ON )
  P2VAR(uint16, AUTOMATIC, SOAD_APPL_VAR) BufLengthPtr
#else
  uint16 BufLength
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  )
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_TX_DYN_LEN == STD_OFF )
  uint16                localBufLength = BufLength;
#endif /* SOAD_TX_DYN_LEN == STD_OFF */
  SoAd_SizeOfSocketType sockIdx = 0u;
  BufReq_ReturnType     retVal = BUFREQ_E_NOT_OK;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( BufPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# if ( SOAD_TX_DYN_LEN == STD_ON )
  else if ( BufLengthPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( *BufLengthPtr == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
# else
  else if ( localBufLength == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
# endif /* SOAD_TX_DYN_LEN == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle copy request for transmission data. */
#if ( SOAD_TX_DYN_LEN == STD_ON )
    retVal = SoAd_Tx_CopyTxData(sockIdx, BufPtr, BufLengthPtr);                                                        /* SBSW_SOAD_POINTER_FORWARD */
#else
    retVal = SoAd_Tx_CopyTxData(sockIdx, BufPtr, &localBufLength);                                                     /* SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_TX_DYN_LEN == STD_ON */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_COPY_TX_DATA, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_CopyTxData() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_TxConfirmation()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TxConfirmation(
  SoAd_SocketIdType SocketId,
  uint16 Length)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = 0u;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( Length == 0u )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( !SoAd_IsTxMgtUsedOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle TxConfirmation. */
    SoAd_Tx_TxConfirmation(sockIdx, Length);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TX_CONFIRMATION, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TxConfirmation() */

/**********************************************************************************************************************
 *  SoAd_LocalIpAddrAssignmentChg()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_LocalIpAddrAssignmentChg(
  SoAd_LocalAddrIdType IpAddrId,
  SoAd_IpAddrStateType State)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( (State != SOAD_IPADDR_STATE_ASSIGNED) &&
    (State != SOAD_IPADDR_STATE_ONHOLD) &&
    (State != SOAD_IPADDR_STATE_UNASSIGNED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle local address state change. */
    SoAd_SoCon_LocalIpAddrAssignmentChg(SoAd_GetLocalAddrIdxOfLocalAddrIdMap(IpAddrId), State);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_LOCAL_IP_ADDR_ASSIGNMENT_CHG, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_LocalIpAddrAssignmentChg() */

/**********************************************************************************************************************
 *  SoAd_TcpAccepted()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_MSR_Rule8.13 */
/* PRQA S 3206 4 */ /* MD_SoAd_UnusedParameter */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TcpAccepted(
  SoAd_SocketIdType SocketId,
  SoAd_SocketIdType SocketIdConnected,
  P2VAR(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = 0u;
  Std_ReturnType        retVal = E_NOT_OK;
#if ( SOAD_TCP == STD_ON )
  uint8                 errorId = SOAD_E_NO_ERROR;
#else
  uint8                 errorId = SOAD_E_INV_SOCKETID;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# if ( SOAD_TCP == STD_ON )
  else if ( !SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx))) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( SoAd_IsTcpInitiateOfSocketTcp(
    SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( SocketIdConnected == SOAD_INV_SOCKET_ID )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( RemoteAddrPtr == NULL_PTR )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
  else if ( SoAd_GetDomainOfLocalAddr(
    SoAd_GetLocalAddrIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) !=
      RemoteAddrPtr->domain )
  {
    errorId = SOAD_E_PARAM_POINTER;
  }
# endif /* SOAD_TCP == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
    /* #30 Handle acceptance of TCP connection establishment (if enabled). */
    retVal = SoAd_SoCon_TcpAccepted(sockIdx, SocketIdConnected, RemoteAddrPtr);                                        /* SBSW_SOAD_POINTER_FORWARD */
#else
    SOAD_DUMMY_STATEMENT(SocketIdConnected); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    SOAD_DUMMY_STATEMENT(RemoteAddrPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_TCP == STD_ON  */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
# if ( SOAD_TCP == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
# endif /* SOAD_TCP == STD_ON */
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCP_ACCEPTED, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

  return retVal;
} /* SoAd_TcpAccepted() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_TcpConnected()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpConnected(
  SoAd_SocketIdType SocketId)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = 0u;
#if ( SOAD_TCP == STD_ON )
  uint8                 errorId = SOAD_E_NO_ERROR;
#else
  uint8                 errorId = SOAD_E_INV_SOCKETID;
#endif /* SOAD_TCP == STD_ON */

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# if ( SOAD_TCP == STD_ON )
  else if ( !SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx))) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
  else if ( !SoAd_IsTcpInitiateOfSocketTcp(
    SoAd_GetSocketTcpIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) )
  {
    errorId = SOAD_E_INV_SOCKETID;
  }
# endif /* SOAD_TCP == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_TCP == STD_ON )
    /* #30 Handle TCP connect (if enabled). */
    SoAd_SoCon_TcpConnected(sockIdx);
#endif /* SOAD_TCP == STD_ON  */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
# if ( SOAD_TCP == STD_ON )
  if ( errorId != SOAD_E_NO_ERROR )
# endif /* SOAD_TCP == STD_ON */
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCP_CONNECTED, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TcpConnected() */

/**********************************************************************************************************************
 *  SoAd_TcpIpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TcpIpEvent(
  SoAd_SocketIdType SocketId,
  SoAd_EventType Event)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfSocketType sockIdx = 0u;
  uint8                 errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_NOT_OK )                                          /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
  {
    /* SoAd may be called with a SocketId which is already removed from socket mapping. Do not report a DET error. */
  }
# if ( SOAD_TCP == STD_ON )
  else if ( (SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx))) ) &&
    (Event != SOAD_TCP_RESET) &&
    (Event != SOAD_TCP_CLOSED) &&
    (Event != SOAD_TCP_FIN_RECEIVED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if (
    (SoAd_IsSocketTcpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) &&
    (SoAd_GetSocketIdxOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx))) == sockIdx) &&
    (Event == SOAD_TCP_FIN_RECEIVED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if (
    (SoAd_IsSocketUdpUsedOfSoConGrp(SoAd_GetSoConGrpIdxOfSoCon(SoAd_GetSoConStartIdxOfSocket(sockIdx)))) &&
    (Event != SOAD_UDP_CLOSED) )
  {
    errorId = SOAD_E_INV_ARG;
  }
# else
  else if ( Event != SOAD_UDP_CLOSED )
  {
    errorId = SOAD_E_INV_ARG;
  }
# endif /* SOAD_TCP == STD_ON */
  else
#else
  if ( SoAd_SoCon_GetSockIdxBySocketId(SocketId, &sockIdx) == E_OK )                                                   /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Handle event on socket. */
    SoAd_SoCon_Event(sockIdx, Event);
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_TCPIP_EVENT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_TcpIpEvent() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  SoAd_DhcpEvent()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_DhcpEvent(
  SoAd_LocalAddrIdType IpAddrId,
  SoAd_DhcpEventType Event)
{
  /* ----- Local Variables ---------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
  SoAd_DhcpEventCbkIterType cbkIter;
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  uint8                     errorId = SOAD_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( SOAD_DEV_ERROR_DETECT == STD_ON )
  /* #10 Check initialization state. */
  if ( SoAd_State == SOAD_STATE_UNINIT )
  {
    errorId = SOAD_E_NOTINIT;
  }
  /* #20 Check plausibility of all input parameters. */
  else if ( (IpAddrId >= SoAd_GetSizeOfLocalAddrIdMap())
# if ( SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE )
    || SoAd_IsInvalidHndOfLocalAddrIdMap(IpAddrId)
# endif /* SOAD_CONFIGURATION_VARIANT == SOAD_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE */
    )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else if ( Event == SOAD_DHCP_EVENT_INVALID )
  {
    errorId = SOAD_E_INV_ARG;
  }
  else
#endif /* SOAD_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
#if ( SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_2 */
# if ( (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) )
    /* #30 Forward DHCP event to user (if DHCP is enabled and socket API is AUTOSAR). */
    for ( cbkIter = 0u; cbkIter < SoAd_GetSizeOfDhcpEventCbk(); cbkIter++ )
    {
      if ( SoAd_GetDhcpEventCbk(cbkIter) != NULL_PTR )
      {
        SoAd_GetDhcpEventCbk(cbkIter)(IpAddrId, Event);                                                                /* SBSW_SOAD_FUNCTION_PTR */
      }
    }
# else
    SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    SOAD_DUMMY_STATEMENT(Event); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
# endif /* (SOAD_DHCPV6_CLIENT_ENABLED == STD_ON) || (SOAD_DHCPV4_CLIENT_ENABLED == STD_ON) */
#else
    SOAD_DUMMY_STATEMENT(IpAddrId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
    SOAD_DUMMY_STATEMENT(Event); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */
#endif /* SOAD_SOCKET_API == SOAD_SOCKET_API_AUTOSAR */
  }

  /* ----- Development Error Report --------------------------------------- */
#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
  /* #40 Report default error if any occurred. */
  if ( errorId != SOAD_E_NO_ERROR )
  {
    (void)Det_ReportError(SOAD_MODULE_ID, SOAD_INSTANCE_ID_DET, SOAD_SID_DHCP_EVENT, errorId);
  }
#else
  SOAD_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */
} /* SoAd_DhcpEvent() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */ /*lint !e451 */

/* Justification for module-specific MISRA deviations:
 MD_SoAd_BasicType: directive 4.6
      Reason:     Data type is used for parameters of called service functions.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_UnusedParameter: rule 2.7
      Reason:     Function parameter is only used in some configurations or is required by specification but not used.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_ConstCausedByUnused: rule 8.13
      Reason:     Function parameter is only used in some configurations.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_PointerCastOnStruct: rule 11.3
      Reason:     A generic struct is used to support one generic parameter in a function but with different derived
                  types which are identified by an element in the generic struct.
      Risk:       Issues concerning safety, portability, and readability.
      Prevention: Program flow has been verified by component tests and code inspection.
 MD_SoAd_PointerCastOnParam: rule 11.3
      Reason:     A generic type is used to support one generic parameter in a function but with different derived
                  types which are identified by an additional function parameter.
      Risk:       Issues concerning safety, portability, and readability.
      Prevention: Program flow has been verified by component tests and code inspection.
 MD_SoAd_GenericWiderTypeCast: rule 10.3, rule 10.8
      Reason:     A configuration dependent data type is cast to the widest expected data type to be
                  generic/configuration independent.
      Risk:       Type mismatch may indicate usage of a wrong data type or variable.
      Prevention: Code inspection.
 MD_SoAd_MacroRedundantCheck: rule 13.7
      Reason:     Value of macro is provided by other module. It may have a different value.
      Risk:       Duplicated macro with same value may lead to misunderstanding while code inspection.
      Prevention: Code inspection.
 MD_SoAd_UsageNotDetected: rule 2.2
      Reason:     Tool does not detect usage of value.
      Risk:       None.
      Prevention: No prevention necessary.
 MD_SoAd_BooleanValueRangeCheck: rule 2.1, rule 2.2, rule 13.7, rule 14.1, rule 14.3
      Reason:     The value range size of boolean may be greater than 2. Therefore, the value range is checked for
                  invalid values. In configurations with a value range of 2 causes this check "always true/false"
                  conditions and unreachable code.
      Risk:       None.
      Prevention: No prevention necessary.
 */

/* Safe BSW assumptions:

  Element existence:
    EventQueueIdent -> always available
    TimeoutListIdent -> always available
    TimeoutListUdpAlive -> available if at least one SoAdSocketRoute over UDP SoAdSocketConnection with
      SoAdSocketUdpAliveSupervisionTimeout is configured
    TimeoutListNPduUdpTx -> available if at least one IF SoAdPduRoute with SoAdTxUdpTriggerMode TRIGGER_NEVER and no
      TP SoAdPduRoute over UDP SoAdSocketConnection is configured

  Indirections:
    SoCon -> RxMgt 1:0..1 (available if a SoAdSocketRoute is configured)
    SoCon -> RxBufferConfig 1:0..1 (available if a
      IF SoAdSocketRoute over TCP SoAdSocketConnection is configured
      OR
      TP SoAdSocketRoute over UDP SoAdSocketConnection is configured
      OR
      TP SoAdSocketRoute over TCP SoAdSocketConnection with PDU header option is configured)
    SoCon -> RxBufStructMgt 1:0..1 (available if a SoAdSocketRoute over TCP SoAdSocketConnection is configured)
    SoCon -> TxMgt 1:0..1 (available if a SoAdPduRoute is configured)
    SoCon -> TpTxBufferConfig 1:0..1 (available if a TP SoAdPduRoute over UDP SoAdSocketConnection is configured)
    SoCon -> TcpTxQueue 1:0..1 (available if TCP is configured on SoAdSocketConnection)
    SoCon -> NPduUdpTx 1:0..1 (available if at least one IF SoAdPduRoute with SoAdTxUdpTriggerMode TRIGGER_NEVER
      and no TP SoAdPduRoute over UDP SoAdSocketConnection is configured)
    SoCon -> Socket 1:1
    SoCon -> SoConGrp 1:1
    SoConGrp -> Socket 1:0..1 (available if UDP/TCP SoAdSocketConnection and no SoAdSocketTcpInitiate are configured)
    Socket -> SoCon 1:1..n
    TcpTxQueue-> TcpTxQueueData 1:1..n
    NPduUdpTx -> NPduUdpTxBuffer 0..n (available if at least one SoAdPduRoute without SoAdTxIfTriggerTransmit is
      configured; n = NPduUdpTxBufferMinOfSocketUdp)
    NPduUdpTx -> NPduUdpTxQueue 0..n (available if at least one SoAdPduRoute with SoAdTxIfTriggerTransmit is
      configured; n = NPduUdpTxQueueSizeOfSocketUdp)
    NPduUdpTxQueue -> NPduUdpTxBuffer 0..n (available if at least one SoAdPduRoute without SoAdTxIfTriggerTransmit is
      configured additionally; n = NPduUdpTxBufferMinOfSocketUdp)
    TpTxBufferConfig -> TpTxBuffer 1:0..n (available if a TP SoAdPduRoute over UDP SoAdSocketConnection is configured;
      n = SOAD_PDU_HDR_SIZE (if enabled) + maximum configured TP-PDU size on corresponding SoAdSocketConnection)
    RxBufferConfig -> IfRxBuffer 1:0..n (available if a IF SoAdSocketRoute over TCP SoAdSocketConnection is configured;
      n = SOAD_PDU_HDR_SIZE (if enabled) + maximum configured IF-PDU size on corresponding SoAdSocketConnectionGroup)
    RxBufferConfig -> TpRxBuffer 1:0..n (available if a TP SoAdSocketRoute over
      UDP SoAdSocketConnection is configured; n = maximum configured TP-PDU size on SoAdSocketConnection
      OR
      TCP SoAdSocketConnection with SoAdTxPduHeaderId is configured; n = SOAD_PDU_HDR_SIZE)
    SocketRoute -> UpperLayer 1:1
    SocketRoute -> SoCon 1:1
    UpperLayer -> IfRxIndicationCbk 1:0..1 (available if a IF SoAdSocketRoute is configured)
    UpperLayer -> IfTriggerTransmitCbk 1:0..1 (available if a IF SoAdPduRoute and SoAdIfTriggerTransmit are configured)
    UpperLayer -> IfTxConfirmationCbk 1:0..1 (available if a IF SoAdPduRoute and SoAdIfTxConfirmation are configured)
    UpperLayer -> TpCopyRxDataCbk 1:0..1 (available if a TP SoAdSocketRoute and no SoAdTpCopyRxDataWithConstPointer are
      configured - xor to TpCopyRxDataConstCbk)
    UpperLayer -> TpCopyRxDataConstCbk 1:0..1 (available if a TP SoAdSocketRoute and SoAdTpCopyRxDataWithConstPointer
      are configured - xor to TpCopyRxDataCbk)
    UpperLayer -> TpCopyTxDataCbk 1:0..1 (available if a TP SoAdPduRoute and no SoAdTpCopyTxDataWithConstPointer are
      configured - xor to TpCopyTxDataConstCbk)
    UpperLayer -> TpCopyTxDataConstCbk 1:0..1 (available if a TP SoAdPduRoute and SoAdTpCopyTxDataWithConstPointer are
      configured - xor to TpCopyTxDataCbk)
    UpperLayer -> TpRxIndicationCbk 1:0..1 (available if a TP SoAdSocketRoute is configured)
    UpperLayer -> TpStartOfReceptionCbk 1:0..1 (available if a TP SoAdSocketRoute and no
      SoAdTpStartOfReceptionWithConstPointer are configured - xor to TpStartOfReceptionConstCbk)
    UpperLayer -> TpStartOfReceptionConstCbk 1:0..1 (available if a TP SoAdSocketRoute and
      SoAdTpStartOfReceptionWithConstPointer are configured - xor to TpStartOfReceptionCbk)
    UpperLayer -> TpTxConfirmationCbk 1:0..1 (available if a TP SoAdPduRoute is configured)
    TimeoutListIdent -> TimeoutListDyn(UdpAlive) 1:0..1 (available if at least one SoAdSocketRoute over UDP
      SoAdSocketConnection with SoAdSocketUdpAliveSupervisionTimeout is configured)
    TimeoutListIdent -> TimeoutListDyn(NPduUdpTx) 1:0..1 (available if at least one IF SoAdPduRoute with
      SoAdTxUdpTriggerMode TRIGGER_NEVER and no TP SoAdPduRoute over UDP SoAdSocketConnection is configured)
    EventQueueIdent -> EventQueueSocketIdx 1:0..1 (available if BSD Socket API is configured)
    EventQueueIdent -> EventQueueTpRxSoCon 1:0..1 (available if a TP SoAdSocketRoute is configured)
    EventQueueIdent -> EventQueueLocalAddr 1:0..1 (available if BSD Socket API is configured)
    EventQueueIdent -> EventQueueStateSoCon 1:1
    EventQueueIdent -> EventQueueTpTxSoCon 1:0..1 (available if a TP SoAdPduRoute is configured)
    EventQueueIdent -> EventQueueTcpTxSoCon 1:0..1 (available if BSD Socket API and a TCP SoAdSocketConnection is
      configured)
    EventQueueIdent -> EventQueueIfUdpPduRoute 1:0..1 (available if a IF SoAdPduRoute over UDP SoAdSocketConnection is
      configured)
    EventQueueIdent -> EventQueueIfTxRouteGrp 1:0..1 (available if a SoAdRoutingGroupTxTriggerable is enabled)

  Size Constraints:
    TpTxBufferConfigDyn <-> TpTxBufferConfig
    TcpTxQueueMgt <-> TcpTxQueue
    NPduUdpTx <-> NPduUdpTxDyn
    SocketDyn <-> Socket
    BestMatchSoConIdxList <-> maximum number of SoCon per SoConGrp (at least 1)
    EventQueue <-> EventQueueDyn
    EventQueueFlag <-> maximum of size of: SoCon, Socket, LocalAddr, PduRoute or RouteGrp
    EventQueueSocketIdx <-> Socket
    EventQueueTpRxSoCon <-> SoCon (with TP socket routes)
    EventQueueLocalAddr <-> LocalAddr
    EventQueueStateSoCon <-> SoCon
    EventQueueTpTxSoCon <-> SoCon (with TP PDU routes)
    EventQueueTcpTxSoCon <-> SoCon (on TCP socket connection)
    EventQueueIfUdpPduRoute <-> PduRoute (IF on UDP socket connection)
    EventQueueIfTxRouteGrp <-> RouteGrp (with Tx triggerable)
    TimeoutListUdpAliveMap <-> SoCon
    TimeoutListNPduUdpTxMap <-> NPduUdpTx

  These assumptions are modeled in ComStackLib (verification: to be reviewed in generator).
*/

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_SOAD_CSL01
    \DESCRIPTION      Access to array with index using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL01 of ComStackLib.

  \ID SBSW_SOAD_CSL02
    \DESCRIPTION      Access to array with index of array with same size using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL02 of ComStackLib.

  \ID SBSW_SOAD_CSL03
    \DESCRIPTION      Access to array via indirection using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib. The index used to access the indirection may depend
                         on a function parameter. The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller.

  \ID SBSW_SOAD_CSL03_CSL02
    \DESCRIPTION      Access to array with index of array with same size via indirection using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 followed by CSL02 of ComStackLib.

  \ID SBSW_SOAD_OPTIONAL_CSL03
    \DESCRIPTION      Access to array via optional indirection using ComStackLib.
    \COUNTERMEASURE   \N Qualified use-case CSL03 of ComStackLib. According to the Safe BSW assumptions modeled in
                         ComStackLib it is ensured that optional indirection is available here. The index used to
                         access the indirection may depend on a function parameter. The validity of the function
                         parameter is defined at the function declaration and has to be ensured by the caller.

  \ID SBSW_SOAD_OPTIONAL_CHECKED_CSL03
    \DESCRIPTION      Access to array via optional indirection using ComStackLib.
    \COUNTERMEASURE   \R The availability of the optional indirection (qualified use-case CSL03 of ComStackLib) is
                         checked. The index used to access the indirection may depend on a function parameter. The
                         validity of the function parameter is defined at the function declaration and has to be
                         ensured by the caller.

  \ID SBSW_SOAD_OPTIONAL_CHECKED_PREPROC_CSL03
    \DESCRIPTION      Access to array via optional indirection using ComStackLib.
    \COUNTERMEASURE   \N The availability of the optional indirection (qualified use-case CSL03 of ComStackLib) is
                         checked in a specific preprocessor variant. The index used to access the indirection may
                         depend on a function parameter. The validity of the function parameter is defined at the
                         function declaration and has to be ensured by the caller. In other preprocessor variants the
                         runtime check is not available. In this case according to the Safe BSW assumptions modeled in
                         ComStackLib it is ensured that optional indirection is available here.

  \ID SBSW_SOAD_CALCULATED_CSL03_RxBufStructSeg
    \DESCRIPTION      Access to array "SoAd_RxBufStructSeg" based on index stored in "SoAd_RxBufStructMgt".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in "SoAd_SoCon" to
                         get corresponding start and end index of "SoAd_RxBufStructSeg". "SoAd_RxBufStructMgt" is used
                         to store an index and a fill level calculated in range of start and end index provided by
                         "SoAd_SoCon". After initialization the values are always in valid range. Calculations based on
                         the stored values always consider the start and end index given in "SoAd_SoCon".

  \ID SBSW_SOAD_CALCULATED_CSL03_TcpTxQueueData
    \DESCRIPTION      Access to array "SoAd_TcpTxQueueData" based on index stored in "SoAd_TcpTxQueueMgt".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_TcpTxQueue" to get corresponding start and end index of "SoAd_TcpTxQueueData".
                         "SoAd_TcpTxQueueMgt" is used to store an index and fill level calculated in range of start
                         and end index provided by "SoAd_TcpTxQueue". After initialization the values are always in
                         valid range. Calculations based on the stored values always consider the start and end index
                         given in "SoAd_TcpTxQueue".

  \ID SBSW_SOAD_CALCULATED_CSL03_NPduUdpTxQueue
    \DESCRIPTION      Access to array "SoAd_NPduUdpTxQueue" based on index stored in "SoAd_NPduUdpTxDyn".
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxQueue".
                         "SoAd_NPduUdpTxDyn" is used to store an fill level calculated in range of start and end index
                         provided by "SoAd_NPduUdpTx". After initialization the value is always in valid range.
                         Calculations based on the stored value always consider the start and end index given in
                         "SoAd_NPduUdpTx".

  \ID SBSW_SOAD_CALCULATED_CSL03_IpFragBufConfigDyn
    \DESCRIPTION      Access to array "SoAd_IpFragBufConfigDyn" based on index stored in "SoAd_IpFragMgt".
    \COUNTERMEASURE   \N The index stored in "SoAd_IpFragMgt" is always checked against the size of
                         "SoAd_IpFragBufConfig". To access "SoAd_IpFragBufConfigDyn" with an index checked against size
                         of "SoAd_IpFragBufConfig" is qualified use-case CSL02. The index stored in "SoAd_IpFragMgt" is
                         always valid or set to an invalid value after initialization. Before index is used to access
                         "SoAd_IpFragBufConfigDyn" the value is checked against the invalid value.

  \ID SBSW_SOAD_CALCULATED_TimeoutListUdpAlive
    \DESCRIPTION      Access to array "SoAd_TimeoutListUdpAlive" based on index stored in "SoAd_TimeoutListDyn" or
                      "SoAd_TimeoutListUdpAliveMap".
    \COUNTERMEASURE   \N The index/fill level stored in "SoAd_TimeoutListDyn" is incremented/decremented with the
                         elements added to or removed from array list "SoAd_TimeoutListUdpAlive". Therefore, the index
                         is always valid after initialization. The index stored in "SoAd_TimeoutListUdpAliveMap" is set
                         dependent on the index/fill level provided by "SoAd_TimeoutListDyn" or set to an invalid
                         value if unused. When using the value runtime checks are implemented to verify that invalid
                         value is not used as index to access the array.

  \ID SBSW_SOAD_CALCULATED_TimeoutListUdpAliveMap
    \DESCRIPTION      Access to array "SoAd_TimeoutListUdpAliveMap" based on index stored in
                      "SoAd_TimeoutListUdpAlive".
    \COUNTERMEASURE   \N The index stored in "SoAd_TimeoutListUdpAlive" is only used to access
                         "SoAd_TimeoutListUdpAliveMap" when index is valid. This is verified by runtime checks for
                         "SoAd_TimeoutListUdpAlive" with the assumption that all elements of a specific entry in
                         "SoAd_TimeoutListUdpAlive" are set consistently.

  \ID SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx
    \DESCRIPTION      Access to array "SoAd_TimeoutListNPduUdpTx" based on index stored in "SoAd_TimeoutListDyn" or
                      "SoAd_TimeoutListNPduUdpTxMap".
    \COUNTERMEASURE   \N The index/fill level stored in "SoAd_TimeoutListDyn" is incremented/decremented with the
                         elements added to or removed from array list "SoAd_TimeoutListNPduUdpTx". Therefore, the index
                         is always valid after initialization. The index stored in "SoAd_TimeoutListNPduUdpTxMap" is
                         set dependent on the index/fill level provided by "SoAd_TimeoutListDyn" or set to an invalid
                         value if unused. When using the value runtime checks are implemented to verify that invalid
                         value is not used as index to access the array.

  \ID SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTxMap
    \DESCRIPTION      Access to array "SoAd_TimeoutListNPduUdpTxMap" based on index stored in
                      "SoAd_TimeoutListNPduUdpTx".
    \COUNTERMEASURE   \N The index stored in "SoAd_TimeoutListNPduUdpTx" is only used to access
                         "SoAd_TimeoutListNPduUdpTxMap" when index is valid. This is verified by runtime checks for
                         "SoAd_TimeoutListNPduUdpTx" with the assumption that all elements of a specific entry in
                         "SoAd_TimeoutListNPduUdpTx" are set consistently.

  \ID SBSW_SOAD_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards a "null" pointer. The pointer can be used to write to the corresponding
                      invalid memory location.
    \COUNTERMEASURE   \N A different function parameter indicates that pointer must not be used or the function is
                         defined to be called "null" pointer.

  \ID SBSW_SOAD_CAST_POINTER_FORWARD
    \DESCRIPTION      A pointer to a local variable is passed as function parameter with cast to different data type.
                      Pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Local variables are located in valid memory locations. A different function parameter
                         indicates how pointer must be used. Callee cast back to the original data type. The expected
                         data type is defined by the callee.

  \ID SBSW_SOAD_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which could be used to write to the
                      corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type or an additional
                         function parameter is used to describe pointer validity. This is ensured by the caller.

  \ID SBSW_SOAD_POINTER_FORWARD_EXPECTED_SIZE_TX
    \DESCRIPTION      The function forwards pointer to array passed as function parameter which could be used to write
                      to the corresponding memory location. The callee expects a specific range which is not ensured
                      in this context.
    \COUNTERMEASURE   \N In this context a struct "SoAd_TxMgt" is used to store the length to be transmitted. The
                         transmission buffer is provided together with a function parameter which indicates the size of
                         the provided buffer. The validity is ensured by the provider. The size of the provided buffer
                         is checked in this context before (SoAd_Tx_CopyTxDataCheckParameter()) against the values
                         stored in "SoAd_TxMgt" to ensure that forwarded pointer fits to the expected range.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset. Pointer can be used to
                      write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function 
                         parameter. The offset is checked at runtime in a sub-routine or in the called function itself
                         (iterative call) to be smaller than the size indicated by the function parameter.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_FORWARD_NPduUdpTxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_NPduUdpTxBuffer" with offset. Pointer can be used to
                      write to the corresponding memory location.
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxBuffer".
                         "SoAd_NPduUdpTxDyn" is used to store the nPdu length calculated in range of start and end
                         index. Actually "NPduUdpTxBufferMinOfSocketUdp" is used instead of start and end index 
                         provided by "SoAd_NPduUdpTx". According to the Safe BSW assupmtions these values are
                         equivalent. After initialization the length stored in "SoAd_NPduUdpTxDyn" is always in valid
                         range. Calculations based on the stored value always consider the
                         "NPduUdpTxBufferMinOfSocketUdp".

  \ID SBSW_SOAD_CONST_POINTER_AND_POINTER_WITH_OFFSET_FORWARD_NPduUdpTxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_NPduUdpTxBuffer" with offset. Pointer can be used to
                      write to the corresponding memory location. Additionaly function forwards a pointer to constant.
    \COUNTERMEASURE   \N There is an indirection modeled with ComStackLib (Qualified use-case CSL03) in
                         "SoAd_NPduUdpTx" to get corresponding start and end index of "SoAd_NPduUdpTxBuffer".
                         "SoAd_NPduUdpTxDyn" is used to store the nPdu length calculated in range of start and end
                         index. Actually "NPduUdpTxBufferMinOfSocketUdp" is used instead of start and end index 
                         provided by "SoAd_NPduUdpTx". According to the Safe BSW assupmtions these values are
                         equivalent. After initialization the length stored in "SoAd_NPduUdpTxDyn" is always in valid
                         range. Calculations based on the stored value always consider the
                         "NPduUdpTxBufferMinOfSocketUdp".
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to constant.
    \COUNTERMEASURE   \N A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_POINTER_AND_NULL_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter and a "null" pointer which could be
                      used to write to the corresponding memory locations.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range. This is ensured by the caller. To
                         forward a "null" pointer is supported by the function.

  \ID SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which could be
                      used to write to the corresponding memory location and a pointer to constant.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type or an additional
                         function parameter is used to describe pointer validity. This is ensured by the caller.
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_AND_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset and directly without
                      offset. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter. The offset is checked at runtime to be smaller than the size
                         indicated by the function parameter.

  \ID SBSW_SOAD_POINTER_WITH_OFFSET_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter with offset which can be used to write
                      to the corresponding memory location and a pointer to constant.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function
                         parameter. The offset is checked at runtime to be smaller than the size indicated by the
                         function parameter. A pointer to constant must not be used to write to the corresponding
                         memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable which could be used to write to memory
                      location of the variable.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL01
    \DESCRIPTION      The function forwards pointer to a local/global array generated by ComStackLib which could be
                      used to write to memory location.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of array can
                         be passed as function parameter. The array size if forwarded as addtional function parameter
                         to indicate the valid memory range of the array. The value is checked according to qualified
                         use-case CSL01.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size which is
                      passed as function parameter. The pointer could be used to write to memory location.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib.

  \ID SBSW_SOAD_VARIABLE_POINTER_FORWARD_CSL02_CSL03
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size. The
                      index to array with same size is retrieved by indirection using ComStackLib. The index to
                      indirection is passed as function parameter. The pointer could be used to write to memory
                      location.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib. The usage of
                         indirections is qualified use-case CSL03 of ComStackLib.

  \ID SBSW_SOAD_POINTER_FORWARD_IfRxBuffer
    \DESCRIPTION      The function forwards pointer to array "SoAd_IfRxBuffer" with index stored in a global variable
                      "IfRxBufferIdxOfRxBufferConfigDyn". The pointer could be used to write to memory location.
    \COUNTERMEASURE   \N The global variable is set in SoAd_RxIf_TcpPduHdrReceiveHeader() which is called previously. A
                         runtime check ensures that the value is in valid range. Additionally
                         SoAd_RxIf_TcpPduHdrReceiveHeader() checks that this function is not able to exceed the valid
                         range beyond the index. Only if SoAd_RxIf_TcpPduHdrReceiveHeader() succeeds this function is
                         called.

  \ID SBSW_SOAD_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable which could be used to write to memory
                      location of the variable and a pointer to constant.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. A pointer to constant must not be used to write to the
                         corresponding memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_CSL02_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global array with index of array with same size which is
                      passed as function parameter and pointer to constant. None-constant pointers could be used to
                      write to memory location.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The access with an
                         index of array with same size is qualified use-case CSL02 of ComStackLib. A pointer to
                         constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_VARIABLE_POINTER_CSL03_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global array with index of an optional indirection which
                      is accessed with an index passed as function parameter and pointer to constant. None-constant
                      pointers could be used to write to memory location.
    \COUNTERMEASURE   \N Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter. The validity of the index passed as function parameter is
                         defined at the function declaration and has to be ensured by the caller. The availability of
                         the optional indirection (qualified use-case CSL03 of ComStackLib) is checked at runtime. A
                         pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter, pointer to a local/global variable
                      and pointer to constant. None-constant pointers could be used to write to memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. Local/gobal variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter. A pointer to constant must not be used to write
                         to the corresponding memory location.

  \ID SBSW_SOAD_OPTIONAL_POINTER_FORWARD_CSL03
    \DESCRIPTION      The function forwards pointer to an optional array generated by ComStackLib which could be used
                      to write to memory location.
    \COUNTERMEASURE   \N The pointer to the array generated by ComStackLib is based on qualified use-case CSL03 of
                         ComStackLib. According to the Safe BSW assumptions modeled in ComStackLib it is ensured that
                         optional indirection is available here. The index used to access the indirection may depend
                         on a function parameter. The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller.

  \ID SBSW_SOAD_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter and to a local/global variable. Both
                      pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. Local/global variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter.

  \ID SBSW_SOAD_POINTER_EXPECTED_SIZE_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter which requires a specific length and
                      to a local/global variable. Both pointer can be used to write to the corresponding memory
                      location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering additional function
                         parameter. This is ensured by the caller. The required range is checked previously against the
                         additional function parameter by a sub-routine in this function. Local/global variables are
                         located in valid memory locations. Therefore, address of variable can be passed as function
                         parameter.

  \ID SBSW_SOAD_POINTER_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer passed as function parameter as pointer and to a local/global
                      variable. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering an additional function
                         parameter which is used to describe pointer validity. This is ensured by the caller.
                         Local/global variables are located in valid memory locations. Therefore, address of
                         variable can be passed as function parameter.

  \ID SBSW_SOAD_POINTER_AND_POINTER_FORWARD_CSL01
    \DESCRIPTION      The function forwards pointer passed as function parameter and to an array generated by
                      ComStackLib. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. The pointer to the array generated by ComStackLib is based on qualified use-case
                         CSL01 of ComStackLib.

  \ID SBSW_SOAD_POINTER_AND_CONST_POINTER_FORWARD_CSL02
    \DESCRIPTION      The function forwards pointer passed as function parameter and to an element generated by
                      ComStackLib. Both pointer can be used to write to the corresponding memory location.
    \COUNTERMEASURE   \N Pointers passed to function point to a valid memory range considering type of pointer or an
                         additional function parameter is used to describe pointer validity. This is ensured by the
                         caller. The pointer to the element generated by ComStackLib is based on qualified use-case
                         CSL02 of ComStackLib.

  \ID SBSW_SOAD_CONST_POINTER_AND_OPTIONAL_POINTER_FORWARD_CSL03
    \DESCRIPTION      The function forwards pointer to constant and to an optional element generated by ComStackLib.
                      The pointer to optional element generated by ComStackLib can be used to write to the
                      corresponding memory location.
    \COUNTERMEASURE   \N A pointer to constant must not be used to write to the corresponding memory location. The
                         pointer to the element generated by ComStackLib is based on qualified use-case CSL03 of
                         ComStackLib. According to the Safe BSW assumptions modeled in ComStackLib it is ensured that
                         optional indirection is available here. The index used to access the indirection may depend
                         on a function parameter. The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. In case element generated by ComStackLib is
                         an array an addtional parameter describes the valid range. The value of the additional
                         parameter is verified by a runtime check or the Safe BSW assumptions modeled in ComStackLib.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_FORWARD
    \DESCRIPTION      The function forwards pointer to struct element after casting a pointer passed as function
                      parameter to a different type. This may lead to access violations when pointer is not valid.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type". The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type" have additional common struct elements.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_STRUCT_ELEMENT_AND_CONST_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to struct element after casting a pointer passed as function
                      parameter to a different type. This may lead to access violations when pointer is not valid.
                      Additionally the function forwards pointer to constant.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type". The validity of the function parameter is defined at the function
                         declaration and has to be ensured by the caller. "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type" have additional common struct elements.
                         A pointer to constant must not be used to write to the corresponding memory location.

  \ID SBSW_SOAD_SOCK_ADDR_VARIABLE_POINTER_AND_VARIABLE_POINTER_FORWARD
    \DESCRIPTION      The function forwards pointer to a local/global variable with cast to a different struct type
                      which could be used to write to memory location of the variable.
                      Additionally the function forwards pointer to a local/global variable which could be used to
                      write to memory location of the variable.
    \COUNTERMEASURE   \N Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. Refer to
                         definition of generic type "SoAd_SockAddrType" and specfic types "SoAd_SockAddrInetType" and
                         "SoAd_SockAddrInet6Type".
                         Local/gobal variables are located in valid memory locations. Therefore, address of variable
                         can be passed as function parameter.

  \ID SBSW_SOAD_SOCK_ADDR_CAST_POINTER_WRITE
    \DESCRIPTION      The function casts a pointer to a different struct type and uses struct elements of the different
                      struct type to write to the memory location the pointer points to.
    \COUNTERMEASURE   \R Module casts a specific struct type to a generic struct type which is used as function
                         parameter. Depending on a common struct element (used in all specific struct types and
                         generic struct) module can cast back to the corresponding specific struct type. By checking
                         the common struct element it is ensured that only valid memory location is accessed. This is
                         done by a runtime check. Refer to definition of generic type "SoAd_SockAddrType" and specfic
                         types "SoAd_SockAddrInetType" and "SoAd_SockAddrInet6Type".

  \ID SBSW_SOAD_POINTER_WRITE
    \DESCRIPTION      Write access to pointer passed as function parameter.
    \COUNTERMEASURE   \N Pointer passed as function parameter points to valid memory location. This includes struct
                         members in case pointer points to a struct type. This is ensured by caller.

  \ID SBSW_SOAD_PARAMETER_IDX
    \DESCRIPTION      Write access to array element with index given as function parameter which is not checked for
                      validity. The index may be an index of array with same size using ComStackLib.
    \COUNTERMEASURE   \N The valid range of the function parameter is defined at the function declaration and
                         has to be ensured by the caller. In case index is index of different array qualified use-case
                         CSL02 of ComStackLib applies.

  \ID SBSW_SOAD_INDEX_BY_FUNCTION
    \DESCRIPTION      The function writes to array element with index retrieved by subfunction.
    \COUNTERMEASURE   \N Subfunction always returns a valid index for accessed array or indicates if returned value
                         must not be used (e.g. via specific function return value).

  \ID SBSW_SOAD_EXPECTED_SIZE_WRITE
    \DESCRIPTION      The function writes to an array with a specific index. The array size is not checked.
    \COUNTERMEASURE   \N The array has an expected length so indexes within this length can be used to write to
                         corresponding memory location. The expected length is specified by data type (e.g. array of
                         specific size), by Safe BSW assumptions modeled in ComStackLib or by size restrictions in case
                         of function parameter.

  \ID SBSW_SOAD_FUNCTION_PTR
    \DESCRIPTION      Calling a function pointer stored in an array with an index using ComStackLib.
    \COUNTERMEASURE   \S The user of MICROSAR Safe shall verify that a configurable callback exists if configured.
                         Verification can be performed by a review of the code of the corresponding user.
                         SMI-150374
                      \R In case an optional function pointer is used availability is enusured by a runtime "null"
                         pointer check. Index validity is already ensured by qualified use-case CSL03 of ComStackLib.
                         In case of optional indirection it is ensured that optional indirection is available according
                         to Safe BSW assumptions modeled in ComStackLib.

SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN

  \ID COV_SOAD_COMPATIBILITY
    \ACCEPT TX
    \ACCEPT XF
    \REASON [COV_MSR_COMPATIBILITY]

  \ID COV_SOAD_QM_FEATURE_1
    \ACCEPT XF
    \ACCEPT XF xf xf
    \REASON This code is part of a QM-Feature and has to be deactivated for SafeBSW.

  \ID COV_SOAD_QM_FEATURE_2
    \ACCEPT TX
    \REASON This code is only deactivated when a QM-Feature is activated.

  \ID COV_SOAD_QM_FEATURE_3
    \ACCEPT XX
    \ACCEPT XX xx xx
    \REASON This decision is only activated when a QM-Feature activated.

  \ID COV_SOAD_DEV_ERROR_DETECT
    \ACCEPT TX
    \ACCEPT TX tx tf
    \REASON SafeBSW requires DEV_ERROR_DETECT to be always on. The other condition is covered completely.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: SoAd.c
 *********************************************************************************************************************/
