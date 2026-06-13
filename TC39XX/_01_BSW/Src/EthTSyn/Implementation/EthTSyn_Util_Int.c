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
/*!        \file  EthTSyn_Util_Int.c
 *        \brief  EthTSyn Util source file - Internal Functions
 *      \details  EthTSyn Util source file containing the implementation of utilities used by different Sub-Modules of
 *                of the EthTSyn
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

#define ETHTSYN_UTIL_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTSyn_Util_Int.h" /* PRQA S 3219, 0883 */ /* MD_EthTSyn_3219, MD_EthTSyn_0883 */
#include "EthTSyn_Int.h" /* PRQA S 3219 */ /* MD_EthTSyn_3219 */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of EthTSyn header file */
#if (  (ETHTSYN_SW_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_SW_MINOR_VERSION != (2u)) \
    || (ETHTSYN_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthTSyn_Util_Int.c and EthTSyn.h are inconsistent"
#endif

/* Check the version of the configuration header file */
#if (  (ETHTSYN_CFG_MAJOR_VERSION != (13u)) \
    || (ETHTSYN_CFG_MINOR_VERSION != (2u)) )
# error "Version numbers of EthTSyn_Util_Int.c and EthTSyn_Cfg.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
/* 48 bit seconds */
#define ETHTSYN_TIMESTAMP_MAX_SECONDS                                 (0xFFFFFFFFFFFFLL)
/* 10^9 nanoseconds per second */
#define ETHTSYN_TIMESTAMP_MAX_NANOSECONDS                             (1000000000uL)
/* 63 bit max timediff in nanoseconds */
#define ETHTSYN_TIMEDIFF_MAX_NANOSECONDS                              (0x7FFFFFFFFFFFFFFFLL)
#define ETHTSYN_TIMEDIFF_MAX_SECONDS                                  (ETHTSYN_TIMEDIFF_MAX_NANOSECONDS /\
                                                                      (EthTSyn_TimediffType)\
                                                                      ETHTSYN_TIMESTAMP_MAX_NANOSECONDS)

/* Virtual Local Time MACROS */
#define ETHTSYN_VLT_NS_HIGH_MASK                                      (0xFFFFFFFF00000000uLL)
#define ETHTSYN_VLT_NS_HIGH_SHIFT                                     (32u)
#define ETHTSYN_VLT_NS_LOW_MASK                                       (0x00000000FFFFFFFFuLL)
#define ETHTSYN_VLT_NS_LOW_SHIFT                                      (0u)

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define ETHTSYN_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck
 *********************************************************************************************************************/
/*! \brief      Gets the expected message length and verifies the message type of the passed message.
 *  \details    -
 *  \param[in]  MsgPtr                        Pointer to the message to be checked
 *  \param[out] ExpectedLengthPtr             The expected message length
 *  \param[out] IsExpectedLengthMinLengthPtr  TRUE:  The expected message length is just the minimal length
 *                                            FALSE: The expected message length has to match exactly
 *  \return     ETHTSYN_E_NO_ERROR - Message type valid and expected length successfully retrieved. Out parameter valid.
 *  \return     other value - Message type invalid or failed to retrieve expected length. Out parameter invalid.
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(
  ETHTSYN_P2CONST(uint8)    MsgPtr,
    ETHTSYN_P2VAR(uint16)   ExpectedLengthPtr,
    ETHTSYN_P2VAR(boolean)  IsExpectedLengthMinLengthPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_AddTimediffToTimestamp
 *********************************************************************************************************************/
/*! \brief         Adds the passed time difference to the provided timestamp.
 *  \details       -
 *  \param[in]     TimeDiffNs     The time difference in nanoseconds
 *  \param[in,out] TimestampPtr   In:   The timestamp to be incremented by the given time difference
 *                                Out:  The given Timestamp + the given time difference
 *  \return        E_OK - Successfully added the time difference to the timestamp
 *  \return        E_NOT_OK - Failed to added the time difference to the timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Timestamps
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_AddTimediffToTimestamp(
                  uint64                          TimeDiffNs,
    ETHTSYN_P2VAR(EthTSyn_InternalTimestampType)  TimestampPtr);

/**********************************************************************************************************************
 *  EthTSyn_Util_SubtractTimediffFromTimestamp
 *********************************************************************************************************************/
/*! \brief         Subtracts the passed time difference from the provided timestamp.
 *  \details       -
 *  \param[in]     TimeDiffNs     The time difference in nanoseconds
 *  \param[in,out] TimestampPtr   In:   The timestamp to be decremented by the given time difference
 *                                Out:  The given Timestamp - the given time difference
 *  \return        E_OK - Successfully subtracted the time difference from the timestamp
 *                 E_NOT_OK - Failed to subtract the time difference from the timestamp
 *  \pre           -
 *  \context       TASK|ISR2
 *  \reentrant     TRUE for different Timestamps
 *********************************************************************************************************************/
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_SubtractTimediffFromTimestamp(
                  uint64                          TimeDiffNs,
    ETHTSYN_P2VAR(EthTSyn_InternalTimestampType)  TimestampPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
  *  EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck
  *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
 ETHTSYN_LOCAL_INLINE FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(
   ETHTSYN_P2CONST(uint8)   MsgPtr,
    ETHTSYN_P2VAR(uint16)   ExpectedLengthPtr,
    ETHTSYN_P2VAR(boolean)  IsExpectedLengthMinLengthPtr)
{
   /* ----- Local Variables ---------------------------------------------- */
   uint8 errorId = ETHTSYN_E_NO_ERROR;

   /* ----- Implementation ----------------------------------------------- */
   (*ExpectedLengthPtr) = 0;                                                                                           /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
   (*IsExpectedLengthMinLengthPtr) = FALSE;                                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

   /* #10 Check the message type. */
   /* Shift of ETHTSYN_MSG_HDR_MSG_TYPE_SHIFT is not required because it is 0. */
   switch(IpBase_GetUint8(MsgPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS) & ETHTSYN_MSG_HDR_MSG_TYPE_MASK)                       /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
   {
   /* #100 Set the expected length for valid message types. */
   case ETHTSYN_MSG_TYPE_SYNC:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_SYNC_LENGTH;                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   case ETHTSYN_MSG_TYPE_FOLLOW_UP:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_FOLLOW_UP_RX_MIN_LENGTH;                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       (*IsExpectedLengthMinLengthPtr) = TRUE;                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_REQ:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_RESP:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   case ETHTSYN_MSG_TYPE_ANNOUNCE:
     {
       (*ExpectedLengthPtr) = ETHTSYN_MSG_ANNOUNCE_LENGTH;                                                             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       (*IsExpectedLengthMinLengthPtr) = TRUE;                                                                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
       break;
     }

   default:
     {
       /* #101 Invalid message type. Set errorId. */
       errorId = ETHTSYN_E_MSG_TYPE;
       break;
     }
   }

   return errorId;
} /* EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck() */

/**********************************************************************************************************************
 *  EthTSyn_Util_AddTimediffToTimestamp
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_AddTimediffToTimestamp(
                uint64                         TimeDiffNs,
  ETHTSYN_P2VAR(EthTSyn_InternalTimestampType) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_UTimediffType DiffSeconds;
  uint32 DiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  DiffSeconds = (EthTSyn_UTimediffType)(TimeDiffNs / ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);
  DiffNanoseconds = (uint32)(TimeDiffNs % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);

  /* #10 Overflow check of rounded up seconds -> Check nanoseconds overflow not required */
  if((EthTSyn_UTimediffType)((TimestampPtr->seconds + 1u) + DiffSeconds) <=
      ((EthTSyn_UTimediffType)ETHTSYN_TIMESTAMP_MAX_SECONDS))
  {
    /* #20 Add nanoseconds of both summands */
    TimestampPtr->nanoseconds += (uint32)DiffNanoseconds;                                                              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    /* #30 Add seconds of overflow nanoseconds */
    TimestampPtr->seconds += (uint64)((uint64)TimestampPtr->nanoseconds / (uint64)ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);  /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    /* #40 Truncate overflow nanoseconds */
    TimestampPtr->nanoseconds = TimestampPtr->nanoseconds % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS;                         /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    /* #50 Add seconds */
    TimestampPtr->seconds += (EthTSyn_UTimediffType)DiffSeconds;                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    retVal = E_OK;
  }

  return retVal;
} /* EthTSyn_Util_AddTimediffToTimestamp() */

/**********************************************************************************************************************
 *  EthTSyn_Util_SubtractTimediffFromTimestamp
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
ETHTSYN_LOCAL_INLINE FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_SubtractTimediffFromTimestamp(
                uint64                         TimeDiffNs,
  ETHTSYN_P2VAR(EthTSyn_InternalTimestampType) TimestampPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_UTimediffType DiffSeconds;
  uint32 DiffNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  DiffSeconds = (EthTSyn_UTimediffType)(TimeDiffNs / ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);
  DiffNanoseconds = (uint32)(TimeDiffNs % ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);

  /* #10 Check that result is not negative. */
  if(DiffSeconds <= TimestampPtr->seconds)
  {
    /* #20 Check for Nanoseconds underflow. */
    if(DiffNanoseconds <= TimestampPtr->nanoseconds)
    {
      /* #200 Calculate timestamp and mark result as valid. */
      TimestampPtr->seconds -= DiffSeconds;                                                                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
      TimestampPtr->nanoseconds -= DiffNanoseconds;                                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

      retVal = E_OK;
    }
    else
    {
      /* #30 Handle Underflow. Destination seconds must be greater than difference seconds. */
      if(TimestampPtr->seconds > DiffSeconds)
      {
        /* #300 Calculate timestamp and mark result as valid. */
        TimestampPtr->seconds--;                                                                                       /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
        TimestampPtr->nanoseconds =
            (uint32)(((ETHTSYN_TIMESTAMP_MAX_NANOSECONDS + TimestampPtr->nanoseconds) - DiffNanoseconds));             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
        TimestampPtr->seconds -= DiffSeconds;                                                                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

        retVal = E_OK;
      }
    }
  }

  return retVal;
} /* EthTSyn_Util_SubtractTimediffFromTimestamp() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampPlusTimediff
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampPlusTimediff(
    ETHTSYN_P2VAR(EthTSyn_GlobalTimestampType) DestTimestampPtr,
  ETHTSYN_P2CONST(EthTSyn_TimediffType)        TimediffPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  EthTSyn_InternalTimestampType internalTimestamp;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert Global to internal Timestamp. */
  internalTimestamp.nanoseconds = DestTimestampPtr->nanoseconds;
  internalTimestamp.seconds     = DestTimestampPtr->seconds;
  internalTimestamp.seconds    |= ((uint64)DestTimestampPtr->secondsHi << 32u);

  /* #20 Check for positive value of time difference. */
  if((*TimediffPtr) > 0)
  {
    /* #200 Positive Timediff. Add Timediff to timestamp. */
    EthTSyn_UTimediffType TimediffU64Ns = (EthTSyn_UTimediffType)(*TimediffPtr);
    retVal = EthTSyn_Util_AddTimediffToTimestamp(TimediffU64Ns, &internalTimestamp);                                   /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  }
  else if((*TimediffPtr) < 0)
  {
    /* #201 Negative Timediff. Subtract Timediff from timestamp. */
    EthTSyn_UTimediffType TimediffU64Ns = (EthTSyn_UTimediffType)(-(*TimediffPtr));
    retVal = EthTSyn_Util_SubtractTimediffFromTimestamp(TimediffU64Ns, &internalTimestamp);                            /* SBSW_ETHTSYN_REFERENCE_OF_LOCAL_VARIABLE */
  }
  else
  {
    /* #202 Timediff is zero -> add nothing. */
    retVal = E_OK;
  }

  /* The seconds field of the internal timestamp has a value range from 0 - (2^48-1) */
  /* #30 Check if result is valid. */
  if(retVal == E_OK)
  {
    /* #300 Convert Internal to global Timestamp. */
    DestTimestampPtr->nanoseconds = internalTimestamp.nanoseconds;                                                     /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    DestTimestampPtr->seconds     = (uint32)internalTimestamp.seconds;                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
    DestTimestampPtr->secondsHi   = (uint16)(internalTimestamp.seconds >> 32u);                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  }

  return retVal;
} /* EthTSyn_Util_TimestampPlusTimediff() */

/**********************************************************************************************************************
 *  EthTSyn_Util_TimestampMinusTimestamp
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_Util_TimestampMinusTimestamp(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp1Ptr,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) Timestamp2Ptr,
    ETHTSYN_P2VAR(EthTSyn_TimediffType)        TimediffPtr)
 {
   /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  EthTSyn_TimediffType diffSeconds;
  EthTSyn_TimediffType diffNanoseconds;
  EthTSyn_UTimediffType diffSecondsU64;
  EthTSyn_InternalTimestampType internalTimestamp1;
  EthTSyn_InternalTimestampType internalTimestamp2;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert Global to internal Timestamp. */
  internalTimestamp1.nanoseconds = Timestamp1Ptr->nanoseconds;
  internalTimestamp1.seconds     = Timestamp1Ptr->seconds;
  internalTimestamp1.seconds    |= ((uint64)Timestamp1Ptr->secondsHi << 32u);

  internalTimestamp2.nanoseconds = Timestamp2Ptr->nanoseconds;
  internalTimestamp2.seconds     = Timestamp2Ptr->seconds;
  internalTimestamp2.seconds    |= ((uint64)Timestamp2Ptr->secondsHi << 32u);


  /* #20 Check if difference in seconds is suitable for nanoseconds difference value.
   * No overflow is expected due Seconds field of EthTSyn_TimestampType should not exceed 2^48. */
  diffSeconds = (EthTSyn_TimediffType)internalTimestamp1.seconds - (EthTSyn_TimediffType)internalTimestamp2.seconds;

  /* check if time difference is less zero */
  if(diffSeconds < 0)
  {
    diffSecondsU64 = (EthTSyn_UTimediffType)(-diffSeconds);
  }
  /* time difference is greater zero */
  else
  {
    diffSecondsU64 = (EthTSyn_UTimediffType)diffSeconds;
  }

  /* #30 Round up difference in seconds due to handle possible nanoseconds overflow in further calculation. */
  diffSecondsU64++;
  /* #40 Check if time difference in seconds is suitable for nanoseconds difference value. */
  if(diffSecondsU64 < (EthTSyn_UTimediffType)ETHTSYN_TIMEDIFF_MAX_SECONDS)
  {
    /* #50 Calculate time difference. */
    /* calculate correct nanoseconds time difference */
    diffNanoseconds = (EthTSyn_TimediffType)
      ((EthTSyn_TimediffType)internalTimestamp1.nanoseconds - (EthTSyn_TimediffType)internalTimestamp2.nanoseconds);

    /* set seconds value */
    (*TimediffPtr) = diffSeconds * ((EthTSyn_TimediffType)ETHTSYN_TIMESTAMP_MAX_NANOSECONDS);                          /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    /* add nanoseconds value */
    (*TimediffPtr) = (*TimediffPtr) + diffNanoseconds;                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */

    retVal = E_OK;
  }
  /* timediff value exceeds max nanoseconds value */
  else
  {
    (*TimediffPtr) = 0;                                                                                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM */
  }

  return retVal;
} /* EthTSyn_Util_TimestampMinusTimestamp() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_TsToIntVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_UtilVlt_TsToIntVlt(
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) TsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltType intVlt;
  uint64 tsSeconds;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert timestamp into internal virtual local time. */
  tsSeconds = (uint64)TsPtr->secondsHi << 32u;
  tsSeconds |= (uint64)TsPtr->seconds;

  intVlt = (tsSeconds * ETHTSYN_NANOSECONDS_PER_SECOND) + TsPtr->nanoseconds;

  return intVlt;
} /* EthTSyn_UtilVlt_TsToIntVlt() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltToTs
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_GlobalTimestampType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltToTs(
  EthTSyn_IntVltType IntVlt)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_GlobalTimestampType globalTs;
  uint64 vltSeconds;
  uint32 vltNanoseconds;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert internal virtual local time into timestamp. */
  vltSeconds = (uint64)(IntVlt / ETHTSYN_NANOSECONDS_PER_SECOND);
  vltNanoseconds = (uint32)(IntVlt % ETHTSYN_NANOSECONDS_PER_SECOND);

  globalTs.secondsHi = (uint16)(vltSeconds >> 32u);
  globalTs.seconds = (uint32)vltSeconds;
  globalTs.nanoseconds = vltNanoseconds;

  return globalTs;
} /* EthTSyn_UtilVlt_IntVltToTs() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_VltToIntVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(EthTSyn_IntVltType, ETHTSYN_CODE) EthTSyn_UtilVlt_VltToIntVlt(
  ETHTSYN_P2CONST(StbM_VirtualLocalTimeType) VltPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltType intVlt;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert virtual local time into internal virtual local time. */
  intVlt = (EthTSyn_IntVltType)((EthTSyn_IntVltType)VltPtr->nanosecondsHi << ETHTSYN_VLT_NS_HIGH_SHIFT);
  intVlt |= (EthTSyn_IntVltType)VltPtr->nanosecondsLo;

  return intVlt;
} /* EthTSyn_UtilVlt_VltToIntVlt() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltToVlt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(StbM_VirtualLocalTimeType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltToVlt(
  EthTSyn_IntVltType IntVlt)
{
  /* ----- Local Variables ---------------------------------------------- */
  StbM_VirtualLocalTimeType vlt;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Convert internal virtual local time into virtual local time. */
  vlt.nanosecondsHi = (uint32)((IntVlt & ETHTSYN_VLT_NS_HIGH_MASK) >> ETHTSYN_VLT_NS_HIGH_SHIFT);
  vlt.nanosecondsLo = (uint32)(IntVlt & ETHTSYN_VLT_NS_LOW_MASK);

  return vlt;
} /* EthTSyn_UtilVlt_IntVltToVlt() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_IntVltMgmtToTsMgmt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(EthTSyn_TsMgmtStructType, ETHTSYN_CODE) EthTSyn_UtilVlt_IntVltMgmtToTsMgmt(
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IntVltMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_TsMgmtStructType tsMgmt;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If internal virtual local time is valid. */
  if(IntVltMgmtPtr->IntVltValid == TRUE)
  {
    /* #100 Convert the internal virtual local time into a global time stamp and mark the global time stamp as
     *      available. */
    tsMgmt.Ts = EthTSyn_UtilVlt_IntVltToTs(IntVltMgmtPtr->IntVlt);
    tsMgmt.State = ETHTSYN_TS_S_AVAILABLE;
  }
  /* #20 Otherwise, mark the global time stamp as invalid as well. */
  else
  {
    tsMgmt.State = ETHTSYN_TS_S_INVALID;
  }

  return tsMgmt;
} /* EthTSyn_UtilVlt_IntVltMgmtToTsMgmt() */

/**********************************************************************************************************************
 *  EthTSyn_UtilVlt_TsMgmtToIntVltMgmt
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(EthTSyn_IntVltMgmtType, ETHTSYN_CODE) EthTSyn_UtilVlt_TsMgmtToIntVltMgmt(
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) TsMgmtPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthTSyn_IntVltMgmtType intVltMgmt;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If global timestamp is available. */
  if (TsMgmtPtr->State == ETHTSYN_TS_S_AVAILABLE)
  {
    /* #100 Convert the global time stamp into an internal virtual local time and mark the virtual local time as
     *      valid. */
    intVltMgmt.IntVlt = EthTSyn_UtilVlt_TsToIntVlt(&TsMgmtPtr->Ts);                                                    /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
    intVltMgmt.IntVltValid = TRUE;
  }
  /* #20 Otherwise, mark the internal virtual local time stamp as invalid. */
  else
  {
    intVltMgmt.IntVltValid = FALSE;
  }

  return intVltMgmt;
} /* EthTSyn_UtilVlt_TsMgmtToIntVltMgmt() */

/**********************************************************************************************************************
 *  RX UTILS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageGeneral
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageGeneral(
  ETHTSYN_P2CONST(uint8) RxBufPtr,
                  uint16 LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Message length sanity check */
  if(LenByte < ETHTSYN_HDR_COM_LENGTH)
  {
    /* Invalid message length, message is smaller than common header --> drop message */
    /* Note: This should never happen since the common header length is 34 while the min Eth Frame Payload size is 46 */
    errorId = ETHTSYN_E_MSG_LENGTH;
  }
  else
  {
    /* #20 Check header message length vs. LenByte */
    if(IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS) > LenByte)                                           /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    {
      errorId = ETHTSYN_E_MSG_LENGTH;
    }
    /* #30 Check EthTSyn Protocol version */
    /* Shift of ETHTSYN_MSG_HDR_VERSION_PTP_SHIFT not required because it is 0. */
    else if((IpBase_GetUint8(RxBufPtr, ETHTSYN_MSG_HDR_VERSION_PTP_OFS) & ETHTSYN_MSG_HDR_VERSION_PTP_MASK) !=
      ETHTSYN_SUPPORTED_PROTOCOL_VERSION)                                                                              /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    {
      /* Invalid EthTSyn protocol version --> drop message */
      errorId = ETHTSYN_E_PROTOCOL_VERSION;
    }
    else
    {
      errorId = ETHTSYN_E_NO_ERROR;
    }
  }

  return errorId;
} /* EthTSyn_UtilRx_CheckMessageGeneral() */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_CheckMessageTypeAndLength
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(uint8, ETHTSYN_CODE) EthTSyn_UtilRx_CheckMessageTypeAndLength(
  ETHTSYN_P2CONST(uint8)  RxBufPtr,
                  uint16  LenByte)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId;
  uint16 expectedMsgLength = 0;
  boolean expectedMsgLengthIsMinLength = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Try to get the expected message length and validate message type. */
  errorId = EthTSyn_UtilRx_GetExpectedMsgLengthWithMsgTypeCheck(RxBufPtr, &expectedMsgLength,
      &expectedMsgLengthIsMinLength);                                                                                  /* SBSW_ETHTSYN_ETH_RX_BUFFER_FWD_AND_LOC_VAR_REF */

  if(errorId == ETHTSYN_E_NO_ERROR)
  {
    /* #20 Verify message length. */
    uint16 msgLengthHeader = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS);                               /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    if(expectedMsgLengthIsMinLength == TRUE)
    {
      if( (LenByte < expectedMsgLength) || (msgLengthHeader < expectedMsgLength) )
      {
        errorId = ETHTSYN_E_MSG_LENGTH;
      }
    }
    else
    {
      if( (LenByte < expectedMsgLength) || (msgLengthHeader != expectedMsgLength) )
      {
        errorId = ETHTSYN_E_MSG_LENGTH;
      }
    }
  }

  return errorId;
} /* EthTSyn_UtilRx_CheckMessageTypeAndLength() */

#if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_QualifyAnnounceMsg
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilRx_QualifyAnnounceMsg(
  ETHTSYN_P2CONST(uint8)                  RxBufPtr,
                  EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint16 assumedLenByte;
  uint16 stepsRemovedCnt;
  const uint16 lenByte = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS);                                   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
  const uint16 pathTraceTlvLen = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_LEN_OFS);              /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get attributes of announce message. */
  stepsRemovedCnt = IpBase_GetUint16(RxBufPtr, ETHTSYN_MSG_ANNOUNCE_STEPS_REMOVED_OFS);                                /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */

  /* #20 Sanity check of announce path trace TLV length field. */
  if((pathTraceTlvLen % ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH) == 0u)
  {
    const EthTSyn_CtrlIdxOfPortType ctrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
    const EthTSyn_AnnounceInfoIdxOfSlavePortType announceInfoIdx = EthTSyn_GetAnnounceInfoIdxOfSlavePort(slavePortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ctrlIdx);
    const uint16 pathSequenceTlvCnt = pathTraceTlvLen / ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH;

    /* #30 Calculate assumed length including the tlv path sequence. Subtract the
     * ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH because the length of one element is already
     * included in the ETHTSYN_MSG_ANNOUNCE_LENGTH. */
    assumedLenByte = (uint16)(ETHTSYN_MSG_ANNOUNCE_LENGTH + pathTraceTlvLen -
      ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH);

    /* #40 Check that received Announce message is not from own system and that own system is not included in the path
     * sequence. */
     /* PRQA S 3415 5 */ /* MD_EthTSyn_3415_ReadOnly */
    if(
      (IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS) != ctrlStatePtr->ClockIdentity) &&   /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      (IpBase_GetUint64(RxBufPtr, ETHTSYN_MSG_ANNOUNCE_GM_IDENTITY_OFS) != ctrlStatePtr->ClockIdentity) &&             /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
      (lenByte == assumedLenByte) &&
      (stepsRemovedCnt <= EthTSyn_GetMaxeStepsRemovedOfAnnounceInfo(announceInfoIdx))
      )
    {
      uint32 currPathTraceElemOfs = ETHTSYN_MSG_ANNOUNCE_PATH_TRACE_TLV_PATH_SEQ_START_OFS;
      uint16_least i;
      retVal = E_OK;

      /* Iterate through path sequence of path trace TLV and ensure that own system is not included. */
      for(i = 0; i < pathSequenceTlvCnt; i++)
      {
        if(IpBase_GetUint64(RxBufPtr, currPathTraceElemOfs) == ctrlStatePtr->ClockIdentity)                            /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
        {
          retVal = E_NOT_OK;
          break;
        }
        currPathTraceElemOfs += ETHTSYN_MSG_ANNOUNCE_PATH_SEQUENCE_ELEMENT_LENGTH;
      }
    }
  }

  return retVal;
} /* EthTSyn_UtilRx_QualifyAnnounceMsg() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */
#endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection
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
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection(
  EthTSyn_IntPortIdxType PortIdx,
  uint64                 SrcClockIdentity)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 runtimeErrorId = ETHTSYN_E_NO_ERROR; /* PRQA S 2981 */ /* MD_EthTSyn_2981_ErrorId */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check Port Role. */
#if ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) )
  if(EthTSyn_IsSlavePortUsedOfPort(PortIdx) == TRUE)
#endif /* ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) ) */
#if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
  {
# if ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || \
     (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) || \
     (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON) \
     )
    const EthTSyn_TimeDomainIdxOfPortType timeDomainIdx = EthTSyn_GetTimeDomainIdxOfPort(PortIdx);
    /* #20 Check if master clock identity is already valid. */
    if(EthTSyn_IsGmPresentOfSystemState(timeDomainIdx) == TRUE)
    {
      /* #200 Master clock identity is valid: Verify the source clock identity and set errorId to ETHTSYN_E_TSCONFLICT
       *      in case of invalid source clock identity. */
      if(SrcClockIdentity != EthTSyn_GetGmClockIdentityOfSystemState(timeDomainIdx))
      {
        runtimeErrorId = ETHTSYN_E_TSCONFLICT;
      }
    }
    else
# endif /* ( (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) || \
       (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) || \
       (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_ON)) */
    {
      /* #201 Master clock identity is not valid: Check if announce is used for the slave port. */
# if (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON)
      const EthTSyn_SlavePortIdxOfPortType slavePortIdx = EthTSyn_GetSlavePortIdxOfPort(PortIdx);
      if(EthTSyn_IsAnnounceInfoUsedOfSlavePort(slavePortIdx) == TRUE)
      {
        /* #2010 Announce is used: Set errorId to ETHTSYN_E_TSCONFLICT. */
        runtimeErrorId = ETHTSYN_E_TSCONFLICT;
      }
      else
# endif /* (ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_ON) */
      {
# if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
        /* #2011 Announce is not used: Store the master clock identity. */
        EthTSyn_SetGmPresentOfSystemState(timeDomainIdx, TRUE);                                                        /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
        EthTSyn_SetGmClockIdentityOfSystemState(timeDomainIdx, SrcClockIdentity);                                      /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_SUB_MEMBER_ACCESS */
# else
        /* Nothing to do. */
# endif /* (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */
      }

    }
  }
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
#if ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) )
  else
#endif /* ( (ETHTSYN_SLAVE_SUPPORT == STD_ON) && (ETHTSYN_MASTER_SUPPORT == STD_ON) ) */
#if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  {
    /* #30 Master Port: Set errorId to ETHTSYN_E_TMCONFLICT. */
    runtimeErrorId = ETHTSYN_E_TMCONFLICT;
  }
#endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

#if (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON)
  /* #40 Report runtime error if any occurred. */
# if (ETHTSYN_SLAVE_SUPPORT == STD_ON)
  if(runtimeErrorId != ETHTSYN_E_NO_ERROR)
# endif /* (ETHTSYN_SLAVE_SUPPORT == STD_ON) */
  {
    (void)Det_ReportRuntimeError(ETHTSYN_MODULE_ID, ETHTSYN_INSTANCE_ID,
        ETHTSYN_SID_SYNC_PORT_ROLE_CHECK_WITH_MS_CONFLICT_DETECT, runtimeErrorId);
  }
#endif /* (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_ON) */

#if (ETHTSYN_SLAVE_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(SrcClockIdentity); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#else
# if ((ETHTSYN_ANNOUNCE_RX_SUPPORT == STD_OFF) && \
     (ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION == STD_OFF) && \
     (ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT == STD_OFF) \
     )
  ETHTSYN_DUMMY_STATEMENT(SrcClockIdentity); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(PortIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif
#endif /* (ETHTSYN_SLAVE_SUPPORT == STD_OFF) */

  return (boolean)(runtimeErrorId == ETHTSYN_E_NO_ERROR); /* PRQA S 2995, 2996, 4304 */ /* MD_EthTSyn_2995, MD_EthTSyn_2996, MD_MSR_AutosarBoolean */
} /* EthTSyn_UtilRx_SyncPortRoleCheckWithMasterSlaveConflictDetection() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  EthTSyn_UtilRx_PortIdentityIsEqual
 *********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_PortIdentityIsEqual(
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType)  LocalPortIdentityPtr,
  ETHTSYN_P2CONST(uint8)                     MsgPortIdentStartPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isEqual = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* PRQA S 3415 6 */ /* MD_EthTSyn_3415_ReadOnly */
  if(
    (LocalPortIdentityPtr->PortNumber ==
      IpBase_GetUint16(MsgPortIdentStartPtr, ETHTSYN_MSG_PORT_IDENT_PORT_NUM_OFS)) &&                                  /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    (LocalPortIdentityPtr->ClockIdentity ==
      IpBase_GetUint64(MsgPortIdentStartPtr, ETHTSYN_MSG_PORT_IDENT_CLOCK_IDENTY_OFS))                                 /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    )
  {
    isEqual = TRUE;
  }

  return isEqual;
} /* EthTSyn_UtilRx_PortIdentityIsEqual() */

#if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_UtilRx_PortIdentityIsEqualLocalPort
 *********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
*/
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilRx_PortIdentityIsEqualLocalPort(
                  EthTSyn_IntPortIdxType  PortIdx,
  ETHTSYN_P2CONST(uint8)                  MsgPortIdentStartPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean isEqual = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  if(EthTSyn_GetNumberOfPort(PortIdx) == IpBase_GetUint16(MsgPortIdentStartPtr, ETHTSYN_MSG_PORT_IDENT_PORT_NUM_OFS))  /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
  {
    const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
    ETHTSYN_CONSTP2CONST(EthTSyn_CtrlStateType) ctrlStatePtr = EthTSyn_GetAddrCtrlState(ethTSynCtrlIdx);

    if(ctrlStatePtr->ClockIdentity ==
      IpBase_GetUint64(MsgPortIdentStartPtr, ETHTSYN_MSG_PORT_IDENT_CLOCK_IDENTY_OFS))                                 /* SBSW_ETHTSYN_ETH_RX_BUFFER_READ_FWD */
    {
      isEqual = TRUE;
    }
  }

  return isEqual;
} /* EthTSyn_UtilRx_PortIdentityIsEqualLocalPort() */
#endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

#if (ETHTSYN_TX_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  TX UTILS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ProvideTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_ProvideTxBuffer(
               EthTSyn_IntPortIdxType         PortIdx,
 ETHTSYN_P2VAR(EthTSyn_EthTxBufferStructType) TxBufferPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  uint16 bufferLength = TxBufferPtr->Length;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the debounce timer of the physical port expired. */
  if(EthTSyn_UtilTx_IsDebounceTimerExpired(PortIdx) == TRUE)
  {
    /* #20 Request Ethernet TxBuffer from EthIf via EthIf_ProvideTxBuffer(). */
    /* PRQA S 0310, 0311, 3305 3 */ /* MD_EthTSyn_PtrCast_EthBuffer */
    if(EthIf_ProvideTxBuffer(EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIdx), ETHTSYN_FRAME_TYPE,
      EthTSyn_GetFramePrioOfPort(PortIdx), &(TxBufferPtr->BufferIdx),
      (ETHTSYN_P2VAR(ETHTSYN_P2VAR(Eth_DataType)))&(TxBufferPtr->BufferPtr), &bufferLength) == BUFREQ_OK)              /* SBSW_ETHTSYN_PTR_FORWARD_STRUCT_MEMBER_AND_LOC_VAR */
    {
      /* #30 TxBuffer allocated. Initialize it with '0'. */
      VStdLib_MemClr(TxBufferPtr->BufferPtr, TxBufferPtr->Length); /* PRQA S 0315 */ /* MD_MSR_VStdLibCopy */          /* SBSW_ETHTSYN_PROVIDE_TX_BUFFER_CLR */

      retVal = E_OK;
    }
  }

  return retVal;
} /* EthTSyn_UtilTx_ProvideTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareTransmission
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
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareTransmission(
                  EthTSyn_EthIfCtrlIdxOfCtrlType   EthIfCtrlIdx,
                  uint8                            TxBufferIdx,
                  EthTSyn_EnableTimestampFlagsType EnableTsFlags,
  ETHTSYN_P2CONST(EthTSyn_SwtMgmtInfoType)         SwtMgmtInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* Initialize with E_OK because E_OK should be returned when no action is performed */
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
  boolean enableHwTimestamp = EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_HW_TS_MASK);
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
  /* #10 Check if switch information have to be set. */
  if(SwtMgmtInfoPtr != NULL_PTR)
  {
    /* #30 Set switch management information. */
    retVal = EthIf_SetSwitchMgmtInfo(EthIfCtrlIdx, TxBufferIdx, (ETHTSYN_P2VAR(EthSwt_MgmtInfoType))SwtMgmtInfoPtr); /* PRQA S 0311 */ /* MD_EthTSyn_0311 */ /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
    /* #20 Enable switch egress timestamp if required. */
    if((retVal == E_OK) && (EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_SWT_TS_MASK) == TRUE)) /* PRQA S 3415 */ /* MD_EthTSyn_3415_ReadOnly */
    {
      retVal = EthIf_SwitchEnableTimeStamping(EthIfCtrlIdx, TxBufferIdx,                                               /* SBSW_ETHTSYN_INTERNAL_FUNCTION_POINTER_PARAM_FORWARD */
        (ETHTSYN_P2VAR(EthSwt_MgmtInfoType))SwtMgmtInfoPtr); /* PRQA S 0311 */ /* MD_EthTSyn_0311 */
#   if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
      enableHwTimestamp =
        (boolean)(EthTSyn_Util_AreBitsSet(EnableTsFlags, ETHTSYN_ENABLE_TS_HW_XOR_SWT_TS_MASK) == FALSE); /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
#   endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
    }
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */
  }
  if(retVal == E_OK)
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
  {
# if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON)
    /* #40 Enable egress timestamp (HW) if required. */
    if(enableHwTimestamp == TRUE)
    {
      retVal = EthIf_EnableEgressTimestamp(EthIfCtrlIdx, TxBufferIdx);
    }
# endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_ON) */
  }

  /* #50 Handle dummy statements. */
# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(SwtMgmtInfoPtr); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(EthIfCtrlIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
  ETHTSYN_DUMMY_STATEMENT(TxBufferIdx); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_OFF) */
# if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF)
#  if (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF)
  ETHTSYN_DUMMY_STATEMENT(EnableTsFlags); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#  endif /* (ETHTSYN_HW_TIMESTAMP_SUPPORT == STD_OFF) */
# endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_OFF) */

  return retVal;
} /* EthTSyn_UtilTx_PrepareTransmission() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTSYN_CODE) EthTSyn_UtilTx_Transmit(
  EthTSyn_IntPortIdxType PortIdx,
  uint8                  TxBufferIdx,
  uint16                 TxLength)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  const EthTSyn_CtrlIdxOfPortType ethTSynCtrlIdx = EthTSyn_GetCtrlIdxOfPort(PortIdx);
  const EthTSyn_EthIfCtrlIdxOfCtrlType ethIfCtrlIdx = EthTSyn_GetEthIfCtrlIdxOfCtrl(ethTSynCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Trigger the transmission of the passed Ethernet transmission buffer with the passed length. */
  /* PRQA S 0311 2 */ /* MD_EthTSyn_0311 */
  retVal = EthIf_Transmit(ethIfCtrlIdx, TxBufferIdx, ETHTSYN_FRAME_TYPE, TRUE, TxLength,
    (ETHTSYN_P2VAR(uint8))EthTSyn_DestinationMac);                                                                     /* SBSW_ETHTSYN_GLOBAL_VAR_AS_PTR */

  /* #20 Recharge the debounce timer if transmission succeeded. */
  if(retVal == E_OK)
  {
    EthTSyn_UtilTx_RechargeDebounceTimer(PortIdx);
  }

  return retVal;
} /* EthTSyn_UtilTx_Transmit() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_ReleaseTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_ReleaseTxBuffer(EthTSyn_EthIfCtrlIdxOfCtrlType EthIfCtrlIdx,
  uint8 TxBufferIdx)
{
  /* #10 Release the Ethernet transmission buffer by calling EthIf_Transmit with a length of '0' */
  /* PRQA S 0311 2 */ /* MD_EthTSyn_0311 */
  (void)EthIf_Transmit(EthIfCtrlIdx, TxBufferIdx, ETHTSYN_FRAME_TYPE, FALSE, 0,
    (ETHTSYN_P2VAR(uint8))EthTSyn_DestinationMac);                                                                     /* SBSW_ETHTSYN_GLOBAL_VAR_AS_PTR */
} /* EthTSyn_UtilTx_ReleaseTxBuffer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_PrepareCommonMsgHdr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_PrepareCommonMsgHdr(
  ETHTSYN_P2VAR(uint8)                  TxBufPtr,
                uint8                   MsgType,
                EthTSyn_IntPortIdxType  PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 msgLength = 0u;
  uint16 sequenceId = 0u;
  uint8 comHdrControl = 0u;
  sint8 logMessageInterval = 0;
  uint8 flagsFieldByte0 = 0u;
  uint8 flagsFieldByte1 = ETHTSYN_FLAGS_OCTET_1_DEFAULT_VALUE;
  const uint16 portNumber = (uint16)EthTSyn_GetNumberOfPort(PortIdx);
  const uint8 domainNumber = EthTSyn_GetIdOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(PortIdx));
  const EthTSyn_ClockIdentityType srcPortIdentity =
    (EthTSyn_GetAddrCtrlState(EthTSyn_GetCtrlIdxOfPort(PortIdx)))->ClockIdentity;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get message specific values of the common message header from Message type. */
  switch(MsgType)
  {
# if (ETHTSYN_MASTER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_SYNC:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = ETHTSYN_MSG_SYNC_LENGTH;
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_SYNC;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      flagsFieldByte0 = ETHTSYN_FLAGS_OCTET_0_TWO_STEP;
      break;
    }

  case ETHTSYN_MSG_TYPE_FOLLOW_UP:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = EthTSyn_GetFollowUpMsgLengthOfMasterPort(EthTSyn_GetMasterPortIdxOfPort(PortIdx));
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_FOLLOW_UP;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      break;
    }
# endif /* (ETHTSYN_MASTER_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_REQ:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayInitiatorIdxOfPdelayConfigType pDelayInitiatorIdx =
        EthTSyn_GetPdelayInitiatorIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayReqSmIdxOfPdelayInitiatorType pDelayReqSmIdx =
        EthTSyn_GetPdelayReqSmIdxOfPdelayInitiator(pDelayInitiatorIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayReqSmType) pDelayReqSmPtr = EthTSyn_GetAddrPdelayReqSm(pDelayReqSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_REQ_LENGTH;
      sequenceId = pDelayReqSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_REQ;
      logMessageInterval = EthTSyn_GetLogMessageIntervalOfPdelayInitiator(pDelayInitiatorIdx);
      break;
    }
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_PDELAY_RESP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_RESP_LENGTH;
      sequenceId = pDelayRespSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP;
      logMessageInterval = ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT;
      flagsFieldByte0 = ETHTSYN_FLAGS_OCTET_0_TWO_STEP;
      break;
    }

  case ETHTSYN_MSG_TYPE_PDELAY_RES_FOLLOW_UP:
    {
      const EthTSyn_PdelayConfigIdxOfPortType pDelayCfgIdx = EthTSyn_GetPdelayConfigIdxOfPort(PortIdx);
      const EthTSyn_PdelayResponderIdxOfPdelayConfigType pDelayResponderIdx =
        EthTSyn_GetPdelayResponderIdxOfPdelayConfig(pDelayCfgIdx);
      const EthTSyn_PdelayRespSmIdxOfPdelayResponderType pDelayRespSmIdx =
        EthTSyn_GetPdelayRespSmIdxOfPdelayResponder(pDelayResponderIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_PdelayRespSmType) pDelayRespSmPtr = EthTSyn_GetAddrPdelayRespSm(pDelayRespSmIdx);

      msgLength = ETHTSYN_MSG_P_DELAY_RESP_FOLLOW_UP_LENGTH;
      sequenceId = pDelayRespSmPtr->PdelayReq.SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_PDELAY_RESP_FOLLOW_UP;
      logMessageInterval = ETHTSYN_HDR_COM_LOG_MESSAGE_INTERVAL_DEFAULT;
      break;
    }
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# if (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON)
  case ETHTSYN_MSG_TYPE_ANNOUNCE:
    {
      const EthTSyn_MasterPortIdxOfPortType masterPortIdx = EthTSyn_GetMasterPortIdxOfPort(PortIdx);
      ETHTSYN_CONSTP2CONST(EthTSyn_SyncSendSmType) syncSendSmPtr = EthTSyn_GetAddrSyncSendSm(masterPortIdx);

      msgLength = ETHTSYN_MSG_ANNOUNCE_LENGTH;
      sequenceId = syncSendSmPtr->SequenceId;
      comHdrControl = ETHTSYN_HDR_COM_CONTROL_ANNOUNCE;
      logMessageInterval = syncSendSmPtr->LogMessageInterval;
      break;
    }
# endif /* (ETHTSYN_ANNOUNCE_TX_SUPPORT == STD_ON) */

  default:
    {
      /* This should never happen. Transmission of message with type which is not supported in the current
         configuration. Do nothing. */
      break;
    }
  } /* PRQA S 3315 */ /* MD_EthTSyn_3315 */

  /* #20 Set common message header attributes. */
  /* Because the hole Ethernet transmission buffer (at least the part relevant for EthTSyn) is initialized with '0'
   * by the EthTSyn, setting message fields to '0' explicitly is not required (e.g. reserved fields). */
  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_MSG_TYPE_OFS, (uint8)(ETHTSYN_HDR_COM_TRANSPORT_SPECIFIC | MsgType));      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_VERSION_PTP_OFS, ETHTSYN_SUPPORTED_PROTOCOL_VERSION);                      /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_HDR_MSG_LENGTH_OFS, msgLength);                                               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_DOMAIN_NUM_OFS, domainNumber);                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_FLAGS_0_OFS, flagsFieldByte0);                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_FLAGS_1_OFS, flagsFieldByte1);                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint64(TxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_CLOCK_IDENT_OFS, srcPortIdentity);                         /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_HDR_SRC_PORT_IDENT_PORT_NUM_OFS, portNumber);                                 /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */

  IpBase_PutUint16(TxBufPtr, ETHTSYN_MSG_HDR_SEQUENCE_ID_OFS, sequenceId);                                             /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_CONTROL_OFS, comHdrControl);                                               /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
  IpBase_PutUint8(TxBufPtr, ETHTSYN_MSG_HDR_LOG_MSG_INTERVAL_OFS, (uint8)logMessageInterval);                          /* SBSW_ETHTSYN_ETH_TX_BUFFER_FWD */
} /* EthTSyn_UtilTx_PrepareCommonMsgHdr() */ /* PRQA S 6050 */ /* MD_EthTSyn_6050_CslAccess */

/**********************************************************************************************************************
 *  DEBOUNCE TIMER HANDLING
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_UtilTx_InitDebounceTimer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_InitDebounceTimer(
  EthTSyn_PhysPortIterType PyhsPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the debounce timer to '0'. */
  EthTSyn_SetDebounceTimerOfPhysPort(PyhsPortIdx, 0u);                                                                 /* SBSW_ETHTSYN_INTERNAL_FUNCTION_IDX_PARAM_CSL_03_02 */
} /* EthTSyn_UtilTx_InitDebounceTimer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_RechargeDebounceTimer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_RechargeDebounceTimer(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PhysPortCfgIdxOfPortType physPortCfgIdx = EthTSyn_GetPhysPortCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set the debounce timer to the configured start value. */
  EthTSyn_SetDebounceTimerOfPhysPort(physPortCfgIdx, EthTSyn_GetDebounceTimeOfPhysPortCfg(physPortCfgIdx));            /* SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND */
} /* EthTSyn_UtilTx_RechargeDebounceTimer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_DecDebounceTimer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTSYN_CODE) EthTSyn_UtilTx_DecDebounceTimer(
  EthTSyn_PhysPortIterType PhyPortIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the debounce timer not yet expired. */
  if(EthTSyn_GetDebounceTimerOfPhysPort(PhyPortIdx) > 0u)
  {
    /* #20 Decrement the debounce timer. */
    EthTSyn_DecDebounceTimerOfPhysPort(PhyPortIdx);                                                                    /* SBSW_ETHTSYN_INT_FUNC_IDX_PARAM_CSL_02_MANDATORY_IND */
  }
} /* EthTSyn_UtilTx_DecDebounceTimer() */

/**********************************************************************************************************************
 *  EthTSyn_UtilTx_IsDebounceTimerExpired
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(boolean, ETHTSYN_CODE) EthTSyn_UtilTx_IsDebounceTimerExpired(
  EthTSyn_IntPortIdxType PortIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  const EthTSyn_PhysPortCfgIdxOfPortType physPortCfgIdx = EthTSyn_GetPhysPortCfgIdxOfPort(PortIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if debounce timer reached '0'. */
  return (boolean)(EthTSyn_GetDebounceTimerOfPhysPort(physPortCfgIdx) == 0u);
} /* EthTSyn_UtilTx_IsDebounceTimerExpired() */

/**********************************************************************************************************************
 *  END: TX UTILS
 *********************************************************************************************************************/
#endif /* (ETHTSYN_TX_SUPPORT == STD_ON) */

#define ETHTSYN_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* Justification for module-specific MISRA deviations:
 * see file EthTSyn.c
*/

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Util_Int.c
 *********************************************************************************************************************/
