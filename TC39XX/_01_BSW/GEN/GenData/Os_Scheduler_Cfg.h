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
 *              File: Os_Scheduler_Cfg.h
 *   Generation Time: 2025-09-02 11:14:44
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_SCHEDULER_CFG_H
# define OS_SCHEDULER_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Defines whether round robin scheduling is enabled (STD_ON) or not (STD_OFF). */
# define OS_CFG_SCHEDULE_ROUND_ROB_ENABLED       (STD_OFF)

/*! Defines the number of all task queues. */
# define OS_CFG_NUM_TASKQUEUES                   (22u)

/* Number of task queue activation slots: OsCore0 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE0_SLOTS     (3u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE0_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE0_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE0_SLOTS     (4u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE0_SLOTS     (4u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE0_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE0_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE0_SLOTS     (2u)

/* Number of task queue activation slots: OsCore1 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE1_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE1_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE1_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE1_SLOTS     (4u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE1_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE1_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE1_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE1_SLOTS     (2u)

/* Number of task queue activation slots: OsCore2 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE2_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE2_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE2_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE2_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE2_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE2_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE2_SLOTS     (2u)

/* Number of task queue activation slots: OsCore3 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE3_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE3_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE3_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE3_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE3_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE3_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE3_SLOTS     (2u)

/* Number of task queue activation slots: OsCore4 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE4_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE4_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE4_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE4_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE4_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE4_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE4_SLOTS     (2u)

/* Number of task queue activation slots: OsCore5 */
# define OS_CFG_NUM_TASKQUEUE0_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE1_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE2_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE3_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE4_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE5_OSCORE5_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE6_OSCORE5_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE7_OSCORE5_SLOTS     (2u)
# define OS_CFG_NUM_TASKQUEUE8_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE9_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE10_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE11_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE12_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE13_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE14_OSCORE5_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE15_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE16_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE17_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE18_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE19_OSCORE5_SLOTS     (1u)
# define OS_CFG_NUM_TASKQUEUE20_OSCORE5_SLOTS     (101u)
# define OS_CFG_NUM_TASKQUEUE21_OSCORE5_SLOTS     (2u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


#endif /* OS_SCHEDULER_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Scheduler_Cfg.h
 *********************************************************************************************************************/
