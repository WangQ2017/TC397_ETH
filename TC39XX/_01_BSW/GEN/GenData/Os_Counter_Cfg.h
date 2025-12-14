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
 *            Module: Os
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Os_Counter_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_COUNTER_CFG_H 
# define OS_COUNTER_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether any counter uses SW increment (STD_ON) or not (STD_OFF) */
# define OS_CFG_COUNTER_SW_USED                  (STD_OFF)

/*! Defines whether any counter uses PIT (STD_ON) or not (STD_OFF) */
# define OS_CFG_COUNTER_PIT_USED                 (STD_OFF)

/*! Defines whether any counter uses High Resolution (STD_ON) or not (STD_OFF) */
# define OS_CFG_COUNTER_HRT_USED                 (STD_ON)

/*! Defines whether any counter uses FRT as PIT (STD_ON) or not (STD_OFF) */
# define OS_CFG_COUNTER_PFRT_USED                (STD_OFF)

/*! Number of counter jobs: SystemTimer_OsCore0 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE0_JOBS     (10uL)

/*! Number of counter jobs: SystemTimer_OsCore1 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE1_JOBS     (3uL)

/*! Number of counter jobs: SystemTimer_OsCore2 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE2_JOBS     (2uL)

/*! Number of counter jobs: SystemTimer_OsCore3 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE3_JOBS     (2uL)

/*! Number of counter jobs: SystemTimer_OsCore4 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE4_JOBS     (2uL)

/*! Number of counter jobs: SystemTimer_OsCore5 */
# define OS_CFG_NUM_COUNTER_SYSTEMTIMER_OSCORE5_JOBS     (2uL)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_COUNTER_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Counter_Cfg.h
 *********************************************************************************************************************/
