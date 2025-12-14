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
 *            Module: UdpNm
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: UdpNm_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (UDPNM_CFG_H)
# define UDPNM_CFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_CSL_0779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ComStack_Types.h"
#include "NmStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Symbolic name defines for UdpNmTxPdus */



/**
 * \defgroup UdpNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define UdpNmConf_UdpNmTxPdu_UdpNmTxPdu                               0u
/**\} */

/* Symbolic name defines for UdpNmTxUserDataPdus */



/**
 * \defgroup UdpNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define UdpNmConf_UdpNmUserDataTxPdu_UdpNmUserDataTxPdu               0u
/**\} */

/* Symbolic name defines for UdpNmRxPdus */



/**
 * \defgroup UdpNmHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define UdpNmConf_UdpNmRxPdu_UdpNmRxPdu                               0u
/**\} */

/* Options */
#define UDPNM_USER_DATA_ENABLED                         STD_OFF
#define UDPNM_PASSIVE_MODE_ENABLED                      STD_OFF
#define UDPNM_VERSION_INFO_API                          STD_OFF
#define UDPNM_PDU_RX_INDICATION_ENABLED                 STD_OFF
#define UDPNM_STATE_CHANGE_IND_ENABLED                  STD_ON
#define UDPNM_REMOTE_SLEEP_IND_ENABLED                  STD_OFF
#define UDPNM_BUS_SYNCHRONIZATION_ENABLED               STD_OFF
#define UDPNM_COM_USER_DATA_SUPPORT                     STD_ON
#define UDPNM_COORDINATOR_SYNC_SUPPORT                  STD_OFF
#define UDPNM_RUNTIME_MEASUREMENT_SUPPORT               STD_OFF
#define UDPNM_RUNTIME_ERROR_REPORT                      STD_ON
#define UDPNM_PDUR_UDPNM_TXCONFIRMATION                 STD_OFF
#define UDPNM_CAR_WUP_FILTER_FEATURE_ENABLED            STD_OFF
#define UDPNM_IMMEDIATE_NM_TX_FEATURE_ENABLED           STD_ON
#define UDPNM_ACTIVE_WUP_BIT_FEATURE_ENABLED            STD_ON
#define UDPNM_PN_FEATURE_ENABLED                        STD_ON
#define UDPNM_PN_ERA_CALC_FEATURE_ENABLED               STD_OFF
#define UDPNM_PN_EIRA_CALC_FEATURE_ENABLED              STD_ON
#define UDPNM_ALLOW_TRIGGERED_MSG_TRANSMISSION          STD_ON

#define UDPNM_OPTIMIZE_CHANNEL_ENABLED

#define UDPNM_EXPECTED_GENERATOR_COMPATIBILITY_VERSION  0x0600u

/* Invalid Channel Handle */
#define UDPNM_INVALID_CHANNEL      0xFFu

/* Pdu CBV / NID Position Defines */
#define UDPNM_PDU_OFF              0xFFu
#define UDPNM_PDU_BYTE_0           0x00u
#define UDPNM_PDU_BYTE_1           0x01u

/* PN Calculation */
#if ( UDPNM_PN_EIRA_CALC_FEATURE_ENABLED == STD_ON ) || ( UDPNM_PN_ERA_CALC_FEATURE_ENABLED == STD_ON )
# define UDPNM_PN_CALC_FEATURE_ENABLED
#endif

#if defined (UDPNM_ISDEF_PNEIRACALCENABLED)
#else
# define UDPNM_ISDEF_PNEIRACALCENABLED                     STD_ON
#endif

#if defined (UDPNM_ISDEF_PNENABLEDINVARIANT)
#else
# define UDPNM_ISDEF_PNENABLEDINVARIANT                    STD_ON
#endif

/**********************************************************************************************************************
    General Defines
**********************************************************************************************************************/
#ifndef UDPNM_DEV_ERROR_DETECT
#define UDPNM_DEV_ERROR_DETECT STD_ON
#endif
#ifndef UDPNM_DEV_ERROR_REPORT
#define UDPNM_DEV_ERROR_REPORT STD_ON
#endif
#ifndef UDPNM_USE_DUMMY_STATEMENT
#define UDPNM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef UDPNM_DUMMY_STATEMENT
#define UDPNM_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef UDPNM_DUMMY_STATEMENT_CONST
#define UDPNM_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef UDPNM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define UDPNM_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef UDPNM_ATOMIC_VARIABLE_ACCESS
#define UDPNM_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef UDPNM_PROCESSOR_TC397X_STEPB
#define UDPNM_PROCESSOR_TC397X_STEPB
#endif
#ifndef UDPNM_COMP_TASKING
#define UDPNM_COMP_TASKING
#endif
#ifndef UDPNM_GEN_GENERATOR_MSR
#define UDPNM_GEN_GENERATOR_MSR
#endif
#ifndef UDPNM_CPUTYPE_BITORDER_LSB2MSB
#define UDPNM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef UDPNM_CONFIGURATION_VARIANT_PRECOMPILE
#define UDPNM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef UDPNM_CONFIGURATION_VARIANT_LINKTIME
#define UDPNM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define UDPNM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef UDPNM_CONFIGURATION_VARIANT
#define UDPNM_CONFIGURATION_VARIANT UDPNM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef UDPNM_POSTBUILD_VARIANT_SUPPORT
#define UDPNM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif
 

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  UdpNmPCDataSwitches  UdpNm Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define UDPNM_CHANNELCONFIG                                                                         STD_ON
#define UDPNM_ACTIVEWAKEUPBITENABLEDOFCHANNELCONFIG                                                 STD_ON
#define UDPNM_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG                                                   STD_ON
#define UDPNM_CARWAKEUPBITMASKOFCHANNELCONFIG                                                       STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CarWakeUpBitMask' Reason: 'CarWupRx is disabled' */
#define UDPNM_CARWAKEUPBYTEPOSITIONOFCHANNELCONFIG                                                  STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CarWakeUpBytePosition' Reason: 'CarWupRx is disabled' */
#define UDPNM_CARWAKEUPFILTERENABLEDOFCHANNELCONFIG                                                 STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CarWakeUpFilterEnabled' Reason: 'CarWupFilterFeature is disabled' */
#define UDPNM_CARWAKEUPFILTERNODEIDOFCHANNELCONFIG                                                  STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CarWakeUpFilterNodeId' Reason: 'CarWupFilterFeature is disabled' */
#define UDPNM_CARWAKEUPRXENABLEDOFCHANNELCONFIG                                                     STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CarWakeUpRxEnabled' Reason: 'CarWupRx is disabled' */
#define UDPNM_CHANNELIDOFCHANNELCONFIG                                                              STD_ON
#define UDPNM_COMCONTROLENABLEDOFCHANNELCONFIG                                                      STD_ON
#define UDPNM_CRIBITALWAYSENABLEDOFCHANNELCONFIG                                                    STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.CriBitAlwaysEnabled' Reason: 'the value of UdpNm_CriBitAlwaysEnabledOfChannelConfig is always 'false' due to this, the array is deactivated.' */
#define UDPNM_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG                                                   STD_ON
#define UDPNM_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG                                               STD_ON
#define UDPNM_IMMEDIATERESTARTENABLEDOFCHANNELCONFIG                                                STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.ImmediateRestartEnabled' Reason: 'ImmediateRestart is disabled' */
#define UDPNM_MSGCYCLETIMEOFCHANNELCONFIG                                                           STD_ON
#define UDPNM_MSGTIMEOUTTIMEOFCHANNELCONFIG                                                         STD_ON
#define UDPNM_NODEDETECTIONENABLEDOFCHANNELCONFIG                                                   STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.NodeDetectionEnabled' Reason: 'NodeDetection is disabled' */
#define UDPNM_NODEIDENABLEDOFCHANNELCONFIG                                                          STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.NodeIdEnabled' Reason: 'NodeId is disabled' */
#define UDPNM_PDUCBVPOSITIONOFCHANNELCONFIG                                                         STD_ON
#define UDPNM_PDUNIDPOSITIONOFCHANNELCONFIG                                                         STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.PduNidPosition' Reason: 'No channel has a configured Node Id Position' */
#define UDPNM_PNERACALCENABLEDOFCHANNELCONFIG                                                       STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.PnEraCalcEnabled' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PNERARXPDUIDOFCHANNELCONFIG                                                           STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.PnEraRxPduId' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG                                         STD_ON
#define UDPNM_REMOTESLEEPINDTIMEOFCHANNELCONFIG                                                     STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.RemoteSleepIndTime' Reason: 'RemoteSleepIndEnabled is disabled' */
#define UDPNM_REPEATMESSAGETIMEOFCHANNELCONFIG                                                      STD_ON
#define UDPNM_REPEATMSGINDENABLEDOFCHANNELCONFIG                                                    STD_OFF  /**< Deactivateable: 'UdpNm_ChannelConfig.RepeatMsgIndEnabled' Reason: 'the value of UdpNm_RepeatMsgIndEnabledOfChannelConfig is always 'false' due to this, the array is deactivated.' */
#define UDPNM_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG                                               STD_ON
#define UDPNM_TIMEOUTTIMEOFCHANNELCONFIG                                                            STD_ON
#define UDPNM_WAITBUSSLEEPTIMEOFCHANNELCONFIG                                                       STD_ON
#define UDPNM_COMMSTATE                                                                             STD_ON
#define UDPNM_COORDREADYTOSLEEPSTATE                                                                STD_ON
#define UDPNM_FINALMAGICNUMBER                                                                      STD_OFF  /**< Deactivateable: 'UdpNm_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define UDPNM_GENERATORCOMPATIBILITYVERSION                                                         STD_OFF  /**< Deactivateable: 'UdpNm_GeneratorCompatibilityVersion' Reason: 'Variant is not VARIANT-POST-BUILD-LOADABLE' */
#define UDPNM_IMMEDIATENMMSGCOUNT                                                                   STD_ON
#define UDPNM_IMMEDIATERESTARTFAILEDFLAG                                                            STD_OFF  /**< Deactivateable: 'UdpNm_ImmediateRestartFailedFlag' Reason: 'ImmediateRestart is disabled' */
#define UDPNM_INITDATAHASHCODE                                                                      STD_OFF  /**< Deactivateable: 'UdpNm_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define UDPNM_MODULEINITIALIZED                                                                     STD_ON
#define UDPNM_MSGCONFIRMATIONFLAG                                                                   STD_ON
#define UDPNM_MSGINDICATIONFLAG                                                                     STD_ON
#define UDPNM_MSGREQUEST                                                                            STD_ON
#define UDPNM_MSGTIMEOUTTIMER                                                                       STD_ON
#define UDPNM_MSGTIMER                                                                              STD_ON
#define UDPNM_NETWORKRESTARTFLAG                                                                    STD_ON
#define UDPNM_NMSTATE                                                                               STD_ON
#define UDPNM_PBCHANNELCONFIG                                                                       STD_ON
#define UDPNM_ALLOWTRIGGEREDMSGTRANSMISSIONOFPBCHANNELCONFIG                                        STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.AllowTriggeredMsgTransmission' Reason: 'the value of UdpNm_AllowTriggeredMsgTransmissionOfPbChannelConfig is always 'false' due to this, the array is deactivated.' */
#define UDPNM_MSGCYCLEOFFSETOFPBCHANNELCONFIG                                                       STD_ON
#define UDPNM_NODEIDOFPBCHANNELCONFIG                                                               STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.NodeId' Reason: 'NodeId is disabled' */
#define UDPNM_PNENABLEDOFPBCHANNELCONFIG                                                            STD_ON
#define UDPNM_PNRESETTIMEOFPBCHANNELCONFIG                                                          STD_ON
#define UDPNM_RXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                                                  STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageDataEndIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATALENGTHOFPBCHANNELCONFIG                                                  STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageDataLength' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                                                STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageDataStartIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATAUSEDOFPBCHANNELCONFIG                                                    STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageDataUsed' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_CBVIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                                                STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_CBVUsed' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_CARWAKEUPBYTEIDXOFPBCHANNELCONFIG                                       STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_CarWakeUpByteIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_CARWAKEUPBYTEUSEDOFPBCHANNELCONFIG                                      STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_CarWakeUpByteUsed' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_NIDIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG                                                STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_NIDUsed' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG                                         STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_UserDataEndIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG                                         STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_UserDataLength' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG                                       STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_UserDataStartIdx' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_RXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG                                           STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.RxMessageData_UserDataUsed' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                                                  STD_ON
#define UDPNM_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG                                                  STD_ON
#define UDPNM_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                                                STD_ON
#define UDPNM_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                                                    STD_ON
#define UDPNM_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                                                 STD_ON
#define UDPNM_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                                                STD_ON
#define UDPNM_TXMESSAGEDATA_NIDIDXOFPBCHANNELCONFIG                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.TxMessageData_NIDIdx' Reason: 'the optional indirection is deactivated because TxMessageData_NIDUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define UDPNM_TXMESSAGEDATA_NIDUSEDOFPBCHANNELCONFIG                                                STD_OFF  /**< Deactivateable: 'UdpNm_PbChannelConfig.TxMessageData_NIDUsed' Reason: 'the optional indirection is deactivated because TxMessageData_NIDUsedOfPbChannelConfig is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define UDPNM_TXMESSAGEDATA_PNFILTERMASKENDIDXOFPBCHANNELCONFIG                                     STD_ON
#define UDPNM_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG                                   STD_ON
#define UDPNM_TXMESSAGEDATA_PNFILTERMASKUSEDOFPBCHANNELCONFIG                                       STD_ON
#define UDPNM_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG                                         STD_ON
#define UDPNM_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG                                         STD_ON
#define UDPNM_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG                                       STD_ON
#define UDPNM_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG                                           STD_ON
#define UDPNM_TXPDUIDOFPBCHANNELCONFIG                                                              STD_ON
#define UDPNM_TXUSERDATAPDUIDOFPBCHANNELCONFIG                                                      STD_ON
#define UDPNM_PBPNCCLUSTERCONFIGEXT                                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PbPncClusterConfigExt' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PDUIDTOCHINDEX                                                                        STD_OFF  /**< Deactivateable: 'UdpNm_PduIdToChIndex' Reason: 'PB-S is not active or channel reference is invariant over all channels' */
#define UDPNM_PNCLUSTERREQ                                                                          STD_ON
#define UDPNM_PNCLUSTERREQEXT                                                                       STD_OFF  /**< Deactivateable: 'UdpNm_PnClusterReqExt' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PNCLUSTERREQEXTNEW                                                                    STD_OFF  /**< Deactivateable: 'UdpNm_PnClusterReqExtNew' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PNCLUSTERREQNEW                                                                       STD_ON
#define UDPNM_PNCLUSTERRESETTIMER                                                                   STD_ON
#define UDPNM_PNCLUSTERRESETTIMEREXT                                                                STD_OFF  /**< Deactivateable: 'UdpNm_PnClusterResetTimerExt' Reason: 'EraCalcFeature is disabled' */
#define UDPNM_PNEIRACALCENABLED                                                                     STD_ON
#define UDPNM_PNEIRARXPDUID                                                                         STD_ON
#define UDPNM_PNENABLEDINVARIANT                                                                    STD_ON
#define UDPNM_PNINFOBYTECONFIG                                                                      STD_ON
#define UDPNM_PNCLUSTERRESETTIMERENDIDXOFPNINFOBYTECONFIG                                           STD_ON
#define UDPNM_PNCLUSTERRESETTIMERSTARTIDXOFPNINFOBYTECONFIG                                         STD_ON
#define UDPNM_PNCLUSTERRESETTIMERUSEDOFPNINFOBYTECONFIG                                             STD_ON
#define UDPNM_PNFILTERMASKOFPNINFOBYTECONFIG                                                        STD_ON
#define UDPNM_PNINFOLENGTH                                                                          STD_ON
#define UDPNM_PNINFOOFFSET                                                                          STD_ON
#define UDPNM_REMOTESLEEPINDSTATE                                                                   STD_OFF  /**< Deactivateable: 'UdpNm_RemoteSleepIndState' Reason: 'RemoteSleepIndEnabled is disabled' */
#define UDPNM_REMOTESLEEPTIMER                                                                      STD_OFF  /**< Deactivateable: 'UdpNm_RemoteSleepTimer' Reason: 'RemoteSleepIndEnabled is disabled' */
#define UDPNM_REPEATMSGBITINDFLAG                                                                   STD_OFF  /**< Deactivateable: 'UdpNm_RepeatMsgBitIndFlag' Reason: 'NodeDetection is disabled' */
#define UDPNM_REPEATMSGREQFLAG                                                                      STD_OFF  /**< Deactivateable: 'UdpNm_RepeatMsgReqFlag' Reason: 'NodeDetection is disabled' */
#define UDPNM_REPEATMSGTIMER                                                                        STD_ON
#define UDPNM_RETRYFIRSTMESSAGEREQUESTFLAG                                                          STD_ON
#define UDPNM_RXMESSAGEDATA                                                                         STD_OFF  /**< Deactivateable: 'UdpNm_RxMessageData' Reason: 'RxMessageDataBuffer is disabled' */
#define UDPNM_SIZEOFCHANNELCONFIG                                                                   STD_ON
#define UDPNM_SIZEOFCOMMSTATE                                                                       STD_ON
#define UDPNM_SIZEOFCOORDREADYTOSLEEPSTATE                                                          STD_ON
#define UDPNM_SIZEOFIMMEDIATENMMSGCOUNT                                                             STD_ON
#define UDPNM_SIZEOFMSGCONFIRMATIONFLAG                                                             STD_ON
#define UDPNM_SIZEOFMSGINDICATIONFLAG                                                               STD_ON
#define UDPNM_SIZEOFMSGREQUEST                                                                      STD_ON
#define UDPNM_SIZEOFMSGTIMEOUTTIMER                                                                 STD_ON
#define UDPNM_SIZEOFMSGTIMER                                                                        STD_ON
#define UDPNM_SIZEOFNETWORKRESTARTFLAG                                                              STD_ON
#define UDPNM_SIZEOFNMSTATE                                                                         STD_ON
#define UDPNM_SIZEOFPBCHANNELCONFIG                                                                 STD_ON
#define UDPNM_SIZEOFPNCLUSTERREQ                                                                    STD_ON
#define UDPNM_SIZEOFPNCLUSTERREQNEW                                                                 STD_ON
#define UDPNM_SIZEOFPNINFOBYTECONFIG                                                                STD_ON
#define UDPNM_SIZEOFREPEATMSGTIMER                                                                  STD_ON
#define UDPNM_SIZEOFRETRYFIRSTMESSAGEREQUESTFLAG                                                    STD_ON
#define UDPNM_SIZEOFSYSTONMCHIND                                                                    STD_ON
#define UDPNM_SIZEOFTIMEOUTTIMER                                                                    STD_ON
#define UDPNM_SIZEOFTXCONTROLSTATE                                                                  STD_ON
#define UDPNM_SIZEOFTXCONTROLSTATEREQUEST                                                           STD_ON
#define UDPNM_SIZEOFTXMESSAGEDATA                                                                   STD_ON
#define UDPNM_SIZEOFWAITBUSSLEEPTIMER                                                               STD_ON
#define UDPNM_SYSTONMCHIND                                                                          STD_ON
#define UDPNM_TIMEOUTTIMER                                                                          STD_ON
#define UDPNM_TXCONTROLSTATE                                                                        STD_ON
#define UDPNM_TXCONTROLSTATEREQUEST                                                                 STD_ON
#define UDPNM_TXMESSAGEDATA                                                                         STD_ON
#define UDPNM_WAITBUSSLEEPTIMER                                                                     STD_ON
#define UDPNM_PCCONFIG                                                                              STD_ON
#define UDPNM_CHANNELCONFIGOFPCCONFIG                                                               STD_ON
#define UDPNM_COMMSTATEOFPCCONFIG                                                                   STD_ON
#define UDPNM_COORDREADYTOSLEEPSTATEOFPCCONFIG                                                      STD_ON
#define UDPNM_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'UdpNm_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define UDPNM_GENERATORCOMPATIBILITYVERSIONOFPCCONFIG                                               STD_OFF  /**< Deactivateable: 'UdpNm_PCConfig.GeneratorCompatibilityVersion' Reason: 'Variant is not VARIANT-POST-BUILD-LOADABLE' */
#define UDPNM_IMMEDIATENMMSGCOUNTOFPCCONFIG                                                         STD_ON
#define UDPNM_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'UdpNm_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define UDPNM_MODULEINITIALIZEDOFPCCONFIG                                                           STD_ON
#define UDPNM_MSGCONFIRMATIONFLAGOFPCCONFIG                                                         STD_ON
#define UDPNM_MSGINDICATIONFLAGOFPCCONFIG                                                           STD_ON
#define UDPNM_MSGREQUESTOFPCCONFIG                                                                  STD_ON
#define UDPNM_MSGTIMEOUTTIMEROFPCCONFIG                                                             STD_ON
#define UDPNM_MSGTIMEROFPCCONFIG                                                                    STD_ON
#define UDPNM_NETWORKRESTARTFLAGOFPCCONFIG                                                          STD_ON
#define UDPNM_NMSTATEOFPCCONFIG                                                                     STD_ON
#define UDPNM_PBCHANNELCONFIGOFPCCONFIG                                                             STD_ON
#define UDPNM_PNCLUSTERREQNEWOFPCCONFIG                                                             STD_ON
#define UDPNM_PNCLUSTERREQOFPCCONFIG                                                                STD_ON
#define UDPNM_PNCLUSTERRESETTIMEROFPCCONFIG                                                         STD_ON
#define UDPNM_PNEIRACALCENABLEDOFPCCONFIG                                                           STD_ON
#define UDPNM_PNEIRARXPDUIDOFPCCONFIG                                                               STD_ON
#define UDPNM_PNENABLEDINVARIANTOFPCCONFIG                                                          STD_ON
#define UDPNM_PNINFOBYTECONFIGOFPCCONFIG                                                            STD_ON
#define UDPNM_PNINFOLENGTHOFPCCONFIG                                                                STD_ON
#define UDPNM_PNINFOOFFSETOFPCCONFIG                                                                STD_ON
#define UDPNM_REPEATMSGTIMEROFPCCONFIG                                                              STD_ON
#define UDPNM_RETRYFIRSTMESSAGEREQUESTFLAGOFPCCONFIG                                                STD_ON
#define UDPNM_SIZEOFCHANNELCONFIGOFPCCONFIG                                                         STD_ON
#define UDPNM_SIZEOFCOMMSTATEOFPCCONFIG                                                             STD_ON
#define UDPNM_SIZEOFCOORDREADYTOSLEEPSTATEOFPCCONFIG                                                STD_ON
#define UDPNM_SIZEOFIMMEDIATENMMSGCOUNTOFPCCONFIG                                                   STD_ON
#define UDPNM_SIZEOFMSGCONFIRMATIONFLAGOFPCCONFIG                                                   STD_ON
#define UDPNM_SIZEOFMSGINDICATIONFLAGOFPCCONFIG                                                     STD_ON
#define UDPNM_SIZEOFMSGREQUESTOFPCCONFIG                                                            STD_ON
#define UDPNM_SIZEOFMSGTIMEOUTTIMEROFPCCONFIG                                                       STD_ON
#define UDPNM_SIZEOFMSGTIMEROFPCCONFIG                                                              STD_ON
#define UDPNM_SIZEOFNETWORKRESTARTFLAGOFPCCONFIG                                                    STD_ON
#define UDPNM_SIZEOFNMSTATEOFPCCONFIG                                                               STD_ON
#define UDPNM_SIZEOFPBCHANNELCONFIGOFPCCONFIG                                                       STD_ON
#define UDPNM_SIZEOFPNCLUSTERREQNEWOFPCCONFIG                                                       STD_ON
#define UDPNM_SIZEOFPNCLUSTERREQOFPCCONFIG                                                          STD_ON
#define UDPNM_SIZEOFPNINFOBYTECONFIGOFPCCONFIG                                                      STD_ON
#define UDPNM_SIZEOFREPEATMSGTIMEROFPCCONFIG                                                        STD_ON
#define UDPNM_SIZEOFRETRYFIRSTMESSAGEREQUESTFLAGOFPCCONFIG                                          STD_ON
#define UDPNM_SIZEOFSYSTONMCHINDOFPCCONFIG                                                          STD_ON
#define UDPNM_SIZEOFTIMEOUTTIMEROFPCCONFIG                                                          STD_ON
#define UDPNM_SIZEOFTXCONTROLSTATEOFPCCONFIG                                                        STD_ON
#define UDPNM_SIZEOFTXCONTROLSTATEREQUESTOFPCCONFIG                                                 STD_ON
#define UDPNM_SIZEOFTXMESSAGEDATAOFPCCONFIG                                                         STD_ON
#define UDPNM_SIZEOFWAITBUSSLEEPTIMEROFPCCONFIG                                                     STD_ON
#define UDPNM_SYSTONMCHINDOFPCCONFIG                                                                STD_ON
#define UDPNM_TIMEOUTTIMEROFPCCONFIG                                                                STD_ON
#define UDPNM_TXCONTROLSTATEOFPCCONFIG                                                              STD_ON
#define UDPNM_TXCONTROLSTATEREQUESTOFPCCONFIG                                                       STD_ON
#define UDPNM_TXMESSAGEDATAOFPCCONFIG                                                               STD_ON
#define UDPNM_WAITBUSSLEEPTIMEROFPCCONFIG                                                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCMinNumericValueDefines  UdpNm Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define UDPNM_MIN_COMMSTATE                                                                         0u
#define UDPNM_MIN_COORDREADYTOSLEEPSTATE                                                            0u
#define UDPNM_MIN_IMMEDIATENMMSGCOUNT                                                               0u
#define UDPNM_MIN_MSGREQUEST                                                                        0u
#define UDPNM_MIN_MSGTIMEOUTTIMER                                                                   0u
#define UDPNM_MIN_MSGTIMER                                                                          0u
#define UDPNM_MIN_NETWORKRESTARTFLAG                                                                0u
#define UDPNM_MIN_NMSTATE                                                                           0u
#define UDPNM_MIN_PNCLUSTERREQ                                                                      0u
#define UDPNM_MIN_PNCLUSTERREQNEW                                                                   0u
#define UDPNM_MIN_PNCLUSTERRESETTIMER                                                               0u
#define UDPNM_MIN_REPEATMSGTIMER                                                                    0u
#define UDPNM_MIN_TIMEOUTTIMER                                                                      0u
#define UDPNM_MIN_TXCONTROLSTATE                                                                    0u
#define UDPNM_MIN_TXCONTROLSTATEREQUEST                                                             0u
#define UDPNM_MIN_TXMESSAGEDATA                                                                     0u
#define UDPNM_MIN_WAITBUSSLEEPTIMER                                                                 0u
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCMaxNumericValueDefines  UdpNm Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define UDPNM_MAX_COMMSTATE                                                                         255u
#define UDPNM_MAX_COORDREADYTOSLEEPSTATE                                                            255u
#define UDPNM_MAX_IMMEDIATENMMSGCOUNT                                                               255u
#define UDPNM_MAX_MSGREQUEST                                                                        255u
#define UDPNM_MAX_MSGTIMEOUTTIMER                                                                   65535u
#define UDPNM_MAX_MSGTIMER                                                                          65535u
#define UDPNM_MAX_NETWORKRESTARTFLAG                                                                255u
#define UDPNM_MAX_NMSTATE                                                                           255u
#define UDPNM_MAX_PNCLUSTERREQ                                                                      255u
#define UDPNM_MAX_PNCLUSTERREQNEW                                                                   255u
#define UDPNM_MAX_PNCLUSTERRESETTIMER                                                               65535u
#define UDPNM_MAX_REPEATMSGTIMER                                                                    65535u
#define UDPNM_MAX_TIMEOUTTIMER                                                                      65535u
#define UDPNM_MAX_TXCONTROLSTATE                                                                    255u
#define UDPNM_MAX_TXCONTROLSTATEREQUEST                                                             255u
#define UDPNM_MAX_TXMESSAGEDATA                                                                     255u
#define UDPNM_MAX_WAITBUSSLEEPTIMER                                                                 4294967295u
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCNoReferenceDefines  UdpNm No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define UDPNM_NO_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                                               255u
#define UDPNM_NO_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                                             255u
#define UDPNM_NO_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                                              255u
#define UDPNM_NO_TXMESSAGEDATA_PNFILTERMASKENDIDXOFPBCHANNELCONFIG                                  255u
#define UDPNM_NO_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG                                255u
#define UDPNM_NO_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG                                      255u
#define UDPNM_NO_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG                                    255u
#define UDPNM_NO_TXPDUIDOFPBCHANNELCONFIG                                                           255u
#define UDPNM_NO_TXUSERDATAPDUIDOFPBCHANNELCONFIG                                                   255u
#define UDPNM_NO_PNCLUSTERRESETTIMERENDIDXOFPNINFOBYTECONFIG                                        255u
#define UDPNM_NO_PNCLUSTERRESETTIMERSTARTIDXOFPNINFOBYTECONFIG                                      255u
#define UDPNM_NO_SYSTONMCHIND                                                                       255u
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCIsReducedToDefineDefines  UdpNm Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define UDPNM_ISDEF_ACTIVEWAKEUPBITENABLEDOFCHANNELCONFIG                                           STD_OFF
#define UDPNM_ISDEF_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG                                             STD_OFF
#define UDPNM_ISDEF_CHANNELIDOFCHANNELCONFIG                                                        STD_OFF
#define UDPNM_ISDEF_COMCONTROLENABLEDOFCHANNELCONFIG                                                STD_OFF
#define UDPNM_ISDEF_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG                                             STD_OFF
#define UDPNM_ISDEF_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG                                         STD_OFF
#define UDPNM_ISDEF_MSGCYCLETIMEOFCHANNELCONFIG                                                     STD_OFF
#define UDPNM_ISDEF_MSGTIMEOUTTIMEOFCHANNELCONFIG                                                   STD_OFF
#define UDPNM_ISDEF_PDUCBVPOSITIONOFCHANNELCONFIG                                                   STD_OFF
#define UDPNM_ISDEF_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG                                   STD_OFF
#define UDPNM_ISDEF_REPEATMESSAGETIMEOFCHANNELCONFIG                                                STD_OFF
#define UDPNM_ISDEF_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG                                         STD_OFF
#define UDPNM_ISDEF_TIMEOUTTIMEOFCHANNELCONFIG                                                      STD_OFF
#define UDPNM_ISDEF_WAITBUSSLEEPTIMEOFCHANNELCONFIG                                                 STD_OFF
#define UDPNM_ISDEF_MSGCYCLEOFFSETOFPBCHANNELCONFIG                                                 STD_OFF
#define UDPNM_ISDEF_PNENABLEDOFPBCHANNELCONFIG                                                      STD_OFF
#define UDPNM_ISDEF_PNRESETTIMEOFPBCHANNELCONFIG                                                    STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                                            STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG                                            STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                                          STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                                              STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                                           STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                                          STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_PNFILTERMASKENDIDXOFPBCHANNELCONFIG                               STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG                             STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_PNFILTERMASKUSEDOFPBCHANNELCONFIG                                 STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG                                   STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG                                   STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG                                 STD_OFF
#define UDPNM_ISDEF_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG                                     STD_OFF
#define UDPNM_ISDEF_TXPDUIDOFPBCHANNELCONFIG                                                        STD_OFF
#define UDPNM_ISDEF_TXUSERDATAPDUIDOFPBCHANNELCONFIG                                                STD_OFF
#define UDPNM_ISDEF_PNCLUSTERRESETTIMERENDIDXOFPNINFOBYTECONFIG                                     STD_OFF
#define UDPNM_ISDEF_PNCLUSTERRESETTIMERSTARTIDXOFPNINFOBYTECONFIG                                   STD_OFF
#define UDPNM_ISDEF_PNCLUSTERRESETTIMERUSEDOFPNINFOBYTECONFIG                                       STD_OFF
#define UDPNM_ISDEF_PNFILTERMASKOFPNINFOBYTECONFIG                                                  STD_OFF
#define UDPNM_ISDEF_SYSTONMCHIND                                                                    STD_OFF
#define UDPNM_ISDEF_CHANNELCONFIGOFPCCONFIG                                                         STD_ON
#define UDPNM_ISDEF_COMMSTATEOFPCCONFIG                                                             STD_ON
#define UDPNM_ISDEF_COORDREADYTOSLEEPSTATEOFPCCONFIG                                                STD_ON
#define UDPNM_ISDEF_IMMEDIATENMMSGCOUNTOFPCCONFIG                                                   STD_ON
#define UDPNM_ISDEF_MODULEINITIALIZEDOFPCCONFIG                                                     STD_ON
#define UDPNM_ISDEF_MSGCONFIRMATIONFLAGOFPCCONFIG                                                   STD_ON
#define UDPNM_ISDEF_MSGINDICATIONFLAGOFPCCONFIG                                                     STD_ON
#define UDPNM_ISDEF_MSGREQUESTOFPCCONFIG                                                            STD_ON
#define UDPNM_ISDEF_MSGTIMEOUTTIMEROFPCCONFIG                                                       STD_ON
#define UDPNM_ISDEF_MSGTIMEROFPCCONFIG                                                              STD_ON
#define UDPNM_ISDEF_NETWORKRESTARTFLAGOFPCCONFIG                                                    STD_ON
#define UDPNM_ISDEF_NMSTATEOFPCCONFIG                                                               STD_ON
#define UDPNM_ISDEF_PBCHANNELCONFIGOFPCCONFIG                                                       STD_ON
#define UDPNM_ISDEF_PNCLUSTERREQNEWOFPCCONFIG                                                       STD_ON
#define UDPNM_ISDEF_PNCLUSTERREQOFPCCONFIG                                                          STD_ON
#define UDPNM_ISDEF_PNCLUSTERRESETTIMEROFPCCONFIG                                                   STD_ON
#define UDPNM_ISDEF_PNINFOBYTECONFIGOFPCCONFIG                                                      STD_ON
#define UDPNM_ISDEF_REPEATMSGTIMEROFPCCONFIG                                                        STD_ON
#define UDPNM_ISDEF_RETRYFIRSTMESSAGEREQUESTFLAGOFPCCONFIG                                          STD_ON
#define UDPNM_ISDEF_SYSTONMCHINDOFPCCONFIG                                                          STD_ON
#define UDPNM_ISDEF_TIMEOUTTIMEROFPCCONFIG                                                          STD_ON
#define UDPNM_ISDEF_TXCONTROLSTATEOFPCCONFIG                                                        STD_ON
#define UDPNM_ISDEF_TXCONTROLSTATEREQUESTOFPCCONFIG                                                 STD_ON
#define UDPNM_ISDEF_TXMESSAGEDATAOFPCCONFIG                                                         STD_ON
#define UDPNM_ISDEF_WAITBUSSLEEPTIMEROFPCCONFIG                                                     STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCEqualsAlwaysToDefines  UdpNm Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define UDPNM_EQ2_ACTIVEWAKEUPBITENABLEDOFCHANNELCONFIG                                             
#define UDPNM_EQ2_ALLMESSAGESKEEPAWAKEOFCHANNELCONFIG                                               
#define UDPNM_EQ2_CHANNELIDOFCHANNELCONFIG                                                          
#define UDPNM_EQ2_COMCONTROLENABLEDOFCHANNELCONFIG                                                  
#define UDPNM_EQ2_IMMEDIATENMCYCLETIMEOFCHANNELCONFIG                                               
#define UDPNM_EQ2_IMMEDIATENMTRANSMISSIONSOFCHANNELCONFIG                                           
#define UDPNM_EQ2_MSGCYCLETIMEOFCHANNELCONFIG                                                       
#define UDPNM_EQ2_MSGTIMEOUTTIMEOFCHANNELCONFIG                                                     
#define UDPNM_EQ2_PDUCBVPOSITIONOFCHANNELCONFIG                                                     
#define UDPNM_EQ2_PNHANDLEMULTIPLENETWORKREQUESTOFCHANNELCONFIG                                     
#define UDPNM_EQ2_REPEATMESSAGETIMEOFCHANNELCONFIG                                                  
#define UDPNM_EQ2_RETRYFIRSTMESSAGEREQUESTOFCHANNELCONFIG                                           
#define UDPNM_EQ2_TIMEOUTTIMEOFCHANNELCONFIG                                                        
#define UDPNM_EQ2_WAITBUSSLEEPTIMEOFCHANNELCONFIG                                                   
#define UDPNM_EQ2_MSGCYCLEOFFSETOFPBCHANNELCONFIG                                                   
#define UDPNM_EQ2_PNENABLEDOFPBCHANNELCONFIG                                                        
#define UDPNM_EQ2_PNRESETTIMEOFPBCHANNELCONFIG                                                      
#define UDPNM_EQ2_TXMESSAGEDATAENDIDXOFPBCHANNELCONFIG                                              
#define UDPNM_EQ2_TXMESSAGEDATALENGTHOFPBCHANNELCONFIG                                              
#define UDPNM_EQ2_TXMESSAGEDATASTARTIDXOFPBCHANNELCONFIG                                            
#define UDPNM_EQ2_TXMESSAGEDATAUSEDOFPBCHANNELCONFIG                                                
#define UDPNM_EQ2_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG                                             
#define UDPNM_EQ2_TXMESSAGEDATA_CBVUSEDOFPBCHANNELCONFIG                                            
#define UDPNM_EQ2_TXMESSAGEDATA_PNFILTERMASKENDIDXOFPBCHANNELCONFIG                                 
#define UDPNM_EQ2_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG                               
#define UDPNM_EQ2_TXMESSAGEDATA_PNFILTERMASKUSEDOFPBCHANNELCONFIG                                   
#define UDPNM_EQ2_TXMESSAGEDATA_USERDATAENDIDXOFPBCHANNELCONFIG                                     
#define UDPNM_EQ2_TXMESSAGEDATA_USERDATALENGTHOFPBCHANNELCONFIG                                     
#define UDPNM_EQ2_TXMESSAGEDATA_USERDATASTARTIDXOFPBCHANNELCONFIG                                   
#define UDPNM_EQ2_TXMESSAGEDATA_USERDATAUSEDOFPBCHANNELCONFIG                                       
#define UDPNM_EQ2_TXPDUIDOFPBCHANNELCONFIG                                                          
#define UDPNM_EQ2_TXUSERDATAPDUIDOFPBCHANNELCONFIG                                                  
#define UDPNM_EQ2_PNCLUSTERRESETTIMERENDIDXOFPNINFOBYTECONFIG                                       
#define UDPNM_EQ2_PNCLUSTERRESETTIMERSTARTIDXOFPNINFOBYTECONFIG                                     
#define UDPNM_EQ2_PNCLUSTERRESETTIMERUSEDOFPNINFOBYTECONFIG                                         
#define UDPNM_EQ2_PNFILTERMASKOFPNINFOBYTECONFIG                                                    
#define UDPNM_EQ2_SYSTONMCHIND                                                                      
#define UDPNM_EQ2_CHANNELCONFIGOFPCCONFIG                                                           UdpNm_ChannelConfig
#define UDPNM_EQ2_COMMSTATEOFPCCONFIG                                                               UdpNm_CommState.raw
#define UDPNM_EQ2_COORDREADYTOSLEEPSTATEOFPCCONFIG                                                  UdpNm_CoordReadyToSleepState.raw
#define UDPNM_EQ2_IMMEDIATENMMSGCOUNTOFPCCONFIG                                                     UdpNm_ImmediateNmMsgCount.raw
#define UDPNM_EQ2_MODULEINITIALIZEDOFPCCONFIG                                                       (&(UdpNm_ModuleInitialized))
#define UDPNM_EQ2_MSGCONFIRMATIONFLAGOFPCCONFIG                                                     UdpNm_MsgConfirmationFlag.raw
#define UDPNM_EQ2_MSGINDICATIONFLAGOFPCCONFIG                                                       UdpNm_MsgIndicationFlag.raw
#define UDPNM_EQ2_MSGREQUESTOFPCCONFIG                                                              UdpNm_MsgRequest.raw
#define UDPNM_EQ2_MSGTIMEOUTTIMEROFPCCONFIG                                                         UdpNm_MsgTimeoutTimer.raw
#define UDPNM_EQ2_MSGTIMEROFPCCONFIG                                                                UdpNm_MsgTimer.raw
#define UDPNM_EQ2_NETWORKRESTARTFLAGOFPCCONFIG                                                      UdpNm_NetworkRestartFlag.raw
#define UDPNM_EQ2_NMSTATEOFPCCONFIG                                                                 UdpNm_NmState.raw
#define UDPNM_EQ2_PBCHANNELCONFIGOFPCCONFIG                                                         UdpNm_PbChannelConfig
#define UDPNM_EQ2_PNCLUSTERREQNEWOFPCCONFIG                                                         UdpNm_PnClusterReqNew.raw
#define UDPNM_EQ2_PNCLUSTERREQOFPCCONFIG                                                            UdpNm_PnClusterReq.raw
#define UDPNM_EQ2_PNCLUSTERRESETTIMEROFPCCONFIG                                                     UdpNm_PnClusterResetTimer.raw
#define UDPNM_EQ2_PNINFOBYTECONFIGOFPCCONFIG                                                        UdpNm_PnInfoByteConfig
#define UDPNM_EQ2_REPEATMSGTIMEROFPCCONFIG                                                          UdpNm_RepeatMsgTimer.raw
#define UDPNM_EQ2_RETRYFIRSTMESSAGEREQUESTFLAGOFPCCONFIG                                            UdpNm_RetryFirstMessageRequestFlag.raw
#define UDPNM_EQ2_SYSTONMCHINDOFPCCONFIG                                                            UdpNm_SysToNmChInd
#define UDPNM_EQ2_TIMEOUTTIMEROFPCCONFIG                                                            UdpNm_TimeoutTimer.raw
#define UDPNM_EQ2_TXCONTROLSTATEOFPCCONFIG                                                          UdpNm_TxControlState.raw
#define UDPNM_EQ2_TXCONTROLSTATEREQUESTOFPCCONFIG                                                   UdpNm_TxControlStateRequest.raw
#define UDPNM_EQ2_TXMESSAGEDATAOFPCCONFIG                                                           UdpNm_TxMessageData
#define UDPNM_EQ2_WAITBUSSLEEPTIMEROFPCCONFIG                                                       UdpNm_WaitBusSleepTimer.raw
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCSymbolicInitializationPointers  UdpNm Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define UdpNm_Config_Ptr                                                                            NULL_PTR  /**< symbolic identifier which shall be used to initialize 'UdpNm' */
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCInitializationSymbols  UdpNm Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define UdpNm_Config                                                                                NULL_PTR  /**< symbolic identifier which could be used to initialize 'UdpNm */
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCGeneral  UdpNm General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define UDPNM_CHECK_INIT_POINTER                                                                    STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define UDPNM_FINAL_MAGIC_NUMBER                                                                    0x211Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of UdpNm */
#define UDPNM_INDIVIDUAL_POSTBUILD                                                                  STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'UdpNm' is not configured to be postbuild capable. */
#define UDPNM_INIT_DATA                                                                             UDPNM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define UDPNM_INIT_DATA_HASH_CODE                                                                   1834652678  /**< the precompile constant to validate the initialization structure at initialization time of UdpNm with a hashcode. The seed value is '0x211Eu' */
#define UDPNM_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define UDPNM_USE_INIT_POINTER                                                                      STD_OFF  /**< STD_ON if the init pointer UdpNm shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  UdpNmPBDataSwitches  UdpNm Data Switches  (POST_BUILD)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define UDPNM_PBCONFIG                                                                              STD_OFF  /**< Deactivateable: 'UdpNm_PBConfig' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define UDPNM_LTCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PBConfig.LTConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
#define UDPNM_PCCONFIGIDXOFPBCONFIG                                                                 STD_OFF  /**< Deactivateable: 'UdpNm_PBConfig.PCConfigIdx' Reason: 'the module configuration is VARIANT_PRE_COMPILE.' */
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
  \defgroup  UdpNmPCGetConstantDuplicatedRootDataMacros  UdpNm Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define UdpNm_GetChannelConfigOfPCConfig()                                                          UdpNm_ChannelConfig  /**< the pointer to UdpNm_ChannelConfig */
#define UdpNm_GetCommStateOfPCConfig()                                                              UdpNm_CommState.raw  /**< the pointer to UdpNm_CommState */
#define UdpNm_GetCoordReadyToSleepStateOfPCConfig()                                                 UdpNm_CoordReadyToSleepState.raw  /**< the pointer to UdpNm_CoordReadyToSleepState */
#define UdpNm_GetImmediateNmMsgCountOfPCConfig()                                                    UdpNm_ImmediateNmMsgCount.raw  /**< the pointer to UdpNm_ImmediateNmMsgCount */
#define UdpNm_GetModuleInitializedOfPCConfig()                                                      (&(UdpNm_ModuleInitialized))  /**< the pointer to UdpNm_ModuleInitialized */
#define UdpNm_GetMsgConfirmationFlagOfPCConfig()                                                    UdpNm_MsgConfirmationFlag.raw  /**< the pointer to UdpNm_MsgConfirmationFlag */
#define UdpNm_GetMsgIndicationFlagOfPCConfig()                                                      UdpNm_MsgIndicationFlag.raw  /**< the pointer to UdpNm_MsgIndicationFlag */
#define UdpNm_GetMsgRequestOfPCConfig()                                                             UdpNm_MsgRequest.raw  /**< the pointer to UdpNm_MsgRequest */
#define UdpNm_GetMsgTimeoutTimerOfPCConfig()                                                        UdpNm_MsgTimeoutTimer.raw  /**< the pointer to UdpNm_MsgTimeoutTimer */
#define UdpNm_GetMsgTimerOfPCConfig()                                                               UdpNm_MsgTimer.raw  /**< the pointer to UdpNm_MsgTimer */
#define UdpNm_GetNetworkRestartFlagOfPCConfig()                                                     UdpNm_NetworkRestartFlag.raw  /**< the pointer to UdpNm_NetworkRestartFlag */
#define UdpNm_GetNmStateOfPCConfig()                                                                UdpNm_NmState.raw  /**< the pointer to UdpNm_NmState */
#define UdpNm_GetPbChannelConfigOfPCConfig()                                                        UdpNm_PbChannelConfig  /**< the pointer to UdpNm_PbChannelConfig */
#define UdpNm_GetPnClusterReqNewOfPCConfig()                                                        UdpNm_PnClusterReqNew.raw  /**< the pointer to UdpNm_PnClusterReqNew */
#define UdpNm_GetPnClusterReqOfPCConfig()                                                           UdpNm_PnClusterReq.raw  /**< the pointer to UdpNm_PnClusterReq */
#define UdpNm_GetPnClusterResetTimerOfPCConfig()                                                    UdpNm_PnClusterResetTimer.raw  /**< the pointer to UdpNm_PnClusterResetTimer */
#define UdpNm_IsPnEiraCalcEnabledOfPCConfig()                                                       (((TRUE)) != FALSE)  /**< Determines if PN EIRA Calculation is active or not */
#define UdpNm_GetPnEiraRxPduIdOfPCConfig()                                                          PduRConf_PduRSrcPdu_PduRSrcPdu  /**< I-PDU handle of Com PDU for EIRA */
#define UdpNm_IsPnEnabledInVariantOfPCConfig()                                                      (((TRUE)) != FALSE)  /**< Partial Networking Enabled in this variant */
#define UdpNm_GetPnInfoByteConfigOfPCConfig()                                                       UdpNm_PnInfoByteConfig  /**< the pointer to UdpNm_PnInfoByteConfig */
#define UdpNm_GetPnInfoLengthOfPCConfig()                                                           7u  /**< PnInfoLength value */
#define UdpNm_GetPnInfoOffsetOfPCConfig()                                                           1u  /**< PnInfoOffset value */
#define UdpNm_GetRepeatMsgTimerOfPCConfig()                                                         UdpNm_RepeatMsgTimer.raw  /**< the pointer to UdpNm_RepeatMsgTimer */
#define UdpNm_GetRetryFirstMessageRequestFlagOfPCConfig()                                           UdpNm_RetryFirstMessageRequestFlag.raw  /**< the pointer to UdpNm_RetryFirstMessageRequestFlag */
#define UdpNm_GetSizeOfChannelConfigOfPCConfig()                                                    1u  /**< the number of accomplishable value elements in UdpNm_ChannelConfig */
#define UdpNm_GetSizeOfPbChannelConfigOfPCConfig()                                                  1u  /**< the number of accomplishable value elements in UdpNm_PbChannelConfig */
#define UdpNm_GetSizeOfPnInfoByteConfigOfPCConfig()                                                 7u  /**< the number of accomplishable value elements in UdpNm_PnInfoByteConfig */
#define UdpNm_GetSizeOfSysToNmChIndOfPCConfig()                                                     1u  /**< the number of accomplishable value elements in UdpNm_SysToNmChInd */
#define UdpNm_GetSizeOfTxMessageDataOfPCConfig()                                                    8u  /**< the number of accomplishable value elements in UdpNm_TxMessageData */
#define UdpNm_GetSysToNmChIndOfPCConfig()                                                           UdpNm_SysToNmChInd  /**< the pointer to UdpNm_SysToNmChInd */
#define UdpNm_GetTimeoutTimerOfPCConfig()                                                           UdpNm_TimeoutTimer.raw  /**< the pointer to UdpNm_TimeoutTimer */
#define UdpNm_GetTxControlStateOfPCConfig()                                                         UdpNm_TxControlState.raw  /**< the pointer to UdpNm_TxControlState */
#define UdpNm_GetTxControlStateRequestOfPCConfig()                                                  UdpNm_TxControlStateRequest.raw  /**< the pointer to UdpNm_TxControlStateRequest */
#define UdpNm_GetTxMessageDataOfPCConfig()                                                          UdpNm_TxMessageData  /**< the pointer to UdpNm_TxMessageData */
#define UdpNm_GetWaitBusSleepTimerOfPCConfig()                                                      UdpNm_WaitBusSleepTimer.raw  /**< the pointer to UdpNm_WaitBusSleepTimer */
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCGetDuplicatedRootDataMacros  UdpNm Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define UdpNm_GetSizeOfCommStateOfPCConfig()                                                        UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_CommState */
#define UdpNm_GetSizeOfCoordReadyToSleepStateOfPCConfig()                                           UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_CoordReadyToSleepState */
#define UdpNm_GetSizeOfImmediateNmMsgCountOfPCConfig()                                              UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_ImmediateNmMsgCount */
#define UdpNm_GetSizeOfMsgConfirmationFlagOfPCConfig()                                              UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_MsgConfirmationFlag */
#define UdpNm_GetSizeOfMsgIndicationFlagOfPCConfig()                                                UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_MsgIndicationFlag */
#define UdpNm_GetSizeOfMsgRequestOfPCConfig()                                                       UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_MsgRequest */
#define UdpNm_GetSizeOfMsgTimeoutTimerOfPCConfig()                                                  UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_MsgTimeoutTimer */
#define UdpNm_GetSizeOfMsgTimerOfPCConfig()                                                         UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_MsgTimer */
#define UdpNm_GetSizeOfNetworkRestartFlagOfPCConfig()                                               UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_NetworkRestartFlag */
#define UdpNm_GetSizeOfNmStateOfPCConfig()                                                          UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_NmState */
#define UdpNm_GetSizeOfPnClusterReqNewOfPCConfig()                                                  UdpNm_GetSizeOfPnInfoByteConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_PnClusterReqNew */
#define UdpNm_GetSizeOfPnClusterReqOfPCConfig()                                                     UdpNm_GetSizeOfPnInfoByteConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_PnClusterReq */
#define UdpNm_GetSizeOfRepeatMsgTimerOfPCConfig()                                                   UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_RepeatMsgTimer */
#define UdpNm_GetSizeOfRetryFirstMessageRequestFlagOfPCConfig()                                     UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_RetryFirstMessageRequestFlag */
#define UdpNm_GetSizeOfTimeoutTimerOfPCConfig()                                                     UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_TimeoutTimer */
#define UdpNm_GetSizeOfTxControlStateOfPCConfig()                                                   UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_TxControlState */
#define UdpNm_GetSizeOfTxControlStateRequestOfPCConfig()                                            UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_TxControlStateRequest */
#define UdpNm_GetSizeOfWaitBusSleepTimerOfPCConfig()                                                UdpNm_GetSizeOfChannelConfigOfPCConfig()  /**< the number of accomplishable value elements in UdpNm_WaitBusSleepTimer */
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCGetDataMacros  UdpNm Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define UdpNm_IsActiveWakeUpBitEnabledOfChannelConfig(Index)                                        ((UdpNm_GetChannelConfigOfPCConfig()[(Index)].ActiveWakeUpBitEnabledOfChannelConfig) != FALSE)
#define UdpNm_IsAllMessagesKeepAwakeOfChannelConfig(Index)                                          ((UdpNm_GetChannelConfigOfPCConfig()[(Index)].AllMessagesKeepAwakeOfChannelConfig) != FALSE)
#define UdpNm_GetChannelIdOfChannelConfig(Index)                                                    ((NetworkHandleType)UdpNm_GetChannelConfigOfPCConfig()[(Index)].ChannelIdOfChannelConfig)
#define UdpNm_IsComControlEnabledOfChannelConfig(Index)                                             ((UdpNm_GetChannelConfigOfPCConfig()[(Index)].ComControlEnabledOfChannelConfig) != FALSE)
#define UdpNm_GetImmediateNmCycleTimeOfChannelConfig(Index)                                         (UdpNm_GetChannelConfigOfPCConfig()[(Index)].ImmediateNmCycleTimeOfChannelConfig)
#define UdpNm_GetImmediateNmTransmissionsOfChannelConfig(Index)                                     (UdpNm_GetChannelConfigOfPCConfig()[(Index)].ImmediateNmTransmissionsOfChannelConfig)
#define UdpNm_GetMsgCycleTimeOfChannelConfig(Index)                                                 (UdpNm_GetChannelConfigOfPCConfig()[(Index)].MsgCycleTimeOfChannelConfig)
#define UdpNm_GetMsgTimeoutTimeOfChannelConfig(Index)                                               (UdpNm_GetChannelConfigOfPCConfig()[(Index)].MsgTimeoutTimeOfChannelConfig)
#define UdpNm_GetPduCbvPositionOfChannelConfig(Index)                                               (UdpNm_GetChannelConfigOfPCConfig()[(Index)].PduCbvPositionOfChannelConfig)
#define UdpNm_IsPnHandleMultipleNetworkRequestOfChannelConfig(Index)                                ((UdpNm_GetChannelConfigOfPCConfig()[(Index)].PnHandleMultipleNetworkRequestOfChannelConfig) != FALSE)
#define UdpNm_GetRepeatMessageTimeOfChannelConfig(Index)                                            (UdpNm_GetChannelConfigOfPCConfig()[(Index)].RepeatMessageTimeOfChannelConfig)
#define UdpNm_IsRetryFirstMessageRequestOfChannelConfig(Index)                                      ((UdpNm_GetChannelConfigOfPCConfig()[(Index)].RetryFirstMessageRequestOfChannelConfig) != FALSE)
#define UdpNm_GetTimeoutTimeOfChannelConfig(Index)                                                  (UdpNm_GetChannelConfigOfPCConfig()[(Index)].TimeoutTimeOfChannelConfig)
#define UdpNm_GetWaitBusSleepTimeOfChannelConfig(Index)                                             (UdpNm_GetChannelConfigOfPCConfig()[(Index)].WaitBusSleepTimeOfChannelConfig)
#define UdpNm_GetCommState(Index)                                                                   (UdpNm_GetCommStateOfPCConfig()[(Index)])
#define UdpNm_GetCoordReadyToSleepState(Index)                                                      (UdpNm_GetCoordReadyToSleepStateOfPCConfig()[(Index)])
#define UdpNm_GetImmediateNmMsgCount(Index)                                                         (UdpNm_GetImmediateNmMsgCountOfPCConfig()[(Index)])
#define UdpNm_IsModuleInitialized()                                                                 (((*(UdpNm_GetModuleInitializedOfPCConfig()))) != FALSE)
#define UdpNm_IsMsgConfirmationFlag(Index)                                                          ((UdpNm_GetMsgConfirmationFlagOfPCConfig()[(Index)]) != FALSE)
#define UdpNm_IsMsgIndicationFlag(Index)                                                            ((UdpNm_GetMsgIndicationFlagOfPCConfig()[(Index)]) != FALSE)
#define UdpNm_GetMsgRequest(Index)                                                                  (UdpNm_GetMsgRequestOfPCConfig()[(Index)])
#define UdpNm_GetMsgTimeoutTimer(Index)                                                             (UdpNm_GetMsgTimeoutTimerOfPCConfig()[(Index)])
#define UdpNm_GetMsgTimer(Index)                                                                    (UdpNm_GetMsgTimerOfPCConfig()[(Index)])
#define UdpNm_GetNetworkRestartFlag(Index)                                                          (UdpNm_GetNetworkRestartFlagOfPCConfig()[(Index)])
#define UdpNm_GetNmState(Index)                                                                     (UdpNm_GetNmStateOfPCConfig()[(Index)])
#define UdpNm_GetMsgCycleOffsetOfPbChannelConfig(Index)                                             (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].MsgCycleOffsetOfPbChannelConfig)
#define UdpNm_IsPnEnabledOfPbChannelConfig(Index)                                                   ((UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].PnEnabledOfPbChannelConfig) != FALSE)
#define UdpNm_GetPnResetTimeOfPbChannelConfig(Index)                                                (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].PnResetTimeOfPbChannelConfig)
#define UdpNm_GetTxMessageDataEndIdxOfPbChannelConfig(Index)                                        (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataEndIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageDataLengthOfPbChannelConfig(Index)                                        (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataLengthOfPbChannelConfig)
#define UdpNm_GetTxMessageDataStartIdxOfPbChannelConfig(Index)                                      (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageDataStartIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(Index)                                       (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_CBVIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageData_PnFilterMaskEndIdxOfPbChannelConfig(Index)                           (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_PnFilterMaskEndIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageData_PnFilterMaskStartIdxOfPbChannelConfig(Index)                         (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageData_UserDataEndIdxOfPbChannelConfig(Index)                               (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataEndIdxOfPbChannelConfig)
#define UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(Index)                               (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataLengthOfPbChannelConfig)
#define UdpNm_GetTxMessageData_UserDataStartIdxOfPbChannelConfig(Index)                             (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxMessageData_UserDataStartIdxOfPbChannelConfig)
#define UdpNm_GetTxPduIdOfPbChannelConfig(Index)                                                    (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxPduIdOfPbChannelConfig)
#define UdpNm_GetTxUserDataPduIdOfPbChannelConfig(Index)                                            (UdpNm_GetPbChannelConfigOfPCConfig()[(Index)].TxUserDataPduIdOfPbChannelConfig)
#define UdpNm_GetPnClusterReq(Index)                                                                (UdpNm_GetPnClusterReqOfPCConfig()[(Index)])
#define UdpNm_GetPnClusterReqNew(Index)                                                             (UdpNm_GetPnClusterReqNewOfPCConfig()[(Index)])
#define UdpNm_GetPnClusterResetTimer(Index)                                                         (UdpNm_GetPnClusterResetTimerOfPCConfig()[(Index)])
#define UdpNm_GetPnClusterResetTimerEndIdxOfPnInfoByteConfig(Index)                                 (UdpNm_GetPnInfoByteConfigOfPCConfig()[(Index)].PnClusterResetTimerEndIdxOfPnInfoByteConfig)
#define UdpNm_GetPnClusterResetTimerStartIdxOfPnInfoByteConfig(Index)                               (UdpNm_GetPnInfoByteConfigOfPCConfig()[(Index)].PnClusterResetTimerStartIdxOfPnInfoByteConfig)
#define UdpNm_GetPnFilterMaskOfPnInfoByteConfig(Index)                                              (UdpNm_GetPnInfoByteConfigOfPCConfig()[(Index)].PnFilterMaskOfPnInfoByteConfig)
#define UdpNm_GetRepeatMsgTimer(Index)                                                              (UdpNm_GetRepeatMsgTimerOfPCConfig()[(Index)])
#define UdpNm_IsRetryFirstMessageRequestFlag(Index)                                                 ((UdpNm_GetRetryFirstMessageRequestFlagOfPCConfig()[(Index)]) != FALSE)
#define UdpNm_GetSysToNmChInd(Index)                                                                (UdpNm_GetSysToNmChIndOfPCConfig()[(Index)])
#define UdpNm_GetTimeoutTimer(Index)                                                                (UdpNm_GetTimeoutTimerOfPCConfig()[(Index)])
#define UdpNm_GetTxControlState(Index)                                                              (UdpNm_GetTxControlStateOfPCConfig()[(Index)])
#define UdpNm_GetTxControlStateRequest(Index)                                                       (UdpNm_GetTxControlStateRequestOfPCConfig()[(Index)])
#define UdpNm_GetTxMessageData(Index)                                                               (UdpNm_GetTxMessageDataOfPCConfig()[(Index)])
#define UdpNm_GetWaitBusSleepTimer(Index)                                                           (UdpNm_GetWaitBusSleepTimerOfPCConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCGetDeduplicatedDataMacros  UdpNm Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define UdpNm_IsTxMessageDataUsedOfPbChannelConfig(Index)                                           (((boolean)(UdpNm_GetTxMessageDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to UdpNm_TxMessageData */
#define UdpNm_IsTxMessageData_CBVUsedOfPbChannelConfig(Index)                                       (((boolean)(UdpNm_GetTxMessageData_CBVIdxOfPbChannelConfig(Index) != UDPNM_NO_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to UdpNm_TxMessageData */
#define UdpNm_IsTxMessageData_PnFilterMaskUsedOfPbChannelConfig(Index)                              (((boolean)(UdpNm_GetTxMessageData_PnFilterMaskStartIdxOfPbChannelConfig(Index) != UDPNM_NO_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to UdpNm_TxMessageData */
#define UdpNm_IsTxMessageData_UserDataUsedOfPbChannelConfig(Index)                                  (((boolean)(UdpNm_GetTxMessageData_UserDataLengthOfPbChannelConfig(Index) != 0u)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to UdpNm_TxMessageData */
#define UdpNm_IsPnEiraCalcEnabled()                                                                 UdpNm_IsPnEiraCalcEnabledOfPCConfig()
#define UdpNm_GetPnEiraRxPduId()                                                                    UdpNm_GetPnEiraRxPduIdOfPCConfig()
#define UdpNm_IsPnEnabledInVariant()                                                                UdpNm_IsPnEnabledInVariantOfPCConfig()
#define UdpNm_IsPnClusterResetTimerUsedOfPnInfoByteConfig(Index)                                    (((boolean)(UdpNm_GetPnClusterResetTimerStartIdxOfPnInfoByteConfig(Index) != UDPNM_NO_PNCLUSTERRESETTIMERSTARTIDXOFPNINFOBYTECONFIG)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to UdpNm_PnClusterResetTimer */
#define UdpNm_GetPnInfoLength()                                                                     UdpNm_GetPnInfoLengthOfPCConfig()
#define UdpNm_GetPnInfoOffset()                                                                     UdpNm_GetPnInfoOffsetOfPCConfig()
#define UdpNm_GetSizeOfChannelConfig()                                                              UdpNm_GetSizeOfChannelConfigOfPCConfig()
#define UdpNm_GetSizeOfCommState()                                                                  UdpNm_GetSizeOfCommStateOfPCConfig()
#define UdpNm_GetSizeOfCoordReadyToSleepState()                                                     UdpNm_GetSizeOfCoordReadyToSleepStateOfPCConfig()
#define UdpNm_GetSizeOfImmediateNmMsgCount()                                                        UdpNm_GetSizeOfImmediateNmMsgCountOfPCConfig()
#define UdpNm_GetSizeOfMsgConfirmationFlag()                                                        UdpNm_GetSizeOfMsgConfirmationFlagOfPCConfig()
#define UdpNm_GetSizeOfMsgIndicationFlag()                                                          UdpNm_GetSizeOfMsgIndicationFlagOfPCConfig()
#define UdpNm_GetSizeOfMsgRequest()                                                                 UdpNm_GetSizeOfMsgRequestOfPCConfig()
#define UdpNm_GetSizeOfMsgTimeoutTimer()                                                            UdpNm_GetSizeOfMsgTimeoutTimerOfPCConfig()
#define UdpNm_GetSizeOfMsgTimer()                                                                   UdpNm_GetSizeOfMsgTimerOfPCConfig()
#define UdpNm_GetSizeOfNetworkRestartFlag()                                                         UdpNm_GetSizeOfNetworkRestartFlagOfPCConfig()
#define UdpNm_GetSizeOfNmState()                                                                    UdpNm_GetSizeOfNmStateOfPCConfig()
#define UdpNm_GetSizeOfPbChannelConfig()                                                            UdpNm_GetSizeOfPbChannelConfigOfPCConfig()
#define UdpNm_GetSizeOfPnClusterReq()                                                               UdpNm_GetSizeOfPnClusterReqOfPCConfig()
#define UdpNm_GetSizeOfPnClusterReqNew()                                                            UdpNm_GetSizeOfPnClusterReqNewOfPCConfig()
#define UdpNm_GetSizeOfPnInfoByteConfig()                                                           UdpNm_GetSizeOfPnInfoByteConfigOfPCConfig()
#define UdpNm_GetSizeOfRepeatMsgTimer()                                                             UdpNm_GetSizeOfRepeatMsgTimerOfPCConfig()
#define UdpNm_GetSizeOfRetryFirstMessageRequestFlag()                                               UdpNm_GetSizeOfRetryFirstMessageRequestFlagOfPCConfig()
#define UdpNm_GetSizeOfSysToNmChInd()                                                               UdpNm_GetSizeOfSysToNmChIndOfPCConfig()
#define UdpNm_GetSizeOfTimeoutTimer()                                                               UdpNm_GetSizeOfTimeoutTimerOfPCConfig()
#define UdpNm_GetSizeOfTxControlState()                                                             UdpNm_GetSizeOfTxControlStateOfPCConfig()
#define UdpNm_GetSizeOfTxControlStateRequest()                                                      UdpNm_GetSizeOfTxControlStateRequestOfPCConfig()
#define UdpNm_GetSizeOfTxMessageData()                                                              UdpNm_GetSizeOfTxMessageDataOfPCConfig()
#define UdpNm_GetSizeOfWaitBusSleepTimer()                                                          UdpNm_GetSizeOfWaitBusSleepTimerOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCSetDataMacros  UdpNm Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define UdpNm_SetCommState(Index, Value)                                                            UdpNm_GetCommStateOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetCoordReadyToSleepState(Index, Value)                                               UdpNm_GetCoordReadyToSleepStateOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetImmediateNmMsgCount(Index, Value)                                                  UdpNm_GetImmediateNmMsgCountOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetModuleInitialized(Value)                                                           (*(UdpNm_GetModuleInitializedOfPCConfig())) = (Value)
#define UdpNm_SetMsgConfirmationFlag(Index, Value)                                                  UdpNm_GetMsgConfirmationFlagOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetMsgIndicationFlag(Index, Value)                                                    UdpNm_GetMsgIndicationFlagOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetMsgRequest(Index, Value)                                                           UdpNm_GetMsgRequestOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetMsgTimeoutTimer(Index, Value)                                                      UdpNm_GetMsgTimeoutTimerOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetMsgTimer(Index, Value)                                                             UdpNm_GetMsgTimerOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetNetworkRestartFlag(Index, Value)                                                   UdpNm_GetNetworkRestartFlagOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetNmState(Index, Value)                                                              UdpNm_GetNmStateOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetPnClusterReq(Index, Value)                                                         UdpNm_GetPnClusterReqOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetPnClusterReqNew(Index, Value)                                                      UdpNm_GetPnClusterReqNewOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetPnClusterResetTimer(Index, Value)                                                  UdpNm_GetPnClusterResetTimerOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetRepeatMsgTimer(Index, Value)                                                       UdpNm_GetRepeatMsgTimerOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetRetryFirstMessageRequestFlag(Index, Value)                                         UdpNm_GetRetryFirstMessageRequestFlagOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetTimeoutTimer(Index, Value)                                                         UdpNm_GetTimeoutTimerOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetTxControlState(Index, Value)                                                       UdpNm_GetTxControlStateOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetTxControlStateRequest(Index, Value)                                                UdpNm_GetTxControlStateRequestOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetTxMessageData(Index, Value)                                                        UdpNm_GetTxMessageDataOfPCConfig()[(Index)] = (Value)
#define UdpNm_SetWaitBusSleepTimer(Index, Value)                                                    UdpNm_GetWaitBusSleepTimerOfPCConfig()[(Index)] = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCGetAddressOfDataMacros  UdpNm Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define UdpNm_GetAddrNmState(Index)                                                                 (&UdpNm_GetNmState(Index))
#define UdpNm_GetAddrPnClusterReq(Index)                                                            (&UdpNm_GetPnClusterReq(Index))
#define UdpNm_GetAddrPnClusterReqNew(Index)                                                         (&UdpNm_GetPnClusterReqNew(Index))
#define UdpNm_GetAddrTxMessageData(Index)                                                           (&UdpNm_GetTxMessageData(Index))
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCHasMacros  UdpNm Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define UdpNm_HasChannelConfig()                                                                    (TRUE != FALSE)
#define UdpNm_HasActiveWakeUpBitEnabledOfChannelConfig()                                            (TRUE != FALSE)
#define UdpNm_HasAllMessagesKeepAwakeOfChannelConfig()                                              (TRUE != FALSE)
#define UdpNm_HasChannelIdOfChannelConfig()                                                         (TRUE != FALSE)
#define UdpNm_HasComControlEnabledOfChannelConfig()                                                 (TRUE != FALSE)
#define UdpNm_HasImmediateNmCycleTimeOfChannelConfig()                                              (TRUE != FALSE)
#define UdpNm_HasImmediateNmTransmissionsOfChannelConfig()                                          (TRUE != FALSE)
#define UdpNm_HasMsgCycleTimeOfChannelConfig()                                                      (TRUE != FALSE)
#define UdpNm_HasMsgTimeoutTimeOfChannelConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasPduCbvPositionOfChannelConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasPnHandleMultipleNetworkRequestOfChannelConfig()                                    (TRUE != FALSE)
#define UdpNm_HasRepeatMessageTimeOfChannelConfig()                                                 (TRUE != FALSE)
#define UdpNm_HasRetryFirstMessageRequestOfChannelConfig()                                          (TRUE != FALSE)
#define UdpNm_HasTimeoutTimeOfChannelConfig()                                                       (TRUE != FALSE)
#define UdpNm_HasWaitBusSleepTimeOfChannelConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasCommState()                                                                        (TRUE != FALSE)
#define UdpNm_HasCoordReadyToSleepState()                                                           (TRUE != FALSE)
#define UdpNm_HasImmediateNmMsgCount()                                                              (TRUE != FALSE)
#define UdpNm_HasModuleInitialized()                                                                (TRUE != FALSE)
#define UdpNm_HasMsgConfirmationFlag()                                                              (TRUE != FALSE)
#define UdpNm_HasMsgIndicationFlag()                                                                (TRUE != FALSE)
#define UdpNm_HasMsgRequest()                                                                       (TRUE != FALSE)
#define UdpNm_HasMsgTimeoutTimer()                                                                  (TRUE != FALSE)
#define UdpNm_HasMsgTimer()                                                                         (TRUE != FALSE)
#define UdpNm_HasNetworkRestartFlag()                                                               (TRUE != FALSE)
#define UdpNm_HasNmState()                                                                          (TRUE != FALSE)
#define UdpNm_HasPbChannelConfig()                                                                  (TRUE != FALSE)
#define UdpNm_HasMsgCycleOffsetOfPbChannelConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasPnEnabledOfPbChannelConfig()                                                       (TRUE != FALSE)
#define UdpNm_HasPnResetTimeOfPbChannelConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasTxMessageDataEndIdxOfPbChannelConfig()                                             (TRUE != FALSE)
#define UdpNm_HasTxMessageDataLengthOfPbChannelConfig()                                             (TRUE != FALSE)
#define UdpNm_HasTxMessageDataStartIdxOfPbChannelConfig()                                           (TRUE != FALSE)
#define UdpNm_HasTxMessageDataUsedOfPbChannelConfig()                                               (TRUE != FALSE)
#define UdpNm_HasTxMessageData_CBVIdxOfPbChannelConfig()                                            (TRUE != FALSE)
#define UdpNm_HasTxMessageData_CBVUsedOfPbChannelConfig()                                           (TRUE != FALSE)
#define UdpNm_HasTxMessageData_PnFilterMaskEndIdxOfPbChannelConfig()                                (TRUE != FALSE)
#define UdpNm_HasTxMessageData_PnFilterMaskStartIdxOfPbChannelConfig()                              (TRUE != FALSE)
#define UdpNm_HasTxMessageData_PnFilterMaskUsedOfPbChannelConfig()                                  (TRUE != FALSE)
#define UdpNm_HasTxMessageData_UserDataEndIdxOfPbChannelConfig()                                    (TRUE != FALSE)
#define UdpNm_HasTxMessageData_UserDataLengthOfPbChannelConfig()                                    (TRUE != FALSE)
#define UdpNm_HasTxMessageData_UserDataStartIdxOfPbChannelConfig()                                  (TRUE != FALSE)
#define UdpNm_HasTxMessageData_UserDataUsedOfPbChannelConfig()                                      (TRUE != FALSE)
#define UdpNm_HasTxPduIdOfPbChannelConfig()                                                         (TRUE != FALSE)
#define UdpNm_HasTxUserDataPduIdOfPbChannelConfig()                                                 (TRUE != FALSE)
#define UdpNm_HasPnClusterReq()                                                                     (TRUE != FALSE)
#define UdpNm_HasPnClusterReqNew()                                                                  (TRUE != FALSE)
#define UdpNm_HasPnClusterResetTimer()                                                              (TRUE != FALSE)
#define UdpNm_HasPnEiraCalcEnabled()                                                                (TRUE != FALSE)
#define UdpNm_HasPnEiraRxPduId()                                                                    (TRUE != FALSE)
#define UdpNm_HasPnEnabledInVariant()                                                               (TRUE != FALSE)
#define UdpNm_HasPnInfoByteConfig()                                                                 (TRUE != FALSE)
#define UdpNm_HasPnClusterResetTimerEndIdxOfPnInfoByteConfig()                                      (TRUE != FALSE)
#define UdpNm_HasPnClusterResetTimerStartIdxOfPnInfoByteConfig()                                    (TRUE != FALSE)
#define UdpNm_HasPnClusterResetTimerUsedOfPnInfoByteConfig()                                        (TRUE != FALSE)
#define UdpNm_HasPnFilterMaskOfPnInfoByteConfig()                                                   (TRUE != FALSE)
#define UdpNm_HasPnInfoLength()                                                                     (TRUE != FALSE)
#define UdpNm_HasPnInfoOffset()                                                                     (TRUE != FALSE)
#define UdpNm_HasRepeatMsgTimer()                                                                   (TRUE != FALSE)
#define UdpNm_HasRetryFirstMessageRequestFlag()                                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfChannelConfig()                                                              (TRUE != FALSE)
#define UdpNm_HasSizeOfCommState()                                                                  (TRUE != FALSE)
#define UdpNm_HasSizeOfCoordReadyToSleepState()                                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfImmediateNmMsgCount()                                                        (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgConfirmationFlag()                                                        (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgIndicationFlag()                                                          (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgRequest()                                                                 (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgTimeoutTimer()                                                            (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgTimer()                                                                   (TRUE != FALSE)
#define UdpNm_HasSizeOfNetworkRestartFlag()                                                         (TRUE != FALSE)
#define UdpNm_HasSizeOfNmState()                                                                    (TRUE != FALSE)
#define UdpNm_HasSizeOfPbChannelConfig()                                                            (TRUE != FALSE)
#define UdpNm_HasSizeOfPnClusterReq()                                                               (TRUE != FALSE)
#define UdpNm_HasSizeOfPnClusterReqNew()                                                            (TRUE != FALSE)
#define UdpNm_HasSizeOfPnInfoByteConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasSizeOfRepeatMsgTimer()                                                             (TRUE != FALSE)
#define UdpNm_HasSizeOfRetryFirstMessageRequestFlag()                                               (TRUE != FALSE)
#define UdpNm_HasSizeOfSysToNmChInd()                                                               (TRUE != FALSE)
#define UdpNm_HasSizeOfTimeoutTimer()                                                               (TRUE != FALSE)
#define UdpNm_HasSizeOfTxControlState()                                                             (TRUE != FALSE)
#define UdpNm_HasSizeOfTxControlStateRequest()                                                      (TRUE != FALSE)
#define UdpNm_HasSizeOfTxMessageData()                                                              (TRUE != FALSE)
#define UdpNm_HasSizeOfWaitBusSleepTimer()                                                          (TRUE != FALSE)
#define UdpNm_HasSysToNmChInd()                                                                     (TRUE != FALSE)
#define UdpNm_HasTimeoutTimer()                                                                     (TRUE != FALSE)
#define UdpNm_HasTxControlState()                                                                   (TRUE != FALSE)
#define UdpNm_HasTxControlStateRequest()                                                            (TRUE != FALSE)
#define UdpNm_HasTxMessageData()                                                                    (TRUE != FALSE)
#define UdpNm_HasWaitBusSleepTimer()                                                                (TRUE != FALSE)
#define UdpNm_HasPCConfig()                                                                         (TRUE != FALSE)
#define UdpNm_HasChannelConfigOfPCConfig()                                                          (TRUE != FALSE)
#define UdpNm_HasCommStateOfPCConfig()                                                              (TRUE != FALSE)
#define UdpNm_HasCoordReadyToSleepStateOfPCConfig()                                                 (TRUE != FALSE)
#define UdpNm_HasImmediateNmMsgCountOfPCConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasModuleInitializedOfPCConfig()                                                      (TRUE != FALSE)
#define UdpNm_HasMsgConfirmationFlagOfPCConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasMsgIndicationFlagOfPCConfig()                                                      (TRUE != FALSE)
#define UdpNm_HasMsgRequestOfPCConfig()                                                             (TRUE != FALSE)
#define UdpNm_HasMsgTimeoutTimerOfPCConfig()                                                        (TRUE != FALSE)
#define UdpNm_HasMsgTimerOfPCConfig()                                                               (TRUE != FALSE)
#define UdpNm_HasNetworkRestartFlagOfPCConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasNmStateOfPCConfig()                                                                (TRUE != FALSE)
#define UdpNm_HasPbChannelConfigOfPCConfig()                                                        (TRUE != FALSE)
#define UdpNm_HasPnClusterReqNewOfPCConfig()                                                        (TRUE != FALSE)
#define UdpNm_HasPnClusterReqOfPCConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasPnClusterResetTimerOfPCConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasPnEiraCalcEnabledOfPCConfig()                                                      (TRUE != FALSE)
#define UdpNm_HasPnEiraRxPduIdOfPCConfig()                                                          (TRUE != FALSE)
#define UdpNm_HasPnEnabledInVariantOfPCConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasPnInfoByteConfigOfPCConfig()                                                       (TRUE != FALSE)
#define UdpNm_HasPnInfoLengthOfPCConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasPnInfoOffsetOfPCConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasRepeatMsgTimerOfPCConfig()                                                         (TRUE != FALSE)
#define UdpNm_HasRetryFirstMessageRequestFlagOfPCConfig()                                           (TRUE != FALSE)
#define UdpNm_HasSizeOfChannelConfigOfPCConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasSizeOfCommStateOfPCConfig()                                                        (TRUE != FALSE)
#define UdpNm_HasSizeOfCoordReadyToSleepStateOfPCConfig()                                           (TRUE != FALSE)
#define UdpNm_HasSizeOfImmediateNmMsgCountOfPCConfig()                                              (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgConfirmationFlagOfPCConfig()                                              (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgIndicationFlagOfPCConfig()                                                (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgRequestOfPCConfig()                                                       (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgTimeoutTimerOfPCConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasSizeOfMsgTimerOfPCConfig()                                                         (TRUE != FALSE)
#define UdpNm_HasSizeOfNetworkRestartFlagOfPCConfig()                                               (TRUE != FALSE)
#define UdpNm_HasSizeOfNmStateOfPCConfig()                                                          (TRUE != FALSE)
#define UdpNm_HasSizeOfPbChannelConfigOfPCConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasSizeOfPnClusterReqNewOfPCConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasSizeOfPnClusterReqOfPCConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfPnInfoByteConfigOfPCConfig()                                                 (TRUE != FALSE)
#define UdpNm_HasSizeOfRepeatMsgTimerOfPCConfig()                                                   (TRUE != FALSE)
#define UdpNm_HasSizeOfRetryFirstMessageRequestFlagOfPCConfig()                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfSysToNmChIndOfPCConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfTimeoutTimerOfPCConfig()                                                     (TRUE != FALSE)
#define UdpNm_HasSizeOfTxControlStateOfPCConfig()                                                   (TRUE != FALSE)
#define UdpNm_HasSizeOfTxControlStateRequestOfPCConfig()                                            (TRUE != FALSE)
#define UdpNm_HasSizeOfTxMessageDataOfPCConfig()                                                    (TRUE != FALSE)
#define UdpNm_HasSizeOfWaitBusSleepTimerOfPCConfig()                                                (TRUE != FALSE)
#define UdpNm_HasSysToNmChIndOfPCConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasTimeoutTimerOfPCConfig()                                                           (TRUE != FALSE)
#define UdpNm_HasTxControlStateOfPCConfig()                                                         (TRUE != FALSE)
#define UdpNm_HasTxControlStateRequestOfPCConfig()                                                  (TRUE != FALSE)
#define UdpNm_HasTxMessageDataOfPCConfig()                                                          (TRUE != FALSE)
#define UdpNm_HasWaitBusSleepTimerOfPCConfig()                                                      (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCIncrementDataMacros  UdpNm Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define UdpNm_IncCommState(Index)                                                                   UdpNm_GetCommState(Index)++
#define UdpNm_IncCoordReadyToSleepState(Index)                                                      UdpNm_GetCoordReadyToSleepState(Index)++
#define UdpNm_IncImmediateNmMsgCount(Index)                                                         UdpNm_GetImmediateNmMsgCount(Index)++
#define UdpNm_IncMsgRequest(Index)                                                                  UdpNm_GetMsgRequest(Index)++
#define UdpNm_IncMsgTimeoutTimer(Index)                                                             UdpNm_GetMsgTimeoutTimer(Index)++
#define UdpNm_IncMsgTimer(Index)                                                                    UdpNm_GetMsgTimer(Index)++
#define UdpNm_IncNetworkRestartFlag(Index)                                                          UdpNm_GetNetworkRestartFlag(Index)++
#define UdpNm_IncNmState(Index)                                                                     UdpNm_GetNmState(Index)++
#define UdpNm_IncPnClusterReq(Index)                                                                UdpNm_GetPnClusterReq(Index)++
#define UdpNm_IncPnClusterReqNew(Index)                                                             UdpNm_GetPnClusterReqNew(Index)++
#define UdpNm_IncPnClusterResetTimer(Index)                                                         UdpNm_GetPnClusterResetTimer(Index)++
#define UdpNm_IncRepeatMsgTimer(Index)                                                              UdpNm_GetRepeatMsgTimer(Index)++
#define UdpNm_IncTimeoutTimer(Index)                                                                UdpNm_GetTimeoutTimer(Index)++
#define UdpNm_IncTxControlState(Index)                                                              UdpNm_GetTxControlState(Index)++
#define UdpNm_IncTxControlStateRequest(Index)                                                       UdpNm_GetTxControlStateRequest(Index)++
#define UdpNm_IncTxMessageData(Index)                                                               UdpNm_GetTxMessageData(Index)++
#define UdpNm_IncWaitBusSleepTimer(Index)                                                           UdpNm_GetWaitBusSleepTimer(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCDecrementDataMacros  UdpNm Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define UdpNm_DecCommState(Index)                                                                   UdpNm_GetCommState(Index)--
#define UdpNm_DecCoordReadyToSleepState(Index)                                                      UdpNm_GetCoordReadyToSleepState(Index)--
#define UdpNm_DecImmediateNmMsgCount(Index)                                                         UdpNm_GetImmediateNmMsgCount(Index)--
#define UdpNm_DecMsgRequest(Index)                                                                  UdpNm_GetMsgRequest(Index)--
#define UdpNm_DecMsgTimeoutTimer(Index)                                                             UdpNm_GetMsgTimeoutTimer(Index)--
#define UdpNm_DecMsgTimer(Index)                                                                    UdpNm_GetMsgTimer(Index)--
#define UdpNm_DecNetworkRestartFlag(Index)                                                          UdpNm_GetNetworkRestartFlag(Index)--
#define UdpNm_DecNmState(Index)                                                                     UdpNm_GetNmState(Index)--
#define UdpNm_DecPnClusterReq(Index)                                                                UdpNm_GetPnClusterReq(Index)--
#define UdpNm_DecPnClusterReqNew(Index)                                                             UdpNm_GetPnClusterReqNew(Index)--
#define UdpNm_DecPnClusterResetTimer(Index)                                                         UdpNm_GetPnClusterResetTimer(Index)--
#define UdpNm_DecRepeatMsgTimer(Index)                                                              UdpNm_GetRepeatMsgTimer(Index)--
#define UdpNm_DecTimeoutTimer(Index)                                                                UdpNm_GetTimeoutTimer(Index)--
#define UdpNm_DecTxControlState(Index)                                                              UdpNm_GetTxControlState(Index)--
#define UdpNm_DecTxControlStateRequest(Index)                                                       UdpNm_GetTxControlStateRequest(Index)--
#define UdpNm_DecTxMessageData(Index)                                                               UdpNm_GetTxMessageData(Index)--
#define UdpNm_DecWaitBusSleepTimer(Index)                                                           UdpNm_GetWaitBusSleepTimer(Index)--
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCAddDataMacros  UdpNm Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/ 
#define UdpNm_AddCommState(Index, Value)                                                            UdpNm_SetCommState(Index, (UdpNm_GetCommState(Index) + Value))
#define UdpNm_AddCoordReadyToSleepState(Index, Value)                                               UdpNm_SetCoordReadyToSleepState(Index, (UdpNm_GetCoordReadyToSleepState(Index) + Value))
#define UdpNm_AddImmediateNmMsgCount(Index, Value)                                                  UdpNm_SetImmediateNmMsgCount(Index, (UdpNm_GetImmediateNmMsgCount(Index) + Value))
#define UdpNm_AddMsgRequest(Index, Value)                                                           UdpNm_SetMsgRequest(Index, (UdpNm_GetMsgRequest(Index) + Value))
#define UdpNm_AddMsgTimeoutTimer(Index, Value)                                                      UdpNm_SetMsgTimeoutTimer(Index, (UdpNm_GetMsgTimeoutTimer(Index) + Value))
#define UdpNm_AddMsgTimer(Index, Value)                                                             UdpNm_SetMsgTimer(Index, (UdpNm_GetMsgTimer(Index) + Value))
#define UdpNm_AddNetworkRestartFlag(Index, Value)                                                   UdpNm_SetNetworkRestartFlag(Index, (UdpNm_GetNetworkRestartFlag(Index) + Value))
#define UdpNm_AddNmState(Index, Value)                                                              UdpNm_SetNmState(Index, (UdpNm_GetNmState(Index) + Value))
#define UdpNm_AddPnClusterReq(Index, Value)                                                         UdpNm_SetPnClusterReq(Index, (UdpNm_GetPnClusterReq(Index) + Value))
#define UdpNm_AddPnClusterReqNew(Index, Value)                                                      UdpNm_SetPnClusterReqNew(Index, (UdpNm_GetPnClusterReqNew(Index) + Value))
#define UdpNm_AddPnClusterResetTimer(Index, Value)                                                  UdpNm_SetPnClusterResetTimer(Index, (UdpNm_GetPnClusterResetTimer(Index) + Value))
#define UdpNm_AddRepeatMsgTimer(Index, Value)                                                       UdpNm_SetRepeatMsgTimer(Index, (UdpNm_GetRepeatMsgTimer(Index) + Value))
#define UdpNm_AddTimeoutTimer(Index, Value)                                                         UdpNm_SetTimeoutTimer(Index, (UdpNm_GetTimeoutTimer(Index) + Value))
#define UdpNm_AddTxControlState(Index, Value)                                                       UdpNm_SetTxControlState(Index, (UdpNm_GetTxControlState(Index) + Value))
#define UdpNm_AddTxControlStateRequest(Index, Value)                                                UdpNm_SetTxControlStateRequest(Index, (UdpNm_GetTxControlStateRequest(Index) + Value))
#define UdpNm_AddTxMessageData(Index, Value)                                                        UdpNm_SetTxMessageData(Index, (UdpNm_GetTxMessageData(Index) + Value))
#define UdpNm_AddWaitBusSleepTimer(Index, Value)                                                    UdpNm_SetWaitBusSleepTimer(Index, (UdpNm_GetWaitBusSleepTimer(Index) + Value))
/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCSubstractDataMacros  UdpNm Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/ 
#define UdpNm_SubCommState(Index, Value)                                                            UdpNm_SetCommState(Index, (UdpNm_GetCommState(Index) - Value))
#define UdpNm_SubCoordReadyToSleepState(Index, Value)                                               UdpNm_SetCoordReadyToSleepState(Index, (UdpNm_GetCoordReadyToSleepState(Index) - Value))
#define UdpNm_SubImmediateNmMsgCount(Index, Value)                                                  UdpNm_SetImmediateNmMsgCount(Index, (UdpNm_GetImmediateNmMsgCount(Index) - Value))
#define UdpNm_SubMsgRequest(Index, Value)                                                           UdpNm_SetMsgRequest(Index, (UdpNm_GetMsgRequest(Index) - Value))
#define UdpNm_SubMsgTimeoutTimer(Index, Value)                                                      UdpNm_SetMsgTimeoutTimer(Index, (UdpNm_GetMsgTimeoutTimer(Index) - Value))
#define UdpNm_SubMsgTimer(Index, Value)                                                             UdpNm_SetMsgTimer(Index, (UdpNm_GetMsgTimer(Index) - Value))
#define UdpNm_SubNetworkRestartFlag(Index, Value)                                                   UdpNm_SetNetworkRestartFlag(Index, (UdpNm_GetNetworkRestartFlag(Index) - Value))
#define UdpNm_SubNmState(Index, Value)                                                              UdpNm_SetNmState(Index, (UdpNm_GetNmState(Index) - Value))
#define UdpNm_SubPnClusterReq(Index, Value)                                                         UdpNm_SetPnClusterReq(Index, (UdpNm_GetPnClusterReq(Index) - Value))
#define UdpNm_SubPnClusterReqNew(Index, Value)                                                      UdpNm_SetPnClusterReqNew(Index, (UdpNm_GetPnClusterReqNew(Index) - Value))
#define UdpNm_SubPnClusterResetTimer(Index, Value)                                                  UdpNm_SetPnClusterResetTimer(Index, (UdpNm_GetPnClusterResetTimer(Index) - Value))
#define UdpNm_SubRepeatMsgTimer(Index, Value)                                                       UdpNm_SetRepeatMsgTimer(Index, (UdpNm_GetRepeatMsgTimer(Index) - Value))
#define UdpNm_SubTimeoutTimer(Index, Value)                                                         UdpNm_SetTimeoutTimer(Index, (UdpNm_GetTimeoutTimer(Index) - Value))
#define UdpNm_SubTxControlState(Index, Value)                                                       UdpNm_SetTxControlState(Index, (UdpNm_GetTxControlState(Index) - Value))
#define UdpNm_SubTxControlStateRequest(Index, Value)                                                UdpNm_SetTxControlStateRequest(Index, (UdpNm_GetTxControlStateRequest(Index) - Value))
#define UdpNm_SubTxMessageData(Index, Value)                                                        UdpNm_SetTxMessageData(Index, (UdpNm_GetTxMessageData(Index) - Value))
#define UdpNm_SubWaitBusSleepTimer(Index, Value)                                                    UdpNm_SetWaitBusSleepTimer(Index, (UdpNm_GetWaitBusSleepTimer(Index) - Value))
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

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
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
  \defgroup  UdpNmPCIterableTypes  UdpNm Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate UdpNm_ChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfChannelConfig() } \endspec */ 
typedef uint8_least UdpNm_ChannelConfigIterType;

/**   \brief  type used to iterate UdpNm_PbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfPbChannelConfig() } \endspec */ 
typedef uint8_least UdpNm_PbChannelConfigIterType;

/**   \brief  type used to iterate UdpNm_PnClusterResetTimer */
typedef uint8_least UdpNm_PnClusterResetTimerIterType;

/**   \brief  type used to iterate UdpNm_PnInfoByteConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfPnInfoByteConfig() } \endspec */ 
typedef uint8_least UdpNm_PnInfoByteConfigIterType;

/**   \brief  type used to iterate UdpNm_SysToNmChInd */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfSysToNmChInd() } \endspec */ 
typedef uint8_least UdpNm_SysToNmChIndIterType;

/**   \brief  type used to iterate UdpNm_TxMessageData */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8_least UdpNm_TxMessageDataIterType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCIterableTypesWithSizeRelations  UdpNm Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate UdpNm_CommState */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfCommState() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_CommStateIterType;

/**   \brief  type used to iterate UdpNm_CoordReadyToSleepState */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfCoordReadyToSleepState() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_CoordReadyToSleepStateIterType;

/**   \brief  type used to iterate UdpNm_ImmediateNmMsgCount */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfImmediateNmMsgCount() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_ImmediateNmMsgCountIterType;

/**   \brief  type used to iterate UdpNm_MsgConfirmationFlag */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfMsgConfirmationFlag() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_MsgConfirmationFlagIterType;

/**   \brief  type used to iterate UdpNm_MsgIndicationFlag */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfMsgIndicationFlag() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_MsgIndicationFlagIterType;

/**   \brief  type used to iterate UdpNm_MsgRequest */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfMsgRequest() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_MsgRequestIterType;

/**   \brief  type used to iterate UdpNm_MsgTimeoutTimer */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfMsgTimeoutTimer() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_MsgTimeoutTimerIterType;

/**   \brief  type used to iterate UdpNm_MsgTimer */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfMsgTimer() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_MsgTimerIterType;

/**   \brief  type used to iterate UdpNm_NetworkRestartFlag */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfNetworkRestartFlag() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_NetworkRestartFlagIterType;

/**   \brief  type used to iterate UdpNm_NmState */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfNmState() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_NmStateIterType;

/**   \brief  type used to iterate UdpNm_PnClusterReq */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfPnClusterReq() } \endspec */ 
typedef UdpNm_PnInfoByteConfigIterType UdpNm_PnClusterReqIterType;

/**   \brief  type used to iterate UdpNm_PnClusterReqNew */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfPnClusterReqNew() } \endspec */ 
typedef UdpNm_PnInfoByteConfigIterType UdpNm_PnClusterReqNewIterType;

/**   \brief  type used to iterate UdpNm_RepeatMsgTimer */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfRepeatMsgTimer() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_RepeatMsgTimerIterType;

/**   \brief  type used to iterate UdpNm_RetryFirstMessageRequestFlag */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfRetryFirstMessageRequestFlag() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_RetryFirstMessageRequestFlagIterType;

/**   \brief  type used to iterate UdpNm_TimeoutTimer */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTimeoutTimer() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_TimeoutTimerIterType;

/**   \brief  type used to iterate UdpNm_TxControlState */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxControlState() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_TxControlStateIterType;

/**   \brief  type used to iterate UdpNm_TxControlStateRequest */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxControlStateRequest() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_TxControlStateRequestIterType;

/**   \brief  type used to iterate UdpNm_WaitBusSleepTimer */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfWaitBusSleepTimer() } \endspec */ 
typedef UdpNm_ChannelConfigIterType UdpNm_WaitBusSleepTimerIterType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCValueTypes  UdpNm Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for UdpNm_ActiveWakeUpBitEnabledOfChannelConfig */
typedef boolean UdpNm_ActiveWakeUpBitEnabledOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_AllMessagesKeepAwakeOfChannelConfig */
typedef boolean UdpNm_AllMessagesKeepAwakeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_ChannelIdOfChannelConfig */
typedef uint8 UdpNm_ChannelIdOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_ComControlEnabledOfChannelConfig */
typedef boolean UdpNm_ComControlEnabledOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_ImmediateNmCycleTimeOfChannelConfig */
typedef uint8 UdpNm_ImmediateNmCycleTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_ImmediateNmTransmissionsOfChannelConfig */
typedef uint8 UdpNm_ImmediateNmTransmissionsOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_MsgCycleTimeOfChannelConfig */
typedef uint8 UdpNm_MsgCycleTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_MsgTimeoutTimeOfChannelConfig */
typedef uint8 UdpNm_MsgTimeoutTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_PduCbvPositionOfChannelConfig */
typedef uint8 UdpNm_PduCbvPositionOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_PnHandleMultipleNetworkRequestOfChannelConfig */
typedef boolean UdpNm_PnHandleMultipleNetworkRequestOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_RepeatMessageTimeOfChannelConfig */
typedef uint8 UdpNm_RepeatMessageTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_RetryFirstMessageRequestOfChannelConfig */
typedef boolean UdpNm_RetryFirstMessageRequestOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_TimeoutTimeOfChannelConfig */
typedef uint16 UdpNm_TimeoutTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_WaitBusSleepTimeOfChannelConfig */
typedef uint8 UdpNm_WaitBusSleepTimeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_CommState */
typedef uint8 UdpNm_CommStateType;

/**   \brief  value based type definition for UdpNm_CoordReadyToSleepState */
typedef uint8 UdpNm_CoordReadyToSleepStateType;

/**   \brief  value based type definition for UdpNm_ImmediateNmMsgCount */
typedef uint8 UdpNm_ImmediateNmMsgCountType;

/**   \brief  value based type definition for UdpNm_ModuleInitialized */
typedef boolean UdpNm_ModuleInitializedType;

/**   \brief  value based type definition for UdpNm_MsgConfirmationFlag */
typedef boolean UdpNm_MsgConfirmationFlagType;

/**   \brief  value based type definition for UdpNm_MsgIndicationFlag */
typedef boolean UdpNm_MsgIndicationFlagType;

/**   \brief  value based type definition for UdpNm_MsgRequest */
typedef uint8 UdpNm_MsgRequestType;

/**   \brief  value based type definition for UdpNm_MsgTimeoutTimer */
typedef uint16 UdpNm_MsgTimeoutTimerType;

/**   \brief  value based type definition for UdpNm_MsgTimer */
typedef uint16 UdpNm_MsgTimerType;

/**   \brief  value based type definition for UdpNm_NetworkRestartFlag */
typedef uint8 UdpNm_NetworkRestartFlagType;

/**   \brief  value based type definition for UdpNm_NmState */
typedef uint8 UdpNm_NmStateType;

/**   \brief  value based type definition for UdpNm_MsgCycleOffsetOfPbChannelConfig */
typedef uint8 UdpNm_MsgCycleOffsetOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_PnEnabledOfPbChannelConfig */
typedef boolean UdpNm_PnEnabledOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_PnResetTimeOfPbChannelConfig */
typedef uint8 UdpNm_PnResetTimeOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageDataEndIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageDataLengthOfPbChannelConfig */
typedef uint8 UdpNm_TxMessageDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageDataStartIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageDataUsedOfPbChannelConfig */
typedef boolean UdpNm_TxMessageDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_CBVIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageData_CBVIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_CBVUsedOfPbChannelConfig */
typedef boolean UdpNm_TxMessageData_CBVUsedOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_PnFilterMaskEndIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageData_PnFilterMaskEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageData_PnFilterMaskStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_PnFilterMaskUsedOfPbChannelConfig */
typedef boolean UdpNm_TxMessageData_PnFilterMaskUsedOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_UserDataEndIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageData_UserDataEndIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_UserDataLengthOfPbChannelConfig */
typedef uint8 UdpNm_TxMessageData_UserDataLengthOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_UserDataStartIdxOfPbChannelConfig */
/*! \spec strong type invariant () { self < UdpNm_GetSizeOfTxMessageData() } \endspec */ 
typedef uint8 UdpNm_TxMessageData_UserDataStartIdxOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxMessageData_UserDataUsedOfPbChannelConfig */
typedef boolean UdpNm_TxMessageData_UserDataUsedOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxPduIdOfPbChannelConfig */
typedef uint8 UdpNm_TxPduIdOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_TxUserDataPduIdOfPbChannelConfig */
typedef uint8 UdpNm_TxUserDataPduIdOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_PnClusterReq */
typedef uint8 UdpNm_PnClusterReqType;

/**   \brief  value based type definition for UdpNm_PnClusterReqNew */
typedef uint8 UdpNm_PnClusterReqNewType;

/**   \brief  value based type definition for UdpNm_PnClusterResetTimer */
typedef uint16 UdpNm_PnClusterResetTimerType;

/**   \brief  value based type definition for UdpNm_PnEiraCalcEnabled */
typedef boolean UdpNm_PnEiraCalcEnabledType;

/**   \brief  value based type definition for UdpNm_PnEiraRxPduId */
typedef uint8 UdpNm_PnEiraRxPduIdType;

/**   \brief  value based type definition for UdpNm_PnEnabledInVariant */
typedef boolean UdpNm_PnEnabledInVariantType;

/**   \brief  value based type definition for UdpNm_PnClusterResetTimerEndIdxOfPnInfoByteConfig */
typedef uint8 UdpNm_PnClusterResetTimerEndIdxOfPnInfoByteConfigType;

/**   \brief  value based type definition for UdpNm_PnClusterResetTimerStartIdxOfPnInfoByteConfig */
typedef uint8 UdpNm_PnClusterResetTimerStartIdxOfPnInfoByteConfigType;

/**   \brief  value based type definition for UdpNm_PnClusterResetTimerUsedOfPnInfoByteConfig */
typedef boolean UdpNm_PnClusterResetTimerUsedOfPnInfoByteConfigType;

/**   \brief  value based type definition for UdpNm_PnFilterMaskOfPnInfoByteConfig */
typedef uint8 UdpNm_PnFilterMaskOfPnInfoByteConfigType;

/**   \brief  value based type definition for UdpNm_PnInfoLength */
typedef uint8 UdpNm_PnInfoLengthType;

/**   \brief  value based type definition for UdpNm_PnInfoOffset */
typedef uint8 UdpNm_PnInfoOffsetType;

/**   \brief  value based type definition for UdpNm_RepeatMsgTimer */
typedef uint16 UdpNm_RepeatMsgTimerType;

/**   \brief  value based type definition for UdpNm_RetryFirstMessageRequestFlag */
typedef boolean UdpNm_RetryFirstMessageRequestFlagType;

/**   \brief  value based type definition for UdpNm_SizeOfChannelConfig */
typedef uint8 UdpNm_SizeOfChannelConfigType;

/**   \brief  value based type definition for UdpNm_SizeOfCommState */
typedef uint8 UdpNm_SizeOfCommStateType;

/**   \brief  value based type definition for UdpNm_SizeOfCoordReadyToSleepState */
typedef uint8 UdpNm_SizeOfCoordReadyToSleepStateType;

/**   \brief  value based type definition for UdpNm_SizeOfImmediateNmMsgCount */
typedef uint8 UdpNm_SizeOfImmediateNmMsgCountType;

/**   \brief  value based type definition for UdpNm_SizeOfMsgConfirmationFlag */
typedef uint8 UdpNm_SizeOfMsgConfirmationFlagType;

/**   \brief  value based type definition for UdpNm_SizeOfMsgIndicationFlag */
typedef uint8 UdpNm_SizeOfMsgIndicationFlagType;

/**   \brief  value based type definition for UdpNm_SizeOfMsgRequest */
typedef uint8 UdpNm_SizeOfMsgRequestType;

/**   \brief  value based type definition for UdpNm_SizeOfMsgTimeoutTimer */
typedef uint8 UdpNm_SizeOfMsgTimeoutTimerType;

/**   \brief  value based type definition for UdpNm_SizeOfMsgTimer */
typedef uint8 UdpNm_SizeOfMsgTimerType;

/**   \brief  value based type definition for UdpNm_SizeOfNetworkRestartFlag */
typedef uint8 UdpNm_SizeOfNetworkRestartFlagType;

/**   \brief  value based type definition for UdpNm_SizeOfNmState */
typedef uint8 UdpNm_SizeOfNmStateType;

/**   \brief  value based type definition for UdpNm_SizeOfPbChannelConfig */
typedef uint8 UdpNm_SizeOfPbChannelConfigType;

/**   \brief  value based type definition for UdpNm_SizeOfPnClusterReq */
typedef uint8 UdpNm_SizeOfPnClusterReqType;

/**   \brief  value based type definition for UdpNm_SizeOfPnClusterReqNew */
typedef uint8 UdpNm_SizeOfPnClusterReqNewType;

/**   \brief  value based type definition for UdpNm_SizeOfPnInfoByteConfig */
typedef uint8 UdpNm_SizeOfPnInfoByteConfigType;

/**   \brief  value based type definition for UdpNm_SizeOfRepeatMsgTimer */
typedef uint8 UdpNm_SizeOfRepeatMsgTimerType;

/**   \brief  value based type definition for UdpNm_SizeOfRetryFirstMessageRequestFlag */
typedef uint8 UdpNm_SizeOfRetryFirstMessageRequestFlagType;

/**   \brief  value based type definition for UdpNm_SizeOfSysToNmChInd */
typedef uint8 UdpNm_SizeOfSysToNmChIndType;

/**   \brief  value based type definition for UdpNm_SizeOfTimeoutTimer */
typedef uint8 UdpNm_SizeOfTimeoutTimerType;

/**   \brief  value based type definition for UdpNm_SizeOfTxControlState */
typedef uint8 UdpNm_SizeOfTxControlStateType;

/**   \brief  value based type definition for UdpNm_SizeOfTxControlStateRequest */
typedef uint8 UdpNm_SizeOfTxControlStateRequestType;

/**   \brief  value based type definition for UdpNm_SizeOfTxMessageData */
typedef uint8 UdpNm_SizeOfTxMessageDataType;

/**   \brief  value based type definition for UdpNm_SizeOfWaitBusSleepTimer */
typedef uint8 UdpNm_SizeOfWaitBusSleepTimerType;

/**   \brief  value based type definition for UdpNm_SysToNmChInd */
typedef uint8 UdpNm_SysToNmChIndType;

/**   \brief  value based type definition for UdpNm_TimeoutTimer */
typedef uint16 UdpNm_TimeoutTimerType;

/**   \brief  value based type definition for UdpNm_TxControlState */
typedef uint8 UdpNm_TxControlStateType;

/**   \brief  value based type definition for UdpNm_TxControlStateRequest */
typedef uint8 UdpNm_TxControlStateRequestType;

/**   \brief  value based type definition for UdpNm_TxMessageData */
typedef uint8 UdpNm_TxMessageDataType;

/**   \brief  value based type definition for UdpNm_WaitBusSleepTimer */
typedef uint32 UdpNm_WaitBusSleepTimerType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  UdpNmPCStructTypes  UdpNm Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in UdpNm_ChannelConfig */
typedef struct sUdpNm_ChannelConfigType
{
  UdpNm_TimeoutTimeOfChannelConfigType TimeoutTimeOfChannelConfig;  /**< Timeout for the NM messages [ms]. */
  UdpNm_ActiveWakeUpBitEnabledOfChannelConfigType ActiveWakeUpBitEnabledOfChannelConfig;  /**< Determines if Active WUP Bit Handling is active or not */
  UdpNm_AllMessagesKeepAwakeOfChannelConfigType AllMessagesKeepAwakeOfChannelConfig;  /**< Determines if all NM PDUs are relevant or not */
  UdpNm_ComControlEnabledOfChannelConfigType ComControlEnabledOfChannelConfig;  /**< Determines if Com Control is active or not */
  UdpNm_PnHandleMultipleNetworkRequestOfChannelConfigType PnHandleMultipleNetworkRequestOfChannelConfig;  /**< Determines whether a call of UdpNm_NetworkRequest leads to a transition to Repeat Message from Network Mode */
  UdpNm_RetryFirstMessageRequestOfChannelConfigType RetryFirstMessageRequestOfChannelConfig;  /**< Determines if Retry First Message Request feature is active or not */
  UdpNm_ChannelIdOfChannelConfigType ChannelIdOfChannelConfig;  /**< Channel ID configured for the respective instance of the NM. */
  UdpNm_ImmediateNmCycleTimeOfChannelConfigType ImmediateNmCycleTimeOfChannelConfig;  /**< Fast NM PDU Transmission Time during WUP */
  UdpNm_ImmediateNmTransmissionsOfChannelConfigType ImmediateNmTransmissionsOfChannelConfig;  /**< Number of fast NM PDU Transmissions during WUP */
  UdpNm_MsgCycleTimeOfChannelConfigType MsgCycleTimeOfChannelConfig;  /**< Period of a NM message [ms]. It determines the periodic rate in the periodic transmission mode. */
  UdpNm_MsgTimeoutTimeOfChannelConfigType MsgTimeoutTimeOfChannelConfig;  /**< Transmission Timeout [ms] of NM message. If there is no transmission confirmation within this timeout, the UDP NM module shall give an error notification. */
  UdpNm_PduCbvPositionOfChannelConfigType PduCbvPositionOfChannelConfig;  /**< Control Bit Vector Position in the PDU */
  UdpNm_RepeatMessageTimeOfChannelConfigType RepeatMessageTimeOfChannelConfig;  /**< Timeout for Repeat Message State [ms]. */
  UdpNm_WaitBusSleepTimeOfChannelConfigType WaitBusSleepTimeOfChannelConfig;  /**< Timeout for bus calm down phase [ms]. */
} UdpNm_ChannelConfigType;

/**   \brief  type used in UdpNm_PbChannelConfig */
/*! 
 * \spec strong type invariant () { 
 *   (!(self.TxMessageDataLengthOfPbChannelConfig != 0u) || (self.TxMessageDataEndIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageDataLengthOfPbChannelConfig != 0u) || (self.TxMessageDataStartIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageData_CBVIdxOfPbChannelConfig != UDPNM_NO_TXMESSAGEDATA_CBVIDXOFPBCHANNELCONFIG) || (self.TxMessageData_CBVIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig != UDPNM_NO_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG) || (self.TxMessageData_PnFilterMaskEndIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig != UDPNM_NO_TXMESSAGEDATA_PNFILTERMASKSTARTIDXOFPBCHANNELCONFIG) || (self.TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageData_UserDataLengthOfPbChannelConfig != 0u) || (self.TxMessageData_UserDataEndIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData())) &&
 *   (!(self.TxMessageData_UserDataLengthOfPbChannelConfig != 0u) || (self.TxMessageData_UserDataStartIdxOfPbChannelConfig < UdpNm_GetSizeOfTxMessageData()))
 * }
 * \endspec 
 */ 
typedef struct sUdpNm_PbChannelConfigType
{
  UdpNm_PnEnabledOfPbChannelConfigType PnEnabledOfPbChannelConfig;  /**< Partial Networking Enabled on this cluster */
  UdpNm_MsgCycleOffsetOfPbChannelConfigType MsgCycleOffsetOfPbChannelConfig;
  UdpNm_PnResetTimeOfPbChannelConfigType PnResetTimeOfPbChannelConfig;  /**< PnResetTimer value */
  UdpNm_TxMessageDataEndIdxOfPbChannelConfigType TxMessageDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageDataLengthOfPbChannelConfigType TxMessageDataLengthOfPbChannelConfig;  /**< the number of relations pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageDataStartIdxOfPbChannelConfigType TxMessageDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_CBVIdxOfPbChannelConfigType TxMessageData_CBVIdxOfPbChannelConfig;  /**< the index of the 0:1 relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_PnFilterMaskEndIdxOfPbChannelConfigType TxMessageData_PnFilterMaskEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_PnFilterMaskStartIdxOfPbChannelConfigType TxMessageData_PnFilterMaskStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_UserDataEndIdxOfPbChannelConfigType TxMessageData_UserDataEndIdxOfPbChannelConfig;  /**< the end index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_UserDataLengthOfPbChannelConfigType TxMessageData_UserDataLengthOfPbChannelConfig;  /**< the number of relations pointing to UdpNm_TxMessageData */
  UdpNm_TxMessageData_UserDataStartIdxOfPbChannelConfigType TxMessageData_UserDataStartIdxOfPbChannelConfig;  /**< the start index of the 0:n relation pointing to UdpNm_TxMessageData */
  UdpNm_TxPduIdOfPbChannelConfigType TxPduIdOfPbChannelConfig;  /**< PDU ID for the UdpNm TX Data PDU */
  UdpNm_TxUserDataPduIdOfPbChannelConfigType TxUserDataPduIdOfPbChannelConfig;  /**< PDU handle for the user data PDU */
} UdpNm_PbChannelConfigType;

/**   \brief  type used in UdpNm_PnInfoByteConfig */
typedef struct sUdpNm_PnInfoByteConfigType
{
  UdpNm_PnClusterResetTimerEndIdxOfPnInfoByteConfigType PnClusterResetTimerEndIdxOfPnInfoByteConfig;  /**< the end index of the 0:n relation pointing to UdpNm_PnClusterResetTimer */
  UdpNm_PnClusterResetTimerStartIdxOfPnInfoByteConfigType PnClusterResetTimerStartIdxOfPnInfoByteConfig;  /**< the start index of the 0:n relation pointing to UdpNm_PnClusterResetTimer */
  UdpNm_PnFilterMaskOfPnInfoByteConfigType PnFilterMaskOfPnInfoByteConfig;  /**< PnFilterMask for PnInfoBytes */
} UdpNm_PnInfoByteConfigType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCSymbolicStructTypes  UdpNm Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to UdpNm_CommState */
typedef struct UdpNm_CommStateStructSTag
{
  UdpNm_CommStateType ComMChannel_Vlan10;
} UdpNm_CommStateStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_CoordReadyToSleepState */
typedef struct UdpNm_CoordReadyToSleepStateStructSTag
{
  UdpNm_CoordReadyToSleepStateType ComMChannel_Vlan10;
} UdpNm_CoordReadyToSleepStateStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_ImmediateNmMsgCount */
typedef struct UdpNm_ImmediateNmMsgCountStructSTag
{
  UdpNm_ImmediateNmMsgCountType ComMChannel_Vlan10;
} UdpNm_ImmediateNmMsgCountStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_MsgConfirmationFlag */
typedef struct UdpNm_MsgConfirmationFlagStructSTag
{
  UdpNm_MsgConfirmationFlagType ComMChannel_Vlan10;
} UdpNm_MsgConfirmationFlagStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_MsgIndicationFlag */
typedef struct UdpNm_MsgIndicationFlagStructSTag
{
  UdpNm_MsgIndicationFlagType ComMChannel_Vlan10;
} UdpNm_MsgIndicationFlagStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_MsgRequest */
typedef struct UdpNm_MsgRequestStructSTag
{
  UdpNm_MsgRequestType ComMChannel_Vlan10;
} UdpNm_MsgRequestStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_MsgTimeoutTimer */
typedef struct UdpNm_MsgTimeoutTimerStructSTag
{
  UdpNm_MsgTimeoutTimerType ComMChannel_Vlan10;
} UdpNm_MsgTimeoutTimerStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_MsgTimer */
typedef struct UdpNm_MsgTimerStructSTag
{
  UdpNm_MsgTimerType ComMChannel_Vlan10;
} UdpNm_MsgTimerStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_NetworkRestartFlag */
typedef struct UdpNm_NetworkRestartFlagStructSTag
{
  UdpNm_NetworkRestartFlagType ComMChannel_Vlan10;
} UdpNm_NetworkRestartFlagStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_NmState */
typedef struct UdpNm_NmStateStructSTag
{
  UdpNm_NmStateType ComMChannel_Vlan10;
} UdpNm_NmStateStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_PnClusterReq */
typedef struct UdpNm_PnClusterReqStructSTag
{
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte0;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte1;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte2;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte3;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte4;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte5;
  UdpNm_PnClusterReqType UdpNmPnFilterMaskByte6;
} UdpNm_PnClusterReqStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_PnClusterReqNew */
typedef struct UdpNm_PnClusterReqNewStructSTag
{
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte0;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte1;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte2;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte3;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte4;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte5;
  UdpNm_PnClusterReqNewType UdpNmPnFilterMaskByte6;
} UdpNm_PnClusterReqNewStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_PnClusterResetTimer */
typedef struct UdpNm_PnClusterResetTimerStructSTag
{
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte0[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte1[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte2[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte3[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte4[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte5[8];
  UdpNm_PnClusterResetTimerType UdpNmPnFilterMaskByte6[8];
} UdpNm_PnClusterResetTimerStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_RepeatMsgTimer */
typedef struct UdpNm_RepeatMsgTimerStructSTag
{
  UdpNm_RepeatMsgTimerType ComMChannel_Vlan10;
} UdpNm_RepeatMsgTimerStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_RetryFirstMessageRequestFlag */
typedef struct UdpNm_RetryFirstMessageRequestFlagStructSTag
{
  UdpNm_RetryFirstMessageRequestFlagType ComMChannel_Vlan10;
} UdpNm_RetryFirstMessageRequestFlagStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_TimeoutTimer */
typedef struct UdpNm_TimeoutTimerStructSTag
{
  UdpNm_TimeoutTimerType ComMChannel_Vlan10;
} UdpNm_TimeoutTimerStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_TxControlState */
typedef struct UdpNm_TxControlStateStructSTag
{
  UdpNm_TxControlStateType ComMChannel_Vlan10;
} UdpNm_TxControlStateStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_TxControlStateRequest */
typedef struct UdpNm_TxControlStateRequestStructSTag
{
  UdpNm_TxControlStateRequestType ComMChannel_Vlan10;
} UdpNm_TxControlStateRequestStructSType;

/**   \brief  type to be used as symbolic data element access to UdpNm_WaitBusSleepTimer */
typedef struct UdpNm_WaitBusSleepTimerStructSTag
{
  UdpNm_WaitBusSleepTimerType ComMChannel_Vlan10;
} UdpNm_WaitBusSleepTimerStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCUnionIndexAndSymbolTypes  UdpNm Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access UdpNm_CommState in an index and symbol based style. */
typedef union UdpNm_CommStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_CommStateType raw[1];
  UdpNm_CommStateStructSType str;
} UdpNm_CommStateUType;

/**   \brief  type to access UdpNm_CoordReadyToSleepState in an index and symbol based style. */
typedef union UdpNm_CoordReadyToSleepStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_CoordReadyToSleepStateType raw[1];
  UdpNm_CoordReadyToSleepStateStructSType str;
} UdpNm_CoordReadyToSleepStateUType;

/**   \brief  type to access UdpNm_ImmediateNmMsgCount in an index and symbol based style. */
typedef union UdpNm_ImmediateNmMsgCountUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_ImmediateNmMsgCountType raw[1];
  UdpNm_ImmediateNmMsgCountStructSType str;
} UdpNm_ImmediateNmMsgCountUType;

/**   \brief  type to access UdpNm_MsgConfirmationFlag in an index and symbol based style. */
typedef union UdpNm_MsgConfirmationFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_MsgConfirmationFlagType raw[1];
  UdpNm_MsgConfirmationFlagStructSType str;
} UdpNm_MsgConfirmationFlagUType;

/**   \brief  type to access UdpNm_MsgIndicationFlag in an index and symbol based style. */
typedef union UdpNm_MsgIndicationFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_MsgIndicationFlagType raw[1];
  UdpNm_MsgIndicationFlagStructSType str;
} UdpNm_MsgIndicationFlagUType;

/**   \brief  type to access UdpNm_MsgRequest in an index and symbol based style. */
typedef union UdpNm_MsgRequestUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_MsgRequestType raw[1];
  UdpNm_MsgRequestStructSType str;
} UdpNm_MsgRequestUType;

/**   \brief  type to access UdpNm_MsgTimeoutTimer in an index and symbol based style. */
typedef union UdpNm_MsgTimeoutTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_MsgTimeoutTimerType raw[1];
  UdpNm_MsgTimeoutTimerStructSType str;
} UdpNm_MsgTimeoutTimerUType;

/**   \brief  type to access UdpNm_MsgTimer in an index and symbol based style. */
typedef union UdpNm_MsgTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_MsgTimerType raw[1];
  UdpNm_MsgTimerStructSType str;
} UdpNm_MsgTimerUType;

/**   \brief  type to access UdpNm_NetworkRestartFlag in an index and symbol based style. */
typedef union UdpNm_NetworkRestartFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_NetworkRestartFlagType raw[1];
  UdpNm_NetworkRestartFlagStructSType str;
} UdpNm_NetworkRestartFlagUType;

/**   \brief  type to access UdpNm_NmState in an index and symbol based style. */
typedef union UdpNm_NmStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_NmStateType raw[1];
  UdpNm_NmStateStructSType str;
} UdpNm_NmStateUType;

/**   \brief  type to access UdpNm_PnClusterReq in an index and symbol based style. */
typedef union UdpNm_PnClusterReqUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_PnClusterReqType raw[7];
  UdpNm_PnClusterReqStructSType str;
} UdpNm_PnClusterReqUType;

/**   \brief  type to access UdpNm_PnClusterReqNew in an index and symbol based style. */
typedef union UdpNm_PnClusterReqNewUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_PnClusterReqNewType raw[7];
  UdpNm_PnClusterReqNewStructSType str;
} UdpNm_PnClusterReqNewUType;

/**   \brief  type to access UdpNm_PnClusterResetTimer in an index and symbol based style. */
typedef union UdpNm_PnClusterResetTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_PnClusterResetTimerType raw[56];
  UdpNm_PnClusterResetTimerStructSType str;
} UdpNm_PnClusterResetTimerUType;

/**   \brief  type to access UdpNm_RepeatMsgTimer in an index and symbol based style. */
typedef union UdpNm_RepeatMsgTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_RepeatMsgTimerType raw[1];
  UdpNm_RepeatMsgTimerStructSType str;
} UdpNm_RepeatMsgTimerUType;

/**   \brief  type to access UdpNm_RetryFirstMessageRequestFlag in an index and symbol based style. */
typedef union UdpNm_RetryFirstMessageRequestFlagUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_RetryFirstMessageRequestFlagType raw[1];
  UdpNm_RetryFirstMessageRequestFlagStructSType str;
} UdpNm_RetryFirstMessageRequestFlagUType;

/**   \brief  type to access UdpNm_TimeoutTimer in an index and symbol based style. */
typedef union UdpNm_TimeoutTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_TimeoutTimerType raw[1];
  UdpNm_TimeoutTimerStructSType str;
} UdpNm_TimeoutTimerUType;

/**   \brief  type to access UdpNm_TxControlState in an index and symbol based style. */
typedef union UdpNm_TxControlStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_TxControlStateType raw[1];
  UdpNm_TxControlStateStructSType str;
} UdpNm_TxControlStateUType;

/**   \brief  type to access UdpNm_TxControlStateRequest in an index and symbol based style. */
typedef union UdpNm_TxControlStateRequestUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_TxControlStateRequestType raw[1];
  UdpNm_TxControlStateRequestStructSType str;
} UdpNm_TxControlStateRequestUType;

/**   \brief  type to access UdpNm_WaitBusSleepTimer in an index and symbol based style. */
typedef union UdpNm_WaitBusSleepTimerUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  UdpNm_WaitBusSleepTimerType raw[1];
  UdpNm_WaitBusSleepTimerStructSType str;
} UdpNm_WaitBusSleepTimerUType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCRootPointerTypes  UdpNm Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to UdpNm_ChannelConfig */
typedef P2CONST(UdpNm_ChannelConfigType, TYPEDEF, UDPNM_CONST) UdpNm_ChannelConfigPtrType;

/**   \brief  type used to point to UdpNm_CommState */
typedef P2VAR(UdpNm_CommStateType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_CommStatePtrType;

/**   \brief  type used to point to UdpNm_CoordReadyToSleepState */
typedef P2VAR(UdpNm_CoordReadyToSleepStateType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_CoordReadyToSleepStatePtrType;

/**   \brief  type used to point to UdpNm_ImmediateNmMsgCount */
typedef P2VAR(UdpNm_ImmediateNmMsgCountType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_ImmediateNmMsgCountPtrType;

/**   \brief  type used to point to UdpNm_ModuleInitialized */
typedef P2VAR(UdpNm_ModuleInitializedType, TYPEDEF, UDPNM_VAR_ZERO_INIT) UdpNm_ModuleInitializedPtrType;

/**   \brief  type used to point to UdpNm_MsgConfirmationFlag */
typedef P2VAR(UdpNm_MsgConfirmationFlagType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_MsgConfirmationFlagPtrType;

/**   \brief  type used to point to UdpNm_MsgIndicationFlag */
typedef P2VAR(UdpNm_MsgIndicationFlagType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_MsgIndicationFlagPtrType;

/**   \brief  type used to point to UdpNm_MsgRequest */
typedef P2VAR(UdpNm_MsgRequestType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_MsgRequestPtrType;

/**   \brief  type used to point to UdpNm_MsgTimeoutTimer */
typedef P2VAR(UdpNm_MsgTimeoutTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_MsgTimeoutTimerPtrType;

/**   \brief  type used to point to UdpNm_MsgTimer */
typedef P2VAR(UdpNm_MsgTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_MsgTimerPtrType;

/**   \brief  type used to point to UdpNm_NetworkRestartFlag */
typedef P2VAR(UdpNm_NetworkRestartFlagType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_NetworkRestartFlagPtrType;

/**   \brief  type used to point to UdpNm_NmState */
typedef P2VAR(UdpNm_NmStateType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_NmStatePtrType;

/**   \brief  type used to point to UdpNm_PbChannelConfig */
typedef P2CONST(UdpNm_PbChannelConfigType, TYPEDEF, UDPNM_CONST) UdpNm_PbChannelConfigPtrType;

/**   \brief  type used to point to UdpNm_PnClusterReq */
typedef P2VAR(UdpNm_PnClusterReqType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_PnClusterReqPtrType;

/**   \brief  type used to point to UdpNm_PnClusterReqNew */
typedef P2VAR(UdpNm_PnClusterReqNewType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_PnClusterReqNewPtrType;

/**   \brief  type used to point to UdpNm_PnClusterResetTimer */
typedef P2VAR(UdpNm_PnClusterResetTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_PnClusterResetTimerPtrType;

/**   \brief  type used to point to UdpNm_PnInfoByteConfig */
typedef P2CONST(UdpNm_PnInfoByteConfigType, TYPEDEF, UDPNM_CONST) UdpNm_PnInfoByteConfigPtrType;

/**   \brief  type used to point to UdpNm_RepeatMsgTimer */
typedef P2VAR(UdpNm_RepeatMsgTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_RepeatMsgTimerPtrType;

/**   \brief  type used to point to UdpNm_RetryFirstMessageRequestFlag */
typedef P2VAR(UdpNm_RetryFirstMessageRequestFlagType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_RetryFirstMessageRequestFlagPtrType;

/**   \brief  type used to point to UdpNm_SysToNmChInd */
typedef P2CONST(UdpNm_SysToNmChIndType, TYPEDEF, UDPNM_CONST) UdpNm_SysToNmChIndPtrType;

/**   \brief  type used to point to UdpNm_TimeoutTimer */
typedef P2VAR(UdpNm_TimeoutTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_TimeoutTimerPtrType;

/**   \brief  type used to point to UdpNm_TxControlState */
typedef P2VAR(UdpNm_TxControlStateType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_TxControlStatePtrType;

/**   \brief  type used to point to UdpNm_TxControlStateRequest */
typedef P2VAR(UdpNm_TxControlStateRequestType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_TxControlStateRequestPtrType;

/**   \brief  type used to point to UdpNm_TxMessageData */
typedef P2VAR(UdpNm_TxMessageDataType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_TxMessageDataPtrType;

/**   \brief  type used to point to UdpNm_WaitBusSleepTimer */
typedef P2VAR(UdpNm_WaitBusSleepTimerType, TYPEDEF, UDPNM_VAR_NOINIT) UdpNm_WaitBusSleepTimerPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  UdpNmPCRootValueTypes  UdpNm Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in UdpNm_PCConfig */
typedef struct sUdpNm_PCConfigType
{
  uint8 UdpNm_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} UdpNm_PCConfigType;

typedef UdpNm_PCConfigType UdpNm_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  UdpNm_ChannelConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_ChannelConfig
  \details
  Element                           Description
  TimeoutTime                       Timeout for the NM messages [ms].
  ActiveWakeUpBitEnabled            Determines if Active WUP Bit Handling is active or not
  AllMessagesKeepAwake              Determines if all NM PDUs are relevant or not
  ComControlEnabled                 Determines if Com Control is active or not
  PnHandleMultipleNetworkRequest    Determines whether a call of UdpNm_NetworkRequest leads to a transition to Repeat Message from Network Mode
  RetryFirstMessageRequest          Determines if Retry First Message Request feature is active or not
  ChannelId                         Channel ID configured for the respective instance of the NM.
  ImmediateNmCycleTime              Fast NM PDU Transmission Time during WUP
  ImmediateNmTransmissions          Number of fast NM PDU Transmissions during WUP
  MsgCycleTime                      Period of a NM message [ms]. It determines the periodic rate in the periodic transmission mode.
  MsgTimeoutTime                    Transmission Timeout [ms] of NM message. If there is no transmission confirmation within this timeout, the UDP NM module shall give an error notification.
  PduCbvPosition                    Control Bit Vector Position in the PDU
  RepeatMessageTime                 Timeout for Repeat Message State [ms].
  WaitBusSleepTime                  Timeout for bus calm down phase [ms].
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(UdpNm_ChannelConfigType, UDPNM_CONST) UdpNm_ChannelConfig[1];
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PbChannelConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_PbChannelConfig
  \brief  Structure for post-build channel configuration parameters
  \details
  Element                               Description
  PnEnabled                             Partial Networking Enabled on this cluster
  MsgCycleOffset                    
  PnResetTime                           PnResetTimer value
  TxMessageDataEndIdx                   the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageDataLength                   the number of relations pointing to UdpNm_TxMessageData
  TxMessageDataStartIdx                 the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_CBVIdx                  the index of the 0:1 relation pointing to UdpNm_TxMessageData
  TxMessageData_PnFilterMaskEndIdx      the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_PnFilterMaskStartIdx    the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_UserDataEndIdx          the end index of the 0:n relation pointing to UdpNm_TxMessageData
  TxMessageData_UserDataLength          the number of relations pointing to UdpNm_TxMessageData
  TxMessageData_UserDataStartIdx        the start index of the 0:n relation pointing to UdpNm_TxMessageData
  TxPduId                               PDU ID for the UdpNm TX Data PDU
  TxUserDataPduId                       PDU handle for the user data PDU
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(UdpNm_PbChannelConfigType, UDPNM_CONST) UdpNm_PbChannelConfig[1];
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnInfoByteConfig
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnInfoByteConfig
  \details
  Element                        Description
  PnClusterResetTimerEndIdx      the end index of the 0:n relation pointing to UdpNm_PnClusterResetTimer
  PnClusterResetTimerStartIdx    the start index of the 0:n relation pointing to UdpNm_PnClusterResetTimer
  PnFilterMask                   PnFilterMask for PnInfoBytes
*/ 
#define UDPNM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(UdpNm_PnInfoByteConfigType, UDPNM_CONST) UdpNm_PnInfoByteConfig[7];
#define UDPNM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_SysToNmChInd
**********************************************************************************************************************/
/** 
  \var    UdpNm_SysToNmChInd
  \brief  Channel indirection: System Channel handle to NM channel handle
*/ 
#define UDPNM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(UdpNm_SysToNmChIndType, UDPNM_CONST) UdpNm_SysToNmChInd[1];
#define UDPNM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_CommState
**********************************************************************************************************************/
/** 
  \var    UdpNm_CommState
  \brief  Internal state for the application's need for communication.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_CommStateUType, UDPNM_VAR_NOINIT) UdpNm_CommState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_CoordReadyToSleepState
**********************************************************************************************************************/
/** 
  \var    UdpNm_CoordReadyToSleepState
  \brief  State for Rx of Coordinator Sleep Ready Bit:
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_CoordReadyToSleepStateUType, UDPNM_VAR_NOINIT) UdpNm_CoordReadyToSleepState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_ImmediateNmMsgCount
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_ImmediateNmMsgCountUType, UDPNM_VAR_NOINIT) UdpNm_ImmediateNmMsgCount;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_ModuleInitialized
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_ModuleInitializedType, UDPNM_VAR_ZERO_INIT) UdpNm_ModuleInitialized;
#define UDPNM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgConfirmationFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgConfirmationFlag
  \brief  Message Confirmation Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_MsgConfirmationFlagUType, UDPNM_VAR_NOINIT) UdpNm_MsgConfirmationFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgIndicationFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgIndicationFlag
  \brief  Message Indication Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_MsgIndicationFlagUType, UDPNM_VAR_NOINIT) UdpNm_MsgIndicationFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgRequest
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgRequest
  \brief  Internal Message Request Variable
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_MsgRequestUType, UDPNM_VAR_NOINIT) UdpNm_MsgRequest;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgTimeoutTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_MsgTimeoutTimerUType, UDPNM_VAR_NOINIT) UdpNm_MsgTimeoutTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_MsgTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_MsgTimer
  \brief  Timer for NM message transmission.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_MsgTimerUType, UDPNM_VAR_NOINIT) UdpNm_MsgTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_NetworkRestartFlag
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_NetworkRestartFlagUType, UDPNM_VAR_NOINIT) UdpNm_NetworkRestartFlag;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_NmState
**********************************************************************************************************************/
/** 
  \var    UdpNm_NmState
  \brief  Current state of the state machine
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_NmStateUType, UDPNM_VAR_NOINIT) UdpNm_NmState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterReq
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterReq
  \brief  Internal Cluster Request Buffer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_PnClusterReqUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterReq;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterReqNew
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterReqNew
  \brief  Internal Cluster Request Buffer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_PnClusterReqNewUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterReqNew;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_PnClusterResetTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_PnClusterResetTimer
  \brief  Pn Cluster Reset Timer
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_PnClusterResetTimerUType, UDPNM_VAR_NOINIT) UdpNm_PnClusterResetTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_RepeatMsgTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_RepeatMsgTimerUType, UDPNM_VAR_NOINIT) UdpNm_RepeatMsgTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_RetryFirstMessageRequestFlag
**********************************************************************************************************************/
/** 
  \var    UdpNm_RetryFirstMessageRequestFlag
  \brief  Retry First Message Request Flag
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_RetryFirstMessageRequestFlagUType, UDPNM_VAR_NOINIT) UdpNm_RetryFirstMessageRequestFlag;  /* PRQA S 0777, 0759 */  /* MD_MSR_Rule5.1, MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TimeoutTimer
**********************************************************************************************************************/
/** 
  \var    UdpNm_TimeoutTimer
  \brief  Timer for NM Algorithm.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_TimeoutTimerUType, UDPNM_VAR_NOINIT) UdpNm_TimeoutTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxControlState
**********************************************************************************************************************/
/** 
  \var    UdpNm_TxControlState
  \brief  Message transmission control state.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_TxControlStateUType, UDPNM_VAR_NOINIT) UdpNm_TxControlState;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxControlStateRequest
**********************************************************************************************************************/
/** 
  \var    UdpNm_TxControlStateRequest
  \brief  Message transmission control state request.
*/ 
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_TxControlStateRequestUType, UDPNM_VAR_NOINIT) UdpNm_TxControlStateRequest;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_TxMessageData
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_TxMessageDataType, UDPNM_VAR_NOINIT) UdpNm_TxMessageData[8];
#define UDPNM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  UdpNm_WaitBusSleepTimer
**********************************************************************************************************************/
#define UDPNM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(UdpNm_WaitBusSleepTimerUType, UDPNM_VAR_NOINIT) UdpNm_WaitBusSleepTimer;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define UDPNM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: POST_BUILD
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/




/**********************************************************************************************************************
 *  FUNCTIONS
 *********************************************************************************************************************/

#define UDPNM_START_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  MAIN FUNCTIONS
 *********************************************************************************************************************/
 
/***********************************************************************************************************************
 *  UdpNm_MainFunction_0()
 **********************************************************************************************************************/
/*! \brief      Numbered Main function of the UdpNm 0
 *  \pre        UdpNm is initialized
 *  \context    Task level
 *  \note       Generated for each independent UdpNm channel
 *  \note       Scheduled by the BSW scheduler
 **********************************************************************************************************************/
FUNC(void, UDPNM_CODE) UdpNm_MainFunction_0(void);


/**********************************************************************************************************************
  UdpNm_LocalMainFunctionChannelSelector()
**********************************************************************************************************************/
/*! \brief       Preselects if ComM channel is connected to a valid UdpNm channel
 *  \details     This function is called by the generated functions UdpNm_Mainfunction_<x>. 
 *               It shall not be called by the application.
 *  \pre         -
 *  \config      -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *********************************************************************************************************************/
extern FUNC( void, UDPNM_CODE ) UdpNm_LocalMainFunctionChannelSelector( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

#define UDPNM_STOP_SEC_CODE
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  END OF FILE: UdpNm_Cfg.h
**********************************************************************************************************************/
#endif /* UDPNM_CFG_H */

