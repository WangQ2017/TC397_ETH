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
 *              File: Os_Isr_Lcfg.c
 *   Generation Time: 2025-08-29 14:51:59
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/* PRQA S 0777, 0779, 0828 EOF */ /* MD_MSR_Rule5.1, MD_MSR_Rule5.2, MD_MSR_Dir1.1 */

#define OS_ISR_LCFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/* AUTOSAR includes */
#include "Std_Types.h"

/* Os module declarations */
#include "Os_Isr_Lcfg.h"
#include "Os_Isr.h"

/* Os kernel module dependencies */
#include "Os_AccessCheck_Lcfg.h"
#include "Os_Application_Lcfg.h"
#include "Os_Common.h"
#include "Os_Core_Lcfg.h"
#include "Os_Counter_Lcfg.h"
#include "Os_MemoryProtection_Lcfg.h"
#include "Os_Stack_Lcfg.h"
#include "Os_Thread.h"
#include "Os_Timer.h"
#include "Os_TimingProtection_Lcfg.h"
#include "Os_Trace_Lcfg.h"
#include "Os_XSignal_Lcfg.h"
#include "Os_XSignal.h"

/* Os hal dependencies */
#include "Os_Hal_Context_Lcfg.h"
#include "Os_Hal_Interrupt_Lcfg.h"


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

#define OS_START_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore0 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore0_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore0 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore0_Dyn;

#define OS_STOP_SEC_CORE0_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore1 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore1_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore1 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore1_Dyn;

#define OS_STOP_SEC_CORE1_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore2 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore2_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore2 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore2_Dyn;

#define OS_STOP_SEC_CORE2_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore3 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore3_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore3 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore3_Dyn;

#define OS_STOP_SEC_CORE3_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore4 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore4_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore4 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore4_Dyn;

#define OS_STOP_SEC_CORE4_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Dynamic ISR data: CounterIsr_SystemTimer_OsCore5 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_CounterIsr_SystemTimer_OsCore5_Dyn;

/*! Dynamic ISR data: XSignalIsr_OsCore5 */
OS_LOCAL VAR(Os_IsrType, OS_VAR_NOINIT) OsCfg_Isr_XSignalIsr_OsCore5_Dyn;

#define OS_STOP_SEC_CORE5_VAR_NOINIT_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT DATA
 *********************************************************************************************************************/

#define OS_START_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore0 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore0_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore0,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore0,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore0 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore0_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore0_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore0,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore0)
};
/*! ISR configuration data: XSignalIsr_OsCore0 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore0,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore0,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore0 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore0,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore0_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore0_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore0_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore0,
    /* .Core                  = */ &OsCfg_Core_OsCore0,
    /* .IntApiState           = */ &OsCfg_Core_OsCore0_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore0_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore0,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore0_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore0_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE0_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore0
}
;
#define OS_STOP_SEC_CORE0_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore1 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore1_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore1,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore1,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore1 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore1_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore1,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore1)
};
/*! ISR configuration data: XSignalIsr_OsCore1 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore1,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore1,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore1 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore1,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore1_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore1_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore1_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore1,
    /* .Core                  = */ &OsCfg_Core_OsCore1,
    /* .IntApiState           = */ &OsCfg_Core_OsCore1_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore1_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore1,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore1_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore1_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE1_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore1
}
;
#define OS_STOP_SEC_CORE1_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore2 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore2_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore2,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore2,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore2 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore2_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore2_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore2,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore2)
};
/*! ISR configuration data: XSignalIsr_OsCore2 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore2,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore2,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore2 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore2,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore2_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore2_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore2_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore2,
    /* .Core                  = */ &OsCfg_Core_OsCore2,
    /* .IntApiState           = */ &OsCfg_Core_OsCore2_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore2_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore2,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore2_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore2_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE2_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore2
}
;
#define OS_STOP_SEC_CORE2_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore3 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore3_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore3,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore3,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore3 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore3_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore3_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore3,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore3)
};
/*! ISR configuration data: XSignalIsr_OsCore3 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore3_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore3,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore3,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore3 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore3,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore3_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore3_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore3_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore3,
    /* .Core                  = */ &OsCfg_Core_OsCore3,
    /* .IntApiState           = */ &OsCfg_Core_OsCore3_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore3_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore3,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore3_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore3_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE3_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore3
}
;
#define OS_STOP_SEC_CORE3_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore4 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore4_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore4,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore4,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore4 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore4_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore4_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore4,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore4)
};
/*! ISR configuration data: XSignalIsr_OsCore4 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore4_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore4,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore4,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore4 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore4,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore4_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore4_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore4_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore4,
    /* .Core                  = */ &OsCfg_Core_OsCore4,
    /* .IntApiState           = */ &OsCfg_Core_OsCore4_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore4_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore4,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore4_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore4_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE4_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore4
}
;
#define OS_STOP_SEC_CORE4_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! ISR configuration data: CounterIsr_SystemTimer_OsCore5 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore5_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_CounterIsr_SystemTimer_OsCore5,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_CounterIsr_SystemTimer_OsCore5,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_TimerIsrConfigType, OS_CONST) OsCfg_Isr_CounterIsr_SystemTimer_OsCore5 =
{
  /* .Isr     = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_CounterIsr_SystemTimer_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore5_Isr_Level2_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_CounterIsr_SystemTimer_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_CounterIsr_SystemTimer_OsCore5_HwConfig,
  /* .IsrId                     = */ CounterIsr_SystemTimer_OsCore5,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .Counter = */ OS_COUNTER_CASTCONFIG_TIMERHRT_2_COUNTER(OsCfg_Counter_SystemTimer_OsCore5)
};
/*! ISR configuration data: XSignalIsr_OsCore5 */
CONST(Os_IsrHwConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore5_HwConfig =
{
  /* .HwConfig                  = */ &OsCfg_Hal_IntIsr_XSignalIsr_OsCore5,
  /* .MapConfig                 = */ &OsCfg_Hal_IntIsrMap_XSignalIsr_OsCore5,
  /* .IsMapped                  = */ FALSE,
  /* .IsPostActionRequired      = */ FALSE
}
;  
CONST(Os_XSigIsrConfigType, OS_CONST) OsCfg_Isr_XSignalIsr_OsCore5 =
{
  /* .IsrCfg        = */
  {
  /* .Thread   = */
  {
    /* .ContextConfig         = */ &OsCfg_Hal_Context_XSignalIsr_OsCore5,
    /* .Context               = */ &OsCfg_Hal_Context_OsCore5_Isr_Level1_Dyn,
    /* .Stack                 = */ &OsCfg_Stack_OsCore5_Isr_Core,
    /* .Dyn                   = */ OS_ISR_CASTDYN_ISR_2_THREAD(OsCfg_Isr_XSignalIsr_OsCore5_Dyn),
    /* .OwnerApplication      = */ &OsCfg_App_SystemApplication_OsCore5,
    /* .Core                  = */ &OsCfg_Core_OsCore5,
    /* .IntApiState           = */ &OsCfg_Core_OsCore5_Dyn.IntApiState,
    /* .TimeProtConfig        = */ NULL_PTR,
    /* .MpAccessRightsInitial = */ NULL_PTR,
    /* .AccessRights          = */ &OsCfg_AccessCheck_NoAccess,
    /* .Trace                 = */ NULL_PTR,
    /* .FpuContext            = */ NULL_PTR,
    /* .InitialCallContext    = */ OS_CALLCONTEXT_ISR2,
    /* .PreThreadHook         = */ NULL_PTR,
    /* .InitDuringStartUp     = */ FALSE,
    /* .UsesFpu               = */ FALSE
  },
  /* .SourceConfig              = */ &OsCfg_Isr_XSignalIsr_OsCore5_HwConfig,
  /* .IsrId                     = */ XSignalIsr_OsCore5,
  /* .IsEnabledOnInitialization = */ FALSE
}
,
  /* .FunctionTable = */ &OsCfg_Isr_XSignalIsr_OsCore5_FuncTable,
  /* .RecvPortRefs  = */ OsCfg_Isr_XSignalIsr_OsCore5_PortRefs,
  /* .RecvPortCount = */ (Os_ObjIdxType)OS_CFG_NUM_ISR_XSIGNALISR_OSCORE5_PORTS,
  /* .HwConfig      = */ &OsCfg_Hal_XSig_XSignalIsr_OsCore5
}
;
#define OS_STOP_SEC_CORE5_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap_OsSections.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/*! Object reference table for category 2 ISRs. */
CONSTP2CONST(Os_IsrConfigType, OS_CONST, OS_CONST) OsCfg_IsrRefs[OS_ISRID_COUNT + 1] =  /* PRQA S 4521 */ /* MD_Os_Rule10.1_4521 */
{
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore0),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore1),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore2),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore3),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore4),
  OS_TIMER_CASTCONFIG_TIMERISR_2_ISR(OsCfg_Isr_CounterIsr_SystemTimer_OsCore5),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore0),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore1),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore2),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore3),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore4),
  OS_XSIGNAL_CASTCONFIG_XSIGNALISR_2_ISR(OsCfg_Isr_XSignalIsr_OsCore5),
  NULL_PTR
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
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
 *  END OF FILE: Os_Isr_Lcfg.c
 *********************************************************************************************************************/
