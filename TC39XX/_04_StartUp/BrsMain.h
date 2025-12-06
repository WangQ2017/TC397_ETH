
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsMain.h
      Project:  Vector Basic Runtime System
       Module:  BrsMain

  \brief Description:  Main header of BRS contains
                       - Main function (called from StartUpCode and calls stack entry EcuM_Init())
                       - Call of BrsHw HW initialization routines
                       - 1ms handler, with support of cycle functions with several cycle times
                       - Exception handling
                       - Default_Init_Task, Main and Background Task which can be used by the operating system

  \attention Please note:
    The demo and example programs only show special aspects of the software. With regard to the fact
    that these programs are meant for demonstration purposes only, Vector Informatik liability shall be
    expressly excluded in cases of ordinary negligence, to the extent admissible by law or statute.
**********************************************************************************************************************/

#ifndef _BRSMAIN_H_
#define _BRSMAIN_H_

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "Compiler.h"

#include "vBrsCfg.h"

#if !defined (BRS_ENABLE_FBL_SUPPORT)
#include "Os.h"
#endif

#if defined (BRS_ENABLE_HSM_SUPPORT)
  #include "vHsm.h"
#else
# if !defined (BRS_FBL_NO_ECUMINIT)
/* Ecu State Manager has to be available in system (BSW module or BRS Stub) */
  #include "EcuM.h"
# endif
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/

/**********************************************************************************************************************
  MODULE VERSION
**********************************************************************************************************************/
/*
 * Description: This is the BrsHw main and bug fix version. The version numbers are BCD coded.
 *              E.g. a main version of 1.23 is coded with 0x0123, a bug fix version of 9 is coded 0x09.
 */
#define BRSMAIN_VERSION        0x0202u
#define BRSMAIN_BUGFIX_VERSION 0x02u

/**********************************************************************************************************************
  GLOBAL TYPE DEFINITIONS
**********************************************************************************************************************/
#if defined (BRS_ENABLE_TESTSUITE_SUPPORT) || defined (BRS_ENABLE_SUPPORT_LEDS) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  #define BRS_ENABLE_1MS_HANDLER
#endif

#if defined (BRS_ENABLE_1MS_HANDLER)
typedef enum
{
  BRSMAIN_CYCLETIME_BACKGROUND,
  BRSMAIN_CYCLETIME_1MS,
  BRSMAIN_CYCLETIME_10MS,
  BRSMAIN_CYCLETIME_100MS,
  BRSMAIN_CYCLETIME_250MS,
  BRSMAIN_CYCLETIME_500MS,
  BRSMAIN_CYCLETIME_1000MS
}brsMain_Cyclic_Cycletime;
#endif

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/

/*******************************************************************************
 * ModuleCode for BrsMainExceptionHandler
 ******************************************************************************/
#define BRSERROR_MODULE_BRSHW           0x01
#define BRSERROR_MODULE_BRSMAIN         0x02
#define BRSERROR_MODULE_BRSSTARTUP      0x03
#define BRSERROR_MODULE_BRSMAINSTARTUP  0x04

/*******************************************************************************
 * ErrorCodes for BrsMainExceptionHandler
 * 0x00 to 0x7f are assigned to the BRS
 * 0x80 to 0xff are assigned to the application
 ******************************************************************************/
/* General error which is not assigned to a special error class */
#define kBrsUndefinedError                   0x00

/* No handler is installed in interrupt vector table for given interrupt */
#define kBrsInterruptHandlerNotInstalled     0x01

/* A GenTool setting is different to the excepted value */
#define kBrsWrongGenToolSettings             0x02

/* BrsHwRestoreInterrupt is called more often than BrsHwDisableInterrupt */
#define kBrsIllegalInterruptRestoration      0x03

/* Hardware configuration like clock setting is wrong */
#define kBrsIllegalHardwareConfiguration     0x04

/* Illegal parameter used like wrong channel parameter */
#define kBrsIllegalParameter                 0x05

/* Illegal TCC channel used */
#define kBrsTccChannelOutOfRange             0x06

/* Interrupt from unknown source occurred */
#define kBrsUnknownInterrupt                 0x07

/* CAN1 and CAN2 interrupts cannot be distinguished from each other */
#define kBrsAmbiguousInterruptSource         0x08

/* Execution of library version check in Common_SipVersionCheck failed */
#define kBrsLibraryVersionCheckFailed        0x09

/* OS ErrorHook called */
#define kBrsOsErrorHookCall                  0x0A

/* BRS not properly initialized */
#define kBrsConfigUninit                     0x0B

/* Application software returned to main */
#define kBrsIllegalReturnFromMain            0x0C

/* Assembler code reached, which should never be handled */
#define kBrsIllegalAssemblerReached          0x0D

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
void BrsMainInit(void);

#if defined (BRS_ENABLE_1MS_HANDLER)
void BrsMainRegisterCyclic(void (*)(void), brsMain_Cyclic_Cycletime);

void BrsMainCyclic1ms(void);

# if !defined (BRS_ENABLE_FBL_SUPPORT)
TASK(BrsMainTask);
TASK(BrsMainBackgroundTask);
# endif
#endif

#if !defined (BRS_ENABLE_FBL_SUPPORT)
TASK(Default_Init_Task);
TASK(Default_Init_Task_Trusted);
#endif

#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
TASK(Default_Init_Task_Core1);
TASK(Default_Init_Task_Core1_Trusted);
TASK(Default_Init_Task_Core2);
TASK(Default_Init_Task_Core2_Trusted);
TASK(Default_Init_Task_Core3);
TASK(Default_Init_Task_Core3_Trusted);
TASK(Default_Init_Task_Core4);
TASK(Default_Init_Task_Core4_Trusted);
TASK(Default_Init_Task_Core5);
TASK(Default_Init_Task_Core5_Trusted);
TASK(Default_Init_Task_Core6);
TASK(Default_Init_Task_Core6_Trusted);
#endif


#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
typedef enum
{
  BRSMAIN_TOGGLEPIN_LED,
  BRSMAIN_TOGGLEPIN_WD,
  BRSMAIN_TOGGLEPIN_CUSTOM
}brsMain_TogglePin;

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
/*****************************************************************************/
/**
 * @brief      This API is used to toggle a PortPin.
 *             Per default, the following parameters are available:
 *               BRSMAIN_TOGGLEPIN_LED
 *               BRSMAIN_TOGGLEPIN_WD
 *               BRSMAIN_TOGGLEPIN_CUSTOM
 *             Depending pins must be configured and initialized within BrsHw.
 * @pre        -
 * @param[in]  Pin to be toggled
 * @param[out] -
 * @return     -
 * @context    Function is called from all modules to set or clear a PortPin
 */
/*****************************************************************************/
void BrsMainTogglePin(brsMain_TogglePin);
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/

#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif
void BrsMainExceptionHandler(uint8 ErrorCode, uint8 ModuleCode, uint16 LineNumber);
#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif

void BrsMainExceptionStartup(void);

int main(void);

#endif /*_BRSMAIN_H_*/
