
/**********************************************************************************************************************
  COPYRIGHT
-----------------------------------------------------------------------------------------------------------------------
  \par      copyright
  \verbatim
  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.

                This software is copyright protected and proprietary to Vector Informatik GmbH.
                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
                All other rights remain with Vector Informatik GmbH.
  \endverbatim
-----------------------------------------------------------------------------------------------------------------------
  FILE DESCRIPTION
-----------------------------------------------------------------------------------------------------------------------
  \file  File:  BrsMainStartup.c
      Project:  Vector Basic Runtime System
       Module:  BrsMain

  \brief Description:  Vector Basic Runtime System module source for startup routines.

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
  01.00.00  2017-11-14  visfsn  Initial creation
  01.01.00  2018-03-27  visbwa  Renamed BrsAsrStartup into BrsStartup, added version check, reworked includes,
                                added example code text
  01.01.01  2018-05-16  visbwa  Added extern declaration of brsHwZeroRamAreaSet and brsHwInitRamAreaSet
  01.01.02  2018-07-02  visces  Removed outdated brsHwZeroRamAreaSet and brsHwInitRamAreaSet
  01.02.00  2018-08-16  visbwa  Replaced include of RamInitSections.h by vLinkGen_RamInitSections.h (vLinkGen used!)
  01.03.00  2018-10-08  visbwa  Changed include of BrsCfg.h into vBrsCfg.h in BrsMainStartup.h (vBaseEnv 1.1.0)
  01.04.00  2019-05-06  visbwa  Support for vLinkGen 1.04.00 (renamed struct names of vlinkGen areas),
                                added support for zero init blocks, renamed Brs_RamZeroInit() to Brs_MemoryZeroInit(),
                                renamed Brs_RomToRamInit() to Brs_MemoryInit(), check for missing hard reset detection
  01.04.01  2019-05-10  visbwa  Changed include of vLinkGen header to support new vLinkGen file structure
  01.04.02  2019-07-22  visbwa  Added check for configured VLINKGEN_ZERO_INIT_BLOCK_COUNT_HARD_RESET
  01.05.00  2019-08-07  visbwa  Added InitPattern parameter to Brs_MemoryZeroInit() and added the new configuration
                                values for the init pattern to the depending calls,
                                added sample implementation for Hard-reset blocks and areas
  01.06.00  2019-10-07  visbwa  Added support of platform individual ZeroInit function BrsHw_AsmMemoryZeroInitLoop()
                                in Brs_MemoryZeroInit(), triggered with BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE
  01.07.00  2020-02-04  visbwa  Added filtering of MultiCore parts through C_BRSASR_USECASE_SINGLECORE_COMMENT,
                                removed error directive at usage of BrsHwGetResetReason()
  02.00.00  2020-05-12  visbwa  Major updates for vBaseEnv 2.0.0 (new BrsMain hooks concept, vLinkGen 2.0)
            2020-06-03  visbwa  Updated vLinkGen define and struct names to new vLinkGen 2.0 naming schema,
                                added version check for vLinkGen version
  02.01.00  2020-07-03  visbwa  Reduced calls of BrsHw_GetCore() inside Brs_PreMainStartup() to a single call
  02.01.01  2020-09-25  visbwa  Encapsuled memPtr in Brs_MemoryZeroInit() to prevent compiler warnings
  02.01.02  2020-12-07  visbwa  Increased for loop variable in Brs_MemoryZeroInit() and Brs_MemoryInit() from uint8 to
                                uint32 (depending datatypes will be increased in vLinkGen), removed AUTHOR IDENTITY
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
#include "BrsMainStartup.h"
#include "BrsHw.h"
#include "BrsMain.h"

#include "vLinkGen_Lcfg.h"

/**********************************************************************************************************************
  VERSION CHECK
**********************************************************************************************************************/
#if (BRSMAINSTARTUP_VERSION != 0x0201u)
  #error "Header and source file are inconsistent!"
#endif
#if (BRSMAINSTARTUP_BUGFIX_VERSION != 0x02u)
  #error "Different versions of bugfix in Header and Source used!"
#endif

/**********************************************************************************************************************
  CONFIGURATION CHECK
**********************************************************************************************************************/
#if !defined (BRS_INIT_PATTERN_BLOCKS)           || \
    !defined (BRS_INIT_PATTERN_HARDRESET_BLOCKS) || \
    !defined (BRS_INIT_PATTERN_AREAS)            || \
    !defined (BRS_INIT_PATTERN_HARDRESET_AREAS)
  #error "Your environment is missing the mandatory init pattern. They should be generated out of vBRS in Configurator5."
#endif

#if (VLINKGEN_CFG_MAJOR_VERSION != 2u)
  #error "This StartUpCode is dependent to the vLinkGen version! vLinkGen major version does not fit!"
#else
# if (VLINKGEN_CFG_MINOR_VERSION < 0u)
  #error "This StartUpCode is dependent to the vLinkGen version! Your vLinkGen minor version is too old!"
# endif
#endif


/**********************************************************************************************************************
  DEFINITION + MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONST VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL CONST VARIABLES
**********************************************************************************************************************/

/**********************************************************************************************************************
  PROTOTYPES OF GLOBAL FUNCTIONS
**********************************************************************************************************************/
extern void BrsMain_MemoryInit_StageZero_Hook(uint32);
extern void BrsMain_MemoryInit_StageOne_Hook(uint32);
extern void BrsMain_MemoryInit_StageHardReset_Hook(uint32);
extern void BrsMain_MemoryInit_StageTwo_Hook(uint32);
extern void BrsMain_MemoryInit_StageThree_Hook(uint32);
extern void BrsMain_PreMainHook(uint32);

/**********************************************************************************************************************
  PROTOTYPES OF LOCAL FUNCTIONS
**********************************************************************************************************************/
void Brs_MemoryZeroInit(const vLinkGen_MemAreaSet *, uint32, uint32);
void Brs_MemoryInit(const vLinkGen_RamMemAreaSet *, uint32);

/**********************************************************************************************************************
  FUNCTION DEFINITIONS
**********************************************************************************************************************/
/*****************************************************************************/
/**
 * @brief      Unified routine for Pre Main() Startup.
 * @pre        Stack pointer needs to be initilialized in StartUpCode before.
 * @param[in]  -
 * @param[out] -
 * @return     -
 * @context    Function is called from assembler startup code
 *             Called by all cores
 *             All APIs are called with current Core ID
 */
/*****************************************************************************/
void Brs_PreMainStartup(void)
{
  uint32 coreID;
#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS>1uL) || \
    (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS>1uL) || \
    (VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS>1uL)
  brsHw_ResetReasonType ResetReason;
#endif

  coreID = BrsHw_GetCore();

  BrsMain_MemoryInit_StageZero_Hook(coreID);

#if (VLINKGEN_CFG_NUM_ZERO_INIT_ZERO_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Zero_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "ZERO" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Zero_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif

#if (VLINKGEN_CFG_NUM_INIT_ZERO_GROUPS>1uL)
  /* vLinkGen_Init_Zero_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "ZERO" */
  Brs_MemoryInit(&vLinkGen_Init_Zero_GroupsSet, coreID);
#endif

  BrsMain_MemoryInit_StageOne_Hook(coreID);

#if (VLINKGEN_CFG_NUM_ZERO_INIT_ONE_BLOCKS>1uL)
  /* vLinkGen_ZeroInit_One_BlocksSet contains vLinkGen memory region blocks, configured with Init Stage "ONE" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_One_BlocksSet, BRS_INIT_PATTERN_BLOCKS, coreID);
#endif

#if (VLINKGEN_CFG_NUM_ZERO_INIT_ONE_GROUPS>1uL)
  /* vLinkGen_ZeroInit_One_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "ONE" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_One_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif

#if (VLINKGEN_CFG_NUM_INIT_ONE_GROUPS>1uL)
  /* vLinkGen_Init_One_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "ONE" */
  Brs_MemoryInit(&vLinkGen_Init_One_GroupsSet, coreID);
#endif

  BrsMain_MemoryInit_StageHardReset_Hook(coreID);

#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS>1uL) || \
    (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS>1uL) || \
    (VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS>1uL)
  ResetReason = BrsHwGetResetReason();
#endif

#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_BLOCKS>1uL)
  if (ResetReason != BRSHW_RESET_SW)
  {
    /* vLinkGen_ZeroInit_HardReset_BlocksSet contains vLinkGen memory region blocks, configured with Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryZeroInit(&vLinkGen_ZeroInit_HardReset_BlocksSet, BRS_INIT_PATTERN_HARDRESET_BLOCKS, coreID);
  }
#endif

#if (VLINKGEN_CFG_NUM_ZERO_INIT_HARD_RESET_GROUPS>1uL)
  if (ResetReason != BRSHW_RESET_SW)
  {
    /* vLinkGen_ZeroInit_HardReset_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryZeroInit(&vLinkGen_ZeroInit_HardReset_GroupsSet, BRS_INIT_PATTERN_HARDRESET_AREAS, coreID);
  }
#endif

#if (VLINKGEN_CFG_NUM_INIT_HARD_RESET_GROUPS>1uL)
  if (ResetReason != BRSHW_RESET_SW)
  {
    /* vLinkGen_Init_HardReset_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "HARD_RESET_ONLY" */
    Brs_MemoryInit(&vLinkGen_Init_HardReset_GroupsSet, coreID);
  }
#endif

  BrsMain_MemoryInit_StageTwo_Hook(coreID);

#if (VLINKGEN_CFG_NUM_ZERO_INIT_TWO_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Two_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "TWO" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Two_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif

#if (VLINKGEN_CFG_NUM_INIT_TWO_GROUPS>1uL)
  /* vLinkGen_Init_Two_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "TWO" */
  Brs_MemoryInit(&vLinkGen_Init_Two_GroupsSet, coreID);
#endif

  BrsMain_MemoryInit_StageThree_Hook(coreID);

#if (VLINKGEN_CFG_NUM_ZERO_INIT_THREE_GROUPS>1uL)
  /* vLinkGen_ZeroInit_Three_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "ZERO_INIT" and Init Stage "THREE" */
  Brs_MemoryZeroInit(&vLinkGen_ZeroInit_Three_GroupsSet, BRS_INIT_PATTERN_AREAS, coreID);
#endif

#if (VLINKGEN_CFG_NUM_INIT_THREE_GROUPS>1uL)
  /* vLinkGen_Init_Three_GroupsSet contains vLinkGen VarSectionGroups, configured with Init Policy "INIT" and Init Stage "THREE" */
  Brs_MemoryInit(&vLinkGen_Init_Three_GroupsSet, coreID);
#endif

  BrsMain_PreMainHook(coreID);

#if defined (BRS_ENABLE_OS_MULTICORESUPPORT)
  if (coreID == BRSHW_INIT_CORE_ID)
  {
    BrsHw_UnlockCores(coreID); /* unlocks all previously locked cores */
  }
#endif
  main();
}

/*****************************************************************************/
/**
 * @brief      Generic routine for RAM zeroing.
 * @pre        -
 * @param[in]  memAreaSet shall point to the first element of a vLinkGen_MemAreaSet struct array
 * @param[in]  InitPattern describes the pattern, to be used for the memory initialization
 * @param[in]  coreId shall describe the ID of the current CPU
 * @param[out] -
 * @return     -
 * @context    Function is called from Brs_PreMainStartup() to initialize memory ares,
 *             generated out of vLinkGen configuration
 */
/*****************************************************************************/
void Brs_MemoryZeroInit(const vLinkGen_MemAreaSet *memAreaSet, uint32 InitPattern, uint32 coreId)
{
  uint8 i;
#if !defined (BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE)
  volatile uint32 *memPtr;
#endif

  for (i=0; i<memAreaSet->Num; i++)
  {
    if (memAreaSet->Areas[i].Core==coreId && (memAreaSet->Areas[i].End - memAreaSet->Areas[i].Start) > 0)
    {
#if defined (BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE)
      BrsHw_AsmMemoryZeroInitLoop(memAreaSet->Areas[i].Start, memAreaSet->Areas[i].End, InitPattern);

#else
      memPtr = (volatile uint32*)memAreaSet->Areas[i].Start;
      while ((uint32)memPtr < memAreaSet->Areas[i].End)
      {
        *memPtr = InitPattern;
        memPtr++;
      }
#endif /*else BRSHW_ASM_MEMORY_ZERO_INIT_LOOP_AVAILABLE*/
    }
  }
}

/*****************************************************************************/
/**
 * @brief      Generic routine for ROM to RAM initialization.
 * @pre        -
 * @param[in]  memAreasSet shall point to the first element of a vLinkGen_RamMemAreaSet struct array
 * @param[in]  coreId shall describe the ID of the current CPU
 * @param[out] -
 * @return     -
 * @context    Function is called from Brs_PreMainStartup() to initialize memory ares,
 *             generated out of vLinkGen configuration
 */
/*****************************************************************************/
void Brs_MemoryInit(const vLinkGen_RamMemAreaSet *memAreasSet, uint32 coreId)
{
  volatile uint32 *memPtr;
  volatile uint32 *romPtr;
  uint8 i;

  for (i=0; i<memAreasSet->Num; i++)
  {
    if (memAreasSet->Areas[i].Core==coreId && ((memAreasSet->Areas[i].End - memAreasSet->Areas[i].Start) > 0))
    {
      if ((memAreasSet->Areas[i].End - memAreasSet->Areas[i].Start) != (memAreasSet->Areas[i].Romend - memAreasSet->Areas[i].Romstart))
      {
        /* Defined size in rom does not match ram size */
        BrsMainExceptionHandler(kBrsIllegalParameter, BRSERROR_MODULE_BRSMAINSTARTUP, (uint16)(__LINE__));
      }

      memPtr = (volatile uint32*)memAreasSet->Areas[i].Start;
      romPtr = (volatile uint32*)memAreasSet->Areas[i].Romstart;
      while ((uint32)memPtr < memAreasSet->Areas[i].End)
      {
        *memPtr = *romPtr;
        memPtr++;
        romPtr++;
      }
    }
  }
}
