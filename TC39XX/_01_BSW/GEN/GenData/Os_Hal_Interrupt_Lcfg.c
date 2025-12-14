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
 *              File: Os_Hal_Interrupt_Lcfg.c
 *   Generation Time: 2025-12-14 21:26:07
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_HAL_INTERRUPT_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Hal_Interrupt_Lcfg.h"
#include "Os_Hal_Interrupt.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Core.h"


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore0 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x300uL,
  /* .CoreAssignment = */ 0
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore0 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: EthIsr_EthCtrlConfig_EthInterruptServiceRoutine */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_EthIsr_EthCtrlConfig_EthInterruptServiceRoutine =
{
  /* .Level          = */ 50,
  /* .Source         = */ 0x588uL,
  /* .CoreAssignment = */ 0
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_EthIsr_EthCtrlConfig_EthInterruptServiceRoutine =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore0 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0x990uL,
  /* .CoreAssignment = */ 0
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore0 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore0 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore0,
};

#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore1 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore1 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x308uL,
  /* .CoreAssignment = */ 2
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore1 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore1 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0x9b0uL,
  /* .CoreAssignment = */ 2
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore1 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore1 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore1,
};

#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore2 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore2 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x310uL,
  /* .CoreAssignment = */ 3
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore2 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore2 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0x9d0uL,
  /* .CoreAssignment = */ 3
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore2 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore2 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore2,
};

#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore3 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore3 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x318uL,
  /* .CoreAssignment = */ 4
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore3 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore3 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore3 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0x9f0uL,
  /* .CoreAssignment = */ 4
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore3 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore3 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore3 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore3,
};

#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore4 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore4 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x320uL,
  /* .CoreAssignment = */ 5
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore4 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore4 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore4 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0xa10uL,
  /* .CoreAssignment = */ 5
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore4 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore4 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore4 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore4,
};

#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! HAL ISR configuration data: CounterIsr_SystemTimer_OsCore5 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore5 =
{
  /* .Level          = */ 100,
  /* .Source         = */ 0x328uL,
  /* .CoreAssignment = */ 6
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore5 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL ISR configuration data: XSignalIsr_OsCore5 */
CONST(Os_Hal_IntIsrConfigType, OS_CONST) OsCfg_Hal_IntIsr_XSignalIsr_OsCore5 =
{
  /* .Level          = */ 1,
  /* .Source         = */ 0xa30uL,
  /* .CoreAssignment = */ 6
};

CONST(Os_Hal_IntIsrMapConfigType, OS_CONST) OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore5 =
{
  /* .Dummy         = */ (uint32)0
};

/*! HAL X-Signal ISR configuration data: XSignalIsr_OsCore5 */
CONST(Os_Hal_XSigInterruptConfigType, OS_CONST) OsCfg_Hal_XSig_XSignalIsr_OsCore5 =
{
  /* .ConfigData  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore5,
};

#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt_Lcfg.c
 *********************************************************************************************************************/
