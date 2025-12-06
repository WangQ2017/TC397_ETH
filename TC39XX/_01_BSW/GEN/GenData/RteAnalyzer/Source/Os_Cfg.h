/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Os_Cfg.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Os definitions
 *********************************************************************************************************************/

#ifndef _OS_CFG_H_
# define _OS_CFG_H_

/* Os definitions */

/* Tasks */
# define OsTask_Asw_OsCore0 (0U)
# define OsTask_Asw_OsCore1 (1U)
# define OsTask_Asw_OsCore2 (2U)
# define OsTask_Asw_OsCore3 (3U)
# define OsTask_Asw_OsCore4 (4U)
# define OsTask_Asw_OsCore5 (5U)
# define OsTask_Bsw_OsCore0 (6U)
# define OsTask_Bsw_OsCore1 (7U)
# define OsTask_Bsw_OsCore2 (8U)
# define OsTask_Bsw_OsCore3 (9U)
# define OsTask_Bsw_OsCore4 (10U)
# define OsTask_Bsw_OsCore5 (11U)
# define OsTask_Init_OsCore0 (12U)
# define OsTask_Init_OsCore1 (13U)
# define OsTask_Init_OsCore2 (14U)
# define OsTask_Init_OsCore3 (15U)
# define OsTask_Init_OsCore4 (16U)
# define OsTask_Init_OsCore5 (17U)
# define OsTask_lock_2ms (18U)
# define OsTask_window_2ms (19U)

/* Counters */
# define SystemTimer_OsCore0 (0U)
# define SystemTimer_OsCore1 (1U)
# define SystemTimer_OsCore2 (2U)
# define SystemTimer_OsCore3 (3U)
# define SystemTimer_OsCore4 (4U)
# define SystemTimer_OsCore5 (5U)

/* Alarms */
# define Rte_Al_TE_Cdd_Core0_Runnable_20 (0U)
# define Rte_Al_TE_Cdd_Core0_Runnable_5ms (1U)
# define Rte_Al_TE_Cdd_nm_Cdd_Nm_Runnable10ms (2U)
# define Rte_Al_TE_Cdd_Core1_Cdd_Core1_Runnable10ms (3U)
# define Rte_Al_TE_Cdd_Core2_Cdd_Core2_Runnable10ms (4U)
# define Rte_Al_TE_Cdd_Core3_Cdd_Core3_Runnable10ms (5U)
# define Rte_Al_TE_Cdd_Core4_Cdd_Core4_Runnable10ms (6U)
# define Rte_Al_TE_Cdd_Core5_Cdd_Core5_Runnable10ms (7U)
# define Rte_Al_TE2_OsTask_Bsw_OsCore0_0_10ms (8U)
# define Rte_Al_TE2_EcuM_EcuM_MainFunction (9U)
# define Rte_Al_TE3_EcuM_EcuM_MainFunction (10U)
# define Rte_Al_TE4_EcuM_EcuM_MainFunction (11U)
# define Rte_Al_TE5_EcuM_EcuM_MainFunction (12U)
# define Rte_Al_TE6_EcuM_EcuM_MainFunction (13U)
# define Rte_Al_TE_swc_lock_Runnable_2ms (14U)
# define Rte_Al_TE_window_core1_Runnable_windows_2ms (15U)

/* Events */
# define Rte_Ev_Run_Cdd_Core0_Runnable_20 (0x04U)
# define Rte_Ev_Run_Cdd_Core0_Runnable_5ms (0x02U)
# define Rte_Ev_Run_Cdd_nm_Cdd_Nm_Runnable10ms (0x01U)

/* Spinlocks */

/* Resources */

/* ScheduleTables */

/* Cores */
# define OS_CORE_ID_0 (0U)
# define OS_CORE_ID_1 (1U)
# define OS_CORE_ID_2 (2U)
# define OS_CORE_ID_3 (3U)
# define OS_CORE_ID_4 (4U)
# define OS_CORE_ID_5 (5U)
# include "usrostyp.h"

/* Trusted Functions */


#endif /* _OS_CFG_H_ */
