/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_TrafficHandling.h
 *        \brief  Traffic handling sub-module header of the Ethernet controller driver
 *
 *      \details  Provides access to the traffic handling related API of the Ethernet controller driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_TRAFFIC_HANDLING_H)
# define ETH_30_TC3XX_TRAFFIC_HANDLING_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"

# if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_SetBandwidthLimit() */
#  define ETH_30_TC3XX_SID_SET_BANDWIDTH_LIMIT                         (0x40u)
/*!< Service ID: Eth_30_Tc3xx_GetBandwidthLimit() */
#  define ETH_30_TC3XX_SID_GET_BANDWIDTH_LIMIT                         (0x41u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief        Reconfigures the bandwidth limit set for a transmission queue.
 *  \details      -
 *  \param[in]    CtrlIdx          Controller Index
 *  \param[in]    QueuePrio        Queue Priority
 *  \param[in]    BandwidthLimit   Bandwidth limit which shall be assigned for the TX queue (in [bits/s])
 *  \return       E_NOT_OK - New bandwidth limit couldn't be set.
 *  \return       E_OK - New bandwidth limit set.
 *  \context      ANY
 *  \reentrant    TRUE for different queue priorities
 *  \synchronous  TRUE
 *  \pre          Ethernet controller is operational in mode ACTIVE
 *  \trace        CREQ-137703
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetBandwidthLimit(
  uint8  CtrlIdx,
  uint8  QueuePrio,
  uint32 BandwidthLimit);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief        Retrieves the currently configured bandwidth limit of a transmission queue.
 *  \details      -
 *  \param[in]    CtrlIdx            Controller Index
 *  \param[in]    QueuePrio          Queue Priority
 *  \param[out]   BandwidthLimitPtr  Pointer to where to store the currently configured bandwidth limit (in [bit/s])
 *  \return       E_NOT_OK - Current bandwidth limit couldn't be retrieved.
 *  \return       E_OK - Current bandwidth limit retrieved.
 *  \context      ANY
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \pre          Ethernet controller is operational in mode ACTIVE
 *  \trace        CREQ-137704
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetBandwidthLimit(
        uint8                         CtrlIdx,
        uint8                         QueuePrio,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) BandwidthLimitPtr);

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */
#endif /* ETH_30_TC3XX_TRAFFIC_HANDLING_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TrafficHandling.h
 *********************************************************************************************************************/
