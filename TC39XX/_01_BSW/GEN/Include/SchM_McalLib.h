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
 *            Module: vBRS
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ..\Include\SchM_McalLib.h
 *   Generation Time: 2025-01-25 21:08:51
 *           Project: TC387_DEMO - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Please note:
 *    The demo and example programs only show special aspects of the software. With regard to the fact
 *    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
 *    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
 *********************************************************************************************************************/

#ifndef SCHM_MCALLIB_H
# define SCHM_MCALLIB_H

# include "Os.h"

# define SchM_Enter_McalLib_PeripheralEndInit() SuspendAllInterrupts()
# define SchM_Exit_McalLib_PeripheralEndInit() ResumeAllInterrupts()

# define SchM_Enter_McalLib_SafetyEndInit() SuspendAllInterrupts()
# define SchM_Exit_McalLib_SafetyEndInit() ResumeAllInterrupts()

# define SchM_Enter_McalLib_CpuEndInit() SuspendAllInterrupts()
# define SchM_Exit_McalLib_CpuEndInit() ResumeAllInterrupts()

# define SchM_Enter_McalLib_StmTimerResolution() SuspendAllInterrupts()
# define SchM_Exit_McalLib_StmTimerResolution() ResumeAllInterrupts()

#endif /* SCHM_MCALLIB_H */
