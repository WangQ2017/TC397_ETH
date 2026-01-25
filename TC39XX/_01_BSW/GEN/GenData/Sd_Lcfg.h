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
 *            Module: Sd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Sd_Lcfg.h
 *   Generation Time: 2026-01-24 23:52:01
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined (SD_LCFG_H)
#define SD_LCFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Sd_Types.h"

/**********************************************************************************************************************
*  CAPABILITY RECORD USER FUNCTION CALLOUT DECLARATION
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  SdPCDataSwitches  Sd Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define SD_ADDRESSSTORAGE                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDROFADDRESSSTORAGE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_FLAGSOFADDRESSSTORAGE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXMULTICASTFLAGSOFADDRESSSTORAGE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXMULTICASTSESSIONIDOFADDRESSSTORAGE                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXUNICASTFLAGSOFADDRESSSTORAGE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXUNICASTSESSIONIDOFADDRESSSTORAGE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYNRPENDINGIDXOFADDRESSSTORAGE                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SESSIONIDCOUNTEROFADDRESSSTORAGE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORD                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTR                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENT                                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_AUTOREQUIREOFCLIENT                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDENDIDXOFCLIENT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFCLIENT                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDSTARTIDXOFCLIENT                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDUSEDOFCLIENT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTTIMERIDXOFCLIENT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAYIDXOFCLIENT                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAYUSEDOFCLIENT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPENDIDXOFCLIENT                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPUSEDOFCLIENT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_HANDLEIDOFCLIENT                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDOFCLIENT                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDXOFCLIENT                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MAJORVERSIONOFCLIENT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODIDXOFCLIENT                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODUSEDOFCLIENT                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MINORVERSIONOFCLIENT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MINORVERSIONWILDCARDOFCLIENT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBEROFCLIENT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEIDOFCLIENT                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDENDIDXOFCLIENT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDSTARTIDXOFCLIENT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDUSEDOFCLIENT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONENDIDXOFCLIENT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONSTARTIDXOFCLIENT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONUSEDOFCLIENT                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTDYN                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGESERVERIDXOFCLIENTDYN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CURRENTSTATEOFCLIENTDYN                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTMAINOFCLIENTDYN                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTRXOFCLIENTDYN                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODTCPSOCONIDOFCLIENTDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODUDPSOCONIDOFCLIENTDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_OFFEREDTTLOFCLIENTDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REPETITIONRUNOFCLIENTDYN                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RETRYCOUNTEROFCLIENTDYN                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RETRYTIMEROFCLIENTDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERTCPENDPOINTADDROFCLIENTDYN                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERUDPENDPOINTADDROFCLIENTDYN                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPREQCOUNTEROFCLIENTDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEEXECUTIONREQUESTEDOFCLIENTDYN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEOFCLIENTDYN                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATESWCOFCLIENTDYN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TIMETOTRIGGERSENDOFCLIENTDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TIMERTTLOFCLIENTDYN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLIST                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGEIDXOFCLIENTLIST                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ASSIGNEDTCPSOCONIDOFCLIENTLIST                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ASSIGNEDUDPSOCONIDOFCLIENTLIST                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTSTATEOFCLIENTLIST                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGETCPIDXOFCLIENTLIST                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGEUDPIDXOFCLIENTLIST                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFREFERENCESOFCLIENTLIST                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTEDTTLOFCLIENTLIST                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXRESERVEDOFCLIENTLIST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SUBSCRIBEDUNTILOFCLIENTLIST                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTMAP                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTIDXOFCLIENTMAP                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTUSEDOFCLIENTMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INVALIDHNDOFCLIENTMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTTIMER                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALFINDDELAYMAXOFCLIENTTIMER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALFINDDELAYMINOFCLIENTTIMER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALFINDREPETITIONBASEDELAYOFCLIENTTIMER                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALFINDREPETITIONSMAXOFCLIENTTIMER                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTRESPONSEMAXDELAYOFCLIENTTIMER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTRESPONSEMINDELAYOFCLIENTTIMER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TTLOFCLIENTTIMER                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAY                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUP                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_AUTOREQUIREOFCONSUMEDEVENTGROUP                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTIDXOFCONSUMEDEVENTGROUP                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTTIMERIDXOFCONSUMEDEVENTGROUP                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTGROUPIDOFCONSUMEDEVENTGROUP                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_HANDLEIDOFCONSUMEDEVENTGROUP                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTENDPOINTADDRUSEDOFCONSUMEDEVENTGROUP                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONIDENDIDXOFCONSUMEDEVENTGROUP                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONIDUSEDOFCONSUMEDEVENTGROUP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPMULTICASTACTREFUSEDOFCONSUMEDEVENTGROUP                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTCPACTREFUSEDOFCONSUMEDEVENTGROUP                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPUDPACTREFUSEDOFCONSUMEDEVENTGROUP                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ACKNOWLEDGEDTTLOFCONSUMEDEVENTGROUPDYN                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CURRENTSTATEOFCONSUMEDEVENTGROUPDYN                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTOFCONSUMEDEVENTGROUPDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONIDOFCONSUMEDEVENTGROUPDYN                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXINDICATIONCOUNTOFCONSUMEDEVENTGROUPDYN                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEMODEREQUESTOFCONSUMEDEVENTGROUPDYN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONMARKEDFORCLOSUREOFCONSUMEDEVENTGROUPDYN                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEOFCONSUMEDEVENTGROUPDYN                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDOFCONSUMEDEVENTGROUPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TIMERTTLOFCONSUMEDEVENTGROUPDYN                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERSUBSCRIPTIONOFCONSUMEDEVENTGROUPDYN                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONIDOFCONSUMEDEVENTGROUPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPUSEDOFCONSUMEDEVENTGROUPMAP                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INVALIDHNDOFCONSUMEDEVENTGROUPMAP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGE                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDROFENDPOINTSTORAGE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFREFERENCESOFENDPOINTSTORAGE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TYPEOFENDPOINTSTORAGE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLER                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTENDIDXOFEVENTHANDLER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTSTARTIDXOFEVENTHANDLER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTGROUPIDOFEVENTHANDLER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERMULTICASTUSEDOFEVENTHANDLER                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERTCPIDXOFEVENTHANDLER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERTCPUSEDOFEVENTHANDLER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERUDPIDXOFEVENTHANDLER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERUDPUSEDOFEVENTHANDLER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_HANDLEIDOFEVENTHANDLER                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTTHRESHOLDOFEVENTHANDLER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERIDXOFEVENTHANDLER                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERTIMERIDXOFEVENTHANDLER                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONACTIVATIONMAPENDIDXOFEVENTHANDLER                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONACTIVATIONMAPUSEDOFEVENTHANDLER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERDYN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFCLIENTSOFEVENTHANDLERDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTSTATEOFEVENTHANDLERDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEOFEVENTHANDLERDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERMULTICAST                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERMULTICAST                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONIDOFEVENTHANDLERMULTICAST                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERTCP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERTCP                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERTCP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERUDP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERUDP                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERUDP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_FINALMAGICNUMBER                                                                         STD_OFF  /**< Deactivateable: 'Sd_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define SD_INITDATAHASHCODE                                                                         STD_OFF  /**< Deactivateable: 'Sd_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define SD_INSTANCE                                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGEENDIDXOFINSTANCE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGESTARTIDXOFINSTANCE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDENDIDXOFINSTANCE                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDSTARTIDXOFINSTANCE                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDUSEDOFINSTANCE                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTENDIDXOFINSTANCE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTSTARTIDXOFINSTANCE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTUSEDOFINSTANCE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EMALFORMEDMSGIDOFINSTANCE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENACKRECVIDOFINSTANCE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EOUTOFRESIDOFINSTANCE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGEENDIDXOFINSTANCE                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGESTARTIDXOFINSTANCE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTRXPDUIDOFINSTANCE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTRXSOCONIDOFINSTANCE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_QUEUEPROCESSLIMITOFINSTANCE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RETRYDELAYOFINSTANCE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RETRYMAXOFINSTANCE                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTENDIDXOFINSTANCE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTSTARTIDXOFINSTANCE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTUSEDOFINSTANCE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYENDIDXOFINSTANCE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYSTARTIDXOFINSTANCE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERENDIDXOFINSTANCE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERSTARTIDXOFINSTANCE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERUSEDOFINSTANCE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDENDIDXOFINSTANCE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDSTARTIDXOFINSTANCE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDUSEDOFINSTANCE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TXPDUIDOFINSTANCE                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TXSOCONIDOFINSTANCE                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONENDIDXOFINSTANCE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONSTARTIDXOFINSTANCE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONUSEDOFINSTANCE                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UNICASTRXPDUIDOFINSTANCE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UNICASTRXSOCONIDOFINSTANCE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEDYN                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NEXTSTATEMACHINERUNOFINSTANCEDYN                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RUNMODEOFINSTANCEDYN                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTENDIDXOFINSTANCEDYN                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTLISTFULLOFINSTANCEDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTSTARTIDXOFINSTANCEDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYENDIDXOFINSTANCEDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYNRPENDINGIDXOFINSTANCEDYN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYSTARTIDXOFINSTANCEDYN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEOFINSTANCEDYN                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_IPADDRREQUEST                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PORTSETIDXOFIPADDRREQUEST                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTCNTIDXOFIPADDRREQUEST                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONIDOFIPADDRREQUEST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATICIPCONFIGURATIONOFIPADDRREQUEST                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATICPORTCONFIGURATIONOFIPADDRREQUEST                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MAXNROPTIONSPERENTRY                                                                     STD_ON
#define SD_METHOD                                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFIDXOFMETHOD                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPACTREFUSEDOFMETHOD                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPCONFIGUREDOFMETHOD                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPCONFIGUREDOFMETHOD                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTENDPOINTADDR                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONID                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFOPTIONS                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_OPTIONINDEX                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PAYLOAD                                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PORTSET                                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTCNT                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUP                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPDYN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATUSOFROUTINGGROUPDYN                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENT                                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTIDXOFRXEVENT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERIDXOFRXEVENT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTOFRXEVENT                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRY                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGEIDXOFSENDENTRY                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTIDXOFSENDENTRY                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTIDXOFSENDENTRY                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPIDXOFSENDENTRY                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENTRYTYPEOFSENDENTRY                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERIDOFSENDENTRY                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERIDXOFSENDENTRY                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDOFSENDENTRY                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDXOFSENDENTRY                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MAJORVERSIONOFSENDENTRY                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RESERVEDFIELDOFSENDENTRY                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYNEXTIDXOFSENDENTRY                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERIDXOFSENDENTRY                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEIDOFSENDENTRY                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TIMETOSENDOFSENDENTRY                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_VALIDOFSENDENTRY                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVER                                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_AUTOAVAILABLEOFSERVER                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDENDIDXOFSERVER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFSERVER                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDSTARTIDXOFSERVER                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDUSEDOFSERVER                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAYIDXOFSERVER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAYUSEDOFSERVER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERENDIDXOFSERVER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERSTARTIDXOFSERVER                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERUSEDOFSERVER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_HANDLEIDOFSERVER                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDOFSERVER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEIDXOFSERVER                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MAJORVERSIONOFSERVER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODIDXOFSERVER                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_METHODUSEDOFSERVER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MINORVERSIONOFSERVER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERTIMERIDXOFSERVER                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBEROFSERVER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEIDOFSERVER                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDENDIDXOFSERVER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDSTARTIDXOFSERVER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDUSEDOFSERVER                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONENDIDXOFSERVER                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONSTARTIDXOFSERVER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONUSEDOFSERVER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERDYN                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALOFFERREPETITIONRUNOFSERVERDYN                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPREQCOUNTEROFSERVERDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEEXECUTIONREQUESTEDOFSERVERDYN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEMACHINEOFSERVERDYN                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATESWCOFSERVERDYN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TIMETOTRIGGERSENDOFSERVERDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERMAP                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INVALIDHNDOFSERVERMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERIDXOFSERVERMAP                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERUSEDOFSERVERMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERTIMER                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALOFFERDELAYMAXOFSERVERTIMER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALOFFERDELAYMINOFSERVERTIMER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALOFFERREPETITIONBASEDELAYOFSERVERTIMER                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INITIALOFFERREPETITIONSMAXOFSERVERTIMER                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_OFFERCYCLICDELAYOFSERVERTIMER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTRESPONSEMAXDELAYOFSERVERTIMER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTRESPONSEMINDELAYOFSERVERTIMER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TTLOFSERVERTIMER                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUP                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBERENDIDXOFSERVICEGROUP                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBERSTARTIDXOFSERVICEGROUP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMAP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INVALIDHNDOFSERVICEGROUPMAP                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPIDXOFSERVICEGROUPMAP                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPUSEDOFSERVICEGROUPMAP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTIDXOFSERVICEGROUPMEMBER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTUSEDOFSERVICEGROUPMEMBER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERIDXOFSERVICEGROUPMEMBER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERUSEDOFSERVICEGROUPMEMBER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFADDRESSSTORAGE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCAPABILITYRECORD                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCAPABILITYRECORDFUNCTIONCALLOUTPTR                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENT                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTDYN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTLIST                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTMAP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTTIMER                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCOMMONINITIALDELAY                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUP                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUPDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUPMAP                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFENDPOINTSTORAGE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERMULTICAST                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERTCP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERUDP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFINSTANCE                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFINSTANCEDYN                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFIPADDRREQUEST                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMETHOD                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMULTICASTENDPOINTADDR                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMULTICASTSOCONID                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFOPTIONINDEX                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFPAYLOAD                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFPORTSET                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFREQUESTCNT                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFROUTINGGROUP                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFROUTINGGROUPDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFRXEVENT                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSENDENTRY                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVER                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERDYN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERMAP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERTIMER                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUP                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUPMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUPMEMBER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSOCONACTIVATIONMAP                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTCPSOCONID                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTCPSOCONMODEMAP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTRIGGERTRANSMIT                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFUDPSOCON                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONACTIVATIONMAP                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFACTIVATIONSOFSOCONACTIVATIONMAP                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONIDOFSOCONACTIVATIONMAP                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONID                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONMODEMAP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMIT                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTIDXOFTRIGGERTRANSMIT                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERIDXOFTRIGGERTRANSMIT                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_STATEOFTRIGGERTRANSMIT                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITENDIDX                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITFULL                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITSTARTIDX                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCON                                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_IDOFUDPSOCON                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PRECONFIGUREDOFUDPSOCON                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PCCONFIG                                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ADDRESSSTORAGEOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CAPABILITYRECORDOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTDYNOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTLISTOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTMAPOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTOFPCCONFIG                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CLIENTTIMEROFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_COMMONINITIALDELAYOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPDYNOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPMAPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_CONSUMEDEVENTGROUPOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ENDPOINTSTORAGEOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERDYNOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERMULTICASTOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLEROFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERTCPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_EVENTHANDLERUDPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_FINALMAGICNUMBEROFPCCONFIG                                                               STD_OFF  /**< Deactivateable: 'Sd_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define SD_INITDATAHASHCODEOFPCCONFIG                                                               STD_OFF  /**< Deactivateable: 'Sd_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define SD_INSTANCEDYNOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_INSTANCEOFPCCONFIG                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_IPADDRREQUESTOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MAXNROPTIONSPERENTRYOFPCCONFIG                                                           STD_ON
#define SD_METHODOFPCCONFIG                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTENDPOINTADDROFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_MULTICASTSOCONIDOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_NROFOPTIONSOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_OPTIONINDEXOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PAYLOADOFPCCONFIG                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_PORTSETOFPCCONFIG                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_REQUESTCNTOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPDYNOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_ROUTINGGROUPOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_RXEVENTOFPCCONFIG                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SENDENTRYOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERDYNOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERMAPOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVEROFPCCONFIG                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVERTIMEROFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMAPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPMEMBEROFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SERVICEGROUPOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFADDRESSSTORAGEOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCAPABILITYRECORDOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTDYNOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTLISTOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTMAPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCLIENTTIMEROFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCOMMONINITIALDELAYOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUPDYNOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUPMAPOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFCONSUMEDEVENTGROUPOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFENDPOINTSTORAGEOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERDYNOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERMULTICASTOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLEROFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERTCPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFEVENTHANDLERUDPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFINSTANCEDYNOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFINSTANCEOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFIPADDRREQUESTOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMETHODOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMULTICASTENDPOINTADDROFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFMULTICASTSOCONIDOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFOPTIONINDEXOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFPAYLOADOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFPORTSETOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFREQUESTCNTOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFROUTINGGROUPDYNOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFROUTINGGROUPOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFRXEVENTOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSENDENTRYOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERDYNOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERMAPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVEROFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVERTIMEROFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUPMAPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUPMEMBEROFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSERVICEGROUPOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFSOCONACTIVATIONMAPOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTCPSOCONIDOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTCPSOCONMODEMAPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFTRIGGERTRANSMITOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SIZEOFUDPSOCONOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_SOCONACTIVATIONMAPOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONIDOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TCPSOCONMODEMAPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITENDIDXOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITFULLOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_TRIGGERTRANSMITSTARTIDXOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SD_UDPSOCONOFPCCONFIG                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  SdPCMinNumericValueDefines  Sd Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define SD_MIN_FLAGSOFADDRESSSTORAGE                                                                0u
#define SD_MIN_RXMULTICASTFLAGSOFADDRESSSTORAGE                                                     0u
#define SD_MIN_RXMULTICASTSESSIONIDOFADDRESSSTORAGE                                                 0u
#define SD_MIN_RXUNICASTFLAGSOFADDRESSSTORAGE                                                       0u
#define SD_MIN_RXUNICASTSESSIONIDOFADDRESSSTORAGE                                                   0u
#define SD_MIN_SENDENTRYNRPENDINGIDXOFADDRESSSTORAGE                                                0u
#define SD_MIN_SESSIONIDCOUNTEROFADDRESSSTORAGE                                                     0u
#define SD_MIN_ADDRESSSTORAGESERVERIDXOFCLIENTDYN                                                   0u
#define SD_MIN_OFFEREDTTLOFCLIENTDYN                                                                0u
#define SD_MIN_REPETITIONRUNOFCLIENTDYN                                                             0u
#define SD_MIN_RETRYCOUNTEROFCLIENTDYN                                                              0u
#define SD_MIN_SERVICEGROUPREQCOUNTEROFCLIENTDYN                                                    0u
#define SD_MIN_ADDRESSSTORAGEIDXOFCLIENTLIST                                                        0u
#define SD_MIN_ENDPOINTSTORAGETCPIDXOFCLIENTLIST                                                    0u
#define SD_MIN_ENDPOINTSTORAGEUDPIDXOFCLIENTLIST                                                    0u
#define SD_MIN_NROFREFERENCESOFCLIENTLIST                                                           0u
#define SD_MIN_REQUESTEDTTLOFCLIENTLIST                                                             0u
#define SD_MIN_RXRESERVEDOFCLIENTLIST                                                               0u
#define SD_MIN_COMMONINITIALDELAY                                                                   0u
#define SD_MIN_ACKNOWLEDGEDTTLOFCONSUMEDEVENTGROUPDYN                                               0u
#define SD_MIN_RXINDICATIONCOUNTOFCONSUMEDEVENTGROUPDYN                                             0u
#define SD_MIN_NROFREFERENCESOFENDPOINTSTORAGE                                                      0u
#define SD_MIN_NROFCLIENTSOFEVENTHANDLERDYN                                                         0u
#define SD_MIN_RXEVENTENDIDXOFINSTANCEDYN                                                           0u
#define SD_MIN_RXEVENTSTARTIDXOFINSTANCEDYN                                                         0u
#define SD_MIN_SENDENTRYENDIDXOFINSTANCEDYN                                                         0u
#define SD_MIN_SENDENTRYNRPENDINGIDXOFINSTANCEDYN                                                   0u
#define SD_MIN_SENDENTRYSTARTIDXOFINSTANCEDYN                                                       0u
#define SD_MIN_NROFOPTIONS                                                                          0u
#define SD_MIN_OPTIONINDEX                                                                          0u
#define SD_MIN_PAYLOAD                                                                              0u
#define SD_MIN_REQUESTCNT                                                                           0u
#define SD_MIN_CLIENTLISTIDXOFRXEVENT                                                               0u
#define SD_MIN_EVENTHANDLERIDXOFRXEVENT                                                             0u
#define SD_MIN_ADDRESSSTORAGEIDXOFSENDENTRY                                                         0u
#define SD_MIN_CLIENTIDXOFSENDENTRY                                                                 0u
#define SD_MIN_CLIENTLISTIDXOFSENDENTRY                                                             0u
#define SD_MIN_CONSUMEDEVENTGROUPIDXOFSENDENTRY                                                     0u
#define SD_MIN_EVENTHANDLERIDOFSENDENTRY                                                            0u
#define SD_MIN_EVENTHANDLERIDXOFSENDENTRY                                                           0u
#define SD_MIN_INSTANCEIDOFSENDENTRY                                                                0u
#define SD_MIN_INSTANCEIDXOFSENDENTRY                                                               0u
#define SD_MIN_MAJORVERSIONOFSENDENTRY                                                              0u
#define SD_MIN_RESERVEDFIELDOFSENDENTRY                                                             0u
#define SD_MIN_SENDENTRYNEXTIDXOFSENDENTRY                                                          0u
#define SD_MIN_SERVERIDXOFSENDENTRY                                                                 0u
#define SD_MIN_SERVICEIDOFSENDENTRY                                                                 0u
#define SD_MIN_INITIALOFFERREPETITIONRUNOFSERVERDYN                                                 0u
#define SD_MIN_SERVICEGROUPREQCOUNTEROFSERVERDYN                                                    0u
#define SD_MIN_NROFACTIVATIONSOFSOCONACTIVATIONMAP                                                  0u
#define SD_MIN_CLIENTLISTIDXOFTRIGGERTRANSMIT                                                       0u
#define SD_MIN_EVENTHANDLERIDXOFTRIGGERTRANSMIT                                                     0u
#define SD_MIN_TRIGGERTRANSMITENDIDX                                                                0u
#define SD_MIN_TRIGGERTRANSMITSTARTIDX                                                              0u
/** 
  \}
*/ 

/** 
  \defgroup  SdPCMaxNumericValueDefines  Sd Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define SD_MAX_FLAGSOFADDRESSSTORAGE                                                                255u
#define SD_MAX_RXMULTICASTFLAGSOFADDRESSSTORAGE                                                     255u
#define SD_MAX_RXMULTICASTSESSIONIDOFADDRESSSTORAGE                                                 65535u
#define SD_MAX_RXUNICASTFLAGSOFADDRESSSTORAGE                                                       255u
#define SD_MAX_RXUNICASTSESSIONIDOFADDRESSSTORAGE                                                   65535u
#define SD_MAX_SENDENTRYNRPENDINGIDXOFADDRESSSTORAGE                                                255u
#define SD_MAX_SESSIONIDCOUNTEROFADDRESSSTORAGE                                                     65535u
#define SD_MAX_ADDRESSSTORAGESERVERIDXOFCLIENTDYN                                                   255u
#define SD_MAX_OFFEREDTTLOFCLIENTDYN                                                                4294967295u
#define SD_MAX_REPETITIONRUNOFCLIENTDYN                                                             255u
#define SD_MAX_RETRYCOUNTEROFCLIENTDYN                                                              255u
#define SD_MAX_SERVICEGROUPREQCOUNTEROFCLIENTDYN                                                    255u
#define SD_MAX_ADDRESSSTORAGEIDXOFCLIENTLIST                                                        255u
#define SD_MAX_ENDPOINTSTORAGETCPIDXOFCLIENTLIST                                                    255u
#define SD_MAX_ENDPOINTSTORAGEUDPIDXOFCLIENTLIST                                                    255u
#define SD_MAX_NROFREFERENCESOFCLIENTLIST                                                           255u
#define SD_MAX_REQUESTEDTTLOFCLIENTLIST                                                             4294967295u
#define SD_MAX_RXRESERVEDOFCLIENTLIST                                                               65535u
#define SD_MAX_COMMONINITIALDELAY                                                                   4294967295u
#define SD_MAX_ACKNOWLEDGEDTTLOFCONSUMEDEVENTGROUPDYN                                               4294967295u
#define SD_MAX_RXINDICATIONCOUNTOFCONSUMEDEVENTGROUPDYN                                             255u
#define SD_MAX_NROFREFERENCESOFENDPOINTSTORAGE                                                      255u
#define SD_MAX_NROFCLIENTSOFEVENTHANDLERDYN                                                         65535u
#define SD_MAX_RXEVENTENDIDXOFINSTANCEDYN                                                           255u
#define SD_MAX_RXEVENTSTARTIDXOFINSTANCEDYN                                                         255u
#define SD_MAX_SENDENTRYENDIDXOFINSTANCEDYN                                                         255u
#define SD_MAX_SENDENTRYNRPENDINGIDXOFINSTANCEDYN                                                   255u
#define SD_MAX_SENDENTRYSTARTIDXOFINSTANCEDYN                                                       255u
#define SD_MAX_NROFOPTIONS                                                                          65535u
#define SD_MAX_OPTIONINDEX                                                                          65535u
#define SD_MAX_PAYLOAD                                                                              255u
#define SD_MAX_REQUESTCNT                                                                           65535u
#define SD_MAX_CLIENTLISTIDXOFRXEVENT                                                               255u
#define SD_MAX_EVENTHANDLERIDXOFRXEVENT                                                             255u
#define SD_MAX_ADDRESSSTORAGEIDXOFSENDENTRY                                                         255u
#define SD_MAX_CLIENTIDXOFSENDENTRY                                                                 255u
#define SD_MAX_CLIENTLISTIDXOFSENDENTRY                                                             255u
#define SD_MAX_CONSUMEDEVENTGROUPIDXOFSENDENTRY                                                     255u
#define SD_MAX_EVENTHANDLERIDOFSENDENTRY                                                            65535u
#define SD_MAX_EVENTHANDLERIDXOFSENDENTRY                                                           255u
#define SD_MAX_INSTANCEIDOFSENDENTRY                                                                65535u
#define SD_MAX_INSTANCEIDXOFSENDENTRY                                                               255u
#define SD_MAX_MAJORVERSIONOFSENDENTRY                                                              255u
#define SD_MAX_RESERVEDFIELDOFSENDENTRY                                                             65535u
#define SD_MAX_SENDENTRYNEXTIDXOFSENDENTRY                                                          255u
#define SD_MAX_SERVERIDXOFSENDENTRY                                                                 255u
#define SD_MAX_SERVICEIDOFSENDENTRY                                                                 65535u
#define SD_MAX_INITIALOFFERREPETITIONRUNOFSERVERDYN                                                 255u
#define SD_MAX_SERVICEGROUPREQCOUNTEROFSERVERDYN                                                    255u
#define SD_MAX_NROFACTIVATIONSOFSOCONACTIVATIONMAP                                                  255u
#define SD_MAX_CLIENTLISTIDXOFTRIGGERTRANSMIT                                                       255u
#define SD_MAX_EVENTHANDLERIDXOFTRIGGERTRANSMIT                                                     255u
#define SD_MAX_TRIGGERTRANSMITENDIDX                                                                255u
#define SD_MAX_TRIGGERTRANSMITSTARTIDX                                                              255u
/** 
  \}
*/ 

/** 
  \defgroup  SdPCNoReferenceDefines  Sd No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define SD_NO_CAPABILITYRECORDENDIDXOFCLIENT                                                        255u
#define SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT                                         255u
#define SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT                                                      255u
#define SD_NO_COMMONINITIALDELAYIDXOFCLIENT                                                         255u
#define SD_NO_CONSUMEDEVENTGROUPENDIDXOFCLIENT                                                      255u
#define SD_NO_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT                                                    255u
#define SD_NO_METHODIDXOFCLIENT                                                                     255u
#define SD_NO_TCPSOCONIDENDIDXOFCLIENT                                                              255u
#define SD_NO_TCPSOCONIDSTARTIDXOFCLIENT                                                            255u
#define SD_NO_UDPSOCONENDIDXOFCLIENT                                                                255u
#define SD_NO_UDPSOCONSTARTIDXOFCLIENT                                                              255u
#define SD_NO_ADDRESSSTORAGESERVERIDXOFCLIENTDYN                                                    255u
#define SD_NO_ADDRESSSTORAGEIDXOFCLIENTLIST                                                         255u
#define SD_NO_ENDPOINTSTORAGETCPIDXOFCLIENTLIST                                                     255u
#define SD_NO_ENDPOINTSTORAGEUDPIDXOFCLIENTLIST                                                     255u
#define SD_NO_CLIENTIDXOFCLIENTMAP                                                                  255u
#define SD_NO_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP                                          255u
#define SD_NO_MULTICASTSOCONIDENDIDXOFCONSUMEDEVENTGROUP                                            255u
#define SD_NO_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP                                          255u
#define SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP                                    255u
#define SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP                                          255u
#define SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP                                          255u
#define SD_NO_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP                                          255u
#define SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER                                                255u
#define SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER                                                      255u
#define SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER                                                      255u
#define SD_NO_SOCONACTIVATIONMAPENDIDXOFEVENTHANDLER                                                255u
#define SD_NO_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER                                              255u
#define SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST                                          255u
#define SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP                                                255u
#define SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP                                               255u
#define SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP                                                255u
#define SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP                                               255u
#define SD_NO_CAPABILITYRECORDENDIDXOFINSTANCE                                                      255u
#define SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE                                                    255u
#define SD_NO_CLIENTENDIDXOFINSTANCE                                                                255u
#define SD_NO_CLIENTSTARTIDXOFINSTANCE                                                              255u
#define SD_NO_RXEVENTENDIDXOFINSTANCE                                                               255u
#define SD_NO_RXEVENTSTARTIDXOFINSTANCE                                                             255u
#define SD_NO_SERVERENDIDXOFINSTANCE                                                                255u
#define SD_NO_SERVERSTARTIDXOFINSTANCE                                                              255u
#define SD_NO_TCPSOCONIDENDIDXOFINSTANCE                                                            255u
#define SD_NO_TCPSOCONIDSTARTIDXOFINSTANCE                                                          255u
#define SD_NO_UDPSOCONENDIDXOFINSTANCE                                                              255u
#define SD_NO_UDPSOCONSTARTIDXOFINSTANCE                                                            255u
#define SD_NO_SENDENTRYENDIDXOFINSTANCEDYN                                                          255u
#define SD_NO_SENDENTRYSTARTIDXOFINSTANCEDYN                                                        255u
#define SD_NO_ROUTINGGROUPACTREFIDXOFMETHOD                                                         255u
#define SD_NO_CLIENTLISTIDXOFRXEVENT                                                                255u
#define SD_NO_EVENTHANDLERIDXOFRXEVENT                                                              255u
#define SD_NO_ADDRESSSTORAGEIDXOFSENDENTRY                                                          255u
#define SD_NO_CLIENTIDXOFSENDENTRY                                                                  255u
#define SD_NO_CLIENTLISTIDXOFSENDENTRY                                                              255u
#define SD_NO_CONSUMEDEVENTGROUPIDXOFSENDENTRY                                                      255u
#define SD_NO_EVENTHANDLERIDXOFSENDENTRY                                                            255u
#define SD_NO_INSTANCEIDXOFSENDENTRY                                                                255u
#define SD_NO_SENDENTRYNEXTIDXOFSENDENTRY                                                           255u
#define SD_NO_SERVERIDXOFSENDENTRY                                                                  255u
#define SD_NO_CAPABILITYRECORDENDIDXOFSERVER                                                        255u
#define SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER                                         255u
#define SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER                                                      255u
#define SD_NO_COMMONINITIALDELAYIDXOFSERVER                                                         255u
#define SD_NO_EVENTHANDLERENDIDXOFSERVER                                                            255u
#define SD_NO_EVENTHANDLERSTARTIDXOFSERVER                                                          255u
#define SD_NO_METHODIDXOFSERVER                                                                     255u
#define SD_NO_TCPSOCONIDENDIDXOFSERVER                                                              255u
#define SD_NO_TCPSOCONIDSTARTIDXOFSERVER                                                            255u
#define SD_NO_UDPSOCONENDIDXOFSERVER                                                                255u
#define SD_NO_UDPSOCONSTARTIDXOFSERVER                                                              255u
#define SD_NO_SERVERIDXOFSERVERMAP                                                                  255u
#define SD_NO_SERVICEGROUPIDXOFSERVICEGROUPMAP                                                      255u
#define SD_NO_CLIENTIDXOFSERVICEGROUPMEMBER                                                         255u
#define SD_NO_SERVERIDXOFSERVICEGROUPMEMBER                                                         255u
#define SD_NO_CLIENTLISTIDXOFTRIGGERTRANSMIT                                                        255u
#define SD_NO_EVENTHANDLERIDXOFTRIGGERTRANSMIT                                                      255u
/** 
  \}
*/ 

/** 
  \defgroup  SdPCIsReducedToDefineDefines  Sd Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define SD_ISDEF_CAPABILITYRECORD                                                                   STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTR                                                 STD_OFF
#define SD_ISDEF_AUTOREQUIREOFCLIENT                                                                STD_OFF
#define SD_ISDEF_CAPABILITYRECORDENDIDXOFCLIENT                                                     STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT                                      STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFCLIENT                                     STD_OFF
#define SD_ISDEF_CAPABILITYRECORDSTARTIDXOFCLIENT                                                   STD_OFF
#define SD_ISDEF_CAPABILITYRECORDUSEDOFCLIENT                                                       STD_OFF
#define SD_ISDEF_CLIENTTIMERIDXOFCLIENT                                                             STD_OFF
#define SD_ISDEF_COMMONINITIALDELAYIDXOFCLIENT                                                      STD_OFF
#define SD_ISDEF_COMMONINITIALDELAYUSEDOFCLIENT                                                     STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPENDIDXOFCLIENT                                                   STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT                                                 STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPUSEDOFCLIENT                                                     STD_OFF
#define SD_ISDEF_HANDLEIDOFCLIENT                                                                   STD_OFF
#define SD_ISDEF_INSTANCEIDOFCLIENT                                                                 STD_OFF
#define SD_ISDEF_INSTANCEIDXOFCLIENT                                                                STD_OFF
#define SD_ISDEF_MAJORVERSIONOFCLIENT                                                               STD_OFF
#define SD_ISDEF_METHODIDXOFCLIENT                                                                  STD_OFF
#define SD_ISDEF_METHODUSEDOFCLIENT                                                                 STD_OFF
#define SD_ISDEF_MINORVERSIONOFCLIENT                                                               STD_OFF
#define SD_ISDEF_MINORVERSIONWILDCARDOFCLIENT                                                       STD_OFF
#define SD_ISDEF_SERVICEGROUPMEMBEROFCLIENT                                                         STD_OFF
#define SD_ISDEF_SERVICEIDOFCLIENT                                                                  STD_OFF
#define SD_ISDEF_TCPSOCONIDENDIDXOFCLIENT                                                           STD_OFF
#define SD_ISDEF_TCPSOCONIDSTARTIDXOFCLIENT                                                         STD_OFF
#define SD_ISDEF_TCPSOCONIDUSEDOFCLIENT                                                             STD_OFF
#define SD_ISDEF_UDPSOCONENDIDXOFCLIENT                                                             STD_OFF
#define SD_ISDEF_UDPSOCONSTARTIDXOFCLIENT                                                           STD_OFF
#define SD_ISDEF_UDPSOCONUSEDOFCLIENT                                                               STD_OFF
#define SD_ISDEF_CLIENTIDXOFCLIENTMAP                                                               STD_OFF
#define SD_ISDEF_CLIENTUSEDOFCLIENTMAP                                                              STD_OFF
#define SD_ISDEF_INVALIDHNDOFCLIENTMAP                                                              STD_OFF
#define SD_ISDEF_INITIALFINDDELAYMAXOFCLIENTTIMER                                                   STD_OFF
#define SD_ISDEF_INITIALFINDDELAYMINOFCLIENTTIMER                                                   STD_OFF
#define SD_ISDEF_INITIALFINDREPETITIONBASEDELAYOFCLIENTTIMER                                        STD_OFF
#define SD_ISDEF_INITIALFINDREPETITIONSMAXOFCLIENTTIMER                                             STD_OFF
#define SD_ISDEF_REQUESTRESPONSEMAXDELAYOFCLIENTTIMER                                               STD_OFF
#define SD_ISDEF_REQUESTRESPONSEMINDELAYOFCLIENTTIMER                                               STD_OFF
#define SD_ISDEF_TTLOFCLIENTTIMER                                                                   STD_OFF
#define SD_ISDEF_AUTOREQUIREOFCONSUMEDEVENTGROUP                                                    STD_OFF
#define SD_ISDEF_CLIENTIDXOFCONSUMEDEVENTGROUP                                                      STD_OFF
#define SD_ISDEF_CLIENTTIMERIDXOFCONSUMEDEVENTGROUP                                                 STD_OFF
#define SD_ISDEF_EVENTGROUPIDOFCONSUMEDEVENTGROUP                                                   STD_OFF
#define SD_ISDEF_HANDLEIDOFCONSUMEDEVENTGROUP                                                       STD_OFF
#define SD_ISDEF_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP                                       STD_OFF
#define SD_ISDEF_MULTICASTENDPOINTADDRUSEDOFCONSUMEDEVENTGROUP                                      STD_OFF
#define SD_ISDEF_MULTICASTSOCONIDENDIDXOFCONSUMEDEVENTGROUP                                         STD_OFF
#define SD_ISDEF_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP                                       STD_OFF
#define SD_ISDEF_MULTICASTSOCONIDUSEDOFCONSUMEDEVENTGROUP                                           STD_OFF
#define SD_ISDEF_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP                                 STD_OFF
#define SD_ISDEF_ROUTINGGROUPMULTICASTACTREFUSEDOFCONSUMEDEVENTGROUP                                STD_OFF
#define SD_ISDEF_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP                                       STD_OFF
#define SD_ISDEF_ROUTINGGROUPTCPACTREFUSEDOFCONSUMEDEVENTGROUP                                      STD_OFF
#define SD_ISDEF_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP                                       STD_OFF
#define SD_ISDEF_ROUTINGGROUPUDPACTREFUSEDOFCONSUMEDEVENTGROUP                                      STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP                                       STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPUSEDOFCONSUMEDEVENTGROUPMAP                                      STD_OFF
#define SD_ISDEF_INVALIDHNDOFCONSUMEDEVENTGROUPMAP                                                  STD_OFF
#define SD_ISDEF_CLIENTLISTENDIDXOFEVENTHANDLER                                                     STD_OFF
#define SD_ISDEF_CLIENTLISTSTARTIDXOFEVENTHANDLER                                                   STD_OFF
#define SD_ISDEF_EVENTGROUPIDOFEVENTHANDLER                                                         STD_OFF
#define SD_ISDEF_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER                                             STD_OFF
#define SD_ISDEF_EVENTHANDLERMULTICASTUSEDOFEVENTHANDLER                                            STD_OFF
#define SD_ISDEF_EVENTHANDLERTCPIDXOFEVENTHANDLER                                                   STD_OFF
#define SD_ISDEF_EVENTHANDLERTCPUSEDOFEVENTHANDLER                                                  STD_OFF
#define SD_ISDEF_EVENTHANDLERUDPIDXOFEVENTHANDLER                                                   STD_OFF
#define SD_ISDEF_EVENTHANDLERUDPUSEDOFEVENTHANDLER                                                  STD_OFF
#define SD_ISDEF_HANDLEIDOFEVENTHANDLER                                                             STD_OFF
#define SD_ISDEF_MULTICASTTHRESHOLDOFEVENTHANDLER                                                   STD_OFF
#define SD_ISDEF_SERVERIDXOFEVENTHANDLER                                                            STD_OFF
#define SD_ISDEF_SERVERTIMERIDXOFEVENTHANDLER                                                       STD_OFF
#define SD_ISDEF_SOCONACTIVATIONMAPENDIDXOFEVENTHANDLER                                             STD_OFF
#define SD_ISDEF_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER                                           STD_OFF
#define SD_ISDEF_SOCONACTIVATIONMAPUSEDOFEVENTHANDLER                                               STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST                                       STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERMULTICAST                                      STD_OFF
#define SD_ISDEF_SOCONIDOFEVENTHANDLERMULTICAST                                                     STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP                                             STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERTCP                                            STD_OFF
#define SD_ISDEF_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP                                            STD_OFF
#define SD_ISDEF_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERTCP                                           STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP                                             STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERUDP                                            STD_OFF
#define SD_ISDEF_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP                                            STD_OFF
#define SD_ISDEF_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERUDP                                           STD_OFF
#define SD_ISDEF_ADDRESSSTORAGEENDIDXOFINSTANCE                                                     STD_OFF
#define SD_ISDEF_ADDRESSSTORAGESTARTIDXOFINSTANCE                                                   STD_OFF
#define SD_ISDEF_CAPABILITYRECORDENDIDXOFINSTANCE                                                   STD_OFF
#define SD_ISDEF_CAPABILITYRECORDSTARTIDXOFINSTANCE                                                 STD_OFF
#define SD_ISDEF_CAPABILITYRECORDUSEDOFINSTANCE                                                     STD_OFF
#define SD_ISDEF_CLIENTENDIDXOFINSTANCE                                                             STD_OFF
#define SD_ISDEF_CLIENTSTARTIDXOFINSTANCE                                                           STD_OFF
#define SD_ISDEF_CLIENTUSEDOFINSTANCE                                                               STD_OFF
#define SD_ISDEF_EMALFORMEDMSGIDOFINSTANCE                                                          STD_OFF
#define SD_ISDEF_ENACKRECVIDOFINSTANCE                                                              STD_OFF
#define SD_ISDEF_EOUTOFRESIDOFINSTANCE                                                              STD_OFF
#define SD_ISDEF_ENDPOINTSTORAGEENDIDXOFINSTANCE                                                    STD_OFF
#define SD_ISDEF_ENDPOINTSTORAGESTARTIDXOFINSTANCE                                                  STD_OFF
#define SD_ISDEF_MULTICASTRXPDUIDOFINSTANCE                                                         STD_OFF
#define SD_ISDEF_MULTICASTRXSOCONIDOFINSTANCE                                                       STD_OFF
#define SD_ISDEF_QUEUEPROCESSLIMITOFINSTANCE                                                        STD_OFF
#define SD_ISDEF_RETRYDELAYOFINSTANCE                                                               STD_OFF
#define SD_ISDEF_RETRYMAXOFINSTANCE                                                                 STD_OFF
#define SD_ISDEF_RXEVENTENDIDXOFINSTANCE                                                            STD_OFF
#define SD_ISDEF_RXEVENTSTARTIDXOFINSTANCE                                                          STD_OFF
#define SD_ISDEF_RXEVENTUSEDOFINSTANCE                                                              STD_OFF
#define SD_ISDEF_SENDENTRYENDIDXOFINSTANCE                                                          STD_OFF
#define SD_ISDEF_SENDENTRYSTARTIDXOFINSTANCE                                                        STD_OFF
#define SD_ISDEF_SERVERENDIDXOFINSTANCE                                                             STD_OFF
#define SD_ISDEF_SERVERSTARTIDXOFINSTANCE                                                           STD_OFF
#define SD_ISDEF_SERVERUSEDOFINSTANCE                                                               STD_OFF
#define SD_ISDEF_TCPSOCONIDENDIDXOFINSTANCE                                                         STD_OFF
#define SD_ISDEF_TCPSOCONIDSTARTIDXOFINSTANCE                                                       STD_OFF
#define SD_ISDEF_TCPSOCONIDUSEDOFINSTANCE                                                           STD_OFF
#define SD_ISDEF_TXPDUIDOFINSTANCE                                                                  STD_OFF
#define SD_ISDEF_TXSOCONIDOFINSTANCE                                                                STD_OFF
#define SD_ISDEF_UDPSOCONENDIDXOFINSTANCE                                                           STD_OFF
#define SD_ISDEF_UDPSOCONSTARTIDXOFINSTANCE                                                         STD_OFF
#define SD_ISDEF_UDPSOCONUSEDOFINSTANCE                                                             STD_OFF
#define SD_ISDEF_UNICASTRXPDUIDOFINSTANCE                                                           STD_OFF
#define SD_ISDEF_UNICASTRXSOCONIDOFINSTANCE                                                         STD_OFF
#define SD_ISDEF_PORTSETIDXOFIPADDRREQUEST                                                          STD_OFF
#define SD_ISDEF_REQUESTCNTIDXOFIPADDRREQUEST                                                       STD_OFF
#define SD_ISDEF_SOCONIDOFIPADDRREQUEST                                                             STD_OFF
#define SD_ISDEF_STATICIPCONFIGURATIONOFIPADDRREQUEST                                               STD_OFF
#define SD_ISDEF_STATICPORTCONFIGURATIONOFIPADDRREQUEST                                             STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFIDXOFMETHOD                                                      STD_OFF
#define SD_ISDEF_ROUTINGGROUPACTREFUSEDOFMETHOD                                                     STD_OFF
#define SD_ISDEF_TCPCONFIGUREDOFMETHOD                                                              STD_OFF
#define SD_ISDEF_UDPCONFIGUREDOFMETHOD                                                              STD_OFF
#define SD_ISDEF_MULTICASTSOCONID                                                                   STD_OFF
#define SD_ISDEF_ROUTINGGROUP                                                                       STD_OFF
#define SD_ISDEF_AUTOAVAILABLEOFSERVER                                                              STD_OFF
#define SD_ISDEF_CAPABILITYRECORDENDIDXOFSERVER                                                     STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER                                      STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFSERVER                                     STD_OFF
#define SD_ISDEF_CAPABILITYRECORDSTARTIDXOFSERVER                                                   STD_OFF
#define SD_ISDEF_CAPABILITYRECORDUSEDOFSERVER                                                       STD_OFF
#define SD_ISDEF_COMMONINITIALDELAYIDXOFSERVER                                                      STD_OFF
#define SD_ISDEF_COMMONINITIALDELAYUSEDOFSERVER                                                     STD_OFF
#define SD_ISDEF_EVENTHANDLERENDIDXOFSERVER                                                         STD_OFF
#define SD_ISDEF_EVENTHANDLERSTARTIDXOFSERVER                                                       STD_OFF
#define SD_ISDEF_EVENTHANDLERUSEDOFSERVER                                                           STD_OFF
#define SD_ISDEF_HANDLEIDOFSERVER                                                                   STD_OFF
#define SD_ISDEF_INSTANCEIDOFSERVER                                                                 STD_OFF
#define SD_ISDEF_INSTANCEIDXOFSERVER                                                                STD_OFF
#define SD_ISDEF_MAJORVERSIONOFSERVER                                                               STD_OFF
#define SD_ISDEF_METHODIDXOFSERVER                                                                  STD_OFF
#define SD_ISDEF_METHODUSEDOFSERVER                                                                 STD_OFF
#define SD_ISDEF_MINORVERSIONOFSERVER                                                               STD_OFF
#define SD_ISDEF_SERVERTIMERIDXOFSERVER                                                             STD_OFF
#define SD_ISDEF_SERVICEGROUPMEMBEROFSERVER                                                         STD_OFF
#define SD_ISDEF_SERVICEIDOFSERVER                                                                  STD_OFF
#define SD_ISDEF_TCPSOCONIDENDIDXOFSERVER                                                           STD_OFF
#define SD_ISDEF_TCPSOCONIDSTARTIDXOFSERVER                                                         STD_OFF
#define SD_ISDEF_TCPSOCONIDUSEDOFSERVER                                                             STD_OFF
#define SD_ISDEF_UDPSOCONENDIDXOFSERVER                                                             STD_OFF
#define SD_ISDEF_UDPSOCONSTARTIDXOFSERVER                                                           STD_OFF
#define SD_ISDEF_UDPSOCONUSEDOFSERVER                                                               STD_OFF
#define SD_ISDEF_INVALIDHNDOFSERVERMAP                                                              STD_OFF
#define SD_ISDEF_SERVERIDXOFSERVERMAP                                                               STD_OFF
#define SD_ISDEF_SERVERUSEDOFSERVERMAP                                                              STD_OFF
#define SD_ISDEF_INITIALOFFERDELAYMAXOFSERVERTIMER                                                  STD_OFF
#define SD_ISDEF_INITIALOFFERDELAYMINOFSERVERTIMER                                                  STD_OFF
#define SD_ISDEF_INITIALOFFERREPETITIONBASEDELAYOFSERVERTIMER                                       STD_OFF
#define SD_ISDEF_INITIALOFFERREPETITIONSMAXOFSERVERTIMER                                            STD_OFF
#define SD_ISDEF_OFFERCYCLICDELAYOFSERVERTIMER                                                      STD_OFF
#define SD_ISDEF_REQUESTRESPONSEMAXDELAYOFSERVERTIMER                                               STD_OFF
#define SD_ISDEF_REQUESTRESPONSEMINDELAYOFSERVERTIMER                                               STD_OFF
#define SD_ISDEF_TTLOFSERVERTIMER                                                                   STD_OFF
#define SD_ISDEF_SERVICEGROUPMEMBERENDIDXOFSERVICEGROUP                                             STD_OFF
#define SD_ISDEF_SERVICEGROUPMEMBERSTARTIDXOFSERVICEGROUP                                           STD_OFF
#define SD_ISDEF_INVALIDHNDOFSERVICEGROUPMAP                                                        STD_OFF
#define SD_ISDEF_SERVICEGROUPIDXOFSERVICEGROUPMAP                                                   STD_OFF
#define SD_ISDEF_SERVICEGROUPUSEDOFSERVICEGROUPMAP                                                  STD_OFF
#define SD_ISDEF_CLIENTIDXOFSERVICEGROUPMEMBER                                                      STD_OFF
#define SD_ISDEF_CLIENTUSEDOFSERVICEGROUPMEMBER                                                     STD_OFF
#define SD_ISDEF_SERVERIDXOFSERVICEGROUPMEMBER                                                      STD_OFF
#define SD_ISDEF_SERVERUSEDOFSERVICEGROUPMEMBER                                                     STD_OFF
#define SD_ISDEF_TCPSOCONID                                                                         STD_OFF
#define SD_ISDEF_IDOFUDPSOCON                                                                       STD_OFF
#define SD_ISDEF_PRECONFIGUREDOFUDPSOCON                                                            STD_OFF
#define SD_ISDEF_ADDRESSSTORAGEOFPCCONFIG                                                           STD_OFF
#define SD_ISDEF_CAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                       STD_OFF
#define SD_ISDEF_CAPABILITYRECORDOFPCCONFIG                                                         STD_OFF
#define SD_ISDEF_CLIENTDYNOFPCCONFIG                                                                STD_OFF
#define SD_ISDEF_CLIENTLISTOFPCCONFIG                                                               STD_OFF
#define SD_ISDEF_CLIENTMAPOFPCCONFIG                                                                STD_OFF
#define SD_ISDEF_CLIENTOFPCCONFIG                                                                   STD_OFF
#define SD_ISDEF_CLIENTTIMEROFPCCONFIG                                                              STD_OFF
#define SD_ISDEF_COMMONINITIALDELAYOFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPDYNOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPMAPOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_CONSUMEDEVENTGROUPOFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_ENDPOINTSTORAGEOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_EVENTHANDLERDYNOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_EVENTHANDLERMULTICASTOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_EVENTHANDLEROFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_EVENTHANDLERTCPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_EVENTHANDLERUDPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_INSTANCEDYNOFPCCONFIG                                                              STD_OFF
#define SD_ISDEF_INSTANCEOFPCCONFIG                                                                 STD_OFF
#define SD_ISDEF_IPADDRREQUESTOFPCCONFIG                                                            STD_OFF
#define SD_ISDEF_METHODOFPCCONFIG                                                                   STD_OFF
#define SD_ISDEF_MULTICASTENDPOINTADDROFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_MULTICASTSOCONIDOFPCCONFIG                                                         STD_OFF
#define SD_ISDEF_NROFOPTIONSOFPCCONFIG                                                              STD_OFF
#define SD_ISDEF_OPTIONINDEXOFPCCONFIG                                                              STD_OFF
#define SD_ISDEF_PAYLOADOFPCCONFIG                                                                  STD_OFF
#define SD_ISDEF_PORTSETOFPCCONFIG                                                                  STD_OFF
#define SD_ISDEF_REQUESTCNTOFPCCONFIG                                                               STD_OFF
#define SD_ISDEF_ROUTINGGROUPDYNOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_ROUTINGGROUPOFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_RXEVENTOFPCCONFIG                                                                  STD_OFF
#define SD_ISDEF_SENDENTRYOFPCCONFIG                                                                STD_OFF
#define SD_ISDEF_SERVERDYNOFPCCONFIG                                                                STD_OFF
#define SD_ISDEF_SERVERMAPOFPCCONFIG                                                                STD_OFF
#define SD_ISDEF_SERVEROFPCCONFIG                                                                   STD_OFF
#define SD_ISDEF_SERVERTIMEROFPCCONFIG                                                              STD_OFF
#define SD_ISDEF_SERVICEGROUPMAPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_SERVICEGROUPMEMBEROFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_SERVICEGROUPOFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_SIZEOFADDRESSSTORAGEOFPCCONFIG                                                     STD_OFF
#define SD_ISDEF_SIZEOFCAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                 STD_OFF
#define SD_ISDEF_SIZEOFCAPABILITYRECORDOFPCCONFIG                                                   STD_OFF
#define SD_ISDEF_SIZEOFCLIENTLISTOFPCCONFIG                                                         STD_OFF
#define SD_ISDEF_SIZEOFCLIENTMAPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_SIZEOFCLIENTOFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_SIZEOFCLIENTTIMEROFPCCONFIG                                                        STD_OFF
#define SD_ISDEF_SIZEOFCOMMONINITIALDELAYOFPCCONFIG                                                 STD_OFF
#define SD_ISDEF_SIZEOFCONSUMEDEVENTGROUPMAPOFPCCONFIG                                              STD_OFF
#define SD_ISDEF_SIZEOFCONSUMEDEVENTGROUPOFPCCONFIG                                                 STD_OFF
#define SD_ISDEF_SIZEOFENDPOINTSTORAGEOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_SIZEOFEVENTHANDLERMULTICASTOFPCCONFIG                                              STD_OFF
#define SD_ISDEF_SIZEOFEVENTHANDLEROFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_SIZEOFEVENTHANDLERTCPOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_SIZEOFEVENTHANDLERUDPOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_SIZEOFINSTANCEOFPCCONFIG                                                           STD_OFF
#define SD_ISDEF_SIZEOFIPADDRREQUESTOFPCCONFIG                                                      STD_OFF
#define SD_ISDEF_SIZEOFMETHODOFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_SIZEOFMULTICASTENDPOINTADDROFPCCONFIG                                              STD_OFF
#define SD_ISDEF_SIZEOFMULTICASTSOCONIDOFPCCONFIG                                                   STD_OFF
#define SD_ISDEF_SIZEOFOPTIONINDEXOFPCCONFIG                                                        STD_OFF
#define SD_ISDEF_SIZEOFPAYLOADOFPCCONFIG                                                            STD_OFF
#define SD_ISDEF_SIZEOFPORTSETOFPCCONFIG                                                            STD_OFF
#define SD_ISDEF_SIZEOFREQUESTCNTOFPCCONFIG                                                         STD_OFF
#define SD_ISDEF_SIZEOFROUTINGGROUPOFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_SIZEOFRXEVENTOFPCCONFIG                                                            STD_OFF
#define SD_ISDEF_SIZEOFSENDENTRYOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_SIZEOFSERVERMAPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_SIZEOFSERVEROFPCCONFIG                                                             STD_OFF
#define SD_ISDEF_SIZEOFSERVERTIMEROFPCCONFIG                                                        STD_OFF
#define SD_ISDEF_SIZEOFSERVICEGROUPMAPOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_SIZEOFSERVICEGROUPMEMBEROFPCCONFIG                                                 STD_OFF
#define SD_ISDEF_SIZEOFSERVICEGROUPOFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_SIZEOFSOCONACTIVATIONMAPOFPCCONFIG                                                 STD_OFF
#define SD_ISDEF_SIZEOFTCPSOCONIDOFPCCONFIG                                                         STD_OFF
#define SD_ISDEF_SIZEOFTRIGGERTRANSMITOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_SIZEOFUDPSOCONOFPCCONFIG                                                           STD_OFF
#define SD_ISDEF_SOCONACTIVATIONMAPOFPCCONFIG                                                       STD_OFF
#define SD_ISDEF_TCPSOCONIDOFPCCONFIG                                                               STD_OFF
#define SD_ISDEF_TCPSOCONMODEMAPOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_TRIGGERTRANSMITENDIDXOFPCCONFIG                                                    STD_OFF
#define SD_ISDEF_TRIGGERTRANSMITFULLOFPCCONFIG                                                      STD_OFF
#define SD_ISDEF_TRIGGERTRANSMITOFPCCONFIG                                                          STD_OFF
#define SD_ISDEF_TRIGGERTRANSMITSTARTIDXOFPCCONFIG                                                  STD_OFF
#define SD_ISDEF_UDPSOCONOFPCCONFIG                                                                 STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  SdPCEqualsAlwaysToDefines  Sd Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define SD_EQ2_CAPABILITYRECORD                                                                     
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTR                                                   
#define SD_EQ2_AUTOREQUIREOFCLIENT                                                                  
#define SD_EQ2_CAPABILITYRECORDENDIDXOFCLIENT                                                       
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT                                        
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFCLIENT                                       
#define SD_EQ2_CAPABILITYRECORDSTARTIDXOFCLIENT                                                     
#define SD_EQ2_CAPABILITYRECORDUSEDOFCLIENT                                                         
#define SD_EQ2_CLIENTTIMERIDXOFCLIENT                                                               
#define SD_EQ2_COMMONINITIALDELAYIDXOFCLIENT                                                        
#define SD_EQ2_COMMONINITIALDELAYUSEDOFCLIENT                                                       
#define SD_EQ2_CONSUMEDEVENTGROUPENDIDXOFCLIENT                                                     
#define SD_EQ2_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT                                                   
#define SD_EQ2_CONSUMEDEVENTGROUPUSEDOFCLIENT                                                       
#define SD_EQ2_HANDLEIDOFCLIENT                                                                     
#define SD_EQ2_INSTANCEIDOFCLIENT                                                                   
#define SD_EQ2_INSTANCEIDXOFCLIENT                                                                  
#define SD_EQ2_MAJORVERSIONOFCLIENT                                                                 
#define SD_EQ2_METHODIDXOFCLIENT                                                                    
#define SD_EQ2_METHODUSEDOFCLIENT                                                                   
#define SD_EQ2_MINORVERSIONOFCLIENT                                                                 
#define SD_EQ2_MINORVERSIONWILDCARDOFCLIENT                                                         
#define SD_EQ2_SERVICEGROUPMEMBEROFCLIENT                                                           
#define SD_EQ2_SERVICEIDOFCLIENT                                                                    
#define SD_EQ2_TCPSOCONIDENDIDXOFCLIENT                                                             
#define SD_EQ2_TCPSOCONIDSTARTIDXOFCLIENT                                                           
#define SD_EQ2_TCPSOCONIDUSEDOFCLIENT                                                               
#define SD_EQ2_UDPSOCONENDIDXOFCLIENT                                                               
#define SD_EQ2_UDPSOCONSTARTIDXOFCLIENT                                                             
#define SD_EQ2_UDPSOCONUSEDOFCLIENT                                                                 
#define SD_EQ2_CLIENTIDXOFCLIENTMAP                                                                 
#define SD_EQ2_CLIENTUSEDOFCLIENTMAP                                                                
#define SD_EQ2_INVALIDHNDOFCLIENTMAP                                                                
#define SD_EQ2_INITIALFINDDELAYMAXOFCLIENTTIMER                                                     
#define SD_EQ2_INITIALFINDDELAYMINOFCLIENTTIMER                                                     
#define SD_EQ2_INITIALFINDREPETITIONBASEDELAYOFCLIENTTIMER                                          
#define SD_EQ2_INITIALFINDREPETITIONSMAXOFCLIENTTIMER                                               
#define SD_EQ2_REQUESTRESPONSEMAXDELAYOFCLIENTTIMER                                                 
#define SD_EQ2_REQUESTRESPONSEMINDELAYOFCLIENTTIMER                                                 
#define SD_EQ2_TTLOFCLIENTTIMER                                                                     
#define SD_EQ2_AUTOREQUIREOFCONSUMEDEVENTGROUP                                                      
#define SD_EQ2_CLIENTIDXOFCONSUMEDEVENTGROUP                                                        
#define SD_EQ2_CLIENTTIMERIDXOFCONSUMEDEVENTGROUP                                                   
#define SD_EQ2_EVENTGROUPIDOFCONSUMEDEVENTGROUP                                                     
#define SD_EQ2_HANDLEIDOFCONSUMEDEVENTGROUP                                                         
#define SD_EQ2_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP                                         
#define SD_EQ2_MULTICASTENDPOINTADDRUSEDOFCONSUMEDEVENTGROUP                                        
#define SD_EQ2_MULTICASTSOCONIDENDIDXOFCONSUMEDEVENTGROUP                                           
#define SD_EQ2_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP                                         
#define SD_EQ2_MULTICASTSOCONIDUSEDOFCONSUMEDEVENTGROUP                                             
#define SD_EQ2_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP                                   
#define SD_EQ2_ROUTINGGROUPMULTICASTACTREFUSEDOFCONSUMEDEVENTGROUP                                  
#define SD_EQ2_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP                                         
#define SD_EQ2_ROUTINGGROUPTCPACTREFUSEDOFCONSUMEDEVENTGROUP                                        
#define SD_EQ2_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP                                         
#define SD_EQ2_ROUTINGGROUPUDPACTREFUSEDOFCONSUMEDEVENTGROUP                                        
#define SD_EQ2_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP                                         
#define SD_EQ2_CONSUMEDEVENTGROUPUSEDOFCONSUMEDEVENTGROUPMAP                                        
#define SD_EQ2_INVALIDHNDOFCONSUMEDEVENTGROUPMAP                                                    
#define SD_EQ2_CLIENTLISTENDIDXOFEVENTHANDLER                                                       
#define SD_EQ2_CLIENTLISTSTARTIDXOFEVENTHANDLER                                                     
#define SD_EQ2_EVENTGROUPIDOFEVENTHANDLER                                                           
#define SD_EQ2_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER                                               
#define SD_EQ2_EVENTHANDLERMULTICASTUSEDOFEVENTHANDLER                                              
#define SD_EQ2_EVENTHANDLERTCPIDXOFEVENTHANDLER                                                     
#define SD_EQ2_EVENTHANDLERTCPUSEDOFEVENTHANDLER                                                    
#define SD_EQ2_EVENTHANDLERUDPIDXOFEVENTHANDLER                                                     
#define SD_EQ2_EVENTHANDLERUDPUSEDOFEVENTHANDLER                                                    
#define SD_EQ2_HANDLEIDOFEVENTHANDLER                                                               
#define SD_EQ2_MULTICASTTHRESHOLDOFEVENTHANDLER                                                     
#define SD_EQ2_SERVERIDXOFEVENTHANDLER                                                              
#define SD_EQ2_SERVERTIMERIDXOFEVENTHANDLER                                                         
#define SD_EQ2_SOCONACTIVATIONMAPENDIDXOFEVENTHANDLER                                               
#define SD_EQ2_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER                                             
#define SD_EQ2_SOCONACTIVATIONMAPUSEDOFEVENTHANDLER                                                 
#define SD_EQ2_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST                                         
#define SD_EQ2_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERMULTICAST                                        
#define SD_EQ2_SOCONIDOFEVENTHANDLERMULTICAST                                                       
#define SD_EQ2_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP                                               
#define SD_EQ2_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERTCP                                              
#define SD_EQ2_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP                                              
#define SD_EQ2_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERTCP                                             
#define SD_EQ2_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP                                               
#define SD_EQ2_ROUTINGGROUPACTREFUSEDOFEVENTHANDLERUDP                                              
#define SD_EQ2_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP                                              
#define SD_EQ2_ROUTINGGROUPTRIGGERUSEDOFEVENTHANDLERUDP                                             
#define SD_EQ2_ADDRESSSTORAGEENDIDXOFINSTANCE                                                       
#define SD_EQ2_ADDRESSSTORAGESTARTIDXOFINSTANCE                                                     
#define SD_EQ2_CAPABILITYRECORDENDIDXOFINSTANCE                                                     
#define SD_EQ2_CAPABILITYRECORDSTARTIDXOFINSTANCE                                                   
#define SD_EQ2_CAPABILITYRECORDUSEDOFINSTANCE                                                       
#define SD_EQ2_CLIENTENDIDXOFINSTANCE                                                               
#define SD_EQ2_CLIENTSTARTIDXOFINSTANCE                                                             
#define SD_EQ2_CLIENTUSEDOFINSTANCE                                                                 
#define SD_EQ2_EMALFORMEDMSGIDOFINSTANCE                                                            
#define SD_EQ2_ENACKRECVIDOFINSTANCE                                                                
#define SD_EQ2_EOUTOFRESIDOFINSTANCE                                                                
#define SD_EQ2_ENDPOINTSTORAGEENDIDXOFINSTANCE                                                      
#define SD_EQ2_ENDPOINTSTORAGESTARTIDXOFINSTANCE                                                    
#define SD_EQ2_MULTICASTRXPDUIDOFINSTANCE                                                           
#define SD_EQ2_MULTICASTRXSOCONIDOFINSTANCE                                                         
#define SD_EQ2_QUEUEPROCESSLIMITOFINSTANCE                                                          
#define SD_EQ2_RETRYDELAYOFINSTANCE                                                                 
#define SD_EQ2_RETRYMAXOFINSTANCE                                                                   
#define SD_EQ2_RXEVENTENDIDXOFINSTANCE                                                              
#define SD_EQ2_RXEVENTSTARTIDXOFINSTANCE                                                            
#define SD_EQ2_RXEVENTUSEDOFINSTANCE                                                                
#define SD_EQ2_SENDENTRYENDIDXOFINSTANCE                                                            
#define SD_EQ2_SENDENTRYSTARTIDXOFINSTANCE                                                          
#define SD_EQ2_SERVERENDIDXOFINSTANCE                                                               
#define SD_EQ2_SERVERSTARTIDXOFINSTANCE                                                             
#define SD_EQ2_SERVERUSEDOFINSTANCE                                                                 
#define SD_EQ2_TCPSOCONIDENDIDXOFINSTANCE                                                           
#define SD_EQ2_TCPSOCONIDSTARTIDXOFINSTANCE                                                         
#define SD_EQ2_TCPSOCONIDUSEDOFINSTANCE                                                             
#define SD_EQ2_TXPDUIDOFINSTANCE                                                                    
#define SD_EQ2_TXSOCONIDOFINSTANCE                                                                  
#define SD_EQ2_UDPSOCONENDIDXOFINSTANCE                                                             
#define SD_EQ2_UDPSOCONSTARTIDXOFINSTANCE                                                           
#define SD_EQ2_UDPSOCONUSEDOFINSTANCE                                                               
#define SD_EQ2_UNICASTRXPDUIDOFINSTANCE                                                             
#define SD_EQ2_UNICASTRXSOCONIDOFINSTANCE                                                           
#define SD_EQ2_PORTSETIDXOFIPADDRREQUEST                                                            
#define SD_EQ2_REQUESTCNTIDXOFIPADDRREQUEST                                                         
#define SD_EQ2_SOCONIDOFIPADDRREQUEST                                                               
#define SD_EQ2_STATICIPCONFIGURATIONOFIPADDRREQUEST                                                 
#define SD_EQ2_STATICPORTCONFIGURATIONOFIPADDRREQUEST                                               
#define SD_EQ2_ROUTINGGROUPACTREFIDXOFMETHOD                                                        
#define SD_EQ2_ROUTINGGROUPACTREFUSEDOFMETHOD                                                       
#define SD_EQ2_TCPCONFIGUREDOFMETHOD                                                                
#define SD_EQ2_UDPCONFIGUREDOFMETHOD                                                                
#define SD_EQ2_MULTICASTSOCONID                                                                     
#define SD_EQ2_ROUTINGGROUP                                                                         
#define SD_EQ2_AUTOAVAILABLEOFSERVER                                                                
#define SD_EQ2_CAPABILITYRECORDENDIDXOFSERVER                                                       
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER                                        
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTRUSEDOFSERVER                                       
#define SD_EQ2_CAPABILITYRECORDSTARTIDXOFSERVER                                                     
#define SD_EQ2_CAPABILITYRECORDUSEDOFSERVER                                                         
#define SD_EQ2_COMMONINITIALDELAYIDXOFSERVER                                                        
#define SD_EQ2_COMMONINITIALDELAYUSEDOFSERVER                                                       
#define SD_EQ2_EVENTHANDLERENDIDXOFSERVER                                                           
#define SD_EQ2_EVENTHANDLERSTARTIDXOFSERVER                                                         
#define SD_EQ2_EVENTHANDLERUSEDOFSERVER                                                             
#define SD_EQ2_HANDLEIDOFSERVER                                                                     
#define SD_EQ2_INSTANCEIDOFSERVER                                                                   
#define SD_EQ2_INSTANCEIDXOFSERVER                                                                  
#define SD_EQ2_MAJORVERSIONOFSERVER                                                                 
#define SD_EQ2_METHODIDXOFSERVER                                                                    
#define SD_EQ2_METHODUSEDOFSERVER                                                                   
#define SD_EQ2_MINORVERSIONOFSERVER                                                                 
#define SD_EQ2_SERVERTIMERIDXOFSERVER                                                               
#define SD_EQ2_SERVICEGROUPMEMBEROFSERVER                                                           
#define SD_EQ2_SERVICEIDOFSERVER                                                                    
#define SD_EQ2_TCPSOCONIDENDIDXOFSERVER                                                             
#define SD_EQ2_TCPSOCONIDSTARTIDXOFSERVER                                                           
#define SD_EQ2_TCPSOCONIDUSEDOFSERVER                                                               
#define SD_EQ2_UDPSOCONENDIDXOFSERVER                                                               
#define SD_EQ2_UDPSOCONSTARTIDXOFSERVER                                                             
#define SD_EQ2_UDPSOCONUSEDOFSERVER                                                                 
#define SD_EQ2_INVALIDHNDOFSERVERMAP                                                                
#define SD_EQ2_SERVERIDXOFSERVERMAP                                                                 
#define SD_EQ2_SERVERUSEDOFSERVERMAP                                                                
#define SD_EQ2_INITIALOFFERDELAYMAXOFSERVERTIMER                                                    
#define SD_EQ2_INITIALOFFERDELAYMINOFSERVERTIMER                                                    
#define SD_EQ2_INITIALOFFERREPETITIONBASEDELAYOFSERVERTIMER                                         
#define SD_EQ2_INITIALOFFERREPETITIONSMAXOFSERVERTIMER                                              
#define SD_EQ2_OFFERCYCLICDELAYOFSERVERTIMER                                                        
#define SD_EQ2_REQUESTRESPONSEMAXDELAYOFSERVERTIMER                                                 
#define SD_EQ2_REQUESTRESPONSEMINDELAYOFSERVERTIMER                                                 
#define SD_EQ2_TTLOFSERVERTIMER                                                                     
#define SD_EQ2_SERVICEGROUPMEMBERENDIDXOFSERVICEGROUP                                               
#define SD_EQ2_SERVICEGROUPMEMBERSTARTIDXOFSERVICEGROUP                                             
#define SD_EQ2_INVALIDHNDOFSERVICEGROUPMAP                                                          
#define SD_EQ2_SERVICEGROUPIDXOFSERVICEGROUPMAP                                                     
#define SD_EQ2_SERVICEGROUPUSEDOFSERVICEGROUPMAP                                                    
#define SD_EQ2_CLIENTIDXOFSERVICEGROUPMEMBER                                                        
#define SD_EQ2_CLIENTUSEDOFSERVICEGROUPMEMBER                                                       
#define SD_EQ2_SERVERIDXOFSERVICEGROUPMEMBER                                                        
#define SD_EQ2_SERVERUSEDOFSERVICEGROUPMEMBER                                                       
#define SD_EQ2_TCPSOCONID                                                                           
#define SD_EQ2_IDOFUDPSOCON                                                                         
#define SD_EQ2_PRECONFIGUREDOFUDPSOCON                                                              
#define SD_EQ2_ADDRESSSTORAGEOFPCCONFIG                                                             
#define SD_EQ2_CAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                         
#define SD_EQ2_CAPABILITYRECORDOFPCCONFIG                                                           
#define SD_EQ2_CLIENTDYNOFPCCONFIG                                                                  
#define SD_EQ2_CLIENTLISTOFPCCONFIG                                                                 
#define SD_EQ2_CLIENTMAPOFPCCONFIG                                                                  
#define SD_EQ2_CLIENTOFPCCONFIG                                                                     
#define SD_EQ2_CLIENTTIMEROFPCCONFIG                                                                
#define SD_EQ2_COMMONINITIALDELAYOFPCCONFIG                                                         
#define SD_EQ2_CONSUMEDEVENTGROUPDYNOFPCCONFIG                                                      
#define SD_EQ2_CONSUMEDEVENTGROUPMAPOFPCCONFIG                                                      
#define SD_EQ2_CONSUMEDEVENTGROUPOFPCCONFIG                                                         
#define SD_EQ2_ENDPOINTSTORAGEOFPCCONFIG                                                            
#define SD_EQ2_EVENTHANDLERDYNOFPCCONFIG                                                            
#define SD_EQ2_EVENTHANDLERMULTICASTOFPCCONFIG                                                      
#define SD_EQ2_EVENTHANDLEROFPCCONFIG                                                               
#define SD_EQ2_EVENTHANDLERTCPOFPCCONFIG                                                            
#define SD_EQ2_EVENTHANDLERUDPOFPCCONFIG                                                            
#define SD_EQ2_INSTANCEDYNOFPCCONFIG                                                                
#define SD_EQ2_INSTANCEOFPCCONFIG                                                                   
#define SD_EQ2_IPADDRREQUESTOFPCCONFIG                                                              
#define SD_EQ2_METHODOFPCCONFIG                                                                     
#define SD_EQ2_MULTICASTENDPOINTADDROFPCCONFIG                                                      
#define SD_EQ2_MULTICASTSOCONIDOFPCCONFIG                                                           
#define SD_EQ2_NROFOPTIONSOFPCCONFIG                                                                
#define SD_EQ2_OPTIONINDEXOFPCCONFIG                                                                
#define SD_EQ2_PAYLOADOFPCCONFIG                                                                    
#define SD_EQ2_PORTSETOFPCCONFIG                                                                    
#define SD_EQ2_REQUESTCNTOFPCCONFIG                                                                 
#define SD_EQ2_ROUTINGGROUPDYNOFPCCONFIG                                                            
#define SD_EQ2_ROUTINGGROUPOFPCCONFIG                                                               
#define SD_EQ2_RXEVENTOFPCCONFIG                                                                    
#define SD_EQ2_SENDENTRYOFPCCONFIG                                                                  
#define SD_EQ2_SERVERDYNOFPCCONFIG                                                                  
#define SD_EQ2_SERVERMAPOFPCCONFIG                                                                  
#define SD_EQ2_SERVEROFPCCONFIG                                                                     
#define SD_EQ2_SERVERTIMEROFPCCONFIG                                                                
#define SD_EQ2_SERVICEGROUPMAPOFPCCONFIG                                                            
#define SD_EQ2_SERVICEGROUPMEMBEROFPCCONFIG                                                         
#define SD_EQ2_SERVICEGROUPOFPCCONFIG                                                               
#define SD_EQ2_SIZEOFADDRESSSTORAGEOFPCCONFIG                                                       
#define SD_EQ2_SIZEOFCAPABILITYRECORDFUNCTIONCALLOUTPTROFPCCONFIG                                   
#define SD_EQ2_SIZEOFCAPABILITYRECORDOFPCCONFIG                                                     
#define SD_EQ2_SIZEOFCLIENTLISTOFPCCONFIG                                                           
#define SD_EQ2_SIZEOFCLIENTMAPOFPCCONFIG                                                            
#define SD_EQ2_SIZEOFCLIENTOFPCCONFIG                                                               
#define SD_EQ2_SIZEOFCLIENTTIMEROFPCCONFIG                                                          
#define SD_EQ2_SIZEOFCOMMONINITIALDELAYOFPCCONFIG                                                   
#define SD_EQ2_SIZEOFCONSUMEDEVENTGROUPMAPOFPCCONFIG                                                
#define SD_EQ2_SIZEOFCONSUMEDEVENTGROUPOFPCCONFIG                                                   
#define SD_EQ2_SIZEOFENDPOINTSTORAGEOFPCCONFIG                                                      
#define SD_EQ2_SIZEOFEVENTHANDLERMULTICASTOFPCCONFIG                                                
#define SD_EQ2_SIZEOFEVENTHANDLEROFPCCONFIG                                                         
#define SD_EQ2_SIZEOFEVENTHANDLERTCPOFPCCONFIG                                                      
#define SD_EQ2_SIZEOFEVENTHANDLERUDPOFPCCONFIG                                                      
#define SD_EQ2_SIZEOFINSTANCEOFPCCONFIG                                                             
#define SD_EQ2_SIZEOFIPADDRREQUESTOFPCCONFIG                                                        
#define SD_EQ2_SIZEOFMETHODOFPCCONFIG                                                               
#define SD_EQ2_SIZEOFMULTICASTENDPOINTADDROFPCCONFIG                                                
#define SD_EQ2_SIZEOFMULTICASTSOCONIDOFPCCONFIG                                                     
#define SD_EQ2_SIZEOFOPTIONINDEXOFPCCONFIG                                                          
#define SD_EQ2_SIZEOFPAYLOADOFPCCONFIG                                                              
#define SD_EQ2_SIZEOFPORTSETOFPCCONFIG                                                              
#define SD_EQ2_SIZEOFREQUESTCNTOFPCCONFIG                                                           
#define SD_EQ2_SIZEOFROUTINGGROUPOFPCCONFIG                                                         
#define SD_EQ2_SIZEOFRXEVENTOFPCCONFIG                                                              
#define SD_EQ2_SIZEOFSENDENTRYOFPCCONFIG                                                            
#define SD_EQ2_SIZEOFSERVERMAPOFPCCONFIG                                                            
#define SD_EQ2_SIZEOFSERVEROFPCCONFIG                                                               
#define SD_EQ2_SIZEOFSERVERTIMEROFPCCONFIG                                                          
#define SD_EQ2_SIZEOFSERVICEGROUPMAPOFPCCONFIG                                                      
#define SD_EQ2_SIZEOFSERVICEGROUPMEMBEROFPCCONFIG                                                   
#define SD_EQ2_SIZEOFSERVICEGROUPOFPCCONFIG                                                         
#define SD_EQ2_SIZEOFSOCONACTIVATIONMAPOFPCCONFIG                                                   
#define SD_EQ2_SIZEOFTCPSOCONIDOFPCCONFIG                                                           
#define SD_EQ2_SIZEOFTRIGGERTRANSMITOFPCCONFIG                                                      
#define SD_EQ2_SIZEOFUDPSOCONOFPCCONFIG                                                             
#define SD_EQ2_SOCONACTIVATIONMAPOFPCCONFIG                                                         
#define SD_EQ2_TCPSOCONIDOFPCCONFIG                                                                 
#define SD_EQ2_TCPSOCONMODEMAPOFPCCONFIG                                                            
#define SD_EQ2_TRIGGERTRANSMITENDIDXOFPCCONFIG                                                      
#define SD_EQ2_TRIGGERTRANSMITFULLOFPCCONFIG                                                        
#define SD_EQ2_TRIGGERTRANSMITOFPCCONFIG                                                            
#define SD_EQ2_TRIGGERTRANSMITSTARTIDXOFPCCONFIG                                                    
#define SD_EQ2_UDPSOCONOFPCCONFIG                                                                   
/** 
  \}
*/ 

/** 
  \defgroup  SdPCSymbolicInitializationPointers  Sd Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Sd_Config_Ptr                                                                               &(Sd_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'Sd' */
/** 
  \}
*/ 

/** 
  \defgroup  SdPCInitializationSymbols  Sd Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Sd_Config                                                                                   Sd_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'Sd */
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGeneral  Sd General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define SD_CHECK_INIT_POINTER                                                                       STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define SD_FINAL_MAGIC_NUMBER                                                                       0xAB1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Sd */
#define SD_INDIVIDUAL_POSTBUILD                                                                     STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Sd' is not configured to be postbuild capable. */
#define SD_INIT_DATA                                                                                SD_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define SD_INIT_DATA_HASH_CODE                                                                      -199957183  /**< the precompile constant to validate the initialization structure at initialization time of Sd with a hashcode. The seed value is '0xAB1Eu' */
#define SD_USE_ECUM_BSW_ERROR_HOOK                                                                  STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define SD_USE_INIT_POINTER                                                                         STD_ON  /**< STD_ON if the init pointer Sd shall be used. */
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
  \defgroup  SdPCGetRootDataMacros  Sd Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define Sd_GetAddressStorageOfPCConfig()                                                            Sd_ConfigDataPtr->AddressStorageOfPCConfig
#define Sd_GetCapabilityRecordFunctionCalloutPtrOfPCConfig()                                        Sd_ConfigDataPtr->CapabilityRecordFunctionCalloutPtrOfPCConfig
#define Sd_GetCapabilityRecordOfPCConfig()                                                          Sd_ConfigDataPtr->CapabilityRecordOfPCConfig
#define Sd_GetClientDynOfPCConfig()                                                                 Sd_ConfigDataPtr->ClientDynOfPCConfig
#define Sd_GetClientListOfPCConfig()                                                                Sd_ConfigDataPtr->ClientListOfPCConfig
#define Sd_GetClientMapOfPCConfig()                                                                 Sd_ConfigDataPtr->ClientMapOfPCConfig
#define Sd_GetClientOfPCConfig()                                                                    Sd_ConfigDataPtr->ClientOfPCConfig
#define Sd_GetClientTimerOfPCConfig()                                                               Sd_ConfigDataPtr->ClientTimerOfPCConfig
#define Sd_GetCommonInitialDelayOfPCConfig()                                                        Sd_ConfigDataPtr->CommonInitialDelayOfPCConfig
#define Sd_GetConsumedEventgroupDynOfPCConfig()                                                     Sd_ConfigDataPtr->ConsumedEventgroupDynOfPCConfig
#define Sd_GetConsumedEventgroupMapOfPCConfig()                                                     Sd_ConfigDataPtr->ConsumedEventgroupMapOfPCConfig
#define Sd_GetConsumedEventgroupOfPCConfig()                                                        Sd_ConfigDataPtr->ConsumedEventgroupOfPCConfig
#define Sd_GetEndpointStorageOfPCConfig()                                                           Sd_ConfigDataPtr->EndpointStorageOfPCConfig
#define Sd_GetEventHandlerDynOfPCConfig()                                                           Sd_ConfigDataPtr->EventHandlerDynOfPCConfig
#define Sd_GetEventHandlerMulticastOfPCConfig()                                                     Sd_ConfigDataPtr->EventHandlerMulticastOfPCConfig
#define Sd_GetEventHandlerOfPCConfig()                                                              Sd_ConfigDataPtr->EventHandlerOfPCConfig
#define Sd_GetEventHandlerTcpOfPCConfig()                                                           Sd_ConfigDataPtr->EventHandlerTcpOfPCConfig
#define Sd_GetEventHandlerUdpOfPCConfig()                                                           Sd_ConfigDataPtr->EventHandlerUdpOfPCConfig
#define Sd_GetInstanceDynOfPCConfig()                                                               Sd_ConfigDataPtr->InstanceDynOfPCConfig
#define Sd_GetInstanceOfPCConfig()                                                                  Sd_ConfigDataPtr->InstanceOfPCConfig
#define Sd_GetIpAddrRequestOfPCConfig()                                                             Sd_ConfigDataPtr->IpAddrRequestOfPCConfig
#define Sd_GetMethodOfPCConfig()                                                                    Sd_ConfigDataPtr->MethodOfPCConfig
#define Sd_GetMulticastEndpointAddrOfPCConfig()                                                     Sd_ConfigDataPtr->MulticastEndpointAddrOfPCConfig
#define Sd_GetMulticastSoConIdOfPCConfig()                                                          Sd_ConfigDataPtr->MulticastSoConIdOfPCConfig
#define Sd_GetNrOfOptionsOfPCConfig()                                                               Sd_ConfigDataPtr->NrOfOptionsOfPCConfig
#define Sd_GetOptionIndexOfPCConfig()                                                               Sd_ConfigDataPtr->OptionIndexOfPCConfig
#define Sd_GetPayloadOfPCConfig()                                                                   Sd_ConfigDataPtr->PayloadOfPCConfig
#define Sd_GetPortSetOfPCConfig()                                                                   Sd_ConfigDataPtr->PortSetOfPCConfig
#define Sd_GetRequestCntOfPCConfig()                                                                Sd_ConfigDataPtr->RequestCntOfPCConfig
#define Sd_GetRoutingGroupDynOfPCConfig()                                                           Sd_ConfigDataPtr->RoutingGroupDynOfPCConfig
#define Sd_GetRoutingGroupOfPCConfig()                                                              Sd_ConfigDataPtr->RoutingGroupOfPCConfig
#define Sd_GetRxEventOfPCConfig()                                                                   Sd_ConfigDataPtr->RxEventOfPCConfig
#define Sd_GetSendEntryOfPCConfig()                                                                 Sd_ConfigDataPtr->SendEntryOfPCConfig
#define Sd_GetServerDynOfPCConfig()                                                                 Sd_ConfigDataPtr->ServerDynOfPCConfig
#define Sd_GetServerMapOfPCConfig()                                                                 Sd_ConfigDataPtr->ServerMapOfPCConfig
#define Sd_GetServerOfPCConfig()                                                                    Sd_ConfigDataPtr->ServerOfPCConfig
#define Sd_GetServerTimerOfPCConfig()                                                               Sd_ConfigDataPtr->ServerTimerOfPCConfig
#define Sd_GetServiceGroupMapOfPCConfig()                                                           Sd_ConfigDataPtr->ServiceGroupMapOfPCConfig
#define Sd_GetServiceGroupMemberOfPCConfig()                                                        Sd_ConfigDataPtr->ServiceGroupMemberOfPCConfig
#define Sd_GetServiceGroupOfPCConfig()                                                              Sd_ConfigDataPtr->ServiceGroupOfPCConfig
#define Sd_GetSizeOfAddressStorageOfPCConfig()                                                      Sd_ConfigDataPtr->SizeOfAddressStorageOfPCConfig
#define Sd_GetSizeOfCapabilityRecordFunctionCalloutPtrOfPCConfig()                                  Sd_ConfigDataPtr->SizeOfCapabilityRecordFunctionCalloutPtrOfPCConfig
#define Sd_GetSizeOfCapabilityRecordOfPCConfig()                                                    Sd_ConfigDataPtr->SizeOfCapabilityRecordOfPCConfig
#define Sd_GetSizeOfClientListOfPCConfig()                                                          Sd_ConfigDataPtr->SizeOfClientListOfPCConfig
#define Sd_GetSizeOfClientMapOfPCConfig()                                                           Sd_ConfigDataPtr->SizeOfClientMapOfPCConfig
#define Sd_GetSizeOfClientOfPCConfig()                                                              Sd_ConfigDataPtr->SizeOfClientOfPCConfig
#define Sd_GetSizeOfClientTimerOfPCConfig()                                                         Sd_ConfigDataPtr->SizeOfClientTimerOfPCConfig
#define Sd_GetSizeOfCommonInitialDelayOfPCConfig()                                                  Sd_ConfigDataPtr->SizeOfCommonInitialDelayOfPCConfig
#define Sd_GetSizeOfConsumedEventgroupMapOfPCConfig()                                               Sd_ConfigDataPtr->SizeOfConsumedEventgroupMapOfPCConfig
#define Sd_GetSizeOfConsumedEventgroupOfPCConfig()                                                  Sd_ConfigDataPtr->SizeOfConsumedEventgroupOfPCConfig
#define Sd_GetSizeOfEndpointStorageOfPCConfig()                                                     Sd_ConfigDataPtr->SizeOfEndpointStorageOfPCConfig
#define Sd_GetSizeOfEventHandlerMulticastOfPCConfig()                                               Sd_ConfigDataPtr->SizeOfEventHandlerMulticastOfPCConfig
#define Sd_GetSizeOfEventHandlerOfPCConfig()                                                        Sd_ConfigDataPtr->SizeOfEventHandlerOfPCConfig
#define Sd_GetSizeOfEventHandlerTcpOfPCConfig()                                                     Sd_ConfigDataPtr->SizeOfEventHandlerTcpOfPCConfig
#define Sd_GetSizeOfEventHandlerUdpOfPCConfig()                                                     Sd_ConfigDataPtr->SizeOfEventHandlerUdpOfPCConfig
#define Sd_GetSizeOfInstanceOfPCConfig()                                                            Sd_ConfigDataPtr->SizeOfInstanceOfPCConfig
#define Sd_GetSizeOfIpAddrRequestOfPCConfig()                                                       Sd_ConfigDataPtr->SizeOfIpAddrRequestOfPCConfig
#define Sd_GetSizeOfMethodOfPCConfig()                                                              Sd_ConfigDataPtr->SizeOfMethodOfPCConfig
#define Sd_GetSizeOfMulticastEndpointAddrOfPCConfig()                                               Sd_ConfigDataPtr->SizeOfMulticastEndpointAddrOfPCConfig
#define Sd_GetSizeOfMulticastSoConIdOfPCConfig()                                                    Sd_ConfigDataPtr->SizeOfMulticastSoConIdOfPCConfig
#define Sd_GetSizeOfOptionIndexOfPCConfig()                                                         Sd_ConfigDataPtr->SizeOfOptionIndexOfPCConfig
#define Sd_GetSizeOfPayloadOfPCConfig()                                                             Sd_ConfigDataPtr->SizeOfPayloadOfPCConfig
#define Sd_GetSizeOfPortSetOfPCConfig()                                                             Sd_ConfigDataPtr->SizeOfPortSetOfPCConfig
#define Sd_GetSizeOfRequestCntOfPCConfig()                                                          Sd_ConfigDataPtr->SizeOfRequestCntOfPCConfig
#define Sd_GetSizeOfRoutingGroupOfPCConfig()                                                        Sd_ConfigDataPtr->SizeOfRoutingGroupOfPCConfig
#define Sd_GetSizeOfRxEventOfPCConfig()                                                             Sd_ConfigDataPtr->SizeOfRxEventOfPCConfig
#define Sd_GetSizeOfSendEntryOfPCConfig()                                                           Sd_ConfigDataPtr->SizeOfSendEntryOfPCConfig
#define Sd_GetSizeOfServerMapOfPCConfig()                                                           Sd_ConfigDataPtr->SizeOfServerMapOfPCConfig
#define Sd_GetSizeOfServerOfPCConfig()                                                              Sd_ConfigDataPtr->SizeOfServerOfPCConfig
#define Sd_GetSizeOfServerTimerOfPCConfig()                                                         Sd_ConfigDataPtr->SizeOfServerTimerOfPCConfig
#define Sd_GetSizeOfServiceGroupMapOfPCConfig()                                                     Sd_ConfigDataPtr->SizeOfServiceGroupMapOfPCConfig
#define Sd_GetSizeOfServiceGroupMemberOfPCConfig()                                                  Sd_ConfigDataPtr->SizeOfServiceGroupMemberOfPCConfig
#define Sd_GetSizeOfServiceGroupOfPCConfig()                                                        Sd_ConfigDataPtr->SizeOfServiceGroupOfPCConfig
#define Sd_GetSizeOfSoConActivationMapOfPCConfig()                                                  Sd_ConfigDataPtr->SizeOfSoConActivationMapOfPCConfig
#define Sd_GetSizeOfTcpSoConIdOfPCConfig()                                                          Sd_ConfigDataPtr->SizeOfTcpSoConIdOfPCConfig
#define Sd_GetSizeOfTriggerTransmitOfPCConfig()                                                     Sd_ConfigDataPtr->SizeOfTriggerTransmitOfPCConfig
#define Sd_GetSizeOfUdpSoConOfPCConfig()                                                            Sd_ConfigDataPtr->SizeOfUdpSoConOfPCConfig
#define Sd_GetSoConActivationMapOfPCConfig()                                                        Sd_ConfigDataPtr->SoConActivationMapOfPCConfig
#define Sd_GetTcpSoConIdOfPCConfig()                                                                Sd_ConfigDataPtr->TcpSoConIdOfPCConfig
#define Sd_GetTcpSoConModeMapOfPCConfig()                                                           Sd_ConfigDataPtr->TcpSoConModeMapOfPCConfig
#define Sd_GetTriggerTransmitEndIdxOfPCConfig()                                                     Sd_ConfigDataPtr->TriggerTransmitEndIdxOfPCConfig
#define Sd_GetTriggerTransmitFullOfPCConfig()                                                       Sd_ConfigDataPtr->TriggerTransmitFullOfPCConfig
#define Sd_GetTriggerTransmitOfPCConfig()                                                           Sd_ConfigDataPtr->TriggerTransmitOfPCConfig
#define Sd_GetTriggerTransmitStartIdxOfPCConfig()                                                   Sd_ConfigDataPtr->TriggerTransmitStartIdxOfPCConfig
#define Sd_GetUdpSoConOfPCConfig()                                                                  Sd_ConfigDataPtr->UdpSoConOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGetConstantDuplicatedRootDataMacros  Sd Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define Sd_GetMaxNrOptionsPerEntryOfPCConfig()                                                      10u
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGetDuplicatedRootDataMacros  Sd Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Sd_GetSizeOfClientDynOfPCConfig()                                                           Sd_GetSizeOfClientOfPCConfig()  /**< the number of accomplishable value elements in Sd_ClientDyn */
#define Sd_GetSizeOfConsumedEventgroupDynOfPCConfig()                                               Sd_GetSizeOfConsumedEventgroupOfPCConfig()  /**< the number of accomplishable value elements in Sd_ConsumedEventgroupDyn */
#define Sd_GetSizeOfEventHandlerDynOfPCConfig()                                                     Sd_GetSizeOfEventHandlerOfPCConfig()  /**< the number of accomplishable value elements in Sd_EventHandlerDyn */
#define Sd_GetSizeOfInstanceDynOfPCConfig()                                                         Sd_GetSizeOfInstanceOfPCConfig()  /**< the number of accomplishable value elements in Sd_InstanceDyn */
#define Sd_GetSizeOfRoutingGroupDynOfPCConfig()                                                     Sd_GetSizeOfRoutingGroupOfPCConfig()  /**< the number of accomplishable value elements in Sd_RoutingGroupDyn */
#define Sd_GetSizeOfServerDynOfPCConfig()                                                           Sd_GetSizeOfServerOfPCConfig()  /**< the number of accomplishable value elements in Sd_ServerDyn */
#define Sd_GetSizeOfTcpSoConModeMapOfPCConfig()                                                     Sd_GetSizeOfTcpSoConIdOfPCConfig()  /**< the number of accomplishable value elements in Sd_TcpSoConModeMap */
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGetDataMacros  Sd Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define Sd_GetAddrOfAddressStorage(Index)                                                           (Sd_GetAddressStorageOfPCConfig()[(Index)].AddrOfAddressStorage)
#define Sd_GetFlagsOfAddressStorage(Index)                                                          (Sd_GetAddressStorageOfPCConfig()[(Index)].FlagsOfAddressStorage)
#define Sd_GetRxMulticastFlagsOfAddressStorage(Index)                                               (Sd_GetAddressStorageOfPCConfig()[(Index)].RxMulticastFlagsOfAddressStorage)
#define Sd_GetRxMulticastSessionIdOfAddressStorage(Index)                                           (Sd_GetAddressStorageOfPCConfig()[(Index)].RxMulticastSessionIdOfAddressStorage)
#define Sd_GetRxUnicastFlagsOfAddressStorage(Index)                                                 (Sd_GetAddressStorageOfPCConfig()[(Index)].RxUnicastFlagsOfAddressStorage)
#define Sd_GetRxUnicastSessionIdOfAddressStorage(Index)                                             (Sd_GetAddressStorageOfPCConfig()[(Index)].RxUnicastSessionIdOfAddressStorage)
#define Sd_GetSendEntryNrPendingIdxOfAddressStorage(Index)                                          (Sd_GetAddressStorageOfPCConfig()[(Index)].SendEntryNrPendingIdxOfAddressStorage)
#define Sd_GetSessionIdCounterOfAddressStorage(Index)                                               (Sd_GetAddressStorageOfPCConfig()[(Index)].SessionIdCounterOfAddressStorage)
#define Sd_GetCapabilityRecord(Index)                                                               (Sd_GetCapabilityRecordOfPCConfig()[(Index)])
#define Sd_GetCapabilityRecordFunctionCalloutPtr(Index)                                             (Sd_GetCapabilityRecordFunctionCalloutPtrOfPCConfig()[(Index)])
#define Sd_IsAutoRequireOfClient(Index)                                                             ((Sd_GetClientOfPCConfig()[(Index)].AutoRequireOfClient) != FALSE)
#define Sd_GetCapabilityRecordEndIdxOfClient(Index)                                                 (Sd_GetClientOfPCConfig()[(Index)].CapabilityRecordEndIdxOfClient)
#define Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfClient(Index)                                  (Sd_GetClientOfPCConfig()[(Index)].CapabilityRecordFunctionCalloutPtrIdxOfClient)
#define Sd_GetCapabilityRecordStartIdxOfClient(Index)                                               (Sd_GetClientOfPCConfig()[(Index)].CapabilityRecordStartIdxOfClient)
#define Sd_GetClientTimerIdxOfClient(Index)                                                         (Sd_GetClientOfPCConfig()[(Index)].ClientTimerIdxOfClient)
#define Sd_GetCommonInitialDelayIdxOfClient(Index)                                                  (Sd_GetClientOfPCConfig()[(Index)].CommonInitialDelayIdxOfClient)
#define Sd_GetConsumedEventgroupEndIdxOfClient(Index)                                               (Sd_GetClientOfPCConfig()[(Index)].ConsumedEventgroupEndIdxOfClient)
#define Sd_GetConsumedEventgroupStartIdxOfClient(Index)                                             (Sd_GetClientOfPCConfig()[(Index)].ConsumedEventgroupStartIdxOfClient)
#define Sd_GetHandleIdOfClient(Index)                                                               (Sd_GetClientOfPCConfig()[(Index)].HandleIdOfClient)
#define Sd_GetInstanceIdOfClient(Index)                                                             (Sd_GetClientOfPCConfig()[(Index)].InstanceIdOfClient)
#define Sd_GetInstanceIdxOfClient(Index)                                                            (Sd_GetClientOfPCConfig()[(Index)].InstanceIdxOfClient)
#define Sd_GetMajorVersionOfClient(Index)                                                           (Sd_GetClientOfPCConfig()[(Index)].MajorVersionOfClient)
#define Sd_GetMethodIdxOfClient(Index)                                                              (Sd_GetClientOfPCConfig()[(Index)].MethodIdxOfClient)
#define Sd_GetMinorVersionOfClient(Index)                                                           (Sd_GetClientOfPCConfig()[(Index)].MinorVersionOfClient)
#define Sd_IsMinorVersionWildcardOfClient(Index)                                                    ((Sd_GetClientOfPCConfig()[(Index)].MinorVersionWildcardOfClient) != FALSE)
#define Sd_IsServiceGroupMemberOfClient(Index)                                                      ((Sd_GetClientOfPCConfig()[(Index)].ServiceGroupMemberOfClient) != FALSE)
#define Sd_GetServiceIdOfClient(Index)                                                              (Sd_GetClientOfPCConfig()[(Index)].ServiceIdOfClient)
#define Sd_GetTcpSoConIdEndIdxOfClient(Index)                                                       (Sd_GetClientOfPCConfig()[(Index)].TcpSoConIdEndIdxOfClient)
#define Sd_GetTcpSoConIdStartIdxOfClient(Index)                                                     (Sd_GetClientOfPCConfig()[(Index)].TcpSoConIdStartIdxOfClient)
#define Sd_GetUdpSoConEndIdxOfClient(Index)                                                         (Sd_GetClientOfPCConfig()[(Index)].UdpSoConEndIdxOfClient)
#define Sd_GetUdpSoConStartIdxOfClient(Index)                                                       (Sd_GetClientOfPCConfig()[(Index)].UdpSoConStartIdxOfClient)
#define Sd_GetAddressStorageServerIdxOfClientDyn(Index)                                             (Sd_GetClientDynOfPCConfig()[(Index)].AddressStorageServerIdxOfClientDyn)
#define Sd_GetCurrentStateOfClientDyn(Index)                                                        (Sd_GetClientDynOfPCConfig()[(Index)].CurrentStateOfClientDyn)
#define Sd_GetEventMainOfClientDyn(Index)                                                           (Sd_GetClientDynOfPCConfig()[(Index)].EventMainOfClientDyn)
#define Sd_GetEventRxOfClientDyn(Index)                                                             (Sd_GetClientDynOfPCConfig()[(Index)].EventRxOfClientDyn)
#define Sd_GetMethodTcpSoConIdOfClientDyn(Index)                                                    (Sd_GetClientDynOfPCConfig()[(Index)].MethodTcpSoConIdOfClientDyn)
#define Sd_GetMethodUdpSoConIdOfClientDyn(Index)                                                    (Sd_GetClientDynOfPCConfig()[(Index)].MethodUdpSoConIdOfClientDyn)
#define Sd_GetOfferedTTLOfClientDyn(Index)                                                          (Sd_GetClientDynOfPCConfig()[(Index)].OfferedTTLOfClientDyn)
#define Sd_GetRepetitionRunOfClientDyn(Index)                                                       (Sd_GetClientDynOfPCConfig()[(Index)].RepetitionRunOfClientDyn)
#define Sd_GetRetryCounterOfClientDyn(Index)                                                        (Sd_GetClientDynOfPCConfig()[(Index)].RetryCounterOfClientDyn)
#define Sd_GetRetryTimerOfClientDyn(Index)                                                          (Sd_GetClientDynOfPCConfig()[(Index)].RetryTimerOfClientDyn)
#define Sd_GetServerTcpEndpointAddrOfClientDyn(Index)                                               (Sd_GetClientDynOfPCConfig()[(Index)].ServerTcpEndpointAddrOfClientDyn)
#define Sd_GetServerUdpEndpointAddrOfClientDyn(Index)                                               (Sd_GetClientDynOfPCConfig()[(Index)].ServerUdpEndpointAddrOfClientDyn)
#define Sd_GetServiceGroupReqCounterOfClientDyn(Index)                                              (Sd_GetClientDynOfPCConfig()[(Index)].ServiceGroupReqCounterOfClientDyn)
#define Sd_IsStateMachineExecutionRequestedOfClientDyn(Index)                                       ((Sd_GetClientDynOfPCConfig()[(Index)].StateMachineExecutionRequestedOfClientDyn) != FALSE)
#define Sd_GetStateMachineOfClientDyn(Index)                                                        (Sd_GetClientDynOfPCConfig()[(Index)].StateMachineOfClientDyn)
#define Sd_GetStateSwcOfClientDyn(Index)                                                            (Sd_GetClientDynOfPCConfig()[(Index)].StateSwcOfClientDyn)
#define Sd_GetTimeToTriggerSendOfClientDyn(Index)                                                   (Sd_GetClientDynOfPCConfig()[(Index)].TimeToTriggerSendOfClientDyn)
#define Sd_GetTimerTTLOfClientDyn(Index)                                                            (Sd_GetClientDynOfPCConfig()[(Index)].TimerTTLOfClientDyn)
#define Sd_GetAddressStorageIdxOfClientList(Index)                                                  (Sd_GetClientListOfPCConfig()[(Index)].AddressStorageIdxOfClientList)
#define Sd_GetAssignedTcpSoConIdOfClientList(Index)                                                 (Sd_GetClientListOfPCConfig()[(Index)].AssignedTcpSoConIdOfClientList)
#define Sd_GetAssignedUdpSoConIdOfClientList(Index)                                                 (Sd_GetClientListOfPCConfig()[(Index)].AssignedUdpSoConIdOfClientList)
#define Sd_GetClientStateOfClientList(Index)                                                        (Sd_GetClientListOfPCConfig()[(Index)].ClientStateOfClientList)
#define Sd_GetEndpointStorageTcpIdxOfClientList(Index)                                              (Sd_GetClientListOfPCConfig()[(Index)].EndpointStorageTcpIdxOfClientList)
#define Sd_GetEndpointStorageUdpIdxOfClientList(Index)                                              (Sd_GetClientListOfPCConfig()[(Index)].EndpointStorageUdpIdxOfClientList)
#define Sd_GetNrOfReferencesOfClientList(Index)                                                     (Sd_GetClientListOfPCConfig()[(Index)].NrOfReferencesOfClientList)
#define Sd_GetRequestedTTLOfClientList(Index)                                                       (Sd_GetClientListOfPCConfig()[(Index)].RequestedTTLOfClientList)
#define Sd_GetRxReservedOfClientList(Index)                                                         (Sd_GetClientListOfPCConfig()[(Index)].RxReservedOfClientList)
#define Sd_GetSubscribedUntilOfClientList(Index)                                                    (Sd_GetClientListOfPCConfig()[(Index)].SubscribedUntilOfClientList)
#define Sd_GetClientIdxOfClientMap(Index)                                                           (Sd_GetClientMapOfPCConfig()[(Index)].ClientIdxOfClientMap)
#define Sd_IsInvalidHndOfClientMap(Index)                                                           ((Sd_GetClientMapOfPCConfig()[(Index)].InvalidHndOfClientMap) != FALSE)
#define Sd_GetInitialFindDelayMaxOfClientTimer(Index)                                               (Sd_GetClientTimerOfPCConfig()[(Index)].InitialFindDelayMaxOfClientTimer)
#define Sd_GetInitialFindDelayMinOfClientTimer(Index)                                               (Sd_GetClientTimerOfPCConfig()[(Index)].InitialFindDelayMinOfClientTimer)
#define Sd_GetInitialFindRepetitionBaseDelayOfClientTimer(Index)                                    (Sd_GetClientTimerOfPCConfig()[(Index)].InitialFindRepetitionBaseDelayOfClientTimer)
#define Sd_GetInitialFindRepetitionsMaxOfClientTimer(Index)                                         (Sd_GetClientTimerOfPCConfig()[(Index)].InitialFindRepetitionsMaxOfClientTimer)
#define Sd_GetRequestResponseMaxDelayOfClientTimer(Index)                                           (Sd_GetClientTimerOfPCConfig()[(Index)].RequestResponseMaxDelayOfClientTimer)
#define Sd_GetRequestResponseMinDelayOfClientTimer(Index)                                           (Sd_GetClientTimerOfPCConfig()[(Index)].RequestResponseMinDelayOfClientTimer)
#define Sd_GetTTLOfClientTimer(Index)                                                               (Sd_GetClientTimerOfPCConfig()[(Index)].TTLOfClientTimer)
#define Sd_GetCommonInitialDelay(Index)                                                             (Sd_GetCommonInitialDelayOfPCConfig()[(Index)])
#define Sd_IsAutoRequireOfConsumedEventgroup(Index)                                                 ((Sd_GetConsumedEventgroupOfPCConfig()[(Index)].AutoRequireOfConsumedEventgroup) != FALSE)
#define Sd_GetClientIdxOfConsumedEventgroup(Index)                                                  (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].ClientIdxOfConsumedEventgroup)
#define Sd_GetClientTimerIdxOfConsumedEventgroup(Index)                                             (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].ClientTimerIdxOfConsumedEventgroup)
#define Sd_GetEventGroupIdOfConsumedEventgroup(Index)                                               (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].EventGroupIdOfConsumedEventgroup)
#define Sd_GetHandleIdOfConsumedEventgroup(Index)                                                   (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].HandleIdOfConsumedEventgroup)
#define Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(Index)                                   (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].MulticastEndpointAddrIdxOfConsumedEventgroup)
#define Sd_GetMulticastSoConIdEndIdxOfConsumedEventgroup(Index)                                     (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].MulticastSoConIdEndIdxOfConsumedEventgroup)
#define Sd_GetMulticastSoConIdStartIdxOfConsumedEventgroup(Index)                                   (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].MulticastSoConIdStartIdxOfConsumedEventgroup)
#define Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(Index)                             (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].RoutingGroupMulticastActRefIdxOfConsumedEventgroup)
#define Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(Index)                                   (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].RoutingGroupTcpActRefIdxOfConsumedEventgroup)
#define Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(Index)                                   (Sd_GetConsumedEventgroupOfPCConfig()[(Index)].RoutingGroupUdpActRefIdxOfConsumedEventgroup)
#define Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(Index)                                         (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].AcknowledgedTTLOfConsumedEventgroupDyn)
#define Sd_GetCurrentStateOfConsumedEventgroupDyn(Index)                                            (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].CurrentStateOfConsumedEventgroupDyn)
#define Sd_GetEventOfConsumedEventgroupDyn(Index)                                                   (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].EventOfConsumedEventgroupDyn)
#define Sd_GetMulticastSoConIdOfConsumedEventgroupDyn(Index)                                        (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].MulticastSoConIdOfConsumedEventgroupDyn)
#define Sd_GetRxIndicationCountOfConsumedEventgroupDyn(Index)                                       (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].RxIndicationCountOfConsumedEventgroupDyn)
#define Sd_GetServiceModeRequestOfConsumedEventgroupDyn(Index)                                      (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].ServiceModeRequestOfConsumedEventgroupDyn)
#define Sd_IsSoConMarkedForClosureOfConsumedEventgroupDyn(Index)                                    ((Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].SoConMarkedForClosureOfConsumedEventgroupDyn) != FALSE)
#define Sd_GetStateMachineOfConsumedEventgroupDyn(Index)                                            (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].StateMachineOfConsumedEventgroupDyn)
#define Sd_GetTcpSoConIdOfConsumedEventgroupDyn(Index)                                              (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TcpSoConIdOfConsumedEventgroupDyn)
#define Sd_GetTimerTTLOfConsumedEventgroupDyn(Index)                                                (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TimerTTLOfConsumedEventgroupDyn)
#define Sd_IsTriggerSubscriptionOfConsumedEventgroupDyn(Index)                                      ((Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TriggerSubscriptionOfConsumedEventgroupDyn) != FALSE)
#define Sd_GetUdpSoConIdOfConsumedEventgroupDyn(Index)                                              (Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].UdpSoConIdOfConsumedEventgroupDyn)
#define Sd_GetConsumedEventgroupIdxOfConsumedEventgroupMap(Index)                                   (Sd_GetConsumedEventgroupMapOfPCConfig()[(Index)].ConsumedEventgroupIdxOfConsumedEventgroupMap)
#define Sd_IsInvalidHndOfConsumedEventgroupMap(Index)                                               ((Sd_GetConsumedEventgroupMapOfPCConfig()[(Index)].InvalidHndOfConsumedEventgroupMap) != FALSE)
#define Sd_GetAddrOfEndpointStorage(Index)                                                          (Sd_GetEndpointStorageOfPCConfig()[(Index)].AddrOfEndpointStorage)
#define Sd_GetNrOfReferencesOfEndpointStorage(Index)                                                (Sd_GetEndpointStorageOfPCConfig()[(Index)].NrOfReferencesOfEndpointStorage)
#define Sd_GetTypeOfEndpointStorage(Index)                                                          (Sd_GetEndpointStorageOfPCConfig()[(Index)].TypeOfEndpointStorage)
#define Sd_GetClientListEndIdxOfEventHandler(Index)                                                 (Sd_GetEventHandlerOfPCConfig()[(Index)].ClientListEndIdxOfEventHandler)
#define Sd_GetClientListStartIdxOfEventHandler(Index)                                               (Sd_GetEventHandlerOfPCConfig()[(Index)].ClientListStartIdxOfEventHandler)
#define Sd_GetEventGroupIdOfEventHandler(Index)                                                     (Sd_GetEventHandlerOfPCConfig()[(Index)].EventGroupIdOfEventHandler)
#define Sd_GetEventHandlerMulticastIdxOfEventHandler(Index)                                         (Sd_GetEventHandlerOfPCConfig()[(Index)].EventHandlerMulticastIdxOfEventHandler)
#define Sd_GetEventHandlerTcpIdxOfEventHandler(Index)                                               (Sd_GetEventHandlerOfPCConfig()[(Index)].EventHandlerTcpIdxOfEventHandler)
#define Sd_GetEventHandlerUdpIdxOfEventHandler(Index)                                               (Sd_GetEventHandlerOfPCConfig()[(Index)].EventHandlerUdpIdxOfEventHandler)
#define Sd_GetHandleIdOfEventHandler(Index)                                                         (Sd_GetEventHandlerOfPCConfig()[(Index)].HandleIdOfEventHandler)
#define Sd_GetMulticastThresholdOfEventHandler(Index)                                               (Sd_GetEventHandlerOfPCConfig()[(Index)].MulticastThresholdOfEventHandler)
#define Sd_GetServerIdxOfEventHandler(Index)                                                        (Sd_GetEventHandlerOfPCConfig()[(Index)].ServerIdxOfEventHandler)
#define Sd_GetServerTimerIdxOfEventHandler(Index)                                                   (Sd_GetEventHandlerOfPCConfig()[(Index)].ServerTimerIdxOfEventHandler)
#define Sd_GetSoConActivationMapEndIdxOfEventHandler(Index)                                         (Sd_GetEventHandlerOfPCConfig()[(Index)].SoConActivationMapEndIdxOfEventHandler)
#define Sd_GetSoConActivationMapStartIdxOfEventHandler(Index)                                       (Sd_GetEventHandlerOfPCConfig()[(Index)].SoConActivationMapStartIdxOfEventHandler)
#define Sd_GetNrOfClientsOfEventHandlerDyn(Index)                                                   (Sd_GetEventHandlerDynOfPCConfig()[(Index)].NrOfClientsOfEventHandlerDyn)
#define Sd_GetRequestStateOfEventHandlerDyn(Index)                                                  (Sd_GetEventHandlerDynOfPCConfig()[(Index)].RequestStateOfEventHandlerDyn)
#define Sd_GetStateMachineOfEventHandlerDyn(Index)                                                  (Sd_GetEventHandlerDynOfPCConfig()[(Index)].StateMachineOfEventHandlerDyn)
#define Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(Index)                                   (Sd_GetEventHandlerMulticastOfPCConfig()[(Index)].RoutingGroupActRefIdxOfEventHandlerMulticast)
#define Sd_GetSoConIdOfEventHandlerMulticast(Index)                                                 (Sd_GetEventHandlerMulticastOfPCConfig()[(Index)].SoConIdOfEventHandlerMulticast)
#define Sd_GetRoutingGroupActRefIdxOfEventHandlerTcp(Index)                                         (Sd_GetEventHandlerTcpOfPCConfig()[(Index)].RoutingGroupActRefIdxOfEventHandlerTcp)
#define Sd_GetRoutingGroupTriggerIdxOfEventHandlerTcp(Index)                                        (Sd_GetEventHandlerTcpOfPCConfig()[(Index)].RoutingGroupTriggerIdxOfEventHandlerTcp)
#define Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(Index)                                         (Sd_GetEventHandlerUdpOfPCConfig()[(Index)].RoutingGroupActRefIdxOfEventHandlerUdp)
#define Sd_GetRoutingGroupTriggerIdxOfEventHandlerUdp(Index)                                        (Sd_GetEventHandlerUdpOfPCConfig()[(Index)].RoutingGroupTriggerIdxOfEventHandlerUdp)
#define Sd_GetAddressStorageEndIdxOfInstance(Index)                                                 (Sd_GetInstanceOfPCConfig()[(Index)].AddressStorageEndIdxOfInstance)
#define Sd_GetAddressStorageStartIdxOfInstance(Index)                                               (Sd_GetInstanceOfPCConfig()[(Index)].AddressStorageStartIdxOfInstance)
#define Sd_GetCapabilityRecordEndIdxOfInstance(Index)                                               (Sd_GetInstanceOfPCConfig()[(Index)].CapabilityRecordEndIdxOfInstance)
#define Sd_GetCapabilityRecordStartIdxOfInstance(Index)                                             (Sd_GetInstanceOfPCConfig()[(Index)].CapabilityRecordStartIdxOfInstance)
#define Sd_GetClientEndIdxOfInstance(Index)                                                         (Sd_GetInstanceOfPCConfig()[(Index)].ClientEndIdxOfInstance)
#define Sd_GetClientStartIdxOfInstance(Index)                                                       (Sd_GetInstanceOfPCConfig()[(Index)].ClientStartIdxOfInstance)
#define Sd_GetEMalformedMsgIdOfInstance(Index)                                                      (Sd_GetInstanceOfPCConfig()[(Index)].EMalformedMsgIdOfInstance)
#define Sd_GetENackRecvIdOfInstance(Index)                                                          (Sd_GetInstanceOfPCConfig()[(Index)].ENackRecvIdOfInstance)
#define Sd_GetEOutOfResIdOfInstance(Index)                                                          (Sd_GetInstanceOfPCConfig()[(Index)].EOutOfResIdOfInstance)
#define Sd_GetEndpointStorageEndIdxOfInstance(Index)                                                (Sd_GetInstanceOfPCConfig()[(Index)].EndpointStorageEndIdxOfInstance)
#define Sd_GetEndpointStorageStartIdxOfInstance(Index)                                              (Sd_GetInstanceOfPCConfig()[(Index)].EndpointStorageStartIdxOfInstance)
#define Sd_GetMulticastRxPduIdOfInstance(Index)                                                     (Sd_GetInstanceOfPCConfig()[(Index)].MulticastRxPduIdOfInstance)
#define Sd_GetMulticastRxSoConIdOfInstance(Index)                                                   (Sd_GetInstanceOfPCConfig()[(Index)].MulticastRxSoConIdOfInstance)
#define Sd_GetQueueProcessLimitOfInstance(Index)                                                    (Sd_GetInstanceOfPCConfig()[(Index)].QueueProcessLimitOfInstance)
#define Sd_GetRetryDelayOfInstance(Index)                                                           (Sd_GetInstanceOfPCConfig()[(Index)].RetryDelayOfInstance)
#define Sd_GetRetryMaxOfInstance(Index)                                                             (Sd_GetInstanceOfPCConfig()[(Index)].RetryMaxOfInstance)
#define Sd_GetRxEventEndIdxOfInstance(Index)                                                        (Sd_GetInstanceOfPCConfig()[(Index)].RxEventEndIdxOfInstance)
#define Sd_GetRxEventStartIdxOfInstance(Index)                                                      (Sd_GetInstanceOfPCConfig()[(Index)].RxEventStartIdxOfInstance)
#define Sd_GetSendEntryEndIdxOfInstance(Index)                                                      (Sd_GetInstanceOfPCConfig()[(Index)].SendEntryEndIdxOfInstance)
#define Sd_GetSendEntryStartIdxOfInstance(Index)                                                    (Sd_GetInstanceOfPCConfig()[(Index)].SendEntryStartIdxOfInstance)
#define Sd_GetServerEndIdxOfInstance(Index)                                                         (Sd_GetInstanceOfPCConfig()[(Index)].ServerEndIdxOfInstance)
#define Sd_GetServerStartIdxOfInstance(Index)                                                       (Sd_GetInstanceOfPCConfig()[(Index)].ServerStartIdxOfInstance)
#define Sd_GetTcpSoConIdEndIdxOfInstance(Index)                                                     (Sd_GetInstanceOfPCConfig()[(Index)].TcpSoConIdEndIdxOfInstance)
#define Sd_GetTcpSoConIdStartIdxOfInstance(Index)                                                   (Sd_GetInstanceOfPCConfig()[(Index)].TcpSoConIdStartIdxOfInstance)
#define Sd_GetTxPduIdOfInstance(Index)                                                              (Sd_GetInstanceOfPCConfig()[(Index)].TxPduIdOfInstance)
#define Sd_GetTxSoConIdOfInstance(Index)                                                            (Sd_GetInstanceOfPCConfig()[(Index)].TxSoConIdOfInstance)
#define Sd_GetUdpSoConEndIdxOfInstance(Index)                                                       (Sd_GetInstanceOfPCConfig()[(Index)].UdpSoConEndIdxOfInstance)
#define Sd_GetUdpSoConStartIdxOfInstance(Index)                                                     (Sd_GetInstanceOfPCConfig()[(Index)].UdpSoConStartIdxOfInstance)
#define Sd_GetUnicastRxPduIdOfInstance(Index)                                                       (Sd_GetInstanceOfPCConfig()[(Index)].UnicastRxPduIdOfInstance)
#define Sd_GetUnicastRxSoConIdOfInstance(Index)                                                     (Sd_GetInstanceOfPCConfig()[(Index)].UnicastRxSoConIdOfInstance)
#define Sd_GetNextStateMachineRunOfInstanceDyn(Index)                                               (Sd_GetInstanceDynOfPCConfig()[(Index)].NextStateMachineRunOfInstanceDyn)
#define Sd_GetRunModeOfInstanceDyn(Index)                                                           (Sd_GetInstanceDynOfPCConfig()[(Index)].RunModeOfInstanceDyn)
#define Sd_GetRxEventEndIdxOfInstanceDyn(Index)                                                     (Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventEndIdxOfInstanceDyn)
#define Sd_IsRxEventListFullOfInstanceDyn(Index)                                                    ((Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventListFullOfInstanceDyn) != FALSE)
#define Sd_GetRxEventStartIdxOfInstanceDyn(Index)                                                   (Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventStartIdxOfInstanceDyn)
#define Sd_GetSendEntryEndIdxOfInstanceDyn(Index)                                                   (Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryEndIdxOfInstanceDyn)
#define Sd_GetSendEntryNrPendingIdxOfInstanceDyn(Index)                                             (Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryNrPendingIdxOfInstanceDyn)
#define Sd_GetSendEntryStartIdxOfInstanceDyn(Index)                                                 (Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryStartIdxOfInstanceDyn)
#define Sd_GetStateOfInstanceDyn(Index)                                                             (Sd_GetInstanceDynOfPCConfig()[(Index)].StateOfInstanceDyn)
#define Sd_GetPortSetIdxOfIpAddrRequest(Index)                                                      (Sd_GetIpAddrRequestOfPCConfig()[(Index)].PortSetIdxOfIpAddrRequest)
#define Sd_GetRequestCntIdxOfIpAddrRequest(Index)                                                   (Sd_GetIpAddrRequestOfPCConfig()[(Index)].RequestCntIdxOfIpAddrRequest)
#define Sd_GetSoConIdOfIpAddrRequest(Index)                                                         (Sd_GetIpAddrRequestOfPCConfig()[(Index)].SoConIdOfIpAddrRequest)
#define Sd_IsStaticIpConfigurationOfIpAddrRequest(Index)                                            ((Sd_GetIpAddrRequestOfPCConfig()[(Index)].StaticIpConfigurationOfIpAddrRequest) != FALSE)
#define Sd_IsStaticPortConfigurationOfIpAddrRequest(Index)                                          ((Sd_GetIpAddrRequestOfPCConfig()[(Index)].StaticPortConfigurationOfIpAddrRequest) != FALSE)
#define Sd_GetRoutingGroupActRefIdxOfMethod(Index)                                                  (Sd_GetMethodOfPCConfig()[(Index)].RoutingGroupActRefIdxOfMethod)
#define Sd_IsTcpConfiguredOfMethod(Index)                                                           ((Sd_GetMethodOfPCConfig()[(Index)].TcpConfiguredOfMethod) != FALSE)
#define Sd_IsUdpConfiguredOfMethod(Index)                                                           ((Sd_GetMethodOfPCConfig()[(Index)].UdpConfiguredOfMethod) != FALSE)
#define Sd_GetMulticastEndpointAddr(Index)                                                          (Sd_GetMulticastEndpointAddrOfPCConfig()[(Index)])
#define Sd_GetMulticastSoConId(Index)                                                               (Sd_GetMulticastSoConIdOfPCConfig()[(Index)])
#define Sd_GetNrOfOptions()                                                                         ((*(Sd_GetNrOfOptionsOfPCConfig())))
#define Sd_GetOptionIndex(Index)                                                                    (Sd_GetOptionIndexOfPCConfig()[(Index)])
#define Sd_GetPayload(Index)                                                                        (Sd_GetPayloadOfPCConfig()[(Index)])
#define Sd_IsPortSet(Index)                                                                         ((Sd_GetPortSetOfPCConfig()[(Index)]) != FALSE)
#define Sd_GetRequestCnt(Index)                                                                     (Sd_GetRequestCntOfPCConfig()[(Index)])
#define Sd_GetRoutingGroup(Index)                                                                   (Sd_GetRoutingGroupOfPCConfig()[(Index)])
#define Sd_GetStatusOfRoutingGroupDyn(Index)                                                        (Sd_GetRoutingGroupDynOfPCConfig()[(Index)].StatusOfRoutingGroupDyn)
#define Sd_GetClientListIdxOfRxEvent(Index)                                                         (Sd_GetRxEventOfPCConfig()[(Index)].ClientListIdxOfRxEvent)
#define Sd_GetEventHandlerIdxOfRxEvent(Index)                                                       (Sd_GetRxEventOfPCConfig()[(Index)].EventHandlerIdxOfRxEvent)
#define Sd_GetEventOfRxEvent(Index)                                                                 (Sd_GetRxEventOfPCConfig()[(Index)].EventOfRxEvent)
#define Sd_GetAddressStorageIdxOfSendEntry(Index)                                                   (Sd_GetSendEntryOfPCConfig()[(Index)].AddressStorageIdxOfSendEntry)
#define Sd_GetClientIdxOfSendEntry(Index)                                                           (Sd_GetSendEntryOfPCConfig()[(Index)].ClientIdxOfSendEntry)
#define Sd_GetClientListIdxOfSendEntry(Index)                                                       (Sd_GetSendEntryOfPCConfig()[(Index)].ClientListIdxOfSendEntry)
#define Sd_GetConsumedEventgroupIdxOfSendEntry(Index)                                               (Sd_GetSendEntryOfPCConfig()[(Index)].ConsumedEventgroupIdxOfSendEntry)
#define Sd_GetEntryTypeOfSendEntry(Index)                                                           (Sd_GetSendEntryOfPCConfig()[(Index)].EntryTypeOfSendEntry)
#define Sd_GetEventHandlerIdOfSendEntry(Index)                                                      (Sd_GetSendEntryOfPCConfig()[(Index)].EventHandlerIdOfSendEntry)
#define Sd_GetEventHandlerIdxOfSendEntry(Index)                                                     (Sd_GetSendEntryOfPCConfig()[(Index)].EventHandlerIdxOfSendEntry)
#define Sd_GetInstanceIdOfSendEntry(Index)                                                          (Sd_GetSendEntryOfPCConfig()[(Index)].InstanceIdOfSendEntry)
#define Sd_GetInstanceIdxOfSendEntry(Index)                                                         (Sd_GetSendEntryOfPCConfig()[(Index)].InstanceIdxOfSendEntry)
#define Sd_GetMajorVersionOfSendEntry(Index)                                                        (Sd_GetSendEntryOfPCConfig()[(Index)].MajorVersionOfSendEntry)
#define Sd_GetReservedFieldOfSendEntry(Index)                                                       (Sd_GetSendEntryOfPCConfig()[(Index)].ReservedFieldOfSendEntry)
#define Sd_GetSendEntryNextIdxOfSendEntry(Index)                                                    (Sd_GetSendEntryOfPCConfig()[(Index)].SendEntryNextIdxOfSendEntry)
#define Sd_GetServerIdxOfSendEntry(Index)                                                           (Sd_GetSendEntryOfPCConfig()[(Index)].ServerIdxOfSendEntry)
#define Sd_GetServiceIdOfSendEntry(Index)                                                           (Sd_GetSendEntryOfPCConfig()[(Index)].ServiceIdOfSendEntry)
#define Sd_GetTimeToSendOfSendEntry(Index)                                                          (Sd_GetSendEntryOfPCConfig()[(Index)].TimeToSendOfSendEntry)
#define Sd_IsValidOfSendEntry(Index)                                                                ((Sd_GetSendEntryOfPCConfig()[(Index)].ValidOfSendEntry) != FALSE)
#define Sd_IsAutoAvailableOfServer(Index)                                                           ((Sd_GetServerOfPCConfig()[(Index)].AutoAvailableOfServer) != FALSE)
#define Sd_GetCapabilityRecordEndIdxOfServer(Index)                                                 (Sd_GetServerOfPCConfig()[(Index)].CapabilityRecordEndIdxOfServer)
#define Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfServer(Index)                                  (Sd_GetServerOfPCConfig()[(Index)].CapabilityRecordFunctionCalloutPtrIdxOfServer)
#define Sd_GetCapabilityRecordStartIdxOfServer(Index)                                               (Sd_GetServerOfPCConfig()[(Index)].CapabilityRecordStartIdxOfServer)
#define Sd_GetCommonInitialDelayIdxOfServer(Index)                                                  (Sd_GetServerOfPCConfig()[(Index)].CommonInitialDelayIdxOfServer)
#define Sd_GetEventHandlerEndIdxOfServer(Index)                                                     (Sd_GetServerOfPCConfig()[(Index)].EventHandlerEndIdxOfServer)
#define Sd_GetEventHandlerStartIdxOfServer(Index)                                                   (Sd_GetServerOfPCConfig()[(Index)].EventHandlerStartIdxOfServer)
#define Sd_GetHandleIdOfServer(Index)                                                               (Sd_GetServerOfPCConfig()[(Index)].HandleIdOfServer)
#define Sd_GetInstanceIdOfServer(Index)                                                             (Sd_GetServerOfPCConfig()[(Index)].InstanceIdOfServer)
#define Sd_GetInstanceIdxOfServer(Index)                                                            (Sd_GetServerOfPCConfig()[(Index)].InstanceIdxOfServer)
#define Sd_GetMajorVersionOfServer(Index)                                                           (Sd_GetServerOfPCConfig()[(Index)].MajorVersionOfServer)
#define Sd_GetMethodIdxOfServer(Index)                                                              (Sd_GetServerOfPCConfig()[(Index)].MethodIdxOfServer)
#define Sd_GetMinorVersionOfServer(Index)                                                           (Sd_GetServerOfPCConfig()[(Index)].MinorVersionOfServer)
#define Sd_GetServerTimerIdxOfServer(Index)                                                         (Sd_GetServerOfPCConfig()[(Index)].ServerTimerIdxOfServer)
#define Sd_IsServiceGroupMemberOfServer(Index)                                                      ((Sd_GetServerOfPCConfig()[(Index)].ServiceGroupMemberOfServer) != FALSE)
#define Sd_GetServiceIdOfServer(Index)                                                              (Sd_GetServerOfPCConfig()[(Index)].ServiceIdOfServer)
#define Sd_GetTcpSoConIdEndIdxOfServer(Index)                                                       (Sd_GetServerOfPCConfig()[(Index)].TcpSoConIdEndIdxOfServer)
#define Sd_GetTcpSoConIdStartIdxOfServer(Index)                                                     (Sd_GetServerOfPCConfig()[(Index)].TcpSoConIdStartIdxOfServer)
#define Sd_GetUdpSoConEndIdxOfServer(Index)                                                         (Sd_GetServerOfPCConfig()[(Index)].UdpSoConEndIdxOfServer)
#define Sd_GetUdpSoConStartIdxOfServer(Index)                                                       (Sd_GetServerOfPCConfig()[(Index)].UdpSoConStartIdxOfServer)
#define Sd_GetInitialOfferRepetitionRunOfServerDyn(Index)                                           (Sd_GetServerDynOfPCConfig()[(Index)].InitialOfferRepetitionRunOfServerDyn)
#define Sd_GetServiceGroupReqCounterOfServerDyn(Index)                                              (Sd_GetServerDynOfPCConfig()[(Index)].ServiceGroupReqCounterOfServerDyn)
#define Sd_IsStateMachineExecutionRequestedOfServerDyn(Index)                                       ((Sd_GetServerDynOfPCConfig()[(Index)].StateMachineExecutionRequestedOfServerDyn) != FALSE)
#define Sd_GetStateMachineOfServerDyn(Index)                                                        (Sd_GetServerDynOfPCConfig()[(Index)].StateMachineOfServerDyn)
#define Sd_GetStateSwcOfServerDyn(Index)                                                            (Sd_GetServerDynOfPCConfig()[(Index)].StateSwcOfServerDyn)
#define Sd_GetTimeToTriggerSendOfServerDyn(Index)                                                   (Sd_GetServerDynOfPCConfig()[(Index)].TimeToTriggerSendOfServerDyn)
#define Sd_IsInvalidHndOfServerMap(Index)                                                           ((Sd_GetServerMapOfPCConfig()[(Index)].InvalidHndOfServerMap) != FALSE)
#define Sd_GetServerIdxOfServerMap(Index)                                                           (Sd_GetServerMapOfPCConfig()[(Index)].ServerIdxOfServerMap)
#define Sd_GetInitialOfferDelayMaxOfServerTimer(Index)                                              (Sd_GetServerTimerOfPCConfig()[(Index)].InitialOfferDelayMaxOfServerTimer)
#define Sd_GetInitialOfferDelayMinOfServerTimer(Index)                                              (Sd_GetServerTimerOfPCConfig()[(Index)].InitialOfferDelayMinOfServerTimer)
#define Sd_GetInitialOfferRepetitionBaseDelayOfServerTimer(Index)                                   (Sd_GetServerTimerOfPCConfig()[(Index)].InitialOfferRepetitionBaseDelayOfServerTimer)
#define Sd_GetInitialOfferRepetitionsMaxOfServerTimer(Index)                                        (Sd_GetServerTimerOfPCConfig()[(Index)].InitialOfferRepetitionsMaxOfServerTimer)
#define Sd_GetOfferCyclicDelayOfServerTimer(Index)                                                  (Sd_GetServerTimerOfPCConfig()[(Index)].OfferCyclicDelayOfServerTimer)
#define Sd_GetRequestResponseMaxDelayOfServerTimer(Index)                                           (Sd_GetServerTimerOfPCConfig()[(Index)].RequestResponseMaxDelayOfServerTimer)
#define Sd_GetRequestResponseMinDelayOfServerTimer(Index)                                           (Sd_GetServerTimerOfPCConfig()[(Index)].RequestResponseMinDelayOfServerTimer)
#define Sd_GetTTLOfServerTimer(Index)                                                               (Sd_GetServerTimerOfPCConfig()[(Index)].TTLOfServerTimer)
#define Sd_GetServiceGroupMemberEndIdxOfServiceGroup(Index)                                         (Sd_GetServiceGroupOfPCConfig()[(Index)].ServiceGroupMemberEndIdxOfServiceGroup)
#define Sd_GetServiceGroupMemberStartIdxOfServiceGroup(Index)                                       (Sd_GetServiceGroupOfPCConfig()[(Index)].ServiceGroupMemberStartIdxOfServiceGroup)
#define Sd_IsInvalidHndOfServiceGroupMap(Index)                                                     ((Sd_GetServiceGroupMapOfPCConfig()[(Index)].InvalidHndOfServiceGroupMap) != FALSE)
#define Sd_GetServiceGroupIdxOfServiceGroupMap(Index)                                               (Sd_GetServiceGroupMapOfPCConfig()[(Index)].ServiceGroupIdxOfServiceGroupMap)
#define Sd_GetClientIdxOfServiceGroupMember(Index)                                                  (Sd_GetServiceGroupMemberOfPCConfig()[(Index)].ClientIdxOfServiceGroupMember)
#define Sd_GetServerIdxOfServiceGroupMember(Index)                                                  (Sd_GetServiceGroupMemberOfPCConfig()[(Index)].ServerIdxOfServiceGroupMember)
#define Sd_GetNrOfActivationsOfSoConActivationMap(Index)                                            (Sd_GetSoConActivationMapOfPCConfig()[(Index)].NrOfActivationsOfSoConActivationMap)
#define Sd_GetSoConIdOfSoConActivationMap(Index)                                                    (Sd_GetSoConActivationMapOfPCConfig()[(Index)].SoConIdOfSoConActivationMap)
#define Sd_GetTcpSoConId(Index)                                                                     (Sd_GetTcpSoConIdOfPCConfig()[(Index)])
#define Sd_GetTcpSoConModeMap(Index)                                                                (Sd_GetTcpSoConModeMapOfPCConfig()[(Index)])
#define Sd_GetClientListIdxOfTriggerTransmit(Index)                                                 (Sd_GetTriggerTransmitOfPCConfig()[(Index)].ClientListIdxOfTriggerTransmit)
#define Sd_GetEventHandlerIdxOfTriggerTransmit(Index)                                               (Sd_GetTriggerTransmitOfPCConfig()[(Index)].EventHandlerIdxOfTriggerTransmit)
#define Sd_GetStateOfTriggerTransmit(Index)                                                         (Sd_GetTriggerTransmitOfPCConfig()[(Index)].StateOfTriggerTransmit)
#define Sd_GetTriggerTransmitEndIdx()                                                               ((*(Sd_GetTriggerTransmitEndIdxOfPCConfig())))
#define Sd_IsTriggerTransmitFull()                                                                  (((*(Sd_GetTriggerTransmitFullOfPCConfig()))) != FALSE)
#define Sd_GetTriggerTransmitStartIdx()                                                             ((*(Sd_GetTriggerTransmitStartIdxOfPCConfig())))
#define Sd_GetIdOfUdpSoCon(Index)                                                                   (Sd_GetUdpSoConOfPCConfig()[(Index)].IdOfUdpSoCon)
#define Sd_IsPreconfiguredOfUdpSoCon(Index)                                                         ((Sd_GetUdpSoConOfPCConfig()[(Index)].PreconfiguredOfUdpSoCon) != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGetDeduplicatedDataMacros  Sd Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define Sd_IsCapabilityRecordFunctionCalloutPtrUsedOfClient(Index)                                  (((boolean)(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfClient(Index) != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr */
#define Sd_IsCapabilityRecordUsedOfClient(Index)                                                    (((boolean)(Sd_GetCapabilityRecordStartIdxOfClient(Index) != SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_CapabilityRecord */
#define Sd_IsCommonInitialDelayUsedOfClient(Index)                                                  (((boolean)(Sd_GetCommonInitialDelayIdxOfClient(Index) != SD_NO_COMMONINITIALDELAYIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_CommonInitialDelay */
#define Sd_IsConsumedEventgroupUsedOfClient(Index)                                                  (((boolean)(Sd_GetConsumedEventgroupStartIdxOfClient(Index) != SD_NO_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_ConsumedEventgroup */
#define Sd_IsMethodUsedOfClient(Index)                                                              (((boolean)(Sd_GetMethodIdxOfClient(Index) != SD_NO_METHODIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Method */
#define Sd_IsTcpSoConIdUsedOfClient(Index)                                                          (((boolean)(Sd_GetTcpSoConIdStartIdxOfClient(Index) != SD_NO_TCPSOCONIDSTARTIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_TcpSoConId */
#define Sd_IsUdpSoConUsedOfClient(Index)                                                            (((boolean)(Sd_GetUdpSoConStartIdxOfClient(Index) != SD_NO_UDPSOCONSTARTIDXOFCLIENT)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_UdpSoCon */
#define Sd_IsClientUsedOfClientMap(Index)                                                           (((boolean)(Sd_GetClientIdxOfClientMap(Index) != SD_NO_CLIENTIDXOFCLIENTMAP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Client */
#define Sd_IsMulticastEndpointAddrUsedOfConsumedEventgroup(Index)                                   (((boolean)(Sd_GetMulticastEndpointAddrIdxOfConsumedEventgroup(Index) != SD_NO_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_MulticastEndpointAddr */
#define Sd_IsMulticastSoConIdUsedOfConsumedEventgroup(Index)                                        (((boolean)(Sd_GetMulticastSoConIdStartIdxOfConsumedEventgroup(Index) != SD_NO_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_MulticastSoConId */
#define Sd_IsRoutingGroupMulticastActRefUsedOfConsumedEventgroup(Index)                             (((boolean)(Sd_GetRoutingGroupMulticastActRefIdxOfConsumedEventgroup(Index) != SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupTcpActRefUsedOfConsumedEventgroup(Index)                                   (((boolean)(Sd_GetRoutingGroupTcpActRefIdxOfConsumedEventgroup(Index) != SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupUdpActRefUsedOfConsumedEventgroup(Index)                                   (((boolean)(Sd_GetRoutingGroupUdpActRefIdxOfConsumedEventgroup(Index) != SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsConsumedEventgroupUsedOfConsumedEventgroupMap(Index)                                   (((boolean)(Sd_GetConsumedEventgroupIdxOfConsumedEventgroupMap(Index) != SD_NO_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_ConsumedEventgroup */
#define Sd_IsEventHandlerMulticastUsedOfEventHandler(Index)                                         (((boolean)(Sd_GetEventHandlerMulticastIdxOfEventHandler(Index) != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_EventHandlerMulticast */
#define Sd_IsEventHandlerTcpUsedOfEventHandler(Index)                                               (((boolean)(Sd_GetEventHandlerTcpIdxOfEventHandler(Index) != SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_EventHandlerTcp */
#define Sd_IsEventHandlerUdpUsedOfEventHandler(Index)                                               (((boolean)(Sd_GetEventHandlerUdpIdxOfEventHandler(Index) != SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_EventHandlerUdp */
#define Sd_IsSoConActivationMapUsedOfEventHandler(Index)                                            (((boolean)(Sd_GetSoConActivationMapStartIdxOfEventHandler(Index) != SD_NO_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_SoConActivationMap */
#define Sd_IsRoutingGroupActRefUsedOfEventHandlerMulticast(Index)                                   (((boolean)(Sd_GetRoutingGroupActRefIdxOfEventHandlerMulticast(Index) != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupActRefUsedOfEventHandlerTcp(Index)                                         (((boolean)(Sd_GetRoutingGroupActRefIdxOfEventHandlerTcp(Index) != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupTriggerUsedOfEventHandlerTcp(Index)                                        (((boolean)(Sd_GetRoutingGroupTriggerIdxOfEventHandlerTcp(Index) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupActRefUsedOfEventHandlerUdp(Index)                                         (((boolean)(Sd_GetRoutingGroupActRefIdxOfEventHandlerUdp(Index) != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsRoutingGroupTriggerUsedOfEventHandlerUdp(Index)                                        (((boolean)(Sd_GetRoutingGroupTriggerIdxOfEventHandlerUdp(Index) != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsCapabilityRecordUsedOfInstance(Index)                                                  (((boolean)(Sd_GetCapabilityRecordStartIdxOfInstance(Index) != SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_CapabilityRecord */
#define Sd_IsClientUsedOfInstance(Index)                                                            (((boolean)(Sd_GetClientStartIdxOfInstance(Index) != SD_NO_CLIENTSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_Client */
#define Sd_IsRxEventUsedOfInstance(Index)                                                           (((boolean)(Sd_GetRxEventStartIdxOfInstance(Index) != SD_NO_RXEVENTSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_RxEvent */
#define Sd_IsServerUsedOfInstance(Index)                                                            (((boolean)(Sd_GetServerStartIdxOfInstance(Index) != SD_NO_SERVERSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_Server */
#define Sd_IsTcpSoConIdUsedOfInstance(Index)                                                        (((boolean)(Sd_GetTcpSoConIdStartIdxOfInstance(Index) != SD_NO_TCPSOCONIDSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_TcpSoConId */
#define Sd_IsUdpSoConUsedOfInstance(Index)                                                          (((boolean)(Sd_GetUdpSoConStartIdxOfInstance(Index) != SD_NO_UDPSOCONSTARTIDXOFINSTANCE)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_UdpSoCon */
#define Sd_GetMaxNrOptionsPerEntry()                                                                Sd_GetMaxNrOptionsPerEntryOfPCConfig()
#define Sd_IsRoutingGroupActRefUsedOfMethod(Index)                                                  (((boolean)(Sd_GetRoutingGroupActRefIdxOfMethod(Index) != SD_NO_ROUTINGGROUPACTREFIDXOFMETHOD)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_RoutingGroup */
#define Sd_IsCapabilityRecordFunctionCalloutPtrUsedOfServer(Index)                                  (((boolean)(Sd_GetCapabilityRecordFunctionCalloutPtrIdxOfServer(Index) != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr */
#define Sd_IsCapabilityRecordUsedOfServer(Index)                                                    (((boolean)(Sd_GetCapabilityRecordStartIdxOfServer(Index) != SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_CapabilityRecord */
#define Sd_IsCommonInitialDelayUsedOfServer(Index)                                                  (((boolean)(Sd_GetCommonInitialDelayIdxOfServer(Index) != SD_NO_COMMONINITIALDELAYIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_CommonInitialDelay */
#define Sd_IsEventHandlerUsedOfServer(Index)                                                        (((boolean)(Sd_GetEventHandlerStartIdxOfServer(Index) != SD_NO_EVENTHANDLERSTARTIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_EventHandler */
#define Sd_IsMethodUsedOfServer(Index)                                                              (((boolean)(Sd_GetMethodIdxOfServer(Index) != SD_NO_METHODIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Method */
#define Sd_IsTcpSoConIdUsedOfServer(Index)                                                          (((boolean)(Sd_GetTcpSoConIdStartIdxOfServer(Index) != SD_NO_TCPSOCONIDSTARTIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_TcpSoConId */
#define Sd_IsUdpSoConUsedOfServer(Index)                                                            (((boolean)(Sd_GetUdpSoConStartIdxOfServer(Index) != SD_NO_UDPSOCONSTARTIDXOFSERVER)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to Sd_UdpSoCon */
#define Sd_IsServerUsedOfServerMap(Index)                                                           (((boolean)(Sd_GetServerIdxOfServerMap(Index) != SD_NO_SERVERIDXOFSERVERMAP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Server */
#define Sd_IsServiceGroupUsedOfServiceGroupMap(Index)                                               (((boolean)(Sd_GetServiceGroupIdxOfServiceGroupMap(Index) != SD_NO_SERVICEGROUPIDXOFSERVICEGROUPMAP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_ServiceGroup */
#define Sd_IsClientUsedOfServiceGroupMember(Index)                                                  (((boolean)(Sd_GetClientIdxOfServiceGroupMember(Index) != SD_NO_CLIENTIDXOFSERVICEGROUPMEMBER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Client */
#define Sd_IsServerUsedOfServiceGroupMember(Index)                                                  (((boolean)(Sd_GetServerIdxOfServiceGroupMember(Index) != SD_NO_SERVERIDXOFSERVICEGROUPMEMBER)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to Sd_Server */
#define Sd_GetSizeOfAddressStorage()                                                                Sd_GetSizeOfAddressStorageOfPCConfig()
#define Sd_GetSizeOfCapabilityRecord()                                                              Sd_GetSizeOfCapabilityRecordOfPCConfig()
#define Sd_GetSizeOfCapabilityRecordFunctionCalloutPtr()                                            Sd_GetSizeOfCapabilityRecordFunctionCalloutPtrOfPCConfig()
#define Sd_GetSizeOfClient()                                                                        Sd_GetSizeOfClientOfPCConfig()
#define Sd_GetSizeOfClientDyn()                                                                     Sd_GetSizeOfClientDynOfPCConfig()
#define Sd_GetSizeOfClientList()                                                                    Sd_GetSizeOfClientListOfPCConfig()
#define Sd_GetSizeOfClientMap()                                                                     Sd_GetSizeOfClientMapOfPCConfig()
#define Sd_GetSizeOfClientTimer()                                                                   Sd_GetSizeOfClientTimerOfPCConfig()
#define Sd_GetSizeOfCommonInitialDelay()                                                            Sd_GetSizeOfCommonInitialDelayOfPCConfig()
#define Sd_GetSizeOfConsumedEventgroup()                                                            Sd_GetSizeOfConsumedEventgroupOfPCConfig()
#define Sd_GetSizeOfConsumedEventgroupDyn()                                                         Sd_GetSizeOfConsumedEventgroupDynOfPCConfig()
#define Sd_GetSizeOfConsumedEventgroupMap()                                                         Sd_GetSizeOfConsumedEventgroupMapOfPCConfig()
#define Sd_GetSizeOfEndpointStorage()                                                               Sd_GetSizeOfEndpointStorageOfPCConfig()
#define Sd_GetSizeOfEventHandler()                                                                  Sd_GetSizeOfEventHandlerOfPCConfig()
#define Sd_GetSizeOfEventHandlerDyn()                                                               Sd_GetSizeOfEventHandlerDynOfPCConfig()
#define Sd_GetSizeOfEventHandlerMulticast()                                                         Sd_GetSizeOfEventHandlerMulticastOfPCConfig()
#define Sd_GetSizeOfEventHandlerTcp()                                                               Sd_GetSizeOfEventHandlerTcpOfPCConfig()
#define Sd_GetSizeOfEventHandlerUdp()                                                               Sd_GetSizeOfEventHandlerUdpOfPCConfig()
#define Sd_GetSizeOfInstance()                                                                      Sd_GetSizeOfInstanceOfPCConfig()
#define Sd_GetSizeOfInstanceDyn()                                                                   Sd_GetSizeOfInstanceDynOfPCConfig()
#define Sd_GetSizeOfIpAddrRequest()                                                                 Sd_GetSizeOfIpAddrRequestOfPCConfig()
#define Sd_GetSizeOfMethod()                                                                        Sd_GetSizeOfMethodOfPCConfig()
#define Sd_GetSizeOfMulticastEndpointAddr()                                                         Sd_GetSizeOfMulticastEndpointAddrOfPCConfig()
#define Sd_GetSizeOfMulticastSoConId()                                                              Sd_GetSizeOfMulticastSoConIdOfPCConfig()
#define Sd_GetSizeOfOptionIndex()                                                                   Sd_GetSizeOfOptionIndexOfPCConfig()
#define Sd_GetSizeOfPayload()                                                                       Sd_GetSizeOfPayloadOfPCConfig()
#define Sd_GetSizeOfPortSet()                                                                       Sd_GetSizeOfPortSetOfPCConfig()
#define Sd_GetSizeOfRequestCnt()                                                                    Sd_GetSizeOfRequestCntOfPCConfig()
#define Sd_GetSizeOfRoutingGroup()                                                                  Sd_GetSizeOfRoutingGroupOfPCConfig()
#define Sd_GetSizeOfRoutingGroupDyn()                                                               Sd_GetSizeOfRoutingGroupDynOfPCConfig()
#define Sd_GetSizeOfRxEvent()                                                                       Sd_GetSizeOfRxEventOfPCConfig()
#define Sd_GetSizeOfSendEntry()                                                                     Sd_GetSizeOfSendEntryOfPCConfig()
#define Sd_GetSizeOfServer()                                                                        Sd_GetSizeOfServerOfPCConfig()
#define Sd_GetSizeOfServerDyn()                                                                     Sd_GetSizeOfServerDynOfPCConfig()
#define Sd_GetSizeOfServerMap()                                                                     Sd_GetSizeOfServerMapOfPCConfig()
#define Sd_GetSizeOfServerTimer()                                                                   Sd_GetSizeOfServerTimerOfPCConfig()
#define Sd_GetSizeOfServiceGroup()                                                                  Sd_GetSizeOfServiceGroupOfPCConfig()
#define Sd_GetSizeOfServiceGroupMap()                                                               Sd_GetSizeOfServiceGroupMapOfPCConfig()
#define Sd_GetSizeOfServiceGroupMember()                                                            Sd_GetSizeOfServiceGroupMemberOfPCConfig()
#define Sd_GetSizeOfSoConActivationMap()                                                            Sd_GetSizeOfSoConActivationMapOfPCConfig()
#define Sd_GetSizeOfTcpSoConId()                                                                    Sd_GetSizeOfTcpSoConIdOfPCConfig()
#define Sd_GetSizeOfTcpSoConModeMap()                                                               Sd_GetSizeOfTcpSoConModeMapOfPCConfig()
#define Sd_GetSizeOfTriggerTransmit()                                                               Sd_GetSizeOfTriggerTransmitOfPCConfig()
#define Sd_GetSizeOfUdpSoCon()                                                                      Sd_GetSizeOfUdpSoConOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  SdPCSetDataMacros  Sd Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define Sd_SetAddrOfAddressStorage(Index, Value)                                                    Sd_GetAddressStorageOfPCConfig()[(Index)].AddrOfAddressStorage = (Value)
#define Sd_SetFlagsOfAddressStorage(Index, Value)                                                   Sd_GetAddressStorageOfPCConfig()[(Index)].FlagsOfAddressStorage = (Value)
#define Sd_SetRxMulticastFlagsOfAddressStorage(Index, Value)                                        Sd_GetAddressStorageOfPCConfig()[(Index)].RxMulticastFlagsOfAddressStorage = (Value)
#define Sd_SetRxMulticastSessionIdOfAddressStorage(Index, Value)                                    Sd_GetAddressStorageOfPCConfig()[(Index)].RxMulticastSessionIdOfAddressStorage = (Value)
#define Sd_SetRxUnicastFlagsOfAddressStorage(Index, Value)                                          Sd_GetAddressStorageOfPCConfig()[(Index)].RxUnicastFlagsOfAddressStorage = (Value)
#define Sd_SetRxUnicastSessionIdOfAddressStorage(Index, Value)                                      Sd_GetAddressStorageOfPCConfig()[(Index)].RxUnicastSessionIdOfAddressStorage = (Value)
#define Sd_SetSendEntryNrPendingIdxOfAddressStorage(Index, Value)                                   Sd_GetAddressStorageOfPCConfig()[(Index)].SendEntryNrPendingIdxOfAddressStorage = (Value)
#define Sd_SetSessionIdCounterOfAddressStorage(Index, Value)                                        Sd_GetAddressStorageOfPCConfig()[(Index)].SessionIdCounterOfAddressStorage = (Value)
#define Sd_SetAddressStorageServerIdxOfClientDyn(Index, Value)                                      Sd_GetClientDynOfPCConfig()[(Index)].AddressStorageServerIdxOfClientDyn = (Value)
#define Sd_SetCurrentStateOfClientDyn(Index, Value)                                                 Sd_GetClientDynOfPCConfig()[(Index)].CurrentStateOfClientDyn = (Value)
#define Sd_SetEventMainOfClientDyn(Index, Value)                                                    Sd_GetClientDynOfPCConfig()[(Index)].EventMainOfClientDyn = (Value)
#define Sd_SetEventRxOfClientDyn(Index, Value)                                                      Sd_GetClientDynOfPCConfig()[(Index)].EventRxOfClientDyn = (Value)
#define Sd_SetMethodTcpSoConIdOfClientDyn(Index, Value)                                             Sd_GetClientDynOfPCConfig()[(Index)].MethodTcpSoConIdOfClientDyn = (Value)
#define Sd_SetMethodUdpSoConIdOfClientDyn(Index, Value)                                             Sd_GetClientDynOfPCConfig()[(Index)].MethodUdpSoConIdOfClientDyn = (Value)
#define Sd_SetOfferedTTLOfClientDyn(Index, Value)                                                   Sd_GetClientDynOfPCConfig()[(Index)].OfferedTTLOfClientDyn = (Value)
#define Sd_SetRepetitionRunOfClientDyn(Index, Value)                                                Sd_GetClientDynOfPCConfig()[(Index)].RepetitionRunOfClientDyn = (Value)
#define Sd_SetRetryCounterOfClientDyn(Index, Value)                                                 Sd_GetClientDynOfPCConfig()[(Index)].RetryCounterOfClientDyn = (Value)
#define Sd_SetRetryTimerOfClientDyn(Index, Value)                                                   Sd_GetClientDynOfPCConfig()[(Index)].RetryTimerOfClientDyn = (Value)
#define Sd_SetServerTcpEndpointAddrOfClientDyn(Index, Value)                                        Sd_GetClientDynOfPCConfig()[(Index)].ServerTcpEndpointAddrOfClientDyn = (Value)
#define Sd_SetServerUdpEndpointAddrOfClientDyn(Index, Value)                                        Sd_GetClientDynOfPCConfig()[(Index)].ServerUdpEndpointAddrOfClientDyn = (Value)
#define Sd_SetServiceGroupReqCounterOfClientDyn(Index, Value)                                       Sd_GetClientDynOfPCConfig()[(Index)].ServiceGroupReqCounterOfClientDyn = (Value)
#define Sd_SetStateMachineExecutionRequestedOfClientDyn(Index, Value)                               Sd_GetClientDynOfPCConfig()[(Index)].StateMachineExecutionRequestedOfClientDyn = (Value)
#define Sd_SetStateMachineOfClientDyn(Index, Value)                                                 Sd_GetClientDynOfPCConfig()[(Index)].StateMachineOfClientDyn = (Value)
#define Sd_SetStateSwcOfClientDyn(Index, Value)                                                     Sd_GetClientDynOfPCConfig()[(Index)].StateSwcOfClientDyn = (Value)
#define Sd_SetTimeToTriggerSendOfClientDyn(Index, Value)                                            Sd_GetClientDynOfPCConfig()[(Index)].TimeToTriggerSendOfClientDyn = (Value)
#define Sd_SetTimerTTLOfClientDyn(Index, Value)                                                     Sd_GetClientDynOfPCConfig()[(Index)].TimerTTLOfClientDyn = (Value)
#define Sd_SetAddressStorageIdxOfClientList(Index, Value)                                           Sd_GetClientListOfPCConfig()[(Index)].AddressStorageIdxOfClientList = (Value)
#define Sd_SetAssignedTcpSoConIdOfClientList(Index, Value)                                          Sd_GetClientListOfPCConfig()[(Index)].AssignedTcpSoConIdOfClientList = (Value)
#define Sd_SetAssignedUdpSoConIdOfClientList(Index, Value)                                          Sd_GetClientListOfPCConfig()[(Index)].AssignedUdpSoConIdOfClientList = (Value)
#define Sd_SetClientStateOfClientList(Index, Value)                                                 Sd_GetClientListOfPCConfig()[(Index)].ClientStateOfClientList = (Value)
#define Sd_SetEndpointStorageTcpIdxOfClientList(Index, Value)                                       Sd_GetClientListOfPCConfig()[(Index)].EndpointStorageTcpIdxOfClientList = (Value)
#define Sd_SetEndpointStorageUdpIdxOfClientList(Index, Value)                                       Sd_GetClientListOfPCConfig()[(Index)].EndpointStorageUdpIdxOfClientList = (Value)
#define Sd_SetNrOfReferencesOfClientList(Index, Value)                                              Sd_GetClientListOfPCConfig()[(Index)].NrOfReferencesOfClientList = (Value)
#define Sd_SetRequestedTTLOfClientList(Index, Value)                                                Sd_GetClientListOfPCConfig()[(Index)].RequestedTTLOfClientList = (Value)
#define Sd_SetRxReservedOfClientList(Index, Value)                                                  Sd_GetClientListOfPCConfig()[(Index)].RxReservedOfClientList = (Value)
#define Sd_SetSubscribedUntilOfClientList(Index, Value)                                             Sd_GetClientListOfPCConfig()[(Index)].SubscribedUntilOfClientList = (Value)
#define Sd_SetCommonInitialDelay(Index, Value)                                                      Sd_GetCommonInitialDelayOfPCConfig()[(Index)] = (Value)
#define Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(Index, Value)                                  Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].AcknowledgedTTLOfConsumedEventgroupDyn = (Value)
#define Sd_SetCurrentStateOfConsumedEventgroupDyn(Index, Value)                                     Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].CurrentStateOfConsumedEventgroupDyn = (Value)
#define Sd_SetEventOfConsumedEventgroupDyn(Index, Value)                                            Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].EventOfConsumedEventgroupDyn = (Value)
#define Sd_SetMulticastSoConIdOfConsumedEventgroupDyn(Index, Value)                                 Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].MulticastSoConIdOfConsumedEventgroupDyn = (Value)
#define Sd_SetRxIndicationCountOfConsumedEventgroupDyn(Index, Value)                                Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].RxIndicationCountOfConsumedEventgroupDyn = (Value)
#define Sd_SetServiceModeRequestOfConsumedEventgroupDyn(Index, Value)                               Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].ServiceModeRequestOfConsumedEventgroupDyn = (Value)
#define Sd_SetSoConMarkedForClosureOfConsumedEventgroupDyn(Index, Value)                            Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].SoConMarkedForClosureOfConsumedEventgroupDyn = (Value)
#define Sd_SetStateMachineOfConsumedEventgroupDyn(Index, Value)                                     Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].StateMachineOfConsumedEventgroupDyn = (Value)
#define Sd_SetTcpSoConIdOfConsumedEventgroupDyn(Index, Value)                                       Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TcpSoConIdOfConsumedEventgroupDyn = (Value)
#define Sd_SetTimerTTLOfConsumedEventgroupDyn(Index, Value)                                         Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TimerTTLOfConsumedEventgroupDyn = (Value)
#define Sd_SetTriggerSubscriptionOfConsumedEventgroupDyn(Index, Value)                              Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].TriggerSubscriptionOfConsumedEventgroupDyn = (Value)
#define Sd_SetUdpSoConIdOfConsumedEventgroupDyn(Index, Value)                                       Sd_GetConsumedEventgroupDynOfPCConfig()[(Index)].UdpSoConIdOfConsumedEventgroupDyn = (Value)
#define Sd_SetAddrOfEndpointStorage(Index, Value)                                                   Sd_GetEndpointStorageOfPCConfig()[(Index)].AddrOfEndpointStorage = (Value)
#define Sd_SetNrOfReferencesOfEndpointStorage(Index, Value)                                         Sd_GetEndpointStorageOfPCConfig()[(Index)].NrOfReferencesOfEndpointStorage = (Value)
#define Sd_SetTypeOfEndpointStorage(Index, Value)                                                   Sd_GetEndpointStorageOfPCConfig()[(Index)].TypeOfEndpointStorage = (Value)
#define Sd_SetNrOfClientsOfEventHandlerDyn(Index, Value)                                            Sd_GetEventHandlerDynOfPCConfig()[(Index)].NrOfClientsOfEventHandlerDyn = (Value)
#define Sd_SetRequestStateOfEventHandlerDyn(Index, Value)                                           Sd_GetEventHandlerDynOfPCConfig()[(Index)].RequestStateOfEventHandlerDyn = (Value)
#define Sd_SetStateMachineOfEventHandlerDyn(Index, Value)                                           Sd_GetEventHandlerDynOfPCConfig()[(Index)].StateMachineOfEventHandlerDyn = (Value)
#define Sd_SetNextStateMachineRunOfInstanceDyn(Index, Value)                                        Sd_GetInstanceDynOfPCConfig()[(Index)].NextStateMachineRunOfInstanceDyn = (Value)
#define Sd_SetRunModeOfInstanceDyn(Index, Value)                                                    Sd_GetInstanceDynOfPCConfig()[(Index)].RunModeOfInstanceDyn = (Value)
#define Sd_SetRxEventEndIdxOfInstanceDyn(Index, Value)                                              Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventEndIdxOfInstanceDyn = (Value)
#define Sd_SetRxEventListFullOfInstanceDyn(Index, Value)                                            Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventListFullOfInstanceDyn = (Value)
#define Sd_SetRxEventStartIdxOfInstanceDyn(Index, Value)                                            Sd_GetInstanceDynOfPCConfig()[(Index)].RxEventStartIdxOfInstanceDyn = (Value)
#define Sd_SetSendEntryEndIdxOfInstanceDyn(Index, Value)                                            Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryEndIdxOfInstanceDyn = (Value)
#define Sd_SetSendEntryNrPendingIdxOfInstanceDyn(Index, Value)                                      Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryNrPendingIdxOfInstanceDyn = (Value)
#define Sd_SetSendEntryStartIdxOfInstanceDyn(Index, Value)                                          Sd_GetInstanceDynOfPCConfig()[(Index)].SendEntryStartIdxOfInstanceDyn = (Value)
#define Sd_SetStateOfInstanceDyn(Index, Value)                                                      Sd_GetInstanceDynOfPCConfig()[(Index)].StateOfInstanceDyn = (Value)
#define Sd_SetMulticastEndpointAddr(Index, Value)                                                   Sd_GetMulticastEndpointAddrOfPCConfig()[(Index)] = (Value)
#define Sd_SetNrOfOptions(Value)                                                                    (*(Sd_GetNrOfOptionsOfPCConfig())) = (Value)
#define Sd_SetOptionIndex(Index, Value)                                                             Sd_GetOptionIndexOfPCConfig()[(Index)] = (Value)
#define Sd_SetPayload(Index, Value)                                                                 Sd_GetPayloadOfPCConfig()[(Index)] = (Value)
#define Sd_SetPortSet(Index, Value)                                                                 Sd_GetPortSetOfPCConfig()[(Index)] = (Value)
#define Sd_SetRequestCnt(Index, Value)                                                              Sd_GetRequestCntOfPCConfig()[(Index)] = (Value)
#define Sd_SetStatusOfRoutingGroupDyn(Index, Value)                                                 Sd_GetRoutingGroupDynOfPCConfig()[(Index)].StatusOfRoutingGroupDyn = (Value)
#define Sd_SetClientListIdxOfRxEvent(Index, Value)                                                  Sd_GetRxEventOfPCConfig()[(Index)].ClientListIdxOfRxEvent = (Value)
#define Sd_SetEventHandlerIdxOfRxEvent(Index, Value)                                                Sd_GetRxEventOfPCConfig()[(Index)].EventHandlerIdxOfRxEvent = (Value)
#define Sd_SetEventOfRxEvent(Index, Value)                                                          Sd_GetRxEventOfPCConfig()[(Index)].EventOfRxEvent = (Value)
#define Sd_SetAddressStorageIdxOfSendEntry(Index, Value)                                            Sd_GetSendEntryOfPCConfig()[(Index)].AddressStorageIdxOfSendEntry = (Value)
#define Sd_SetClientIdxOfSendEntry(Index, Value)                                                    Sd_GetSendEntryOfPCConfig()[(Index)].ClientIdxOfSendEntry = (Value)
#define Sd_SetClientListIdxOfSendEntry(Index, Value)                                                Sd_GetSendEntryOfPCConfig()[(Index)].ClientListIdxOfSendEntry = (Value)
#define Sd_SetConsumedEventgroupIdxOfSendEntry(Index, Value)                                        Sd_GetSendEntryOfPCConfig()[(Index)].ConsumedEventgroupIdxOfSendEntry = (Value)
#define Sd_SetEntryTypeOfSendEntry(Index, Value)                                                    Sd_GetSendEntryOfPCConfig()[(Index)].EntryTypeOfSendEntry = (Value)
#define Sd_SetEventHandlerIdOfSendEntry(Index, Value)                                               Sd_GetSendEntryOfPCConfig()[(Index)].EventHandlerIdOfSendEntry = (Value)
#define Sd_SetEventHandlerIdxOfSendEntry(Index, Value)                                              Sd_GetSendEntryOfPCConfig()[(Index)].EventHandlerIdxOfSendEntry = (Value)
#define Sd_SetInstanceIdOfSendEntry(Index, Value)                                                   Sd_GetSendEntryOfPCConfig()[(Index)].InstanceIdOfSendEntry = (Value)
#define Sd_SetInstanceIdxOfSendEntry(Index, Value)                                                  Sd_GetSendEntryOfPCConfig()[(Index)].InstanceIdxOfSendEntry = (Value)
#define Sd_SetMajorVersionOfSendEntry(Index, Value)                                                 Sd_GetSendEntryOfPCConfig()[(Index)].MajorVersionOfSendEntry = (Value)
#define Sd_SetReservedFieldOfSendEntry(Index, Value)                                                Sd_GetSendEntryOfPCConfig()[(Index)].ReservedFieldOfSendEntry = (Value)
#define Sd_SetSendEntryNextIdxOfSendEntry(Index, Value)                                             Sd_GetSendEntryOfPCConfig()[(Index)].SendEntryNextIdxOfSendEntry = (Value)
#define Sd_SetServerIdxOfSendEntry(Index, Value)                                                    Sd_GetSendEntryOfPCConfig()[(Index)].ServerIdxOfSendEntry = (Value)
#define Sd_SetServiceIdOfSendEntry(Index, Value)                                                    Sd_GetSendEntryOfPCConfig()[(Index)].ServiceIdOfSendEntry = (Value)
#define Sd_SetTimeToSendOfSendEntry(Index, Value)                                                   Sd_GetSendEntryOfPCConfig()[(Index)].TimeToSendOfSendEntry = (Value)
#define Sd_SetValidOfSendEntry(Index, Value)                                                        Sd_GetSendEntryOfPCConfig()[(Index)].ValidOfSendEntry = (Value)
#define Sd_SetInitialOfferRepetitionRunOfServerDyn(Index, Value)                                    Sd_GetServerDynOfPCConfig()[(Index)].InitialOfferRepetitionRunOfServerDyn = (Value)
#define Sd_SetServiceGroupReqCounterOfServerDyn(Index, Value)                                       Sd_GetServerDynOfPCConfig()[(Index)].ServiceGroupReqCounterOfServerDyn = (Value)
#define Sd_SetStateMachineExecutionRequestedOfServerDyn(Index, Value)                               Sd_GetServerDynOfPCConfig()[(Index)].StateMachineExecutionRequestedOfServerDyn = (Value)
#define Sd_SetStateMachineOfServerDyn(Index, Value)                                                 Sd_GetServerDynOfPCConfig()[(Index)].StateMachineOfServerDyn = (Value)
#define Sd_SetStateSwcOfServerDyn(Index, Value)                                                     Sd_GetServerDynOfPCConfig()[(Index)].StateSwcOfServerDyn = (Value)
#define Sd_SetTimeToTriggerSendOfServerDyn(Index, Value)                                            Sd_GetServerDynOfPCConfig()[(Index)].TimeToTriggerSendOfServerDyn = (Value)
#define Sd_SetNrOfActivationsOfSoConActivationMap(Index, Value)                                     Sd_GetSoConActivationMapOfPCConfig()[(Index)].NrOfActivationsOfSoConActivationMap = (Value)
#define Sd_SetSoConIdOfSoConActivationMap(Index, Value)                                             Sd_GetSoConActivationMapOfPCConfig()[(Index)].SoConIdOfSoConActivationMap = (Value)
#define Sd_SetTcpSoConModeMap(Index, Value)                                                         Sd_GetTcpSoConModeMapOfPCConfig()[(Index)] = (Value)
#define Sd_SetClientListIdxOfTriggerTransmit(Index, Value)                                          Sd_GetTriggerTransmitOfPCConfig()[(Index)].ClientListIdxOfTriggerTransmit = (Value)
#define Sd_SetEventHandlerIdxOfTriggerTransmit(Index, Value)                                        Sd_GetTriggerTransmitOfPCConfig()[(Index)].EventHandlerIdxOfTriggerTransmit = (Value)
#define Sd_SetStateOfTriggerTransmit(Index, Value)                                                  Sd_GetTriggerTransmitOfPCConfig()[(Index)].StateOfTriggerTransmit = (Value)
#define Sd_SetTriggerTransmitEndIdx(Value)                                                          (*(Sd_GetTriggerTransmitEndIdxOfPCConfig())) = (Value)
#define Sd_SetTriggerTransmitFull(Value)                                                            (*(Sd_GetTriggerTransmitFullOfPCConfig())) = (Value)
#define Sd_SetTriggerTransmitStartIdx(Value)                                                        (*(Sd_GetTriggerTransmitStartIdxOfPCConfig())) = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  SdPCGetAddressOfDataMacros  Sd Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define Sd_GetAddrAddrOfAddressStorage(Index)                                                       (&Sd_GetAddrOfAddressStorage(Index))
#define Sd_GetAddrCapabilityRecord(Index)                                                           (&Sd_GetCapabilityRecord(Index))
#define Sd_GetAddrMethodTcpSoConIdOfClientDyn(Index)                                                (&Sd_GetMethodTcpSoConIdOfClientDyn(Index))
#define Sd_GetAddrMethodUdpSoConIdOfClientDyn(Index)                                                (&Sd_GetMethodUdpSoConIdOfClientDyn(Index))
#define Sd_GetAddrRetryTimerOfClientDyn(Index)                                                      (&Sd_GetRetryTimerOfClientDyn(Index))
#define Sd_GetAddrServerTcpEndpointAddrOfClientDyn(Index)                                           (&Sd_GetServerTcpEndpointAddrOfClientDyn(Index))
#define Sd_GetAddrServerUdpEndpointAddrOfClientDyn(Index)                                           (&Sd_GetServerUdpEndpointAddrOfClientDyn(Index))
#define Sd_GetAddrTimeToTriggerSendOfClientDyn(Index)                                               (&Sd_GetTimeToTriggerSendOfClientDyn(Index))
#define Sd_GetAddrTimerTTLOfClientDyn(Index)                                                        (&Sd_GetTimerTTLOfClientDyn(Index))
#define Sd_GetAddrRxReservedOfClientList(Index)                                                     (&Sd_GetRxReservedOfClientList(Index))
#define Sd_GetAddrSubscribedUntilOfClientList(Index)                                                (&Sd_GetSubscribedUntilOfClientList(Index))
#define Sd_GetAddrTimerTTLOfConsumedEventgroupDyn(Index)                                            (&Sd_GetTimerTTLOfConsumedEventgroupDyn(Index))
#define Sd_GetAddrAddrOfEndpointStorage(Index)                                                      (&Sd_GetAddrOfEndpointStorage(Index))
#define Sd_GetAddrNextStateMachineRunOfInstanceDyn(Index)                                           (&Sd_GetNextStateMachineRunOfInstanceDyn(Index))
#define Sd_GetAddrMulticastEndpointAddr(Index)                                                      (&Sd_GetMulticastEndpointAddr(Index))
#define Sd_GetAddrPayload(Index)                                                                    (&Sd_GetPayload(Index))
#define Sd_GetAddrTimeToSendOfSendEntry(Index)                                                      (&Sd_GetTimeToSendOfSendEntry(Index))
#define Sd_GetAddrTimeToTriggerSendOfServerDyn(Index)                                               (&Sd_GetTimeToTriggerSendOfServerDyn(Index))
/** 
  \}
*/ 

/** 
  \defgroup  SdPCHasMacros  Sd Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define Sd_HasAddressStorage()                                                                      (Sd_GetAddressStorageOfPCConfig() != NULL_PTR)
#define Sd_HasAddrOfAddressStorage()                                                                (TRUE != FALSE)
#define Sd_HasFlagsOfAddressStorage()                                                               (TRUE != FALSE)
#define Sd_HasRxMulticastFlagsOfAddressStorage()                                                    (TRUE != FALSE)
#define Sd_HasRxMulticastSessionIdOfAddressStorage()                                                (TRUE != FALSE)
#define Sd_HasRxUnicastFlagsOfAddressStorage()                                                      (TRUE != FALSE)
#define Sd_HasRxUnicastSessionIdOfAddressStorage()                                                  (TRUE != FALSE)
#define Sd_HasSendEntryNrPendingIdxOfAddressStorage()                                               (TRUE != FALSE)
#define Sd_HasSessionIdCounterOfAddressStorage()                                                    (TRUE != FALSE)
#define Sd_HasCapabilityRecord()                                                                    (Sd_GetCapabilityRecordOfPCConfig() != NULL_PTR)
#define Sd_HasCapabilityRecordFunctionCalloutPtr()                                                  (Sd_GetCapabilityRecordFunctionCalloutPtrOfPCConfig() != NULL_PTR)
#define Sd_HasClient()                                                                              (Sd_GetClientOfPCConfig() != NULL_PTR)
#define Sd_HasAutoRequireOfClient()                                                                 (TRUE != FALSE)
#define Sd_HasCapabilityRecordEndIdxOfClient()                                                      (TRUE != FALSE)
#define Sd_HasCapabilityRecordFunctionCalloutPtrIdxOfClient()                                       (TRUE != FALSE)
#define Sd_HasCapabilityRecordFunctionCalloutPtrUsedOfClient()                                      (TRUE != FALSE)
#define Sd_HasCapabilityRecordStartIdxOfClient()                                                    (TRUE != FALSE)
#define Sd_HasCapabilityRecordUsedOfClient()                                                        (TRUE != FALSE)
#define Sd_HasClientTimerIdxOfClient()                                                              (TRUE != FALSE)
#define Sd_HasCommonInitialDelayIdxOfClient()                                                       (TRUE != FALSE)
#define Sd_HasCommonInitialDelayUsedOfClient()                                                      (TRUE != FALSE)
#define Sd_HasConsumedEventgroupEndIdxOfClient()                                                    (TRUE != FALSE)
#define Sd_HasConsumedEventgroupStartIdxOfClient()                                                  (TRUE != FALSE)
#define Sd_HasConsumedEventgroupUsedOfClient()                                                      (TRUE != FALSE)
#define Sd_HasHandleIdOfClient()                                                                    (TRUE != FALSE)
#define Sd_HasInstanceIdOfClient()                                                                  (TRUE != FALSE)
#define Sd_HasInstanceIdxOfClient()                                                                 (TRUE != FALSE)
#define Sd_HasMajorVersionOfClient()                                                                (TRUE != FALSE)
#define Sd_HasMethodIdxOfClient()                                                                   (TRUE != FALSE)
#define Sd_HasMethodUsedOfClient()                                                                  (TRUE != FALSE)
#define Sd_HasMinorVersionOfClient()                                                                (TRUE != FALSE)
#define Sd_HasMinorVersionWildcardOfClient()                                                        (TRUE != FALSE)
#define Sd_HasServiceGroupMemberOfClient()                                                          (TRUE != FALSE)
#define Sd_HasServiceIdOfClient()                                                                   (TRUE != FALSE)
#define Sd_HasTcpSoConIdEndIdxOfClient()                                                            (TRUE != FALSE)
#define Sd_HasTcpSoConIdStartIdxOfClient()                                                          (TRUE != FALSE)
#define Sd_HasTcpSoConIdUsedOfClient()                                                              (TRUE != FALSE)
#define Sd_HasUdpSoConEndIdxOfClient()                                                              (TRUE != FALSE)
#define Sd_HasUdpSoConStartIdxOfClient()                                                            (TRUE != FALSE)
#define Sd_HasUdpSoConUsedOfClient()                                                                (TRUE != FALSE)
#define Sd_HasClientDyn()                                                                           (Sd_GetClientDynOfPCConfig() != NULL_PTR)
#define Sd_HasAddressStorageServerIdxOfClientDyn()                                                  (TRUE != FALSE)
#define Sd_HasCurrentStateOfClientDyn()                                                             (TRUE != FALSE)
#define Sd_HasEventMainOfClientDyn()                                                                (TRUE != FALSE)
#define Sd_HasEventRxOfClientDyn()                                                                  (TRUE != FALSE)
#define Sd_HasMethodTcpSoConIdOfClientDyn()                                                         (TRUE != FALSE)
#define Sd_HasMethodUdpSoConIdOfClientDyn()                                                         (TRUE != FALSE)
#define Sd_HasOfferedTTLOfClientDyn()                                                               (TRUE != FALSE)
#define Sd_HasRepetitionRunOfClientDyn()                                                            (TRUE != FALSE)
#define Sd_HasRetryCounterOfClientDyn()                                                             (TRUE != FALSE)
#define Sd_HasRetryTimerOfClientDyn()                                                               (TRUE != FALSE)
#define Sd_HasServerTcpEndpointAddrOfClientDyn()                                                    (TRUE != FALSE)
#define Sd_HasServerUdpEndpointAddrOfClientDyn()                                                    (TRUE != FALSE)
#define Sd_HasServiceGroupReqCounterOfClientDyn()                                                   (TRUE != FALSE)
#define Sd_HasStateMachineExecutionRequestedOfClientDyn()                                           (TRUE != FALSE)
#define Sd_HasStateMachineOfClientDyn()                                                             (TRUE != FALSE)
#define Sd_HasStateSwcOfClientDyn()                                                                 (TRUE != FALSE)
#define Sd_HasTimeToTriggerSendOfClientDyn()                                                        (TRUE != FALSE)
#define Sd_HasTimerTTLOfClientDyn()                                                                 (TRUE != FALSE)
#define Sd_HasClientList()                                                                          (Sd_GetClientListOfPCConfig() != NULL_PTR)
#define Sd_HasAddressStorageIdxOfClientList()                                                       (TRUE != FALSE)
#define Sd_HasAssignedTcpSoConIdOfClientList()                                                      (TRUE != FALSE)
#define Sd_HasAssignedUdpSoConIdOfClientList()                                                      (TRUE != FALSE)
#define Sd_HasClientStateOfClientList()                                                             (TRUE != FALSE)
#define Sd_HasEndpointStorageTcpIdxOfClientList()                                                   (TRUE != FALSE)
#define Sd_HasEndpointStorageUdpIdxOfClientList()                                                   (TRUE != FALSE)
#define Sd_HasNrOfReferencesOfClientList()                                                          (TRUE != FALSE)
#define Sd_HasRequestedTTLOfClientList()                                                            (TRUE != FALSE)
#define Sd_HasRxReservedOfClientList()                                                              (TRUE != FALSE)
#define Sd_HasSubscribedUntilOfClientList()                                                         (TRUE != FALSE)
#define Sd_HasClientMap()                                                                           (Sd_GetClientMapOfPCConfig() != NULL_PTR)
#define Sd_HasClientIdxOfClientMap()                                                                (TRUE != FALSE)
#define Sd_HasClientUsedOfClientMap()                                                               (TRUE != FALSE)
#define Sd_HasInvalidHndOfClientMap()                                                               (TRUE != FALSE)
#define Sd_HasClientTimer()                                                                         (Sd_GetClientTimerOfPCConfig() != NULL_PTR)
#define Sd_HasInitialFindDelayMaxOfClientTimer()                                                    (TRUE != FALSE)
#define Sd_HasInitialFindDelayMinOfClientTimer()                                                    (TRUE != FALSE)
#define Sd_HasInitialFindRepetitionBaseDelayOfClientTimer()                                         (TRUE != FALSE)
#define Sd_HasInitialFindRepetitionsMaxOfClientTimer()                                              (TRUE != FALSE)
#define Sd_HasRequestResponseMaxDelayOfClientTimer()                                                (TRUE != FALSE)
#define Sd_HasRequestResponseMinDelayOfClientTimer()                                                (TRUE != FALSE)
#define Sd_HasTTLOfClientTimer()                                                                    (TRUE != FALSE)
#define Sd_HasCommonInitialDelay()                                                                  (Sd_GetCommonInitialDelayOfPCConfig() != NULL_PTR)
#define Sd_HasConsumedEventgroup()                                                                  (Sd_GetConsumedEventgroupOfPCConfig() != NULL_PTR)
#define Sd_HasAutoRequireOfConsumedEventgroup()                                                     (TRUE != FALSE)
#define Sd_HasClientIdxOfConsumedEventgroup()                                                       (TRUE != FALSE)
#define Sd_HasClientTimerIdxOfConsumedEventgroup()                                                  (TRUE != FALSE)
#define Sd_HasEventGroupIdOfConsumedEventgroup()                                                    (TRUE != FALSE)
#define Sd_HasHandleIdOfConsumedEventgroup()                                                        (TRUE != FALSE)
#define Sd_HasMulticastEndpointAddrIdxOfConsumedEventgroup()                                        (TRUE != FALSE)
#define Sd_HasMulticastEndpointAddrUsedOfConsumedEventgroup()                                       (TRUE != FALSE)
#define Sd_HasMulticastSoConIdEndIdxOfConsumedEventgroup()                                          (TRUE != FALSE)
#define Sd_HasMulticastSoConIdStartIdxOfConsumedEventgroup()                                        (TRUE != FALSE)
#define Sd_HasMulticastSoConIdUsedOfConsumedEventgroup()                                            (TRUE != FALSE)
#define Sd_HasRoutingGroupMulticastActRefIdxOfConsumedEventgroup()                                  (TRUE != FALSE)
#define Sd_HasRoutingGroupMulticastActRefUsedOfConsumedEventgroup()                                 (TRUE != FALSE)
#define Sd_HasRoutingGroupTcpActRefIdxOfConsumedEventgroup()                                        (TRUE != FALSE)
#define Sd_HasRoutingGroupTcpActRefUsedOfConsumedEventgroup()                                       (TRUE != FALSE)
#define Sd_HasRoutingGroupUdpActRefIdxOfConsumedEventgroup()                                        (TRUE != FALSE)
#define Sd_HasRoutingGroupUdpActRefUsedOfConsumedEventgroup()                                       (TRUE != FALSE)
#define Sd_HasConsumedEventgroupDyn()                                                               (Sd_GetConsumedEventgroupDynOfPCConfig() != NULL_PTR)
#define Sd_HasAcknowledgedTTLOfConsumedEventgroupDyn()                                              (TRUE != FALSE)
#define Sd_HasCurrentStateOfConsumedEventgroupDyn()                                                 (TRUE != FALSE)
#define Sd_HasEventOfConsumedEventgroupDyn()                                                        (TRUE != FALSE)
#define Sd_HasMulticastSoConIdOfConsumedEventgroupDyn()                                             (TRUE != FALSE)
#define Sd_HasRxIndicationCountOfConsumedEventgroupDyn()                                            (TRUE != FALSE)
#define Sd_HasServiceModeRequestOfConsumedEventgroupDyn()                                           (TRUE != FALSE)
#define Sd_HasSoConMarkedForClosureOfConsumedEventgroupDyn()                                        (TRUE != FALSE)
#define Sd_HasStateMachineOfConsumedEventgroupDyn()                                                 (TRUE != FALSE)
#define Sd_HasTcpSoConIdOfConsumedEventgroupDyn()                                                   (TRUE != FALSE)
#define Sd_HasTimerTTLOfConsumedEventgroupDyn()                                                     (TRUE != FALSE)
#define Sd_HasTriggerSubscriptionOfConsumedEventgroupDyn()                                          (TRUE != FALSE)
#define Sd_HasUdpSoConIdOfConsumedEventgroupDyn()                                                   (TRUE != FALSE)
#define Sd_HasConsumedEventgroupMap()                                                               (Sd_GetConsumedEventgroupMapOfPCConfig() != NULL_PTR)
#define Sd_HasConsumedEventgroupIdxOfConsumedEventgroupMap()                                        (TRUE != FALSE)
#define Sd_HasConsumedEventgroupUsedOfConsumedEventgroupMap()                                       (TRUE != FALSE)
#define Sd_HasInvalidHndOfConsumedEventgroupMap()                                                   (TRUE != FALSE)
#define Sd_HasEndpointStorage()                                                                     (Sd_GetEndpointStorageOfPCConfig() != NULL_PTR)
#define Sd_HasAddrOfEndpointStorage()                                                               (TRUE != FALSE)
#define Sd_HasNrOfReferencesOfEndpointStorage()                                                     (TRUE != FALSE)
#define Sd_HasTypeOfEndpointStorage()                                                               (TRUE != FALSE)
#define Sd_HasEventHandler()                                                                        (Sd_GetEventHandlerOfPCConfig() != NULL_PTR)
#define Sd_HasClientListEndIdxOfEventHandler()                                                      (TRUE != FALSE)
#define Sd_HasClientListStartIdxOfEventHandler()                                                    (TRUE != FALSE)
#define Sd_HasEventGroupIdOfEventHandler()                                                          (TRUE != FALSE)
#define Sd_HasEventHandlerMulticastIdxOfEventHandler()                                              (TRUE != FALSE)
#define Sd_HasEventHandlerMulticastUsedOfEventHandler()                                             (TRUE != FALSE)
#define Sd_HasEventHandlerTcpIdxOfEventHandler()                                                    (TRUE != FALSE)
#define Sd_HasEventHandlerTcpUsedOfEventHandler()                                                   (TRUE != FALSE)
#define Sd_HasEventHandlerUdpIdxOfEventHandler()                                                    (TRUE != FALSE)
#define Sd_HasEventHandlerUdpUsedOfEventHandler()                                                   (TRUE != FALSE)
#define Sd_HasHandleIdOfEventHandler()                                                              (TRUE != FALSE)
#define Sd_HasMulticastThresholdOfEventHandler()                                                    (TRUE != FALSE)
#define Sd_HasServerIdxOfEventHandler()                                                             (TRUE != FALSE)
#define Sd_HasServerTimerIdxOfEventHandler()                                                        (TRUE != FALSE)
#define Sd_HasSoConActivationMapEndIdxOfEventHandler()                                              (TRUE != FALSE)
#define Sd_HasSoConActivationMapStartIdxOfEventHandler()                                            (TRUE != FALSE)
#define Sd_HasSoConActivationMapUsedOfEventHandler()                                                (TRUE != FALSE)
#define Sd_HasEventHandlerDyn()                                                                     (Sd_GetEventHandlerDynOfPCConfig() != NULL_PTR)
#define Sd_HasNrOfClientsOfEventHandlerDyn()                                                        (TRUE != FALSE)
#define Sd_HasRequestStateOfEventHandlerDyn()                                                       (TRUE != FALSE)
#define Sd_HasStateMachineOfEventHandlerDyn()                                                       (TRUE != FALSE)
#define Sd_HasEventHandlerMulticast()                                                               (Sd_GetEventHandlerMulticastOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroupActRefIdxOfEventHandlerMulticast()                                        (TRUE != FALSE)
#define Sd_HasRoutingGroupActRefUsedOfEventHandlerMulticast()                                       (TRUE != FALSE)
#define Sd_HasSoConIdOfEventHandlerMulticast()                                                      (TRUE != FALSE)
#define Sd_HasEventHandlerTcp()                                                                     (Sd_GetEventHandlerTcpOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroupActRefIdxOfEventHandlerTcp()                                              (TRUE != FALSE)
#define Sd_HasRoutingGroupActRefUsedOfEventHandlerTcp()                                             (TRUE != FALSE)
#define Sd_HasRoutingGroupTriggerIdxOfEventHandlerTcp()                                             (TRUE != FALSE)
#define Sd_HasRoutingGroupTriggerUsedOfEventHandlerTcp()                                            (TRUE != FALSE)
#define Sd_HasEventHandlerUdp()                                                                     (Sd_GetEventHandlerUdpOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroupActRefIdxOfEventHandlerUdp()                                              (TRUE != FALSE)
#define Sd_HasRoutingGroupActRefUsedOfEventHandlerUdp()                                             (TRUE != FALSE)
#define Sd_HasRoutingGroupTriggerIdxOfEventHandlerUdp()                                             (TRUE != FALSE)
#define Sd_HasRoutingGroupTriggerUsedOfEventHandlerUdp()                                            (TRUE != FALSE)
#define Sd_HasInstance()                                                                            (Sd_GetInstanceOfPCConfig() != NULL_PTR)
#define Sd_HasAddressStorageEndIdxOfInstance()                                                      (TRUE != FALSE)
#define Sd_HasAddressStorageStartIdxOfInstance()                                                    (TRUE != FALSE)
#define Sd_HasCapabilityRecordEndIdxOfInstance()                                                    (TRUE != FALSE)
#define Sd_HasCapabilityRecordStartIdxOfInstance()                                                  (TRUE != FALSE)
#define Sd_HasCapabilityRecordUsedOfInstance()                                                      (TRUE != FALSE)
#define Sd_HasClientEndIdxOfInstance()                                                              (TRUE != FALSE)
#define Sd_HasClientStartIdxOfInstance()                                                            (TRUE != FALSE)
#define Sd_HasClientUsedOfInstance()                                                                (TRUE != FALSE)
#define Sd_HasEMalformedMsgIdOfInstance()                                                           (TRUE != FALSE)
#define Sd_HasENackRecvIdOfInstance()                                                               (TRUE != FALSE)
#define Sd_HasEOutOfResIdOfInstance()                                                               (TRUE != FALSE)
#define Sd_HasEndpointStorageEndIdxOfInstance()                                                     (TRUE != FALSE)
#define Sd_HasEndpointStorageStartIdxOfInstance()                                                   (TRUE != FALSE)
#define Sd_HasMulticastRxPduIdOfInstance()                                                          (TRUE != FALSE)
#define Sd_HasMulticastRxSoConIdOfInstance()                                                        (TRUE != FALSE)
#define Sd_HasQueueProcessLimitOfInstance()                                                         (TRUE != FALSE)
#define Sd_HasRetryDelayOfInstance()                                                                (TRUE != FALSE)
#define Sd_HasRetryMaxOfInstance()                                                                  (TRUE != FALSE)
#define Sd_HasRxEventEndIdxOfInstance()                                                             (TRUE != FALSE)
#define Sd_HasRxEventStartIdxOfInstance()                                                           (TRUE != FALSE)
#define Sd_HasRxEventUsedOfInstance()                                                               (TRUE != FALSE)
#define Sd_HasSendEntryEndIdxOfInstance()                                                           (TRUE != FALSE)
#define Sd_HasSendEntryStartIdxOfInstance()                                                         (TRUE != FALSE)
#define Sd_HasServerEndIdxOfInstance()                                                              (TRUE != FALSE)
#define Sd_HasServerStartIdxOfInstance()                                                            (TRUE != FALSE)
#define Sd_HasServerUsedOfInstance()                                                                (TRUE != FALSE)
#define Sd_HasTcpSoConIdEndIdxOfInstance()                                                          (TRUE != FALSE)
#define Sd_HasTcpSoConIdStartIdxOfInstance()                                                        (TRUE != FALSE)
#define Sd_HasTcpSoConIdUsedOfInstance()                                                            (TRUE != FALSE)
#define Sd_HasTxPduIdOfInstance()                                                                   (TRUE != FALSE)
#define Sd_HasTxSoConIdOfInstance()                                                                 (TRUE != FALSE)
#define Sd_HasUdpSoConEndIdxOfInstance()                                                            (TRUE != FALSE)
#define Sd_HasUdpSoConStartIdxOfInstance()                                                          (TRUE != FALSE)
#define Sd_HasUdpSoConUsedOfInstance()                                                              (TRUE != FALSE)
#define Sd_HasUnicastRxPduIdOfInstance()                                                            (TRUE != FALSE)
#define Sd_HasUnicastRxSoConIdOfInstance()                                                          (TRUE != FALSE)
#define Sd_HasInstanceDyn()                                                                         (Sd_GetInstanceDynOfPCConfig() != NULL_PTR)
#define Sd_HasNextStateMachineRunOfInstanceDyn()                                                    (TRUE != FALSE)
#define Sd_HasRunModeOfInstanceDyn()                                                                (TRUE != FALSE)
#define Sd_HasRxEventEndIdxOfInstanceDyn()                                                          (TRUE != FALSE)
#define Sd_HasRxEventListFullOfInstanceDyn()                                                        (TRUE != FALSE)
#define Sd_HasRxEventStartIdxOfInstanceDyn()                                                        (TRUE != FALSE)
#define Sd_HasSendEntryEndIdxOfInstanceDyn()                                                        (TRUE != FALSE)
#define Sd_HasSendEntryNrPendingIdxOfInstanceDyn()                                                  (TRUE != FALSE)
#define Sd_HasSendEntryStartIdxOfInstanceDyn()                                                      (TRUE != FALSE)
#define Sd_HasStateOfInstanceDyn()                                                                  (TRUE != FALSE)
#define Sd_HasIpAddrRequest()                                                                       (Sd_GetIpAddrRequestOfPCConfig() != NULL_PTR)
#define Sd_HasPortSetIdxOfIpAddrRequest()                                                           (TRUE != FALSE)
#define Sd_HasRequestCntIdxOfIpAddrRequest()                                                        (TRUE != FALSE)
#define Sd_HasSoConIdOfIpAddrRequest()                                                              (TRUE != FALSE)
#define Sd_HasStaticIpConfigurationOfIpAddrRequest()                                                (TRUE != FALSE)
#define Sd_HasStaticPortConfigurationOfIpAddrRequest()                                              (TRUE != FALSE)
#define Sd_HasMaxNrOptionsPerEntry()                                                                (TRUE != FALSE)
#define Sd_HasMethod()                                                                              (Sd_GetMethodOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroupActRefIdxOfMethod()                                                       (TRUE != FALSE)
#define Sd_HasRoutingGroupActRefUsedOfMethod()                                                      (TRUE != FALSE)
#define Sd_HasTcpConfiguredOfMethod()                                                               (TRUE != FALSE)
#define Sd_HasUdpConfiguredOfMethod()                                                               (TRUE != FALSE)
#define Sd_HasMulticastEndpointAddr()                                                               (Sd_GetMulticastEndpointAddrOfPCConfig() != NULL_PTR)
#define Sd_HasMulticastSoConId()                                                                    (Sd_GetMulticastSoConIdOfPCConfig() != NULL_PTR)
#define Sd_HasNrOfOptions()                                                                         (Sd_GetNrOfOptionsOfPCConfig() != NULL_PTR)
#define Sd_HasOptionIndex()                                                                         (Sd_GetOptionIndexOfPCConfig() != NULL_PTR)
#define Sd_HasPayload()                                                                             (Sd_GetPayloadOfPCConfig() != NULL_PTR)
#define Sd_HasPortSet()                                                                             (Sd_GetPortSetOfPCConfig() != NULL_PTR)
#define Sd_HasRequestCnt()                                                                          (Sd_GetRequestCntOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroup()                                                                        (Sd_GetRoutingGroupOfPCConfig() != NULL_PTR)
#define Sd_HasRoutingGroupDyn()                                                                     (Sd_GetRoutingGroupDynOfPCConfig() != NULL_PTR)
#define Sd_HasStatusOfRoutingGroupDyn()                                                             (TRUE != FALSE)
#define Sd_HasRxEvent()                                                                             (Sd_GetRxEventOfPCConfig() != NULL_PTR)
#define Sd_HasClientListIdxOfRxEvent()                                                              (TRUE != FALSE)
#define Sd_HasEventHandlerIdxOfRxEvent()                                                            (TRUE != FALSE)
#define Sd_HasEventOfRxEvent()                                                                      (TRUE != FALSE)
#define Sd_HasSendEntry()                                                                           (Sd_GetSendEntryOfPCConfig() != NULL_PTR)
#define Sd_HasAddressStorageIdxOfSendEntry()                                                        (TRUE != FALSE)
#define Sd_HasClientIdxOfSendEntry()                                                                (TRUE != FALSE)
#define Sd_HasClientListIdxOfSendEntry()                                                            (TRUE != FALSE)
#define Sd_HasConsumedEventgroupIdxOfSendEntry()                                                    (TRUE != FALSE)
#define Sd_HasEntryTypeOfSendEntry()                                                                (TRUE != FALSE)
#define Sd_HasEventHandlerIdOfSendEntry()                                                           (TRUE != FALSE)
#define Sd_HasEventHandlerIdxOfSendEntry()                                                          (TRUE != FALSE)
#define Sd_HasInstanceIdOfSendEntry()                                                               (TRUE != FALSE)
#define Sd_HasInstanceIdxOfSendEntry()                                                              (TRUE != FALSE)
#define Sd_HasMajorVersionOfSendEntry()                                                             (TRUE != FALSE)
#define Sd_HasReservedFieldOfSendEntry()                                                            (TRUE != FALSE)
#define Sd_HasSendEntryNextIdxOfSendEntry()                                                         (TRUE != FALSE)
#define Sd_HasServerIdxOfSendEntry()                                                                (TRUE != FALSE)
#define Sd_HasServiceIdOfSendEntry()                                                                (TRUE != FALSE)
#define Sd_HasTimeToSendOfSendEntry()                                                               (TRUE != FALSE)
#define Sd_HasValidOfSendEntry()                                                                    (TRUE != FALSE)
#define Sd_HasServer()                                                                              (Sd_GetServerOfPCConfig() != NULL_PTR)
#define Sd_HasAutoAvailableOfServer()                                                               (TRUE != FALSE)
#define Sd_HasCapabilityRecordEndIdxOfServer()                                                      (TRUE != FALSE)
#define Sd_HasCapabilityRecordFunctionCalloutPtrIdxOfServer()                                       (TRUE != FALSE)
#define Sd_HasCapabilityRecordFunctionCalloutPtrUsedOfServer()                                      (TRUE != FALSE)
#define Sd_HasCapabilityRecordStartIdxOfServer()                                                    (TRUE != FALSE)
#define Sd_HasCapabilityRecordUsedOfServer()                                                        (TRUE != FALSE)
#define Sd_HasCommonInitialDelayIdxOfServer()                                                       (TRUE != FALSE)
#define Sd_HasCommonInitialDelayUsedOfServer()                                                      (TRUE != FALSE)
#define Sd_HasEventHandlerEndIdxOfServer()                                                          (TRUE != FALSE)
#define Sd_HasEventHandlerStartIdxOfServer()                                                        (TRUE != FALSE)
#define Sd_HasEventHandlerUsedOfServer()                                                            (TRUE != FALSE)
#define Sd_HasHandleIdOfServer()                                                                    (TRUE != FALSE)
#define Sd_HasInstanceIdOfServer()                                                                  (TRUE != FALSE)
#define Sd_HasInstanceIdxOfServer()                                                                 (TRUE != FALSE)
#define Sd_HasMajorVersionOfServer()                                                                (TRUE != FALSE)
#define Sd_HasMethodIdxOfServer()                                                                   (TRUE != FALSE)
#define Sd_HasMethodUsedOfServer()                                                                  (TRUE != FALSE)
#define Sd_HasMinorVersionOfServer()                                                                (TRUE != FALSE)
#define Sd_HasServerTimerIdxOfServer()                                                              (TRUE != FALSE)
#define Sd_HasServiceGroupMemberOfServer()                                                          (TRUE != FALSE)
#define Sd_HasServiceIdOfServer()                                                                   (TRUE != FALSE)
#define Sd_HasTcpSoConIdEndIdxOfServer()                                                            (TRUE != FALSE)
#define Sd_HasTcpSoConIdStartIdxOfServer()                                                          (TRUE != FALSE)
#define Sd_HasTcpSoConIdUsedOfServer()                                                              (TRUE != FALSE)
#define Sd_HasUdpSoConEndIdxOfServer()                                                              (TRUE != FALSE)
#define Sd_HasUdpSoConStartIdxOfServer()                                                            (TRUE != FALSE)
#define Sd_HasUdpSoConUsedOfServer()                                                                (TRUE != FALSE)
#define Sd_HasServerDyn()                                                                           (Sd_GetServerDynOfPCConfig() != NULL_PTR)
#define Sd_HasInitialOfferRepetitionRunOfServerDyn()                                                (TRUE != FALSE)
#define Sd_HasServiceGroupReqCounterOfServerDyn()                                                   (TRUE != FALSE)
#define Sd_HasStateMachineExecutionRequestedOfServerDyn()                                           (TRUE != FALSE)
#define Sd_HasStateMachineOfServerDyn()                                                             (TRUE != FALSE)
#define Sd_HasStateSwcOfServerDyn()                                                                 (TRUE != FALSE)
#define Sd_HasTimeToTriggerSendOfServerDyn()                                                        (TRUE != FALSE)
#define Sd_HasServerMap()                                                                           (Sd_GetServerMapOfPCConfig() != NULL_PTR)
#define Sd_HasInvalidHndOfServerMap()                                                               (TRUE != FALSE)
#define Sd_HasServerIdxOfServerMap()                                                                (TRUE != FALSE)
#define Sd_HasServerUsedOfServerMap()                                                               (TRUE != FALSE)
#define Sd_HasServerTimer()                                                                         (Sd_GetServerTimerOfPCConfig() != NULL_PTR)
#define Sd_HasInitialOfferDelayMaxOfServerTimer()                                                   (TRUE != FALSE)
#define Sd_HasInitialOfferDelayMinOfServerTimer()                                                   (TRUE != FALSE)
#define Sd_HasInitialOfferRepetitionBaseDelayOfServerTimer()                                        (TRUE != FALSE)
#define Sd_HasInitialOfferRepetitionsMaxOfServerTimer()                                             (TRUE != FALSE)
#define Sd_HasOfferCyclicDelayOfServerTimer()                                                       (TRUE != FALSE)
#define Sd_HasRequestResponseMaxDelayOfServerTimer()                                                (TRUE != FALSE)
#define Sd_HasRequestResponseMinDelayOfServerTimer()                                                (TRUE != FALSE)
#define Sd_HasTTLOfServerTimer()                                                                    (TRUE != FALSE)
#define Sd_HasServiceGroup()                                                                        (Sd_GetServiceGroupOfPCConfig() != NULL_PTR)
#define Sd_HasServiceGroupMemberEndIdxOfServiceGroup()                                              (TRUE != FALSE)
#define Sd_HasServiceGroupMemberStartIdxOfServiceGroup()                                            (TRUE != FALSE)
#define Sd_HasServiceGroupMap()                                                                     (Sd_GetServiceGroupMapOfPCConfig() != NULL_PTR)
#define Sd_HasInvalidHndOfServiceGroupMap()                                                         (TRUE != FALSE)
#define Sd_HasServiceGroupIdxOfServiceGroupMap()                                                    (TRUE != FALSE)
#define Sd_HasServiceGroupUsedOfServiceGroupMap()                                                   (TRUE != FALSE)
#define Sd_HasServiceGroupMember()                                                                  (Sd_GetServiceGroupMemberOfPCConfig() != NULL_PTR)
#define Sd_HasClientIdxOfServiceGroupMember()                                                       (TRUE != FALSE)
#define Sd_HasClientUsedOfServiceGroupMember()                                                      (TRUE != FALSE)
#define Sd_HasServerIdxOfServiceGroupMember()                                                       (TRUE != FALSE)
#define Sd_HasServerUsedOfServiceGroupMember()                                                      (TRUE != FALSE)
#define Sd_HasSizeOfAddressStorage()                                                                (TRUE != FALSE)
#define Sd_HasSizeOfCapabilityRecord()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfCapabilityRecordFunctionCalloutPtr()                                            (TRUE != FALSE)
#define Sd_HasSizeOfClient()                                                                        (TRUE != FALSE)
#define Sd_HasSizeOfClientDyn()                                                                     (TRUE != FALSE)
#define Sd_HasSizeOfClientList()                                                                    (TRUE != FALSE)
#define Sd_HasSizeOfClientMap()                                                                     (TRUE != FALSE)
#define Sd_HasSizeOfClientTimer()                                                                   (TRUE != FALSE)
#define Sd_HasSizeOfCommonInitialDelay()                                                            (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroup()                                                            (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroupDyn()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroupMap()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfEndpointStorage()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfEventHandler()                                                                  (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerDyn()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerMulticast()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerTcp()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerUdp()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfInstance()                                                                      (TRUE != FALSE)
#define Sd_HasSizeOfInstanceDyn()                                                                   (TRUE != FALSE)
#define Sd_HasSizeOfIpAddrRequest()                                                                 (TRUE != FALSE)
#define Sd_HasSizeOfMethod()                                                                        (TRUE != FALSE)
#define Sd_HasSizeOfMulticastEndpointAddr()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfMulticastSoConId()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfOptionIndex()                                                                   (TRUE != FALSE)
#define Sd_HasSizeOfPayload()                                                                       (TRUE != FALSE)
#define Sd_HasSizeOfPortSet()                                                                       (TRUE != FALSE)
#define Sd_HasSizeOfRequestCnt()                                                                    (TRUE != FALSE)
#define Sd_HasSizeOfRoutingGroup()                                                                  (TRUE != FALSE)
#define Sd_HasSizeOfRoutingGroupDyn()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfRxEvent()                                                                       (TRUE != FALSE)
#define Sd_HasSizeOfSendEntry()                                                                     (TRUE != FALSE)
#define Sd_HasSizeOfServer()                                                                        (TRUE != FALSE)
#define Sd_HasSizeOfServerDyn()                                                                     (TRUE != FALSE)
#define Sd_HasSizeOfServerMap()                                                                     (TRUE != FALSE)
#define Sd_HasSizeOfServerTimer()                                                                   (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroup()                                                                  (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroupMap()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroupMember()                                                            (TRUE != FALSE)
#define Sd_HasSizeOfSoConActivationMap()                                                            (TRUE != FALSE)
#define Sd_HasSizeOfTcpSoConId()                                                                    (TRUE != FALSE)
#define Sd_HasSizeOfTcpSoConModeMap()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfTriggerTransmit()                                                               (TRUE != FALSE)
#define Sd_HasSizeOfUdpSoCon()                                                                      (TRUE != FALSE)
#define Sd_HasSoConActivationMap()                                                                  (Sd_GetSoConActivationMapOfPCConfig() != NULL_PTR)
#define Sd_HasNrOfActivationsOfSoConActivationMap()                                                 (TRUE != FALSE)
#define Sd_HasSoConIdOfSoConActivationMap()                                                         (TRUE != FALSE)
#define Sd_HasTcpSoConId()                                                                          (Sd_GetTcpSoConIdOfPCConfig() != NULL_PTR)
#define Sd_HasTcpSoConModeMap()                                                                     (Sd_GetTcpSoConModeMapOfPCConfig() != NULL_PTR)
#define Sd_HasTriggerTransmit()                                                                     (Sd_GetTriggerTransmitOfPCConfig() != NULL_PTR)
#define Sd_HasClientListIdxOfTriggerTransmit()                                                      (TRUE != FALSE)
#define Sd_HasEventHandlerIdxOfTriggerTransmit()                                                    (TRUE != FALSE)
#define Sd_HasStateOfTriggerTransmit()                                                              (TRUE != FALSE)
#define Sd_HasTriggerTransmitEndIdx()                                                               (Sd_GetTriggerTransmitEndIdxOfPCConfig() != NULL_PTR)
#define Sd_HasTriggerTransmitFull()                                                                 (Sd_GetTriggerTransmitFullOfPCConfig() != NULL_PTR)
#define Sd_HasTriggerTransmitStartIdx()                                                             (Sd_GetTriggerTransmitStartIdxOfPCConfig() != NULL_PTR)
#define Sd_HasUdpSoCon()                                                                            (Sd_GetUdpSoConOfPCConfig() != NULL_PTR)
#define Sd_HasIdOfUdpSoCon()                                                                        (TRUE != FALSE)
#define Sd_HasPreconfiguredOfUdpSoCon()                                                             (TRUE != FALSE)
#define Sd_HasPCConfig()                                                                            (TRUE != FALSE)
#define Sd_HasAddressStorageOfPCConfig()                                                            (TRUE != FALSE)
#define Sd_HasCapabilityRecordFunctionCalloutPtrOfPCConfig()                                        (TRUE != FALSE)
#define Sd_HasCapabilityRecordOfPCConfig()                                                          (TRUE != FALSE)
#define Sd_HasClientDynOfPCConfig()                                                                 (TRUE != FALSE)
#define Sd_HasClientListOfPCConfig()                                                                (TRUE != FALSE)
#define Sd_HasClientMapOfPCConfig()                                                                 (TRUE != FALSE)
#define Sd_HasClientOfPCConfig()                                                                    (TRUE != FALSE)
#define Sd_HasClientTimerOfPCConfig()                                                               (TRUE != FALSE)
#define Sd_HasCommonInitialDelayOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasConsumedEventgroupDynOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasConsumedEventgroupMapOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasConsumedEventgroupOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasEndpointStorageOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasEventHandlerDynOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasEventHandlerMulticastOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasEventHandlerOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasEventHandlerTcpOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasEventHandlerUdpOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasInstanceDynOfPCConfig()                                                               (TRUE != FALSE)
#define Sd_HasInstanceOfPCConfig()                                                                  (TRUE != FALSE)
#define Sd_HasIpAddrRequestOfPCConfig()                                                             (TRUE != FALSE)
#define Sd_HasMaxNrOptionsPerEntryOfPCConfig()                                                      (TRUE != FALSE)
#define Sd_HasMethodOfPCConfig()                                                                    (TRUE != FALSE)
#define Sd_HasMulticastEndpointAddrOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasMulticastSoConIdOfPCConfig()                                                          (TRUE != FALSE)
#define Sd_HasNrOfOptionsOfPCConfig()                                                               (TRUE != FALSE)
#define Sd_HasOptionIndexOfPCConfig()                                                               (TRUE != FALSE)
#define Sd_HasPayloadOfPCConfig()                                                                   (TRUE != FALSE)
#define Sd_HasPortSetOfPCConfig()                                                                   (TRUE != FALSE)
#define Sd_HasRequestCntOfPCConfig()                                                                (TRUE != FALSE)
#define Sd_HasRoutingGroupDynOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasRoutingGroupOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasRxEventOfPCConfig()                                                                   (TRUE != FALSE)
#define Sd_HasSendEntryOfPCConfig()                                                                 (TRUE != FALSE)
#define Sd_HasServerDynOfPCConfig()                                                                 (TRUE != FALSE)
#define Sd_HasServerMapOfPCConfig()                                                                 (TRUE != FALSE)
#define Sd_HasServerOfPCConfig()                                                                    (TRUE != FALSE)
#define Sd_HasServerTimerOfPCConfig()                                                               (TRUE != FALSE)
#define Sd_HasServiceGroupMapOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasServiceGroupMemberOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasServiceGroupOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfAddressStorageOfPCConfig()                                                      (TRUE != FALSE)
#define Sd_HasSizeOfCapabilityRecordFunctionCalloutPtrOfPCConfig()                                  (TRUE != FALSE)
#define Sd_HasSizeOfCapabilityRecordOfPCConfig()                                                    (TRUE != FALSE)
#define Sd_HasSizeOfClientDynOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasSizeOfClientListOfPCConfig()                                                          (TRUE != FALSE)
#define Sd_HasSizeOfClientMapOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasSizeOfClientOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfClientTimerOfPCConfig()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfCommonInitialDelayOfPCConfig()                                                  (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroupDynOfPCConfig()                                               (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroupMapOfPCConfig()                                               (TRUE != FALSE)
#define Sd_HasSizeOfConsumedEventgroupOfPCConfig()                                                  (TRUE != FALSE)
#define Sd_HasSizeOfEndpointStorageOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerDynOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerMulticastOfPCConfig()                                               (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerTcpOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfEventHandlerUdpOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfInstanceDynOfPCConfig()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfInstanceOfPCConfig()                                                            (TRUE != FALSE)
#define Sd_HasSizeOfIpAddrRequestOfPCConfig()                                                       (TRUE != FALSE)
#define Sd_HasSizeOfMethodOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfMulticastEndpointAddrOfPCConfig()                                               (TRUE != FALSE)
#define Sd_HasSizeOfMulticastSoConIdOfPCConfig()                                                    (TRUE != FALSE)
#define Sd_HasSizeOfOptionIndexOfPCConfig()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfPayloadOfPCConfig()                                                             (TRUE != FALSE)
#define Sd_HasSizeOfPortSetOfPCConfig()                                                             (TRUE != FALSE)
#define Sd_HasSizeOfRequestCntOfPCConfig()                                                          (TRUE != FALSE)
#define Sd_HasSizeOfRoutingGroupDynOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfRoutingGroupOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasSizeOfRxEventOfPCConfig()                                                             (TRUE != FALSE)
#define Sd_HasSizeOfSendEntryOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasSizeOfServerDynOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasSizeOfServerMapOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasSizeOfServerOfPCConfig()                                                              (TRUE != FALSE)
#define Sd_HasSizeOfServerTimerOfPCConfig()                                                         (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroupMapOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroupMemberOfPCConfig()                                                  (TRUE != FALSE)
#define Sd_HasSizeOfServiceGroupOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasSizeOfSoConActivationMapOfPCConfig()                                                  (TRUE != FALSE)
#define Sd_HasSizeOfTcpSoConIdOfPCConfig()                                                          (TRUE != FALSE)
#define Sd_HasSizeOfTcpSoConModeMapOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfTriggerTransmitOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasSizeOfUdpSoConOfPCConfig()                                                            (TRUE != FALSE)
#define Sd_HasSoConActivationMapOfPCConfig()                                                        (TRUE != FALSE)
#define Sd_HasTcpSoConIdOfPCConfig()                                                                (TRUE != FALSE)
#define Sd_HasTcpSoConModeMapOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasTriggerTransmitEndIdxOfPCConfig()                                                     (TRUE != FALSE)
#define Sd_HasTriggerTransmitFullOfPCConfig()                                                       (TRUE != FALSE)
#define Sd_HasTriggerTransmitOfPCConfig()                                                           (TRUE != FALSE)
#define Sd_HasTriggerTransmitStartIdxOfPCConfig()                                                   (TRUE != FALSE)
#define Sd_HasUdpSoConOfPCConfig()                                                                  (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  SdPCIncrementDataMacros  Sd Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define Sd_IncFlagsOfAddressStorage(Index)                                                          Sd_GetFlagsOfAddressStorage(Index)++
#define Sd_IncRxMulticastFlagsOfAddressStorage(Index)                                               Sd_GetRxMulticastFlagsOfAddressStorage(Index)++
#define Sd_IncRxMulticastSessionIdOfAddressStorage(Index)                                           Sd_GetRxMulticastSessionIdOfAddressStorage(Index)++
#define Sd_IncRxUnicastFlagsOfAddressStorage(Index)                                                 Sd_GetRxUnicastFlagsOfAddressStorage(Index)++
#define Sd_IncRxUnicastSessionIdOfAddressStorage(Index)                                             Sd_GetRxUnicastSessionIdOfAddressStorage(Index)++
#define Sd_IncSendEntryNrPendingIdxOfAddressStorage(Index)                                          Sd_GetSendEntryNrPendingIdxOfAddressStorage(Index)++
#define Sd_IncSessionIdCounterOfAddressStorage(Index)                                               Sd_GetSessionIdCounterOfAddressStorage(Index)++
#define Sd_IncAddressStorageServerIdxOfClientDyn(Index)                                             Sd_GetAddressStorageServerIdxOfClientDyn(Index)++
#define Sd_IncOfferedTTLOfClientDyn(Index)                                                          Sd_GetOfferedTTLOfClientDyn(Index)++
#define Sd_IncRepetitionRunOfClientDyn(Index)                                                       Sd_GetRepetitionRunOfClientDyn(Index)++
#define Sd_IncRetryCounterOfClientDyn(Index)                                                        Sd_GetRetryCounterOfClientDyn(Index)++
#define Sd_IncServiceGroupReqCounterOfClientDyn(Index)                                              Sd_GetServiceGroupReqCounterOfClientDyn(Index)++
#define Sd_IncAddressStorageIdxOfClientList(Index)                                                  Sd_GetAddressStorageIdxOfClientList(Index)++
#define Sd_IncEndpointStorageTcpIdxOfClientList(Index)                                              Sd_GetEndpointStorageTcpIdxOfClientList(Index)++
#define Sd_IncEndpointStorageUdpIdxOfClientList(Index)                                              Sd_GetEndpointStorageUdpIdxOfClientList(Index)++
#define Sd_IncNrOfReferencesOfClientList(Index)                                                     Sd_GetNrOfReferencesOfClientList(Index)++
#define Sd_IncRequestedTTLOfClientList(Index)                                                       Sd_GetRequestedTTLOfClientList(Index)++
#define Sd_IncRxReservedOfClientList(Index)                                                         Sd_GetRxReservedOfClientList(Index)++
#define Sd_IncCommonInitialDelay(Index)                                                             Sd_GetCommonInitialDelay(Index)++
#define Sd_IncAcknowledgedTTLOfConsumedEventgroupDyn(Index)                                         Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(Index)++
#define Sd_IncRxIndicationCountOfConsumedEventgroupDyn(Index)                                       Sd_GetRxIndicationCountOfConsumedEventgroupDyn(Index)++
#define Sd_IncNrOfReferencesOfEndpointStorage(Index)                                                Sd_GetNrOfReferencesOfEndpointStorage(Index)++
#define Sd_IncNrOfClientsOfEventHandlerDyn(Index)                                                   Sd_GetNrOfClientsOfEventHandlerDyn(Index)++
#define Sd_IncRxEventEndIdxOfInstanceDyn(Index)                                                     Sd_GetRxEventEndIdxOfInstanceDyn(Index)++
#define Sd_IncRxEventStartIdxOfInstanceDyn(Index)                                                   Sd_GetRxEventStartIdxOfInstanceDyn(Index)++
#define Sd_IncSendEntryEndIdxOfInstanceDyn(Index)                                                   Sd_GetSendEntryEndIdxOfInstanceDyn(Index)++
#define Sd_IncSendEntryNrPendingIdxOfInstanceDyn(Index)                                             Sd_GetSendEntryNrPendingIdxOfInstanceDyn(Index)++
#define Sd_IncSendEntryStartIdxOfInstanceDyn(Index)                                                 Sd_GetSendEntryStartIdxOfInstanceDyn(Index)++
#define Sd_IncNrOfOptions()                                                                         Sd_GetNrOfOptions()++
#define Sd_IncOptionIndex(Index)                                                                    Sd_GetOptionIndex(Index)++
#define Sd_IncPayload(Index)                                                                        Sd_GetPayload(Index)++
#define Sd_IncRequestCnt(Index)                                                                     Sd_GetRequestCnt(Index)++
#define Sd_IncClientListIdxOfRxEvent(Index)                                                         Sd_GetClientListIdxOfRxEvent(Index)++
#define Sd_IncEventHandlerIdxOfRxEvent(Index)                                                       Sd_GetEventHandlerIdxOfRxEvent(Index)++
#define Sd_IncAddressStorageIdxOfSendEntry(Index)                                                   Sd_GetAddressStorageIdxOfSendEntry(Index)++
#define Sd_IncClientIdxOfSendEntry(Index)                                                           Sd_GetClientIdxOfSendEntry(Index)++
#define Sd_IncClientListIdxOfSendEntry(Index)                                                       Sd_GetClientListIdxOfSendEntry(Index)++
#define Sd_IncConsumedEventgroupIdxOfSendEntry(Index)                                               Sd_GetConsumedEventgroupIdxOfSendEntry(Index)++
#define Sd_IncEventHandlerIdOfSendEntry(Index)                                                      Sd_GetEventHandlerIdOfSendEntry(Index)++
#define Sd_IncEventHandlerIdxOfSendEntry(Index)                                                     Sd_GetEventHandlerIdxOfSendEntry(Index)++
#define Sd_IncInstanceIdOfSendEntry(Index)                                                          Sd_GetInstanceIdOfSendEntry(Index)++
#define Sd_IncInstanceIdxOfSendEntry(Index)                                                         Sd_GetInstanceIdxOfSendEntry(Index)++
#define Sd_IncMajorVersionOfSendEntry(Index)                                                        Sd_GetMajorVersionOfSendEntry(Index)++
#define Sd_IncReservedFieldOfSendEntry(Index)                                                       Sd_GetReservedFieldOfSendEntry(Index)++
#define Sd_IncSendEntryNextIdxOfSendEntry(Index)                                                    Sd_GetSendEntryNextIdxOfSendEntry(Index)++
#define Sd_IncServerIdxOfSendEntry(Index)                                                           Sd_GetServerIdxOfSendEntry(Index)++
#define Sd_IncServiceIdOfSendEntry(Index)                                                           Sd_GetServiceIdOfSendEntry(Index)++
#define Sd_IncInitialOfferRepetitionRunOfServerDyn(Index)                                           Sd_GetInitialOfferRepetitionRunOfServerDyn(Index)++
#define Sd_IncServiceGroupReqCounterOfServerDyn(Index)                                              Sd_GetServiceGroupReqCounterOfServerDyn(Index)++
#define Sd_IncNrOfActivationsOfSoConActivationMap(Index)                                            Sd_GetNrOfActivationsOfSoConActivationMap(Index)++
#define Sd_IncClientListIdxOfTriggerTransmit(Index)                                                 Sd_GetClientListIdxOfTriggerTransmit(Index)++
#define Sd_IncEventHandlerIdxOfTriggerTransmit(Index)                                               Sd_GetEventHandlerIdxOfTriggerTransmit(Index)++
#define Sd_IncTriggerTransmitEndIdx()                                                               Sd_GetTriggerTransmitEndIdx()++
#define Sd_IncTriggerTransmitStartIdx()                                                             Sd_GetTriggerTransmitStartIdx()++
/** 
  \}
*/ 

/** 
  \defgroup  SdPCDecrementDataMacros  Sd Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define Sd_DecFlagsOfAddressStorage(Index)                                                          Sd_GetFlagsOfAddressStorage(Index)--
#define Sd_DecRxMulticastFlagsOfAddressStorage(Index)                                               Sd_GetRxMulticastFlagsOfAddressStorage(Index)--
#define Sd_DecRxMulticastSessionIdOfAddressStorage(Index)                                           Sd_GetRxMulticastSessionIdOfAddressStorage(Index)--
#define Sd_DecRxUnicastFlagsOfAddressStorage(Index)                                                 Sd_GetRxUnicastFlagsOfAddressStorage(Index)--
#define Sd_DecRxUnicastSessionIdOfAddressStorage(Index)                                             Sd_GetRxUnicastSessionIdOfAddressStorage(Index)--
#define Sd_DecSendEntryNrPendingIdxOfAddressStorage(Index)                                          Sd_GetSendEntryNrPendingIdxOfAddressStorage(Index)--
#define Sd_DecSessionIdCounterOfAddressStorage(Index)                                               Sd_GetSessionIdCounterOfAddressStorage(Index)--
#define Sd_DecAddressStorageServerIdxOfClientDyn(Index)                                             Sd_GetAddressStorageServerIdxOfClientDyn(Index)--
#define Sd_DecOfferedTTLOfClientDyn(Index)                                                          Sd_GetOfferedTTLOfClientDyn(Index)--
#define Sd_DecRepetitionRunOfClientDyn(Index)                                                       Sd_GetRepetitionRunOfClientDyn(Index)--
#define Sd_DecRetryCounterOfClientDyn(Index)                                                        Sd_GetRetryCounterOfClientDyn(Index)--
#define Sd_DecServiceGroupReqCounterOfClientDyn(Index)                                              Sd_GetServiceGroupReqCounterOfClientDyn(Index)--
#define Sd_DecAddressStorageIdxOfClientList(Index)                                                  Sd_GetAddressStorageIdxOfClientList(Index)--
#define Sd_DecEndpointStorageTcpIdxOfClientList(Index)                                              Sd_GetEndpointStorageTcpIdxOfClientList(Index)--
#define Sd_DecEndpointStorageUdpIdxOfClientList(Index)                                              Sd_GetEndpointStorageUdpIdxOfClientList(Index)--
#define Sd_DecNrOfReferencesOfClientList(Index)                                                     Sd_GetNrOfReferencesOfClientList(Index)--
#define Sd_DecRequestedTTLOfClientList(Index)                                                       Sd_GetRequestedTTLOfClientList(Index)--
#define Sd_DecRxReservedOfClientList(Index)                                                         Sd_GetRxReservedOfClientList(Index)--
#define Sd_DecCommonInitialDelay(Index)                                                             Sd_GetCommonInitialDelay(Index)--
#define Sd_DecAcknowledgedTTLOfConsumedEventgroupDyn(Index)                                         Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(Index)--
#define Sd_DecRxIndicationCountOfConsumedEventgroupDyn(Index)                                       Sd_GetRxIndicationCountOfConsumedEventgroupDyn(Index)--
#define Sd_DecNrOfReferencesOfEndpointStorage(Index)                                                Sd_GetNrOfReferencesOfEndpointStorage(Index)--
#define Sd_DecNrOfClientsOfEventHandlerDyn(Index)                                                   Sd_GetNrOfClientsOfEventHandlerDyn(Index)--
#define Sd_DecRxEventEndIdxOfInstanceDyn(Index)                                                     Sd_GetRxEventEndIdxOfInstanceDyn(Index)--
#define Sd_DecRxEventStartIdxOfInstanceDyn(Index)                                                   Sd_GetRxEventStartIdxOfInstanceDyn(Index)--
#define Sd_DecSendEntryEndIdxOfInstanceDyn(Index)                                                   Sd_GetSendEntryEndIdxOfInstanceDyn(Index)--
#define Sd_DecSendEntryNrPendingIdxOfInstanceDyn(Index)                                             Sd_GetSendEntryNrPendingIdxOfInstanceDyn(Index)--
#define Sd_DecSendEntryStartIdxOfInstanceDyn(Index)                                                 Sd_GetSendEntryStartIdxOfInstanceDyn(Index)--
#define Sd_DecNrOfOptions()                                                                         Sd_GetNrOfOptions()--
#define Sd_DecOptionIndex(Index)                                                                    Sd_GetOptionIndex(Index)--
#define Sd_DecPayload(Index)                                                                        Sd_GetPayload(Index)--
#define Sd_DecRequestCnt(Index)                                                                     Sd_GetRequestCnt(Index)--
#define Sd_DecClientListIdxOfRxEvent(Index)                                                         Sd_GetClientListIdxOfRxEvent(Index)--
#define Sd_DecEventHandlerIdxOfRxEvent(Index)                                                       Sd_GetEventHandlerIdxOfRxEvent(Index)--
#define Sd_DecAddressStorageIdxOfSendEntry(Index)                                                   Sd_GetAddressStorageIdxOfSendEntry(Index)--
#define Sd_DecClientIdxOfSendEntry(Index)                                                           Sd_GetClientIdxOfSendEntry(Index)--
#define Sd_DecClientListIdxOfSendEntry(Index)                                                       Sd_GetClientListIdxOfSendEntry(Index)--
#define Sd_DecConsumedEventgroupIdxOfSendEntry(Index)                                               Sd_GetConsumedEventgroupIdxOfSendEntry(Index)--
#define Sd_DecEventHandlerIdOfSendEntry(Index)                                                      Sd_GetEventHandlerIdOfSendEntry(Index)--
#define Sd_DecEventHandlerIdxOfSendEntry(Index)                                                     Sd_GetEventHandlerIdxOfSendEntry(Index)--
#define Sd_DecInstanceIdOfSendEntry(Index)                                                          Sd_GetInstanceIdOfSendEntry(Index)--
#define Sd_DecInstanceIdxOfSendEntry(Index)                                                         Sd_GetInstanceIdxOfSendEntry(Index)--
#define Sd_DecMajorVersionOfSendEntry(Index)                                                        Sd_GetMajorVersionOfSendEntry(Index)--
#define Sd_DecReservedFieldOfSendEntry(Index)                                                       Sd_GetReservedFieldOfSendEntry(Index)--
#define Sd_DecSendEntryNextIdxOfSendEntry(Index)                                                    Sd_GetSendEntryNextIdxOfSendEntry(Index)--
#define Sd_DecServerIdxOfSendEntry(Index)                                                           Sd_GetServerIdxOfSendEntry(Index)--
#define Sd_DecServiceIdOfSendEntry(Index)                                                           Sd_GetServiceIdOfSendEntry(Index)--
#define Sd_DecInitialOfferRepetitionRunOfServerDyn(Index)                                           Sd_GetInitialOfferRepetitionRunOfServerDyn(Index)--
#define Sd_DecServiceGroupReqCounterOfServerDyn(Index)                                              Sd_GetServiceGroupReqCounterOfServerDyn(Index)--
#define Sd_DecNrOfActivationsOfSoConActivationMap(Index)                                            Sd_GetNrOfActivationsOfSoConActivationMap(Index)--
#define Sd_DecClientListIdxOfTriggerTransmit(Index)                                                 Sd_GetClientListIdxOfTriggerTransmit(Index)--
#define Sd_DecEventHandlerIdxOfTriggerTransmit(Index)                                               Sd_GetEventHandlerIdxOfTriggerTransmit(Index)--
#define Sd_DecTriggerTransmitEndIdx()                                                               Sd_GetTriggerTransmitEndIdx()--
#define Sd_DecTriggerTransmitStartIdx()                                                             Sd_GetTriggerTransmitStartIdx()--
/** 
  \}
*/ 

/** 
  \defgroup  SdPCAddDataMacros  Sd Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/ 
#define Sd_AddFlagsOfAddressStorage(Index, Value)                                                   Sd_SetFlagsOfAddressStorage(Index, (Sd_GetFlagsOfAddressStorage(Index) + Value))
#define Sd_AddRxMulticastFlagsOfAddressStorage(Index, Value)                                        Sd_SetRxMulticastFlagsOfAddressStorage(Index, (Sd_GetRxMulticastFlagsOfAddressStorage(Index) + Value))
#define Sd_AddRxMulticastSessionIdOfAddressStorage(Index, Value)                                    Sd_SetRxMulticastSessionIdOfAddressStorage(Index, (Sd_GetRxMulticastSessionIdOfAddressStorage(Index) + Value))
#define Sd_AddRxUnicastFlagsOfAddressStorage(Index, Value)                                          Sd_SetRxUnicastFlagsOfAddressStorage(Index, (Sd_GetRxUnicastFlagsOfAddressStorage(Index) + Value))
#define Sd_AddRxUnicastSessionIdOfAddressStorage(Index, Value)                                      Sd_SetRxUnicastSessionIdOfAddressStorage(Index, (Sd_GetRxUnicastSessionIdOfAddressStorage(Index) + Value))
#define Sd_AddSendEntryNrPendingIdxOfAddressStorage(Index, Value)                                   Sd_SetSendEntryNrPendingIdxOfAddressStorage(Index, (Sd_GetSendEntryNrPendingIdxOfAddressStorage(Index) + Value))
#define Sd_AddSessionIdCounterOfAddressStorage(Index, Value)                                        Sd_SetSessionIdCounterOfAddressStorage(Index, (Sd_GetSessionIdCounterOfAddressStorage(Index) + Value))
#define Sd_AddAddressStorageServerIdxOfClientDyn(Index, Value)                                      Sd_SetAddressStorageServerIdxOfClientDyn(Index, (Sd_GetAddressStorageServerIdxOfClientDyn(Index) + Value))
#define Sd_AddOfferedTTLOfClientDyn(Index, Value)                                                   Sd_SetOfferedTTLOfClientDyn(Index, (Sd_GetOfferedTTLOfClientDyn(Index) + Value))
#define Sd_AddRepetitionRunOfClientDyn(Index, Value)                                                Sd_SetRepetitionRunOfClientDyn(Index, (Sd_GetRepetitionRunOfClientDyn(Index) + Value))
#define Sd_AddRetryCounterOfClientDyn(Index, Value)                                                 Sd_SetRetryCounterOfClientDyn(Index, (Sd_GetRetryCounterOfClientDyn(Index) + Value))
#define Sd_AddServiceGroupReqCounterOfClientDyn(Index, Value)                                       Sd_SetServiceGroupReqCounterOfClientDyn(Index, (Sd_GetServiceGroupReqCounterOfClientDyn(Index) + Value))
#define Sd_AddAddressStorageIdxOfClientList(Index, Value)                                           Sd_SetAddressStorageIdxOfClientList(Index, (Sd_GetAddressStorageIdxOfClientList(Index) + Value))
#define Sd_AddEndpointStorageTcpIdxOfClientList(Index, Value)                                       Sd_SetEndpointStorageTcpIdxOfClientList(Index, (Sd_GetEndpointStorageTcpIdxOfClientList(Index) + Value))
#define Sd_AddEndpointStorageUdpIdxOfClientList(Index, Value)                                       Sd_SetEndpointStorageUdpIdxOfClientList(Index, (Sd_GetEndpointStorageUdpIdxOfClientList(Index) + Value))
#define Sd_AddNrOfReferencesOfClientList(Index, Value)                                              Sd_SetNrOfReferencesOfClientList(Index, (Sd_GetNrOfReferencesOfClientList(Index) + Value))
#define Sd_AddRequestedTTLOfClientList(Index, Value)                                                Sd_SetRequestedTTLOfClientList(Index, (Sd_GetRequestedTTLOfClientList(Index) + Value))
#define Sd_AddRxReservedOfClientList(Index, Value)                                                  Sd_SetRxReservedOfClientList(Index, (Sd_GetRxReservedOfClientList(Index) + Value))
#define Sd_AddCommonInitialDelay(Index, Value)                                                      Sd_SetCommonInitialDelay(Index, (Sd_GetCommonInitialDelay(Index) + Value))
#define Sd_AddAcknowledgedTTLOfConsumedEventgroupDyn(Index, Value)                                  Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(Index, (Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(Index) + Value))
#define Sd_AddRxIndicationCountOfConsumedEventgroupDyn(Index, Value)                                Sd_SetRxIndicationCountOfConsumedEventgroupDyn(Index, (Sd_GetRxIndicationCountOfConsumedEventgroupDyn(Index) + Value))
#define Sd_AddNrOfReferencesOfEndpointStorage(Index, Value)                                         Sd_SetNrOfReferencesOfEndpointStorage(Index, (Sd_GetNrOfReferencesOfEndpointStorage(Index) + Value))
#define Sd_AddNrOfClientsOfEventHandlerDyn(Index, Value)                                            Sd_SetNrOfClientsOfEventHandlerDyn(Index, (Sd_GetNrOfClientsOfEventHandlerDyn(Index) + Value))
#define Sd_AddRxEventEndIdxOfInstanceDyn(Index, Value)                                              Sd_SetRxEventEndIdxOfInstanceDyn(Index, (Sd_GetRxEventEndIdxOfInstanceDyn(Index) + Value))
#define Sd_AddRxEventStartIdxOfInstanceDyn(Index, Value)                                            Sd_SetRxEventStartIdxOfInstanceDyn(Index, (Sd_GetRxEventStartIdxOfInstanceDyn(Index) + Value))
#define Sd_AddSendEntryEndIdxOfInstanceDyn(Index, Value)                                            Sd_SetSendEntryEndIdxOfInstanceDyn(Index, (Sd_GetSendEntryEndIdxOfInstanceDyn(Index) + Value))
#define Sd_AddSendEntryNrPendingIdxOfInstanceDyn(Index, Value)                                      Sd_SetSendEntryNrPendingIdxOfInstanceDyn(Index, (Sd_GetSendEntryNrPendingIdxOfInstanceDyn(Index) + Value))
#define Sd_AddSendEntryStartIdxOfInstanceDyn(Index, Value)                                          Sd_SetSendEntryStartIdxOfInstanceDyn(Index, (Sd_GetSendEntryStartIdxOfInstanceDyn(Index) + Value))
#define Sd_AddNrOfOptions(Value)                                                                    Sd_SetNrOfOptions((Sd_GetNrOfOptions() + Value))
#define Sd_AddOptionIndex(Index, Value)                                                             Sd_SetOptionIndex(Index, (Sd_GetOptionIndex(Index) + Value))
#define Sd_AddPayload(Index, Value)                                                                 Sd_SetPayload(Index, (Sd_GetPayload(Index) + Value))
#define Sd_AddRequestCnt(Index, Value)                                                              Sd_SetRequestCnt(Index, (Sd_GetRequestCnt(Index) + Value))
#define Sd_AddClientListIdxOfRxEvent(Index, Value)                                                  Sd_SetClientListIdxOfRxEvent(Index, (Sd_GetClientListIdxOfRxEvent(Index) + Value))
#define Sd_AddEventHandlerIdxOfRxEvent(Index, Value)                                                Sd_SetEventHandlerIdxOfRxEvent(Index, (Sd_GetEventHandlerIdxOfRxEvent(Index) + Value))
#define Sd_AddAddressStorageIdxOfSendEntry(Index, Value)                                            Sd_SetAddressStorageIdxOfSendEntry(Index, (Sd_GetAddressStorageIdxOfSendEntry(Index) + Value))
#define Sd_AddClientIdxOfSendEntry(Index, Value)                                                    Sd_SetClientIdxOfSendEntry(Index, (Sd_GetClientIdxOfSendEntry(Index) + Value))
#define Sd_AddClientListIdxOfSendEntry(Index, Value)                                                Sd_SetClientListIdxOfSendEntry(Index, (Sd_GetClientListIdxOfSendEntry(Index) + Value))
#define Sd_AddConsumedEventgroupIdxOfSendEntry(Index, Value)                                        Sd_SetConsumedEventgroupIdxOfSendEntry(Index, (Sd_GetConsumedEventgroupIdxOfSendEntry(Index) + Value))
#define Sd_AddEventHandlerIdOfSendEntry(Index, Value)                                               Sd_SetEventHandlerIdOfSendEntry(Index, (Sd_GetEventHandlerIdOfSendEntry(Index) + Value))
#define Sd_AddEventHandlerIdxOfSendEntry(Index, Value)                                              Sd_SetEventHandlerIdxOfSendEntry(Index, (Sd_GetEventHandlerIdxOfSendEntry(Index) + Value))
#define Sd_AddInstanceIdOfSendEntry(Index, Value)                                                   Sd_SetInstanceIdOfSendEntry(Index, (Sd_GetInstanceIdOfSendEntry(Index) + Value))
#define Sd_AddInstanceIdxOfSendEntry(Index, Value)                                                  Sd_SetInstanceIdxOfSendEntry(Index, (Sd_GetInstanceIdxOfSendEntry(Index) + Value))
#define Sd_AddMajorVersionOfSendEntry(Index, Value)                                                 Sd_SetMajorVersionOfSendEntry(Index, (Sd_GetMajorVersionOfSendEntry(Index) + Value))
#define Sd_AddReservedFieldOfSendEntry(Index, Value)                                                Sd_SetReservedFieldOfSendEntry(Index, (Sd_GetReservedFieldOfSendEntry(Index) + Value))
#define Sd_AddSendEntryNextIdxOfSendEntry(Index, Value)                                             Sd_SetSendEntryNextIdxOfSendEntry(Index, (Sd_GetSendEntryNextIdxOfSendEntry(Index) + Value))
#define Sd_AddServerIdxOfSendEntry(Index, Value)                                                    Sd_SetServerIdxOfSendEntry(Index, (Sd_GetServerIdxOfSendEntry(Index) + Value))
#define Sd_AddServiceIdOfSendEntry(Index, Value)                                                    Sd_SetServiceIdOfSendEntry(Index, (Sd_GetServiceIdOfSendEntry(Index) + Value))
#define Sd_AddInitialOfferRepetitionRunOfServerDyn(Index, Value)                                    Sd_SetInitialOfferRepetitionRunOfServerDyn(Index, (Sd_GetInitialOfferRepetitionRunOfServerDyn(Index) + Value))
#define Sd_AddServiceGroupReqCounterOfServerDyn(Index, Value)                                       Sd_SetServiceGroupReqCounterOfServerDyn(Index, (Sd_GetServiceGroupReqCounterOfServerDyn(Index) + Value))
#define Sd_AddNrOfActivationsOfSoConActivationMap(Index, Value)                                     Sd_SetNrOfActivationsOfSoConActivationMap(Index, (Sd_GetNrOfActivationsOfSoConActivationMap(Index) + Value))
#define Sd_AddClientListIdxOfTriggerTransmit(Index, Value)                                          Sd_SetClientListIdxOfTriggerTransmit(Index, (Sd_GetClientListIdxOfTriggerTransmit(Index) + Value))
#define Sd_AddEventHandlerIdxOfTriggerTransmit(Index, Value)                                        Sd_SetEventHandlerIdxOfTriggerTransmit(Index, (Sd_GetEventHandlerIdxOfTriggerTransmit(Index) + Value))
#define Sd_AddTriggerTransmitEndIdx(Value)                                                          Sd_SetTriggerTransmitEndIdx((Sd_GetTriggerTransmitEndIdx() + Value))
#define Sd_AddTriggerTransmitStartIdx(Value)                                                        Sd_SetTriggerTransmitStartIdx((Sd_GetTriggerTransmitStartIdx() + Value))
/** 
  \}
*/ 

/** 
  \defgroup  SdPCSubstractDataMacros  Sd Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/ 
#define Sd_SubFlagsOfAddressStorage(Index, Value)                                                   Sd_SetFlagsOfAddressStorage(Index, (Sd_GetFlagsOfAddressStorage(Index) - Value))
#define Sd_SubRxMulticastFlagsOfAddressStorage(Index, Value)                                        Sd_SetRxMulticastFlagsOfAddressStorage(Index, (Sd_GetRxMulticastFlagsOfAddressStorage(Index) - Value))
#define Sd_SubRxMulticastSessionIdOfAddressStorage(Index, Value)                                    Sd_SetRxMulticastSessionIdOfAddressStorage(Index, (Sd_GetRxMulticastSessionIdOfAddressStorage(Index) - Value))
#define Sd_SubRxUnicastFlagsOfAddressStorage(Index, Value)                                          Sd_SetRxUnicastFlagsOfAddressStorage(Index, (Sd_GetRxUnicastFlagsOfAddressStorage(Index) - Value))
#define Sd_SubRxUnicastSessionIdOfAddressStorage(Index, Value)                                      Sd_SetRxUnicastSessionIdOfAddressStorage(Index, (Sd_GetRxUnicastSessionIdOfAddressStorage(Index) - Value))
#define Sd_SubSendEntryNrPendingIdxOfAddressStorage(Index, Value)                                   Sd_SetSendEntryNrPendingIdxOfAddressStorage(Index, (Sd_GetSendEntryNrPendingIdxOfAddressStorage(Index) - Value))
#define Sd_SubSessionIdCounterOfAddressStorage(Index, Value)                                        Sd_SetSessionIdCounterOfAddressStorage(Index, (Sd_GetSessionIdCounterOfAddressStorage(Index) - Value))
#define Sd_SubAddressStorageServerIdxOfClientDyn(Index, Value)                                      Sd_SetAddressStorageServerIdxOfClientDyn(Index, (Sd_GetAddressStorageServerIdxOfClientDyn(Index) - Value))
#define Sd_SubOfferedTTLOfClientDyn(Index, Value)                                                   Sd_SetOfferedTTLOfClientDyn(Index, (Sd_GetOfferedTTLOfClientDyn(Index) - Value))
#define Sd_SubRepetitionRunOfClientDyn(Index, Value)                                                Sd_SetRepetitionRunOfClientDyn(Index, (Sd_GetRepetitionRunOfClientDyn(Index) - Value))
#define Sd_SubRetryCounterOfClientDyn(Index, Value)                                                 Sd_SetRetryCounterOfClientDyn(Index, (Sd_GetRetryCounterOfClientDyn(Index) - Value))
#define Sd_SubServiceGroupReqCounterOfClientDyn(Index, Value)                                       Sd_SetServiceGroupReqCounterOfClientDyn(Index, (Sd_GetServiceGroupReqCounterOfClientDyn(Index) - Value))
#define Sd_SubAddressStorageIdxOfClientList(Index, Value)                                           Sd_SetAddressStorageIdxOfClientList(Index, (Sd_GetAddressStorageIdxOfClientList(Index) - Value))
#define Sd_SubEndpointStorageTcpIdxOfClientList(Index, Value)                                       Sd_SetEndpointStorageTcpIdxOfClientList(Index, (Sd_GetEndpointStorageTcpIdxOfClientList(Index) - Value))
#define Sd_SubEndpointStorageUdpIdxOfClientList(Index, Value)                                       Sd_SetEndpointStorageUdpIdxOfClientList(Index, (Sd_GetEndpointStorageUdpIdxOfClientList(Index) - Value))
#define Sd_SubNrOfReferencesOfClientList(Index, Value)                                              Sd_SetNrOfReferencesOfClientList(Index, (Sd_GetNrOfReferencesOfClientList(Index) - Value))
#define Sd_SubRequestedTTLOfClientList(Index, Value)                                                Sd_SetRequestedTTLOfClientList(Index, (Sd_GetRequestedTTLOfClientList(Index) - Value))
#define Sd_SubRxReservedOfClientList(Index, Value)                                                  Sd_SetRxReservedOfClientList(Index, (Sd_GetRxReservedOfClientList(Index) - Value))
#define Sd_SubCommonInitialDelay(Index, Value)                                                      Sd_SetCommonInitialDelay(Index, (Sd_GetCommonInitialDelay(Index) - Value))
#define Sd_SubAcknowledgedTTLOfConsumedEventgroupDyn(Index, Value)                                  Sd_SetAcknowledgedTTLOfConsumedEventgroupDyn(Index, (Sd_GetAcknowledgedTTLOfConsumedEventgroupDyn(Index) - Value))
#define Sd_SubRxIndicationCountOfConsumedEventgroupDyn(Index, Value)                                Sd_SetRxIndicationCountOfConsumedEventgroupDyn(Index, (Sd_GetRxIndicationCountOfConsumedEventgroupDyn(Index) - Value))
#define Sd_SubNrOfReferencesOfEndpointStorage(Index, Value)                                         Sd_SetNrOfReferencesOfEndpointStorage(Index, (Sd_GetNrOfReferencesOfEndpointStorage(Index) - Value))
#define Sd_SubNrOfClientsOfEventHandlerDyn(Index, Value)                                            Sd_SetNrOfClientsOfEventHandlerDyn(Index, (Sd_GetNrOfClientsOfEventHandlerDyn(Index) - Value))
#define Sd_SubRxEventEndIdxOfInstanceDyn(Index, Value)                                              Sd_SetRxEventEndIdxOfInstanceDyn(Index, (Sd_GetRxEventEndIdxOfInstanceDyn(Index) - Value))
#define Sd_SubRxEventStartIdxOfInstanceDyn(Index, Value)                                            Sd_SetRxEventStartIdxOfInstanceDyn(Index, (Sd_GetRxEventStartIdxOfInstanceDyn(Index) - Value))
#define Sd_SubSendEntryEndIdxOfInstanceDyn(Index, Value)                                            Sd_SetSendEntryEndIdxOfInstanceDyn(Index, (Sd_GetSendEntryEndIdxOfInstanceDyn(Index) - Value))
#define Sd_SubSendEntryNrPendingIdxOfInstanceDyn(Index, Value)                                      Sd_SetSendEntryNrPendingIdxOfInstanceDyn(Index, (Sd_GetSendEntryNrPendingIdxOfInstanceDyn(Index) - Value))
#define Sd_SubSendEntryStartIdxOfInstanceDyn(Index, Value)                                          Sd_SetSendEntryStartIdxOfInstanceDyn(Index, (Sd_GetSendEntryStartIdxOfInstanceDyn(Index) - Value))
#define Sd_SubNrOfOptions(Value)                                                                    Sd_SetNrOfOptions((Sd_GetNrOfOptions() - Value))
#define Sd_SubOptionIndex(Index, Value)                                                             Sd_SetOptionIndex(Index, (Sd_GetOptionIndex(Index) - Value))
#define Sd_SubPayload(Index, Value)                                                                 Sd_SetPayload(Index, (Sd_GetPayload(Index) - Value))
#define Sd_SubRequestCnt(Index, Value)                                                              Sd_SetRequestCnt(Index, (Sd_GetRequestCnt(Index) - Value))
#define Sd_SubClientListIdxOfRxEvent(Index, Value)                                                  Sd_SetClientListIdxOfRxEvent(Index, (Sd_GetClientListIdxOfRxEvent(Index) - Value))
#define Sd_SubEventHandlerIdxOfRxEvent(Index, Value)                                                Sd_SetEventHandlerIdxOfRxEvent(Index, (Sd_GetEventHandlerIdxOfRxEvent(Index) - Value))
#define Sd_SubAddressStorageIdxOfSendEntry(Index, Value)                                            Sd_SetAddressStorageIdxOfSendEntry(Index, (Sd_GetAddressStorageIdxOfSendEntry(Index) - Value))
#define Sd_SubClientIdxOfSendEntry(Index, Value)                                                    Sd_SetClientIdxOfSendEntry(Index, (Sd_GetClientIdxOfSendEntry(Index) - Value))
#define Sd_SubClientListIdxOfSendEntry(Index, Value)                                                Sd_SetClientListIdxOfSendEntry(Index, (Sd_GetClientListIdxOfSendEntry(Index) - Value))
#define Sd_SubConsumedEventgroupIdxOfSendEntry(Index, Value)                                        Sd_SetConsumedEventgroupIdxOfSendEntry(Index, (Sd_GetConsumedEventgroupIdxOfSendEntry(Index) - Value))
#define Sd_SubEventHandlerIdOfSendEntry(Index, Value)                                               Sd_SetEventHandlerIdOfSendEntry(Index, (Sd_GetEventHandlerIdOfSendEntry(Index) - Value))
#define Sd_SubEventHandlerIdxOfSendEntry(Index, Value)                                              Sd_SetEventHandlerIdxOfSendEntry(Index, (Sd_GetEventHandlerIdxOfSendEntry(Index) - Value))
#define Sd_SubInstanceIdOfSendEntry(Index, Value)                                                   Sd_SetInstanceIdOfSendEntry(Index, (Sd_GetInstanceIdOfSendEntry(Index) - Value))
#define Sd_SubInstanceIdxOfSendEntry(Index, Value)                                                  Sd_SetInstanceIdxOfSendEntry(Index, (Sd_GetInstanceIdxOfSendEntry(Index) - Value))
#define Sd_SubMajorVersionOfSendEntry(Index, Value)                                                 Sd_SetMajorVersionOfSendEntry(Index, (Sd_GetMajorVersionOfSendEntry(Index) - Value))
#define Sd_SubReservedFieldOfSendEntry(Index, Value)                                                Sd_SetReservedFieldOfSendEntry(Index, (Sd_GetReservedFieldOfSendEntry(Index) - Value))
#define Sd_SubSendEntryNextIdxOfSendEntry(Index, Value)                                             Sd_SetSendEntryNextIdxOfSendEntry(Index, (Sd_GetSendEntryNextIdxOfSendEntry(Index) - Value))
#define Sd_SubServerIdxOfSendEntry(Index, Value)                                                    Sd_SetServerIdxOfSendEntry(Index, (Sd_GetServerIdxOfSendEntry(Index) - Value))
#define Sd_SubServiceIdOfSendEntry(Index, Value)                                                    Sd_SetServiceIdOfSendEntry(Index, (Sd_GetServiceIdOfSendEntry(Index) - Value))
#define Sd_SubInitialOfferRepetitionRunOfServerDyn(Index, Value)                                    Sd_SetInitialOfferRepetitionRunOfServerDyn(Index, (Sd_GetInitialOfferRepetitionRunOfServerDyn(Index) - Value))
#define Sd_SubServiceGroupReqCounterOfServerDyn(Index, Value)                                       Sd_SetServiceGroupReqCounterOfServerDyn(Index, (Sd_GetServiceGroupReqCounterOfServerDyn(Index) - Value))
#define Sd_SubNrOfActivationsOfSoConActivationMap(Index, Value)                                     Sd_SetNrOfActivationsOfSoConActivationMap(Index, (Sd_GetNrOfActivationsOfSoConActivationMap(Index) - Value))
#define Sd_SubClientListIdxOfTriggerTransmit(Index, Value)                                          Sd_SetClientListIdxOfTriggerTransmit(Index, (Sd_GetClientListIdxOfTriggerTransmit(Index) - Value))
#define Sd_SubEventHandlerIdxOfTriggerTransmit(Index, Value)                                        Sd_SetEventHandlerIdxOfTriggerTransmit(Index, (Sd_GetEventHandlerIdxOfTriggerTransmit(Index) - Value))
#define Sd_SubTriggerTransmitEndIdx(Value)                                                          Sd_SetTriggerTransmitEndIdx((Sd_GetTriggerTransmitEndIdx() - Value))
#define Sd_SubTriggerTransmitStartIdx(Value)                                                        Sd_SetTriggerTransmitStartIdx((Sd_GetTriggerTransmitStartIdx() - Value))
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


#if(!defined(SD_SIZEOFADDRESSSTORAGE))
typedef uint8 Sd_SizeOfAddressStorageType;
#endif
#if(!defined(SD_SIZEOFCAPABILITYRECORD))
typedef uint8 Sd_SizeOfCapabilityRecordType;
#endif
#if(!defined(SD_SIZEOFCLIENTLIST))
typedef uint8 Sd_SizeOfClientListType;
# define Sd_GetSizeOfClientList() 0u
#endif
#if(!defined(SD_SIZEOFCLIENT))
typedef uint8 Sd_SizeOfClientType;
# define Sd_GetSizeOfClient() 0u
#endif
#if(!defined(SD_SIZEOFCONSUMEDEVENTGROUP))
typedef uint8 Sd_SizeOfConsumedEventgroupType;
# define Sd_GetSizeOfConsumedEventgroup() 0u
#endif
#if(!defined(SD_SIZEOFENDPOINTSTORAGE))
typedef uint8 Sd_SizeOfEndpointStorageType;
#endif
#if(!defined(SD_SIZEOFEVENTHANDLER))
typedef uint8 Sd_SizeOfEventHandlerType;
# define Sd_GetSizeOfEventHandler() 0u
#endif
#if(!defined(SD_SIZEOFINSTANCE))
typedef uint8 Sd_SizeOfInstanceType;
#endif
#if(!defined(SD_SIZEOFMULTICASTSOCONID))
typedef uint8 Sd_SizeOfMulticastSoConIdType;
#endif
#if(!defined(SD_SIZEOFPAYLOAD))
typedef uint8 Sd_SizeOfPayloadType;
#endif
#if(!defined(SD_SIZEOFRXEVENT))
typedef uint8 Sd_SizeOfRxEventType;
#endif
#if(!defined(SD_SIZEOFSENDENTRY))
typedef uint8 Sd_SizeOfSendEntryType;
#endif
#if(!defined(SD_SIZEOFSERVERTIMER))
typedef uint8 Sd_SizeOfServerTimerType;
#endif
#if(!defined(SD_SIZEOFSERVER))
typedef uint8 Sd_SizeOfServerType;
# define Sd_GetSizeOfServer() 0u
#endif
#if(SD_SOCONACTIVATIONMAP == STD_OFF)
typedef uint8 Sd_SizeOfSoConActivationMapType;
#endif
#if(!defined(SD_SIZEOFTRIGGERTRANSMIT))
typedef uint8 Sd_SizeOfTriggerTransmitType;
#endif

/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
#if !defined (SD_LOCAL_INLINE)
# define SD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  SdPCIterableTypes  Sd Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Sd_AddressStorage */
typedef uint8_least Sd_AddressStorageIterType;

/**   \brief  type used to iterate Sd_CapabilityRecord */
typedef uint8_least Sd_CapabilityRecordIterType;

/**   \brief  type used to iterate Sd_CapabilityRecordFunctionCalloutPtr */
typedef uint8_least Sd_CapabilityRecordFunctionCalloutPtrIterType;

/**   \brief  type used to iterate Sd_Client */
typedef uint8_least Sd_ClientIterType;

/**   \brief  type used to iterate Sd_ClientList */
typedef uint8_least Sd_ClientListIterType;

/**   \brief  type used to iterate Sd_ClientMap */
typedef uint8_least Sd_ClientMapIterType;

/**   \brief  type used to iterate Sd_ClientTimer */
typedef uint8_least Sd_ClientTimerIterType;

/**   \brief  type used to iterate Sd_CommonInitialDelay */
typedef uint8_least Sd_CommonInitialDelayIterType;

/**   \brief  type used to iterate Sd_ConsumedEventgroup */
typedef uint8_least Sd_ConsumedEventgroupIterType;

/**   \brief  type used to iterate Sd_ConsumedEventgroupMap */
typedef uint8_least Sd_ConsumedEventgroupMapIterType;

/**   \brief  type used to iterate Sd_EndpointStorage */
typedef uint8_least Sd_EndpointStorageIterType;

/**   \brief  type used to iterate Sd_EventHandler */
typedef uint8_least Sd_EventHandlerIterType;

/**   \brief  type used to iterate Sd_EventHandlerMulticast */
typedef uint8_least Sd_EventHandlerMulticastIterType;

/**   \brief  type used to iterate Sd_EventHandlerTcp */
typedef uint8_least Sd_EventHandlerTcpIterType;

/**   \brief  type used to iterate Sd_EventHandlerUdp */
typedef uint8_least Sd_EventHandlerUdpIterType;

/**   \brief  type used to iterate Sd_Instance */
typedef uint8_least Sd_InstanceIterType;

/**   \brief  type used to iterate Sd_IpAddrRequest */
typedef uint8_least Sd_IpAddrRequestIterType;

/**   \brief  type used to iterate Sd_Method */
typedef uint8_least Sd_MethodIterType;

/**   \brief  type used to iterate Sd_MulticastEndpointAddr */
typedef uint8_least Sd_MulticastEndpointAddrIterType;

/**   \brief  type used to iterate Sd_MulticastSoConId */
typedef uint8_least Sd_MulticastSoConIdIterType;

/**   \brief  type used to iterate Sd_OptionIndex */
typedef uint8_least Sd_OptionIndexIterType;

/**   \brief  type used to iterate Sd_Payload */
typedef uint16_least Sd_PayloadIterType;

/**   \brief  type used to iterate Sd_PortSet */
typedef uint8_least Sd_PortSetIterType;

/**   \brief  type used to iterate Sd_RequestCnt */
typedef uint8_least Sd_RequestCntIterType;

/**   \brief  type used to iterate Sd_RoutingGroup */
typedef uint8_least Sd_RoutingGroupIterType;

/**   \brief  type used to iterate Sd_RxEvent */
typedef uint8_least Sd_RxEventIterType;

/**   \brief  type used to iterate Sd_SendEntry */
typedef uint8_least Sd_SendEntryIterType;

/**   \brief  type used to iterate Sd_Server */
typedef uint8_least Sd_ServerIterType;

/**   \brief  type used to iterate Sd_ServerMap */
typedef uint8_least Sd_ServerMapIterType;

/**   \brief  type used to iterate Sd_ServerTimer */
typedef uint8_least Sd_ServerTimerIterType;

/**   \brief  type used to iterate Sd_ServiceGroup */
typedef uint8_least Sd_ServiceGroupIterType;

/**   \brief  type used to iterate Sd_ServiceGroupMap */
typedef uint8_least Sd_ServiceGroupMapIterType;

/**   \brief  type used to iterate Sd_ServiceGroupMember */
typedef uint8_least Sd_ServiceGroupMemberIterType;

/**   \brief  type used to iterate Sd_SoConActivationMap */
typedef uint8_least Sd_SoConActivationMapIterType;

/**   \brief  type used to iterate Sd_TcpSoConId */
typedef uint8_least Sd_TcpSoConIdIterType;

/**   \brief  type used to iterate Sd_TriggerTransmit */
typedef uint8_least Sd_TriggerTransmitIterType;

/**   \brief  type used to iterate Sd_UdpSoCon */
typedef uint8_least Sd_UdpSoConIterType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCIterableTypesWithSizeRelations  Sd Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Sd_ClientDyn */
typedef Sd_ClientIterType Sd_ClientDynIterType;

/**   \brief  type used to iterate Sd_ConsumedEventgroupDyn */
typedef Sd_ConsumedEventgroupIterType Sd_ConsumedEventgroupDynIterType;

/**   \brief  type used to iterate Sd_EventHandlerDyn */
typedef Sd_EventHandlerIterType Sd_EventHandlerDynIterType;

/**   \brief  type used to iterate Sd_InstanceDyn */
typedef Sd_InstanceIterType Sd_InstanceDynIterType;

/**   \brief  type used to iterate Sd_RoutingGroupDyn */
typedef Sd_RoutingGroupIterType Sd_RoutingGroupDynIterType;

/**   \brief  type used to iterate Sd_ServerDyn */
typedef Sd_ServerIterType Sd_ServerDynIterType;

/**   \brief  type used to iterate Sd_TcpSoConModeMap */
typedef Sd_TcpSoConIdIterType Sd_TcpSoConModeMapIterType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCValueTypes  Sd Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Sd_FlagsOfAddressStorage */
typedef uint8 Sd_FlagsOfAddressStorageType;

/**   \brief  value based type definition for Sd_RxMulticastFlagsOfAddressStorage */
typedef uint8 Sd_RxMulticastFlagsOfAddressStorageType;

/**   \brief  value based type definition for Sd_RxMulticastSessionIdOfAddressStorage */
typedef uint16 Sd_RxMulticastSessionIdOfAddressStorageType;

/**   \brief  value based type definition for Sd_RxUnicastFlagsOfAddressStorage */
typedef uint8 Sd_RxUnicastFlagsOfAddressStorageType;

/**   \brief  value based type definition for Sd_RxUnicastSessionIdOfAddressStorage */
typedef uint16 Sd_RxUnicastSessionIdOfAddressStorageType;

/**   \brief  value based type definition for Sd_SendEntryNrPendingIdxOfAddressStorage */
typedef uint8 Sd_SendEntryNrPendingIdxOfAddressStorageType;

/**   \brief  value based type definition for Sd_SessionIdCounterOfAddressStorage */
typedef uint16 Sd_SessionIdCounterOfAddressStorageType;

/**   \brief  value based type definition for Sd_CapabilityRecord */
typedef uint8 Sd_CapabilityRecordType;

/**   \brief  value based type definition for Sd_AutoRequireOfClient */
typedef boolean Sd_AutoRequireOfClientType;

/**   \brief  value based type definition for Sd_CapabilityRecordEndIdxOfClient */
typedef uint8 Sd_CapabilityRecordEndIdxOfClientType;

/**   \brief  value based type definition for Sd_CapabilityRecordFunctionCalloutPtrIdxOfClient */
typedef uint8 Sd_CapabilityRecordFunctionCalloutPtrIdxOfClientType;

/**   \brief  value based type definition for Sd_CapabilityRecordFunctionCalloutPtrUsedOfClient */
typedef boolean Sd_CapabilityRecordFunctionCalloutPtrUsedOfClientType;

/**   \brief  value based type definition for Sd_CapabilityRecordStartIdxOfClient */
typedef uint8 Sd_CapabilityRecordStartIdxOfClientType;

/**   \brief  value based type definition for Sd_CapabilityRecordUsedOfClient */
typedef boolean Sd_CapabilityRecordUsedOfClientType;

/**   \brief  value based type definition for Sd_ClientTimerIdxOfClient */
typedef uint8 Sd_ClientTimerIdxOfClientType;

/**   \brief  value based type definition for Sd_CommonInitialDelayIdxOfClient */
typedef uint8 Sd_CommonInitialDelayIdxOfClientType;

/**   \brief  value based type definition for Sd_CommonInitialDelayUsedOfClient */
typedef boolean Sd_CommonInitialDelayUsedOfClientType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupEndIdxOfClient */
typedef uint8 Sd_ConsumedEventgroupEndIdxOfClientType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupStartIdxOfClient */
typedef uint8 Sd_ConsumedEventgroupStartIdxOfClientType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupUsedOfClient */
typedef boolean Sd_ConsumedEventgroupUsedOfClientType;

/**   \brief  value based type definition for Sd_HandleIdOfClient */
typedef uint8 Sd_HandleIdOfClientType;

/**   \brief  value based type definition for Sd_InstanceIdOfClient */
typedef uint8 Sd_InstanceIdOfClientType;

/**   \brief  value based type definition for Sd_InstanceIdxOfClient */
typedef uint8 Sd_InstanceIdxOfClientType;

/**   \brief  value based type definition for Sd_MajorVersionOfClient */
typedef uint8 Sd_MajorVersionOfClientType;

/**   \brief  value based type definition for Sd_MethodIdxOfClient */
typedef uint8 Sd_MethodIdxOfClientType;

/**   \brief  value based type definition for Sd_MethodUsedOfClient */
typedef boolean Sd_MethodUsedOfClientType;

/**   \brief  value based type definition for Sd_MinorVersionOfClient */
typedef uint8 Sd_MinorVersionOfClientType;

/**   \brief  value based type definition for Sd_MinorVersionWildcardOfClient */
typedef boolean Sd_MinorVersionWildcardOfClientType;

/**   \brief  value based type definition for Sd_ServiceGroupMemberOfClient */
typedef boolean Sd_ServiceGroupMemberOfClientType;

/**   \brief  value based type definition for Sd_ServiceIdOfClient */
typedef uint16 Sd_ServiceIdOfClientType;

/**   \brief  value based type definition for Sd_TcpSoConIdEndIdxOfClient */
typedef uint8 Sd_TcpSoConIdEndIdxOfClientType;

/**   \brief  value based type definition for Sd_TcpSoConIdStartIdxOfClient */
typedef uint8 Sd_TcpSoConIdStartIdxOfClientType;

/**   \brief  value based type definition for Sd_TcpSoConIdUsedOfClient */
typedef boolean Sd_TcpSoConIdUsedOfClientType;

/**   \brief  value based type definition for Sd_UdpSoConEndIdxOfClient */
typedef uint8 Sd_UdpSoConEndIdxOfClientType;

/**   \brief  value based type definition for Sd_UdpSoConStartIdxOfClient */
typedef uint8 Sd_UdpSoConStartIdxOfClientType;

/**   \brief  value based type definition for Sd_UdpSoConUsedOfClient */
typedef boolean Sd_UdpSoConUsedOfClientType;

/**   \brief  value based type definition for Sd_AddressStorageServerIdxOfClientDyn */
typedef uint8 Sd_AddressStorageServerIdxOfClientDynType;

/**   \brief  value based type definition for Sd_OfferedTTLOfClientDyn */
typedef uint32 Sd_OfferedTTLOfClientDynType;

/**   \brief  value based type definition for Sd_RepetitionRunOfClientDyn */
typedef uint8 Sd_RepetitionRunOfClientDynType;

/**   \brief  value based type definition for Sd_RetryCounterOfClientDyn */
typedef uint8 Sd_RetryCounterOfClientDynType;

/**   \brief  value based type definition for Sd_ServiceGroupReqCounterOfClientDyn */
typedef uint8 Sd_ServiceGroupReqCounterOfClientDynType;

/**   \brief  value based type definition for Sd_StateMachineExecutionRequestedOfClientDyn */
typedef boolean Sd_StateMachineExecutionRequestedOfClientDynType;

/**   \brief  value based type definition for Sd_AddressStorageIdxOfClientList */
typedef uint8 Sd_AddressStorageIdxOfClientListType;

/**   \brief  value based type definition for Sd_EndpointStorageTcpIdxOfClientList */
typedef uint8 Sd_EndpointStorageTcpIdxOfClientListType;

/**   \brief  value based type definition for Sd_EndpointStorageUdpIdxOfClientList */
typedef uint8 Sd_EndpointStorageUdpIdxOfClientListType;

/**   \brief  value based type definition for Sd_NrOfReferencesOfClientList */
typedef uint8 Sd_NrOfReferencesOfClientListType;

/**   \brief  value based type definition for Sd_RequestedTTLOfClientList */
typedef uint32 Sd_RequestedTTLOfClientListType;

/**   \brief  value based type definition for Sd_RxReservedOfClientList */
typedef uint16 Sd_RxReservedOfClientListType;

/**   \brief  value based type definition for Sd_ClientIdxOfClientMap */
typedef uint8 Sd_ClientIdxOfClientMapType;

/**   \brief  value based type definition for Sd_ClientUsedOfClientMap */
typedef boolean Sd_ClientUsedOfClientMapType;

/**   \brief  value based type definition for Sd_InvalidHndOfClientMap */
typedef boolean Sd_InvalidHndOfClientMapType;

/**   \brief  value based type definition for Sd_InitialFindDelayMaxOfClientTimer */
typedef uint8 Sd_InitialFindDelayMaxOfClientTimerType;

/**   \brief  value based type definition for Sd_InitialFindDelayMinOfClientTimer */
typedef uint8 Sd_InitialFindDelayMinOfClientTimerType;

/**   \brief  value based type definition for Sd_InitialFindRepetitionBaseDelayOfClientTimer */
typedef uint8 Sd_InitialFindRepetitionBaseDelayOfClientTimerType;

/**   \brief  value based type definition for Sd_InitialFindRepetitionsMaxOfClientTimer */
typedef uint8 Sd_InitialFindRepetitionsMaxOfClientTimerType;

/**   \brief  value based type definition for Sd_RequestResponseMaxDelayOfClientTimer */
typedef uint8 Sd_RequestResponseMaxDelayOfClientTimerType;

/**   \brief  value based type definition for Sd_RequestResponseMinDelayOfClientTimer */
typedef uint8 Sd_RequestResponseMinDelayOfClientTimerType;

/**   \brief  value based type definition for Sd_TTLOfClientTimer */
typedef uint32 Sd_TTLOfClientTimerType;

/**   \brief  value based type definition for Sd_CommonInitialDelay */
typedef uint32 Sd_CommonInitialDelayType;

/**   \brief  value based type definition for Sd_AutoRequireOfConsumedEventgroup */
typedef boolean Sd_AutoRequireOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_ClientIdxOfConsumedEventgroup */
typedef uint8 Sd_ClientIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_ClientTimerIdxOfConsumedEventgroup */
typedef uint8 Sd_ClientTimerIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_EventGroupIdOfConsumedEventgroup */
typedef uint8 Sd_EventGroupIdOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_HandleIdOfConsumedEventgroup */
typedef uint8 Sd_HandleIdOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_MulticastEndpointAddrIdxOfConsumedEventgroup */
typedef uint8 Sd_MulticastEndpointAddrIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_MulticastEndpointAddrUsedOfConsumedEventgroup */
typedef boolean Sd_MulticastEndpointAddrUsedOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_MulticastSoConIdEndIdxOfConsumedEventgroup */
typedef uint8 Sd_MulticastSoConIdEndIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_MulticastSoConIdStartIdxOfConsumedEventgroup */
typedef uint8 Sd_MulticastSoConIdStartIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_MulticastSoConIdUsedOfConsumedEventgroup */
typedef boolean Sd_MulticastSoConIdUsedOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupMulticastActRefIdxOfConsumedEventgroup */
typedef uint8 Sd_RoutingGroupMulticastActRefIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupMulticastActRefUsedOfConsumedEventgroup */
typedef boolean Sd_RoutingGroupMulticastActRefUsedOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupTcpActRefIdxOfConsumedEventgroup */
typedef uint8 Sd_RoutingGroupTcpActRefIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupTcpActRefUsedOfConsumedEventgroup */
typedef boolean Sd_RoutingGroupTcpActRefUsedOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupUdpActRefIdxOfConsumedEventgroup */
typedef uint8 Sd_RoutingGroupUdpActRefIdxOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_RoutingGroupUdpActRefUsedOfConsumedEventgroup */
typedef boolean Sd_RoutingGroupUdpActRefUsedOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_AcknowledgedTTLOfConsumedEventgroupDyn */
typedef uint32 Sd_AcknowledgedTTLOfConsumedEventgroupDynType;

/**   \brief  value based type definition for Sd_RxIndicationCountOfConsumedEventgroupDyn */
typedef uint8 Sd_RxIndicationCountOfConsumedEventgroupDynType;

/**   \brief  value based type definition for Sd_SoConMarkedForClosureOfConsumedEventgroupDyn */
typedef boolean Sd_SoConMarkedForClosureOfConsumedEventgroupDynType;

/**   \brief  value based type definition for Sd_TriggerSubscriptionOfConsumedEventgroupDyn */
typedef boolean Sd_TriggerSubscriptionOfConsumedEventgroupDynType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupIdxOfConsumedEventgroupMap */
typedef uint8 Sd_ConsumedEventgroupIdxOfConsumedEventgroupMapType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupUsedOfConsumedEventgroupMap */
typedef boolean Sd_ConsumedEventgroupUsedOfConsumedEventgroupMapType;

/**   \brief  value based type definition for Sd_InvalidHndOfConsumedEventgroupMap */
typedef boolean Sd_InvalidHndOfConsumedEventgroupMapType;

/**   \brief  value based type definition for Sd_NrOfReferencesOfEndpointStorage */
typedef uint8 Sd_NrOfReferencesOfEndpointStorageType;

/**   \brief  value based type definition for Sd_ClientListEndIdxOfEventHandler */
typedef uint8 Sd_ClientListEndIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_ClientListStartIdxOfEventHandler */
typedef uint8 Sd_ClientListStartIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventGroupIdOfEventHandler */
typedef uint8 Sd_EventGroupIdOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerMulticastIdxOfEventHandler */
typedef uint8 Sd_EventHandlerMulticastIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerMulticastUsedOfEventHandler */
typedef boolean Sd_EventHandlerMulticastUsedOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerTcpIdxOfEventHandler */
typedef uint8 Sd_EventHandlerTcpIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerTcpUsedOfEventHandler */
typedef boolean Sd_EventHandlerTcpUsedOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerUdpIdxOfEventHandler */
typedef uint8 Sd_EventHandlerUdpIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_EventHandlerUdpUsedOfEventHandler */
typedef boolean Sd_EventHandlerUdpUsedOfEventHandlerType;

/**   \brief  value based type definition for Sd_HandleIdOfEventHandler */
typedef uint8 Sd_HandleIdOfEventHandlerType;

/**   \brief  value based type definition for Sd_MulticastThresholdOfEventHandler */
typedef uint8 Sd_MulticastThresholdOfEventHandlerType;

/**   \brief  value based type definition for Sd_ServerIdxOfEventHandler */
typedef uint8 Sd_ServerIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_ServerTimerIdxOfEventHandler */
typedef uint8 Sd_ServerTimerIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_SoConActivationMapEndIdxOfEventHandler */
typedef uint8 Sd_SoConActivationMapEndIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_SoConActivationMapStartIdxOfEventHandler */
typedef uint8 Sd_SoConActivationMapStartIdxOfEventHandlerType;

/**   \brief  value based type definition for Sd_SoConActivationMapUsedOfEventHandler */
typedef boolean Sd_SoConActivationMapUsedOfEventHandlerType;

/**   \brief  value based type definition for Sd_NrOfClientsOfEventHandlerDyn */
typedef uint16 Sd_NrOfClientsOfEventHandlerDynType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefIdxOfEventHandlerMulticast */
typedef uint8 Sd_RoutingGroupActRefIdxOfEventHandlerMulticastType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefUsedOfEventHandlerMulticast */
typedef boolean Sd_RoutingGroupActRefUsedOfEventHandlerMulticastType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefIdxOfEventHandlerTcp */
typedef uint8 Sd_RoutingGroupActRefIdxOfEventHandlerTcpType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefUsedOfEventHandlerTcp */
typedef boolean Sd_RoutingGroupActRefUsedOfEventHandlerTcpType;

/**   \brief  value based type definition for Sd_RoutingGroupTriggerIdxOfEventHandlerTcp */
typedef uint8 Sd_RoutingGroupTriggerIdxOfEventHandlerTcpType;

/**   \brief  value based type definition for Sd_RoutingGroupTriggerUsedOfEventHandlerTcp */
typedef boolean Sd_RoutingGroupTriggerUsedOfEventHandlerTcpType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefIdxOfEventHandlerUdp */
typedef uint8 Sd_RoutingGroupActRefIdxOfEventHandlerUdpType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefUsedOfEventHandlerUdp */
typedef boolean Sd_RoutingGroupActRefUsedOfEventHandlerUdpType;

/**   \brief  value based type definition for Sd_RoutingGroupTriggerIdxOfEventHandlerUdp */
typedef uint8 Sd_RoutingGroupTriggerIdxOfEventHandlerUdpType;

/**   \brief  value based type definition for Sd_RoutingGroupTriggerUsedOfEventHandlerUdp */
typedef boolean Sd_RoutingGroupTriggerUsedOfEventHandlerUdpType;

/**   \brief  value based type definition for Sd_AddressStorageEndIdxOfInstance */
typedef uint8 Sd_AddressStorageEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_AddressStorageStartIdxOfInstance */
typedef uint8 Sd_AddressStorageStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_CapabilityRecordEndIdxOfInstance */
typedef uint8 Sd_CapabilityRecordEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_CapabilityRecordStartIdxOfInstance */
typedef uint8 Sd_CapabilityRecordStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_CapabilityRecordUsedOfInstance */
typedef boolean Sd_CapabilityRecordUsedOfInstanceType;

/**   \brief  value based type definition for Sd_ClientEndIdxOfInstance */
typedef uint8 Sd_ClientEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_ClientStartIdxOfInstance */
typedef uint8 Sd_ClientStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_ClientUsedOfInstance */
typedef boolean Sd_ClientUsedOfInstanceType;

/**   \brief  value based type definition for Sd_EndpointStorageEndIdxOfInstance */
typedef uint8 Sd_EndpointStorageEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_EndpointStorageStartIdxOfInstance */
typedef uint8 Sd_EndpointStorageStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_MulticastRxPduIdOfInstance */
typedef PduIdType Sd_MulticastRxPduIdOfInstanceType;

/**   \brief  value based type definition for Sd_QueueProcessLimitOfInstance */
typedef uint8 Sd_QueueProcessLimitOfInstanceType;

/**   \brief  value based type definition for Sd_RetryDelayOfInstance */
typedef uint8 Sd_RetryDelayOfInstanceType;

/**   \brief  value based type definition for Sd_RetryMaxOfInstance */
typedef uint8 Sd_RetryMaxOfInstanceType;

/**   \brief  value based type definition for Sd_RxEventEndIdxOfInstance */
typedef uint8 Sd_RxEventEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_RxEventStartIdxOfInstance */
typedef uint8 Sd_RxEventStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_RxEventUsedOfInstance */
typedef boolean Sd_RxEventUsedOfInstanceType;

/**   \brief  value based type definition for Sd_SendEntryEndIdxOfInstance */
typedef uint8 Sd_SendEntryEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_SendEntryStartIdxOfInstance */
typedef uint8 Sd_SendEntryStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_ServerEndIdxOfInstance */
typedef uint8 Sd_ServerEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_ServerStartIdxOfInstance */
typedef uint8 Sd_ServerStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_ServerUsedOfInstance */
typedef boolean Sd_ServerUsedOfInstanceType;

/**   \brief  value based type definition for Sd_TcpSoConIdEndIdxOfInstance */
typedef uint8 Sd_TcpSoConIdEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_TcpSoConIdStartIdxOfInstance */
typedef uint8 Sd_TcpSoConIdStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_TcpSoConIdUsedOfInstance */
typedef boolean Sd_TcpSoConIdUsedOfInstanceType;

/**   \brief  value based type definition for Sd_TxPduIdOfInstance */
typedef PduIdType Sd_TxPduIdOfInstanceType;

/**   \brief  value based type definition for Sd_UdpSoConEndIdxOfInstance */
typedef uint8 Sd_UdpSoConEndIdxOfInstanceType;

/**   \brief  value based type definition for Sd_UdpSoConStartIdxOfInstance */
typedef uint8 Sd_UdpSoConStartIdxOfInstanceType;

/**   \brief  value based type definition for Sd_UdpSoConUsedOfInstance */
typedef boolean Sd_UdpSoConUsedOfInstanceType;

/**   \brief  value based type definition for Sd_UnicastRxPduIdOfInstance */
typedef PduIdType Sd_UnicastRxPduIdOfInstanceType;

/**   \brief  value based type definition for Sd_RxEventEndIdxOfInstanceDyn */
typedef uint8 Sd_RxEventEndIdxOfInstanceDynType;

/**   \brief  value based type definition for Sd_RxEventListFullOfInstanceDyn */
typedef boolean Sd_RxEventListFullOfInstanceDynType;

/**   \brief  value based type definition for Sd_RxEventStartIdxOfInstanceDyn */
typedef uint8 Sd_RxEventStartIdxOfInstanceDynType;

/**   \brief  value based type definition for Sd_SendEntryEndIdxOfInstanceDyn */
typedef uint8 Sd_SendEntryEndIdxOfInstanceDynType;

/**   \brief  value based type definition for Sd_SendEntryNrPendingIdxOfInstanceDyn */
typedef uint8 Sd_SendEntryNrPendingIdxOfInstanceDynType;

/**   \brief  value based type definition for Sd_SendEntryStartIdxOfInstanceDyn */
typedef uint8 Sd_SendEntryStartIdxOfInstanceDynType;

/**   \brief  value based type definition for Sd_PortSetIdxOfIpAddrRequest */
typedef uint8 Sd_PortSetIdxOfIpAddrRequestType;

/**   \brief  value based type definition for Sd_RequestCntIdxOfIpAddrRequest */
typedef uint8 Sd_RequestCntIdxOfIpAddrRequestType;

/**   \brief  value based type definition for Sd_StaticIpConfigurationOfIpAddrRequest */
typedef boolean Sd_StaticIpConfigurationOfIpAddrRequestType;

/**   \brief  value based type definition for Sd_StaticPortConfigurationOfIpAddrRequest */
typedef boolean Sd_StaticPortConfigurationOfIpAddrRequestType;

/**   \brief  value based type definition for Sd_MaxNrOptionsPerEntry */
typedef uint8 Sd_MaxNrOptionsPerEntryType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefIdxOfMethod */
typedef uint8 Sd_RoutingGroupActRefIdxOfMethodType;

/**   \brief  value based type definition for Sd_RoutingGroupActRefUsedOfMethod */
typedef boolean Sd_RoutingGroupActRefUsedOfMethodType;

/**   \brief  value based type definition for Sd_TcpConfiguredOfMethod */
typedef boolean Sd_TcpConfiguredOfMethodType;

/**   \brief  value based type definition for Sd_UdpConfiguredOfMethod */
typedef boolean Sd_UdpConfiguredOfMethodType;

/**   \brief  value based type definition for Sd_NrOfOptions */
typedef uint16 Sd_NrOfOptionsType;

/**   \brief  value based type definition for Sd_OptionIndex */
typedef uint16 Sd_OptionIndexType;

/**   \brief  value based type definition for Sd_Payload */
typedef uint8 Sd_PayloadType;

/**   \brief  value based type definition for Sd_PortSet */
typedef boolean Sd_PortSetType;

/**   \brief  value based type definition for Sd_RequestCnt */
typedef uint16 Sd_RequestCntType;

/**   \brief  value based type definition for Sd_ClientListIdxOfRxEvent */
typedef uint8 Sd_ClientListIdxOfRxEventType;

/**   \brief  value based type definition for Sd_EventHandlerIdxOfRxEvent */
typedef uint8 Sd_EventHandlerIdxOfRxEventType;

/**   \brief  value based type definition for Sd_AddressStorageIdxOfSendEntry */
typedef uint8 Sd_AddressStorageIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_ClientIdxOfSendEntry */
typedef uint8 Sd_ClientIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_ClientListIdxOfSendEntry */
typedef uint8 Sd_ClientListIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_ConsumedEventgroupIdxOfSendEntry */
typedef uint8 Sd_ConsumedEventgroupIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_EventHandlerIdOfSendEntry */
typedef uint16 Sd_EventHandlerIdOfSendEntryType;

/**   \brief  value based type definition for Sd_EventHandlerIdxOfSendEntry */
typedef uint8 Sd_EventHandlerIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_InstanceIdOfSendEntry */
typedef uint16 Sd_InstanceIdOfSendEntryType;

/**   \brief  value based type definition for Sd_InstanceIdxOfSendEntry */
typedef uint8 Sd_InstanceIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_MajorVersionOfSendEntry */
typedef uint8 Sd_MajorVersionOfSendEntryType;

/**   \brief  value based type definition for Sd_ReservedFieldOfSendEntry */
typedef uint16 Sd_ReservedFieldOfSendEntryType;

/**   \brief  value based type definition for Sd_SendEntryNextIdxOfSendEntry */
typedef uint8 Sd_SendEntryNextIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_ServerIdxOfSendEntry */
typedef uint8 Sd_ServerIdxOfSendEntryType;

/**   \brief  value based type definition for Sd_ServiceIdOfSendEntry */
typedef uint16 Sd_ServiceIdOfSendEntryType;

/**   \brief  value based type definition for Sd_ValidOfSendEntry */
typedef boolean Sd_ValidOfSendEntryType;

/**   \brief  value based type definition for Sd_AutoAvailableOfServer */
typedef boolean Sd_AutoAvailableOfServerType;

/**   \brief  value based type definition for Sd_CapabilityRecordEndIdxOfServer */
typedef uint8 Sd_CapabilityRecordEndIdxOfServerType;

/**   \brief  value based type definition for Sd_CapabilityRecordFunctionCalloutPtrIdxOfServer */
typedef uint8 Sd_CapabilityRecordFunctionCalloutPtrIdxOfServerType;

/**   \brief  value based type definition for Sd_CapabilityRecordFunctionCalloutPtrUsedOfServer */
typedef boolean Sd_CapabilityRecordFunctionCalloutPtrUsedOfServerType;

/**   \brief  value based type definition for Sd_CapabilityRecordStartIdxOfServer */
typedef uint8 Sd_CapabilityRecordStartIdxOfServerType;

/**   \brief  value based type definition for Sd_CapabilityRecordUsedOfServer */
typedef boolean Sd_CapabilityRecordUsedOfServerType;

/**   \brief  value based type definition for Sd_CommonInitialDelayIdxOfServer */
typedef uint8 Sd_CommonInitialDelayIdxOfServerType;

/**   \brief  value based type definition for Sd_CommonInitialDelayUsedOfServer */
typedef boolean Sd_CommonInitialDelayUsedOfServerType;

/**   \brief  value based type definition for Sd_EventHandlerEndIdxOfServer */
typedef uint8 Sd_EventHandlerEndIdxOfServerType;

/**   \brief  value based type definition for Sd_EventHandlerStartIdxOfServer */
typedef uint8 Sd_EventHandlerStartIdxOfServerType;

/**   \brief  value based type definition for Sd_EventHandlerUsedOfServer */
typedef boolean Sd_EventHandlerUsedOfServerType;

/**   \brief  value based type definition for Sd_HandleIdOfServer */
typedef uint8 Sd_HandleIdOfServerType;

/**   \brief  value based type definition for Sd_InstanceIdOfServer */
typedef uint8 Sd_InstanceIdOfServerType;

/**   \brief  value based type definition for Sd_InstanceIdxOfServer */
typedef uint8 Sd_InstanceIdxOfServerType;

/**   \brief  value based type definition for Sd_MajorVersionOfServer */
typedef uint8 Sd_MajorVersionOfServerType;

/**   \brief  value based type definition for Sd_MethodIdxOfServer */
typedef uint8 Sd_MethodIdxOfServerType;

/**   \brief  value based type definition for Sd_MethodUsedOfServer */
typedef boolean Sd_MethodUsedOfServerType;

/**   \brief  value based type definition for Sd_MinorVersionOfServer */
typedef uint8 Sd_MinorVersionOfServerType;

/**   \brief  value based type definition for Sd_ServerTimerIdxOfServer */
typedef uint8 Sd_ServerTimerIdxOfServerType;

/**   \brief  value based type definition for Sd_ServiceGroupMemberOfServer */
typedef boolean Sd_ServiceGroupMemberOfServerType;

/**   \brief  value based type definition for Sd_ServiceIdOfServer */
typedef uint16 Sd_ServiceIdOfServerType;

/**   \brief  value based type definition for Sd_TcpSoConIdEndIdxOfServer */
typedef uint8 Sd_TcpSoConIdEndIdxOfServerType;

/**   \brief  value based type definition for Sd_TcpSoConIdStartIdxOfServer */
typedef uint8 Sd_TcpSoConIdStartIdxOfServerType;

/**   \brief  value based type definition for Sd_TcpSoConIdUsedOfServer */
typedef boolean Sd_TcpSoConIdUsedOfServerType;

/**   \brief  value based type definition for Sd_UdpSoConEndIdxOfServer */
typedef uint8 Sd_UdpSoConEndIdxOfServerType;

/**   \brief  value based type definition for Sd_UdpSoConStartIdxOfServer */
typedef uint8 Sd_UdpSoConStartIdxOfServerType;

/**   \brief  value based type definition for Sd_UdpSoConUsedOfServer */
typedef boolean Sd_UdpSoConUsedOfServerType;

/**   \brief  value based type definition for Sd_InitialOfferRepetitionRunOfServerDyn */
typedef uint8 Sd_InitialOfferRepetitionRunOfServerDynType;

/**   \brief  value based type definition for Sd_ServiceGroupReqCounterOfServerDyn */
typedef uint8 Sd_ServiceGroupReqCounterOfServerDynType;

/**   \brief  value based type definition for Sd_StateMachineExecutionRequestedOfServerDyn */
typedef boolean Sd_StateMachineExecutionRequestedOfServerDynType;

/**   \brief  value based type definition for Sd_InvalidHndOfServerMap */
typedef boolean Sd_InvalidHndOfServerMapType;

/**   \brief  value based type definition for Sd_ServerIdxOfServerMap */
typedef uint8 Sd_ServerIdxOfServerMapType;

/**   \brief  value based type definition for Sd_ServerUsedOfServerMap */
typedef boolean Sd_ServerUsedOfServerMapType;

/**   \brief  value based type definition for Sd_InitialOfferDelayMaxOfServerTimer */
typedef uint8 Sd_InitialOfferDelayMaxOfServerTimerType;

/**   \brief  value based type definition for Sd_InitialOfferDelayMinOfServerTimer */
typedef uint8 Sd_InitialOfferDelayMinOfServerTimerType;

/**   \brief  value based type definition for Sd_InitialOfferRepetitionBaseDelayOfServerTimer */
typedef uint8 Sd_InitialOfferRepetitionBaseDelayOfServerTimerType;

/**   \brief  value based type definition for Sd_InitialOfferRepetitionsMaxOfServerTimer */
typedef uint8 Sd_InitialOfferRepetitionsMaxOfServerTimerType;

/**   \brief  value based type definition for Sd_OfferCyclicDelayOfServerTimer */
typedef uint8 Sd_OfferCyclicDelayOfServerTimerType;

/**   \brief  value based type definition for Sd_RequestResponseMaxDelayOfServerTimer */
typedef uint8 Sd_RequestResponseMaxDelayOfServerTimerType;

/**   \brief  value based type definition for Sd_RequestResponseMinDelayOfServerTimer */
typedef uint8 Sd_RequestResponseMinDelayOfServerTimerType;

/**   \brief  value based type definition for Sd_TTLOfServerTimer */
typedef uint32 Sd_TTLOfServerTimerType;

/**   \brief  value based type definition for Sd_ServiceGroupMemberEndIdxOfServiceGroup */
typedef uint8 Sd_ServiceGroupMemberEndIdxOfServiceGroupType;

/**   \brief  value based type definition for Sd_ServiceGroupMemberStartIdxOfServiceGroup */
typedef uint8 Sd_ServiceGroupMemberStartIdxOfServiceGroupType;

/**   \brief  value based type definition for Sd_InvalidHndOfServiceGroupMap */
typedef boolean Sd_InvalidHndOfServiceGroupMapType;

/**   \brief  value based type definition for Sd_ServiceGroupIdxOfServiceGroupMap */
typedef uint8 Sd_ServiceGroupIdxOfServiceGroupMapType;

/**   \brief  value based type definition for Sd_ServiceGroupUsedOfServiceGroupMap */
typedef boolean Sd_ServiceGroupUsedOfServiceGroupMapType;

/**   \brief  value based type definition for Sd_ClientIdxOfServiceGroupMember */
typedef uint8 Sd_ClientIdxOfServiceGroupMemberType;

/**   \brief  value based type definition for Sd_ClientUsedOfServiceGroupMember */
typedef boolean Sd_ClientUsedOfServiceGroupMemberType;

/**   \brief  value based type definition for Sd_ServerIdxOfServiceGroupMember */
typedef uint8 Sd_ServerIdxOfServiceGroupMemberType;

/**   \brief  value based type definition for Sd_ServerUsedOfServiceGroupMember */
typedef boolean Sd_ServerUsedOfServiceGroupMemberType;

/**   \brief  value based type definition for Sd_SizeOfAddressStorage */
typedef uint8 Sd_SizeOfAddressStorageType;

/**   \brief  value based type definition for Sd_SizeOfCapabilityRecord */
typedef uint8 Sd_SizeOfCapabilityRecordType;

/**   \brief  value based type definition for Sd_SizeOfCapabilityRecordFunctionCalloutPtr */
typedef uint8 Sd_SizeOfCapabilityRecordFunctionCalloutPtrType;

/**   \brief  value based type definition for Sd_SizeOfClient */
typedef uint8 Sd_SizeOfClientType;

/**   \brief  value based type definition for Sd_SizeOfClientDyn */
typedef uint8 Sd_SizeOfClientDynType;

/**   \brief  value based type definition for Sd_SizeOfClientList */
typedef uint8 Sd_SizeOfClientListType;

/**   \brief  value based type definition for Sd_SizeOfClientMap */
typedef uint8 Sd_SizeOfClientMapType;

/**   \brief  value based type definition for Sd_SizeOfClientTimer */
typedef uint8 Sd_SizeOfClientTimerType;

/**   \brief  value based type definition for Sd_SizeOfCommonInitialDelay */
typedef uint8 Sd_SizeOfCommonInitialDelayType;

/**   \brief  value based type definition for Sd_SizeOfConsumedEventgroup */
typedef uint8 Sd_SizeOfConsumedEventgroupType;

/**   \brief  value based type definition for Sd_SizeOfConsumedEventgroupDyn */
typedef uint8 Sd_SizeOfConsumedEventgroupDynType;

/**   \brief  value based type definition for Sd_SizeOfConsumedEventgroupMap */
typedef uint8 Sd_SizeOfConsumedEventgroupMapType;

/**   \brief  value based type definition for Sd_SizeOfEndpointStorage */
typedef uint8 Sd_SizeOfEndpointStorageType;

/**   \brief  value based type definition for Sd_SizeOfEventHandler */
typedef uint8 Sd_SizeOfEventHandlerType;

/**   \brief  value based type definition for Sd_SizeOfEventHandlerDyn */
typedef uint8 Sd_SizeOfEventHandlerDynType;

/**   \brief  value based type definition for Sd_SizeOfEventHandlerMulticast */
typedef uint8 Sd_SizeOfEventHandlerMulticastType;

/**   \brief  value based type definition for Sd_SizeOfEventHandlerTcp */
typedef uint8 Sd_SizeOfEventHandlerTcpType;

/**   \brief  value based type definition for Sd_SizeOfEventHandlerUdp */
typedef uint8 Sd_SizeOfEventHandlerUdpType;

/**   \brief  value based type definition for Sd_SizeOfInstance */
typedef uint8 Sd_SizeOfInstanceType;

/**   \brief  value based type definition for Sd_SizeOfInstanceDyn */
typedef uint8 Sd_SizeOfInstanceDynType;

/**   \brief  value based type definition for Sd_SizeOfIpAddrRequest */
typedef uint8 Sd_SizeOfIpAddrRequestType;

/**   \brief  value based type definition for Sd_SizeOfMethod */
typedef uint8 Sd_SizeOfMethodType;

/**   \brief  value based type definition for Sd_SizeOfMulticastEndpointAddr */
typedef uint8 Sd_SizeOfMulticastEndpointAddrType;

/**   \brief  value based type definition for Sd_SizeOfMulticastSoConId */
typedef uint8 Sd_SizeOfMulticastSoConIdType;

/**   \brief  value based type definition for Sd_SizeOfOptionIndex */
typedef uint8 Sd_SizeOfOptionIndexType;

/**   \brief  value based type definition for Sd_SizeOfPayload */
typedef uint16 Sd_SizeOfPayloadType;

/**   \brief  value based type definition for Sd_SizeOfPortSet */
typedef uint8 Sd_SizeOfPortSetType;

/**   \brief  value based type definition for Sd_SizeOfRequestCnt */
typedef uint8 Sd_SizeOfRequestCntType;

/**   \brief  value based type definition for Sd_SizeOfRoutingGroup */
typedef uint8 Sd_SizeOfRoutingGroupType;

/**   \brief  value based type definition for Sd_SizeOfRoutingGroupDyn */
typedef uint8 Sd_SizeOfRoutingGroupDynType;

/**   \brief  value based type definition for Sd_SizeOfRxEvent */
typedef uint8 Sd_SizeOfRxEventType;

/**   \brief  value based type definition for Sd_SizeOfSendEntry */
typedef uint8 Sd_SizeOfSendEntryType;

/**   \brief  value based type definition for Sd_SizeOfServer */
typedef uint8 Sd_SizeOfServerType;

/**   \brief  value based type definition for Sd_SizeOfServerDyn */
typedef uint8 Sd_SizeOfServerDynType;

/**   \brief  value based type definition for Sd_SizeOfServerMap */
typedef uint8 Sd_SizeOfServerMapType;

/**   \brief  value based type definition for Sd_SizeOfServerTimer */
typedef uint8 Sd_SizeOfServerTimerType;

/**   \brief  value based type definition for Sd_SizeOfServiceGroup */
typedef uint8 Sd_SizeOfServiceGroupType;

/**   \brief  value based type definition for Sd_SizeOfServiceGroupMap */
typedef uint8 Sd_SizeOfServiceGroupMapType;

/**   \brief  value based type definition for Sd_SizeOfServiceGroupMember */
typedef uint8 Sd_SizeOfServiceGroupMemberType;

/**   \brief  value based type definition for Sd_SizeOfSoConActivationMap */
typedef uint8 Sd_SizeOfSoConActivationMapType;

/**   \brief  value based type definition for Sd_SizeOfTcpSoConId */
typedef uint8 Sd_SizeOfTcpSoConIdType;

/**   \brief  value based type definition for Sd_SizeOfTcpSoConModeMap */
typedef uint8 Sd_SizeOfTcpSoConModeMapType;

/**   \brief  value based type definition for Sd_SizeOfTriggerTransmit */
typedef uint8 Sd_SizeOfTriggerTransmitType;

/**   \brief  value based type definition for Sd_SizeOfUdpSoCon */
typedef uint8 Sd_SizeOfUdpSoConType;

/**   \brief  value based type definition for Sd_NrOfActivationsOfSoConActivationMap */
typedef uint8 Sd_NrOfActivationsOfSoConActivationMapType;

/**   \brief  value based type definition for Sd_ClientListIdxOfTriggerTransmit */
typedef uint8 Sd_ClientListIdxOfTriggerTransmitType;

/**   \brief  value based type definition for Sd_EventHandlerIdxOfTriggerTransmit */
typedef uint8 Sd_EventHandlerIdxOfTriggerTransmitType;

/**   \brief  value based type definition for Sd_TriggerTransmitEndIdx */
typedef uint8 Sd_TriggerTransmitEndIdxType;

/**   \brief  value based type definition for Sd_TriggerTransmitFull */
typedef boolean Sd_TriggerTransmitFullType;

/**   \brief  value based type definition for Sd_TriggerTransmitStartIdx */
typedef uint8 Sd_TriggerTransmitStartIdxType;

/**   \brief  value based type definition for Sd_PreconfiguredOfUdpSoCon */
typedef boolean Sd_PreconfiguredOfUdpSoConType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  SdPCStructTypes  Sd Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Sd_AddressStorage */
typedef struct sSd_AddressStorageType
{
  Sd_RxMulticastSessionIdOfAddressStorageType RxMulticastSessionIdOfAddressStorage;  /**< RX multicast session ID */
  Sd_RxUnicastSessionIdOfAddressStorageType RxUnicastSessionIdOfAddressStorage;  /**< RX unicast session ID */
  Sd_SessionIdCounterOfAddressStorageType SessionIdCounterOfAddressStorage;  /**< TX session ID */
  Sd_FlagsOfAddressStorageType FlagsOfAddressStorage;  /**< TX flags */
  Sd_RxMulticastFlagsOfAddressStorageType RxMulticastFlagsOfAddressStorage;  /**< RX multicast flags */
  Sd_RxUnicastFlagsOfAddressStorageType RxUnicastFlagsOfAddressStorage;  /**< RX unicast flags */
  Sd_SendEntryNrPendingIdxOfAddressStorageType SendEntryNrPendingIdxOfAddressStorage;  /**< the index of the 1:1 relation pointing to Sd_SendEntry */
  Sd_SockAddrContainerType AddrOfAddressStorage;  /**< Address of the communication partner */
} Sd_AddressStorageType;

/**   \brief  type used in Sd_Client */
/*! \spec weak type invariant () { 
 * (self.InstanceIdxOfClient < Sd_GetSizeOfInstance()) &&
 * (self.ClientTimerIdxOfClient < Sd_GetSizeOfClientTimer()) &&
 * (!((self.CapabilityRecordFunctionCalloutPtrIdxOfClient != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFCLIENT)) || (self.CapabilityRecordFunctionCalloutPtrIdxOfClient < Sd_GetSizeOfCapabilityRecordFunctionCalloutPtr())) &&
 * (!((self.CapabilityRecordStartIdxOfClient != SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT)) || (self.CapabilityRecordStartIdxOfClient < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.CapabilityRecordStartIdxOfClient != SD_NO_CAPABILITYRECORDSTARTIDXOFCLIENT)) || (self.CapabilityRecordEndIdxOfClient < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.UdpSoConStartIdxOfClient != SD_NO_UDPSOCONSTARTIDXOFCLIENT)) || (self.UdpSoConStartIdxOfClient < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.UdpSoConStartIdxOfClient != SD_NO_UDPSOCONSTARTIDXOFCLIENT)) || (self.UdpSoConEndIdxOfClient < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.TcpSoConIdStartIdxOfClient != SD_NO_TCPSOCONIDSTARTIDXOFCLIENT)) || (self.TcpSoConIdStartIdxOfClient < Sd_GetSizeOfTcpSoConId())) &&
 * (!((self.TcpSoConIdStartIdxOfClient != SD_NO_TCPSOCONIDSTARTIDXOFCLIENT)) || (self.TcpSoConIdEndIdxOfClient < Sd_GetSizeOfTcpSoConId())) &&
 * (!((self.MethodIdxOfClient != SD_NO_METHODIDXOFCLIENT)) || (self.MethodIdxOfClient < Sd_GetSizeOfMethod())) &&
 * (!((self.ConsumedEventgroupStartIdxOfClient != SD_NO_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT)) || (self.ConsumedEventgroupStartIdxOfClient < Sd_GetSizeOfConsumedEventgroup())) &&
 * (!((self.ConsumedEventgroupStartIdxOfClient != SD_NO_CONSUMEDEVENTGROUPSTARTIDXOFCLIENT)) || (self.ConsumedEventgroupEndIdxOfClient < Sd_GetSizeOfConsumedEventgroup())) &&
 * (!((self.CommonInitialDelayIdxOfClient != SD_NO_COMMONINITIALDELAYIDXOFCLIENT)) || (self.CommonInitialDelayIdxOfClient < Sd_GetSizeOfCommonInitialDelay()))
 * } */
typedef struct sSd_ClientType
{
  Sd_ServiceIdOfClientType ServiceIdOfClient;  /**< Service ID */
  Sd_AutoRequireOfClientType AutoRequireOfClient;  /**< Auto require flag */
  Sd_MinorVersionWildcardOfClientType MinorVersionWildcardOfClient;  /**< Indicates if MinorVersion is configured to wildcard. */
  Sd_ServiceGroupMemberOfClientType ServiceGroupMemberOfClient;  /**< Specifies if service is member of a ServiceGroup. */
  Sd_CapabilityRecordEndIdxOfClientType CapabilityRecordEndIdxOfClient;  /**< the end index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_CapabilityRecordFunctionCalloutPtrIdxOfClientType CapabilityRecordFunctionCalloutPtrIdxOfClient;  /**< the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr */
  Sd_CapabilityRecordStartIdxOfClientType CapabilityRecordStartIdxOfClient;  /**< the start index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_ClientTimerIdxOfClientType ClientTimerIdxOfClient;  /**< the index of the 1:1 relation pointing to Sd_ClientTimer */
  Sd_CommonInitialDelayIdxOfClientType CommonInitialDelayIdxOfClient;  /**< the index of the 0:1 relation pointing to Sd_CommonInitialDelay */
  Sd_ConsumedEventgroupEndIdxOfClientType ConsumedEventgroupEndIdxOfClient;  /**< the end index of the 0:n relation pointing to Sd_ConsumedEventgroup */
  Sd_ConsumedEventgroupStartIdxOfClientType ConsumedEventgroupStartIdxOfClient;  /**< the start index of the 0:n relation pointing to Sd_ConsumedEventgroup */
  Sd_HandleIdOfClientType HandleIdOfClient;  /**< Handle ID */
  Sd_InstanceIdOfClientType InstanceIdOfClient;  /**< Instance ID */
  Sd_InstanceIdxOfClientType InstanceIdxOfClient;  /**< the index of the 1:1 relation pointing to Sd_Instance */
  Sd_MajorVersionOfClientType MajorVersionOfClient;  /**< Major Version */
  Sd_MethodIdxOfClientType MethodIdxOfClient;  /**< the index of the 0:1 relation pointing to Sd_Method */
  Sd_MinorVersionOfClientType MinorVersionOfClient;  /**< Minor Version */
  Sd_TcpSoConIdEndIdxOfClientType TcpSoConIdEndIdxOfClient;  /**< the end index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_TcpSoConIdStartIdxOfClientType TcpSoConIdStartIdxOfClient;  /**< the start index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_UdpSoConEndIdxOfClientType UdpSoConEndIdxOfClient;  /**< the end index of the 0:n relation pointing to Sd_UdpSoCon */
  Sd_UdpSoConStartIdxOfClientType UdpSoConStartIdxOfClient;  /**< the start index of the 0:n relation pointing to Sd_UdpSoCon */
} Sd_ClientType;

/**   \brief  type used in Sd_ClientDyn */
typedef struct sSd_ClientDynType
{
  Sd_OfferedTTLOfClientDynType OfferedTTLOfClientDyn;  /**< Offered Time To Live */
  Sd_AddressStorageServerIdxOfClientDynType AddressStorageServerIdxOfClientDyn;  /**< the index of the 0:1 relation pointing to Sd_AddressStorage */
  Sd_RepetitionRunOfClientDynType RepetitionRunOfClientDyn;  /**< Repetition run counter */
  Sd_RetryCounterOfClientDynType RetryCounterOfClientDyn;  /**< Counter for subscribe eventgroup retry handling. */
  Sd_ServiceGroupReqCounterOfClientDynType ServiceGroupReqCounterOfClientDyn;  /**< Client request counter for ServiceGroup service API */
  Sd_StateMachineExecutionRequestedOfClientDynType StateMachineExecutionRequestedOfClientDyn;  /**< Flag if State machine shall be executed for this client */
  Sd_ClientServiceCurrentStateType CurrentStateOfClientDyn;  /**< Current state */
  Sd_ClientServiceEventType EventMainOfClientDyn;  /**< Event processed in MainFunction. */
  Sd_ClientServiceEventType EventRxOfClientDyn;  /**< Received event */
  SoAd_SoConIdType MethodTcpSoConIdOfClientDyn;  /**< TCP method SoConId */
  SoAd_SoConIdType MethodUdpSoConIdOfClientDyn;  /**< UDP method SoConId */
  Sd_ExtendedTimeType RetryTimerOfClientDyn;  /**< Timer for subscribe eventgroup retry handling. */
  Sd_SockAddrContainerType ServerTcpEndpointAddrOfClientDyn;  /**< Server TCP endpoint address */
  Sd_SockAddrContainerType ServerUdpEndpointAddrOfClientDyn;  /**< Server UDP endpoint address */
  Sd_ClientStateMachineType StateMachineOfClientDyn;  /**< State machine */
  Sd_ClientServiceSetStateType StateSwcOfClientDyn;  /**< Requested state */
  Sd_ExtendedTimeType TimeToTriggerSendOfClientDyn;  /**< Time to trigger next message transmission */
  Sd_ExtendedTimeType TimerTTLOfClientDyn;  /**< Time To Live */
} Sd_ClientDynType;

/**   \brief  type used in Sd_ClientList */
typedef struct sSd_ClientListType
{
  Sd_RequestedTTLOfClientListType RequestedTTLOfClientList;  /**< Requested TimeToLive */
  Sd_RxReservedOfClientListType RxReservedOfClientList;  /**< Received reserved field */
  Sd_AddressStorageIdxOfClientListType AddressStorageIdxOfClientList;  /**< the index of the 0:1 relation pointing to Sd_AddressStorage */
  Sd_EndpointStorageTcpIdxOfClientListType EndpointStorageTcpIdxOfClientList;  /**< the index of the 0:1 relation pointing to Sd_EndpointStorage */
  Sd_EndpointStorageUdpIdxOfClientListType EndpointStorageUdpIdxOfClientList;  /**< the index of the 0:1 relation pointing to Sd_EndpointStorage */
  Sd_NrOfReferencesOfClientListType NrOfReferencesOfClientList;  /**< Number of simultaneous subscriptions */
  SoAd_SoConIdType AssignedTcpSoConIdOfClientList;  /**< Used TCP SocketConnection ID */
  SoAd_SoConIdType AssignedUdpSoConIdOfClientList;  /**< Used UDP SocketConnection ID */
  Sd_EventHandlerClientStateType ClientStateOfClientList;  /**< State of the client */
  Sd_ExtendedTimeType SubscribedUntilOfClientList;  /**< Point in time till the client is subscribed */
} Sd_ClientListType;

/**   \brief  type used in Sd_ClientMap */
/*! \spec weak type invariant () { 
 * (!((self.ClientIdxOfClientMap != SD_NO_CLIENTIDXOFCLIENTMAP)) || (self.ClientIdxOfClientMap < Sd_GetSizeOfClient()))
 * } */
typedef struct sSd_ClientMapType
{
  Sd_InvalidHndOfClientMapType InvalidHndOfClientMap;  /**< FALSE, if the handle of Sd_ClientMap is valid and can be used in the embedded code for further processing in the embedded code. */
  Sd_ClientIdxOfClientMapType ClientIdxOfClientMap;  /**< the index of the 0:1 relation pointing to Sd_Client */
} Sd_ClientMapType;

/**   \brief  type used in Sd_ClientTimer */
typedef struct sSd_ClientTimerType
{
  Sd_TTLOfClientTimerType TTLOfClientTimer;  /**< Time To Live */
  Sd_InitialFindDelayMaxOfClientTimerType InitialFindDelayMaxOfClientTimer;  /**< Maximal initial delay for FindService message */
  Sd_InitialFindDelayMinOfClientTimerType InitialFindDelayMinOfClientTimer;  /**< Minimal initial delay for FindService message */
  Sd_InitialFindRepetitionBaseDelayOfClientTimerType InitialFindRepetitionBaseDelayOfClientTimer;  /**< Base delay for FindService messages during initial find phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS. */
  Sd_InitialFindRepetitionsMaxOfClientTimerType InitialFindRepetitionsMaxOfClientTimer;  /**< Amount of FindService messages transmitted during initial find phase */
  Sd_RequestResponseMaxDelayOfClientTimerType RequestResponseMaxDelayOfClientTimer;  /**< Maximal request-response delay */
  Sd_RequestResponseMinDelayOfClientTimerType RequestResponseMinDelayOfClientTimer;  /**< Minimal request-response delay */
} Sd_ClientTimerType;

/**   \brief  type used in Sd_ConsumedEventgroup */
/*! \spec weak type invariant () { 
 * (self.ClientIdxOfConsumedEventgroup < Sd_GetSizeOfClient()) &&
 * (self.ClientTimerIdxOfConsumedEventgroup < Sd_GetSizeOfClientTimer()) &&
 * (!((self.MulticastSoConIdStartIdxOfConsumedEventgroup != SD_NO_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP)) || (self.MulticastSoConIdStartIdxOfConsumedEventgroup < Sd_GetSizeOfMulticastSoConId())) &&
 * (!((self.MulticastSoConIdStartIdxOfConsumedEventgroup != SD_NO_MULTICASTSOCONIDSTARTIDXOFCONSUMEDEVENTGROUP)) || (self.MulticastSoConIdEndIdxOfConsumedEventgroup < Sd_GetSizeOfMulticastSoConId())) &&
 * (!((self.MulticastEndpointAddrIdxOfConsumedEventgroup != SD_NO_MULTICASTENDPOINTADDRIDXOFCONSUMEDEVENTGROUP)) || (self.MulticastEndpointAddrIdxOfConsumedEventgroup < Sd_GetSizeOfMulticastEndpointAddr())) &&
 * (!((self.RoutingGroupMulticastActRefIdxOfConsumedEventgroup != SD_NO_ROUTINGGROUPMULTICASTACTREFIDXOFCONSUMEDEVENTGROUP)) || (self.RoutingGroupMulticastActRefIdxOfConsumedEventgroup < Sd_GetSizeOfRoutingGroup())) &&
 * (!((self.RoutingGroupTcpActRefIdxOfConsumedEventgroup != SD_NO_ROUTINGGROUPTCPACTREFIDXOFCONSUMEDEVENTGROUP)) || (self.RoutingGroupTcpActRefIdxOfConsumedEventgroup < Sd_GetSizeOfRoutingGroup())) &&
 * (!((self.RoutingGroupUdpActRefIdxOfConsumedEventgroup != SD_NO_ROUTINGGROUPUDPACTREFIDXOFCONSUMEDEVENTGROUP)) || (self.RoutingGroupUdpActRefIdxOfConsumedEventgroup < Sd_GetSizeOfRoutingGroup()))
 * } */
typedef struct sSd_ConsumedEventgroupType
{
  Sd_AutoRequireOfConsumedEventgroupType AutoRequireOfConsumedEventgroup;  /**< Auto require flag */
  Sd_ClientIdxOfConsumedEventgroupType ClientIdxOfConsumedEventgroup;  /**< the index of the 1:1 relation pointing to Sd_Client */
  Sd_ClientTimerIdxOfConsumedEventgroupType ClientTimerIdxOfConsumedEventgroup;  /**< the index of the 1:1 relation pointing to Sd_ClientTimer */
  Sd_EventGroupIdOfConsumedEventgroupType EventGroupIdOfConsumedEventgroup;  /**< Eventgroup ID */
  Sd_HandleIdOfConsumedEventgroupType HandleIdOfConsumedEventgroup;  /**< Handle ID */
  Sd_MulticastEndpointAddrIdxOfConsumedEventgroupType MulticastEndpointAddrIdxOfConsumedEventgroup;  /**< the index of the 0:1 relation pointing to Sd_MulticastEndpointAddr */
  Sd_MulticastSoConIdEndIdxOfConsumedEventgroupType MulticastSoConIdEndIdxOfConsumedEventgroup;  /**< the end index of the 0:n relation pointing to Sd_MulticastSoConId */
  Sd_MulticastSoConIdStartIdxOfConsumedEventgroupType MulticastSoConIdStartIdxOfConsumedEventgroup;  /**< the start index of the 0:n relation pointing to Sd_MulticastSoConId */
  Sd_RoutingGroupMulticastActRefIdxOfConsumedEventgroupType RoutingGroupMulticastActRefIdxOfConsumedEventgroup;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
  Sd_RoutingGroupTcpActRefIdxOfConsumedEventgroupType RoutingGroupTcpActRefIdxOfConsumedEventgroup;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
  Sd_RoutingGroupUdpActRefIdxOfConsumedEventgroupType RoutingGroupUdpActRefIdxOfConsumedEventgroup;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
} Sd_ConsumedEventgroupType;

/**   \brief  type used in Sd_ConsumedEventgroupDyn */
typedef struct sSd_ConsumedEventgroupDynType
{
  Sd_AcknowledgedTTLOfConsumedEventgroupDynType AcknowledgedTTLOfConsumedEventgroupDyn;  /**< Acknowledge Time To Live */
  Sd_RxIndicationCountOfConsumedEventgroupDynType RxIndicationCountOfConsumedEventgroupDyn;  /**< Counter to differentiate RxIndication calls. */
  Sd_SoConMarkedForClosureOfConsumedEventgroupDynType SoConMarkedForClosureOfConsumedEventgroupDyn;  /**< Flag if EventGroup has been unconfigured and SoCon can be closed. */
  Sd_TriggerSubscriptionOfConsumedEventgroupDynType TriggerSubscriptionOfConsumedEventgroupDyn;  /**< Flag indicating if a subscription shall be triggered. */
  Sd_ConsumedEventGroupCurrentStateType CurrentStateOfConsumedEventgroupDyn;  /**< Current state */
  Sd_ClientEventgroupEventType EventOfConsumedEventgroupDyn;  /**< Received event */
  SoAd_SoConIdType MulticastSoConIdOfConsumedEventgroupDyn;  /**< Configured multicast SocketConnection */
  Sd_ConsumedEventGroupSetStateType ServiceModeRequestOfConsumedEventgroupDyn;  /**< Requested state */
  Sd_ConsumedEventGroupStateMachineType StateMachineOfConsumedEventgroupDyn;  /**< State machine */
  SoAd_SoConIdType TcpSoConIdOfConsumedEventgroupDyn;  /**< Configured TCP SocketConnection */
  Sd_ExtendedTimeType TimerTTLOfConsumedEventgroupDyn;  /**< Time To Live */
  SoAd_SoConIdType UdpSoConIdOfConsumedEventgroupDyn;  /**< Configured UDP SocketConnection */
} Sd_ConsumedEventgroupDynType;

/**   \brief  type used in Sd_ConsumedEventgroupMap */
/*! \spec weak type invariant () { 
 * (!((self.ConsumedEventgroupIdxOfConsumedEventgroupMap != SD_NO_CONSUMEDEVENTGROUPIDXOFCONSUMEDEVENTGROUPMAP)) || (self.ConsumedEventgroupIdxOfConsumedEventgroupMap < Sd_GetSizeOfConsumedEventgroup()))
 * } */
typedef struct sSd_ConsumedEventgroupMapType
{
  Sd_InvalidHndOfConsumedEventgroupMapType InvalidHndOfConsumedEventgroupMap;  /**< FALSE, if the handle of Sd_ConsumedEventgroupMap is valid and can be used in the embedded code for further processing in the embedded code. */
  Sd_ConsumedEventgroupIdxOfConsumedEventgroupMapType ConsumedEventgroupIdxOfConsumedEventgroupMap;  /**< the index of the 0:1 relation pointing to Sd_ConsumedEventgroup */
} Sd_ConsumedEventgroupMapType;

/**   \brief  type used in Sd_EndpointStorage */
typedef struct sSd_EndpointStorageType
{
  Sd_NrOfReferencesOfEndpointStorageType NrOfReferencesOfEndpointStorage;  /**< Number of external references */
  Sd_SockAddrContainerType AddrOfEndpointStorage;  /**< Endpoint address */
  Sd_EndpointType TypeOfEndpointStorage;  /**< Endpoint type */
} Sd_EndpointStorageType;

/**   \brief  type used in Sd_EventHandler */
/*! \spec weak type invariant () { 
 * (self.ServerIdxOfEventHandler < Sd_GetSizeOfServer()) &&
 * (self.ServerTimerIdxOfEventHandler < Sd_GetSizeOfServerTimer()) &&
 * (self.ClientListStartIdxOfEventHandler < Sd_GetSizeOfClientList()) &&
 * (self.ClientListEndIdxOfEventHandler < Sd_GetSizeOfClientList()) &&
 * (!((self.EventHandlerUdpIdxOfEventHandler != SD_NO_EVENTHANDLERUDPIDXOFEVENTHANDLER)) || (self.EventHandlerUdpIdxOfEventHandler < Sd_GetSizeOfEventHandlerUdp())) &&
 * (!((self.EventHandlerTcpIdxOfEventHandler != SD_NO_EVENTHANDLERTCPIDXOFEVENTHANDLER)) || (self.EventHandlerTcpIdxOfEventHandler < Sd_GetSizeOfEventHandlerTcp())) &&
 * (!((self.EventHandlerMulticastIdxOfEventHandler != SD_NO_EVENTHANDLERMULTICASTIDXOFEVENTHANDLER)) || (self.EventHandlerMulticastIdxOfEventHandler < Sd_GetSizeOfEventHandlerMulticast())) &&
 * (!((self.SoConActivationMapStartIdxOfEventHandler != SD_NO_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER)) || (self.SoConActivationMapStartIdxOfEventHandler < Sd_GetSizeOfSoConActivationMap())) &&
 * (!((self.SoConActivationMapStartIdxOfEventHandler != SD_NO_SOCONACTIVATIONMAPSTARTIDXOFEVENTHANDLER)) || (self.SoConActivationMapEndIdxOfEventHandler < Sd_GetSizeOfSoConActivationMap()))
 * } */
typedef struct sSd_EventHandlerType
{
  Sd_ClientListEndIdxOfEventHandlerType ClientListEndIdxOfEventHandler;  /**< the end index of the 1:n relation pointing to Sd_ClientList */
  Sd_ClientListStartIdxOfEventHandlerType ClientListStartIdxOfEventHandler;  /**< the start index of the 1:n relation pointing to Sd_ClientList */
  Sd_EventGroupIdOfEventHandlerType EventGroupIdOfEventHandler;  /**< Eventgroup ID */
  Sd_EventHandlerMulticastIdxOfEventHandlerType EventHandlerMulticastIdxOfEventHandler;  /**< the index of the 0:1 relation pointing to Sd_EventHandlerMulticast */
  Sd_EventHandlerTcpIdxOfEventHandlerType EventHandlerTcpIdxOfEventHandler;  /**< the index of the 0:1 relation pointing to Sd_EventHandlerTcp */
  Sd_EventHandlerUdpIdxOfEventHandlerType EventHandlerUdpIdxOfEventHandler;  /**< the index of the 0:1 relation pointing to Sd_EventHandlerUdp */
  Sd_HandleIdOfEventHandlerType HandleIdOfEventHandler;  /**< Handle ID */
  Sd_MulticastThresholdOfEventHandlerType MulticastThresholdOfEventHandler;  /**< Multicast threshold */
  Sd_ServerIdxOfEventHandlerType ServerIdxOfEventHandler;  /**< the index of the 1:1 relation pointing to Sd_Server */
  Sd_ServerTimerIdxOfEventHandlerType ServerTimerIdxOfEventHandler;  /**< the index of the 1:1 relation pointing to Sd_ServerTimer */
  Sd_SoConActivationMapEndIdxOfEventHandlerType SoConActivationMapEndIdxOfEventHandler;  /**< the end index of the 0:n relation pointing to Sd_SoConActivationMap */
  Sd_SoConActivationMapStartIdxOfEventHandlerType SoConActivationMapStartIdxOfEventHandler;  /**< the start index of the 0:n relation pointing to Sd_SoConActivationMap */
} Sd_EventHandlerType;

/**   \brief  type used in Sd_EventHandlerDyn */
typedef struct sSd_EventHandlerDynType
{
  Sd_NrOfClientsOfEventHandlerDynType NrOfClientsOfEventHandlerDyn;  /**< Nr of subscribed clients */
  Sd_EventHandlerCurrentStateType RequestStateOfEventHandlerDyn;  /**< Request state */
  Sd_EventHandlerStateMachineType StateMachineOfEventHandlerDyn;  /**< State machine */
} Sd_EventHandlerDynType;

/**   \brief  type used in Sd_EventHandlerMulticast */
/*! \spec weak type invariant () { 
 * (!((self.RoutingGroupActRefIdxOfEventHandlerMulticast != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERMULTICAST)) || (self.RoutingGroupActRefIdxOfEventHandlerMulticast < Sd_GetSizeOfRoutingGroup()))
 * } */
typedef struct sSd_EventHandlerMulticastType
{
  Sd_RoutingGroupActRefIdxOfEventHandlerMulticastType RoutingGroupActRefIdxOfEventHandlerMulticast;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
  SoAd_SoConIdType SoConIdOfEventHandlerMulticast;  /**< SocketConnection used for multicast transmittsion */
} Sd_EventHandlerMulticastType;

/**   \brief  type used in Sd_EventHandlerTcp */
/*! \spec weak type invariant () { 
 * (!((self.RoutingGroupActRefIdxOfEventHandlerTcp != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERTCP)) || (self.RoutingGroupActRefIdxOfEventHandlerTcp < Sd_GetSizeOfRoutingGroup())) &&
 * (!((self.RoutingGroupTriggerIdxOfEventHandlerTcp != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERTCP)) || (self.RoutingGroupTriggerIdxOfEventHandlerTcp < Sd_GetSizeOfRoutingGroup()))
 * } */
typedef struct sSd_EventHandlerTcpType
{
  Sd_RoutingGroupActRefIdxOfEventHandlerTcpType RoutingGroupActRefIdxOfEventHandlerTcp;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
  Sd_RoutingGroupTriggerIdxOfEventHandlerTcpType RoutingGroupTriggerIdxOfEventHandlerTcp;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
} Sd_EventHandlerTcpType;

/**   \brief  type used in Sd_EventHandlerUdp */
/*! \spec weak type invariant () { 
 * (!((self.RoutingGroupActRefIdxOfEventHandlerUdp != SD_NO_ROUTINGGROUPACTREFIDXOFEVENTHANDLERUDP)) || (self.RoutingGroupActRefIdxOfEventHandlerUdp < Sd_GetSizeOfRoutingGroup())) &&
 * (!((self.RoutingGroupTriggerIdxOfEventHandlerUdp != SD_NO_ROUTINGGROUPTRIGGERIDXOFEVENTHANDLERUDP)) || (self.RoutingGroupTriggerIdxOfEventHandlerUdp < Sd_GetSizeOfRoutingGroup()))
 * } */
typedef struct sSd_EventHandlerUdpType
{
  Sd_RoutingGroupActRefIdxOfEventHandlerUdpType RoutingGroupActRefIdxOfEventHandlerUdp;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
  Sd_RoutingGroupTriggerIdxOfEventHandlerUdpType RoutingGroupTriggerIdxOfEventHandlerUdp;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
} Sd_EventHandlerUdpType;

/**   \brief  type used in Sd_Instance */
/*! \spec weak type invariant () { 
 * (self.AddressStorageStartIdxOfInstance < Sd_GetSizeOfAddressStorage()) &&
 * (self.AddressStorageEndIdxOfInstance < Sd_GetSizeOfAddressStorage()) &&
 * (self.EndpointStorageStartIdxOfInstance < Sd_GetSizeOfEndpointStorage()) &&
 * (self.EndpointStorageEndIdxOfInstance < Sd_GetSizeOfEndpointStorage()) &&
 * (self.SendEntryStartIdxOfInstance < Sd_GetSizeOfSendEntry()) &&
 * (self.SendEntryEndIdxOfInstance < Sd_GetSizeOfSendEntry()) &&
 * (!((self.ServerStartIdxOfInstance != SD_NO_SERVERSTARTIDXOFINSTANCE)) || (self.ServerStartIdxOfInstance < Sd_GetSizeOfServer())) &&
 * (!((self.ServerStartIdxOfInstance != SD_NO_SERVERSTARTIDXOFINSTANCE)) || (self.ServerEndIdxOfInstance < Sd_GetSizeOfServer())) &&
 * (!((self.ClientStartIdxOfInstance != SD_NO_CLIENTSTARTIDXOFINSTANCE)) || (self.ClientStartIdxOfInstance < Sd_GetSizeOfClient())) &&
 * (!((self.ClientStartIdxOfInstance != SD_NO_CLIENTSTARTIDXOFINSTANCE)) || (self.ClientEndIdxOfInstance < Sd_GetSizeOfClient())) &&
 * (!((self.CapabilityRecordStartIdxOfInstance != SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE)) || (self.CapabilityRecordStartIdxOfInstance < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.CapabilityRecordStartIdxOfInstance != SD_NO_CAPABILITYRECORDSTARTIDXOFINSTANCE)) || (self.CapabilityRecordEndIdxOfInstance < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.RxEventStartIdxOfInstance != SD_NO_RXEVENTSTARTIDXOFINSTANCE)) || (self.RxEventStartIdxOfInstance < Sd_GetSizeOfRxEvent())) &&
 * (!((self.RxEventStartIdxOfInstance != SD_NO_RXEVENTSTARTIDXOFINSTANCE)) || (self.RxEventEndIdxOfInstance < Sd_GetSizeOfRxEvent())) &&
 * (!((self.UdpSoConStartIdxOfInstance != SD_NO_UDPSOCONSTARTIDXOFINSTANCE)) || (self.UdpSoConStartIdxOfInstance < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.UdpSoConStartIdxOfInstance != SD_NO_UDPSOCONSTARTIDXOFINSTANCE)) || (self.UdpSoConEndIdxOfInstance < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.TcpSoConIdStartIdxOfInstance != SD_NO_TCPSOCONIDSTARTIDXOFINSTANCE)) || (self.TcpSoConIdStartIdxOfInstance < Sd_GetSizeOfTcpSoConId())) &&
 * (!((self.TcpSoConIdStartIdxOfInstance != SD_NO_TCPSOCONIDSTARTIDXOFINSTANCE)) || (self.TcpSoConIdEndIdxOfInstance < Sd_GetSizeOfTcpSoConId()))
 * } */
typedef struct sSd_InstanceType
{
  Sd_MulticastRxPduIdOfInstanceType MulticastRxPduIdOfInstance;  /**< RX PDU ID used for multicast reception */
  Sd_TxPduIdOfInstanceType TxPduIdOfInstance;  /**< TX PDU ID used for message transmission */
  Sd_UnicastRxPduIdOfInstanceType UnicastRxPduIdOfInstance;  /**< RX PDU ID used for unicast reception */
  Sd_AddressStorageEndIdxOfInstanceType AddressStorageEndIdxOfInstance;  /**< the end index of the 1:n relation pointing to Sd_AddressStorage */
  Sd_AddressStorageStartIdxOfInstanceType AddressStorageStartIdxOfInstance;  /**< the start index of the 1:n relation pointing to Sd_AddressStorage */
  Sd_CapabilityRecordEndIdxOfInstanceType CapabilityRecordEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_CapabilityRecordStartIdxOfInstanceType CapabilityRecordStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_ClientEndIdxOfInstanceType ClientEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_Client */
  Sd_ClientStartIdxOfInstanceType ClientStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_Client */
  Sd_EndpointStorageEndIdxOfInstanceType EndpointStorageEndIdxOfInstance;  /**< the end index of the 1:n relation pointing to Sd_EndpointStorage */
  Sd_EndpointStorageStartIdxOfInstanceType EndpointStorageStartIdxOfInstance;  /**< the start index of the 1:n relation pointing to Sd_EndpointStorage */
  Sd_QueueProcessLimitOfInstanceType QueueProcessLimitOfInstance;  /**< Maximum number of Rx Queue Entries which shall be processed during one MainFunction cycle. */
  Sd_RetryDelayOfInstanceType RetryDelayOfInstance;  /**< Delay when a not answered subscription will be retriggered. */
  Sd_RetryMaxOfInstanceType RetryMaxOfInstance;  /**< Maximum count of subscription retries. */
  Sd_RxEventEndIdxOfInstanceType RxEventEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_RxEvent */
  Sd_RxEventStartIdxOfInstanceType RxEventStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_RxEvent */
  Sd_SendEntryEndIdxOfInstanceType SendEntryEndIdxOfInstance;  /**< the end index of the 1:n relation pointing to Sd_SendEntry */
  Sd_SendEntryStartIdxOfInstanceType SendEntryStartIdxOfInstance;  /**< the start index of the 1:n relation pointing to Sd_SendEntry */
  Sd_ServerEndIdxOfInstanceType ServerEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_Server */
  Sd_ServerStartIdxOfInstanceType ServerStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_Server */
  Sd_TcpSoConIdEndIdxOfInstanceType TcpSoConIdEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_TcpSoConIdStartIdxOfInstanceType TcpSoConIdStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_UdpSoConEndIdxOfInstanceType UdpSoConEndIdxOfInstance;  /**< the end index of the 0:n relation pointing to Sd_UdpSoCon */
  Sd_UdpSoConStartIdxOfInstanceType UdpSoConStartIdxOfInstance;  /**< the start index of the 0:n relation pointing to Sd_UdpSoCon */
  Sd_Dem_EventIdType EMalformedMsgIdOfInstance;  /**< DEM Event ID for malformed messages */
  Sd_Dem_EventIdType ENackRecvIdOfInstance;  /**< DEM Event ID for received SubscribeEventgroupNack messages */
  Sd_Dem_EventIdType EOutOfResIdOfInstance;  /**< DEM Event ID for too few available resources */
  SoAd_SoConIdType MulticastRxSoConIdOfInstance;  /**< RX SocketConnection ID used for multicast reception */
  SoAd_SoConIdType TxSoConIdOfInstance;  /**< TX SocketConnection ID used for message transmission */
  SoAd_SoConIdType UnicastRxSoConIdOfInstance;  /**< RX SocketConnection ID used for unicast reception */
} Sd_InstanceType;

/**   \brief  type used in Sd_InstanceDyn */
typedef struct sSd_InstanceDynType
{
  Sd_RxEventEndIdxOfInstanceDynType RxEventEndIdxOfInstanceDyn;  /**< the index of the 1:1 relation pointing to Sd_RxEvent */
  Sd_RxEventListFullOfInstanceDynType RxEventListFullOfInstanceDyn;  /**< Full flag of dynamic queue */
  Sd_RxEventStartIdxOfInstanceDynType RxEventStartIdxOfInstanceDyn;  /**< the index of the 1:1 relation pointing to Sd_RxEvent */
  Sd_SendEntryEndIdxOfInstanceDynType SendEntryEndIdxOfInstanceDyn;  /**< the index of the 0:1 relation pointing to Sd_SendEntry */
  Sd_SendEntryNrPendingIdxOfInstanceDynType SendEntryNrPendingIdxOfInstanceDyn;  /**< the index of the 1:1 relation pointing to Sd_SendEntry */
  Sd_SendEntryStartIdxOfInstanceDynType SendEntryStartIdxOfInstanceDyn;  /**< the index of the 0:1 relation pointing to Sd_SendEntry */
  Sd_ExtendedTimeType NextStateMachineRunOfInstanceDyn;  /**< Time indicating next execution of state machines */
  Sd_RunModeType RunModeOfInstanceDyn;  /**< Communication mode */
  Sd_ServiceInstanceStateType StateOfInstanceDyn;  /**< State */
} Sd_InstanceDynType;

/**   \brief  type used in Sd_IpAddrRequest */
/*! \spec weak type invariant () { 
 * (self.RequestCntIdxOfIpAddrRequest < Sd_GetSizeOfRequestCnt()) &&
 * (self.PortSetIdxOfIpAddrRequest < Sd_GetSizeOfPortSet())
 * } */
typedef struct sSd_IpAddrRequestType
{
  Sd_StaticIpConfigurationOfIpAddrRequestType StaticIpConfigurationOfIpAddrRequest;  /**< Indicates if a static IP address is configured */
  Sd_StaticPortConfigurationOfIpAddrRequestType StaticPortConfigurationOfIpAddrRequest;  /**< Indicates is a static port is configured */
  Sd_PortSetIdxOfIpAddrRequestType PortSetIdxOfIpAddrRequest;  /**< the index of the 1:1 relation pointing to Sd_PortSet */
  Sd_RequestCntIdxOfIpAddrRequestType RequestCntIdxOfIpAddrRequest;  /**< the index of the 1:1 relation pointing to Sd_RequestCnt */
  SoAd_SoConIdType SoConIdOfIpAddrRequest;  /**< SocketConnection ID */
} Sd_IpAddrRequestType;

/**   \brief  type used in Sd_Method */
/*! \spec weak type invariant () { 
 * (!((self.RoutingGroupActRefIdxOfMethod != SD_NO_ROUTINGGROUPACTREFIDXOFMETHOD)) || (self.RoutingGroupActRefIdxOfMethod < Sd_GetSizeOfRoutingGroup()))
 * } */
typedef struct sSd_MethodType
{
  Sd_TcpConfiguredOfMethodType TcpConfiguredOfMethod;  /**< Indicates whether the method is configured for TCP */
  Sd_UdpConfiguredOfMethodType UdpConfiguredOfMethod;  /**< Indicates whether the method is configured for UDP */
  Sd_RoutingGroupActRefIdxOfMethodType RoutingGroupActRefIdxOfMethod;  /**< the index of the 0:1 relation pointing to Sd_RoutingGroup */
} Sd_MethodType;

/**   \brief  type used in Sd_RoutingGroupDyn */
typedef struct sSd_RoutingGroupDynType
{
  Sd_RoutingGroupStatusType StatusOfRoutingGroupDyn;  /**< Status (disabled/enabled/unknown) of RoutingGroup */
} Sd_RoutingGroupDynType;

/**   \brief  type used in Sd_RxEvent */
typedef struct sSd_RxEventType
{
  Sd_ClientListIdxOfRxEventType ClientListIdxOfRxEvent;  /**< the index of the 0:1 relation pointing to Sd_ClientList */
  Sd_EventHandlerIdxOfRxEventType EventHandlerIdxOfRxEvent;  /**< the index of the 0:1 relation pointing to Sd_EventHandler */
  Sd_ServerEventgroupEventType EventOfRxEvent;  /**< Received event */
} Sd_RxEventType;

/**   \brief  type used in Sd_SendEntry */
typedef struct sSd_SendEntryType
{
  Sd_EventHandlerIdOfSendEntryType EventHandlerIdOfSendEntry;  /**< EventHandler ID */
  Sd_InstanceIdOfSendEntryType InstanceIdOfSendEntry;  /**< Instance ID */
  Sd_ReservedFieldOfSendEntryType ReservedFieldOfSendEntry;  /**< Reserved Field */
  Sd_ServiceIdOfSendEntryType ServiceIdOfSendEntry;  /**< Service ID */
  Sd_AddressStorageIdxOfSendEntryType AddressStorageIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_AddressStorage */
  Sd_ClientIdxOfSendEntryType ClientIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_Client */
  Sd_ClientListIdxOfSendEntryType ClientListIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_ClientList */
  Sd_ConsumedEventgroupIdxOfSendEntryType ConsumedEventgroupIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_ConsumedEventgroup */
  Sd_EventHandlerIdxOfSendEntryType EventHandlerIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_EventHandler */
  Sd_InstanceIdxOfSendEntryType InstanceIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_Instance */
  Sd_MajorVersionOfSendEntryType MajorVersionOfSendEntry;  /**< Major Version */
  Sd_SendEntryNextIdxOfSendEntryType SendEntryNextIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_SendEntry */
  Sd_ServerIdxOfSendEntryType ServerIdxOfSendEntry;  /**< the index of the 0:1 relation pointing to Sd_Server */
  Sd_ValidOfSendEntryType ValidOfSendEntry;  /**< Flag indicating if the entry is valid */
  Sd_EntryType EntryTypeOfSendEntry;  /**< Type of entry */
  Sd_ExtendedTimeType TimeToSendOfSendEntry;  /**< Time when message shall be sent */
} Sd_SendEntryType;

/**   \brief  type used in Sd_Server */
/*! \spec weak type invariant () { 
 * (self.InstanceIdxOfServer < Sd_GetSizeOfInstance()) &&
 * (self.ServerTimerIdxOfServer < Sd_GetSizeOfServerTimer()) &&
 * (!((self.CapabilityRecordFunctionCalloutPtrIdxOfServer != SD_NO_CAPABILITYRECORDFUNCTIONCALLOUTPTRIDXOFSERVER)) || (self.CapabilityRecordFunctionCalloutPtrIdxOfServer < Sd_GetSizeOfCapabilityRecordFunctionCalloutPtr())) &&
 * (!((self.CapabilityRecordStartIdxOfServer != SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER)) || (self.CapabilityRecordStartIdxOfServer < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.CapabilityRecordStartIdxOfServer != SD_NO_CAPABILITYRECORDSTARTIDXOFSERVER)) || (self.CapabilityRecordEndIdxOfServer < Sd_GetSizeOfCapabilityRecord())) &&
 * (!((self.UdpSoConStartIdxOfServer != SD_NO_UDPSOCONSTARTIDXOFSERVER)) || (self.UdpSoConStartIdxOfServer < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.UdpSoConStartIdxOfServer != SD_NO_UDPSOCONSTARTIDXOFSERVER)) || (self.UdpSoConEndIdxOfServer < Sd_GetSizeOfUdpSoCon())) &&
 * (!((self.TcpSoConIdStartIdxOfServer != SD_NO_TCPSOCONIDSTARTIDXOFSERVER)) || (self.TcpSoConIdStartIdxOfServer < Sd_GetSizeOfTcpSoConId())) &&
 * (!((self.TcpSoConIdStartIdxOfServer != SD_NO_TCPSOCONIDSTARTIDXOFSERVER)) || (self.TcpSoConIdEndIdxOfServer < Sd_GetSizeOfTcpSoConId())) &&
 * (!((self.MethodIdxOfServer != SD_NO_METHODIDXOFSERVER)) || (self.MethodIdxOfServer < Sd_GetSizeOfMethod())) &&
 * (!((self.EventHandlerStartIdxOfServer != SD_NO_EVENTHANDLERSTARTIDXOFSERVER)) || (self.EventHandlerStartIdxOfServer < Sd_GetSizeOfEventHandler())) &&
 * (!((self.EventHandlerStartIdxOfServer != SD_NO_EVENTHANDLERSTARTIDXOFSERVER)) || (self.EventHandlerEndIdxOfServer < Sd_GetSizeOfEventHandler())) &&
 * (!((self.CommonInitialDelayIdxOfServer != SD_NO_COMMONINITIALDELAYIDXOFSERVER)) || (self.CommonInitialDelayIdxOfServer < Sd_GetSizeOfCommonInitialDelay()))
 * } */
typedef struct sSd_ServerType
{
  Sd_ServiceIdOfServerType ServiceIdOfServer;  /**< Service ID */
  Sd_AutoAvailableOfServerType AutoAvailableOfServer;  /**< Auto available flag */
  Sd_ServiceGroupMemberOfServerType ServiceGroupMemberOfServer;  /**< Specifies if service is member of a ServiceGroup. */
  Sd_CapabilityRecordEndIdxOfServerType CapabilityRecordEndIdxOfServer;  /**< the end index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_CapabilityRecordFunctionCalloutPtrIdxOfServerType CapabilityRecordFunctionCalloutPtrIdxOfServer;  /**< the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr */
  Sd_CapabilityRecordStartIdxOfServerType CapabilityRecordStartIdxOfServer;  /**< the start index of the 0:n relation pointing to Sd_CapabilityRecord */
  Sd_CommonInitialDelayIdxOfServerType CommonInitialDelayIdxOfServer;  /**< the index of the 0:1 relation pointing to Sd_CommonInitialDelay */
  Sd_EventHandlerEndIdxOfServerType EventHandlerEndIdxOfServer;  /**< the end index of the 0:n relation pointing to Sd_EventHandler */
  Sd_EventHandlerStartIdxOfServerType EventHandlerStartIdxOfServer;  /**< the start index of the 0:n relation pointing to Sd_EventHandler */
  Sd_HandleIdOfServerType HandleIdOfServer;  /**< Handle ID */
  Sd_InstanceIdOfServerType InstanceIdOfServer;  /**< Instance ID */
  Sd_InstanceIdxOfServerType InstanceIdxOfServer;  /**< the index of the 1:1 relation pointing to Sd_Instance */
  Sd_MajorVersionOfServerType MajorVersionOfServer;  /**< Major Version */
  Sd_MethodIdxOfServerType MethodIdxOfServer;  /**< the index of the 0:1 relation pointing to Sd_Method */
  Sd_MinorVersionOfServerType MinorVersionOfServer;  /**< Minor Version */
  Sd_ServerTimerIdxOfServerType ServerTimerIdxOfServer;  /**< the index of the 1:1 relation pointing to Sd_ServerTimer */
  Sd_TcpSoConIdEndIdxOfServerType TcpSoConIdEndIdxOfServer;  /**< the end index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_TcpSoConIdStartIdxOfServerType TcpSoConIdStartIdxOfServer;  /**< the start index of the 0:n relation pointing to Sd_TcpSoConId */
  Sd_UdpSoConEndIdxOfServerType UdpSoConEndIdxOfServer;  /**< the end index of the 0:n relation pointing to Sd_UdpSoCon */
  Sd_UdpSoConStartIdxOfServerType UdpSoConStartIdxOfServer;  /**< the start index of the 0:n relation pointing to Sd_UdpSoCon */
} Sd_ServerType;

/**   \brief  type used in Sd_ServerDyn */
typedef struct sSd_ServerDynType
{
  Sd_InitialOfferRepetitionRunOfServerDynType InitialOfferRepetitionRunOfServerDyn;  /**< Counting the number of repetition runs */
  Sd_ServiceGroupReqCounterOfServerDynType ServiceGroupReqCounterOfServerDyn;  /**< Server availability counter for ServiceGroup service API */
  Sd_StateMachineExecutionRequestedOfServerDynType StateMachineExecutionRequestedOfServerDyn;  /**< Flag if State machine shall be executed for this server */
  Sd_ServerStateMachineType StateMachineOfServerDyn;  /**< State machine */
  Sd_ServerServiceSetStateType StateSwcOfServerDyn;  /**< Requested state */
  Sd_ExtendedTimeType TimeToTriggerSendOfServerDyn;  /**< Point in time the next message will be transmitted */
} Sd_ServerDynType;

/**   \brief  type used in Sd_ServerMap */
/*! \spec weak type invariant () { 
 * (!((self.ServerIdxOfServerMap != SD_NO_SERVERIDXOFSERVERMAP)) || (self.ServerIdxOfServerMap < Sd_GetSizeOfServer()))
 * } */
typedef struct sSd_ServerMapType
{
  Sd_InvalidHndOfServerMapType InvalidHndOfServerMap;  /**< FALSE, if the handle of Sd_ServerMap is valid and can be used in the embedded code for further processing in the embedded code. */
  Sd_ServerIdxOfServerMapType ServerIdxOfServerMap;  /**< the index of the 0:1 relation pointing to Sd_Server */
} Sd_ServerMapType;

/**   \brief  type used in Sd_ServerTimer */
typedef struct sSd_ServerTimerType
{
  Sd_TTLOfServerTimerType TTLOfServerTimer;  /**< Time To Live */
  Sd_InitialOfferDelayMaxOfServerTimerType InitialOfferDelayMaxOfServerTimer;  /**< Initial maximal Offer delay */
  Sd_InitialOfferDelayMinOfServerTimerType InitialOfferDelayMinOfServerTimer;  /**< Initial minimal Offer delay */
  Sd_InitialOfferRepetitionBaseDelayOfServerTimerType InitialOfferRepetitionBaseDelayOfServerTimer;  /**< Base delay used for timing of OfferServices messages during repetition phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS. */
  Sd_InitialOfferRepetitionsMaxOfServerTimerType InitialOfferRepetitionsMaxOfServerTimer;  /**< Amount of OfferService messages transmitted during repetition phase */
  Sd_OfferCyclicDelayOfServerTimerType OfferCyclicDelayOfServerTimer;  /**< Delay used for cyclic transmission of OfferService messages. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS. */
  Sd_RequestResponseMaxDelayOfServerTimerType RequestResponseMaxDelayOfServerTimer;  /**< Maximal request-response delay */
  Sd_RequestResponseMinDelayOfServerTimerType RequestResponseMinDelayOfServerTimer;  /**< Minimal request-response delay */
} Sd_ServerTimerType;

/**   \brief  type used in Sd_ServiceGroup */
/*! \spec weak type invariant () { 
 * (self.ServiceGroupMemberStartIdxOfServiceGroup < Sd_GetSizeOfServiceGroupMember()) &&
 * (self.ServiceGroupMemberEndIdxOfServiceGroup < Sd_GetSizeOfServiceGroupMember())
 * } */
typedef struct sSd_ServiceGroupType
{
  Sd_ServiceGroupMemberEndIdxOfServiceGroupType ServiceGroupMemberEndIdxOfServiceGroup;  /**< the end index of the 1:n relation pointing to Sd_ServiceGroupMember */
  Sd_ServiceGroupMemberStartIdxOfServiceGroupType ServiceGroupMemberStartIdxOfServiceGroup;  /**< the start index of the 1:n relation pointing to Sd_ServiceGroupMember */
} Sd_ServiceGroupType;

/**   \brief  type used in Sd_ServiceGroupMap */
/*! \spec weak type invariant () { 
 * (!((self.ServiceGroupIdxOfServiceGroupMap != SD_NO_SERVICEGROUPIDXOFSERVICEGROUPMAP)) || (self.ServiceGroupIdxOfServiceGroupMap < Sd_GetSizeOfServiceGroup()))
 * } */
typedef struct sSd_ServiceGroupMapType
{
  Sd_InvalidHndOfServiceGroupMapType InvalidHndOfServiceGroupMap;  /**< FALSE, if the handle of Sd_ServiceGroupMap is valid and can be used in the embedded code for further processing in the embedded code. */
  Sd_ServiceGroupIdxOfServiceGroupMapType ServiceGroupIdxOfServiceGroupMap;  /**< the index of the 0:1 relation pointing to Sd_ServiceGroup */
} Sd_ServiceGroupMapType;

/**   \brief  type used in Sd_ServiceGroupMember */
/*! \spec weak type invariant () { 
 * (!((self.ServerIdxOfServiceGroupMember != SD_NO_SERVERIDXOFSERVICEGROUPMEMBER)) || (self.ServerIdxOfServiceGroupMember < Sd_GetSizeOfServer())) &&
 * (!((self.ClientIdxOfServiceGroupMember != SD_NO_CLIENTIDXOFSERVICEGROUPMEMBER)) || (self.ClientIdxOfServiceGroupMember < Sd_GetSizeOfClient()))
 * } */
typedef struct sSd_ServiceGroupMemberType
{
  Sd_ClientIdxOfServiceGroupMemberType ClientIdxOfServiceGroupMember;  /**< the index of the 0:1 relation pointing to Sd_Client */
  Sd_ServerIdxOfServiceGroupMemberType ServerIdxOfServiceGroupMember;  /**< the index of the 0:1 relation pointing to Sd_Server */
} Sd_ServiceGroupMemberType;

/**   \brief  type used in Sd_SoConActivationMap */
typedef struct sSd_SoConActivationMapType
{
  Sd_NrOfActivationsOfSoConActivationMapType NrOfActivationsOfSoConActivationMap;  /**< Nr of activations */
  SoAd_SoConIdType SoConIdOfSoConActivationMap;  /**< SocketConnection ID */
} Sd_SoConActivationMapType;

/**   \brief  type used in Sd_TriggerTransmit */
typedef struct sSd_TriggerTransmitType
{
  Sd_ClientListIdxOfTriggerTransmitType ClientListIdxOfTriggerTransmit;  /**< the index of the 0:1 relation pointing to Sd_ClientList */
  Sd_EventHandlerIdxOfTriggerTransmitType EventHandlerIdxOfTriggerTransmit;  /**< the index of the 0:1 relation pointing to Sd_EventHandler */
  Sd_TriggerTransmitStateType StateOfTriggerTransmit;  /**< State */
} Sd_TriggerTransmitType;

/**   \brief  type used in Sd_UdpSoCon */
typedef struct sSd_UdpSoConType
{
  Sd_PreconfiguredOfUdpSoConType PreconfiguredOfUdpSoCon;  /**< Specifies if SoCon is preconfigured with IP and Port or not */
  SoAd_SoConIdType IdOfUdpSoCon;  /**< IDs of UDP SocketConnections */
} Sd_UdpSoConType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCSymbolicStructTypes  Sd Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to Sd_AddressStorage */
typedef struct Sd_AddressStorageStructSTag
{
  Sd_AddressStorageType SdInstance_Vlan23[10];
} Sd_AddressStorageStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_ClientList */
typedef struct Sd_ClientListStructSTag
{
  Sd_ClientListType SdEventHandler_0xC3C0_FaultInfo[2];
  Sd_ClientListType SdEventHandler_0xC3C1_SenState[2];
  Sd_ClientListType SdEventHandler_0xC3C1_EcuState;
} Sd_ClientListStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_EndpointStorage */
typedef struct Sd_EndpointStorageStructSTag
{
  Sd_EndpointStorageType SdInstance_Vlan23[20];
} Sd_EndpointStorageStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_MulticastEndpointAddr */
typedef struct Sd_MulticastEndpointAddrStructSTag
{
  Sd_SockAddrContainerType SdConsumedEventGroup_0xC3CB_VechicleSpeed;
  Sd_SockAddrContainerType SdConsumedEventGroup_0xC3CD_VechicleInfo;
} Sd_MulticastEndpointAddrStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_PortSet */
typedef struct Sd_PortSetStructSTag
{
  Sd_PortSetType SCG_SD_UDP_Multicast_Rx_Any_40000;
} Sd_PortSetStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_RequestCnt */
typedef struct Sd_RequestCntStructSTag
{
  Sd_RequestCntType TcpIpLocalAddr_Multicast_Any_vlan23;
} Sd_RequestCntStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_RoutingGroupDyn */
typedef struct Sd_RoutingGroupDynStructSTag
{
  Sd_RoutingGroupDynType SoAdRoutingGroup_FaultInfo_AC;
  Sd_RoutingGroupDynType SoAdRoutingGroup_FaultInfo_AM;
  Sd_RoutingGroupDynType SoAdRoutingGroup_SenState_AC;
  Sd_RoutingGroupDynType SoAdRoutingGroup_SenState_AM;
  Sd_RoutingGroupDynType SoAdRoutingGroup_EcuState_AC;
  Sd_RoutingGroupDynType SoAdRoutingGroup_VechicleSpeed_AM;
  Sd_RoutingGroupDynType SoAdRoutingGroup_VechicleSpeed_AC;
  Sd_RoutingGroupDynType SoAdRoutingGroup_VechicleInfo_AM;
  Sd_RoutingGroupDynType SoAdRoutingGroup_VechicleInfo_AC;
  Sd_RoutingGroupDynType SoAdRoutingGroup_VechicleStatus_AC;
} Sd_RoutingGroupDynStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_RxEvent */
typedef struct Sd_RxEventStructSTag
{
  Sd_RxEventType SdInstance_Vlan23[32];
} Sd_RxEventStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_SendEntry */
typedef struct Sd_SendEntryStructSTag
{
  Sd_SendEntryType SdInstance_Vlan23[32];
} Sd_SendEntryStructSType;

/**   \brief  type to be used as symbolic data element access to Sd_SoConActivationMap */
typedef struct Sd_SoConActivationMapStructSTag
{
  Sd_SoConActivationMapType SdEventHandler_0xC3C0_FaultInfo[2];
  Sd_SoConActivationMapType SdEventHandler_0xC3C1_SenState[2];
  Sd_SoConActivationMapType SdEventHandler_0xC3C1_EcuState;
} Sd_SoConActivationMapStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCUnionIndexAndSymbolTypes  Sd Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access Sd_AddressStorage in an index and symbol based style. */
typedef union Sd_AddressStorageUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_AddressStorageType raw[10];
  Sd_AddressStorageStructSType str;
} Sd_AddressStorageUType;

/**   \brief  type to access Sd_ClientList in an index and symbol based style. */
typedef union Sd_ClientListUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_ClientListType raw[5];
  Sd_ClientListStructSType str;
} Sd_ClientListUType;

/**   \brief  type to access Sd_EndpointStorage in an index and symbol based style. */
typedef union Sd_EndpointStorageUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_EndpointStorageType raw[20];
  Sd_EndpointStorageStructSType str;
} Sd_EndpointStorageUType;

/**   \brief  type to access Sd_MulticastEndpointAddr in an index and symbol based style. */
typedef union Sd_MulticastEndpointAddrUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_SockAddrContainerType raw[2];
  Sd_MulticastEndpointAddrStructSType str;
} Sd_MulticastEndpointAddrUType;

/**   \brief  type to access Sd_PortSet in an index and symbol based style. */
typedef union Sd_PortSetUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_PortSetType raw[1];
  Sd_PortSetStructSType str;
} Sd_PortSetUType;

/**   \brief  type to access Sd_RequestCnt in an index and symbol based style. */
typedef union Sd_RequestCntUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_RequestCntType raw[1];
  Sd_RequestCntStructSType str;
} Sd_RequestCntUType;

/**   \brief  type to access Sd_RoutingGroupDyn in an index and symbol based style. */
typedef union Sd_RoutingGroupDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_RoutingGroupDynType raw[10];
  Sd_RoutingGroupDynStructSType str;
} Sd_RoutingGroupDynUType;

/**   \brief  type to access Sd_RxEvent in an index and symbol based style. */
typedef union Sd_RxEventUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_RxEventType raw[32];
  Sd_RxEventStructSType str;
} Sd_RxEventUType;

/**   \brief  type to access Sd_SendEntry in an index and symbol based style. */
typedef union Sd_SendEntryUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_SendEntryType raw[32];
  Sd_SendEntryStructSType str;
} Sd_SendEntryUType;

/**   \brief  type to access Sd_SoConActivationMap in an index and symbol based style. */
typedef union Sd_SoConActivationMapUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  Sd_SoConActivationMapType raw[5];
  Sd_SoConActivationMapStructSType str;
} Sd_SoConActivationMapUType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCRootPointerTypes  Sd Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to Sd_AddressStorage */
typedef P2VAR(Sd_AddressStorageType, TYPEDEF, SD_VAR_NOINIT) Sd_AddressStoragePtrType;

/**   \brief  type used to point to Sd_AddrOfAddressStorage */
typedef P2VAR(Sd_SockAddrContainerType, TYPEDEF, SD_VAR_NOINIT) Sd_AddrOfAddressStoragePtrType;

/**   \brief  type used to point to Sd_CapabilityRecord */
typedef P2CONST(Sd_CapabilityRecordType, TYPEDEF, SD_CONST) Sd_CapabilityRecordPtrType;

/**   \brief  type used to point to Sd_CapabilityRecordFunctionCalloutPtr */
typedef P2CONST(Sd_CapabilityRecordCalloutFunctionApiType, TYPEDEF, SD_CONST) Sd_CapabilityRecordFunctionCalloutPtrPtrType;

/**   \brief  type used to point to Sd_Client */
typedef P2CONST(Sd_ClientType, TYPEDEF, SD_CONST) Sd_ClientPtrType;

/**   \brief  type used to point to Sd_ClientDyn */
typedef P2VAR(Sd_ClientDynType, TYPEDEF, SD_VAR_NOINIT) Sd_ClientDynPtrType;

/**   \brief  type used to point to Sd_MethodTcpSoConIdOfClientDyn */
typedef P2VAR(SoAd_SoConIdType, TYPEDEF, SD_VAR_NOINIT) Sd_MethodTcpSoConIdOfClientDynPtrType;

/**   \brief  type used to point to Sd_MethodUdpSoConIdOfClientDyn */
typedef P2VAR(SoAd_SoConIdType, TYPEDEF, SD_VAR_NOINIT) Sd_MethodUdpSoConIdOfClientDynPtrType;

/**   \brief  type used to point to Sd_RetryTimerOfClientDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_RetryTimerOfClientDynPtrType;

/**   \brief  type used to point to Sd_ServerTcpEndpointAddrOfClientDyn */
typedef P2VAR(Sd_SockAddrContainerType, TYPEDEF, SD_VAR_NOINIT) Sd_ServerTcpEndpointAddrOfClientDynPtrType;

/**   \brief  type used to point to Sd_ServerUdpEndpointAddrOfClientDyn */
typedef P2VAR(Sd_SockAddrContainerType, TYPEDEF, SD_VAR_NOINIT) Sd_ServerUdpEndpointAddrOfClientDynPtrType;

/**   \brief  type used to point to Sd_TimeToTriggerSendOfClientDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_TimeToTriggerSendOfClientDynPtrType;

/**   \brief  type used to point to Sd_TimerTTLOfClientDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_TimerTTLOfClientDynPtrType;

/**   \brief  type used to point to Sd_ClientList */
typedef P2VAR(Sd_ClientListType, TYPEDEF, SD_VAR_NOINIT) Sd_ClientListPtrType;

/**   \brief  type used to point to Sd_RxReservedOfClientList */
typedef P2VAR(Sd_RxReservedOfClientListType, TYPEDEF, SD_VAR_NOINIT) Sd_RxReservedOfClientListPtrType;

/**   \brief  type used to point to Sd_SubscribedUntilOfClientList */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_SubscribedUntilOfClientListPtrType;

/**   \brief  type used to point to Sd_ClientMap */
typedef P2CONST(Sd_ClientMapType, TYPEDEF, SD_CONST) Sd_ClientMapPtrType;

/**   \brief  type used to point to Sd_ClientTimer */
typedef P2CONST(Sd_ClientTimerType, TYPEDEF, SD_CONST) Sd_ClientTimerPtrType;

/**   \brief  type used to point to Sd_CommonInitialDelay */
typedef P2VAR(Sd_CommonInitialDelayType, TYPEDEF, SD_VAR_NOINIT) Sd_CommonInitialDelayPtrType;

/**   \brief  type used to point to Sd_ConsumedEventgroup */
typedef P2CONST(Sd_ConsumedEventgroupType, TYPEDEF, SD_CONST) Sd_ConsumedEventgroupPtrType;

/**   \brief  type used to point to Sd_ConsumedEventgroupDyn */
typedef P2VAR(Sd_ConsumedEventgroupDynType, TYPEDEF, SD_VAR_NOINIT) Sd_ConsumedEventgroupDynPtrType;

/**   \brief  type used to point to Sd_TimerTTLOfConsumedEventgroupDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_TimerTTLOfConsumedEventgroupDynPtrType;

/**   \brief  type used to point to Sd_ConsumedEventgroupMap */
typedef P2CONST(Sd_ConsumedEventgroupMapType, TYPEDEF, SD_CONST) Sd_ConsumedEventgroupMapPtrType;

/**   \brief  type used to point to Sd_EndpointStorage */
typedef P2VAR(Sd_EndpointStorageType, TYPEDEF, SD_VAR_NOINIT) Sd_EndpointStoragePtrType;

/**   \brief  type used to point to Sd_AddrOfEndpointStorage */
typedef P2VAR(Sd_SockAddrContainerType, TYPEDEF, SD_VAR_NOINIT) Sd_AddrOfEndpointStoragePtrType;

/**   \brief  type used to point to Sd_EventHandler */
typedef P2CONST(Sd_EventHandlerType, TYPEDEF, SD_CONST) Sd_EventHandlerPtrType;

/**   \brief  type used to point to Sd_EventHandlerDyn */
typedef P2VAR(Sd_EventHandlerDynType, TYPEDEF, SD_VAR_NOINIT) Sd_EventHandlerDynPtrType;

/**   \brief  type used to point to Sd_EventHandlerMulticast */
typedef P2CONST(Sd_EventHandlerMulticastType, TYPEDEF, SD_CONST) Sd_EventHandlerMulticastPtrType;

/**   \brief  type used to point to Sd_EventHandlerTcp */
typedef P2CONST(Sd_EventHandlerTcpType, TYPEDEF, SD_CONST) Sd_EventHandlerTcpPtrType;

/**   \brief  type used to point to Sd_EventHandlerUdp */
typedef P2CONST(Sd_EventHandlerUdpType, TYPEDEF, SD_CONST) Sd_EventHandlerUdpPtrType;

/**   \brief  type used to point to Sd_Instance */
typedef P2CONST(Sd_InstanceType, TYPEDEF, SD_CONST) Sd_InstancePtrType;

/**   \brief  type used to point to Sd_InstanceDyn */
typedef P2VAR(Sd_InstanceDynType, TYPEDEF, SD_VAR_NOINIT) Sd_InstanceDynPtrType;

/**   \brief  type used to point to Sd_NextStateMachineRunOfInstanceDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_NextStateMachineRunOfInstanceDynPtrType;

/**   \brief  type used to point to Sd_IpAddrRequest */
typedef P2CONST(Sd_IpAddrRequestType, TYPEDEF, SD_CONST) Sd_IpAddrRequestPtrType;

/**   \brief  type used to point to Sd_Method */
typedef P2CONST(Sd_MethodType, TYPEDEF, SD_CONST) Sd_MethodPtrType;

/**   \brief  type used to point to Sd_MulticastEndpointAddr */
typedef P2VAR(Sd_SockAddrContainerType, TYPEDEF, SD_VAR_NOINIT) Sd_MulticastEndpointAddrPtrType;

/**   \brief  type used to point to Sd_MulticastSoConId */
typedef P2CONST(SoAd_SoConIdType, TYPEDEF, SD_CONST) Sd_MulticastSoConIdPtrType;

/**   \brief  type used to point to Sd_NrOfOptions */
typedef P2VAR(Sd_NrOfOptionsType, TYPEDEF, SD_VAR_NOINIT) Sd_NrOfOptionsPtrType;

/**   \brief  type used to point to Sd_OptionIndex */
typedef P2VAR(Sd_OptionIndexType, TYPEDEF, SD_VAR_NOINIT) Sd_OptionIndexPtrType;

/**   \brief  type used to point to Sd_Payload */
typedef P2VAR(Sd_PayloadType, TYPEDEF, SD_VAR_NOINIT) Sd_PayloadPtrType;

/**   \brief  type used to point to Sd_PortSet */
typedef P2VAR(Sd_PortSetType, TYPEDEF, SD_VAR_NOINIT) Sd_PortSetPtrType;

/**   \brief  type used to point to Sd_RequestCnt */
typedef P2VAR(Sd_RequestCntType, TYPEDEF, SD_VAR_NOINIT) Sd_RequestCntPtrType;

/**   \brief  type used to point to Sd_RoutingGroup */
typedef P2CONST(SoAd_RoutingGroupIdType, TYPEDEF, SD_CONST) Sd_RoutingGroupPtrType;

/**   \brief  type used to point to Sd_RoutingGroupDyn */
typedef P2VAR(Sd_RoutingGroupDynType, TYPEDEF, SD_VAR_NOINIT) Sd_RoutingGroupDynPtrType;

/**   \brief  type used to point to Sd_RxEvent */
typedef P2VAR(Sd_RxEventType, TYPEDEF, SD_VAR_NOINIT) Sd_RxEventPtrType;

/**   \brief  type used to point to Sd_SendEntry */
typedef P2VAR(Sd_SendEntryType, TYPEDEF, SD_VAR_NOINIT) Sd_SendEntryPtrType;

/**   \brief  type used to point to Sd_TimeToSendOfSendEntry */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_TimeToSendOfSendEntryPtrType;

/**   \brief  type used to point to Sd_Server */
typedef P2CONST(Sd_ServerType, TYPEDEF, SD_CONST) Sd_ServerPtrType;

/**   \brief  type used to point to Sd_ServerDyn */
typedef P2VAR(Sd_ServerDynType, TYPEDEF, SD_VAR_NOINIT) Sd_ServerDynPtrType;

/**   \brief  type used to point to Sd_TimeToTriggerSendOfServerDyn */
typedef P2VAR(Sd_ExtendedTimeType, TYPEDEF, SD_VAR_NOINIT) Sd_TimeToTriggerSendOfServerDynPtrType;

/**   \brief  type used to point to Sd_ServerMap */
typedef P2CONST(Sd_ServerMapType, TYPEDEF, SD_CONST) Sd_ServerMapPtrType;

/**   \brief  type used to point to Sd_ServerTimer */
typedef P2CONST(Sd_ServerTimerType, TYPEDEF, SD_CONST) Sd_ServerTimerPtrType;

/**   \brief  type used to point to Sd_ServiceGroup */
typedef P2CONST(Sd_ServiceGroupType, TYPEDEF, SD_CONST) Sd_ServiceGroupPtrType;

/**   \brief  type used to point to Sd_ServiceGroupMap */
typedef P2CONST(Sd_ServiceGroupMapType, TYPEDEF, SD_CONST) Sd_ServiceGroupMapPtrType;

/**   \brief  type used to point to Sd_ServiceGroupMember */
typedef P2CONST(Sd_ServiceGroupMemberType, TYPEDEF, SD_CONST) Sd_ServiceGroupMemberPtrType;

/**   \brief  type used to point to Sd_SoConActivationMap */
typedef P2VAR(Sd_SoConActivationMapType, TYPEDEF, SD_VAR_NOINIT) Sd_SoConActivationMapPtrType;

/**   \brief  type used to point to Sd_TcpSoConId */
typedef P2CONST(SoAd_SoConIdType, TYPEDEF, SD_CONST) Sd_TcpSoConIdPtrType;

/**   \brief  type used to point to Sd_TcpSoConModeMap */
typedef P2VAR(Sd_SoConModeType, TYPEDEF, SD_VAR_NOINIT) Sd_TcpSoConModeMapPtrType;

/**   \brief  type used to point to Sd_TriggerTransmit */
typedef P2VAR(Sd_TriggerTransmitType, TYPEDEF, SD_VAR_NOINIT) Sd_TriggerTransmitPtrType;

/**   \brief  type used to point to Sd_TriggerTransmitEndIdx */
typedef P2VAR(Sd_TriggerTransmitEndIdxType, TYPEDEF, SD_VAR_NOINIT) Sd_TriggerTransmitEndIdxPtrType;

/**   \brief  type used to point to Sd_TriggerTransmitFull */
typedef P2VAR(Sd_TriggerTransmitFullType, TYPEDEF, SD_VAR_NOINIT) Sd_TriggerTransmitFullPtrType;

/**   \brief  type used to point to Sd_TriggerTransmitStartIdx */
typedef P2VAR(Sd_TriggerTransmitStartIdxType, TYPEDEF, SD_VAR_NOINIT) Sd_TriggerTransmitStartIdxPtrType;

/**   \brief  type used to point to Sd_UdpSoCon */
typedef P2CONST(Sd_UdpSoConType, TYPEDEF, SD_CONST) Sd_UdpSoConPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  SdPCRootValueTypes  Sd Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Sd_PCConfig */
typedef struct sSd_PCConfigType
{
  Sd_AddressStoragePtrType AddressStorageOfPCConfig;  /**< the pointer to Sd_AddressStorage */
  Sd_CapabilityRecordPtrType CapabilityRecordOfPCConfig;  /**< the pointer to Sd_CapabilityRecord */
  Sd_CapabilityRecordFunctionCalloutPtrPtrType CapabilityRecordFunctionCalloutPtrOfPCConfig;  /**< the pointer to Sd_CapabilityRecordFunctionCalloutPtr */
  Sd_ClientPtrType ClientOfPCConfig;  /**< the pointer to Sd_Client */
  Sd_ClientDynPtrType ClientDynOfPCConfig;  /**< the pointer to Sd_ClientDyn */
  Sd_ClientListPtrType ClientListOfPCConfig;  /**< the pointer to Sd_ClientList */
  Sd_ClientMapPtrType ClientMapOfPCConfig;  /**< the pointer to Sd_ClientMap */
  Sd_ClientTimerPtrType ClientTimerOfPCConfig;  /**< the pointer to Sd_ClientTimer */
  Sd_CommonInitialDelayPtrType CommonInitialDelayOfPCConfig;  /**< the pointer to Sd_CommonInitialDelay */
  Sd_ConsumedEventgroupPtrType ConsumedEventgroupOfPCConfig;  /**< the pointer to Sd_ConsumedEventgroup */
  Sd_ConsumedEventgroupDynPtrType ConsumedEventgroupDynOfPCConfig;  /**< the pointer to Sd_ConsumedEventgroupDyn */
  Sd_ConsumedEventgroupMapPtrType ConsumedEventgroupMapOfPCConfig;  /**< the pointer to Sd_ConsumedEventgroupMap */
  Sd_EndpointStoragePtrType EndpointStorageOfPCConfig;  /**< the pointer to Sd_EndpointStorage */
  Sd_EventHandlerPtrType EventHandlerOfPCConfig;  /**< the pointer to Sd_EventHandler */
  Sd_EventHandlerDynPtrType EventHandlerDynOfPCConfig;  /**< the pointer to Sd_EventHandlerDyn */
  Sd_EventHandlerMulticastPtrType EventHandlerMulticastOfPCConfig;  /**< the pointer to Sd_EventHandlerMulticast */
  Sd_EventHandlerTcpPtrType EventHandlerTcpOfPCConfig;  /**< the pointer to Sd_EventHandlerTcp */
  Sd_EventHandlerUdpPtrType EventHandlerUdpOfPCConfig;  /**< the pointer to Sd_EventHandlerUdp */
  Sd_InstancePtrType InstanceOfPCConfig;  /**< the pointer to Sd_Instance */
  Sd_InstanceDynPtrType InstanceDynOfPCConfig;  /**< the pointer to Sd_InstanceDyn */
  Sd_IpAddrRequestPtrType IpAddrRequestOfPCConfig;  /**< the pointer to Sd_IpAddrRequest */
  Sd_MethodPtrType MethodOfPCConfig;  /**< the pointer to Sd_Method */
  Sd_MulticastEndpointAddrPtrType MulticastEndpointAddrOfPCConfig;  /**< the pointer to Sd_MulticastEndpointAddr */
  Sd_MulticastSoConIdPtrType MulticastSoConIdOfPCConfig;  /**< the pointer to Sd_MulticastSoConId */
  Sd_NrOfOptionsPtrType NrOfOptionsOfPCConfig;  /**< the pointer to Sd_NrOfOptions */
  Sd_OptionIndexPtrType OptionIndexOfPCConfig;  /**< the pointer to Sd_OptionIndex */
  Sd_PayloadPtrType PayloadOfPCConfig;  /**< the pointer to Sd_Payload */
  Sd_PortSetPtrType PortSetOfPCConfig;  /**< the pointer to Sd_PortSet */
  Sd_RequestCntPtrType RequestCntOfPCConfig;  /**< the pointer to Sd_RequestCnt */
  Sd_RoutingGroupPtrType RoutingGroupOfPCConfig;  /**< the pointer to Sd_RoutingGroup */
  Sd_RoutingGroupDynPtrType RoutingGroupDynOfPCConfig;  /**< the pointer to Sd_RoutingGroupDyn */
  Sd_RxEventPtrType RxEventOfPCConfig;  /**< the pointer to Sd_RxEvent */
  Sd_SendEntryPtrType SendEntryOfPCConfig;  /**< the pointer to Sd_SendEntry */
  Sd_ServerPtrType ServerOfPCConfig;  /**< the pointer to Sd_Server */
  Sd_ServerDynPtrType ServerDynOfPCConfig;  /**< the pointer to Sd_ServerDyn */
  Sd_ServerMapPtrType ServerMapOfPCConfig;  /**< the pointer to Sd_ServerMap */
  Sd_ServerTimerPtrType ServerTimerOfPCConfig;  /**< the pointer to Sd_ServerTimer */
  Sd_ServiceGroupPtrType ServiceGroupOfPCConfig;  /**< the pointer to Sd_ServiceGroup */
  Sd_ServiceGroupMapPtrType ServiceGroupMapOfPCConfig;  /**< the pointer to Sd_ServiceGroupMap */
  Sd_ServiceGroupMemberPtrType ServiceGroupMemberOfPCConfig;  /**< the pointer to Sd_ServiceGroupMember */
  Sd_SoConActivationMapPtrType SoConActivationMapOfPCConfig;  /**< the pointer to Sd_SoConActivationMap */
  Sd_TcpSoConIdPtrType TcpSoConIdOfPCConfig;  /**< the pointer to Sd_TcpSoConId */
  Sd_TcpSoConModeMapPtrType TcpSoConModeMapOfPCConfig;  /**< the pointer to Sd_TcpSoConModeMap */
  Sd_TriggerTransmitPtrType TriggerTransmitOfPCConfig;  /**< the pointer to Sd_TriggerTransmit */
  Sd_TriggerTransmitEndIdxPtrType TriggerTransmitEndIdxOfPCConfig;  /**< the pointer to Sd_TriggerTransmitEndIdx */
  Sd_TriggerTransmitFullPtrType TriggerTransmitFullOfPCConfig;  /**< the pointer to Sd_TriggerTransmitFull */
  Sd_TriggerTransmitStartIdxPtrType TriggerTransmitStartIdxOfPCConfig;  /**< the pointer to Sd_TriggerTransmitStartIdx */
  Sd_UdpSoConPtrType UdpSoConOfPCConfig;  /**< the pointer to Sd_UdpSoCon */
  Sd_SizeOfPayloadType SizeOfPayloadOfPCConfig;  /**< the number of accomplishable value elements in Sd_Payload */
  Sd_SizeOfAddressStorageType SizeOfAddressStorageOfPCConfig;  /**< the number of accomplishable value elements in Sd_AddressStorage */
  Sd_SizeOfCapabilityRecordType SizeOfCapabilityRecordOfPCConfig;  /**< the number of accomplishable value elements in Sd_CapabilityRecord */
  Sd_SizeOfCapabilityRecordFunctionCalloutPtrType SizeOfCapabilityRecordFunctionCalloutPtrOfPCConfig;  /**< the number of accomplishable value elements in Sd_CapabilityRecordFunctionCalloutPtr */
  Sd_SizeOfClientType SizeOfClientOfPCConfig;  /**< the number of accomplishable value elements in Sd_Client */
  Sd_SizeOfClientListType SizeOfClientListOfPCConfig;  /**< the number of accomplishable value elements in Sd_ClientList */
  Sd_SizeOfClientMapType SizeOfClientMapOfPCConfig;  /**< the number of accomplishable value elements in Sd_ClientMap */
  Sd_SizeOfClientTimerType SizeOfClientTimerOfPCConfig;  /**< the number of accomplishable value elements in Sd_ClientTimer */
  Sd_SizeOfCommonInitialDelayType SizeOfCommonInitialDelayOfPCConfig;  /**< the number of accomplishable value elements in Sd_CommonInitialDelay */
  Sd_SizeOfConsumedEventgroupType SizeOfConsumedEventgroupOfPCConfig;  /**< the number of accomplishable value elements in Sd_ConsumedEventgroup */
  Sd_SizeOfConsumedEventgroupMapType SizeOfConsumedEventgroupMapOfPCConfig;  /**< the number of accomplishable value elements in Sd_ConsumedEventgroupMap */
  Sd_SizeOfEndpointStorageType SizeOfEndpointStorageOfPCConfig;  /**< the number of accomplishable value elements in Sd_EndpointStorage */
  Sd_SizeOfEventHandlerType SizeOfEventHandlerOfPCConfig;  /**< the number of accomplishable value elements in Sd_EventHandler */
  Sd_SizeOfEventHandlerMulticastType SizeOfEventHandlerMulticastOfPCConfig;  /**< the number of accomplishable value elements in Sd_EventHandlerMulticast */
  Sd_SizeOfEventHandlerTcpType SizeOfEventHandlerTcpOfPCConfig;  /**< the number of accomplishable value elements in Sd_EventHandlerTcp */
  Sd_SizeOfEventHandlerUdpType SizeOfEventHandlerUdpOfPCConfig;  /**< the number of accomplishable value elements in Sd_EventHandlerUdp */
  Sd_SizeOfInstanceType SizeOfInstanceOfPCConfig;  /**< the number of accomplishable value elements in Sd_Instance */
  Sd_SizeOfIpAddrRequestType SizeOfIpAddrRequestOfPCConfig;  /**< the number of accomplishable value elements in Sd_IpAddrRequest */
  Sd_SizeOfMethodType SizeOfMethodOfPCConfig;  /**< the number of accomplishable value elements in Sd_Method */
  Sd_SizeOfMulticastEndpointAddrType SizeOfMulticastEndpointAddrOfPCConfig;  /**< the number of accomplishable value elements in Sd_MulticastEndpointAddr */
  Sd_SizeOfMulticastSoConIdType SizeOfMulticastSoConIdOfPCConfig;  /**< the number of accomplishable value elements in Sd_MulticastSoConId */
  Sd_SizeOfOptionIndexType SizeOfOptionIndexOfPCConfig;  /**< the number of accomplishable value elements in Sd_OptionIndex */
  Sd_SizeOfPortSetType SizeOfPortSetOfPCConfig;  /**< the number of accomplishable value elements in Sd_PortSet */
  Sd_SizeOfRequestCntType SizeOfRequestCntOfPCConfig;  /**< the number of accomplishable value elements in Sd_RequestCnt */
  Sd_SizeOfRoutingGroupType SizeOfRoutingGroupOfPCConfig;  /**< the number of accomplishable value elements in Sd_RoutingGroup */
  Sd_SizeOfRxEventType SizeOfRxEventOfPCConfig;  /**< the number of accomplishable value elements in Sd_RxEvent */
  Sd_SizeOfSendEntryType SizeOfSendEntryOfPCConfig;  /**< the number of accomplishable value elements in Sd_SendEntry */
  Sd_SizeOfServerType SizeOfServerOfPCConfig;  /**< the number of accomplishable value elements in Sd_Server */
  Sd_SizeOfServerMapType SizeOfServerMapOfPCConfig;  /**< the number of accomplishable value elements in Sd_ServerMap */
  Sd_SizeOfServerTimerType SizeOfServerTimerOfPCConfig;  /**< the number of accomplishable value elements in Sd_ServerTimer */
  Sd_SizeOfServiceGroupType SizeOfServiceGroupOfPCConfig;  /**< the number of accomplishable value elements in Sd_ServiceGroup */
  Sd_SizeOfServiceGroupMapType SizeOfServiceGroupMapOfPCConfig;  /**< the number of accomplishable value elements in Sd_ServiceGroupMap */
  Sd_SizeOfServiceGroupMemberType SizeOfServiceGroupMemberOfPCConfig;  /**< the number of accomplishable value elements in Sd_ServiceGroupMember */
  Sd_SizeOfSoConActivationMapType SizeOfSoConActivationMapOfPCConfig;  /**< the number of accomplishable value elements in Sd_SoConActivationMap */
  Sd_SizeOfTcpSoConIdType SizeOfTcpSoConIdOfPCConfig;  /**< the number of accomplishable value elements in Sd_TcpSoConId */
  Sd_SizeOfTriggerTransmitType SizeOfTriggerTransmitOfPCConfig;  /**< the number of accomplishable value elements in Sd_TriggerTransmit */
  Sd_SizeOfUdpSoConType SizeOfUdpSoConOfPCConfig;  /**< the number of accomplishable value elements in Sd_UdpSoCon */
} Sd_PCConfigType;

typedef Sd_PCConfigType Sd_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access Sd_PCConfig in a symbol based style. */
typedef struct sSd_PCConfigsType
{
  Sd_PCConfigType Config;  /**< [Config] */
} Sd_PCConfigsType;

/** 
  \}
*/ 




typedef struct
{
  SD_P2CONST(PduInfoType)             PduInfoPtr;
  Sd_SizeOfAddressStorageType         AddressStorageIdx;
  boolean                             RebootDetected;
  boolean                             MulticastMessage;
} Sd_RxMessageInfoType;

/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  Sd_Client
**********************************************************************************************************************/
/** 
  \var    Sd_Client
  \brief  Configuration data of SdClientService. List is sorted by ServiceId (and HandleId if ServiceId is not unique) per SdInstance.
  \details
  Element                                  Description
  ServiceId                                Service ID
  AutoRequire                              Auto require flag
  MinorVersionWildcard                     Indicates if MinorVersion is configured to wildcard.
  ServiceGroupMember                       Specifies if service is member of a ServiceGroup.
  CapabilityRecordEndIdx                   the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtrIdx    the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr
  CapabilityRecordStartIdx                 the start index of the 0:n relation pointing to Sd_CapabilityRecord
  ClientTimerIdx                           the index of the 1:1 relation pointing to Sd_ClientTimer
  CommonInitialDelayIdx                    the index of the 0:1 relation pointing to Sd_CommonInitialDelay
  ConsumedEventgroupEndIdx                 the end index of the 0:n relation pointing to Sd_ConsumedEventgroup
  ConsumedEventgroupStartIdx               the start index of the 0:n relation pointing to Sd_ConsumedEventgroup
  HandleId                                 Handle ID
  InstanceId                               Instance ID
  InstanceIdx                              the index of the 1:1 relation pointing to Sd_Instance
  MajorVersion                             Major Version
  MethodIdx                                the index of the 0:1 relation pointing to Sd_Method
  MinorVersion                             Minor Version
  TcpSoConIdEndIdx                         the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx                       the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx                           the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx                         the start index of the 0:n relation pointing to Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ClientType, SD_CONST) Sd_Client[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientMap
**********************************************************************************************************************/
/** 
  \var    Sd_ClientMap
  \brief  Handle ID map for SdClientServices
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of Sd_ClientMap is valid and can be used in the embedded code for further processing in the embedded code.
  ClientIdx     the index of the 0:1 relation pointing to Sd_Client
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ClientMapType, SD_CONST) Sd_ClientMap[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientTimer
**********************************************************************************************************************/
/** 
  \var    Sd_ClientTimer
  \brief  Timer parameter for SdClientService and SdConsumedEventgroup
  \details
  Element                           Description
  TTL                               Time To Live
  InitialFindDelayMax               Maximal initial delay for FindService message
  InitialFindDelayMin               Minimal initial delay for FindService message
  InitialFindRepetitionBaseDelay    Base delay for FindService messages during initial find phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  InitialFindRepetitionsMax         Amount of FindService messages transmitted during initial find phase
  RequestResponseMaxDelay           Maximal request-response delay
  RequestResponseMinDelay           Minimal request-response delay
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ClientTimerType, SD_CONST) Sd_ClientTimer[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroup
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroup
  \brief  Configuration data of SdConsumedEventgroup
  \details
  Element                           Description
  AutoRequire                       Auto require flag
  ClientIdx                         the index of the 1:1 relation pointing to Sd_Client
  ClientTimerIdx                    the index of the 1:1 relation pointing to Sd_ClientTimer
  EventGroupId                      Eventgroup ID
  HandleId                          Handle ID
  MulticastEndpointAddrIdx          the index of the 0:1 relation pointing to Sd_MulticastEndpointAddr
  MulticastSoConIdEndIdx            the end index of the 0:n relation pointing to Sd_MulticastSoConId
  MulticastSoConIdStartIdx          the start index of the 0:n relation pointing to Sd_MulticastSoConId
  RoutingGroupMulticastActRefIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTcpActRefIdx          the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupUdpActRefIdx          the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ConsumedEventgroupType, SD_CONST) Sd_ConsumedEventgroup[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroupMap
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroupMap
  \brief  Handle ID map for SdConsumedEventgroups
  \details
  Element                  Description
  InvalidHnd               FALSE, if the handle of Sd_ConsumedEventgroupMap is valid and can be used in the embedded code for further processing in the embedded code.
  ConsumedEventgroupIdx    the index of the 0:1 relation pointing to Sd_ConsumedEventgroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ConsumedEventgroupMapType, SD_CONST) Sd_ConsumedEventgroupMap[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandler
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandler
  \brief  Configuration data of SdEventHandler
  \details
  Element                       Description
  ClientListEndIdx              the end index of the 1:n relation pointing to Sd_ClientList
  ClientListStartIdx            the start index of the 1:n relation pointing to Sd_ClientList
  EventGroupId                  Eventgroup ID
  EventHandlerMulticastIdx      the index of the 0:1 relation pointing to Sd_EventHandlerMulticast
  EventHandlerTcpIdx            the index of the 0:1 relation pointing to Sd_EventHandlerTcp
  EventHandlerUdpIdx            the index of the 0:1 relation pointing to Sd_EventHandlerUdp
  HandleId                      Handle ID
  MulticastThreshold            Multicast threshold
  ServerIdx                     the index of the 1:1 relation pointing to Sd_Server
  ServerTimerIdx                the index of the 1:1 relation pointing to Sd_ServerTimer
  SoConActivationMapEndIdx      the end index of the 0:n relation pointing to Sd_SoConActivationMap
  SoConActivationMapStartIdx    the start index of the 0:n relation pointing to Sd_SoConActivationMap
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_EventHandlerType, SD_CONST) Sd_EventHandler[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerMulticast
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerMulticast
  \brief  Configuration of SdEventHandlerMulticast
  \details
  Element                  Description
  RoutingGroupActRefIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
  SoConId                  SocketConnection used for multicast transmittsion
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_EventHandlerMulticastType, SD_CONST) Sd_EventHandlerMulticast[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerTcp
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerTcp
  \brief  Configuration of SdEventHandlerTcp
  \details
  Element                   Description
  RoutingGroupActRefIdx     the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTriggerIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_EventHandlerTcpType, SD_CONST) Sd_EventHandlerTcp[1];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerUdp
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerUdp
  \brief  Configuration of SdEventHandlerUdp
  \details
  Element                   Description
  RoutingGroupActRefIdx     the index of the 0:1 relation pointing to Sd_RoutingGroup
  RoutingGroupTriggerIdx    the index of the 0:1 relation pointing to Sd_RoutingGroup
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_EventHandlerUdpType, SD_CONST) Sd_EventHandlerUdp[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Instance
**********************************************************************************************************************/
/** 
  \var    Sd_Instance
  \brief  Configuration data for SdInstance
  \details
  Element                     Description
  MulticastRxPduId            RX PDU ID used for multicast reception
  TxPduId                     TX PDU ID used for message transmission
  UnicastRxPduId              RX PDU ID used for unicast reception
  AddressStorageEndIdx        the end index of the 1:n relation pointing to Sd_AddressStorage
  AddressStorageStartIdx      the start index of the 1:n relation pointing to Sd_AddressStorage
  CapabilityRecordEndIdx      the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordStartIdx    the start index of the 0:n relation pointing to Sd_CapabilityRecord
  ClientEndIdx                the end index of the 0:n relation pointing to Sd_Client
  ClientStartIdx              the start index of the 0:n relation pointing to Sd_Client
  EndpointStorageEndIdx       the end index of the 1:n relation pointing to Sd_EndpointStorage
  EndpointStorageStartIdx     the start index of the 1:n relation pointing to Sd_EndpointStorage
  QueueProcessLimit           Maximum number of Rx Queue Entries which shall be processed during one MainFunction cycle.
  RetryDelay                  Delay when a not answered subscription will be retriggered.
  RetryMax                    Maximum count of subscription retries.
  RxEventEndIdx               the end index of the 0:n relation pointing to Sd_RxEvent
  RxEventStartIdx             the start index of the 0:n relation pointing to Sd_RxEvent
  SendEntryEndIdx             the end index of the 1:n relation pointing to Sd_SendEntry
  SendEntryStartIdx           the start index of the 1:n relation pointing to Sd_SendEntry
  ServerEndIdx                the end index of the 0:n relation pointing to Sd_Server
  ServerStartIdx              the start index of the 0:n relation pointing to Sd_Server
  TcpSoConIdEndIdx            the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx          the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx              the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx            the start index of the 0:n relation pointing to Sd_UdpSoCon
  EMalformedMsgId             DEM Event ID for malformed messages
  ENackRecvId                 DEM Event ID for received SubscribeEventgroupNack messages
  EOutOfResId                 DEM Event ID for too few available resources
  MulticastRxSoConId          RX SocketConnection ID used for multicast reception
  TxSoConId                   TX SocketConnection ID used for message transmission
  UnicastRxSoConId            RX SocketConnection ID used for unicast reception
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_InstanceType, SD_CONST) Sd_Instance[1];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_IpAddrRequest
**********************************************************************************************************************/
/** 
  \var    Sd_IpAddrRequest
  \brief  Management structure for IP address requests of multicast IP addresses
  \details
  Element                    Description
  StaticIpConfiguration      Indicates if a static IP address is configured
  StaticPortConfiguration    Indicates is a static port is configured
  PortSetIdx                 the index of the 1:1 relation pointing to Sd_PortSet
  RequestCntIdx              the index of the 1:1 relation pointing to Sd_RequestCnt
  SoConId                    SocketConnection ID
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_IpAddrRequestType, SD_CONST) Sd_IpAddrRequest[1];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_MulticastSoConId
**********************************************************************************************************************/
/** 
  \var    Sd_MulticastSoConId
  \brief  SocketConnections used for multicast communication
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SoConIdType, SD_CONST) Sd_MulticastSoConId[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RoutingGroup
**********************************************************************************************************************/
/** 
  \var    Sd_RoutingGroup
  \brief  SoAd RoutingGroups relevant for SD
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_RoutingGroupIdType, SD_CONST) Sd_RoutingGroup[10];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Server
**********************************************************************************************************************/
/** 
  \var    Sd_Server
  \brief  Configuration data of SdServerService. List is sorted by ServiceId (and HandleId if ServiceId is not unique) per SdInstance.
  \details
  Element                                  Description
  ServiceId                                Service ID
  AutoAvailable                            Auto available flag
  ServiceGroupMember                       Specifies if service is member of a ServiceGroup.
  CapabilityRecordEndIdx                   the end index of the 0:n relation pointing to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtrIdx    the index of the 0:1 relation pointing to Sd_CapabilityRecordFunctionCalloutPtr
  CapabilityRecordStartIdx                 the start index of the 0:n relation pointing to Sd_CapabilityRecord
  CommonInitialDelayIdx                    the index of the 0:1 relation pointing to Sd_CommonInitialDelay
  EventHandlerEndIdx                       the end index of the 0:n relation pointing to Sd_EventHandler
  EventHandlerStartIdx                     the start index of the 0:n relation pointing to Sd_EventHandler
  HandleId                                 Handle ID
  InstanceId                               Instance ID
  InstanceIdx                              the index of the 1:1 relation pointing to Sd_Instance
  MajorVersion                             Major Version
  MethodIdx                                the index of the 0:1 relation pointing to Sd_Method
  MinorVersion                             Minor Version
  ServerTimerIdx                           the index of the 1:1 relation pointing to Sd_ServerTimer
  TcpSoConIdEndIdx                         the end index of the 0:n relation pointing to Sd_TcpSoConId
  TcpSoConIdStartIdx                       the start index of the 0:n relation pointing to Sd_TcpSoConId
  UdpSoConEndIdx                           the end index of the 0:n relation pointing to Sd_UdpSoCon
  UdpSoConStartIdx                         the start index of the 0:n relation pointing to Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ServerType, SD_CONST) Sd_Server[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerMap
**********************************************************************************************************************/
/** 
  \var    Sd_ServerMap
  \brief  Handle ID map for SdServerServices
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of Sd_ServerMap is valid and can be used in the embedded code for further processing in the embedded code.
  ServerIdx     the index of the 0:1 relation pointing to Sd_Server
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ServerMapType, SD_CONST) Sd_ServerMap[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerTimer
**********************************************************************************************************************/
/** 
  \var    Sd_ServerTimer
  \brief  Timer parameter for SdServerService and SdEventHandler
  \details
  Element                            Description
  TTL                                Time To Live
  InitialOfferDelayMax               Initial maximal Offer delay
  InitialOfferDelayMin               Initial minimal Offer delay
  InitialOfferRepetitionBaseDelay    Base delay used for timing of OfferServices messages during repetition phase. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  InitialOfferRepetitionsMax         Amount of OfferService messages transmitted during repetition phase
  OfferCyclicDelay                   Delay used for cyclic transmission of OfferService messages. Value is greater or equal SD_MAIN_FCT_CYCLE_TIME_MS.
  RequestResponseMaxDelay            Maximal request-response delay
  RequestResponseMinDelay            Minimal request-response delay
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_ServerTimerType, SD_CONST) Sd_ServerTimer[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TcpSoConId
**********************************************************************************************************************/
/** 
  \var    Sd_TcpSoConId
  \brief  Available TCP SocketConnections
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SoConIdType, SD_CONST) Sd_TcpSoConId[2];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_UdpSoCon
**********************************************************************************************************************/
/** 
  \var    Sd_UdpSoCon
  \brief  Available UDP SocketConnections
  \details
  Element          Description
  Preconfigured    Specifies if SoCon is preconfigured with IP and Port or not
  Id               IDs of UDP SocketConnections
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_UdpSoConType, SD_CONST) Sd_UdpSoCon[3];
#define SD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_AddressStorage
**********************************************************************************************************************/
/** 
  \var    Sd_AddressStorage
  \brief  State information of communication partner
  \details
  Element                  Description
  RxMulticastSessionId     RX multicast session ID
  RxUnicastSessionId       RX unicast session ID
  SessionIdCounter         TX session ID
  Flags                    TX flags
  RxMulticastFlags         RX multicast flags
  RxUnicastFlags           RX unicast flags
  SendEntryNrPendingIdx    the index of the 1:1 relation pointing to Sd_SendEntry
  Addr                     Address of the communication partner
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_AddressStorageUType, SD_VAR_NOINIT) Sd_AddressStorage;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ClientDyn
  \brief  Dynamic configuration data for SdClientService
  \details
  Element                           Description
  OfferedTTL                        Offered Time To Live
  AddressStorageServerIdx           the index of the 0:1 relation pointing to Sd_AddressStorage
  RepetitionRun                     Repetition run counter
  RetryCounter                      Counter for subscribe eventgroup retry handling.
  ServiceGroupReqCounter            Client request counter for ServiceGroup service API
  StateMachineExecutionRequested    Flag if State machine shall be executed for this client
  CurrentState                      Current state
  EventMain                         Event processed in MainFunction.
  EventRx                           Received event
  MethodTcpSoConId                  TCP method SoConId
  MethodUdpSoConId                  UDP method SoConId
  RetryTimer                        Timer for subscribe eventgroup retry handling.
  ServerTcpEndpointAddr             Server TCP endpoint address
  ServerUdpEndpointAddr             Server UDP endpoint address
  StateMachine                      State machine
  StateSwc                          Requested state
  TimeToTriggerSend                 Time to trigger next message transmission
  TimerTTL                          Time To Live
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_ClientDynType, SD_VAR_NOINIT) Sd_ClientDyn[3];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ClientList
**********************************************************************************************************************/
/** 
  \var    Sd_ClientList
  \brief  Dynamic data of subscribed clients
  \details
  Element                  Description
  RequestedTTL             Requested TimeToLive
  RxReserved               Received reserved field
  AddressStorageIdx        the index of the 0:1 relation pointing to Sd_AddressStorage
  EndpointStorageTcpIdx    the index of the 0:1 relation pointing to Sd_EndpointStorage
  EndpointStorageUdpIdx    the index of the 0:1 relation pointing to Sd_EndpointStorage
  NrOfReferences           Number of simultaneous subscriptions
  AssignedTcpSoConId       Used TCP SocketConnection ID
  AssignedUdpSoConId       Used UDP SocketConnection ID
  ClientState              State of the client
  SubscribedUntil          Point in time till the client is subscribed
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_ClientListUType, SD_VAR_NOINIT) Sd_ClientList;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ConsumedEventgroupDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ConsumedEventgroupDyn
  \brief  Dynamic configuration of SdConsumedEventgroup
  \details
  Element                  Description
  AcknowledgedTTL          Acknowledge Time To Live
  RxIndicationCount        Counter to differentiate RxIndication calls.
  SoConMarkedForClosure    Flag if EventGroup has been unconfigured and SoCon can be closed.
  TriggerSubscription      Flag indicating if a subscription shall be triggered.
  CurrentState             Current state
  Event                    Received event
  MulticastSoConId         Configured multicast SocketConnection
  ServiceModeRequest       Requested state
  StateMachine             State machine
  TcpSoConId               Configured TCP SocketConnection
  TimerTTL                 Time To Live
  UdpSoConId               Configured UDP SocketConnection
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_ConsumedEventgroupDynType, SD_VAR_NOINIT) Sd_ConsumedEventgroupDyn[3];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EndpointStorage
**********************************************************************************************************************/
/** 
  \var    Sd_EndpointStorage
  \brief  Received endpoint options
  \details
  Element           Description
  NrOfReferences    Number of external references
  Addr              Endpoint address
  Type              Endpoint type
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_EndpointStorageUType, SD_VAR_NOINIT) Sd_EndpointStorage;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_EventHandlerDyn
**********************************************************************************************************************/
/** 
  \var    Sd_EventHandlerDyn
  \brief  Dynamic configuration of SdEventHandler
  \details
  Element         Description
  NrOfClients     Nr of subscribed clients
  RequestState    Request state
  StateMachine    State machine
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_EventHandlerDynType, SD_VAR_NOINIT) Sd_EventHandlerDyn[3];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_InstanceDyn
**********************************************************************************************************************/
/** 
  \var    Sd_InstanceDyn
  \brief  Variable data for each SdInstance
  \details
  Element                  Description
  RxEventEndIdx            the index of the 1:1 relation pointing to Sd_RxEvent
  RxEventListFull          Full flag of dynamic queue
  RxEventStartIdx          the index of the 1:1 relation pointing to Sd_RxEvent
  SendEntryEndIdx          the index of the 0:1 relation pointing to Sd_SendEntry
  SendEntryNrPendingIdx    the index of the 1:1 relation pointing to Sd_SendEntry
  SendEntryStartIdx        the index of the 0:1 relation pointing to Sd_SendEntry
  NextStateMachineRun      Time indicating next execution of state machines
  RunMode                  Communication mode
  State                    State
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_InstanceDynType, SD_VAR_NOINIT) Sd_InstanceDyn[1];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_MulticastEndpointAddr
**********************************************************************************************************************/
/** 
  \var    Sd_MulticastEndpointAddr
  \brief  Server multicast endpoint address
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_MulticastEndpointAddrUType, SD_VAR_NOINIT) Sd_MulticastEndpointAddr;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_NrOfOptions
**********************************************************************************************************************/
/** 
  \var    Sd_NrOfOptions
  \brief  Number of options saved in the OptionIndex
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_NrOfOptionsType, SD_VAR_NOINIT) Sd_NrOfOptions;
#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_OptionIndex
**********************************************************************************************************************/
/** 
  \var    Sd_OptionIndex
  \brief  Payload offset of options
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_OptionIndexType, SD_VAR_NOINIT) Sd_OptionIndex[10];
#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_Payload
**********************************************************************************************************************/
/** 
  \var    Sd_Payload
  \brief  Buffer used for message transmission
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_PayloadType, SD_VAR_NOINIT) Sd_Payload[1464];
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_PortSet
**********************************************************************************************************************/
/** 
  \var    Sd_PortSet
  \brief  Indicates if the port is already set
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_PortSetUType, SD_VAR_NOINIT) Sd_PortSet;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RequestCnt
**********************************************************************************************************************/
/** 
  \var    Sd_RequestCnt
  \brief  Nr of IP address assignment requests
*/ 
#define SD_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_RequestCntUType, SD_VAR_NOINIT) Sd_RequestCnt;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RoutingGroupDyn
**********************************************************************************************************************/
/** 
  \var    Sd_RoutingGroupDyn
  \brief  Dynamic data of SoAd RoutingGroups relevant for SD
  \details
  Element    Description
  Status     Status (disabled/enabled/unknown) of RoutingGroup
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_RoutingGroupDynUType, SD_VAR_NOINIT) Sd_RoutingGroupDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_RxEvent
**********************************************************************************************************************/
/** 
  \var    Sd_RxEvent
  \brief  Saves received server events
  \details
  Element            Description
  ClientListIdx      the index of the 0:1 relation pointing to Sd_ClientList
  EventHandlerIdx    the index of the 0:1 relation pointing to Sd_EventHandler
  Event              Received event
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_RxEventUType, SD_VAR_NOINIT) Sd_RxEvent;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_SendEntry
**********************************************************************************************************************/
/** 
  \var    Sd_SendEntry
  \brief  Saves messages which shall be transmitted
  \details
  Element                  Description
  EventHandlerId           EventHandler ID
  InstanceId               Instance ID
  ReservedField            Reserved Field
  ServiceId                Service ID
  AddressStorageIdx        the index of the 0:1 relation pointing to Sd_AddressStorage
  ClientIdx                the index of the 0:1 relation pointing to Sd_Client
  ClientListIdx            the index of the 0:1 relation pointing to Sd_ClientList
  ConsumedEventgroupIdx    the index of the 0:1 relation pointing to Sd_ConsumedEventgroup
  EventHandlerIdx          the index of the 0:1 relation pointing to Sd_EventHandler
  InstanceIdx              the index of the 0:1 relation pointing to Sd_Instance
  MajorVersion             Major Version
  SendEntryNextIdx         the index of the 0:1 relation pointing to Sd_SendEntry
  ServerIdx                the index of the 0:1 relation pointing to Sd_Server
  Valid                    Flag indicating if the entry is valid
  EntryType                Type of entry
  TimeToSend               Time when message shall be sent
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_SendEntryUType, SD_VAR_NOINIT) Sd_SendEntry;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_ServerDyn
**********************************************************************************************************************/
/** 
  \var    Sd_ServerDyn
  \brief  Dynamic configuration data of SdServerService
  \details
  Element                           Description
  InitialOfferRepetitionRun         Counting the number of repetition runs
  ServiceGroupReqCounter            Server availability counter for ServiceGroup service API
  StateMachineExecutionRequested    Flag if State machine shall be executed for this server
  StateMachine                      State machine
  StateSwc                          Requested state
  TimeToTriggerSend                 Point in time the next message will be transmitted
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_ServerDynType, SD_VAR_NOINIT) Sd_ServerDyn[3];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_SoConActivationMap
**********************************************************************************************************************/
/** 
  \var    Sd_SoConActivationMap
  \brief  Configuration data of SocketConnections
  \details
  Element            Description
  NrOfActivations    Nr of activations
  SoConId            SocketConnection ID
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_SoConActivationMapUType, SD_VAR_NOINIT) Sd_SoConActivationMap;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TcpSoConModeMap
**********************************************************************************************************************/
/** 
  \var    Sd_TcpSoConModeMap
  \brief  Map to save the actual SocketConnection mode
*/ 
#define SD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_SoConModeType, SD_VAR_NOINIT) Sd_TcpSoConModeMap[2];
#define SD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitEndIdx
**********************************************************************************************************************/
/** 
  \var    Sd_TriggerTransmitEndIdx
  \brief  the index of the 1:1 relation pointing to Sd_TriggerTransmit
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_TriggerTransmitEndIdxType, SD_VAR_NOINIT) Sd_TriggerTransmitEndIdx;
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitFull
**********************************************************************************************************************/
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_TriggerTransmitFullType, SD_VAR_NOINIT) Sd_TriggerTransmitFull;
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_TriggerTransmitStartIdx
**********************************************************************************************************************/
/** 
  \var    Sd_TriggerTransmitStartIdx
  \brief  the index of the 1:1 relation pointing to Sd_TriggerTransmit
*/ 
#define SD_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(Sd_TriggerTransmitStartIdxType, SD_VAR_NOINIT) Sd_TriggerTransmitStartIdx;
#define SD_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Sd_PCConfig
**********************************************************************************************************************/
/** 
  \var    Sd_PCConfig
  \details
  Element                                     Description
  AddressStorage                              the pointer to Sd_AddressStorage
  CapabilityRecord                            the pointer to Sd_CapabilityRecord
  CapabilityRecordFunctionCalloutPtr          the pointer to Sd_CapabilityRecordFunctionCalloutPtr
  Client                                      the pointer to Sd_Client
  ClientDyn                                   the pointer to Sd_ClientDyn
  ClientList                                  the pointer to Sd_ClientList
  ClientMap                                   the pointer to Sd_ClientMap
  ClientTimer                                 the pointer to Sd_ClientTimer
  CommonInitialDelay                          the pointer to Sd_CommonInitialDelay
  ConsumedEventgroup                          the pointer to Sd_ConsumedEventgroup
  ConsumedEventgroupDyn                       the pointer to Sd_ConsumedEventgroupDyn
  ConsumedEventgroupMap                       the pointer to Sd_ConsumedEventgroupMap
  EndpointStorage                             the pointer to Sd_EndpointStorage
  EventHandler                                the pointer to Sd_EventHandler
  EventHandlerDyn                             the pointer to Sd_EventHandlerDyn
  EventHandlerMulticast                       the pointer to Sd_EventHandlerMulticast
  EventHandlerTcp                             the pointer to Sd_EventHandlerTcp
  EventHandlerUdp                             the pointer to Sd_EventHandlerUdp
  Instance                                    the pointer to Sd_Instance
  InstanceDyn                                 the pointer to Sd_InstanceDyn
  IpAddrRequest                               the pointer to Sd_IpAddrRequest
  Method                                      the pointer to Sd_Method
  MulticastEndpointAddr                       the pointer to Sd_MulticastEndpointAddr
  MulticastSoConId                            the pointer to Sd_MulticastSoConId
  NrOfOptions                                 the pointer to Sd_NrOfOptions
  OptionIndex                                 the pointer to Sd_OptionIndex
  Payload                                     the pointer to Sd_Payload
  PortSet                                     the pointer to Sd_PortSet
  RequestCnt                                  the pointer to Sd_RequestCnt
  RoutingGroup                                the pointer to Sd_RoutingGroup
  RoutingGroupDyn                             the pointer to Sd_RoutingGroupDyn
  RxEvent                                     the pointer to Sd_RxEvent
  SendEntry                                   the pointer to Sd_SendEntry
  Server                                      the pointer to Sd_Server
  ServerDyn                                   the pointer to Sd_ServerDyn
  ServerMap                                   the pointer to Sd_ServerMap
  ServerTimer                                 the pointer to Sd_ServerTimer
  ServiceGroup                                the pointer to Sd_ServiceGroup
  ServiceGroupMap                             the pointer to Sd_ServiceGroupMap
  ServiceGroupMember                          the pointer to Sd_ServiceGroupMember
  SoConActivationMap                          the pointer to Sd_SoConActivationMap
  TcpSoConId                                  the pointer to Sd_TcpSoConId
  TcpSoConModeMap                             the pointer to Sd_TcpSoConModeMap
  TriggerTransmit                             the pointer to Sd_TriggerTransmit
  TriggerTransmitEndIdx                       the pointer to Sd_TriggerTransmitEndIdx
  TriggerTransmitFull                         the pointer to Sd_TriggerTransmitFull
  TriggerTransmitStartIdx                     the pointer to Sd_TriggerTransmitStartIdx
  UdpSoCon                                    the pointer to Sd_UdpSoCon
  SizeOfPayload                               the number of accomplishable value elements in Sd_Payload
  SizeOfAddressStorage                        the number of accomplishable value elements in Sd_AddressStorage
  SizeOfCapabilityRecord                      the number of accomplishable value elements in Sd_CapabilityRecord
  SizeOfCapabilityRecordFunctionCalloutPtr    the number of accomplishable value elements in Sd_CapabilityRecordFunctionCalloutPtr
  SizeOfClient                                the number of accomplishable value elements in Sd_Client
  SizeOfClientList                            the number of accomplishable value elements in Sd_ClientList
  SizeOfClientMap                             the number of accomplishable value elements in Sd_ClientMap
  SizeOfClientTimer                           the number of accomplishable value elements in Sd_ClientTimer
  SizeOfCommonInitialDelay                    the number of accomplishable value elements in Sd_CommonInitialDelay
  SizeOfConsumedEventgroup                    the number of accomplishable value elements in Sd_ConsumedEventgroup
  SizeOfConsumedEventgroupMap                 the number of accomplishable value elements in Sd_ConsumedEventgroupMap
  SizeOfEndpointStorage                       the number of accomplishable value elements in Sd_EndpointStorage
  SizeOfEventHandler                          the number of accomplishable value elements in Sd_EventHandler
  SizeOfEventHandlerMulticast                 the number of accomplishable value elements in Sd_EventHandlerMulticast
  SizeOfEventHandlerTcp                       the number of accomplishable value elements in Sd_EventHandlerTcp
  SizeOfEventHandlerUdp                       the number of accomplishable value elements in Sd_EventHandlerUdp
  SizeOfInstance                              the number of accomplishable value elements in Sd_Instance
  SizeOfIpAddrRequest                         the number of accomplishable value elements in Sd_IpAddrRequest
  SizeOfMethod                                the number of accomplishable value elements in Sd_Method
  SizeOfMulticastEndpointAddr                 the number of accomplishable value elements in Sd_MulticastEndpointAddr
  SizeOfMulticastSoConId                      the number of accomplishable value elements in Sd_MulticastSoConId
  SizeOfOptionIndex                           the number of accomplishable value elements in Sd_OptionIndex
  SizeOfPortSet                               the number of accomplishable value elements in Sd_PortSet
  SizeOfRequestCnt                            the number of accomplishable value elements in Sd_RequestCnt
  SizeOfRoutingGroup                          the number of accomplishable value elements in Sd_RoutingGroup
  SizeOfRxEvent                               the number of accomplishable value elements in Sd_RxEvent
  SizeOfSendEntry                             the number of accomplishable value elements in Sd_SendEntry
  SizeOfServer                                the number of accomplishable value elements in Sd_Server
  SizeOfServerMap                             the number of accomplishable value elements in Sd_ServerMap
  SizeOfServerTimer                           the number of accomplishable value elements in Sd_ServerTimer
  SizeOfServiceGroup                          the number of accomplishable value elements in Sd_ServiceGroup
  SizeOfServiceGroupMap                       the number of accomplishable value elements in Sd_ServiceGroupMap
  SizeOfServiceGroupMember                    the number of accomplishable value elements in Sd_ServiceGroupMember
  SizeOfSoConActivationMap                    the number of accomplishable value elements in Sd_SoConActivationMap
  SizeOfTcpSoConId                            the number of accomplishable value elements in Sd_TcpSoConId
  SizeOfTriggerTransmit                       the number of accomplishable value elements in Sd_TriggerTransmit
  SizeOfUdpSoCon                              the number of accomplishable value elements in Sd_UdpSoCon
*/ 
#define SD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(Sd_PCConfigsType, SD_CONST) Sd_PCConfig;
#define SD_STOP_SEC_CONST_UNSPECIFIED
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


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTIONS
**********************************************************************************************************************/


#endif  /* SD_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Sd_Lcfg.h
 *********************************************************************************************************************/
