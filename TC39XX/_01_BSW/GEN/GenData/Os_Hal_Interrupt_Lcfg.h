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
 *              File: Os_Hal_Interrupt_Lcfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


                                                                                                                        /* PRQA S 0388  EOF */ /* MD_MSR_Dir1.1 */

#ifndef OS_HAL_INTERRUPT_LCFG_H
# define OS_HAL_INTERRUPT_LCFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_Interrupt_Cfg.h"
# include "Os_Hal_Interrupt_Types.h"

/* Os kernel module dependencies */
# include "Os_Interrupt_Types.h"

/* Os hal dependencies */
# include "Os_Hal_Core_Types.h"


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

# define OS_START_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore0 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore0;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore0;

/*! HAL ISR configuration data: EthIsr_EthCtrlConfig_EthInterruptServiceRoutine */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_EthIsr_EthCtrlConfig_EthInterruptServiceRoutine;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_EthIsr_EthCtrlConfig_EthInterruptServiceRoutine;

/*! HAL ISR configuration data: XSignalIsr_OsCore0 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore0;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore0;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore0 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore0;

# define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore1 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore1;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore1;

/*! HAL ISR configuration data: XSignalIsr_OsCore1 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore1;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore1;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore1 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore1;

# define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore2 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore2;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore2;

/*! HAL ISR configuration data: XSignalIsr_OsCore2 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore2;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore2;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore2 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore2;

# define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore3 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore3;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore3;

/*! HAL ISR configuration data: XSignalIsr_OsCore3 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore3;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore3;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore3 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore3;

# define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore4 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore4;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore4;

/*! HAL ISR configuration data: XSignalIsr_OsCore4 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore4;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore4;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore4 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore4;

# define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


# define OS_START_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore5 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore5;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore5;

/*! HAL ISR configuration data: XSignalIsr_OsCore5 */
extern CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore5;
extern CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore5;

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore5 */
extern CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore5;

# define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
# include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


#endif /* OS_HAL_INTERRUPT_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt_Lcfg.h
 *********************************************************************************************************************/
