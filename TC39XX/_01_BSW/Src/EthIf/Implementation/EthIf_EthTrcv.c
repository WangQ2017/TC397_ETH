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
/*!        \file  EthIf_EthTrcv.c
 *        \brief  EthIf EthTrcv public API source file
 *
 *      \details  Implementation of the public API of the sub-module EthTrcv of EthIf.
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

#define ETHIF_ETHTRCV_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_EthTrcv.h"
#include "EthIf_EthTrcv_Cbk.h"
#include "EthIf_EthTrcv_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_EthTrcv.c and EthIf.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_ETHTRCV_LOCAL)                                                                                      /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHTRCV_LOCAL                                          static
#endif

#if !defined (ETHIF_ETHTRCV_LOCAL_INLINE)                                                                               /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ETHTRCV_LOCAL_INLINE                                   LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_QueryForWakeupMap
 *********************************************************************************************************************/
/*! \brief          Queries for a wakeup map
 *  \details        This function queries for the wakeup map by taking the wakeup source passed.
 *  \param[in]      wakeupSource  Wakeup source of EcuM
 *  \return         ETHIF_INVALID_WAKEUP_MAP - no wakeup map found
 *  \return         other values - wakeup map index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_WakeupMapIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupMap(
  EcuM_WakeupSourceType wakeupSource);

/**********************************************************************************************************************
 *  EthIf_QueryForWakeupTransceiver
 *********************************************************************************************************************/
/*! \brief          Queries for the wakeup Ethernet transceiver
 *  \details        This function queries for the wakeup Ethernet transceiver belonging to the EthIf controller.
 *  \param[in]      ethIfCtrlIdx    EthIf controller index
 *  \return         ETHIF_INVALID_WAKEUP_ETHTRCV - no wakeup transceiver found
 *  \return         other values - index of the transceiver within the physical layer elements of the EthIf controller
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_EthTrcvIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupTransceiver(
  EthIf_EthIfCtrlIterType ethIfCtrlIdx);

#endif /* ETHIF_WAKEUP_SUPPORT */

#if( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_Internal_GetTrcvSignalQuality
 *********************************************************************************************************************/
/*! \brief          Prepare and get the signal quality of the transceiver
 *  \details        Function checks the link state and of the transceiver and forward the call to the function,
 *                  which will get the actual signal quality and update the list of the measured values.
 *                  Reentrant for different trcvIdx. Non reentrant for the same trcvIdx.
 *  \param[in]      trcvIdx Index of the transceiver within the context of the Ethernet Interface
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Internal_GetTrcvSignalQuality(
  EthIf_EthTrcvIterType trcvIdx);
/**********************************************************************************************************************
 *  EthIf_Update_TrcvSignalQualityList
 *********************************************************************************************************************/
/*! \brief          Get the actual signal quality and update the list of the measured signal quality values of the
 *                  transceiver
 *  \details        Function get the actual signal quality and updates the list of the measured signal qualities
 *                  values of the transceivers. The highest and lowest signal quality are updated depend on current
 *                  signal quality.
 *                  Reentrant for different trcvIdx. Non reentrant for the same trcvIdx.
 *  \param[in]      trcvIdx           Index of the transceiver within the context of the Ethernet Interface
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Update_TrcvSignalQualityList(
  EthIf_EthTrcvIterType trcvIdx);

/**********************************************************************************************************************
 *  EthIf_Reset_TrcvSignalQualityList
 *********************************************************************************************************************/
/*! \brief          Reset the signal quality of the transceiver
 *  \details        Function reset the signal quality of the transceiver which stored in a list in
 *                  Ethernet interface. The highest signal quality will be set to 0. The current signal quality will
 *                  be set to 0xFFFFFFFF.
 *                  Reentrant for different trcvIdx. Non reentrant for the same trcvIdx.
 *  \param[in]      trcvIdx           Index of the transceiver within the context of the Ethernet Interface
 *  \pre            -
 *  \context        TASK
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_Reset_TrcvSignalQualityList(
  EthIf_EthTrcvIterType trcvIdx);
#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 *  EthIf_QueryForWakeupMap
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_WakeupMapIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupMap(
  EcuM_WakeupSourceType wakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_WakeupMapIterType  queriedWakeupMapIdx;
  EthIf_WakeupMapIterType  wakeupMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedWakeupMapIdx = EthIf_GetSizeOfWakeupMap();

  /* #10 For each wakeup map */
  for( wakeupMapIdx = 0;
       wakeupMapIdx < EthIf_GetSizeOfWakeupMap();
       wakeupMapIdx++ )
  {
    /* #100 Check if wakeup source queried for matches the one of the map */
    if( wakeupSource == EthIf_GetWakeupSourceOfWakeupMap(wakeupMapIdx) )
    {
      /* #1000 Wakeup source matched -> wakeup map found */
      queriedWakeupMapIdx = wakeupMapIdx;
      break;
    }
  }

  return queriedWakeupMapIdx;
} /* EthIf_QueryForWakeupMap() */

/**********************************************************************************************************************
 *  EthIf_QueryForWakeupTransceiver
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(EthIf_EthTrcvIterType, ETHIF_ETHTRCV_INLINE_CODE) EthIf_QueryForWakeupTransceiver(
    EthIf_EthIfCtrlIterType ethIfCtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthTrcvIterType queriedWakeupEthTrcvIdx;
  EthIf_PhysLayerInitElemsIdxOfEthIfCtrlType physLayerInitElemsIdx;

  /* ----- Implementation ----------------------------------------------- */
  queriedWakeupEthTrcvIdx = ETHIF_INVALID_WAKEUP_ETHTRCV;
  physLayerInitElemsIdx   = EthIf_GetPhysLayerInitElemsIdxOfEthIfCtrl(ethIfCtrlIdx);

  /* #10 Check if EthTrcv is mapped to EthIf controller */
  if( EthIf_IsEthTrcvUsedOfPhysLayerInitElems(physLayerInitElemsIdx) == TRUE )
  {
    queriedWakeupEthTrcvIdx = EthIf_GetEthTrcvIdxOfPhysLayerInitElems(physLayerInitElemsIdx);
  }

  return queriedWakeupEthTrcvIdx;
} /* EthIf_QueryForWakeupTransceiver() */

#endif /* ETHIF_WAKEUP_SUPPORT */

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
 *  EthIf_Internal_GetTrcvSignalQuality
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Internal_GetTrcvSignalQuality(
  EthIf_EthTrcvIterType trcvIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  EthTrcv_LinkStateType linkState;

  EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(trcvIdx);

  /* #10 If the transceiver is in state ACTIVE */
  if( EthIf_GetEthTrcvModeCnt(trcvIdx) > 0U )
  {
    if( EthIf_GetGetLinkStateOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #1000 Get the link state of the port of the transceiver */
      if( EthIf_GetGetLinkStateOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(trcvIdx),                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
                                                                 &linkState) == E_OK )
      {
        /* #10000 If the link state is in state ACTIVE */
        if( linkState == ETHTRCV_LINK_STATE_ACTIVE )
        {
          retVal = EthIf_Update_TrcvSignalQualityList(trcvIdx);
        }
      }
    }
  }

  return retVal;
} /* EthIf_Internal_GetTrcvSignalQuality */

/**********************************************************************************************************************
 *  EthIf_Update_TrcvSignalQualityList
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
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_LINK_INLINE_CODE) EthIf_Update_TrcvSignalQualityList(
  EthIf_EthTrcvIterType trcvIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint8 actualSignalQuality = 0U;
  uint8 errorId = ETHIF_E_NO_ERROR;

  EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(trcvIdx);

  if (EthIf_GetGetPhySignalQualityOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR)
  {

    /* #100 Get the actual signal quality of the transceiver */
    if (EthIf_GetGetPhySignalQualityOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(trcvIdx),            /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03  */
                                                                       &actualSignalQuality) == E_OK)
    {
      /* #1000 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
      EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      /* #1010 Update the actual transceiver signal quality, which is stored in Ethernet Interface */
      EthIf_GetSignalQualityResult(trcvIdx).ActualSignalQuality = (uint32)actualSignalQuality;                          /* SBSW_ETHIF_INT_FCT_IDX_PASS */

      /* #1020 Update the maximal transceiver signal quality, which is stored in Ethernet Interface */
      if ((uint32)actualSignalQuality > EthIf_GetSignalQualityResult(trcvIdx).HighestSignalQuality)
      {
          EthIf_GetSignalQualityResult(trcvIdx).HighestSignalQuality = (uint32)actualSignalQuality;                     /* SBSW_ETHIF_INT_FCT_IDX_PASS */
      }
      /* #1030 Update the minimal transceiver signal quality, which is stored in Ethernet Interface */
      if ((uint32)actualSignalQuality < EthIf_GetSignalQualityResult(trcvIdx).LowestSignalQuality)
      {
          EthIf_GetSignalQualityResult(trcvIdx).LowestSignalQuality = (uint32)actualSignalQuality;                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */
      }

      /* #1040 Leave exclusive area -> processing on elements finished */
      EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      retVal = E_OK;
    }
  }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
  else
  {
    errorId = ETHIF_E_INV_DRIVER_API_CALL;
  }
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #20 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_Update_TrcvSignalQualityList */

/**********************************************************************************************************************
 *  EthIf_Reset_TrcvSignalQualityList
 *********************************************************************************************************************/
/*!
 *Internal comment removed.
 *
 *
 *
 *
 * */
ETHIF_ETHTRCV_LOCAL_INLINE FUNC(void, ETHIF_LINK_INLINE_CODE) EthIf_Reset_TrcvSignalQualityList(
  EthIf_EthTrcvIterType trcvIdx)
{
  /* #10 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
  EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Initialization of the signal quality of the transceiver*/
  EthIf_GetSignalQualityResult(trcvIdx).ActualSignalQuality = 0U;                                                       /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_GetSignalQualityResult(trcvIdx).HighestSignalQuality = 0U;                                                      /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  EthIf_GetSignalQualityResult(trcvIdx).LowestSignalQuality = LOWEST_SIGNAL_QUALITY_INIT;                               /* SBSW_ETHIF_INT_FCT_IDX_PASS */

  /* #30 Leave exclusive area -> processing on elements finished */
  EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* EthIf_Reset_TrcvSignalQualityList */
#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetTransceiverWakeupMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetTransceiverWakeupMode(
  EcuM_WakeupSourceType   WakeupSource,
  EthTrcv_WakeupModeType  WakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal       = E_NOT_OK;
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393861 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393862 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( (WakeupMode != ETHTRCV_WUM_DISABLE) &&
           (WakeupMode != ETHTRCV_WUM_ENABLE)  &&
           (WakeupMode != ETHTRCV_WUM_CLEAR)      )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393949 */
      retVal = EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                           WakeupMode);                                 /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_SetTransceiverWakeupMode() */

/**********************************************************************************************************************
 * EthIf_GetTransceiverWakeupMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTransceiverWakeupMode(
        EcuM_WakeupSourceType                               WakeupSource,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType          retVal       = E_NOT_OK;
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393864 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393865 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( WakeupModePtr == NULL_PTR )
  {
    /* \trace SPEC-2393866 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393951 */
      retVal = EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                           WakeupModePtr);                              /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetTransceiverWakeupMode() */

/**********************************************************************************************************************
 * EthIf_CheckWakeup
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_CheckWakeup(
  EcuM_WakeupSourceType  WakeupSource)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8                   errorId      = ETHIF_E_NO_ERROR;
  EthIf_WakeupMapIterType wakeupMapIdx = EthIf_QueryForWakeupMap(WakeupSource);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393869 */
    /* \trace SPEC-2393872 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( wakeupMapIdx >= EthIf_GetSizeOfWakeupMap() )
  {
    /* \trace SPEC-2393870 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIdxOfWakeupMapType ethTrcvIdx = EthIf_GetEthTrcvIdxOfWakeupMap(wakeupMapIdx);
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      /* \trace SPEC-2393952 */
      (void)EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx));            /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CHECK_WAKEUP, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

} /* EthIf_CheckWakeup() */

/**********************************************************************************************************************
 * EthIf_VSetTransceiverWakeupMode
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VSetTransceiverWakeupMode(
  uint8                   CtrlIdx,
  EthTrcv_WakeupModeType  WakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( (WakeupMode != ETHTRCV_WUM_DISABLE) &&
           (WakeupMode != ETHTRCV_WUM_ENABLE)  &&
           (WakeupMode != ETHTRCV_WUM_CLEAR)      )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx = EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);
      /* #300 Check if driver provides the API */
      if( EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        retVal = EthIf_GetSetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                             WakeupMode);                               /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_VSetTransceiverWakeupMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_VGetTransceiverWakeupMode
 **********************************************************************************************************************/
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VGetTransceiverWakeupMode(
        uint8                                               CtrlIdx,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( WakeupModePtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx =  EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #300 Check if driver provides the API */
      if( EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        retVal = EthIf_GetGetTrcvWakeupModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx),
                                                                             WakeupModePtr);                            /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_VGetTransceiverWakeupMode() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * EthIf_VCheckWakeup
 **********************************************************************************************************************/
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
FUNC(void, ETHIF_CODE) EthIf_VCheckWakeup(
  uint8  CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvIterType ethTrcvIdx =  EthIf_QueryForWakeupTransceiver(CtrlIdx);

    /* #30 Check if wakeup transceiver for EthIf controller exists */
    if( ethTrcvIdx != ETHIF_INVALID_WAKEUP_ETHTRCV )
    {
      EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(ethTrcvIdx);

      /* #300 Check if driver provides the API */
      if( EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
      {
        /* #3000 Redirect call to the driver */
        (void)EthIf_GetCheckWakeupOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(ethTrcvIdx));          /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_PARAM;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CHECK_WAKEUP, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

} /* EthIf_VCheckWakeup() */

#endif /* ETHIF_WAKEUP_SUPPORT */

/**********************************************************************************************************************
 * EthIf_SetPhyTxMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetPhyTxMode(
  uint8                  TrcvIdx,
  EthTrcv_PhyTxModeType  Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( TrcvIdx >= EthIf_GetSizeOfEthTrcvDrvApi() )
  {
    errorId = ETHIF_E_INV_TRCV_IDX;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(TrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetSetPhyTxModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetSetPhyTxModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(TrcvIdx),
                                                                      Mode);                                           /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
#if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
#endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_PHY_TX_MODE, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_SetPhyTxMode() */

/**********************************************************************************************************************
 * EthIf_GetCableDiagnosticsResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetCableDiagnosticsResult (
        uint8                                                    TrcvIdx,
  P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHIF_APPL_VAR)  ResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( TrcvIdx >= EthIf_GetSizeOfEthTrcvDrvApi() )
  {
    errorId = ETHIF_E_INV_TRCV_IDX;
  }
  else if( ResultPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(TrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetGetCableDiagnosticsResultOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetGetCableDiagnosticsResultOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)
                                                                                   EthIf_GetSnvOfEthTrcv(TrcvIdx),
                                                                                   ResultPtr);                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
#if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
#endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_CABLE_DIAGNOSTICS_RESULT, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_GetCableDiagnosticsResult() */

/**********************************************************************************************************************
 * EthIf_SetPhyTestMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetPhyTestMode(
  uint8                    TrcvIdx,
  EthTrcv_PhyTestModeType  Mode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal  = E_NOT_OK;
  uint8          errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( TrcvIdx >= EthIf_GetSizeOfEthTrcvDrvApi() )
  {
    errorId = ETHIF_E_INV_TRCV_IDX;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthTrcvDrvApiIdxOfEthTrcvType ethTrcvDrvApiIdx = EthIf_GetEthTrcvDrvApiIdxOfEthTrcv(TrcvIdx);

    /* #30 Check if driver provides the API */
    if( EthIf_GetSetPhyTestModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx) != NULL_PTR )
    {
      /* #300 Redirect call to the driver */
      retVal = EthIf_GetSetPhyTestModeOfEthTrcvDrvApi(ethTrcvDrvApiIdx)((uint8)EthIf_GetSnvOfEthTrcv(TrcvIdx),
                                                                        Mode);                                         /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_CSL03 */
    }
#if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_SAFE_FEAT */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
#endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_SET_PHY_TEST_MODE, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_SetPhyTestMode() */

#if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
*  EthIf_GetTrcvSignalQuality
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTrcvSignalQuality(
        uint8 TrcvIdx,
  P2VAR(EthIf_SignalQualityResultType, AUTOMATIC, ETHIF_APPL_VAR) ResultPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId  = ETHIF_E_NO_ERROR;

# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( TrcvIdx >= EthIf_GetSizeOfEthTrcv() )
  {
    errorId = ETHIF_E_INV_TRCV_IDX;
  }
  else if ( ResultPtr == NULL_PTR )
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */

  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Get the signal quality of the transceiver*/
    retVal = EthIf_Internal_GetTrcvSignalQuality(TrcvIdx);

    /* #40 Enter exclusive area (Reason: Ensure consistency of signal quality statistics) */
    EthIf_EnterExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #50 Prepare signal quality return values */
    if (retVal == E_OK)
    {
       ResultPtr->ActualSignalQuality  = EthIf_GetSignalQualityResult(TrcvIdx).ActualSignalQuality;                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
       ResultPtr->HighestSignalQuality = EthIf_GetSignalQualityResult(TrcvIdx).HighestSignalQuality;                        /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
       ResultPtr->LowestSignalQuality  = EthIf_GetSignalQualityResult(TrcvIdx).LowestSignalQuality;                         /* SBSW_ETHIF_PUB_FCT_PARAM_PTR_WRITE */
    } else {
      EthIf_Reset_TrcvSignalQualityList(TrcvIdx);
    }

    /* #60 Leave exclusive area -> processing on elements finished */
    EthIf_ExitExclusiveArea(SIGNAL_QUALITY); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #70 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_GET_TRANSCEIVER_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_GetTrcvSignalQuality() */

/**********************************************************************************************************************
*  EthIf_ClearTrcvSignalQuality
*********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ClearTrcvSignalQuality(
  uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId  = ETHIF_E_NO_ERROR;

# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
# endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( TrcvIdx >= EthIf_GetSizeOfEthTrcv() )
  {
    errorId = ETHIF_E_INV_TRCV_IDX;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Clear the signal quality of the transceiver*/
    EthIf_Reset_TrcvSignalQualityList(TrcvIdx);
    retVal = E_OK;
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_CLEAR_TRANSCEIVER_SIGNAL_QUALITY, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_ClearTrcvSignalQuality() */

/**********************************************************************************************************************
 *  EthIf_PollTrcvSignalQualities
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_PollTrcvSignalQualities( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthTrcvIterType ethTrcvIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each transceiver */
  for( ethTrcvIdx = 0U;
       ethTrcvIdx < EthIf_GetSizeOfEthTrcv();
       ethTrcvIdx++ )
  {
    /* #100 Get the transceiver signal quality and store it in Ethernet interface*/
    if (EthIf_Internal_GetTrcvSignalQuality(ethTrcvIdx) == E_NOT_OK)
    {
      /* #1000 If it fails, clear the signal quality*/
      EthIf_Reset_TrcvSignalQualityList(ethTrcvIdx);
    }
  }
} /* EthIf_PollTrcvSignalQualities */

/**********************************************************************************************************************
 *  EthIf_TrcvSignalQualityList_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_TrcvSignalQualityList_Init( void )
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthTrcvIterType ethTrcvIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 For each transceiver */
  for( ethTrcvIdx = 0U;
       ethTrcvIdx < EthIf_GetSizeOfEthTrcv();
       ethTrcvIdx++ )
  {
    /* #100 Initialization of the signal quality of all the transceivers*/
    EthIf_Reset_TrcvSignalQualityList(ethTrcvIdx);
  }
} /* EthIf_TrcvSignalQualityList_Init */
#endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthTrcv.c
 *********************************************************************************************************************/

