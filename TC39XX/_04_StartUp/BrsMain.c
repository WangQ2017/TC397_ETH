
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
  \file  File:  BrsMain.c
      Project:  Vector Basic Runtime System
       Module:  BrsMain

  \brief Description:  Main file of BRS contains
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

/**********************************************************************************************************************
  REVISION HISTORY
 ----------------------------------------------------------------------------------------------------------------------
  Version   Date        Author  Description
  --------  ----------  ------  ---------------------------------------------------------------------------------------
  01.00.00  2018-03-20  visbwa  Initial creation of new BRS code basis
            2018-05-08  visbwa  Introduced support for Generic Testsuite (BRS_ENABLE_TESTSUITE_SUPPORT),
                                removed support for all other testsuites,
                                introduced BRS_ENABLE_1MS_HANDLER and brsMain_CallCounter1sec
  01.00.01  2018-06-22  visbwa  Added CAN stack exclusive area workaround from former BswInit_Callout_Stubs.c
  01.00.02  2018-06-25  visbwa  Added configuration check for OS_MS2TICKS_SystemTimer into BrsMain.h
  01.00.03  2018-07-18  visbwa  Moved BrsHwDisableInterruptAtPowerOn() from BrsMainInit() into main()
                                (OS specifies, this has to be called before Os_Init() and for every Core)
  01.00.04  2018-07-30  visbwa  Encapsuled call of BrsHwDisableInterruptAtPowerOn() with usecase != VTT
  01.01.00  2018-10-08  visbwa  Changed include of BrsCfg.h into vBrsCfg.h in BrsMain.h (vBaseEnv 1.1.0)
  01.01.01  2018-10-10  visbwa  Moved BrsTestsuiteInit() from BrsMainInit() into Default_Init_Task(),
                                removed usage of BRS_ENABLE_HLPTEST_SUPPORT (generic Testsuite concept!)
  01.01.02  2018-11-05  visbwa  Fixed include order (Can.h previous to BrsTestsuite.h)
  01.01.03  2018-11-13  visbwa  Implemented Default_Init_Tasks for projects with up to 6 Cores,
                                fixed VTT support within IdleTasks (CANoeAPI_ConsumeTicks)
  01.02.00  2018-11-21  visbwa  Added testsuite callouts into every function
  01.02.01  2018-11-30  visbwa  Removed include of Rte_Main.h (Rte_Start() not called any more)
  01.03.00  2018-12-21  visbwa  Added call of new API Os_InitialEnableInterruptSources() within every Default_Init_Task
  01.03.01  2019-03-06  visbwa  Added hint for DrvCan using infix, added wrapper for Can_30_Mcan
  01.03.02  2019-06-13  vismaa  Added additional Default_Init_Task_Core6
  01.03.03  2019-06-26  visbwa  Moved call of BrsMainInit() previous to call of Os_Init()
  01.04.00  2019-07-02  visbwa  Enhanced FBL support (encapsulations, call of fblmain())
  01.04.01  2019-07-29  visbwa  Added implementation of BrsMainExceptionStartup() for calls from assembler StartUpCode
  01.05.00  2019-08-08  visbwa  Implemented support for different FBL usecases Legacy, WithoutOSScheduling and
                                OSScheduling, added BrsMainExceptionHandler module code for BrsMainStartup, changed FBL
                                call from fblmain() to FblMain() for legacy mode, removed include of fbl_main.h
  01.06.00  2019-08-28  visbwa  Changed encapsulation of task implementations (not used for FBL usecases Legacy and
                                WithoutOSScheduling any more)
            2019-10-09  visbwa  Enhanced support for VTT platform
  01.06.01  2019-11-04  visbwa  Changed include of Can.h into CanIf.h, to get rid of DrvCan with infix (Can_30_Mcan.h),
                                enhanced MemMap + SchM exclusive area abstraction for Mcan driver (uses infixes)
  01.07.00  2019-11-25  visbwa  Implemented Default_Init_Task_Trusted and Default_Init_Task_Corex_Trusted to allow the
                                SafeContext partitioning UseCase
            2019-11-27  visbwa  Changed include structure for vBrsCfg.h in BrsMain.h (does now also exist for VTT)
            2019-11-29  visbwa  Enhanced encapsulation with _MICROSOFT_C_VTT_ for DualTarget UseCase (no BrsHw!)
            2019-12-04  visbwa  Fixed encapsulation of DrvCan parts
  01.08.00  2020-02-11  visbwa  Support for UseCase HSM (BRS_ENABLE_HSM_SUPPORT, no EcuM),
                                added filtering of MultiCore parts through C_BRSASR_USECASE_SINGLECORE_COMMENT,
                                support for generated DrvCan macros to support modules with infix names
  01.09.00  2020-03-12  visbwa  Encapsulation of SchM implementation with MemMap defines for UseCase FBL,
                                encapsulation of struct brsMain_Cyclic_Callbacks with MemMap and 1ms-handler defines
  01.09.01  2020-04-22  visbwa  Added conditional call of BrsHwDisableEccErrorReporting() for FBL UseCase
  02.00.00  2020-05-29  visbwa  Major updates for vBaseEnv 2.0.0
                                - added BrsMainTogglePin() (moved from BrsHw.c BrsHwTogglePin())
  02.01.00  2020-06-29  visbwa  Added support for preferred PLL and Watchdog init in BrsMainInit()
  02.01.01  2020-07-24  visbwa  Soft increase for FBL_Legacy support
  02.02.00  2020-08-10  visbwa  Support for FBL Legacy UseCase w/o OS, usage of new FBL UseCase defines;
                                MemMap encapsulation of BrsMainExceptionHandler(), enabled 1ms handler also for FBL,
                                BrsMainCyclic1ms() usable from extern, removed usage of BrsAsrApplCanInterruptLockCtr
                                for FBL (FBL is always in polling mode)
  02.02.01  2020-10-30  visbwa  Added include of Os.h for VTT (usage of ShutdownOS()), removed AUTHOR IDENTITY
  02.02.02  2021-01-14  visbwa  Adapted main() to also call Os_Init() for FBL with VTT
**********************************************************************************************************************/

/**********************************************************************************************************************
*  EXAMPLE CODE ONLY
*  -------------------------------------------------------------------------------------------------------------------
*  This Example Code is only intended for illustrating an example of a possible BSW integration and BSW configuration.
*  The Example Code has not passed any quality control measures and may be incomplete. The Example Code is neither
*  intended nor qualified for use in series production. The Example Code as well as any of its modifications and/or
*  implementations must be tested with diligent care and must comply with all quality requirements which are necessary
*  according to the state of the art before their use.
*********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#include "BrsMain.h"

#if !defined (_MICROSOFT_C_VTT_)
  #include "BrsHw.h"
#else
  #include "CANoeAPI.h"
  #include <stdio.h>
  #include "Os.h"
#endif

#if defined (BRS_ENABLE_CAN_SUPPORT)
  #include BRS_DRVCAN_HEADER_FILENAME
#endif

#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  #include "BrsTestsuite.h"
#endif

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (BRSMAIN_VERSION != 0x0202u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAIN_BUGFIX_VERSION != 0x02u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/

/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/
#if defined (BRS_ENABLE_1MS_HANDLER)
  #define BRSMAIN_CYCLIC_MAX_CALLBACKS 2u

  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
  typedef struct
  {
    void (*FunctionPointer[BRSMAIN_CYCLIC_MAX_CALLBACKS]) (void);
    uint8 FunctionCounter;
  }brsMain_Cyclic_Callbacks;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/

#if defined (BRS_ENABLE_CAN_SUPPORT) && !defined (BRS_ENABLE_FBL_SUPPORT)
  #define START_SEC_VAR_NOINIT_8BIT
  #include "MemMap.h"
  static uint8 BrsAsrApplCanInterruptLockCtr;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_CAN_SUPPORT&&!BRS_ENABLE_FBL_SUPPORT*/

/**********************************************************************************************************************
  GLOBAL CONST VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL VARIABLES
**********************************************************************************************************************/
#if defined (BRS_ENABLE_1MS_HANDLER)
  #define START_SEC_VAR_ZERO_INIT_16BIT
  #include "MemMap.h"
  /**
   * \var brsMain_CallCounter1ms
   *      Counter for calls of the function BrsMainCyclic1ms
   */
  static volatile uint16 brsMain_CallCounter1ms;

  /**
   * \var brsMain_CallCounter1sec
   *      Counter for 1000 calls of the function BrsMainCyclic1ms
   */
  static volatile uint16 brsMain_CallCounter1sec;
  #define STOP_SEC_VAR
  #include "MemMap.h"

  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_Background;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_10ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_100ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_250ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_500ms;
  static brsMain_Cyclic_Callbacks brsMain_Cyclic_Callbacks_1000ms;
  #define STOP_SEC_VAR
  #include "MemMap.h"
#endif /*BRS_ENABLE_1MS_HANDLER*/

/**********************************************************************************************************************
  LOCAL CONST VARIABLES
**********************************************************************************************************************/
# if defined (_MICROSOFT_C_VTT_)
  #define BRSMAIN_ERRORBUFFERSIZE  120
#endif

/**********************************************************************************************************************
  PROTOTYPES OF GLOBAL FUNCTIONS
**********************************************************************************************************************/
#if defined (BRS_FBL_NO_ECUMINIT)
extern void FblMain(void);
#endif

/**********************************************************************************************************************
  PROTOTYPES OF LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  FUNCTION DEFINITIONS
**********************************************************************************************************************/
#if !defined (_MICROSOFT_C_VTT_)
# if defined (BRS_ENABLE_SUPPORT_LEDS)
void BrsMainWrapperTogglePinLED(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_LED);
}
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
void BrsMainWrapperTogglePinWD(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_WD);
}
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
void BrsMainWrapperTogglePinCustom(void)
{
  BrsMainTogglePin(BRSMAIN_TOGGLEPIN_CUSTOM);
}
# endif
#endif /*!_MICROSOFT_C_VTT_*/

/*****************************************************************************/
/**
 * @brief      Main initialization routine.
 *             Contains initialisation of BRSModules and BrsMain specific initialization
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from main
 */
/*****************************************************************************/
void BrsMainInit(void)
{
#if defined (BRSMAIN_BRSMAININIT_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainInit();
#endif

#if defined (BRS_ENABLE_CAN_SUPPORT) && !defined (BRS_ENABLE_FBL_SUPPORT)
  /* UserDefined ExclusiveArea handling for CAN channels, according to AN-ISC-8-1149_ErrorHook_E_OS_DISABLED_INT.pdf */
  BrsAsrApplCanInterruptLockCtr = 0u;
#endif

#if !defined (BRS_FBL_NO_ECUMINIT) && !defined (BRS_FBL_WITH_ECUMINIT) && !defined (_MICROSOFT_C_VTT_)
# if !defined (BRS_ENABLE_PREFER_PLL_WATCHDOG_INIT)
  /* If preferred feature is acivated, initialization will take place in BrsMain_MemoryInit_StageOne_Hook(). */
#  if defined (BRSHW_PREINIT_AVAILABLE)
  BrsHwPreInitPowerOn();
#  endif

#  if defined (BRS_ENABLE_WATCHDOG)
  BrsHwWatchdogInitPowerOn();
#  endif

#  if defined (BRS_ENABLE_PLLCLOCKS)
  BrsHwPllInitPowerOn();
#  endif
# endif /*!BRS_ENABLE_PREFER_PLL_WATCHDOG_INIT*/

# if defined (BRS_ENABLE_PORT)
  BrsHwPortInitPowerOn();
# endif

# if defined (BRS_ENABLE_FBL_SUPPORT)
#  if defined (BRSHW_DISABLE_ECC_AVAILABLE)
  BrsHwDisableEccErrorReporting();
#  endif
# endif
#endif /*!BRS_FBL_NO_ECUMINIT&&!BRS_FBL_WITH_ECUMINIT&&!_MICROSOFT_C_VTT_*/

#if defined (BRS_ENABLE_1MS_HANDLER)
  brsMain_CallCounter1ms = 0u;
  brsMain_CallCounter1sec = 0u;

  brsMain_Cyclic_Callbacks_Background.FunctionCounter = 0u;
  brsMain_Cyclic_Callbacks_1ms.FunctionCounter        = 0u;
  brsMain_Cyclic_Callbacks_10ms.FunctionCounter       = 0u;
  brsMain_Cyclic_Callbacks_100ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_250ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_500ms.FunctionCounter      = 0u;
  brsMain_Cyclic_Callbacks_1000ms.FunctionCounter     = 0u;
#endif /*BRS_ENABLE_1MS_HANDLER*/

#if !defined (_MICROSOFT_C_VTT_)
# if defined (BRS_ENABLE_SUPPORT_LEDS)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinLED, BRSMAIN_CYCLETIME_500MS);
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinWD, BRSMAIN_CYCLETIME_250MS);
# endif

# if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  BrsMainRegisterCyclic(BrsMainWrapperTogglePinCustom, BRSMAIN_CYCLETIME_1000MS);
# endif
#endif /*!_MICROSOFT_C_VTT_*/
}

#if defined (BRS_ENABLE_1MS_HANDLER)
/*****************************************************************************/
/**
 * @brief      Routine to register cyclic callbacks.
 * @pre        Initialization of BrsMain was done threw call of BrsMainInit().
 * @param[in]  FunctionPointer has to be a pointer to a function of type
 *             void function(void).
 * @param[in]  Cycletime described the cycletime, the callback should be triggered.
 * @param[out] -
 * @return     -
 * @context    Function is called from modules that need cyclic callbacks.
 */
/*****************************************************************************/
void BrsMainRegisterCyclic(void (*FunctionPointer)(void), brsMain_Cyclic_Cycletime Cycletime)
{
#if defined (BRSMAIN_BRSMAINREGISTERCYCLIC_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainRegisterCyclic(FunctionPointer, Cycletime);
#endif

  switch (Cycletime)
  {
    case BRSMAIN_CYCLETIME_BACKGROUND:
      if (brsMain_Cyclic_Callbacks_Background.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_Background.FunctionPointer[brsMain_Cyclic_Callbacks_Background.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_Background.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_1MS:
      if (brsMain_Cyclic_Callbacks_1ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_1ms.FunctionPointer[brsMain_Cyclic_Callbacks_1ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_1ms.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_10MS:
      if (brsMain_Cyclic_Callbacks_10ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_10ms.FunctionPointer[brsMain_Cyclic_Callbacks_10ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_10ms.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_100MS:
      if (brsMain_Cyclic_Callbacks_100ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_100ms.FunctionPointer[brsMain_Cyclic_Callbacks_100ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_100ms.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_250MS:
      if (brsMain_Cyclic_Callbacks_250ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_250ms.FunctionPointer[brsMain_Cyclic_Callbacks_250ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_250ms.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_500MS:
      if (brsMain_Cyclic_Callbacks_500ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_500ms.FunctionPointer[brsMain_Cyclic_Callbacks_500ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_500ms.FunctionCounter++;
      break;

    case BRSMAIN_CYCLETIME_1000MS:
      if (brsMain_Cyclic_Callbacks_1000ms.FunctionCounter >= BRSMAIN_CYCLIC_MAX_CALLBACKS)
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      brsMain_Cyclic_Callbacks_1000ms.FunctionPointer[brsMain_Cyclic_Callbacks_1000ms.FunctionCounter] = FunctionPointer;
      brsMain_Cyclic_Callbacks_1000ms.FunctionCounter++;
      break;

    default:
      BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAIN, (uint16)(__LINE__));
      break;
  }
}
#endif /*BRS_ENABLE_1MS_HANDLER*/

#if !defined (BRS_ENABLE_FBL_SUPPORT)
/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo().
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS.
 */
/*****************************************************************************/
TASK(Default_Init_Task)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task();
#endif

#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  /* Workaround for RTE ESCAN00078832 */
  /* Use this code, if you get a Det Error at the end of Rte_Start() on MasterCore */
  /* Rte_Start() on the SlaveCores has to be called first, before Rte_Start() on MasterCore */
  /* SET THIS InitTask TO FULL PREEMPTIVE (OsTaskSchedule) within OsConfig! */
  /*while(Rte_InitState_1 != RTE_STATE_INIT)
  {
    (void)Schedule();
  }*/
#endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/

#if defined (BRS_ENABLE_TESTSUITE_SUPPORT)
  BrsTestsuiteInit();
#endif

#if defined (BRS_ENABLE_HSM_SUPPORT)
  vHsm_StartupTwo();
#else
  EcuM_StartupTwo();
#endif

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources().
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS. It is separated from
 *             Default_Init_Task() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

# if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 2nd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 2nd Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core1)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE1_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core1();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 2nd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 2nd Core. It is separated from
 *             Default_Init_Task_Core1() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core1_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE1_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core1_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 3rd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 3rd Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core2)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE2_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core2();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 3rd Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 3rd Core. It is separated from
 *             Default_Init_Task_Core2() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core2_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE2_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core2_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 4th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 4th Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core3)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE3_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core3();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 4th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 4th Core. It is separated from
 *             Default_Init_Task_Core3() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core3_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE3_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core3_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 5th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 5th Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core4)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE4_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core4();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 5th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 5th Core. It is separated from
 *             Default_Init_Task_Core4() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core4_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE4_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core4_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 6th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 6th Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core5)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE5_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core5();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 6th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 6th Core. It is separated from
 *             Default_Init_Task_Core5() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core5_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE5_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core5_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call EcuM_StartupTwo() on the 7th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 7th Core.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core6)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE6_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core6();
#endif

  EcuM_StartupTwo();

  (void)TerminateTask();
}

/*****************************************************************************/
/**
 * @brief      InitTask to call Os_InitialEnableInterruptSources() on the 7th Core.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS on the 7th Core. It is separated from
 *             Default_Init_Task_Core6() to allow the SafeContext partitioning UseCase.
 */
/*****************************************************************************/
TASK(Default_Init_Task_Core6_Trusted)
{
#if defined (BRSMAIN_DEFAULT_INIT_TASK_CORE6_TRUSTED_CALLOUT)
  BrsTestsuite_BrsMain_Default_Init_Task_Core6_Trusted();
#endif

  Os_InitialEnableInterruptSources(FALSE);

  (void)TerminateTask();
}
# endif /*BRS_ENABLE_OS_MULTICORESUPPORT*/
#endif /*!BRS_ENABLE_FBL_SUPPORT*/

#if defined (BRS_ENABLE_1MS_HANDLER)
/*****************************************************************************/
/**
 * @brief      One millisecond handler for BrsMain
 *               - Executes retransmission of BRS TCC messages
 *               - Toggling of LED (alive signal)
 *               - BRS Test code (1s cyclic negative TCC response message)
 * @pre        Initialization of BrsMain was done threw call of BrsMainInit().
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called each millisecond either from the main loop or from the BRS main task (TASK(mainTask))
 */
/*****************************************************************************/
void BrsMainCyclic1ms(void)
{
  uint8 cycliccounter;

#if defined (BRSMAIN_BRSMAINCYCLIC1MS_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainCyclic1ms();
#endif

  brsMain_CallCounter1ms++;

  for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_1ms.FunctionCounter; cycliccounter++)
    brsMain_Cyclic_Callbacks_1ms.FunctionPointer[cycliccounter]();

  if (brsMain_CallCounter1ms %10 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_10ms.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_10ms.FunctionPointer[cycliccounter]();
  }

  if (brsMain_CallCounter1ms %100 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_100ms.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_100ms.FunctionPointer[cycliccounter]();
  }

  if (brsMain_CallCounter1ms %250 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_250ms.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_250ms.FunctionPointer[cycliccounter]();
  }

  if (brsMain_CallCounter1ms %500 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_500ms.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_500ms.FunctionPointer[cycliccounter]();
  }

  if (brsMain_CallCounter1ms %1000 == 0)
  {
    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_1000ms.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_1000ms.FunctionPointer[cycliccounter]();
    brsMain_CallCounter1ms = 0u;
    brsMain_CallCounter1sec++;
  }
}

# if !defined (BRS_ENABLE_FBL_SUPPORT)
/*****************************************************************************/
/**
 * @brief      BrsMainTask executes the 1 millisecond handler
 *             The function initiates calls to BrsMainCyclic1ms
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    The task is started once by the OS and activated by
 *             the OS event EvCyclicAlarm_1ms
 */
/*****************************************************************************/
TASK(BrsMainTask)
{
  EventMaskType ev;

#if defined (BRSMAIN_BRSMAINTASK_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainTask();
#endif

  (void)SetRelAlarm(BrsCyclicAlarm_1ms, OS_MS2TICKS_SystemTimer(1), OS_MS2TICKS_SystemTimer(1));

  for(;;)
  {
    (void)WaitEvent(BrsEvCyclicAlarm_1ms);
    (void)GetEvent(BrsMainTask, &ev);
    (void)ClearEvent(ev);
    if(ev & BrsEvCyclicAlarm_1ms)
    {
      /* 1ms event detected, call the ms handler */
      BrsMainCyclic1ms();
    }
  }
}

TASK(BrsMainBackgroundTask)
{
  uint8 cycliccounter;

#if defined (BRSMAIN_BRSMAINBACKGROUNDTASK_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainBackgroundTask();
#endif

  for(;;)
  {
# if defined (_MICROSOFT_C_VTT_)
    CANoeAPI_ConsumeTicks(100);
# endif

    for (cycliccounter=0u; cycliccounter<brsMain_Cyclic_Callbacks_Background.FunctionCounter; cycliccounter++)
      brsMain_Cyclic_Callbacks_Background.FunctionPointer[cycliccounter]();

    (void)Schedule();
  }
}
# endif /*!BRS_ENABLE_FBL_SUPPORT*/
#endif /*BRS_ENABLE_1MS_HANDLER*/


#if defined (BRS_ENABLE_SUPPORT_LEDS)          || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN) || \
    defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
# if !defined (BRS_ENABLE_PORT)
  #define BRSHW_PORT_LOGIC_HIGH STD_HIGH
  #define BRSHW_PORT_LOGIC_LOW STD_LOW
# endif
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
void BrsMainTogglePin(brsMain_TogglePin Pin)
{
  #define START_SEC_VAR_NOINIT_UNSPECIFIED
  #include "MemMap.h"
#if defined (BRS_ENABLE_SUPPORT_LEDS)
  static uint8 BrsMain_ToggleSwitch_LED = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
  static uint8 BrsMain_ToggleSwitch_WD = BRSHW_PORT_LOGIC_HIGH;
#endif
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
  static uint8 BrsMain_ToggleSwitch_CUSTOM = BRSHW_PORT_LOGIC_HIGH;
#endif
  #define STOP_SEC_VAR
  #include "MemMap.h"

  switch (Pin)
  {
#if defined (BRS_ENABLE_SUPPORT_LEDS)
    case BRSMAIN_TOGGLEPIN_LED:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_LED, BrsMain_ToggleSwitch_LED & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleLED, BrsMain_ToggleSwitch_LED & 0x01);
# endif
      BrsMain_ToggleSwitch_LED++;
      break;
#endif /*BRS_ENABLE_SUPPORT_LEDS*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN)
    case BRSMAIN_TOGGLEPIN_WD:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_WD, BrsMain_ToggleSwitch_WD & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleWdPin, BrsMain_ToggleSwitch_WD & 0x01);
# endif
      BrsMain_ToggleSwitch_WD++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN*/
#if defined (BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN)
    case BRSMAIN_TOGGLEPIN_CUSTOM:
# if defined (BRS_ENABLE_PORT)
      BrsHwPort_SetLevel(BRSHW_PORT_TOGGLE_CUSTOM, BrsMain_ToggleSwitch_CUSTOM & 0x01);
# else
      Dio_WriteChannel(BrsHw_DioChannel_ToggleCustomPin, BrsMain_ToggleSwitch_CUSTOM & 0x01);
# endif
      BrsMain_ToggleSwitch_CUSTOM++;
      break;
#endif /*BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/
    default:
      BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSHW, (uint16)(__LINE__));
      break;
  }
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_SUPPORT_LEDS||BRS_ENABLE_SUPPORT_TOGGLE_WD_PIN||BRS_ENABLE_SUPPORT_TOGGLE_CUSTOM_PIN*/

#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif
/*****************************************************************************/
/**
 * @brief      This is the central exeption handler of BRS.
 *             All BRS modules and all CANbedded specific fatal error handler will
 *             call this API in case an assertion has failed.
 * @pre        -
 * @param[in]  ErrorCode shall hold the caller specific error code (uint8)
 * @param[in]  ModuleCode shall describe the caller; please use the CI constant as parameter (uint8)
 * @param[in]  LineNumber shall be the line where the assertion has failed, or,
 *             if not available on caller location, the line where this API is
 *             called from
 * @param[out] -
 * @return     -
 * @context    This function implements an endless loop with locked interrupts.
 *             The recommendation is to set a breakpoint on top of this function
 *             to see if any assertion has failed during the code execution.
 *             Due to an assertion has failed and the endless loop runs with
 *             locked global interrupts there will be no life after the call ...
 */
/*****************************************************************************/
void BrsMainExceptionHandler(uint8 ErrorCode, uint8 ModuleCode, uint16 LineNumber)
{
#if defined (BRSMAIN_BRSMAINEXCEPTIONHANDLER_CALLOUT)
  BrsTestsuite_BrsMain_BrsMainExceptionHandler();
#endif

#if defined (BRS_ENABLE_SAFECTXSUPPORT)
  while(1)
  {}

#else
# if defined (_MICROSOFT_C_VTT_)
  char error[BRSMAIN_ERRORBUFFERSIZE];

  sprintf_s(error, BRSMAIN_ERRORBUFFERSIZE, "BrsMainExceptionHandler Code: [0x%x] ModuleCode: [0x%x] LineNumber: [0x%x]", ErrorCode, ModuleCode, LineNumber);

  CANoeAPI_WriteString(error);
  ShutdownOS(0);

# else
  volatile uint8 BrsMain_Continue;
  BrsMain_Continue = 0;

#if !defined (BRS_ENABLE_FBL_SUPPORT) /* FBL is always running in polling mode with interrupts disabled */
  DisableAllInterrupts();
#endif

  while (BrsMain_Continue == 0)
  {
    /* Set BrsMain_Continue to 1 to continue here.
     *  If the debugger is not able to show the stack properly, this mechanism can be used to find the
     *  source of the exception. */
  }
# endif /*_MICROSOFT_C_VTT_*/
#endif /*BRS_ENABLE_SAFECTXSUPPORT*/
}
#if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
#endif

/*****************************************************************************/
/**
 * @brief      This is just a wrapper to ease calls to
 *             BrsMainExceptionHandler() from assembler StartUpCode.
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    This function will call BrsMainExceptionHandler() with the
 *             error code for reaching illegal assembler in StartUpCpde.
 */
/*****************************************************************************/
void BrsMainExceptionStartup(void)
{
  BrsMainExceptionHandler(kBrsIllegalAssemblerReached, BRSERROR_MODULE_BRSSTARTUP, (uint16)0);
}

/*****************************************************************************/
/**
 * @brief      Main function
 * @pre        -
 * @param[in]  -
 * @param[out] -
 * @return     always 0 as the function is not expected to return
 * @context    Called by the startup code
 */
/*****************************************************************************/
int main(void)
{
#if defined (BRSMAIN_MAIN_CALLOUT)
  BrsTestsuite_BrsMain_main();
#endif

#if !defined (_MICROSOFT_C_VTT_)
  BrsHwDisableInterruptAtPowerOn();

# if (BRS_CPU_CORE_AMOUNT>1)
  if (BrsHw_GetCore() == BRSHW_INIT_CORE_ID)
# endif
#endif /*!_MICROSOFT_C_VTT_*/
  {
    BrsMainInit();
  }

#if defined (BRS_FBL_NO_ECUMINIT)
  FblMain();

#else
# if !defined (BRS_ENABLE_FBL_SUPPORT) || defined (_MICROSOFT_C_VTT_)
  Os_InitMemory();
  Os_Init();
# endif

# if defined (BRS_ENABLE_HSM_SUPPORT)
  vHsm_Init();
# else
  EcuM_Init(); /* never returns */
# endif
#endif /*else BRS_FBL_NO_ECUMINIT*/

  return 0;
}

/***********************************************************************************************************************
 *  Additional UserCode can be placed here
 **********************************************************************************************************************/

#if defined (BRS_ENABLE_CAN_SUPPORT)
/***********************************************************************************************************************
 * UserDefined ExclusiveArea handling for CAN channels, according to AN-ISC-8-1149_ErrorHook_E_OS_DISABLED_INT.pdf
 **********************************************************************************************************************/
/* Macro is generated in vBrsCfg.h, to support drivers with infix.
   Sample w/o infix: void SchM_Enter_Can_CAN_EXCLUSIVE_AREA_0(void)
                     Can_DisableControllerInterrupts(0u);
   Sample w/ infix:  void SchM_Enter_Can_30_Mcan_CAN_30_MCAN_EXCLUSIVE_AREA_0(void)
                     Can_30_Mcan_DisableControllerInterrupts(0u);*/
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_0)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Enter,EXCLUSIVE_AREA_6)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

BRS_DRVCAN_EXCLUSIVE_AREA_INFIX(Exit,EXCLUSIVE_AREA_6)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_CAN_SUPPORT*/

#if defined (BRS_ENABLE_CAN_SUPPORT)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
void SchM_Enter_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

void SchM_Exit_CanIf_CANIF_EXCLUSIVE_AREA_0(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_CAN_SUPPORT*/

#if defined (BRS_ENABLE_CAN_SUPPORT)
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (++BrsAsrApplCanInterruptLockCtr == 1u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Disable)(0u);
  }
#endif
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_4(void)
{
#if !defined (BRS_ENABLE_FBL_SUPPORT)
  if (--BrsAsrApplCanInterruptLockCtr == 0u)
  {
    BRS_DRVCAN_ControllerInterrupts_INFIX(Enable)(0u);
  }
#endif
}

void SchM_Enter_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_CanSM_CANSM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
#endif /*BRS_ENABLE_CAN_SUPPORT*/

# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_START_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
void SchM_Enter_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}

void SchM_Exit_ComM_COMM_EXCLUSIVE_AREA_1(void)
{
  /* Protects against task interruptions -> no locking needed, because all main functions are on same task */
}
# if defined (BRS_ENABLE_FBL_SUPPORT)
  #define BRS_STOP_SEC_RAM_CODE
  #include "Brs_MemMap.h"
# endif
