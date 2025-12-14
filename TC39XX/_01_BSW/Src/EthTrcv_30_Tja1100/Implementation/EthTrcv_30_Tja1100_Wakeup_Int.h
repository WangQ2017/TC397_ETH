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
/*         \file  EthTrcv_30_Tja1100_Wakeup_Int.h
 *        \brief  Ethernet transceiver driver wake-up internal header
 *
 *      \details  Header file containing the private function declarations of the Ethernet Transceiver driver's wake-up
 *                module
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
#if !defined (ETHTRCV_30_TJA1100_WAKEUP_INT_H)
# define ETHTRCV_30_TJA1100_WAKEUP_INT_H
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Lcfg.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# if ( ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE )
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_InspectWakeupReasons()
 **********************************************************************************************************************/
/*! \brief       Performs an inspection for occurred wake-up events according to the configured inspection type
 *  \details     This function performs a wake-up inspection dependent on the configured inspection type and stores the
 *               related AUTOSAR wake-up reasons.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \return      E_NOT_OK      - Wakeup event inspection could be processed successfully.
 *               E_OK          - Wakeup event inspection couldn't be processed successfully.

 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Wake-up enabled
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_InspectWakeupReasons(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReportWakeup()
 **********************************************************************************************************************/
/*! \brief       Reports occured wake-up events to EcuM
 *  \details     This function maps occured AUTOSAR wake-up reasons to the related EcuM wake-up sources and reports them.
 *               After reporting the wake-up reasons will be cleared.
 *  \param[in]   TrcvIdx          Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                                minus one.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Wake-up enabled
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReportWakeup(
    EthTrcv_30_Tja1100_EthTrcvIterType TrcvIdx);
# endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif /* ETHTRCV_30_TJA1100_WAKEUP_INT_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Wakeup_Int.h
 *********************************************************************************************************************/
