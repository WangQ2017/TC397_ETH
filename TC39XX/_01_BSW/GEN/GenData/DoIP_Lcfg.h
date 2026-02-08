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
 *            Module: DoIP
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: DoIP_Lcfg.h
 *   Generation Time: 2026-02-08 21:29:40
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined(DOIP_LCFG_H)
# define DOIP_LCFG_H

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "DoIP_Types.h"

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  DoIPPCDataSwitches  DoIP Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define DOIP_ALIVECHECKLIST                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPIDXOFALIVECHECKLIST                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNEL                                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_APITYPEOFCHANNEL                                                                       STD_OFF  /**< Deactivateable: 'DoIP_Channel.ApiType' Reason: 'IF API is disabled.' */
#define DOIP_BITMASKOFCHANNEL                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DEFAULTCHANNELOFCHANNEL                                                                STD_OFF  /**< Deactivateable: 'DoIP_Channel.DefaultChannel' Reason: 'PDU size dependent routing is disabled.' */
#define DOIP_ECUADDROFCHANNEL                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IFTXBUFENDIDXOFCHANNEL                                                                 STD_OFF  /**< Deactivateable: 'DoIP_Channel.IfTxBufEndIdx' Reason: 'IF API is disabled.' */
#define DOIP_IFTXBUFSTARTIDXOFCHANNEL                                                               STD_OFF  /**< Deactivateable: 'DoIP_Channel.IfTxBufStartIdx' Reason: 'IF API is disabled.' */
#define DOIP_IFTXBUFUSEDOFCHANNEL                                                                   STD_OFF  /**< Deactivateable: 'DoIP_Channel.IfTxBufUsed' Reason: 'IF API is disabled.' */
#define DOIP_MAXPDUSIZEOFCHANNEL                                                                    STD_OFF  /**< Deactivateable: 'DoIP_Channel.MaxPduSize' Reason: 'PDU size dependent routing is disabled.' */
#define DOIP_PDURRXPDUIDOFCHANNEL                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PDURTXCONFPDUIDOFCHANNEL                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERIDXOFCHANNEL                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPMAXLENOFCHANNEL                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELDYN                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXMSGLENOFCHANNELDYN                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELIND                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTION                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_LOCALADDRIDXOFCONNECTION                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXCANCELPDUIDOFCONNECTION                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SOADTXPDUIDOFCONNECTION                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONDYN                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRSTATEOFCONNECTIONDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SOCONCLOSINGOFCONNECTIONDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SOCONIDOFCONNECTIONDYN                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SOCONSTATEOFCONNECTIONDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONGROUP                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPINDENDIDXOFCONNECTIONGROUP                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPINDSTARTIDXOFCONNECTIONGROUP                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONIND                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCP                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONGROUPIDXOFCONNECTIONTCP                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXHDRBUFENDIDXOFCONNECTIONTCP                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXHDRBUFSTARTIDXOFCONNECTIONTCP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SECURITYREQUIREDOFCONNECTIONTCP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTENDIDXOFCONNECTIONTCP                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTSTARTIDXOFCONNECTIONTCP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPDYN                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ACTIVSTATEOFCONNECTIONTCPDYN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELRXACTIVEOFCONNECTIONTCPDYN                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELRXLASTIDXOFCONNECTIONTCPDYN                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_INACTIVCNTOFCONNECTIONTCPDYN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_LASTRXBUFSIZEOFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_LASTRXTGTADDROFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_LASTTXBUFSIZEOFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONIDXOFCONNECTIONTCPDYN                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXMSGOFFSETOFCONNECTIONTCPDYN                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXTPSESSIONACTIVEOFCONNECTIONTCPDYN                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SKIPRXMSGOFCONNECTIONTCPDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERADDROFCONNECTIONTCPDYN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERIDXOFCONNECTIONTCPDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPTXPRECLOSESOCKETOFCONNECTIONTCPDYN                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPTXPREHDRTYPEOFCONNECTIONTCPDYN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPTXPREPARAM1OFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPTXPREPARAM2OFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TPTXPREPARAM3OFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXBYTESCOPIEDOFCONNECTIONTCPDYN                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTQUEIDXOFCONNECTIONTCPDYN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTQUELVLOFCONNECTIONTCPDYN                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTPSESSIONACTIVEOFCONNECTIONTCPDYN                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_VERIFYRXPDUOFFSETOFCONNECTIONTCPDYN                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPIND                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DEFAULTTESTER                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERIDXOFDEFAULTTESTER                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DIAGNACKBUF                                                                            STD_ON
#define DOIP_EID                                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_FINALMAGICNUMBER                                                                       STD_OFF  /**< Deactivateable: 'DoIP_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DOIP_GID                                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IFTXBUF                                                                                STD_OFF  /**< Deactivateable: 'DoIP_IfTxBuf' Reason: 'IF API is disabled.' */
#define DOIP_INITDATAHASHCODE                                                                       STD_OFF  /**< Deactivateable: 'DoIP_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define DOIP_IPADDRASSIGNMENT                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ASSIGNMENTTYPEOFIPADDRASSIGNMENT                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONTROLIPASSIGNMENTOFIPADDRASSIGNMENT                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRASSIGNMENTDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRREQSTATEOFIPADDRASSIGNMENTDYN                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRLIST                                                                             STD_OFF  /**< Deactivateable: 'DoIP_IpAddrList' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_IPADDROFIPADDRLIST                                                                     STD_OFF  /**< Deactivateable: 'DoIP_IpAddrList.IpAddr' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_TRIGGERVEHANNOFIPADDRLIST                                                              STD_OFF  /**< Deactivateable: 'DoIP_IpAddrList.TriggerVehAnn' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_LOCALADDR                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONINDENDIDXOFLOCALADDR                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONINDSTARTIDXOFLOCALADDR                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DOMAINTYPEOFLOCALADDR                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRASSIGNMENTENDIDXOFLOCALADDR                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRASSIGNMENTSTARTIDXOFLOCALADDR                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRLISTENDIDXOFLOCALADDR                                                            STD_OFF  /**< Deactivateable: 'DoIP_LocalAddr.IpAddrListEndIdx' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_IPADDRLISTSTARTIDXOFLOCALADDR                                                          STD_OFF  /**< Deactivateable: 'DoIP_LocalAddr.IpAddrListStartIdx' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_IPADDRLISTUSEDOFLOCALADDR                                                              STD_OFF  /**< Deactivateable: 'DoIP_LocalAddr.IpAddrListUsed' Reason: 'DHCP vendor option for DoIP not supported.' */
#define DOIP_TCPIPLOCALADDRIDOFLOCALADDR                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_UDPALIVETIMEOUTOFLOCALADDR                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PDURRXCANCELPDUID                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELIDXOFPDURRXCANCELPDUID                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PDURTXPDUID                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELIDXOFPDURTXPDUID                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTACTIVHANDLER                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ALIVECHECKCNTOFROUTACTIVHANDLER                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ALIVECHECKELEMNUMOFROUTACTIVHANDLER                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPIDXOFROUTACTIVHANDLER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_OEMSPECREQOFROUTACTIVHANDLER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_OEMSPECRESOFROUTACTIVHANDLER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_OEMSPECUSEDOFROUTACTIVHANDLER                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONIDXOFROUTACTIVHANDLER                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERADDROFROUTACTIVHANDLER                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERIDXOFROUTACTIVHANDLER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATION                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_AUTHFUNCPTROFROUTINGACTIVATION                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_AUTHFUNCWITHREMADDROFROUTINGACTIVATION                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_AUTHREQLENGTHOFROUTINGACTIVATION                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_AUTHRESLENGTHOFROUTINGACTIVATION                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_AUTHWITHREMADDRFUNCPTROFROUTINGACTIVATION                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_BITMASKINGUSEDOFROUTINGACTIVATION                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELINDENDIDXOFROUTINGACTIVATION                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELINDSTARTIDXOFROUTINGACTIVATION                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELINDUSEDOFROUTINGACTIVATION                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONFFUNCPTROFROUTINGACTIVATION                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONFFUNCWITHREMADDROFROUTINGACTIVATION                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONFREQLENGTHOFROUTINGACTIVATION                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONFRESLENGTHOFROUTINGACTIVATION                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONFWITHREMADDRFUNCPTROFROUTINGACTIVATION                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_MASKEDBITSOFROUTINGACTIVATION                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONNUMOFROUTINGACTIVATION                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SECURITYREQUIREDOFROUTINGACTIVATION                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONIND                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXHDRBUF                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFALIVECHECKLIST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNEL                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNELDYN                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNELIND                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTION                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONDYN                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONGROUP                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONIND                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCP                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCPDYN                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCPIND                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFDEFAULTTESTER                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFDIAGNACKBUF                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFEID                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFGID                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFIPADDRASSIGNMENT                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFIPADDRASSIGNMENTDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFLOCALADDR                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFPDURRXCANCELPDUID                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFPDURTXPDUID                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTACTIVHANDLER                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTINGACTIVATION                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTINGACTIVATIONIND                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFRXHDRBUF                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTESTER                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTESTERDYN                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXHDRBUF                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXTCPMGT                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXTCPMGTDYN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXUDPMGTLIST                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTER                                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CENTRALSECURITYOFTESTER                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DIAGNACKBUFENDIDXOFTESTER                                                              STD_ON
#define DOIP_DIAGNACKBUFSTARTIDXOFTESTER                                                            STD_ON
#define DOIP_DIAGNACKBUFUSEDOFTESTER                                                                STD_ON
#define DOIP_MASKEDBITSOFTESTER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONINDENDIDXOFTESTER                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONINDSTARTIDXOFTESTER                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERADDROFTESTER                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERDYN                                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPIDXOFTESTERDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DIAGNACKOFFSETOFTESTERDYN                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXHDRBUF                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGT                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXHDRBUFENDIDXOFTXTCPMGT                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXHDRBUFSTARTIDXOFTXTCPMGT                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTDYN                                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELIDXOFTXTCPMGTDYN                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_MSGOFTXTCPMGTDYN                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXHDRBUFLENOFTXTCPMGTDYN                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXUDPMGTLIST                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONIDXOFTXUDPMGTLIST                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_HDRTYPEOFTXUDPMGTLIST                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PARAM1OFTXUDPMGTLIST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PARAM2OFTXUDPMGTLIST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_REMOTEADDROFTXUDPMGTLIST                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RETRYATTEMPTOFTXUDPMGTLIST                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PCCONFIG                                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ALIVECHECKLISTOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELDYNOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELINDOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CHANNELOFPCCONFIG                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONDYNOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONGROUPOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONINDOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPDYNOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPINDOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_CONNECTIONTCPOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DEFAULTTESTEROFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_DIAGNACKBUFOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_EIDOFPCCONFIG                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'DoIP_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define DOIP_GIDOFPCCONFIG                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'DoIP_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define DOIP_IPADDRASSIGNMENTDYNOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_IPADDRASSIGNMENTOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_LOCALADDROFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PDURRXCANCELPDUIDOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_PDURTXPDUIDOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTACTIVHANDLEROFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONINDOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_ROUTINGACTIVATIONOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_RXHDRBUFOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFALIVECHECKLISTOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNELDYNOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNELINDOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCHANNELOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONDYNOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONGROUPOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONINDOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCPDYNOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCPINDOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFCONNECTIONTCPOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFDEFAULTTESTEROFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFDIAGNACKBUFOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFEIDOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFGIDOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFIPADDRASSIGNMENTDYNOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFIPADDRASSIGNMENTOFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFLOCALADDROFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFPDURRXCANCELPDUIDOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFPDURTXPDUIDOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTACTIVHANDLEROFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTINGACTIVATIONINDOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFROUTINGACTIVATIONOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFRXHDRBUFOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTESTERDYNOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTESTEROFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXHDRBUFOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXTCPMGTDYNOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXTCPMGTOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_SIZEOFTXUDPMGTLISTOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTERDYNOFPCCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TESTEROFPCCONFIG                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXHDRBUFOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTDYNOFPCCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXTCPMGTOFPCCONFIG                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define DOIP_TXUDPMGTLISTOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCMinNumericValueDefines  DoIP Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define DOIP_MIN_CONNECTIONTCPIDXOFALIVECHECKLIST                                                   0u
#define DOIP_MIN_TXMSGLENOFCHANNELDYN                                                               0u
#define DOIP_MIN_CHANNELRXLASTIDXOFCONNECTIONTCPDYN                                                 0u
#define DOIP_MIN_INACTIVCNTOFCONNECTIONTCPDYN                                                       0u
#define DOIP_MIN_LASTRXBUFSIZEOFCONNECTIONTCPDYN                                                    0u
#define DOIP_MIN_LASTRXTGTADDROFCONNECTIONTCPDYN                                                    0u
#define DOIP_MIN_LASTTXBUFSIZEOFCONNECTIONTCPDYN                                                    0u
#define DOIP_MIN_ROUTINGACTIVATIONIDXOFCONNECTIONTCPDYN                                             0u
#define DOIP_MIN_RXMSGOFFSETOFCONNECTIONTCPDYN                                                      0u
#define DOIP_MIN_TESTERADDROFCONNECTIONTCPDYN                                                       0u
#define DOIP_MIN_TESTERIDXOFCONNECTIONTCPDYN                                                        0u
#define DOIP_MIN_TXBYTESCOPIEDOFCONNECTIONTCPDYN                                                    0u
#define DOIP_MIN_TXTCPMGTQUEIDXOFCONNECTIONTCPDYN                                                   0u
#define DOIP_MIN_TXTCPMGTQUELVLOFCONNECTIONTCPDYN                                                   0u
#define DOIP_MIN_VERIFYRXPDUOFFSETOFCONNECTIONTCPDYN                                                0u
#define DOIP_MIN_DIAGNACKBUF                                                                        0u
#define DOIP_MIN_ALIVECHECKCNTOFROUTACTIVHANDLER                                                    0u
#define DOIP_MIN_ALIVECHECKELEMNUMOFROUTACTIVHANDLER                                                0u
#define DOIP_MIN_CONNECTIONTCPIDXOFROUTACTIVHANDLER                                                 0u
#define DOIP_MIN_OEMSPECREQOFROUTACTIVHANDLER                                                       0u
#define DOIP_MIN_OEMSPECRESOFROUTACTIVHANDLER                                                       0u
#define DOIP_MIN_ROUTINGACTIVATIONIDXOFROUTACTIVHANDLER                                             0u
#define DOIP_MIN_TESTERADDROFROUTACTIVHANDLER                                                       0u
#define DOIP_MIN_TESTERIDXOFROUTACTIVHANDLER                                                        0u
#define DOIP_MIN_RXHDRBUF                                                                           0u
#define DOIP_MIN_CONNECTIONTCPIDXOFTESTERDYN                                                        0u
#define DOIP_MIN_DIAGNACKOFFSETOFTESTERDYN                                                          0u
#define DOIP_MIN_TXHDRBUF                                                                           0u
#define DOIP_MIN_CHANNELIDXOFTXTCPMGTDYN                                                            0u
#define DOIP_MIN_TXHDRBUFLENOFTXTCPMGTDYN                                                           0u
#define DOIP_MIN_CONNECTIONIDXOFTXUDPMGTLIST                                                        0u
#define DOIP_MIN_HDRTYPEOFTXUDPMGTLIST                                                              0u
#define DOIP_MIN_RETRYATTEMPTOFTXUDPMGTLIST                                                         0u
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCMaxNumericValueDefines  DoIP Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define DOIP_MAX_CONNECTIONTCPIDXOFALIVECHECKLIST                                                   255u
#define DOIP_MAX_TXMSGLENOFCHANNELDYN                                                               65535u
#define DOIP_MAX_CHANNELRXLASTIDXOFCONNECTIONTCPDYN                                                 255u
#define DOIP_MAX_INACTIVCNTOFCONNECTIONTCPDYN                                                       4294967295u
#define DOIP_MAX_LASTRXBUFSIZEOFCONNECTIONTCPDYN                                                    65535u
#define DOIP_MAX_LASTRXTGTADDROFCONNECTIONTCPDYN                                                    65535u
#define DOIP_MAX_LASTTXBUFSIZEOFCONNECTIONTCPDYN                                                    65535u
#define DOIP_MAX_ROUTINGACTIVATIONIDXOFCONNECTIONTCPDYN                                             255u
#define DOIP_MAX_RXMSGOFFSETOFCONNECTIONTCPDYN                                                      18446744073709551615u
#define DOIP_MAX_TESTERADDROFCONNECTIONTCPDYN                                                       65535u
#define DOIP_MAX_TESTERIDXOFCONNECTIONTCPDYN                                                        255u
#define DOIP_MAX_TXBYTESCOPIEDOFCONNECTIONTCPDYN                                                    65535u
#define DOIP_MAX_TXTCPMGTQUEIDXOFCONNECTIONTCPDYN                                                   255u
#define DOIP_MAX_TXTCPMGTQUELVLOFCONNECTIONTCPDYN                                                   255u
#define DOIP_MAX_VERIFYRXPDUOFFSETOFCONNECTIONTCPDYN                                                65535u
#define DOIP_MAX_DIAGNACKBUF                                                                        255u
#define DOIP_MAX_ALIVECHECKCNTOFROUTACTIVHANDLER                                                    65535u
#define DOIP_MAX_ALIVECHECKELEMNUMOFROUTACTIVHANDLER                                                255u
#define DOIP_MAX_CONNECTIONTCPIDXOFROUTACTIVHANDLER                                                 255u
#define DOIP_MAX_OEMSPECREQOFROUTACTIVHANDLER                                                       4294967295u
#define DOIP_MAX_OEMSPECRESOFROUTACTIVHANDLER                                                       4294967295u
#define DOIP_MAX_ROUTINGACTIVATIONIDXOFROUTACTIVHANDLER                                             255u
#define DOIP_MAX_TESTERADDROFROUTACTIVHANDLER                                                       65535u
#define DOIP_MAX_TESTERIDXOFROUTACTIVHANDLER                                                        255u
#define DOIP_MAX_RXHDRBUF                                                                           255u
#define DOIP_MAX_CONNECTIONTCPIDXOFTESTERDYN                                                        255u
#define DOIP_MAX_DIAGNACKOFFSETOFTESTERDYN                                                          4294967295u
#define DOIP_MAX_TXHDRBUF                                                                           255u
#define DOIP_MAX_CHANNELIDXOFTXTCPMGTDYN                                                            255u
#define DOIP_MAX_TXHDRBUFLENOFTXTCPMGTDYN                                                           65535u
#define DOIP_MAX_CONNECTIONIDXOFTXUDPMGTLIST                                                        255u
#define DOIP_MAX_HDRTYPEOFTXUDPMGTLIST                                                              65535u
#define DOIP_MAX_RETRYATTEMPTOFTXUDPMGTLIST                                                         65535u
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCNoReferenceDefines  DoIP No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define DOIP_NO_PDURRXPDUIDOFCHANNEL                                                                255u
#define DOIP_NO_PDURTXCONFPDUIDOFCHANNEL                                                            255u
#define DOIP_NO_RXCANCELPDUIDOFCONNECTION                                                           255u
#define DOIP_NO_SOADTXPDUIDOFCONNECTION                                                             255u
#define DOIP_NO_CHANNELRXLASTIDXOFCONNECTIONTCPDYN                                                  255u
#define DOIP_NO_ROUTINGACTIVATIONIDXOFCONNECTIONTCPDYN                                              255u
#define DOIP_NO_TESTERIDXOFCONNECTIONTCPDYN                                                         255u
#define DOIP_NO_CONNECTIONTCPIDXOFROUTACTIVHANDLER                                                  255u
#define DOIP_NO_ROUTINGACTIVATIONIDXOFROUTACTIVHANDLER                                              255u
#define DOIP_NO_TESTERIDXOFROUTACTIVHANDLER                                                         255u
#define DOIP_NO_CHANNELINDENDIDXOFROUTINGACTIVATION                                                 255u
#define DOIP_NO_CHANNELINDSTARTIDXOFROUTINGACTIVATION                                               255u
#define DOIP_NO_DIAGNACKBUFENDIDXOFTESTER                                                           65535u
#define DOIP_NO_DIAGNACKBUFSTARTIDXOFTESTER                                                         65535u
#define DOIP_NO_CONNECTIONTCPIDXOFTESTERDYN                                                         255u
#define DOIP_NO_CHANNELIDXOFTXTCPMGTDYN                                                             255u
#define DOIP_NO_CONNECTIONIDXOFTXUDPMGTLIST                                                         255u
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCMaskedBitDefines  DoIP Masked Bit Defines (PRE_COMPILE)
  \brief  These defines are masks to extract packed boolean data.
  \{
*/ 
#define DOIP_AUTHFUNCWITHREMADDROFROUTINGACTIVATION_MASK                                            0x10u
#define DOIP_BITMASKINGUSEDOFROUTINGACTIVATION_MASK                                                 0x08u
#define DOIP_CHANNELINDUSEDOFROUTINGACTIVATION_MASK                                                 0x04u
#define DOIP_CONFFUNCWITHREMADDROFROUTINGACTIVATION_MASK                                            0x02u
#define DOIP_SECURITYREQUIREDOFROUTINGACTIVATION_MASK                                               0x01u
#define DOIP_CENTRALSECURITYOFTESTER_MASK                                                           0x02u
#define DOIP_DIAGNACKBUFUSEDOFTESTER_MASK                                                           0x01u
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCIsReducedToDefineDefines  DoIP Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define DOIP_ISDEF_BITMASKOFCHANNEL                                                                 STD_OFF
#define DOIP_ISDEF_ECUADDROFCHANNEL                                                                 STD_OFF
#define DOIP_ISDEF_PDURRXPDUIDOFCHANNEL                                                             STD_OFF
#define DOIP_ISDEF_PDURTXCONFPDUIDOFCHANNEL                                                         STD_OFF
#define DOIP_ISDEF_TESTERIDXOFCHANNEL                                                               STD_OFF
#define DOIP_ISDEF_TPMAXLENOFCHANNEL                                                                STD_OFF
#define DOIP_ISDEF_CHANNELIND                                                                       STD_OFF
#define DOIP_ISDEF_LOCALADDRIDXOFCONNECTION                                                         STD_OFF
#define DOIP_ISDEF_RXCANCELPDUIDOFCONNECTION                                                        STD_OFF
#define DOIP_ISDEF_SOADTXPDUIDOFCONNECTION                                                          STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPINDENDIDXOFCONNECTIONGROUP                                          STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPINDSTARTIDXOFCONNECTIONGROUP                                        STD_OFF
#define DOIP_ISDEF_CONNECTIONIND                                                                    STD_OFF
#define DOIP_ISDEF_CONNECTIONGROUPIDXOFCONNECTIONTCP                                                STD_OFF
#define DOIP_ISDEF_RXHDRBUFENDIDXOFCONNECTIONTCP                                                    STD_OFF
#define DOIP_ISDEF_RXHDRBUFSTARTIDXOFCONNECTIONTCP                                                  STD_OFF
#define DOIP_ISDEF_SECURITYREQUIREDOFCONNECTIONTCP                                                  STD_OFF
#define DOIP_ISDEF_TXTCPMGTENDIDXOFCONNECTIONTCP                                                    STD_OFF
#define DOIP_ISDEF_TXTCPMGTSTARTIDXOFCONNECTIONTCP                                                  STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPIND                                                                 STD_OFF
#define DOIP_ISDEF_TESTERIDXOFDEFAULTTESTER                                                         STD_OFF
#define DOIP_ISDEF_EID                                                                              STD_OFF
#define DOIP_ISDEF_GID                                                                              STD_OFF
#define DOIP_ISDEF_ASSIGNMENTTYPEOFIPADDRASSIGNMENT                                                 STD_OFF
#define DOIP_ISDEF_CONTROLIPASSIGNMENTOFIPADDRASSIGNMENT                                            STD_OFF
#define DOIP_ISDEF_CONNECTIONINDENDIDXOFLOCALADDR                                                   STD_OFF
#define DOIP_ISDEF_CONNECTIONINDSTARTIDXOFLOCALADDR                                                 STD_OFF
#define DOIP_ISDEF_DOMAINTYPEOFLOCALADDR                                                            STD_OFF
#define DOIP_ISDEF_IPADDRASSIGNMENTENDIDXOFLOCALADDR                                                STD_OFF
#define DOIP_ISDEF_IPADDRASSIGNMENTSTARTIDXOFLOCALADDR                                              STD_OFF
#define DOIP_ISDEF_TCPIPLOCALADDRIDOFLOCALADDR                                                      STD_OFF
#define DOIP_ISDEF_UDPALIVETIMEOUTOFLOCALADDR                                                       STD_OFF
#define DOIP_ISDEF_CHANNELIDXOFPDURRXCANCELPDUID                                                    STD_OFF
#define DOIP_ISDEF_CHANNELIDXOFPDURTXPDUID                                                          STD_OFF
#define DOIP_ISDEF_AUTHFUNCPTROFROUTINGACTIVATION                                                   STD_OFF
#define DOIP_ISDEF_AUTHFUNCWITHREMADDROFROUTINGACTIVATION                                           STD_OFF
#define DOIP_ISDEF_AUTHREQLENGTHOFROUTINGACTIVATION                                                 STD_OFF
#define DOIP_ISDEF_AUTHRESLENGTHOFROUTINGACTIVATION                                                 STD_OFF
#define DOIP_ISDEF_AUTHWITHREMADDRFUNCPTROFROUTINGACTIVATION                                        STD_OFF
#define DOIP_ISDEF_BITMASKINGUSEDOFROUTINGACTIVATION                                                STD_OFF
#define DOIP_ISDEF_CHANNELINDENDIDXOFROUTINGACTIVATION                                              STD_OFF
#define DOIP_ISDEF_CHANNELINDSTARTIDXOFROUTINGACTIVATION                                            STD_OFF
#define DOIP_ISDEF_CHANNELINDUSEDOFROUTINGACTIVATION                                                STD_OFF
#define DOIP_ISDEF_CONFFUNCPTROFROUTINGACTIVATION                                                   STD_OFF
#define DOIP_ISDEF_CONFFUNCWITHREMADDROFROUTINGACTIVATION                                           STD_OFF
#define DOIP_ISDEF_CONFREQLENGTHOFROUTINGACTIVATION                                                 STD_OFF
#define DOIP_ISDEF_CONFRESLENGTHOFROUTINGACTIVATION                                                 STD_OFF
#define DOIP_ISDEF_CONFWITHREMADDRFUNCPTROFROUTINGACTIVATION                                        STD_OFF
#define DOIP_ISDEF_MASKEDBITSOFROUTINGACTIVATION                                                    STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONNUMOFROUTINGACTIVATION                                          STD_OFF
#define DOIP_ISDEF_SECURITYREQUIREDOFROUTINGACTIVATION                                              STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONIND                                                             STD_OFF
#define DOIP_ISDEF_CENTRALSECURITYOFTESTER                                                          STD_OFF
#define DOIP_ISDEF_DIAGNACKBUFENDIDXOFTESTER                                                        STD_OFF
#define DOIP_ISDEF_DIAGNACKBUFSTARTIDXOFTESTER                                                      STD_OFF
#define DOIP_ISDEF_DIAGNACKBUFUSEDOFTESTER                                                          STD_OFF
#define DOIP_ISDEF_MASKEDBITSOFTESTER                                                               STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONINDENDIDXOFTESTER                                               STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONINDSTARTIDXOFTESTER                                             STD_OFF
#define DOIP_ISDEF_TESTERADDROFTESTER                                                               STD_OFF
#define DOIP_ISDEF_TXHDRBUFENDIDXOFTXTCPMGT                                                         STD_OFF
#define DOIP_ISDEF_TXHDRBUFSTARTIDXOFTXTCPMGT                                                       STD_OFF
#define DOIP_ISDEF_ALIVECHECKLISTOFPCCONFIG                                                         STD_OFF
#define DOIP_ISDEF_CHANNELDYNOFPCCONFIG                                                             STD_OFF
#define DOIP_ISDEF_CHANNELINDOFPCCONFIG                                                             STD_OFF
#define DOIP_ISDEF_CHANNELOFPCCONFIG                                                                STD_OFF
#define DOIP_ISDEF_CONNECTIONDYNOFPCCONFIG                                                          STD_OFF
#define DOIP_ISDEF_CONNECTIONGROUPOFPCCONFIG                                                        STD_OFF
#define DOIP_ISDEF_CONNECTIONINDOFPCCONFIG                                                          STD_OFF
#define DOIP_ISDEF_CONNECTIONOFPCCONFIG                                                             STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPDYNOFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPINDOFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_CONNECTIONTCPOFPCCONFIG                                                          STD_OFF
#define DOIP_ISDEF_DEFAULTTESTEROFPCCONFIG                                                          STD_OFF
#define DOIP_ISDEF_DIAGNACKBUFOFPCCONFIG                                                            STD_OFF
#define DOIP_ISDEF_EIDOFPCCONFIG                                                                    STD_OFF
#define DOIP_ISDEF_GIDOFPCCONFIG                                                                    STD_OFF
#define DOIP_ISDEF_IPADDRASSIGNMENTDYNOFPCCONFIG                                                    STD_OFF
#define DOIP_ISDEF_IPADDRASSIGNMENTOFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_LOCALADDROFPCCONFIG                                                              STD_OFF
#define DOIP_ISDEF_PDURRXCANCELPDUIDOFPCCONFIG                                                      STD_OFF
#define DOIP_ISDEF_PDURTXPDUIDOFPCCONFIG                                                            STD_OFF
#define DOIP_ISDEF_ROUTACTIVHANDLEROFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONINDOFPCCONFIG                                                   STD_OFF
#define DOIP_ISDEF_ROUTINGACTIVATIONOFPCCONFIG                                                      STD_OFF
#define DOIP_ISDEF_RXHDRBUFOFPCCONFIG                                                               STD_OFF
#define DOIP_ISDEF_SIZEOFALIVECHECKLISTOFPCCONFIG                                                   STD_OFF
#define DOIP_ISDEF_SIZEOFCHANNELINDOFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_SIZEOFCHANNELOFPCCONFIG                                                          STD_OFF
#define DOIP_ISDEF_SIZEOFCONNECTIONGROUPOFPCCONFIG                                                  STD_OFF
#define DOIP_ISDEF_SIZEOFCONNECTIONINDOFPCCONFIG                                                    STD_OFF
#define DOIP_ISDEF_SIZEOFCONNECTIONOFPCCONFIG                                                       STD_OFF
#define DOIP_ISDEF_SIZEOFCONNECTIONTCPINDOFPCCONFIG                                                 STD_OFF
#define DOIP_ISDEF_SIZEOFCONNECTIONTCPOFPCCONFIG                                                    STD_OFF
#define DOIP_ISDEF_SIZEOFDEFAULTTESTEROFPCCONFIG                                                    STD_OFF
#define DOIP_ISDEF_SIZEOFDIAGNACKBUFOFPCCONFIG                                                      STD_OFF
#define DOIP_ISDEF_SIZEOFEIDOFPCCONFIG                                                              STD_OFF
#define DOIP_ISDEF_SIZEOFGIDOFPCCONFIG                                                              STD_OFF
#define DOIP_ISDEF_SIZEOFIPADDRASSIGNMENTOFPCCONFIG                                                 STD_OFF
#define DOIP_ISDEF_SIZEOFLOCALADDROFPCCONFIG                                                        STD_OFF
#define DOIP_ISDEF_SIZEOFPDURRXCANCELPDUIDOFPCCONFIG                                                STD_OFF
#define DOIP_ISDEF_SIZEOFPDURTXPDUIDOFPCCONFIG                                                      STD_OFF
#define DOIP_ISDEF_SIZEOFROUTACTIVHANDLEROFPCCONFIG                                                 STD_OFF
#define DOIP_ISDEF_SIZEOFROUTINGACTIVATIONINDOFPCCONFIG                                             STD_OFF
#define DOIP_ISDEF_SIZEOFROUTINGACTIVATIONOFPCCONFIG                                                STD_OFF
#define DOIP_ISDEF_SIZEOFRXHDRBUFOFPCCONFIG                                                         STD_OFF
#define DOIP_ISDEF_SIZEOFTESTEROFPCCONFIG                                                           STD_OFF
#define DOIP_ISDEF_SIZEOFTXHDRBUFOFPCCONFIG                                                         STD_OFF
#define DOIP_ISDEF_SIZEOFTXTCPMGTOFPCCONFIG                                                         STD_OFF
#define DOIP_ISDEF_SIZEOFTXUDPMGTLISTOFPCCONFIG                                                     STD_OFF
#define DOIP_ISDEF_TESTERDYNOFPCCONFIG                                                              STD_OFF
#define DOIP_ISDEF_TESTEROFPCCONFIG                                                                 STD_OFF
#define DOIP_ISDEF_TXHDRBUFOFPCCONFIG                                                               STD_OFF
#define DOIP_ISDEF_TXTCPMGTDYNOFPCCONFIG                                                            STD_OFF
#define DOIP_ISDEF_TXTCPMGTOFPCCONFIG                                                               STD_OFF
#define DOIP_ISDEF_TXUDPMGTLISTOFPCCONFIG                                                           STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCEqualsAlwaysToDefines  DoIP Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define DOIP_EQ2_BITMASKOFCHANNEL                                                                   
#define DOIP_EQ2_ECUADDROFCHANNEL                                                                   
#define DOIP_EQ2_PDURRXPDUIDOFCHANNEL                                                               
#define DOIP_EQ2_PDURTXCONFPDUIDOFCHANNEL                                                           
#define DOIP_EQ2_TESTERIDXOFCHANNEL                                                                 
#define DOIP_EQ2_TPMAXLENOFCHANNEL                                                                  
#define DOIP_EQ2_CHANNELIND                                                                         
#define DOIP_EQ2_LOCALADDRIDXOFCONNECTION                                                           
#define DOIP_EQ2_RXCANCELPDUIDOFCONNECTION                                                          
#define DOIP_EQ2_SOADTXPDUIDOFCONNECTION                                                            
#define DOIP_EQ2_CONNECTIONTCPINDENDIDXOFCONNECTIONGROUP                                            
#define DOIP_EQ2_CONNECTIONTCPINDSTARTIDXOFCONNECTIONGROUP                                          
#define DOIP_EQ2_CONNECTIONIND                                                                      
#define DOIP_EQ2_CONNECTIONGROUPIDXOFCONNECTIONTCP                                                  
#define DOIP_EQ2_RXHDRBUFENDIDXOFCONNECTIONTCP                                                      
#define DOIP_EQ2_RXHDRBUFSTARTIDXOFCONNECTIONTCP                                                    
#define DOIP_EQ2_SECURITYREQUIREDOFCONNECTIONTCP                                                    
#define DOIP_EQ2_TXTCPMGTENDIDXOFCONNECTIONTCP                                                      
#define DOIP_EQ2_TXTCPMGTSTARTIDXOFCONNECTIONTCP                                                    
#define DOIP_EQ2_CONNECTIONTCPIND                                                                   
#define DOIP_EQ2_TESTERIDXOFDEFAULTTESTER                                                           
#define DOIP_EQ2_EID                                                                                
#define DOIP_EQ2_GID                                                                                
#define DOIP_EQ2_ASSIGNMENTTYPEOFIPADDRASSIGNMENT                                                   
#define DOIP_EQ2_CONTROLIPASSIGNMENTOFIPADDRASSIGNMENT                                              
#define DOIP_EQ2_CONNECTIONINDENDIDXOFLOCALADDR                                                     
#define DOIP_EQ2_CONNECTIONINDSTARTIDXOFLOCALADDR                                                   
#define DOIP_EQ2_DOMAINTYPEOFLOCALADDR                                                              
#define DOIP_EQ2_IPADDRASSIGNMENTENDIDXOFLOCALADDR                                                  
#define DOIP_EQ2_IPADDRASSIGNMENTSTARTIDXOFLOCALADDR                                                
#define DOIP_EQ2_TCPIPLOCALADDRIDOFLOCALADDR                                                        
#define DOIP_EQ2_UDPALIVETIMEOUTOFLOCALADDR                                                         
#define DOIP_EQ2_CHANNELIDXOFPDURRXCANCELPDUID                                                      
#define DOIP_EQ2_CHANNELIDXOFPDURTXPDUID                                                            
#define DOIP_EQ2_AUTHFUNCPTROFROUTINGACTIVATION                                                     
#define DOIP_EQ2_AUTHFUNCWITHREMADDROFROUTINGACTIVATION                                             
#define DOIP_EQ2_AUTHREQLENGTHOFROUTINGACTIVATION                                                   
#define DOIP_EQ2_AUTHRESLENGTHOFROUTINGACTIVATION                                                   
#define DOIP_EQ2_AUTHWITHREMADDRFUNCPTROFROUTINGACTIVATION                                          
#define DOIP_EQ2_BITMASKINGUSEDOFROUTINGACTIVATION                                                  
#define DOIP_EQ2_CHANNELINDENDIDXOFROUTINGACTIVATION                                                
#define DOIP_EQ2_CHANNELINDSTARTIDXOFROUTINGACTIVATION                                              
#define DOIP_EQ2_CHANNELINDUSEDOFROUTINGACTIVATION                                                  
#define DOIP_EQ2_CONFFUNCPTROFROUTINGACTIVATION                                                     
#define DOIP_EQ2_CONFFUNCWITHREMADDROFROUTINGACTIVATION                                             
#define DOIP_EQ2_CONFREQLENGTHOFROUTINGACTIVATION                                                   
#define DOIP_EQ2_CONFRESLENGTHOFROUTINGACTIVATION                                                   
#define DOIP_EQ2_CONFWITHREMADDRFUNCPTROFROUTINGACTIVATION                                          
#define DOIP_EQ2_MASKEDBITSOFROUTINGACTIVATION                                                      
#define DOIP_EQ2_ROUTINGACTIVATIONNUMOFROUTINGACTIVATION                                            
#define DOIP_EQ2_SECURITYREQUIREDOFROUTINGACTIVATION                                                
#define DOIP_EQ2_ROUTINGACTIVATIONIND                                                               
#define DOIP_EQ2_CENTRALSECURITYOFTESTER                                                            
#define DOIP_EQ2_DIAGNACKBUFENDIDXOFTESTER                                                          
#define DOIP_EQ2_DIAGNACKBUFSTARTIDXOFTESTER                                                        
#define DOIP_EQ2_DIAGNACKBUFUSEDOFTESTER                                                            
#define DOIP_EQ2_MASKEDBITSOFTESTER                                                                 
#define DOIP_EQ2_ROUTINGACTIVATIONINDENDIDXOFTESTER                                                 
#define DOIP_EQ2_ROUTINGACTIVATIONINDSTARTIDXOFTESTER                                               
#define DOIP_EQ2_TESTERADDROFTESTER                                                                 
#define DOIP_EQ2_TXHDRBUFENDIDXOFTXTCPMGT                                                           
#define DOIP_EQ2_TXHDRBUFSTARTIDXOFTXTCPMGT                                                         
#define DOIP_EQ2_ALIVECHECKLISTOFPCCONFIG                                                           
#define DOIP_EQ2_CHANNELDYNOFPCCONFIG                                                               
#define DOIP_EQ2_CHANNELINDOFPCCONFIG                                                               
#define DOIP_EQ2_CHANNELOFPCCONFIG                                                                  
#define DOIP_EQ2_CONNECTIONDYNOFPCCONFIG                                                            
#define DOIP_EQ2_CONNECTIONGROUPOFPCCONFIG                                                          
#define DOIP_EQ2_CONNECTIONINDOFPCCONFIG                                                            
#define DOIP_EQ2_CONNECTIONOFPCCONFIG                                                               
#define DOIP_EQ2_CONNECTIONTCPDYNOFPCCONFIG                                                         
#define DOIP_EQ2_CONNECTIONTCPINDOFPCCONFIG                                                         
#define DOIP_EQ2_CONNECTIONTCPOFPCCONFIG                                                            
#define DOIP_EQ2_DEFAULTTESTEROFPCCONFIG                                                            
#define DOIP_EQ2_DIAGNACKBUFOFPCCONFIG                                                              
#define DOIP_EQ2_EIDOFPCCONFIG                                                                      
#define DOIP_EQ2_GIDOFPCCONFIG                                                                      
#define DOIP_EQ2_IPADDRASSIGNMENTDYNOFPCCONFIG                                                      
#define DOIP_EQ2_IPADDRASSIGNMENTOFPCCONFIG                                                         
#define DOIP_EQ2_LOCALADDROFPCCONFIG                                                                
#define DOIP_EQ2_PDURRXCANCELPDUIDOFPCCONFIG                                                        
#define DOIP_EQ2_PDURTXPDUIDOFPCCONFIG                                                              
#define DOIP_EQ2_ROUTACTIVHANDLEROFPCCONFIG                                                         
#define DOIP_EQ2_ROUTINGACTIVATIONINDOFPCCONFIG                                                     
#define DOIP_EQ2_ROUTINGACTIVATIONOFPCCONFIG                                                        
#define DOIP_EQ2_RXHDRBUFOFPCCONFIG                                                                 
#define DOIP_EQ2_SIZEOFALIVECHECKLISTOFPCCONFIG                                                     
#define DOIP_EQ2_SIZEOFCHANNELINDOFPCCONFIG                                                         
#define DOIP_EQ2_SIZEOFCHANNELOFPCCONFIG                                                            
#define DOIP_EQ2_SIZEOFCONNECTIONGROUPOFPCCONFIG                                                    
#define DOIP_EQ2_SIZEOFCONNECTIONINDOFPCCONFIG                                                      
#define DOIP_EQ2_SIZEOFCONNECTIONOFPCCONFIG                                                         
#define DOIP_EQ2_SIZEOFCONNECTIONTCPINDOFPCCONFIG                                                   
#define DOIP_EQ2_SIZEOFCONNECTIONTCPOFPCCONFIG                                                      
#define DOIP_EQ2_SIZEOFDEFAULTTESTEROFPCCONFIG                                                      
#define DOIP_EQ2_SIZEOFDIAGNACKBUFOFPCCONFIG                                                        
#define DOIP_EQ2_SIZEOFEIDOFPCCONFIG                                                                
#define DOIP_EQ2_SIZEOFGIDOFPCCONFIG                                                                
#define DOIP_EQ2_SIZEOFIPADDRASSIGNMENTOFPCCONFIG                                                   
#define DOIP_EQ2_SIZEOFLOCALADDROFPCCONFIG                                                          
#define DOIP_EQ2_SIZEOFPDURRXCANCELPDUIDOFPCCONFIG                                                  
#define DOIP_EQ2_SIZEOFPDURTXPDUIDOFPCCONFIG                                                        
#define DOIP_EQ2_SIZEOFROUTACTIVHANDLEROFPCCONFIG                                                   
#define DOIP_EQ2_SIZEOFROUTINGACTIVATIONINDOFPCCONFIG                                               
#define DOIP_EQ2_SIZEOFROUTINGACTIVATIONOFPCCONFIG                                                  
#define DOIP_EQ2_SIZEOFRXHDRBUFOFPCCONFIG                                                           
#define DOIP_EQ2_SIZEOFTESTEROFPCCONFIG                                                             
#define DOIP_EQ2_SIZEOFTXHDRBUFOFPCCONFIG                                                           
#define DOIP_EQ2_SIZEOFTXTCPMGTOFPCCONFIG                                                           
#define DOIP_EQ2_SIZEOFTXUDPMGTLISTOFPCCONFIG                                                       
#define DOIP_EQ2_TESTERDYNOFPCCONFIG                                                                
#define DOIP_EQ2_TESTEROFPCCONFIG                                                                   
#define DOIP_EQ2_TXHDRBUFOFPCCONFIG                                                                 
#define DOIP_EQ2_TXTCPMGTDYNOFPCCONFIG                                                              
#define DOIP_EQ2_TXTCPMGTOFPCCONFIG                                                                 
#define DOIP_EQ2_TXUDPMGTLISTOFPCCONFIG                                                             
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCSymbolicNonDereferenciateablePointers  DoIP Symbolic Non Dereferenciateable Pointers (PRE_COMPILE)
  \brief  Symbolic non dereferenciateable pointers to be used if all values are optimized to a defined and to return a correct value for has macros in variants.
  \{
*/ 
#define DoIP_ChannelInd                                                                             ((DoIP_ChannelIndPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_ConnectionGroup                                                                        ((DoIP_ConnectionGroupPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_ConnectionInd                                                                          ((DoIP_ConnectionIndPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_ConnectionTcpInd                                                                       ((DoIP_ConnectionTcpIndPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_PduRRxCancelPduId                                                                      ((DoIP_PduRRxCancelPduIdPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_PduRTxPduId                                                                            ((DoIP_PduRTxPduIdPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_RoutingActivationInd                                                                   ((DoIP_RoutingActivationIndPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
#define DoIP_Tester                                                                                 ((DoIP_TesterPtrType)(&(DoIP_PCConfig)))  /**< Non derefenciateable valid pointer */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCSymbolicInitializationPointers  DoIP Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define DoIP_Config_Ptr                                                                             &(DoIP_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'DoIP' */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCInitializationSymbols  DoIP Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define DoIP_Config                                                                                 DoIP_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'DoIP */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGeneral  DoIP General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define DOIP_CHECK_INIT_POINTER                                                                     STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define DOIP_FINAL_MAGIC_NUMBER                                                                     0xAD1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of DoIP */
#define DOIP_INDIVIDUAL_POSTBUILD                                                                   STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'DoIP' is not configured to be postbuild capable. */
#define DOIP_INIT_DATA                                                                              DOIP_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define DOIP_INIT_DATA_HASH_CODE                                                                    352479520  /**< the precompile constant to validate the initialization structure at initialization time of DoIP with a hashcode. The seed value is '0xAD1Eu' */
#define DOIP_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define DOIP_USE_INIT_POINTER                                                                       STD_ON  /**< STD_ON if the init pointer DoIP shall be used. */
/** 
  \}
*/ 



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
  \defgroup  DoIPPCGetRootDataMacros  DoIP Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define DoIP_GetAliveCheckListOfPCConfig()                                                          DoIP_ConfigDataPtr->AliveCheckListOfPCConfig
#define DoIP_GetChannelDynOfPCConfig()                                                              DoIP_ConfigDataPtr->ChannelDynOfPCConfig
#define DoIP_GetChannelIndOfPCConfig()                                                              DoIP_ConfigDataPtr->ChannelIndOfPCConfig
#define DoIP_GetChannelOfPCConfig()                                                                 DoIP_ConfigDataPtr->ChannelOfPCConfig
#define DoIP_GetConnectionDynOfPCConfig()                                                           DoIP_ConfigDataPtr->ConnectionDynOfPCConfig
#define DoIP_GetConnectionGroupOfPCConfig()                                                         DoIP_ConfigDataPtr->ConnectionGroupOfPCConfig
#define DoIP_GetConnectionIndOfPCConfig()                                                           DoIP_ConfigDataPtr->ConnectionIndOfPCConfig
#define DoIP_GetConnectionOfPCConfig()                                                              DoIP_ConfigDataPtr->ConnectionOfPCConfig
#define DoIP_GetConnectionTcpDynOfPCConfig()                                                        DoIP_ConfigDataPtr->ConnectionTcpDynOfPCConfig
#define DoIP_GetConnectionTcpIndOfPCConfig()                                                        DoIP_ConfigDataPtr->ConnectionTcpIndOfPCConfig
#define DoIP_GetConnectionTcpOfPCConfig()                                                           DoIP_ConfigDataPtr->ConnectionTcpOfPCConfig
#define DoIP_GetDefaultTesterOfPCConfig()                                                           DoIP_ConfigDataPtr->DefaultTesterOfPCConfig
#define DoIP_GetDiagNAckBufOfPCConfig()                                                             DoIP_ConfigDataPtr->DiagNAckBufOfPCConfig
#define DoIP_GetEIdOfPCConfig()                                                                     DoIP_ConfigDataPtr->EIdOfPCConfig
#define DoIP_GetGIdOfPCConfig()                                                                     DoIP_ConfigDataPtr->GIdOfPCConfig
#define DoIP_GetIpAddrAssignmentDynOfPCConfig()                                                     DoIP_ConfigDataPtr->IpAddrAssignmentDynOfPCConfig
#define DoIP_GetIpAddrAssignmentOfPCConfig()                                                        DoIP_ConfigDataPtr->IpAddrAssignmentOfPCConfig
#define DoIP_GetLocalAddrOfPCConfig()                                                               DoIP_ConfigDataPtr->LocalAddrOfPCConfig
#define DoIP_GetPduRRxCancelPduIdOfPCConfig()                                                       DoIP_ConfigDataPtr->PduRRxCancelPduIdOfPCConfig
#define DoIP_GetPduRTxPduIdOfPCConfig()                                                             DoIP_ConfigDataPtr->PduRTxPduIdOfPCConfig
#define DoIP_GetRoutActivHandlerOfPCConfig()                                                        DoIP_ConfigDataPtr->RoutActivHandlerOfPCConfig
#define DoIP_GetRoutingActivationIndOfPCConfig()                                                    DoIP_ConfigDataPtr->RoutingActivationIndOfPCConfig
#define DoIP_GetRoutingActivationOfPCConfig()                                                       DoIP_ConfigDataPtr->RoutingActivationOfPCConfig
#define DoIP_GetRxHdrBufOfPCConfig()                                                                DoIP_ConfigDataPtr->RxHdrBufOfPCConfig
#define DoIP_GetSizeOfAliveCheckListOfPCConfig()                                                    DoIP_ConfigDataPtr->SizeOfAliveCheckListOfPCConfig
#define DoIP_GetSizeOfChannelIndOfPCConfig()                                                        DoIP_ConfigDataPtr->SizeOfChannelIndOfPCConfig
#define DoIP_GetSizeOfChannelOfPCConfig()                                                           DoIP_ConfigDataPtr->SizeOfChannelOfPCConfig
#define DoIP_GetSizeOfConnectionGroupOfPCConfig()                                                   DoIP_ConfigDataPtr->SizeOfConnectionGroupOfPCConfig
#define DoIP_GetSizeOfConnectionIndOfPCConfig()                                                     DoIP_ConfigDataPtr->SizeOfConnectionIndOfPCConfig
#define DoIP_GetSizeOfConnectionOfPCConfig()                                                        DoIP_ConfigDataPtr->SizeOfConnectionOfPCConfig
#define DoIP_GetSizeOfConnectionTcpIndOfPCConfig()                                                  DoIP_ConfigDataPtr->SizeOfConnectionTcpIndOfPCConfig
#define DoIP_GetSizeOfConnectionTcpOfPCConfig()                                                     DoIP_ConfigDataPtr->SizeOfConnectionTcpOfPCConfig
#define DoIP_GetSizeOfDefaultTesterOfPCConfig()                                                     DoIP_ConfigDataPtr->SizeOfDefaultTesterOfPCConfig
#define DoIP_GetSizeOfDiagNAckBufOfPCConfig()                                                       DoIP_ConfigDataPtr->SizeOfDiagNAckBufOfPCConfig
#define DoIP_GetSizeOfEIdOfPCConfig()                                                               DoIP_ConfigDataPtr->SizeOfEIdOfPCConfig
#define DoIP_GetSizeOfGIdOfPCConfig()                                                               DoIP_ConfigDataPtr->SizeOfGIdOfPCConfig
#define DoIP_GetSizeOfIpAddrAssignmentOfPCConfig()                                                  DoIP_ConfigDataPtr->SizeOfIpAddrAssignmentOfPCConfig
#define DoIP_GetSizeOfLocalAddrOfPCConfig()                                                         DoIP_ConfigDataPtr->SizeOfLocalAddrOfPCConfig
#define DoIP_GetSizeOfPduRRxCancelPduIdOfPCConfig()                                                 DoIP_ConfigDataPtr->SizeOfPduRRxCancelPduIdOfPCConfig
#define DoIP_GetSizeOfPduRTxPduIdOfPCConfig()                                                       DoIP_ConfigDataPtr->SizeOfPduRTxPduIdOfPCConfig
#define DoIP_GetSizeOfRoutActivHandlerOfPCConfig()                                                  DoIP_ConfigDataPtr->SizeOfRoutActivHandlerOfPCConfig
#define DoIP_GetSizeOfRoutingActivationIndOfPCConfig()                                              DoIP_ConfigDataPtr->SizeOfRoutingActivationIndOfPCConfig
#define DoIP_GetSizeOfRoutingActivationOfPCConfig()                                                 DoIP_ConfigDataPtr->SizeOfRoutingActivationOfPCConfig
#define DoIP_GetSizeOfRxHdrBufOfPCConfig()                                                          DoIP_ConfigDataPtr->SizeOfRxHdrBufOfPCConfig
#define DoIP_GetSizeOfTesterOfPCConfig()                                                            DoIP_ConfigDataPtr->SizeOfTesterOfPCConfig
#define DoIP_GetSizeOfTxHdrBufOfPCConfig()                                                          DoIP_ConfigDataPtr->SizeOfTxHdrBufOfPCConfig
#define DoIP_GetSizeOfTxTcpMgtOfPCConfig()                                                          DoIP_ConfigDataPtr->SizeOfTxTcpMgtOfPCConfig
#define DoIP_GetSizeOfTxUdpMgtListOfPCConfig()                                                      DoIP_ConfigDataPtr->SizeOfTxUdpMgtListOfPCConfig
#define DoIP_GetTesterDynOfPCConfig()                                                               DoIP_ConfigDataPtr->TesterDynOfPCConfig
#define DoIP_GetTesterOfPCConfig()                                                                  DoIP_ConfigDataPtr->TesterOfPCConfig
#define DoIP_GetTxHdrBufOfPCConfig()                                                                DoIP_ConfigDataPtr->TxHdrBufOfPCConfig
#define DoIP_GetTxTcpMgtDynOfPCConfig()                                                             DoIP_ConfigDataPtr->TxTcpMgtDynOfPCConfig
#define DoIP_GetTxTcpMgtOfPCConfig()                                                                DoIP_ConfigDataPtr->TxTcpMgtOfPCConfig
#define DoIP_GetTxUdpMgtListOfPCConfig()                                                            DoIP_ConfigDataPtr->TxUdpMgtListOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGetDuplicatedRootDataMacros  DoIP Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define DoIP_GetSizeOfChannelDynOfPCConfig()                                                        DoIP_GetSizeOfChannelOfPCConfig()  /**< the number of accomplishable value elements in DoIP_ChannelDyn */
#define DoIP_GetSizeOfConnectionDynOfPCConfig()                                                     DoIP_GetSizeOfConnectionOfPCConfig()  /**< the number of accomplishable value elements in DoIP_ConnectionDyn */
#define DoIP_GetSizeOfConnectionTcpDynOfPCConfig()                                                  DoIP_GetSizeOfConnectionTcpOfPCConfig()  /**< the number of accomplishable value elements in DoIP_ConnectionTcpDyn */
#define DoIP_GetSizeOfIpAddrAssignmentDynOfPCConfig()                                               DoIP_GetSizeOfIpAddrAssignmentOfPCConfig()  /**< the number of accomplishable value elements in DoIP_IpAddrAssignmentDyn */
#define DoIP_GetSizeOfTesterDynOfPCConfig()                                                         DoIP_GetSizeOfTesterOfPCConfig()  /**< the number of accomplishable value elements in DoIP_TesterDyn */
#define DoIP_GetSizeOfTxTcpMgtDynOfPCConfig()                                                       DoIP_GetSizeOfTxTcpMgtOfPCConfig()  /**< the number of accomplishable value elements in DoIP_TxTcpMgtDyn */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGetDataMacros  DoIP Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define DoIP_GetConnectionTcpIdxOfAliveCheckList(Index)                                             (DoIP_GetAliveCheckListOfPCConfig()[(Index)].ConnectionTcpIdxOfAliveCheckList)
#define DoIP_GetEcuAddrOfChannel(Index)                                                             (DoIP_GetChannelOfPCConfig()[(Index)].EcuAddrOfChannel)
#define DoIP_GetPduRRxPduIdOfChannel(Index)                                                         (DoIP_GetChannelOfPCConfig()[(Index)].PduRRxPduIdOfChannel)
#define DoIP_GetPduRTxConfPduIdOfChannel(Index)                                                     (DoIP_GetChannelOfPCConfig()[(Index)].PduRTxConfPduIdOfChannel)
#define DoIP_GetTpMaxLenOfChannel(Index)                                                            (DoIP_GetChannelOfPCConfig()[(Index)].TpMaxLenOfChannel)
#define DoIP_GetTxMsgLenOfChannelDyn(Index)                                                         (DoIP_GetChannelDynOfPCConfig()[(Index)].TxMsgLenOfChannelDyn)
#define DoIP_GetLocalAddrIdxOfConnection(Index)                                                     (DoIP_GetConnectionOfPCConfig()[(Index)].LocalAddrIdxOfConnection)
#define DoIP_GetRxCancelPduIdOfConnection(Index)                                                    (DoIP_GetConnectionOfPCConfig()[(Index)].RxCancelPduIdOfConnection)
#define DoIP_GetSoAdTxPduIdOfConnection(Index)                                                      (DoIP_GetConnectionOfPCConfig()[(Index)].SoAdTxPduIdOfConnection)
#define DoIP_GetIpAddrStateOfConnectionDyn(Index)                                                   (DoIP_GetConnectionDynOfPCConfig()[(Index)].IpAddrStateOfConnectionDyn)
#define DoIP_IsSoConClosingOfConnectionDyn(Index)                                                   ((DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConClosingOfConnectionDyn) != FALSE)
#define DoIP_GetSoConIdOfConnectionDyn(Index)                                                       (DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConIdOfConnectionDyn)
#define DoIP_GetSoConStateOfConnectionDyn(Index)                                                    (DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConStateOfConnectionDyn)
#define DoIP_GetConnectionGroupIdxOfConnectionTcp(Index)                                            (DoIP_GetConnectionTcpOfPCConfig()[(Index)].ConnectionGroupIdxOfConnectionTcp)
#define DoIP_GetRxHdrBufStartIdxOfConnectionTcp(Index)                                              (DoIP_GetConnectionTcpOfPCConfig()[(Index)].RxHdrBufStartIdxOfConnectionTcp)
#define DoIP_IsSecurityRequiredOfConnectionTcp(Index)                                               ((DoIP_GetConnectionTcpOfPCConfig()[(Index)].SecurityRequiredOfConnectionTcp) != FALSE)
#define DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(Index)                                              (DoIP_GetConnectionTcpOfPCConfig()[(Index)].TxTcpMgtStartIdxOfConnectionTcp)
#define DoIP_GetActivStateOfConnectionTcpDyn(Index)                                                 (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ActivStateOfConnectionTcpDyn)
#define DoIP_IsChannelRxActiveOfConnectionTcpDyn(Index)                                             ((DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ChannelRxActiveOfConnectionTcpDyn) != FALSE)
#define DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(Index)                                           (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ChannelRxLastIdxOfConnectionTcpDyn)
#define DoIP_GetInactivCntOfConnectionTcpDyn(Index)                                                 (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].InactivCntOfConnectionTcpDyn)
#define DoIP_GetLastRxBufSizeOfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastRxBufSizeOfConnectionTcpDyn)
#define DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastRxTgtAddrOfConnectionTcpDyn)
#define DoIP_GetLastTxBufSizeOfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastTxBufSizeOfConnectionTcpDyn)
#define DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(Index)                                       (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RoutingActivationIdxOfConnectionTcpDyn)
#define DoIP_GetRxMsgOffsetOfConnectionTcpDyn(Index)                                                (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RxMsgOffsetOfConnectionTcpDyn)
#define DoIP_IsRxTpSessionActiveOfConnectionTcpDyn(Index)                                           ((DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RxTpSessionActiveOfConnectionTcpDyn) != FALSE)
#define DoIP_IsSkipRxMsgOfConnectionTcpDyn(Index)                                                   ((DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].SkipRxMsgOfConnectionTcpDyn) != FALSE)
#define DoIP_GetTesterAddrOfConnectionTcpDyn(Index)                                                 (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TesterAddrOfConnectionTcpDyn)
#define DoIP_GetTesterIdxOfConnectionTcpDyn(Index)                                                  (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TesterIdxOfConnectionTcpDyn)
#define DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(Index)                                         (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreCloseSocketOfConnectionTcpDyn)
#define DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(Index)                                             (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreHdrTypeOfConnectionTcpDyn)
#define DoIP_GetTpTxPreParam1OfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam1OfConnectionTcpDyn)
#define DoIP_GetTpTxPreParam2OfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam2OfConnectionTcpDyn)
#define DoIP_GetTpTxPreParam3OfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam3OfConnectionTcpDyn)
#define DoIP_GetTxBytesCopiedOfConnectionTcpDyn(Index)                                              (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxBytesCopiedOfConnectionTcpDyn)
#define DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(Index)                                             (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTcpMgtQueIdxOfConnectionTcpDyn)
#define DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(Index)                                             (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTcpMgtQueLvlOfConnectionTcpDyn)
#define DoIP_IsTxTpSessionActiveOfConnectionTcpDyn(Index)                                           ((DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTpSessionActiveOfConnectionTcpDyn) != FALSE)
#define DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(Index)                                          (DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].VerifyRxPduOffsetOfConnectionTcpDyn)
#define DoIP_GetTesterIdxOfDefaultTester(Index)                                                     (DoIP_GetDefaultTesterOfPCConfig()[(Index)].TesterIdxOfDefaultTester)
#define DoIP_GetDiagNAckBuf(Index)                                                                  (DoIP_GetDiagNAckBufOfPCConfig()[(Index)])
#define DoIP_GetEId(Index)                                                                          (DoIP_GetEIdOfPCConfig()[(Index)])
#define DoIP_GetGId(Index)                                                                          (DoIP_GetGIdOfPCConfig()[(Index)])
#define DoIP_GetAssignmentTypeOfIpAddrAssignment(Index)                                             (DoIP_GetIpAddrAssignmentOfPCConfig()[(Index)].AssignmentTypeOfIpAddrAssignment)
#define DoIP_IsControlIpAssignmentOfIpAddrAssignment(Index)                                         ((DoIP_GetIpAddrAssignmentOfPCConfig()[(Index)].ControlIpAssignmentOfIpAddrAssignment) != FALSE)
#define DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(Index)                                          (DoIP_GetIpAddrAssignmentDynOfPCConfig()[(Index)].IpAddrReqStateOfIpAddrAssignmentDyn)
#define DoIP_GetDomainTypeOfLocalAddr(Index)                                                        (DoIP_GetLocalAddrOfPCConfig()[(Index)].DomainTypeOfLocalAddr)
#define DoIP_IsUdpAliveTimeoutOfLocalAddr(Index)                                                    ((DoIP_GetLocalAddrOfPCConfig()[(Index)].UdpAliveTimeoutOfLocalAddr) != FALSE)
#define DoIP_GetAliveCheckCntOfRoutActivHandler(Index)                                              (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].AliveCheckCntOfRoutActivHandler)
#define DoIP_GetAliveCheckElemNumOfRoutActivHandler(Index)                                          (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].AliveCheckElemNumOfRoutActivHandler)
#define DoIP_GetConnectionTcpIdxOfRoutActivHandler(Index)                                           (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].ConnectionTcpIdxOfRoutActivHandler)
#define DoIP_GetOemSpecReqOfRoutActivHandler(Index)                                                 (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecReqOfRoutActivHandler)
#define DoIP_GetOemSpecResOfRoutActivHandler(Index)                                                 (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecResOfRoutActivHandler)
#define DoIP_IsOemSpecUsedOfRoutActivHandler(Index)                                                 ((DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecUsedOfRoutActivHandler) != FALSE)
#define DoIP_GetRoutingActivationIdxOfRoutActivHandler(Index)                                       (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].RoutingActivationIdxOfRoutActivHandler)
#define DoIP_GetTesterAddrOfRoutActivHandler(Index)                                                 (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].TesterAddrOfRoutActivHandler)
#define DoIP_GetTesterIdxOfRoutActivHandler(Index)                                                  (DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].TesterIdxOfRoutActivHandler)
#define DoIP_GetAuthFuncPtrOfRoutingActivation(Index)                                               (DoIP_GetRoutingActivationOfPCConfig()[(Index)].AuthFuncPtrOfRoutingActivation)
#define DoIP_GetAuthWithRemAddrFuncPtrOfRoutingActivation(Index)                                    (DoIP_GetRoutingActivationOfPCConfig()[(Index)].AuthWithRemAddrFuncPtrOfRoutingActivation)
#define DoIP_GetConfFuncPtrOfRoutingActivation(Index)                                               (DoIP_GetRoutingActivationOfPCConfig()[(Index)].ConfFuncPtrOfRoutingActivation)
#define DoIP_GetConfWithRemAddrFuncPtrOfRoutingActivation(Index)                                    (DoIP_GetRoutingActivationOfPCConfig()[(Index)].ConfWithRemAddrFuncPtrOfRoutingActivation)
#define DoIP_GetRxHdrBuf(Index)                                                                     (DoIP_GetRxHdrBufOfPCConfig()[(Index)])
#define DoIP_GetConnectionTcpIdxOfTesterDyn(Index)                                                  (DoIP_GetTesterDynOfPCConfig()[(Index)].ConnectionTcpIdxOfTesterDyn)
#define DoIP_GetDiagNAckOffsetOfTesterDyn(Index)                                                    (DoIP_GetTesterDynOfPCConfig()[(Index)].DiagNAckOffsetOfTesterDyn)
#define DoIP_GetTxHdrBuf(Index)                                                                     (DoIP_GetTxHdrBufOfPCConfig()[(Index)])
#define DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(Index)                                                   (DoIP_GetTxTcpMgtOfPCConfig()[(Index)].TxHdrBufStartIdxOfTxTcpMgt)
#define DoIP_GetChannelIdxOfTxTcpMgtDyn(Index)                                                      (DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].ChannelIdxOfTxTcpMgtDyn)
#define DoIP_GetMsgOfTxTcpMgtDyn(Index)                                                             (DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].MsgOfTxTcpMgtDyn)
#define DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(Index)                                                     (DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].TxHdrBufLenOfTxTcpMgtDyn)
#define DoIP_GetConnectionIdxOfTxUdpMgtList(Index)                                                  (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].ConnectionIdxOfTxUdpMgtList)
#define DoIP_GetHdrTypeOfTxUdpMgtList(Index)                                                        (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].HdrTypeOfTxUdpMgtList)
#define DoIP_GetParam1OfTxUdpMgtList(Index)                                                         (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].Param1OfTxUdpMgtList)
#define DoIP_GetParam2OfTxUdpMgtList(Index)                                                         (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].Param2OfTxUdpMgtList)
#define DoIP_GetRemoteAddrOfTxUdpMgtList(Index)                                                     (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].RemoteAddrOfTxUdpMgtList)
#define DoIP_GetRetryAttemptOfTxUdpMgtList(Index)                                                   (DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].RetryAttemptOfTxUdpMgtList)
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGetBitDataMacros  DoIP Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define DoIP_IsBitmaskingUsedOfRoutingActivation(Index)                                             (DOIP_BITMASKINGUSEDOFROUTINGACTIVATION_MASK == (DoIP_GetMaskedBitsOfRoutingActivation(Index) & DOIP_BITMASKINGUSEDOFROUTINGACTIVATION_MASK))  /**< indicates if the routing activation refer to one or more target addresses with bitmasking */
#define DoIP_IsDiagNAckBufUsedOfTester(Index)                                                       (DOIP_DIAGNACKBUFUSEDOFTESTER_MASK == (DoIP_GetMaskedBitsOfTester(Index) & DOIP_DIAGNACKBUFUSEDOFTESTER_MASK))  /**< TRUE, if the 0:n relation has 1 relation pointing to DoIP_DiagNAckBuf */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGetDeduplicatedDataMacros  DoIP Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define DoIP_GetBitMaskOfChannel(Index)                                                             ((DoIP_BitMaskOfChannelType)((DoIP_GetTpMaxLenOfChannel(Index) + 61440u)))  /**< bit mask for logical address masking */
#define DoIP_GetTesterIdxOfChannel(Index)                                                           ((DoIP_TesterIdxOfChannelType)((DoIP_GetTpMaxLenOfChannel(Index) - 4095u)))  /**< the index of the 1:1 relation pointing to DoIP_Tester */
#define DoIP_GetChannelInd(Index)                                                                   ((DoIP_ChannelIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to DoIP_Channel */
#define DoIP_GetConnectionTcpIndEndIdxOfConnectionGroup(Index)                                      ((DoIP_ConnectionTcpIndEndIdxOfConnectionGroupType)((((DoIP_ConnectionTcpIndEndIdxOfConnectionGroupType)(Index)) + 2u)))  /**< the end index of the 1:n relation pointing to DoIP_ConnectionTcpInd */
#define DoIP_GetConnectionTcpIndStartIdxOfConnectionGroup(Index)                                    ((DoIP_ConnectionTcpIndStartIdxOfConnectionGroupType)((Index)))  /**< the start index of the 1:n relation pointing to DoIP_ConnectionTcpInd */
#define DoIP_GetConnectionInd(Index)                                                                ((DoIP_ConnectionIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to DoIP_Connection */
#define DoIP_GetRxHdrBufEndIdxOfConnectionTcp(Index)                                                ((DoIP_RxHdrBufEndIdxOfConnectionTcpType)((DoIP_GetRxHdrBufStartIdxOfConnectionTcp(Index) + 19u)))  /**< the end index of the 1:n relation pointing to DoIP_RxHdrBuf */
#define DoIP_GetTxTcpMgtEndIdxOfConnectionTcp(Index)                                                ((DoIP_TxTcpMgtEndIdxOfConnectionTcpType)((DoIP_GetTxTcpMgtStartIdxOfConnectionTcp(Index) + 2u)))  /**< the end index of the 1:n relation pointing to DoIP_TxTcpMgt */
#define DoIP_GetConnectionTcpInd(Index)                                                             ((DoIP_ConnectionTcpIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to DoIP_ConnectionTcp */
#define DoIP_GetConnectionIndEndIdxOfLocalAddr(Index)                                               ((DoIP_ConnectionIndEndIdxOfLocalAddrType)((((DoIP_ConnectionIndEndIdxOfLocalAddrType)(Index)) + 4u)))  /**< the end index of the 1:n relation pointing to DoIP_ConnectionInd */
#define DoIP_GetConnectionIndStartIdxOfLocalAddr(Index)                                             ((DoIP_ConnectionIndStartIdxOfLocalAddrType)((Index)))  /**< the start index of the 1:n relation pointing to DoIP_ConnectionInd */
#define DoIP_GetIpAddrAssignmentEndIdxOfLocalAddr(Index)                                            ((DoIP_IpAddrAssignmentEndIdxOfLocalAddrType)((((DoIP_IpAddrAssignmentEndIdxOfLocalAddrType)(Index)) + 2u)))  /**< the end index of the 1:n relation pointing to DoIP_IpAddrAssignment */
#define DoIP_GetIpAddrAssignmentStartIdxOfLocalAddr(Index)                                          ((DoIP_IpAddrAssignmentStartIdxOfLocalAddrType)((Index)))  /**< the start index of the 1:n relation pointing to DoIP_IpAddrAssignment */
#define DoIP_GetTcpIpLocalAddrIdOfLocalAddr(Index)                                                  ((DoIP_TcpIpLocalAddrIdOfLocalAddrType)((((DoIP_TcpIpLocalAddrIdOfLocalAddrType)(Index)) + 7u)))  /**< the TcpIp local address id */
#define DoIP_GetChannelIdxOfPduRRxCancelPduId(Index)                                                ((DoIP_ChannelIdxOfPduRRxCancelPduIdType)((Index)))  /**< the index of the 1:1 relation pointing to DoIP_Channel */
#define DoIP_GetChannelIdxOfPduRTxPduId(Index)                                                      ((DoIP_ChannelIdxOfPduRTxPduIdType)((Index)))  /**< the index of the 1:1 relation pointing to DoIP_Channel */
#define DoIP_IsAuthFuncWithRemAddrOfRoutingActivation(Index)                                        DoIP_IsBitmaskingUsedOfRoutingActivation(Index)  /**< indicates if the authentification function is used with a remote adddress */
#define DoIP_GetAuthReqLengthOfRoutingActivation(Index)                                             ((DoIP_AuthReqLengthOfRoutingActivationType)((Index)))  /**< authentification request length */
#define DoIP_GetAuthResLengthOfRoutingActivation(Index)                                             ((DoIP_AuthResLengthOfRoutingActivationType)((Index)))  /**< authentification response length */
#define DoIP_GetChannelIndEndIdxOfRoutingActivation(Index)                                          ((DoIP_ChannelIndEndIdxOfRoutingActivationType)((((DoIP_ChannelIndEndIdxOfRoutingActivationType)(Index)) + 2u)))  /**< the end index of the 0:n relation pointing to DoIP_ChannelInd */
#define DoIP_GetChannelIndStartIdxOfRoutingActivation(Index)                                        ((DoIP_ChannelIndStartIdxOfRoutingActivationType)((Index)))  /**< the start index of the 0:n relation pointing to DoIP_ChannelInd */
#define DoIP_IsChannelIndUsedOfRoutingActivation(Index)                                             (((!(DoIP_IsBitmaskingUsedOfRoutingActivation(Index)))) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to DoIP_ChannelInd */
#define DoIP_IsConfFuncWithRemAddrOfRoutingActivation(Index)                                        DoIP_IsBitmaskingUsedOfRoutingActivation(Index)  /**< indicates if the confirmation function is used with a remote adddress */
#define DoIP_GetConfReqLengthOfRoutingActivation(Index)                                             ((DoIP_ConfReqLengthOfRoutingActivationType)((Index)))  /**< confirmation request length */
#define DoIP_GetConfResLengthOfRoutingActivation(Index)                                             ((DoIP_ConfResLengthOfRoutingActivationType)((Index)))  /**< confirmation response length */
#define DoIP_GetMaskedBitsOfRoutingActivation(Index)                                                ((DoIP_MaskedBitsOfRoutingActivationType)((((DoIP_MaskedBitsOfRoutingActivationType)(Index)) + 0x04u)))  /**< contains bitcoded the boolean data of DoIP_AuthFuncWithRemAddrOfRoutingActivation, DoIP_BitmaskingUsedOfRoutingActivation, DoIP_ChannelIndUsedOfRoutingActivation, DoIP_ConfFuncWithRemAddrOfRoutingActivation, DoIP_SecurityRequiredOfRoutingActivation */
#define DoIP_GetRoutingActivationNumOfRoutingActivation(Index)                                      ((DoIP_RoutingActivationNumOfRoutingActivationType)((Index)))  /**< routing activation number */
#define DoIP_IsSecurityRequiredOfRoutingActivation(Index)                                           DoIP_IsBitmaskingUsedOfRoutingActivation(Index)  /**< indicates if the routing activation requires security on the corresponding TCP connection */
#define DoIP_GetRoutingActivationInd(Index)                                                         ((DoIP_RoutingActivationIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to DoIP_RoutingActivation */
#define DoIP_GetSizeOfAliveCheckList()                                                              DoIP_GetSizeOfAliveCheckListOfPCConfig()
#define DoIP_GetSizeOfChannel()                                                                     DoIP_GetSizeOfChannelOfPCConfig()
#define DoIP_GetSizeOfChannelDyn()                                                                  DoIP_GetSizeOfChannelDynOfPCConfig()
#define DoIP_GetSizeOfChannelInd()                                                                  DoIP_GetSizeOfChannelIndOfPCConfig()
#define DoIP_GetSizeOfConnection()                                                                  DoIP_GetSizeOfConnectionOfPCConfig()
#define DoIP_GetSizeOfConnectionDyn()                                                               DoIP_GetSizeOfConnectionDynOfPCConfig()
#define DoIP_GetSizeOfConnectionGroup()                                                             DoIP_GetSizeOfConnectionGroupOfPCConfig()
#define DoIP_GetSizeOfConnectionInd()                                                               DoIP_GetSizeOfConnectionIndOfPCConfig()
#define DoIP_GetSizeOfConnectionTcp()                                                               DoIP_GetSizeOfConnectionTcpOfPCConfig()
#define DoIP_GetSizeOfConnectionTcpDyn()                                                            DoIP_GetSizeOfConnectionTcpDynOfPCConfig()
#define DoIP_GetSizeOfConnectionTcpInd()                                                            DoIP_GetSizeOfConnectionTcpIndOfPCConfig()
#define DoIP_GetSizeOfDefaultTester()                                                               DoIP_GetSizeOfDefaultTesterOfPCConfig()
#define DoIP_GetSizeOfDiagNAckBuf()                                                                 DoIP_GetSizeOfDiagNAckBufOfPCConfig()
#define DoIP_GetSizeOfEId()                                                                         DoIP_GetSizeOfEIdOfPCConfig()
#define DoIP_GetSizeOfGId()                                                                         DoIP_GetSizeOfGIdOfPCConfig()
#define DoIP_GetSizeOfIpAddrAssignment()                                                            DoIP_GetSizeOfIpAddrAssignmentOfPCConfig()
#define DoIP_GetSizeOfIpAddrAssignmentDyn()                                                         DoIP_GetSizeOfIpAddrAssignmentDynOfPCConfig()
#define DoIP_GetSizeOfLocalAddr()                                                                   DoIP_GetSizeOfLocalAddrOfPCConfig()
#define DoIP_GetSizeOfPduRRxCancelPduId()                                                           DoIP_GetSizeOfPduRRxCancelPduIdOfPCConfig()
#define DoIP_GetSizeOfPduRTxPduId()                                                                 DoIP_GetSizeOfPduRTxPduIdOfPCConfig()
#define DoIP_GetSizeOfRoutActivHandler()                                                            DoIP_GetSizeOfRoutActivHandlerOfPCConfig()
#define DoIP_GetSizeOfRoutingActivation()                                                           DoIP_GetSizeOfRoutingActivationOfPCConfig()
#define DoIP_GetSizeOfRoutingActivationInd()                                                        DoIP_GetSizeOfRoutingActivationIndOfPCConfig()
#define DoIP_GetSizeOfRxHdrBuf()                                                                    DoIP_GetSizeOfRxHdrBufOfPCConfig()
#define DoIP_GetSizeOfTester()                                                                      DoIP_GetSizeOfTesterOfPCConfig()
#define DoIP_GetSizeOfTesterDyn()                                                                   DoIP_GetSizeOfTesterDynOfPCConfig()
#define DoIP_GetSizeOfTxHdrBuf()                                                                    DoIP_GetSizeOfTxHdrBufOfPCConfig()
#define DoIP_GetSizeOfTxTcpMgt()                                                                    DoIP_GetSizeOfTxTcpMgtOfPCConfig()
#define DoIP_GetSizeOfTxTcpMgtDyn()                                                                 DoIP_GetSizeOfTxTcpMgtDynOfPCConfig()
#define DoIP_GetSizeOfTxUdpMgtList()                                                                DoIP_GetSizeOfTxUdpMgtListOfPCConfig()
#define DoIP_IsCentralSecurityOfTester(Index)                                                       (((!(DoIP_IsDiagNAckBufUsedOfTester(Index)))) != FALSE)  /**< indicates if a further action is required */
#define DoIP_GetDiagNAckBufEndIdxOfTester(Index)                                                    ((DoIP_DiagNAckBufEndIdxOfTesterType)((((DoIP_DiagNAckBufEndIdxOfTesterType)(Index)) + 256u)))  /**< the end index of the 0:n relation pointing to DoIP_DiagNAckBuf */
#define DoIP_GetDiagNAckBufStartIdxOfTester(Index)                                                  ((DoIP_DiagNAckBufStartIdxOfTesterType)((Index)))  /**< the start index of the 0:n relation pointing to DoIP_DiagNAckBuf */
#define DoIP_GetMaskedBitsOfTester(Index)                                                           ((DoIP_MaskedBitsOfTesterType)((((DoIP_MaskedBitsOfTesterType)(Index)) + 0x01u)))  /**< contains bitcoded the boolean data of DoIP_CentralSecurityOfTester, DoIP_DiagNAckBufUsedOfTester */
#define DoIP_GetRoutingActivationIndEndIdxOfTester(Index)                                           ((DoIP_RoutingActivationIndEndIdxOfTesterType)((((DoIP_RoutingActivationIndEndIdxOfTesterType)(Index)) + 1u)))  /**< the end index of the 1:n relation pointing to DoIP_RoutingActivationInd */
#define DoIP_GetRoutingActivationIndStartIdxOfTester(Index)                                         ((DoIP_RoutingActivationIndStartIdxOfTesterType)((Index)))  /**< the start index of the 1:n relation pointing to DoIP_RoutingActivationInd */
#define DoIP_GetTesterAddrOfTester(Index)                                                           ((DoIP_TesterAddrOfTesterType)((((DoIP_TesterAddrOfTesterType)(Index)) + 0x0E80u)))  /**< testers active address */
#define DoIP_GetTxHdrBufEndIdxOfTxTcpMgt(Index)                                                     ((DoIP_TxHdrBufEndIdxOfTxTcpMgtType)((DoIP_GetTxHdrBufStartIdxOfTxTcpMgt(Index) + 21u)))  /**< the end index of the 1:n relation pointing to DoIP_TxHdrBuf */
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCSetDataMacros  DoIP Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define DoIP_SetConnectionTcpIdxOfAliveCheckList(Index, Value)                                      DoIP_GetAliveCheckListOfPCConfig()[(Index)].ConnectionTcpIdxOfAliveCheckList = (Value)
#define DoIP_SetTxMsgLenOfChannelDyn(Index, Value)                                                  DoIP_GetChannelDynOfPCConfig()[(Index)].TxMsgLenOfChannelDyn = (Value)
#define DoIP_SetIpAddrStateOfConnectionDyn(Index, Value)                                            DoIP_GetConnectionDynOfPCConfig()[(Index)].IpAddrStateOfConnectionDyn = (Value)
#define DoIP_SetSoConClosingOfConnectionDyn(Index, Value)                                           DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConClosingOfConnectionDyn = (Value)
#define DoIP_SetSoConIdOfConnectionDyn(Index, Value)                                                DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConIdOfConnectionDyn = (Value)
#define DoIP_SetSoConStateOfConnectionDyn(Index, Value)                                             DoIP_GetConnectionDynOfPCConfig()[(Index)].SoConStateOfConnectionDyn = (Value)
#define DoIP_SetActivStateOfConnectionTcpDyn(Index, Value)                                          DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ActivStateOfConnectionTcpDyn = (Value)
#define DoIP_SetChannelRxActiveOfConnectionTcpDyn(Index, Value)                                     DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ChannelRxActiveOfConnectionTcpDyn = (Value)
#define DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(Index, Value)                                    DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].ChannelRxLastIdxOfConnectionTcpDyn = (Value)
#define DoIP_SetInactivCntOfConnectionTcpDyn(Index, Value)                                          DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].InactivCntOfConnectionTcpDyn = (Value)
#define DoIP_SetLastRxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastRxBufSizeOfConnectionTcpDyn = (Value)
#define DoIP_SetLastRxTgtAddrOfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastRxTgtAddrOfConnectionTcpDyn = (Value)
#define DoIP_SetLastTxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].LastTxBufSizeOfConnectionTcpDyn = (Value)
#define DoIP_SetRoutingActivationIdxOfConnectionTcpDyn(Index, Value)                                DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RoutingActivationIdxOfConnectionTcpDyn = (Value)
#define DoIP_SetRxMsgOffsetOfConnectionTcpDyn(Index, Value)                                         DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RxMsgOffsetOfConnectionTcpDyn = (Value)
#define DoIP_SetRxTpSessionActiveOfConnectionTcpDyn(Index, Value)                                   DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].RxTpSessionActiveOfConnectionTcpDyn = (Value)
#define DoIP_SetSkipRxMsgOfConnectionTcpDyn(Index, Value)                                           DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].SkipRxMsgOfConnectionTcpDyn = (Value)
#define DoIP_SetTesterAddrOfConnectionTcpDyn(Index, Value)                                          DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TesterAddrOfConnectionTcpDyn = (Value)
#define DoIP_SetTesterIdxOfConnectionTcpDyn(Index, Value)                                           DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TesterIdxOfConnectionTcpDyn = (Value)
#define DoIP_SetTpTxPreCloseSocketOfConnectionTcpDyn(Index, Value)                                  DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreCloseSocketOfConnectionTcpDyn = (Value)
#define DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(Index, Value)                                      DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreHdrTypeOfConnectionTcpDyn = (Value)
#define DoIP_SetTpTxPreParam1OfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam1OfConnectionTcpDyn = (Value)
#define DoIP_SetTpTxPreParam2OfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam2OfConnectionTcpDyn = (Value)
#define DoIP_SetTpTxPreParam3OfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TpTxPreParam3OfConnectionTcpDyn = (Value)
#define DoIP_SetTxBytesCopiedOfConnectionTcpDyn(Index, Value)                                       DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxBytesCopiedOfConnectionTcpDyn = (Value)
#define DoIP_SetTxTcpMgtQueIdxOfConnectionTcpDyn(Index, Value)                                      DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTcpMgtQueIdxOfConnectionTcpDyn = (Value)
#define DoIP_SetTxTcpMgtQueLvlOfConnectionTcpDyn(Index, Value)                                      DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTcpMgtQueLvlOfConnectionTcpDyn = (Value)
#define DoIP_SetTxTpSessionActiveOfConnectionTcpDyn(Index, Value)                                   DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].TxTpSessionActiveOfConnectionTcpDyn = (Value)
#define DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(Index, Value)                                   DoIP_GetConnectionTcpDynOfPCConfig()[(Index)].VerifyRxPduOffsetOfConnectionTcpDyn = (Value)
#define DoIP_SetDiagNAckBuf(Index, Value)                                                           DoIP_GetDiagNAckBufOfPCConfig()[(Index)] = (Value)
#define DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(Index, Value)                                   DoIP_GetIpAddrAssignmentDynOfPCConfig()[(Index)].IpAddrReqStateOfIpAddrAssignmentDyn = (Value)
#define DoIP_SetAliveCheckCntOfRoutActivHandler(Index, Value)                                       DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].AliveCheckCntOfRoutActivHandler = (Value)
#define DoIP_SetAliveCheckElemNumOfRoutActivHandler(Index, Value)                                   DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].AliveCheckElemNumOfRoutActivHandler = (Value)
#define DoIP_SetConnectionTcpIdxOfRoutActivHandler(Index, Value)                                    DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].ConnectionTcpIdxOfRoutActivHandler = (Value)
#define DoIP_SetOemSpecReqOfRoutActivHandler(Index, Value)                                          DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecReqOfRoutActivHandler = (Value)
#define DoIP_SetOemSpecResOfRoutActivHandler(Index, Value)                                          DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecResOfRoutActivHandler = (Value)
#define DoIP_SetOemSpecUsedOfRoutActivHandler(Index, Value)                                         DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].OemSpecUsedOfRoutActivHandler = (Value)
#define DoIP_SetRoutingActivationIdxOfRoutActivHandler(Index, Value)                                DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].RoutingActivationIdxOfRoutActivHandler = (Value)
#define DoIP_SetTesterAddrOfRoutActivHandler(Index, Value)                                          DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].TesterAddrOfRoutActivHandler = (Value)
#define DoIP_SetTesterIdxOfRoutActivHandler(Index, Value)                                           DoIP_GetRoutActivHandlerOfPCConfig()[(Index)].TesterIdxOfRoutActivHandler = (Value)
#define DoIP_SetRxHdrBuf(Index, Value)                                                              DoIP_GetRxHdrBufOfPCConfig()[(Index)] = (Value)
#define DoIP_SetConnectionTcpIdxOfTesterDyn(Index, Value)                                           DoIP_GetTesterDynOfPCConfig()[(Index)].ConnectionTcpIdxOfTesterDyn = (Value)
#define DoIP_SetDiagNAckOffsetOfTesterDyn(Index, Value)                                             DoIP_GetTesterDynOfPCConfig()[(Index)].DiagNAckOffsetOfTesterDyn = (Value)
#define DoIP_SetTxHdrBuf(Index, Value)                                                              DoIP_GetTxHdrBufOfPCConfig()[(Index)] = (Value)
#define DoIP_SetChannelIdxOfTxTcpMgtDyn(Index, Value)                                               DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].ChannelIdxOfTxTcpMgtDyn = (Value)
#define DoIP_SetMsgOfTxTcpMgtDyn(Index, Value)                                                      DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].MsgOfTxTcpMgtDyn = (Value)
#define DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(Index, Value)                                              DoIP_GetTxTcpMgtDynOfPCConfig()[(Index)].TxHdrBufLenOfTxTcpMgtDyn = (Value)
#define DoIP_SetConnectionIdxOfTxUdpMgtList(Index, Value)                                           DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].ConnectionIdxOfTxUdpMgtList = (Value)
#define DoIP_SetHdrTypeOfTxUdpMgtList(Index, Value)                                                 DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].HdrTypeOfTxUdpMgtList = (Value)
#define DoIP_SetParam1OfTxUdpMgtList(Index, Value)                                                  DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].Param1OfTxUdpMgtList = (Value)
#define DoIP_SetParam2OfTxUdpMgtList(Index, Value)                                                  DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].Param2OfTxUdpMgtList = (Value)
#define DoIP_SetRemoteAddrOfTxUdpMgtList(Index, Value)                                              DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].RemoteAddrOfTxUdpMgtList = (Value)
#define DoIP_SetRetryAttemptOfTxUdpMgtList(Index, Value)                                            DoIP_GetTxUdpMgtListOfPCConfig()[(Index)].RetryAttemptOfTxUdpMgtList = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCGetAddressOfDataMacros  DoIP Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define DoIP_GetAddrDiagNAckBuf(Index)                                                              (&DoIP_GetDiagNAckBuf(Index))
#define DoIP_GetAddrEId(Index)                                                                      (&DoIP_GetEId(Index))
#define DoIP_GetAddrGId(Index)                                                                      (&DoIP_GetGId(Index))
#define DoIP_GetAddrRxHdrBuf(Index)                                                                 (&DoIP_GetRxHdrBuf(Index))
#define DoIP_GetAddrTxHdrBuf(Index)                                                                 (&DoIP_GetTxHdrBuf(Index))
#define DoIP_GetAddrMsgOfTxTcpMgtDyn(Index)                                                         (&DoIP_GetMsgOfTxTcpMgtDyn(Index))
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCHasMacros  DoIP Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define DoIP_HasAliveCheckList()                                                                    (DoIP_GetAliveCheckListOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionTcpIdxOfAliveCheckList()                                                  (TRUE != FALSE)
#define DoIP_HasChannel()                                                                           (DoIP_GetChannelOfPCConfig() != NULL_PTR)
#define DoIP_HasBitMaskOfChannel()                                                                  (TRUE != FALSE)
#define DoIP_HasEcuAddrOfChannel()                                                                  (TRUE != FALSE)
#define DoIP_HasPduRRxPduIdOfChannel()                                                              (TRUE != FALSE)
#define DoIP_HasPduRTxConfPduIdOfChannel()                                                          (TRUE != FALSE)
#define DoIP_HasTesterIdxOfChannel()                                                                (TRUE != FALSE)
#define DoIP_HasTpMaxLenOfChannel()                                                                 (TRUE != FALSE)
#define DoIP_HasChannelDyn()                                                                        (DoIP_GetChannelDynOfPCConfig() != NULL_PTR)
#define DoIP_HasTxMsgLenOfChannelDyn()                                                              (TRUE != FALSE)
#define DoIP_HasChannelInd()                                                                        (DoIP_GetChannelIndOfPCConfig() != NULL_PTR)
#define DoIP_HasConnection()                                                                        (DoIP_GetConnectionOfPCConfig() != NULL_PTR)
#define DoIP_HasLocalAddrIdxOfConnection()                                                          (TRUE != FALSE)
#define DoIP_HasRxCancelPduIdOfConnection()                                                         (TRUE != FALSE)
#define DoIP_HasSoAdTxPduIdOfConnection()                                                           (TRUE != FALSE)
#define DoIP_HasConnectionDyn()                                                                     (DoIP_GetConnectionDynOfPCConfig() != NULL_PTR)
#define DoIP_HasIpAddrStateOfConnectionDyn()                                                        (TRUE != FALSE)
#define DoIP_HasSoConClosingOfConnectionDyn()                                                       (TRUE != FALSE)
#define DoIP_HasSoConIdOfConnectionDyn()                                                            (TRUE != FALSE)
#define DoIP_HasSoConStateOfConnectionDyn()                                                         (TRUE != FALSE)
#define DoIP_HasConnectionGroup()                                                                   (DoIP_GetConnectionGroupOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionTcpIndEndIdxOfConnectionGroup()                                           (TRUE != FALSE)
#define DoIP_HasConnectionTcpIndStartIdxOfConnectionGroup()                                         (TRUE != FALSE)
#define DoIP_HasConnectionInd()                                                                     (DoIP_GetConnectionIndOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionTcp()                                                                     (DoIP_GetConnectionTcpOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionGroupIdxOfConnectionTcp()                                                 (TRUE != FALSE)
#define DoIP_HasRxHdrBufEndIdxOfConnectionTcp()                                                     (TRUE != FALSE)
#define DoIP_HasRxHdrBufStartIdxOfConnectionTcp()                                                   (TRUE != FALSE)
#define DoIP_HasSecurityRequiredOfConnectionTcp()                                                   (TRUE != FALSE)
#define DoIP_HasTxTcpMgtEndIdxOfConnectionTcp()                                                     (TRUE != FALSE)
#define DoIP_HasTxTcpMgtStartIdxOfConnectionTcp()                                                   (TRUE != FALSE)
#define DoIP_HasConnectionTcpDyn()                                                                  (DoIP_GetConnectionTcpDynOfPCConfig() != NULL_PTR)
#define DoIP_HasActivStateOfConnectionTcpDyn()                                                      (TRUE != FALSE)
#define DoIP_HasChannelRxActiveOfConnectionTcpDyn()                                                 (TRUE != FALSE)
#define DoIP_HasChannelRxLastIdxOfConnectionTcpDyn()                                                (TRUE != FALSE)
#define DoIP_HasInactivCntOfConnectionTcpDyn()                                                      (TRUE != FALSE)
#define DoIP_HasLastRxBufSizeOfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasLastRxTgtAddrOfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasLastTxBufSizeOfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasRoutingActivationIdxOfConnectionTcpDyn()                                            (TRUE != FALSE)
#define DoIP_HasRxMsgOffsetOfConnectionTcpDyn()                                                     (TRUE != FALSE)
#define DoIP_HasRxTpSessionActiveOfConnectionTcpDyn()                                               (TRUE != FALSE)
#define DoIP_HasSkipRxMsgOfConnectionTcpDyn()                                                       (TRUE != FALSE)
#define DoIP_HasTesterAddrOfConnectionTcpDyn()                                                      (TRUE != FALSE)
#define DoIP_HasTesterIdxOfConnectionTcpDyn()                                                       (TRUE != FALSE)
#define DoIP_HasTpTxPreCloseSocketOfConnectionTcpDyn()                                              (TRUE != FALSE)
#define DoIP_HasTpTxPreHdrTypeOfConnectionTcpDyn()                                                  (TRUE != FALSE)
#define DoIP_HasTpTxPreParam1OfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasTpTxPreParam2OfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasTpTxPreParam3OfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasTxBytesCopiedOfConnectionTcpDyn()                                                   (TRUE != FALSE)
#define DoIP_HasTxTcpMgtQueIdxOfConnectionTcpDyn()                                                  (TRUE != FALSE)
#define DoIP_HasTxTcpMgtQueLvlOfConnectionTcpDyn()                                                  (TRUE != FALSE)
#define DoIP_HasTxTpSessionActiveOfConnectionTcpDyn()                                               (TRUE != FALSE)
#define DoIP_HasVerifyRxPduOffsetOfConnectionTcpDyn()                                               (TRUE != FALSE)
#define DoIP_HasConnectionTcpInd()                                                                  (DoIP_GetConnectionTcpIndOfPCConfig() != NULL_PTR)
#define DoIP_HasDefaultTester()                                                                     (DoIP_GetDefaultTesterOfPCConfig() != NULL_PTR)
#define DoIP_HasTesterIdxOfDefaultTester()                                                          (TRUE != FALSE)
#define DoIP_HasDiagNAckBuf()                                                                       (DoIP_GetDiagNAckBufOfPCConfig() != NULL_PTR)
#define DoIP_HasEId()                                                                               (DoIP_GetEIdOfPCConfig() != NULL_PTR)
#define DoIP_HasGId()                                                                               (DoIP_GetGIdOfPCConfig() != NULL_PTR)
#define DoIP_HasIpAddrAssignment()                                                                  (DoIP_GetIpAddrAssignmentOfPCConfig() != NULL_PTR)
#define DoIP_HasAssignmentTypeOfIpAddrAssignment()                                                  (TRUE != FALSE)
#define DoIP_HasControlIpAssignmentOfIpAddrAssignment()                                             (TRUE != FALSE)
#define DoIP_HasIpAddrAssignmentDyn()                                                               (DoIP_GetIpAddrAssignmentDynOfPCConfig() != NULL_PTR)
#define DoIP_HasIpAddrReqStateOfIpAddrAssignmentDyn()                                               (TRUE != FALSE)
#define DoIP_HasLocalAddr()                                                                         (DoIP_GetLocalAddrOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionIndEndIdxOfLocalAddr()                                                    (TRUE != FALSE)
#define DoIP_HasConnectionIndStartIdxOfLocalAddr()                                                  (TRUE != FALSE)
#define DoIP_HasDomainTypeOfLocalAddr()                                                             (TRUE != FALSE)
#define DoIP_HasIpAddrAssignmentEndIdxOfLocalAddr()                                                 (TRUE != FALSE)
#define DoIP_HasIpAddrAssignmentStartIdxOfLocalAddr()                                               (TRUE != FALSE)
#define DoIP_HasTcpIpLocalAddrIdOfLocalAddr()                                                       (TRUE != FALSE)
#define DoIP_HasUdpAliveTimeoutOfLocalAddr()                                                        (TRUE != FALSE)
#define DoIP_HasPduRRxCancelPduId()                                                                 (DoIP_GetPduRRxCancelPduIdOfPCConfig() != NULL_PTR)
#define DoIP_HasChannelIdxOfPduRRxCancelPduId()                                                     (TRUE != FALSE)
#define DoIP_HasPduRTxPduId()                                                                       (DoIP_GetPduRTxPduIdOfPCConfig() != NULL_PTR)
#define DoIP_HasChannelIdxOfPduRTxPduId()                                                           (TRUE != FALSE)
#define DoIP_HasRoutActivHandler()                                                                  (DoIP_GetRoutActivHandlerOfPCConfig() != NULL_PTR)
#define DoIP_HasAliveCheckCntOfRoutActivHandler()                                                   (TRUE != FALSE)
#define DoIP_HasAliveCheckElemNumOfRoutActivHandler()                                               (TRUE != FALSE)
#define DoIP_HasConnectionTcpIdxOfRoutActivHandler()                                                (TRUE != FALSE)
#define DoIP_HasOemSpecReqOfRoutActivHandler()                                                      (TRUE != FALSE)
#define DoIP_HasOemSpecResOfRoutActivHandler()                                                      (TRUE != FALSE)
#define DoIP_HasOemSpecUsedOfRoutActivHandler()                                                     (TRUE != FALSE)
#define DoIP_HasRoutingActivationIdxOfRoutActivHandler()                                            (TRUE != FALSE)
#define DoIP_HasTesterAddrOfRoutActivHandler()                                                      (TRUE != FALSE)
#define DoIP_HasTesterIdxOfRoutActivHandler()                                                       (TRUE != FALSE)
#define DoIP_HasRoutingActivation()                                                                 (DoIP_GetRoutingActivationOfPCConfig() != NULL_PTR)
#define DoIP_HasAuthFuncPtrOfRoutingActivation()                                                    (TRUE != FALSE)
#define DoIP_HasAuthFuncWithRemAddrOfRoutingActivation()                                            (TRUE != FALSE)
#define DoIP_HasAuthReqLengthOfRoutingActivation()                                                  (TRUE != FALSE)
#define DoIP_HasAuthResLengthOfRoutingActivation()                                                  (TRUE != FALSE)
#define DoIP_HasAuthWithRemAddrFuncPtrOfRoutingActivation()                                         (TRUE != FALSE)
#define DoIP_HasBitmaskingUsedOfRoutingActivation()                                                 (TRUE != FALSE)
#define DoIP_HasChannelIndEndIdxOfRoutingActivation()                                               (TRUE != FALSE)
#define DoIP_HasChannelIndStartIdxOfRoutingActivation()                                             (TRUE != FALSE)
#define DoIP_HasChannelIndUsedOfRoutingActivation()                                                 (TRUE != FALSE)
#define DoIP_HasConfFuncPtrOfRoutingActivation()                                                    (TRUE != FALSE)
#define DoIP_HasConfFuncWithRemAddrOfRoutingActivation()                                            (TRUE != FALSE)
#define DoIP_HasConfReqLengthOfRoutingActivation()                                                  (TRUE != FALSE)
#define DoIP_HasConfResLengthOfRoutingActivation()                                                  (TRUE != FALSE)
#define DoIP_HasConfWithRemAddrFuncPtrOfRoutingActivation()                                         (TRUE != FALSE)
#define DoIP_HasMaskedBitsOfRoutingActivation()                                                     (TRUE != FALSE)
#define DoIP_HasRoutingActivationNumOfRoutingActivation()                                           (TRUE != FALSE)
#define DoIP_HasSecurityRequiredOfRoutingActivation()                                               (TRUE != FALSE)
#define DoIP_HasRoutingActivationInd()                                                              (DoIP_GetRoutingActivationIndOfPCConfig() != NULL_PTR)
#define DoIP_HasRxHdrBuf()                                                                          (DoIP_GetRxHdrBufOfPCConfig() != NULL_PTR)
#define DoIP_HasSizeOfAliveCheckList()                                                              (TRUE != FALSE)
#define DoIP_HasSizeOfChannel()                                                                     (TRUE != FALSE)
#define DoIP_HasSizeOfChannelDyn()                                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfChannelInd()                                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfConnection()                                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionDyn()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionGroup()                                                             (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionInd()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcp()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcpDyn()                                                            (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcpInd()                                                            (TRUE != FALSE)
#define DoIP_HasSizeOfDefaultTester()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfDiagNAckBuf()                                                                 (TRUE != FALSE)
#define DoIP_HasSizeOfEId()                                                                         (TRUE != FALSE)
#define DoIP_HasSizeOfGId()                                                                         (TRUE != FALSE)
#define DoIP_HasSizeOfIpAddrAssignment()                                                            (TRUE != FALSE)
#define DoIP_HasSizeOfIpAddrAssignmentDyn()                                                         (TRUE != FALSE)
#define DoIP_HasSizeOfLocalAddr()                                                                   (TRUE != FALSE)
#define DoIP_HasSizeOfPduRRxCancelPduId()                                                           (TRUE != FALSE)
#define DoIP_HasSizeOfPduRTxPduId()                                                                 (TRUE != FALSE)
#define DoIP_HasSizeOfRoutActivHandler()                                                            (TRUE != FALSE)
#define DoIP_HasSizeOfRoutingActivation()                                                           (TRUE != FALSE)
#define DoIP_HasSizeOfRoutingActivationInd()                                                        (TRUE != FALSE)
#define DoIP_HasSizeOfRxHdrBuf()                                                                    (TRUE != FALSE)
#define DoIP_HasSizeOfTester()                                                                      (TRUE != FALSE)
#define DoIP_HasSizeOfTesterDyn()                                                                   (TRUE != FALSE)
#define DoIP_HasSizeOfTxHdrBuf()                                                                    (TRUE != FALSE)
#define DoIP_HasSizeOfTxTcpMgt()                                                                    (TRUE != FALSE)
#define DoIP_HasSizeOfTxTcpMgtDyn()                                                                 (TRUE != FALSE)
#define DoIP_HasSizeOfTxUdpMgtList()                                                                (TRUE != FALSE)
#define DoIP_HasTester()                                                                            (DoIP_GetTesterOfPCConfig() != NULL_PTR)
#define DoIP_HasCentralSecurityOfTester()                                                           (TRUE != FALSE)
#define DoIP_HasDiagNAckBufEndIdxOfTester()                                                         (TRUE != FALSE)
#define DoIP_HasDiagNAckBufStartIdxOfTester()                                                       (TRUE != FALSE)
#define DoIP_HasDiagNAckBufUsedOfTester()                                                           (TRUE != FALSE)
#define DoIP_HasMaskedBitsOfTester()                                                                (TRUE != FALSE)
#define DoIP_HasRoutingActivationIndEndIdxOfTester()                                                (TRUE != FALSE)
#define DoIP_HasRoutingActivationIndStartIdxOfTester()                                              (TRUE != FALSE)
#define DoIP_HasTesterAddrOfTester()                                                                (TRUE != FALSE)
#define DoIP_HasTesterDyn()                                                                         (DoIP_GetTesterDynOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionTcpIdxOfTesterDyn()                                                       (TRUE != FALSE)
#define DoIP_HasDiagNAckOffsetOfTesterDyn()                                                         (TRUE != FALSE)
#define DoIP_HasTxHdrBuf()                                                                          (DoIP_GetTxHdrBufOfPCConfig() != NULL_PTR)
#define DoIP_HasTxTcpMgt()                                                                          (DoIP_GetTxTcpMgtOfPCConfig() != NULL_PTR)
#define DoIP_HasTxHdrBufEndIdxOfTxTcpMgt()                                                          (TRUE != FALSE)
#define DoIP_HasTxHdrBufStartIdxOfTxTcpMgt()                                                        (TRUE != FALSE)
#define DoIP_HasTxTcpMgtDyn()                                                                       (DoIP_GetTxTcpMgtDynOfPCConfig() != NULL_PTR)
#define DoIP_HasChannelIdxOfTxTcpMgtDyn()                                                           (TRUE != FALSE)
#define DoIP_HasMsgOfTxTcpMgtDyn()                                                                  (TRUE != FALSE)
#define DoIP_HasTxHdrBufLenOfTxTcpMgtDyn()                                                          (TRUE != FALSE)
#define DoIP_HasTxUdpMgtList()                                                                      (DoIP_GetTxUdpMgtListOfPCConfig() != NULL_PTR)
#define DoIP_HasConnectionIdxOfTxUdpMgtList()                                                       (TRUE != FALSE)
#define DoIP_HasHdrTypeOfTxUdpMgtList()                                                             (TRUE != FALSE)
#define DoIP_HasParam1OfTxUdpMgtList()                                                              (TRUE != FALSE)
#define DoIP_HasParam2OfTxUdpMgtList()                                                              (TRUE != FALSE)
#define DoIP_HasRemoteAddrOfTxUdpMgtList()                                                          (TRUE != FALSE)
#define DoIP_HasRetryAttemptOfTxUdpMgtList()                                                        (TRUE != FALSE)
#define DoIP_HasPCConfig()                                                                          (TRUE != FALSE)
#define DoIP_HasAliveCheckListOfPCConfig()                                                          (TRUE != FALSE)
#define DoIP_HasChannelDynOfPCConfig()                                                              (TRUE != FALSE)
#define DoIP_HasChannelIndOfPCConfig()                                                              (TRUE != FALSE)
#define DoIP_HasChannelOfPCConfig()                                                                 (TRUE != FALSE)
#define DoIP_HasConnectionDynOfPCConfig()                                                           (TRUE != FALSE)
#define DoIP_HasConnectionGroupOfPCConfig()                                                         (TRUE != FALSE)
#define DoIP_HasConnectionIndOfPCConfig()                                                           (TRUE != FALSE)
#define DoIP_HasConnectionOfPCConfig()                                                              (TRUE != FALSE)
#define DoIP_HasConnectionTcpDynOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasConnectionTcpIndOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasConnectionTcpOfPCConfig()                                                           (TRUE != FALSE)
#define DoIP_HasDefaultTesterOfPCConfig()                                                           (TRUE != FALSE)
#define DoIP_HasDiagNAckBufOfPCConfig()                                                             (TRUE != FALSE)
#define DoIP_HasEIdOfPCConfig()                                                                     (TRUE != FALSE)
#define DoIP_HasGIdOfPCConfig()                                                                     (TRUE != FALSE)
#define DoIP_HasIpAddrAssignmentDynOfPCConfig()                                                     (TRUE != FALSE)
#define DoIP_HasIpAddrAssignmentOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasLocalAddrOfPCConfig()                                                               (TRUE != FALSE)
#define DoIP_HasPduRRxCancelPduIdOfPCConfig()                                                       (TRUE != FALSE)
#define DoIP_HasPduRTxPduIdOfPCConfig()                                                             (TRUE != FALSE)
#define DoIP_HasRoutActivHandlerOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasRoutingActivationIndOfPCConfig()                                                    (TRUE != FALSE)
#define DoIP_HasRoutingActivationOfPCConfig()                                                       (TRUE != FALSE)
#define DoIP_HasRxHdrBufOfPCConfig()                                                                (TRUE != FALSE)
#define DoIP_HasSizeOfAliveCheckListOfPCConfig()                                                    (TRUE != FALSE)
#define DoIP_HasSizeOfChannelDynOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasSizeOfChannelIndOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasSizeOfChannelOfPCConfig()                                                           (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionDynOfPCConfig()                                                     (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionGroupOfPCConfig()                                                   (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionIndOfPCConfig()                                                     (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionOfPCConfig()                                                        (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcpDynOfPCConfig()                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcpIndOfPCConfig()                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfConnectionTcpOfPCConfig()                                                     (TRUE != FALSE)
#define DoIP_HasSizeOfDefaultTesterOfPCConfig()                                                     (TRUE != FALSE)
#define DoIP_HasSizeOfDiagNAckBufOfPCConfig()                                                       (TRUE != FALSE)
#define DoIP_HasSizeOfEIdOfPCConfig()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfGIdOfPCConfig()                                                               (TRUE != FALSE)
#define DoIP_HasSizeOfIpAddrAssignmentDynOfPCConfig()                                               (TRUE != FALSE)
#define DoIP_HasSizeOfIpAddrAssignmentOfPCConfig()                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfLocalAddrOfPCConfig()                                                         (TRUE != FALSE)
#define DoIP_HasSizeOfPduRRxCancelPduIdOfPCConfig()                                                 (TRUE != FALSE)
#define DoIP_HasSizeOfPduRTxPduIdOfPCConfig()                                                       (TRUE != FALSE)
#define DoIP_HasSizeOfRoutActivHandlerOfPCConfig()                                                  (TRUE != FALSE)
#define DoIP_HasSizeOfRoutingActivationIndOfPCConfig()                                              (TRUE != FALSE)
#define DoIP_HasSizeOfRoutingActivationOfPCConfig()                                                 (TRUE != FALSE)
#define DoIP_HasSizeOfRxHdrBufOfPCConfig()                                                          (TRUE != FALSE)
#define DoIP_HasSizeOfTesterDynOfPCConfig()                                                         (TRUE != FALSE)
#define DoIP_HasSizeOfTesterOfPCConfig()                                                            (TRUE != FALSE)
#define DoIP_HasSizeOfTxHdrBufOfPCConfig()                                                          (TRUE != FALSE)
#define DoIP_HasSizeOfTxTcpMgtDynOfPCConfig()                                                       (TRUE != FALSE)
#define DoIP_HasSizeOfTxTcpMgtOfPCConfig()                                                          (TRUE != FALSE)
#define DoIP_HasSizeOfTxUdpMgtListOfPCConfig()                                                      (TRUE != FALSE)
#define DoIP_HasTesterDynOfPCConfig()                                                               (TRUE != FALSE)
#define DoIP_HasTesterOfPCConfig()                                                                  (TRUE != FALSE)
#define DoIP_HasTxHdrBufOfPCConfig()                                                                (TRUE != FALSE)
#define DoIP_HasTxTcpMgtDynOfPCConfig()                                                             (TRUE != FALSE)
#define DoIP_HasTxTcpMgtOfPCConfig()                                                                (TRUE != FALSE)
#define DoIP_HasTxUdpMgtListOfPCConfig()                                                            (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCIncrementDataMacros  DoIP Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define DoIP_IncConnectionTcpIdxOfAliveCheckList(Index)                                             DoIP_GetConnectionTcpIdxOfAliveCheckList(Index)++
#define DoIP_IncTxMsgLenOfChannelDyn(Index)                                                         DoIP_GetTxMsgLenOfChannelDyn(Index)++
#define DoIP_IncIpAddrStateOfConnectionDyn(Index)                                                   DoIP_GetIpAddrStateOfConnectionDyn(Index)++
#define DoIP_IncSoConIdOfConnectionDyn(Index)                                                       DoIP_GetSoConIdOfConnectionDyn(Index)++
#define DoIP_IncSoConStateOfConnectionDyn(Index)                                                    DoIP_GetSoConStateOfConnectionDyn(Index)++
#define DoIP_IncActivStateOfConnectionTcpDyn(Index)                                                 DoIP_GetActivStateOfConnectionTcpDyn(Index)++
#define DoIP_IncChannelRxLastIdxOfConnectionTcpDyn(Index)                                           DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(Index)++
#define DoIP_IncInactivCntOfConnectionTcpDyn(Index)                                                 DoIP_GetInactivCntOfConnectionTcpDyn(Index)++
#define DoIP_IncLastRxBufSizeOfConnectionTcpDyn(Index)                                              DoIP_GetLastRxBufSizeOfConnectionTcpDyn(Index)++
#define DoIP_IncLastRxTgtAddrOfConnectionTcpDyn(Index)                                              DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(Index)++
#define DoIP_IncLastTxBufSizeOfConnectionTcpDyn(Index)                                              DoIP_GetLastTxBufSizeOfConnectionTcpDyn(Index)++
#define DoIP_IncRoutingActivationIdxOfConnectionTcpDyn(Index)                                       DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(Index)++
#define DoIP_IncRxMsgOffsetOfConnectionTcpDyn(Index)                                                DoIP_GetRxMsgOffsetOfConnectionTcpDyn(Index)++
#define DoIP_IncTesterAddrOfConnectionTcpDyn(Index)                                                 DoIP_GetTesterAddrOfConnectionTcpDyn(Index)++
#define DoIP_IncTesterIdxOfConnectionTcpDyn(Index)                                                  DoIP_GetTesterIdxOfConnectionTcpDyn(Index)++
#define DoIP_IncTpTxPreCloseSocketOfConnectionTcpDyn(Index)                                         DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(Index)++
#define DoIP_IncTpTxPreHdrTypeOfConnectionTcpDyn(Index)                                             DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(Index)++
#define DoIP_IncTpTxPreParam1OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam1OfConnectionTcpDyn(Index)++
#define DoIP_IncTpTxPreParam2OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam2OfConnectionTcpDyn(Index)++
#define DoIP_IncTpTxPreParam3OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam3OfConnectionTcpDyn(Index)++
#define DoIP_IncTxBytesCopiedOfConnectionTcpDyn(Index)                                              DoIP_GetTxBytesCopiedOfConnectionTcpDyn(Index)++
#define DoIP_IncTxTcpMgtQueIdxOfConnectionTcpDyn(Index)                                             DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(Index)++
#define DoIP_IncTxTcpMgtQueLvlOfConnectionTcpDyn(Index)                                             DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(Index)++
#define DoIP_IncVerifyRxPduOffsetOfConnectionTcpDyn(Index)                                          DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(Index)++
#define DoIP_IncDiagNAckBuf(Index)                                                                  DoIP_GetDiagNAckBuf(Index)++
#define DoIP_IncIpAddrReqStateOfIpAddrAssignmentDyn(Index)                                          DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(Index)++
#define DoIP_IncAliveCheckCntOfRoutActivHandler(Index)                                              DoIP_GetAliveCheckCntOfRoutActivHandler(Index)++
#define DoIP_IncAliveCheckElemNumOfRoutActivHandler(Index)                                          DoIP_GetAliveCheckElemNumOfRoutActivHandler(Index)++
#define DoIP_IncConnectionTcpIdxOfRoutActivHandler(Index)                                           DoIP_GetConnectionTcpIdxOfRoutActivHandler(Index)++
#define DoIP_IncOemSpecReqOfRoutActivHandler(Index)                                                 DoIP_GetOemSpecReqOfRoutActivHandler(Index)++
#define DoIP_IncOemSpecResOfRoutActivHandler(Index)                                                 DoIP_GetOemSpecResOfRoutActivHandler(Index)++
#define DoIP_IncRoutingActivationIdxOfRoutActivHandler(Index)                                       DoIP_GetRoutingActivationIdxOfRoutActivHandler(Index)++
#define DoIP_IncTesterAddrOfRoutActivHandler(Index)                                                 DoIP_GetTesterAddrOfRoutActivHandler(Index)++
#define DoIP_IncTesterIdxOfRoutActivHandler(Index)                                                  DoIP_GetTesterIdxOfRoutActivHandler(Index)++
#define DoIP_IncRxHdrBuf(Index)                                                                     DoIP_GetRxHdrBuf(Index)++
#define DoIP_IncConnectionTcpIdxOfTesterDyn(Index)                                                  DoIP_GetConnectionTcpIdxOfTesterDyn(Index)++
#define DoIP_IncDiagNAckOffsetOfTesterDyn(Index)                                                    DoIP_GetDiagNAckOffsetOfTesterDyn(Index)++
#define DoIP_IncTxHdrBuf(Index)                                                                     DoIP_GetTxHdrBuf(Index)++
#define DoIP_IncChannelIdxOfTxTcpMgtDyn(Index)                                                      DoIP_GetChannelIdxOfTxTcpMgtDyn(Index)++
#define DoIP_IncMsgOfTxTcpMgtDyn(Index)                                                             DoIP_GetMsgOfTxTcpMgtDyn(Index)++
#define DoIP_IncTxHdrBufLenOfTxTcpMgtDyn(Index)                                                     DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(Index)++
#define DoIP_IncConnectionIdxOfTxUdpMgtList(Index)                                                  DoIP_GetConnectionIdxOfTxUdpMgtList(Index)++
#define DoIP_IncHdrTypeOfTxUdpMgtList(Index)                                                        DoIP_GetHdrTypeOfTxUdpMgtList(Index)++
#define DoIP_IncParam1OfTxUdpMgtList(Index)                                                         DoIP_GetParam1OfTxUdpMgtList(Index)++
#define DoIP_IncParam2OfTxUdpMgtList(Index)                                                         DoIP_GetParam2OfTxUdpMgtList(Index)++
#define DoIP_IncRemoteAddrOfTxUdpMgtList(Index)                                                     DoIP_GetRemoteAddrOfTxUdpMgtList(Index)++
#define DoIP_IncRetryAttemptOfTxUdpMgtList(Index)                                                   DoIP_GetRetryAttemptOfTxUdpMgtList(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCDecrementDataMacros  DoIP Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define DoIP_DecConnectionTcpIdxOfAliveCheckList(Index)                                             DoIP_GetConnectionTcpIdxOfAliveCheckList(Index)--
#define DoIP_DecTxMsgLenOfChannelDyn(Index)                                                         DoIP_GetTxMsgLenOfChannelDyn(Index)--
#define DoIP_DecIpAddrStateOfConnectionDyn(Index)                                                   DoIP_GetIpAddrStateOfConnectionDyn(Index)--
#define DoIP_DecSoConIdOfConnectionDyn(Index)                                                       DoIP_GetSoConIdOfConnectionDyn(Index)--
#define DoIP_DecSoConStateOfConnectionDyn(Index)                                                    DoIP_GetSoConStateOfConnectionDyn(Index)--
#define DoIP_DecActivStateOfConnectionTcpDyn(Index)                                                 DoIP_GetActivStateOfConnectionTcpDyn(Index)--
#define DoIP_DecChannelRxLastIdxOfConnectionTcpDyn(Index)                                           DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(Index)--
#define DoIP_DecInactivCntOfConnectionTcpDyn(Index)                                                 DoIP_GetInactivCntOfConnectionTcpDyn(Index)--
#define DoIP_DecLastRxBufSizeOfConnectionTcpDyn(Index)                                              DoIP_GetLastRxBufSizeOfConnectionTcpDyn(Index)--
#define DoIP_DecLastRxTgtAddrOfConnectionTcpDyn(Index)                                              DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(Index)--
#define DoIP_DecLastTxBufSizeOfConnectionTcpDyn(Index)                                              DoIP_GetLastTxBufSizeOfConnectionTcpDyn(Index)--
#define DoIP_DecRoutingActivationIdxOfConnectionTcpDyn(Index)                                       DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(Index)--
#define DoIP_DecRxMsgOffsetOfConnectionTcpDyn(Index)                                                DoIP_GetRxMsgOffsetOfConnectionTcpDyn(Index)--
#define DoIP_DecTesterAddrOfConnectionTcpDyn(Index)                                                 DoIP_GetTesterAddrOfConnectionTcpDyn(Index)--
#define DoIP_DecTesterIdxOfConnectionTcpDyn(Index)                                                  DoIP_GetTesterIdxOfConnectionTcpDyn(Index)--
#define DoIP_DecTpTxPreCloseSocketOfConnectionTcpDyn(Index)                                         DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(Index)--
#define DoIP_DecTpTxPreHdrTypeOfConnectionTcpDyn(Index)                                             DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(Index)--
#define DoIP_DecTpTxPreParam1OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam1OfConnectionTcpDyn(Index)--
#define DoIP_DecTpTxPreParam2OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam2OfConnectionTcpDyn(Index)--
#define DoIP_DecTpTxPreParam3OfConnectionTcpDyn(Index)                                              DoIP_GetTpTxPreParam3OfConnectionTcpDyn(Index)--
#define DoIP_DecTxBytesCopiedOfConnectionTcpDyn(Index)                                              DoIP_GetTxBytesCopiedOfConnectionTcpDyn(Index)--
#define DoIP_DecTxTcpMgtQueIdxOfConnectionTcpDyn(Index)                                             DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(Index)--
#define DoIP_DecTxTcpMgtQueLvlOfConnectionTcpDyn(Index)                                             DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(Index)--
#define DoIP_DecVerifyRxPduOffsetOfConnectionTcpDyn(Index)                                          DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(Index)--
#define DoIP_DecDiagNAckBuf(Index)                                                                  DoIP_GetDiagNAckBuf(Index)--
#define DoIP_DecIpAddrReqStateOfIpAddrAssignmentDyn(Index)                                          DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(Index)--
#define DoIP_DecAliveCheckCntOfRoutActivHandler(Index)                                              DoIP_GetAliveCheckCntOfRoutActivHandler(Index)--
#define DoIP_DecAliveCheckElemNumOfRoutActivHandler(Index)                                          DoIP_GetAliveCheckElemNumOfRoutActivHandler(Index)--
#define DoIP_DecConnectionTcpIdxOfRoutActivHandler(Index)                                           DoIP_GetConnectionTcpIdxOfRoutActivHandler(Index)--
#define DoIP_DecOemSpecReqOfRoutActivHandler(Index)                                                 DoIP_GetOemSpecReqOfRoutActivHandler(Index)--
#define DoIP_DecOemSpecResOfRoutActivHandler(Index)                                                 DoIP_GetOemSpecResOfRoutActivHandler(Index)--
#define DoIP_DecRoutingActivationIdxOfRoutActivHandler(Index)                                       DoIP_GetRoutingActivationIdxOfRoutActivHandler(Index)--
#define DoIP_DecTesterAddrOfRoutActivHandler(Index)                                                 DoIP_GetTesterAddrOfRoutActivHandler(Index)--
#define DoIP_DecTesterIdxOfRoutActivHandler(Index)                                                  DoIP_GetTesterIdxOfRoutActivHandler(Index)--
#define DoIP_DecRxHdrBuf(Index)                                                                     DoIP_GetRxHdrBuf(Index)--
#define DoIP_DecConnectionTcpIdxOfTesterDyn(Index)                                                  DoIP_GetConnectionTcpIdxOfTesterDyn(Index)--
#define DoIP_DecDiagNAckOffsetOfTesterDyn(Index)                                                    DoIP_GetDiagNAckOffsetOfTesterDyn(Index)--
#define DoIP_DecTxHdrBuf(Index)                                                                     DoIP_GetTxHdrBuf(Index)--
#define DoIP_DecChannelIdxOfTxTcpMgtDyn(Index)                                                      DoIP_GetChannelIdxOfTxTcpMgtDyn(Index)--
#define DoIP_DecMsgOfTxTcpMgtDyn(Index)                                                             DoIP_GetMsgOfTxTcpMgtDyn(Index)--
#define DoIP_DecTxHdrBufLenOfTxTcpMgtDyn(Index)                                                     DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(Index)--
#define DoIP_DecConnectionIdxOfTxUdpMgtList(Index)                                                  DoIP_GetConnectionIdxOfTxUdpMgtList(Index)--
#define DoIP_DecHdrTypeOfTxUdpMgtList(Index)                                                        DoIP_GetHdrTypeOfTxUdpMgtList(Index)--
#define DoIP_DecParam1OfTxUdpMgtList(Index)                                                         DoIP_GetParam1OfTxUdpMgtList(Index)--
#define DoIP_DecParam2OfTxUdpMgtList(Index)                                                         DoIP_GetParam2OfTxUdpMgtList(Index)--
#define DoIP_DecRemoteAddrOfTxUdpMgtList(Index)                                                     DoIP_GetRemoteAddrOfTxUdpMgtList(Index)--
#define DoIP_DecRetryAttemptOfTxUdpMgtList(Index)                                                   DoIP_GetRetryAttemptOfTxUdpMgtList(Index)--
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCAddDataMacros  DoIP Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/ 
#define DoIP_AddConnectionTcpIdxOfAliveCheckList(Index, Value)                                      DoIP_SetConnectionTcpIdxOfAliveCheckList(Index, (DoIP_GetConnectionTcpIdxOfAliveCheckList(Index) + Value))
#define DoIP_AddTxMsgLenOfChannelDyn(Index, Value)                                                  DoIP_SetTxMsgLenOfChannelDyn(Index, (DoIP_GetTxMsgLenOfChannelDyn(Index) + Value))
#define DoIP_AddIpAddrStateOfConnectionDyn(Index, Value)                                            DoIP_SetIpAddrStateOfConnectionDyn(Index, (DoIP_GetIpAddrStateOfConnectionDyn(Index) + Value))
#define DoIP_AddSoConIdOfConnectionDyn(Index, Value)                                                DoIP_SetSoConIdOfConnectionDyn(Index, (DoIP_GetSoConIdOfConnectionDyn(Index) + Value))
#define DoIP_AddSoConStateOfConnectionDyn(Index, Value)                                             DoIP_SetSoConStateOfConnectionDyn(Index, (DoIP_GetSoConStateOfConnectionDyn(Index) + Value))
#define DoIP_AddActivStateOfConnectionTcpDyn(Index, Value)                                          DoIP_SetActivStateOfConnectionTcpDyn(Index, (DoIP_GetActivStateOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddChannelRxLastIdxOfConnectionTcpDyn(Index, Value)                                    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(Index, (DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddInactivCntOfConnectionTcpDyn(Index, Value)                                          DoIP_SetInactivCntOfConnectionTcpDyn(Index, (DoIP_GetInactivCntOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddLastRxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastRxBufSizeOfConnectionTcpDyn(Index, (DoIP_GetLastRxBufSizeOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddLastRxTgtAddrOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastRxTgtAddrOfConnectionTcpDyn(Index, (DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddLastTxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastTxBufSizeOfConnectionTcpDyn(Index, (DoIP_GetLastTxBufSizeOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddRoutingActivationIdxOfConnectionTcpDyn(Index, Value)                                DoIP_SetRoutingActivationIdxOfConnectionTcpDyn(Index, (DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddRxMsgOffsetOfConnectionTcpDyn(Index, Value)                                         DoIP_SetRxMsgOffsetOfConnectionTcpDyn(Index, (DoIP_GetRxMsgOffsetOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTesterAddrOfConnectionTcpDyn(Index, Value)                                          DoIP_SetTesterAddrOfConnectionTcpDyn(Index, (DoIP_GetTesterAddrOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTesterIdxOfConnectionTcpDyn(Index, Value)                                           DoIP_SetTesterIdxOfConnectionTcpDyn(Index, (DoIP_GetTesterIdxOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTpTxPreCloseSocketOfConnectionTcpDyn(Index, Value)                                  DoIP_SetTpTxPreCloseSocketOfConnectionTcpDyn(Index, (DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTpTxPreHdrTypeOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(Index, (DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTpTxPreParam1OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam1OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam1OfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTpTxPreParam2OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam2OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam2OfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTpTxPreParam3OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam3OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam3OfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTxBytesCopiedOfConnectionTcpDyn(Index, Value)                                       DoIP_SetTxBytesCopiedOfConnectionTcpDyn(Index, (DoIP_GetTxBytesCopiedOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTxTcpMgtQueIdxOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTxTcpMgtQueIdxOfConnectionTcpDyn(Index, (DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddTxTcpMgtQueLvlOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTxTcpMgtQueLvlOfConnectionTcpDyn(Index, (DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddVerifyRxPduOffsetOfConnectionTcpDyn(Index, Value)                                   DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(Index, (DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(Index) + Value))
#define DoIP_AddDiagNAckBuf(Index, Value)                                                           DoIP_SetDiagNAckBuf(Index, (DoIP_GetDiagNAckBuf(Index) + Value))
#define DoIP_AddIpAddrReqStateOfIpAddrAssignmentDyn(Index, Value)                                   DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(Index, (DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(Index) + Value))
#define DoIP_AddAliveCheckCntOfRoutActivHandler(Index, Value)                                       DoIP_SetAliveCheckCntOfRoutActivHandler(Index, (DoIP_GetAliveCheckCntOfRoutActivHandler(Index) + Value))
#define DoIP_AddAliveCheckElemNumOfRoutActivHandler(Index, Value)                                   DoIP_SetAliveCheckElemNumOfRoutActivHandler(Index, (DoIP_GetAliveCheckElemNumOfRoutActivHandler(Index) + Value))
#define DoIP_AddConnectionTcpIdxOfRoutActivHandler(Index, Value)                                    DoIP_SetConnectionTcpIdxOfRoutActivHandler(Index, (DoIP_GetConnectionTcpIdxOfRoutActivHandler(Index) + Value))
#define DoIP_AddOemSpecReqOfRoutActivHandler(Index, Value)                                          DoIP_SetOemSpecReqOfRoutActivHandler(Index, (DoIP_GetOemSpecReqOfRoutActivHandler(Index) + Value))
#define DoIP_AddOemSpecResOfRoutActivHandler(Index, Value)                                          DoIP_SetOemSpecResOfRoutActivHandler(Index, (DoIP_GetOemSpecResOfRoutActivHandler(Index) + Value))
#define DoIP_AddRoutingActivationIdxOfRoutActivHandler(Index, Value)                                DoIP_SetRoutingActivationIdxOfRoutActivHandler(Index, (DoIP_GetRoutingActivationIdxOfRoutActivHandler(Index) + Value))
#define DoIP_AddTesterAddrOfRoutActivHandler(Index, Value)                                          DoIP_SetTesterAddrOfRoutActivHandler(Index, (DoIP_GetTesterAddrOfRoutActivHandler(Index) + Value))
#define DoIP_AddTesterIdxOfRoutActivHandler(Index, Value)                                           DoIP_SetTesterIdxOfRoutActivHandler(Index, (DoIP_GetTesterIdxOfRoutActivHandler(Index) + Value))
#define DoIP_AddRxHdrBuf(Index, Value)                                                              DoIP_SetRxHdrBuf(Index, (DoIP_GetRxHdrBuf(Index) + Value))
#define DoIP_AddConnectionTcpIdxOfTesterDyn(Index, Value)                                           DoIP_SetConnectionTcpIdxOfTesterDyn(Index, (DoIP_GetConnectionTcpIdxOfTesterDyn(Index) + Value))
#define DoIP_AddDiagNAckOffsetOfTesterDyn(Index, Value)                                             DoIP_SetDiagNAckOffsetOfTesterDyn(Index, (DoIP_GetDiagNAckOffsetOfTesterDyn(Index) + Value))
#define DoIP_AddTxHdrBuf(Index, Value)                                                              DoIP_SetTxHdrBuf(Index, (DoIP_GetTxHdrBuf(Index) + Value))
#define DoIP_AddChannelIdxOfTxTcpMgtDyn(Index, Value)                                               DoIP_SetChannelIdxOfTxTcpMgtDyn(Index, (DoIP_GetChannelIdxOfTxTcpMgtDyn(Index) + Value))
#define DoIP_AddMsgOfTxTcpMgtDyn(Index, Value)                                                      DoIP_SetMsgOfTxTcpMgtDyn(Index, (DoIP_GetMsgOfTxTcpMgtDyn(Index) + Value))
#define DoIP_AddTxHdrBufLenOfTxTcpMgtDyn(Index, Value)                                              DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(Index, (DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(Index) + Value))
#define DoIP_AddConnectionIdxOfTxUdpMgtList(Index, Value)                                           DoIP_SetConnectionIdxOfTxUdpMgtList(Index, (DoIP_GetConnectionIdxOfTxUdpMgtList(Index) + Value))
#define DoIP_AddHdrTypeOfTxUdpMgtList(Index, Value)                                                 DoIP_SetHdrTypeOfTxUdpMgtList(Index, (DoIP_GetHdrTypeOfTxUdpMgtList(Index) + Value))
#define DoIP_AddParam1OfTxUdpMgtList(Index, Value)                                                  DoIP_SetParam1OfTxUdpMgtList(Index, (DoIP_GetParam1OfTxUdpMgtList(Index) + Value))
#define DoIP_AddParam2OfTxUdpMgtList(Index, Value)                                                  DoIP_SetParam2OfTxUdpMgtList(Index, (DoIP_GetParam2OfTxUdpMgtList(Index) + Value))
#define DoIP_AddRemoteAddrOfTxUdpMgtList(Index, Value)                                              DoIP_SetRemoteAddrOfTxUdpMgtList(Index, (DoIP_GetRemoteAddrOfTxUdpMgtList(Index) + Value))
#define DoIP_AddRetryAttemptOfTxUdpMgtList(Index, Value)                                            DoIP_SetRetryAttemptOfTxUdpMgtList(Index, (DoIP_GetRetryAttemptOfTxUdpMgtList(Index) + Value))
/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCSubstractDataMacros  DoIP Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/ 
#define DoIP_SubConnectionTcpIdxOfAliveCheckList(Index, Value)                                      DoIP_SetConnectionTcpIdxOfAliveCheckList(Index, (DoIP_GetConnectionTcpIdxOfAliveCheckList(Index) - Value))
#define DoIP_SubTxMsgLenOfChannelDyn(Index, Value)                                                  DoIP_SetTxMsgLenOfChannelDyn(Index, (DoIP_GetTxMsgLenOfChannelDyn(Index) - Value))
#define DoIP_SubIpAddrStateOfConnectionDyn(Index, Value)                                            DoIP_SetIpAddrStateOfConnectionDyn(Index, (DoIP_GetIpAddrStateOfConnectionDyn(Index) - Value))
#define DoIP_SubSoConIdOfConnectionDyn(Index, Value)                                                DoIP_SetSoConIdOfConnectionDyn(Index, (DoIP_GetSoConIdOfConnectionDyn(Index) - Value))
#define DoIP_SubSoConStateOfConnectionDyn(Index, Value)                                             DoIP_SetSoConStateOfConnectionDyn(Index, (DoIP_GetSoConStateOfConnectionDyn(Index) - Value))
#define DoIP_SubActivStateOfConnectionTcpDyn(Index, Value)                                          DoIP_SetActivStateOfConnectionTcpDyn(Index, (DoIP_GetActivStateOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubChannelRxLastIdxOfConnectionTcpDyn(Index, Value)                                    DoIP_SetChannelRxLastIdxOfConnectionTcpDyn(Index, (DoIP_GetChannelRxLastIdxOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubInactivCntOfConnectionTcpDyn(Index, Value)                                          DoIP_SetInactivCntOfConnectionTcpDyn(Index, (DoIP_GetInactivCntOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubLastRxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastRxBufSizeOfConnectionTcpDyn(Index, (DoIP_GetLastRxBufSizeOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubLastRxTgtAddrOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastRxTgtAddrOfConnectionTcpDyn(Index, (DoIP_GetLastRxTgtAddrOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubLastTxBufSizeOfConnectionTcpDyn(Index, Value)                                       DoIP_SetLastTxBufSizeOfConnectionTcpDyn(Index, (DoIP_GetLastTxBufSizeOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubRoutingActivationIdxOfConnectionTcpDyn(Index, Value)                                DoIP_SetRoutingActivationIdxOfConnectionTcpDyn(Index, (DoIP_GetRoutingActivationIdxOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubRxMsgOffsetOfConnectionTcpDyn(Index, Value)                                         DoIP_SetRxMsgOffsetOfConnectionTcpDyn(Index, (DoIP_GetRxMsgOffsetOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTesterAddrOfConnectionTcpDyn(Index, Value)                                          DoIP_SetTesterAddrOfConnectionTcpDyn(Index, (DoIP_GetTesterAddrOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTesterIdxOfConnectionTcpDyn(Index, Value)                                           DoIP_SetTesterIdxOfConnectionTcpDyn(Index, (DoIP_GetTesterIdxOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTpTxPreCloseSocketOfConnectionTcpDyn(Index, Value)                                  DoIP_SetTpTxPreCloseSocketOfConnectionTcpDyn(Index, (DoIP_GetTpTxPreCloseSocketOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTpTxPreHdrTypeOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTpTxPreHdrTypeOfConnectionTcpDyn(Index, (DoIP_GetTpTxPreHdrTypeOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTpTxPreParam1OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam1OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam1OfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTpTxPreParam2OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam2OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam2OfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTpTxPreParam3OfConnectionTcpDyn(Index, Value)                                       DoIP_SetTpTxPreParam3OfConnectionTcpDyn(Index, (DoIP_GetTpTxPreParam3OfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTxBytesCopiedOfConnectionTcpDyn(Index, Value)                                       DoIP_SetTxBytesCopiedOfConnectionTcpDyn(Index, (DoIP_GetTxBytesCopiedOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTxTcpMgtQueIdxOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTxTcpMgtQueIdxOfConnectionTcpDyn(Index, (DoIP_GetTxTcpMgtQueIdxOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubTxTcpMgtQueLvlOfConnectionTcpDyn(Index, Value)                                      DoIP_SetTxTcpMgtQueLvlOfConnectionTcpDyn(Index, (DoIP_GetTxTcpMgtQueLvlOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubVerifyRxPduOffsetOfConnectionTcpDyn(Index, Value)                                   DoIP_SetVerifyRxPduOffsetOfConnectionTcpDyn(Index, (DoIP_GetVerifyRxPduOffsetOfConnectionTcpDyn(Index) - Value))
#define DoIP_SubDiagNAckBuf(Index, Value)                                                           DoIP_SetDiagNAckBuf(Index, (DoIP_GetDiagNAckBuf(Index) - Value))
#define DoIP_SubIpAddrReqStateOfIpAddrAssignmentDyn(Index, Value)                                   DoIP_SetIpAddrReqStateOfIpAddrAssignmentDyn(Index, (DoIP_GetIpAddrReqStateOfIpAddrAssignmentDyn(Index) - Value))
#define DoIP_SubAliveCheckCntOfRoutActivHandler(Index, Value)                                       DoIP_SetAliveCheckCntOfRoutActivHandler(Index, (DoIP_GetAliveCheckCntOfRoutActivHandler(Index) - Value))
#define DoIP_SubAliveCheckElemNumOfRoutActivHandler(Index, Value)                                   DoIP_SetAliveCheckElemNumOfRoutActivHandler(Index, (DoIP_GetAliveCheckElemNumOfRoutActivHandler(Index) - Value))
#define DoIP_SubConnectionTcpIdxOfRoutActivHandler(Index, Value)                                    DoIP_SetConnectionTcpIdxOfRoutActivHandler(Index, (DoIP_GetConnectionTcpIdxOfRoutActivHandler(Index) - Value))
#define DoIP_SubOemSpecReqOfRoutActivHandler(Index, Value)                                          DoIP_SetOemSpecReqOfRoutActivHandler(Index, (DoIP_GetOemSpecReqOfRoutActivHandler(Index) - Value))
#define DoIP_SubOemSpecResOfRoutActivHandler(Index, Value)                                          DoIP_SetOemSpecResOfRoutActivHandler(Index, (DoIP_GetOemSpecResOfRoutActivHandler(Index) - Value))
#define DoIP_SubRoutingActivationIdxOfRoutActivHandler(Index, Value)                                DoIP_SetRoutingActivationIdxOfRoutActivHandler(Index, (DoIP_GetRoutingActivationIdxOfRoutActivHandler(Index) - Value))
#define DoIP_SubTesterAddrOfRoutActivHandler(Index, Value)                                          DoIP_SetTesterAddrOfRoutActivHandler(Index, (DoIP_GetTesterAddrOfRoutActivHandler(Index) - Value))
#define DoIP_SubTesterIdxOfRoutActivHandler(Index, Value)                                           DoIP_SetTesterIdxOfRoutActivHandler(Index, (DoIP_GetTesterIdxOfRoutActivHandler(Index) - Value))
#define DoIP_SubRxHdrBuf(Index, Value)                                                              DoIP_SetRxHdrBuf(Index, (DoIP_GetRxHdrBuf(Index) - Value))
#define DoIP_SubConnectionTcpIdxOfTesterDyn(Index, Value)                                           DoIP_SetConnectionTcpIdxOfTesterDyn(Index, (DoIP_GetConnectionTcpIdxOfTesterDyn(Index) - Value))
#define DoIP_SubDiagNAckOffsetOfTesterDyn(Index, Value)                                             DoIP_SetDiagNAckOffsetOfTesterDyn(Index, (DoIP_GetDiagNAckOffsetOfTesterDyn(Index) - Value))
#define DoIP_SubTxHdrBuf(Index, Value)                                                              DoIP_SetTxHdrBuf(Index, (DoIP_GetTxHdrBuf(Index) - Value))
#define DoIP_SubChannelIdxOfTxTcpMgtDyn(Index, Value)                                               DoIP_SetChannelIdxOfTxTcpMgtDyn(Index, (DoIP_GetChannelIdxOfTxTcpMgtDyn(Index) - Value))
#define DoIP_SubMsgOfTxTcpMgtDyn(Index, Value)                                                      DoIP_SetMsgOfTxTcpMgtDyn(Index, (DoIP_GetMsgOfTxTcpMgtDyn(Index) - Value))
#define DoIP_SubTxHdrBufLenOfTxTcpMgtDyn(Index, Value)                                              DoIP_SetTxHdrBufLenOfTxTcpMgtDyn(Index, (DoIP_GetTxHdrBufLenOfTxTcpMgtDyn(Index) - Value))
#define DoIP_SubConnectionIdxOfTxUdpMgtList(Index, Value)                                           DoIP_SetConnectionIdxOfTxUdpMgtList(Index, (DoIP_GetConnectionIdxOfTxUdpMgtList(Index) - Value))
#define DoIP_SubHdrTypeOfTxUdpMgtList(Index, Value)                                                 DoIP_SetHdrTypeOfTxUdpMgtList(Index, (DoIP_GetHdrTypeOfTxUdpMgtList(Index) - Value))
#define DoIP_SubParam1OfTxUdpMgtList(Index, Value)                                                  DoIP_SetParam1OfTxUdpMgtList(Index, (DoIP_GetParam1OfTxUdpMgtList(Index) - Value))
#define DoIP_SubParam2OfTxUdpMgtList(Index, Value)                                                  DoIP_SetParam2OfTxUdpMgtList(Index, (DoIP_GetParam2OfTxUdpMgtList(Index) - Value))
#define DoIP_SubRemoteAddrOfTxUdpMgtList(Index, Value)                                              DoIP_SetRemoteAddrOfTxUdpMgtList(Index, (DoIP_GetRemoteAddrOfTxUdpMgtList(Index) - Value))
#define DoIP_SubRetryAttemptOfTxUdpMgtList(Index, Value)                                            DoIP_SetRetryAttemptOfTxUdpMgtList(Index, (DoIP_GetRetryAttemptOfTxUdpMgtList(Index) - Value))
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
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  DoIPPCIterableTypes  DoIP Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate DoIP_AliveCheckList */
typedef uint8_least DoIP_AliveCheckListIterType;

/**   \brief  type used to iterate DoIP_Channel */
typedef uint8_least DoIP_ChannelIterType;

/**   \brief  type used to iterate DoIP_ChannelInd */
typedef uint8_least DoIP_ChannelIndIterType;

/**   \brief  type used to iterate DoIP_Connection */
typedef uint8_least DoIP_ConnectionIterType;

/**   \brief  type used to iterate DoIP_ConnectionGroup */
typedef uint8_least DoIP_ConnectionGroupIterType;

/**   \brief  type used to iterate DoIP_ConnectionInd */
typedef uint8_least DoIP_ConnectionIndIterType;

/**   \brief  type used to iterate DoIP_ConnectionTcp */
typedef uint8_least DoIP_ConnectionTcpIterType;

/**   \brief  type used to iterate DoIP_ConnectionTcpInd */
typedef uint8_least DoIP_ConnectionTcpIndIterType;

/**   \brief  type used to iterate DoIP_DefaultTester */
typedef uint8_least DoIP_DefaultTesterIterType;

/**   \brief  type used to iterate DoIP_DiagNAckBuf */
typedef uint16_least DoIP_DiagNAckBufIterType;

/**   \brief  type used to iterate DoIP_EId */
typedef uint8_least DoIP_EIdIterType;

/**   \brief  type used to iterate DoIP_GId */
typedef uint8_least DoIP_GIdIterType;

/**   \brief  type used to iterate DoIP_IpAddrAssignment */
typedef uint8_least DoIP_IpAddrAssignmentIterType;

/**   \brief  type used to iterate DoIP_LocalAddr */
typedef uint8_least DoIP_LocalAddrIterType;

/**   \brief  type used to iterate DoIP_PduRRxCancelPduId */
typedef uint8_least DoIP_PduRRxCancelPduIdIterType;

/**   \brief  type used to iterate DoIP_PduRTxPduId */
typedef uint8_least DoIP_PduRTxPduIdIterType;

/**   \brief  type used to iterate DoIP_RoutActivHandler */
typedef uint8_least DoIP_RoutActivHandlerIterType;

/**   \brief  type used to iterate DoIP_RoutingActivation */
typedef uint8_least DoIP_RoutingActivationIterType;

/**   \brief  type used to iterate DoIP_RoutingActivationInd */
typedef uint8_least DoIP_RoutingActivationIndIterType;

/**   \brief  type used to iterate DoIP_RxHdrBuf */
typedef uint8_least DoIP_RxHdrBufIterType;

/**   \brief  type used to iterate DoIP_Tester */
typedef uint8_least DoIP_TesterIterType;

/**   \brief  type used to iterate DoIP_TxHdrBuf */
typedef uint8_least DoIP_TxHdrBufIterType;

/**   \brief  type used to iterate DoIP_TxTcpMgt */
typedef uint8_least DoIP_TxTcpMgtIterType;

/**   \brief  type used to iterate DoIP_TxUdpMgtList */
typedef uint8_least DoIP_TxUdpMgtListIterType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCIterableTypesWithSizeRelations  DoIP Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate DoIP_ChannelDyn */
typedef DoIP_ChannelIterType DoIP_ChannelDynIterType;

/**   \brief  type used to iterate DoIP_ConnectionDyn */
typedef DoIP_ConnectionIterType DoIP_ConnectionDynIterType;

/**   \brief  type used to iterate DoIP_ConnectionTcpDyn */
typedef DoIP_ConnectionTcpIterType DoIP_ConnectionTcpDynIterType;

/**   \brief  type used to iterate DoIP_IpAddrAssignmentDyn */
typedef DoIP_IpAddrAssignmentIterType DoIP_IpAddrAssignmentDynIterType;

/**   \brief  type used to iterate DoIP_TesterDyn */
typedef DoIP_TesterIterType DoIP_TesterDynIterType;

/**   \brief  type used to iterate DoIP_TxTcpMgtDyn */
typedef DoIP_TxTcpMgtIterType DoIP_TxTcpMgtDynIterType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCValueTypes  DoIP Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for DoIP_ConnectionTcpIdxOfAliveCheckList */
typedef uint8 DoIP_ConnectionTcpIdxOfAliveCheckListType;

/**   \brief  value based type definition for DoIP_BitMaskOfChannel */
typedef uint16 DoIP_BitMaskOfChannelType;

/**   \brief  value based type definition for DoIP_EcuAddrOfChannel */
typedef uint16 DoIP_EcuAddrOfChannelType;

/**   \brief  value based type definition for DoIP_PduRRxPduIdOfChannel */
typedef uint8 DoIP_PduRRxPduIdOfChannelType;

/**   \brief  value based type definition for DoIP_PduRTxConfPduIdOfChannel */
typedef uint8 DoIP_PduRTxConfPduIdOfChannelType;

/**   \brief  value based type definition for DoIP_TesterIdxOfChannel */
typedef uint8 DoIP_TesterIdxOfChannelType;

/**   \brief  value based type definition for DoIP_TpMaxLenOfChannel */
typedef uint16 DoIP_TpMaxLenOfChannelType;

/**   \brief  value based type definition for DoIP_TxMsgLenOfChannelDyn */
typedef PduLengthType DoIP_TxMsgLenOfChannelDynType;

/**   \brief  value based type definition for DoIP_ChannelInd */
typedef uint8 DoIP_ChannelIndType;

/**   \brief  value based type definition for DoIP_LocalAddrIdxOfConnection */
typedef uint8 DoIP_LocalAddrIdxOfConnectionType;

/**   \brief  value based type definition for DoIP_RxCancelPduIdOfConnection */
typedef uint8 DoIP_RxCancelPduIdOfConnectionType;

/**   \brief  value based type definition for DoIP_SoAdTxPduIdOfConnection */
typedef uint8 DoIP_SoAdTxPduIdOfConnectionType;

/**   \brief  value based type definition for DoIP_SoConClosingOfConnectionDyn */
typedef boolean DoIP_SoConClosingOfConnectionDynType;

/**   \brief  value based type definition for DoIP_ConnectionTcpIndEndIdxOfConnectionGroup */
typedef uint8 DoIP_ConnectionTcpIndEndIdxOfConnectionGroupType;

/**   \brief  value based type definition for DoIP_ConnectionTcpIndStartIdxOfConnectionGroup */
typedef uint8 DoIP_ConnectionTcpIndStartIdxOfConnectionGroupType;

/**   \brief  value based type definition for DoIP_ConnectionInd */
typedef uint8 DoIP_ConnectionIndType;

/**   \brief  value based type definition for DoIP_ConnectionGroupIdxOfConnectionTcp */
typedef uint8 DoIP_ConnectionGroupIdxOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_RxHdrBufEndIdxOfConnectionTcp */
typedef uint8 DoIP_RxHdrBufEndIdxOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_RxHdrBufStartIdxOfConnectionTcp */
typedef uint8 DoIP_RxHdrBufStartIdxOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_SecurityRequiredOfConnectionTcp */
typedef boolean DoIP_SecurityRequiredOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_TxTcpMgtEndIdxOfConnectionTcp */
typedef uint8 DoIP_TxTcpMgtEndIdxOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_TxTcpMgtStartIdxOfConnectionTcp */
typedef uint8 DoIP_TxTcpMgtStartIdxOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_ChannelRxActiveOfConnectionTcpDyn */
typedef boolean DoIP_ChannelRxActiveOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_ChannelRxLastIdxOfConnectionTcpDyn */
typedef uint8 DoIP_ChannelRxLastIdxOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_InactivCntOfConnectionTcpDyn */
typedef uint32 DoIP_InactivCntOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_LastRxBufSizeOfConnectionTcpDyn */
typedef PduLengthType DoIP_LastRxBufSizeOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_LastRxTgtAddrOfConnectionTcpDyn */
typedef uint16 DoIP_LastRxTgtAddrOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_LastTxBufSizeOfConnectionTcpDyn */
typedef PduLengthType DoIP_LastTxBufSizeOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_RoutingActivationIdxOfConnectionTcpDyn */
typedef uint8 DoIP_RoutingActivationIdxOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_RxMsgOffsetOfConnectionTcpDyn */
typedef uint64 DoIP_RxMsgOffsetOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_RxTpSessionActiveOfConnectionTcpDyn */
typedef boolean DoIP_RxTpSessionActiveOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_SkipRxMsgOfConnectionTcpDyn */
typedef boolean DoIP_SkipRxMsgOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TesterAddrOfConnectionTcpDyn */
typedef uint16 DoIP_TesterAddrOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TesterIdxOfConnectionTcpDyn */
typedef uint8 DoIP_TesterIdxOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TxBytesCopiedOfConnectionTcpDyn */
typedef PduLengthType DoIP_TxBytesCopiedOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TxTcpMgtQueIdxOfConnectionTcpDyn */
typedef uint8 DoIP_TxTcpMgtQueIdxOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TxTcpMgtQueLvlOfConnectionTcpDyn */
typedef uint8 DoIP_TxTcpMgtQueLvlOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_TxTpSessionActiveOfConnectionTcpDyn */
typedef boolean DoIP_TxTpSessionActiveOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_VerifyRxPduOffsetOfConnectionTcpDyn */
typedef PduLengthType DoIP_VerifyRxPduOffsetOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_ConnectionTcpInd */
typedef uint8 DoIP_ConnectionTcpIndType;

/**   \brief  value based type definition for DoIP_TesterIdxOfDefaultTester */
typedef uint8 DoIP_TesterIdxOfDefaultTesterType;

/**   \brief  value based type definition for DoIP_DiagNAckBuf */
typedef uint8 DoIP_DiagNAckBufType;

/**   \brief  value based type definition for DoIP_EId */
typedef uint8 DoIP_EIdType;

/**   \brief  value based type definition for DoIP_GId */
typedef uint8 DoIP_GIdType;

/**   \brief  value based type definition for DoIP_ControlIpAssignmentOfIpAddrAssignment */
typedef boolean DoIP_ControlIpAssignmentOfIpAddrAssignmentType;

/**   \brief  value based type definition for DoIP_ConnectionIndEndIdxOfLocalAddr */
typedef uint8 DoIP_ConnectionIndEndIdxOfLocalAddrType;

/**   \brief  value based type definition for DoIP_ConnectionIndStartIdxOfLocalAddr */
typedef uint8 DoIP_ConnectionIndStartIdxOfLocalAddrType;

/**   \brief  value based type definition for DoIP_IpAddrAssignmentEndIdxOfLocalAddr */
typedef uint8 DoIP_IpAddrAssignmentEndIdxOfLocalAddrType;

/**   \brief  value based type definition for DoIP_IpAddrAssignmentStartIdxOfLocalAddr */
typedef uint8 DoIP_IpAddrAssignmentStartIdxOfLocalAddrType;

/**   \brief  value based type definition for DoIP_TcpIpLocalAddrIdOfLocalAddr */
typedef uint8 DoIP_TcpIpLocalAddrIdOfLocalAddrType;

/**   \brief  value based type definition for DoIP_UdpAliveTimeoutOfLocalAddr */
typedef boolean DoIP_UdpAliveTimeoutOfLocalAddrType;

/**   \brief  value based type definition for DoIP_ChannelIdxOfPduRRxCancelPduId */
typedef uint8 DoIP_ChannelIdxOfPduRRxCancelPduIdType;

/**   \brief  value based type definition for DoIP_ChannelIdxOfPduRTxPduId */
typedef uint8 DoIP_ChannelIdxOfPduRTxPduIdType;

/**   \brief  value based type definition for DoIP_AliveCheckCntOfRoutActivHandler */
typedef uint16 DoIP_AliveCheckCntOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_AliveCheckElemNumOfRoutActivHandler */
typedef uint8 DoIP_AliveCheckElemNumOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_ConnectionTcpIdxOfRoutActivHandler */
typedef uint8 DoIP_ConnectionTcpIdxOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_OemSpecReqOfRoutActivHandler */
typedef uint32 DoIP_OemSpecReqOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_OemSpecResOfRoutActivHandler */
typedef uint32 DoIP_OemSpecResOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_OemSpecUsedOfRoutActivHandler */
typedef boolean DoIP_OemSpecUsedOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_RoutingActivationIdxOfRoutActivHandler */
typedef uint8 DoIP_RoutingActivationIdxOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_TesterAddrOfRoutActivHandler */
typedef uint16 DoIP_TesterAddrOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_TesterIdxOfRoutActivHandler */
typedef uint8 DoIP_TesterIdxOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_AuthFuncWithRemAddrOfRoutingActivation */
typedef boolean DoIP_AuthFuncWithRemAddrOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_AuthReqLengthOfRoutingActivation */
typedef uint8 DoIP_AuthReqLengthOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_AuthResLengthOfRoutingActivation */
typedef uint8 DoIP_AuthResLengthOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_BitmaskingUsedOfRoutingActivation */
typedef boolean DoIP_BitmaskingUsedOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ChannelIndEndIdxOfRoutingActivation */
typedef uint8 DoIP_ChannelIndEndIdxOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ChannelIndStartIdxOfRoutingActivation */
typedef uint8 DoIP_ChannelIndStartIdxOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ChannelIndUsedOfRoutingActivation */
typedef boolean DoIP_ChannelIndUsedOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ConfFuncWithRemAddrOfRoutingActivation */
typedef boolean DoIP_ConfFuncWithRemAddrOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ConfReqLengthOfRoutingActivation */
typedef uint8 DoIP_ConfReqLengthOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_ConfResLengthOfRoutingActivation */
typedef uint8 DoIP_ConfResLengthOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_MaskedBitsOfRoutingActivation */
typedef uint8 DoIP_MaskedBitsOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_RoutingActivationNumOfRoutingActivation */
typedef uint8 DoIP_RoutingActivationNumOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_SecurityRequiredOfRoutingActivation */
typedef boolean DoIP_SecurityRequiredOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_RoutingActivationInd */
typedef uint8 DoIP_RoutingActivationIndType;

/**   \brief  value based type definition for DoIP_RxHdrBuf */
typedef uint8 DoIP_RxHdrBufType;

/**   \brief  value based type definition for DoIP_SizeOfAliveCheckList */
typedef uint8 DoIP_SizeOfAliveCheckListType;

/**   \brief  value based type definition for DoIP_SizeOfChannel */
typedef uint8 DoIP_SizeOfChannelType;

/**   \brief  value based type definition for DoIP_SizeOfChannelDyn */
typedef uint8 DoIP_SizeOfChannelDynType;

/**   \brief  value based type definition for DoIP_SizeOfChannelInd */
typedef uint8 DoIP_SizeOfChannelIndType;

/**   \brief  value based type definition for DoIP_SizeOfConnection */
typedef uint8 DoIP_SizeOfConnectionType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionDyn */
typedef uint8 DoIP_SizeOfConnectionDynType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionGroup */
typedef uint8 DoIP_SizeOfConnectionGroupType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionInd */
typedef uint8 DoIP_SizeOfConnectionIndType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionTcp */
typedef uint8 DoIP_SizeOfConnectionTcpType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionTcpDyn */
typedef uint8 DoIP_SizeOfConnectionTcpDynType;

/**   \brief  value based type definition for DoIP_SizeOfConnectionTcpInd */
typedef uint8 DoIP_SizeOfConnectionTcpIndType;

/**   \brief  value based type definition for DoIP_SizeOfDefaultTester */
typedef uint8 DoIP_SizeOfDefaultTesterType;

/**   \brief  value based type definition for DoIP_SizeOfDiagNAckBuf */
typedef uint16 DoIP_SizeOfDiagNAckBufType;

/**   \brief  value based type definition for DoIP_SizeOfEId */
typedef uint8 DoIP_SizeOfEIdType;

/**   \brief  value based type definition for DoIP_SizeOfGId */
typedef uint8 DoIP_SizeOfGIdType;

/**   \brief  value based type definition for DoIP_SizeOfIpAddrAssignment */
typedef uint8 DoIP_SizeOfIpAddrAssignmentType;

/**   \brief  value based type definition for DoIP_SizeOfIpAddrAssignmentDyn */
typedef uint8 DoIP_SizeOfIpAddrAssignmentDynType;

/**   \brief  value based type definition for DoIP_SizeOfLocalAddr */
typedef uint8 DoIP_SizeOfLocalAddrType;

/**   \brief  value based type definition for DoIP_SizeOfPduRRxCancelPduId */
typedef uint8 DoIP_SizeOfPduRRxCancelPduIdType;

/**   \brief  value based type definition for DoIP_SizeOfPduRTxPduId */
typedef uint8 DoIP_SizeOfPduRTxPduIdType;

/**   \brief  value based type definition for DoIP_SizeOfRoutActivHandler */
typedef uint8 DoIP_SizeOfRoutActivHandlerType;

/**   \brief  value based type definition for DoIP_SizeOfRoutingActivation */
typedef uint8 DoIP_SizeOfRoutingActivationType;

/**   \brief  value based type definition for DoIP_SizeOfRoutingActivationInd */
typedef uint8 DoIP_SizeOfRoutingActivationIndType;

/**   \brief  value based type definition for DoIP_SizeOfRxHdrBuf */
typedef uint8 DoIP_SizeOfRxHdrBufType;

/**   \brief  value based type definition for DoIP_SizeOfTester */
typedef uint8 DoIP_SizeOfTesterType;

/**   \brief  value based type definition for DoIP_SizeOfTesterDyn */
typedef uint8 DoIP_SizeOfTesterDynType;

/**   \brief  value based type definition for DoIP_SizeOfTxHdrBuf */
typedef uint8 DoIP_SizeOfTxHdrBufType;

/**   \brief  value based type definition for DoIP_SizeOfTxTcpMgt */
typedef uint8 DoIP_SizeOfTxTcpMgtType;

/**   \brief  value based type definition for DoIP_SizeOfTxTcpMgtDyn */
typedef uint8 DoIP_SizeOfTxTcpMgtDynType;

/**   \brief  value based type definition for DoIP_SizeOfTxUdpMgtList */
typedef uint8 DoIP_SizeOfTxUdpMgtListType;

/**   \brief  value based type definition for DoIP_CentralSecurityOfTester */
typedef boolean DoIP_CentralSecurityOfTesterType;

/**   \brief  value based type definition for DoIP_DiagNAckBufEndIdxOfTester */
typedef uint16 DoIP_DiagNAckBufEndIdxOfTesterType;

/**   \brief  value based type definition for DoIP_DiagNAckBufStartIdxOfTester */
typedef uint16 DoIP_DiagNAckBufStartIdxOfTesterType;

/**   \brief  value based type definition for DoIP_DiagNAckBufUsedOfTester */
typedef boolean DoIP_DiagNAckBufUsedOfTesterType;

/**   \brief  value based type definition for DoIP_MaskedBitsOfTester */
typedef uint8 DoIP_MaskedBitsOfTesterType;

/**   \brief  value based type definition for DoIP_RoutingActivationIndEndIdxOfTester */
typedef uint8 DoIP_RoutingActivationIndEndIdxOfTesterType;

/**   \brief  value based type definition for DoIP_RoutingActivationIndStartIdxOfTester */
typedef uint8 DoIP_RoutingActivationIndStartIdxOfTesterType;

/**   \brief  value based type definition for DoIP_TesterAddrOfTester */
typedef uint16 DoIP_TesterAddrOfTesterType;

/**   \brief  value based type definition for DoIP_ConnectionTcpIdxOfTesterDyn */
typedef uint8 DoIP_ConnectionTcpIdxOfTesterDynType;

/**   \brief  value based type definition for DoIP_DiagNAckOffsetOfTesterDyn */
typedef uint32 DoIP_DiagNAckOffsetOfTesterDynType;

/**   \brief  value based type definition for DoIP_TxHdrBuf */
typedef uint8 DoIP_TxHdrBufType;

/**   \brief  value based type definition for DoIP_TxHdrBufEndIdxOfTxTcpMgt */
typedef uint8 DoIP_TxHdrBufEndIdxOfTxTcpMgtType;

/**   \brief  value based type definition for DoIP_TxHdrBufStartIdxOfTxTcpMgt */
typedef uint8 DoIP_TxHdrBufStartIdxOfTxTcpMgtType;

/**   \brief  value based type definition for DoIP_ChannelIdxOfTxTcpMgtDyn */
typedef uint8 DoIP_ChannelIdxOfTxTcpMgtDynType;

/**   \brief  value based type definition for DoIP_TxHdrBufLenOfTxTcpMgtDyn */
typedef PduLengthType DoIP_TxHdrBufLenOfTxTcpMgtDynType;

/**   \brief  value based type definition for DoIP_ConnectionIdxOfTxUdpMgtList */
typedef uint8 DoIP_ConnectionIdxOfTxUdpMgtListType;

/**   \brief  value based type definition for DoIP_HdrTypeOfTxUdpMgtList */
typedef uint16 DoIP_HdrTypeOfTxUdpMgtListType;

/**   \brief  value based type definition for DoIP_RetryAttemptOfTxUdpMgtList */
typedef uint16 DoIP_RetryAttemptOfTxUdpMgtListType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  DoIPPCStructTypes  DoIP Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in DoIP_AliveCheckList */
typedef struct sDoIP_AliveCheckListType
{
  DoIP_ConnectionTcpIdxOfAliveCheckListType ConnectionTcpIdxOfAliveCheckList;  /**< the index of the 1:1 relation pointing to DoIP_ConnectionTcp */
} DoIP_AliveCheckListType;

/**   \brief  type used in DoIP_Channel */
typedef struct sDoIP_ChannelType
{
  DoIP_EcuAddrOfChannelType EcuAddrOfChannel;  /**< logical ecu addr */
  DoIP_TpMaxLenOfChannelType TpMaxLenOfChannel;  /**< maximum TP length */
  DoIP_PduRRxPduIdOfChannelType PduRRxPduIdOfChannel;  /**< PduR PduId for reception */
  DoIP_PduRTxConfPduIdOfChannelType PduRTxConfPduIdOfChannel;  /**< PduR PduId for transmission confirmation */
} DoIP_ChannelType;

/**   \brief  type used in DoIP_ChannelDyn */
typedef struct sDoIP_ChannelDynType
{
  DoIP_TxMsgLenOfChannelDynType TxMsgLenOfChannelDyn;  /**< message length to transmit */
} DoIP_ChannelDynType;

/**   \brief  type used in DoIP_Connection */
/*! \spec weak type invariant () { 
 * (self.LocalAddrIdxOfConnection < DoIP_GetSizeOfLocalAddr())
 * } */
typedef struct sDoIP_ConnectionType
{
  DoIP_LocalAddrIdxOfConnectionType LocalAddrIdxOfConnection;  /**< the index of the 1:1 relation pointing to DoIP_LocalAddr */
  DoIP_RxCancelPduIdOfConnectionType RxCancelPduIdOfConnection;  /**< PduId used for reception cancelation */
  DoIP_SoAdTxPduIdOfConnectionType SoAdTxPduIdOfConnection;  /**< PduId used for transmission */
} DoIP_ConnectionType;

/**   \brief  type used in DoIP_ConnectionDyn */
typedef struct sDoIP_ConnectionDynType
{
  DoIP_SoConClosingOfConnectionDynType SoConClosingOfConnectionDyn;  /**< indicates if socket connection is closing */
  SoAd_IpAddrStateType IpAddrStateOfConnectionDyn;  /**< ip address state */
  SoAd_SoConIdType SoConIdOfConnectionDyn;  /**< socket connection id */
  SoAd_SoConModeType SoConStateOfConnectionDyn;  /**< socket connection state */
} DoIP_ConnectionDynType;

/**   \brief  type used in DoIP_ConnectionGroup */
typedef struct sDoIP_ConnectionGroupType
{
  uint8 DoIP_ConnectionGroupNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} DoIP_ConnectionGroupType;

/**   \brief  type used in DoIP_ConnectionTcp */
/*! \spec weak type invariant () { 
 * (self.TxTcpMgtStartIdxOfConnectionTcp < DoIP_GetSizeOfTxTcpMgt()) &&
 * (self.RxHdrBufStartIdxOfConnectionTcp < DoIP_GetSizeOfRxHdrBuf()) &&
 * (self.ConnectionGroupIdxOfConnectionTcp < DoIP_GetSizeOfConnectionGroup())
 * } */
typedef struct sDoIP_ConnectionTcpType
{
  DoIP_SecurityRequiredOfConnectionTcpType SecurityRequiredOfConnectionTcp;  /**< security required */
  DoIP_ConnectionGroupIdxOfConnectionTcpType ConnectionGroupIdxOfConnectionTcp;  /**< the index of the 1:1 relation pointing to DoIP_ConnectionGroup */
  DoIP_RxHdrBufStartIdxOfConnectionTcpType RxHdrBufStartIdxOfConnectionTcp;  /**< the start index of the 1:n relation pointing to DoIP_RxHdrBuf */
  DoIP_TxTcpMgtStartIdxOfConnectionTcpType TxTcpMgtStartIdxOfConnectionTcp;  /**< the start index of the 1:n relation pointing to DoIP_TxTcpMgt */
} DoIP_ConnectionTcpType;

/**   \brief  type used in DoIP_ConnectionTcpDyn */
typedef struct sDoIP_ConnectionTcpDynType
{
  DoIP_RxMsgOffsetOfConnectionTcpDynType RxMsgOffsetOfConnectionTcpDyn;  /**< number of already copied bytes */
  DoIP_InactivCntOfConnectionTcpDynType InactivCntOfConnectionTcpDyn;  /**< inactivity timeout */
  DoIP_LastRxBufSizeOfConnectionTcpDynType LastRxBufSizeOfConnectionTcpDyn;  /**< buffer size of previous message part */
  DoIP_LastRxTgtAddrOfConnectionTcpDynType LastRxTgtAddrOfConnectionTcpDyn;  /**< ast used target address */
  DoIP_LastTxBufSizeOfConnectionTcpDynType LastTxBufSizeOfConnectionTcpDyn;  /**< buffer size of previous message part */
  DoIP_TesterAddrOfConnectionTcpDynType TesterAddrOfConnectionTcpDyn;  /**< tester address */
  DoIP_TxBytesCopiedOfConnectionTcpDynType TxBytesCopiedOfConnectionTcpDyn;  /**< number of already copied bytes */
  DoIP_VerifyRxPduOffsetOfConnectionTcpDynType VerifyRxPduOffsetOfConnectionTcpDyn;  /**< offset in header buffer. This user data can be used for rx pdu verification */
  DoIP_ChannelRxActiveOfConnectionTcpDynType ChannelRxActiveOfConnectionTcpDyn;  /**< indicates if reception channel is still active */
  DoIP_ChannelRxLastIdxOfConnectionTcpDynType ChannelRxLastIdxOfConnectionTcpDyn;  /**< the index of the 0:1 relation pointing to DoIP_Channel */
  DoIP_RoutingActivationIdxOfConnectionTcpDynType RoutingActivationIdxOfConnectionTcpDyn;  /**< the index of the 0:1 relation pointing to DoIP_RoutingActivation */
  DoIP_RxTpSessionActiveOfConnectionTcpDynType RxTpSessionActiveOfConnectionTcpDyn;  /**< lock for TP session */
  DoIP_SkipRxMsgOfConnectionTcpDynType SkipRxMsgOfConnectionTcpDyn;  /**< indicates if message should be skiped */
  DoIP_TesterIdxOfConnectionTcpDynType TesterIdxOfConnectionTcpDyn;  /**< the index of the 0:1 relation pointing to DoIP_Tester */
  DoIP_TxTcpMgtQueIdxOfConnectionTcpDynType TxTcpMgtQueIdxOfConnectionTcpDyn;  /**< manamgement queue index */
  DoIP_TxTcpMgtQueLvlOfConnectionTcpDynType TxTcpMgtQueLvlOfConnectionTcpDyn;  /**< managment queue fill level */
  DoIP_TxTpSessionActiveOfConnectionTcpDynType TxTpSessionActiveOfConnectionTcpDyn;  /**< lock for TP session */
  DoIP_RoutActivStateType ActivStateOfConnectionTcpDyn;  /**< state of routing activation indicates next action */
  boolean TpTxPreCloseSocketOfConnectionTcpDyn;  /**< indicates if socket should be cosed after transmission */
  uint16 TpTxPreHdrTypeOfConnectionTcpDyn;  /**< header type of prepared transmission */
  uint16 TpTxPreParam1OfConnectionTcpDyn;  /**< parameter depends on header type of prepared transmission */
  uint32 TpTxPreParam2OfConnectionTcpDyn;  /**< parameter depends on header type of prepared transmission */
  uint8 TpTxPreParam3OfConnectionTcpDyn;  /**< parameter depends on header type of prepared transmission */
} DoIP_ConnectionTcpDynType;

/**   \brief  type used in DoIP_DefaultTester */
/*! \spec weak type invariant () { 
 * (self.TesterIdxOfDefaultTester < DoIP_GetSizeOfTester())
 * } */
typedef struct sDoIP_DefaultTesterType
{
  DoIP_TesterIdxOfDefaultTesterType TesterIdxOfDefaultTester;  /**< the index of the 1:1 relation pointing to DoIP_Tester */
} DoIP_DefaultTesterType;

/**   \brief  type used in DoIP_IpAddrAssignment */
typedef struct sDoIP_IpAddrAssignmentType
{
  DoIP_ControlIpAssignmentOfIpAddrAssignmentType ControlIpAssignmentOfIpAddrAssignment;  /**< indicates if IP address assigment shall be requested/released */
  DoIP_IpAddrAssignmentTypeType AssignmentTypeOfIpAddrAssignment;  /**< ip addresss assignment type */
} DoIP_IpAddrAssignmentType;

/**   \brief  type used in DoIP_IpAddrAssignmentDyn */
typedef struct sDoIP_IpAddrAssignmentDynType
{
  DoIP_IpAddrReqStateType IpAddrReqStateOfIpAddrAssignmentDyn;  /**< IP address request state */
} DoIP_IpAddrAssignmentDynType;

/**   \brief  type used in DoIP_LocalAddr */
typedef struct sDoIP_LocalAddrType
{
  DoIP_UdpAliveTimeoutOfLocalAddrType UdpAliveTimeoutOfLocalAddr;  /**< indicates if UDP alive timeout is enabled */
  SoAd_DomainType DomainTypeOfLocalAddr;  /**< domain type */
} DoIP_LocalAddrType;

/**   \brief  type used in DoIP_PduRRxCancelPduId */
typedef struct sDoIP_PduRRxCancelPduIdType
{
  uint8 DoIP_PduRRxCancelPduIdNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} DoIP_PduRRxCancelPduIdType;

/**   \brief  type used in DoIP_PduRTxPduId */
typedef struct sDoIP_PduRTxPduIdType
{
  uint8 DoIP_PduRTxPduIdNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} DoIP_PduRTxPduIdType;

/**   \brief  type used in DoIP_RoutActivHandler */
typedef struct sDoIP_RoutActivHandlerType
{
  DoIP_OemSpecReqOfRoutActivHandlerType OemSpecReqOfRoutActivHandler;  /**< handlers oem specific request buffer */
  DoIP_OemSpecResOfRoutActivHandlerType OemSpecResOfRoutActivHandler;  /**< handlers oem specific response buffer */
  DoIP_AliveCheckCntOfRoutActivHandlerType AliveCheckCntOfRoutActivHandler;  /**< alive check timeout */
  DoIP_TesterAddrOfRoutActivHandlerType TesterAddrOfRoutActivHandler;  /**< handlers active testser address */
  DoIP_AliveCheckElemNumOfRoutActivHandlerType AliveCheckElemNumOfRoutActivHandler;  /**< number of pending alive checks */
  DoIP_ConnectionTcpIdxOfRoutActivHandlerType ConnectionTcpIdxOfRoutActivHandler;  /**< the index of the 0:1 relation pointing to DoIP_ConnectionTcp */
  DoIP_OemSpecUsedOfRoutActivHandlerType OemSpecUsedOfRoutActivHandler;  /**< indicates if oem specific payload type is used */
  DoIP_RoutingActivationIdxOfRoutActivHandlerType RoutingActivationIdxOfRoutActivHandler;  /**< the index of the 0:1 relation pointing to DoIP_RoutingActivation */
  DoIP_TesterIdxOfRoutActivHandlerType TesterIdxOfRoutActivHandler;  /**< the index of the 0:1 relation pointing to DoIP_Tester */
} DoIP_RoutActivHandlerType;

/**   \brief  type used in DoIP_RoutingActivation */
typedef struct sDoIP_RoutingActivationType
{
  DoIP_AuthFctPtrType AuthFuncPtrOfRoutingActivation;  /**< pointer to authentification function */
  DoIP_AuthWithRemAddrFctPtrType AuthWithRemAddrFuncPtrOfRoutingActivation;  /**< pointer to authentification function with remote address */
  DoIP_ConfFctPtrType ConfFuncPtrOfRoutingActivation;  /**< pointer to confirmation function */
  DoIP_ConfWithRemAddrFctPtrType ConfWithRemAddrFuncPtrOfRoutingActivation;  /**< pointer to confirmation function with remote address */
} DoIP_RoutingActivationType;

/**   \brief  type used in DoIP_Tester */
typedef struct sDoIP_TesterType
{
  uint8 DoIP_TesterNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} DoIP_TesterType;

/**   \brief  type used in DoIP_TesterDyn */
typedef struct sDoIP_TesterDynType
{
  DoIP_DiagNAckOffsetOfTesterDynType DiagNAckOffsetOfTesterDyn;  /**< diagnostic nack data buffer offset */
  DoIP_ConnectionTcpIdxOfTesterDynType ConnectionTcpIdxOfTesterDyn;  /**< the index of the 0:1 relation pointing to DoIP_ConnectionTcp */
} DoIP_TesterDynType;

/**   \brief  type used in DoIP_TxTcpMgt */
/*! \spec weak type invariant () { 
 * (self.TxHdrBufStartIdxOfTxTcpMgt < DoIP_GetSizeOfTxHdrBuf())
 * } */
typedef struct sDoIP_TxTcpMgtType
{
  DoIP_TxHdrBufStartIdxOfTxTcpMgtType TxHdrBufStartIdxOfTxTcpMgt;  /**< the start index of the 1:n relation pointing to DoIP_TxHdrBuf */
} DoIP_TxTcpMgtType;

/**   \brief  type used in DoIP_TxTcpMgtDyn */
typedef struct sDoIP_TxTcpMgtDynType
{
  DoIP_TxHdrBufLenOfTxTcpMgtDynType TxHdrBufLenOfTxTcpMgtDyn;  /**< length of header buffer used for transmission */
  DoIP_ChannelIdxOfTxTcpMgtDynType ChannelIdxOfTxTcpMgtDyn;  /**< the index of the 0:1 relation pointing to DoIP_Channel */
  PduInfoType MsgOfTxTcpMgtDyn;
} DoIP_TxTcpMgtDynType;

/**   \brief  type used in DoIP_TxUdpMgtList */
typedef struct sDoIP_TxUdpMgtListType
{
  DoIP_HdrTypeOfTxUdpMgtListType HdrTypeOfTxUdpMgtList;  /**< header tpye */
  DoIP_RetryAttemptOfTxUdpMgtListType RetryAttemptOfTxUdpMgtList;  /**< retry attempts */
  DoIP_ConnectionIdxOfTxUdpMgtListType ConnectionIdxOfTxUdpMgtList;  /**< the index of the 0:1 relation pointing to DoIP_Connection */
  uint32 Param1OfTxUdpMgtList;  /**< parameter depends on header type */
  uint16 Param2OfTxUdpMgtList;  /**< parameter depends on header type */
  SoAd_SockAddrInetXType RemoteAddrOfTxUdpMgtList;  /**< remote ip address for transmission */
} DoIP_TxUdpMgtListType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCSymbolicStructTypes  DoIP Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to DoIP_ConnectionDyn */
typedef struct DoIP_ConnectionDynStructSTag
{
  DoIP_ConnectionDynType TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33[4];
} DoIP_ConnectionDynStructSType;

/**   \brief  type to be used as symbolic data element access to DoIP_DiagNAckBuf */
typedef struct DoIP_DiagNAckBufStructSTag
{
  DoIP_DiagNAckBufType DoIPTester_0x0E80[256];
} DoIP_DiagNAckBufStructSType;

/**   \brief  type to be used as symbolic data element access to DoIP_IpAddrAssignmentDyn */
typedef struct DoIP_IpAddrAssignmentDynStructSTag
{
  DoIP_IpAddrAssignmentDynType TcpIpLocalAddr_NE_DhcpV4_Fixed_169_254_1_33[2];
} DoIP_IpAddrAssignmentDynStructSType;

/**   \brief  type to be used as symbolic data element access to DoIP_RxHdrBuf */
typedef struct DoIP_RxHdrBufStructSTag
{
  DoIP_RxHdrBufType DoIPTcpConnection_TCP_DATA0[19];
  DoIP_RxHdrBufType DoIPTcpConnection_TCP_DATA1[19];
} DoIP_RxHdrBufStructSType;

/**   \brief  type to be used as symbolic data element access to DoIP_TesterDyn */
typedef struct DoIP_TesterDynStructSTag
{
  DoIP_TesterDynType DoIPTester_0x0E80;
} DoIP_TesterDynStructSType;

/**   \brief  type to be used as symbolic data element access to DoIP_TxTcpMgtDyn */
typedef struct DoIP_TxTcpMgtDynStructSTag
{
  DoIP_TxTcpMgtDynType DoIPTcpConnection_TCP_DATA0[2];
  DoIP_TxTcpMgtDynType DoIPTcpConnection_TCP_DATA1[2];
} DoIP_TxTcpMgtDynStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCUnionIndexAndSymbolTypes  DoIP Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access DoIP_ConnectionDyn in an index and symbol based style. */
typedef union DoIP_ConnectionDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_ConnectionDynType raw[4];
  DoIP_ConnectionDynStructSType str;
} DoIP_ConnectionDynUType;

/**   \brief  type to access DoIP_DiagNAckBuf in an index and symbol based style. */
typedef union DoIP_DiagNAckBufUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_DiagNAckBufType raw[256];
  DoIP_DiagNAckBufStructSType str;
} DoIP_DiagNAckBufUType;

/**   \brief  type to access DoIP_IpAddrAssignmentDyn in an index and symbol based style. */
typedef union DoIP_IpAddrAssignmentDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_IpAddrAssignmentDynType raw[2];
  DoIP_IpAddrAssignmentDynStructSType str;
} DoIP_IpAddrAssignmentDynUType;

/**   \brief  type to access DoIP_RxHdrBuf in an index and symbol based style. */
typedef union DoIP_RxHdrBufUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_RxHdrBufType raw[38];
  DoIP_RxHdrBufStructSType str;
} DoIP_RxHdrBufUType;

/**   \brief  type to access DoIP_TesterDyn in an index and symbol based style. */
typedef union DoIP_TesterDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_TesterDynType raw[1];
  DoIP_TesterDynStructSType str;
} DoIP_TesterDynUType;

/**   \brief  type to access DoIP_TxTcpMgtDyn in an index and symbol based style. */
typedef union DoIP_TxTcpMgtDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  DoIP_TxTcpMgtDynType raw[4];
  DoIP_TxTcpMgtDynStructSType str;
} DoIP_TxTcpMgtDynUType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCRootPointerTypes  DoIP Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to DoIP_AliveCheckList */
typedef P2VAR(DoIP_AliveCheckListType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_AliveCheckListPtrType;

/**   \brief  type used to point to DoIP_Channel */
typedef P2CONST(DoIP_ChannelType, TYPEDEF, DOIP_CONST) DoIP_ChannelPtrType;

/**   \brief  type used to point to DoIP_ChannelDyn */
typedef P2VAR(DoIP_ChannelDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_ChannelDynPtrType;

/**   \brief  type used to point to DoIP_ChannelInd */
typedef P2CONST(DoIP_ChannelIndType, TYPEDEF, DOIP_CONST) DoIP_ChannelIndPtrType;

/**   \brief  type used to point to DoIP_Connection */
typedef P2CONST(DoIP_ConnectionType, TYPEDEF, DOIP_CONST) DoIP_ConnectionPtrType;

/**   \brief  type used to point to DoIP_ConnectionDyn */
typedef P2VAR(DoIP_ConnectionDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_ConnectionDynPtrType;

/**   \brief  type used to point to DoIP_ConnectionGroup */
typedef P2CONST(DoIP_ConnectionGroupType, TYPEDEF, DOIP_CONST) DoIP_ConnectionGroupPtrType;

/**   \brief  type used to point to DoIP_ConnectionInd */
typedef P2CONST(DoIP_ConnectionIndType, TYPEDEF, DOIP_CONST) DoIP_ConnectionIndPtrType;

/**   \brief  type used to point to DoIP_ConnectionTcp */
typedef P2CONST(DoIP_ConnectionTcpType, TYPEDEF, DOIP_CONST) DoIP_ConnectionTcpPtrType;

/**   \brief  type used to point to DoIP_ConnectionTcpDyn */
typedef P2VAR(DoIP_ConnectionTcpDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_ConnectionTcpDynPtrType;

/**   \brief  type used to point to DoIP_ConnectionTcpInd */
typedef P2CONST(DoIP_ConnectionTcpIndType, TYPEDEF, DOIP_CONST) DoIP_ConnectionTcpIndPtrType;

/**   \brief  type used to point to DoIP_DefaultTester */
typedef P2CONST(DoIP_DefaultTesterType, TYPEDEF, DOIP_CONST) DoIP_DefaultTesterPtrType;

/**   \brief  type used to point to DoIP_DiagNAckBuf */
typedef P2VAR(DoIP_DiagNAckBufType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_DiagNAckBufPtrType;

/**   \brief  type used to point to DoIP_EId */
typedef P2CONST(DoIP_EIdType, TYPEDEF, DOIP_CONST) DoIP_EIdPtrType;

/**   \brief  type used to point to DoIP_GId */
typedef P2CONST(DoIP_GIdType, TYPEDEF, DOIP_CONST) DoIP_GIdPtrType;

/**   \brief  type used to point to DoIP_IpAddrAssignment */
typedef P2CONST(DoIP_IpAddrAssignmentType, TYPEDEF, DOIP_CONST) DoIP_IpAddrAssignmentPtrType;

/**   \brief  type used to point to DoIP_IpAddrAssignmentDyn */
typedef P2VAR(DoIP_IpAddrAssignmentDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_IpAddrAssignmentDynPtrType;

/**   \brief  type used to point to DoIP_LocalAddr */
typedef P2CONST(DoIP_LocalAddrType, TYPEDEF, DOIP_CONST) DoIP_LocalAddrPtrType;

/**   \brief  type used to point to DoIP_PduRRxCancelPduId */
typedef P2CONST(DoIP_PduRRxCancelPduIdType, TYPEDEF, DOIP_CONST) DoIP_PduRRxCancelPduIdPtrType;

/**   \brief  type used to point to DoIP_PduRTxPduId */
typedef P2CONST(DoIP_PduRTxPduIdType, TYPEDEF, DOIP_CONST) DoIP_PduRTxPduIdPtrType;

/**   \brief  type used to point to DoIP_RoutActivHandler */
typedef P2VAR(DoIP_RoutActivHandlerType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_RoutActivHandlerPtrType;

/**   \brief  type used to point to DoIP_RoutingActivation */
typedef P2CONST(DoIP_RoutingActivationType, TYPEDEF, DOIP_CONST) DoIP_RoutingActivationPtrType;

/**   \brief  type used to point to DoIP_RoutingActivationInd */
typedef P2CONST(DoIP_RoutingActivationIndType, TYPEDEF, DOIP_CONST) DoIP_RoutingActivationIndPtrType;

/**   \brief  type used to point to DoIP_RxHdrBuf */
typedef P2VAR(DoIP_RxHdrBufType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_RxHdrBufPtrType;

/**   \brief  type used to point to DoIP_Tester */
typedef P2CONST(DoIP_TesterType, TYPEDEF, DOIP_CONST) DoIP_TesterPtrType;

/**   \brief  type used to point to DoIP_TesterDyn */
typedef P2VAR(DoIP_TesterDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_TesterDynPtrType;

/**   \brief  type used to point to DoIP_TxHdrBuf */
typedef P2VAR(DoIP_TxHdrBufType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_TxHdrBufPtrType;

/**   \brief  type used to point to DoIP_TxTcpMgt */
typedef P2CONST(DoIP_TxTcpMgtType, TYPEDEF, DOIP_CONST) DoIP_TxTcpMgtPtrType;

/**   \brief  type used to point to DoIP_TxTcpMgtDyn */
typedef P2VAR(DoIP_TxTcpMgtDynType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_TxTcpMgtDynPtrType;

/**   \brief  type used to point to DoIP_MsgOfTxTcpMgtDyn */
typedef P2VAR(PduInfoType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_MsgOfTxTcpMgtDynPtrType;

/**   \brief  type used to point to DoIP_TxUdpMgtList */
typedef P2VAR(DoIP_TxUdpMgtListType, TYPEDEF, DOIP_VAR_NOINIT) DoIP_TxUdpMgtListPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  DoIPPCRootValueTypes  DoIP Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in DoIP_PCConfig */
typedef struct sDoIP_PCConfigType
{
  DoIP_AliveCheckListPtrType AliveCheckListOfPCConfig;  /**< the pointer to DoIP_AliveCheckList */
  DoIP_ChannelPtrType ChannelOfPCConfig;  /**< the pointer to DoIP_Channel */
  DoIP_ChannelDynPtrType ChannelDynOfPCConfig;  /**< the pointer to DoIP_ChannelDyn */
  DoIP_ChannelIndPtrType ChannelIndOfPCConfig;  /**< the pointer to DoIP_ChannelInd */
  DoIP_ConnectionPtrType ConnectionOfPCConfig;  /**< the pointer to DoIP_Connection */
  DoIP_ConnectionDynPtrType ConnectionDynOfPCConfig;  /**< the pointer to DoIP_ConnectionDyn */
  DoIP_ConnectionGroupPtrType ConnectionGroupOfPCConfig;  /**< the pointer to DoIP_ConnectionGroup */
  DoIP_ConnectionIndPtrType ConnectionIndOfPCConfig;  /**< the pointer to DoIP_ConnectionInd */
  DoIP_ConnectionTcpPtrType ConnectionTcpOfPCConfig;  /**< the pointer to DoIP_ConnectionTcp */
  DoIP_ConnectionTcpDynPtrType ConnectionTcpDynOfPCConfig;  /**< the pointer to DoIP_ConnectionTcpDyn */
  DoIP_ConnectionTcpIndPtrType ConnectionTcpIndOfPCConfig;  /**< the pointer to DoIP_ConnectionTcpInd */
  DoIP_DefaultTesterPtrType DefaultTesterOfPCConfig;  /**< the pointer to DoIP_DefaultTester */
  DoIP_DiagNAckBufPtrType DiagNAckBufOfPCConfig;  /**< the pointer to DoIP_DiagNAckBuf */
  DoIP_EIdPtrType EIdOfPCConfig;  /**< the pointer to DoIP_EId */
  DoIP_GIdPtrType GIdOfPCConfig;  /**< the pointer to DoIP_GId */
  DoIP_IpAddrAssignmentPtrType IpAddrAssignmentOfPCConfig;  /**< the pointer to DoIP_IpAddrAssignment */
  DoIP_IpAddrAssignmentDynPtrType IpAddrAssignmentDynOfPCConfig;  /**< the pointer to DoIP_IpAddrAssignmentDyn */
  DoIP_LocalAddrPtrType LocalAddrOfPCConfig;  /**< the pointer to DoIP_LocalAddr */
  DoIP_PduRRxCancelPduIdPtrType PduRRxCancelPduIdOfPCConfig;  /**< the pointer to DoIP_PduRRxCancelPduId */
  DoIP_PduRTxPduIdPtrType PduRTxPduIdOfPCConfig;  /**< the pointer to DoIP_PduRTxPduId */
  DoIP_RoutActivHandlerPtrType RoutActivHandlerOfPCConfig;  /**< the pointer to DoIP_RoutActivHandler */
  DoIP_RoutingActivationPtrType RoutingActivationOfPCConfig;  /**< the pointer to DoIP_RoutingActivation */
  DoIP_RoutingActivationIndPtrType RoutingActivationIndOfPCConfig;  /**< the pointer to DoIP_RoutingActivationInd */
  DoIP_RxHdrBufPtrType RxHdrBufOfPCConfig;  /**< the pointer to DoIP_RxHdrBuf */
  DoIP_TesterPtrType TesterOfPCConfig;  /**< the pointer to DoIP_Tester */
  DoIP_TesterDynPtrType TesterDynOfPCConfig;  /**< the pointer to DoIP_TesterDyn */
  DoIP_TxHdrBufPtrType TxHdrBufOfPCConfig;  /**< the pointer to DoIP_TxHdrBuf */
  DoIP_TxTcpMgtPtrType TxTcpMgtOfPCConfig;  /**< the pointer to DoIP_TxTcpMgt */
  DoIP_TxTcpMgtDynPtrType TxTcpMgtDynOfPCConfig;  /**< the pointer to DoIP_TxTcpMgtDyn */
  DoIP_TxUdpMgtListPtrType TxUdpMgtListOfPCConfig;  /**< the pointer to DoIP_TxUdpMgtList */
  DoIP_SizeOfDiagNAckBufType SizeOfDiagNAckBufOfPCConfig;  /**< the number of accomplishable value elements in DoIP_DiagNAckBuf */
  DoIP_SizeOfAliveCheckListType SizeOfAliveCheckListOfPCConfig;  /**< the number of accomplishable value elements in DoIP_AliveCheckList */
  DoIP_SizeOfChannelType SizeOfChannelOfPCConfig;  /**< the number of accomplishable value elements in DoIP_Channel */
  DoIP_SizeOfChannelIndType SizeOfChannelIndOfPCConfig;  /**< the number of accomplishable value elements in DoIP_ChannelInd */
  DoIP_SizeOfConnectionType SizeOfConnectionOfPCConfig;  /**< the number of accomplishable value elements in DoIP_Connection */
  DoIP_SizeOfConnectionGroupType SizeOfConnectionGroupOfPCConfig;  /**< the number of accomplishable value elements in DoIP_ConnectionGroup */
  DoIP_SizeOfConnectionIndType SizeOfConnectionIndOfPCConfig;  /**< the number of accomplishable value elements in DoIP_ConnectionInd */
  DoIP_SizeOfConnectionTcpType SizeOfConnectionTcpOfPCConfig;  /**< the number of accomplishable value elements in DoIP_ConnectionTcp */
  DoIP_SizeOfConnectionTcpIndType SizeOfConnectionTcpIndOfPCConfig;  /**< the number of accomplishable value elements in DoIP_ConnectionTcpInd */
  DoIP_SizeOfDefaultTesterType SizeOfDefaultTesterOfPCConfig;  /**< the number of accomplishable value elements in DoIP_DefaultTester */
  DoIP_SizeOfEIdType SizeOfEIdOfPCConfig;  /**< the number of accomplishable value elements in DoIP_EId */
  DoIP_SizeOfGIdType SizeOfGIdOfPCConfig;  /**< the number of accomplishable value elements in DoIP_GId */
  DoIP_SizeOfIpAddrAssignmentType SizeOfIpAddrAssignmentOfPCConfig;  /**< the number of accomplishable value elements in DoIP_IpAddrAssignment */
  DoIP_SizeOfLocalAddrType SizeOfLocalAddrOfPCConfig;  /**< the number of accomplishable value elements in DoIP_LocalAddr */
  DoIP_SizeOfPduRRxCancelPduIdType SizeOfPduRRxCancelPduIdOfPCConfig;  /**< the number of accomplishable value elements in DoIP_PduRRxCancelPduId */
  DoIP_SizeOfPduRTxPduIdType SizeOfPduRTxPduIdOfPCConfig;  /**< the number of accomplishable value elements in DoIP_PduRTxPduId */
  DoIP_SizeOfRoutActivHandlerType SizeOfRoutActivHandlerOfPCConfig;  /**< the number of accomplishable value elements in DoIP_RoutActivHandler */
  DoIP_SizeOfRoutingActivationType SizeOfRoutingActivationOfPCConfig;  /**< the number of accomplishable value elements in DoIP_RoutingActivation */
  DoIP_SizeOfRoutingActivationIndType SizeOfRoutingActivationIndOfPCConfig;  /**< the number of accomplishable value elements in DoIP_RoutingActivationInd */
  DoIP_SizeOfRxHdrBufType SizeOfRxHdrBufOfPCConfig;  /**< the number of accomplishable value elements in DoIP_RxHdrBuf */
  DoIP_SizeOfTesterType SizeOfTesterOfPCConfig;  /**< the number of accomplishable value elements in DoIP_Tester */
  DoIP_SizeOfTxHdrBufType SizeOfTxHdrBufOfPCConfig;  /**< the number of accomplishable value elements in DoIP_TxHdrBuf */
  DoIP_SizeOfTxTcpMgtType SizeOfTxTcpMgtOfPCConfig;  /**< the number of accomplishable value elements in DoIP_TxTcpMgt */
  DoIP_SizeOfTxUdpMgtListType SizeOfTxUdpMgtListOfPCConfig;  /**< the number of accomplishable value elements in DoIP_TxUdpMgtList */
} DoIP_PCConfigType;

typedef DoIP_PCConfigType DoIP_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access DoIP_PCConfig in a symbol based style. */
typedef struct sDoIP_PCConfigsType
{
  DoIP_PCConfigType Config;  /**< [Config] */
} DoIP_PCConfigsType;

/** 
  \}
*/ 



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  DoIP_Channel
**********************************************************************************************************************/
/** 
  \var    DoIP_Channel
  \brief  contains static channel data
  \details
  Element            Description
  EcuAddr            logical ecu addr
  TpMaxLen           maximum TP length
  PduRRxPduId        PduR PduId for reception
  PduRTxConfPduId    PduR PduId for transmission confirmation
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_ChannelType, DOIP_CONST) DoIP_Channel[2];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_Connection
**********************************************************************************************************************/
/** 
  \var    DoIP_Connection
  \brief  contains static TCP connection Data. List of DoIPConnections. The RxPduId as well as the TxPduId can be used to access the array.
  \details
  Element          Description
  LocalAddrIdx     the index of the 1:1 relation pointing to DoIP_LocalAddr
  RxCancelPduId    PduId used for reception cancelation
  SoAdTxPduId      PduId used for transmission
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_ConnectionType, DOIP_CONST) DoIP_Connection[4];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionTcp
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionTcp
  \brief  contains static TCP connection data
  \details
  Element               Description
  SecurityRequired      security required
  ConnectionGroupIdx    the index of the 1:1 relation pointing to DoIP_ConnectionGroup
  RxHdrBufStartIdx      the start index of the 1:n relation pointing to DoIP_RxHdrBuf
  TxTcpMgtStartIdx      the start index of the 1:n relation pointing to DoIP_TxTcpMgt
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_ConnectionTcpType, DOIP_CONST) DoIP_ConnectionTcp[2];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_EId
**********************************************************************************************************************/
/** 
  \var    DoIP_EId
  \brief  the EID
*/ 
#define DOIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_EIdType, DOIP_CONST) DoIP_EId[5];
#define DOIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_GId
**********************************************************************************************************************/
/** 
  \var    DoIP_GId
  \brief  the GID
*/ 
#define DOIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_GIdType, DOIP_CONST) DoIP_GId[6];
#define DOIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_IpAddrAssignment
**********************************************************************************************************************/
/** 
  \var    DoIP_IpAddrAssignment
  \brief  contains static IP address assignment data
  \details
  Element                Description
  ControlIpAssignment    indicates if IP address assigment shall be requested/released
  AssignmentType         ip addresss assignment type
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_IpAddrAssignmentType, DOIP_CONST) DoIP_IpAddrAssignment[2];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_LocalAddr
**********************************************************************************************************************/
/** 
  \var    DoIP_LocalAddr
  \brief  contains static local address data
  \details
  Element            Description
  UdpAliveTimeout    indicates if UDP alive timeout is enabled
  DomainType         domain type
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_LocalAddrType, DOIP_CONST) DoIP_LocalAddr[1];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RoutingActivation
**********************************************************************************************************************/
/** 
  \var    DoIP_RoutingActivation
  \brief  contains static routing activation data
  \details
  Element                   Description
  AuthFuncPtr               pointer to authentification function
  AuthWithRemAddrFuncPtr    pointer to authentification function with remote address
  ConfFuncPtr               pointer to confirmation function
  ConfWithRemAddrFuncPtr    pointer to confirmation function with remote address
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_RoutingActivationType, DOIP_CONST) DoIP_RoutingActivation[1];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxTcpMgt
**********************************************************************************************************************/
/** 
  \var    DoIP_TxTcpMgt
  \brief  contains static TCP transmission queue management data
  \details
  Element             Description
  TxHdrBufStartIdx    the start index of the 1:n relation pointing to DoIP_TxHdrBuf
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_TxTcpMgtType, DOIP_CONST) DoIP_TxTcpMgt[4];
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_AliveCheckList
**********************************************************************************************************************/
/** 
  \var    DoIP_AliveCheckList
  \brief  list of connections with pending alive checks
  \details
  Element             Description
  ConnectionTcpIdx    the index of the 1:1 relation pointing to DoIP_ConnectionTcp
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_AliveCheckListType, DOIP_VAR_NOINIT) DoIP_AliveCheckList[2];
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ChannelDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ChannelDyn
  \brief  contains dynamic channel data
  \details
  Element     Description
  TxMsgLen    message length to transmit
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_ChannelDynType, DOIP_VAR_NOINIT) DoIP_ChannelDyn[2];
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionDyn
  \brief  contains dynamic connection data
  \details
  Element         Description
  SoConClosing    indicates if socket connection is closing
  IpAddrState     ip address state
  SoConId         socket connection id
  SoConState      socket connection state
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_ConnectionDynUType, DOIP_VAR_NOINIT) DoIP_ConnectionDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_ConnectionTcpDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_ConnectionTcpDyn
  \brief  contains dynamic TCP connection data
  \details
  Element                 Description
  RxMsgOffset             number of already copied bytes
  InactivCnt              inactivity timeout
  LastRxBufSize           buffer size of previous message part
  LastRxTgtAddr           ast used target address
  LastTxBufSize           buffer size of previous message part
  TesterAddr              tester address
  TxBytesCopied           number of already copied bytes
  VerifyRxPduOffset       offset in header buffer. This user data can be used for rx pdu verification
  ChannelRxActive         indicates if reception channel is still active
  ChannelRxLastIdx        the index of the 0:1 relation pointing to DoIP_Channel
  RoutingActivationIdx    the index of the 0:1 relation pointing to DoIP_RoutingActivation
  RxTpSessionActive       lock for TP session
  SkipRxMsg               indicates if message should be skiped
  TesterIdx               the index of the 0:1 relation pointing to DoIP_Tester
  TxTcpMgtQueIdx          manamgement queue index
  TxTcpMgtQueLvl          managment queue fill level
  TxTpSessionActive       lock for TP session
  ActivState              state of routing activation indicates next action
  TpTxPreCloseSocket      indicates if socket should be cosed after transmission
  TpTxPreHdrType          header type of prepared transmission
  TpTxPreParam1           parameter depends on header type of prepared transmission
  TpTxPreParam2           parameter depends on header type of prepared transmission
  TpTxPreParam3           parameter depends on header type of prepared transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_ConnectionTcpDynType, DOIP_VAR_NOINIT) DoIP_ConnectionTcpDyn[2];
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_DiagNAckBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_DiagNAckBuf
  \brief  diagnostic nack data buffer
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_DiagNAckBufUType, DOIP_VAR_NOINIT) DoIP_DiagNAckBuf;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_IpAddrAssignmentDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_IpAddrAssignmentDyn
  \brief  contains dynamic IP address assignment data
  \details
  Element           Description
  IpAddrReqState    IP address request state
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_IpAddrAssignmentDynUType, DOIP_VAR_NOINIT) DoIP_IpAddrAssignmentDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RoutActivHandler
**********************************************************************************************************************/
/** 
  \var    DoIP_RoutActivHandler
  \brief  single routing activation handler
  \details
  Element                 Description
  OemSpecReq              handlers oem specific request buffer
  OemSpecRes              handlers oem specific response buffer
  AliveCheckCnt           alive check timeout
  TesterAddr              handlers active testser address
  AliveCheckElemNum       number of pending alive checks
  ConnectionTcpIdx        the index of the 0:1 relation pointing to DoIP_ConnectionTcp
  OemSpecUsed             indicates if oem specific payload type is used
  RoutingActivationIdx    the index of the 0:1 relation pointing to DoIP_RoutingActivation
  TesterIdx               the index of the 0:1 relation pointing to DoIP_Tester
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_RoutActivHandlerType, DOIP_VAR_NOINIT) DoIP_RoutActivHandler[1];
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_RxHdrBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_RxHdrBuf
  \brief  buffer which stores the received message header
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_RxHdrBufUType, DOIP_VAR_NOINIT) DoIP_RxHdrBuf;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TesterDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_TesterDyn
  \brief  contains static dynamic data
  \details
  Element             Description
  DiagNAckOffset      diagnostic nack data buffer offset
  ConnectionTcpIdx    the index of the 0:1 relation pointing to DoIP_ConnectionTcp
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_TesterDynUType, DOIP_VAR_NOINIT) DoIP_TesterDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxHdrBuf
**********************************************************************************************************************/
/** 
  \var    DoIP_TxHdrBuf
  \brief  buffer which stores the message header for transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_TxHdrBufType, DOIP_VAR_NOINIT) DoIP_TxHdrBuf[84];
#define DOIP_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxTcpMgtDyn
**********************************************************************************************************************/
/** 
  \var    DoIP_TxTcpMgtDyn
  \brief  contains dynamic TCP transmission queue management data
  \details
  Element        Description
  TxHdrBufLen    length of header buffer used for transmission
  ChannelIdx     the index of the 0:1 relation pointing to DoIP_Channel
  Msg            message buffer
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_TxTcpMgtDynUType, DOIP_VAR_NOINIT) DoIP_TxTcpMgtDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_TxUdpMgtList
**********************************************************************************************************************/
/** 
  \var    DoIP_TxUdpMgtList
  \brief  UDP trasmission list
  \details
  Element          Description
  HdrType          header tpye
  RetryAttempt     retry attempts
  ConnectionIdx    the index of the 0:1 relation pointing to DoIP_Connection
  Param1           parameter depends on header type
  Param2           parameter depends on header type
  RemoteAddr       remote ip address for transmission
*/ 
#define DOIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(DoIP_TxUdpMgtListType, DOIP_VAR_NOINIT) DoIP_TxUdpMgtList[4];
#define DOIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  DoIP_PCConfig
**********************************************************************************************************************/
/** 
  \var    DoIP_PCConfig
  \details
  Element                       Description
  AliveCheckList                the pointer to DoIP_AliveCheckList
  Channel                       the pointer to DoIP_Channel
  ChannelDyn                    the pointer to DoIP_ChannelDyn
  ChannelInd                    the pointer to DoIP_ChannelInd
  Connection                    the pointer to DoIP_Connection
  ConnectionDyn                 the pointer to DoIP_ConnectionDyn
  ConnectionGroup               the pointer to DoIP_ConnectionGroup
  ConnectionInd                 the pointer to DoIP_ConnectionInd
  ConnectionTcp                 the pointer to DoIP_ConnectionTcp
  ConnectionTcpDyn              the pointer to DoIP_ConnectionTcpDyn
  ConnectionTcpInd              the pointer to DoIP_ConnectionTcpInd
  DefaultTester                 the pointer to DoIP_DefaultTester
  DiagNAckBuf                   the pointer to DoIP_DiagNAckBuf
  EId                           the pointer to DoIP_EId
  GId                           the pointer to DoIP_GId
  IpAddrAssignment              the pointer to DoIP_IpAddrAssignment
  IpAddrAssignmentDyn           the pointer to DoIP_IpAddrAssignmentDyn
  LocalAddr                     the pointer to DoIP_LocalAddr
  PduRRxCancelPduId             the pointer to DoIP_PduRRxCancelPduId
  PduRTxPduId                   the pointer to DoIP_PduRTxPduId
  RoutActivHandler              the pointer to DoIP_RoutActivHandler
  RoutingActivation             the pointer to DoIP_RoutingActivation
  RoutingActivationInd          the pointer to DoIP_RoutingActivationInd
  RxHdrBuf                      the pointer to DoIP_RxHdrBuf
  Tester                        the pointer to DoIP_Tester
  TesterDyn                     the pointer to DoIP_TesterDyn
  TxHdrBuf                      the pointer to DoIP_TxHdrBuf
  TxTcpMgt                      the pointer to DoIP_TxTcpMgt
  TxTcpMgtDyn                   the pointer to DoIP_TxTcpMgtDyn
  TxUdpMgtList                  the pointer to DoIP_TxUdpMgtList
  SizeOfDiagNAckBuf             the number of accomplishable value elements in DoIP_DiagNAckBuf
  SizeOfAliveCheckList          the number of accomplishable value elements in DoIP_AliveCheckList
  SizeOfChannel                 the number of accomplishable value elements in DoIP_Channel
  SizeOfChannelInd              the number of accomplishable value elements in DoIP_ChannelInd
  SizeOfConnection              the number of accomplishable value elements in DoIP_Connection
  SizeOfConnectionGroup         the number of accomplishable value elements in DoIP_ConnectionGroup
  SizeOfConnectionInd           the number of accomplishable value elements in DoIP_ConnectionInd
  SizeOfConnectionTcp           the number of accomplishable value elements in DoIP_ConnectionTcp
  SizeOfConnectionTcpInd        the number of accomplishable value elements in DoIP_ConnectionTcpInd
  SizeOfDefaultTester           the number of accomplishable value elements in DoIP_DefaultTester
  SizeOfEId                     the number of accomplishable value elements in DoIP_EId
  SizeOfGId                     the number of accomplishable value elements in DoIP_GId
  SizeOfIpAddrAssignment        the number of accomplishable value elements in DoIP_IpAddrAssignment
  SizeOfLocalAddr               the number of accomplishable value elements in DoIP_LocalAddr
  SizeOfPduRRxCancelPduId       the number of accomplishable value elements in DoIP_PduRRxCancelPduId
  SizeOfPduRTxPduId             the number of accomplishable value elements in DoIP_PduRTxPduId
  SizeOfRoutActivHandler        the number of accomplishable value elements in DoIP_RoutActivHandler
  SizeOfRoutingActivation       the number of accomplishable value elements in DoIP_RoutingActivation
  SizeOfRoutingActivationInd    the number of accomplishable value elements in DoIP_RoutingActivationInd
  SizeOfRxHdrBuf                the number of accomplishable value elements in DoIP_RxHdrBuf
  SizeOfTester                  the number of accomplishable value elements in DoIP_Tester
  SizeOfTxHdrBuf                the number of accomplishable value elements in DoIP_TxHdrBuf
  SizeOfTxTcpMgt                the number of accomplishable value elements in DoIP_TxTcpMgt
  SizeOfTxUdpMgtList            the number of accomplishable value elements in DoIP_TxUdpMgtList
*/ 
#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(DoIP_PCConfigsType, DOIP_CONST) DoIP_PCConfig;
#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



/**********************************************************************************************************************
 *  CALL BACK FUNCTIONS
 *********************************************************************************************************************/

#define DOIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
 *  VIN ACCESS FUNCTION
 *********************************************************************************************************************/
extern CONST(DoIP_GetVinFctPtrType, DOIP_CONST) DoIP_CallGetVinDirect;

/**********************************************************************************************************************
 *  DIAGNOSTIC POWER MODE ACCESS FUNCTION
 *********************************************************************************************************************/
extern CONST(DoIP_PowerModeFctPtrType, DOIP_CONST) DoIP_CallPowerModeDirect;

#define DOIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#endif /* DOIP_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: DoIP_Lcfg.h
 *********************************************************************************************************************/

