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
 *              File: Os_Lcfg.h
 *   Generation Time: 2025-09-02 09:20:49
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef OS_LCFG_H
# define OS_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Cfg.h"
# include "Os_Types.h"
# include "Os_Types_Lcfg.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
# include "Os_Hal_Lcfg.h"

/* User file includes */


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define OS_START_SEC_Default_Init_Task_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CODE) Os_Task_Default_Init_Task(void);

# define OS_STOP_SEC_Default_Init_Task_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core1()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE1_CODE) Os_Task_Default_Init_Task_Core1(void);

# define OS_STOP_SEC_Default_Init_Task_Core1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core1_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core1_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE1_TRUSTED_CODE) Os_Task_Default_Init_Task_Core1_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Core1_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core2()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE2_CODE) Os_Task_Default_Init_Task_Core2(void);

# define OS_STOP_SEC_Default_Init_Task_Core2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core2_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core2_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE2_TRUSTED_CODE) Os_Task_Default_Init_Task_Core2_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Core2_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core3()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE3_CODE) Os_Task_Default_Init_Task_Core3(void);

# define OS_STOP_SEC_Default_Init_Task_Core3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core3_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core3_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE3_TRUSTED_CODE) Os_Task_Default_Init_Task_Core3_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Core3_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core4()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE4_CODE) Os_Task_Default_Init_Task_Core4(void);

# define OS_STOP_SEC_Default_Init_Task_Core4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core4_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core4_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE4_TRUSTED_CODE) Os_Task_Default_Init_Task_Core4_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Core4_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core6_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core6()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE6_CODE) Os_Task_Default_Init_Task_Core6(void);

# define OS_STOP_SEC_Default_Init_Task_Core6_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Core6_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Core6_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_CORE6_TRUSTED_CODE) Os_Task_Default_Init_Task_Core6_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Core6_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_Default_Init_Task_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  Default_Init_Task_Trusted()
 *********************************************************************************************************************/
extern FUNC(void, OS_DEFAULT_INIT_TASK_TRUSTED_CODE) Os_Task_Default_Init_Task_Trusted(void);

# define OS_STOP_SEC_Default_Init_Task_Trusted_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore0()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE0_CODE) Os_Task_OsTask_Asw_OsCore0(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore1()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE1_CODE) Os_Task_OsTask_Asw_OsCore1(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore2()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE2_CODE) Os_Task_OsTask_Asw_OsCore2(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore3()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE3_CODE) Os_Task_OsTask_Asw_OsCore3(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore4()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE4_CODE) Os_Task_OsTask_Asw_OsCore4(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Asw_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Asw_OsCore5()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_ASW_OSCORE5_CODE) Os_Task_OsTask_Asw_OsCore5(void);

# define OS_STOP_SEC_OsTask_Asw_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore0()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE0_CODE) Os_Task_OsTask_Bsw_OsCore0(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore1()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE1_CODE) Os_Task_OsTask_Bsw_OsCore1(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore2()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE2_CODE) Os_Task_OsTask_Bsw_OsCore2(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore3()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE3_CODE) Os_Task_OsTask_Bsw_OsCore3(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore4()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE4_CODE) Os_Task_OsTask_Bsw_OsCore4(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Bsw_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Bsw_OsCore5()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_BSW_OSCORE5_CODE) Os_Task_OsTask_Bsw_OsCore5(void);

# define OS_STOP_SEC_OsTask_Bsw_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore0()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE0_CODE) Os_Task_OsTask_Init_OsCore0(void);

# define OS_STOP_SEC_OsTask_Init_OsCore0_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore1()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE1_CODE) Os_Task_OsTask_Init_OsCore1(void);

# define OS_STOP_SEC_OsTask_Init_OsCore1_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore2()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE2_CODE) Os_Task_OsTask_Init_OsCore2(void);

# define OS_STOP_SEC_OsTask_Init_OsCore2_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore3()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE3_CODE) Os_Task_OsTask_Init_OsCore3(void);

# define OS_STOP_SEC_OsTask_Init_OsCore3_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore4()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE4_CODE) Os_Task_OsTask_Init_OsCore4(void);

# define OS_STOP_SEC_OsTask_Init_OsCore4_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_Init_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_Init_OsCore5()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_INIT_OSCORE5_CODE) Os_Task_OsTask_Init_OsCore5(void);

# define OS_STOP_SEC_OsTask_Init_OsCore5_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_lock_2ms_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_lock_2ms()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_LOCK_2MS_CODE) Os_Task_OsTask_lock_2ms(void);

# define OS_STOP_SEC_OsTask_lock_2ms_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_OsTask_window_2ms_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  OsTask_window_2ms()
 *********************************************************************************************************************/
extern FUNC(void, OS_OSTASK_WINDOW_2MS_CODE) Os_Task_OsTask_window_2ms(void);

# define OS_STOP_SEC_OsTask_window_2ms_CODE
# include "Os_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif /* OS_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Lcfg.h
 *********************************************************************************************************************/
