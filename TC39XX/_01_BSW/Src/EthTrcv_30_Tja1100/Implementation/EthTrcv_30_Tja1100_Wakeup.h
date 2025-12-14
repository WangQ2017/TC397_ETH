/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  EthTrcv_30_Tja1100_Wakeup.h
 *        \brief  Ethernet transceiver driver header file for wake-up related API
 *
 *      \details  Module header providing access to AUTOSAR APIs of the Ethernet transceiver driver
 *
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_TJA1100_WAKEUP_H)
# define ETHTRCV_30_TJA1100_WAKEUP_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_IntDef.h"
# if ( ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE )
#  include "EcuM.h"
#  include "Icu.h"
# endif
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_SID_SET_TRANSCEIVER_WAKEUP_MODE           (0x0DU) /*!< Service ID: EthTrcv_30_Tja1100_SetTransceiverWakeupMode() */
# define ETHTRCV_30_TJA1100_SID_GET_TRANSCEIVER_WAKEUP_MODE           (0x0EU) /*!< Service ID: EthTrcv_30_Tja1100_GetTransceiverWakeupMode() */
# define ETHTRCV_30_TJA1100_SID_CHECK_WAKEUP                          (0x0FU) /*!< Service ID: EthTrcv_30_Tja1100_CheckWakeup() */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# if ( ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetTransceiverWakeupMode
 *********************************************************************************************************************/
/*! \brief       Enable/disable transceiver wake-up or clear wake-up reason
 *  \details     This function allows to enable or disable the transceiver's wake-up feature or to clear any occurred
 *               wake-up reason.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver
 *  \param[in]   TrcvWakeupMode  Operation that shall be performed:
 *                               ETHTRCV_WUM_DISABLE - disable the transceiver wake-up
 *                               ETHTRCV_WUM_ENABLE - enable the transceiver wake-up
 *                               ETHTRCV_WUM_CLEAR - clear wake-up reason
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTransceiverWakeupMode(
    uint8 TrcvIdx,
    EthTrcv_WakeupModeType TrcvWakeupMode);

# if(ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetTransceiverWakeupMode
 *********************************************************************************************************************/
/*! \brief       Gets the current wake-up mode
 *  \details     This function allows to retrieve if the transceiver wake-up is enabled or disabled.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver
 *  \param[out]  TrcvWakeupMode  Pointer to the memory where the transceivers current wake-up mode is stored:
 *                               ETHTRCV_WUM_DISABLE - Transceiver wake-up disabled
 *                               ETHTRCV_WUM_ENABLE - Transceiver wake-up enabled
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTransceiverWakeupMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvWakeupModePtr);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_CheckWakeup
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
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_CheckWakeup(
          uint8  TrcvIdx);
# endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif /* ETHTRCV_30_TJA1100_WAKEUP_H */
