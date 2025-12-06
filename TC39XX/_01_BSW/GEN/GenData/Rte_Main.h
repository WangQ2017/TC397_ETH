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
 *             File:  Rte_Main.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Lifecycle Header File
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_MAIN_H
# define RTE_MAIN_H

# include "Rte.h"

# define RTE_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* BSW Scheduler Life-Cycle API */
FUNC(void, RTE_CODE) SchM_Init(void);
FUNC(void, RTE_CODE) SchM_Deinit(void);

/* RTE Life-Cycle API */
FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);
FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void);

/* Extended Life-Cycle API */
FUNC(void, RTE_CODE) Rte_InitMemory(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore0(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore1(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore2(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore3(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore4(void);
FUNC(void, RTE_CODE) Rte_InitMemory_OsApplication_OsCore5(void);

# define RTE_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* RTE_MAIN_H */
