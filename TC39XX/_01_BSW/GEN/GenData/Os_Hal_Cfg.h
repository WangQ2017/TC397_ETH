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
 *              File: Os_Hal_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

#ifndef OS_HAL_CFG_H
# define OS_HAL_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! HAL configuration major version identification. */
# define OS_CFG_HAL_MAJOR_VERSION                (2u)

/*! HAL configuration minor version identification. */
# define OS_CFG_HAL_MINOR_VERSION                (30u)

/* ISR core and level definitions */
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE0_CORE      (0)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE0_LEVEL     (255)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE1_CORE      (1)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE1_LEVEL     (255)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE2_CORE      (2)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE2_LEVEL     (255)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE3_CORE      (3)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE3_LEVEL     (255)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE4_CORE      (4)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE4_LEVEL     (255)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE5_CORE      (6)
# define OS_ISR_COUNTERISR_SYSTEMTIMER_OSCORE5_LEVEL     (255)
# define OS_ISR_ETHISR_ETHCTRLCONFIG_ETHINTERRUPTSERVICEROUTINE_CORE      (0)
# define OS_ISR_ETHISR_ETHCTRLCONFIG_ETHINTERRUPTSERVICEROUTINE_LEVEL     (50)
# define OS_ISR_XSIGNALISR_OSCORE0_CORE      (0)
# define OS_ISR_XSIGNALISR_OSCORE0_LEVEL     (1)
# define OS_ISR_XSIGNALISR_OSCORE1_CORE      (1)
# define OS_ISR_XSIGNALISR_OSCORE1_LEVEL     (1)
# define OS_ISR_XSIGNALISR_OSCORE2_CORE      (2)
# define OS_ISR_XSIGNALISR_OSCORE2_LEVEL     (1)
# define OS_ISR_XSIGNALISR_OSCORE3_CORE      (3)
# define OS_ISR_XSIGNALISR_OSCORE3_LEVEL     (1)
# define OS_ISR_XSIGNALISR_OSCORE4_CORE      (4)
# define OS_ISR_XSIGNALISR_OSCORE4_LEVEL     (1)
# define OS_ISR_XSIGNALISR_OSCORE5_CORE      (6)
# define OS_ISR_XSIGNALISR_OSCORE5_LEVEL     (1)

/* Hardware counter timing macros */

/* Counter timing macros and constants: SystemTimer_OsCore0 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore0     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore0            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore0        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore0        (10uL)

/* OSEK compatibility for the system timer. */
# define OSMAXALLOWEDVALUE     (OSMAXALLOWEDVALUE_SystemTimer_OsCore0)
# define OSMINCYCLE            (OSMINCYCLE_SystemTimer_OsCore0)
# define OSTICKSPERBASE        (OSTICKSPERBASE_SystemTimer_OsCore0)
# define OSTICKDURATION        (OSTICKDURATION_SystemTimer_OsCore0)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore0(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore0(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore0(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore0(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore0 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore0(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_OsCore1 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore1     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore1            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore1        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore1        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore1(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore1(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore1(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore1(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore1 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore1(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_OsCore2 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore2     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore2            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore2        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore2        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore2(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore2(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore2(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore2(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore2 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore2(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_OsCore3 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore3     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore3            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore3        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore3        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore3(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore3(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore3(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore3(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore3 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore3(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_OsCore4 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore4     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore4            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore4        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore4        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore4(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore4(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore4(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore4(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore4 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore4(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */


/* Counter timing macros and constants: SystemTimer_OsCore5 */
# define OSMAXALLOWEDVALUE_SystemTimer_OsCore5     (1073741823uL) /* 0x3FFFFFFFuL */
# define OSMINCYCLE_SystemTimer_OsCore5            (1uL)
# define OSTICKSPERBASE_SystemTimer_OsCore5        (1uL)
# define OSTICKDURATION_SystemTimer_OsCore5        (10uL)

/*! Macro OS_NS2TICKS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_NS2TICKS_SystemTimer_OsCore5(x)     ( (TickType) (((((uint32)(x)) * 1) + 5) / 10) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2NS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2NS_SystemTimer_OsCore5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 10) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_US2TICKS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_US2TICKS_SystemTimer_OsCore5(x)     ( (TickType) (((((uint32)(x)) * 100) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2US_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2US_SystemTimer_OsCore5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50) / 100) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_MS2TICKS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_MS2TICKS_SystemTimer_OsCore5(x)     ( (TickType) (((((uint32)(x)) * 100000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2MS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2MS_SystemTimer_OsCore5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000) / 100000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */

/*! Macro OS_SEC2TICKS_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_SEC2TICKS_SystemTimer_OsCore5(x)     ( (TickType) (((((uint32)(x)) * 100000000) + 0) / 1) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
/*! Macro OS_TICKS2SEC_SystemTimer_OsCore5 was approximated with a deviation of 0.0ppm. */
# define OS_TICKS2SEC_SystemTimer_OsCore5(x)     ( (PhysicalTimeType) (((((uint32)(x)) * 1) + 50000000) / 100000000) ) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */




/* CAT0 and CAT1 ISR core and level definitions */



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_HAL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Cfg.h
 *********************************************************************************************************************/
