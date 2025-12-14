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
 *            Module: EthTrcv_30_Tja1100
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthTrcv_30_Tja1100_Lcfg.h
 *   Generation Time: 2025-12-14 15:58:18
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETHTRCV_30_TJA1100_LCFG_H)
# define ETHTRCV_30_TJA1100_LCFG_H
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_GenTypes.h"

# if !defined (ETHTRCV_30_TJA1100_LOCAL_INLINE)
#  define ETHTRCV_30_TJA1100_LOCAL_INLINE LOCAL_INLINE
# endif
/**********************************************************************************************************************
 *  RTM MEASUREMENT POINT MACROS
 *********************************************************************************************************************/

# define EthTrcv_30_Tja1100_Rtm_Start(Type)

# define EthTrcv_30_Tja1100_Rtm_Stop(Type)

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTrcv_30_Tja1100_ConfigDataPtr
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_ConfigDataPtr
  \brief  Points to the currently active configuration for EthTrcv_30_Tja1100
  \details
  Pointer is intialized during EthTrcv_30_Tja1100_Init() and holds the active configuration for EthTrcv_30_Tja1100
  were all configuration data is retrieved from during runtime.
*/ 
# define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern P2CONST(EthTrcv_30_Tja1100_ConfigType, ETHTRCV_30_TJA1100_VAR_NOINIT, ETHTRCV_30_TJA1100_INIT_DATA) EthTrcv_30_Tja1100_ConfigDataPtr;
# define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
# include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthTrcv_30_Tja1100PCGetRootDataMacros  EthTrcv_30_Tja1100 Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define EthTrcv_30_Tja1100_GetAccessEntityFctsOfPCConfig()            EthTrcv_30_Tja1100_ConfigDataPtr->AccessEntityFctsOfPCConfig
#define EthTrcv_30_Tja1100_GetCableDiagLoopCyclesOfPCConfig()         EthTrcv_30_Tja1100_ConfigDataPtr->CableDiagLoopCyclesOfPCConfig
#define EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()                     EthTrcv_30_Tja1100_ConfigDataPtr->EthTrcvOfPCConfig
#define EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()              EthTrcv_30_Tja1100_ConfigDataPtr->EthTrcvTja1100OfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessLoopCountOfPCConfig()           EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessLoopCountOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorCycleCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCalloutOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorFailureCalloutOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorFailureDebounceCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceLimiterOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorFailureDebounceLimiterOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorLoopLimiterOfPCConfig()  EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorLoopLimiterOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorRecoveryDebounceCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceLimiterOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->HwAccessMonitorRecoveryDebounceLimiterOfPCConfig
#define EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()             EthTrcv_30_Tja1100_ConfigDataPtr->LinkFailCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()     EthTrcv_30_Tja1100_ConfigDataPtr->LinkStartupDelayCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()            EthTrcv_30_Tja1100_ConfigDataPtr->LinkStartupStateOfPCConfig
#define EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()       EthTrcv_30_Tja1100_ConfigDataPtr->LinkStateDelayCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()     EthTrcv_30_Tja1100_ConfigDataPtr->LinkStateTimeoutCounterOfPCConfig
#define EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMsOfPCConfig()  EthTrcv_30_Tja1100_ConfigDataPtr->MainFunctionLinkHandlingMsOfPCConfig
#define EthTrcv_30_Tja1100_GetMaxPhySignalQualityMeanOfPCConfig()     EthTrcv_30_Tja1100_ConfigDataPtr->MaxPhySignalQualityMeanOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfAccessEntityFctsOfPCConfig()      EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfAccessEntityFctsOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()               EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfEthTrcvOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()        EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfEthTrcvTja1100OfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureCalloutOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfHwAccessMonitorFailureCalloutOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfUserAccessCalloutsOfPCConfig()    EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfUserAccessCalloutsOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfUserInitCalloutsOfPCConfig()      EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfUserInitCalloutsOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfWakeupCalloutOfPCConfig()         EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfWakeupCalloutOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfWakeupMapOfPCConfig()             EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfWakeupMapOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfWakeupOfPCConfig()                EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfWakeupOfPCConfig
#define EthTrcv_30_Tja1100_GetSizeOfWakeupVerificationCalloutOfPCConfig() EthTrcv_30_Tja1100_ConfigDataPtr->SizeOfWakeupVerificationCalloutOfPCConfig
#define EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()         EthTrcv_30_Tja1100_ConfigDataPtr->TrcvHwAccessibilityOfPCConfig
#define EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()               EthTrcv_30_Tja1100_ConfigDataPtr->TrcvLinkStateOfPCConfig
#define EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()                    EthTrcv_30_Tja1100_ConfigDataPtr->TrcvModeOfPCConfig
#define EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()                   EthTrcv_30_Tja1100_ConfigDataPtr->TrcvStateOfPCConfig
#define EthTrcv_30_Tja1100_GetUserAccessCalloutsOfPCConfig()          EthTrcv_30_Tja1100_ConfigDataPtr->UserAccessCalloutsOfPCConfig
#define EthTrcv_30_Tja1100_GetUserInitCalloutsOfPCConfig()            EthTrcv_30_Tja1100_ConfigDataPtr->UserInitCalloutsOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupCalloutOfPCConfig()               EthTrcv_30_Tja1100_ConfigDataPtr->WakeupCalloutOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupMapOfPCConfig()                   EthTrcv_30_Tja1100_ConfigDataPtr->WakeupMapOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()                  EthTrcv_30_Tja1100_ConfigDataPtr->WakeupModeOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupOfPCConfig()                      EthTrcv_30_Tja1100_ConfigDataPtr->WakeupOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()           EthTrcv_30_Tja1100_ConfigDataPtr->WakeupReasonFlagsOfPCConfig
#define EthTrcv_30_Tja1100_GetWakeupVerificationCalloutOfPCConfig()   EthTrcv_30_Tja1100_ConfigDataPtr->WakeupVerificationCalloutOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetDuplicatedRootDataMacros  EthTrcv_30_Tja1100 Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureDebounceCounterOfPCConfig() EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter */
#define EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorRecoveryDebounceCounterOfPCConfig() EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter */
#define EthTrcv_30_Tja1100_GetSizeOfLinkFailCounterOfPCConfig()       EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_LinkFailCounter */
#define EthTrcv_30_Tja1100_GetSizeOfLinkStartupDelayCounterOfPCConfig() EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_LinkStartupDelayCounter */
#define EthTrcv_30_Tja1100_GetSizeOfLinkStartupStateOfPCConfig()      EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_LinkStartupState */
#define EthTrcv_30_Tja1100_GetSizeOfLinkStateDelayCounterOfPCConfig() EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_LinkStateDelayCounter */
#define EthTrcv_30_Tja1100_GetSizeOfLinkStateTimeoutCounterOfPCConfig() EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
#define EthTrcv_30_Tja1100_GetSizeOfTrcvHwAccessibilityOfPCConfig()   EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_TrcvHwAccessibility */
#define EthTrcv_30_Tja1100_GetSizeOfTrcvLinkStateOfPCConfig()         EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_TrcvLinkState */
#define EthTrcv_30_Tja1100_GetSizeOfTrcvModeOfPCConfig()              EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_TrcvMode */
#define EthTrcv_30_Tja1100_GetSizeOfTrcvStateOfPCConfig()             EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_TrcvState */
#define EthTrcv_30_Tja1100_GetSizeOfWakeupModeOfPCConfig()            EthTrcv_30_Tja1100_GetSizeOfWakeupOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupMode */
#define EthTrcv_30_Tja1100_GetSizeOfWakeupReasonFlagsOfPCConfig()     EthTrcv_30_Tja1100_GetSizeOfWakeupOfPCConfig()  /**< the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupReasonFlags */
/** 
  \}
*/ 

  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetDataInlineFunctionPrototypes  Get Data Inline Function Prototypes
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ReadTrcvRegFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetReadTrcvRegOfAccessEntityFcts(EthTrcv_30_Tja1100_AccessEntityFctsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WriteTrcvRegFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWriteTrcvRegOfAccessEntityFcts(EthTrcv_30_Tja1100_AccessEntityFctsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAccessEntityFctsIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAccessEntitySnvOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AddressingIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddressingIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsAutoNegEnabledOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetBasicCtrlRegValOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ConnectionNegOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetConnectionNegOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDemEAccessEventIdOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MiiModeOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMiiModeOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhySignalQualityMeanOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSoCBaseRegAddrOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsSoftResetOnInitEnabledOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSoftResetWaitCyclesOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SpeedOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSpeedOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetClkModeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDerivativeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsExtLinkStateCheckEnabledOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetIntRevMiiOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLdoModeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkFailCounterResetValOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupDelayOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0MiiAddressOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0PortSnvOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0SwitchSnvOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhyEnableOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCallout(EthTrcv_30_Tja1100_HwAccessMonitorFailureCalloutIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HardwareAccessibilityType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_StateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_ModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_StateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvReadCalloutsFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreTrcvReadAccessCalloutOfUserAccessCallouts(EthTrcv_30_Tja1100_UserAccessCalloutsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvWriteCalloutsFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreTrcvWriteAccessCalloutOfUserAccessCallouts(EthTrcv_30_Tja1100_UserAccessCalloutsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPostTrcvInitCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPostInitUserCalloutOfUserInitCallouts(EthTrcv_30_Tja1100_UserInitCalloutsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvInitCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreInitUserCalloutOfUserInitCallouts(EthTrcv_30_Tja1100_UserInitCalloutsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_IcuChannelOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupCalloutIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupInspectionTypeOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMapEndIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMapStartIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupVerificationCalloutIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserWakeupCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupCallout(EthTrcv_30_Tja1100_WakeupCalloutIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetEcuMWakeupSourceOfWakeupMap(EthTrcv_30_Tja1100_WakeupMapIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupReasonOfWakeupMap(EthTrcv_30_Tja1100_WakeupMapIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_WakeupModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonFlagsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserWakeupVerificationCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupVerificationCallout(EthTrcv_30_Tja1100_WakeupVerificationCalloutIterType Index);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetDeduplicatedInlineFunctionPrototypes  Get Deduplicated Inline Function Prototypes
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_CableDiagLoopCyclesType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetCableDiagLoopCycles(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupUsedOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupUsedOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessLoopCountType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessLoopCount(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorLoopLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MainFunctionLinkHandlingMsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMs(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MaxPhySignalQualityMeanType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMaxPhySignalQualityMean(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfAccessEntityFctsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfAccessEntityFcts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorRecoveryDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkFailCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkFailCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStartupDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStartupDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStartupStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStartupState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStateDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStateDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStateTimeoutCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvHwAccessibilityType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvHwAccessibility(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvLinkStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvLinkState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfUserAccessCalloutsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfUserAccessCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfUserInitCalloutsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfUserInitCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupMap(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupReasonFlagsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupReasonFlags(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupVerificationCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupVerificationCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupCalloutUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupCalloutUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupMapUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupVerificationCalloutUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupVerificationCalloutUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCSetDataInlineFunctionPrototypes  Set Data Inline Function Prototypes
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorCycleCounter(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index, EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index, EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index, EthTrcv_30_Tja1100_LinkFailCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index, EthTrcv_30_Tja1100_LinkStartupDelayCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index, EthTrcv_30_Tja1100_LinkStartupStateType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index, EthTrcv_30_Tja1100_LinkStateDelayCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index, EthTrcv_30_Tja1100_LinkStateTimeoutCounterType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index, EthTrcv_30_Tja1100_HardwareAccessibilityType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index, EthTrcv_StateType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index, EthTrcv_ModeType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index, EthTrcv_StateType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index, EthTrcv_WakeupModeType Value);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index, EthTrcv_30_Tja1100_WakeupReasonFlagsType Value);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetAddressOfDataInlineFunctionPrototypes  Get Address Of Data Inline Function Prototypes
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateDelayCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateTimeoutCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvHwAccessibilityPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvLinkStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvModePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupModePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonFlagsPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCHasInlineFunctionPrototypes  Has Inline Function Prototypes
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFcts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasReadTrcvRegOfAccessEntityFcts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWriteTrcvRegOfAccessEntityFcts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasCableDiagLoopCycles(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFctsIdxOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntitySnvOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAddressingIdxOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAutoNegEnabledOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasBasicCtrlRegValOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasConnectionNegOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasDemEAccessEventIdOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMiiModeOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPhySignalQualityMeanOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoCBaseRegAddrOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoftResetOnInitEnabledOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoftResetWaitCyclesOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSpeedOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupIdxOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupUsedOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasClkModeOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasDerivativeOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasExtLinkStateCheckEnabledOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasIntRevMiiOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLdoModeOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounterResetValOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0MiiAddressOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0PortSnvOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0SwitchSnvOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPhyEnableOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessLoopCount(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorCycleCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorLoopLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceLimiter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateTimeoutCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMainFunctionLinkHandlingMs(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMaxPhySignalQualityMean(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfAccessEntityFcts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcv(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvTja1100(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorRecoveryDebounceCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkFailCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateDelayCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateTimeoutCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvHwAccessibility(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvLinkState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserAccessCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserInitCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMap(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupReasonFlags(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupVerificationCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvHwAccessibility(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvLinkState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvState(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserAccessCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreTrcvReadAccessCalloutOfUserAccessCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreTrcvWriteAccessCalloutOfUserAccessCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserInitCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPostInitUserCalloutOfUserInitCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreInitUserCalloutOfUserInitCallouts(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasIcuChannelOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutIdxOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutUsedOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupInspectionTypeOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapEndIdxOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapStartIdxOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapUsedOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutIdxOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutUsedOfWakeup(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMap(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEcuMWakeupSourceOfWakeupMap(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonOfWakeupMap(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMode(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonFlags(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCallout(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFctsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasCableDiagLoopCyclesOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvTja1100OfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessLoopCountOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorCycleCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureCalloutOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceLimiterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorLoopLimiterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceLimiterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateDelayCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateTimeoutCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMainFunctionLinkHandlingMsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMaxPhySignalQualityMeanOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfAccessEntityFctsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvTja1100OfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureCalloutOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureDebounceCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorRecoveryDebounceCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkFailCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupDelayCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateDelayCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateTimeoutCounterOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvHwAccessibilityOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvLinkStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvModeOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserAccessCalloutsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserInitCalloutsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupCalloutOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMapOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupModeOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupReasonFlagsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupVerificationCalloutOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvHwAccessibilityOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvLinkStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvModeOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvStateOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserAccessCalloutsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserInitCalloutsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupModeOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonFlagsOfPCConfig(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutOfPCConfig(void);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCIncrementInlineFunctionPrototypes  Increment Inline Function Prototypes
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorCycleCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCDecrementInlineFunctionPrototypes  Decrement Inline Function Prototypes
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorCycleCounter(void);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index);
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index);
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


# if !defined(ETHTRCV_30_TJA1100_UNIT_TEST)
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTIONS
**********************************************************************************************************************/
#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetDataInlineFunctions  EthTrcv_30_Tja1100 Get Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ReadTrcvRegFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetReadTrcvRegOfAccessEntityFcts(EthTrcv_30_Tja1100_AccessEntityFctsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_ReadTrcvRegFctPtrType) EthTrcv_30_Tja1100_GetAccessEntityFctsOfPCConfig()[(Index)].ReadTrcvRegOfAccessEntityFcts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WriteTrcvRegFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWriteTrcvRegOfAccessEntityFcts(EthTrcv_30_Tja1100_AccessEntityFctsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WriteTrcvRegFctPtrType) EthTrcv_30_Tja1100_GetAccessEntityFctsOfPCConfig()[(Index)].WriteTrcvRegOfAccessEntityFcts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAccessEntityFctsIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].AccessEntityFctsIdxOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAccessEntitySnvOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].AccessEntitySnvOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AddressingIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddressingIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_AddressingIdxOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].AddressingIdxOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsAutoNegEnabledOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_AutoNegEnabledOfEthTrcvType) ((EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].AutoNegEnabledOfEthTrcv) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetBasicCtrlRegValOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_BasicCtrlRegValOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].BasicCtrlRegValOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ConnectionNegOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetConnectionNegOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_ConnectionNegOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].ConnectionNegOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDemEAccessEventIdOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_DemEAccessEventIdOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].DemEAccessEventIdOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MiiModeOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMiiModeOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_MiiModeOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].MiiModeOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhySignalQualityMeanOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].PhySignalQualityMeanOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSoCBaseRegAddrOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SoCBaseRegAddrOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].SoCBaseRegAddrOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsSoftResetOnInitEnabledOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SoftResetOnInitEnabledOfEthTrcvType) ((EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].SoftResetOnInitEnabledOfEthTrcv) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSoftResetWaitCyclesOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].SoftResetWaitCyclesOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SpeedOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSpeedOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SpeedOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].SpeedOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType) EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig()[(Index)].WakeupIdxOfEthTrcv;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetClkModeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].ClkModeOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDerivativeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].DerivativeOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsExtLinkStateCheckEnabledOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_ExtLinkStateCheckEnabledOfEthTrcvTja1100Type) ((EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].ExtLinkStateCheckEnabledOfEthTrcvTja1100) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetIntRevMiiOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].IntRevMiiOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLdoModeOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].LdoModeOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkFailCounterResetValOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkFailCounterResetValOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].LinkFailCounterResetValOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupDelayOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStartupDelayOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].LinkStartupDelayOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0MiiAddressOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].P0MiiAddressOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0PortSnvOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].P0PortSnvOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetP0SwitchSnvOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].P0SwitchSnvOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhyEnableOfEthTrcvTja1100(EthTrcv_30_Tja1100_EthTrcvTja1100IterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig()[(Index)].PhyEnableOfEthTrcvTja1100;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType) (*(EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig()));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCallout(EthTrcv_30_Tja1100_HwAccessMonitorFailureCalloutIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCalloutOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkFailCounterType) EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStartupDelayCounterType) EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStartupStateType) EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStateDelayCounterType) EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStateTimeoutCounterType) EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HardwareAccessibilityType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HardwareAccessibilityType) EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_StateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_StateType) EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_ModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_ModeType) EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_StateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_StateType) EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvReadCalloutsFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreTrcvReadAccessCalloutOfUserAccessCallouts(EthTrcv_30_Tja1100_UserAccessCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserPreTrcvReadCalloutsFctPtrType) EthTrcv_30_Tja1100_GetUserAccessCalloutsOfPCConfig()[(Index)].PreTrcvReadAccessCalloutOfUserAccessCallouts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvWriteCalloutsFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreTrcvWriteAccessCalloutOfUserAccessCallouts(EthTrcv_30_Tja1100_UserAccessCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserPreTrcvWriteCalloutsFctPtrType) EthTrcv_30_Tja1100_GetUserAccessCalloutsOfPCConfig()[(Index)].PreTrcvWriteAccessCalloutOfUserAccessCallouts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPostTrcvInitCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPostInitUserCalloutOfUserInitCallouts(EthTrcv_30_Tja1100_UserInitCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserPostTrcvInitCalloutFctPtrType) EthTrcv_30_Tja1100_GetUserInitCalloutsOfPCConfig()[(Index)].PostInitUserCalloutOfUserInitCallouts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserPreTrcvInitCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPreInitUserCalloutOfUserInitCallouts(EthTrcv_30_Tja1100_UserInitCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserPreTrcvInitCalloutFctPtrType) EthTrcv_30_Tja1100_GetUserInitCalloutsOfPCConfig()[(Index)].PreInitUserCalloutOfUserInitCallouts;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_IcuChannelOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_IcuChannelOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].IcuChannelOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupCalloutIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].WakeupCalloutIdxOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupInspectionTypeOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupInspectionTypeOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].WakeupInspectionTypeOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMapEndIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupMapEndIdxOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].WakeupMapEndIdxOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMapStartIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupMapStartIdxOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].WakeupMapStartIdxOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupVerificationCalloutIdxOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupVerificationCalloutIdxOfWakeupType) EthTrcv_30_Tja1100_GetWakeupOfPCConfig()[(Index)].WakeupVerificationCalloutIdxOfWakeup;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserWakeupCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupCallout(EthTrcv_30_Tja1100_WakeupCalloutIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserWakeupCalloutFctPtrType) EthTrcv_30_Tja1100_GetWakeupCalloutOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetEcuMWakeupSourceOfWakeupMap(EthTrcv_30_Tja1100_WakeupMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_EcuMWakeupSourceOfWakeupMapType) EthTrcv_30_Tja1100_GetWakeupMapOfPCConfig()[(Index)].EcuMWakeupSourceOfWakeupMap;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupReasonOfWakeupMap(EthTrcv_30_Tja1100_WakeupMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupReasonOfWakeupMapType) EthTrcv_30_Tja1100_GetWakeupMapOfPCConfig()[(Index)].WakeupReasonOfWakeupMap;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_WakeupModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_WakeupModeType) EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonFlagsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupReasonFlagsType) EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()[(Index)];
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_UserWakeupVerificationCalloutFctPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetWakeupVerificationCallout(EthTrcv_30_Tja1100_WakeupVerificationCalloutIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_UserWakeupVerificationCalloutFctPtrType) EthTrcv_30_Tja1100_GetWakeupVerificationCalloutOfPCConfig()[(Index)];
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetDeduplicatedInlineFunctions  EthTrcv_30_Tja1100 Get Deduplicated Inline Functions (PRE_COMPILE)
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_CableDiagLoopCyclesType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetCableDiagLoopCycles(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_CableDiagLoopCyclesType) EthTrcv_30_Tja1100_GetCableDiagLoopCyclesOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupUsedOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupUsedOfEthTrcv(EthTrcv_30_Tja1100_EthTrcvIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupUsedOfEthTrcvType) (((boolean)(EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(Index) != ETHTRCV_30_TJA1100_NO_WAKEUPIDXOFETHTRCV)) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessLoopCountType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessLoopCount(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessLoopCountType) EthTrcv_30_Tja1100_GetHwAccessLoopCountOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceLimiterType) EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceLimiterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorLoopLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorLoopLimiterType) EthTrcv_30_Tja1100_GetHwAccessMonitorLoopLimiterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceLimiterType) EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceLimiterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MainFunctionLinkHandlingMsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMs(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_MainFunctionLinkHandlingMsType) EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMsOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_MaxPhySignalQualityMeanType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetMaxPhySignalQualityMean(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_MaxPhySignalQualityMeanType) EthTrcv_30_Tja1100_GetMaxPhySignalQualityMeanOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfAccessEntityFctsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfAccessEntityFcts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfAccessEntityFctsType) EthTrcv_30_Tja1100_GetSizeOfAccessEntityFctsOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfEthTrcvType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfEthTrcvType) EthTrcv_30_Tja1100_GetSizeOfEthTrcvOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100Type, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfEthTrcvTja1100Type) EthTrcv_30_Tja1100_GetSizeOfEthTrcvTja1100OfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureCalloutType) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureCalloutOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfHwAccessMonitorFailureDebounceCounterType) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorFailureDebounceCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfHwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorRecoveryDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfHwAccessMonitorRecoveryDebounceCounterType) EthTrcv_30_Tja1100_GetSizeOfHwAccessMonitorRecoveryDebounceCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkFailCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkFailCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfLinkFailCounterType) EthTrcv_30_Tja1100_GetSizeOfLinkFailCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStartupDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStartupDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfLinkStartupDelayCounterType) EthTrcv_30_Tja1100_GetSizeOfLinkStartupDelayCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStartupStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStartupState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfLinkStartupStateType) EthTrcv_30_Tja1100_GetSizeOfLinkStartupStateOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStateDelayCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStateDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfLinkStateDelayCounterType) EthTrcv_30_Tja1100_GetSizeOfLinkStateDelayCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfLinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfLinkStateTimeoutCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfLinkStateTimeoutCounterType) EthTrcv_30_Tja1100_GetSizeOfLinkStateTimeoutCounterOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvHwAccessibilityType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvHwAccessibility(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfTrcvHwAccessibilityType) EthTrcv_30_Tja1100_GetSizeOfTrcvHwAccessibilityOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvLinkStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvLinkState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfTrcvLinkStateType) EthTrcv_30_Tja1100_GetSizeOfTrcvLinkStateOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfTrcvModeType) EthTrcv_30_Tja1100_GetSizeOfTrcvModeOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfTrcvStateType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfTrcvState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfTrcvStateType) EthTrcv_30_Tja1100_GetSizeOfTrcvStateOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfUserAccessCalloutsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfUserAccessCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfUserAccessCalloutsType) EthTrcv_30_Tja1100_GetSizeOfUserAccessCalloutsOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfUserInitCalloutsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfUserInitCalloutsType) EthTrcv_30_Tja1100_GetSizeOfUserInitCalloutsOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupType) EthTrcv_30_Tja1100_GetSizeOfWakeupOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupCalloutType) EthTrcv_30_Tja1100_GetSizeOfWakeupCalloutOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupMapType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupMapType) EthTrcv_30_Tja1100_GetSizeOfWakeupMapOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupModeType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupModeType) EthTrcv_30_Tja1100_GetSizeOfWakeupModeOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupReasonFlagsType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupReasonFlags(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupReasonFlagsType) EthTrcv_30_Tja1100_GetSizeOfWakeupReasonFlagsOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_SizeOfWakeupVerificationCalloutType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetSizeOfWakeupVerificationCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_SizeOfWakeupVerificationCalloutType) EthTrcv_30_Tja1100_GetSizeOfWakeupVerificationCalloutOfPCConfig();
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupCalloutUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupCalloutUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupCalloutUsedOfWakeupType) (((boolean)(EthTrcv_30_Tja1100_GetWakeupCalloutIdxOfWakeup(Index) != ETHTRCV_30_TJA1100_NO_WAKEUPCALLOUTIDXOFWAKEUP)) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupMapUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupMapUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupMapUsedOfWakeupType) (((boolean)(EthTrcv_30_Tja1100_GetWakeupMapStartIdxOfWakeup(Index) != ETHTRCV_30_TJA1100_NO_WAKEUPMAPSTARTIDXOFWAKEUP)) != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupVerificationCalloutUsedOfWakeupType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IsWakeupVerificationCalloutUsedOfWakeup(EthTrcv_30_Tja1100_WakeupIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupVerificationCalloutUsedOfWakeupType) (((boolean)(EthTrcv_30_Tja1100_GetWakeupVerificationCalloutIdxOfWakeup(Index) != ETHTRCV_30_TJA1100_NO_WAKEUPVERIFICATIONCALLOUTIDXOFWAKEUP)) != FALSE);
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCSetDataInlineFunctions  EthTrcv_30_Tja1100 Set Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorCycleCounter(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  (*(EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig())) = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index, EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index, EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index, EthTrcv_30_Tja1100_LinkFailCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index, EthTrcv_30_Tja1100_LinkStartupDelayCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index, EthTrcv_30_Tja1100_LinkStartupStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index, EthTrcv_30_Tja1100_LinkStateDelayCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index, EthTrcv_30_Tja1100_LinkStateTimeoutCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index, EthTrcv_30_Tja1100_HardwareAccessibilityType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index, EthTrcv_StateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index, EthTrcv_ModeType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index, EthTrcv_StateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index, EthTrcv_WakeupModeType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()[(Index)] = (Value);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index, EthTrcv_30_Tja1100_WakeupReasonFlagsType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()[(Index)] = (Value);
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCGetAddressOfDataInlineFunctions  EthTrcv_30_Tja1100 Get Address Of Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterPtrType) (&(EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterPtrType) (&(EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkFailCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkFailCounterPtrType) (&(EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupDelayCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStartupDelayCounterPtrType) (&(EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStartupStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStartupStatePtrType) (&(EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateDelayCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStateDelayCounterPtrType) (&(EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_LinkStateTimeoutCounterPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_LinkStateTimeoutCounterPtrType) (&(EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvHwAccessibilityPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_TrcvHwAccessibilityPtrType) (&(EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvLinkStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_TrcvLinkStatePtrType) (&(EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvModePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_TrcvModePtrType) (&(EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_TrcvStatePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_TrcvStatePtrType) (&(EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupModePtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupModePtrType) (&(EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()[(Index)]));
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(EthTrcv_30_Tja1100_WakeupReasonFlagsPtrType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetAddrWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (EthTrcv_30_Tja1100_WakeupReasonFlagsPtrType) (&(EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()[(Index)]));
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCHasInlineFunctions  EthTrcv_30_Tja1100 Has Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFcts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetAccessEntityFctsOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasReadTrcvRegOfAccessEntityFcts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWriteTrcvRegOfAccessEntityFcts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasCableDiagLoopCycles(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetEthTrcvOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFctsIdxOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntitySnvOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAddressingIdxOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAutoNegEnabledOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasBasicCtrlRegValOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasConnectionNegOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasDemEAccessEventIdOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMiiModeOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPhySignalQualityMeanOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoCBaseRegAddrOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoftResetOnInitEnabledOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSoftResetWaitCyclesOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSpeedOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupIdxOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupUsedOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetEthTrcvTja1100OfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasClkModeOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasDerivativeOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasExtLinkStateCheckEnabledOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasIntRevMiiOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLdoModeOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounterResetValOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0MiiAddressOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0PortSnvOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasP0SwitchSnvOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPhyEnableOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessLoopCount(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorCycleCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCalloutOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorLoopLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceLimiter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateTimeoutCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMainFunctionLinkHandlingMs(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMaxPhySignalQualityMean(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfAccessEntityFcts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcv(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvTja1100(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorRecoveryDebounceCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkFailCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateDelayCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateTimeoutCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvHwAccessibility(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvLinkState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserAccessCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupReasonFlags(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupVerificationCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvHwAccessibility(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvLinkState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserAccessCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetUserAccessCalloutsOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreTrcvReadAccessCalloutOfUserAccessCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreTrcvWriteAccessCalloutOfUserAccessCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetUserInitCalloutsOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPostInitUserCalloutOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPreInitUserCalloutOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasIcuChannelOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutIdxOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutUsedOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupInspectionTypeOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapEndIdxOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapStartIdxOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapUsedOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutIdxOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutUsedOfWakeup(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupCalloutOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupMapOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEcuMWakeupSourceOfWakeupMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonOfWakeupMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMode(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonFlags(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCallout(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (EthTrcv_30_Tja1100_GetWakeupVerificationCalloutOfPCConfig() != NULL_PTR);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasAccessEntityFctsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasCableDiagLoopCyclesOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasEthTrcvTja1100OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessLoopCountOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorCycleCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorFailureDebounceLimiterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorLoopLimiterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasHwAccessMonitorRecoveryDebounceLimiterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkFailCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupDelayCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStartupStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateDelayCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasLinkStateTimeoutCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMainFunctionLinkHandlingMsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasMaxPhySignalQualityMeanOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfAccessEntityFctsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfEthTrcvTja1100OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorFailureDebounceCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfHwAccessMonitorRecoveryDebounceCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkFailCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupDelayCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStartupStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateDelayCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfLinkStateTimeoutCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvHwAccessibilityOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvLinkStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvModeOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfTrcvStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserAccessCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfUserInitCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupModeOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupReasonFlagsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasSizeOfWakeupVerificationCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvHwAccessibilityOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvLinkStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvModeOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasTrcvStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserAccessCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasUserInitCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupModeOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupReasonFlagsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_HasWakeupVerificationCalloutOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCIncrementInlineFunctions  EthTrcv_30_Tja1100 Increment Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorCycleCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  (*(EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig()))++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()[(Index)]++;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_IncWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()[(Index)]++;
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETHTRCV_30_TJA1100_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  EthTrcv_30_Tja1100PCDecrementInlineFunctions  EthTrcv_30_Tja1100 Decrement Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorCycleCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  (*(EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounterOfPCConfig()))--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorFailureDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecHwAccessMonitorRecoveryDebounceCounter(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkFailCounter(EthTrcv_30_Tja1100_LinkFailCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkFailCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStartupDelayCounter(EthTrcv_30_Tja1100_LinkStartupDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupDelayCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStartupState(EthTrcv_30_Tja1100_LinkStartupStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStartupStateOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStateDelayCounter(EthTrcv_30_Tja1100_LinkStateDelayCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateDelayCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecLinkStateTimeoutCounter(EthTrcv_30_Tja1100_LinkStateTimeoutCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetLinkStateTimeoutCounterOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvHwAccessibility(EthTrcv_30_Tja1100_TrcvHwAccessibilityIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvHwAccessibilityOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvLinkState(EthTrcv_30_Tja1100_TrcvLinkStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvLinkStateOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvMode(EthTrcv_30_Tja1100_TrcvModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvModeOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecTrcvState(EthTrcv_30_Tja1100_TrcvStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetTrcvStateOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecWakeupMode(EthTrcv_30_Tja1100_WakeupModeIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupModeOfPCConfig()[(Index)]--;
}
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_DecWakeupReasonFlags(EthTrcv_30_Tja1100_WakeupReasonFlagsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  EthTrcv_30_Tja1100_GetWakeupReasonFlagsOfPCConfig()[(Index)]--;
}
/** 
  \}
*/ 

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


# endif /* ETHTRCV_30_TJA1100_UNIT_TEST */
#endif /* ETHTRCV_30_TJA1100_LCFG_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Lcfg.h
 *********************************************************************************************************************/
 
