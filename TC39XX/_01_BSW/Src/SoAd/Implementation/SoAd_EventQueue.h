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
/**        \file  SoAd_EventQueue.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component EventQueue.
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

#if !defined (SOAD_EVENT_QUEUE_H)
# define SOAD_EVENT_QUEUE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd.h"
# include "SoAd_Priv.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define SOAD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
  SoAd_EventQueue_Init()
**********************************************************************************************************************/
/*! \brief        Initializes all event queues.
 *  \details      Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_EventQueue_Init(void);

/**********************************************************************************************************************
  SoAd_EventQueue_AddElement()
**********************************************************************************************************************/
/*! \brief        Adds an event to a specific queue.
 *  \details      Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \param[in]    EventQueue  Name of the event queue.
 *                            [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \param[in]    HandleIdx   Handle index (e.g. socket connection index).
 *                            [range: HandleIdx < SoAd_GetSizeOf<HandleType>()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_EventQueue_AddElement(
  SoAd_EventQueueEnumType EventQueue,
  uint32 HandleIdx);

/**********************************************************************************************************************
  SoAd_EventQueue_GetNextElement()
**********************************************************************************************************************/
/*! \brief        Gets the next element of an specific event queue.
 *  \details      Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \param[in]    EventQueue    Name of the event queue.
 *                              [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \param[out]   HandleIdxPtr  Pointer to the handle index of next element (e.g. socket connection index).
 *  \return       E_OK          Queue has elements and next element is returned and removed from event queue.
 *  \return       E_NOT_OK      Queue has no elements left.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_EventQueue_GetNextElement(
  SoAd_EventQueueEnumType EventQueue,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr);

/**********************************************************************************************************************
  SoAd_EventQueue_GetElementNumToHandle()
**********************************************************************************************************************/
/*! \brief        Returns the number of successively handled events on an specific event queue.
 *  \details      Returns 0 in case event queue is not present. Refer to "Concept for EventQueue" in SoAd_EventQueue.c.
 *  \param[in]    EventQueue          Name of the event queue.
 *                                    [range:  SOAD_EVENT_QUEUE_SOCK_IDX .. SOAD_EVENT_QUEUE_SO_CON_STATE]
 *  \return       ElementNumToHandle  Number of successively handled events.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(uint32, SOAD_CODE) SoAd_EventQueue_GetElementNumToHandle(
  SoAd_EventQueueEnumType EventQueue);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_EVENT_QUEUE_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_EventQueue.h
 *********************************************************************************************************************/
