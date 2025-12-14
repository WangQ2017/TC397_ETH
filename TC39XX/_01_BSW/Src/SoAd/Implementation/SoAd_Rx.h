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
/**        \file  SoAd_Rx.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component Rx.
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

#if !defined (SOAD_RX_H)
# define SOAD_RX_H

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
 *  SoAd_Rx_InitSoCon()
 *********************************************************************************************************************/
/*! \brief        Initializes Rx structs on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx      Socket connection index.
 *                              [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Rx_InitSoCon(
  SoAd_SizeOfSoConType SoConIdx);

 /*********************************************************************************************************************
 *  SoAd_Rx_RxIndication()
 *********************************************************************************************************************/
 /*! \brief       Receives data from socket.
 *  \details      -
 *  \param[in]    SockIdx         Module internal socket index.
 *                                [range: SockIdx < SoAd_GetSizeOfSocket()]
 *  \param[in]    RemoteAddrPtr   Pointer to remote address.
 *                                [Points to one of the following structs depending on configured IP address version of
 *                                parameter SockIdx:
 *                                  - SoAd_SockAddrInetType for IPv4
 *                                  - SoAd_SockAddrInet6Type for IPv6]
 *  \param[in]    BufPtr          Pointer to buffer of received data.
 *  \param[in]    Length          Length of received data.
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different socket indexes, FALSE for same socket index.
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Rx_RxIndication(
  SoAd_SizeOfSocketType SockIdx,
  P2CONST(SoAd_SockAddrType, AUTOMATIC, SOAD_APPL_VAR) RemoteAddrPtr,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_VAR) BufPtr,
  uint16 Length,
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

/**********************************************************************************************************************
 *  SoAd_Rx_TpStartOfReception()
**********************************************************************************************************************/
/*! \brief        Calls StartOfReception to begin a TP session in case PDU header is disabled.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \return       E_OK        Call to StartOfReception succeeded or is not required.
 *  \return       E_NOT_OK    Call to StartOfReception failed.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_TpStartOfReception(
  SoAd_SizeOfSoConType SoConIdx);

/**********************************************************************************************************************
 *  SoAd_Rx_TpCancelReceive()
 *********************************************************************************************************************/
/*! \brief        Requests reception cancellation of a specific TP-PDU.
 *  \details      -
 *  \param[in]    SockRouteDestIdx  Socket route destination index.
 *                                  [range: SockRouteDestIdx < SoAd_GetSizeOfSocketRouteDest()]
 *  \return       E_OK              Receive cancellation request was accepted.
 *  \return       E_NOT_OK          Receive cancellation request was not accepted.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Rx_TpCancelReceive(
  SoAd_SizeOfSocketRouteDestType SockRouteDestIdx);

/**********************************************************************************************************************
 *  SoAd_Rx_TerminateReceive()
**********************************************************************************************************************/
/*! \brief        Terminates active reception on a socket connection.
 *  \details      -
 *  \param[in]    SoConIdx    Socket connection index.
 *                            [range: SoConIdx < SoAd_GetSizeOfSoCon()]
 *  \param[in]    NormalClose Indicates if termination is initiated by close request.
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Rx_TerminateReceive(
  SoAd_SizeOfSoConType SoConIdx,
  boolean NormalClose);

/**********************************************************************************************************************
 *  SoAd_Rx_HandleReception()
**********************************************************************************************************************/
/*! \brief        Handles reception in main function context.
 *  \details      -
 *  \param[out]   ErrorIdPtr      Pointer to error identifier (set if error occurred).
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
**********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Rx_HandleReception(
  P2VAR(uint8, AUTOMATIC, SOAD_APPL_DATA) ErrorIdPtr);

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* SOAD_RX_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Rx.h
 *********************************************************************************************************************/
