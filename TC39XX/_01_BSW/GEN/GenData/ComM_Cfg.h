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
 *            Module: ComM
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: ComM_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined(COMM_CFG_H)
#define COMM_CFG_H

/* -----------------------------------------------------------------------------
    &&&~ INCLUDES
 ----------------------------------------------------------------------------- */

#include "ComM_Types.h"

/* -----------------------------------------------------------------------------
    &&&~ CONFIGURATION DEFINES
 ----------------------------------------------------------------------------- */

#ifndef COMM_USE_DUMMY_STATEMENT
#define COMM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_DUMMY_STATEMENT
#define COMM_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_DUMMY_STATEMENT_CONST
#define COMM_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define COMM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef COMM_ATOMIC_VARIABLE_ACCESS
#define COMM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef COMM_PROCESSOR_TC397X_STEPB
#define COMM_PROCESSOR_TC397X_STEPB
#endif
#ifndef COMM_COMP_TASKING
#define COMM_COMP_TASKING
#endif
#ifndef COMM_GEN_GENERATOR_MSR
#define COMM_GEN_GENERATOR_MSR
#endif
#ifndef COMM_CPUTYPE_BITORDER_LSB2MSB
#define COMM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef COMM_CONFIGURATION_VARIANT_PRECOMPILE
#define COMM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef COMM_CONFIGURATION_VARIANT_LINKTIME
#define COMM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define COMM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef COMM_CONFIGURATION_VARIANT
#define COMM_CONFIGURATION_VARIANT COMM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef COMM_POSTBUILD_VARIANT_SUPPORT
#define COMM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#ifndef COMM_DEV_ERROR_DETECT
#define COMM_DEV_ERROR_DETECT STD_ON
#endif
#ifndef COMM_DEV_ERROR_REPORT
#define COMM_DEV_ERROR_REPORT STD_ON
#endif

#define COMM_INIT_POINTER_ENABLED                       STD_OFF
#define COMM_VERSION_INFO_API                           STD_OFF

#define COMM_MODE_LIMITATION                            STD_OFF
#define COMM_WAKEUP_INHIBITION                          STD_OFF

#define COMM_PNC_SUPPORT                                STD_ON
#define COMM_PNC_ACTIVE_COORD                           STD_OFF
#define COMM_PNC_PS_TIMER                               200u
#define COMM_ACTIVE_PNC                                 1u
#define COMM_PNC_EXTENDED_FUNCTIONALITY_ENABLED         STD_OFF
#define COMM_PNC_TO_CHANNEL_ROUTING_LIMITATION_ENABLED  STD_OFF
#define COMM_PNC_PASSIVE_GW_SUPPORT                     STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_ACTIVE             STD_OFF
#define COMM_PNC_EXISTS_GATEWAY_TYPE_NONE               STD_OFF
#define COMM_PNC_SIGNAL_LENGTH                          7u
#define COMM_PNC_MAX_NUMBER_OF_EIRA_RX                  1u
#define COMM_PNC_CHECK_ENABLED_AT_RUNTIME               STD_OFF
#define COMM_PNC_0_VECTOR_AVOIDANCE                     STD_OFF

#define COMM_NM_GW_EXT_ENABLED                          STD_OFF
#define COMM_KEEP_AWAKE_CHANNELS_SUPPORT                STD_ON
#define COMM_BUS_TYPE_INTERNAL_PRESENT                  STD_OFF
#define COMM_BUS_TYPE_FR_PRESENT                        STD_OFF
#define COMM_BUS_TYPE_LIN_PRESENT                       STD_OFF
#define COMM_EXISTS_ONLY_NONE_NMTYPEOFCHANNEL           STD_OFF

#define COMM_FULL_COMM_REQUEST_NOTIF                    STD_OFF
#define COMM_MAX_NUMBER_OF_USERS                        2u
#define COMM_DCM_INDICATION                             STD_OFF
#define COMM_USERMODENOTIFUNC_PNC_USER_ONLY             STD_ON

#define COMM_SYNCHRONOUS_WAKE_UP                        STD_ON
#define COMM_EXTENDED_RAM_CHECK                         STD_OFF

#define COMM_ACTIVE_CHANNEL                             1u
#define COMM_NVM_SUPPORT                                STD_OFF



/* -----------------------------------------------------------------------------
    &&&~ USER HANDLES
 ----------------------------------------------------------------------------- */

#define ComMConf_ComMUser_ComMUser_Channel_Vlan10 0u 
#define ComMConf_ComMUser_ComMUser_Pnc00          1u 


/* -----------------------------------------------------------------------------
    &&&~ CHANNEL HANDLES
 ----------------------------------------------------------------------------- */
 
#define ComMConf_ComMChannel_ComMChannel_Vlan10 0u 


/* -----------------------------------------------------------------------------
    &&&~ PNC HANDLES
 ----------------------------------------------------------------------------- */

#define ComMConf_ComMPnc_ComMPnc_00 0u 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCDataSwitches  ComM Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define COMM_ACTIVEPNCCOMMODE                                         STD_ON
#define COMM_BUSPNCCOMMODEREQ                                         STD_ON
#define COMM_BUSSLEEPMODEINDICATED                                    STD_OFF  /**< Deactivateable: 'ComM_BusSleepModeIndicated' Reason: 'NM variant LINSLAVE is not present' */
#define COMM_CHANNEL                                                  STD_ON
#define COMM_BUSTYPEOFCHANNEL                                         STD_ON
#define COMM_ENABLEDOFCHANNEL                                         STD_OFF  /**< Deactivateable: 'ComM_Channel.Enabled' Reason: 'the value of ComM_EnabledOfChannel is always 'true' due to this, the array is deactivated.' */
#define COMM_GWTYPEOFCHANNEL                                          STD_ON
#define COMM_INHIBITIONINITVALUEOFCHANNEL                             STD_ON
#define COMM_J1939SUPPORTOFCHANNEL                                    STD_OFF  /**< Deactivateable: 'ComM_Channel.J1939Support' Reason: 'the value of ComM_J1939SupportOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_MANAGINGCHANNELIDOFCHANNEL                               STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingChannelId' Reason: 'the value of ComM_ManagingChannelIdOfChannel is always 'COMM_NO_MANAGINGCHANNELIDOFCHANNEL' due to this, the array is deactivated.' */
#define COMM_MANAGINGCHANNELOFCHANNEL                                 STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingChannel' Reason: 'the value of ComM_ManagingChannelOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_MANAGINGUSEROFCHANNEL                                    STD_OFF  /**< Deactivateable: 'ComM_Channel.ManagingUser' Reason: 'the value of ComM_ManagingUserOfChannel is always 'COMM_NO_MANAGINGUSEROFCHANNEL' due to this, the array is deactivated.' */
#define COMM_MINFULLCOMTIMEOFCHANNEL                                  STD_OFF  /**< Deactivateable: 'ComM_Channel.MinFullComTime' Reason: 'the value of ComM_MinFullComTimeOfChannel is always '0' due to this, the array is deactivated.' */
#define COMM_NMLIGHTDURATIONOFCHANNEL                                 STD_OFF  /**< Deactivateable: 'ComM_Channel.NmLightDuration' Reason: 'the value of ComM_NmLightDurationOfChannel is always '0' due to this, the array is deactivated.' */
#define COMM_NMLIGHTSILENTDURATIONOFCHANNEL                           STD_OFF  /**< Deactivateable: 'ComM_Channel.NmLightSilentDuration' Reason: 'the value of ComM_NmLightSilentDurationOfChannel is always '0' due to this, the array is deactivated.' */
#define COMM_NMSUPPORTOFCHANNEL                                       STD_ON
#define COMM_NMTYPEOFCHANNEL                                          STD_ON
#define COMM_PASSIVEORLINSLAVEOFCHANNEL                               STD_OFF  /**< Deactivateable: 'ComM_Channel.PassiveOrLinSlave' Reason: 'the value of ComM_PassiveOrLinSlaveOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_PNCNMREQUESTOFCHANNEL                                    STD_ON
#define COMM_RESETAFTERFORCINGNOCOMMOFCHANNEL                         STD_OFF  /**< Deactivateable: 'ComM_Channel.ResetAfterForcingNoComm' Reason: 'the value of ComM_ResetAfterForcingNoCommOfChannel is always 'false' due to this, the array is deactivated.' */
#define COMM_SILENTSUPPORTOFCHANNEL                                   STD_ON
#define COMM_WAKEUPSTATEOFCHANNEL                                     STD_ON
#define COMM_CHANNELPB                                                STD_ON
#define COMM_PNCPBINDENDIDXOFCHANNELPB                                STD_ON
#define COMM_PNCPBINDSTARTIDXOFCHANNELPB                              STD_ON
#define COMM_PNCPBINDUSEDOFCHANNELPB                                  STD_ON
#define COMM_USERREQFULLCOMENDIDXOFCHANNELPB                          STD_ON
#define COMM_USERREQFULLCOMSTARTIDXOFCHANNELPB                        STD_ON
#define COMM_USERREQFULLCOMUSEDOFCHANNELPB                            STD_ON
#define COMM_DCMREQUESTACTIVE                                         STD_OFF  /**< Deactivateable: 'ComM_DcmRequestActive' Reason: 'Keep Awake Channel support or Dcm support is disabled' */
#define COMM_FINALMAGICNUMBER                                         STD_OFF  /**< Deactivateable: 'ComM_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_FULLCOMREQUESTERS                                        STD_OFF  /**< Deactivateable: 'ComM_FullComRequesters' Reason: 'Deactivated because no channel had ComMFullCommRequestNoficiation enabled' */
#define COMM_INITDATAHASHCODE                                         STD_OFF  /**< Deactivateable: 'ComM_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_LASTSTATECHANGE                                          STD_OFF  /**< Deactivateable: 'ComM_LastStateChange' Reason: 'No user mode Notification configured.' */
#define COMM_MINFULLCOMMODETIMER                                      STD_OFF  /**< Deactivateable: 'ComM_MinFullComModeTimer' Reason: 'Min Full Com Timer is disabled' */
#define COMM_NMLIGHTTIMER                                             STD_OFF  /**< Deactivateable: 'ComM_NmLightTimer' Reason: 'Nm Light and Nm Light Silent Timers are disabled' */
#define COMM_PNC                                                      STD_ON
#define COMM_CLEARMASKOFPNC                                           STD_ON
#define COMM_COORDINATEDOFPNC                                         STD_OFF  /**< Deactivateable: 'ComM_Pnc.Coordinated' Reason: 'the value of ComM_CoordinatedOfPnc is always 'false' due to this, the array is deactivated.' */
#define COMM_PNCIDOFPNC                                               STD_ON
#define COMM_SETMASKOFPNC                                             STD_ON
#define COMM_SYSTEMUSEROFPNC                                          STD_OFF  /**< Deactivateable: 'ComM_Pnc.SystemUser' Reason: 'the value of ComM_SystemUserOfPnc is always '65535' due to this, the array is deactivated.' */
#define COMM_WAKEUPENABLEDOFPNC                                       STD_OFF  /**< Deactivateable: 'ComM_Pnc.WakeupEnabled' Reason: 'the value of ComM_WakeupEnabledOfPnc is always 'false' due to this, the array is deactivated.' */
#define COMM_PNCCHANNELMAPPING                                        STD_ON
#define COMM_PNCPSLEEPTIMER                                           STD_ON
#define COMM_PNCPB                                                    STD_ON
#define COMM_PNCCHANNELMAPPINGENDIDXOFPNCPB                           STD_ON
#define COMM_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                         STD_ON
#define COMM_PNCCHANNELMAPPINGUSEDOFPNCPB                             STD_ON
#define COMM_PNCSIGNALINDENDIDXOFPNCPB                                STD_ON
#define COMM_PNCSIGNALINDSTARTIDXOFPNCPB                              STD_ON
#define COMM_PNCSIGNALINDUSEDOFPNCPB                                  STD_ON
#define COMM_SIGNALBYTEINDEXOFPNCPB                                   STD_ON
#define COMM_USERREQPNCFULLCOMENDIDXOFPNCPB                           STD_ON
#define COMM_USERREQPNCFULLCOMSTARTIDXOFPNCPB                         STD_ON
#define COMM_PNCPBIND                                                 STD_ON
#define COMM_PNCSIGNAL                                                STD_ON
#define COMM_BUSTYPEIDOFPNCSIGNAL                                     STD_ON
#define COMM_CHANNELIDXOFPNCSIGNAL                                    STD_ON
#define COMM_CHANNELUSEDOFPNCSIGNAL                                   STD_ON
#define COMM_PNCSIGNALVALUESENDIDXOFPNCSIGNAL                         STD_ON
#define COMM_PNCSIGNALVALUESSTARTIDXOFPNCSIGNAL                       STD_ON
#define COMM_PNCSIGNALVALUESUSEDOFPNCSIGNAL                           STD_ON
#define COMM_TYPEOFPNCSIGNAL                                          STD_ON
#define COMM_PNCSIGNALIND                                             STD_ON
#define COMM_PNCSIGNALVALUES                                          STD_ON
#define COMM_SIZEOFACTIVEPNCCOMMODE                                   STD_ON
#define COMM_SIZEOFBUSPNCCOMMODEREQ                                   STD_ON
#define COMM_SIZEOFCHANNEL                                            STD_ON
#define COMM_SIZEOFCHANNELPB                                          STD_ON
#define COMM_SIZEOFPNC                                                STD_ON
#define COMM_SIZEOFPNCCHANNELMAPPING                                  STD_ON
#define COMM_SIZEOFPNCPSLEEPTIMER                                     STD_ON
#define COMM_SIZEOFPNCPB                                              STD_ON
#define COMM_SIZEOFPNCPBIND                                           STD_ON
#define COMM_SIZEOFPNCSIGNAL                                          STD_ON
#define COMM_SIZEOFPNCSIGNALIND                                       STD_ON
#define COMM_SIZEOFPNCSIGNALVALUES                                    STD_ON
#define COMM_SIZEOFUSER                                               STD_ON
#define COMM_SIZEOFUSERBYTEMASK                                       STD_ON
#define COMM_SIZEOFUSERPNCBYTEMASK                                    STD_ON
#define COMM_SIZEOFUSERREQFULLCOM                                     STD_ON
#define COMM_SIZEOFUSERREQPNCFULLCOM                                  STD_ON
#define COMM_USER                                                     STD_ON
#define COMM_PNCUSEROFUSER                                            STD_ON
#define COMM_USERBYTEMASKENDIDXOFUSER                                 STD_ON
#define COMM_USERBYTEMASKSTARTIDXOFUSER                               STD_ON
#define COMM_USERBYTEMASKUSEDOFUSER                                   STD_ON
#define COMM_USERPNCBYTEMASKENDIDXOFUSER                              STD_ON
#define COMM_USERPNCBYTEMASKSTARTIDXOFUSER                            STD_ON
#define COMM_USERPNCBYTEMASKUSEDOFUSER                                STD_ON
#define COMM_USERBYTEMASK                                             STD_ON
#define COMM_CHANNELOFUSERBYTEMASK                                    STD_ON
#define COMM_CLEARMASKOFUSERBYTEMASK                                  STD_ON
#define COMM_SETMASKOFUSERBYTEMASK                                    STD_ON
#define COMM_USERREQFULLCOMIDXOFUSERBYTEMASK                          STD_ON
#define COMM_USERMODENOTIFUNC                                         STD_OFF  /**< Deactivateable: 'ComM_UserModeNotiFunc' Reason: 'No user mode Notification configured.' */
#define COMM_USERPNCBYTEMASK                                          STD_ON
#define COMM_CLEARMASKOFUSERPNCBYTEMASK                               STD_ON
#define COMM_PNCIDOFUSERPNCBYTEMASK                                   STD_ON
#define COMM_SETMASKOFUSERPNCBYTEMASK                                 STD_ON
#define COMM_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK                    STD_ON
#define COMM_USERREQFULLCOM                                           STD_ON
#define COMM_USERREQPNCFULLCOM                                        STD_ON
#define COMM_PCCONFIG                                                 STD_ON
#define COMM_ACTIVEPNCCOMMODEOFPCCONFIG                               STD_ON
#define COMM_BUSPNCCOMMODEREQOFPCCONFIG                               STD_ON
#define COMM_CHANNELOFPCCONFIG                                        STD_ON
#define COMM_CHANNELPBOFPCCONFIG                                      STD_ON
#define COMM_FINALMAGICNUMBEROFPCCONFIG                               STD_OFF  /**< Deactivateable: 'ComM_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_INITDATAHASHCODEOFPCCONFIG                               STD_OFF  /**< Deactivateable: 'ComM_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define COMM_PNCCHANNELMAPPINGOFPCCONFIG                              STD_ON
#define COMM_PNCOFPCCONFIG                                            STD_ON
#define COMM_PNCPSLEEPTIMEROFPCCONFIG                                 STD_ON
#define COMM_PNCPBINDOFPCCONFIG                                       STD_ON
#define COMM_PNCPBOFPCCONFIG                                          STD_ON
#define COMM_PNCSIGNALINDOFPCCONFIG                                   STD_ON
#define COMM_PNCSIGNALOFPCCONFIG                                      STD_ON
#define COMM_PNCSIGNALVALUESOFPCCONFIG                                STD_ON
#define COMM_SIZEOFACTIVEPNCCOMMODEOFPCCONFIG                         STD_ON
#define COMM_SIZEOFBUSPNCCOMMODEREQOFPCCONFIG                         STD_ON
#define COMM_SIZEOFCHANNELOFPCCONFIG                                  STD_ON
#define COMM_SIZEOFCHANNELPBOFPCCONFIG                                STD_ON
#define COMM_SIZEOFPNCCHANNELMAPPINGOFPCCONFIG                        STD_ON
#define COMM_SIZEOFPNCOFPCCONFIG                                      STD_ON
#define COMM_SIZEOFPNCPSLEEPTIMEROFPCCONFIG                           STD_ON
#define COMM_SIZEOFPNCPBINDOFPCCONFIG                                 STD_ON
#define COMM_SIZEOFPNCPBOFPCCONFIG                                    STD_ON
#define COMM_SIZEOFPNCSIGNALINDOFPCCONFIG                             STD_ON
#define COMM_SIZEOFPNCSIGNALOFPCCONFIG                                STD_ON
#define COMM_SIZEOFPNCSIGNALVALUESOFPCCONFIG                          STD_ON
#define COMM_SIZEOFUSERBYTEMASKOFPCCONFIG                             STD_ON
#define COMM_SIZEOFUSEROFPCCONFIG                                     STD_ON
#define COMM_SIZEOFUSERPNCBYTEMASKOFPCCONFIG                          STD_ON
#define COMM_SIZEOFUSERREQFULLCOMOFPCCONFIG                           STD_ON
#define COMM_SIZEOFUSERREQPNCFULLCOMOFPCCONFIG                        STD_ON
#define COMM_USERBYTEMASKOFPCCONFIG                                   STD_ON
#define COMM_USEROFPCCONFIG                                           STD_ON
#define COMM_USERPNCBYTEMASKOFPCCONFIG                                STD_ON
#define COMM_USERREQFULLCOMOFPCCONFIG                                 STD_ON
#define COMM_USERREQPNCFULLCOMOFPCCONFIG                              STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCMinNumericValueDefines  ComM Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define COMM_MIN_PNCPSLEEPTIMER                                       0u
#define COMM_MIN_PNCSIGNALVALUES                                      0u
#define COMM_MIN_USERREQFULLCOM                                       0u
#define COMM_MIN_USERREQPNCFULLCOM                                    0u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCMaxNumericValueDefines  ComM Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define COMM_MAX_PNCPSLEEPTIMER                                       65535u
#define COMM_MAX_PNCSIGNALVALUES                                      255u
#define COMM_MAX_USERREQFULLCOM                                       255u
#define COMM_MAX_USERREQPNCFULLCOM                                    255u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCNoReferenceDefines  ComM No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define COMM_NO_PNCPBINDENDIDXOFCHANNELPB                             255u
#define COMM_NO_PNCPBINDSTARTIDXOFCHANNELPB                           255u
#define COMM_NO_USERREQFULLCOMENDIDXOFCHANNELPB                       255u
#define COMM_NO_USERREQFULLCOMSTARTIDXOFCHANNELPB                     255u
#define COMM_NO_PNCCHANNELMAPPINGENDIDXOFPNCPB                        255u
#define COMM_NO_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                      255u
#define COMM_NO_PNCSIGNALINDENDIDXOFPNCPB                             255u
#define COMM_NO_PNCSIGNALINDSTARTIDXOFPNCPB                           255u
#define COMM_NO_CHANNELIDXOFPNCSIGNAL                                 255u
#define COMM_NO_PNCSIGNALVALUESENDIDXOFPNCSIGNAL                      255u
#define COMM_NO_PNCSIGNALVALUESSTARTIDXOFPNCSIGNAL                    255u
#define COMM_NO_USERBYTEMASKENDIDXOFUSER                              255u
#define COMM_NO_USERBYTEMASKSTARTIDXOFUSER                            255u
#define COMM_NO_USERPNCBYTEMASKENDIDXOFUSER                           255u
#define COMM_NO_USERPNCBYTEMASKSTARTIDXOFUSER                         255u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEnumExistsDefines  ComM Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_NMTYPEOFCHANNEL          STD_OFF
#define COMM_EXISTS_FULL_NMTYPEOFCHANNEL                              STD_ON
#define COMM_EXISTS_PASSIVE_NMTYPEOFCHANNEL                           STD_OFF
#define COMM_EXISTS_LIGHT_NMTYPEOFCHANNEL                             STD_OFF
#define COMM_EXISTS_NONE_NMTYPEOFCHANNEL                              STD_OFF
#define COMM_EXISTS_LINSLAVE_NMTYPEOFCHANNEL                          STD_OFF
#define COMM_EXISTS_EIRA_RX_TYPEOFPNCSIGNAL                           STD_ON
#define COMM_EXISTS_EIRA_TX_TYPEOFPNCSIGNAL                           STD_ON
#define COMM_EXISTS_ERA_RX_TYPEOFPNCSIGNAL                            STD_OFF
#define COMM_EXISTS_NOT_USED_IN_THIS_VARIANT_TYPEOFPNCSIGNAL          STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEnumDefines  ComM Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define COMM_FULL_NMTYPEOFCHANNEL                                     0x01u
#define COMM_EIRA_RX_TYPEOFPNCSIGNAL                                  0x00u
#define COMM_EIRA_TX_TYPEOFPNCSIGNAL                                  0x01u
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIsReducedToDefineDefines  ComM Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define COMM_ISDEF_BUSTYPEOFCHANNEL                                   STD_ON
#define COMM_ISDEF_GWTYPEOFCHANNEL                                    STD_ON
#define COMM_ISDEF_INHIBITIONINITVALUEOFCHANNEL                       STD_ON
#define COMM_ISDEF_NMSUPPORTOFCHANNEL                                 STD_ON
#define COMM_ISDEF_NMTYPEOFCHANNEL                                    STD_ON
#define COMM_ISDEF_PNCNMREQUESTOFCHANNEL                              STD_ON
#define COMM_ISDEF_SILENTSUPPORTOFCHANNEL                             STD_ON
#define COMM_ISDEF_WAKEUPSTATEOFCHANNEL                               STD_ON
#define COMM_ISDEF_PNCPBINDENDIDXOFCHANNELPB                          STD_ON
#define COMM_ISDEF_PNCPBINDSTARTIDXOFCHANNELPB                        STD_ON
#define COMM_ISDEF_PNCPBINDUSEDOFCHANNELPB                            STD_ON
#define COMM_ISDEF_USERREQFULLCOMENDIDXOFCHANNELPB                    STD_ON
#define COMM_ISDEF_USERREQFULLCOMSTARTIDXOFCHANNELPB                  STD_ON
#define COMM_ISDEF_USERREQFULLCOMUSEDOFCHANNELPB                      STD_ON
#define COMM_ISDEF_CLEARMASKOFPNC                                     STD_ON
#define COMM_ISDEF_PNCIDOFPNC                                         STD_ON
#define COMM_ISDEF_SETMASKOFPNC                                       STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPING                                  STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPINGENDIDXOFPNCPB                     STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                   STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPINGUSEDOFPNCPB                       STD_ON
#define COMM_ISDEF_PNCSIGNALINDENDIDXOFPNCPB                          STD_ON
#define COMM_ISDEF_PNCSIGNALINDSTARTIDXOFPNCPB                        STD_ON
#define COMM_ISDEF_PNCSIGNALINDUSEDOFPNCPB                            STD_ON
#define COMM_ISDEF_SIGNALBYTEINDEXOFPNCPB                             STD_ON
#define COMM_ISDEF_USERREQPNCFULLCOMENDIDXOFPNCPB                     STD_ON
#define COMM_ISDEF_USERREQPNCFULLCOMSTARTIDXOFPNCPB                   STD_ON
#define COMM_ISDEF_PNCPBIND                                           STD_ON
#define COMM_ISDEF_BUSTYPEIDOFPNCSIGNAL                               STD_ON
#define COMM_ISDEF_CHANNELIDXOFPNCSIGNAL                              STD_OFF
#define COMM_ISDEF_CHANNELUSEDOFPNCSIGNAL                             STD_OFF
#define COMM_ISDEF_PNCSIGNALVALUESENDIDXOFPNCSIGNAL                   STD_OFF
#define COMM_ISDEF_PNCSIGNALVALUESSTARTIDXOFPNCSIGNAL                 STD_OFF
#define COMM_ISDEF_PNCSIGNALVALUESUSEDOFPNCSIGNAL                     STD_ON
#define COMM_ISDEF_TYPEOFPNCSIGNAL                                    STD_OFF
#define COMM_ISDEF_PNCSIGNALIND                                       STD_ON
#define COMM_ISDEF_PNCUSEROFUSER                                      STD_OFF
#define COMM_ISDEF_USERBYTEMASKENDIDXOFUSER                           STD_OFF
#define COMM_ISDEF_USERBYTEMASKSTARTIDXOFUSER                         STD_OFF
#define COMM_ISDEF_USERBYTEMASKUSEDOFUSER                             STD_ON
#define COMM_ISDEF_USERPNCBYTEMASKENDIDXOFUSER                        STD_OFF
#define COMM_ISDEF_USERPNCBYTEMASKSTARTIDXOFUSER                      STD_OFF
#define COMM_ISDEF_USERPNCBYTEMASKUSEDOFUSER                          STD_OFF
#define COMM_ISDEF_CHANNELOFUSERBYTEMASK                              STD_ON
#define COMM_ISDEF_CLEARMASKOFUSERBYTEMASK                            STD_OFF
#define COMM_ISDEF_SETMASKOFUSERBYTEMASK                              STD_OFF
#define COMM_ISDEF_USERREQFULLCOMIDXOFUSERBYTEMASK                    STD_ON
#define COMM_ISDEF_CLEARMASKOFUSERPNCBYTEMASK                         STD_ON
#define COMM_ISDEF_PNCIDOFUSERPNCBYTEMASK                             STD_ON
#define COMM_ISDEF_SETMASKOFUSERPNCBYTEMASK                           STD_ON
#define COMM_ISDEF_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK              STD_ON
#define COMM_ISDEF_ACTIVEPNCCOMMODEOFPCCONFIG                         STD_ON
#define COMM_ISDEF_BUSPNCCOMMODEREQOFPCCONFIG                         STD_ON
#define COMM_ISDEF_CHANNELOFPCCONFIG                                  STD_ON
#define COMM_ISDEF_CHANNELPBOFPCCONFIG                                STD_ON
#define COMM_ISDEF_PNCCHANNELMAPPINGOFPCCONFIG                        STD_ON
#define COMM_ISDEF_PNCOFPCCONFIG                                      STD_ON
#define COMM_ISDEF_PNCPSLEEPTIMEROFPCCONFIG                           STD_ON
#define COMM_ISDEF_PNCPBINDOFPCCONFIG                                 STD_ON
#define COMM_ISDEF_PNCPBOFPCCONFIG                                    STD_ON
#define COMM_ISDEF_PNCSIGNALINDOFPCCONFIG                             STD_ON
#define COMM_ISDEF_PNCSIGNALOFPCCONFIG                                STD_ON
#define COMM_ISDEF_PNCSIGNALVALUESOFPCCONFIG                          STD_ON
#define COMM_ISDEF_USERBYTEMASKOFPCCONFIG                             STD_ON
#define COMM_ISDEF_USEROFPCCONFIG                                     STD_ON
#define COMM_ISDEF_USERPNCBYTEMASKOFPCCONFIG                          STD_ON
#define COMM_ISDEF_USERREQFULLCOMOFPCCONFIG                           STD_ON
#define COMM_ISDEF_USERREQPNCFULLCOMOFPCCONFIG                        STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCEqualsAlwaysToDefines  ComM Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define COMM_EQ2_BUSTYPEOFCHANNEL                                     COMM_BUS_TYPE_ETH
#define COMM_EQ2_GWTYPEOFCHANNEL                                      COMM_GATEWAY_TYPE_NONE
#define COMM_EQ2_INHIBITIONINITVALUEOFCHANNEL                         0x00u
#define COMM_EQ2_NMSUPPORTOFCHANNEL                                   TRUE
#define COMM_EQ2_NMTYPEOFCHANNEL                                      COMM_FULL_NMTYPEOFCHANNEL
#define COMM_EQ2_PNCNMREQUESTOFCHANNEL                                TRUE
#define COMM_EQ2_SILENTSUPPORTOFCHANNEL                               TRUE
#define COMM_EQ2_WAKEUPSTATEOFCHANNEL                                 COMM_FULL_COM_READY_SLEEP
#define COMM_EQ2_PNCPBINDENDIDXOFCHANNELPB                            1u
#define COMM_EQ2_PNCPBINDSTARTIDXOFCHANNELPB                          0u
#define COMM_EQ2_PNCPBINDUSEDOFCHANNELPB                              TRUE
#define COMM_EQ2_USERREQFULLCOMENDIDXOFCHANNELPB                      1u
#define COMM_EQ2_USERREQFULLCOMSTARTIDXOFCHANNELPB                    0u
#define COMM_EQ2_USERREQFULLCOMUSEDOFCHANNELPB                        TRUE
#define COMM_EQ2_CLEARMASKOFPNC                                       0xFEu
#define COMM_EQ2_PNCIDOFPNC                                           0u
#define COMM_EQ2_SETMASKOFPNC                                         0x01u
#define COMM_EQ2_PNCCHANNELMAPPING                                    0u
#define COMM_EQ2_PNCCHANNELMAPPINGENDIDXOFPNCPB                       1u
#define COMM_EQ2_PNCCHANNELMAPPINGSTARTIDXOFPNCPB                     0u
#define COMM_EQ2_PNCCHANNELMAPPINGUSEDOFPNCPB                         TRUE
#define COMM_EQ2_PNCSIGNALINDENDIDXOFPNCPB                            1u
#define COMM_EQ2_PNCSIGNALINDSTARTIDXOFPNCPB                          0u
#define COMM_EQ2_PNCSIGNALINDUSEDOFPNCPB                              TRUE
#define COMM_EQ2_SIGNALBYTEINDEXOFPNCPB                               0u
#define COMM_EQ2_USERREQPNCFULLCOMENDIDXOFPNCPB                       1u
#define COMM_EQ2_USERREQPNCFULLCOMSTARTIDXOFPNCPB                     0u
#define COMM_EQ2_PNCPBIND                                             0u
#define COMM_EQ2_BUSTYPEIDOFPNCSIGNAL                                 0u
#define COMM_EQ2_CHANNELIDXOFPNCSIGNAL                                
#define COMM_EQ2_CHANNELUSEDOFPNCSIGNAL                               
#define COMM_EQ2_PNCSIGNALVALUESENDIDXOFPNCSIGNAL                     
#define COMM_EQ2_PNCSIGNALVALUESSTARTIDXOFPNCSIGNAL                   
#define COMM_EQ2_PNCSIGNALVALUESUSEDOFPNCSIGNAL                       TRUE
#define COMM_EQ2_TYPEOFPNCSIGNAL                                      
#define COMM_EQ2_PNCSIGNALIND                                         1u
#define COMM_EQ2_PNCUSEROFUSER                                        
#define COMM_EQ2_USERBYTEMASKENDIDXOFUSER                             
#define COMM_EQ2_USERBYTEMASKSTARTIDXOFUSER                           
#define COMM_EQ2_USERBYTEMASKUSEDOFUSER                               TRUE
#define COMM_EQ2_USERPNCBYTEMASKENDIDXOFUSER                          
#define COMM_EQ2_USERPNCBYTEMASKSTARTIDXOFUSER                        
#define COMM_EQ2_USERPNCBYTEMASKUSEDOFUSER                            
#define COMM_EQ2_CHANNELOFUSERBYTEMASK                                0u
#define COMM_EQ2_CLEARMASKOFUSERBYTEMASK                              
#define COMM_EQ2_SETMASKOFUSERBYTEMASK                                
#define COMM_EQ2_USERREQFULLCOMIDXOFUSERBYTEMASK                      0u
#define COMM_EQ2_CLEARMASKOFUSERPNCBYTEMASK                           0xFEu
#define COMM_EQ2_PNCIDOFUSERPNCBYTEMASK                               0u
#define COMM_EQ2_SETMASKOFUSERPNCBYTEMASK                             0x01u
#define COMM_EQ2_USERREQPNCFULLCOMIDXOFUSERPNCBYTEMASK                0u
#define COMM_EQ2_ACTIVEPNCCOMMODEOFPCCONFIG                           ComM_ActivePncComMode
#define COMM_EQ2_BUSPNCCOMMODEREQOFPCCONFIG                           ComM_BusPncComModeReq
#define COMM_EQ2_CHANNELOFPCCONFIG                                    ComM_Channel
#define COMM_EQ2_CHANNELPBOFPCCONFIG                                  ComM_ChannelPb
#define COMM_EQ2_PNCCHANNELMAPPINGOFPCCONFIG                          ComM_PncChannelMapping
#define COMM_EQ2_PNCOFPCCONFIG                                        ComM_Pnc
#define COMM_EQ2_PNCPSLEEPTIMEROFPCCONFIG                             ComM_PncPSleepTimer
#define COMM_EQ2_PNCPBINDOFPCCONFIG                                   ComM_PncPbInd
#define COMM_EQ2_PNCPBOFPCCONFIG                                      ComM_PncPb
#define COMM_EQ2_PNCSIGNALINDOFPCCONFIG                               ComM_PncSignalInd
#define COMM_EQ2_PNCSIGNALOFPCCONFIG                                  ComM_PncSignal
#define COMM_EQ2_PNCSIGNALVALUESOFPCCONFIG                            ComM_PncSignalValues.raw
#define COMM_EQ2_USERBYTEMASKOFPCCONFIG                               ComM_UserByteMask
#define COMM_EQ2_USEROFPCCONFIG                                       ComM_User
#define COMM_EQ2_USERPNCBYTEMASKOFPCCONFIG                            ComM_UserPncByteMask
#define COMM_EQ2_USERREQFULLCOMOFPCCONFIG                             ComM_UserReqFullCom
#define COMM_EQ2_USERREQPNCFULLCOMOFPCCONFIG                          ComM_UserReqPncFullCom
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSymbolicInitializationPointers  ComM Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define ComM_Config_Ptr                                               NULL_PTR  /**< symbolic identifier which shall be used to initialize 'ComM' */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCInitializationSymbols  ComM Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define ComM_Config                                                   NULL_PTR  /**< symbolic identifier which could be used to initialize 'ComM */
/** 
  \}
*/ 

/** 
  \defgroup  ComMPCGeneral  ComM General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define COMM_CHECK_INIT_POINTER                                       STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define COMM_FINAL_MAGIC_NUMBER                                       0x0C1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of ComM */
#define COMM_INDIVIDUAL_POSTBUILD                                     STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'ComM' is not configured to be postbuild capable. */
#define COMM_INIT_DATA                                                COMM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define COMM_INIT_DATA_HASH_CODE                                      -215872543  /**< the precompile constant to validate the initialization structure at initialization time of ComM with a hashcode. The seed value is '0x0C1Eu' */
#define COMM_USE_ECUM_BSW_ERROR_HOOK                                  STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define COMM_USE_INIT_POINTER                                         STD_OFF  /**< STD_ON if the init pointer ComM shall be used. */
/** 
  \}
*/ 



/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCIterableTypes  ComM Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate ComM_Channel */
typedef uint8_least ComM_ChannelIterType;

/**   \brief  type used to iterate ComM_ChannelPb */
typedef uint8_least ComM_ChannelPbIterType;

/**   \brief  type used to iterate ComM_Pnc */
typedef uint8_least ComM_PncIterType;

/**   \brief  type used to iterate ComM_PncChannelMapping */
typedef uint8_least ComM_PncChannelMappingIterType;

/**   \brief  type used to iterate ComM_PncPb */
typedef uint8_least ComM_PncPbIterType;

/**   \brief  type used to iterate ComM_PncPbInd */
typedef uint8_least ComM_PncPbIndIterType;

/**   \brief  type used to iterate ComM_PncSignal */
typedef uint8_least ComM_PncSignalIterType;

/**   \brief  type used to iterate ComM_PncSignalInd */
typedef uint8_least ComM_PncSignalIndIterType;

/**   \brief  type used to iterate ComM_PncSignalValues */
typedef uint8_least ComM_PncSignalValuesIterType;

/**   \brief  type used to iterate ComM_User */
typedef uint8_least ComM_UserIterType;

/**   \brief  type used to iterate ComM_UserByteMask */
typedef uint8_least ComM_UserByteMaskIterType;

/**   \brief  type used to iterate ComM_UserPncByteMask */
typedef uint8_least ComM_UserPncByteMaskIterType;

/**   \brief  type used to iterate ComM_UserReqFullCom */
typedef uint8_least ComM_UserReqFullComIterType;

/**   \brief  type used to iterate ComM_UserReqPncFullCom */
typedef uint8_least ComM_UserReqPncFullComIterType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCIterableTypesWithSizeRelations  ComM Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate ComM_ActivePncComMode */
typedef ComM_PncIterType ComM_ActivePncComModeIterType;

/**   \brief  type used to iterate ComM_BusPncComModeReq */
typedef ComM_PncIterType ComM_BusPncComModeReqIterType;

/**   \brief  type used to iterate ComM_PncPSleepTimer */
typedef ComM_PncIterType ComM_PncPSleepTimerIterType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCValueTypes  ComM Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for ComM_GwTypeOfChannel */
typedef uint8 ComM_GwTypeOfChannelType;

/**   \brief  value based type definition for ComM_InhibitionInitValueOfChannel */
typedef uint8 ComM_InhibitionInitValueOfChannelType;

/**   \brief  value based type definition for ComM_NmSupportOfChannel */
typedef boolean ComM_NmSupportOfChannelType;

/**   \brief  value based type definition for ComM_NmTypeOfChannel */
typedef uint8 ComM_NmTypeOfChannelType;

/**   \brief  value based type definition for ComM_PncNmRequestOfChannel */
typedef boolean ComM_PncNmRequestOfChannelType;

/**   \brief  value based type definition for ComM_SilentSupportOfChannel */
typedef boolean ComM_SilentSupportOfChannelType;

/**   \brief  value based type definition for ComM_WakeupStateOfChannel */
typedef uint8 ComM_WakeupStateOfChannelType;

/**   \brief  value based type definition for ComM_PncPbIndEndIdxOfChannelPb */
typedef uint8 ComM_PncPbIndEndIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_PncPbIndStartIdxOfChannelPb */
typedef uint8 ComM_PncPbIndStartIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_PncPbIndUsedOfChannelPb */
typedef boolean ComM_PncPbIndUsedOfChannelPbType;

/**   \brief  value based type definition for ComM_UserReqFullComEndIdxOfChannelPb */
typedef uint8 ComM_UserReqFullComEndIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_UserReqFullComStartIdxOfChannelPb */
typedef uint8 ComM_UserReqFullComStartIdxOfChannelPbType;

/**   \brief  value based type definition for ComM_UserReqFullComUsedOfChannelPb */
typedef boolean ComM_UserReqFullComUsedOfChannelPbType;

/**   \brief  value based type definition for ComM_ClearMaskOfPnc */
typedef uint8 ComM_ClearMaskOfPncType;

/**   \brief  value based type definition for ComM_PncIdOfPnc */
typedef uint8 ComM_PncIdOfPncType;

/**   \brief  value based type definition for ComM_SetMaskOfPnc */
typedef uint8 ComM_SetMaskOfPncType;

/**   \brief  value based type definition for ComM_PncChannelMapping */
typedef uint8 ComM_PncChannelMappingType;

/**   \brief  value based type definition for ComM_PncPSleepTimer */
typedef uint16 ComM_PncPSleepTimerType;

/**   \brief  value based type definition for ComM_PncChannelMappingEndIdxOfPncPb */
typedef uint8 ComM_PncChannelMappingEndIdxOfPncPbType;

/**   \brief  value based type definition for ComM_PncChannelMappingStartIdxOfPncPb */
typedef uint8 ComM_PncChannelMappingStartIdxOfPncPbType;

/**   \brief  value based type definition for ComM_PncChannelMappingUsedOfPncPb */
typedef boolean ComM_PncChannelMappingUsedOfPncPbType;

/**   \brief  value based type definition for ComM_PncSignalIndEndIdxOfPncPb */
typedef uint8 ComM_PncSignalIndEndIdxOfPncPbType;

/**   \brief  value based type definition for ComM_PncSignalIndStartIdxOfPncPb */
typedef uint8 ComM_PncSignalIndStartIdxOfPncPbType;

/**   \brief  value based type definition for ComM_PncSignalIndUsedOfPncPb */
typedef boolean ComM_PncSignalIndUsedOfPncPbType;

/**   \brief  value based type definition for ComM_SignalByteIndexOfPncPb */
typedef uint8 ComM_SignalByteIndexOfPncPbType;

/**   \brief  value based type definition for ComM_UserReqPncFullComEndIdxOfPncPb */
typedef uint8 ComM_UserReqPncFullComEndIdxOfPncPbType;

/**   \brief  value based type definition for ComM_UserReqPncFullComStartIdxOfPncPb */
typedef uint8 ComM_UserReqPncFullComStartIdxOfPncPbType;

/**   \brief  value based type definition for ComM_PncPbInd */
typedef uint8 ComM_PncPbIndType;

/**   \brief  value based type definition for ComM_BusTypeIdOfPncSignal */
typedef uint8 ComM_BusTypeIdOfPncSignalType;

/**   \brief  value based type definition for ComM_ChannelIdxOfPncSignal */
typedef uint8 ComM_ChannelIdxOfPncSignalType;

/**   \brief  value based type definition for ComM_ChannelUsedOfPncSignal */
typedef boolean ComM_ChannelUsedOfPncSignalType;

/**   \brief  value based type definition for ComM_PncSignalValuesEndIdxOfPncSignal */
typedef uint8 ComM_PncSignalValuesEndIdxOfPncSignalType;

/**   \brief  value based type definition for ComM_PncSignalValuesStartIdxOfPncSignal */
typedef uint8 ComM_PncSignalValuesStartIdxOfPncSignalType;

/**   \brief  value based type definition for ComM_PncSignalValuesUsedOfPncSignal */
typedef boolean ComM_PncSignalValuesUsedOfPncSignalType;

/**   \brief  value based type definition for ComM_TypeOfPncSignal */
typedef uint8 ComM_TypeOfPncSignalType;

/**   \brief  value based type definition for ComM_PncSignalInd */
typedef uint8 ComM_PncSignalIndType;

/**   \brief  value based type definition for ComM_PncSignalValues */
typedef uint8 ComM_PncSignalValuesType;

/**   \brief  value based type definition for ComM_SizeOfActivePncComMode */
typedef uint8 ComM_SizeOfActivePncComModeType;

/**   \brief  value based type definition for ComM_SizeOfBusPncComModeReq */
typedef uint8 ComM_SizeOfBusPncComModeReqType;

/**   \brief  value based type definition for ComM_SizeOfChannel */
typedef uint8 ComM_SizeOfChannelType;

/**   \brief  value based type definition for ComM_SizeOfChannelPb */
typedef uint8 ComM_SizeOfChannelPbType;

/**   \brief  value based type definition for ComM_SizeOfPnc */
typedef uint8 ComM_SizeOfPncType;

/**   \brief  value based type definition for ComM_SizeOfPncChannelMapping */
typedef uint8 ComM_SizeOfPncChannelMappingType;

/**   \brief  value based type definition for ComM_SizeOfPncPSleepTimer */
typedef uint8 ComM_SizeOfPncPSleepTimerType;

/**   \brief  value based type definition for ComM_SizeOfPncPb */
typedef uint8 ComM_SizeOfPncPbType;

/**   \brief  value based type definition for ComM_SizeOfPncPbInd */
typedef uint8 ComM_SizeOfPncPbIndType;

/**   \brief  value based type definition for ComM_SizeOfPncSignal */
typedef uint8 ComM_SizeOfPncSignalType;

/**   \brief  value based type definition for ComM_SizeOfPncSignalInd */
typedef uint8 ComM_SizeOfPncSignalIndType;

/**   \brief  value based type definition for ComM_SizeOfPncSignalValues */
typedef uint8 ComM_SizeOfPncSignalValuesType;

/**   \brief  value based type definition for ComM_SizeOfUser */
typedef uint8 ComM_SizeOfUserType;

/**   \brief  value based type definition for ComM_SizeOfUserByteMask */
typedef uint8 ComM_SizeOfUserByteMaskType;

/**   \brief  value based type definition for ComM_SizeOfUserPncByteMask */
typedef uint8 ComM_SizeOfUserPncByteMaskType;

/**   \brief  value based type definition for ComM_SizeOfUserReqFullCom */
typedef uint8 ComM_SizeOfUserReqFullComType;

/**   \brief  value based type definition for ComM_SizeOfUserReqPncFullCom */
typedef uint8 ComM_SizeOfUserReqPncFullComType;

/**   \brief  value based type definition for ComM_PncUserOfUser */
typedef boolean ComM_PncUserOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskEndIdxOfUser */
typedef uint8 ComM_UserByteMaskEndIdxOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskStartIdxOfUser */
typedef uint8 ComM_UserByteMaskStartIdxOfUserType;

/**   \brief  value based type definition for ComM_UserByteMaskUsedOfUser */
typedef boolean ComM_UserByteMaskUsedOfUserType;

/**   \brief  value based type definition for ComM_UserPncByteMaskEndIdxOfUser */
typedef uint8 ComM_UserPncByteMaskEndIdxOfUserType;

/**   \brief  value based type definition for ComM_UserPncByteMaskStartIdxOfUser */
typedef uint8 ComM_UserPncByteMaskStartIdxOfUserType;

/**   \brief  value based type definition for ComM_UserPncByteMaskUsedOfUser */
typedef boolean ComM_UserPncByteMaskUsedOfUserType;

/**   \brief  value based type definition for ComM_ChannelOfUserByteMask */
typedef uint8 ComM_ChannelOfUserByteMaskType;

/**   \brief  value based type definition for ComM_ClearMaskOfUserByteMask */
typedef uint8 ComM_ClearMaskOfUserByteMaskType;

/**   \brief  value based type definition for ComM_SetMaskOfUserByteMask */
typedef uint8 ComM_SetMaskOfUserByteMaskType;

/**   \brief  value based type definition for ComM_UserReqFullComIdxOfUserByteMask */
typedef uint8 ComM_UserReqFullComIdxOfUserByteMaskType;

/**   \brief  value based type definition for ComM_ClearMaskOfUserPncByteMask */
typedef uint8 ComM_ClearMaskOfUserPncByteMaskType;

/**   \brief  value based type definition for ComM_PncIDOfUserPncByteMask */
typedef uint8 ComM_PncIDOfUserPncByteMaskType;

/**   \brief  value based type definition for ComM_SetMaskOfUserPncByteMask */
typedef uint8 ComM_SetMaskOfUserPncByteMaskType;

/**   \brief  value based type definition for ComM_UserReqPncFullComIdxOfUserPncByteMask */
typedef uint8 ComM_UserReqPncFullComIdxOfUserPncByteMaskType;

/**   \brief  value based type definition for ComM_UserReqFullCom */
typedef uint8 ComM_UserReqFullComType;

/**   \brief  value based type definition for ComM_UserReqPncFullCom */
typedef uint8 ComM_UserReqPncFullComType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  ComMPCStructTypes  ComM Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in ComM_Channel */
typedef struct sComM_ChannelType
{
  uint8 ComM_ChannelNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_ChannelType;

/**   \brief  type used in ComM_ChannelPb */
typedef struct sComM_ChannelPbType
{
  uint8 ComM_ChannelPbNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_ChannelPbType;

/**   \brief  type used in ComM_Pnc */
typedef struct sComM_PncType
{
  uint8 ComM_PncNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_PncType;

/**   \brief  type used in ComM_PncPb */
typedef struct sComM_PncPbType
{
  uint8 ComM_PncPbNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_PncPbType;

/**   \brief  type used in ComM_PncSignal */
typedef struct sComM_PncSignalType
{
  ComM_ChannelIdxOfPncSignalType ChannelIdxOfPncSignal;  /**< the index of the 0:1 relation pointing to ComM_Channel */
  ComM_PncSignalValuesEndIdxOfPncSignalType PncSignalValuesEndIdxOfPncSignal;  /**< the end index of the 0:n relation pointing to ComM_PncSignalValues */
  ComM_PncSignalValuesStartIdxOfPncSignalType PncSignalValuesStartIdxOfPncSignal;  /**< the start index of the 0:n relation pointing to ComM_PncSignalValues */
  ComM_TypeOfPncSignalType TypeOfPncSignal;  /**< Partial network signal type */
} ComM_PncSignalType;

/**   \brief  type used in ComM_User */
typedef struct sComM_UserType
{
  ComM_PncUserOfUserType PncUserOfUser;  /**< decides if a user is a partial network user or a direct channel user */
  ComM_UserByteMaskEndIdxOfUserType UserByteMaskEndIdxOfUser;  /**< the end index of the 0:n relation pointing to ComM_UserByteMask */
  ComM_UserByteMaskStartIdxOfUserType UserByteMaskStartIdxOfUser;  /**< the start index of the 0:n relation pointing to ComM_UserByteMask */
  ComM_UserPncByteMaskEndIdxOfUserType UserPncByteMaskEndIdxOfUser;  /**< the end index of the 0:n relation pointing to ComM_UserPncByteMask */
  ComM_UserPncByteMaskStartIdxOfUserType UserPncByteMaskStartIdxOfUser;  /**< the start index of the 0:n relation pointing to ComM_UserPncByteMask */
} ComM_UserType;

/**   \brief  type used in ComM_UserByteMask */
typedef struct sComM_UserByteMaskType
{
  ComM_ClearMaskOfUserByteMaskType ClearMaskOfUserByteMask;  /**< Clear-mask for clearing the bit which corresponds to this user */
  ComM_SetMaskOfUserByteMaskType SetMaskOfUserByteMask;  /**< Set-mask for setting the bit which corresponds to this user */
} ComM_UserByteMaskType;

/**   \brief  type used in ComM_UserPncByteMask */
typedef struct sComM_UserPncByteMaskType
{
  uint8 ComM_UserPncByteMaskNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_UserPncByteMaskType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCSymbolicStructTypes  ComM Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to ComM_PncSignalValues */
typedef struct ComM_PncSignalValuesStructSTag
{
  ComM_PncSignalValuesType ComM_ComConf_ComSignal_ComSignalPnc_EIRA_ETH_Rx[7];
  ComM_PncSignalValuesType ComM_ComConf_ComSignal_ComSignalPnc_EIRA_ETH_Tx[7];
} ComM_PncSignalValuesStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCUnionIndexAndSymbolTypes  ComM Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access ComM_PncSignalValues in an index and symbol based style. */
typedef union ComM_PncSignalValuesUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  ComM_PncSignalValuesType raw[14];
  ComM_PncSignalValuesStructSType str;
} ComM_PncSignalValuesUType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCRootPointerTypes  ComM Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to ComM_ActivePncComMode */
typedef P2VAR(ComM_PncModeType, TYPEDEF, COMM_VAR_NOINIT) ComM_ActivePncComModePtrType;

/**   \brief  type used to point to ComM_BusPncComModeReq */
typedef P2VAR(ComM_PncModeType, TYPEDEF, COMM_VAR_NOINIT) ComM_BusPncComModeReqPtrType;

/**   \brief  type used to point to ComM_Channel */
typedef P2CONST(ComM_ChannelType, TYPEDEF, COMM_CONST) ComM_ChannelPtrType;

/**   \brief  type used to point to ComM_ChannelPb */
typedef P2CONST(ComM_ChannelPbType, TYPEDEF, COMM_CONST) ComM_ChannelPbPtrType;

/**   \brief  type used to point to ComM_Pnc */
typedef P2CONST(ComM_PncType, TYPEDEF, COMM_CONST) ComM_PncPtrType;

/**   \brief  type used to point to ComM_PncChannelMapping */
typedef P2CONST(ComM_PncChannelMappingType, TYPEDEF, COMM_CONST) ComM_PncChannelMappingPtrType;

/**   \brief  type used to point to ComM_PncPSleepTimer */
typedef P2VAR(ComM_PncPSleepTimerType, TYPEDEF, COMM_VAR_NOINIT) ComM_PncPSleepTimerPtrType;

/**   \brief  type used to point to ComM_PncPb */
typedef P2CONST(ComM_PncPbType, TYPEDEF, COMM_CONST) ComM_PncPbPtrType;

/**   \brief  type used to point to ComM_PncPbInd */
typedef P2CONST(ComM_PncPbIndType, TYPEDEF, COMM_CONST) ComM_PncPbIndPtrType;

/**   \brief  type used to point to ComM_PncSignal */
typedef P2CONST(ComM_PncSignalType, TYPEDEF, COMM_CONST) ComM_PncSignalPtrType;

/**   \brief  type used to point to ComM_PncSignalInd */
typedef P2CONST(ComM_PncSignalIndType, TYPEDEF, COMM_CONST) ComM_PncSignalIndPtrType;

/**   \brief  type used to point to ComM_PncSignalValues */
typedef P2VAR(ComM_PncSignalValuesType, TYPEDEF, COMM_VAR_NOINIT) ComM_PncSignalValuesPtrType;

/**   \brief  type used to point to ComM_User */
typedef P2CONST(ComM_UserType, TYPEDEF, COMM_CONST) ComM_UserPtrType;

/**   \brief  type used to point to ComM_UserByteMask */
typedef P2CONST(ComM_UserByteMaskType, TYPEDEF, COMM_CONST) ComM_UserByteMaskPtrType;

/**   \brief  type used to point to ComM_UserPncByteMask */
typedef P2CONST(ComM_UserPncByteMaskType, TYPEDEF, COMM_CONST) ComM_UserPncByteMaskPtrType;

/**   \brief  type used to point to ComM_UserReqFullCom */
typedef P2VAR(ComM_UserReqFullComType, TYPEDEF, COMM_VAR_NOINIT) ComM_UserReqFullComPtrType;

/**   \brief  type used to point to ComM_UserReqPncFullCom */
typedef P2VAR(ComM_UserReqPncFullComType, TYPEDEF, COMM_VAR_NOINIT) ComM_UserReqPncFullComPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  ComMPCRootValueTypes  ComM Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in ComM_PCConfig */
typedef struct sComM_PCConfigType
{
  uint8 ComM_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} ComM_PCConfigType;

typedef ComM_PCConfigType ComM_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 




#endif /* COMM_CFG_H */

