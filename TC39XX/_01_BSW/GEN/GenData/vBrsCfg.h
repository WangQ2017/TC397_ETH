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
 *              File: .\vBrsCfg.h
 *   Generation Time: 2025-08-29 14:51:59
 *           Project: TC397_BSW - Version 1.0
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

#ifndef _VBRSCFG_H_
#define _VBRSCFG_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#if !defined (BRS_INCLUDED_BY_ASM_FILE)
# include "Std_Types.h"
#endif

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#define BASIC_RUNTIME_SYSTEM_TYPE_MSR4

#define BRS_GENERATED_HW_CONFIG_VERSION 355U

/*******************************************************************************
 Standard BRS configuration
*******************************************************************************/
/* Testsuite support is disabled (#define BRS_ENABLE_TESTSUITE_SUPPORT) */

/* TCC support is disabled (#define BRS_ENABLE_TCC_COMIF_SUPPORT) */

/* LED support is disabled (#define BRS_ENABLE_SUPPORT_LEDS) */

/* Toggle custom pin support is disabled (#define BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN) */

/* Toggle watchdog pin support is disabled (#define BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) */


/*******************************************************************************
 Additional BRS support features
*******************************************************************************/
/* Switch to enable support of SafeContext OS */
/* SafeContext support is disabled (#define BRS_ENABLE_SAFECTXSUPPORT) */

/* Switch to enable support of MultiCore OS */
#define BRS_ENABLE_OS_MULTICORESUPPORT

/* Switches to enable support of FlashBootLoader and to define the FBL Type */
/* FlashBootLoader support is disabled (#define BRS_ENABLE_FBL_SUPPORT) */

/* Switch to enable support of Hardware Security Module (HSM) */
/* HSM support is disabled (#define BRS_ENABLE_HSM_SUPPORT) */

/* Switch to enable support of OS UseCase "Interrupt Only" */
/* OS UseCase "Interrupt Only" is disabled (#define BRS_ENABLE_OS_INTERRUPT_ONLY) */

/*******************************************************************************
 BRS hardware configuration constants
*******************************************************************************/
/* Main Oscillator Clock (MHz) */
#define BRS_OSC_CLK 20

/* Timebase Clock (MHz) */
#define BRS_TIMEBASE_CLOCK 100

/* Peripheral Clock (MHz) */
#define BRS_PERIPH_CLOCK 100

/*******************************************************************************
 BRS software modules
*******************************************************************************/
#define BRS_ENABLE_WATCHDOG

/*******************************************************************************
 Tested Derivative: Infineon Aurix 2G TC39x Family
*******************************************************************************/
#define BRS_DERIVATIVE_TC39x

/*******************************************************************************
 CPU Core
*******************************************************************************/
#define BRS_CPU_CORE_TC162

/*******************************************************************************
 CPU Max Frequency (MHz)
*******************************************************************************/
#define BRS_CPU_MAX_FREQUENCY 300

/*******************************************************************************
 CPU Core Amount (number of cores)
*******************************************************************************/
#define BRS_CPU_CORE_AMOUNT 6

/*******************************************************************************
 Derivative Group
*******************************************************************************/
#define BRS_DERIVATIVE_GROUP_TC3xx

/*******************************************************************************
 Pll Group
*******************************************************************************/
#define BRS_PLL_GROUP_B

/*******************************************************************************
 Port Group
*******************************************************************************/
#define BRS_PORT_GROUP_B

/*******************************************************************************
 Reset Group
*******************************************************************************/
#define BRS_RESET_GROUP_B

/*******************************************************************************
 Watchdog Group
*******************************************************************************/
#define BRS_WATCHDOG_GROUP_B

/*******************************************************************************
 Init Patterns
*******************************************************************************/
#define BRS_INIT_PATTERN_BLOCKS (0x0UL)
#define BRS_INIT_PATTERN_HARDRESET_BLOCKS (0x0UL)
#define BRS_INIT_PATTERN_AREAS (0x0UL)
#define BRS_INIT_PATTERN_HARDRESET_AREAS (0x0UL)

#endif /*_VBRSCFG_H_*/

