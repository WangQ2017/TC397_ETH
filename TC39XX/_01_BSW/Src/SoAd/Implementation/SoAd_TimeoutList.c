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
/**        \file  SoAd_TimeoutList.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component TimeoutList.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_TIMEOUT_LIST_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_TimeoutList.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

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
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_TimeoutList_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_TimeoutList_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_TimeoutListDynIterType           timeoutListIter;
  SoAd_TimeoutListUdpAliveMapIterType   timeoutListUdpAliveMapIter;
  SoAd_TimeoutListNPduUdpTxMapIterType  timeoutListNPduUdpTxMapIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all timeout lists and reset management struct. */
  for ( timeoutListIter = 0u; timeoutListIter < SoAd_GetSizeOfTimeoutListDyn(); timeoutListIter++ )
  {
    SoAd_SetLvlOfTimeoutListDyn(timeoutListIter, 0u);                                                                  /* SBSW_SOAD_CSL01 */
  }

  /* #20 Reset timeout list for UDP alive supervision timeout. */
  for ( timeoutListUdpAliveMapIter = 0u;
    timeoutListUdpAliveMapIter < SoAd_GetSizeOfTimeoutListUdpAliveMap();
    timeoutListUdpAliveMapIter++ )
  {
    SoAd_SetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(timeoutListUdpAliveMapIter,                                 /* SBSW_SOAD_CSL01 */
      SoAd_GetSizeOfTimeoutListUdpAlive());
  }

  /* #30 Reset timeout list for nPdu. */
  for ( timeoutListNPduUdpTxMapIter = 0u;
    timeoutListNPduUdpTxMapIter < SoAd_GetSizeOfTimeoutListNPduUdpTxMap();
    timeoutListNPduUdpTxMapIter++ )
  {
    SoAd_SetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(timeoutListNPduUdpTxMapIter,                              /* SBSW_SOAD_CSL01 */
      SoAd_GetSizeOfTimeoutListNPduUdpTx());
  }
} /* SoAd_TimeoutList_Init() */

/**********************************************************************************************************************
 *  SoAd_TimeoutList_SetElement()
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
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_SetElement(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx,
  uint32 Timeout,
  uint32 TimerCounter)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTimeoutListDynType timeListIdx;
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that timeout list is written inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Set element for UDP alive supervision timeout. */
  if ( TimeoutList == SOAD_TIMEOUT_LIST_UDP_ALIVE )
  {
    SoAd_SizeOfSoConType soConIdx = (SoAd_SizeOfSoConType)HandleIdx;

    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynUdpAliveIdxOfTimeoutListIdent(0u);

    /* #200 Check if handle is not yet in list. */
    if ( SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx) ==
      SoAd_GetSizeOfTimeoutListUdpAlive() )
    {
      /* #2000 Add handle to list. */
      SoAd_SetSoConIdxOfTimeoutListUdpAlive(SoAd_GetLvlOfTimeoutListDyn(timeListIdx), soConIdx);                       /* SBSW_SOAD_CALCULATED_TimeoutListUdpAlive */
      SoAd_SetTimeoutOfTimeoutListUdpAlive(SoAd_GetLvlOfTimeoutListDyn(timeListIdx),                                   /* SBSW_SOAD_CALCULATED_TimeoutListUdpAlive */
        (uint32)(TimerCounter + Timeout));

      /* #2001 Add used list index to socket connection to list index map. */
      SoAd_SetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx,                                                 /* SBSW_SOAD_PARAMETER_IDX */
        (SoAd_SizeOfTimeoutListUdpAliveType)SoAd_GetLvlOfTimeoutListDyn(timeListIdx));

      /* #2002 Increment timeout list level. */
      SoAd_IncLvlOfTimeoutListDyn(timeListIdx);                                                                        /* SBSW_SOAD_OPTIONAL_CSL03 */

      retVal = E_OK;
    }
    /* #201 Update timeout in list entry otherwise. */
    else
    {
      SoAd_SetTimeoutOfTimeoutListUdpAlive(SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx),           /* SBSW_SOAD_CALCULATED_TimeoutListUdpAlive */
        (uint32)(TimerCounter + Timeout));

      retVal = E_OK;
    }
  }
  /* #21 Set element for nPdu timeout otherwise. */
  else
  {
    SoAd_SizeOfNPduUdpTxType nPduUdpTxIdx = (SoAd_SizeOfNPduUdpTxType)HandleIdx;

    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent(0u);

    /* #210 Check if handle is not yet in list. */
    if ( SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx) ==
      SoAd_GetSizeOfTimeoutListNPduUdpTx() )
    {
      /* #2100 Check if list size is sufficient for new element. */
      if ( SoAd_GetLvlOfTimeoutListDyn(timeListIdx) < SoAd_GetSizeOfTimeoutListNPduUdpTx() )
      {
        /* #21000 Add handle to list. */
        SoAd_SetNPduUdpTxIdxOfTimeoutListNPduUdpTx(SoAd_GetLvlOfTimeoutListDyn(timeListIdx), nPduUdpTxIdx);            /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx */
        SoAd_SetTimeoutOfTimeoutListNPduUdpTx(SoAd_GetLvlOfTimeoutListDyn(timeListIdx),                                /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx */
          (uint32)(TimerCounter + Timeout));

        /* #21001 Add used list index to nPdu to list index map. */
        SoAd_SetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx,                                         /* SBSW_SOAD_PARAMETER_IDX */
          (SoAd_SizeOfTimeoutListNPduUdpTxType)SoAd_GetLvlOfTimeoutListDyn(timeListIdx));

        /* #21002 Increment timeout list level. */
        SoAd_IncLvlOfTimeoutListDyn(timeListIdx);                                                                      /* SBSW_SOAD_OPTIONAL_CSL03 */

        retVal = E_OK;
      }
    }
    /* #211 Update timeout in list entry otherwise. */
    else
    {
      SoAd_SetTimeoutOfTimeoutListNPduUdpTx(SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx),    /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx */
        (uint32)(TimerCounter + Timeout));

      retVal = E_OK;
    }
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TimeoutList_SetElement() */

/**********************************************************************************************************************
 *  SoAd_TimeoutList_GetCurrentTimeout()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_GetCurrentTimeout(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) TimeoutPtr,
  uint32 TimerCounter)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that timeout list is written inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Get current value for UDP alive supervision timeout. */
  if ( TimeoutList == SOAD_TIMEOUT_LIST_UDP_ALIVE )
  {
    SoAd_SizeOfSoConType                soConIdx;
    SoAd_SizeOfTimeoutListUdpAliveType  timeListUdpAliveIdx;

    soConIdx = (SoAd_SizeOfSoConType)HandleIdx;
    timeListUdpAliveIdx = SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx);

    /* #200 Check if handle is in list. */
    if ( timeListUdpAliveIdx != SoAd_GetSizeOfTimeoutListUdpAlive() )
    {
      /* #2000 Get current timeout value. */
      uint32 currentTimeout = SoAd_GetTimeoutOfTimeoutListUdpAlive(timeListUdpAliveIdx);

      if ( currentTimeout >= TimerCounter )
      { /* no timer counter overflow */
        *TimeoutPtr = (uint32)(currentTimeout - TimerCounter);                                                         /* SBSW_SOAD_POINTER_WRITE */
      }
      else
      { /* timer counter overflow */
        *TimeoutPtr = (uint32)(currentTimeout + (SOAD_MAX_TIMEOUT_32 - TimerCounter));                                 /* SBSW_SOAD_POINTER_WRITE */
      }

      retVal = E_OK;
    }
  }
  /* #21 Get current value for nPdu timeout otherwise. */
  else
  {
    SoAd_SizeOfNPduUdpTxType            nPduUdpTxIdx;
    SoAd_SizeOfTimeoutListNPduUdpTxType timeListnPduUdpTxIdx;

    nPduUdpTxIdx = (SoAd_SizeOfNPduUdpTxType)HandleIdx;
    timeListnPduUdpTxIdx = SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx);

    /* #210 Check if handle is in list. */
    if ( timeListnPduUdpTxIdx != SoAd_GetSizeOfTimeoutListNPduUdpTx() )
    {
      /* #2100 Get current timeout value. */
      uint32 currentTimeout = SoAd_GetTimeoutOfTimeoutListNPduUdpTx(timeListnPduUdpTxIdx);

      if ( currentTimeout >= TimerCounter )
      { /* no timer counter overflow */
        *TimeoutPtr = (uint32)(currentTimeout - TimerCounter);                                                         /* SBSW_SOAD_POINTER_WRITE */
      }
      else
      { /* timer counter overflow */
        *TimeoutPtr = (uint32)(currentTimeout + (SOAD_MAX_TIMEOUT_32 - TimerCounter));                                 /* SBSW_SOAD_POINTER_WRITE */
      }

      retVal = E_OK;
    }
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TimeoutList_GetCurrentTimeout() */

/**********************************************************************************************************************
 *  SoAd_TimeoutList_CheckElements()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_CheckElements(
  SoAd_TimeoutListEnumType TimeoutList,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ElementIdxPtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr,
  uint32 TimerCounter)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTimeoutListDynType timeListIdx;
  Std_ReturnType                retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that timeout list is written and read inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check elements of UDP alive supervision timeout. */
  if ( TimeoutList == SOAD_TIMEOUT_LIST_UDP_ALIVE )
  {
    SoAd_TimeoutListUdpAliveIterType timeListUdpAliveIter;

    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynUdpAliveIdxOfTimeoutListIdent(0u);

    /* #200 Search for timeout. */
    for ( timeListUdpAliveIter = (SoAd_SizeOfTimeoutListUdpAliveType)*ElementIdxPtr;
      timeListUdpAliveIter < SoAd_GetLvlOfTimeoutListDyn(timeListIdx);
      timeListUdpAliveIter++ )
    {
      if ( SoAd_GetTimeoutOfTimeoutListUdpAlive(timeListUdpAliveIter) == TimerCounter )
      {
        /* #2000 Return first occurred timeout. */
        *ElementIdxPtr = (uint32)timeListUdpAliveIter;                                                                 /* SBSW_SOAD_POINTER_WRITE */
        *HandleIdxPtr = SoAd_GetSoConIdxOfTimeoutListUdpAlive(timeListUdpAliveIter);                                   /* SBSW_SOAD_POINTER_WRITE */
        retVal = E_OK;
        break;
      }
    }
  }
  /* #21 Check elements of nPdu timeout. */
  else
  {
    SoAd_TimeoutListNPduUdpTxIterType timeListNPduUdpTxIter;

    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent(0u);

    /* #210 Search for timeout. */
    for ( timeListNPduUdpTxIter = (SoAd_SizeOfTimeoutListNPduUdpTxType)*ElementIdxPtr;
      timeListNPduUdpTxIter < SoAd_GetLvlOfTimeoutListDyn(timeListIdx);
      timeListNPduUdpTxIter++ )
    {
      if ( SoAd_GetTimeoutOfTimeoutListNPduUdpTx(timeListNPduUdpTxIter) == TimerCounter )
      {
        /* #2100 Return first occurred timeout. */
        *ElementIdxPtr = (uint32)timeListNPduUdpTxIter;                                                                /* SBSW_SOAD_POINTER_WRITE */
        *HandleIdxPtr = SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(timeListNPduUdpTxIter);                             /* SBSW_SOAD_POINTER_WRITE */
        retVal = E_OK;
        break;
      }
    }
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_TimeoutList_CheckElements() */

/**********************************************************************************************************************
 *  SoAd_TimeoutList_RemoveElement()
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
FUNC(void, SOAD_CODE) SoAd_TimeoutList_RemoveElement(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfTimeoutListDynType timeListIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that timeout list is written inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Remove element from UDP alive supervision timeout. */
  if ( TimeoutList == SOAD_TIMEOUT_LIST_UDP_ALIVE )
  {
    SoAd_SizeOfSoConType                soConIdx;
    SoAd_SizeOfTimeoutListUdpAliveType  timeListUdpAliveIdx;
    SoAd_SizeOfTimeoutListUdpAliveType  lastTimeListUdpAliveIdx;

    soConIdx = (SoAd_SizeOfSoConType)HandleIdx;
    timeListUdpAliveIdx = SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx);
    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynUdpAliveIdxOfTimeoutListIdent(0u);

    /* #200 Check if handle index has an element. */
    if ( timeListUdpAliveIdx != SoAd_GetSizeOfTimeoutListUdpAlive() )
    {
      /* #2000 Remove element of handle index. */
      SoAd_DecLvlOfTimeoutListDyn(timeListIdx);                                                                        /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(soConIdx, SoAd_GetSizeOfTimeoutListUdpAlive());           /* SBSW_SOAD_PARAMETER_IDX */

      /* Get index of last element in list (lvl is already decremented so lvl is last index). */
      lastTimeListUdpAliveIdx = (SoAd_SizeOfTimeoutListUdpAliveType)SoAd_GetLvlOfTimeoutListDyn(timeListIdx);

      /* #2001 Check if list has more elements. */
      if ( (lastTimeListUdpAliveIdx > 0u) && (lastTimeListUdpAliveIdx != timeListUdpAliveIdx) )
      {
        /* #20010 Replace removed element by last element. */
        /* Replace at index. */
        SoAd_SetSoConIdxOfTimeoutListUdpAlive(timeListUdpAliveIdx,                                                     /* SBSW_SOAD_CALCULATED_TimeoutListUdpAlive */
          SoAd_GetSoConIdxOfTimeoutListUdpAlive(lastTimeListUdpAliveIdx));
        SoAd_SetTimeoutOfTimeoutListUdpAlive(timeListUdpAliveIdx,                                                      /* SBSW_SOAD_CALCULATED_TimeoutListUdpAlive */
          SoAd_GetTimeoutOfTimeoutListUdpAlive(lastTimeListUdpAliveIdx));

        /* Update map of replacing element. */
        SoAd_SetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(                                                        /* SBSW_SOAD_CALCULATED_TimeoutListUdpAliveMap */
          SoAd_GetSoConIdxOfTimeoutListUdpAlive(lastTimeListUdpAliveIdx),
          timeListUdpAliveIdx);
      }
    }
  }
  /* #21 Remove element from nPdu timeout. */
  else
  {
    SoAd_SizeOfNPduUdpTxType            nPduUdpTxIdx;
    SoAd_SizeOfTimeoutListNPduUdpTxType timeListNPduUdpTxIdx;
    SoAd_SizeOfTimeoutListNPduUdpTxType lastTimeListNPduUdpTxIdx;

    nPduUdpTxIdx = (SoAd_SizeOfNPduUdpTxType)HandleIdx;
    timeListNPduUdpTxIdx = SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx);
    /* Optional indirection with constant index: Refer to precondition in function description. */
    timeListIdx = SoAd_GetTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent(0u);

    /* #210 Check if handle index has an element. */
    if ( timeListNPduUdpTxIdx != SoAd_GetSizeOfTimeoutListNPduUdpTx() )
    {
      /* #2100 Remove element of handle index. */
      SoAd_DecLvlOfTimeoutListDyn(timeListIdx);                                                                        /* SBSW_SOAD_OPTIONAL_CSL03 */
      SoAd_SetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(nPduUdpTxIdx, SoAd_GetSizeOfTimeoutListNPduUdpTx());    /* SBSW_SOAD_PARAMETER_IDX */

      /* Get index of last element in list (lvl is already decremented so lvl is last index). */
      lastTimeListNPduUdpTxIdx = (SoAd_SizeOfTimeoutListNPduUdpTxType)SoAd_GetLvlOfTimeoutListDyn(timeListIdx);

      /* #2101 Check if list has more elements. */
      if ( (lastTimeListNPduUdpTxIdx > 0u) && (lastTimeListNPduUdpTxIdx != timeListNPduUdpTxIdx) )
      {
        /* #21010 Replace removed element by last element. */
        /* Replace at index. */
        SoAd_SetNPduUdpTxIdxOfTimeoutListNPduUdpTx(timeListNPduUdpTxIdx,                                               /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx */
          SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(lastTimeListNPduUdpTxIdx));
        SoAd_SetTimeoutOfTimeoutListNPduUdpTx(timeListNPduUdpTxIdx,                                                    /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTx */
          SoAd_GetTimeoutOfTimeoutListNPduUdpTx(lastTimeListNPduUdpTxIdx));

        /* Update map of replacing element. */
        SoAd_SetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(                                                      /* SBSW_SOAD_CALCULATED_TimeoutListNPduUdpTxMap */
          SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(lastTimeListNPduUdpTxIdx),
          timeListNPduUdpTxIdx);
      }
    }
  }

  /* #30 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_TimeoutList_RemoveElement() */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/* Concept for TimeoutList:

  All timeouts handled in a list use the same mechanism. Therefore, there is a generic handling for all timeout lists.
  Each timeout list is identified by an enum value used in the API functions. A generic parameter name "HandleIdx" is
  used in the API functions to identify the object with timeout (e.g. timeout list: UdpAlive -> handle: SoConIdx). The
  timeout value depends on a global counter incremented in each main function. The timeout list stores the value of the
  global counter when the timeout will exceed. The timeout calculation is designed to handle one counter overflow.

  The timeout list entries are stored in "SoAd_TimeoutList<TimeoutList>". When an object adds an timeout to this list
  "SoAd_TimeoutList<TimeoutList>Map" is used to map the object index to the index/element of the timeout list.
  The timeout list is not sorted according to the timeouts. So in main function each element has to be checked. The
  timeout list is not designed to have unused elements. Therefore, when a timeout exceeds and is removed from the
  timeout list the last timeout list element is moved to the index of the removed element.

*/

/**********************************************************************************************************************
 *  END OF FILE: SoAd_TimeoutList.c
 *********************************************************************************************************************/
