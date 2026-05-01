/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2019)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu_PBCfg.c                                          **
**                                                                           **
**  VERSION :  6.0.0                                                         **
**                                                                           **
**  DATE, TIME: 2026-05-01, 21:03:31               !!!IGNORE-LINE!!!         **
**                                                                           **
**  GENERATOR : Build b170330-0431                  !!!IGNORE-LINE!!!        **
**                                                                           **
**  BSW MODULE DECRIPTION : NA                                               **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : FLS configuration generated out of ECU configuration      **
**                   file                                                    **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include Flash Module File */
#include "Fls_17_Dmu.h"
#include "Fls_17_Dmu_ac.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/



/* EVER Notification Function is not configured */

/* PVER Notification Function is not configured */

/* Illegal State Notification function is not configured */

/*******************************************************************************
**                      Global Constant Definitions                          **
*******************************************************************************/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"

/* Fls State Variable structure */

static Fls_17_Dmu_StateType  FlsStateVar;

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_VAR_CLEARED_ASIL_B_LOCAL_UNSPECIFIED
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
#include "Fls_17_Dmu_MemMap.h"

/* MISRA2012_RULE_8_7_JUSTIFICATION: External linkage is needed as it is used 
     in more than one translation unit. */
/* MISRA2012_RULE_8_4_JUSTIFICATION: Defined as per AUTOSAR */

const Fls_17_Dmu_ConfigType Fls_17_Dmu_Config =
{

  /* Fls state variable structure */
  &FlsStateVar,
  
  /* Maximum number of bytes to Read in one cycle */
  /* Fast Mode */
  64U,
  
  /* Normal Mode */
  32U,

  /* Job End Notification */
  NULL_PTR,
  
  /* Job Error Notification */
  NULL_PTR,
  
  /* EVER Notification */
  NULL_PTR,
  
  /* PVER Notification */
  NULL_PTR,
  
  /* Illegal State Notification */
  NULL_PTR,
  
  /*Wait state configuration for Read access and error correction */
  (((uint32)FLS_17_DMU_WAIT_STATE_READACCESS9) |
  ((uint32)FLS_17_DMU_WAIT_STATE_ERRORCORRECTION1 << 16U)) ,
  
  /* FlsCallCycle for timeout monitoring, convert to us by multiplying by 
  1000 * 1000 */
  10000U,
  /* Default mode of FLS driver */
  MEMIF_MODE_SLOW
};

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar 
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CONFIG_DATA_ASIL_B_LOCAL_UNSPECIFIED

/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safeguard. It complies to Autosar guidelines.*/
/* MISRA2012_RULE_20_1_JUSTIFICATION: Memmap header usage as per Autosar
   guideline.*/
 #include "Fls_17_Dmu_MemMap.h"

