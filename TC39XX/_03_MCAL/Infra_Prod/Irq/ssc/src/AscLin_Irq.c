/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2020)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME     : Irq.c                                                      **
**                                                                            **
**  VERSION      : 6.0.0                                                      **
**                                                                            **
**  DATE         : 2020-07-02                                                 **
**                                                                            **
**  VARIANT      : Variant PC                                                 **
**                                                                            **
**  PLATFORM     : Infineon AURIX2G                                           **
**                                                                            **
**  AUTHOR       : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**  VENDOR       : Infineon Technologies                                      **
**                                                                            **
**  DESCRIPTION  : Irq Driver source file                                     **
**                                                                            **
**  SPECIFICATION(S) : na                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : yes                                              **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Inclusion of Tasking sfr file */
#include "IfxSrc_reg.h"

/*Include Irq Module header file*/
#include "Os.h"
#include "Irq.h"

#include "Uart.h"


#if IRQ_ASCLIN0_TX_TOS != IRQ_TOS_DMA
#if((IRQ_ASCLIN0_TX_PRIO > 0) || (IRQ_ASCLIN0_TX_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN0_TX_PRIO > 0) && (IRQ_ASCLIN0_TX_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN0TX_ISR, 0, IRQ_ASCLIN0_TX_PRIO)
#elif IRQ_ASCLIN0_TX_CAT == IRQ_CAT2
ISR(ASCLIN0TX_ISR)
#endif
{
    // ENABLE();
    /* call uart Interrupt function */
    Uart_IsrTransmit(0);
}
#endif
#endif

#if IRQ_ASCLIN0_ERR_TOS != IRQ_TOS_DMA
#if((IRQ_ASCLIN0_ERR_PRIO > 0) || (IRQ_ASCLIN0_ERR_CAT == IRQ_CAT2))
#if((IRQ_ASCLIN0_ERR_PRIO > 0) && (IRQ_ASCLIN0_ERR_CAT == IRQ_CAT1))
IFX_INTERRUPT(ASCLIN0ERR_ISR, 0, IRQ_ASCLIN0_ERR_PRIO)
#elif IRQ_ASCLIN0_ERR_CAT == IRQ_CAT2
ISR(ASCLIN0ERR_ISR)
#endif
{
    // ENABLE();
    /* call uart Interrupt function */
    Uart_IsrError(0);
}
#endif
#endif