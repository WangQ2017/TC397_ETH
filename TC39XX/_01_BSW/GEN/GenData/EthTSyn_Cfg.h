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
 *            Module: EthTSyn
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthTSyn_Cfg.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#ifndef ETHTSYN_CFG_H
#define ETHTSYN_CFG_H
 
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
 
/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#ifndef ETHTSYN_USE_DUMMY_STATEMENT
#define ETHTSYN_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTSYN_DUMMY_STATEMENT
#define ETHTSYN_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTSYN_DUMMY_STATEMENT_CONST
#define ETHTSYN_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTSYN_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ETHTSYN_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ETHTSYN_ATOMIC_VARIABLE_ACCESS
#define ETHTSYN_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef ETHTSYN_PROCESSOR_TC397X_STEPB
#define ETHTSYN_PROCESSOR_TC397X_STEPB
#endif
#ifndef ETHTSYN_COMP_TASKING
#define ETHTSYN_COMP_TASKING
#endif
#ifndef ETHTSYN_GEN_GENERATOR_MSR
#define ETHTSYN_GEN_GENERATOR_MSR
#endif
#ifndef ETHTSYN_CPUTYPE_BITORDER_LSB2MSB
#define ETHTSYN_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef ETHTSYN_CONFIGURATION_VARIANT_PRECOMPILE
#define ETHTSYN_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ETHTSYN_CONFIGURATION_VARIANT_LINKTIME
#define ETHTSYN_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ETHTSYN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ETHTSYN_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ETHTSYN_CONFIGURATION_VARIANT
#define ETHTSYN_CONFIGURATION_VARIANT ETHTSYN_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ETHTSYN_POSTBUILD_VARIANT_SUPPORT
#define ETHTSYN_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif
 


/**********************************************************************************************************************
 *  INTEGER DEFINES
 *********************************************************************************************************************/
#define ETHTSYN_CFG_MAJOR_VERSION                     13u
#define ETHTSYN_CFG_MINOR_VERSION                     2u

#define ETHTSYN_MAIN_FUNCTION_CYCLE                   5u /*  ms  */ 
#define ETHTSYN_FRAME_TYPE                            0x88F7u
#define ETHTSYN_TIME_DOMAIN_COUNT                     1u
#define ETHTSYN_PORT_COUNT                            1u

#define ETHTSYN_FLAGS_OCTET_1_DEFAULT_VALUE           0x00u
#define ETHTSYN_FOLLOW_UP_DATA_ID_LIST_SIZE           16u
#define ETHTSYN_SWT_MGMT_MSG_BUFFER_PAYLOAD_SIZE      2u /*  Dummy size for type SwtMgmt typedefs. SwtMgmt is disabled and type is not used.  */ 
#define ETHTSYN_SWT_MGMT_RX_MSG_BUFFER_SIZE           2u /*  Dummy size for type SwtMgmt typedefs. SwtMgmt is disabled and type is not used.  */ 

/* ----- Bridge mode values ----- */
#define ETHTSYN_SWT_MGMT_BRIDGE_MODE_NONE             0u
#define ETHTSYN_SWT_MGMT_BRIDGE_MODE_TRANSPARENT      1u
#define ETHTSYN_SWT_MGMT_BRIDGE_MODE_BOUNDARY         2u


/**********************************************************************************************************************
 *  SWITCH DEFINES
 *********************************************************************************************************************/
#define ETHTSYN_DEV_ERROR_DETECT                                 STD_ON
#define ETHTSYN_DEV_ERROR_REPORT                                 STD_ON
#define ETHTSYN_VERSION_INFO_API                                 STD_OFF

#define ETHTSYN_HW_TIMESTAMP_SUPPORT                             STD_ON
#define ETHTSYN_CRC_SUPPORT                                      STD_OFF
#define ETHTSYN_MASTER_SLAVE_CONFLICT_DETECTION                  STD_OFF
#define ETHTSYN_MESSAGE_COMPLIANCE                               STD_OFF
#define ETHTSYN_OFS_TIME_DOMAIN_SUPPORT                          STD_OFF
#define ETHTSYN_TX_SUPPORT                                       STD_ON
#define ETHTSYN_PDELAY_INITIATOR_SUPPORT                         STD_ON
#define ETHTSYN_PDELAY_RESPONDER_SUPPORT                         STD_ON
#define ETHTSYN_MASTER_SUPPORT                                   STD_OFF
#define ETHTSYN_ANNOUNCE_TX_SUPPORT                              STD_OFF
#define ETHTSYN_SLAVE_SUPPORT                                    STD_ON
#define ETHTSYN_ANNOUNCE_RX_SUPPORT                              STD_OFF
#define ETHTSYN_SRC_PORT_IDENT_CHECK_SUPPORT                     STD_OFF
#define ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT                   STD_OFF
#define ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT                    STD_OFF
#define ETHTSYN_SWT_MGMT_SUPPORT                                 STD_OFF
#define ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT                   STD_OFF
#define ETHTSYN_SWT_TIME_SYNC_SUPPORT                            STD_OFF
#define ETHTSYN_SWT_MGMT_BRIDGE_MODE                             ETHTSYN_SWT_MGMT_BRIDGE_MODE_NONE
#define ETHTSYN_SWT_MGMT_ONE_TAS                                 STD_OFF /*  Consider Host and Switch as one Time-Aware system  */ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  EthTSynPCDataSwitches  EthTSyn Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define ETHTSYN_ANNOUNCEINFO                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCEALLOWEDRXDELAYOFANNOUNCEINFO                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MAXESTEPSREMOVEDOFANNOUNCEINFO                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCERECEIVESM                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSM                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCECYCLETIMEROFANNOUNCESENDSM                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEOFANNOUNCESENDSM                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSMCFG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCETXCYCLEOFANNOUNCESENDSMCFG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CTRL                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ETHIFCTRLIDXOFCTRL                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTINDENDIDXOFCTRL                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTINDSTARTIDXOFCTRL                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CTRLSTATE                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_DESTINATIONMAC                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FINALMAGICNUMBER                                                                    STD_OFF  /**< Deactivateable: 'EthTSyn_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTSYN_FOLLOWUPDATAIDLIST                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_INITDATAHASHCODE                                                                    STD_OFF  /**< Deactivateable: 'EthTSyn_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTSYN_MASTERPORT                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSMCFGIDXOFMASTERPORT                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSMCFGUSEDOFMASTERPORT                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CRCTIMEFLAGSOFMASTERPORT                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CYCLICMSGRESUMECNTOFMASTERPORT                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPMSGLENGTHOFMASTERPORT                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPSENTCBKPTROFMASTERPORT                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_IMMEDIATETIMESYNCOFMASTERPORT                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFSSUBTLVOFMASTERPORT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTIDXOFMASTERPORT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATUSSUBTLVOFMASTERPORT                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCLOGMSGINTERVALOFMASTERPORT                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCSENDINTERVALOFMASTERPORT                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCSENTCBKPTROFMASTERPORT                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMESUBTLVOFMASTERPORT                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TXCRCSECUREDOFMASTERPORT                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_USERDATASUBTLVOFMASTERPORT                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTIDENTITY                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CLOCKIDENTITYOFMASTERPORTIDENTITY                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFFSETTIMEDOMAIN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_IDOFOFFSETTIMEDOMAIN                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFOFFSETTIMEDOMAIN                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFSCORRDURATIONINSYNCCYCLES                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_COUNTEROFOFSCORRDURATIONINSYNCCYCLES                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RESTARTEDOFOFSCORRDURATIONINSYNCCYCLES                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYCONFIG                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ALWAYSASCAPABLEOFPDELAYCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_INITIALPDELAYNSOFPDELAYCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINITIATORIDXOFPDELAYCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINITIATORUSEDOFPDELAYCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPONDERIDXOFPDELAYCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPONDERUSEDOFPDELAYCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTIDXOFPDELAYCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_USESTATICPDELAYOFPDELAYCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINFO                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ASCAPABLEOFPDELAYINFO                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYVALUENSOFPDELAYINFO                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_USEAVERAGEOFPDELAYINFO                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINITIATOR                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ALLOWEDLOSTRESPONSESOFPDELAYINITIATOR                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_AVERAGEWEIGHTOFPDELAYINITIATOR                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_LOGMESSAGEINTERVALOFPDELAYINITIATOR                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYREQSMIDXOFPDELAYINITIATOR                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYTHRESHOLDOFPDELAYINITIATOR                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RESPRESPFOLLOWUPTIMEOUTOFPDELAYINITIATOR                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TXINTERVALMFOFPDELAYINITIATOR                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYREQSM                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPSM                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPONDER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPSMIDXOFPDELAYRESPONDER                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PHYSPORT                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_DEBOUNCETIMEROFPHYSPORT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PHYSPORTCFG                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_DEBOUNCETIMEOFPHYSPORTCFG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORT                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CTRLIDXOFPORT                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FRAMEPRIOOFPORT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTIDXOFPORT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTUSEDOFPORT                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_NUMBEROFPORT                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYCONFIGIDXOFPORT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYCONFIGUSEDOFPORT                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PHYSPORTCFGIDXOFPORT                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORTIDXOFPORT                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORTUSEDOFPORT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STBMTIMESRCEQUALOFPORT                                                              STD_ON
#define ETHTSYN_SWITCHPORTMGMTIDXOFPORT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHPORTMGMTUSEDOFPORT                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEDOMAINIDXOFPORT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDMASTERCFGIDXOFPORT                                                         STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidMasterCfgIdx' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDMASTERCFGUSEDOFPORT                                                        STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidMasterCfgUsed' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDPDREQCFGIDXOFPORT                                                          STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidPdReqCfgIdx' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDPDREQCFGUSEDOFPORT                                                         STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidPdReqCfgUsed' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDPDRESPCFGIDXOFPORT                                                         STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidPdRespCfgIdx' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDPDRESPCFGUSEDOFPORT                                                        STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidPdRespCfgUsed' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDSLAVECFGIDXOFPORT                                                          STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidSlaveCfgIdx' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_TIMEVALIDSLAVECFGUSEDOFPORT                                                         STD_OFF  /**< Deactivateable: 'EthTSyn_Port.TimeValidSlaveCfgUsed' Reason: 'TimeValidation is deactivated' */
#define ETHTSYN_PORTIND                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTSYNCSENDSM                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEOFPORTSYNCSENDSM                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHOSTEGRINTVLTMGMTOFPORTSYNCSENDSM                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCSWTEGRTSMGMTOFPORTSYNCSENDSM                                                    STD_OFF  /**< Deactivateable: 'EthTSyn_PortSyncSendSm.SyncSwtEgrTsMgmt' Reason: 'Switch timestamp support is disabled' */
#define ETHTSYN_SYNCSWTINGRTSMGMTOFPORTSYNCSENDSM                                                   STD_OFF  /**< Deactivateable: 'EthTSyn_PortSyncSendSm.SyncSwtIngrTsMgmt' Reason: 'Switch timestamp support is disabled' */
#define ETHTSYN_SYNCTXCONFCALLEDOFPORTSYNCSENDSM                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TXBUFIDXOFPORTSYNCSENDSM                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TXBUFPTROFPORTSYNCSENDSM                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATEMEASUREMENT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ACCUMULATEDMASTERTIMEDIFFOFRATEMEASUREMENT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ACCUMULATEDSWTTIMEDIFFOFRATEMEASUREMENT                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ACTIVENROFSYNCCYCLESOFRATEMEASUREMENT                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ACTIVEOFRATEMEASUREMENT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SITESYNCSYNCSM                                                                      STD_OFF  /**< Deactivateable: 'EthTSyn_SiteSyncSyncSm' Reason: 'Switch management is disabled' */
#define ETHTSYN_SIZEOFANNOUNCEINFO                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCERECEIVESM                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCESENDSM                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCESENDSMCFG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFCTRL                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFCTRLSTATE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFDESTINATIONMAC                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFFOLLOWUPDATAIDLIST                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFMASTERPORT                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFMASTERPORTIDENTITY                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFOFFSETTIMEDOMAIN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFOFSCORRDURATIONINSYNCCYCLES                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYINFO                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYINITIATOR                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYREQSM                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYRESPSM                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYRESPONDER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPHYSPORT                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPHYSPORTCFG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORT                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORTIND                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORTSYNCSENDSM                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFRATEMEASUREMENT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSLAVEPORT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSLAVESWITCHIDXLIST                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHPORTMGMT                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMECFG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMEINFO                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMETXFRAMEINFO                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHTIMESYNCCFG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHTIMESYNCINFO                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWTMGMTRCVDMSGBUF                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWTTIMESYNCRATEREGULATORCFG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYNCRECEIVESM                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYNCSENDSM                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYSTEMSTATE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEBASEUPDATECOUNTER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEDOMAIN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDMASTERCFG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDMASTERDATA                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDREQCFG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDREQDATA                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDRESPCFG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDRESPDATA                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDSLAVECFG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDSLAVEDATA                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORT                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCEINFOIDXOFSLAVEPORT                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCEINFOUSEDOFSLAVEPORT                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CRCFLAGSRXVALIDATEDOFSLAVEPORT                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPALLOWEDRXDELAYOFSLAVEPORT                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTIDENTITYIDXOFSLAVEPORT                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTIDENTITYUSEDOFSLAVEPORT                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTIDXOFSLAVEPORT                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RXCRCVALIDATEDOFSLAVEPORT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVESWITCHIDXLIST                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHPORTMGMT                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTIDXOFSWITCHPORTMGMT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHIDXOFSWITCHPORTMGMT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMECFG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ETHIFCTRLIDXOFSWITCHSYNCFRAMECFG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FRAMEPRIOOFSWITCHSYNCFRAMECFG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MGMTPORTETHIFSWITCHIDXOFSWITCHSYNCFRAMECFG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MGMTPORTSWITCHPORTIDXOFSWITCHSYNCFRAMECFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTIDXOFSWITCHSYNCFRAMECFG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHTIMESYNCCFGIDXOFSWITCHSYNCFRAMECFG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCTXINTERVALOFSWITCHSYNCFRAMECFG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMEINFO                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PRECISEORIGINTSMGMTOFSWITCHSYNCFRAMEINFO                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SEQUENCEIDOFSWITCHSYNCFRAMEINFO                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEOFSWITCHSYNCFRAMEINFO                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTINGRESSTSMGMTOFSWITCHSYNCFRAMEINFO                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCTXCNTOFSWITCHSYNCFRAMEINFO                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMETXFRAMEINFO                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_BUFADDROFSWITCHSYNCFRAMETXFRAMEINFO                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_BUFIDXOFSWITCHSYNCFRAMETXFRAMEINFO                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_GLOBALTIMEOFSWITCHSYNCFRAMETXFRAMEINFO                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_INTVLTOFSWITCHSYNCFRAMETXFRAMEINFO                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHTIMESYNCCFG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_APPLYRATERATIOTOSLAVESWITCHESOFSWITCHTIMESYNCCFG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ETHIFSWITCHIDXOFSWITCHTIMESYNCCFG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MAXOUTOFSYNCCNTOFSWITCHTIMESYNCCFG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVESWITCHIDXLISTENDIDXOFSWITCHTIMESYNCCFG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVESWITCHIDXLISTUSEDOFSWITCHTIMESYNCCFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMECFGUSEDOFSWITCHTIMESYNCCFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTSYNCSTATECHGFCTPTROFSWITCHTIMESYNCCFG                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTTIMESYNCRATEREGULATORCFGIDXOFSWITCHTIMESYNCCFG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCEVENTTIMEOUTOFSWITCHTIMESYNCCFG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCPRECISIONLIMITNSOFSWITCHTIMESYNCCFG                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEDOMAINIDXOFSWITCHTIMESYNCCFG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHTIMESYNCINFO                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CURRENTOFFSETNSOFSWITCHTIMESYNCINFO                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_LASTCORRECTEDOFFSETNSOFSWITCHTIMESYNCINFO                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OUTOFSYNCCNTOFSWITCHTIMESYNCINFO                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PREVTIMESTAMPINFOOFSWITCHTIMESYNCINFO                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEOFSWITCHTIMESYNCINFO                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTSYNCSTATEOFSWITCHTIMESYNCINFO                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCEVENTTIMEOUTCNTOFSWITCHTIMESYNCINFO                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMESTAMPINFOOFSWITCHTIMESYNCINFO                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_WASSYNCREACHEDOFSWITCHTIMESYNCINFO                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTMGMTOBJHNDL                                                                  STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtMgmtObjHndl' Reason: 'Switch management is disabeld' */
#define ETHTSYN_ETHSWTMGMTOBJPTROFSWTMGMTMGMTOBJHNDL                                                STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtMgmtObjHndl.EthSwtMgmtObjPtr' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTEGRESSTSMGMTOFSWTMGMTMGMTOBJHNDL                                                 STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtMgmtObjHndl.SwtEgressTsMgmt' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTINGRESSTSMGMTOFSWTMGMTMGMTOBJHNDL                                                STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtMgmtObjHndl.SwtIngressTsMgmt' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTINFOOFSWTMGMTMGMTOBJHNDL                                                     STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtMgmtObjHndl.SwtMgmtInfo' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRCVDMSGBUF                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTRXBUF                                                                        STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBuf' Reason: 'Switch management is disabeld' */
#define ETHTSYN_CTRLIDXOFSWTMGMTRXBUF                                                               STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBuf.CtrlIdx' Reason: 'Switch management is disabeld' */
#define ETHTSYN_HOSTINGRESSINTVLTMGMTOFSWTMGMTRXBUF                                                 STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBuf.HostIngressIntVltMgmt' Reason: 'Switch management is disabeld' */
#define ETHTSYN_STATEOFSWTMGMTRXBUF                                                                 STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBuf.State' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRXBUFCFG                                                                     STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBufCfg' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTMGMTOBJHNDLIDXOFSWTMGMTRXBUFCFG                                              STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBufCfg.SwtMgmtMgmtObjHndlIdx' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRCVDMSGBUFENDIDXOFSWTMGMTRXBUFCFG                                            STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBufCfg.SwtMgmtRcvdMsgBufEndIdx' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRCVDMSGBUFLENGTHOFSWTMGMTRXBUFCFG                                            STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBufCfg.SwtMgmtRcvdMsgBufLength' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRCVDMSGBUFSTARTIDXOFSWTMGMTRXBUFCFG                                          STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtRxBufCfg.SwtMgmtRcvdMsgBufStartIdx' Reason: 'Switch management is disabeld' */
#define ETHTSYN_SWTMGMTRXBUFQUEUECURRPROCIDX                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTRXBUFQUEUEFREEIDX                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTTXMGMTOBJ                                                                    STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObj' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_CTRLIDXOFSWTMGMTTXMGMTOBJ                                                           STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObj.CtrlIdx' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_SMEGRESSTSMGMTPTROFSWTMGMTTXMGMTOBJ                                                 STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObj.SmEgressTsMgmtPtr' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_SMINGRESSTSMGMTPTROFSWTMGMTTXMGMTOBJ                                                STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObj.SmIngressTsMgmtPtr' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_STATEOFSWTMGMTTXMGMTOBJ                                                             STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObj.State' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_SWTMGMTTXMGMTOBJCFG                                                                 STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObjCfg' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_SWTMGMTMGMTOBJHNDLIDXOFSWTMGMTTXMGMTOBJCFG                                          STD_OFF  /**< Deactivateable: 'EthTSyn_SwtMgmtTxMgmtObjCfg.SwtMgmtMgmtObjHndlIdx' Reason: 'Switch management or Switch timestamping is disabeld' */
#define ETHTSYN_SWTMGMTTXMGMTOBJQUEUECURRPROCIDX                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTTXMGMTOBJQUEUEFREEIDX                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTTIMESYNCRATEREGULATORCFG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_NRPARALLELRATEMEASUREMENTSOFSWTTIMESYNCRATEREGULATORCFG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_NRSYNCCYCLESFOROFSCORROFSWTTIMESYNCRATEREGULATORCFG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFSJUMPCORRTHRESHOLDNSOFSWTTIMESYNCRATEREGULATORCFG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATEMEASUREMENTENDIDXOFSWTTIMESYNCRATEREGULATORCFG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATEMEASUREMENTLENGTHOFSWTTIMESYNCRATEREGULATORCFG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATEMEASUREMENTSTARTIDXOFSWTTIMESYNCRATEREGULATORCFG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATERATIOMAXOFSWTTIMESYNCRATEREGULATORCFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATERATIOMINOFSWTTIMESYNCRATEREGULATORCFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_USEINITIALOFFSETCORRECTIONOFSWTTIMESYNCRATEREGULATORCFG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCRECEIVESM                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCSENDSM                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYSTEMSTATE                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_GMCLOCKIDENTITYOFSYSTEMSTATE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_GMPRESENTOFSYSTEMSTATE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEBASEUPDATECOUNTER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_VALIDOFTIMEBASEUPDATECOUNTER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_VALUEOFTIMEBASEUPDATECOUNTER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEDOMAIN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPDATAIDLISTENDIDXOFTIMEDOMAIN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FOLLOWUPDATAIDLISTUSEDOFTIMEDOMAIN                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_IDOFTIMEDOMAIN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_IMMEDIATETIMESYNCOFTIMEDOMAIN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTENDIDXOFTIMEDOMAIN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTLENGTHOFTIMEDOMAIN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTSTARTIDXOFTIMEDOMAIN                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTUSEDOFTIMEDOMAIN                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFFSETTIMEDOMAINENDIDXOFTIMEDOMAIN                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFFSETTIMEDOMAINUSEDOFTIMEDOMAIN                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SITESYNCSYNCSMIDXOFTIMEDOMAIN                                                       STD_OFF  /**< Deactivateable: 'EthTSyn_TimeDomain.SiteSyncSyncSmIdx' Reason: 'Switch management is disabled' */
#define ETHTSYN_SITESYNCSYNCSMUSEDOFTIMEDOMAIN                                                      STD_OFF  /**< Deactivateable: 'EthTSyn_TimeDomain.SiteSyncSyncSmUsed' Reason: 'Switch management is disabled' */
#define ETHTSYN_SLAVEPORTENDIDXOFTIMEDOMAIN                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORTSTARTIDXOFTIMEDOMAIN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORTUSEDOFTIMEDOMAIN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTKEEPSRCPORTIDENTITYOFTIMEDOMAIN                                              STD_OFF  /**< Deactivateable: 'EthTSyn_TimeDomain.SwtMgmtKeepSrcPortIdentity' Reason: 'Switch management is disabled' */
#define ETHTSYN_SWTMGMTNUMMSGFWDRETRYOFTIMEDOMAIN                                                   STD_OFF  /**< Deactivateable: 'EthTSyn_TimeDomain.SwtMgmtNumMsgFwdRetry' Reason: 'Switch management is disabled' */
#define ETHTSYN_SWTMGMTSYNCTIMEOUTOFTIMEDOMAIN                                                      STD_OFF  /**< Deactivateable: 'EthTSyn_TimeDomain.SwtMgmtSyncTimeout' Reason: 'Switch management is disabled' */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFTIMEDOMAIN                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDMASTERCFG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDMASTERCFG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDMASTERDATA                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CORRECTIONFIELDOFTIMEVALIDMASTERDATA                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PRECISEORIGINTIMESTAMPOFTIMEVALIDMASTERDATA                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SEQUENCEIDOFTIMEVALIDMASTERDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCCLOCKIDOFTIMEVALIDMASTERDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCPORTNUMOFTIMEVALIDMASTERDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEFLAGSOFTIMEVALIDMASTERDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCEGRESSTSVLTOFTIMEVALIDMASTERDATA                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDREQCFG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDREQCFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDREQDATA                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CURRPDELAYOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDREQEGRESSTSVLTOFTIMEVALIDPDREQDATA                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDREQRCVDTSOFTIMEVALIDPDREQDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDRESPCLOCKIDOFTIMEVALIDPDREQDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDRESPINGRESSTSVLTOFTIMEVALIDPDREQDATA                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDRESPPORTNUMOFTIMEVALIDPDREQDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDRESPSENTTSOFTIMEVALIDPDREQDATA                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_REFTIMEGLOBALOFTIMEVALIDPDREQDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_REFTIMEVLTOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SEQUENCEIDOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCCLOCKIDOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCPORTNUMOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEFLAGSOFTIMEVALIDPDREQDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDRESPCFG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDRESPCFG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDRESPDATA                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDREQCLOCKIDOFTIMEVALIDPDRESPDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDREQINGRESSTSVLTOFTIMEVALIDPDRESPDATA                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDREQPORTNUMOFTIMEVALIDPDRESPDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDRESPEGRESSTSVLTOFTIMEVALIDPDRESPDATA                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_REFTIMEGLOBALOFTIMEVALIDPDRESPDATA                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_REFTIMEVLTOFTIMEVALIDPDRESPDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SEQUENCEIDOFTIMEVALIDPDRESPDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCCLOCKIDOFTIMEVALIDPDRESPDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SRCPORTNUMOFTIMEVALIDPDRESPDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEFLAGSOFTIMEVALIDPDRESPDATA                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDSLAVECFG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDSLAVECFG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDSLAVEDATA                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CORRECTIONFIELDOFTIMEVALIDSLAVEDATA                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CURRPDELAYOFTIMEVALIDSLAVEDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERCLOCKIDOFTIMEVALIDSLAVEDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTNUMOFTIMEVALIDSLAVEDATA                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PRECISEORIGINTIMESTAMPOFTIMEVALIDSLAVEDATA                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SEQUENCEIDOFTIMEVALIDSLAVEDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_STATEFLAGSOFTIMEVALIDSLAVEDATA                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCINGRESSTSVLTOFTIMEVALIDSLAVEDATA                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PCCONFIG                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCEINFOOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCERECEIVESMOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSMCFGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_ANNOUNCESENDSMOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CTRLOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_CTRLSTATEOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_DESTINATIONMACOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_FINALMAGICNUMBEROFPCCONFIG                                                          STD_OFF  /**< Deactivateable: 'EthTSyn_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTSYN_FOLLOWUPDATAIDLISTOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_INITDATAHASHCODEOFPCCONFIG                                                          STD_OFF  /**< Deactivateable: 'EthTSyn_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETHTSYN_MASTERPORTIDENTITYOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_MASTERPORTOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFFSETTIMEDOMAINOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_OFSCORRDURATIONINSYNCCYCLESOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYCONFIGOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINFOOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYINITIATOROFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYREQSMOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPSMOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PDELAYRESPONDEROFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PHYSPORTCFGOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PHYSPORTOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTINDOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_PORTSYNCSENDSMOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_RATEMEASUREMENTOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCEINFOOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCERECEIVESMOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCESENDSMCFGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFANNOUNCESENDSMOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFCTRLOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFCTRLSTATEOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFDESTINATIONMACOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFFOLLOWUPDATAIDLISTOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFMASTERPORTIDENTITYOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFMASTERPORTOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFOFFSETTIMEDOMAINOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFOFSCORRDURATIONINSYNCCYCLESOFPCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYCONFIGOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYINFOOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYINITIATOROFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYREQSMOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYRESPSMOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPDELAYRESPONDEROFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPHYSPORTCFGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPHYSPORTOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORTINDOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORTOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFPORTSYNCSENDSMOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFRATEMEASUREMENTOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSLAVEPORTOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSLAVESWITCHIDXLISTOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHPORTMGMTOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMECFGOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMEINFOOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHSYNCFRAMETXFRAMEINFOOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHTIMESYNCCFGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWITCHTIMESYNCINFOOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWTMGMTRCVDMSGBUFOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYNCRECEIVESMOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYNCSENDSMOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFSYSTEMSTATEOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEBASEUPDATECOUNTEROFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEDOMAINOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDMASTERCFGOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDMASTERDATAOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDREQCFGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDREQDATAOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDRESPCFGOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDPDRESPDATAOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDSLAVECFGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SIZEOFTIMEVALIDSLAVEDATAOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVEPORTOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SLAVESWITCHIDXLISTOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHPORTMGMTOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMECFGOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMEINFOOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHSYNCFRAMETXFRAMEINFOOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHTIMESYNCCFGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWITCHTIMESYNCINFOOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTRCVDMSGBUFOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTRXBUFQUEUECURRPROCIDXOFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTRXBUFQUEUEFREEIDXOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTTXMGMTOBJQUEUECURRPROCIDXOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTMGMTTXMGMTOBJQUEUEFREEIDXOFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCRECEIVESMOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYNCSENDSMOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_SYSTEMSTATEOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEBASEUPDATECOUNTEROFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEDOMAINOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDMASTERCFGOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDMASTERDATAOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDREQCFGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDREQDATAOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDRESPCFGOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDPDRESPDATAOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDSLAVECFGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETHTSYN_TIMEVALIDSLAVEDATAOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCMinNumericValueDefines  EthTSyn Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define ETHTSYN_MIN_ANNOUNCECYCLETIMEROFANNOUNCESENDSM                                              0u
#define ETHTSYN_MIN_COUNTEROFOFSCORRDURATIONINSYNCCYCLES                                            0u
#define ETHTSYN_MIN_DEBOUNCETIMEROFPHYSPORT                                                         0u
#define ETHTSYN_MIN_TXBUFIDXOFPORTSYNCSENDSM                                                        0u
#define ETHTSYN_MIN_ACTIVENROFSYNCCYCLESOFRATEMEASUREMENT                                           0u
#define ETHTSYN_MIN_SEQUENCEIDOFSWITCHSYNCFRAMEINFO                                                 0u
#define ETHTSYN_MIN_SYNCTXCNTOFSWITCHSYNCFRAMEINFO                                                  0u
#define ETHTSYN_MIN_BUFIDXOFSWITCHSYNCFRAMETXFRAMEINFO                                              0u
#define ETHTSYN_MIN_CURRENTOFFSETNSOFSWITCHTIMESYNCINFO                                             -9223372036854775808
#define ETHTSYN_MIN_LASTCORRECTEDOFFSETNSOFSWITCHTIMESYNCINFO                                       -9223372036854775808
#define ETHTSYN_MIN_OUTOFSYNCCNTOFSWITCHTIMESYNCINFO                                                0u
#define ETHTSYN_MIN_SYNCEVENTTIMEOUTCNTOFSWITCHTIMESYNCINFO                                         0u
#define ETHTSYN_MIN_SWTMGMTRCVDMSGBUF                                                               0u
#define ETHTSYN_MIN_SWTMGMTRXBUFQUEUECURRPROCIDX                                                    0u
#define ETHTSYN_MIN_SWTMGMTRXBUFQUEUEFREEIDX                                                        0u
#define ETHTSYN_MIN_SWTMGMTTXMGMTOBJQUEUECURRPROCIDX                                                0u
#define ETHTSYN_MIN_SWTMGMTTXMGMTOBJQUEUEFREEIDX                                                    0u
#define ETHTSYN_MIN_GMCLOCKIDENTITYOFSYSTEMSTATE                                                    0u
#define ETHTSYN_MIN_VALUEOFTIMEBASEUPDATECOUNTER                                                    0u
#define ETHTSYN_MIN_CORRECTIONFIELDOFTIMEVALIDMASTERDATA                                            -9223372036854775808
#define ETHTSYN_MIN_SEQUENCEIDOFTIMEVALIDMASTERDATA                                                 0u
#define ETHTSYN_MIN_SRCCLOCKIDOFTIMEVALIDMASTERDATA                                                 0u
#define ETHTSYN_MIN_SRCPORTNUMOFTIMEVALIDMASTERDATA                                                 0u
#define ETHTSYN_MIN_STATEFLAGSOFTIMEVALIDMASTERDATA                                                 0u
#define ETHTSYN_MIN_CURRPDELAYOFTIMEVALIDPDREQDATA                                                  0u
#define ETHTSYN_MIN_PDRESPCLOCKIDOFTIMEVALIDPDREQDATA                                               0u
#define ETHTSYN_MIN_PDRESPPORTNUMOFTIMEVALIDPDREQDATA                                               0u
#define ETHTSYN_MIN_SEQUENCEIDOFTIMEVALIDPDREQDATA                                                  0u
#define ETHTSYN_MIN_SRCCLOCKIDOFTIMEVALIDPDREQDATA                                                  0u
#define ETHTSYN_MIN_SRCPORTNUMOFTIMEVALIDPDREQDATA                                                  0u
#define ETHTSYN_MIN_STATEFLAGSOFTIMEVALIDPDREQDATA                                                  0u
#define ETHTSYN_MIN_PDREQCLOCKIDOFTIMEVALIDPDRESPDATA                                               0u
#define ETHTSYN_MIN_PDREQPORTNUMOFTIMEVALIDPDRESPDATA                                               0u
#define ETHTSYN_MIN_SEQUENCEIDOFTIMEVALIDPDRESPDATA                                                 0u
#define ETHTSYN_MIN_SRCCLOCKIDOFTIMEVALIDPDRESPDATA                                                 0u
#define ETHTSYN_MIN_SRCPORTNUMOFTIMEVALIDPDRESPDATA                                                 0u
#define ETHTSYN_MIN_STATEFLAGSOFTIMEVALIDPDRESPDATA                                                 0u
#define ETHTSYN_MIN_CORRECTIONFIELDOFTIMEVALIDSLAVEDATA                                             -9223372036854775808
#define ETHTSYN_MIN_CURRPDELAYOFTIMEVALIDSLAVEDATA                                                  0u
#define ETHTSYN_MIN_MASTERCLOCKIDOFTIMEVALIDSLAVEDATA                                               0u
#define ETHTSYN_MIN_MASTERPORTNUMOFTIMEVALIDSLAVEDATA                                               0u
#define ETHTSYN_MIN_SEQUENCEIDOFTIMEVALIDSLAVEDATA                                                  0u
#define ETHTSYN_MIN_STATEFLAGSOFTIMEVALIDSLAVEDATA                                                  0u
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCMaxNumericValueDefines  EthTSyn Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define ETHTSYN_MAX_ANNOUNCECYCLETIMEROFANNOUNCESENDSM                                              4294967295u
#define ETHTSYN_MAX_COUNTEROFOFSCORRDURATIONINSYNCCYCLES                                            255u
#define ETHTSYN_MAX_DEBOUNCETIMEROFPHYSPORT                                                         4294967295u
#define ETHTSYN_MAX_TXBUFIDXOFPORTSYNCSENDSM                                                        255u
#define ETHTSYN_MAX_ACTIVENROFSYNCCYCLESOFRATEMEASUREMENT                                           255u
#define ETHTSYN_MAX_SEQUENCEIDOFSWITCHSYNCFRAMEINFO                                                 65535u
#define ETHTSYN_MAX_SYNCTXCNTOFSWITCHSYNCFRAMEINFO                                                  4294967295u
#define ETHTSYN_MAX_BUFIDXOFSWITCHSYNCFRAMETXFRAMEINFO                                              255u
#define ETHTSYN_MAX_CURRENTOFFSETNSOFSWITCHTIMESYNCINFO                                             9223372036854775807
#define ETHTSYN_MAX_LASTCORRECTEDOFFSETNSOFSWITCHTIMESYNCINFO                                       9223372036854775807
#define ETHTSYN_MAX_OUTOFSYNCCNTOFSWITCHTIMESYNCINFO                                                255u
#define ETHTSYN_MAX_SYNCEVENTTIMEOUTCNTOFSWITCHTIMESYNCINFO                                         4294967295u
#define ETHTSYN_MAX_SWTMGMTRCVDMSGBUF                                                               255u
#define ETHTSYN_MAX_SWTMGMTRXBUFQUEUECURRPROCIDX                                                    255u
#define ETHTSYN_MAX_SWTMGMTRXBUFQUEUEFREEIDX                                                        255u
#define ETHTSYN_MAX_SWTMGMTTXMGMTOBJQUEUECURRPROCIDX                                                255u
#define ETHTSYN_MAX_SWTMGMTTXMGMTOBJQUEUEFREEIDX                                                    255u
#define ETHTSYN_MAX_GMCLOCKIDENTITYOFSYSTEMSTATE                                                    18446744073709551615u
#define ETHTSYN_MAX_VALUEOFTIMEBASEUPDATECOUNTER                                                    255u
#define ETHTSYN_MAX_CORRECTIONFIELDOFTIMEVALIDMASTERDATA                                            9223372036854775807
#define ETHTSYN_MAX_SEQUENCEIDOFTIMEVALIDMASTERDATA                                                 65535u
#define ETHTSYN_MAX_SRCCLOCKIDOFTIMEVALIDMASTERDATA                                                 18446744073709551615u
#define ETHTSYN_MAX_SRCPORTNUMOFTIMEVALIDMASTERDATA                                                 65535u
#define ETHTSYN_MAX_STATEFLAGSOFTIMEVALIDMASTERDATA                                                 255u
#define ETHTSYN_MAX_CURRPDELAYOFTIMEVALIDPDREQDATA                                                  4294967295u
#define ETHTSYN_MAX_PDRESPCLOCKIDOFTIMEVALIDPDREQDATA                                               18446744073709551615u
#define ETHTSYN_MAX_PDRESPPORTNUMOFTIMEVALIDPDREQDATA                                               65535u
#define ETHTSYN_MAX_SEQUENCEIDOFTIMEVALIDPDREQDATA                                                  65535u
#define ETHTSYN_MAX_SRCCLOCKIDOFTIMEVALIDPDREQDATA                                                  18446744073709551615u
#define ETHTSYN_MAX_SRCPORTNUMOFTIMEVALIDPDREQDATA                                                  65535u
#define ETHTSYN_MAX_STATEFLAGSOFTIMEVALIDPDREQDATA                                                  255u
#define ETHTSYN_MAX_PDREQCLOCKIDOFTIMEVALIDPDRESPDATA                                               18446744073709551615u
#define ETHTSYN_MAX_PDREQPORTNUMOFTIMEVALIDPDRESPDATA                                               65535u
#define ETHTSYN_MAX_SEQUENCEIDOFTIMEVALIDPDRESPDATA                                                 65535u
#define ETHTSYN_MAX_SRCCLOCKIDOFTIMEVALIDPDRESPDATA                                                 18446744073709551615u
#define ETHTSYN_MAX_SRCPORTNUMOFTIMEVALIDPDRESPDATA                                                 65535u
#define ETHTSYN_MAX_STATEFLAGSOFTIMEVALIDPDRESPDATA                                                 255u
#define ETHTSYN_MAX_CORRECTIONFIELDOFTIMEVALIDSLAVEDATA                                             9223372036854775807
#define ETHTSYN_MAX_CURRPDELAYOFTIMEVALIDSLAVEDATA                                                  4294967295u
#define ETHTSYN_MAX_MASTERCLOCKIDOFTIMEVALIDSLAVEDATA                                               18446744073709551615u
#define ETHTSYN_MAX_MASTERPORTNUMOFTIMEVALIDSLAVEDATA                                               65535u
#define ETHTSYN_MAX_SEQUENCEIDOFTIMEVALIDSLAVEDATA                                                  65535u
#define ETHTSYN_MAX_STATEFLAGSOFTIMEVALIDSLAVEDATA                                                  255u
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCNoReferenceDefines  EthTSyn No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define ETHTSYN_NO_ANNOUNCEALLOWEDRXDELAYOFANNOUNCEINFO                                             255u
#define ETHTSYN_NO_MAXESTEPSREMOVEDOFANNOUNCEINFO                                                   255u
#define ETHTSYN_NO_ANNOUNCETXCYCLEOFANNOUNCESENDSMCFG                                               255u
#define ETHTSYN_NO_ANNOUNCESENDSMCFGIDXOFMASTERPORT                                                 255u
#define ETHTSYN_NO_CRCTIMEFLAGSOFMASTERPORT                                                         255u
#define ETHTSYN_NO_CYCLICMSGRESUMECNTOFMASTERPORT                                                   255u
#define ETHTSYN_NO_FOLLOWUPMSGLENGTHOFMASTERPORT                                                    255u
#define ETHTSYN_NO_SYNCLOGMSGINTERVALOFMASTERPORT                                                   127
#define ETHTSYN_NO_SYNCSENDINTERVALOFMASTERPORT                                                     255u
#define ETHTSYN_NO_CLOCKIDENTITYOFMASTERPORTIDENTITY                                                255u
#define ETHTSYN_NO_IDOFOFFSETTIMEDOMAIN                                                             255u
#define ETHTSYN_NO_INITIALPDELAYNSOFPDELAYCONFIG                                                    65535u
#define ETHTSYN_NO_PDELAYINITIATORIDXOFPDELAYCONFIG                                                 255u
#define ETHTSYN_NO_PDELAYRESPONDERIDXOFPDELAYCONFIG                                                 255u
#define ETHTSYN_NO_ALLOWEDLOSTRESPONSESOFPDELAYINITIATOR                                            255u
#define ETHTSYN_NO_AVERAGEWEIGHTOFPDELAYINITIATOR                                                   255u
#define ETHTSYN_NO_LOGMESSAGEINTERVALOFPDELAYINITIATOR                                              127
#define ETHTSYN_NO_PDELAYTHRESHOLDOFPDELAYINITIATOR                                                 4294967295u
#define ETHTSYN_NO_RESPRESPFOLLOWUPTIMEOUTOFPDELAYINITIATOR                                         255u
#define ETHTSYN_NO_TXINTERVALMFOFPDELAYINITIATOR                                                    255u
#define ETHTSYN_NO_DEBOUNCETIMEOFPHYSPORTCFG                                                        255u
#define ETHTSYN_NO_FRAMEPRIOOFPORT                                                                  255u
#define ETHTSYN_NO_MASTERPORTIDXOFPORT                                                              255u
#define ETHTSYN_NO_NUMBEROFPORT                                                                     255u
#define ETHTSYN_NO_PDELAYCONFIGIDXOFPORT                                                            255u
#define ETHTSYN_NO_SLAVEPORTIDXOFPORT                                                               255u
#define ETHTSYN_NO_SWITCHPORTMGMTIDXOFPORT                                                          255u
#define ETHTSYN_NO_ANNOUNCEINFOIDXOFSLAVEPORT                                                       255u
#define ETHTSYN_NO_CRCFLAGSRXVALIDATEDOFSLAVEPORT                                                   255u
#define ETHTSYN_NO_FOLLOWUPALLOWEDRXDELAYOFSLAVEPORT                                                255u
#define ETHTSYN_NO_MASTERPORTIDENTITYIDXOFSLAVEPORT                                                 255u
#define ETHTSYN_NO_PORTIDXOFSWITCHPORTMGMT                                                          255u
#define ETHTSYN_NO_SWITCHIDXOFSWITCHPORTMGMT                                                        255u
#define ETHTSYN_NO_FRAMEPRIOOFSWITCHSYNCFRAMECFG                                                    255u
#define ETHTSYN_NO_SYNCTXINTERVALOFSWITCHSYNCFRAMECFG                                               255u
#define ETHTSYN_NO_MAXOUTOFSYNCCNTOFSWITCHTIMESYNCCFG                                               255u
#define ETHTSYN_NO_SLAVESWITCHIDXLISTENDIDXOFSWITCHTIMESYNCCFG                                      255u
#define ETHTSYN_NO_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG                                    255u
#define ETHTSYN_NO_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG                                         255u
#define ETHTSYN_NO_SYNCEVENTTIMEOUTOFSWITCHTIMESYNCCFG                                              255u
#define ETHTSYN_NO_SYNCPRECISIONLIMITNSOFSWITCHTIMESYNCCFG                                          255u
#define ETHTSYN_NO_NRPARALLELRATEMEASUREMENTSOFSWTTIMESYNCRATEREGULATORCFG                          255u
#define ETHTSYN_NO_NRSYNCCYCLESFOROFSCORROFSWTTIMESYNCRATEREGULATORCFG                              255u
#define ETHTSYN_NO_OFSJUMPCORRTHRESHOLDNSOFSWTTIMESYNCRATEREGULATORCFG                              255u
#define ETHTSYN_NO_FOLLOWUPDATAIDLISTENDIDXOFTIMEDOMAIN                                             255u
#define ETHTSYN_NO_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN                                           255u
#define ETHTSYN_NO_IDOFTIMEDOMAIN                                                                   255u
#define ETHTSYN_NO_MASTERPORTENDIDXOFTIMEDOMAIN                                                     255u
#define ETHTSYN_NO_MASTERPORTSTARTIDXOFTIMEDOMAIN                                                   255u
#define ETHTSYN_NO_OFFSETTIMEDOMAINENDIDXOFTIMEDOMAIN                                               255u
#define ETHTSYN_NO_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN                                             255u
#define ETHTSYN_NO_SLAVEPORTENDIDXOFTIMEDOMAIN                                                      255u
#define ETHTSYN_NO_SLAVEPORTSTARTIDXOFTIMEDOMAIN                                                    255u
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCEnumDefines  EthTSyn Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define ETHTSYN_IDLE_STATEOFANNOUNCESENDSM                                                          0x00u
#define ETHTSYN_TX_ANNOUNCE_STATEOFANNOUNCESENDSM                                                   0x01u
#define ETHTSYN_PENDING_STATEOFPORTSYNCSENDSM                                                       0x00u
#define ETHTSYN_TX_SYNC_STATEOFPORTSYNCSENDSM                                                       0x01u
#define ETHTSYN_WAIT_SYNC_TX_CONF_STATEOFPORTSYNCSENDSM                                             0x02u
#define ETHTSYN_WAIT_TX_FUP_STATEOFPORTSYNCSENDSM                                                   0x03u
#define ETHTSYN_TX_FUP_STATEOFPORTSYNCSENDSM                                                        0x04u
#define ETHTSYN_WAIT_FUP_TX_CONF_STATEOFPORTSYNCSENDSM                                              0x05u
#define ETHTSYN_IDLE_STATEOFSWITCHSYNCFRAMEINFO                                                     0x00u
#define ETHTSYN_WAIT_TX_STATEOFSWITCHSYNCFRAMEINFO                                                  0x01u
#define ETHTSYN_WAIT_TS_STATEOFSWITCHSYNCFRAMEINFO                                                  0x02u
#define ETHTSYN_WAIT_FIRST_STATEOFSWITCHTIMESYNCINFO                                                0x00u
#define ETHTSYN_WAIT_SECOND_STATEOFSWITCHTIMESYNCINFO                                               0x01u
#define ETHTSYN_WAIT_STATEOFSWITCHTIMESYNCINFO                                                      0x02u
#define ETHTSYN_READY_STATEOFSWITCHTIMESYNCINFO                                                     0x03u
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCIsReducedToDefineDefines  EthTSyn Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define ETHTSYN_ISDEF_ANNOUNCEALLOWEDRXDELAYOFANNOUNCEINFO                                          STD_OFF
#define ETHTSYN_ISDEF_MAXESTEPSREMOVEDOFANNOUNCEINFO                                                STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCETXCYCLEOFANNOUNCESENDSMCFG                                            STD_OFF
#define ETHTSYN_ISDEF_ETHIFCTRLIDXOFCTRL                                                            STD_OFF
#define ETHTSYN_ISDEF_PORTINDENDIDXOFCTRL                                                           STD_OFF
#define ETHTSYN_ISDEF_PORTINDSTARTIDXOFCTRL                                                         STD_OFF
#define ETHTSYN_ISDEF_DESTINATIONMAC                                                                STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPDATAIDLIST                                                            STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCESENDSMCFGIDXOFMASTERPORT                                              STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCESENDSMCFGUSEDOFMASTERPORT                                             STD_OFF
#define ETHTSYN_ISDEF_CRCTIMEFLAGSOFMASTERPORT                                                      STD_OFF
#define ETHTSYN_ISDEF_CYCLICMSGRESUMECNTOFMASTERPORT                                                STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPMSGLENGTHOFMASTERPORT                                                 STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPSENTCBKPTROFMASTERPORT                                                STD_OFF
#define ETHTSYN_ISDEF_IMMEDIATETIMESYNCOFMASTERPORT                                                 STD_OFF
#define ETHTSYN_ISDEF_OFSSUBTLVOFMASTERPORT                                                         STD_OFF
#define ETHTSYN_ISDEF_PORTIDXOFMASTERPORT                                                           STD_OFF
#define ETHTSYN_ISDEF_STATUSSUBTLVOFMASTERPORT                                                      STD_OFF
#define ETHTSYN_ISDEF_SYNCLOGMSGINTERVALOFMASTERPORT                                                STD_OFF
#define ETHTSYN_ISDEF_SYNCSENDINTERVALOFMASTERPORT                                                  STD_OFF
#define ETHTSYN_ISDEF_SYNCSENTCBKPTROFMASTERPORT                                                    STD_OFF
#define ETHTSYN_ISDEF_TIMESUBTLVOFMASTERPORT                                                        STD_OFF
#define ETHTSYN_ISDEF_TXCRCSECUREDOFMASTERPORT                                                      STD_OFF
#define ETHTSYN_ISDEF_USERDATASUBTLVOFMASTERPORT                                                    STD_OFF
#define ETHTSYN_ISDEF_CLOCKIDENTITYOFMASTERPORTIDENTITY                                             STD_OFF
#define ETHTSYN_ISDEF_IDOFOFFSETTIMEDOMAIN                                                          STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFOFFSETTIMEDOMAIN                                      STD_OFF
#define ETHTSYN_ISDEF_ALWAYSASCAPABLEOFPDELAYCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_INITIALPDELAYNSOFPDELAYCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_PDELAYINITIATORIDXOFPDELAYCONFIG                                              STD_OFF
#define ETHTSYN_ISDEF_PDELAYINITIATORUSEDOFPDELAYCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_PDELAYRESPONDERIDXOFPDELAYCONFIG                                              STD_OFF
#define ETHTSYN_ISDEF_PDELAYRESPONDERUSEDOFPDELAYCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_PORTIDXOFPDELAYCONFIG                                                         STD_OFF
#define ETHTSYN_ISDEF_USESTATICPDELAYOFPDELAYCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_ALLOWEDLOSTRESPONSESOFPDELAYINITIATOR                                         STD_OFF
#define ETHTSYN_ISDEF_AVERAGEWEIGHTOFPDELAYINITIATOR                                                STD_OFF
#define ETHTSYN_ISDEF_LOGMESSAGEINTERVALOFPDELAYINITIATOR                                           STD_OFF
#define ETHTSYN_ISDEF_PDELAYREQSMIDXOFPDELAYINITIATOR                                               STD_OFF
#define ETHTSYN_ISDEF_PDELAYTHRESHOLDOFPDELAYINITIATOR                                              STD_OFF
#define ETHTSYN_ISDEF_RESPRESPFOLLOWUPTIMEOUTOFPDELAYINITIATOR                                      STD_OFF
#define ETHTSYN_ISDEF_TXINTERVALMFOFPDELAYINITIATOR                                                 STD_OFF
#define ETHTSYN_ISDEF_PDELAYRESPSMIDXOFPDELAYRESPONDER                                              STD_OFF
#define ETHTSYN_ISDEF_DEBOUNCETIMEOFPHYSPORTCFG                                                     STD_OFF
#define ETHTSYN_ISDEF_CTRLIDXOFPORT                                                                 STD_OFF
#define ETHTSYN_ISDEF_FRAMEPRIOOFPORT                                                               STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTIDXOFPORT                                                           STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTUSEDOFPORT                                                          STD_OFF
#define ETHTSYN_ISDEF_NUMBEROFPORT                                                                  STD_OFF
#define ETHTSYN_ISDEF_PDELAYCONFIGIDXOFPORT                                                         STD_OFF
#define ETHTSYN_ISDEF_PDELAYCONFIGUSEDOFPORT                                                        STD_OFF
#define ETHTSYN_ISDEF_PHYSPORTCFGIDXOFPORT                                                          STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTIDXOFPORT                                                            STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTUSEDOFPORT                                                           STD_OFF
#define ETHTSYN_ISDEF_STBMTIMESRCEQUALOFPORT                                                        STD_OFF
#define ETHTSYN_ISDEF_SWITCHPORTMGMTIDXOFPORT                                                       STD_OFF
#define ETHTSYN_ISDEF_SWITCHPORTMGMTUSEDOFPORT                                                      STD_OFF
#define ETHTSYN_ISDEF_TIMEDOMAINIDXOFPORT                                                           STD_OFF
#define ETHTSYN_ISDEF_PORTIND                                                                       STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCEINFOIDXOFSLAVEPORT                                                    STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCEINFOUSEDOFSLAVEPORT                                                   STD_OFF
#define ETHTSYN_ISDEF_CRCFLAGSRXVALIDATEDOFSLAVEPORT                                                STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPALLOWEDRXDELAYOFSLAVEPORT                                             STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTIDENTITYIDXOFSLAVEPORT                                              STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTIDENTITYUSEDOFSLAVEPORT                                             STD_OFF
#define ETHTSYN_ISDEF_PORTIDXOFSLAVEPORT                                                            STD_OFF
#define ETHTSYN_ISDEF_RXCRCVALIDATEDOFSLAVEPORT                                                     STD_OFF
#define ETHTSYN_ISDEF_SLAVESWITCHIDXLIST                                                            STD_OFF
#define ETHTSYN_ISDEF_PORTIDXOFSWITCHPORTMGMT                                                       STD_OFF
#define ETHTSYN_ISDEF_SWITCHIDXOFSWITCHPORTMGMT                                                     STD_OFF
#define ETHTSYN_ISDEF_ETHIFCTRLIDXOFSWITCHSYNCFRAMECFG                                              STD_OFF
#define ETHTSYN_ISDEF_FRAMEPRIOOFSWITCHSYNCFRAMECFG                                                 STD_OFF
#define ETHTSYN_ISDEF_MGMTPORTETHIFSWITCHIDXOFSWITCHSYNCFRAMECFG                                    STD_OFF
#define ETHTSYN_ISDEF_MGMTPORTSWITCHPORTIDXOFSWITCHSYNCFRAMECFG                                     STD_OFF
#define ETHTSYN_ISDEF_PORTIDXOFSWITCHSYNCFRAMECFG                                                   STD_OFF
#define ETHTSYN_ISDEF_SWITCHTIMESYNCCFGIDXOFSWITCHSYNCFRAMECFG                                      STD_OFF
#define ETHTSYN_ISDEF_SYNCTXINTERVALOFSWITCHSYNCFRAMECFG                                            STD_OFF
#define ETHTSYN_ISDEF_APPLYRATERATIOTOSLAVESWITCHESOFSWITCHTIMESYNCCFG                              STD_OFF
#define ETHTSYN_ISDEF_ETHIFSWITCHIDXOFSWITCHTIMESYNCCFG                                             STD_OFF
#define ETHTSYN_ISDEF_MAXOUTOFSYNCCNTOFSWITCHTIMESYNCCFG                                            STD_OFF
#define ETHTSYN_ISDEF_SLAVESWITCHIDXLISTENDIDXOFSWITCHTIMESYNCCFG                                   STD_OFF
#define ETHTSYN_ISDEF_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG                                 STD_OFF
#define ETHTSYN_ISDEF_SLAVESWITCHIDXLISTUSEDOFSWITCHTIMESYNCCFG                                     STD_OFF
#define ETHTSYN_ISDEF_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG                                      STD_OFF
#define ETHTSYN_ISDEF_SWITCHSYNCFRAMECFGUSEDOFSWITCHTIMESYNCCFG                                     STD_OFF
#define ETHTSYN_ISDEF_SWTSYNCSTATECHGFCTPTROFSWITCHTIMESYNCCFG                                      STD_OFF
#define ETHTSYN_ISDEF_SWTTIMESYNCRATEREGULATORCFGIDXOFSWITCHTIMESYNCCFG                             STD_OFF
#define ETHTSYN_ISDEF_SYNCEVENTTIMEOUTOFSWITCHTIMESYNCCFG                                           STD_OFF
#define ETHTSYN_ISDEF_SYNCPRECISIONLIMITNSOFSWITCHTIMESYNCCFG                                       STD_OFF
#define ETHTSYN_ISDEF_TIMEDOMAINIDXOFSWITCHTIMESYNCCFG                                              STD_OFF
#define ETHTSYN_ISDEF_NRPARALLELRATEMEASUREMENTSOFSWTTIMESYNCRATEREGULATORCFG                       STD_OFF
#define ETHTSYN_ISDEF_NRSYNCCYCLESFOROFSCORROFSWTTIMESYNCRATEREGULATORCFG                           STD_OFF
#define ETHTSYN_ISDEF_OFSJUMPCORRTHRESHOLDNSOFSWTTIMESYNCRATEREGULATORCFG                           STD_OFF
#define ETHTSYN_ISDEF_RATEMEASUREMENTENDIDXOFSWTTIMESYNCRATEREGULATORCFG                            STD_OFF
#define ETHTSYN_ISDEF_RATEMEASUREMENTLENGTHOFSWTTIMESYNCRATEREGULATORCFG                            STD_OFF
#define ETHTSYN_ISDEF_RATEMEASUREMENTSTARTIDXOFSWTTIMESYNCRATEREGULATORCFG                          STD_OFF
#define ETHTSYN_ISDEF_RATERATIOMAXOFSWTTIMESYNCRATEREGULATORCFG                                     STD_OFF
#define ETHTSYN_ISDEF_RATERATIOMINOFSWTTIMESYNCRATEREGULATORCFG                                     STD_OFF
#define ETHTSYN_ISDEF_USEINITIALOFFSETCORRECTIONOFSWTTIMESYNCRATEREGULATORCFG                       STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPDATAIDLISTENDIDXOFTIMEDOMAIN                                          STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN                                        STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPDATAIDLISTUSEDOFTIMEDOMAIN                                            STD_OFF
#define ETHTSYN_ISDEF_IDOFTIMEDOMAIN                                                                STD_OFF
#define ETHTSYN_ISDEF_IMMEDIATETIMESYNCOFTIMEDOMAIN                                                 STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTENDIDXOFTIMEDOMAIN                                                  STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTLENGTHOFTIMEDOMAIN                                                  STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTSTARTIDXOFTIMEDOMAIN                                                STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTUSEDOFTIMEDOMAIN                                                    STD_OFF
#define ETHTSYN_ISDEF_OFFSETTIMEDOMAINENDIDXOFTIMEDOMAIN                                            STD_OFF
#define ETHTSYN_ISDEF_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN                                          STD_OFF
#define ETHTSYN_ISDEF_OFFSETTIMEDOMAINUSEDOFTIMEDOMAIN                                              STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTENDIDXOFTIMEDOMAIN                                                   STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTSTARTIDXOFTIMEDOMAIN                                                 STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTUSEDOFTIMEDOMAIN                                                     STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFTIMEDOMAIN                                            STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDMASTERCFG                                    STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDREQCFG                                     STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDRESPCFG                                    STD_OFF
#define ETHTSYN_ISDEF_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDSLAVECFG                                     STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCEINFOOFPCCONFIG                                                        STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCERECEIVESMOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCESENDSMCFGOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_ANNOUNCESENDSMOFPCCONFIG                                                      STD_OFF
#define ETHTSYN_ISDEF_CTRLOFPCCONFIG                                                                STD_OFF
#define ETHTSYN_ISDEF_CTRLSTATEOFPCCONFIG                                                           STD_OFF
#define ETHTSYN_ISDEF_DESTINATIONMACOFPCCONFIG                                                      STD_OFF
#define ETHTSYN_ISDEF_FOLLOWUPDATAIDLISTOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTIDENTITYOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_MASTERPORTOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_OFFSETTIMEDOMAINOFPCCONFIG                                                    STD_OFF
#define ETHTSYN_ISDEF_OFSCORRDURATIONINSYNCCYCLESOFPCCONFIG                                         STD_OFF
#define ETHTSYN_ISDEF_PDELAYCONFIGOFPCCONFIG                                                        STD_OFF
#define ETHTSYN_ISDEF_PDELAYINFOOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_PDELAYINITIATOROFPCCONFIG                                                     STD_OFF
#define ETHTSYN_ISDEF_PDELAYREQSMOFPCCONFIG                                                         STD_OFF
#define ETHTSYN_ISDEF_PDELAYRESPSMOFPCCONFIG                                                        STD_OFF
#define ETHTSYN_ISDEF_PDELAYRESPONDEROFPCCONFIG                                                     STD_OFF
#define ETHTSYN_ISDEF_PHYSPORTCFGOFPCCONFIG                                                         STD_OFF
#define ETHTSYN_ISDEF_PHYSPORTOFPCCONFIG                                                            STD_OFF
#define ETHTSYN_ISDEF_PORTINDOFPCCONFIG                                                             STD_OFF
#define ETHTSYN_ISDEF_PORTOFPCCONFIG                                                                STD_OFF
#define ETHTSYN_ISDEF_PORTSYNCSENDSMOFPCCONFIG                                                      STD_OFF
#define ETHTSYN_ISDEF_RATEMEASUREMENTOFPCCONFIG                                                     STD_OFF
#define ETHTSYN_ISDEF_SIZEOFANNOUNCEINFOOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SIZEOFANNOUNCESENDSMCFGOFPCCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_SIZEOFCTRLOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_SIZEOFDESTINATIONMACOFPCCONFIG                                                STD_OFF
#define ETHTSYN_ISDEF_SIZEOFFOLLOWUPDATAIDLISTOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFMASTERPORTIDENTITYOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFMASTERPORTOFPCCONFIG                                                    STD_OFF
#define ETHTSYN_ISDEF_SIZEOFOFFSETTIMEDOMAINOFPCCONFIG                                              STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPDELAYCONFIGOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPDELAYINITIATOROFPCCONFIG                                               STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPDELAYREQSMOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPDELAYRESPSMOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPDELAYRESPONDEROFPCCONFIG                                               STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPHYSPORTCFGOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPORTINDOFPCCONFIG                                                       STD_OFF
#define ETHTSYN_ISDEF_SIZEOFPORTOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_SIZEOFRATEMEASUREMENTOFPCCONFIG                                               STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSLAVEPORTOFPCCONFIG                                                     STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSLAVESWITCHIDXLISTOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSWITCHPORTMGMTOFPCCONFIG                                                STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSWITCHSYNCFRAMECFGOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSWITCHTIMESYNCCFGOFPCCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSWTMGMTRCVDMSGBUFOFPCCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_SIZEOFSWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                   STD_OFF
#define ETHTSYN_ISDEF_SIZEOFTIMEDOMAINOFPCCONFIG                                                    STD_OFF
#define ETHTSYN_ISDEF_SIZEOFTIMEVALIDMASTERCFGOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFTIMEVALIDPDREQCFGOFPCCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_SIZEOFTIMEVALIDPDRESPCFGOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SIZEOFTIMEVALIDSLAVECFGOFPCCONFIG                                             STD_OFF
#define ETHTSYN_ISDEF_SLAVEPORTOFPCCONFIG                                                           STD_OFF
#define ETHTSYN_ISDEF_SLAVESWITCHIDXLISTOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SWITCHPORTMGMTOFPCCONFIG                                                      STD_OFF
#define ETHTSYN_ISDEF_SWITCHSYNCFRAMECFGOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SWITCHSYNCFRAMEINFOOFPCCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_SWITCHSYNCFRAMETXFRAMEINFOOFPCCONFIG                                          STD_OFF
#define ETHTSYN_ISDEF_SWITCHTIMESYNCCFGOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_SWITCHTIMESYNCINFOOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_SWTMGMTRCVDMSGBUFOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_SWTMGMTRXBUFQUEUECURRPROCIDXOFPCCONFIG                                        STD_OFF
#define ETHTSYN_ISDEF_SWTMGMTRXBUFQUEUEFREEIDXOFPCCONFIG                                            STD_OFF
#define ETHTSYN_ISDEF_SWTMGMTTXMGMTOBJQUEUECURRPROCIDXOFPCCONFIG                                    STD_OFF
#define ETHTSYN_ISDEF_SWTMGMTTXMGMTOBJQUEUEFREEIDXOFPCCONFIG                                        STD_OFF
#define ETHTSYN_ISDEF_SWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                         STD_OFF
#define ETHTSYN_ISDEF_SYNCRECEIVESMOFPCCONFIG                                                       STD_OFF
#define ETHTSYN_ISDEF_SYNCSENDSMOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_SYSTEMSTATEOFPCCONFIG                                                         STD_OFF
#define ETHTSYN_ISDEF_TIMEBASEUPDATECOUNTEROFPCCONFIG                                               STD_OFF
#define ETHTSYN_ISDEF_TIMEDOMAINOFPCCONFIG                                                          STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDMASTERCFGOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDMASTERDATAOFPCCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDPDREQCFGOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDPDREQDATAOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDPDRESPCFGOFPCCONFIG                                                  STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDPDRESPDATAOFPCCONFIG                                                 STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDSLAVECFGOFPCCONFIG                                                   STD_OFF
#define ETHTSYN_ISDEF_TIMEVALIDSLAVEDATAOFPCCONFIG                                                  STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCEqualsAlwaysToDefines  EthTSyn Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define ETHTSYN_EQ2_ANNOUNCEALLOWEDRXDELAYOFANNOUNCEINFO                                            
#define ETHTSYN_EQ2_MAXESTEPSREMOVEDOFANNOUNCEINFO                                                  
#define ETHTSYN_EQ2_ANNOUNCETXCYCLEOFANNOUNCESENDSMCFG                                              
#define ETHTSYN_EQ2_ETHIFCTRLIDXOFCTRL                                                              
#define ETHTSYN_EQ2_PORTINDENDIDXOFCTRL                                                             
#define ETHTSYN_EQ2_PORTINDSTARTIDXOFCTRL                                                           
#define ETHTSYN_EQ2_DESTINATIONMAC                                                                  
#define ETHTSYN_EQ2_FOLLOWUPDATAIDLIST                                                              
#define ETHTSYN_EQ2_ANNOUNCESENDSMCFGIDXOFMASTERPORT                                                
#define ETHTSYN_EQ2_ANNOUNCESENDSMCFGUSEDOFMASTERPORT                                               
#define ETHTSYN_EQ2_CRCTIMEFLAGSOFMASTERPORT                                                        
#define ETHTSYN_EQ2_CYCLICMSGRESUMECNTOFMASTERPORT                                                  
#define ETHTSYN_EQ2_FOLLOWUPMSGLENGTHOFMASTERPORT                                                   
#define ETHTSYN_EQ2_FOLLOWUPSENTCBKPTROFMASTERPORT                                                  
#define ETHTSYN_EQ2_IMMEDIATETIMESYNCOFMASTERPORT                                                   
#define ETHTSYN_EQ2_OFSSUBTLVOFMASTERPORT                                                           
#define ETHTSYN_EQ2_PORTIDXOFMASTERPORT                                                             
#define ETHTSYN_EQ2_STATUSSUBTLVOFMASTERPORT                                                        
#define ETHTSYN_EQ2_SYNCLOGMSGINTERVALOFMASTERPORT                                                  
#define ETHTSYN_EQ2_SYNCSENDINTERVALOFMASTERPORT                                                    
#define ETHTSYN_EQ2_SYNCSENTCBKPTROFMASTERPORT                                                      
#define ETHTSYN_EQ2_TIMESUBTLVOFMASTERPORT                                                          
#define ETHTSYN_EQ2_TXCRCSECUREDOFMASTERPORT                                                        
#define ETHTSYN_EQ2_USERDATASUBTLVOFMASTERPORT                                                      
#define ETHTSYN_EQ2_CLOCKIDENTITYOFMASTERPORTIDENTITY                                               
#define ETHTSYN_EQ2_IDOFOFFSETTIMEDOMAIN                                                            
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFOFFSETTIMEDOMAIN                                        
#define ETHTSYN_EQ2_ALWAYSASCAPABLEOFPDELAYCONFIG                                                   
#define ETHTSYN_EQ2_INITIALPDELAYNSOFPDELAYCONFIG                                                   
#define ETHTSYN_EQ2_PDELAYINITIATORIDXOFPDELAYCONFIG                                                
#define ETHTSYN_EQ2_PDELAYINITIATORUSEDOFPDELAYCONFIG                                               
#define ETHTSYN_EQ2_PDELAYRESPONDERIDXOFPDELAYCONFIG                                                
#define ETHTSYN_EQ2_PDELAYRESPONDERUSEDOFPDELAYCONFIG                                               
#define ETHTSYN_EQ2_PORTIDXOFPDELAYCONFIG                                                           
#define ETHTSYN_EQ2_USESTATICPDELAYOFPDELAYCONFIG                                                   
#define ETHTSYN_EQ2_ALLOWEDLOSTRESPONSESOFPDELAYINITIATOR                                           
#define ETHTSYN_EQ2_AVERAGEWEIGHTOFPDELAYINITIATOR                                                  
#define ETHTSYN_EQ2_LOGMESSAGEINTERVALOFPDELAYINITIATOR                                             
#define ETHTSYN_EQ2_PDELAYREQSMIDXOFPDELAYINITIATOR                                                 
#define ETHTSYN_EQ2_PDELAYTHRESHOLDOFPDELAYINITIATOR                                                
#define ETHTSYN_EQ2_RESPRESPFOLLOWUPTIMEOUTOFPDELAYINITIATOR                                        
#define ETHTSYN_EQ2_TXINTERVALMFOFPDELAYINITIATOR                                                   
#define ETHTSYN_EQ2_PDELAYRESPSMIDXOFPDELAYRESPONDER                                                
#define ETHTSYN_EQ2_DEBOUNCETIMEOFPHYSPORTCFG                                                       
#define ETHTSYN_EQ2_CTRLIDXOFPORT                                                                   
#define ETHTSYN_EQ2_FRAMEPRIOOFPORT                                                                 
#define ETHTSYN_EQ2_MASTERPORTIDXOFPORT                                                             
#define ETHTSYN_EQ2_MASTERPORTUSEDOFPORT                                                            
#define ETHTSYN_EQ2_NUMBEROFPORT                                                                    
#define ETHTSYN_EQ2_PDELAYCONFIGIDXOFPORT                                                           
#define ETHTSYN_EQ2_PDELAYCONFIGUSEDOFPORT                                                          
#define ETHTSYN_EQ2_PHYSPORTCFGIDXOFPORT                                                            
#define ETHTSYN_EQ2_SLAVEPORTIDXOFPORT                                                              
#define ETHTSYN_EQ2_SLAVEPORTUSEDOFPORT                                                             
#define ETHTSYN_EQ2_STBMTIMESRCEQUALOFPORT                                                          
#define ETHTSYN_EQ2_SWITCHPORTMGMTIDXOFPORT                                                         
#define ETHTSYN_EQ2_SWITCHPORTMGMTUSEDOFPORT                                                        
#define ETHTSYN_EQ2_TIMEDOMAINIDXOFPORT                                                             
#define ETHTSYN_EQ2_PORTIND                                                                         
#define ETHTSYN_EQ2_ANNOUNCEINFOIDXOFSLAVEPORT                                                      
#define ETHTSYN_EQ2_ANNOUNCEINFOUSEDOFSLAVEPORT                                                     
#define ETHTSYN_EQ2_CRCFLAGSRXVALIDATEDOFSLAVEPORT                                                  
#define ETHTSYN_EQ2_FOLLOWUPALLOWEDRXDELAYOFSLAVEPORT                                               
#define ETHTSYN_EQ2_MASTERPORTIDENTITYIDXOFSLAVEPORT                                                
#define ETHTSYN_EQ2_MASTERPORTIDENTITYUSEDOFSLAVEPORT                                               
#define ETHTSYN_EQ2_PORTIDXOFSLAVEPORT                                                              
#define ETHTSYN_EQ2_RXCRCVALIDATEDOFSLAVEPORT                                                       
#define ETHTSYN_EQ2_SLAVESWITCHIDXLIST                                                              
#define ETHTSYN_EQ2_PORTIDXOFSWITCHPORTMGMT                                                         
#define ETHTSYN_EQ2_SWITCHIDXOFSWITCHPORTMGMT                                                       
#define ETHTSYN_EQ2_ETHIFCTRLIDXOFSWITCHSYNCFRAMECFG                                                
#define ETHTSYN_EQ2_FRAMEPRIOOFSWITCHSYNCFRAMECFG                                                   
#define ETHTSYN_EQ2_MGMTPORTETHIFSWITCHIDXOFSWITCHSYNCFRAMECFG                                      
#define ETHTSYN_EQ2_MGMTPORTSWITCHPORTIDXOFSWITCHSYNCFRAMECFG                                       
#define ETHTSYN_EQ2_PORTIDXOFSWITCHSYNCFRAMECFG                                                     
#define ETHTSYN_EQ2_SWITCHTIMESYNCCFGIDXOFSWITCHSYNCFRAMECFG                                        
#define ETHTSYN_EQ2_SYNCTXINTERVALOFSWITCHSYNCFRAMECFG                                              
#define ETHTSYN_EQ2_APPLYRATERATIOTOSLAVESWITCHESOFSWITCHTIMESYNCCFG                                
#define ETHTSYN_EQ2_ETHIFSWITCHIDXOFSWITCHTIMESYNCCFG                                               
#define ETHTSYN_EQ2_MAXOUTOFSYNCCNTOFSWITCHTIMESYNCCFG                                              
#define ETHTSYN_EQ2_SLAVESWITCHIDXLISTENDIDXOFSWITCHTIMESYNCCFG                                     
#define ETHTSYN_EQ2_SLAVESWITCHIDXLISTSTARTIDXOFSWITCHTIMESYNCCFG                                   
#define ETHTSYN_EQ2_SLAVESWITCHIDXLISTUSEDOFSWITCHTIMESYNCCFG                                       
#define ETHTSYN_EQ2_SWITCHSYNCFRAMECFGIDXOFSWITCHTIMESYNCCFG                                        
#define ETHTSYN_EQ2_SWITCHSYNCFRAMECFGUSEDOFSWITCHTIMESYNCCFG                                       
#define ETHTSYN_EQ2_SWTSYNCSTATECHGFCTPTROFSWITCHTIMESYNCCFG                                        
#define ETHTSYN_EQ2_SWTTIMESYNCRATEREGULATORCFGIDXOFSWITCHTIMESYNCCFG                               
#define ETHTSYN_EQ2_SYNCEVENTTIMEOUTOFSWITCHTIMESYNCCFG                                             
#define ETHTSYN_EQ2_SYNCPRECISIONLIMITNSOFSWITCHTIMESYNCCFG                                         
#define ETHTSYN_EQ2_TIMEDOMAINIDXOFSWITCHTIMESYNCCFG                                                
#define ETHTSYN_EQ2_NRPARALLELRATEMEASUREMENTSOFSWTTIMESYNCRATEREGULATORCFG                         
#define ETHTSYN_EQ2_NRSYNCCYCLESFOROFSCORROFSWTTIMESYNCRATEREGULATORCFG                             
#define ETHTSYN_EQ2_OFSJUMPCORRTHRESHOLDNSOFSWTTIMESYNCRATEREGULATORCFG                             
#define ETHTSYN_EQ2_RATEMEASUREMENTENDIDXOFSWTTIMESYNCRATEREGULATORCFG                              
#define ETHTSYN_EQ2_RATEMEASUREMENTLENGTHOFSWTTIMESYNCRATEREGULATORCFG                              
#define ETHTSYN_EQ2_RATEMEASUREMENTSTARTIDXOFSWTTIMESYNCRATEREGULATORCFG                            
#define ETHTSYN_EQ2_RATERATIOMAXOFSWTTIMESYNCRATEREGULATORCFG                                       
#define ETHTSYN_EQ2_RATERATIOMINOFSWTTIMESYNCRATEREGULATORCFG                                       
#define ETHTSYN_EQ2_USEINITIALOFFSETCORRECTIONOFSWTTIMESYNCRATEREGULATORCFG                         
#define ETHTSYN_EQ2_FOLLOWUPDATAIDLISTENDIDXOFTIMEDOMAIN                                            
#define ETHTSYN_EQ2_FOLLOWUPDATAIDLISTSTARTIDXOFTIMEDOMAIN                                          
#define ETHTSYN_EQ2_FOLLOWUPDATAIDLISTUSEDOFTIMEDOMAIN                                              
#define ETHTSYN_EQ2_IDOFTIMEDOMAIN                                                                  
#define ETHTSYN_EQ2_IMMEDIATETIMESYNCOFTIMEDOMAIN                                                   
#define ETHTSYN_EQ2_MASTERPORTENDIDXOFTIMEDOMAIN                                                    
#define ETHTSYN_EQ2_MASTERPORTLENGTHOFTIMEDOMAIN                                                    
#define ETHTSYN_EQ2_MASTERPORTSTARTIDXOFTIMEDOMAIN                                                  
#define ETHTSYN_EQ2_MASTERPORTUSEDOFTIMEDOMAIN                                                      
#define ETHTSYN_EQ2_OFFSETTIMEDOMAINENDIDXOFTIMEDOMAIN                                              
#define ETHTSYN_EQ2_OFFSETTIMEDOMAINSTARTIDXOFTIMEDOMAIN                                            
#define ETHTSYN_EQ2_OFFSETTIMEDOMAINUSEDOFTIMEDOMAIN                                                
#define ETHTSYN_EQ2_SLAVEPORTENDIDXOFTIMEDOMAIN                                                     
#define ETHTSYN_EQ2_SLAVEPORTSTARTIDXOFTIMEDOMAIN                                                   
#define ETHTSYN_EQ2_SLAVEPORTUSEDOFTIMEDOMAIN                                                       
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFTIMEDOMAIN                                              
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDMASTERCFG                                      
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDREQCFG                                       
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDPDRESPCFG                                      
#define ETHTSYN_EQ2_SYNCHRONIZEDTIMEBASEIDOFTIMEVALIDSLAVECFG                                       
#define ETHTSYN_EQ2_ANNOUNCEINFOOFPCCONFIG                                                          
#define ETHTSYN_EQ2_ANNOUNCERECEIVESMOFPCCONFIG                                                     
#define ETHTSYN_EQ2_ANNOUNCESENDSMCFGOFPCCONFIG                                                     
#define ETHTSYN_EQ2_ANNOUNCESENDSMOFPCCONFIG                                                        
#define ETHTSYN_EQ2_CTRLOFPCCONFIG                                                                  
#define ETHTSYN_EQ2_CTRLSTATEOFPCCONFIG                                                             
#define ETHTSYN_EQ2_DESTINATIONMACOFPCCONFIG                                                        
#define ETHTSYN_EQ2_FOLLOWUPDATAIDLISTOFPCCONFIG                                                    
#define ETHTSYN_EQ2_MASTERPORTIDENTITYOFPCCONFIG                                                    
#define ETHTSYN_EQ2_MASTERPORTOFPCCONFIG                                                            
#define ETHTSYN_EQ2_OFFSETTIMEDOMAINOFPCCONFIG                                                      
#define ETHTSYN_EQ2_OFSCORRDURATIONINSYNCCYCLESOFPCCONFIG                                           
#define ETHTSYN_EQ2_PDELAYCONFIGOFPCCONFIG                                                          
#define ETHTSYN_EQ2_PDELAYINFOOFPCCONFIG                                                            
#define ETHTSYN_EQ2_PDELAYINITIATOROFPCCONFIG                                                       
#define ETHTSYN_EQ2_PDELAYREQSMOFPCCONFIG                                                           
#define ETHTSYN_EQ2_PDELAYRESPSMOFPCCONFIG                                                          
#define ETHTSYN_EQ2_PDELAYRESPONDEROFPCCONFIG                                                       
#define ETHTSYN_EQ2_PHYSPORTCFGOFPCCONFIG                                                           
#define ETHTSYN_EQ2_PHYSPORTOFPCCONFIG                                                              
#define ETHTSYN_EQ2_PORTINDOFPCCONFIG                                                               
#define ETHTSYN_EQ2_PORTOFPCCONFIG                                                                  
#define ETHTSYN_EQ2_PORTSYNCSENDSMOFPCCONFIG                                                        
#define ETHTSYN_EQ2_RATEMEASUREMENTOFPCCONFIG                                                       
#define ETHTSYN_EQ2_SIZEOFANNOUNCEINFOOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SIZEOFANNOUNCESENDSMCFGOFPCCONFIG                                               
#define ETHTSYN_EQ2_SIZEOFCTRLOFPCCONFIG                                                            
#define ETHTSYN_EQ2_SIZEOFDESTINATIONMACOFPCCONFIG                                                  
#define ETHTSYN_EQ2_SIZEOFFOLLOWUPDATAIDLISTOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFMASTERPORTIDENTITYOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFMASTERPORTOFPCCONFIG                                                      
#define ETHTSYN_EQ2_SIZEOFOFFSETTIMEDOMAINOFPCCONFIG                                                
#define ETHTSYN_EQ2_SIZEOFPDELAYCONFIGOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SIZEOFPDELAYINITIATOROFPCCONFIG                                                 
#define ETHTSYN_EQ2_SIZEOFPDELAYREQSMOFPCCONFIG                                                     
#define ETHTSYN_EQ2_SIZEOFPDELAYRESPSMOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SIZEOFPDELAYRESPONDEROFPCCONFIG                                                 
#define ETHTSYN_EQ2_SIZEOFPHYSPORTCFGOFPCCONFIG                                                     
#define ETHTSYN_EQ2_SIZEOFPORTINDOFPCCONFIG                                                         
#define ETHTSYN_EQ2_SIZEOFPORTOFPCCONFIG                                                            
#define ETHTSYN_EQ2_SIZEOFRATEMEASUREMENTOFPCCONFIG                                                 
#define ETHTSYN_EQ2_SIZEOFSLAVEPORTOFPCCONFIG                                                       
#define ETHTSYN_EQ2_SIZEOFSLAVESWITCHIDXLISTOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFSWITCHPORTMGMTOFPCCONFIG                                                  
#define ETHTSYN_EQ2_SIZEOFSWITCHSYNCFRAMECFGOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFSWITCHTIMESYNCCFGOFPCCONFIG                                               
#define ETHTSYN_EQ2_SIZEOFSWTMGMTRCVDMSGBUFOFPCCONFIG                                               
#define ETHTSYN_EQ2_SIZEOFSWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                     
#define ETHTSYN_EQ2_SIZEOFTIMEDOMAINOFPCCONFIG                                                      
#define ETHTSYN_EQ2_SIZEOFTIMEVALIDMASTERCFGOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFTIMEVALIDPDREQCFGOFPCCONFIG                                               
#define ETHTSYN_EQ2_SIZEOFTIMEVALIDPDRESPCFGOFPCCONFIG                                              
#define ETHTSYN_EQ2_SIZEOFTIMEVALIDSLAVECFGOFPCCONFIG                                               
#define ETHTSYN_EQ2_SLAVEPORTOFPCCONFIG                                                             
#define ETHTSYN_EQ2_SLAVESWITCHIDXLISTOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SWITCHPORTMGMTOFPCCONFIG                                                        
#define ETHTSYN_EQ2_SWITCHSYNCFRAMECFGOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SWITCHSYNCFRAMEINFOOFPCCONFIG                                                   
#define ETHTSYN_EQ2_SWITCHSYNCFRAMETXFRAMEINFOOFPCCONFIG                                            
#define ETHTSYN_EQ2_SWITCHTIMESYNCCFGOFPCCONFIG                                                     
#define ETHTSYN_EQ2_SWITCHTIMESYNCINFOOFPCCONFIG                                                    
#define ETHTSYN_EQ2_SWTMGMTRCVDMSGBUFOFPCCONFIG                                                     
#define ETHTSYN_EQ2_SWTMGMTRXBUFQUEUECURRPROCIDXOFPCCONFIG                                          
#define ETHTSYN_EQ2_SWTMGMTRXBUFQUEUEFREEIDXOFPCCONFIG                                              
#define ETHTSYN_EQ2_SWTMGMTTXMGMTOBJQUEUECURRPROCIDXOFPCCONFIG                                      
#define ETHTSYN_EQ2_SWTMGMTTXMGMTOBJQUEUEFREEIDXOFPCCONFIG                                          
#define ETHTSYN_EQ2_SWTTIMESYNCRATEREGULATORCFGOFPCCONFIG                                           
#define ETHTSYN_EQ2_SYNCRECEIVESMOFPCCONFIG                                                         
#define ETHTSYN_EQ2_SYNCSENDSMOFPCCONFIG                                                            
#define ETHTSYN_EQ2_SYSTEMSTATEOFPCCONFIG                                                           
#define ETHTSYN_EQ2_TIMEBASEUPDATECOUNTEROFPCCONFIG                                                 
#define ETHTSYN_EQ2_TIMEDOMAINOFPCCONFIG                                                            
#define ETHTSYN_EQ2_TIMEVALIDMASTERCFGOFPCCONFIG                                                    
#define ETHTSYN_EQ2_TIMEVALIDMASTERDATAOFPCCONFIG                                                   
#define ETHTSYN_EQ2_TIMEVALIDPDREQCFGOFPCCONFIG                                                     
#define ETHTSYN_EQ2_TIMEVALIDPDREQDATAOFPCCONFIG                                                    
#define ETHTSYN_EQ2_TIMEVALIDPDRESPCFGOFPCCONFIG                                                    
#define ETHTSYN_EQ2_TIMEVALIDPDRESPDATAOFPCCONFIG                                                   
#define ETHTSYN_EQ2_TIMEVALIDSLAVECFGOFPCCONFIG                                                     
#define ETHTSYN_EQ2_TIMEVALIDSLAVEDATAOFPCCONFIG                                                    
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCSymbolicInitializationPointers  EthTSyn Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define EthTSyn_Config_Ptr                                                                          &(EthTSyn_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'EthTSyn' */
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCInitializationSymbols  EthTSyn Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define EthTSyn_Config                                                                              EthTSyn_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'EthTSyn */
/** 
  \}
*/ 

/** 
  \defgroup  EthTSynPCGeneral  EthTSyn General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define ETHTSYN_CHECK_INIT_POINTER                                                                  STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define ETHTSYN_FINAL_MAGIC_NUMBER                                                                  0xA41Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of EthTSyn */
#define ETHTSYN_INDIVIDUAL_POSTBUILD                                                                STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'EthTSyn' is not configured to be postbuild capable. */
#define ETHTSYN_INIT_DATA                                                                           ETHTSYN_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define ETHTSYN_INIT_DATA_HASH_CODE                                                                 66437530  /**< the precompile constant to validate the initialization structure at initialization time of EthTSyn with a hashcode. The seed value is '0xA41Eu' */
#define ETHTSYN_USE_ECUM_BSW_ERROR_HOOK                                                             STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define ETHTSYN_USE_INIT_POINTER                                                                    STD_ON  /**< STD_ON if the init pointer EthTSyn shall be used. */
/** 
  \}
*/ 




#endif /* ETHTSYN_CFG_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Cfg.h
 *********************************************************************************************************************/

