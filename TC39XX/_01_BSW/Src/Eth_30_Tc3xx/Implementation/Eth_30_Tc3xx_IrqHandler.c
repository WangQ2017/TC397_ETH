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
/*!        \file  Eth_30_Tc3xx_IrqHandler.c
 *        \brief  Interrupt handling sub-module of driver
 *
 *      \details  -
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

/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETH_30_TC3XX_IRQ_HANDLER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_IrqHandler_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
# define ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE                         LOCAL_INLINE
#endif /* ETH_30_TC3XX_IRQ_HANDLER_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOAL FUNCTION DEFINITIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ProcessIsr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProcessIsr(
  uint8 ctrlIdx,
  uint8 isrIdx)
{
  Eth_30_Tc3xx_IsrIrqEventFuncsIterType      irqEventIdx;
  Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType isrInfosIdx = Eth_30_Tc3xx_GetIsrInfosStartIdxOfEthCtrl(ctrlIdx) + isrIdx;

  /* #10 Iterate over all interrupt service routine info structures containing the configured IRQ-handlers and
   *     optional Pre-/Post-ISR user functions of an Ethernet controller configuration */
  for (irqEventIdx = Eth_30_Tc3xx_GetIsrIrqEventFuncsStartIdxOfIsrInfos(isrInfosIdx);
       irqEventIdx < Eth_30_Tc3xx_GetIsrIrqEventFuncsEndIdxOfIsrInfos(isrInfosIdx);
       irqEventIdx++)
  {
    Eth_30_Tc3xx_IrqEventFctPtrType isrIrqEventFuncsPtr = Eth_30_Tc3xx_GetIsrIrqEventFuncs(irqEventIdx);
    /* #110 If the currently checked function is not a NULL_PTR and thus available */
    if (isrIrqEventFuncsPtr != NULL_PTR)
    {
      /* #1110 Call the currently checked Pre-/Post-ISR-UserFunction or IRQ-handler */
      isrIrqEventFuncsPtr(ctrlIdx);                                                                                     /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03 */
    }
  }
} /* Eth_30_Tc3xx_ProcessIsr() */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_IrqHandler.c
 *********************************************************************************************************************/
