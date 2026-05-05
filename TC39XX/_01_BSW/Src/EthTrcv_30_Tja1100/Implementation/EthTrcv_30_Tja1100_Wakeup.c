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
/*         \file  EthTrcv_30_Tja1100_Wakeup.c
 *        \brief  Source file containing the core implementation of the Ethernet transceiver driver's Wakeup related
 *                part
 *
 *      \details  The file EthTrcv_30_Tja1100_Wakeup.c is the source file which contains the hardware independent parts
 *                of the implementation of the Ethernet transceiver driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK in the module's header file
 *********************************************************************************************************************/
#define ETHTRCV_30_TJA1100_WAKEUP_SOURCE
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTrcv_30_Tja1100.h"
#include "EthTrcv_30_Tja1100_Wakeup_Int.h"
#include "EthTrcv_30_Tja1100_Wakeup_UsrIfc.h"
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of the configuration header file */
#if (  (ETHTRCV_30_TJA1100_CFG_MAJOR_VERSION != (4u)) \
    || (ETHTRCV_30_TJA1100_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTrcv_30_Tja1100_Wakeup.c and EthTrcv_30_Tja1100_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined(ETHTRCV_30_TJA1100_WU_LOCAL)                                                                               /* COV_ETHTRCV_COMPATIBILITY */
# define ETHTRCV_30_TJA1100_WU_LOCAL                                  static
#endif

#if !defined(ETHTRCV_30_TJA1100_WU_LOCAL_INLINE)                                                                        /* COV_ETHTRCV_COMPATIBILITY */
# define ETHTRCV_30_TJA1100_WU_LOCAL_INLINE                           LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define ETHTRCV_30_TJA1100_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode
 *********************************************************************************************************************/
/*! \brief       Enable/disable transceiver wakeup or clear wakeup reason
 *  \details     This function allows to enable or disable the transceiver's wakeup feature or to clear any occurred
 *               wakeup reason.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver
 *  \param[in]   TrcvWakeupMode  Operation that shall be performed:
 *                               ETHTRCV_WUM_DISABLE - disable the transceiver wakeup
 *                               ETHTRCV_WUM_ENABLE - enable the transceiver wakeup
 *                               ETHTRCV_WUM_CLEAR - clear wakeup reason
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode(
    uint8 TrcvIdx,
    EthTrcv_WakeupModeType TrcvWakeupMode);

# if(ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode
 *********************************************************************************************************************/
/*! \brief       Gets the current wake-up mode
 *  \details     This function allows to retrieve if the transceiver wake-up is enabled or disabled.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver
 *  \param[out]  TrcvWakeupMode  Wakeup mode the transceiver is currently set to:
 *                               ETHTRCV_WUM_DISABLE - Transceiver wake-up disabled
 *                               ETHTRCV_WUM_ENABLE - Transceiver wake-up enabled
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvWakeupModePtr);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_CheckWakeup
 *********************************************************************************************************************/
/*! \brief       Performs a wake-up check.
 *  \details     This function performs a check of the transceiver's wake-up function.
 *  \param[in]   TrcvIdx    Zero based index of the transceiver
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_CheckWakeup(
          uint8  TrcvIdx);
/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode
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
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode(
    uint8 TrcvIdx,
    EthTrcv_WakeupModeType TrcvWakeupMode)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check the parameter TrcvWakeupMode */
  switch( TrcvWakeupMode )
  {
    /* #20 In case TrcvWakeupMode is ETHTRCV_WUM_DISABLE or ETHTRCV_WUM_ENABLE */
    case ETHTRCV_WUM_DISABLE:

    case ETHTRCV_WUM_ENABLE:
      /* #210 Set the global wakeup mode variable to ETHTRCV_WUM_DISABLE or ETHTRCV_WUM_ENABLE */
      EthTrcv_30_Tja1100_SetWakeupMode(TrcvIdx, TrcvWakeupMode);                                                        /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      retVal = E_OK;
      /* #220 Leave the function */
      break;
    /* #30 In case TrcvWakeupMode is ETHTRCV_WUM_CLEAR */
    case ETHTRCV_WUM_CLEAR:
      /* #310 Clear all wakeup reasons */
      EthTrcv_30_Tja1100_ClearWakeupReasons(TrcvIdx);
      retVal = E_OK;
      /* #320 Leave the function */
      break;
      /* #40 In case TrcvWakeupMode is unsupported */
    default:
      /* #410 Return E_NOT_OK */
      break;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode() */

# if(ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvWakeupModePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Report the content of the global wakeup mode variable */
  *TrcvWakeupModePtr = EthTrcv_30_Tja1100_GetWakeupMode(TrcvIdx);                                                       /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  retVal = E_OK;

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode() */
#endif  /* ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_CheckWakeup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_WU_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_CheckWakeup(
  uint8  TrcvIdx)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The global wake-up mode variable is ETHTRCV_WUM_ENABLE */
  if( EthTrcv_30_Tja1100_GetWakeupMode(TrcvIdx) == ETHTRCV_WUM_ENABLE )
  {
    /* #110 Check for wake-up events and handle them */
    retVal = EthTrcv_30_Tja1100_InspectWakeupReasons(TrcvIdx);
    if( retVal == E_OK )
    {
      EthTrcv_30_Tja1100_ReportWakeup(TrcvIdx);
    }
  }
  /* #20 The global wake-up variable is ETHTRCV_WUM_DISABLE */
  else
  {
    /* #210 Leave the function */
    retVal = E_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_CheckWakeup() */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_InspectWakeupReasons()
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
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_InspectWakeupReasons(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{

  Std_ReturnType retVal = E_NOT_OK;
  EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType wakeupIdx = EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(TrcvIdx);

  /* #10 The wake-up inspection is performed with an ICU channel */
  if(EthTrcv_30_Tja1100_GetWakeupInspectionTypeOfWakeup(wakeupIdx) == ETHTRCV_30_TJA1100_ICU_CHANNEL_WAKEUPINSPECTIONTYPEOFWAKEUP)
  {
    /* #110 The configured ICU channel returns the input state ACTIVE */
    if(Icu_GetInputState(EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(wakeupIdx)) == ICU_ACTIVE)
    {
      /* #1110 Set the wake-up reason to PIN */
      EthTrcv_30_Tja1100_SetWakeupReasonToPin(TrcvIdx);
    }
    /* #120 Return that the request completed successfully */
    retVal = E_OK;
  }
  /* #20 The wake-up inspection is performed with user code */
  else if( EthTrcv_30_Tja1100_GetWakeupInspectionTypeOfWakeup(wakeupIdx) == ETHTRCV_30_TJA1100_USER_CODE_WAKEUPINSPECTIONTYPEOFWAKEUP )
  {
    EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType verifyIdx = EthTrcv_30_Tja1100_GetWakeupVerificationCalloutIdxOfWakeup(wakeupIdx);
    /* #210 Call the interface to the user code which performs the wake-up inspection */
    if( EthTrcv_30_Tja1100_GetWakeupVerificationCallout(verifyIdx) != NULL_PTR )
    {
      EthTrcv_30_Tja1100_GetWakeupVerificationCallout(verifyIdx)((uint8)TrcvIdx);                                       /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL03 */
      retVal = E_OK;
    }
  }
  /* #30 The wake-up inspection is not performed with an ICU channel or with user-code */
  else
  {
    /* #310 Return that this inspection type is not supported */
  }
  return retVal;
} /* EthTrcv_30_Tja1100_InspectWakeupReasons() */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReportWakeup()
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
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReportWakeup(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupMapIterType loopIdx;
  EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType wakeupIdx = EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(TrcvIdx);

  /* #10 Loop over all possible wake-up reasons */
  for( loopIdx = 0; loopIdx < ETHTRCV_WUR_NUM; loopIdx++ )
  {
    EthTrcv_30_Tja1100_WakeupReasonFlagsType reasonMask;

    /* #110 For each wake-up reason prepare a bit mask to check if it is set */
    reasonMask = (EthTrcv_30_Tja1100_WakeupReasonFlagsType)(0x01U << loopIdx);

    /* #120 The AUTOSAR wakeup reason is set */
    if((reasonMask & EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx)) != 0U )
    {
      EthTrcv_30_Tja1100_WakeupMapIterType innerLoopIdx;
      EthTrcv_30_Tja1100_WakeupReasonFlagsIterType wakeupReason;

      /* #1210 Loop over all AUTOSAR wake-up reasons, which are calculated by incrementing the loop variable */
      wakeupReason = loopIdx + 1U;

      for( innerLoopIdx = EthTrcv_30_Tja1100_GetWakeupMapStartIdxOfWakeup(wakeupIdx);
           innerLoopIdx < EthTrcv_30_Tja1100_GetWakeupMapEndIdxOfWakeup(wakeupIdx);
           innerLoopIdx++ )
      {
        /* #12110 A mapping exists to the corresponding EcuM wake-up source */
        if( wakeupReason == EthTrcv_30_Tja1100_GetWakeupReasonOfWakeupMap(innerLoopIdx) )
        {
          uint32 wakeupEventMask;
          /* #121110 Calculate the corresponding EcuM bit-mask */
          wakeupEventMask = (uint32)(1U << EthTrcv_30_Tja1100_GetEcuMWakeupSourceOfWakeupMap(innerLoopIdx));
          /* #121120 inform EcuM about the detected wake-up event */
          EcuM_SetWakeupEvent(wakeupEventMask);
        }
      }
    }
  }
  /* #20 Clear wake-up reasons after they have been reported to the EcuM */
  EthTrcv_30_Tja1100_ClearWakeupReasons(TrcvIdx);
} /* EthTrcv_30_Tja1100_ReportWakeup() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToGeneral()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToGeneral(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_GENERAL_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a general wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToBus()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToBus(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_BUS_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a bus related wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToInternal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToInternal(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_INTERNAL_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a internal wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToReset(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_RESET_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a reset as wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToPowerOn()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToPowerOn(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_POWER_ON_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a power on as wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToPin()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToPin(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_PIN_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a pin voltage transition as wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_SetWakeupReasonToSysErr()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonToSysErr(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_WakeupReasonFlagsType flags = EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx);

  flags |= (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_SYSERR_FLAGS_MASK;
  /* #10 Set the wake-up reason flag corresponding to a system error as wake-up reason */
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, flags);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_IsWakeupReasonPending()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupReasonPending(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  boolean result = FALSE;

  /* #10 A wake-up reason is pending */
  if(EthTrcv_30_Tja1100_GetWakeupReasonFlags(TrcvIdx) != ETHTRCV_WUR_CLEAR_MASK)
  {
    /* #110 Report that a wake-up reason is pending */
    result = TRUE;
  }
  return result;
}

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ClearWakeupReasons()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ClearWakeupReasons(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx)
{
  EthTrcv_30_Tja1100_SetWakeupReasonFlags(TrcvIdx, (EthTrcv_30_Tja1100_WakeupReasonFlagsType)ETHTRCV_WUR_CLEAR_MASK);   /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetTransceiverWakeupMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTransceiverWakeupMode(
    uint8 TrcvIdx,
    EthTrcv_WakeupModeType TrcvWakeupMode)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if((TrcvWakeupMode != ETHTRCV_WUM_DISABLE) &&
          (TrcvWakeupMode != ETHTRCV_WUM_ENABLE) &&
          (TrcvWakeupMode != ETHTRCV_WUM_CLEAR))
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_PARAM;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call internal SetTransceiverWakeupMode */
    retVal = EthTrcv_30_Tja1100_Internal_SetTransceiverWakeupMode(TrcvIdx, TrcvWakeupMode);
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_SET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_SetTransceiverWakeupMode() */

# if(ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetTransceiverWakeupMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTransceiverWakeupMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvWakeupModePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvWakeupModePtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call internal GetTransceiverWakeupMode */
    retVal = EthTrcv_30_Tja1100_Internal_GetTransceiverWakeupMode(TrcvIdx, TrcvWakeupModePtr);                          /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_TRANSCEIVER_WAKEUP_MODE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetTransceiverWakeupMode() */
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_CheckWakeup
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_CheckWakeup(
  uint8  TrcvIdx)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call internal CheckWakeup */
    retVal = EthTrcv_30_Tja1100_Internal_CheckWakeup(TrcvIdx);
  }

# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_CHECK_WAKEUP, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_CheckWakeup() */
#endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Wakeup.c
 *********************************************************************************************************************/
