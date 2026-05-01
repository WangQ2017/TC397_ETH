/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2020)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  FILENAME   : Fls_17_Dmu.h                                                **
**                                                                           **
**  VERSION :  1.40.0_20.0.0                                                 **
**                                                                           **
**  DATE       :  2020-05-22                                                 **
**                                                                           **
**  VARIANT   : Variant PB                                                   **
**                                                                           **
**  PLATFORM  : Infineon AURIX2G                                             **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This file exports functionality of Flash driver           **
**                                                                           **
**  SPECIFICATION(S) : Specification of FLS Driver, AUTOSAR Release 4.2.2    **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/
/* [cover parentID={D4AC2E4F-6D86-4b0b-A3E8-031DBD101412}][/cover] */
/* [cover parentID={D0DC9620-096E-49ad-B133-83B17D89DABC}][/cover] */
#ifndef  FLS_17_DMU_H
#define  FLS_17_DMU_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
/* Inclusion of Platform_Types.h and Compiler.h  */
#include "Std_Types.h"

/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Atomic write function */
#include "McalLib.h"

/* Fls Module Configuration header file */
#include "Fls_17_Dmu_Cfg.h"

/* Conditional Inclusion of Developement Error Tracer File */
#if ((FLS_17_DMU_DEV_ERROR_DETECT == STD_ON ) || \
     (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)) || \
     (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/*
    Published paramters
*/

/* FLS Vendor ID */
#define FLS_17_DMU_VENDOR_ID                  ((uint16)17)
/* FLS Module ID */
#define FLS_17_DMU_MODULE_ID                  ((uint16)92)

#if(FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
    (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/* Development error values - DET's */
/* API service called with wrong parameter */
#define FLS_17_DMU_E_PARAM_CONFIG           ((uint8)1)
/* API service called with wrong/inconsistent Address(s)*/
#define FLS_17_DMU_E_PARAM_ADDRESS          ((uint8)2)
/* API service called with wrong/inconsistent length(s)*/
#define FLS_17_DMU_E_PARAM_LENGTH           ((uint8)3)
/* API service called with wrong/inconsistent Data(s)*/
#define FLS_17_DMU_E_PARAM_DATA             ((uint8)4)
/* API service called without module initalization */
#define FLS_17_DMU_E_UNINIT                 ((uint8)5)
/* API service called while    Driver is still busy  */
#define FLS_17_DMU_E_BUSY                   ((uint8)6)
/* Erase Verification (blank check) failed */
#define FLS_17_DMU_E_VERIFY_ERASE_FAILED    ((uint8)7)
/* Write Verification (compare) failed */
#define FLS_17_DMU_E_VERIFY_WRITE_FAILED    ((uint8)8)
/* Timeout for Erase/write jobs */
#define FLS_17_DMU_E_TIMEOUT                ((uint8)9)
/* API service called with NULL parameter */
#define FLS_17_DMU_E_PARAM_POINTER          ((uint8)10)
#endif /* FLS_DEV_ERROR_DETECT */

#if (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
/*Safety Errors*/
/* API service called with wrong/inconsistent Address(s)*/
#define FLS_17_DMU_SE_PARAM_ADDRESS          ((uint8)2)
/* API service called with wrong/inconsistent length(s)*/
#define FLS_17_DMU_SE_PARAM_LENGTH           ((uint8)3)
/* API service called with wrong/inconsistent Data(s)*/
#define FLS_17_DMU_SE_PARAM_DATA             ((uint8)4)
/* API service called while    Driver is still busy  */
#define FLS_17_DMU_SE_BUSY                   ((uint8)6)
/*Invalid parameter*/
#define FLS_17_DMU_SE_PARAM_INVLD            ((uint8)90)
/*Initialization failed in Init*/
#define FLS_17_DMU_SE_INIT_FAILED            ((uint8)95)
/*Suspend Operation not allowed*/
#define FLS_17_DMU_SE_ILLGL_OPERTN           ((uint8)100)
/*HW Busy*/
#define FLS_17_DMU_SE_HW_BUSY           ((uint8)110)
/*Timeout after the command is executed*/
#define FLS_17_DMU_SE_HW_TIMEOUT         ((uint8)115)
/*Suspend Erase Error*/
#define FLS_17_DMU_SE_SUSPNDERASE_FAIL      ((uint8)80)
/*Invalid Interrupt*/
#define FLS_17_DMU_SE_INVALID_ISR            ((uint8)120)
#endif/*Safety Errors*/

#if(FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
   (FLS_17_DMU_SAFETY_ENABLE == STD_ON) || \
   (FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
/* API Service ID's */
#define FLS_17_DMU_SID_INIT           ((uint8)0)
#define FLS_17_DMU_SID_ERASE          ((uint8)1)
#define FLS_17_DMU_SID_WRITE          ((uint8)2)
#define FLS_17_DMU_SID_CANCEL         ((uint8)3)
#define FLS_17_DMU_SID_GETSTATUS      ((uint8)4)
#define FLS_17_DMU_SID_GETJOBRESULT   ((uint8)5)
#define FLS_17_DMU_SID_MAIN           ((uint8)6)
#define FLS_17_DMU_SID_READ           ((uint8)7)
#define FLS_17_DMU_SID_COMPARE        ((uint8)8)
#define FLS_17_DMU_SID_SETMODE        ((uint8)9)
#define FLS_17_DMU_SID_BLANKCHECK     ((uint8)10)
#define FLS_17_DMU_SID_GETVERSIONINFO ((uint8)16)
#define FLS_17_DMU_SID_READSYNC       ((uint8)33)
#define FLS_17_DMU_SID_COMPARESYNC    ((uint8)34)
#define FLS_17_DMU_SID_CANCELNONERASE ((uint8)35)
#define FLS_17_DMU_SID_VERIFYERASE    ((uint8)36)
#define FLS_17_DMU_SID_VERIFYSECTORERASE ((uint8)44)
#define FLS_17_DMU_SID_SUSPENDERASE   ((uint8)37)
#define FLS_17_DMU_SID_GETOPERSTATUS  ((uint8)38)
#define FLS_17_DMU_SID_CONTROLTIMEOUTDET ((uint8)39)
#define FLS_17_DMU_SID_ISHARDENINGREQ ((uint8)40)
#define FLS_17_DMU_SID_ISR            ((uint8)45)
#define FLS_17_DMU_SID_RESUMEERASE    ((uint8)42)
#define FLS_17_DMU_SID_INITCHECK      ((uint8)43)
#endif /*API Sevice IDs*/


#if(FLS_17_DMU_RUNTIME_ERROR_DETECT == STD_ON)
/* Run Time Errors */
#define FLS_17_DMU_E_ERASE_FAILED          ((uint8)0x01)
#define FLS_17_DMU_E_WRITE_FAILED          ((uint8)0x02)
#define FLS_17_DMU_E_READ_FAILED           ((uint8)0x03)
#define FLS_17_DMU_E_COMPARE_FAILED        ((uint8)0x04)
#define FLS_17_DMU_E_BLANKCHECK_FAILED     ((uint8)0x1E)
#define FLS_17_DMU_E_HARDENCHK_FAIL        ((uint8)0x37)
#define FLS_17_DMU_E_RESUME_FAIL           ((uint8)0x38)
#define FLS_17_DMU_E_INIT_FAILED           ((uint8)0x39)
#endif /* FLS_RUNTIME_ERROR_DETECT */

/* Options of FlsJobType */
#define FLS_17_DMU_NONE      ((uint8)0)
#define FLS_17_DMU_WRITE     ((uint8)1)
#define FLS_17_DMU_ERASE     ((uint8)2)
#define FLS_17_DMU_READ      ((uint8)3)
#define FLS_17_DMU_COMPARE   ((uint8)4)
#define FLS_17_DMU_READSYNC  ((uint8)5)
#define FLS_17_DMU_CANCEL    ((uint8)6)
#define FLS_17_DMU_COMPARESYNC    ((uint8)7)
#define FLS_17_DMU_VERIFYERASE    ((uint8)8)
#define FLS_17_DMU_BLANKCHECK     ((uint8)9)

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*Hardening Return Values*/
#define FLS_17_DMU_HARDENCHK_NOTREQD  ((Fls_17_Dmu_HardenType)0)
#define FLS_17_DMU_HARDENCHK_REQRD    ((Fls_17_Dmu_HardenType)1)
#define FLS_17_DMU_HARDENCHK_ERROR    ((Fls_17_Dmu_HardenType)2)
/*Hardening Align Check*/
#define FLS_17_DMU_PAGE_HARDEN           ((uint8)(0x55))
#define FLS_17_DMU_WORDLINE_HARDEN       ((uint8)(0xAA))
#endif

/* Erase/Program verification using VER bit */
/* If PVER check has to be disabled, then strict margin check for '0'
   should be implemented in Fls_17_Dmu_CompareWordsSync API; this is needed
   to detect early interrupted programming operation. */
#define FLS_17_DMU_VER_ERROR_CHECK (STD_ON)

#define FLS_17_DMU_BURST_PAGE_SIZE (32U)
#define FLS_17_DMU_WORDLINE_SIZE   (512U)

/* DF0's individual Logical sector size: 4K bytes */
#define FLS_17_DMU_LOGICALSECTOR_SIZE (4096U)

/*Worst case 100ns delay for the HW busy bit to get set for FSI@20Mhz.*/
#define FLS_17_DMU_HWBUSY_DELAY          (100U)

#define FLS_17_DMU_SUBSECTOR_SIZE (FLS_17_DMU_LOGICALSECTOR_SIZE)

#define FLS_17_DMU_MCAL_SUPERVISOR (0U)
#define FLS_17_DMU_MCAL_USER1      (1U)

#define FLS_17_DMU_PAGE_WRITE   (0U)
#define FLS_17_DMU_BURST_WRITE  (1U)
/* Options for DFLS Read Access Wait States.Note SysClk(Mhz)/ WaitStates <=63*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS0  (0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS1  (1U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS2  (2U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS3  (3U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS4  (4U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS5  (5U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS6  (6U)  /* Default Wait States */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS7  (7U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS8  (8U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS9  (9U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS10 (10U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS11 (11U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS12 (12U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS13 (13U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS14 (14U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS15 (15U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS16 (16U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS17 (17U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS18 (18U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS19 (19U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS20 (20U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS21 (21U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS22 (22U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS23 (23U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS24 (24U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS25 (25U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS26 (26U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS27 (27U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS28 (28U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS29 (29U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS30 (30U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS31 (31U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS32 (32U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS33 (33U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS34 (34U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS35 (35U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS36 (36U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS37 (37U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS38 (38U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS39 (39U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS40 (40U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS41 (41U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS42 (42U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS43 (43U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS44 (44U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS45 (45U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS46 (46U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS47 (47U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS48 (48U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS49 (49U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS50 (50U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS51 (51U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS52 (52U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS53 (53U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS54 (54U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS55 (55U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS56 (56U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS57 (57U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS58 (58U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS59 (59U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS60 (60U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS61 (61U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS62 (62U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS63 (63U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS64 (64U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS65 (65U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS66 (66U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS67 (67U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS68 (68U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS69 (69U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS70 (70U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS71 (71U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS72 (72U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS73 (73U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS74 (74U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS75 (75U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS76 (76U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS77 (77U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS78 (78U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS79 (79U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS80 (80U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS81 (81U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS82 (82U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS83 (83U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS84 (84U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS85 (85U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS86 (86U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS87 (87U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS88 (88U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS89 (89U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS90 (90U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS91 (91U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS92 (92U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS93 (93U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS94 (94U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS95 (95U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS96 (96U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS97 (97U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS98 (98U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS99 (99U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS100 (100U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS101 (101U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS102 (102U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS103 (103U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS104 (104U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS105 (105U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS106 (106U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS107 (107U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS108 (108U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS109 (109U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS110 (110U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS111 (111U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS112 (112U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS113 (113U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS114 (114U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS115 (115U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS116 (116U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS117 (117U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS118 (118U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS119 (119U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS120 (120U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS121 (121U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS122 (122U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS123 (123U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS124 (124U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS125 (125U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS126 (126U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS127 (127U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS128 (128U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS129 (129U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS130 (130U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS131 (131U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS132 (132U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS133 (133U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS134 (134U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS135 (135U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS136 (136U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS137 (137U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS138 (138U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS139 (139U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS140 (140U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS141 (141U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS142 (142U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS143 (143U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS144 (144U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS145 (145U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS146 (146U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS147 (147U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS148 (148U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS149 (149U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS150 (150U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS151 (151U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS152 (152U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS153 (153U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS154 (154U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS155 (155U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS156 (156U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS157 (157U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS158 (158U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS159 (159U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS160 (160U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS161 (161U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS162 (162U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS163 (163U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS164 (164U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS165 (165U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS166 (166U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS167 (167U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS168 (168U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS169 (169U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS170 (170U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS171 (171U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS172 (172U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS173 (173U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS174 (174U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS175 (175U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS176 (176U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS177 (177U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS178 (178U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS179 (179U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS180 (180U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS181 (181U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS182 (182U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS183 (183U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS184 (184U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS185 (185U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS186 (186U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS187 (187U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS188 (188U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS189 (189U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS190 (190U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS191 (191U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS192 (192U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS193 (193U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS194 (194U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS195 (195U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS196 (196U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS197 (197U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS198 (198U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS199 (199U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS200 (200U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS201 (201U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS202 (202U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS203 (203U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS204 (204U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS205 (205U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS206 (206U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS207 (207U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS208 (208U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS209 (209U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS210 (210U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS211 (211U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS212 (212U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS213 (213U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS214 (214U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS215 (215U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS216 (216U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS217 (217U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS218 (218U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS219 (219U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS220 (220U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS221 (221U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS222 (222U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS223 (223U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS224 (224U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS225 (225U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS226 (226U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS227 (227U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS228 (228U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS229 (229U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS230 (230U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS231 (231U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS232 (232U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS233 (233U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS234 (234U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS235 (235U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS236 (236U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS237 (237U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS238 (238U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS239 (239U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS240 (240U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS241 (241U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS242 (242U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS243 (243U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS244 (244U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS245 (245U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS246 (246U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS247 (247U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS248 (248U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS249 (249U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS250 (250U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS251 (251U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS252 (252U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS253 (253U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS254 (254U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_READACCESS255 (255U)
/* Options for DFLS Error Correction Wait States */
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION0 (0U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION1 (1U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION2 (2U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION3 (3U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION4 (4U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION5 (5U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION6 (6U)
/*MISRA2012_RULE_5_1_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_WAIT_STATE_ERRORCORRECTION7 (7U)


/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/* [cover parentID={AEBC6EE4-722B-471c-BCA8-756866BF1671}] */
typedef uint32 Fls_17_Dmu_AddressType;
/*  [/cover] */

/* [cover parentID={C99A4CBA-743A-4fc6-A260-F8699A0BF36A}] */
typedef uint32 Fls_17_Dmu_LengthType;
/*  [/cover] */
/* [cover parentID={7CC7EAC9-39DA-4e13-AFF9-BF2FE8484521}][/cover]*/
typedef struct
{
  unsigned_int Reserved1 : 1;

  unsigned_int Write     : 1;

  unsigned_int Erase     : 1;

  unsigned_int Read      : 1;

  unsigned_int Compare   : 1;

  unsigned_int Reserved2 : 3;
} Fls_17_Dmu_JobStartType;

/* Return values of the function Fls_17_Dmu_GetNotifCaller */
/* [cover parentID={6797898F-5651-46a0-944A-B2F3BE377F23}][/cover] */
/* [cover parentID={1AE3AA55-AC0E-4f57-9FDF-60AB99C40E54}][/cover] */
/* [cover parentID={1AE3AA55-AC0E-4f57-9FDF-60AB99C40E54}][/cover] */
typedef uint8 Fls_17_Dmu_Job_Type;
/* [cover parentID={60B2F68B-08A5-4029-916D-03293423BF65}][/cover] */
typedef uint8 Fls_17_Dmu_HardenType;

#define FLS_17_DMU_NO_JOB        ((Fls_17_Dmu_Job_Type)FLS_17_DMU_NONE)
#define FLS_17_DMU_WRITE_JOB     ((Fls_17_Dmu_Job_Type)FLS_17_DMU_WRITE)
#define FLS_17_DMU_ERASE_JOB     ((Fls_17_Dmu_Job_Type)FLS_17_DMU_ERASE)
#define FLS_17_DMU_READ_JOB      ((Fls_17_Dmu_Job_Type)FLS_17_DMU_READ)
#define FLS_17_DMU_COMPARE_JOB   ((Fls_17_Dmu_Job_Type)FLS_17_DMU_COMPARE)
#define FLS_17_DMU_READSYNC_JOB  ((Fls_17_Dmu_Job_Type)FLS_17_DMU_READSYNC)
#define FLS_17_DMU_CANCEL_JOB    ((Fls_17_Dmu_Job_Type)FLS_17_DMU_CANCEL)
#define FLS_17_DMU_BLANKCHECK_JOB   ((Fls_17_Dmu_Job_Type)FLS_17_DMU_BLANKCHECK)

/* [cover parentID={521A2761-98D4-4d2f-BEA2-CD9EFC8D051C}][/cover] */
typedef struct
{
    /* Source address for read job,
      destination aage address for write job,
      DFLASH physical address for erase job */
  uint32 FlsReadAddress;
  uint32 FlsWriteAddress;
  uint32 FlsEraseAddress;

  /* Erase and Write Timeout Cycle Count */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint32 FlsEraseTimeoutCycleCount;
  uint32 FlsWriteTimeoutCycleCount;
  #endif

  /* Number of bytes to read or write */
  Fls_17_Dmu_LengthType FlsReadLength;
  Fls_17_Dmu_LengthType FlsWriteLength;

  /* Destination pointer for read job and
     source pointer for write job */
  uint8* FlsReadBufferPtr;
  const uint8* FlsWriteBufferPtr;

  /* Variable used to store Job Result of the Flash */
  MemIf_JobResultType FlsJobResult;

  /* FLS Mode - Fast or Slow */
  MemIf_ModeType FlsMode;

  /* Job type for which notification was raised */
  Fls_17_Dmu_Job_Type NotifCaller;

  /* Status to indicate if the job has been started */
  Fls_17_Dmu_JobStartType JobStarted;

  /* Number of sectors to be erased */
  uint16 FlsEraseNumSectors;
  /* Number of sectors to be erased in 1 command cycle */
  uint8 FlsEraseNumSecPerCmd;
  /* Status of current jobtype */
  Fls_17_Dmu_Job_Type FlsJobType;

  /* PVER error status */
  #if(FLS_17_DMU_VER_ERROR_CHECK == STD_ON)
  #if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
  uint8 FlsPver;
  #endif
  #endif
  /*EVER error status*/
  uint8 FlsEver;

  /* Command Sequence Timeout Error Status */
  uint8 FlsTimeoutErr;

  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) || \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  /* Timeout handling status */
  uint8 FlsTimeoutControl;
  #endif

} Fls_17_Dmu_StateType;

/*
Type:Fls_17_Dmu_NotifFunctionPtrType
Function pointer for JobEnd and JobError Notification
*/
typedef void (*Fls_17_Dmu_NotifFunctionPtrType)(void);

/*
  This is the type of Flash external data structure containing
  the overall initialization data for the Flash Driver
*/
/* [cover parentID={5A6BA16E-9635-4713-B7C6-06F2DE9AB50E}]
  [/cover] */
typedef struct
{
  Fls_17_Dmu_StateType   *FlsStateVarPtr;

  /* FLS_MAX_READ, Maximum number of bytes to Read in one cycle of FLS driver
    job processing */
  Fls_17_Dmu_LengthType FlsFastRead;
  Fls_17_Dmu_LengthType FlsSlowRead;
  /* Funtion pointer for JobEndNotification.*/
  Fls_17_Dmu_NotifFunctionPtrType FlsJobEndNotificationPtr;

  /* Funtion pointer for JobErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsJobErrorNotificationPtr;

  /* Funtion pointer for EVER ErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsEraseVerifyErrNotifPtr;

  /* Funtion pointer for PVER ErrorNotification. */
  Fls_17_Dmu_NotifFunctionPtrType FlsProgVerifyErrNotifPtr;

  /* Funtion pointer for Illegal State Notification */
  Fls_17_Dmu_NotifFunctionPtrType FlsIllegalStateNotificationPtr;

  /* Wait state configuration for Read access and error correction */
  uint32 FlsWaitStates;

  /* FLS call cycle */
  #if (FLS_17_DMU_DEV_ERROR_DETECT == STD_ON) ||                 \
      (FLS_17_DMU_SAFETY_ENABLE == STD_ON)
  uint32 FlsCallCycle;
  #endif

  /* Default mode of FLS Driver */
  MemIf_ModeType FlsDefaultMode;

} Fls_17_Dmu_ConfigType;
/* [cover parentID={8D832E9B-AF58-4d48-8C2F-241BE30E65E2}][/cover] */
/*   Typedefs for FLS INIT API to be used by MEMIF module */
typedef void (*Fls_Init_Type)(const Fls_17_Dmu_ConfigType* ConfigPtr);


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/




/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_START_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

/*******************************************************************************
**                                                                            **
** Syntax : void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType*const ConfigPtr) **
**                                                                            **
** Service ID:  0x00                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  ConfigPtr - Pointer to configuration set                **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Driver Module Initialization function                        **
** Service for FLASH initialization. The Initialization function shall        **
** initialize all Flash relevant registers with the values of the structure   **
** referenced by the parameter ConfigPtr.                                     **
**                                                                            **
*******************************************************************************/
extern void Fls_17_Dmu_Init(const Fls_17_Dmu_ConfigType*const ConfigPtr);

#if (FLS_17_DMU_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_GetVersionInfo(                                   **
**                                  Std_VersionInfoType *const VersioninfoPtr)**
**                                                                            **
** Service ID:     0x10                                                       **
**                                                                            **
** Sync/Async:      Synchronous                                               **
**                                                                            **
** Reentrancy:      reentrant                                                 **
**                                                                            **
** Parameters (in): VersioninfoPtr : Pointer to where to store the version    **
**                                   information of this module.              **
**                                                                            **
** Parameters (out):none                                                      **
**                                                                            **
** Return value:    none                                                      **
**                                                                            **
** Description :    This service returns the version information of           **
**                  this module.                                              **
**                  The version information includes:                         **
**                  Module Id,Vendor Id , Vendor specific version numbers     **
**                                                                            **
*******************************************************************************/
extern void Fls_17_Dmu_GetVersionInfo
                               (Std_VersionInfoType* const VersionInfoPtr);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetVersionInfo(VersioninfoPtr) \
                      (ERROR_FlsVersionInfoApi_NOT_SELECTED)

#endif/*(FLS_VERSION_INFO_API == STD_ON)*/

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Erase(                                  **
**                              const Fls_17_Dmu_AddressType TargetAddress,   **
**                              const Fls_17_Dmu_LengthType Length            **
**                                  )                                         **
**                                                                            **
** Service ID:  0x01                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress and Length                                **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API Erases Flash. It copies the given parameters to     **
** driver internal variables, initiates the erase job, sets the driver status **
** to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                         **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Erase(
                              const Fls_17_Dmu_AddressType TargetAddress,
                              const Fls_17_Dmu_LengthType Length
                               );


/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Write(                                  **
**                                const Fls_17_Dmu_AddressType TargetAddress, **
**                                const uint8 *const SourceAddressPtr,        **
**                                const Fls_17_Dmu_LengthType Length          **
**                                  );                                        **
**                                                                            **
** Service ID:  0x02                                                          **
**                                                                            **
** Sync/Async:  ASynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddressPtr,TargetAddress and Length                 **
**                                                                            **
** Parameters (out): E_OK: command has been accepted                          **
**                   E_NOT_OK: command has not been accepted                  **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : Writing to given flash address.                              **
** Service for writing one or more flash pages. This service copies the given **
** parameters to driver internal variables, initiate a Write job, set driver  **
** status to MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                  **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Write(
                                 const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 *const SourceAddressPtr,
                                 const Fls_17_Dmu_LengthType Length
                                  );


#if (FLS_17_DMU_COMPARE_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Compare(                                **
**                                      const Fls_AddressType SourceAddress,  **
**                                      const uint8 *const TargetAddressPtr,  **
**                                   const Fls_LengthType Length              **
**                                    );                                      **
**                                                                            **
** Service ID:  0x08                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :SourceAddress, TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for comparing the contents of an area of flash memory**
** with that of an application data buffer. This service shall copy the given **
** parameters to driver internal variables, initiate a compare job, set the   **
** driver status to MEMIF_BUSY, set the job result to MEMIF_JOB_PENDING       **
** and return with E_OK.                                                      **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Compare(
                            const Fls_17_Dmu_AddressType SourceAddress,
                            const uint8 *const TargetAddressPtr,
                            const Fls_17_Dmu_LengthType Length
                            );
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Compare( SourceAddress, \
                     TargetAddressPtr, \
                     Length          \
                   )                 \
(ERROR_FlsCompareApi_NOT_SELECTED)

#endif

#if (FLS_17_DMU_BLANK_CHECK_API == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_BlankCheck(                             **
**                                const Fls_17_Dmu_AddressType TargetAddress  **
**                                const  Fls_17_Dmu_LengthType Length         **
**                                    );                                      **
**                                                                            **
** Service ID:  0x0A                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :TargetAddress and Length                                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : This API is a Service is to verify, whether a given memory   **
** area has been erased but not (yet) programmed.                             **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_BlankCheck(
                                    const Fls_17_Dmu_AddressType TargetAddress,
                                    const Fls_17_Dmu_LengthType Length
                                     );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_BlankCheck(TargetAddress,\
                             Length \
                           )\
(ERROR_FlsBlankCheckApi_NOT_SELECTED)
#endif

#if  (FLS_17_DMU_CANCEL_API  ==  STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_Cancel(Void)                                      **
**                                                                            **
** Service ID:  0x03                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash job.                                **
** Read and Compare jobs will be cancelled immediately. Write and Erase jobs  **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
extern void Fls_17_Dmu_Cancel(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Cancel(void) \
(ERROR_FlsCancelApi_NOT_SELECTED)

#endif

#if(FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : void Fls_17_Dmu_CancelNonEraseJobs(void)                          **
**                                                                            **
** Service ID: 0x28                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Service for Canceling an ongoing flash jobs except the erase job.          **
** Read and Compare jobs will be cancelled immediately. Write job             **
** will be cancelled in driver immediately but hardware might still be busy   **
** until the ongoing operation is completed for the already issued commands   **
*******************************************************************************/
extern void Fls_17_Dmu_CancelNonEraseJobs(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_CancelNonEraseJobs() \
     (ERROR_FlsIfxFeeUse_NOT_SELECTED)
#endif

#if  (FLS_17_DMU_GET_STATUS_API  ==  STD_ON)
/*******************************************************************************
** Syntax : MemIf_StatusType Fls_17_Dmu_GetStatus(void)                       **
**                                                                            **
** Service ID:  0x04                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_StatusType                                        **
**                                                                            **
** Description :                                                              **
**         This service shall return the driver state synchronously           **
*******************************************************************************/
extern MemIf_StatusType Fls_17_Dmu_GetStatus(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetStatus() \
(ERROR_FlsGetStatusApi_NOT_SELECTED)

#endif

#if (FLS_17_DMU_GET_JOB_RESULT_API  ==  STD_ON)
/*******************************************************************************
** Syntax : MemIf_JobResultType Fls_17_Dmu_GetJobResult(void)                 **
**                                                                            **
** Service ID:  0x05                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Re-entrant                                                    **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  MemIf_JobResultType                                     **
**                                                                            **
** Description :                                                              **
**         This service shall return the result of the last job synchronously **
*******************************************************************************/
extern MemIf_JobResultType Fls_17_Dmu_GetJobResult(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetJobResult() \
(ERROR_FlsGetJobResultApi_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : void Fls_17_Dmu_MainFunction(void)                                **
**                                                                            **
** Service ID:  0x06                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
**         This service shall perform the processing of the flash read,write  **
**         and erase jobs                                                     **
*******************************************************************************/
extern void Fls_17_Dmu_MainFunction(void);

/*******************************************************************************
** Syntax : void Fls_17_Dmu_SetMode(MemIf_ModeType Mode)                      **
**                                                                            **
** Service ID:  0x09                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : Mode MEMIF_MODE_SLOW:                                    **
**                        Slow read access                                    **
**                                                                            **
**                        MEMIF_MODE_FAST:                                    **
**                        Fast read access                                    **
**                                                                            **
** Parameters (out): : None                                                   **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This API sets the Flash driver's operation mode.             **
**               FAST or SLOW mode impacts only Read/Compare operations.      **
**               Based on the currently active mode, the number of bytes to be**
**               read from Flash in each call of Fls_17_Dmu_MainFunction is   **
**               taken from the configuration                                 **
*******************************************************************************/
#if  (FLS_17_DMU_SET_MODE_API  ==  STD_ON)
extern void Fls_17_Dmu_SetMode(const MemIf_ModeType Mode);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_SetMode(Mode) \
(ERROR_FlsSetModeApi_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_Read(                                   **
**                               const Fls_17_Dmu_AddressType SourceAddress,  **
**                                 uint8 *const TargetAddressPtr,             **
**                               const Fls_17_Dmu_LengthType Length           **
**                                 );                                         **
** Service ID:  0x07                                                          **
**                                                                            **
** Sync/Async:  Asynchronous                                                  **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress,TargetAddressPtr and Length                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    :  E_OK: command has been accepted                         **
**                    E_NOT_OK: command has not been accepted                 **
**                                                                            **
** Description : Service for reading from flash memory. This service copies   **
** the given parameters to driver internal variables, set driver status to    **
** MEMIF_BUSY and job result to MEMIF_JOB_PENDING.                            **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_Read(
                                const Fls_17_Dmu_AddressType SourceAddress,
                                uint8 *const TargetAddressPtr,
                                const Fls_17_Dmu_LengthType Length
                               );


#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_ReadWordsSync(                          **
                                   const Fls_17_Dmu_AddressType SourceAddress,**
**                                           uint32 *const TargetAddressPtr,  **
**                                       const uint32 Length                  **
**                                         );                                 **
**                                                                            **
** Service ID:  0x21                                                          **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr and Length               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Read successful                                    **
**                   E_NOT_OK: HW busy or read failed with ECC error          **
**                                                                            **
** Description : Service for reading word data from flash bank synchronously  **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_ReadWordsSync
                              (const Fls_17_Dmu_AddressType SourceAddress,
                               uint32 *const TargetAddressPtr,
                               const uint32 Length
                               );

/*******************************************************************************
** Syntax : Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void)               **
**                                                                            **
** Service ID: 0x29                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description :                                                              **
** Ths function returns the FLS Job that raised the notification              **
*******************************************************************************/
extern Fls_17_Dmu_Job_Type Fls_17_Dmu_GetNotifCaller(void);

/*******************************************************************************
** Syntax:Std_ReturnType Fls_17_Dmu_CompareWordsSync(                         **
**                                 const Fls_17_Dmu_AddressType SourceAddress,**
**                                   const uint32 *const TargetAddressPtr,    **
**                                       const  uint32 Length);               **
**                                                                            **
** Service ID: 0x22                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : SourceAddress, TargetAddressPtr, Length                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : E_OK: Compare successful                                 **
**                   E_NOT_OK: HW busy or compare failed or ECC error         **
**                                                                            **
** Description : Service for comparing data from flash bank synchronously     **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_CompareWordsSync(
                              const Fls_17_Dmu_AddressType SourceAddress,
                              const uint32 *const TargetAddressPtr,
                              const uint32 Length);

#if (FLS_17_DMU_IFX_NVM_PRESENT == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_VerifyErase(                            **
**                              const Fls_17_Dmu_AddressType TargetAddress,   **
**                                 uint32 * const UnerasedWordlineAddressPtr, **
**                                 uint8 * const UnerasedWordlineCountPtr );  **
**                                                                            **
**                                                                            **
** Service ID: 0x23                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress                                            **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a sector                      **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_VerifyErase(
                                   const Fls_17_Dmu_AddressType TargetAddress,
                                   uint32 *const UnerasedWordlineAddressPtr,
                                   uint8 *const UnerasedWordlineCountPtr );

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifyErase(TargetAddress, UnerasedWordlineAddressPtr,  \
                                              UnerasedWordlineCountPtr) \
(ERROR_Fls_17_Dmu_VerifyErase_NOT_SELECTED)
#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_VerifySectorErase(                      **
**                                 const Fls_17_Dmu_AddressType TargetAddress,**
**                                 uint32 * const UnerasedWordlineAddressPtr, **
**                                 uint8 * const UnerasedWordlineCountPtr,    **
**                                 const uint8 Sector);                       **
**                                                                            **
**                                                                            **
** Service ID: 0x24                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) : TargetAddress, Sector                                    **
**                                                                            **
** Parameters (out): UnerasedWordlineAddressPtr,UnerasedWordlineCountPtr      **
**                                                                            **
** Return value    :  E_OK: Erase verification successful                     **
**                    E_NOT_OK: HW busy or erase verification failed          **
**                                                                            **
** Description : Service for verifying erase of a logical sector              **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_VerifySectorErase(
                                  const Fls_17_Dmu_AddressType TargetAddress,
                                  uint32 *const UnerasedWordlineAddressPtr,
                                  uint8 * const UnerasedWordlineCountPtr,
                                  const uint8 Sector);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_ReadWordsSync(SourceAddress,TargetAddressPtr,Length) \
(ERROR_FlsIfxFeeUse_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_GetNotifCaller() \
(ERROR_FlsIfxFeeUse_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_CompareWordsSync(SourceAddress,TargetAddressPtr,\
                                                        Length) \
(ERROR_FlsIfxFeeUse_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifySectorErase(TargetAddress, UnerasedWordlineAddressPtr, \
                                     UnerasedWordlineCountPtr,Sector) \
(ERROR_FlsIfxFeeUse_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_VerifyErase(TargetAddress, UnerasedWordlineAddressPtr,  \
                                              UnerasedWordlineCountPtr) \
(ERROR_FlsIfxFeeUse_NOT_SELECTED)

#endif /* #if (FLS_IFX_FEE_USED == STD_ON) */

#if (FLS_17_DMU_USE_ERASESUSPEND == STD_ON)
/*******************************************************************************
** Syntax : Std_ReturnType  Fls_17_Dmu_SuspendErase (void)                    **
**                                                                            **
** Service ID: 0x25                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_SuspendErase(void);

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_ResumeErase (void)                      **
**                                                                            **
**                                                                            **
** Service ID: 0x26                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - Erase suspend successful                         **
**                    E_NOT_OK - Erase suspend failed                         **
**                                                                            **
** Description :                                                              **
** Ths function suspends an ongoing erase of a sector.                        **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_ResumeErase (void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_SuspendErase() \
(ERROR_FlsUseEraseSuspend_NOT_SELECTED)

/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_ResumeErase() \
(ERROR_FlsUseEraseSuspend_NOT_SELECTED)

#endif /* FLS_USE_ERASESUSPEND == STD_ON */

/*******************************************************************************
** Syntax : void Fls_17_Dmu_Isr(void)                                         **
**                                                                            **
** Service ID: None                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non Re-entrant                                                **
**                                                                            **
** Parameters (in) : void                                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value    : void                                                     **
**                                                                            **
** Description : This routine is used instead of Main function if configured  **
** for Erase and Write Jobs.                                                  **
*******************************************************************************/
#if( FLS_17_DMU_USE_INTERRUPTS == STD_ON)

extern void Fls_17_Dmu_Isr(void);

#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Error generation when API is called
without configuring it  */
#define Fls_17_Dmu_Isr() \
(ERROR_FlsUseInterrupts_NOT_SELECTED)

#endif

/*******************************************************************************
** Syntax : Std_ReturnType Fls_17_Dmu_GetOperStatus(void)                     **
**                                                                            **
** Service ID: 0x2A                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  E_OK - No OPER error                                    **
**                    E_NOT_OK - OPER error has occured                       **
**                                                                            **
** Description : This function provides the OPER error status                 **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_GetOperStatus(void);

/*******************************************************************************
** Syntax : void Fls_17_Dmu_ControlTimeoutDet(const uint8 Param)              **
**                                                                            **
** Service ID: 0x2B                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  Param                                                   **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  None                                                    **
**                                                                            **
** Description : This is the function to disable and re-enable detection /    **
**               reporting of timeout DET                                     **
*******************************************************************************/
extern void Fls_17_Dmu_ControlTimeoutDet(const uint8 Param);

#if (FLS_17_DMU_IFX_FEE_USED == STD_ON)
/*******************************************************************************
** Syntax : Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(             **
**                               const Fls_17_Dmu_AddressType TargetAddress   **
**                                                 const uint8 AlignChk)      **
**                                                                            **
** Service ID: 0x2C                                                           **
**                                                                            **
** Sync/Async:  Synchronous                                                   **
**                                                                            **
** Reentrancy:  Non reentrant                                                 **
**                                                                            **
** Parameters (in) :  TargetAddress                                           **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value    :  Std_ReturnType                                          **
**                                                                            **
** Description : The function checks whether the contents of memory at        **
                 requested wordline address needs hardening or not            **
*******************************************************************************/
extern Fls_17_Dmu_HardenType Fls_17_Dmu_IsHardeningRequired(
                                 const Fls_17_Dmu_AddressType TargetAddress,
                                 const uint8 AlignChk);
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
#define Fls_17_Dmu_IsHardeningRequired(TargetAddress, AlignChk) \
                                             (ERROR_FlsIfxFeeUse_NOT_SELECTED)
#endif/*FLS_17_DMU_IFX_FEE_USED == STD_ON*/

#if (FLS_17_DMU_INITCHECK_API == STD_ON)
/*******************************************************************************
** Traceability   : [cover parentID={FABE1515-678B-4067-9C75-7DBE5B2AB39C}]   **
**                                                                            **
** Syntax         : Std_ReturnType Fls_17_Dmu_InitCheck                       **
**                            (                                               **
**                             const Fls_17_Dmu_ConfigType *const ConfigPtr   **
**                            )                                               **
**                                                                            **
** Description    : This function verifies the initialization the GPT driver  **
**                  in context to the core from where the API is invoked.     **
**                                                                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID     : 0x0E                                                      **
**                                                                            **
** Sync/Async     : Synchronous                                               **
**                                                                            **
** Reentrancy     : Non Reentrant                                             **
**                                                                            **
** Parameters(in) : None                                                      **
**                                                                            **
** Parameters(out): Fls                                                       **
**                                                                            **
** Return value   : E_OK     - Initialization comparison is success           **
**                  E_NOT_OK - Initialization comparison failed               **
**                                                                            **
*******************************************************************************/
extern Std_ReturnType Fls_17_Dmu_InitCheck(
                             const Fls_17_Dmu_ConfigType *const ConfigPtr);
/******************************************************************************/
#else
/* MISRA2012_RULE_4_9_JUSTIFICATION: Function like macro used to generate
 compile time error in case of incorrect configuration*/
/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define Fls_17_Dmu_InitCheck(ConfigPtr) (ERROR_FlsInitCheck_NOT_SELECTED)
#endif
/* End of #if (FLS_INITCHECK_API == STD_ON) */


/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*MISRA2012_RULE_5_1_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_2_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/*MISRA2012_RULE_5_4_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
/* MISRA2012_RULE_5_5_JUSTIFICATION:Memmap macros are defined as per Autosar
naming convention, hence it goes beyond 32 characters.*/
#define FLS_17_DMU_STOP_SEC_CODE_ASIL_B_LOCAL
/* MISRA2012_RULE_4_10_JUSTIFICATION: Memmap header is repeatedly included
   without safegaurd. It complies to Autosar guidelines. */
#include "Fls_17_Dmu_MemMap.h"

#include "Fls_17_Dmu_PBcfg.h"

#endif

