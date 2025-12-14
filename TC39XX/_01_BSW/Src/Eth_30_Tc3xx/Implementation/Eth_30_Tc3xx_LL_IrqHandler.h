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
/*!        \file  Eth_30_Tc3xx_LL_IrqHandler.h
 *        \brief  Header of lower layer part of the interrupt handler
 *
 *      \details  Lower layer interrupt handler header file.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_LL_IRQ_HANDLER_H)
# define ETH_30_TC3XX_LL_IRQ_HANDLER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Tx()
 **********************************************************************************************************************/
/*! \brief       Handles the transmit interrupt of queue 0
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Tx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ0Rx()
 **********************************************************************************************************************/
/*! \brief       Handles the receive interrupt of queue 0
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ0Rx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Tx()
 **********************************************************************************************************************/
/*! \brief       Handles the transmit interrupt of queue 1
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Tx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ1Rx()
 **********************************************************************************************************************/
/*! \brief       Handles the receive interrupt of queue 1
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ1Rx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Tx()
 **********************************************************************************************************************/
/*! \brief       Handles the transmit interrupt of queue 2
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Tx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ2Rx()
 **********************************************************************************************************************/
/*! \brief       Handles the receive interrupt of queue 2
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ2Rx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Tx()
 **********************************************************************************************************************/
/*! \brief       Handles the transmit interrupt of queue 3
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Tx(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_IrqHdlrQ3Rx()
 **********************************************************************************************************************/
/*! \brief       Handles the receive interrupt of queue 3
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of Eth controller
 *  \context     ISR1|ISR2
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IrqHdlrQ3Rx(
  uint8 ctrlIdx);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_IRQ_HANDLER_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_IrqHandler.h
 *********************************************************************************************************************/
