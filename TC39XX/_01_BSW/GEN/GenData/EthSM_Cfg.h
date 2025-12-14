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
 *            Module: EthSM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthSM_Cfg.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined (ETHSM_CFG_H)
# define ETHSM_CFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0779 EOF */ /* MD_MSR_Rule5.2 */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#ifndef ETHSM_DEV_ERROR_DETECT
#define ETHSM_DEV_ERROR_DETECT STD_ON
#endif
#ifndef ETHSM_DEV_ERROR_REPORT
#define ETHSM_DEV_ERROR_REPORT STD_ON
#endif
#ifndef ETHSM_USE_DUMMY_STATEMENT
#define ETHSM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHSM_DUMMY_STATEMENT
#define ETHSM_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHSM_DUMMY_STATEMENT_CONST
#define ETHSM_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHSM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ETHSM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ETHSM_ATOMIC_VARIABLE_ACCESS
#define ETHSM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef ETHSM_PROCESSOR_TC397X_STEPB
#define ETHSM_PROCESSOR_TC397X_STEPB
#endif
#ifndef ETHSM_COMP_TASKING
#define ETHSM_COMP_TASKING
#endif
#ifndef ETHSM_GEN_GENERATOR_MSR
#define ETHSM_GEN_GENERATOR_MSR
#endif
#ifndef ETHSM_CPUTYPE_BITORDER_LSB2MSB
#define ETHSM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef ETHSM_CONFIGURATION_VARIANT_PRECOMPILE
#define ETHSM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ETHSM_CONFIGURATION_VARIANT_LINKTIME
#define ETHSM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ETHSM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ETHSM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ETHSM_CONFIGURATION_VARIANT
#define ETHSM_CONFIGURATION_VARIANT ETHSM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ETHSM_POSTBUILD_VARIANT_SUPPORT
#define ETHSM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
 *  DEM EVENTS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  SWITCH DEFINES
 *********************************************************************************************************************/
#define ETHSM_VERSION_INFO_API             STD_OFF

#define ETHSM_IS_LINK_DOWN_DEM_ENABLED     STD_OFF
#define ETHSM_IS_ETHIF_TIMEOUT_DEM_ENABLED STD_OFF
#define ETHSM_IS_TCPIP_ENABLED             STD_ON
#define ETHSM_IS_VECTOR_TCPIP              STD_ON
#define ETHSM_IS_VECTOR_ETHIF              STD_ON

#define ETHSM_ENABLE_ETHIF_API_TIMEOUT     STD_OFF


/**********************************************************************************************************************
 *  INTEGER DEFINES
 *********************************************************************************************************************/
#define ETHSM_MAIN_FUNCTION_PERIOD         5u

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthSMPCDataSwitches  EthSM Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define ETHSM_ACTIVEIPVXCNT                                           STD_ON
#define ETHSM_CHANNELCONFIG                                           STD_ON
#define ETHSM_COMMNETWORKHANDLEOFCHANNELCONFIG                        STD_ON
#define ETHSM_CONFIRMATIONTIMEOUTOFCHANNELCONFIG                      STD_ON
#define ETHSM_ETHIFCONTROLLEROFCHANNELCONFIG                          STD_ON
#define ETHSM_LINKDOWNDEMENABLEDOFCHANNELCONFIG                       STD_OFF  /**< Deactivateable: 'EthSM_ChannelConfig.LinkDownDemEnabled' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define ETHSM_MAXRETRIESOFCHANNELCONFIG                               STD_ON
#define ETHSM_STACKTYPEOFCHANNELCONFIG                                STD_ON
#define ETHSM_TIMEOUTDEMENABLEDOFCHANNELCONFIG                        STD_OFF  /**< Deactivateable: 'EthSM_ChannelConfig.TimeoutDemEnabled' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define ETHSM_FINALMAGICNUMBER                                        STD_OFF  /**< Deactivateable: 'EthSM_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHSM_INITDATAHASHCODE                                        STD_OFF  /**< Deactivateable: 'EthSM_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHSM_INITIALIZED                                             STD_ON
#define ETHSM_LASTREPORTEDSTATE                                       STD_ON
#define ETHSM_MODE                                                    STD_ON
#define ETHSM_NETIDXBYCOMMNETWHND                                     STD_ON
#define ETHSM_NETIDXBYETHIFCTRLIDX                                    STD_ON
#define ETHSM_REQUESTEDMODE                                           STD_ON
#define ETHSM_SIZEOFACTIVEIPVXCNT                                     STD_ON
#define ETHSM_SIZEOFCHANNELCONFIG                                     STD_ON
#define ETHSM_SIZEOFLASTREPORTEDSTATE                                 STD_ON
#define ETHSM_SIZEOFMODE                                              STD_ON
#define ETHSM_SIZEOFNETIDXBYCOMMNETWHND                               STD_ON
#define ETHSM_SIZEOFNETIDXBYETHIFCTRLIDX                              STD_ON
#define ETHSM_SIZEOFREQUESTEDMODE                                     STD_ON
#define ETHSM_SIZEOFSTATE                                             STD_ON
#define ETHSM_SIZEOFTCPIPSTATE                                        STD_ON
#define ETHSM_SIZEOFTRCVLINKSTATE                                     STD_ON
#define ETHSM_STATE                                                   STD_ON
#define ETHSM_TCPIPSTATE                                              STD_ON
#define ETHSM_TRCVLINKSTATE                                           STD_ON
#define ETHSM_PCCONFIG                                                STD_ON
#define ETHSM_ACTIVEIPVXCNTOFPCCONFIG                                 STD_ON
#define ETHSM_CHANNELCONFIGOFPCCONFIG                                 STD_ON
#define ETHSM_FINALMAGICNUMBEROFPCCONFIG                              STD_OFF  /**< Deactivateable: 'EthSM_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHSM_INITDATAHASHCODEOFPCCONFIG                              STD_OFF  /**< Deactivateable: 'EthSM_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHSM_INITIALIZEDOFPCCONFIG                                   STD_ON
#define ETHSM_LASTREPORTEDSTATEOFPCCONFIG                             STD_ON
#define ETHSM_MODEOFPCCONFIG                                          STD_ON
#define ETHSM_NETIDXBYCOMMNETWHNDOFPCCONFIG                           STD_ON
#define ETHSM_NETIDXBYETHIFCTRLIDXOFPCCONFIG                          STD_ON
#define ETHSM_REQUESTEDMODEOFPCCONFIG                                 STD_ON
#define ETHSM_SIZEOFACTIVEIPVXCNTOFPCCONFIG                           STD_ON
#define ETHSM_SIZEOFCHANNELCONFIGOFPCCONFIG                           STD_ON
#define ETHSM_SIZEOFLASTREPORTEDSTATEOFPCCONFIG                       STD_ON
#define ETHSM_SIZEOFMODEOFPCCONFIG                                    STD_ON
#define ETHSM_SIZEOFNETIDXBYCOMMNETWHNDOFPCCONFIG                     STD_ON
#define ETHSM_SIZEOFNETIDXBYETHIFCTRLIDXOFPCCONFIG                    STD_ON
#define ETHSM_SIZEOFREQUESTEDMODEOFPCCONFIG                           STD_ON
#define ETHSM_SIZEOFSTATEOFPCCONFIG                                   STD_ON
#define ETHSM_SIZEOFTCPIPSTATEOFPCCONFIG                              STD_ON
#define ETHSM_SIZEOFTRCVLINKSTATEOFPCCONFIG                           STD_ON
#define ETHSM_STATEOFPCCONFIG                                         STD_ON
#define ETHSM_TCPIPSTATEOFPCCONFIG                                    STD_ON
#define ETHSM_TRCVLINKSTATEOFPCCONFIG                                 STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCMinNumericValueDefines  EthSM Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define ETHSM_MIN_ACTIVEIPVXCNT                                       0u
#define ETHSM_MIN_LASTREPORTEDSTATE                                   0u
#define ETHSM_MIN_MODE                                                0u
#define ETHSM_MIN_REQUESTEDMODE                                       0u
#define ETHSM_MIN_STATE                                               0u
#define ETHSM_MIN_TCPIPSTATE                                          0u
#define ETHSM_MIN_TRCVLINKSTATE                                       0u
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCMaxNumericValueDefines  EthSM Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define ETHSM_MAX_ACTIVEIPVXCNT                                       255u
#define ETHSM_MAX_LASTREPORTEDSTATE                                   255u
#define ETHSM_MAX_MODE                                                255u
#define ETHSM_MAX_REQUESTEDMODE                                       255u
#define ETHSM_MAX_STATE                                               255u
#define ETHSM_MAX_TCPIPSTATE                                          255u
#define ETHSM_MAX_TRCVLINKSTATE                                       255u
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCNoReferenceDefines  EthSM No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define ETHSM_NO_NETIDXBYCOMMNETWHND                                  255u
#define ETHSM_NO_NETIDXBYETHIFCTRLIDX                                 255u
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCIsReducedToDefineDefines  EthSM Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define ETHSM_ISDEF_COMMNETWORKHANDLEOFCHANNELCONFIG                  STD_ON
#define ETHSM_ISDEF_CONFIRMATIONTIMEOUTOFCHANNELCONFIG                STD_ON
#define ETHSM_ISDEF_ETHIFCONTROLLEROFCHANNELCONFIG                    STD_ON
#define ETHSM_ISDEF_MAXRETRIESOFCHANNELCONFIG                         STD_ON
#define ETHSM_ISDEF_STACKTYPEOFCHANNELCONFIG                          STD_ON
#define ETHSM_ISDEF_NETIDXBYCOMMNETWHND                               STD_ON
#define ETHSM_ISDEF_NETIDXBYETHIFCTRLIDX                              STD_ON
#define ETHSM_ISDEF_ACTIVEIPVXCNTOFPCCONFIG                           STD_ON
#define ETHSM_ISDEF_CHANNELCONFIGOFPCCONFIG                           STD_ON
#define ETHSM_ISDEF_INITIALIZEDOFPCCONFIG                             STD_ON
#define ETHSM_ISDEF_LASTREPORTEDSTATEOFPCCONFIG                       STD_ON
#define ETHSM_ISDEF_MODEOFPCCONFIG                                    STD_ON
#define ETHSM_ISDEF_NETIDXBYCOMMNETWHNDOFPCCONFIG                     STD_ON
#define ETHSM_ISDEF_NETIDXBYETHIFCTRLIDXOFPCCONFIG                    STD_ON
#define ETHSM_ISDEF_REQUESTEDMODEOFPCCONFIG                           STD_ON
#define ETHSM_ISDEF_STATEOFPCCONFIG                                   STD_ON
#define ETHSM_ISDEF_TCPIPSTATEOFPCCONFIG                              STD_ON
#define ETHSM_ISDEF_TRCVLINKSTATEOFPCCONFIG                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCEqualsAlwaysToDefines  EthSM Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define ETHSM_EQ2_COMMNETWORKHANDLEOFCHANNELCONFIG                    ComMConf_ComMChannel_ComMChannel_Vlan10
#define ETHSM_EQ2_CONFIRMATIONTIMEOUTOFCHANNELCONFIG                  20u
#define ETHSM_EQ2_ETHIFCONTROLLEROFCHANNELCONFIG                      ((EthSM_EthIfControllerOfChannelConfigType)EthIfConf_EthIfController_EthIfController_Vlan10)
#define ETHSM_EQ2_MAXRETRIESOFCHANNELCONFIG                           0u
#define ETHSM_EQ2_STACKTYPEOFCHANNELCONFIG                            ETHSM_STACK_TYPE_TCPIP
#define ETHSM_EQ2_NETIDXBYCOMMNETWHND                                 0u
#define ETHSM_EQ2_NETIDXBYETHIFCTRLIDX                                0u
#define ETHSM_EQ2_ACTIVEIPVXCNTOFPCCONFIG                             EthSM_ActiveIpVxCnt.raw
#define ETHSM_EQ2_CHANNELCONFIGOFPCCONFIG                             EthSM_ChannelConfig
#define ETHSM_EQ2_INITIALIZEDOFPCCONFIG                               (&(EthSM_Initialized))
#define ETHSM_EQ2_LASTREPORTEDSTATEOFPCCONFIG                         EthSM_LastReportedState.raw
#define ETHSM_EQ2_MODEOFPCCONFIG                                      EthSM_Mode.raw
#define ETHSM_EQ2_NETIDXBYCOMMNETWHNDOFPCCONFIG                       EthSM_NetIdxByComMNetwHnd
#define ETHSM_EQ2_NETIDXBYETHIFCTRLIDXOFPCCONFIG                      EthSM_NetIdxByEthIfCtrlIdx
#define ETHSM_EQ2_REQUESTEDMODEOFPCCONFIG                             EthSM_RequestedMode.raw
#define ETHSM_EQ2_STATEOFPCCONFIG                                     EthSM_State.raw
#define ETHSM_EQ2_TCPIPSTATEOFPCCONFIG                                EthSM_TcpIpState.raw
#define ETHSM_EQ2_TRCVLINKSTATEOFPCCONFIG                             EthSM_TrcvLinkState.raw
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCSymbolicInitializationPointers  EthSM Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define EthSM_Config_Ptr                                              NULL_PTR  /**< symbolic identifier which shall be used to initialize 'EthSM' */
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCInitializationSymbols  EthSM Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define EthSM_Config                                                  NULL_PTR  /**< symbolic identifier which could be used to initialize 'EthSM */
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCGeneral  EthSM General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define ETHSM_CHECK_INIT_POINTER                                      STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define ETHSM_FINAL_MAGIC_NUMBER                                      0x8F1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of EthSM */
#define ETHSM_INDIVIDUAL_POSTBUILD                                    STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'EthSM' is not configured to be postbuild capable. */
#define ETHSM_INIT_DATA                                               ETHSM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define ETHSM_INIT_DATA_HASH_CODE                                     -2061256265  /**< the precompile constant to validate the initialization structure at initialization time of EthSM with a hashcode. The seed value is '0x8F1Eu' */
#define ETHSM_USE_ECUM_BSW_ERROR_HOOK                                 STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define ETHSM_USE_INIT_POINTER                                        STD_OFF  /**< STD_ON if the init pointer EthSM shall be used. */
/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthSMPCGetConstantDuplicatedRootDataMacros  EthSM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define EthSM_GetActiveIpVxCntOfPCConfig()                            EthSM_ActiveIpVxCnt.raw  /**< the pointer to EthSM_ActiveIpVxCnt */
#define EthSM_GetChannelConfigOfPCConfig()                            EthSM_ChannelConfig  /**< the pointer to EthSM_ChannelConfig */
#define EthSM_GetInitializedOfPCConfig()                              (&(EthSM_Initialized))  /**< the pointer to EthSM_Initialized */
#define EthSM_GetLastReportedStateOfPCConfig()                        EthSM_LastReportedState.raw  /**< the pointer to EthSM_LastReportedState */
#define EthSM_GetModeOfPCConfig()                                     EthSM_Mode.raw  /**< the pointer to EthSM_Mode */
#define EthSM_GetNetIdxByComMNetwHndOfPCConfig()                      EthSM_NetIdxByComMNetwHnd  /**< the pointer to EthSM_NetIdxByComMNetwHnd */
#define EthSM_GetNetIdxByEthIfCtrlIdxOfPCConfig()                     EthSM_NetIdxByEthIfCtrlIdx  /**< the pointer to EthSM_NetIdxByEthIfCtrlIdx */
#define EthSM_GetRequestedModeOfPCConfig()                            EthSM_RequestedMode.raw  /**< the pointer to EthSM_RequestedMode */
#define EthSM_GetSizeOfChannelConfigOfPCConfig()                      1u  /**< the number of accomplishable value elements in EthSM_ChannelConfig */
#define EthSM_GetSizeOfNetIdxByComMNetwHndOfPCConfig()                1u  /**< the number of accomplishable value elements in EthSM_NetIdxByComMNetwHnd */
#define EthSM_GetSizeOfNetIdxByEthIfCtrlIdxOfPCConfig()               1u  /**< the number of accomplishable value elements in EthSM_NetIdxByEthIfCtrlIdx */
#define EthSM_GetStateOfPCConfig()                                    EthSM_State.raw  /**< the pointer to EthSM_State */
#define EthSM_GetTcpIpStateOfPCConfig()                               EthSM_TcpIpState.raw  /**< the pointer to EthSM_TcpIpState */
#define EthSM_GetTrcvLinkStateOfPCConfig()                            EthSM_TrcvLinkState.raw  /**< the pointer to EthSM_TrcvLinkState */
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCGetDuplicatedRootDataMacros  EthSM Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define EthSM_GetSizeOfActiveIpVxCntOfPCConfig()                      EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_ActiveIpVxCnt */
#define EthSM_GetSizeOfLastReportedStateOfPCConfig()                  EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_LastReportedState */
#define EthSM_GetSizeOfModeOfPCConfig()                               EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_Mode */
#define EthSM_GetSizeOfRequestedModeOfPCConfig()                      EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_RequestedMode */
#define EthSM_GetSizeOfStateOfPCConfig()                              EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_State */
#define EthSM_GetSizeOfTcpIpStateOfPCConfig()                         EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_TcpIpState */
#define EthSM_GetSizeOfTrcvLinkStateOfPCConfig()                      EthSM_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in EthSM_TrcvLinkState */
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCGetDataMacros  EthSM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define EthSM_GetActiveIpVxCnt(Index)                                 (EthSM_GetActiveIpVxCntOfPCConfig()[(Index)])
#define EthSM_IsInitialized()                                         (((*(EthSM_GetInitializedOfPCConfig()))) != FALSE)
#define EthSM_GetLastReportedState(Index)                             (EthSM_GetLastReportedStateOfPCConfig()[(Index)])
#define EthSM_GetMode(Index)                                          (EthSM_GetModeOfPCConfig()[(Index)])
#define EthSM_GetRequestedMode(Index)                                 (EthSM_GetRequestedModeOfPCConfig()[(Index)])
#define EthSM_GetState(Index)                                         (EthSM_GetStateOfPCConfig()[(Index)])
#define EthSM_GetTcpIpState(Index)                                    (EthSM_GetTcpIpStateOfPCConfig()[(Index)])
#define EthSM_GetTrcvLinkState(Index)                                 (EthSM_GetTrcvLinkStateOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCGetDeduplicatedDataMacros  EthSM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define EthSM_GetComMNetworkHandleOfChannelConfig(Index)              ComMConf_ComMChannel_ComMChannel_Vlan10
#define EthSM_GetConfirmationTimeoutOfChannelConfig(Index)            20u
#define EthSM_GetEthIfControllerOfChannelConfig(Index)                ((EthSM_EthIfControllerOfChannelConfigType)EthIfConf_EthIfController_EthIfController_Vlan10)
#define EthSM_GetMaxRetriesOfChannelConfig(Index)                     0u
#define EthSM_GetStackTypeOfChannelConfig(Index)                      ETHSM_STACK_TYPE_TCPIP
#define EthSM_GetNetIdxByComMNetwHnd(Index)                           0u
#define EthSM_GetNetIdxByEthIfCtrlIdx(Index)                          0u
#define EthSM_GetSizeOfActiveIpVxCnt()                                EthSM_GetSizeOfActiveIpVxCntOfPCConfig()
#define EthSM_GetSizeOfChannelConfig()                                EthSM_GetSizeOfChannelConfigOfPCConfig()
#define EthSM_GetSizeOfLastReportedState()                            EthSM_GetSizeOfLastReportedStateOfPCConfig()
#define EthSM_GetSizeOfMode()                                         EthSM_GetSizeOfModeOfPCConfig()
#define EthSM_GetSizeOfNetIdxByComMNetwHnd()                          EthSM_GetSizeOfNetIdxByComMNetwHndOfPCConfig()
#define EthSM_GetSizeOfNetIdxByEthIfCtrlIdx()                         EthSM_GetSizeOfNetIdxByEthIfCtrlIdxOfPCConfig()
#define EthSM_GetSizeOfRequestedMode()                                EthSM_GetSizeOfRequestedModeOfPCConfig()
#define EthSM_GetSizeOfState()                                        EthSM_GetSizeOfStateOfPCConfig()
#define EthSM_GetSizeOfTcpIpState()                                   EthSM_GetSizeOfTcpIpStateOfPCConfig()
#define EthSM_GetSizeOfTrcvLinkState()                                EthSM_GetSizeOfTrcvLinkStateOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCSetDataMacros  EthSM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define EthSM_SetActiveIpVxCnt(Index, Value)                          EthSM_GetActiveIpVxCntOfPCConfig()[(Index)] = (Value)
#define EthSM_SetInitialized(Value)                                   (*(EthSM_GetInitializedOfPCConfig())) = (Value)
#define EthSM_SetLastReportedState(Index, Value)                      EthSM_GetLastReportedStateOfPCConfig()[(Index)] = (Value)
#define EthSM_SetMode(Index, Value)                                   EthSM_GetModeOfPCConfig()[(Index)] = (Value)
#define EthSM_SetRequestedMode(Index, Value)                          EthSM_GetRequestedModeOfPCConfig()[(Index)] = (Value)
#define EthSM_SetState(Index, Value)                                  EthSM_GetStateOfPCConfig()[(Index)] = (Value)
#define EthSM_SetTcpIpState(Index, Value)                             EthSM_GetTcpIpStateOfPCConfig()[(Index)] = (Value)
#define EthSM_SetTrcvLinkState(Index, Value)                          EthSM_GetTrcvLinkStateOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCHasMacros  EthSM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define EthSM_HasActiveIpVxCnt()                                      (TRUE != FALSE)
#define EthSM_HasChannelConfig()                                      (TRUE != FALSE)
#define EthSM_HasComMNetworkHandleOfChannelConfig()                   (TRUE != FALSE)
#define EthSM_HasConfirmationTimeoutOfChannelConfig()                 (TRUE != FALSE)
#define EthSM_HasEthIfControllerOfChannelConfig()                     (TRUE != FALSE)
#define EthSM_HasMaxRetriesOfChannelConfig()                          (TRUE != FALSE)
#define EthSM_HasStackTypeOfChannelConfig()                           (TRUE != FALSE)
#define EthSM_HasInitialized()                                        (TRUE != FALSE)
#define EthSM_HasLastReportedState()                                  (TRUE != FALSE)
#define EthSM_HasMode()                                               (TRUE != FALSE)
#define EthSM_HasNetIdxByComMNetwHnd()                                (TRUE != FALSE)
#define EthSM_HasNetIdxByEthIfCtrlIdx()                               (TRUE != FALSE)
#define EthSM_HasRequestedMode()                                      (TRUE != FALSE)
#define EthSM_HasSizeOfActiveIpVxCnt()                                (TRUE != FALSE)
#define EthSM_HasSizeOfChannelConfig()                                (TRUE != FALSE)
#define EthSM_HasSizeOfLastReportedState()                            (TRUE != FALSE)
#define EthSM_HasSizeOfMode()                                         (TRUE != FALSE)
#define EthSM_HasSizeOfNetIdxByComMNetwHnd()                          (TRUE != FALSE)
#define EthSM_HasSizeOfNetIdxByEthIfCtrlIdx()                         (TRUE != FALSE)
#define EthSM_HasSizeOfRequestedMode()                                (TRUE != FALSE)
#define EthSM_HasSizeOfState()                                        (TRUE != FALSE)
#define EthSM_HasSizeOfTcpIpState()                                   (TRUE != FALSE)
#define EthSM_HasSizeOfTrcvLinkState()                                (TRUE != FALSE)
#define EthSM_HasState()                                              (TRUE != FALSE)
#define EthSM_HasTcpIpState()                                         (TRUE != FALSE)
#define EthSM_HasTrcvLinkState()                                      (TRUE != FALSE)
#define EthSM_HasPCConfig()                                           (TRUE != FALSE)
#define EthSM_HasActiveIpVxCntOfPCConfig()                            (TRUE != FALSE)
#define EthSM_HasChannelConfigOfPCConfig()                            (TRUE != FALSE)
#define EthSM_HasInitializedOfPCConfig()                              (TRUE != FALSE)
#define EthSM_HasLastReportedStateOfPCConfig()                        (TRUE != FALSE)
#define EthSM_HasModeOfPCConfig()                                     (TRUE != FALSE)
#define EthSM_HasNetIdxByComMNetwHndOfPCConfig()                      (TRUE != FALSE)
#define EthSM_HasNetIdxByEthIfCtrlIdxOfPCConfig()                     (TRUE != FALSE)
#define EthSM_HasRequestedModeOfPCConfig()                            (TRUE != FALSE)
#define EthSM_HasSizeOfActiveIpVxCntOfPCConfig()                      (TRUE != FALSE)
#define EthSM_HasSizeOfChannelConfigOfPCConfig()                      (TRUE != FALSE)
#define EthSM_HasSizeOfLastReportedStateOfPCConfig()                  (TRUE != FALSE)
#define EthSM_HasSizeOfModeOfPCConfig()                               (TRUE != FALSE)
#define EthSM_HasSizeOfNetIdxByComMNetwHndOfPCConfig()                (TRUE != FALSE)
#define EthSM_HasSizeOfNetIdxByEthIfCtrlIdxOfPCConfig()               (TRUE != FALSE)
#define EthSM_HasSizeOfRequestedModeOfPCConfig()                      (TRUE != FALSE)
#define EthSM_HasSizeOfStateOfPCConfig()                              (TRUE != FALSE)
#define EthSM_HasSizeOfTcpIpStateOfPCConfig()                         (TRUE != FALSE)
#define EthSM_HasSizeOfTrcvLinkStateOfPCConfig()                      (TRUE != FALSE)
#define EthSM_HasStateOfPCConfig()                                    (TRUE != FALSE)
#define EthSM_HasTcpIpStateOfPCConfig()                               (TRUE != FALSE)
#define EthSM_HasTrcvLinkStateOfPCConfig()                            (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCIncrementDataMacros  EthSM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define EthSM_IncActiveIpVxCnt(Index)                                 EthSM_GetActiveIpVxCnt(Index)++
#define EthSM_IncLastReportedState(Index)                             EthSM_GetLastReportedState(Index)++
#define EthSM_IncMode(Index)                                          EthSM_GetMode(Index)++
#define EthSM_IncRequestedMode(Index)                                 EthSM_GetRequestedMode(Index)++
#define EthSM_IncState(Index)                                         EthSM_GetState(Index)++
#define EthSM_IncTcpIpState(Index)                                    EthSM_GetTcpIpState(Index)++
#define EthSM_IncTrcvLinkState(Index)                                 EthSM_GetTrcvLinkState(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCDecrementDataMacros  EthSM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define EthSM_DecActiveIpVxCnt(Index)                                 EthSM_GetActiveIpVxCnt(Index)--
#define EthSM_DecLastReportedState(Index)                             EthSM_GetLastReportedState(Index)--
#define EthSM_DecMode(Index)                                          EthSM_GetMode(Index)--
#define EthSM_DecRequestedMode(Index)                                 EthSM_GetRequestedMode(Index)--
#define EthSM_DecState(Index)                                         EthSM_GetState(Index)--
#define EthSM_DecTcpIpState(Index)                                    EthSM_GetTcpIpState(Index)--
#define EthSM_DecTrcvLinkState(Index)                                 EthSM_GetTrcvLinkState(Index)--
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthSMPCIterableTypes  EthSM Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate EthSM_ChannelConfig */
typedef uint8_least EthSM_ChannelConfigIterType;

/**   \brief  type used to iterate EthSM_NetIdxByComMNetwHnd */
typedef uint8_least EthSM_NetIdxByComMNetwHndIterType;

/**   \brief  type used to iterate EthSM_NetIdxByEthIfCtrlIdx */
typedef uint8_least EthSM_NetIdxByEthIfCtrlIdxIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCIterableTypesWithSizeRelations  EthSM Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate EthSM_ActiveIpVxCnt */
typedef EthSM_ChannelConfigIterType EthSM_ActiveIpVxCntIterType;

/**   \brief  type used to iterate EthSM_LastReportedState */
typedef EthSM_ChannelConfigIterType EthSM_LastReportedStateIterType;

/**   \brief  type used to iterate EthSM_Mode */
typedef EthSM_ChannelConfigIterType EthSM_ModeIterType;

/**   \brief  type used to iterate EthSM_RequestedMode */
typedef EthSM_ChannelConfigIterType EthSM_RequestedModeIterType;

/**   \brief  type used to iterate EthSM_State */
typedef EthSM_ChannelConfigIterType EthSM_StateIterType;

/**   \brief  type used to iterate EthSM_TcpIpState */
typedef EthSM_ChannelConfigIterType EthSM_TcpIpStateIterType;

/**   \brief  type used to iterate EthSM_TrcvLinkState */
typedef EthSM_ChannelConfigIterType EthSM_TrcvLinkStateIterType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCValueTypes  EthSM Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for EthSM_ActiveIpVxCnt */
typedef uint8 EthSM_ActiveIpVxCntType;

/**   \brief  value based type definition for EthSM_ComMNetworkHandleOfChannelConfig */
typedef uint8 EthSM_ComMNetworkHandleOfChannelConfigType;

/**   \brief  value based type definition for EthSM_ConfirmationTimeoutOfChannelConfig */
typedef uint8 EthSM_ConfirmationTimeoutOfChannelConfigType;

/**   \brief  value based type definition for EthSM_EthIfControllerOfChannelConfig */
typedef uint8 EthSM_EthIfControllerOfChannelConfigType;

/**   \brief  value based type definition for EthSM_MaxRetriesOfChannelConfig */
typedef uint8 EthSM_MaxRetriesOfChannelConfigType;

/**   \brief  value based type definition for EthSM_StackTypeOfChannelConfig */
typedef uint8 EthSM_StackTypeOfChannelConfigType;

/**   \brief  value based type definition for EthSM_Initialized */
typedef boolean EthSM_InitializedType;

/**   \brief  value based type definition for EthSM_LastReportedState */
typedef uint8 EthSM_LastReportedStateType;

/**   \brief  value based type definition for EthSM_Mode */
typedef uint8 EthSM_ModeType;

/**   \brief  value based type definition for EthSM_NetIdxByComMNetwHnd */
typedef uint8 EthSM_NetIdxByComMNetwHndType;

/**   \brief  value based type definition for EthSM_NetIdxByEthIfCtrlIdx */
typedef uint8 EthSM_NetIdxByEthIfCtrlIdxType;

/**   \brief  value based type definition for EthSM_RequestedMode */
typedef uint8 EthSM_RequestedModeType;

/**   \brief  value based type definition for EthSM_SizeOfActiveIpVxCnt */
typedef uint8 EthSM_SizeOfActiveIpVxCntType;

/**   \brief  value based type definition for EthSM_SizeOfChannelConfig */
typedef uint8 EthSM_SizeOfChannelConfigType;

/**   \brief  value based type definition for EthSM_SizeOfLastReportedState */
typedef uint8 EthSM_SizeOfLastReportedStateType;

/**   \brief  value based type definition for EthSM_SizeOfMode */
typedef uint8 EthSM_SizeOfModeType;

/**   \brief  value based type definition for EthSM_SizeOfNetIdxByComMNetwHnd */
typedef uint8 EthSM_SizeOfNetIdxByComMNetwHndType;

/**   \brief  value based type definition for EthSM_SizeOfNetIdxByEthIfCtrlIdx */
typedef uint8 EthSM_SizeOfNetIdxByEthIfCtrlIdxType;

/**   \brief  value based type definition for EthSM_SizeOfRequestedMode */
typedef uint8 EthSM_SizeOfRequestedModeType;

/**   \brief  value based type definition for EthSM_SizeOfState */
typedef uint8 EthSM_SizeOfStateType;

/**   \brief  value based type definition for EthSM_SizeOfTcpIpState */
typedef uint8 EthSM_SizeOfTcpIpStateType;

/**   \brief  value based type definition for EthSM_SizeOfTrcvLinkState */
typedef uint8 EthSM_SizeOfTrcvLinkStateType;

/**   \brief  value based type definition for EthSM_State */
typedef uint8 EthSM_StateType;

/**   \brief  value based type definition for EthSM_TcpIpState */
typedef uint8 EthSM_TcpIpStateType;

/**   \brief  value based type definition for EthSM_TrcvLinkState */
typedef uint8 EthSM_TrcvLinkStateType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  EthSMPCStructTypes  EthSM Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in EthSM_ChannelConfig */
typedef struct sEthSM_ChannelConfigType
{
  uint8 EthSM_ChannelConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} EthSM_ChannelConfigType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCSymbolicStructTypes  EthSM Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to EthSM_ActiveIpVxCnt */
typedef struct EthSM_ActiveIpVxCntStructSTag
{
  EthSM_ActiveIpVxCntType EthSMNetwork_Vlan10;
} EthSM_ActiveIpVxCntStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_LastReportedState */
typedef struct EthSM_LastReportedStateStructSTag
{
  EthSM_LastReportedStateType EthSMNetwork_Vlan10;
} EthSM_LastReportedStateStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_Mode */
typedef struct EthSM_ModeStructSTag
{
  EthSM_ModeType EthSMNetwork_Vlan10;
} EthSM_ModeStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_RequestedMode */
typedef struct EthSM_RequestedModeStructSTag
{
  EthSM_RequestedModeType EthSMNetwork_Vlan10;
} EthSM_RequestedModeStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_State */
typedef struct EthSM_StateStructSTag
{
  EthSM_StateType EthSMNetwork_Vlan10;
} EthSM_StateStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_TcpIpState */
typedef struct EthSM_TcpIpStateStructSTag
{
  EthSM_TcpIpStateType EthSMNetwork_Vlan10;
} EthSM_TcpIpStateStructSType;

/**   \brief  type to be used as symbolic data element access to EthSM_TrcvLinkState */
typedef struct EthSM_TrcvLinkStateStructSTag
{
  EthSM_TrcvLinkStateType EthSMNetwork_Vlan10;
} EthSM_TrcvLinkStateStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCUnionIndexAndSymbolTypes  EthSM Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access EthSM_ActiveIpVxCnt in an index and symbol based style. */
typedef union EthSM_ActiveIpVxCntUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_ActiveIpVxCntType raw[1];
  EthSM_ActiveIpVxCntStructSType str;
} EthSM_ActiveIpVxCntUType;

/**   \brief  type to access EthSM_LastReportedState in an index and symbol based style. */
typedef union EthSM_LastReportedStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_LastReportedStateType raw[1];
  EthSM_LastReportedStateStructSType str;
} EthSM_LastReportedStateUType;

/**   \brief  type to access EthSM_Mode in an index and symbol based style. */
typedef union EthSM_ModeUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_ModeType raw[1];
  EthSM_ModeStructSType str;
} EthSM_ModeUType;

/**   \brief  type to access EthSM_RequestedMode in an index and symbol based style. */
typedef union EthSM_RequestedModeUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_RequestedModeType raw[1];
  EthSM_RequestedModeStructSType str;
} EthSM_RequestedModeUType;

/**   \brief  type to access EthSM_State in an index and symbol based style. */
typedef union EthSM_StateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_StateType raw[1];
  EthSM_StateStructSType str;
} EthSM_StateUType;

/**   \brief  type to access EthSM_TcpIpState in an index and symbol based style. */
typedef union EthSM_TcpIpStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_TcpIpStateType raw[1];
  EthSM_TcpIpStateStructSType str;
} EthSM_TcpIpStateUType;

/**   \brief  type to access EthSM_TrcvLinkState in an index and symbol based style. */
typedef union EthSM_TrcvLinkStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  EthSM_TrcvLinkStateType raw[1];
  EthSM_TrcvLinkStateStructSType str;
} EthSM_TrcvLinkStateUType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCRootPointerTypes  EthSM Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to EthSM_ActiveIpVxCnt */
typedef P2VAR(EthSM_ActiveIpVxCntType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_ActiveIpVxCntPtrType;

/**   \brief  type used to point to EthSM_ChannelConfig */
typedef P2CONST(EthSM_ChannelConfigType, TYPEDEF, ETHSM_CONST) EthSM_ChannelConfigPtrType;

/**   \brief  type used to point to EthSM_Initialized */
typedef P2VAR(EthSM_InitializedType, TYPEDEF, ETHSM_VAR_ZERO_INIT) EthSM_InitializedPtrType;

/**   \brief  type used to point to EthSM_LastReportedState */
typedef P2VAR(EthSM_LastReportedStateType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_LastReportedStatePtrType;

/**   \brief  type used to point to EthSM_Mode */
typedef P2VAR(EthSM_ModeType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_ModePtrType;

/**   \brief  type used to point to EthSM_NetIdxByComMNetwHnd */
typedef P2CONST(EthSM_NetIdxByComMNetwHndType, TYPEDEF, ETHSM_CONST) EthSM_NetIdxByComMNetwHndPtrType;

/**   \brief  type used to point to EthSM_NetIdxByEthIfCtrlIdx */
typedef P2CONST(EthSM_NetIdxByEthIfCtrlIdxType, TYPEDEF, ETHSM_CONST) EthSM_NetIdxByEthIfCtrlIdxPtrType;

/**   \brief  type used to point to EthSM_RequestedMode */
typedef P2VAR(EthSM_RequestedModeType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_RequestedModePtrType;

/**   \brief  type used to point to EthSM_State */
typedef P2VAR(EthSM_StateType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_StatePtrType;

/**   \brief  type used to point to EthSM_TcpIpState */
typedef P2VAR(EthSM_TcpIpStateType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_TcpIpStatePtrType;

/**   \brief  type used to point to EthSM_TrcvLinkState */
typedef P2VAR(EthSM_TrcvLinkStateType, TYPEDEF, ETHSM_VAR_NOINIT) EthSM_TrcvLinkStatePtrType;

/** 
  \}
*/ 

/** 
  \defgroup  EthSMPCRootValueTypes  EthSM Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in EthSM_PCConfig */
typedef struct sEthSM_PCConfigType
{
  uint8 EthSM_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} EthSM_PCConfigType;

typedef EthSM_PCConfigType EthSM_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  EthSM_ActiveIpVxCnt
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_ActiveIpVxCntUType, ETHSM_VAR_NOINIT) EthSM_ActiveIpVxCnt;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_Initialized
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_InitializedType, ETHSM_VAR_ZERO_INIT) EthSM_Initialized;
#define ETHSM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_LastReportedState
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_LastReportedStateUType, ETHSM_VAR_NOINIT) EthSM_LastReportedState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_Mode
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_ModeUType, ETHSM_VAR_NOINIT) EthSM_Mode;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_RequestedMode
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_RequestedModeUType, ETHSM_VAR_NOINIT) EthSM_RequestedMode;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_State
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_StateUType, ETHSM_VAR_NOINIT) EthSM_State;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_TcpIpState
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_TcpIpStateUType, ETHSM_VAR_NOINIT) EthSM_TcpIpState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  EthSM_TrcvLinkState
**********************************************************************************************************************/
#define ETHSM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(EthSM_TrcvLinkStateUType, ETHSM_VAR_NOINIT) EthSM_TrcvLinkState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define ETHSM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



#endif /* ETHSM_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: EthSM_Cfg.h
 *********************************************************************************************************************/

