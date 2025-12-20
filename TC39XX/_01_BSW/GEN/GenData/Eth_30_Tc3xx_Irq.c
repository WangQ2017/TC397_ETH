/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: Eth_30_Tc3xx
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Eth_30_Tc3xx_Irq.c
 *   Generation Time: 2025-12-20 10:36:03
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */

#define ETH_30_TC3XX_IRQ_SOURCE

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_IrqHandler_Int.h"
#include "Os.h"

/**********************************************************************************************************************
 *  LOCAL MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  RAM VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  ROM VARIABLES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine
 **********************************************************************************************************************/
/*! \brief       Handles a interrupt related to the EthCtrlConfig_MAIN Ethernet controller
 *  \details     Function processes the interrupt event handlers and - if configured - pre- and post-ISR-User-Functions.
 *               Following interrupt events of the controller are processed:
 *               - Pre-ISR-User-Function: not configured
 *               - Ethernet Tx interrupt queue 0: Eth_30_Tc3xx_IrqHdlrQ0Tx()
 *               - Post-ISR-User-Function: not configured
 *  \context     ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 **********************************************************************************************************************/
ISR( EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine ) /* PRQA S 3408 */ /* MD_Eth_30_Tc3xx_3408 */
{
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(EthConf_EthCtrlConfig_EthCtrlConfig_MAIN);
  uint8 isrIdx       = 0u;
  Eth_30_Tc3xx_ProcessIsr(localCtrlIdx, isrIdx);
} /* EthIsr_EthCtrlConfig_MAIN_EthInterruptServiceRoutine() */


#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* sub-module specific MISRA deviations:
 MD_Eth_30_Tc3xx_3408
      Reason:     Interrupt service routines must not have external linkage. Os will declare them as soon as they
                  are configured in Os.
      Risk:       Compiler/linker warnings/errors could occur.
      Prevention: Check if compiler/linker warnings/errors occur and derive actions dependent on these.
 */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Irq.c
 *********************************************************************************************************************/


