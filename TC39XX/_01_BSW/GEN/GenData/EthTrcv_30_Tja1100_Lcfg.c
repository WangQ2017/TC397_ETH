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
 *              File: EthTrcv_30_Tja1100_Lcfg.c
 *   Generation Time: 2025-12-14 15:58:18
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define ETHTRCV_30_TJA1100_LCFG_SOURCE
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/* PRQA S 0612 EOF */ /* MD_EthTrcv_30_Tja1100_0612 */
/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
#include "EthTrcv_30_Tja1100_Lcfg.h"

#include "Eth_30_Tc3xx.h"

#include "EthTrcv_Callout.h"

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTrcv_30_Tja1100_AccessEntityFcts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_AccessEntityFcts
  \brief  Functions of the accesses entities to read/write transceiver registers.
  \details
  Element         Description
  ReadTrcvReg     Function to call when a read register shall be performed
  WriteTrcvReg    Function to call when a write register shall be performed
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_AccessEntityFctsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_AccessEntityFcts[1] = {
    /* Index    ReadTrcvReg           WriteTrcvReg                 Referable Keys */
  { /*     0 */ Eth_30_Tc3xx_ReadMii, Eth_30_Tc3xx_WriteMii }   /* [/ActiveEcuC/EthTrcv/EthTrcvConfigSet/EthTrcvConfig] */
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_EthTrcv
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_EthTrcv
  \brief  Ethernet transceivers managed by the driver.
  \details
  Element                   Description
  BasicCtrlRegVal           Initialization value of basic control register
  AutoNegEnabled            Auto negotiation configuration
  SoftResetOnInitEnabled    Soft reset on initialization configuraiton
  AccessEntityFctsIdx       the index of the 1:1 relation pointing to EthTrcv_30_Tja1100_AccessEntityFcts
  AccessEntitySnv           Entity providing access to the transceiver hardware
  AddressingIdx             Addressing index in context of the access entity to address the transceiver hardware
  ConnectionNeg             Connection negotiation configuration
  DemEAccessEventId         ETHTRCV_E_ACCESS DEM event
  MiiMode                   Mii interface
  PhySignalQualityMean      Mean value of phyisical signal quality
  SoCBaseRegAddr            Base register address within memory space of SoC in case PHY is integrated as module into SoC.
  SoftResetWaitCycles       Soft reset wait cycles
  Speed                     Transceiver speed
  WakeupIdx                 the index of the 0:1 relation pointing to EthTrcv_30_Tja1100_Wakeup
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_EthTrcvType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcv[1] = {
    /* Index    BasicCtrlRegVal  AutoNegEnabled  SoftResetOnInitEnabled  AccessEntityFctsIdx                                                            AccessEntitySnv                      AddressingIdx  ConnectionNeg                                              DemEAccessEventId                                 MiiMode                                        PhySignalQualityMean  SoCBaseRegAddr                                 SoftResetWaitCycles  Speed                                             WakeupIdx                                                                                          */
  { /*     0 */         0x8160u,          FALSE,                  FALSE,                  0u  /* /ActiveEcuC/EthTrcv/EthTrcvConfigSet/EthTrcvConfig */, EthConf_EthCtrlConfig_EthCtrlConfig,            0u, ETHTRCV_30_TJA1100_CONN_NEG_MASTER_CONNECTIONNEGOFETHTRCV, ETHTRCV_30_TJA1100_NO_DEMEACCESSEVENTIDOFETHTRCV, ETHTRCV_30_TJA1100_RMII_MODE_MIIMODEOFETHTRCV,                 100u, ETHTRCV_30_TJA1100_NO_SOCBASEREGADDROFETHTRCV,                  0u, ETHTRCV_30_TJA1100_TRCV_SPEED_100_SPEEDOFETHTRCV, ETHTRCV_30_TJA1100_NO_WAKEUPIDXOFETHTRCV  /* /ActiveEcuC/EthTrcv/EthTrcvConfigSet/EthTrcvConfig */ }
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_EthTrcvTja1100
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_EthTrcvTja1100
  \brief  Tja1100 specific configuration data.
  \details
  Element                     Description
  ExtLinkStateCheckEnabled    Extended link state check configuration.
  ClkMode                     Clock mode.
  Derivative                  Tja110x derivative.
  IntRevMii                   Internal Reverse MII.
  LdoMode                     LDO mode.
  LinkFailCounterResetVal     Initialization value for link fail counter
  LinkStartupDelay            Delay till link initialization is triggered after transceiver is enabled.
  P0MiiAddress                MII address of P0.
  P0PortSnv                   SNV of port used to access P0.
  P0SwitchSnv                 SNV of switch used to access P0.
  PhyEnable                   PHY Enable.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_EthTrcvTja1100Type, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_EthTrcvTja1100[1] = {
    /* Index    ExtLinkStateCheckEnabled  ClkMode                                                        Derivative                                             IntRevMii                                                         LdoMode                                                 LinkFailCounterResetVal  LinkStartupDelay  P0MiiAddress  P0PortSnv                                        P0SwitchSnv                                        PhyEnable                                                   */
  { /*     0 */                    FALSE, ETHTRCV_30_TJA1100_INVALID_CLOCK_MODE_CLKMODEOFETHTRCVTJA1100, ETHTRCV_30_TJA1100_TJA1101_DERIVATIVEOFETHTRCVTJA1100, ETHTRCV_30_TJA1100_INT_REV_MII_INVALID_INTREVMIIOFETHTRCVTJA1100, ETHTRCV_30_TJA1100_LDO_INVALID_LDOMODEOFETHTRCVTJA1100,                     40u,              20u,           0u, ETHTRCV_30_TJA1100_NO_P0PORTSNVOFETHTRCVTJA1100, ETHTRCV_30_TJA1100_NO_P0SWITCHSNVOFETHTRCVTJA1100, ETHTRCV_30_TJA1100_PHY_EN_INVALID_PHYENABLEOFETHTRCVTJA1100 }
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  \brief  Hardware access monitor failure callouts to application.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_UserHwAccessMonitorFailureCalloutFctPtrType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout[1] = {
  /* Index     HwAccessMonitorFailureCallout      Referable Keys */
  /*     0 */ NULL_PTR                         /* [/ActiveEcuC/EthTrcv/EthTrcvConfigSet/EthTrcvConfig] */
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_UserAccessCallouts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_UserAccessCallouts
  \brief  pretransceiver read/write access callouts to application.
  \details
  Element                      Description
  PreTrcvReadAccessCallout     Pre-Transceiver Read Access callout
  PreTrcvWriteAccessCallout    Pre-Transceiver Write Access callout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_UserAccessCalloutsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserAccessCallouts[1] = {
    /* Index    PreTrcvReadAccessCallout  PreTrcvWriteAccessCallout */
  { /*     0 */ NULL_PTR                , NULL_PTR                  }
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_UserInitCallouts
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_UserInitCallouts
  \brief  Pre-/Post-Transceiver-Initialization callouts to application.
  \details
  Element                Description
  PostInitUserCallout    Post-Transceiver-Initialization callout
  PreInitUserCallout     Pre-Transceiver-Initialization callout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_UserInitCalloutsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_UserInitCallouts[1] = {
    /* Index    PostInitUserCallout          PreInitUserCallout         */
  { /*     0 */ EthTrcv_PostTrcvInitCallout, EthTrcv_PreTrcvInitCallout }
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
  \brief  The Wakeup reason cycle Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter;
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
  \brief  Performs debouncing for the Hw access feature before triggering the error reaction
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
  \brief  Performs debouncing for the Hw access feature before triggering the error recovery
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkFailCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkFailCounter
  \brief  Link fail counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_LinkFailCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkFailCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStartupDelayCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStartupDelayCounter
  \brief  Link Startup Delay Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_LinkStartupDelayCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupDelayCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStartupState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStartupState
  \brief  Link Startup State
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_LinkStartupStateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStartupState[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStateDelayCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStateDelayCounter
  \brief  Link State Delay Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_LinkStateDelayCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateDelayCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_LinkStateTimeoutCounter
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_LinkStateTimeoutCounter
  \brief  Link State Timeout Counter
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_LinkStateTimeoutCounterType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_LinkStateTimeoutCounter[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvHwAccessibility
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvHwAccessibility
  \brief  Transceiver hardware accessibility
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_30_Tja1100_HardwareAccessibilityType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvHwAccessibility[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvLinkState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvLinkState
  \brief  Transceiver link state.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvLinkState[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvMode
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvMode
  \brief  Transceiver operating mode.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_ModeType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvMode[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_TrcvState
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_TrcvState
  \brief  Transceiver initialization state.
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_NOINIT) EthTrcv_30_Tja1100_TrcvState[1];
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  EthTrcv_30_Tja1100_PCConfig
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_PCConfig
  \details
  Element                                   Description
  AccessEntityFcts                          the pointer to EthTrcv_30_Tja1100_AccessEntityFcts
  EthTrcv                                   the pointer to EthTrcv_30_Tja1100_EthTrcv
  EthTrcvTja1100                            the pointer to EthTrcv_30_Tja1100_EthTrcvTja1100
  HwAccessMonitorCycleCounter               the pointer to EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter
  HwAccessMonitorFailureCallout             the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  HwAccessMonitorFailureDebounceCounter     the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter
  HwAccessMonitorRecoveryDebounceCounter    the pointer to EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter
  LinkFailCounter                           the pointer to EthTrcv_30_Tja1100_LinkFailCounter
  LinkStartupDelayCounter                   the pointer to EthTrcv_30_Tja1100_LinkStartupDelayCounter
  LinkStartupState                          the pointer to EthTrcv_30_Tja1100_LinkStartupState
  LinkStateDelayCounter                     the pointer to EthTrcv_30_Tja1100_LinkStateDelayCounter
  LinkStateTimeoutCounter                   the pointer to EthTrcv_30_Tja1100_LinkStateTimeoutCounter
  TrcvHwAccessibility                       the pointer to EthTrcv_30_Tja1100_TrcvHwAccessibility
  TrcvLinkState                             the pointer to EthTrcv_30_Tja1100_TrcvLinkState
  TrcvMode                                  the pointer to EthTrcv_30_Tja1100_TrcvMode
  TrcvState                                 the pointer to EthTrcv_30_Tja1100_TrcvState
  UserAccessCallouts                        the pointer to EthTrcv_30_Tja1100_UserAccessCallouts
  UserInitCallouts                          the pointer to EthTrcv_30_Tja1100_UserInitCallouts
  Wakeup                                    the pointer to EthTrcv_30_Tja1100_Wakeup
  WakeupCallout                             the pointer to EthTrcv_30_Tja1100_WakeupCallout
  WakeupMap                                 the pointer to EthTrcv_30_Tja1100_WakeupMap
  WakeupMode                                the pointer to EthTrcv_30_Tja1100_WakeupMode
  WakeupReasonFlags                         the pointer to EthTrcv_30_Tja1100_WakeupReasonFlags
  WakeupVerificationCallout                 the pointer to EthTrcv_30_Tja1100_WakeupVerificationCallout
  CableDiagLoopCycles                       Maximum tries the driver performs to get results during cable diagnostics.
  HwAccessLoopCount                         Maximum tries the driver performs to access the hardware.
  HwAccessMonitorFailureDebounceLimiter     The debounce limiter number. The debouncing is completed when the debounce counter reaches that value
  HwAccessMonitorLoopLimiter                The loop limiter value to realize the period of the hardware access check in relation to the main function period
  HwAccessMonitorRecoveryDebounceLimiter    The debounce limiter number. The debouncing is completed when the debounce counter reaches that value
  MainFunctionLinkHandlingMs                Period in milliseconds the main function for the link handling of Tja1100 is called with
  MaxPhySignalQualityMean                   Maximum physical signal quality mean configured for the Ethernet transceivers
  SizeOfAccessEntityFcts                    the number of accomplishable value elements in EthTrcv_30_Tja1100_AccessEntityFcts
  SizeOfEthTrcv                             the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcv
  SizeOfEthTrcvTja1100                      the number of accomplishable value elements in EthTrcv_30_Tja1100_EthTrcvTja1100
  SizeOfHwAccessMonitorFailureCallout       the number of accomplishable value elements in EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout
  SizeOfUserAccessCallouts                  the number of accomplishable value elements in EthTrcv_30_Tja1100_UserAccessCallouts
  SizeOfUserInitCallouts                    the number of accomplishable value elements in EthTrcv_30_Tja1100_UserInitCallouts
  SizeOfWakeup                              the number of accomplishable value elements in EthTrcv_30_Tja1100_Wakeup
  SizeOfWakeupCallout                       the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupCallout
  SizeOfWakeupMap                           the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupMap
  SizeOfWakeupVerificationCallout           the number of accomplishable value elements in EthTrcv_30_Tja1100_WakeupVerificationCallout
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(EthTrcv_30_Tja1100_PCConfigsType, ETHTRCV_30_TJA1100_CONST) EthTrcv_30_Tja1100_PCConfig = {
  { /* Index: 0 Keys: [Config] */
      EthTrcv_30_Tja1100_AccessEntityFcts                        /**< the pointer to EthTrcv_30_Tja1100_AccessEntityFcts */
    , EthTrcv_30_Tja1100_EthTrcv                                 /**< the pointer to EthTrcv_30_Tja1100_EthTrcv */
    , EthTrcv_30_Tja1100_EthTrcvTja1100                          /**< the pointer to EthTrcv_30_Tja1100_EthTrcvTja1100 */
    , (&(EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter))        /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorCycleCounter */
    , EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout           /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
    , EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter   /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounter */
    , EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter  /**< the pointer to EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounter */
    , EthTrcv_30_Tja1100_LinkFailCounter                         /**< the pointer to EthTrcv_30_Tja1100_LinkFailCounter */
    , EthTrcv_30_Tja1100_LinkStartupDelayCounter                 /**< the pointer to EthTrcv_30_Tja1100_LinkStartupDelayCounter */
    , EthTrcv_30_Tja1100_LinkStartupState                        /**< the pointer to EthTrcv_30_Tja1100_LinkStartupState */
    , EthTrcv_30_Tja1100_LinkStateDelayCounter                   /**< the pointer to EthTrcv_30_Tja1100_LinkStateDelayCounter */
    , EthTrcv_30_Tja1100_LinkStateTimeoutCounter                 /**< the pointer to EthTrcv_30_Tja1100_LinkStateTimeoutCounter */
    , EthTrcv_30_Tja1100_TrcvHwAccessibility                     /**< the pointer to EthTrcv_30_Tja1100_TrcvHwAccessibility */
    , EthTrcv_30_Tja1100_TrcvLinkState                           /**< the pointer to EthTrcv_30_Tja1100_TrcvLinkState */
    , EthTrcv_30_Tja1100_TrcvMode                                /**< the pointer to EthTrcv_30_Tja1100_TrcvMode */
    , EthTrcv_30_Tja1100_TrcvState                               /**< the pointer to EthTrcv_30_Tja1100_TrcvState */
    , EthTrcv_30_Tja1100_UserAccessCallouts                      /**< the pointer to EthTrcv_30_Tja1100_UserAccessCallouts */
    , EthTrcv_30_Tja1100_UserInitCallouts                        /**< the pointer to EthTrcv_30_Tja1100_UserInitCallouts */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_Wakeup */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_WakeupCallout */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_WakeupMap */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_WakeupMode */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_WakeupReasonFlags */
    , NULL_PTR                                                   /**< the pointer to EthTrcv_30_Tja1100_WakeupVerificationCallout */
    , 10000u
    , 0u
    , 0u
    , 1u
    , 0u
    , 5u
    , 100u
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_AccessEntityFcts */
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_EthTrcv */
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_EthTrcvTja1100 */
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_HwAccessMonitorFailureCallout */
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_UserAccessCallouts */
    , 1u                                                         /**< the number of elements in EthTrcv_30_Tja1100_UserInitCallouts */
    , 0u                                                         /**< the number of elements in EthTrcv_30_Tja1100_Wakeup */
    , 0u                                                         /**< the number of elements in EthTrcv_30_Tja1100_WakeupCallout */
    , 0u                                                         /**< the number of elements in EthTrcv_30_Tja1100_WakeupMap */
    , 0u                                                         /**< the number of elements in EthTrcv_30_Tja1100_WakeupVerificationCallout */
  }
};
#define ETHTRCV_30_TJA1100_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthTrcv_30_Tja1100_ConfigDataPtr
**********************************************************************************************************************/
/** 
  \var    EthTrcv_30_Tja1100_ConfigDataPtr
  \brief  Points to the currently active configuration for EthTrcv_30_Tja1100
*/ 
#define ETHTRCV_30_TJA1100_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
P2CONST(EthTrcv_30_Tja1100_ConfigType, ETHTRCV_30_TJA1100_VAR_NOINIT, ETHTRCV_30_TJA1100_INIT_DATA) EthTrcv_30_Tja1100_ConfigDataPtr;
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Lcfg.c
 *********************************************************************************************************************/

