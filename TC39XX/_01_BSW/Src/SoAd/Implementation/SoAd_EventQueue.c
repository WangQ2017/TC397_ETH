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
/**        \file  SoAd_EventQueue.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component EventQueue.
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

/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_EVENT_QUEUE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_EventQueue.h"

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
  SoAd_EventQueue_GetEventQueueIdx()
**********************************************************************************************************************/
/*! \brief      Returns the event queue index of a event queue identified by name.
 *  \details    Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \pre        -
 *  \param[in]  EventQueue    Name of the event queue.
 *                            [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \return     EveQueIdx     Index of the event queue.
 *                            [range:  EveQueIdx < SoAd_GetSizeOfEventQueue()]
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfEventQueueType, SOAD_CODE) SoAd_EventQueue_GetEventQueueIdx(
  SoAd_EventQueueEnumType EventQueue);

/**********************************************************************************************************************
  SoAd_EventQueue_GetEventQueueSize()
**********************************************************************************************************************/
/*! \brief      Returns the event queue size of a event queue identified by name.
 *  \details    Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \pre        -
 *  \param[in]  EventQueue      Name of the event queue.
 *                              [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \return     EventQueueSize  Size of the event queue.
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_EventQueue_GetEventQueueSize(
  SoAd_EventQueueEnumType EventQueue);

/**********************************************************************************************************************
  SoAd_EventQueue_AddHandleIdx()
**********************************************************************************************************************/
/*! \brief      Adds handle index to a specific event queue.
 *  \details    Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \pre        -
 *  \param[in]  EventQueue    Name of the event queue.
 *                            [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \param[in]  WriteIdx      Index of event queue to write handle index.
 *                            [range: WriteIdx <  SoAd_GetSizeOf<EventQueue>()]
 *  \param[in]  HandleIdx     Handle index (e.g. socket connection index).
 *                            [range: HandleIdx < SoAd_GetSizeOf<HandleType>()]
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_EventQueue_AddHandleIdx(
  SoAd_EventQueueEnumType EventQueue,
  uint32 WriteIdx,
  uint32 HandleIdx);

/**********************************************************************************************************************
  SoAd_EventQueue_GetHandleIdx()
**********************************************************************************************************************/
/*! \brief      Gets oldest handle index of a specific event queue.
 *  \details    Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \pre        -
 *  \param[in]  EventQueue    Name of the event queue.
 *                            [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \param[out] HandleIdx     Pointer to the handle index of next element (e.g. socket connection index).
 *                            [range: HandleIdx < SoAd_GetSizeOf<HandleType>()]
 *  \context    TASK
 *  \reentrant  TRUE
 *********************************************************************************************************************/
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_EventQueue_GetHandleIdx(
  SoAd_EventQueueEnumType EventQueue,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *  SoAd_EventQueue_GetEventQueueIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(SoAd_SizeOfEventQueueType, SOAD_CODE) SoAd_EventQueue_GetEventQueueIdx(
  SoAd_EventQueueEnumType EventQueue)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfEventQueueType eveQueIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get event queue index of event queue. */
  switch (EventQueue)
  {
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_SOCK_IDX:
    {
      eveQueIdx = SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(0u);
      break;
    }
    case SOAD_EVENT_QUEUE_LOCAL_ADDR:
    {
      eveQueIdx = SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(0u);
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE:
    {
      eveQueIdx = SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(0u);
      break;
    }
    case SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP:
    {
      eveQueIdx = SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(0u);
      break;
    }
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_TCP_TX_SO_CON:
    {
      eveQueIdx = SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(0u);
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_TP_TX_SO_CON:
    {
      eveQueIdx = SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(0u);
      break;
    }
    case SOAD_EVENT_QUEUE_TP_RX_SO_CON:
    {
      eveQueIdx = SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(0u);
      break;
    }
    default: /* SOAD_EVENT_QUEUE_SO_CON_STATE */
    {
      eveQueIdx = SoAd_GetEventQueueStateSoConIdxOfEventQueueIdent(0u);
      break;
    }
  }

  return eveQueIdx;
} /* SoAd_EventQueue_GetEventQueueIdx() */

 /**********************************************************************************************************************
 *  SoAd_EventQueue_GetEventQueueSize()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(uint32, SOAD_CODE) SoAd_EventQueue_GetEventQueueSize(
  SoAd_EventQueueEnumType EventQueue)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32 eveQueSize;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get event queue size of event queue. */
  switch (EventQueue)
  {
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_SOCK_IDX:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueSocketIdx();
      break;
    }
    case SOAD_EVENT_QUEUE_LOCAL_ADDR:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueLocalAddr();
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueIfUdpPduRoute();
      break;
    }
    case SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueIfTxRouteGrp();
      break;
    }
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_TCP_TX_SO_CON:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueTcpTxSoCon();
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_TP_TX_SO_CON:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueTpTxSoCon();
      break;
    }
    case SOAD_EVENT_QUEUE_TP_RX_SO_CON:
    {
      eveQueSize = SoAd_GetSizeOfEventQueueTpRxSoCon();
      break;
    }
    default: /* SOAD_EVENT_QUEUE_SO_CON_STATE */
    {
      eveQueSize = SoAd_GetSizeOfEventQueueStateSoCon();
      break;
    }
  }

  return eveQueSize;
} /* SoAd_EventQueue_GetEventQueueSize() */

 /**********************************************************************************************************************
 *  SoAd_EventQueue_AddHandleIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_EventQueue_AddHandleIdx(
  SoAd_EventQueueEnumType EventQueue,
  uint32 WriteIdx,
  uint32 HandleIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Add handle index to corresponding event queue. */
  switch (EventQueue)
  {
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_SOCK_IDX:
    {
      SoAd_SetSocketIdxOfEventQueueSocketIdx(WriteIdx, (SoAd_SizeOfSocketType)HandleIdx);                              /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
    case SOAD_EVENT_QUEUE_LOCAL_ADDR:
    {
      SoAd_SetLocalAddrIdxOfEventQueueLocalAddr(WriteIdx, (SoAd_SizeOfLocalAddrType)HandleIdx);                        /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE:
    {
      SoAd_SetPduRouteIdxOfEventQueueIfUdpPduRoute(WriteIdx, (SoAd_SizeOfPduRouteType)HandleIdx);                      /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
    case SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP:
    {
      SoAd_SetRouteGrpIdxOfEventQueueIfTxRouteGrp(WriteIdx, (SoAd_SizeOfRouteGrpType)HandleIdx);                       /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_TCP_TX_SO_CON:
    {
      SoAd_SetSoConIdxOfEventQueueTcpTxSoCon(WriteIdx, (SoAd_SizeOfSoConType)HandleIdx);                               /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_TP_TX_SO_CON:
    {
      SoAd_SetSoConIdxOfEventQueueTpTxSoCon(WriteIdx, (SoAd_SizeOfSoConType)HandleIdx);                                /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
    case SOAD_EVENT_QUEUE_TP_RX_SO_CON:
    {
      SoAd_SetSoConIdxOfEventQueueTpRxSoCon(WriteIdx, (SoAd_SizeOfSoConType)HandleIdx);                                /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
    default: /* SOAD_EVENT_QUEUE_SO_CON_STATE */
    {
      SoAd_SetSoConIdxOfEventQueueStateSoCon(WriteIdx, (SoAd_SizeOfSoConType)HandleIdx);                               /* SBSW_SOAD_PARAMETER_IDX */
      break;
    }
  }
} /* SoAd_EventQueue_AddHandleIdx() */

 /**********************************************************************************************************************
 *  SoAd_EventQueue_GetHandleIdx()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
SOAD_LOCAL_INLINE FUNC(void, SOAD_CODE) SoAd_EventQueue_GetHandleIdx(
  SoAd_EventQueueEnumType EventQueue,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get handle index from corresponding event queue. */
  switch (EventQueue)
  {
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_SOCK_IDX:
    {
      *HandleIdxPtr = SoAd_GetSocketIdxOfEventQueueSocketIdx(                                                          /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(0u)));
      break;
    }
    case SOAD_EVENT_QUEUE_LOCAL_ADDR:
    {
      *HandleIdxPtr = SoAd_GetLocalAddrIdxOfEventQueueLocalAddr(                                                       /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(0u)));
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE:
    {
      *HandleIdxPtr = SoAd_GetPduRouteIdxOfEventQueueIfUdpPduRoute(                                                    /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(0u)));
      break;
    }
    case SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP:
    {
      *HandleIdxPtr = SoAd_GetRouteGrpIdxOfEventQueueIfTxRouteGrp(                                                     /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(0u)));
      break;
    }
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_TCP_TX_SO_CON:
    {
      *HandleIdxPtr = SoAd_GetSoConIdxOfEventQueueTcpTxSoCon(                                                          /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(0u)));
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_TP_TX_SO_CON:
    {
      *HandleIdxPtr = SoAd_GetSoConIdxOfEventQueueTpTxSoCon(                                                           /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(0u)));
      break;
    }
    case SOAD_EVENT_QUEUE_TP_RX_SO_CON:
    {
      *HandleIdxPtr = SoAd_GetSoConIdxOfEventQueueTpRxSoCon(                                                           /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(0u)));
      break;
    }
    default: /* SOAD_EVENT_QUEUE_SO_CON_STATE */
    {
      *HandleIdxPtr = SoAd_GetSoConIdxOfEventQueueStateSoCon(                                                          /* SBSW_SOAD_POINTER_WRITE */
        SoAd_GetIdxOfEventQueueDyn(
          SoAd_GetEventQueueStateSoConIdxOfEventQueueIdent(0u)));
      break;
    }
  }
} /* SoAd_EventQueue_GetHandleIdx() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SoAd_EventQueue_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_EventQueue_Init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_EventQueueIterType     eventQueueIter;
  SoAd_EventQueueFlagIterType eventQueueFlagIter;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize management struct of all event queues. */
  for ( eventQueueIter = 0u; eventQueueIter < SoAd_GetSizeOfEventQueue(); eventQueueIter++ )
  {
    SoAd_SetIdxOfEventQueueDyn(eventQueueIter, 0u);                                                                    /* SBSW_SOAD_CSL02 */
    SoAd_SetLvlOfEventQueueDyn(eventQueueIter, 0u);                                                                    /* SBSW_SOAD_CSL02 */
  }
  /* #20 Initialize event queue flags. */
  for ( eventQueueFlagIter = 0u; eventQueueFlagIter < SoAd_GetSizeOfEventQueueFlag(); eventQueueFlagIter++ )
  {
    SoAd_SetEventQueueFlag(eventQueueFlagIter, 0u);                                                                    /* SBSW_SOAD_CSL01 */
  }
} /* SoAd_EventQueue_Init() */

/**********************************************************************************************************************
 *  SoAd_EventQueue_AddElement()
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
FUNC(void, SOAD_CODE) SoAd_EventQueue_AddElement(
  SoAd_EventQueueEnumType EventQueue,
  uint32 HandleIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                    writeIdx;
  SoAd_SizeOfEventQueueType eveQueIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that event queue is written inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Get event queue index of event queue. */
  eveQueIdx = SoAd_EventQueue_GetEventQueueIdx(EventQueue);

  /* #30 Check if event is not yet in queue. */
  if ( (SoAd_GetEventQueueFlag(HandleIdx) & SoAd_GetBitPatternOfEventQueue(eveQueIdx)) == 0u )
  {
    /* #40 Get next queue index. */
    /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
    if ( (uint32)(SoAd_GetIdxOfEventQueueDyn(eveQueIdx) + SoAd_GetLvlOfEventQueueDyn(eveQueIdx)) >=
      SoAd_EventQueue_GetEventQueueSize(EventQueue) )
    { /* wrap around */
      writeIdx = (uint32)(SoAd_GetLvlOfEventQueueDyn(eveQueIdx) -
        (SoAd_EventQueue_GetEventQueueSize(EventQueue) - SoAd_GetIdxOfEventQueueDyn(eveQueIdx)));
    }
    else
    { /* no wrap around */
      /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
      writeIdx = (uint32)(SoAd_GetIdxOfEventQueueDyn(eveQueIdx) + SoAd_GetLvlOfEventQueueDyn(eveQueIdx));
    }

    /* #50 Add new queue entry. */
    SoAd_EventQueue_AddHandleIdx(EventQueue, writeIdx, HandleIdx);
    SoAd_IncLvlOfEventQueueDyn(eveQueIdx);                                                                             /* SBSW_SOAD_INDEX_BY_FUNCTION */

    /* #60 Set flag to indicate that handle index is in queue. */
    SoAd_SetEventQueueFlag(HandleIdx, (SoAd_EventQueueFlagType)(SoAd_GetEventQueueFlag(HandleIdx) |                    /* SBSW_SOAD_PARAMETER_IDX */
      SoAd_GetBitPatternOfEventQueue(eveQueIdx)));
  }

  /* #70 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_EventQueue_AddElement() */

/**********************************************************************************************************************
 *  SoAd_EventQueue_GetNextElement()
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
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EventQueue_GetNextElement(
  SoAd_EventQueueEnumType EventQueue,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  SoAd_SizeOfEventQueueType eveQueIdx;
  Std_ReturnType            retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent that event queue is written inconsistent. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Get event queue index of event queue. */
  eveQueIdx = SoAd_EventQueue_GetEventQueueIdx(EventQueue);

  /* #30 Check if at least one event is in queue. */
  if ( SoAd_GetLvlOfEventQueueDyn(eveQueIdx) > 0u )
  {
    /* #300 Get next element. */
    SoAd_EventQueue_GetHandleIdx(EventQueue, HandleIdxPtr);                                                            /* SBSW_SOAD_POINTER_FORWARD */

    /* #301 Remove element from queue. */
    /* PRQA S 4391 1 */ /* MD_SoAd_GenericWiderTypeCast */
    if ( (uint32)(SoAd_GetIdxOfEventQueueDyn(eveQueIdx) + 1u) == SoAd_EventQueue_GetEventQueueSize(EventQueue) )
    { /* wrap around */
      SoAd_SetIdxOfEventQueueDyn(eveQueIdx, 0u);                                                                       /* SBSW_SOAD_INDEX_BY_FUNCTION */
    }
    else
    { /* no wrap around */
      SoAd_IncIdxOfEventQueueDyn(eveQueIdx);                                                                           /* SBSW_SOAD_INDEX_BY_FUNCTION */
    }
    SoAd_DecLvlOfEventQueueDyn(eveQueIdx);                                                                             /* SBSW_SOAD_INDEX_BY_FUNCTION */

    /* #302 Reset event flag for handle index. */
    SoAd_SetEventQueueFlag(*HandleIdxPtr, (SoAd_EventQueueFlagType)(SoAd_GetEventQueueFlag(*HandleIdxPtr) &            /* SBSW_SOAD_INDEX_BY_FUNCTION */
      ((SoAd_EventQueueFlagType)~SoAd_GetBitPatternOfEventQueue(eveQueIdx))));

    retVal = E_OK;
  }

  SOAD_END_CRITICAL_SECTION();

  return retVal;
} /* SoAd_EventQueue_GetNextElement() */

 /**********************************************************************************************************************
 *  SoAd_EventQueue_GetElementNumToHandle()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(uint32, SOAD_CODE) SoAd_EventQueue_GetElementNumToHandle(
  SoAd_EventQueueEnumType EventQueue)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint32                      elementNumToHandle;
  SoAd_LvlOfEventQueueDynType lvl = 0u;
  SoAd_LimitOfEventQueueType  limit = 0u;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Get limit of successively handled events and current level of event queue. */
  switch (EventQueue)
  {
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_SOCK_IDX:
    {
      lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(0u));
      limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(0u));
      break;
    }
    case SOAD_EVENT_QUEUE_LOCAL_ADDR:
    {
      lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(0u));
      limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(0u));
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_IF_UDP_PDU_ROUTE:
    {
      if ( SoAd_HasEventQueueIfUdpPduRoute() )
      {
        lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(0u));
        limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(0u));
      }
      break;
    }
    case SOAD_EVENT_QUEUE_IF_TX_ROUTE_GRP:
    {
      if ( SoAd_HasEventQueueIfTxRouteGrp() )
      {
        lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(0u));
        limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(0u));
      }
      break;
    }
#if ( SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR ) /* COV_SOAD_QM_FEATURE_1 */
    case SOAD_EVENT_QUEUE_TCP_TX_SO_CON:
    {
      if ( SoAd_HasEventQueueTcpTxSoCon() )
      {
        lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(0u));
        limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(0u));
      }
      break;
    }
#endif /* SOAD_SOCKET_API != SOAD_SOCKET_API_AUTOSAR */
    case SOAD_EVENT_QUEUE_TP_TX_SO_CON:
    {
      if ( SoAd_HasEventQueueTpTxSoCon() )
      {
        lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(0u));
        limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(0u));
      }
      break;
    }
    case SOAD_EVENT_QUEUE_TP_RX_SO_CON:
    {
      if ( SoAd_HasEventQueueTpRxSoCon() )
      {
        lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(0u));
        limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(0u));
      }
      break;
    }
    default: /* SOAD_EVENT_QUEUE_SO_CON_STATE */
    {
      lvl = SoAd_GetLvlOfEventQueueDyn(SoAd_GetEventQueueStateSoConIdxOfEventQueueIdent(0u));
      limit = SoAd_GetLimitOfEventQueue(SoAd_GetEventQueueStateSoConIdxOfEventQueueIdent(0u));
      break;
    }
  }

  /* #20 Return limit if current level exceeds the limit. */
  if ( lvl > limit )
  {
    elementNumToHandle = limit;
  }
  /* #21 Return current level otherwise. */
  else
  {
    elementNumToHandle = lvl;
  }

  return elementNumToHandle;
} /* SoAd_EventQueue_GetElementNumToHandle() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/* Concept for EventQueue:

  All events handled in a queue use the same mechanism. Therefore, there is a generic handling for all event
  queues. Each event queue is identified by an enum value used in the API functions. A generic parameter name
  "HandleIdx" is used in the API functions to identify the object which generates an event (e.g. event queue:
  StateSoCon -> handle: SoConIdx).

  The events are stored and processed as FIFO in "SoAd_EventQueue<EventQueue>" array and managed by
  "SoAd_EventQueueDyn". To identify the event the object index is stored in the queue. Since there is just one event
  queue entry for an object it has to be checked whether the object is already stored in the event queue. To check and
  set this "SoAd_GetEventQueueFlag" is used. To save RAM "SoAd_GetEventQueueFlag" is accessed via a bit pattern for
  each event queue so just one bit is used to indicate if object is already stored in queue. The bit pattern is stored
  in "SoAd_GetBitPatternOfEventQueue".

*/

/**********************************************************************************************************************
 *  END OF FILE: SoAd_EventQueue.c
 *********************************************************************************************************************/
