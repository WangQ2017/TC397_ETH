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
 *              File: ..\Include\SchM_BswM.h
 *   Generation Time: 2025-01-25 21:22:47
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

#ifndef SCHM_BSWM_H
# define SCHM_BSWM_H

# include "Os.h"

# ifdef __cplusplus
extern "C" {
# endif  /* __cplusplus */

# include "Std_Types.h"

# define BSWM_START_SEC_CODE
# include "MemMap.h"

FUNC(void, BSWM_CODE) BswM_MainFunction_OsApplication_OsCore0(void);
FUNC(void, BSWM_CODE) BswM_MainFunction_OsApplication_OsCore1(void);
FUNC(void, BSWM_CODE) BswM_MainFunction_OsApplication_OsCore2(void);
FUNC(void, BSWM_CODE) BswM_MainFunction_OsApplication_OsCore3(void);

# define BSWM_STOP_SEC_CODE
# include "MemMap.h"

# ifdef __cplusplus
} /* extern "C" */
# endif  /* __cplusplus */

# define SchM_Enter_BswM_BSWM_EXCLUSIVE_AREA_0() SuspendAllInterrupts()
# define SchM_Exit_BswM_BSWM_EXCLUSIVE_AREA_0() ResumeAllInterrupts()

#endif /* SCHM_BSWM_H */
