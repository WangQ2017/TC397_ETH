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
/**        \file  SoAd_TimeoutList.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component TimeoutList.
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

#if !defined (SOAD_TIMEOUT_LIST_H)
# define SOAD_TIMEOUT_LIST_H

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
  SoAd_TimeoutList_Init()
**********************************************************************************************************************/
/*! \brief        Initializes all timeout lists.
 *  \details      Refer to "Concept for TimeoutList" in SoAd_TimeoutList.c.
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TimeoutList_Init(void);

/**********************************************************************************************************************
  SoAd_TimeoutList_SetElement()
**********************************************************************************************************************/
/*! \brief        Sets an element in a specific timeout list.
 *  \details      Adds an element if not already in list or updates element otherwise. Refer to "Concept for
 *                TimeoutList" in SoAd_TimeoutList.c.
 *  \param[in]    TimeoutList   Name of timeout list.
 *                              [range: SOAD_TIMEOUT_LIST_UDP_ALIVE, SOAD_TIMEOUT_LIST_N_PDU]
 *  \param[in]    HandleIdx     Handle index
 *                              [range: HandleIdx < SoAd_GetSizeOf<HandleType>(); HandleType: SoCon, NPduUdpTx]
 *  \param[in]    Timeout       Configured timeout value.
 *  \param[in]    TimerCounter  Running timer counter value.
 *  \return       E_OK          Element added or updated.
 *  \return       E_NOT_OK      List size is not sufficient (occurs if limitation is enabled only).
 *  \pre          Timeout list elements identified by parameter "TimeoutList" have to exist (refer to Safe BSW
 *                assumptions for TimeoutListIdent -> TimeoutListDyn(NPduUdpTx) and TimeoutListNPduUdpTx or for
 *                TimeoutListIdent -> TimeoutListDyn(UdpAlive) and TimeoutListUdpAlive).
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_SetElement(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx,
  uint32 Timeout,
  uint32 TimerCounter);

/**********************************************************************************************************************
  SoAd_TimeoutList_GetCurrentTimeout()
**********************************************************************************************************************/
/*! \brief        Gets the current timeout value of an element in a specific timeout list.
 *  \details      Refer to "Concept for TimeoutList" in SoAd_TimeoutList.c.
 *  \param[in]    TimeoutList   Name of timeout list.
 *                              [range: SOAD_TIMEOUT_LIST_UDP_ALIVE, SOAD_TIMEOUT_LIST_N_PDU]
 *  \param[in]    HandleIdx     Handle index
 *                              [range: HandleIdx < SoAd_GetSizeOf<HandleType>(); HandleType: SoCon, NPduUdpTx]
 *  \param[out]   TimeoutPtr    Pointer to current timeout value.
 *  \param[in]    TimerCounter  Running timer counter value.
 *  \return       E_OK          Element is in timeout list and current timeout value is returned.
 *  \return       E_NOT_OK      Element is not in timeout list.
 *  \pre          Timeout list elements identified by parameter "TimeoutList" have to exist (refer to Safe BSW
 *                assumptions for TimeoutListIdent -> TimeoutListDyn(NPduUdpTx) and TimeoutListNPduUdpTx or for
 *                TimeoutListIdent -> TimeoutListDyn(UdpAlive) and TimeoutListUdpAlive).
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_GetCurrentTimeout(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) TimeoutPtr,
  uint32 TimerCounter);

/**********************************************************************************************************************
  SoAd_TimeoutList_CheckElements()
**********************************************************************************************************************/
/*! \brief        Checks for a timeout in a specific timeout list.
 *  \details      Refer to "Concept for TimeoutList" in SoAd_TimeoutList.c.
 *  \param[in]    TimeoutList   Name of timeout list.
 *                              [range: SOAD_TIMEOUT_LIST_UDP_ALIVE, SOAD_TIMEOUT_LIST_N_PDU]
 *  \param[out]   ElementIdxPtr Pointer to element index with timeout.
 *  \param[out]   HandleIdxPtr  Pointer to handle index with timeout.
 *                              [range: HandleIdx < SoAd_GetSizeOf<HandleType>(); HandleType: SoCon, NPduUdpTx]
 *  \param[in]    TimerCounter  Running timer counter value.
 *  \return       E_OK          Element with timeout found and out parameter are set.
 *  \return       E_NOT_OK      No element with timeout found.
 *  \pre          Timeout list elements identified by parameter "TimeoutList" have to exist (refer to Safe BSW
 *                assumptions for TimeoutListIdent -> TimeoutListDyn(NPduUdpTx) and TimeoutListNPduUdpTx or for
 *                TimeoutListIdent -> TimeoutListDyn(UdpAlive) and TimeoutListUdpAlive).
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_TimeoutList_CheckElements(
  SoAd_TimeoutListEnumType TimeoutList,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) ElementIdxPtr,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) HandleIdxPtr,
  uint32 TimerCounter);

/**********************************************************************************************************************
  SoAd_TimeoutList_RemoveElement()
**********************************************************************************************************************/
/*! \brief        Removes an element from a specific timeout list.
 *  \details      Refer to "Concept for TimeoutList" in SoAd_TimeoutList.c.
 *  \param[in]    TimeoutList   Name of timeout list.
 *                              [range: SOAD_TIMEOUT_LIST_UDP_ALIVE, SOAD_TIMEOUT_LIST_N_PDU]
 *  \param[in]    HandleIdx     Handle index (e.g. socket connection index).
 *                              [range: HandleIdx < SoAd_GetSizeOf<HandleType>(); HandleType: SoCon, NPduUdpTx]
 *  \pre          Timeout list elements identified by parameter "TimeoutList" have to exist (refer to Safe BSW
 *                assumptions for TimeoutListIdent -> TimeoutListDyn(NPduUdpTx) and TimeoutListNPduUdpTx or for
 *                TimeoutListIdent -> TimeoutListDyn(UdpAlive) and TimeoutListUdpAlive).
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_TimeoutList_RemoveElement(
  SoAd_TimeoutListEnumType TimeoutList,
  uint32 HandleIdx);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_TIMEOUT_LIST_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_TimeoutList.h
 *********************************************************************************************************************/
