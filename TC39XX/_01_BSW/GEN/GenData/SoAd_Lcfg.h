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
 *            Module: SoAd
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: SoAd_Lcfg.h
 *   Generation Time: 2025-12-14 17:03:57
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined (SOAD_LCFG_H)
# define SOAD_LCFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "SoAd_Types.h"

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  SoAdPCDataSwitches  SoAd Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define SOAD_ADDRIPV4                                                 STD_OFF  /**< Deactivateable: 'SoAd_AddrIpV4' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_ADDRIPV6                                                 STD_OFF  /**< Deactivateable: 'SoAd_AddrIpV6' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_BESTMATCHSOCONIDXLIST                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFBESTMATCHSOCONIDXLIST                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_CTRLNAME                                                 STD_OFF  /**< Deactivateable: 'SoAd_CtrlName' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_DHCPEVENTCBK                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BITPATTERNOFEVENTQUEUE                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LIMITOFEVENTQUEUE                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEDYN                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IDXOFEVENTQUEUEDYN                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LVLOFEVENTQUEUEDYN                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEFLAG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIDENT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFTXROUTEGRPUSEDOFEVENTQUEUEIDENT              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFUDPPDUROUTEIDXOFEVENTQUEUEIDENT              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFUDPPDUROUTEUSEDOFEVENTQUEUEIDENT             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUELOCALADDRUSEDOFEVENTQUEUEIDENT                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESOCKIDXUSEDOFEVENTQUEUEIDENT                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESTATESOCONIDXOFEVENTQUEUEIDENT                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETCPTXSOCONUSEDOFEVENTQUEUEIDENT                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPRXSOCONUSEDOFEVENTQUEUEIDENT                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPTXSOCONUSEDOFEVENTQUEUEIDENT                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFTXROUTEGRP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPIDXOFEVENTQUEUEIFTXROUTEGRP                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFUDPPDUROUTE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEIDXOFEVENTQUEUEIFUDPPDUROUTE                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUELOCALADDR                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRIDXOFEVENTQUEUELOCALADDR                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESOCKETIDX                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETIDXOFEVENTQUEUESOCKETIDX                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESTATESOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFEVENTQUEUESTATESOCON                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETCPTXSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFEVENTQUEUETCPTXSOCON                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPRXSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFEVENTQUEUETPRXSOCON                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPTXSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFEVENTQUEUETPTXSOCON                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_FINALMAGICNUMBER                                         STD_OFF  /**< Deactivateable: 'SoAd_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define SOAD_FIRSTFREEINTEGRITYSOCKETIDX                              STD_OFF  /**< Deactivateable: 'SoAd_FirstFreeIntegritySocketIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_FIRSTUSEDINTEGRITYSOCKETIDX                              STD_OFF  /**< Deactivateable: 'SoAd_FirstUsedIntegritySocketIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_IFRXBUFFER                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INITDATAHASHCODE                                         STD_OFF  /**< Deactivateable: 'SoAd_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define SOAD_INTEGRITYSOCKETDYN                                       STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_DOMAINOFINTEGRITYSOCKETDYN                               STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.Domain' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_INTEGRITYIFIDXOFINTEGRITYSOCKETDYN                       STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.IntegrityIfIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_IPADDRESSOFINTEGRITYSOCKETDYN                            STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.IpAddress' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_NEXTINTEGRITYSOCKETIDXOFINTEGRITYSOCKETDYN               STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.NextIntegritySocketIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_PORTOFINTEGRITYSOCKETDYN                                 STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.Port' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_PREVINTEGRITYSOCKETIDXOFINTEGRITYSOCKETDYN               STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.PrevIntegritySocketIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_PROTOCOLOFINTEGRITYSOCKETDYN                             STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.Protocol' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_SOCKETIDOFINTEGRITYSOCKETDYN                             STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.SocketId' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_STATEOFINTEGRITYSOCKETDYN                                STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.State' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_USEDCOUNTOFINTEGRITYSOCKETDYN                            STD_OFF  /**< Deactivateable: 'SoAd_IntegritySocketDyn.UsedCount' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_IPFRAGBUF                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFENDIDXOFIPFRAGBUFCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFSTARTIDXOFIPFRAGBUFCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFCONFIGDYN                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LENGTHOFIPFRAGBUFCONFIGDYN                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGMGT                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFCONFIGIDXOFIPFRAGMGT                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LASTFREEINTEGRITYSOCKETIDX                               STD_OFF  /**< Deactivateable: 'SoAd_LastFreeIntegritySocketIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_LOCALADDR                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ADDRIDOFLOCALADDR                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ADDRIPV4IDXOFLOCALADDR                                   STD_OFF  /**< Deactivateable: 'SoAd_LocalAddr.AddrIpV4Idx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_ADDRIPV4USEDOFLOCALADDR                                  STD_OFF  /**< Deactivateable: 'SoAd_LocalAddr.AddrIpV4Used' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_ADDRIPV6IDXOFLOCALADDR                                   STD_OFF  /**< Deactivateable: 'SoAd_LocalAddr.AddrIpV6Idx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_ADDRIPV6USEDOFLOCALADDR                                  STD_OFF  /**< Deactivateable: 'SoAd_LocalAddr.AddrIpV6Used' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_ADDRESSTYPEOFLOCALADDR                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ASSIGNTRIGGEROFLOCALADDR                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ASSIGNTYPEOFLOCALADDR                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_DOMAINOFLOCALADDR                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NETMASKOFLOCALADDR                                       STD_OFF  /**< Deactivateable: 'SoAd_LocalAddr.Netmask' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPIPCTRLIDXOFLOCALADDR                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRBYTCPIPCTRLIND                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRCHECKINTERVAL                                   STD_OFF  /**< Deactivateable: 'SoAd_LocalAddrCheckInterval' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LOCALADDRDYN                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ADDROFLOCALADDRDYN                                       STD_OFF  /**< Deactivateable: 'SoAd_LocalAddrDyn.Addr' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_CHECKAVAILABILITYOFLOCALADDRDYN                          STD_OFF  /**< Deactivateable: 'SoAd_LocalAddrDyn.CheckAvailability' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_IPADDRREQSTATEOFLOCALADDRDYN                             STD_OFF  /**< Deactivateable: 'SoAd_LocalAddrDyn.IpAddrReqState' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_IPADDRSTATEOFLOCALADDRDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NETMASKOFLOCALADDRDYN                                    STD_OFF  /**< Deactivateable: 'SoAd_LocalAddrDyn.Netmask' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LOCALADDRIDMAP                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INVALIDHNDOFLOCALADDRIDMAP                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRIDXOFLOCALADDRIDMAP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBK                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKIND                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_MAXIFROUTEGRPTRANSMITPDUSIZE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_METADATARXBUF                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTX                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFERENDIDXOFNPDUUDPTX                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFERSTARTIDXOFNPDUUDPTX                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFERUSEDOFNPDUUDPTX                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUEENDIDXOFNPDUUDPTX                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUESTARTIDXOFNPDUUDPTX                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUEUSEDOFNPDUUDPTX                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFNPDUUDPTX                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFER                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXDYN                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BUFLENOFNPDUUDPTXDYN                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LVLOFNPDUUDPTXDYN                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RETRYCNTOFNPDUUDPTXDYN                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TOTALLENOFNPDUUDPTXDYN                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRANSMISSIONACTIVEOFNPDUUDPTXDYN                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_COPIEDOFNPDUUDPTXQUEUE                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LENOFNPDUUDPTXQUEUE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFERIDXOFNPDUUDPTXQUEUE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTIDXOFNPDUUDPTXQUEUE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTE                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ALLPDUROUTEDESTWITHPDUHDROFPDUROUTE                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFTRIGGERTRANSMITMODEOFPDUROUTE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_METADATATXENABLEDOFPDUROUTE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTENDIDXOFPDUROUTE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTSTARTIDXOFPDUROUTE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXCONFENABLEDOFPDUROUTE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXCONFPDUIDOFPDUROUTE                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXOPTIMIZEDOFPDUROUTE                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UPPERLAYERAPIOFPDUROUTE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UPPERLAYERIDXOFPDUROUTE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDEST                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEIDXOFPDUROUTEDEST                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYPDUROUTEDESTINDUSEDOFPDUROUTEDEST         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFPDUROUTEDEST                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXPDUHDRIDOFPDUROUTEDEST                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXUDPTRIGGERMODEOFPDUROUTEDEST                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UDPTRIGGERTIMEOUTOFPDUROUTEDEST                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTBYSOCONIND                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTIND                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDYN                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PENDINGTXCONFMAINOFPDUROUTEDYN                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PENDINGTXCONFNUMOFPDUROUTEDYN                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RCVREMADDR                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV4                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ADDROFREMADDRIPV4                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PORTOFREMADDRIPV4                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV6                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ADDROFREMADDRIPV6                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PORTOFREMADDRIPV6                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ENABLEDATINITOFROUTEGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_MULTIINSTANCEONGRPOFROUTEGRP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTINDENDIDXOFROUTEGRP                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTINDSTARTIDXOFROUTEGRP                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTINDUSEDOFROUTEGRP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONENDIDXOFROUTEGRP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONSTARTIDXOFROUTEGRP                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONUSEDOFROUTEGRP                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEINDENDIDXOFROUTEGRP                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEINDSTARTIDXOFROUTEGRP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEINDUSEDOFROUTEGRP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXTRIGGERABLEOFROUTEGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPIDMAP                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INVALIDHNDOFROUTEGRPIDMAP                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPIDXOFROUTEGRPIDMAP                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCON                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPIDXOFROUTEGRPSOCON                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFROUTEGRPSOCON                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYPDUROUTEDESTIND                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYSOCKETROUTEDESTIND                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONDYN                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ENABLEDOFROUTEGRPSOCONDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SENTOFROUTEGRPSOCONDYN                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGEROFROUTEGRPSOCONDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTMGT                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGIDXOFRXBUFSTRUCTMGT                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGLVLOFRXBUFSTRUCTMGT                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_DATAPTROFRXBUFSTRUCTSEG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LENOFRXBUFSTRUCTSEG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFRXBUFFERENDIDXOFRXBUFFERCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFRXBUFFERSTARTIDXOFRXBUFFERCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFRXBUFFERUSEDOFRXBUFFERCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFERENDIDXOFRXBUFFERCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFERUSEDOFRXBUFFERCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIGDYN                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFRXBUFFERIDXOFRXBUFFERCONFIGDYN                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFERIDXOFRXBUFFERCONFIGDYN                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXMGT                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_CANCELREQUESTEDOFRXMGT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBYTESPENDINGOFRXMGT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDESTIDXOFRXMGT                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXPDUIDIDMAP                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INVALIDHNDOFRXPDUIDIDMAP                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDESTIDXOFRXPDUIDIDMAP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SETLINGERTIMEOUTENABLED                                  STD_OFF  /**< Deactivateable: 'SoAd_SetLingerTimeoutEnabled' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SHUTDOWNFINISHEDCBK                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFBESTMATCHSOCONIDXLIST                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFDHCPEVENTCBK                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUE                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEFLAG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIDENT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIFTXROUTEGRP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIFUDPPDUROUTE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUELOCALADDR                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUESOCKETIDX                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUESTATESOCON                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETCPTXSOCON                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETPRXSOCON                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETPTXSOCON                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIFRXBUFFER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUF                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUFCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUFCONFIGDYN                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGMGT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDR                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRBYTCPIPCTRLIND                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRDYN                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRIDMAP                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALIPADDRASSIGNMENTCHGCBK                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKIND                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFMETADATARXBUF                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTX                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXBUFFER                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXDYN                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXQUEUE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTE                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDEST                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDESTBYSOCONIND                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDESTIND                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDYN                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRCVREMADDR                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFREMADDRIPV4                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFREMADDRIPV6                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRP                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPIDMAP                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONBYPDUROUTEDESTIND                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONBYSOCKETROUTEDESTIND                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONDYN                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFSTRUCTMGT                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFSTRUCTSEG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFFERCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFFERCONFIGDYN                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXMGT                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXPDUIDIDMAP                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSHUTDOWNFINISHEDCBK                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCON                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONDYN                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONGRP                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMAP                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMODECHGCBK                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMODECHGCBKIND                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKET                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETDYN                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETREPORTERRORCBK                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTE                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTEDEST                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTEIND                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETTCP                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETUDP                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPIPCTRL                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPKEEPALIVEGLOBALLYENABLED                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTLSSOCKETCREATEDNOTIFICATIONCBK                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUE                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUEDATA                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUEMGT                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTDYN                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTIDENT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTNPDUUDPTX                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTNPDUUDPTXMAP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTUDPALIVE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTUDPALIVEMAP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTLSCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPRXBUFFER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFERCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFERCONFIGDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUF                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUFCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUFCONFIGDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTXMGT                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTXPDUIDMAP                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFUPPERLAYER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCON                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGMGTIDXOFSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGMGTUSEDOFSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKINDUSEDOFSOCON                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXIDXOFSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXUSEDOFSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTBYSOCONINDUSEDOFSOCON                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RCVREMADDRIDXOFSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RCVREMADDRUSEDOFSOCON                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV4IDXOFSOCON                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV4USEDOFSOCON                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV6IDXOFSOCON                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV6USEDOFSOCON                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRSTATEOFSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTMGTIDXOFSOCON                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTMGTUSEDOFSOCON                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGENDIDXOFSOCON                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGSTARTIDXOFSOCON                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGUSEDOFSOCON                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIGIDXOFSOCON                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIGUSEDOFSOCON                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXMGTIDXOFSOCON                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXMGTUSEDOFSOCON                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONGRPIDXOFSOCON                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDOFSOCON                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKINDENDIDXOFSOCON                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKINDSTARTIDXOFSOCON                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKINDUSEDOFSOCON                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETIDXOFSOCON                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEENDIDXOFSOCON                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTESTARTIDXOFSOCON                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEUSEDOFSOCON                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEIDXOFSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEUSEDOFSOCON                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TLSCONFIGIDXOFSOCON                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TLSCONFIGUSEDOFSOCON                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIGIDXOFSOCON                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIGUSEDOFSOCON                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXMGTIDXOFSOCON                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXMGTUSEDOFSOCON                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_VERIFYRXPDUENABLEDOFSOCON                                STD_OFF  /**< Deactivateable: 'SoAd_SoCon.VerifyRxPduEnabled' Reason: 'SoAdVerifyRxPduCallback is not configured.' */
#define SOAD_SOCONDYN                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ABORTOFSOCONDYN                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_CLOSEMODEOFSOCONDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_MODEOFSOCONDYN                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_OPENCLOSECOUNTEROFSOCONDYN                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRDYNOFSOCONDYN                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRSTATEDYNOFSOCONDYN                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONGRP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BESTMATCHWITHPDUHEADERENABLEDOFSOCONGRP                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BESTMATCHWITHSOCKROUTEENABLEDOFSOCONGRP                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_FRAMEPRIORITYOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRIDXOFSOCONGRP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRUSEDOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALPORTOFSOCONGRP                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_MSGACCEPTFILTERENABLEDOFSOCONGRP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUHDRENABLEDOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONENDIDXOFSOCONGRP                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONSTARTIDXOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKAUTOSOCONSETUPKEEPONLINEOFSOCONGRP                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKAUTOSOCONSETUPOFSOCONGRP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETIDXOFSOCONGRP                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTCPIDXOFSOCONGRP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTCPUSEDOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETUDPIDXOFSOCONGRP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETUDPUSEDOFSOCONGRP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETUSEDOFSOCONGRP                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMAP                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INVALIDHNDOFSOCONMAP                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFSOCONMAP                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBK                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKIND                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKET                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONENDIDXOFSOCKET                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONSTARTIDXOFSOCKET                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPRXBUFFERENDIDXOFSOCKET                                STD_OFF  /**< Deactivateable: 'SoAd_Socket.TcpRxBufferEndIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXBUFFERSTARTIDXOFSOCKET                              STD_OFF  /**< Deactivateable: 'SoAd_Socket.TcpRxBufferStartIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXBUFFERUSEDOFSOCKET                                  STD_OFF  /**< Deactivateable: 'SoAd_Socket.TcpRxBufferUsed' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXMGTIDXOFSOCKET                                      STD_OFF  /**< Deactivateable: 'SoAd_Socket.TcpRxMgtIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXMGTUSEDOFSOCKET                                     STD_OFF  /**< Deactivateable: 'SoAd_Socket.TcpRxMgtUsed' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETDYN                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_DIRLINKSOCKETIDOFSOCKETDYN                               STD_OFF  /**< Deactivateable: 'SoAd_SocketDyn.DirLinkSocketId' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LIMNODESOCKETIDOFSOCKETDYN                               STD_OFF  /**< Deactivateable: 'SoAd_SocketDyn.LimNodeSocketId' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LOCALPORTOFSOCKETDYN                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SKIPBYTESOFSOCKETDYN                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONTXACTIVEIDXOFSOCKETDYN                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETIDOFSOCKETDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTXBUFFERQUEUEFIRSTIDXOFSOCKETDYN                   STD_OFF  /**< Deactivateable: 'SoAd_SocketDyn.SocketTxBufferQueueFirstIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUELASTIDXOFSOCKETDYN                    STD_OFF  /**< Deactivateable: 'SoAd_SocketDyn.SocketTxBufferQueueLastIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUENUMOFSOCKETDYN                        STD_OFF  /**< Deactivateable: 'SoAd_SocketDyn.SocketTxBufferQueueNum' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_STATEOFSOCKETDYN                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETREPORTERRORCBK                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTE                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_METADATARXENABLEDOFSOCKETROUTE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXPDUHDRIDOFSOCKETROUTE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFSOCKETROUTE                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDESTENDIDXOFSOCKETROUTE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDESTSTARTIDXOFSOCKETROUTE                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UPPERLAYERAPIOFSOCKETROUTE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDEST                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYSOCKETROUTEDESTINDUSEDOFSOCKETROUTEDEST   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXPDUIDOFSOCKETROUTEDEST                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEIDXOFSOCKETROUTEDEST                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UPPERLAYERIDXOFSOCKETROUTEDEST                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEIND                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTCP                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IMMEDTPTXCONFOFSOCKETTCP                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPINITIATEOFSOCKETTCP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPKEEPALIVEINTERVALOFSOCKETTCP                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPKEEPALIVEOFSOCKETTCP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPKEEPALIVEPROBESMAXOFSOCKETTCP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPKEEPALIVETIMEOFSOCKETTCP                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPNODELAYOFSOCKETTCP                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPRXBUFMINOFSOCKETTCP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXBUFMINOFSOCKETTCP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTOINTEGRITYSOCKETMAP                               STD_OFF  /**< Deactivateable: 'SoAd_SocketToIntegritySocketMap' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_INTEGRITYSOCKETDYNIDXOFSOCKETTOINTEGRITYSOCKETMAP        STD_OFF  /**< Deactivateable: 'SoAd_SocketToIntegritySocketMap.IntegritySocketDynIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_LOCALADDRIDXOFSOCKETTOINTEGRITYSOCKETMAP                 STD_OFF  /**< Deactivateable: 'SoAd_SocketToIntegritySocketMap.LocalAddrIdx' Reason: 'SoAdSocketApiType is not set to INTEGRITY' */
#define SOAD_SOCKETTXBUFFER                                           STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBuffer' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERMAXNUMPERSOCKET                            STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferMaxNumPerSocket' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERMGT                                        STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferMgt' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUEFIRSTUNUSEDIDXOFSOCKETTXBUFFERMGT     STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferMgt.SocketTxBufferQueueFirstUnusedIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUELASTUNUSEDIDXOFSOCKETTXBUFFERMGT      STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferMgt.SocketTxBufferQueueLastUnusedIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUE                                      STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueue' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERENDIDXOFSOCKETTXBUFFERQUEUE                STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueue.SocketTxBufferEndIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERSTARTIDXOFSOCKETTXBUFFERQUEUE              STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueue.SocketTxBufferStartIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUEDYN                                   STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LASTLENOFSOCKETTXBUFFERQUEUEDYN                          STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.LastLen' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LENOFSOCKETTXBUFFERQUEUEDYN                              STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.Len' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_READYOFSOCKETTXBUFFERQUEUEDYN                            STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.Ready' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETIDXOFSOCKETTXBUFFERQUEUEDYN                        STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.SocketIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUENEXTIDXOFSOCKETTXBUFFERQUEUEDYN       STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.SocketTxBufferQueueNextIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETTXBUFFERQUEUEPREVIDXOFSOCKETTXBUFFERQUEUEDYN       STD_OFF  /**< Deactivateable: 'SoAd_SocketTxBufferQueueDyn.SocketTxBufferQueuePrevIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETUDP                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ALIVETIMEOUTMAXCNTOFSOCKETUDP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BROADCASTRXENABLEDOFSOCKETUDP                            STD_OFF  /**< Deactivateable: 'SoAd_SocketUdp.BroadcastRxEnabled' Reason: 'SoAdSocketApiType is neither set to LINUX nor QNX' */
#define SOAD_IMMEDIFTXCONFLISTSIZEOFSOCKETUDP                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IMMEDIFTXCONFOFSOCKETUDP                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFERMINOFSOCKETUDP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUESIZEOFSOCKETUDP                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RETRYQUEUELIMITOFSOCKETUDP                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UDPLISTENONLYOFSOCKETUDP                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UDPSTRICTHDRLENCHECKENABLEDOFSOCKETUDP                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UDPTRIGGERTIMEOUTOFSOCKETUDP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPIPCTRL                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_CTRLNAMEENDIDXOFTCPIPCTRL                                STD_OFF  /**< Deactivateable: 'SoAd_TcpIpCtrl.CtrlNameEndIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_CTRLNAMESTARTIDXOFTCPIPCTRL                              STD_OFF  /**< Deactivateable: 'SoAd_TcpIpCtrl.CtrlNameStartIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LOCALADDRBYTCPIPCTRLINDENDIDXOFTCPIPCTRL                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRBYTCPIPCTRLINDSTARTIDXOFTCPIPCTRL               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRBYTCPIPCTRLINDUSEDOFTCPIPCTRL                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RETRYENABLEDOFTCPIPCTRL                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SETEGRESSENABLEDOFTCPIPCTRL                              STD_OFF  /**< Deactivateable: 'SoAd_TcpIpCtrl.SetEgressEnabled' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPIPCTRLDYN                                             STD_OFF  /**< Deactivateable: 'SoAd_TcpIpCtrlDyn' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_CTRLIDXOFTCPIPCTRLDYN                                    STD_OFF  /**< Deactivateable: 'SoAd_TcpIpCtrlDyn.CtrlIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPKEEPALIVEGLOBALLYENABLED                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPRXBUFFER                                              STD_OFF  /**< Deactivateable: 'SoAd_TcpRxBuffer' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXMGT                                                 STD_OFF  /**< Deactivateable: 'SoAd_TcpRxMgt' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LENOFTCPRXMGT                                            STD_OFF  /**< Deactivateable: 'SoAd_TcpRxMgt.Len' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPRXBUFFERIDXOFTCPRXMGT                                 STD_OFF  /**< Deactivateable: 'SoAd_TcpRxMgt.TcpRxBufferIdx' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_TCPTLSSOCKETCREATEDNOTIFICATIONCBK                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUE                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEDATAENDIDXOFTCPTXQUEUE                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEDATASTARTIDXOFTCPTXQUEUE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEDATA                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LENOFTCPTXQUEUEDATA                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEIDXOFTCPTXQUEUEDATA                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEMGT                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LVLOFTCPTXQUEUEMGT                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEDATAIDXOFTCPTXQUEUEMGT                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TOTLENOFTCPTXQUEUEMGT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYN                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LVLOFTIMEOUTLISTDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTIDENT                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYNNPDUUDPTXUSEDOFTIMEOUTLISTIDENT            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYNUDPALIVEUSEDOFTIMEOUTLISTIDENT             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTNPDUUDPTX                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTX                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTOFTIMEOUTLISTNPDUUDPTX                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTNPDUUDPTXMAP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTNPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTXMAP         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTUDPALIVE                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONIDXOFTIMEOUTLISTUDPALIVE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTOFTIMEOUTLISTUDPALIVE                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTUDPALIVEMAP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTUDPALIVEIDXOFTIMEOUTLISTUDPALIVEMAP           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TLSCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSIZEOFTLSCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTLSSOCKETCREATEDNOTIFICATIONCBKIDXOFTLSCONFIG         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTLSSOCKETCREATEDNOTIFICATIONCBKUSEDOFTLSCONFIG        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXBUFSIZEOFTLSCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFER                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFER                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERENDIDXOFTPTXBUFFERCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERSTARTIDXOFTPTXBUFFERCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERUSEDOFTPTXBUFFERCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIGDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERIDXOFTPTXBUFFERCONFIGDYN                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUF                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFENDIDXOFTRIGGERBUFCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFSTARTIDXOFTRIGGERBUFCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFCONFIGDYN                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LENGTHOFTRIGGERBUFCONFIGDYN                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEIDXOFTRIGGERBUFCONFIGDYN                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXMGT                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_CANCELREQUESTEDOFTXMGT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTIDXOFTXMGT                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXBUFPTROFTXMGT                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXBYTESLENOFTXMGT                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXBYTESPENDINGOFTXMGT                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXPDUIDMAP                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INVALIDHNDOFTXPDUIDMAP                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEIDXOFTXPDUIDMAP                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UDPRXBUFFER                                              STD_OFF  /**< Deactivateable: 'SoAd_UdpRxBuffer' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_UPPERLAYER                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFRXINDICATIONCBKOFUPPERLAYER                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFTRIGGERTRANSMITCBKOFUPPERLAYER                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IFTXCONFIRMATIONCBKOFUPPERLAYER                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPCOPYRXDATACBKOFUPPERLAYER                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPCOPYRXDATACONSTCBKOFUPPERLAYER                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPCOPYTXDATACBKOFUPPERLAYER                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPCOPYTXDATACONSTCBKOFUPPERLAYER                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXINDICATIONCBKOFUPPERLAYER                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPSTARTOFRECEPTIONCBKOFUPPERLAYER                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPSTARTOFRECEPTIONCONSTCBKOFUPPERLAYER                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXCONFIRMATIONCBKOFUPPERLAYER                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_VERIFYRXPDUBUF                                           STD_OFF  /**< Deactivateable: 'SoAd_VerifyRxPduBuf' Reason: 'SoAdVerifyRxPduMaxDataLength is 0.' */
#define SOAD_VERIFYRXPDUCBK                                           STD_OFF  /**< Deactivateable: 'SoAd_VerifyRxPduCbk' Reason: 'SoAdVerifyRxPduCallback is not configured.' */
#define SOAD_PCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_BESTMATCHSOCONIDXLISTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_DHCPEVENTCBKOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEDYNOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEFLAGOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIDENTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFTXROUTEGRPOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEIFUDPPDUROUTEOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUELOCALADDROFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUEOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESOCKETIDXOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUESTATESOCONOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETCPTXSOCONOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPRXSOCONOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_EVENTQUEUETPTXSOCONOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_FINALMAGICNUMBEROFPCCONFIG                               STD_OFF  /**< Deactivateable: 'SoAd_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define SOAD_IFRXBUFFEROFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_INITDATAHASHCODEOFPCCONFIG                               STD_OFF  /**< Deactivateable: 'SoAd_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define SOAD_IPFRAGBUFCONFIGDYNOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFCONFIGOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGBUFOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_IPFRAGMGTOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRBYTCPIPCTRLINDOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRCHECKINTERVALOFPCCONFIG                         STD_OFF  /**< Deactivateable: 'SoAd_PCConfig.LocalAddrCheckInterval' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_LOCALADDRDYNOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDRIDMAPOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALADDROFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_LOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_MAXIFROUTEGRPTRANSMITPDUSIZEOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_METADATARXBUFOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXBUFFEROFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXDYNOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_NPDUUDPTXQUEUEOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTBYSOCONINDOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTINDOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDESTOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEDYNOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_PDUROUTEOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RCVREMADDROFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV4OFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_REMADDRIPV6OFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPIDMAPOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONDYNOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_ROUTEGRPSOCONOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTMGTOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFSTRUCTSEGOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIGDYNOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXBUFFERCONFIGOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXMGTOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_RXPDUIDIDMAPOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SHUTDOWNFINISHEDCBKOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFBESTMATCHSOCONIDXLISTOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFDHCPEVENTCBKOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEDYNOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEFLAGOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIDENTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIFTXROUTEGRPOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEIFUDPPDUROUTEOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUELOCALADDROFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUEOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUESOCKETIDXOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUESTATESOCONOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETCPTXSOCONOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETPRXSOCONOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFEVENTQUEUETPTXSOCONOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIFRXBUFFEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUFCONFIGDYNOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUFCONFIGOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGBUFOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFIPFRAGMGTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRBYTCPIPCTRLINDOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRDYNOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDRIDMAPOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALADDROFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFMETADATARXBUFOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXBUFFEROFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXDYNOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFNPDUUDPTXQUEUEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDESTBYSOCONINDOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDESTINDOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDESTOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEDYNOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFPDUROUTEOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRCVREMADDROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFREMADDRIPV4OFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFREMADDRIPV6OFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPIDMAPOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONDYNOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFROUTEGRPSOCONOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFSTRUCTMGTOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFSTRUCTSEGOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFFERCONFIGDYNOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXBUFFERCONFIGOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXMGTOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFRXPDUIDIDMAPOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSHUTDOWNFINISHEDCBKOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONDYNOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONGRPOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMAPOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMODECHGCBKINDOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONMODECHGCBKOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCONOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETDYNOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETOFPCCONFIG                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETREPORTERRORCBKOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTEDESTOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTEINDOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETROUTEOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETTCPOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFSOCKETUDPOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPIPCTRLOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUEDATAOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUEMGTOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTCPTXQUEUEOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTDYNOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTIDENTOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTNPDUUDPTXOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTUDPALIVEMAPOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTIMEOUTLISTUDPALIVEOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTLSCONFIGOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPRXBUFFEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFERCONFIGDYNOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFERCONFIGOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTPTXBUFFEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUFCONFIGDYNOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUFCONFIGOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTRIGGERBUFOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTXMGTOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFTXPDUIDMAPOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SIZEOFUPPERLAYEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONDYNOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONGRPOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMAPOFPCCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKINDOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONMODECHGCBKOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCONOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETDYNOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETOFPCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETREPORTERRORCBKOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEDESTOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEINDOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETROUTEOFPCCONFIG                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTCPOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_SOCKETTXBUFFERMAXNUMPERSOCKETOFPCCONFIG                  STD_OFF  /**< Deactivateable: 'SoAd_PCConfig.SocketTxBufferMaxNumPerSocket' Reason: 'SoAdSocketApiType is AUTOSAR.' */
#define SOAD_SOCKETUDPOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPIPCTRLOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEDATAOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEMGTOFPCCONFIG                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TCPTXQUEUEOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTDYNOFPCCONFIG                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTIDENTOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTNPDUUDPTXOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTUDPALIVEMAPOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TIMEOUTLISTUDPALIVEOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TLSCONFIGOFPCCONFIG                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPRXBUFFEROFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIGDYNOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFERCONFIGOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TPTXBUFFEROFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFCONFIGDYNOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFCONFIGOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TRIGGERBUFOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXMGTOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_TXPDUIDMAPOFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define SOAD_UPPERLAYEROFPCCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCMinNumericValueDefines  SoAd Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define SOAD_MIN_SOCONIDXOFBESTMATCHSOCONIDXLIST                      0u
#define SOAD_MIN_IDXOFEVENTQUEUEDYN                                   0u
#define SOAD_MIN_LVLOFEVENTQUEUEDYN                                   0u
#define SOAD_MIN_ROUTEGRPIDXOFEVENTQUEUEIFTXROUTEGRP                  0u
#define SOAD_MIN_PDUROUTEIDXOFEVENTQUEUEIFUDPPDUROUTE                 0u
#define SOAD_MIN_LOCALADDRIDXOFEVENTQUEUELOCALADDR                    0u
#define SOAD_MIN_SOCKETIDXOFEVENTQUEUESOCKETIDX                       0u
#define SOAD_MIN_SOCONIDXOFEVENTQUEUESTATESOCON                       0u
#define SOAD_MIN_SOCONIDXOFEVENTQUEUETCPTXSOCON                       0u
#define SOAD_MIN_SOCONIDXOFEVENTQUEUETPRXSOCON                        0u
#define SOAD_MIN_SOCONIDXOFEVENTQUEUETPTXSOCON                        0u
#define SOAD_MIN_IFRXBUFFER                                           0u
#define SOAD_MIN_IPFRAGBUF                                            0u
#define SOAD_MIN_LENGTHOFIPFRAGBUFCONFIGDYN                           0u
#define SOAD_MIN_IPFRAGBUFCONFIGIDXOFIPFRAGMGT                        0u
#define SOAD_MIN_METADATARXBUF                                        0u
#define SOAD_MIN_NPDUUDPTXBUFFER                                      0u
#define SOAD_MIN_BUFLENOFNPDUUDPTXDYN                                 0u
#define SOAD_MIN_LVLOFNPDUUDPTXDYN                                    0u
#define SOAD_MIN_RETRYCNTOFNPDUUDPTXDYN                               0u
#define SOAD_MIN_TOTALLENOFNPDUUDPTXDYN                               0u
#define SOAD_MIN_LENOFNPDUUDPTXQUEUE                                  0u
#define SOAD_MIN_NPDUUDPTXBUFFERIDXOFNPDUUDPTXQUEUE                   0u
#define SOAD_MIN_PDUROUTEDESTIDXOFNPDUUDPTXQUEUE                      0u
#define SOAD_MIN_RXBUFSTRUCTSEGIDXOFRXBUFSTRUCTMGT                    0u
#define SOAD_MIN_RXBUFSTRUCTSEGLVLOFRXBUFSTRUCTMGT                    0u
#define SOAD_MIN_LENOFRXBUFSTRUCTSEG                                  0u
#define SOAD_MIN_IFRXBUFFERIDXOFRXBUFFERCONFIGDYN                     0u
#define SOAD_MIN_TPRXBUFFERIDXOFRXBUFFERCONFIGDYN                     0u
#define SOAD_MIN_RXBYTESPENDINGOFRXMGT                                0u
#define SOAD_MIN_SOCKETROUTEDESTIDXOFRXMGT                            0u
#define SOAD_MIN_OPENCLOSECOUNTEROFSOCONDYN                           0u
#define SOAD_MIN_SKIPBYTESOFSOCKETDYN                                 0u
#define SOAD_MIN_SOCONTXACTIVEIDXOFSOCKETDYN                          0u
#define SOAD_MIN_LENOFTCPTXQUEUEDATA                                  0u
#define SOAD_MIN_PDUROUTEIDXOFTCPTXQUEUEDATA                          0u
#define SOAD_MIN_LVLOFTCPTXQUEUEMGT                                   0u
#define SOAD_MIN_TCPTXQUEUEDATAIDXOFTCPTXQUEUEMGT                     0u
#define SOAD_MIN_TOTLENOFTCPTXQUEUEMGT                                0u
#define SOAD_MIN_LVLOFTIMEOUTLISTDYN                                  0u
#define SOAD_MIN_NPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTX                   0u
#define SOAD_MIN_TIMEOUTOFTIMEOUTLISTNPDUUDPTX                        0u
#define SOAD_MIN_TIMEOUTLISTNPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTXMAP     0u
#define SOAD_MIN_SOCONIDXOFTIMEOUTLISTUDPALIVE                        0u
#define SOAD_MIN_TIMEOUTOFTIMEOUTLISTUDPALIVE                         0u
#define SOAD_MIN_TIMEOUTLISTUDPALIVEIDXOFTIMEOUTLISTUDPALIVEMAP       0u
#define SOAD_MIN_TPRXBUFFER                                           0u
#define SOAD_MIN_TPTXBUFFER                                           0u
#define SOAD_MIN_TPTXBUFFERIDXOFTPTXBUFFERCONFIGDYN                   0u
#define SOAD_MIN_TRIGGERBUF                                           0u
#define SOAD_MIN_LENGTHOFTRIGGERBUFCONFIGDYN                          0u
#define SOAD_MIN_PDUROUTEIDXOFTRIGGERBUFCONFIGDYN                     0u
#define SOAD_MIN_PDUROUTEDESTIDXOFTXMGT                               0u
#define SOAD_MIN_TXBYTESLENOFTXMGT                                    0u
#define SOAD_MIN_TXBYTESPENDINGOFTXMGT                                0u
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCMaxNumericValueDefines  SoAd Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define SOAD_MAX_SOCONIDXOFBESTMATCHSOCONIDXLIST                      255u
#define SOAD_MAX_IDXOFEVENTQUEUEDYN                                   65535u
#define SOAD_MAX_LVLOFEVENTQUEUEDYN                                   65535u
#define SOAD_MAX_ROUTEGRPIDXOFEVENTQUEUEIFTXROUTEGRP                  255u
#define SOAD_MAX_PDUROUTEIDXOFEVENTQUEUEIFUDPPDUROUTE                 255u
#define SOAD_MAX_LOCALADDRIDXOFEVENTQUEUELOCALADDR                    255u
#define SOAD_MAX_SOCKETIDXOFEVENTQUEUESOCKETIDX                       255u
#define SOAD_MAX_SOCONIDXOFEVENTQUEUESTATESOCON                       255u
#define SOAD_MAX_SOCONIDXOFEVENTQUEUETCPTXSOCON                       255u
#define SOAD_MAX_SOCONIDXOFEVENTQUEUETPRXSOCON                        255u
#define SOAD_MAX_SOCONIDXOFEVENTQUEUETPTXSOCON                        255u
#define SOAD_MAX_IFRXBUFFER                                           255u
#define SOAD_MAX_IPFRAGBUF                                            255u
#define SOAD_MAX_LENGTHOFIPFRAGBUFCONFIGDYN                           65535u
#define SOAD_MAX_IPFRAGBUFCONFIGIDXOFIPFRAGMGT                        255u
#define SOAD_MAX_METADATARXBUF                                        255u
#define SOAD_MAX_NPDUUDPTXBUFFER                                      255u
#define SOAD_MAX_BUFLENOFNPDUUDPTXDYN                                 65535u
#define SOAD_MAX_LVLOFNPDUUDPTXDYN                                    255u
#define SOAD_MAX_RETRYCNTOFNPDUUDPTXDYN                               65535u
#define SOAD_MAX_TOTALLENOFNPDUUDPTXDYN                               4294967295u
#define SOAD_MAX_LENOFNPDUUDPTXQUEUE                                  255u
#define SOAD_MAX_NPDUUDPTXBUFFERIDXOFNPDUUDPTXQUEUE                   255u
#define SOAD_MAX_PDUROUTEDESTIDXOFNPDUUDPTXQUEUE                      255u
#define SOAD_MAX_RXBUFSTRUCTSEGIDXOFRXBUFSTRUCTMGT                    255u
#define SOAD_MAX_RXBUFSTRUCTSEGLVLOFRXBUFSTRUCTMGT                    255u
#define SOAD_MAX_LENOFRXBUFSTRUCTSEG                                  65535u
#define SOAD_MAX_IFRXBUFFERIDXOFRXBUFFERCONFIGDYN                     255u
#define SOAD_MAX_TPRXBUFFERIDXOFRXBUFFERCONFIGDYN                     255u
#define SOAD_MAX_RXBYTESPENDINGOFRXMGT                                255u
#define SOAD_MAX_SOCKETROUTEDESTIDXOFRXMGT                            255u
#define SOAD_MAX_OPENCLOSECOUNTEROFSOCONDYN                           4294967295u
#define SOAD_MAX_SKIPBYTESOFSOCKETDYN                                 4294967295u
#define SOAD_MAX_SOCONTXACTIVEIDXOFSOCKETDYN                          255u
#define SOAD_MAX_LENOFTCPTXQUEUEDATA                                  255u
#define SOAD_MAX_PDUROUTEIDXOFTCPTXQUEUEDATA                          255u
#define SOAD_MAX_LVLOFTCPTXQUEUEMGT                                   65535u
#define SOAD_MAX_TCPTXQUEUEDATAIDXOFTCPTXQUEUEMGT                     255u
#define SOAD_MAX_TOTLENOFTCPTXQUEUEMGT                                4294967295u
#define SOAD_MAX_LVLOFTIMEOUTLISTDYN                                  65535u
#define SOAD_MAX_NPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTX                   255u
#define SOAD_MAX_TIMEOUTOFTIMEOUTLISTNPDUUDPTX                        4294967295u
#define SOAD_MAX_TIMEOUTLISTNPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTXMAP     255u
#define SOAD_MAX_SOCONIDXOFTIMEOUTLISTUDPALIVE                        255u
#define SOAD_MAX_TIMEOUTOFTIMEOUTLISTUDPALIVE                         4294967295u
#define SOAD_MAX_TIMEOUTLISTUDPALIVEIDXOFTIMEOUTLISTUDPALIVEMAP       255u
#define SOAD_MAX_TPRXBUFFER                                           255u
#define SOAD_MAX_TPTXBUFFER                                           255u
#define SOAD_MAX_TPTXBUFFERIDXOFTPTXBUFFERCONFIGDYN                   255u
#define SOAD_MAX_TRIGGERBUF                                           255u
#define SOAD_MAX_LENGTHOFTRIGGERBUFCONFIGDYN                          65535u
#define SOAD_MAX_PDUROUTEIDXOFTRIGGERBUFCONFIGDYN                     255u
#define SOAD_MAX_PDUROUTEDESTIDXOFTXMGT                               255u
#define SOAD_MAX_TXBYTESLENOFTXMGT                                    255u
#define SOAD_MAX_TXBYTESPENDINGOFTXMGT                                255u
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCNoReferenceDefines  SoAd No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define SOAD_NO_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT            255u
#define SOAD_NO_EVENTQUEUEIFUDPPDUROUTEIDXOFEVENTQUEUEIDENT           255u
#define SOAD_NO_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT               255u
#define SOAD_NO_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT                 255u
#define SOAD_NO_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT              255u
#define SOAD_NO_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT               255u
#define SOAD_NO_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT               255u
#define SOAD_NO_ROUTEGRPIDXOFEVENTQUEUEIFTXROUTEGRP                   255u
#define SOAD_NO_PDUROUTEIDXOFEVENTQUEUEIFUDPPDUROUTE                  255u
#define SOAD_NO_LOCALADDRIDXOFEVENTQUEUELOCALADDR                     255u
#define SOAD_NO_SOCKETIDXOFEVENTQUEUESOCKETIDX                        255u
#define SOAD_NO_SOCONIDXOFEVENTQUEUESTATESOCON                        255u
#define SOAD_NO_SOCONIDXOFEVENTQUEUETCPTXSOCON                        255u
#define SOAD_NO_SOCONIDXOFEVENTQUEUETPRXSOCON                         255u
#define SOAD_NO_SOCONIDXOFEVENTQUEUETPTXSOCON                         255u
#define SOAD_NO_NPDUUDPTXBUFFERENDIDXOFNPDUUDPTX                      255u
#define SOAD_NO_NPDUUDPTXBUFFERSTARTIDXOFNPDUUDPTX                    255u
#define SOAD_NO_NPDUUDPTXQUEUEENDIDXOFNPDUUDPTX                       255u
#define SOAD_NO_NPDUUDPTXQUEUESTARTIDXOFNPDUUDPTX                     255u
#define SOAD_NO_PDUROUTEDESTIDXOFNPDUUDPTXQUEUE                       255u
#define SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST    255u
#define SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST  255u
#define SOAD_NO_TXPDUHDRIDOFPDUROUTEDEST                              255u
#define SOAD_NO_PDUROUTEDESTINDENDIDXOFROUTEGRP                       255u
#define SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP                     255u
#define SOAD_NO_ROUTEGRPSOCONENDIDXOFROUTEGRP                         255u
#define SOAD_NO_ROUTEGRPSOCONSTARTIDXOFROUTEGRP                       255u
#define SOAD_NO_SOCKETROUTEINDENDIDXOFROUTEGRP                        255u
#define SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP                      255u
#define SOAD_NO_IFRXBUFFERENDIDXOFRXBUFFERCONFIG                      255u
#define SOAD_NO_IFRXBUFFERSTARTIDXOFRXBUFFERCONFIG                    255u
#define SOAD_NO_TPRXBUFFERENDIDXOFRXBUFFERCONFIG                      255u
#define SOAD_NO_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG                    255u
#define SOAD_NO_IFRXBUFFERIDXOFRXBUFFERCONFIGDYN                      255u
#define SOAD_NO_TPRXBUFFERIDXOFRXBUFFERCONFIGDYN                      255u
#define SOAD_NO_IPFRAGMGTIDXOFSOCON                                   255u
#define SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON           255u
#define SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON         255u
#define SOAD_NO_NPDUUDPTXIDXOFSOCON                                   255u
#define SOAD_NO_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON                   255u
#define SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON                 255u
#define SOAD_NO_RCVREMADDRIDXOFSOCON                                  255u
#define SOAD_NO_REMADDRIPV4IDXOFSOCON                                 255u
#define SOAD_NO_REMADDRIPV6IDXOFSOCON                                 255u
#define SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON                              255u
#define SOAD_NO_RXBUFSTRUCTSEGENDIDXOFSOCON                           255u
#define SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON                         255u
#define SOAD_NO_RXBUFFERCONFIGIDXOFSOCON                              255u
#define SOAD_NO_RXMGTIDXOFSOCON                                       255u
#define SOAD_NO_SOCONMODECHGCBKINDENDIDXOFSOCON                       255u
#define SOAD_NO_SOCONMODECHGCBKINDSTARTIDXOFSOCON                     255u
#define SOAD_NO_SOCKETROUTEENDIDXOFSOCON                              255u
#define SOAD_NO_SOCKETROUTESTARTIDXOFSOCON                            255u
#define SOAD_NO_TCPTXQUEUEIDXOFSOCON                                  255u
#define SOAD_NO_TLSCONFIGIDXOFSOCON                                   255u
#define SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON                            255u
#define SOAD_NO_TXMGTIDXOFSOCON                                       255u
#define SOAD_NO_FRAMEPRIORITYOFSOCONGRP                               255u
#define SOAD_NO_LOCALADDRIDXOFSOCONGRP                                255u
#define SOAD_NO_SOCKETIDXOFSOCONGRP                                   255u
#define SOAD_NO_SOCKETTCPIDXOFSOCONGRP                                255u
#define SOAD_NO_SOCKETUDPIDXOFSOCONGRP                                255u
#define SOAD_NO_SOCONTXACTIVEIDXOFSOCKETDYN                           255u
#define SOAD_NO_RXPDUHDRIDOFSOCKETROUTE                               255u
#define SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST 255u
#define SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST 255u
#define SOAD_NO_TCPKEEPALIVEINTERVALOFSOCKETTCP                       255u
#define SOAD_NO_TCPKEEPALIVEPROBESMAXOFSOCKETTCP                      255u
#define SOAD_NO_TCPKEEPALIVETIMEOFSOCKETTCP                           255u
#define SOAD_NO_LOCALADDRBYTCPIPCTRLINDENDIDXOFTCPIPCTRL              255u
#define SOAD_NO_LOCALADDRBYTCPIPCTRLINDSTARTIDXOFTCPIPCTRL            255u
#define SOAD_NO_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT          255u
#define SOAD_NO_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT           255u
#define SOAD_NO_NPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTX                    255u
#define SOAD_NO_TIMEOUTLISTNPDUUDPTXIDXOFTIMEOUTLISTNPDUUDPTXMAP      255u
#define SOAD_NO_SOCONIDXOFTIMEOUTLISTUDPALIVE                         255u
#define SOAD_NO_TIMEOUTLISTUDPALIVEIDXOFTIMEOUTLISTUDPALIVEMAP        255u
#define SOAD_NO_TCPTLSSOCKETCREATEDNOTIFICATIONCBKIDXOFTLSCONFIG      255u
#define SOAD_NO_TPTXBUFFERENDIDXOFTPTXBUFFERCONFIG                    255u
#define SOAD_NO_TPTXBUFFERSTARTIDXOFTPTXBUFFERCONFIG                  255u
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCIsReducedToDefineDefines  SoAd Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define SOAD_ISDEF_DHCPEVENTCBK                                       STD_OFF
#define SOAD_ISDEF_BITPATTERNOFEVENTQUEUE                             STD_OFF
#define SOAD_ISDEF_LIMITOFEVENTQUEUE                                  STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT         STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFTXROUTEGRPUSEDOFEVENTQUEUEIDENT        STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFUDPPDUROUTEIDXOFEVENTQUEUEIDENT        STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFUDPPDUROUTEUSEDOFEVENTQUEUEIDENT       STD_OFF
#define SOAD_ISDEF_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT            STD_OFF
#define SOAD_ISDEF_EVENTQUEUELOCALADDRUSEDOFEVENTQUEUEIDENT           STD_OFF
#define SOAD_ISDEF_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT              STD_OFF
#define SOAD_ISDEF_EVENTQUEUESOCKIDXUSEDOFEVENTQUEUEIDENT             STD_OFF
#define SOAD_ISDEF_EVENTQUEUESTATESOCONIDXOFEVENTQUEUEIDENT           STD_OFF
#define SOAD_ISDEF_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT           STD_OFF
#define SOAD_ISDEF_EVENTQUEUETCPTXSOCONUSEDOFEVENTQUEUEIDENT          STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT            STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPRXSOCONUSEDOFEVENTQUEUEIDENT           STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT            STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPTXSOCONUSEDOFEVENTQUEUEIDENT           STD_OFF
#define SOAD_ISDEF_IPFRAGBUFENDIDXOFIPFRAGBUFCONFIG                   STD_OFF
#define SOAD_ISDEF_IPFRAGBUFSTARTIDXOFIPFRAGBUFCONFIG                 STD_OFF
#define SOAD_ISDEF_ADDRIDOFLOCALADDR                                  STD_OFF
#define SOAD_ISDEF_ADDRESSTYPEOFLOCALADDR                             STD_OFF
#define SOAD_ISDEF_ASSIGNTRIGGEROFLOCALADDR                           STD_OFF
#define SOAD_ISDEF_ASSIGNTYPEOFLOCALADDR                              STD_OFF
#define SOAD_ISDEF_DOMAINOFLOCALADDR                                  STD_OFF
#define SOAD_ISDEF_TCPIPCTRLIDXOFLOCALADDR                            STD_OFF
#define SOAD_ISDEF_LOCALADDRBYTCPIPCTRLIND                            STD_OFF
#define SOAD_ISDEF_INVALIDHNDOFLOCALADDRIDMAP                         STD_OFF
#define SOAD_ISDEF_LOCALADDRIDXOFLOCALADDRIDMAP                       STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBK                        STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKIND                     STD_OFF
#define SOAD_ISDEF_NPDUUDPTXBUFFERENDIDXOFNPDUUDPTX                   STD_OFF
#define SOAD_ISDEF_NPDUUDPTXBUFFERSTARTIDXOFNPDUUDPTX                 STD_OFF
#define SOAD_ISDEF_NPDUUDPTXBUFFERUSEDOFNPDUUDPTX                     STD_OFF
#define SOAD_ISDEF_NPDUUDPTXQUEUEENDIDXOFNPDUUDPTX                    STD_OFF
#define SOAD_ISDEF_NPDUUDPTXQUEUESTARTIDXOFNPDUUDPTX                  STD_OFF
#define SOAD_ISDEF_NPDUUDPTXQUEUEUSEDOFNPDUUDPTX                      STD_OFF
#define SOAD_ISDEF_SOCONIDXOFNPDUUDPTX                                STD_OFF
#define SOAD_ISDEF_ALLPDUROUTEDESTWITHPDUHDROFPDUROUTE                STD_OFF
#define SOAD_ISDEF_IFTRIGGERTRANSMITMODEOFPDUROUTE                    STD_OFF
#define SOAD_ISDEF_METADATATXENABLEDOFPDUROUTE                        STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTENDIDXOFPDUROUTE                       STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTSTARTIDXOFPDUROUTE                     STD_OFF
#define SOAD_ISDEF_TXCONFENABLEDOFPDUROUTE                            STD_OFF
#define SOAD_ISDEF_TXCONFPDUIDOFPDUROUTE                              STD_OFF
#define SOAD_ISDEF_TXOPTIMIZEDOFPDUROUTE                              STD_OFF
#define SOAD_ISDEF_UPPERLAYERAPIOFPDUROUTE                            STD_OFF
#define SOAD_ISDEF_UPPERLAYERIDXOFPDUROUTE                            STD_OFF
#define SOAD_ISDEF_PDUROUTEIDXOFPDUROUTEDEST                          STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYPDUROUTEDESTINDUSEDOFPDUROUTEDEST   STD_OFF
#define SOAD_ISDEF_SOCONIDXOFPDUROUTEDEST                             STD_OFF
#define SOAD_ISDEF_TXPDUHDRIDOFPDUROUTEDEST                           STD_OFF
#define SOAD_ISDEF_TXUDPTRIGGERMODEOFPDUROUTEDEST                     STD_OFF
#define SOAD_ISDEF_UDPTRIGGERTIMEOUTOFPDUROUTEDEST                    STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTBYSOCONIND                             STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTIND                                    STD_OFF
#define SOAD_ISDEF_ADDROFREMADDRIPV4                                  STD_OFF
#define SOAD_ISDEF_PORTOFREMADDRIPV4                                  STD_OFF
#define SOAD_ISDEF_ADDROFREMADDRIPV6                                  STD_OFF
#define SOAD_ISDEF_PORTOFREMADDRIPV6                                  STD_OFF
#define SOAD_ISDEF_ENABLEDATINITOFROUTEGRP                            STD_OFF
#define SOAD_ISDEF_MULTIINSTANCEONGRPOFROUTEGRP                       STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTINDENDIDXOFROUTEGRP                    STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTINDSTARTIDXOFROUTEGRP                  STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTINDUSEDOFROUTEGRP                      STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONENDIDXOFROUTEGRP                      STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONSTARTIDXOFROUTEGRP                    STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONUSEDOFROUTEGRP                        STD_OFF
#define SOAD_ISDEF_SOCKETROUTEINDENDIDXOFROUTEGRP                     STD_OFF
#define SOAD_ISDEF_SOCKETROUTEINDSTARTIDXOFROUTEGRP                   STD_OFF
#define SOAD_ISDEF_SOCKETROUTEINDUSEDOFROUTEGRP                       STD_OFF
#define SOAD_ISDEF_TXTRIGGERABLEOFROUTEGRP                            STD_OFF
#define SOAD_ISDEF_INVALIDHNDOFROUTEGRPIDMAP                          STD_OFF
#define SOAD_ISDEF_ROUTEGRPIDXOFROUTEGRPIDMAP                         STD_OFF
#define SOAD_ISDEF_ROUTEGRPIDXOFROUTEGRPSOCON                         STD_OFF
#define SOAD_ISDEF_SOCONIDXOFROUTEGRPSOCON                            STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYPDUROUTEDESTIND                     STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYSOCKETROUTEDESTIND                  STD_OFF
#define SOAD_ISDEF_IFRXBUFFERENDIDXOFRXBUFFERCONFIG                   STD_OFF
#define SOAD_ISDEF_IFRXBUFFERSTARTIDXOFRXBUFFERCONFIG                 STD_OFF
#define SOAD_ISDEF_IFRXBUFFERUSEDOFRXBUFFERCONFIG                     STD_OFF
#define SOAD_ISDEF_TPRXBUFFERENDIDXOFRXBUFFERCONFIG                   STD_OFF
#define SOAD_ISDEF_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG                 STD_OFF
#define SOAD_ISDEF_TPRXBUFFERUSEDOFRXBUFFERCONFIG                     STD_OFF
#define SOAD_ISDEF_INVALIDHNDOFRXPDUIDIDMAP                           STD_OFF
#define SOAD_ISDEF_SOCKETROUTEDESTIDXOFRXPDUIDIDMAP                   STD_OFF
#define SOAD_ISDEF_SHUTDOWNFINISHEDCBK                                STD_OFF
#define SOAD_ISDEF_IPFRAGMGTIDXOFSOCON                                STD_OFF
#define SOAD_ISDEF_IPFRAGMGTUSEDOFSOCON                               STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON        STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON      STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKINDUSEDOFSOCON          STD_OFF
#define SOAD_ISDEF_NPDUUDPTXIDXOFSOCON                                STD_OFF
#define SOAD_ISDEF_NPDUUDPTXUSEDOFSOCON                               STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON                STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON              STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTBYSOCONINDUSEDOFSOCON                  STD_OFF
#define SOAD_ISDEF_RCVREMADDRIDXOFSOCON                               STD_OFF
#define SOAD_ISDEF_RCVREMADDRUSEDOFSOCON                              STD_OFF
#define SOAD_ISDEF_REMADDRIPV4IDXOFSOCON                              STD_OFF
#define SOAD_ISDEF_REMADDRIPV4USEDOFSOCON                             STD_OFF
#define SOAD_ISDEF_REMADDRIPV6IDXOFSOCON                              STD_OFF
#define SOAD_ISDEF_REMADDRIPV6USEDOFSOCON                             STD_OFF
#define SOAD_ISDEF_REMADDRSTATEOFSOCON                                STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTMGTIDXOFSOCON                           STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTMGTUSEDOFSOCON                          STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTSEGENDIDXOFSOCON                        STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTSEGSTARTIDXOFSOCON                      STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTSEGUSEDOFSOCON                          STD_OFF
#define SOAD_ISDEF_RXBUFFERCONFIGIDXOFSOCON                           STD_OFF
#define SOAD_ISDEF_RXBUFFERCONFIGUSEDOFSOCON                          STD_OFF
#define SOAD_ISDEF_RXMGTIDXOFSOCON                                    STD_OFF
#define SOAD_ISDEF_RXMGTUSEDOFSOCON                                   STD_OFF
#define SOAD_ISDEF_SOCONGRPIDXOFSOCON                                 STD_OFF
#define SOAD_ISDEF_SOCONIDOFSOCON                                     STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKINDENDIDXOFSOCON                    STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKINDSTARTIDXOFSOCON                  STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKINDUSEDOFSOCON                      STD_OFF
#define SOAD_ISDEF_SOCKETIDXOFSOCON                                   STD_OFF
#define SOAD_ISDEF_SOCKETROUTEENDIDXOFSOCON                           STD_OFF
#define SOAD_ISDEF_SOCKETROUTESTARTIDXOFSOCON                         STD_OFF
#define SOAD_ISDEF_SOCKETROUTEUSEDOFSOCON                             STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEIDXOFSOCON                               STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEUSEDOFSOCON                              STD_OFF
#define SOAD_ISDEF_TLSCONFIGIDXOFSOCON                                STD_OFF
#define SOAD_ISDEF_TLSCONFIGUSEDOFSOCON                               STD_OFF
#define SOAD_ISDEF_TPTXBUFFERCONFIGIDXOFSOCON                         STD_OFF
#define SOAD_ISDEF_TPTXBUFFERCONFIGUSEDOFSOCON                        STD_OFF
#define SOAD_ISDEF_TXMGTIDXOFSOCON                                    STD_OFF
#define SOAD_ISDEF_TXMGTUSEDOFSOCON                                   STD_OFF
#define SOAD_ISDEF_BESTMATCHWITHPDUHEADERENABLEDOFSOCONGRP            STD_OFF
#define SOAD_ISDEF_BESTMATCHWITHSOCKROUTEENABLEDOFSOCONGRP            STD_OFF
#define SOAD_ISDEF_FRAMEPRIORITYOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_LOCALADDRIDXOFSOCONGRP                             STD_OFF
#define SOAD_ISDEF_LOCALADDRUSEDOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_LOCALPORTOFSOCONGRP                                STD_OFF
#define SOAD_ISDEF_MSGACCEPTFILTERENABLEDOFSOCONGRP                   STD_OFF
#define SOAD_ISDEF_PDUHDRENABLEDOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_SOCONENDIDXOFSOCONGRP                              STD_OFF
#define SOAD_ISDEF_SOCONSTARTIDXOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_SOCKAUTOSOCONSETUPKEEPONLINEOFSOCONGRP             STD_OFF
#define SOAD_ISDEF_SOCKAUTOSOCONSETUPOFSOCONGRP                       STD_OFF
#define SOAD_ISDEF_SOCKETIDXOFSOCONGRP                                STD_OFF
#define SOAD_ISDEF_SOCKETTCPIDXOFSOCONGRP                             STD_OFF
#define SOAD_ISDEF_SOCKETTCPUSEDOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_SOCKETUDPIDXOFSOCONGRP                             STD_OFF
#define SOAD_ISDEF_SOCKETUDPUSEDOFSOCONGRP                            STD_OFF
#define SOAD_ISDEF_SOCKETUSEDOFSOCONGRP                               STD_OFF
#define SOAD_ISDEF_INVALIDHNDOFSOCONMAP                               STD_OFF
#define SOAD_ISDEF_SOCONIDXOFSOCONMAP                                 STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBK                                    STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKIND                                 STD_OFF
#define SOAD_ISDEF_SOCONENDIDXOFSOCKET                                STD_OFF
#define SOAD_ISDEF_SOCONSTARTIDXOFSOCKET                              STD_OFF
#define SOAD_ISDEF_SOCKETREPORTERRORCBK                               STD_OFF
#define SOAD_ISDEF_METADATARXENABLEDOFSOCKETROUTE                     STD_OFF
#define SOAD_ISDEF_RXPDUHDRIDOFSOCKETROUTE                            STD_OFF
#define SOAD_ISDEF_SOCONIDXOFSOCKETROUTE                              STD_OFF
#define SOAD_ISDEF_SOCKETROUTEDESTENDIDXOFSOCKETROUTE                 STD_OFF
#define SOAD_ISDEF_SOCKETROUTEDESTSTARTIDXOFSOCKETROUTE               STD_OFF
#define SOAD_ISDEF_UPPERLAYERAPIOFSOCKETROUTE                         STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYSOCKETROUTEDESTINDUSEDOFSOCKETROUTEDEST STD_OFF
#define SOAD_ISDEF_RXPDUIDOFSOCKETROUTEDEST                           STD_OFF
#define SOAD_ISDEF_SOCKETROUTEIDXOFSOCKETROUTEDEST                    STD_OFF
#define SOAD_ISDEF_UPPERLAYERIDXOFSOCKETROUTEDEST                     STD_OFF
#define SOAD_ISDEF_SOCKETROUTEIND                                     STD_OFF
#define SOAD_ISDEF_IMMEDTPTXCONFOFSOCKETTCP                           STD_OFF
#define SOAD_ISDEF_TCPINITIATEOFSOCKETTCP                             STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVEINTERVALOFSOCKETTCP                    STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVEOFSOCKETTCP                            STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVEPROBESMAXOFSOCKETTCP                   STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVETIMEOFSOCKETTCP                        STD_OFF
#define SOAD_ISDEF_TCPNODELAYOFSOCKETTCP                              STD_OFF
#define SOAD_ISDEF_TCPRXBUFMINOFSOCKETTCP                             STD_OFF
#define SOAD_ISDEF_TCPTXBUFMINOFSOCKETTCP                             STD_OFF
#define SOAD_ISDEF_ALIVETIMEOUTMAXCNTOFSOCKETUDP                      STD_OFF
#define SOAD_ISDEF_IMMEDIFTXCONFLISTSIZEOFSOCKETUDP                   STD_OFF
#define SOAD_ISDEF_IMMEDIFTXCONFOFSOCKETUDP                           STD_OFF
#define SOAD_ISDEF_NPDUUDPTXBUFFERMINOFSOCKETUDP                      STD_OFF
#define SOAD_ISDEF_NPDUUDPTXQUEUESIZEOFSOCKETUDP                      STD_OFF
#define SOAD_ISDEF_RETRYQUEUELIMITOFSOCKETUDP                         STD_OFF
#define SOAD_ISDEF_UDPLISTENONLYOFSOCKETUDP                           STD_OFF
#define SOAD_ISDEF_UDPSTRICTHDRLENCHECKENABLEDOFSOCKETUDP             STD_OFF
#define SOAD_ISDEF_UDPTRIGGERTIMEOUTOFSOCKETUDP                       STD_OFF
#define SOAD_ISDEF_LOCALADDRBYTCPIPCTRLINDENDIDXOFTCPIPCTRL           STD_OFF
#define SOAD_ISDEF_LOCALADDRBYTCPIPCTRLINDSTARTIDXOFTCPIPCTRL         STD_OFF
#define SOAD_ISDEF_LOCALADDRBYTCPIPCTRLINDUSEDOFTCPIPCTRL             STD_OFF
#define SOAD_ISDEF_RETRYENABLEDOFTCPIPCTRL                            STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVEGLOBALLYENABLED                        STD_OFF
#define SOAD_ISDEF_TCPTLSSOCKETCREATEDNOTIFICATIONCBK                 STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEDATAENDIDXOFTCPTXQUEUE                   STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEDATASTARTIDXOFTCPTXQUEUE                 STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT       STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTDYNNPDUUDPTXUSEDOFTIMEOUTLISTIDENT      STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT        STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTDYNUDPALIVEUSEDOFTIMEOUTLISTIDENT       STD_OFF
#define SOAD_ISDEF_RXBUFSIZEOFTLSCONFIG                               STD_OFF
#define SOAD_ISDEF_TCPTLSSOCKETCREATEDNOTIFICATIONCBKIDXOFTLSCONFIG   STD_OFF
#define SOAD_ISDEF_TCPTLSSOCKETCREATEDNOTIFICATIONCBKUSEDOFTLSCONFIG  STD_OFF
#define SOAD_ISDEF_TXBUFSIZEOFTLSCONFIG                               STD_OFF
#define SOAD_ISDEF_TPTXBUFFERENDIDXOFTPTXBUFFERCONFIG                 STD_OFF
#define SOAD_ISDEF_TPTXBUFFERSTARTIDXOFTPTXBUFFERCONFIG               STD_OFF
#define SOAD_ISDEF_TPTXBUFFERUSEDOFTPTXBUFFERCONFIG                   STD_OFF
#define SOAD_ISDEF_TRIGGERBUFENDIDXOFTRIGGERBUFCONFIG                 STD_OFF
#define SOAD_ISDEF_TRIGGERBUFSTARTIDXOFTRIGGERBUFCONFIG               STD_OFF
#define SOAD_ISDEF_INVALIDHNDOFTXPDUIDMAP                             STD_OFF
#define SOAD_ISDEF_PDUROUTEIDXOFTXPDUIDMAP                            STD_OFF
#define SOAD_ISDEF_IFRXINDICATIONCBKOFUPPERLAYER                      STD_OFF
#define SOAD_ISDEF_IFTRIGGERTRANSMITCBKOFUPPERLAYER                   STD_OFF
#define SOAD_ISDEF_IFTXCONFIRMATIONCBKOFUPPERLAYER                    STD_OFF
#define SOAD_ISDEF_TPCOPYRXDATACBKOFUPPERLAYER                        STD_OFF
#define SOAD_ISDEF_TPCOPYRXDATACONSTCBKOFUPPERLAYER                   STD_OFF
#define SOAD_ISDEF_TPCOPYTXDATACBKOFUPPERLAYER                        STD_OFF
#define SOAD_ISDEF_TPCOPYTXDATACONSTCBKOFUPPERLAYER                   STD_OFF
#define SOAD_ISDEF_TPRXINDICATIONCBKOFUPPERLAYER                      STD_OFF
#define SOAD_ISDEF_TPSTARTOFRECEPTIONCBKOFUPPERLAYER                  STD_OFF
#define SOAD_ISDEF_TPSTARTOFRECEPTIONCONSTCBKOFUPPERLAYER             STD_OFF
#define SOAD_ISDEF_TPTXCONFIRMATIONCBKOFUPPERLAYER                    STD_OFF
#define SOAD_ISDEF_BESTMATCHSOCONIDXLISTOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_DHCPEVENTCBKOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_EVENTQUEUEDYNOFPCCONFIG                            STD_OFF
#define SOAD_ISDEF_EVENTQUEUEFLAGOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIDENTOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFTXROUTEGRPOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_EVENTQUEUEIFUDPPDUROUTEOFPCCONFIG                  STD_OFF
#define SOAD_ISDEF_EVENTQUEUELOCALADDROFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_EVENTQUEUEOFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_EVENTQUEUESOCKETIDXOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_EVENTQUEUESTATESOCONOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_EVENTQUEUETCPTXSOCONOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPRXSOCONOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_EVENTQUEUETPTXSOCONOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_IFRXBUFFEROFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_IPFRAGBUFCONFIGDYNOFPCCONFIG                       STD_OFF
#define SOAD_ISDEF_IPFRAGBUFCONFIGOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_IPFRAGBUFOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_IPFRAGMGTOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_LOCALADDRBYTCPIPCTRLINDOFPCCONFIG                  STD_OFF
#define SOAD_ISDEF_LOCALADDRDYNOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_LOCALADDRIDMAPOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_LOCALADDROFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG           STD_OFF
#define SOAD_ISDEF_LOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG              STD_OFF
#define SOAD_ISDEF_MAXIFROUTEGRPTRANSMITPDUSIZEOFPCCONFIG             STD_OFF
#define SOAD_ISDEF_METADATARXBUFOFPCCONFIG                            STD_OFF
#define SOAD_ISDEF_NPDUUDPTXBUFFEROFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_NPDUUDPTXDYNOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_NPDUUDPTXOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_NPDUUDPTXQUEUEOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTBYSOCONINDOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTINDOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_PDUROUTEDESTOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_PDUROUTEDYNOFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_PDUROUTEOFPCCONFIG                                 STD_OFF
#define SOAD_ISDEF_RCVREMADDROFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_REMADDRIPV4OFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_REMADDRIPV6OFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_ROUTEGRPIDMAPOFPCCONFIG                            STD_OFF
#define SOAD_ISDEF_ROUTEGRPOFPCCONFIG                                 STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG           STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG        STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONDYNOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_ROUTEGRPSOCONOFPCCONFIG                            STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTMGTOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_RXBUFSTRUCTSEGOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_RXBUFFERCONFIGDYNOFPCCONFIG                        STD_OFF
#define SOAD_ISDEF_RXBUFFERCONFIGOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_RXMGTOFPCCONFIG                                    STD_OFF
#define SOAD_ISDEF_RXPDUIDIDMAPOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_SHUTDOWNFINISHEDCBKOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_SIZEOFBESTMATCHSOCONIDXLISTOFPCCONFIG              STD_OFF
#define SOAD_ISDEF_SIZEOFDHCPEVENTCBKOFPCCONFIG                       STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUEFLAGOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUEIDENTOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUEIFTXROUTEGRPOFPCCONFIG             STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUEIFUDPPDUROUTEOFPCCONFIG            STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUELOCALADDROFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUEOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUESOCKETIDXOFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUESTATESOCONOFPCCONFIG               STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUETCPTXSOCONOFPCCONFIG               STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUETPRXSOCONOFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFEVENTQUEUETPTXSOCONOFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFIFRXBUFFEROFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFIPFRAGBUFCONFIGOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFIPFRAGBUFOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFIPFRAGMGTOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFLOCALADDRBYTCPIPCTRLINDOFPCCONFIG            STD_OFF
#define SOAD_ISDEF_SIZEOFLOCALADDRIDMAPOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFLOCALADDROFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG     STD_OFF
#define SOAD_ISDEF_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG        STD_OFF
#define SOAD_ISDEF_SIZEOFMETADATARXBUFOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_SIZEOFNPDUUDPTXBUFFEROFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFNPDUUDPTXOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFNPDUUDPTXQUEUEOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFPDUROUTEDESTBYSOCONINDOFPCCONFIG             STD_OFF
#define SOAD_ISDEF_SIZEOFPDUROUTEDESTINDOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFPDUROUTEDESTOFPCCONFIG                       STD_OFF
#define SOAD_ISDEF_SIZEOFPDUROUTEOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_SIZEOFRCVREMADDROFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFREMADDRIPV4OFPCCONFIG                        STD_OFF
#define SOAD_ISDEF_SIZEOFREMADDRIPV6OFPCCONFIG                        STD_OFF
#define SOAD_ISDEF_SIZEOFROUTEGRPIDMAPOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_SIZEOFROUTEGRPOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_SIZEOFROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG     STD_OFF
#define SOAD_ISDEF_SIZEOFROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG  STD_OFF
#define SOAD_ISDEF_SIZEOFROUTEGRPSOCONOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_SIZEOFRXBUFSTRUCTMGTOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFRXBUFSTRUCTSEGOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFRXBUFFERCONFIGOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFRXMGTOFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_SIZEOFRXPDUIDIDMAPOFPCCONFIG                       STD_OFF
#define SOAD_ISDEF_SIZEOFSHUTDOWNFINISHEDCBKOFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFSOCONGRPOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_SIZEOFSOCONMAPOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_SIZEOFSOCONMODECHGCBKINDOFPCCONFIG                 STD_OFF
#define SOAD_ISDEF_SIZEOFSOCONMODECHGCBKOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFSOCONOFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETOFPCCONFIG                             STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETREPORTERRORCBKOFPCCONFIG               STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETROUTEDESTOFPCCONFIG                    STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETROUTEINDOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETROUTEOFPCCONFIG                        STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETTCPOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFSOCKETUDPOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFTCPIPCTRLOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFTCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG        STD_OFF
#define SOAD_ISDEF_SIZEOFTCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG STD_OFF
#define SOAD_ISDEF_SIZEOFTCPTXQUEUEDATAOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFTCPTXQUEUEOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTDYNOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTIDENTOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG            STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTNPDUUDPTXOFPCCONFIG               STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTUDPALIVEMAPOFPCCONFIG             STD_OFF
#define SOAD_ISDEF_SIZEOFTIMEOUTLISTUDPALIVEOFPCCONFIG                STD_OFF
#define SOAD_ISDEF_SIZEOFTLSCONFIGOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SIZEOFTPRXBUFFEROFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFTPTXBUFFERCONFIGOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_SIZEOFTPTXBUFFEROFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFTRIGGERBUFCONFIGOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_SIZEOFTRIGGERBUFOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFTXMGTOFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_SIZEOFTXPDUIDMAPOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SIZEOFUPPERLAYEROFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_SOCONDYNOFPCCONFIG                                 STD_OFF
#define SOAD_ISDEF_SOCONGRPOFPCCONFIG                                 STD_OFF
#define SOAD_ISDEF_SOCONMAPOFPCCONFIG                                 STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKINDOFPCCONFIG                       STD_OFF
#define SOAD_ISDEF_SOCONMODECHGCBKOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SOCONOFPCCONFIG                                    STD_OFF
#define SOAD_ISDEF_SOCKETDYNOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_SOCKETOFPCCONFIG                                   STD_OFF
#define SOAD_ISDEF_SOCKETREPORTERRORCBKOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_SOCKETROUTEDESTOFPCCONFIG                          STD_OFF
#define SOAD_ISDEF_SOCKETROUTEINDOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_SOCKETROUTEOFPCCONFIG                              STD_OFF
#define SOAD_ISDEF_SOCKETTCPOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_SOCKETUDPOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_TCPIPCTRLOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_TCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG              STD_OFF
#define SOAD_ISDEF_TCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG       STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEDATAOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEMGTOFPCCONFIG                            STD_OFF
#define SOAD_ISDEF_TCPTXQUEUEOFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTDYNOFPCCONFIG                           STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTIDENTOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG                  STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTNPDUUDPTXOFPCCONFIG                     STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTUDPALIVEMAPOFPCCONFIG                   STD_OFF
#define SOAD_ISDEF_TIMEOUTLISTUDPALIVEOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_TLSCONFIGOFPCCONFIG                                STD_OFF
#define SOAD_ISDEF_TPRXBUFFEROFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_TPTXBUFFERCONFIGDYNOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_TPTXBUFFERCONFIGOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_TPTXBUFFEROFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_TRIGGERBUFCONFIGDYNOFPCCONFIG                      STD_OFF
#define SOAD_ISDEF_TRIGGERBUFCONFIGOFPCCONFIG                         STD_OFF
#define SOAD_ISDEF_TRIGGERBUFOFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_TXMGTOFPCCONFIG                                    STD_OFF
#define SOAD_ISDEF_TXPDUIDMAPOFPCCONFIG                               STD_OFF
#define SOAD_ISDEF_UPPERLAYEROFPCCONFIG                               STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCEqualsAlwaysToDefines  SoAd Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define SOAD_EQ2_DHCPEVENTCBK                                         
#define SOAD_EQ2_BITPATTERNOFEVENTQUEUE                               
#define SOAD_EQ2_LIMITOFEVENTQUEUE                                    
#define SOAD_EQ2_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT           
#define SOAD_EQ2_EVENTQUEUEIFTXROUTEGRPUSEDOFEVENTQUEUEIDENT          
#define SOAD_EQ2_EVENTQUEUEIFUDPPDUROUTEIDXOFEVENTQUEUEIDENT          
#define SOAD_EQ2_EVENTQUEUEIFUDPPDUROUTEUSEDOFEVENTQUEUEIDENT         
#define SOAD_EQ2_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT              
#define SOAD_EQ2_EVENTQUEUELOCALADDRUSEDOFEVENTQUEUEIDENT             
#define SOAD_EQ2_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT                
#define SOAD_EQ2_EVENTQUEUESOCKIDXUSEDOFEVENTQUEUEIDENT               
#define SOAD_EQ2_EVENTQUEUESTATESOCONIDXOFEVENTQUEUEIDENT             
#define SOAD_EQ2_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT             
#define SOAD_EQ2_EVENTQUEUETCPTXSOCONUSEDOFEVENTQUEUEIDENT            
#define SOAD_EQ2_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT              
#define SOAD_EQ2_EVENTQUEUETPRXSOCONUSEDOFEVENTQUEUEIDENT             
#define SOAD_EQ2_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT              
#define SOAD_EQ2_EVENTQUEUETPTXSOCONUSEDOFEVENTQUEUEIDENT             
#define SOAD_EQ2_IPFRAGBUFENDIDXOFIPFRAGBUFCONFIG                     
#define SOAD_EQ2_IPFRAGBUFSTARTIDXOFIPFRAGBUFCONFIG                   
#define SOAD_EQ2_ADDRIDOFLOCALADDR                                    
#define SOAD_EQ2_ADDRESSTYPEOFLOCALADDR                               
#define SOAD_EQ2_ASSIGNTRIGGEROFLOCALADDR                             
#define SOAD_EQ2_ASSIGNTYPEOFLOCALADDR                                
#define SOAD_EQ2_DOMAINOFLOCALADDR                                    
#define SOAD_EQ2_TCPIPCTRLIDXOFLOCALADDR                              
#define SOAD_EQ2_LOCALADDRBYTCPIPCTRLIND                              
#define SOAD_EQ2_INVALIDHNDOFLOCALADDRIDMAP                           
#define SOAD_EQ2_LOCALADDRIDXOFLOCALADDRIDMAP                         
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBK                          
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKIND                       
#define SOAD_EQ2_NPDUUDPTXBUFFERENDIDXOFNPDUUDPTX                     
#define SOAD_EQ2_NPDUUDPTXBUFFERSTARTIDXOFNPDUUDPTX                   
#define SOAD_EQ2_NPDUUDPTXBUFFERUSEDOFNPDUUDPTX                       
#define SOAD_EQ2_NPDUUDPTXQUEUEENDIDXOFNPDUUDPTX                      
#define SOAD_EQ2_NPDUUDPTXQUEUESTARTIDXOFNPDUUDPTX                    
#define SOAD_EQ2_NPDUUDPTXQUEUEUSEDOFNPDUUDPTX                        
#define SOAD_EQ2_SOCONIDXOFNPDUUDPTX                                  
#define SOAD_EQ2_ALLPDUROUTEDESTWITHPDUHDROFPDUROUTE                  
#define SOAD_EQ2_IFTRIGGERTRANSMITMODEOFPDUROUTE                      
#define SOAD_EQ2_METADATATXENABLEDOFPDUROUTE                          
#define SOAD_EQ2_PDUROUTEDESTENDIDXOFPDUROUTE                         
#define SOAD_EQ2_PDUROUTEDESTSTARTIDXOFPDUROUTE                       
#define SOAD_EQ2_TXCONFENABLEDOFPDUROUTE                              
#define SOAD_EQ2_TXCONFPDUIDOFPDUROUTE                                
#define SOAD_EQ2_TXOPTIMIZEDOFPDUROUTE                                
#define SOAD_EQ2_UPPERLAYERAPIOFPDUROUTE                              
#define SOAD_EQ2_UPPERLAYERIDXOFPDUROUTE                              
#define SOAD_EQ2_PDUROUTEIDXOFPDUROUTEDEST                            
#define SOAD_EQ2_ROUTEGRPSOCONBYPDUROUTEDESTINDENDIDXOFPDUROUTEDEST   
#define SOAD_EQ2_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST 
#define SOAD_EQ2_ROUTEGRPSOCONBYPDUROUTEDESTINDUSEDOFPDUROUTEDEST     
#define SOAD_EQ2_SOCONIDXOFPDUROUTEDEST                               
#define SOAD_EQ2_TXPDUHDRIDOFPDUROUTEDEST                             
#define SOAD_EQ2_TXUDPTRIGGERMODEOFPDUROUTEDEST                       
#define SOAD_EQ2_UDPTRIGGERTIMEOUTOFPDUROUTEDEST                      
#define SOAD_EQ2_PDUROUTEDESTBYSOCONIND                               
#define SOAD_EQ2_PDUROUTEDESTIND                                      
#define SOAD_EQ2_ADDROFREMADDRIPV4                                    
#define SOAD_EQ2_PORTOFREMADDRIPV4                                    
#define SOAD_EQ2_ADDROFREMADDRIPV6                                    
#define SOAD_EQ2_PORTOFREMADDRIPV6                                    
#define SOAD_EQ2_ENABLEDATINITOFROUTEGRP                              
#define SOAD_EQ2_MULTIINSTANCEONGRPOFROUTEGRP                         
#define SOAD_EQ2_PDUROUTEDESTINDENDIDXOFROUTEGRP                      
#define SOAD_EQ2_PDUROUTEDESTINDSTARTIDXOFROUTEGRP                    
#define SOAD_EQ2_PDUROUTEDESTINDUSEDOFROUTEGRP                        
#define SOAD_EQ2_ROUTEGRPSOCONENDIDXOFROUTEGRP                        
#define SOAD_EQ2_ROUTEGRPSOCONSTARTIDXOFROUTEGRP                      
#define SOAD_EQ2_ROUTEGRPSOCONUSEDOFROUTEGRP                          
#define SOAD_EQ2_SOCKETROUTEINDENDIDXOFROUTEGRP                       
#define SOAD_EQ2_SOCKETROUTEINDSTARTIDXOFROUTEGRP                     
#define SOAD_EQ2_SOCKETROUTEINDUSEDOFROUTEGRP                         
#define SOAD_EQ2_TXTRIGGERABLEOFROUTEGRP                              
#define SOAD_EQ2_INVALIDHNDOFROUTEGRPIDMAP                            
#define SOAD_EQ2_ROUTEGRPIDXOFROUTEGRPIDMAP                           
#define SOAD_EQ2_ROUTEGRPIDXOFROUTEGRPSOCON                           
#define SOAD_EQ2_SOCONIDXOFROUTEGRPSOCON                              
#define SOAD_EQ2_ROUTEGRPSOCONBYPDUROUTEDESTIND                       
#define SOAD_EQ2_ROUTEGRPSOCONBYSOCKETROUTEDESTIND                    
#define SOAD_EQ2_IFRXBUFFERENDIDXOFRXBUFFERCONFIG                     
#define SOAD_EQ2_IFRXBUFFERSTARTIDXOFRXBUFFERCONFIG                   
#define SOAD_EQ2_IFRXBUFFERUSEDOFRXBUFFERCONFIG                       
#define SOAD_EQ2_TPRXBUFFERENDIDXOFRXBUFFERCONFIG                     
#define SOAD_EQ2_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG                   
#define SOAD_EQ2_TPRXBUFFERUSEDOFRXBUFFERCONFIG                       
#define SOAD_EQ2_INVALIDHNDOFRXPDUIDIDMAP                             
#define SOAD_EQ2_SOCKETROUTEDESTIDXOFRXPDUIDIDMAP                     
#define SOAD_EQ2_SHUTDOWNFINISHEDCBK                                  
#define SOAD_EQ2_IPFRAGMGTIDXOFSOCON                                  
#define SOAD_EQ2_IPFRAGMGTUSEDOFSOCON                                 
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKINDENDIDXOFSOCON          
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON        
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKINDUSEDOFSOCON            
#define SOAD_EQ2_NPDUUDPTXIDXOFSOCON                                  
#define SOAD_EQ2_NPDUUDPTXUSEDOFSOCON                                 
#define SOAD_EQ2_PDUROUTEDESTBYSOCONINDENDIDXOFSOCON                  
#define SOAD_EQ2_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON                
#define SOAD_EQ2_PDUROUTEDESTBYSOCONINDUSEDOFSOCON                    
#define SOAD_EQ2_RCVREMADDRIDXOFSOCON                                 
#define SOAD_EQ2_RCVREMADDRUSEDOFSOCON                                
#define SOAD_EQ2_REMADDRIPV4IDXOFSOCON                                
#define SOAD_EQ2_REMADDRIPV4USEDOFSOCON                               
#define SOAD_EQ2_REMADDRIPV6IDXOFSOCON                                
#define SOAD_EQ2_REMADDRIPV6USEDOFSOCON                               
#define SOAD_EQ2_REMADDRSTATEOFSOCON                                  
#define SOAD_EQ2_RXBUFSTRUCTMGTIDXOFSOCON                             
#define SOAD_EQ2_RXBUFSTRUCTMGTUSEDOFSOCON                            
#define SOAD_EQ2_RXBUFSTRUCTSEGENDIDXOFSOCON                          
#define SOAD_EQ2_RXBUFSTRUCTSEGSTARTIDXOFSOCON                        
#define SOAD_EQ2_RXBUFSTRUCTSEGUSEDOFSOCON                            
#define SOAD_EQ2_RXBUFFERCONFIGIDXOFSOCON                             
#define SOAD_EQ2_RXBUFFERCONFIGUSEDOFSOCON                            
#define SOAD_EQ2_RXMGTIDXOFSOCON                                      
#define SOAD_EQ2_RXMGTUSEDOFSOCON                                     
#define SOAD_EQ2_SOCONGRPIDXOFSOCON                                   
#define SOAD_EQ2_SOCONIDOFSOCON                                       
#define SOAD_EQ2_SOCONMODECHGCBKINDENDIDXOFSOCON                      
#define SOAD_EQ2_SOCONMODECHGCBKINDSTARTIDXOFSOCON                    
#define SOAD_EQ2_SOCONMODECHGCBKINDUSEDOFSOCON                        
#define SOAD_EQ2_SOCKETIDXOFSOCON                                     
#define SOAD_EQ2_SOCKETROUTEENDIDXOFSOCON                             
#define SOAD_EQ2_SOCKETROUTESTARTIDXOFSOCON                           
#define SOAD_EQ2_SOCKETROUTEUSEDOFSOCON                               
#define SOAD_EQ2_TCPTXQUEUEIDXOFSOCON                                 
#define SOAD_EQ2_TCPTXQUEUEUSEDOFSOCON                                
#define SOAD_EQ2_TLSCONFIGIDXOFSOCON                                  
#define SOAD_EQ2_TLSCONFIGUSEDOFSOCON                                 
#define SOAD_EQ2_TPTXBUFFERCONFIGIDXOFSOCON                           
#define SOAD_EQ2_TPTXBUFFERCONFIGUSEDOFSOCON                          
#define SOAD_EQ2_TXMGTIDXOFSOCON                                      
#define SOAD_EQ2_TXMGTUSEDOFSOCON                                     
#define SOAD_EQ2_BESTMATCHWITHPDUHEADERENABLEDOFSOCONGRP              
#define SOAD_EQ2_BESTMATCHWITHSOCKROUTEENABLEDOFSOCONGRP              
#define SOAD_EQ2_FRAMEPRIORITYOFSOCONGRP                              
#define SOAD_EQ2_LOCALADDRIDXOFSOCONGRP                               
#define SOAD_EQ2_LOCALADDRUSEDOFSOCONGRP                              
#define SOAD_EQ2_LOCALPORTOFSOCONGRP                                  
#define SOAD_EQ2_MSGACCEPTFILTERENABLEDOFSOCONGRP                     
#define SOAD_EQ2_PDUHDRENABLEDOFSOCONGRP                              
#define SOAD_EQ2_SOCONENDIDXOFSOCONGRP                                
#define SOAD_EQ2_SOCONSTARTIDXOFSOCONGRP                              
#define SOAD_EQ2_SOCKAUTOSOCONSETUPKEEPONLINEOFSOCONGRP               
#define SOAD_EQ2_SOCKAUTOSOCONSETUPOFSOCONGRP                         
#define SOAD_EQ2_SOCKETIDXOFSOCONGRP                                  
#define SOAD_EQ2_SOCKETTCPIDXOFSOCONGRP                               
#define SOAD_EQ2_SOCKETTCPUSEDOFSOCONGRP                              
#define SOAD_EQ2_SOCKETUDPIDXOFSOCONGRP                               
#define SOAD_EQ2_SOCKETUDPUSEDOFSOCONGRP                              
#define SOAD_EQ2_SOCKETUSEDOFSOCONGRP                                 
#define SOAD_EQ2_INVALIDHNDOFSOCONMAP                                 
#define SOAD_EQ2_SOCONIDXOFSOCONMAP                                   
#define SOAD_EQ2_SOCONMODECHGCBK                                      
#define SOAD_EQ2_SOCONMODECHGCBKIND                                   
#define SOAD_EQ2_SOCONENDIDXOFSOCKET                                  
#define SOAD_EQ2_SOCONSTARTIDXOFSOCKET                                
#define SOAD_EQ2_SOCKETREPORTERRORCBK                                 
#define SOAD_EQ2_METADATARXENABLEDOFSOCKETROUTE                       
#define SOAD_EQ2_RXPDUHDRIDOFSOCKETROUTE                              
#define SOAD_EQ2_SOCONIDXOFSOCKETROUTE                                
#define SOAD_EQ2_SOCKETROUTEDESTENDIDXOFSOCKETROUTE                   
#define SOAD_EQ2_SOCKETROUTEDESTSTARTIDXOFSOCKETROUTE                 
#define SOAD_EQ2_UPPERLAYERAPIOFSOCKETROUTE                           
#define SOAD_EQ2_ROUTEGRPSOCONBYSOCKETROUTEDESTINDENDIDXOFSOCKETROUTEDEST 
#define SOAD_EQ2_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST 
#define SOAD_EQ2_ROUTEGRPSOCONBYSOCKETROUTEDESTINDUSEDOFSOCKETROUTEDEST 
#define SOAD_EQ2_RXPDUIDOFSOCKETROUTEDEST                             
#define SOAD_EQ2_SOCKETROUTEIDXOFSOCKETROUTEDEST                      
#define SOAD_EQ2_UPPERLAYERIDXOFSOCKETROUTEDEST                       
#define SOAD_EQ2_SOCKETROUTEIND                                       
#define SOAD_EQ2_IMMEDTPTXCONFOFSOCKETTCP                             
#define SOAD_EQ2_TCPINITIATEOFSOCKETTCP                               
#define SOAD_EQ2_TCPKEEPALIVEINTERVALOFSOCKETTCP                      
#define SOAD_EQ2_TCPKEEPALIVEOFSOCKETTCP                              
#define SOAD_EQ2_TCPKEEPALIVEPROBESMAXOFSOCKETTCP                     
#define SOAD_EQ2_TCPKEEPALIVETIMEOFSOCKETTCP                          
#define SOAD_EQ2_TCPNODELAYOFSOCKETTCP                                
#define SOAD_EQ2_TCPRXBUFMINOFSOCKETTCP                               
#define SOAD_EQ2_TCPTXBUFMINOFSOCKETTCP                               
#define SOAD_EQ2_ALIVETIMEOUTMAXCNTOFSOCKETUDP                        
#define SOAD_EQ2_IMMEDIFTXCONFLISTSIZEOFSOCKETUDP                     
#define SOAD_EQ2_IMMEDIFTXCONFOFSOCKETUDP                             
#define SOAD_EQ2_NPDUUDPTXBUFFERMINOFSOCKETUDP                        
#define SOAD_EQ2_NPDUUDPTXQUEUESIZEOFSOCKETUDP                        
#define SOAD_EQ2_RETRYQUEUELIMITOFSOCKETUDP                           
#define SOAD_EQ2_UDPLISTENONLYOFSOCKETUDP                             
#define SOAD_EQ2_UDPSTRICTHDRLENCHECKENABLEDOFSOCKETUDP               
#define SOAD_EQ2_UDPTRIGGERTIMEOUTOFSOCKETUDP                         
#define SOAD_EQ2_LOCALADDRBYTCPIPCTRLINDENDIDXOFTCPIPCTRL             
#define SOAD_EQ2_LOCALADDRBYTCPIPCTRLINDSTARTIDXOFTCPIPCTRL           
#define SOAD_EQ2_LOCALADDRBYTCPIPCTRLINDUSEDOFTCPIPCTRL               
#define SOAD_EQ2_RETRYENABLEDOFTCPIPCTRL                              
#define SOAD_EQ2_TCPKEEPALIVEGLOBALLYENABLED                          
#define SOAD_EQ2_TCPTLSSOCKETCREATEDNOTIFICATIONCBK                   
#define SOAD_EQ2_TCPTXQUEUEDATAENDIDXOFTCPTXQUEUE                     
#define SOAD_EQ2_TCPTXQUEUEDATASTARTIDXOFTCPTXQUEUE                   
#define SOAD_EQ2_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT         
#define SOAD_EQ2_TIMEOUTLISTDYNNPDUUDPTXUSEDOFTIMEOUTLISTIDENT        
#define SOAD_EQ2_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT          
#define SOAD_EQ2_TIMEOUTLISTDYNUDPALIVEUSEDOFTIMEOUTLISTIDENT         
#define SOAD_EQ2_RXBUFSIZEOFTLSCONFIG                                 
#define SOAD_EQ2_TCPTLSSOCKETCREATEDNOTIFICATIONCBKIDXOFTLSCONFIG     
#define SOAD_EQ2_TCPTLSSOCKETCREATEDNOTIFICATIONCBKUSEDOFTLSCONFIG    
#define SOAD_EQ2_TXBUFSIZEOFTLSCONFIG                                 
#define SOAD_EQ2_TPTXBUFFERENDIDXOFTPTXBUFFERCONFIG                   
#define SOAD_EQ2_TPTXBUFFERSTARTIDXOFTPTXBUFFERCONFIG                 
#define SOAD_EQ2_TPTXBUFFERUSEDOFTPTXBUFFERCONFIG                     
#define SOAD_EQ2_TRIGGERBUFENDIDXOFTRIGGERBUFCONFIG                   
#define SOAD_EQ2_TRIGGERBUFSTARTIDXOFTRIGGERBUFCONFIG                 
#define SOAD_EQ2_INVALIDHNDOFTXPDUIDMAP                               
#define SOAD_EQ2_PDUROUTEIDXOFTXPDUIDMAP                              
#define SOAD_EQ2_IFRXINDICATIONCBKOFUPPERLAYER                        
#define SOAD_EQ2_IFTRIGGERTRANSMITCBKOFUPPERLAYER                     
#define SOAD_EQ2_IFTXCONFIRMATIONCBKOFUPPERLAYER                      
#define SOAD_EQ2_TPCOPYRXDATACBKOFUPPERLAYER                          
#define SOAD_EQ2_TPCOPYRXDATACONSTCBKOFUPPERLAYER                     
#define SOAD_EQ2_TPCOPYTXDATACBKOFUPPERLAYER                          
#define SOAD_EQ2_TPCOPYTXDATACONSTCBKOFUPPERLAYER                     
#define SOAD_EQ2_TPRXINDICATIONCBKOFUPPERLAYER                        
#define SOAD_EQ2_TPSTARTOFRECEPTIONCBKOFUPPERLAYER                    
#define SOAD_EQ2_TPSTARTOFRECEPTIONCONSTCBKOFUPPERLAYER               
#define SOAD_EQ2_TPTXCONFIRMATIONCBKOFUPPERLAYER                      
#define SOAD_EQ2_BESTMATCHSOCONIDXLISTOFPCCONFIG                      
#define SOAD_EQ2_DHCPEVENTCBKOFPCCONFIG                               
#define SOAD_EQ2_EVENTQUEUEDYNOFPCCONFIG                              
#define SOAD_EQ2_EVENTQUEUEFLAGOFPCCONFIG                             
#define SOAD_EQ2_EVENTQUEUEIDENTOFPCCONFIG                            
#define SOAD_EQ2_EVENTQUEUEIFTXROUTEGRPOFPCCONFIG                     
#define SOAD_EQ2_EVENTQUEUEIFUDPPDUROUTEOFPCCONFIG                    
#define SOAD_EQ2_EVENTQUEUELOCALADDROFPCCONFIG                        
#define SOAD_EQ2_EVENTQUEUEOFPCCONFIG                                 
#define SOAD_EQ2_EVENTQUEUESOCKETIDXOFPCCONFIG                        
#define SOAD_EQ2_EVENTQUEUESTATESOCONOFPCCONFIG                       
#define SOAD_EQ2_EVENTQUEUETCPTXSOCONOFPCCONFIG                       
#define SOAD_EQ2_EVENTQUEUETPRXSOCONOFPCCONFIG                        
#define SOAD_EQ2_EVENTQUEUETPTXSOCONOFPCCONFIG                        
#define SOAD_EQ2_IFRXBUFFEROFPCCONFIG                                 
#define SOAD_EQ2_IPFRAGBUFCONFIGDYNOFPCCONFIG                         
#define SOAD_EQ2_IPFRAGBUFCONFIGOFPCCONFIG                            
#define SOAD_EQ2_IPFRAGBUFOFPCCONFIG                                  
#define SOAD_EQ2_IPFRAGMGTOFPCCONFIG                                  
#define SOAD_EQ2_LOCALADDRBYTCPIPCTRLINDOFPCCONFIG                    
#define SOAD_EQ2_LOCALADDRDYNOFPCCONFIG                               
#define SOAD_EQ2_LOCALADDRIDMAPOFPCCONFIG                             
#define SOAD_EQ2_LOCALADDROFPCCONFIG                                  
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG             
#define SOAD_EQ2_LOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG                
#define SOAD_EQ2_MAXIFROUTEGRPTRANSMITPDUSIZEOFPCCONFIG               
#define SOAD_EQ2_METADATARXBUFOFPCCONFIG                              
#define SOAD_EQ2_NPDUUDPTXBUFFEROFPCCONFIG                            
#define SOAD_EQ2_NPDUUDPTXDYNOFPCCONFIG                               
#define SOAD_EQ2_NPDUUDPTXOFPCCONFIG                                  
#define SOAD_EQ2_NPDUUDPTXQUEUEOFPCCONFIG                             
#define SOAD_EQ2_PDUROUTEDESTBYSOCONINDOFPCCONFIG                     
#define SOAD_EQ2_PDUROUTEDESTINDOFPCCONFIG                            
#define SOAD_EQ2_PDUROUTEDESTOFPCCONFIG                               
#define SOAD_EQ2_PDUROUTEDYNOFPCCONFIG                                
#define SOAD_EQ2_PDUROUTEOFPCCONFIG                                   
#define SOAD_EQ2_RCVREMADDROFPCCONFIG                                 
#define SOAD_EQ2_REMADDRIPV4OFPCCONFIG                                
#define SOAD_EQ2_REMADDRIPV6OFPCCONFIG                                
#define SOAD_EQ2_ROUTEGRPIDMAPOFPCCONFIG                              
#define SOAD_EQ2_ROUTEGRPOFPCCONFIG                                   
#define SOAD_EQ2_ROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG             
#define SOAD_EQ2_ROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG          
#define SOAD_EQ2_ROUTEGRPSOCONDYNOFPCCONFIG                           
#define SOAD_EQ2_ROUTEGRPSOCONOFPCCONFIG                              
#define SOAD_EQ2_RXBUFSTRUCTMGTOFPCCONFIG                             
#define SOAD_EQ2_RXBUFSTRUCTSEGOFPCCONFIG                             
#define SOAD_EQ2_RXBUFFERCONFIGDYNOFPCCONFIG                          
#define SOAD_EQ2_RXBUFFERCONFIGOFPCCONFIG                             
#define SOAD_EQ2_RXMGTOFPCCONFIG                                      
#define SOAD_EQ2_RXPDUIDIDMAPOFPCCONFIG                               
#define SOAD_EQ2_SHUTDOWNFINISHEDCBKOFPCCONFIG                        
#define SOAD_EQ2_SIZEOFBESTMATCHSOCONIDXLISTOFPCCONFIG                
#define SOAD_EQ2_SIZEOFDHCPEVENTCBKOFPCCONFIG                         
#define SOAD_EQ2_SIZEOFEVENTQUEUEFLAGOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFEVENTQUEUEIDENTOFPCCONFIG                      
#define SOAD_EQ2_SIZEOFEVENTQUEUEIFTXROUTEGRPOFPCCONFIG               
#define SOAD_EQ2_SIZEOFEVENTQUEUEIFUDPPDUROUTEOFPCCONFIG              
#define SOAD_EQ2_SIZEOFEVENTQUEUELOCALADDROFPCCONFIG                  
#define SOAD_EQ2_SIZEOFEVENTQUEUEOFPCCONFIG                           
#define SOAD_EQ2_SIZEOFEVENTQUEUESOCKETIDXOFPCCONFIG                  
#define SOAD_EQ2_SIZEOFEVENTQUEUESTATESOCONOFPCCONFIG                 
#define SOAD_EQ2_SIZEOFEVENTQUEUETCPTXSOCONOFPCCONFIG                 
#define SOAD_EQ2_SIZEOFEVENTQUEUETPRXSOCONOFPCCONFIG                  
#define SOAD_EQ2_SIZEOFEVENTQUEUETPTXSOCONOFPCCONFIG                  
#define SOAD_EQ2_SIZEOFIFRXBUFFEROFPCCONFIG                           
#define SOAD_EQ2_SIZEOFIPFRAGBUFCONFIGOFPCCONFIG                      
#define SOAD_EQ2_SIZEOFIPFRAGBUFOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFIPFRAGMGTOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFLOCALADDRBYTCPIPCTRLINDOFPCCONFIG              
#define SOAD_EQ2_SIZEOFLOCALADDRIDMAPOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFLOCALADDROFPCCONFIG                            
#define SOAD_EQ2_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKINDOFPCCONFIG       
#define SOAD_EQ2_SIZEOFLOCALIPADDRASSIGNMENTCHGCBKOFPCCONFIG          
#define SOAD_EQ2_SIZEOFMETADATARXBUFOFPCCONFIG                        
#define SOAD_EQ2_SIZEOFNPDUUDPTXBUFFEROFPCCONFIG                      
#define SOAD_EQ2_SIZEOFNPDUUDPTXOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFNPDUUDPTXQUEUEOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFPDUROUTEDESTBYSOCONINDOFPCCONFIG               
#define SOAD_EQ2_SIZEOFPDUROUTEDESTINDOFPCCONFIG                      
#define SOAD_EQ2_SIZEOFPDUROUTEDESTOFPCCONFIG                         
#define SOAD_EQ2_SIZEOFPDUROUTEOFPCCONFIG                             
#define SOAD_EQ2_SIZEOFRCVREMADDROFPCCONFIG                           
#define SOAD_EQ2_SIZEOFREMADDRIPV4OFPCCONFIG                          
#define SOAD_EQ2_SIZEOFREMADDRIPV6OFPCCONFIG                          
#define SOAD_EQ2_SIZEOFROUTEGRPIDMAPOFPCCONFIG                        
#define SOAD_EQ2_SIZEOFROUTEGRPOFPCCONFIG                             
#define SOAD_EQ2_SIZEOFROUTEGRPSOCONBYPDUROUTEDESTINDOFPCCONFIG       
#define SOAD_EQ2_SIZEOFROUTEGRPSOCONBYSOCKETROUTEDESTINDOFPCCONFIG    
#define SOAD_EQ2_SIZEOFROUTEGRPSOCONOFPCCONFIG                        
#define SOAD_EQ2_SIZEOFRXBUFSTRUCTMGTOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFRXBUFSTRUCTSEGOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFRXBUFFERCONFIGOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFRXMGTOFPCCONFIG                                
#define SOAD_EQ2_SIZEOFRXPDUIDIDMAPOFPCCONFIG                         
#define SOAD_EQ2_SIZEOFSHUTDOWNFINISHEDCBKOFPCCONFIG                  
#define SOAD_EQ2_SIZEOFSOCONGRPOFPCCONFIG                             
#define SOAD_EQ2_SIZEOFSOCONMAPOFPCCONFIG                             
#define SOAD_EQ2_SIZEOFSOCONMODECHGCBKINDOFPCCONFIG                   
#define SOAD_EQ2_SIZEOFSOCONMODECHGCBKOFPCCONFIG                      
#define SOAD_EQ2_SIZEOFSOCONOFPCCONFIG                                
#define SOAD_EQ2_SIZEOFSOCKETOFPCCONFIG                               
#define SOAD_EQ2_SIZEOFSOCKETREPORTERRORCBKOFPCCONFIG                 
#define SOAD_EQ2_SIZEOFSOCKETROUTEDESTOFPCCONFIG                      
#define SOAD_EQ2_SIZEOFSOCKETROUTEINDOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFSOCKETROUTEOFPCCONFIG                          
#define SOAD_EQ2_SIZEOFSOCKETTCPOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFSOCKETUDPOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFTCPIPCTRLOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFTCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG          
#define SOAD_EQ2_SIZEOFTCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG   
#define SOAD_EQ2_SIZEOFTCPTXQUEUEDATAOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFTCPTXQUEUEOFPCCONFIG                           
#define SOAD_EQ2_SIZEOFTIMEOUTLISTDYNOFPCCONFIG                       
#define SOAD_EQ2_SIZEOFTIMEOUTLISTIDENTOFPCCONFIG                     
#define SOAD_EQ2_SIZEOFTIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG              
#define SOAD_EQ2_SIZEOFTIMEOUTLISTNPDUUDPTXOFPCCONFIG                 
#define SOAD_EQ2_SIZEOFTIMEOUTLISTUDPALIVEMAPOFPCCONFIG               
#define SOAD_EQ2_SIZEOFTIMEOUTLISTUDPALIVEOFPCCONFIG                  
#define SOAD_EQ2_SIZEOFTLSCONFIGOFPCCONFIG                            
#define SOAD_EQ2_SIZEOFTPRXBUFFEROFPCCONFIG                           
#define SOAD_EQ2_SIZEOFTPTXBUFFERCONFIGOFPCCONFIG                     
#define SOAD_EQ2_SIZEOFTPTXBUFFEROFPCCONFIG                           
#define SOAD_EQ2_SIZEOFTRIGGERBUFCONFIGOFPCCONFIG                     
#define SOAD_EQ2_SIZEOFTRIGGERBUFOFPCCONFIG                           
#define SOAD_EQ2_SIZEOFTXMGTOFPCCONFIG                                
#define SOAD_EQ2_SIZEOFTXPDUIDMAPOFPCCONFIG                           
#define SOAD_EQ2_SIZEOFUPPERLAYEROFPCCONFIG                           
#define SOAD_EQ2_SOCONDYNOFPCCONFIG                                   
#define SOAD_EQ2_SOCONGRPOFPCCONFIG                                   
#define SOAD_EQ2_SOCONMAPOFPCCONFIG                                   
#define SOAD_EQ2_SOCONMODECHGCBKINDOFPCCONFIG                         
#define SOAD_EQ2_SOCONMODECHGCBKOFPCCONFIG                            
#define SOAD_EQ2_SOCONOFPCCONFIG                                      
#define SOAD_EQ2_SOCKETDYNOFPCCONFIG                                  
#define SOAD_EQ2_SOCKETOFPCCONFIG                                     
#define SOAD_EQ2_SOCKETREPORTERRORCBKOFPCCONFIG                       
#define SOAD_EQ2_SOCKETROUTEDESTOFPCCONFIG                            
#define SOAD_EQ2_SOCKETROUTEINDOFPCCONFIG                             
#define SOAD_EQ2_SOCKETROUTEOFPCCONFIG                                
#define SOAD_EQ2_SOCKETTCPOFPCCONFIG                                  
#define SOAD_EQ2_SOCKETUDPOFPCCONFIG                                  
#define SOAD_EQ2_TCPIPCTRLOFPCCONFIG                                  
#define SOAD_EQ2_TCPKEEPALIVEGLOBALLYENABLEDOFPCCONFIG                
#define SOAD_EQ2_TCPTLSSOCKETCREATEDNOTIFICATIONCBKOFPCCONFIG         
#define SOAD_EQ2_TCPTXQUEUEDATAOFPCCONFIG                             
#define SOAD_EQ2_TCPTXQUEUEMGTOFPCCONFIG                              
#define SOAD_EQ2_TCPTXQUEUEOFPCCONFIG                                 
#define SOAD_EQ2_TIMEOUTLISTDYNOFPCCONFIG                             
#define SOAD_EQ2_TIMEOUTLISTIDENTOFPCCONFIG                           
#define SOAD_EQ2_TIMEOUTLISTNPDUUDPTXMAPOFPCCONFIG                    
#define SOAD_EQ2_TIMEOUTLISTNPDUUDPTXOFPCCONFIG                       
#define SOAD_EQ2_TIMEOUTLISTUDPALIVEMAPOFPCCONFIG                     
#define SOAD_EQ2_TIMEOUTLISTUDPALIVEOFPCCONFIG                        
#define SOAD_EQ2_TLSCONFIGOFPCCONFIG                                  
#define SOAD_EQ2_TPRXBUFFEROFPCCONFIG                                 
#define SOAD_EQ2_TPTXBUFFERCONFIGDYNOFPCCONFIG                        
#define SOAD_EQ2_TPTXBUFFERCONFIGOFPCCONFIG                           
#define SOAD_EQ2_TPTXBUFFEROFPCCONFIG                                 
#define SOAD_EQ2_TRIGGERBUFCONFIGDYNOFPCCONFIG                        
#define SOAD_EQ2_TRIGGERBUFCONFIGOFPCCONFIG                           
#define SOAD_EQ2_TRIGGERBUFOFPCCONFIG                                 
#define SOAD_EQ2_TXMGTOFPCCONFIG                                      
#define SOAD_EQ2_TXPDUIDMAPOFPCCONFIG                                 
#define SOAD_EQ2_UPPERLAYEROFPCCONFIG                                 
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCSymbolicInitializationPointers  SoAd Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define SoAd_Config_Ptr                                               &(SoAd_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'SoAd' */
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCInitializationSymbols  SoAd Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define SoAd_Config                                                   SoAd_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'SoAd */
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCGeneral  SoAd General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define SOAD_CHECK_INIT_POINTER                                       STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define SOAD_FINAL_MAGIC_NUMBER                                       0x381Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of SoAd */
#define SOAD_INDIVIDUAL_POSTBUILD                                     STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'SoAd' is not configured to be postbuild capable. */
#define SOAD_INIT_DATA                                                SOAD_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define SOAD_INIT_DATA_HASH_CODE                                      -1479254578  /**< the precompile constant to validate the initialization structure at initialization time of SoAd with a hashcode. The seed value is '0x381Eu' */
#define SOAD_USE_ECUM_BSW_ERROR_HOOK                                  STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define SOAD_USE_INIT_POINTER                                         STD_ON  /**< STD_ON if the init pointer SoAd shall be used. */
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
  \defgroup  SoAdPCGetRootDataMacros  SoAd Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define SoAd_GetBestMatchSoConIdxListOfPCConfig()                     SoAd_ConfigDataPtr->BestMatchSoConIdxListOfPCConfig
#define SoAd_GetDhcpEventCbkOfPCConfig()                              SoAd_ConfigDataPtr->DhcpEventCbkOfPCConfig
#define SoAd_GetEventQueueDynOfPCConfig()                             SoAd_ConfigDataPtr->EventQueueDynOfPCConfig
#define SoAd_GetEventQueueFlagOfPCConfig()                            SoAd_ConfigDataPtr->EventQueueFlagOfPCConfig
#define SoAd_GetEventQueueIdentOfPCConfig()                           SoAd_ConfigDataPtr->EventQueueIdentOfPCConfig
#define SoAd_GetEventQueueIfTxRouteGrpOfPCConfig()                    SoAd_ConfigDataPtr->EventQueueIfTxRouteGrpOfPCConfig
#define SoAd_GetEventQueueIfUdpPduRouteOfPCConfig()                   SoAd_ConfigDataPtr->EventQueueIfUdpPduRouteOfPCConfig
#define SoAd_GetEventQueueLocalAddrOfPCConfig()                       SoAd_ConfigDataPtr->EventQueueLocalAddrOfPCConfig
#define SoAd_GetEventQueueOfPCConfig()                                SoAd_ConfigDataPtr->EventQueueOfPCConfig
#define SoAd_GetEventQueueSocketIdxOfPCConfig()                       SoAd_ConfigDataPtr->EventQueueSocketIdxOfPCConfig
#define SoAd_GetEventQueueStateSoConOfPCConfig()                      SoAd_ConfigDataPtr->EventQueueStateSoConOfPCConfig
#define SoAd_GetEventQueueTcpTxSoConOfPCConfig()                      SoAd_ConfigDataPtr->EventQueueTcpTxSoConOfPCConfig
#define SoAd_GetEventQueueTpRxSoConOfPCConfig()                       SoAd_ConfigDataPtr->EventQueueTpRxSoConOfPCConfig
#define SoAd_GetEventQueueTpTxSoConOfPCConfig()                       SoAd_ConfigDataPtr->EventQueueTpTxSoConOfPCConfig
#define SoAd_GetIfRxBufferOfPCConfig()                                SoAd_ConfigDataPtr->IfRxBufferOfPCConfig
#define SoAd_GetIpFragBufConfigDynOfPCConfig()                        SoAd_ConfigDataPtr->IpFragBufConfigDynOfPCConfig
#define SoAd_GetIpFragBufConfigOfPCConfig()                           SoAd_ConfigDataPtr->IpFragBufConfigOfPCConfig
#define SoAd_GetIpFragBufOfPCConfig()                                 SoAd_ConfigDataPtr->IpFragBufOfPCConfig
#define SoAd_GetIpFragMgtOfPCConfig()                                 SoAd_ConfigDataPtr->IpFragMgtOfPCConfig
#define SoAd_GetLocalAddrByTcpIpCtrlIndOfPCConfig()                   SoAd_ConfigDataPtr->LocalAddrByTcpIpCtrlIndOfPCConfig
#define SoAd_GetLocalAddrDynOfPCConfig()                              SoAd_ConfigDataPtr->LocalAddrDynOfPCConfig
#define SoAd_GetLocalAddrIdMapOfPCConfig()                            SoAd_ConfigDataPtr->LocalAddrIdMapOfPCConfig
#define SoAd_GetLocalAddrOfPCConfig()                                 SoAd_ConfigDataPtr->LocalAddrOfPCConfig
#define SoAd_GetLocalIpAddrAssignmentChgCbkIndOfPCConfig()            SoAd_ConfigDataPtr->LocalIpAddrAssignmentChgCbkIndOfPCConfig
#define SoAd_GetLocalIpAddrAssignmentChgCbkOfPCConfig()               SoAd_ConfigDataPtr->LocalIpAddrAssignmentChgCbkOfPCConfig
#define SoAd_GetMaxIfRouteGrpTransmitPduSizeOfPCConfig()              SoAd_ConfigDataPtr->MaxIfRouteGrpTransmitPduSizeOfPCConfig
#define SoAd_GetMetaDataRxBufOfPCConfig()                             SoAd_ConfigDataPtr->MetaDataRxBufOfPCConfig
#define SoAd_GetNPduUdpTxBufferOfPCConfig()                           SoAd_ConfigDataPtr->NPduUdpTxBufferOfPCConfig
#define SoAd_GetNPduUdpTxDynOfPCConfig()                              SoAd_ConfigDataPtr->NPduUdpTxDynOfPCConfig
#define SoAd_GetNPduUdpTxOfPCConfig()                                 SoAd_ConfigDataPtr->NPduUdpTxOfPCConfig
#define SoAd_GetNPduUdpTxQueueOfPCConfig()                            SoAd_ConfigDataPtr->NPduUdpTxQueueOfPCConfig
#define SoAd_GetPduRouteDestBySoConIndOfPCConfig()                    SoAd_ConfigDataPtr->PduRouteDestBySoConIndOfPCConfig
#define SoAd_GetPduRouteDestIndOfPCConfig()                           SoAd_ConfigDataPtr->PduRouteDestIndOfPCConfig
#define SoAd_GetPduRouteDestOfPCConfig()                              SoAd_ConfigDataPtr->PduRouteDestOfPCConfig
#define SoAd_GetPduRouteDynOfPCConfig()                               SoAd_ConfigDataPtr->PduRouteDynOfPCConfig
#define SoAd_GetPduRouteOfPCConfig()                                  SoAd_ConfigDataPtr->PduRouteOfPCConfig
#define SoAd_GetRcvRemAddrOfPCConfig()                                SoAd_ConfigDataPtr->RcvRemAddrOfPCConfig
#define SoAd_GetRemAddrIpV4OfPCConfig()                               SoAd_ConfigDataPtr->RemAddrIpV4OfPCConfig
#define SoAd_GetRemAddrIpV6OfPCConfig()                               SoAd_ConfigDataPtr->RemAddrIpV6OfPCConfig
#define SoAd_GetRouteGrpIdMapOfPCConfig()                             SoAd_ConfigDataPtr->RouteGrpIdMapOfPCConfig
#define SoAd_GetRouteGrpOfPCConfig()                                  SoAd_ConfigDataPtr->RouteGrpOfPCConfig
#define SoAd_GetRouteGrpSoConByPduRouteDestIndOfPCConfig()            SoAd_ConfigDataPtr->RouteGrpSoConByPduRouteDestIndOfPCConfig
#define SoAd_GetRouteGrpSoConBySocketRouteDestIndOfPCConfig()         SoAd_ConfigDataPtr->RouteGrpSoConBySocketRouteDestIndOfPCConfig
#define SoAd_GetRouteGrpSoConDynOfPCConfig()                          SoAd_ConfigDataPtr->RouteGrpSoConDynOfPCConfig
#define SoAd_GetRouteGrpSoConOfPCConfig()                             SoAd_ConfigDataPtr->RouteGrpSoConOfPCConfig
#define SoAd_GetRxBufStructMgtOfPCConfig()                            SoAd_ConfigDataPtr->RxBufStructMgtOfPCConfig
#define SoAd_GetRxBufStructSegOfPCConfig()                            SoAd_ConfigDataPtr->RxBufStructSegOfPCConfig
#define SoAd_GetRxBufferConfigDynOfPCConfig()                         SoAd_ConfigDataPtr->RxBufferConfigDynOfPCConfig
#define SoAd_GetRxBufferConfigOfPCConfig()                            SoAd_ConfigDataPtr->RxBufferConfigOfPCConfig
#define SoAd_GetRxMgtOfPCConfig()                                     SoAd_ConfigDataPtr->RxMgtOfPCConfig
#define SoAd_GetRxPduIdIdMapOfPCConfig()                              SoAd_ConfigDataPtr->RxPduIdIdMapOfPCConfig
#define SoAd_GetShutdownFinishedCbkOfPCConfig()                       SoAd_ConfigDataPtr->ShutdownFinishedCbkOfPCConfig
#define SoAd_GetSizeOfBestMatchSoConIdxListOfPCConfig()               SoAd_ConfigDataPtr->SizeOfBestMatchSoConIdxListOfPCConfig
#define SoAd_GetSizeOfDhcpEventCbkOfPCConfig()                        SoAd_ConfigDataPtr->SizeOfDhcpEventCbkOfPCConfig
#define SoAd_GetSizeOfEventQueueFlagOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfEventQueueFlagOfPCConfig
#define SoAd_GetSizeOfEventQueueIdentOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfEventQueueIdentOfPCConfig
#define SoAd_GetSizeOfEventQueueIfTxRouteGrpOfPCConfig()              SoAd_ConfigDataPtr->SizeOfEventQueueIfTxRouteGrpOfPCConfig
#define SoAd_GetSizeOfEventQueueIfUdpPduRouteOfPCConfig()             SoAd_ConfigDataPtr->SizeOfEventQueueIfUdpPduRouteOfPCConfig
#define SoAd_GetSizeOfEventQueueLocalAddrOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfEventQueueLocalAddrOfPCConfig
#define SoAd_GetSizeOfEventQueueOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfEventQueueOfPCConfig
#define SoAd_GetSizeOfEventQueueSocketIdxOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfEventQueueSocketIdxOfPCConfig
#define SoAd_GetSizeOfEventQueueStateSoConOfPCConfig()                SoAd_ConfigDataPtr->SizeOfEventQueueStateSoConOfPCConfig
#define SoAd_GetSizeOfEventQueueTcpTxSoConOfPCConfig()                SoAd_ConfigDataPtr->SizeOfEventQueueTcpTxSoConOfPCConfig
#define SoAd_GetSizeOfEventQueueTpRxSoConOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfEventQueueTpRxSoConOfPCConfig
#define SoAd_GetSizeOfEventQueueTpTxSoConOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfEventQueueTpTxSoConOfPCConfig
#define SoAd_GetSizeOfIfRxBufferOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfIfRxBufferOfPCConfig
#define SoAd_GetSizeOfIpFragBufConfigOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfIpFragBufConfigOfPCConfig
#define SoAd_GetSizeOfIpFragBufOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfIpFragBufOfPCConfig
#define SoAd_GetSizeOfIpFragMgtOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfIpFragMgtOfPCConfig
#define SoAd_GetSizeOfLocalAddrByTcpIpCtrlIndOfPCConfig()             SoAd_ConfigDataPtr->SizeOfLocalAddrByTcpIpCtrlIndOfPCConfig
#define SoAd_GetSizeOfLocalAddrIdMapOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfLocalAddrIdMapOfPCConfig
#define SoAd_GetSizeOfLocalAddrOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfLocalAddrOfPCConfig
#define SoAd_GetSizeOfLocalIpAddrAssignmentChgCbkIndOfPCConfig()      SoAd_ConfigDataPtr->SizeOfLocalIpAddrAssignmentChgCbkIndOfPCConfig
#define SoAd_GetSizeOfLocalIpAddrAssignmentChgCbkOfPCConfig()         SoAd_ConfigDataPtr->SizeOfLocalIpAddrAssignmentChgCbkOfPCConfig
#define SoAd_GetSizeOfMetaDataRxBufOfPCConfig()                       SoAd_ConfigDataPtr->SizeOfMetaDataRxBufOfPCConfig
#define SoAd_GetSizeOfNPduUdpTxBufferOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfNPduUdpTxBufferOfPCConfig
#define SoAd_GetSizeOfNPduUdpTxOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfNPduUdpTxOfPCConfig
#define SoAd_GetSizeOfNPduUdpTxQueueOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfNPduUdpTxQueueOfPCConfig
#define SoAd_GetSizeOfPduRouteDestBySoConIndOfPCConfig()              SoAd_ConfigDataPtr->SizeOfPduRouteDestBySoConIndOfPCConfig
#define SoAd_GetSizeOfPduRouteDestIndOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfPduRouteDestIndOfPCConfig
#define SoAd_GetSizeOfPduRouteDestOfPCConfig()                        SoAd_ConfigDataPtr->SizeOfPduRouteDestOfPCConfig
#define SoAd_GetSizeOfPduRouteOfPCConfig()                            SoAd_ConfigDataPtr->SizeOfPduRouteOfPCConfig
#define SoAd_GetSizeOfRcvRemAddrOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfRcvRemAddrOfPCConfig
#define SoAd_GetSizeOfRemAddrIpV4OfPCConfig()                         SoAd_ConfigDataPtr->SizeOfRemAddrIpV4OfPCConfig
#define SoAd_GetSizeOfRemAddrIpV6OfPCConfig()                         SoAd_ConfigDataPtr->SizeOfRemAddrIpV6OfPCConfig
#define SoAd_GetSizeOfRouteGrpIdMapOfPCConfig()                       SoAd_ConfigDataPtr->SizeOfRouteGrpIdMapOfPCConfig
#define SoAd_GetSizeOfRouteGrpOfPCConfig()                            SoAd_ConfigDataPtr->SizeOfRouteGrpOfPCConfig
#define SoAd_GetSizeOfRouteGrpSoConByPduRouteDestIndOfPCConfig()      SoAd_ConfigDataPtr->SizeOfRouteGrpSoConByPduRouteDestIndOfPCConfig
#define SoAd_GetSizeOfRouteGrpSoConBySocketRouteDestIndOfPCConfig()   SoAd_ConfigDataPtr->SizeOfRouteGrpSoConBySocketRouteDestIndOfPCConfig
#define SoAd_GetSizeOfRouteGrpSoConOfPCConfig()                       SoAd_ConfigDataPtr->SizeOfRouteGrpSoConOfPCConfig
#define SoAd_GetSizeOfRxBufStructMgtOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfRxBufStructMgtOfPCConfig
#define SoAd_GetSizeOfRxBufStructSegOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfRxBufStructSegOfPCConfig
#define SoAd_GetSizeOfRxBufferConfigOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfRxBufferConfigOfPCConfig
#define SoAd_GetSizeOfRxMgtOfPCConfig()                               SoAd_ConfigDataPtr->SizeOfRxMgtOfPCConfig
#define SoAd_GetSizeOfRxPduIdIdMapOfPCConfig()                        SoAd_ConfigDataPtr->SizeOfRxPduIdIdMapOfPCConfig
#define SoAd_GetSizeOfShutdownFinishedCbkOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfShutdownFinishedCbkOfPCConfig
#define SoAd_GetSizeOfSoConGrpOfPCConfig()                            SoAd_ConfigDataPtr->SizeOfSoConGrpOfPCConfig
#define SoAd_GetSizeOfSoConMapOfPCConfig()                            SoAd_ConfigDataPtr->SizeOfSoConMapOfPCConfig
#define SoAd_GetSizeOfSoConModeChgCbkIndOfPCConfig()                  SoAd_ConfigDataPtr->SizeOfSoConModeChgCbkIndOfPCConfig
#define SoAd_GetSizeOfSoConModeChgCbkOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfSoConModeChgCbkOfPCConfig
#define SoAd_GetSizeOfSoConOfPCConfig()                               SoAd_ConfigDataPtr->SizeOfSoConOfPCConfig
#define SoAd_GetSizeOfSocketOfPCConfig()                              SoAd_ConfigDataPtr->SizeOfSocketOfPCConfig
#define SoAd_GetSizeOfSocketReportErrorCbkOfPCConfig()                SoAd_ConfigDataPtr->SizeOfSocketReportErrorCbkOfPCConfig
#define SoAd_GetSizeOfSocketRouteDestOfPCConfig()                     SoAd_ConfigDataPtr->SizeOfSocketRouteDestOfPCConfig
#define SoAd_GetSizeOfSocketRouteIndOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfSocketRouteIndOfPCConfig
#define SoAd_GetSizeOfSocketRouteOfPCConfig()                         SoAd_ConfigDataPtr->SizeOfSocketRouteOfPCConfig
#define SoAd_GetSizeOfSocketTcpOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfSocketTcpOfPCConfig
#define SoAd_GetSizeOfSocketUdpOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfSocketUdpOfPCConfig
#define SoAd_GetSizeOfTcpIpCtrlOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfTcpIpCtrlOfPCConfig
#define SoAd_GetSizeOfTcpKeepAliveGloballyEnabledOfPCConfig()         SoAd_ConfigDataPtr->SizeOfTcpKeepAliveGloballyEnabledOfPCConfig
#define SoAd_GetSizeOfTcpTlsSocketCreatedNotificationCbkOfPCConfig()  SoAd_ConfigDataPtr->SizeOfTcpTlsSocketCreatedNotificationCbkOfPCConfig
#define SoAd_GetSizeOfTcpTxQueueDataOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfTcpTxQueueDataOfPCConfig
#define SoAd_GetSizeOfTcpTxQueueOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfTcpTxQueueOfPCConfig
#define SoAd_GetSizeOfTimeoutListDynOfPCConfig()                      SoAd_ConfigDataPtr->SizeOfTimeoutListDynOfPCConfig
#define SoAd_GetSizeOfTimeoutListIdentOfPCConfig()                    SoAd_ConfigDataPtr->SizeOfTimeoutListIdentOfPCConfig
#define SoAd_GetSizeOfTimeoutListNPduUdpTxMapOfPCConfig()             SoAd_ConfigDataPtr->SizeOfTimeoutListNPduUdpTxMapOfPCConfig
#define SoAd_GetSizeOfTimeoutListNPduUdpTxOfPCConfig()                SoAd_ConfigDataPtr->SizeOfTimeoutListNPduUdpTxOfPCConfig
#define SoAd_GetSizeOfTimeoutListUdpAliveMapOfPCConfig()              SoAd_ConfigDataPtr->SizeOfTimeoutListUdpAliveMapOfPCConfig
#define SoAd_GetSizeOfTimeoutListUdpAliveOfPCConfig()                 SoAd_ConfigDataPtr->SizeOfTimeoutListUdpAliveOfPCConfig
#define SoAd_GetSizeOfTlsConfigOfPCConfig()                           SoAd_ConfigDataPtr->SizeOfTlsConfigOfPCConfig
#define SoAd_GetSizeOfTpRxBufferOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfTpRxBufferOfPCConfig
#define SoAd_GetSizeOfTpTxBufferConfigOfPCConfig()                    SoAd_ConfigDataPtr->SizeOfTpTxBufferConfigOfPCConfig
#define SoAd_GetSizeOfTpTxBufferOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfTpTxBufferOfPCConfig
#define SoAd_GetSizeOfTriggerBufConfigOfPCConfig()                    SoAd_ConfigDataPtr->SizeOfTriggerBufConfigOfPCConfig
#define SoAd_GetSizeOfTriggerBufOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfTriggerBufOfPCConfig
#define SoAd_GetSizeOfTxMgtOfPCConfig()                               SoAd_ConfigDataPtr->SizeOfTxMgtOfPCConfig
#define SoAd_GetSizeOfTxPduIdMapOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfTxPduIdMapOfPCConfig
#define SoAd_GetSizeOfUpperLayerOfPCConfig()                          SoAd_ConfigDataPtr->SizeOfUpperLayerOfPCConfig
#define SoAd_GetSoConDynOfPCConfig()                                  SoAd_ConfigDataPtr->SoConDynOfPCConfig
#define SoAd_GetSoConGrpOfPCConfig()                                  SoAd_ConfigDataPtr->SoConGrpOfPCConfig
#define SoAd_GetSoConMapOfPCConfig()                                  SoAd_ConfigDataPtr->SoConMapOfPCConfig
#define SoAd_GetSoConModeChgCbkIndOfPCConfig()                        SoAd_ConfigDataPtr->SoConModeChgCbkIndOfPCConfig
#define SoAd_GetSoConModeChgCbkOfPCConfig()                           SoAd_ConfigDataPtr->SoConModeChgCbkOfPCConfig
#define SoAd_GetSoConOfPCConfig()                                     SoAd_ConfigDataPtr->SoConOfPCConfig
#define SoAd_GetSocketDynOfPCConfig()                                 SoAd_ConfigDataPtr->SocketDynOfPCConfig
#define SoAd_GetSocketOfPCConfig()                                    SoAd_ConfigDataPtr->SocketOfPCConfig
#define SoAd_GetSocketReportErrorCbkOfPCConfig()                      SoAd_ConfigDataPtr->SocketReportErrorCbkOfPCConfig
#define SoAd_GetSocketRouteDestOfPCConfig()                           SoAd_ConfigDataPtr->SocketRouteDestOfPCConfig
#define SoAd_GetSocketRouteIndOfPCConfig()                            SoAd_ConfigDataPtr->SocketRouteIndOfPCConfig
#define SoAd_GetSocketRouteOfPCConfig()                               SoAd_ConfigDataPtr->SocketRouteOfPCConfig
#define SoAd_GetSocketTcpOfPCConfig()                                 SoAd_ConfigDataPtr->SocketTcpOfPCConfig
#define SoAd_GetSocketUdpOfPCConfig()                                 SoAd_ConfigDataPtr->SocketUdpOfPCConfig
#define SoAd_GetTcpIpCtrlOfPCConfig()                                 SoAd_ConfigDataPtr->TcpIpCtrlOfPCConfig
#define SoAd_GetTcpKeepAliveGloballyEnabledOfPCConfig()               SoAd_ConfigDataPtr->TcpKeepAliveGloballyEnabledOfPCConfig
#define SoAd_GetTcpTlsSocketCreatedNotificationCbkOfPCConfig()        SoAd_ConfigDataPtr->TcpTlsSocketCreatedNotificationCbkOfPCConfig
#define SoAd_GetTcpTxQueueDataOfPCConfig()                            SoAd_ConfigDataPtr->TcpTxQueueDataOfPCConfig
#define SoAd_GetTcpTxQueueMgtOfPCConfig()                             SoAd_ConfigDataPtr->TcpTxQueueMgtOfPCConfig
#define SoAd_GetTcpTxQueueOfPCConfig()                                SoAd_ConfigDataPtr->TcpTxQueueOfPCConfig
#define SoAd_GetTimeoutListDynOfPCConfig()                            SoAd_ConfigDataPtr->TimeoutListDynOfPCConfig
#define SoAd_GetTimeoutListIdentOfPCConfig()                          SoAd_ConfigDataPtr->TimeoutListIdentOfPCConfig
#define SoAd_GetTimeoutListNPduUdpTxMapOfPCConfig()                   SoAd_ConfigDataPtr->TimeoutListNPduUdpTxMapOfPCConfig
#define SoAd_GetTimeoutListNPduUdpTxOfPCConfig()                      SoAd_ConfigDataPtr->TimeoutListNPduUdpTxOfPCConfig
#define SoAd_GetTimeoutListUdpAliveMapOfPCConfig()                    SoAd_ConfigDataPtr->TimeoutListUdpAliveMapOfPCConfig
#define SoAd_GetTimeoutListUdpAliveOfPCConfig()                       SoAd_ConfigDataPtr->TimeoutListUdpAliveOfPCConfig
#define SoAd_GetTlsConfigOfPCConfig()                                 SoAd_ConfigDataPtr->TlsConfigOfPCConfig
#define SoAd_GetTpRxBufferOfPCConfig()                                SoAd_ConfigDataPtr->TpRxBufferOfPCConfig
#define SoAd_GetTpTxBufferConfigDynOfPCConfig()                       SoAd_ConfigDataPtr->TpTxBufferConfigDynOfPCConfig
#define SoAd_GetTpTxBufferConfigOfPCConfig()                          SoAd_ConfigDataPtr->TpTxBufferConfigOfPCConfig
#define SoAd_GetTpTxBufferOfPCConfig()                                SoAd_ConfigDataPtr->TpTxBufferOfPCConfig
#define SoAd_GetTriggerBufConfigDynOfPCConfig()                       SoAd_ConfigDataPtr->TriggerBufConfigDynOfPCConfig
#define SoAd_GetTriggerBufConfigOfPCConfig()                          SoAd_ConfigDataPtr->TriggerBufConfigOfPCConfig
#define SoAd_GetTriggerBufOfPCConfig()                                SoAd_ConfigDataPtr->TriggerBufOfPCConfig
#define SoAd_GetTxMgtOfPCConfig()                                     SoAd_ConfigDataPtr->TxMgtOfPCConfig
#define SoAd_GetTxPduIdMapOfPCConfig()                                SoAd_ConfigDataPtr->TxPduIdMapOfPCConfig
#define SoAd_GetUpperLayerOfPCConfig()                                SoAd_ConfigDataPtr->UpperLayerOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCGetDuplicatedRootDataMacros  SoAd Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define SoAd_GetSizeOfEventQueueDynOfPCConfig()                       SoAd_GetSizeOfEventQueueOfPCConfig()  /**< the number of accomplishable value elements in SoAd_EventQueueDyn */
#define SoAd_GetSizeOfIpFragBufConfigDynOfPCConfig()                  SoAd_GetSizeOfIpFragBufConfigOfPCConfig()  /**< the number of accomplishable value elements in SoAd_IpFragBufConfigDyn */
#define SoAd_GetSizeOfLocalAddrDynOfPCConfig()                        SoAd_GetSizeOfLocalAddrOfPCConfig()  /**< the number of accomplishable value elements in SoAd_LocalAddrDyn */
#define SoAd_GetSizeOfNPduUdpTxDynOfPCConfig()                        SoAd_GetSizeOfNPduUdpTxOfPCConfig()  /**< the number of accomplishable value elements in SoAd_NPduUdpTxDyn */
#define SoAd_GetSizeOfPduRouteDynOfPCConfig()                         SoAd_GetSizeOfPduRouteOfPCConfig()  /**< the number of accomplishable value elements in SoAd_PduRouteDyn */
#define SoAd_GetSizeOfRouteGrpSoConDynOfPCConfig()                    SoAd_GetSizeOfRouteGrpSoConOfPCConfig()  /**< the number of accomplishable value elements in SoAd_RouteGrpSoConDyn */
#define SoAd_GetSizeOfRxBufferConfigDynOfPCConfig()                   SoAd_GetSizeOfRxBufferConfigOfPCConfig()  /**< the number of accomplishable value elements in SoAd_RxBufferConfigDyn */
#define SoAd_GetSizeOfSoConDynOfPCConfig()                            SoAd_GetSizeOfSoConOfPCConfig()  /**< the number of accomplishable value elements in SoAd_SoConDyn */
#define SoAd_GetSizeOfSocketDynOfPCConfig()                           SoAd_GetSizeOfSocketOfPCConfig()  /**< the number of accomplishable value elements in SoAd_SocketDyn */
#define SoAd_GetSizeOfTcpTxQueueMgtOfPCConfig()                       SoAd_GetSizeOfTcpTxQueueOfPCConfig()  /**< the number of accomplishable value elements in SoAd_TcpTxQueueMgt */
#define SoAd_GetSizeOfTpTxBufferConfigDynOfPCConfig()                 SoAd_GetSizeOfTpTxBufferConfigOfPCConfig()  /**< the number of accomplishable value elements in SoAd_TpTxBufferConfigDyn */
#define SoAd_GetSizeOfTriggerBufConfigDynOfPCConfig()                 SoAd_GetSizeOfTriggerBufConfigOfPCConfig()  /**< the number of accomplishable value elements in SoAd_TriggerBufConfigDyn */
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCGetDataMacros  SoAd Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define SoAd_GetSoConIdxOfBestMatchSoConIdxList(Index)                (SoAd_GetBestMatchSoConIdxListOfPCConfig()[(Index)].SoConIdxOfBestMatchSoConIdxList)
#define SoAd_GetDhcpEventCbk(Index)                                   (SoAd_GetDhcpEventCbkOfPCConfig()[(Index)])
#define SoAd_GetBitPatternOfEventQueue(Index)                         (SoAd_GetEventQueueOfPCConfig()[(Index)].BitPatternOfEventQueue)
#define SoAd_GetLimitOfEventQueue(Index)                              (SoAd_GetEventQueueOfPCConfig()[(Index)].LimitOfEventQueue)
#define SoAd_GetIdxOfEventQueueDyn(Index)                             (SoAd_GetEventQueueDynOfPCConfig()[(Index)].IdxOfEventQueueDyn)
#define SoAd_GetLvlOfEventQueueDyn(Index)                             (SoAd_GetEventQueueDynOfPCConfig()[(Index)].LvlOfEventQueueDyn)
#define SoAd_GetEventQueueFlag(Index)                                 (SoAd_GetEventQueueFlagOfPCConfig()[(Index)])
#define SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(Index)     (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueIfTxRouteGrpIdxOfEventQueueIdent)
#define SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(Index)    (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueIfUdpPduRouteIdxOfEventQueueIdent)
#define SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(Index)        (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueLocalAddrIdxOfEventQueueIdent)
#define SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(Index)          (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueSockIdxIdxOfEventQueueIdent)
#define SoAd_GetEventQueueStateSoConIdxOfEventQueueIdent(Index)       (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueStateSoConIdxOfEventQueueIdent)
#define SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(Index)       (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueTcpTxSoConIdxOfEventQueueIdent)
#define SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(Index)        (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueTpRxSoConIdxOfEventQueueIdent)
#define SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(Index)        (SoAd_GetEventQueueIdentOfPCConfig()[(Index)].EventQueueTpTxSoConIdxOfEventQueueIdent)
#define SoAd_GetRouteGrpIdxOfEventQueueIfTxRouteGrp(Index)            (SoAd_GetEventQueueIfTxRouteGrpOfPCConfig()[(Index)].RouteGrpIdxOfEventQueueIfTxRouteGrp)
#define SoAd_GetPduRouteIdxOfEventQueueIfUdpPduRoute(Index)           (SoAd_GetEventQueueIfUdpPduRouteOfPCConfig()[(Index)].PduRouteIdxOfEventQueueIfUdpPduRoute)
#define SoAd_GetLocalAddrIdxOfEventQueueLocalAddr(Index)              (SoAd_GetEventQueueLocalAddrOfPCConfig()[(Index)].LocalAddrIdxOfEventQueueLocalAddr)
#define SoAd_GetSocketIdxOfEventQueueSocketIdx(Index)                 (SoAd_GetEventQueueSocketIdxOfPCConfig()[(Index)].SocketIdxOfEventQueueSocketIdx)
#define SoAd_GetSoConIdxOfEventQueueStateSoCon(Index)                 (SoAd_GetEventQueueStateSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueStateSoCon)
#define SoAd_GetSoConIdxOfEventQueueTcpTxSoCon(Index)                 (SoAd_GetEventQueueTcpTxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTcpTxSoCon)
#define SoAd_GetSoConIdxOfEventQueueTpRxSoCon(Index)                  (SoAd_GetEventQueueTpRxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTpRxSoCon)
#define SoAd_GetSoConIdxOfEventQueueTpTxSoCon(Index)                  (SoAd_GetEventQueueTpTxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTpTxSoCon)
#define SoAd_GetIfRxBuffer(Index)                                     (SoAd_GetIfRxBufferOfPCConfig()[(Index)])
#define SoAd_GetIpFragBuf(Index)                                      (SoAd_GetIpFragBufOfPCConfig()[(Index)])
#define SoAd_GetIpFragBufEndIdxOfIpFragBufConfig(Index)               (SoAd_GetIpFragBufConfigOfPCConfig()[(Index)].IpFragBufEndIdxOfIpFragBufConfig)
#define SoAd_GetIpFragBufStartIdxOfIpFragBufConfig(Index)             (SoAd_GetIpFragBufConfigOfPCConfig()[(Index)].IpFragBufStartIdxOfIpFragBufConfig)
#define SoAd_GetLengthOfIpFragBufConfigDyn(Index)                     (SoAd_GetIpFragBufConfigDynOfPCConfig()[(Index)].LengthOfIpFragBufConfigDyn)
#define SoAd_GetIpFragBufConfigIdxOfIpFragMgt(Index)                  (SoAd_GetIpFragMgtOfPCConfig()[(Index)].IpFragBufConfigIdxOfIpFragMgt)
#define SoAd_GetAddrIdOfLocalAddr(Index)                              (SoAd_GetLocalAddrOfPCConfig()[(Index)].AddrIdOfLocalAddr)
#define SoAd_GetAddressTypeOfLocalAddr(Index)                         (SoAd_GetLocalAddrOfPCConfig()[(Index)].AddressTypeOfLocalAddr)
#define SoAd_GetAssignTriggerOfLocalAddr(Index)                       (SoAd_GetLocalAddrOfPCConfig()[(Index)].AssignTriggerOfLocalAddr)
#define SoAd_GetAssignTypeOfLocalAddr(Index)                          (SoAd_GetLocalAddrOfPCConfig()[(Index)].AssignTypeOfLocalAddr)
#define SoAd_GetDomainOfLocalAddr(Index)                              (SoAd_GetLocalAddrOfPCConfig()[(Index)].DomainOfLocalAddr)
#define SoAd_GetTcpIpCtrlIdxOfLocalAddr(Index)                        (SoAd_GetLocalAddrOfPCConfig()[(Index)].TcpIpCtrlIdxOfLocalAddr)
#define SoAd_GetLocalAddrByTcpIpCtrlInd(Index)                        (SoAd_GetLocalAddrByTcpIpCtrlIndOfPCConfig()[(Index)])
#define SoAd_GetIpAddrStateOfLocalAddrDyn(Index)                      (SoAd_GetLocalAddrDynOfPCConfig()[(Index)].IpAddrStateOfLocalAddrDyn)
#define SoAd_IsInvalidHndOfLocalAddrIdMap(Index)                      ((SoAd_GetLocalAddrIdMapOfPCConfig()[(Index)].InvalidHndOfLocalAddrIdMap) != FALSE)
#define SoAd_GetLocalAddrIdxOfLocalAddrIdMap(Index)                   (SoAd_GetLocalAddrIdMapOfPCConfig()[(Index)].LocalAddrIdxOfLocalAddrIdMap)
#define SoAd_GetLocalIpAddrAssignmentChgCbk(Index)                    (SoAd_GetLocalIpAddrAssignmentChgCbkOfPCConfig()[(Index)])
#define SoAd_GetLocalIpAddrAssignmentChgCbkInd(Index)                 (SoAd_GetLocalIpAddrAssignmentChgCbkIndOfPCConfig()[(Index)])
#define SoAd_GetMetaDataRxBuf(Index)                                  (SoAd_GetMetaDataRxBufOfPCConfig()[(Index)])
#define SoAd_GetNPduUdpTxBufferEndIdxOfNPduUdpTx(Index)               (SoAd_GetNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxBufferEndIdxOfNPduUdpTx)
#define SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(Index)             (SoAd_GetNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxBufferStartIdxOfNPduUdpTx)
#define SoAd_GetNPduUdpTxQueueEndIdxOfNPduUdpTx(Index)                (SoAd_GetNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxQueueEndIdxOfNPduUdpTx)
#define SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(Index)              (SoAd_GetNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxQueueStartIdxOfNPduUdpTx)
#define SoAd_GetSoConIdxOfNPduUdpTx(Index)                            (SoAd_GetNPduUdpTxOfPCConfig()[(Index)].SoConIdxOfNPduUdpTx)
#define SoAd_GetNPduUdpTxBuffer(Index)                                (SoAd_GetNPduUdpTxBufferOfPCConfig()[(Index)])
#define SoAd_GetBufLenOfNPduUdpTxDyn(Index)                           (SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].BufLenOfNPduUdpTxDyn)
#define SoAd_GetLvlOfNPduUdpTxDyn(Index)                              (SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].LvlOfNPduUdpTxDyn)
#define SoAd_GetRetryCntOfNPduUdpTxDyn(Index)                         (SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].RetryCntOfNPduUdpTxDyn)
#define SoAd_GetTotalLenOfNPduUdpTxDyn(Index)                         (SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].TotalLenOfNPduUdpTxDyn)
#define SoAd_IsTransmissionActiveOfNPduUdpTxDyn(Index)                ((SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].TransmissionActiveOfNPduUdpTxDyn) != FALSE)
#define SoAd_IsCopiedOfNPduUdpTxQueue(Index)                          ((SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].CopiedOfNPduUdpTxQueue) != FALSE)
#define SoAd_GetLenOfNPduUdpTxQueue(Index)                            (SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].LenOfNPduUdpTxQueue)
#define SoAd_GetNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index)             (SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].NPduUdpTxBufferIdxOfNPduUdpTxQueue)
#define SoAd_GetPduRouteDestIdxOfNPduUdpTxQueue(Index)                (SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].PduRouteDestIdxOfNPduUdpTxQueue)
#define SoAd_IsAllPduRouteDestWithPduHdrOfPduRoute(Index)             ((SoAd_GetPduRouteOfPCConfig()[(Index)].AllPduRouteDestWithPduHdrOfPduRoute) != FALSE)
#define SoAd_GetIfTriggerTransmitModeOfPduRoute(Index)                (SoAd_GetPduRouteOfPCConfig()[(Index)].IfTriggerTransmitModeOfPduRoute)
#define SoAd_IsMetaDataTxEnabledOfPduRoute(Index)                     ((SoAd_GetPduRouteOfPCConfig()[(Index)].MetaDataTxEnabledOfPduRoute) != FALSE)
#define SoAd_GetPduRouteDestEndIdxOfPduRoute(Index)                   (SoAd_GetPduRouteOfPCConfig()[(Index)].PduRouteDestEndIdxOfPduRoute)
#define SoAd_GetPduRouteDestStartIdxOfPduRoute(Index)                 (SoAd_GetPduRouteOfPCConfig()[(Index)].PduRouteDestStartIdxOfPduRoute)
#define SoAd_IsTxConfEnabledOfPduRoute(Index)                         ((SoAd_GetPduRouteOfPCConfig()[(Index)].TxConfEnabledOfPduRoute) != FALSE)
#define SoAd_GetTxConfPduIdOfPduRoute(Index)                          (SoAd_GetPduRouteOfPCConfig()[(Index)].TxConfPduIdOfPduRoute)
#define SoAd_IsTxOptimizedOfPduRoute(Index)                           ((SoAd_GetPduRouteOfPCConfig()[(Index)].TxOptimizedOfPduRoute) != FALSE)
#define SoAd_GetUpperLayerApiOfPduRoute(Index)                        (SoAd_GetPduRouteOfPCConfig()[(Index)].UpperLayerApiOfPduRoute)
#define SoAd_GetUpperLayerIdxOfPduRoute(Index)                        (SoAd_GetPduRouteOfPCConfig()[(Index)].UpperLayerIdxOfPduRoute)
#define SoAd_GetPduRouteIdxOfPduRouteDest(Index)                      (SoAd_GetPduRouteDestOfPCConfig()[(Index)].PduRouteIdxOfPduRouteDest)
#define SoAd_GetRouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest(Index) (SoAd_GetPduRouteDestOfPCConfig()[(Index)].RouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest)
#define SoAd_GetRouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest(Index) (SoAd_GetPduRouteDestOfPCConfig()[(Index)].RouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest)
#define SoAd_GetSoConIdxOfPduRouteDest(Index)                         (SoAd_GetPduRouteDestOfPCConfig()[(Index)].SoConIdxOfPduRouteDest)
#define SoAd_GetTxPduHdrIdOfPduRouteDest(Index)                       (SoAd_GetPduRouteDestOfPCConfig()[(Index)].TxPduHdrIdOfPduRouteDest)
#define SoAd_GetTxUdpTriggerModeOfPduRouteDest(Index)                 (SoAd_GetPduRouteDestOfPCConfig()[(Index)].TxUdpTriggerModeOfPduRouteDest)
#define SoAd_GetUdpTriggerTimeoutOfPduRouteDest(Index)                (SoAd_GetPduRouteDestOfPCConfig()[(Index)].UdpTriggerTimeoutOfPduRouteDest)
#define SoAd_GetPduRouteDestBySoConInd(Index)                         (SoAd_GetPduRouteDestBySoConIndOfPCConfig()[(Index)])
#define SoAd_GetPduRouteDestInd(Index)                                (SoAd_GetPduRouteDestIndOfPCConfig()[(Index)])
#define SoAd_IsPendingTxConfMainOfPduRouteDyn(Index)                  ((SoAd_GetPduRouteDynOfPCConfig()[(Index)].PendingTxConfMainOfPduRouteDyn) != FALSE)
#define SoAd_GetPendingTxConfNumOfPduRouteDyn(Index)                  (SoAd_GetPduRouteDynOfPCConfig()[(Index)].PendingTxConfNumOfPduRouteDyn)
#define SoAd_GetRcvRemAddr(Index)                                     (SoAd_GetRcvRemAddrOfPCConfig()[(Index)])
#define SoAd_GetAddrOfRemAddrIpV4(Index)                              (SoAd_GetRemAddrIpV4OfPCConfig()[(Index)].AddrOfRemAddrIpV4)
#define SoAd_GetPortOfRemAddrIpV4(Index)                              (SoAd_GetRemAddrIpV4OfPCConfig()[(Index)].PortOfRemAddrIpV4)
#define SoAd_GetAddrOfRemAddrIpV6(Index)                              (SoAd_GetRemAddrIpV6OfPCConfig()[(Index)].AddrOfRemAddrIpV6)
#define SoAd_GetPortOfRemAddrIpV6(Index)                              (SoAd_GetRemAddrIpV6OfPCConfig()[(Index)].PortOfRemAddrIpV6)
#define SoAd_IsEnabledAtInitOfRouteGrp(Index)                         ((SoAd_GetRouteGrpOfPCConfig()[(Index)].EnabledAtInitOfRouteGrp) != FALSE)
#define SoAd_IsMultiInstanceOnGrpOfRouteGrp(Index)                    ((SoAd_GetRouteGrpOfPCConfig()[(Index)].MultiInstanceOnGrpOfRouteGrp) != FALSE)
#define SoAd_GetPduRouteDestIndEndIdxOfRouteGrp(Index)                (SoAd_GetRouteGrpOfPCConfig()[(Index)].PduRouteDestIndEndIdxOfRouteGrp)
#define SoAd_GetPduRouteDestIndStartIdxOfRouteGrp(Index)              (SoAd_GetRouteGrpOfPCConfig()[(Index)].PduRouteDestIndStartIdxOfRouteGrp)
#define SoAd_GetRouteGrpSoConEndIdxOfRouteGrp(Index)                  (SoAd_GetRouteGrpOfPCConfig()[(Index)].RouteGrpSoConEndIdxOfRouteGrp)
#define SoAd_GetRouteGrpSoConStartIdxOfRouteGrp(Index)                (SoAd_GetRouteGrpOfPCConfig()[(Index)].RouteGrpSoConStartIdxOfRouteGrp)
#define SoAd_GetSocketRouteIndEndIdxOfRouteGrp(Index)                 (SoAd_GetRouteGrpOfPCConfig()[(Index)].SocketRouteIndEndIdxOfRouteGrp)
#define SoAd_GetSocketRouteIndStartIdxOfRouteGrp(Index)               (SoAd_GetRouteGrpOfPCConfig()[(Index)].SocketRouteIndStartIdxOfRouteGrp)
#define SoAd_IsTxTriggerableOfRouteGrp(Index)                         ((SoAd_GetRouteGrpOfPCConfig()[(Index)].TxTriggerableOfRouteGrp) != FALSE)
#define SoAd_IsInvalidHndOfRouteGrpIdMap(Index)                       ((SoAd_GetRouteGrpIdMapOfPCConfig()[(Index)].InvalidHndOfRouteGrpIdMap) != FALSE)
#define SoAd_GetRouteGrpIdxOfRouteGrpIdMap(Index)                     (SoAd_GetRouteGrpIdMapOfPCConfig()[(Index)].RouteGrpIdxOfRouteGrpIdMap)
#define SoAd_GetRouteGrpIdxOfRouteGrpSoCon(Index)                     (SoAd_GetRouteGrpSoConOfPCConfig()[(Index)].RouteGrpIdxOfRouteGrpSoCon)
#define SoAd_GetSoConIdxOfRouteGrpSoCon(Index)                        (SoAd_GetRouteGrpSoConOfPCConfig()[(Index)].SoConIdxOfRouteGrpSoCon)
#define SoAd_GetRouteGrpSoConByPduRouteDestInd(Index)                 (SoAd_GetRouteGrpSoConByPduRouteDestIndOfPCConfig()[(Index)])
#define SoAd_GetRouteGrpSoConBySocketRouteDestInd(Index)              (SoAd_GetRouteGrpSoConBySocketRouteDestIndOfPCConfig()[(Index)])
#define SoAd_IsEnabledOfRouteGrpSoConDyn(Index)                       ((SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].EnabledOfRouteGrpSoConDyn) != FALSE)
#define SoAd_IsSentOfRouteGrpSoConDyn(Index)                          ((SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].SentOfRouteGrpSoConDyn) != FALSE)
#define SoAd_IsTriggerOfRouteGrpSoConDyn(Index)                       ((SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].TriggerOfRouteGrpSoConDyn) != FALSE)
#define SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(Index)              (SoAd_GetRxBufStructMgtOfPCConfig()[(Index)].RxBufStructSegIdxOfRxBufStructMgt)
#define SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(Index)              (SoAd_GetRxBufStructMgtOfPCConfig()[(Index)].RxBufStructSegLvlOfRxBufStructMgt)
#define SoAd_GetDataPtrOfRxBufStructSeg(Index)                        (SoAd_GetRxBufStructSegOfPCConfig()[(Index)].DataPtrOfRxBufStructSeg)
#define SoAd_GetLenOfRxBufStructSeg(Index)                            (SoAd_GetRxBufStructSegOfPCConfig()[(Index)].LenOfRxBufStructSeg)
#define SoAd_GetIfRxBufferEndIdxOfRxBufferConfig(Index)               (SoAd_GetRxBufferConfigOfPCConfig()[(Index)].IfRxBufferEndIdxOfRxBufferConfig)
#define SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(Index)             (SoAd_GetRxBufferConfigOfPCConfig()[(Index)].IfRxBufferStartIdxOfRxBufferConfig)
#define SoAd_GetTpRxBufferEndIdxOfRxBufferConfig(Index)               (SoAd_GetRxBufferConfigOfPCConfig()[(Index)].TpRxBufferEndIdxOfRxBufferConfig)
#define SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(Index)             (SoAd_GetRxBufferConfigOfPCConfig()[(Index)].TpRxBufferStartIdxOfRxBufferConfig)
#define SoAd_GetIfRxBufferIdxOfRxBufferConfigDyn(Index)               (SoAd_GetRxBufferConfigDynOfPCConfig()[(Index)].IfRxBufferIdxOfRxBufferConfigDyn)
#define SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(Index)               (SoAd_GetRxBufferConfigDynOfPCConfig()[(Index)].TpRxBufferIdxOfRxBufferConfigDyn)
#define SoAd_IsCancelRequestedOfRxMgt(Index)                          ((SoAd_GetRxMgtOfPCConfig()[(Index)].CancelRequestedOfRxMgt) != FALSE)
#define SoAd_GetRxBytesPendingOfRxMgt(Index)                          (SoAd_GetRxMgtOfPCConfig()[(Index)].RxBytesPendingOfRxMgt)
#define SoAd_GetSocketRouteDestIdxOfRxMgt(Index)                      (SoAd_GetRxMgtOfPCConfig()[(Index)].SocketRouteDestIdxOfRxMgt)
#define SoAd_IsInvalidHndOfRxPduIdIdMap(Index)                        ((SoAd_GetRxPduIdIdMapOfPCConfig()[(Index)].InvalidHndOfRxPduIdIdMap) != FALSE)
#define SoAd_GetSocketRouteDestIdxOfRxPduIdIdMap(Index)               (SoAd_GetRxPduIdIdMapOfPCConfig()[(Index)].SocketRouteDestIdxOfRxPduIdIdMap)
#define SoAd_GetShutdownFinishedCbk(Index)                            (SoAd_GetShutdownFinishedCbkOfPCConfig()[(Index)])
#define SoAd_GetIpFragMgtIdxOfSoCon(Index)                            (SoAd_GetSoConOfPCConfig()[(Index)].IpFragMgtIdxOfSoCon)
#define SoAd_GetLocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon(Index)    (SoAd_GetSoConOfPCConfig()[(Index)].LocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon)
#define SoAd_GetLocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon(Index)  (SoAd_GetSoConOfPCConfig()[(Index)].LocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon)
#define SoAd_GetNPduUdpTxIdxOfSoCon(Index)                            (SoAd_GetSoConOfPCConfig()[(Index)].NPduUdpTxIdxOfSoCon)
#define SoAd_GetPduRouteDestBySoConIndEndIdxOfSoCon(Index)            (SoAd_GetSoConOfPCConfig()[(Index)].PduRouteDestBySoConIndEndIdxOfSoCon)
#define SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(Index)          (SoAd_GetSoConOfPCConfig()[(Index)].PduRouteDestBySoConIndStartIdxOfSoCon)
#define SoAd_GetRcvRemAddrIdxOfSoCon(Index)                           (SoAd_GetSoConOfPCConfig()[(Index)].RcvRemAddrIdxOfSoCon)
#define SoAd_GetRemAddrIpV4IdxOfSoCon(Index)                          (SoAd_GetSoConOfPCConfig()[(Index)].RemAddrIpV4IdxOfSoCon)
#define SoAd_GetRemAddrIpV6IdxOfSoCon(Index)                          (SoAd_GetSoConOfPCConfig()[(Index)].RemAddrIpV6IdxOfSoCon)
#define SoAd_GetRemAddrStateOfSoCon(Index)                            (SoAd_GetSoConOfPCConfig()[(Index)].RemAddrStateOfSoCon)
#define SoAd_GetRxBufStructMgtIdxOfSoCon(Index)                       (SoAd_GetSoConOfPCConfig()[(Index)].RxBufStructMgtIdxOfSoCon)
#define SoAd_GetRxBufStructSegEndIdxOfSoCon(Index)                    (SoAd_GetSoConOfPCConfig()[(Index)].RxBufStructSegEndIdxOfSoCon)
#define SoAd_GetRxBufStructSegStartIdxOfSoCon(Index)                  (SoAd_GetSoConOfPCConfig()[(Index)].RxBufStructSegStartIdxOfSoCon)
#define SoAd_GetRxBufferConfigIdxOfSoCon(Index)                       (SoAd_GetSoConOfPCConfig()[(Index)].RxBufferConfigIdxOfSoCon)
#define SoAd_GetRxMgtIdxOfSoCon(Index)                                (SoAd_GetSoConOfPCConfig()[(Index)].RxMgtIdxOfSoCon)
#define SoAd_GetSoConGrpIdxOfSoCon(Index)                             (SoAd_GetSoConOfPCConfig()[(Index)].SoConGrpIdxOfSoCon)
#define SoAd_GetSoConIdOfSoCon(Index)                                 (SoAd_GetSoConOfPCConfig()[(Index)].SoConIdOfSoCon)
#define SoAd_GetSoConModeChgCbkIndEndIdxOfSoCon(Index)                (SoAd_GetSoConOfPCConfig()[(Index)].SoConModeChgCbkIndEndIdxOfSoCon)
#define SoAd_GetSoConModeChgCbkIndStartIdxOfSoCon(Index)              (SoAd_GetSoConOfPCConfig()[(Index)].SoConModeChgCbkIndStartIdxOfSoCon)
#define SoAd_GetSocketIdxOfSoCon(Index)                               (SoAd_GetSoConOfPCConfig()[(Index)].SocketIdxOfSoCon)
#define SoAd_GetSocketRouteEndIdxOfSoCon(Index)                       (SoAd_GetSoConOfPCConfig()[(Index)].SocketRouteEndIdxOfSoCon)
#define SoAd_GetSocketRouteStartIdxOfSoCon(Index)                     (SoAd_GetSoConOfPCConfig()[(Index)].SocketRouteStartIdxOfSoCon)
#define SoAd_GetTcpTxQueueIdxOfSoCon(Index)                           (SoAd_GetSoConOfPCConfig()[(Index)].TcpTxQueueIdxOfSoCon)
#define SoAd_GetTlsConfigIdxOfSoCon(Index)                            (SoAd_GetSoConOfPCConfig()[(Index)].TlsConfigIdxOfSoCon)
#define SoAd_GetTpTxBufferConfigIdxOfSoCon(Index)                     (SoAd_GetSoConOfPCConfig()[(Index)].TpTxBufferConfigIdxOfSoCon)
#define SoAd_GetTxMgtIdxOfSoCon(Index)                                (SoAd_GetSoConOfPCConfig()[(Index)].TxMgtIdxOfSoCon)
#define SoAd_IsAbortOfSoConDyn(Index)                                 ((SoAd_GetSoConDynOfPCConfig()[(Index)].AbortOfSoConDyn) != FALSE)
#define SoAd_GetCloseModeOfSoConDyn(Index)                            (SoAd_GetSoConDynOfPCConfig()[(Index)].CloseModeOfSoConDyn)
#define SoAd_GetModeOfSoConDyn(Index)                                 (SoAd_GetSoConDynOfPCConfig()[(Index)].ModeOfSoConDyn)
#define SoAd_GetOpenCloseCounterOfSoConDyn(Index)                     (SoAd_GetSoConDynOfPCConfig()[(Index)].OpenCloseCounterOfSoConDyn)
#define SoAd_GetRemAddrDynOfSoConDyn(Index)                           (SoAd_GetSoConDynOfPCConfig()[(Index)].RemAddrDynOfSoConDyn)
#define SoAd_GetRemAddrStateDynOfSoConDyn(Index)                      (SoAd_GetSoConDynOfPCConfig()[(Index)].RemAddrStateDynOfSoConDyn)
#define SoAd_IsBestMatchWithPduHeaderEnabledOfSoConGrp(Index)         ((SoAd_GetSoConGrpOfPCConfig()[(Index)].BestMatchWithPduHeaderEnabledOfSoConGrp) != FALSE)
#define SoAd_IsBestMatchWithSockRouteEnabledOfSoConGrp(Index)         ((SoAd_GetSoConGrpOfPCConfig()[(Index)].BestMatchWithSockRouteEnabledOfSoConGrp) != FALSE)
#define SoAd_GetFramePriorityOfSoConGrp(Index)                        (SoAd_GetSoConGrpOfPCConfig()[(Index)].FramePriorityOfSoConGrp)
#define SoAd_GetLocalAddrIdxOfSoConGrp(Index)                         (SoAd_GetSoConGrpOfPCConfig()[(Index)].LocalAddrIdxOfSoConGrp)
#define SoAd_GetLocalPortOfSoConGrp(Index)                            (SoAd_GetSoConGrpOfPCConfig()[(Index)].LocalPortOfSoConGrp)
#define SoAd_IsMsgAcceptFilterEnabledOfSoConGrp(Index)                ((SoAd_GetSoConGrpOfPCConfig()[(Index)].MsgAcceptFilterEnabledOfSoConGrp) != FALSE)
#define SoAd_IsPduHdrEnabledOfSoConGrp(Index)                         ((SoAd_GetSoConGrpOfPCConfig()[(Index)].PduHdrEnabledOfSoConGrp) != FALSE)
#define SoAd_GetSoConEndIdxOfSoConGrp(Index)                          (SoAd_GetSoConGrpOfPCConfig()[(Index)].SoConEndIdxOfSoConGrp)
#define SoAd_GetSoConStartIdxOfSoConGrp(Index)                        (SoAd_GetSoConGrpOfPCConfig()[(Index)].SoConStartIdxOfSoConGrp)
#define SoAd_IsSockAutoSoConSetupKeepOnlineOfSoConGrp(Index)          ((SoAd_GetSoConGrpOfPCConfig()[(Index)].SockAutoSoConSetupKeepOnlineOfSoConGrp) != FALSE)
#define SoAd_IsSockAutoSoConSetupOfSoConGrp(Index)                    ((SoAd_GetSoConGrpOfPCConfig()[(Index)].SockAutoSoConSetupOfSoConGrp) != FALSE)
#define SoAd_GetSocketIdxOfSoConGrp(Index)                            (SoAd_GetSoConGrpOfPCConfig()[(Index)].SocketIdxOfSoConGrp)
#define SoAd_GetSocketTcpIdxOfSoConGrp(Index)                         (SoAd_GetSoConGrpOfPCConfig()[(Index)].SocketTcpIdxOfSoConGrp)
#define SoAd_GetSocketUdpIdxOfSoConGrp(Index)                         (SoAd_GetSoConGrpOfPCConfig()[(Index)].SocketUdpIdxOfSoConGrp)
#define SoAd_IsInvalidHndOfSoConMap(Index)                            ((SoAd_GetSoConMapOfPCConfig()[(Index)].InvalidHndOfSoConMap) != FALSE)
#define SoAd_GetSoConIdxOfSoConMap(Index)                             (SoAd_GetSoConMapOfPCConfig()[(Index)].SoConIdxOfSoConMap)
#define SoAd_GetSoConModeChgCbk(Index)                                (SoAd_GetSoConModeChgCbkOfPCConfig()[(Index)])
#define SoAd_GetSoConModeChgCbkInd(Index)                             (SoAd_GetSoConModeChgCbkIndOfPCConfig()[(Index)])
#define SoAd_GetSoConEndIdxOfSocket(Index)                            (SoAd_GetSocketOfPCConfig()[(Index)].SoConEndIdxOfSocket)
#define SoAd_GetSoConStartIdxOfSocket(Index)                          (SoAd_GetSocketOfPCConfig()[(Index)].SoConStartIdxOfSocket)
#define SoAd_GetLocalPortOfSocketDyn(Index)                           (SoAd_GetSocketDynOfPCConfig()[(Index)].LocalPortOfSocketDyn)
#define SoAd_GetSkipBytesOfSocketDyn(Index)                           (SoAd_GetSocketDynOfPCConfig()[(Index)].SkipBytesOfSocketDyn)
#define SoAd_GetSoConTxActiveIdxOfSocketDyn(Index)                    (SoAd_GetSocketDynOfPCConfig()[(Index)].SoConTxActiveIdxOfSocketDyn)
#define SoAd_GetSocketIdOfSocketDyn(Index)                            (SoAd_GetSocketDynOfPCConfig()[(Index)].SocketIdOfSocketDyn)
#define SoAd_GetStateOfSocketDyn(Index)                               (SoAd_GetSocketDynOfPCConfig()[(Index)].StateOfSocketDyn)
#define SoAd_GetSocketReportErrorCbk(Index)                           (SoAd_GetSocketReportErrorCbkOfPCConfig()[(Index)])
#define SoAd_IsMetaDataRxEnabledOfSocketRoute(Index)                  ((SoAd_GetSocketRouteOfPCConfig()[(Index)].MetaDataRxEnabledOfSocketRoute) != FALSE)
#define SoAd_GetRxPduHdrIdOfSocketRoute(Index)                        (SoAd_GetSocketRouteOfPCConfig()[(Index)].RxPduHdrIdOfSocketRoute)
#define SoAd_GetSoConIdxOfSocketRoute(Index)                          (SoAd_GetSocketRouteOfPCConfig()[(Index)].SoConIdxOfSocketRoute)
#define SoAd_GetSocketRouteDestEndIdxOfSocketRoute(Index)             (SoAd_GetSocketRouteOfPCConfig()[(Index)].SocketRouteDestEndIdxOfSocketRoute)
#define SoAd_GetSocketRouteDestStartIdxOfSocketRoute(Index)           (SoAd_GetSocketRouteOfPCConfig()[(Index)].SocketRouteDestStartIdxOfSocketRoute)
#define SoAd_GetUpperLayerApiOfSocketRoute(Index)                     (SoAd_GetSocketRouteOfPCConfig()[(Index)].UpperLayerApiOfSocketRoute)
#define SoAd_GetRouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDest(Index) (SoAd_GetSocketRouteDestOfPCConfig()[(Index)].RouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDest)
#define SoAd_GetRouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest(Index) (SoAd_GetSocketRouteDestOfPCConfig()[(Index)].RouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest)
#define SoAd_GetRxPduIdOfSocketRouteDest(Index)                       (SoAd_GetSocketRouteDestOfPCConfig()[(Index)].RxPduIdOfSocketRouteDest)
#define SoAd_GetSocketRouteIdxOfSocketRouteDest(Index)                (SoAd_GetSocketRouteDestOfPCConfig()[(Index)].SocketRouteIdxOfSocketRouteDest)
#define SoAd_GetUpperLayerIdxOfSocketRouteDest(Index)                 (SoAd_GetSocketRouteDestOfPCConfig()[(Index)].UpperLayerIdxOfSocketRouteDest)
#define SoAd_GetSocketRouteInd(Index)                                 (SoAd_GetSocketRouteIndOfPCConfig()[(Index)])
#define SoAd_IsImmedTpTxConfOfSocketTcp(Index)                        ((SoAd_GetSocketTcpOfPCConfig()[(Index)].ImmedTpTxConfOfSocketTcp) != FALSE)
#define SoAd_IsTcpInitiateOfSocketTcp(Index)                          ((SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpInitiateOfSocketTcp) != FALSE)
#define SoAd_GetTcpKeepAliveIntervalOfSocketTcp(Index)                (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpKeepAliveIntervalOfSocketTcp)
#define SoAd_IsTcpKeepAliveOfSocketTcp(Index)                         ((SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpKeepAliveOfSocketTcp) != FALSE)
#define SoAd_GetTcpKeepAliveProbesMaxOfSocketTcp(Index)               (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpKeepAliveProbesMaxOfSocketTcp)
#define SoAd_GetTcpKeepAliveTimeOfSocketTcp(Index)                    (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpKeepAliveTimeOfSocketTcp)
#define SoAd_GetTcpNoDelayOfSocketTcp(Index)                          (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpNoDelayOfSocketTcp)
#define SoAd_GetTcpRxBufMinOfSocketTcp(Index)                         (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpRxBufMinOfSocketTcp)
#define SoAd_GetTcpTxBufMinOfSocketTcp(Index)                         (SoAd_GetSocketTcpOfPCConfig()[(Index)].TcpTxBufMinOfSocketTcp)
#define SoAd_GetAliveTimeoutMaxCntOfSocketUdp(Index)                  (SoAd_GetSocketUdpOfPCConfig()[(Index)].AliveTimeoutMaxCntOfSocketUdp)
#define SoAd_GetImmedIfTxConfListSizeOfSocketUdp(Index)               (SoAd_GetSocketUdpOfPCConfig()[(Index)].ImmedIfTxConfListSizeOfSocketUdp)
#define SoAd_IsImmedIfTxConfOfSocketUdp(Index)                        ((SoAd_GetSocketUdpOfPCConfig()[(Index)].ImmedIfTxConfOfSocketUdp) != FALSE)
#define SoAd_GetNPduUdpTxBufferMinOfSocketUdp(Index)                  (SoAd_GetSocketUdpOfPCConfig()[(Index)].NPduUdpTxBufferMinOfSocketUdp)
#define SoAd_GetNPduUdpTxQueueSizeOfSocketUdp(Index)                  (SoAd_GetSocketUdpOfPCConfig()[(Index)].NPduUdpTxQueueSizeOfSocketUdp)
#define SoAd_GetRetryQueueLimitOfSocketUdp(Index)                     (SoAd_GetSocketUdpOfPCConfig()[(Index)].RetryQueueLimitOfSocketUdp)
#define SoAd_IsUdpListenOnlyOfSocketUdp(Index)                        ((SoAd_GetSocketUdpOfPCConfig()[(Index)].UdpListenOnlyOfSocketUdp) != FALSE)
#define SoAd_IsUdpStrictHdrLenCheckEnabledOfSocketUdp(Index)          ((SoAd_GetSocketUdpOfPCConfig()[(Index)].UdpStrictHdrLenCheckEnabledOfSocketUdp) != FALSE)
#define SoAd_GetUdpTriggerTimeoutOfSocketUdp(Index)                   (SoAd_GetSocketUdpOfPCConfig()[(Index)].UdpTriggerTimeoutOfSocketUdp)
#define SoAd_GetLocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl(Index)       (SoAd_GetTcpIpCtrlOfPCConfig()[(Index)].LocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl)
#define SoAd_GetLocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl(Index)     (SoAd_GetTcpIpCtrlOfPCConfig()[(Index)].LocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl)
#define SoAd_IsRetryEnabledOfTcpIpCtrl(Index)                         ((SoAd_GetTcpIpCtrlOfPCConfig()[(Index)].RetryEnabledOfTcpIpCtrl) != FALSE)
#define SoAd_IsTcpKeepAliveGloballyEnabled(Index)                     ((SoAd_GetTcpKeepAliveGloballyEnabledOfPCConfig()[(Index)]) != FALSE)
#define SoAd_GetTcpTlsSocketCreatedNotificationCbk(Index)             (SoAd_GetTcpTlsSocketCreatedNotificationCbkOfPCConfig()[(Index)])
#define SoAd_GetTcpTxQueueDataEndIdxOfTcpTxQueue(Index)               (SoAd_GetTcpTxQueueOfPCConfig()[(Index)].TcpTxQueueDataEndIdxOfTcpTxQueue)
#define SoAd_GetTcpTxQueueDataStartIdxOfTcpTxQueue(Index)             (SoAd_GetTcpTxQueueOfPCConfig()[(Index)].TcpTxQueueDataStartIdxOfTcpTxQueue)
#define SoAd_GetLenOfTcpTxQueueData(Index)                            (SoAd_GetTcpTxQueueDataOfPCConfig()[(Index)].LenOfTcpTxQueueData)
#define SoAd_GetPduRouteIdxOfTcpTxQueueData(Index)                    (SoAd_GetTcpTxQueueDataOfPCConfig()[(Index)].PduRouteIdxOfTcpTxQueueData)
#define SoAd_GetLvlOfTcpTxQueueMgt(Index)                             (SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].LvlOfTcpTxQueueMgt)
#define SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(Index)               (SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].TcpTxQueueDataIdxOfTcpTxQueueMgt)
#define SoAd_GetTotLenOfTcpTxQueueMgt(Index)                          (SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].TotLenOfTcpTxQueueMgt)
#define SoAd_GetLvlOfTimeoutListDyn(Index)                            (SoAd_GetTimeoutListDynOfPCConfig()[(Index)].LvlOfTimeoutListDyn)
#define SoAd_GetTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent(Index)   (SoAd_GetTimeoutListIdentOfPCConfig()[(Index)].TimeoutListDynNPduUdpTxIdxOfTimeoutListIdent)
#define SoAd_GetTimeoutListDynUdpAliveIdxOfTimeoutListIdent(Index)    (SoAd_GetTimeoutListIdentOfPCConfig()[(Index)].TimeoutListDynUdpAliveIdxOfTimeoutListIdent)
#define SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index)             (SoAd_GetTimeoutListNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxIdxOfTimeoutListNPduUdpTx)
#define SoAd_GetTimeoutOfTimeoutListNPduUdpTx(Index)                  (SoAd_GetTimeoutListNPduUdpTxOfPCConfig()[(Index)].TimeoutOfTimeoutListNPduUdpTx)
#define SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index) (SoAd_GetTimeoutListNPduUdpTxMapOfPCConfig()[(Index)].TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap)
#define SoAd_GetSoConIdxOfTimeoutListUdpAlive(Index)                  (SoAd_GetTimeoutListUdpAliveOfPCConfig()[(Index)].SoConIdxOfTimeoutListUdpAlive)
#define SoAd_GetTimeoutOfTimeoutListUdpAlive(Index)                   (SoAd_GetTimeoutListUdpAliveOfPCConfig()[(Index)].TimeoutOfTimeoutListUdpAlive)
#define SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index) (SoAd_GetTimeoutListUdpAliveMapOfPCConfig()[(Index)].TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap)
#define SoAd_GetRxBufSizeOfTlsConfig(Index)                           (SoAd_GetTlsConfigOfPCConfig()[(Index)].RxBufSizeOfTlsConfig)
#define SoAd_GetTcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig(Index) (SoAd_GetTlsConfigOfPCConfig()[(Index)].TcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig)
#define SoAd_GetTxBufSizeOfTlsConfig(Index)                           (SoAd_GetTlsConfigOfPCConfig()[(Index)].TxBufSizeOfTlsConfig)
#define SoAd_GetTpRxBuffer(Index)                                     (SoAd_GetTpRxBufferOfPCConfig()[(Index)])
#define SoAd_GetTpTxBuffer(Index)                                     (SoAd_GetTpTxBufferOfPCConfig()[(Index)])
#define SoAd_GetTpTxBufferEndIdxOfTpTxBufferConfig(Index)             (SoAd_GetTpTxBufferConfigOfPCConfig()[(Index)].TpTxBufferEndIdxOfTpTxBufferConfig)
#define SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(Index)           (SoAd_GetTpTxBufferConfigOfPCConfig()[(Index)].TpTxBufferStartIdxOfTpTxBufferConfig)
#define SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(Index)             (SoAd_GetTpTxBufferConfigDynOfPCConfig()[(Index)].TpTxBufferIdxOfTpTxBufferConfigDyn)
#define SoAd_GetTriggerBuf(Index)                                     (SoAd_GetTriggerBufOfPCConfig()[(Index)])
#define SoAd_GetTriggerBufEndIdxOfTriggerBufConfig(Index)             (SoAd_GetTriggerBufConfigOfPCConfig()[(Index)].TriggerBufEndIdxOfTriggerBufConfig)
#define SoAd_GetTriggerBufStartIdxOfTriggerBufConfig(Index)           (SoAd_GetTriggerBufConfigOfPCConfig()[(Index)].TriggerBufStartIdxOfTriggerBufConfig)
#define SoAd_GetLengthOfTriggerBufConfigDyn(Index)                    (SoAd_GetTriggerBufConfigDynOfPCConfig()[(Index)].LengthOfTriggerBufConfigDyn)
#define SoAd_GetPduRouteIdxOfTriggerBufConfigDyn(Index)               (SoAd_GetTriggerBufConfigDynOfPCConfig()[(Index)].PduRouteIdxOfTriggerBufConfigDyn)
#define SoAd_IsCancelRequestedOfTxMgt(Index)                          ((SoAd_GetTxMgtOfPCConfig()[(Index)].CancelRequestedOfTxMgt) != FALSE)
#define SoAd_GetPduRouteDestIdxOfTxMgt(Index)                         (SoAd_GetTxMgtOfPCConfig()[(Index)].PduRouteDestIdxOfTxMgt)
#define SoAd_GetTxBufPtrOfTxMgt(Index)                                (SoAd_GetTxMgtOfPCConfig()[(Index)].TxBufPtrOfTxMgt)
#define SoAd_GetTxBytesLenOfTxMgt(Index)                              (SoAd_GetTxMgtOfPCConfig()[(Index)].TxBytesLenOfTxMgt)
#define SoAd_GetTxBytesPendingOfTxMgt(Index)                          (SoAd_GetTxMgtOfPCConfig()[(Index)].TxBytesPendingOfTxMgt)
#define SoAd_IsInvalidHndOfTxPduIdMap(Index)                          ((SoAd_GetTxPduIdMapOfPCConfig()[(Index)].InvalidHndOfTxPduIdMap) != FALSE)
#define SoAd_GetPduRouteIdxOfTxPduIdMap(Index)                        (SoAd_GetTxPduIdMapOfPCConfig()[(Index)].PduRouteIdxOfTxPduIdMap)
#define SoAd_GetIfRxIndicationCbkOfUpperLayer(Index)                  (SoAd_GetUpperLayerOfPCConfig()[(Index)].IfRxIndicationCbkOfUpperLayer)
#define SoAd_GetIfTriggerTransmitCbkOfUpperLayer(Index)               (SoAd_GetUpperLayerOfPCConfig()[(Index)].IfTriggerTransmitCbkOfUpperLayer)
#define SoAd_GetIfTxConfirmationCbkOfUpperLayer(Index)                (SoAd_GetUpperLayerOfPCConfig()[(Index)].IfTxConfirmationCbkOfUpperLayer)
#define SoAd_GetTpCopyRxDataCbkOfUpperLayer(Index)                    (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpCopyRxDataCbkOfUpperLayer)
#define SoAd_GetTpCopyRxDataConstCbkOfUpperLayer(Index)               (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpCopyRxDataConstCbkOfUpperLayer)
#define SoAd_GetTpCopyTxDataCbkOfUpperLayer(Index)                    (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpCopyTxDataCbkOfUpperLayer)
#define SoAd_GetTpCopyTxDataConstCbkOfUpperLayer(Index)               (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpCopyTxDataConstCbkOfUpperLayer)
#define SoAd_GetTpRxIndicationCbkOfUpperLayer(Index)                  (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpRxIndicationCbkOfUpperLayer)
#define SoAd_GetTpStartOfReceptionCbkOfUpperLayer(Index)              (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpStartOfReceptionCbkOfUpperLayer)
#define SoAd_GetTpStartOfReceptionConstCbkOfUpperLayer(Index)         (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpStartOfReceptionConstCbkOfUpperLayer)
#define SoAd_GetTpTxConfirmationCbkOfUpperLayer(Index)                (SoAd_GetUpperLayerOfPCConfig()[(Index)].TpTxConfirmationCbkOfUpperLayer)
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCGetDeduplicatedDataMacros  SoAd Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define SoAd_IsEventQueueIfTxRouteGrpUsedOfEventQueueIdent(Index)     (((boolean)(SoAd_GetEventQueueIfTxRouteGrpIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUEIFTXROUTEGRPIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueIfUdpPduRouteUsedOfEventQueueIdent(Index)    (((boolean)(SoAd_GetEventQueueIfUdpPduRouteIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUEIFUDPPDUROUTEIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueLocalAddrUsedOfEventQueueIdent(Index)        (((boolean)(SoAd_GetEventQueueLocalAddrIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUELOCALADDRIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueSockIdxUsedOfEventQueueIdent(Index)          (((boolean)(SoAd_GetEventQueueSockIdxIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUESOCKIDXIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueTcpTxSoConUsedOfEventQueueIdent(Index)       (((boolean)(SoAd_GetEventQueueTcpTxSoConIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUETCPTXSOCONIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueTpRxSoConUsedOfEventQueueIdent(Index)        (((boolean)(SoAd_GetEventQueueTpRxSoConIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUETPRXSOCONIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_IsEventQueueTpTxSoConUsedOfEventQueueIdent(Index)        (((boolean)(SoAd_GetEventQueueTpTxSoConIdxOfEventQueueIdent(Index) != SOAD_NO_EVENTQUEUETPTXSOCONIDXOFEVENTQUEUEIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_EventQueue */
#define SoAd_GetMaxIfRouteGrpTransmitPduSize()                        SoAd_GetMaxIfRouteGrpTransmitPduSizeOfPCConfig()
#define SoAd_IsNPduUdpTxBufferUsedOfNPduUdpTx(Index)                  (((boolean)(SoAd_GetNPduUdpTxBufferStartIdxOfNPduUdpTx(Index) != SOAD_NO_NPDUUDPTXBUFFERSTARTIDXOFNPDUUDPTX)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_NPduUdpTxBuffer */
#define SoAd_IsNPduUdpTxQueueUsedOfNPduUdpTx(Index)                   (((boolean)(SoAd_GetNPduUdpTxQueueStartIdxOfNPduUdpTx(Index) != SOAD_NO_NPDUUDPTXQUEUESTARTIDXOFNPDUUDPTX)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_NPduUdpTxQueue */
#define SoAd_IsRouteGrpSoConByPduRouteDestIndUsedOfPduRouteDest(Index) (((boolean)(SoAd_GetRouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest(Index) != SOAD_NO_ROUTEGRPSOCONBYPDUROUTEDESTINDSTARTIDXOFPDUROUTEDEST)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd */
#define SoAd_IsPduRouteDestIndUsedOfRouteGrp(Index)                   (((boolean)(SoAd_GetPduRouteDestIndStartIdxOfRouteGrp(Index) != SOAD_NO_PDUROUTEDESTINDSTARTIDXOFROUTEGRP)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_PduRouteDestInd */
#define SoAd_IsRouteGrpSoConUsedOfRouteGrp(Index)                     (((boolean)(SoAd_GetRouteGrpSoConStartIdxOfRouteGrp(Index) != SOAD_NO_ROUTEGRPSOCONSTARTIDXOFROUTEGRP)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_RouteGrpSoCon */
#define SoAd_IsSocketRouteIndUsedOfRouteGrp(Index)                    (((boolean)(SoAd_GetSocketRouteIndStartIdxOfRouteGrp(Index) != SOAD_NO_SOCKETROUTEINDSTARTIDXOFROUTEGRP)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_SocketRouteInd */
#define SoAd_IsIfRxBufferUsedOfRxBufferConfig(Index)                  (((boolean)(SoAd_GetIfRxBufferStartIdxOfRxBufferConfig(Index) != SOAD_NO_IFRXBUFFERSTARTIDXOFRXBUFFERCONFIG)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_IfRxBuffer */
#define SoAd_IsTpRxBufferUsedOfRxBufferConfig(Index)                  (((boolean)(SoAd_GetTpRxBufferStartIdxOfRxBufferConfig(Index) != SOAD_NO_TPRXBUFFERSTARTIDXOFRXBUFFERCONFIG)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_TpRxBuffer */
#define SoAd_GetSizeOfBestMatchSoConIdxList()                         SoAd_GetSizeOfBestMatchSoConIdxListOfPCConfig()
#define SoAd_GetSizeOfDhcpEventCbk()                                  SoAd_GetSizeOfDhcpEventCbkOfPCConfig()
#define SoAd_GetSizeOfEventQueue()                                    SoAd_GetSizeOfEventQueueOfPCConfig()
#define SoAd_GetSizeOfEventQueueDyn()                                 SoAd_GetSizeOfEventQueueDynOfPCConfig()
#define SoAd_GetSizeOfEventQueueFlag()                                SoAd_GetSizeOfEventQueueFlagOfPCConfig()
#define SoAd_GetSizeOfEventQueueIdent()                               SoAd_GetSizeOfEventQueueIdentOfPCConfig()
#define SoAd_GetSizeOfEventQueueIfTxRouteGrp()                        SoAd_GetSizeOfEventQueueIfTxRouteGrpOfPCConfig()
#define SoAd_GetSizeOfEventQueueIfUdpPduRoute()                       SoAd_GetSizeOfEventQueueIfUdpPduRouteOfPCConfig()
#define SoAd_GetSizeOfEventQueueLocalAddr()                           SoAd_GetSizeOfEventQueueLocalAddrOfPCConfig()
#define SoAd_GetSizeOfEventQueueSocketIdx()                           SoAd_GetSizeOfEventQueueSocketIdxOfPCConfig()
#define SoAd_GetSizeOfEventQueueStateSoCon()                          SoAd_GetSizeOfEventQueueStateSoConOfPCConfig()
#define SoAd_GetSizeOfEventQueueTcpTxSoCon()                          SoAd_GetSizeOfEventQueueTcpTxSoConOfPCConfig()
#define SoAd_GetSizeOfEventQueueTpRxSoCon()                           SoAd_GetSizeOfEventQueueTpRxSoConOfPCConfig()
#define SoAd_GetSizeOfEventQueueTpTxSoCon()                           SoAd_GetSizeOfEventQueueTpTxSoConOfPCConfig()
#define SoAd_GetSizeOfIfRxBuffer()                                    SoAd_GetSizeOfIfRxBufferOfPCConfig()
#define SoAd_GetSizeOfIpFragBuf()                                     SoAd_GetSizeOfIpFragBufOfPCConfig()
#define SoAd_GetSizeOfIpFragBufConfig()                               SoAd_GetSizeOfIpFragBufConfigOfPCConfig()
#define SoAd_GetSizeOfIpFragBufConfigDyn()                            SoAd_GetSizeOfIpFragBufConfigDynOfPCConfig()
#define SoAd_GetSizeOfIpFragMgt()                                     SoAd_GetSizeOfIpFragMgtOfPCConfig()
#define SoAd_GetSizeOfLocalAddr()                                     SoAd_GetSizeOfLocalAddrOfPCConfig()
#define SoAd_GetSizeOfLocalAddrByTcpIpCtrlInd()                       SoAd_GetSizeOfLocalAddrByTcpIpCtrlIndOfPCConfig()
#define SoAd_GetSizeOfLocalAddrDyn()                                  SoAd_GetSizeOfLocalAddrDynOfPCConfig()
#define SoAd_GetSizeOfLocalAddrIdMap()                                SoAd_GetSizeOfLocalAddrIdMapOfPCConfig()
#define SoAd_GetSizeOfLocalIpAddrAssignmentChgCbk()                   SoAd_GetSizeOfLocalIpAddrAssignmentChgCbkOfPCConfig()
#define SoAd_GetSizeOfLocalIpAddrAssignmentChgCbkInd()                SoAd_GetSizeOfLocalIpAddrAssignmentChgCbkIndOfPCConfig()
#define SoAd_GetSizeOfMetaDataRxBuf()                                 SoAd_GetSizeOfMetaDataRxBufOfPCConfig()
#define SoAd_GetSizeOfNPduUdpTx()                                     SoAd_GetSizeOfNPduUdpTxOfPCConfig()
#define SoAd_GetSizeOfNPduUdpTxBuffer()                               SoAd_GetSizeOfNPduUdpTxBufferOfPCConfig()
#define SoAd_GetSizeOfNPduUdpTxDyn()                                  SoAd_GetSizeOfNPduUdpTxDynOfPCConfig()
#define SoAd_GetSizeOfNPduUdpTxQueue()                                SoAd_GetSizeOfNPduUdpTxQueueOfPCConfig()
#define SoAd_GetSizeOfPduRoute()                                      SoAd_GetSizeOfPduRouteOfPCConfig()
#define SoAd_GetSizeOfPduRouteDest()                                  SoAd_GetSizeOfPduRouteDestOfPCConfig()
#define SoAd_GetSizeOfPduRouteDestBySoConInd()                        SoAd_GetSizeOfPduRouteDestBySoConIndOfPCConfig()
#define SoAd_GetSizeOfPduRouteDestInd()                               SoAd_GetSizeOfPduRouteDestIndOfPCConfig()
#define SoAd_GetSizeOfPduRouteDyn()                                   SoAd_GetSizeOfPduRouteDynOfPCConfig()
#define SoAd_GetSizeOfRcvRemAddr()                                    SoAd_GetSizeOfRcvRemAddrOfPCConfig()
#define SoAd_GetSizeOfRemAddrIpV4()                                   SoAd_GetSizeOfRemAddrIpV4OfPCConfig()
#define SoAd_GetSizeOfRemAddrIpV6()                                   SoAd_GetSizeOfRemAddrIpV6OfPCConfig()
#define SoAd_GetSizeOfRouteGrp()                                      SoAd_GetSizeOfRouteGrpOfPCConfig()
#define SoAd_GetSizeOfRouteGrpIdMap()                                 SoAd_GetSizeOfRouteGrpIdMapOfPCConfig()
#define SoAd_GetSizeOfRouteGrpSoCon()                                 SoAd_GetSizeOfRouteGrpSoConOfPCConfig()
#define SoAd_GetSizeOfRouteGrpSoConByPduRouteDestInd()                SoAd_GetSizeOfRouteGrpSoConByPduRouteDestIndOfPCConfig()
#define SoAd_GetSizeOfRouteGrpSoConBySocketRouteDestInd()             SoAd_GetSizeOfRouteGrpSoConBySocketRouteDestIndOfPCConfig()
#define SoAd_GetSizeOfRouteGrpSoConDyn()                              SoAd_GetSizeOfRouteGrpSoConDynOfPCConfig()
#define SoAd_GetSizeOfRxBufStructMgt()                                SoAd_GetSizeOfRxBufStructMgtOfPCConfig()
#define SoAd_GetSizeOfRxBufStructSeg()                                SoAd_GetSizeOfRxBufStructSegOfPCConfig()
#define SoAd_GetSizeOfRxBufferConfig()                                SoAd_GetSizeOfRxBufferConfigOfPCConfig()
#define SoAd_GetSizeOfRxBufferConfigDyn()                             SoAd_GetSizeOfRxBufferConfigDynOfPCConfig()
#define SoAd_GetSizeOfRxMgt()                                         SoAd_GetSizeOfRxMgtOfPCConfig()
#define SoAd_GetSizeOfRxPduIdIdMap()                                  SoAd_GetSizeOfRxPduIdIdMapOfPCConfig()
#define SoAd_GetSizeOfShutdownFinishedCbk()                           SoAd_GetSizeOfShutdownFinishedCbkOfPCConfig()
#define SoAd_GetSizeOfSoCon()                                         SoAd_GetSizeOfSoConOfPCConfig()
#define SoAd_GetSizeOfSoConDyn()                                      SoAd_GetSizeOfSoConDynOfPCConfig()
#define SoAd_GetSizeOfSoConGrp()                                      SoAd_GetSizeOfSoConGrpOfPCConfig()
#define SoAd_GetSizeOfSoConMap()                                      SoAd_GetSizeOfSoConMapOfPCConfig()
#define SoAd_GetSizeOfSoConModeChgCbk()                               SoAd_GetSizeOfSoConModeChgCbkOfPCConfig()
#define SoAd_GetSizeOfSoConModeChgCbkInd()                            SoAd_GetSizeOfSoConModeChgCbkIndOfPCConfig()
#define SoAd_GetSizeOfSocket()                                        SoAd_GetSizeOfSocketOfPCConfig()
#define SoAd_GetSizeOfSocketDyn()                                     SoAd_GetSizeOfSocketDynOfPCConfig()
#define SoAd_GetSizeOfSocketReportErrorCbk()                          SoAd_GetSizeOfSocketReportErrorCbkOfPCConfig()
#define SoAd_GetSizeOfSocketRoute()                                   SoAd_GetSizeOfSocketRouteOfPCConfig()
#define SoAd_GetSizeOfSocketRouteDest()                               SoAd_GetSizeOfSocketRouteDestOfPCConfig()
#define SoAd_GetSizeOfSocketRouteInd()                                SoAd_GetSizeOfSocketRouteIndOfPCConfig()
#define SoAd_GetSizeOfSocketTcp()                                     SoAd_GetSizeOfSocketTcpOfPCConfig()
#define SoAd_GetSizeOfSocketUdp()                                     SoAd_GetSizeOfSocketUdpOfPCConfig()
#define SoAd_GetSizeOfTcpIpCtrl()                                     SoAd_GetSizeOfTcpIpCtrlOfPCConfig()
#define SoAd_GetSizeOfTcpKeepAliveGloballyEnabled()                   SoAd_GetSizeOfTcpKeepAliveGloballyEnabledOfPCConfig()
#define SoAd_GetSizeOfTcpTlsSocketCreatedNotificationCbk()            SoAd_GetSizeOfTcpTlsSocketCreatedNotificationCbkOfPCConfig()
#define SoAd_GetSizeOfTcpTxQueue()                                    SoAd_GetSizeOfTcpTxQueueOfPCConfig()
#define SoAd_GetSizeOfTcpTxQueueData()                                SoAd_GetSizeOfTcpTxQueueDataOfPCConfig()
#define SoAd_GetSizeOfTcpTxQueueMgt()                                 SoAd_GetSizeOfTcpTxQueueMgtOfPCConfig()
#define SoAd_GetSizeOfTimeoutListDyn()                                SoAd_GetSizeOfTimeoutListDynOfPCConfig()
#define SoAd_GetSizeOfTimeoutListIdent()                              SoAd_GetSizeOfTimeoutListIdentOfPCConfig()
#define SoAd_GetSizeOfTimeoutListNPduUdpTx()                          SoAd_GetSizeOfTimeoutListNPduUdpTxOfPCConfig()
#define SoAd_GetSizeOfTimeoutListNPduUdpTxMap()                       SoAd_GetSizeOfTimeoutListNPduUdpTxMapOfPCConfig()
#define SoAd_GetSizeOfTimeoutListUdpAlive()                           SoAd_GetSizeOfTimeoutListUdpAliveOfPCConfig()
#define SoAd_GetSizeOfTimeoutListUdpAliveMap()                        SoAd_GetSizeOfTimeoutListUdpAliveMapOfPCConfig()
#define SoAd_GetSizeOfTlsConfig()                                     SoAd_GetSizeOfTlsConfigOfPCConfig()
#define SoAd_GetSizeOfTpRxBuffer()                                    SoAd_GetSizeOfTpRxBufferOfPCConfig()
#define SoAd_GetSizeOfTpTxBuffer()                                    SoAd_GetSizeOfTpTxBufferOfPCConfig()
#define SoAd_GetSizeOfTpTxBufferConfig()                              SoAd_GetSizeOfTpTxBufferConfigOfPCConfig()
#define SoAd_GetSizeOfTpTxBufferConfigDyn()                           SoAd_GetSizeOfTpTxBufferConfigDynOfPCConfig()
#define SoAd_GetSizeOfTriggerBuf()                                    SoAd_GetSizeOfTriggerBufOfPCConfig()
#define SoAd_GetSizeOfTriggerBufConfig()                              SoAd_GetSizeOfTriggerBufConfigOfPCConfig()
#define SoAd_GetSizeOfTriggerBufConfigDyn()                           SoAd_GetSizeOfTriggerBufConfigDynOfPCConfig()
#define SoAd_GetSizeOfTxMgt()                                         SoAd_GetSizeOfTxMgtOfPCConfig()
#define SoAd_GetSizeOfTxPduIdMap()                                    SoAd_GetSizeOfTxPduIdMapOfPCConfig()
#define SoAd_GetSizeOfUpperLayer()                                    SoAd_GetSizeOfUpperLayerOfPCConfig()
#define SoAd_IsIpFragMgtUsedOfSoCon(Index)                            (((boolean)(SoAd_GetIpFragMgtIdxOfSoCon(Index) != SOAD_NO_IPFRAGMGTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_IpFragMgt */
#define SoAd_IsLocalIpAddrAssignmentChgCbkIndUsedOfSoCon(Index)       (((boolean)(SoAd_GetLocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon(Index) != SOAD_NO_LOCALIPADDRASSIGNMENTCHGCBKINDSTARTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd */
#define SoAd_IsNPduUdpTxUsedOfSoCon(Index)                            (((boolean)(SoAd_GetNPduUdpTxIdxOfSoCon(Index) != SOAD_NO_NPDUUDPTXIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_NPduUdpTx */
#define SoAd_IsPduRouteDestBySoConIndUsedOfSoCon(Index)               (((boolean)(SoAd_GetPduRouteDestBySoConIndStartIdxOfSoCon(Index) != SOAD_NO_PDUROUTEDESTBYSOCONINDSTARTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_PduRouteDestBySoConInd */
#define SoAd_IsRcvRemAddrUsedOfSoCon(Index)                           (((boolean)(SoAd_GetRcvRemAddrIdxOfSoCon(Index) != SOAD_NO_RCVREMADDRIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RcvRemAddr */
#define SoAd_IsRemAddrIpV4UsedOfSoCon(Index)                          (((boolean)(SoAd_GetRemAddrIpV4IdxOfSoCon(Index) != SOAD_NO_REMADDRIPV4IDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RemAddrIpV4 */
#define SoAd_IsRemAddrIpV6UsedOfSoCon(Index)                          (((boolean)(SoAd_GetRemAddrIpV6IdxOfSoCon(Index) != SOAD_NO_REMADDRIPV6IDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RemAddrIpV6 */
#define SoAd_IsRxBufStructMgtUsedOfSoCon(Index)                       (((boolean)(SoAd_GetRxBufStructMgtIdxOfSoCon(Index) != SOAD_NO_RXBUFSTRUCTMGTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RxBufStructMgt */
#define SoAd_IsRxBufStructSegUsedOfSoCon(Index)                       (((boolean)(SoAd_GetRxBufStructSegStartIdxOfSoCon(Index) != SOAD_NO_RXBUFSTRUCTSEGSTARTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_RxBufStructSeg */
#define SoAd_IsRxBufferConfigUsedOfSoCon(Index)                       (((boolean)(SoAd_GetRxBufferConfigIdxOfSoCon(Index) != SOAD_NO_RXBUFFERCONFIGIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RxBufferConfig */
#define SoAd_IsRxMgtUsedOfSoCon(Index)                                (((boolean)(SoAd_GetRxMgtIdxOfSoCon(Index) != SOAD_NO_RXMGTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_RxMgt */
#define SoAd_IsSoConModeChgCbkIndUsedOfSoCon(Index)                   (((boolean)(SoAd_GetSoConModeChgCbkIndStartIdxOfSoCon(Index) != SOAD_NO_SOCONMODECHGCBKINDSTARTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_SoConModeChgCbkInd */
#define SoAd_IsSocketRouteUsedOfSoCon(Index)                          (((boolean)(SoAd_GetSocketRouteStartIdxOfSoCon(Index) != SOAD_NO_SOCKETROUTESTARTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_SocketRoute */
#define SoAd_IsTcpTxQueueUsedOfSoCon(Index)                           (((boolean)(SoAd_GetTcpTxQueueIdxOfSoCon(Index) != SOAD_NO_TCPTXQUEUEIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TcpTxQueue */
#define SoAd_IsTlsConfigUsedOfSoCon(Index)                            (((boolean)(SoAd_GetTlsConfigIdxOfSoCon(Index) != SOAD_NO_TLSCONFIGIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TlsConfig */
#define SoAd_IsTpTxBufferConfigUsedOfSoCon(Index)                     (((boolean)(SoAd_GetTpTxBufferConfigIdxOfSoCon(Index) != SOAD_NO_TPTXBUFFERCONFIGIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TpTxBufferConfig */
#define SoAd_IsTxMgtUsedOfSoCon(Index)                                (((boolean)(SoAd_GetTxMgtIdxOfSoCon(Index) != SOAD_NO_TXMGTIDXOFSOCON)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TxMgt */
#define SoAd_IsLocalAddrUsedOfSoConGrp(Index)                         (((boolean)(SoAd_GetLocalAddrIdxOfSoConGrp(Index) != SOAD_NO_LOCALADDRIDXOFSOCONGRP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_LocalAddr */
#define SoAd_IsSocketTcpUsedOfSoConGrp(Index)                         (((boolean)(SoAd_GetSocketTcpIdxOfSoConGrp(Index) != SOAD_NO_SOCKETTCPIDXOFSOCONGRP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_SocketTcp */
#define SoAd_IsSocketUdpUsedOfSoConGrp(Index)                         (((boolean)(SoAd_GetSocketUdpIdxOfSoConGrp(Index) != SOAD_NO_SOCKETUDPIDXOFSOCONGRP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_SocketUdp */
#define SoAd_IsSocketUsedOfSoConGrp(Index)                            (((boolean)(SoAd_GetSocketIdxOfSoConGrp(Index) != SOAD_NO_SOCKETIDXOFSOCONGRP)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_Socket */
#define SoAd_IsRouteGrpSoConBySocketRouteDestIndUsedOfSocketRouteDest(Index) (((boolean)(SoAd_GetRouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest(Index) != SOAD_NO_ROUTEGRPSOCONBYSOCKETROUTEDESTINDSTARTIDXOFSOCKETROUTEDEST)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd */
#define SoAd_IsLocalAddrByTcpIpCtrlIndUsedOfTcpIpCtrl(Index)          (((boolean)(SoAd_GetLocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl(Index) != SOAD_NO_LOCALADDRBYTCPIPCTRLINDSTARTIDXOFTCPIPCTRL)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_LocalAddrByTcpIpCtrlInd */
#define SoAd_IsTimeoutListDynNPduUdpTxUsedOfTimeoutListIdent(Index)   (((boolean)(SoAd_GetTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent(Index) != SOAD_NO_TIMEOUTLISTDYNNPDUUDPTXIDXOFTIMEOUTLISTIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TimeoutListDyn */
#define SoAd_IsTimeoutListDynUdpAliveUsedOfTimeoutListIdent(Index)    (((boolean)(SoAd_GetTimeoutListDynUdpAliveIdxOfTimeoutListIdent(Index) != SOAD_NO_TIMEOUTLISTDYNUDPALIVEIDXOFTIMEOUTLISTIDENT)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TimeoutListDyn */
#define SoAd_IsTcpTlsSocketCreatedNotificationCbkUsedOfTlsConfig(Index) (((boolean)(SoAd_GetTcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig(Index) != SOAD_NO_TCPTLSSOCKETCREATEDNOTIFICATIONCBKIDXOFTLSCONFIG)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to SoAd_TcpTlsSocketCreatedNotificationCbk */
#define SoAd_IsTpTxBufferUsedOfTpTxBufferConfig(Index)                (((boolean)(SoAd_GetTpTxBufferStartIdxOfTpTxBufferConfig(Index) != SOAD_NO_TPTXBUFFERSTARTIDXOFTPTXBUFFERCONFIG)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to SoAd_TpTxBuffer */
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCSetDataMacros  SoAd Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define SoAd_SetSoConIdxOfBestMatchSoConIdxList(Index, Value)         SoAd_GetBestMatchSoConIdxListOfPCConfig()[(Index)].SoConIdxOfBestMatchSoConIdxList = (Value)
#define SoAd_SetIdxOfEventQueueDyn(Index, Value)                      SoAd_GetEventQueueDynOfPCConfig()[(Index)].IdxOfEventQueueDyn = (Value)
#define SoAd_SetLvlOfEventQueueDyn(Index, Value)                      SoAd_GetEventQueueDynOfPCConfig()[(Index)].LvlOfEventQueueDyn = (Value)
#define SoAd_SetEventQueueFlag(Index, Value)                          SoAd_GetEventQueueFlagOfPCConfig()[(Index)] = (Value)
#define SoAd_SetRouteGrpIdxOfEventQueueIfTxRouteGrp(Index, Value)     SoAd_GetEventQueueIfTxRouteGrpOfPCConfig()[(Index)].RouteGrpIdxOfEventQueueIfTxRouteGrp = (Value)
#define SoAd_SetPduRouteIdxOfEventQueueIfUdpPduRoute(Index, Value)    SoAd_GetEventQueueIfUdpPduRouteOfPCConfig()[(Index)].PduRouteIdxOfEventQueueIfUdpPduRoute = (Value)
#define SoAd_SetLocalAddrIdxOfEventQueueLocalAddr(Index, Value)       SoAd_GetEventQueueLocalAddrOfPCConfig()[(Index)].LocalAddrIdxOfEventQueueLocalAddr = (Value)
#define SoAd_SetSocketIdxOfEventQueueSocketIdx(Index, Value)          SoAd_GetEventQueueSocketIdxOfPCConfig()[(Index)].SocketIdxOfEventQueueSocketIdx = (Value)
#define SoAd_SetSoConIdxOfEventQueueStateSoCon(Index, Value)          SoAd_GetEventQueueStateSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueStateSoCon = (Value)
#define SoAd_SetSoConIdxOfEventQueueTcpTxSoCon(Index, Value)          SoAd_GetEventQueueTcpTxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTcpTxSoCon = (Value)
#define SoAd_SetSoConIdxOfEventQueueTpRxSoCon(Index, Value)           SoAd_GetEventQueueTpRxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTpRxSoCon = (Value)
#define SoAd_SetSoConIdxOfEventQueueTpTxSoCon(Index, Value)           SoAd_GetEventQueueTpTxSoConOfPCConfig()[(Index)].SoConIdxOfEventQueueTpTxSoCon = (Value)
#define SoAd_SetIfRxBuffer(Index, Value)                              SoAd_GetIfRxBufferOfPCConfig()[(Index)] = (Value)
#define SoAd_SetIpFragBuf(Index, Value)                               SoAd_GetIpFragBufOfPCConfig()[(Index)] = (Value)
#define SoAd_SetLengthOfIpFragBufConfigDyn(Index, Value)              SoAd_GetIpFragBufConfigDynOfPCConfig()[(Index)].LengthOfIpFragBufConfigDyn = (Value)
#define SoAd_SetIpFragBufConfigIdxOfIpFragMgt(Index, Value)           SoAd_GetIpFragMgtOfPCConfig()[(Index)].IpFragBufConfigIdxOfIpFragMgt = (Value)
#define SoAd_SetIpAddrStateOfLocalAddrDyn(Index, Value)               SoAd_GetLocalAddrDynOfPCConfig()[(Index)].IpAddrStateOfLocalAddrDyn = (Value)
#define SoAd_SetMetaDataRxBuf(Index, Value)                           SoAd_GetMetaDataRxBufOfPCConfig()[(Index)] = (Value)
#define SoAd_SetNPduUdpTxBuffer(Index, Value)                         SoAd_GetNPduUdpTxBufferOfPCConfig()[(Index)] = (Value)
#define SoAd_SetBufLenOfNPduUdpTxDyn(Index, Value)                    SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].BufLenOfNPduUdpTxDyn = (Value)
#define SoAd_SetLvlOfNPduUdpTxDyn(Index, Value)                       SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].LvlOfNPduUdpTxDyn = (Value)
#define SoAd_SetRetryCntOfNPduUdpTxDyn(Index, Value)                  SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].RetryCntOfNPduUdpTxDyn = (Value)
#define SoAd_SetTotalLenOfNPduUdpTxDyn(Index, Value)                  SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].TotalLenOfNPduUdpTxDyn = (Value)
#define SoAd_SetTransmissionActiveOfNPduUdpTxDyn(Index, Value)        SoAd_GetNPduUdpTxDynOfPCConfig()[(Index)].TransmissionActiveOfNPduUdpTxDyn = (Value)
#define SoAd_SetCopiedOfNPduUdpTxQueue(Index, Value)                  SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].CopiedOfNPduUdpTxQueue = (Value)
#define SoAd_SetLenOfNPduUdpTxQueue(Index, Value)                     SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].LenOfNPduUdpTxQueue = (Value)
#define SoAd_SetNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index, Value)      SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].NPduUdpTxBufferIdxOfNPduUdpTxQueue = (Value)
#define SoAd_SetPduRouteDestIdxOfNPduUdpTxQueue(Index, Value)         SoAd_GetNPduUdpTxQueueOfPCConfig()[(Index)].PduRouteDestIdxOfNPduUdpTxQueue = (Value)
#define SoAd_SetPendingTxConfMainOfPduRouteDyn(Index, Value)          SoAd_GetPduRouteDynOfPCConfig()[(Index)].PendingTxConfMainOfPduRouteDyn = (Value)
#define SoAd_SetPendingTxConfNumOfPduRouteDyn(Index, Value)           SoAd_GetPduRouteDynOfPCConfig()[(Index)].PendingTxConfNumOfPduRouteDyn = (Value)
#define SoAd_SetRcvRemAddr(Index, Value)                              SoAd_GetRcvRemAddrOfPCConfig()[(Index)] = (Value)
#define SoAd_SetEnabledOfRouteGrpSoConDyn(Index, Value)               SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].EnabledOfRouteGrpSoConDyn = (Value)
#define SoAd_SetSentOfRouteGrpSoConDyn(Index, Value)                  SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].SentOfRouteGrpSoConDyn = (Value)
#define SoAd_SetTriggerOfRouteGrpSoConDyn(Index, Value)               SoAd_GetRouteGrpSoConDynOfPCConfig()[(Index)].TriggerOfRouteGrpSoConDyn = (Value)
#define SoAd_SetRxBufStructSegIdxOfRxBufStructMgt(Index, Value)       SoAd_GetRxBufStructMgtOfPCConfig()[(Index)].RxBufStructSegIdxOfRxBufStructMgt = (Value)
#define SoAd_SetRxBufStructSegLvlOfRxBufStructMgt(Index, Value)       SoAd_GetRxBufStructMgtOfPCConfig()[(Index)].RxBufStructSegLvlOfRxBufStructMgt = (Value)
#define SoAd_SetDataPtrOfRxBufStructSeg(Index, Value)                 SoAd_GetRxBufStructSegOfPCConfig()[(Index)].DataPtrOfRxBufStructSeg = (Value)
#define SoAd_SetLenOfRxBufStructSeg(Index, Value)                     SoAd_GetRxBufStructSegOfPCConfig()[(Index)].LenOfRxBufStructSeg = (Value)
#define SoAd_SetIfRxBufferIdxOfRxBufferConfigDyn(Index, Value)        SoAd_GetRxBufferConfigDynOfPCConfig()[(Index)].IfRxBufferIdxOfRxBufferConfigDyn = (Value)
#define SoAd_SetTpRxBufferIdxOfRxBufferConfigDyn(Index, Value)        SoAd_GetRxBufferConfigDynOfPCConfig()[(Index)].TpRxBufferIdxOfRxBufferConfigDyn = (Value)
#define SoAd_SetCancelRequestedOfRxMgt(Index, Value)                  SoAd_GetRxMgtOfPCConfig()[(Index)].CancelRequestedOfRxMgt = (Value)
#define SoAd_SetRxBytesPendingOfRxMgt(Index, Value)                   SoAd_GetRxMgtOfPCConfig()[(Index)].RxBytesPendingOfRxMgt = (Value)
#define SoAd_SetSocketRouteDestIdxOfRxMgt(Index, Value)               SoAd_GetRxMgtOfPCConfig()[(Index)].SocketRouteDestIdxOfRxMgt = (Value)
#define SoAd_SetAbortOfSoConDyn(Index, Value)                         SoAd_GetSoConDynOfPCConfig()[(Index)].AbortOfSoConDyn = (Value)
#define SoAd_SetCloseModeOfSoConDyn(Index, Value)                     SoAd_GetSoConDynOfPCConfig()[(Index)].CloseModeOfSoConDyn = (Value)
#define SoAd_SetModeOfSoConDyn(Index, Value)                          SoAd_GetSoConDynOfPCConfig()[(Index)].ModeOfSoConDyn = (Value)
#define SoAd_SetOpenCloseCounterOfSoConDyn(Index, Value)              SoAd_GetSoConDynOfPCConfig()[(Index)].OpenCloseCounterOfSoConDyn = (Value)
#define SoAd_SetRemAddrDynOfSoConDyn(Index, Value)                    SoAd_GetSoConDynOfPCConfig()[(Index)].RemAddrDynOfSoConDyn = (Value)
#define SoAd_SetRemAddrStateDynOfSoConDyn(Index, Value)               SoAd_GetSoConDynOfPCConfig()[(Index)].RemAddrStateDynOfSoConDyn = (Value)
#define SoAd_SetLocalPortOfSocketDyn(Index, Value)                    SoAd_GetSocketDynOfPCConfig()[(Index)].LocalPortOfSocketDyn = (Value)
#define SoAd_SetSkipBytesOfSocketDyn(Index, Value)                    SoAd_GetSocketDynOfPCConfig()[(Index)].SkipBytesOfSocketDyn = (Value)
#define SoAd_SetSoConTxActiveIdxOfSocketDyn(Index, Value)             SoAd_GetSocketDynOfPCConfig()[(Index)].SoConTxActiveIdxOfSocketDyn = (Value)
#define SoAd_SetSocketIdOfSocketDyn(Index, Value)                     SoAd_GetSocketDynOfPCConfig()[(Index)].SocketIdOfSocketDyn = (Value)
#define SoAd_SetStateOfSocketDyn(Index, Value)                        SoAd_GetSocketDynOfPCConfig()[(Index)].StateOfSocketDyn = (Value)
#define SoAd_SetLenOfTcpTxQueueData(Index, Value)                     SoAd_GetTcpTxQueueDataOfPCConfig()[(Index)].LenOfTcpTxQueueData = (Value)
#define SoAd_SetPduRouteIdxOfTcpTxQueueData(Index, Value)             SoAd_GetTcpTxQueueDataOfPCConfig()[(Index)].PduRouteIdxOfTcpTxQueueData = (Value)
#define SoAd_SetLvlOfTcpTxQueueMgt(Index, Value)                      SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].LvlOfTcpTxQueueMgt = (Value)
#define SoAd_SetTcpTxQueueDataIdxOfTcpTxQueueMgt(Index, Value)        SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].TcpTxQueueDataIdxOfTcpTxQueueMgt = (Value)
#define SoAd_SetTotLenOfTcpTxQueueMgt(Index, Value)                   SoAd_GetTcpTxQueueMgtOfPCConfig()[(Index)].TotLenOfTcpTxQueueMgt = (Value)
#define SoAd_SetLvlOfTimeoutListDyn(Index, Value)                     SoAd_GetTimeoutListDynOfPCConfig()[(Index)].LvlOfTimeoutListDyn = (Value)
#define SoAd_SetNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index, Value)      SoAd_GetTimeoutListNPduUdpTxOfPCConfig()[(Index)].NPduUdpTxIdxOfTimeoutListNPduUdpTx = (Value)
#define SoAd_SetTimeoutOfTimeoutListNPduUdpTx(Index, Value)           SoAd_GetTimeoutListNPduUdpTxOfPCConfig()[(Index)].TimeoutOfTimeoutListNPduUdpTx = (Value)
#define SoAd_SetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index, Value) SoAd_GetTimeoutListNPduUdpTxMapOfPCConfig()[(Index)].TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap = (Value)
#define SoAd_SetSoConIdxOfTimeoutListUdpAlive(Index, Value)           SoAd_GetTimeoutListUdpAliveOfPCConfig()[(Index)].SoConIdxOfTimeoutListUdpAlive = (Value)
#define SoAd_SetTimeoutOfTimeoutListUdpAlive(Index, Value)            SoAd_GetTimeoutListUdpAliveOfPCConfig()[(Index)].TimeoutOfTimeoutListUdpAlive = (Value)
#define SoAd_SetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index, Value) SoAd_GetTimeoutListUdpAliveMapOfPCConfig()[(Index)].TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap = (Value)
#define SoAd_SetTpRxBuffer(Index, Value)                              SoAd_GetTpRxBufferOfPCConfig()[(Index)] = (Value)
#define SoAd_SetTpTxBuffer(Index, Value)                              SoAd_GetTpTxBufferOfPCConfig()[(Index)] = (Value)
#define SoAd_SetTpTxBufferIdxOfTpTxBufferConfigDyn(Index, Value)      SoAd_GetTpTxBufferConfigDynOfPCConfig()[(Index)].TpTxBufferIdxOfTpTxBufferConfigDyn = (Value)
#define SoAd_SetTriggerBuf(Index, Value)                              SoAd_GetTriggerBufOfPCConfig()[(Index)] = (Value)
#define SoAd_SetLengthOfTriggerBufConfigDyn(Index, Value)             SoAd_GetTriggerBufConfigDynOfPCConfig()[(Index)].LengthOfTriggerBufConfigDyn = (Value)
#define SoAd_SetPduRouteIdxOfTriggerBufConfigDyn(Index, Value)        SoAd_GetTriggerBufConfigDynOfPCConfig()[(Index)].PduRouteIdxOfTriggerBufConfigDyn = (Value)
#define SoAd_SetCancelRequestedOfTxMgt(Index, Value)                  SoAd_GetTxMgtOfPCConfig()[(Index)].CancelRequestedOfTxMgt = (Value)
#define SoAd_SetPduRouteDestIdxOfTxMgt(Index, Value)                  SoAd_GetTxMgtOfPCConfig()[(Index)].PduRouteDestIdxOfTxMgt = (Value)
#define SoAd_SetTxBufPtrOfTxMgt(Index, Value)                         SoAd_GetTxMgtOfPCConfig()[(Index)].TxBufPtrOfTxMgt = (Value)
#define SoAd_SetTxBytesLenOfTxMgt(Index, Value)                       SoAd_GetTxMgtOfPCConfig()[(Index)].TxBytesLenOfTxMgt = (Value)
#define SoAd_SetTxBytesPendingOfTxMgt(Index, Value)                   SoAd_GetTxMgtOfPCConfig()[(Index)].TxBytesPendingOfTxMgt = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCGetAddressOfDataMacros  SoAd Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data by the address operator.
  \{
*/ 
#define SoAd_GetAddrIfRxBuffer(Index)                                 (&SoAd_GetIfRxBuffer(Index))
#define SoAd_GetAddrIpFragBuf(Index)                                  (&SoAd_GetIpFragBuf(Index))
#define SoAd_GetAddrMetaDataRxBuf(Index)                              (&SoAd_GetMetaDataRxBuf(Index))
#define SoAd_GetAddrNPduUdpTxBuffer(Index)                            (&SoAd_GetNPduUdpTxBuffer(Index))
#define SoAd_GetAddrRcvRemAddr(Index)                                 (&SoAd_GetRcvRemAddr(Index))
#define SoAd_GetAddrAddrOfRemAddrIpV4(Index)                          (&SoAd_GetAddrOfRemAddrIpV4(Index))
#define SoAd_GetAddrAddrOfRemAddrIpV6(Index)                          (&SoAd_GetAddrOfRemAddrIpV6(Index))
#define SoAd_GetAddrDataPtrOfRxBufStructSeg(Index)                    (&SoAd_GetDataPtrOfRxBufStructSeg(Index))
#define SoAd_GetAddrRemAddrDynOfSoConDyn(Index)                       (&SoAd_GetRemAddrDynOfSoConDyn(Index))
#define SoAd_GetAddrTpRxBuffer(Index)                                 (&SoAd_GetTpRxBuffer(Index))
#define SoAd_GetAddrTpTxBuffer(Index)                                 (&SoAd_GetTpTxBuffer(Index))
#define SoAd_GetAddrTriggerBuf(Index)                                 (&SoAd_GetTriggerBuf(Index))
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCHasMacros  SoAd Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define SoAd_HasBestMatchSoConIdxList()                               (SoAd_GetBestMatchSoConIdxListOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfBestMatchSoConIdxList()                     (TRUE != FALSE)
#define SoAd_HasDhcpEventCbk()                                        (SoAd_GetDhcpEventCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasEventQueue()                                          (SoAd_GetEventQueueOfPCConfig() != NULL_PTR)
#define SoAd_HasBitPatternOfEventQueue()                              (TRUE != FALSE)
#define SoAd_HasLimitOfEventQueue()                                   (TRUE != FALSE)
#define SoAd_HasEventQueueDyn()                                       (SoAd_GetEventQueueDynOfPCConfig() != NULL_PTR)
#define SoAd_HasIdxOfEventQueueDyn()                                  (TRUE != FALSE)
#define SoAd_HasLvlOfEventQueueDyn()                                  (TRUE != FALSE)
#define SoAd_HasEventQueueFlag()                                      (SoAd_GetEventQueueFlagOfPCConfig() != NULL_PTR)
#define SoAd_HasEventQueueIdent()                                     (SoAd_GetEventQueueIdentOfPCConfig() != NULL_PTR)
#define SoAd_HasEventQueueIfTxRouteGrpIdxOfEventQueueIdent()          (TRUE != FALSE)
#define SoAd_HasEventQueueIfTxRouteGrpUsedOfEventQueueIdent()         (TRUE != FALSE)
#define SoAd_HasEventQueueIfUdpPduRouteIdxOfEventQueueIdent()         (TRUE != FALSE)
#define SoAd_HasEventQueueIfUdpPduRouteUsedOfEventQueueIdent()        (TRUE != FALSE)
#define SoAd_HasEventQueueLocalAddrIdxOfEventQueueIdent()             (TRUE != FALSE)
#define SoAd_HasEventQueueLocalAddrUsedOfEventQueueIdent()            (TRUE != FALSE)
#define SoAd_HasEventQueueSockIdxIdxOfEventQueueIdent()               (TRUE != FALSE)
#define SoAd_HasEventQueueSockIdxUsedOfEventQueueIdent()              (TRUE != FALSE)
#define SoAd_HasEventQueueStateSoConIdxOfEventQueueIdent()            (TRUE != FALSE)
#define SoAd_HasEventQueueTcpTxSoConIdxOfEventQueueIdent()            (TRUE != FALSE)
#define SoAd_HasEventQueueTcpTxSoConUsedOfEventQueueIdent()           (TRUE != FALSE)
#define SoAd_HasEventQueueTpRxSoConIdxOfEventQueueIdent()             (TRUE != FALSE)
#define SoAd_HasEventQueueTpRxSoConUsedOfEventQueueIdent()            (TRUE != FALSE)
#define SoAd_HasEventQueueTpTxSoConIdxOfEventQueueIdent()             (TRUE != FALSE)
#define SoAd_HasEventQueueTpTxSoConUsedOfEventQueueIdent()            (TRUE != FALSE)
#define SoAd_HasEventQueueIfTxRouteGrp()                              (SoAd_GetEventQueueIfTxRouteGrpOfPCConfig() != NULL_PTR)
#define SoAd_HasRouteGrpIdxOfEventQueueIfTxRouteGrp()                 (TRUE != FALSE)
#define SoAd_HasEventQueueIfUdpPduRoute()                             (SoAd_GetEventQueueIfUdpPduRouteOfPCConfig() != NULL_PTR)
#define SoAd_HasPduRouteIdxOfEventQueueIfUdpPduRoute()                (TRUE != FALSE)
#define SoAd_HasEventQueueLocalAddr()                                 (SoAd_GetEventQueueLocalAddrOfPCConfig() != NULL_PTR)
#define SoAd_HasLocalAddrIdxOfEventQueueLocalAddr()                   (TRUE != FALSE)
#define SoAd_HasEventQueueSocketIdx()                                 (SoAd_GetEventQueueSocketIdxOfPCConfig() != NULL_PTR)
#define SoAd_HasSocketIdxOfEventQueueSocketIdx()                      (TRUE != FALSE)
#define SoAd_HasEventQueueStateSoCon()                                (SoAd_GetEventQueueStateSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfEventQueueStateSoCon()                      (TRUE != FALSE)
#define SoAd_HasEventQueueTcpTxSoCon()                                (SoAd_GetEventQueueTcpTxSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfEventQueueTcpTxSoCon()                      (TRUE != FALSE)
#define SoAd_HasEventQueueTpRxSoCon()                                 (SoAd_GetEventQueueTpRxSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfEventQueueTpRxSoCon()                       (TRUE != FALSE)
#define SoAd_HasEventQueueTpTxSoCon()                                 (SoAd_GetEventQueueTpTxSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfEventQueueTpTxSoCon()                       (TRUE != FALSE)
#define SoAd_HasIfRxBuffer()                                          (SoAd_GetIfRxBufferOfPCConfig() != NULL_PTR)
#define SoAd_HasIpFragBuf()                                           (SoAd_GetIpFragBufOfPCConfig() != NULL_PTR)
#define SoAd_HasIpFragBufConfig()                                     (SoAd_GetIpFragBufConfigOfPCConfig() != NULL_PTR)
#define SoAd_HasIpFragBufEndIdxOfIpFragBufConfig()                    (TRUE != FALSE)
#define SoAd_HasIpFragBufStartIdxOfIpFragBufConfig()                  (TRUE != FALSE)
#define SoAd_HasIpFragBufConfigDyn()                                  (SoAd_GetIpFragBufConfigDynOfPCConfig() != NULL_PTR)
#define SoAd_HasLengthOfIpFragBufConfigDyn()                          (TRUE != FALSE)
#define SoAd_HasIpFragMgt()                                           (SoAd_GetIpFragMgtOfPCConfig() != NULL_PTR)
#define SoAd_HasIpFragBufConfigIdxOfIpFragMgt()                       (TRUE != FALSE)
#define SoAd_HasLocalAddr()                                           (SoAd_GetLocalAddrOfPCConfig() != NULL_PTR)
#define SoAd_HasAddrIdOfLocalAddr()                                   (TRUE != FALSE)
#define SoAd_HasAddressTypeOfLocalAddr()                              (TRUE != FALSE)
#define SoAd_HasAssignTriggerOfLocalAddr()                            (TRUE != FALSE)
#define SoAd_HasAssignTypeOfLocalAddr()                               (TRUE != FALSE)
#define SoAd_HasDomainOfLocalAddr()                                   (TRUE != FALSE)
#define SoAd_HasTcpIpCtrlIdxOfLocalAddr()                             (TRUE != FALSE)
#define SoAd_HasLocalAddrByTcpIpCtrlInd()                             (SoAd_GetLocalAddrByTcpIpCtrlIndOfPCConfig() != NULL_PTR)
#define SoAd_HasLocalAddrDyn()                                        (SoAd_GetLocalAddrDynOfPCConfig() != NULL_PTR)
#define SoAd_HasIpAddrStateOfLocalAddrDyn()                           (TRUE != FALSE)
#define SoAd_HasLocalAddrIdMap()                                      (SoAd_GetLocalAddrIdMapOfPCConfig() != NULL_PTR)
#define SoAd_HasInvalidHndOfLocalAddrIdMap()                          (TRUE != FALSE)
#define SoAd_HasLocalAddrIdxOfLocalAddrIdMap()                        (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbk()                         (SoAd_GetLocalIpAddrAssignmentChgCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasLocalIpAddrAssignmentChgCbkInd()                      (SoAd_GetLocalIpAddrAssignmentChgCbkIndOfPCConfig() != NULL_PTR)
#define SoAd_HasMaxIfRouteGrpTransmitPduSize()                        (TRUE != FALSE)
#define SoAd_HasMetaDataRxBuf()                                       (SoAd_GetMetaDataRxBufOfPCConfig() != NULL_PTR)
#define SoAd_HasNPduUdpTx()                                           (SoAd_GetNPduUdpTxOfPCConfig() != NULL_PTR)
#define SoAd_HasNPduUdpTxBufferEndIdxOfNPduUdpTx()                    (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBufferStartIdxOfNPduUdpTx()                  (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBufferUsedOfNPduUdpTx()                      (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueueEndIdxOfNPduUdpTx()                     (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueueStartIdxOfNPduUdpTx()                   (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueueUsedOfNPduUdpTx()                       (TRUE != FALSE)
#define SoAd_HasSoConIdxOfNPduUdpTx()                                 (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBuffer()                                     (SoAd_GetNPduUdpTxBufferOfPCConfig() != NULL_PTR)
#define SoAd_HasNPduUdpTxDyn()                                        (SoAd_GetNPduUdpTxDynOfPCConfig() != NULL_PTR)
#define SoAd_HasBufLenOfNPduUdpTxDyn()                                (TRUE != FALSE)
#define SoAd_HasLvlOfNPduUdpTxDyn()                                   (TRUE != FALSE)
#define SoAd_HasRetryCntOfNPduUdpTxDyn()                              (TRUE != FALSE)
#define SoAd_HasTotalLenOfNPduUdpTxDyn()                              (TRUE != FALSE)
#define SoAd_HasTransmissionActiveOfNPduUdpTxDyn()                    (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueue()                                      (SoAd_GetNPduUdpTxQueueOfPCConfig() != NULL_PTR)
#define SoAd_HasCopiedOfNPduUdpTxQueue()                              (TRUE != FALSE)
#define SoAd_HasLenOfNPduUdpTxQueue()                                 (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBufferIdxOfNPduUdpTxQueue()                  (TRUE != FALSE)
#define SoAd_HasPduRouteDestIdxOfNPduUdpTxQueue()                     (TRUE != FALSE)
#define SoAd_HasPduRoute()                                            (SoAd_GetPduRouteOfPCConfig() != NULL_PTR)
#define SoAd_HasAllPduRouteDestWithPduHdrOfPduRoute()                 (TRUE != FALSE)
#define SoAd_HasIfTriggerTransmitModeOfPduRoute()                     (TRUE != FALSE)
#define SoAd_HasMetaDataTxEnabledOfPduRoute()                         (TRUE != FALSE)
#define SoAd_HasPduRouteDestEndIdxOfPduRoute()                        (TRUE != FALSE)
#define SoAd_HasPduRouteDestStartIdxOfPduRoute()                      (TRUE != FALSE)
#define SoAd_HasTxConfEnabledOfPduRoute()                             (TRUE != FALSE)
#define SoAd_HasTxConfPduIdOfPduRoute()                               (TRUE != FALSE)
#define SoAd_HasTxOptimizedOfPduRoute()                               (TRUE != FALSE)
#define SoAd_HasUpperLayerApiOfPduRoute()                             (TRUE != FALSE)
#define SoAd_HasUpperLayerIdxOfPduRoute()                             (TRUE != FALSE)
#define SoAd_HasPduRouteDest()                                        (SoAd_GetPduRouteDestOfPCConfig() != NULL_PTR)
#define SoAd_HasPduRouteIdxOfPduRouteDest()                           (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest()  (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest() (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConByPduRouteDestIndUsedOfPduRouteDest()    (TRUE != FALSE)
#define SoAd_HasSoConIdxOfPduRouteDest()                              (TRUE != FALSE)
#define SoAd_HasTxPduHdrIdOfPduRouteDest()                            (TRUE != FALSE)
#define SoAd_HasTxUdpTriggerModeOfPduRouteDest()                      (TRUE != FALSE)
#define SoAd_HasUdpTriggerTimeoutOfPduRouteDest()                     (TRUE != FALSE)
#define SoAd_HasPduRouteDestBySoConInd()                              (SoAd_GetPduRouteDestBySoConIndOfPCConfig() != NULL_PTR)
#define SoAd_HasPduRouteDestInd()                                     (SoAd_GetPduRouteDestIndOfPCConfig() != NULL_PTR)
#define SoAd_HasPduRouteDyn()                                         (SoAd_GetPduRouteDynOfPCConfig() != NULL_PTR)
#define SoAd_HasPendingTxConfMainOfPduRouteDyn()                      (TRUE != FALSE)
#define SoAd_HasPendingTxConfNumOfPduRouteDyn()                       (TRUE != FALSE)
#define SoAd_HasRcvRemAddr()                                          (SoAd_GetRcvRemAddrOfPCConfig() != NULL_PTR)
#define SoAd_HasRemAddrIpV4()                                         (SoAd_GetRemAddrIpV4OfPCConfig() != NULL_PTR)
#define SoAd_HasAddrOfRemAddrIpV4()                                   (TRUE != FALSE)
#define SoAd_HasPortOfRemAddrIpV4()                                   (TRUE != FALSE)
#define SoAd_HasRemAddrIpV6()                                         (SoAd_GetRemAddrIpV6OfPCConfig() != NULL_PTR)
#define SoAd_HasAddrOfRemAddrIpV6()                                   (TRUE != FALSE)
#define SoAd_HasPortOfRemAddrIpV6()                                   (TRUE != FALSE)
#define SoAd_HasRouteGrp()                                            (SoAd_GetRouteGrpOfPCConfig() != NULL_PTR)
#define SoAd_HasEnabledAtInitOfRouteGrp()                             (TRUE != FALSE)
#define SoAd_HasMultiInstanceOnGrpOfRouteGrp()                        (TRUE != FALSE)
#define SoAd_HasPduRouteDestIndEndIdxOfRouteGrp()                     (TRUE != FALSE)
#define SoAd_HasPduRouteDestIndStartIdxOfRouteGrp()                   (TRUE != FALSE)
#define SoAd_HasPduRouteDestIndUsedOfRouteGrp()                       (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConEndIdxOfRouteGrp()                       (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConStartIdxOfRouteGrp()                     (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConUsedOfRouteGrp()                         (TRUE != FALSE)
#define SoAd_HasSocketRouteIndEndIdxOfRouteGrp()                      (TRUE != FALSE)
#define SoAd_HasSocketRouteIndStartIdxOfRouteGrp()                    (TRUE != FALSE)
#define SoAd_HasSocketRouteIndUsedOfRouteGrp()                        (TRUE != FALSE)
#define SoAd_HasTxTriggerableOfRouteGrp()                             (TRUE != FALSE)
#define SoAd_HasRouteGrpIdMap()                                       (SoAd_GetRouteGrpIdMapOfPCConfig() != NULL_PTR)
#define SoAd_HasInvalidHndOfRouteGrpIdMap()                           (TRUE != FALSE)
#define SoAd_HasRouteGrpIdxOfRouteGrpIdMap()                          (TRUE != FALSE)
#define SoAd_HasRouteGrpSoCon()                                       (SoAd_GetRouteGrpSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasRouteGrpIdxOfRouteGrpSoCon()                          (TRUE != FALSE)
#define SoAd_HasSoConIdxOfRouteGrpSoCon()                             (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConByPduRouteDestInd()                      (SoAd_GetRouteGrpSoConByPduRouteDestIndOfPCConfig() != NULL_PTR)
#define SoAd_HasRouteGrpSoConBySocketRouteDestInd()                   (SoAd_GetRouteGrpSoConBySocketRouteDestIndOfPCConfig() != NULL_PTR)
#define SoAd_HasRouteGrpSoConDyn()                                    (SoAd_GetRouteGrpSoConDynOfPCConfig() != NULL_PTR)
#define SoAd_HasEnabledOfRouteGrpSoConDyn()                           (TRUE != FALSE)
#define SoAd_HasSentOfRouteGrpSoConDyn()                              (TRUE != FALSE)
#define SoAd_HasTriggerOfRouteGrpSoConDyn()                           (TRUE != FALSE)
#define SoAd_HasRxBufStructMgt()                                      (SoAd_GetRxBufStructMgtOfPCConfig() != NULL_PTR)
#define SoAd_HasRxBufStructSegIdxOfRxBufStructMgt()                   (TRUE != FALSE)
#define SoAd_HasRxBufStructSegLvlOfRxBufStructMgt()                   (TRUE != FALSE)
#define SoAd_HasRxBufStructSeg()                                      (SoAd_GetRxBufStructSegOfPCConfig() != NULL_PTR)
#define SoAd_HasDataPtrOfRxBufStructSeg()                             (TRUE != FALSE)
#define SoAd_HasLenOfRxBufStructSeg()                                 (TRUE != FALSE)
#define SoAd_HasRxBufferConfig()                                      (SoAd_GetRxBufferConfigOfPCConfig() != NULL_PTR)
#define SoAd_HasIfRxBufferEndIdxOfRxBufferConfig()                    (TRUE != FALSE)
#define SoAd_HasIfRxBufferStartIdxOfRxBufferConfig()                  (TRUE != FALSE)
#define SoAd_HasIfRxBufferUsedOfRxBufferConfig()                      (TRUE != FALSE)
#define SoAd_HasTpRxBufferEndIdxOfRxBufferConfig()                    (TRUE != FALSE)
#define SoAd_HasTpRxBufferStartIdxOfRxBufferConfig()                  (TRUE != FALSE)
#define SoAd_HasTpRxBufferUsedOfRxBufferConfig()                      (TRUE != FALSE)
#define SoAd_HasRxBufferConfigDyn()                                   (SoAd_GetRxBufferConfigDynOfPCConfig() != NULL_PTR)
#define SoAd_HasIfRxBufferIdxOfRxBufferConfigDyn()                    (TRUE != FALSE)
#define SoAd_HasTpRxBufferIdxOfRxBufferConfigDyn()                    (TRUE != FALSE)
#define SoAd_HasRxMgt()                                               (SoAd_GetRxMgtOfPCConfig() != NULL_PTR)
#define SoAd_HasCancelRequestedOfRxMgt()                              (TRUE != FALSE)
#define SoAd_HasRxBytesPendingOfRxMgt()                               (TRUE != FALSE)
#define SoAd_HasSocketRouteDestIdxOfRxMgt()                           (TRUE != FALSE)
#define SoAd_HasRxPduIdIdMap()                                        (SoAd_GetRxPduIdIdMapOfPCConfig() != NULL_PTR)
#define SoAd_HasInvalidHndOfRxPduIdIdMap()                            (TRUE != FALSE)
#define SoAd_HasSocketRouteDestIdxOfRxPduIdIdMap()                    (TRUE != FALSE)
#define SoAd_HasShutdownFinishedCbk()                                 (SoAd_GetShutdownFinishedCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasSizeOfBestMatchSoConIdxList()                         (TRUE != FALSE)
#define SoAd_HasSizeOfDhcpEventCbk()                                  (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueue()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueDyn()                                 (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueFlag()                                (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIdent()                               (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIfTxRouteGrp()                        (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIfUdpPduRoute()                       (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueLocalAddr()                           (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueSocketIdx()                           (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueStateSoCon()                          (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTcpTxSoCon()                          (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTpRxSoCon()                           (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTpTxSoCon()                           (TRUE != FALSE)
#define SoAd_HasSizeOfIfRxBuffer()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBuf()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBufConfig()                               (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBufConfigDyn()                            (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragMgt()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddr()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrByTcpIpCtrlInd()                       (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrDyn()                                  (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrIdMap()                                (TRUE != FALSE)
#define SoAd_HasSizeOfLocalIpAddrAssignmentChgCbk()                   (TRUE != FALSE)
#define SoAd_HasSizeOfLocalIpAddrAssignmentChgCbkInd()                (TRUE != FALSE)
#define SoAd_HasSizeOfMetaDataRxBuf()                                 (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTx()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxBuffer()                               (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxDyn()                                  (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxQueue()                                (TRUE != FALSE)
#define SoAd_HasSizeOfPduRoute()                                      (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDest()                                  (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDestBySoConInd()                        (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDestInd()                               (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDyn()                                   (TRUE != FALSE)
#define SoAd_HasSizeOfRcvRemAddr()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfRemAddrIpV4()                                   (TRUE != FALSE)
#define SoAd_HasSizeOfRemAddrIpV6()                                   (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrp()                                      (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpIdMap()                                 (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoCon()                                 (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConByPduRouteDestInd()                (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConBySocketRouteDestInd()             (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConDyn()                              (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufStructMgt()                                (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufStructSeg()                                (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufferConfig()                                (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufferConfigDyn()                             (TRUE != FALSE)
#define SoAd_HasSizeOfRxMgt()                                         (TRUE != FALSE)
#define SoAd_HasSizeOfRxPduIdIdMap()                                  (TRUE != FALSE)
#define SoAd_HasSizeOfShutdownFinishedCbk()                           (TRUE != FALSE)
#define SoAd_HasSizeOfSoCon()                                         (TRUE != FALSE)
#define SoAd_HasSizeOfSoConDyn()                                      (TRUE != FALSE)
#define SoAd_HasSizeOfSoConGrp()                                      (TRUE != FALSE)
#define SoAd_HasSizeOfSoConMap()                                      (TRUE != FALSE)
#define SoAd_HasSizeOfSoConModeChgCbk()                               (TRUE != FALSE)
#define SoAd_HasSizeOfSoConModeChgCbkInd()                            (TRUE != FALSE)
#define SoAd_HasSizeOfSocket()                                        (TRUE != FALSE)
#define SoAd_HasSizeOfSocketDyn()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfSocketReportErrorCbk()                          (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRoute()                                   (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRouteDest()                               (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRouteInd()                                (TRUE != FALSE)
#define SoAd_HasSizeOfSocketTcp()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfSocketUdp()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfTcpIpCtrl()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfTcpKeepAliveGloballyEnabled()                   (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTlsSocketCreatedNotificationCbk()            (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueue()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueueData()                                (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueueMgt()                                 (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListDyn()                                (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListIdent()                              (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListNPduUdpTx()                          (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListNPduUdpTxMap()                       (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListUdpAlive()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListUdpAliveMap()                        (TRUE != FALSE)
#define SoAd_HasSizeOfTlsConfig()                                     (TRUE != FALSE)
#define SoAd_HasSizeOfTpRxBuffer()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBuffer()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBufferConfig()                              (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBufferConfigDyn()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBuf()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBufConfig()                              (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBufConfigDyn()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTxMgt()                                         (TRUE != FALSE)
#define SoAd_HasSizeOfTxPduIdMap()                                    (TRUE != FALSE)
#define SoAd_HasSizeOfUpperLayer()                                    (TRUE != FALSE)
#define SoAd_HasSoCon()                                               (SoAd_GetSoConOfPCConfig() != NULL_PTR)
#define SoAd_HasIpFragMgtIdxOfSoCon()                                 (TRUE != FALSE)
#define SoAd_HasIpFragMgtUsedOfSoCon()                                (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon()         (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon()       (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbkIndUsedOfSoCon()           (TRUE != FALSE)
#define SoAd_HasNPduUdpTxIdxOfSoCon()                                 (TRUE != FALSE)
#define SoAd_HasNPduUdpTxUsedOfSoCon()                                (TRUE != FALSE)
#define SoAd_HasPduRouteDestBySoConIndEndIdxOfSoCon()                 (TRUE != FALSE)
#define SoAd_HasPduRouteDestBySoConIndStartIdxOfSoCon()               (TRUE != FALSE)
#define SoAd_HasPduRouteDestBySoConIndUsedOfSoCon()                   (TRUE != FALSE)
#define SoAd_HasRcvRemAddrIdxOfSoCon()                                (TRUE != FALSE)
#define SoAd_HasRcvRemAddrUsedOfSoCon()                               (TRUE != FALSE)
#define SoAd_HasRemAddrIpV4IdxOfSoCon()                               (TRUE != FALSE)
#define SoAd_HasRemAddrIpV4UsedOfSoCon()                              (TRUE != FALSE)
#define SoAd_HasRemAddrIpV6IdxOfSoCon()                               (TRUE != FALSE)
#define SoAd_HasRemAddrIpV6UsedOfSoCon()                              (TRUE != FALSE)
#define SoAd_HasRemAddrStateOfSoCon()                                 (TRUE != FALSE)
#define SoAd_HasRxBufStructMgtIdxOfSoCon()                            (TRUE != FALSE)
#define SoAd_HasRxBufStructMgtUsedOfSoCon()                           (TRUE != FALSE)
#define SoAd_HasRxBufStructSegEndIdxOfSoCon()                         (TRUE != FALSE)
#define SoAd_HasRxBufStructSegStartIdxOfSoCon()                       (TRUE != FALSE)
#define SoAd_HasRxBufStructSegUsedOfSoCon()                           (TRUE != FALSE)
#define SoAd_HasRxBufferConfigIdxOfSoCon()                            (TRUE != FALSE)
#define SoAd_HasRxBufferConfigUsedOfSoCon()                           (TRUE != FALSE)
#define SoAd_HasRxMgtIdxOfSoCon()                                     (TRUE != FALSE)
#define SoAd_HasRxMgtUsedOfSoCon()                                    (TRUE != FALSE)
#define SoAd_HasSoConGrpIdxOfSoCon()                                  (TRUE != FALSE)
#define SoAd_HasSoConIdOfSoCon()                                      (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbkIndEndIdxOfSoCon()                     (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbkIndStartIdxOfSoCon()                   (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbkIndUsedOfSoCon()                       (TRUE != FALSE)
#define SoAd_HasSocketIdxOfSoCon()                                    (TRUE != FALSE)
#define SoAd_HasSocketRouteEndIdxOfSoCon()                            (TRUE != FALSE)
#define SoAd_HasSocketRouteStartIdxOfSoCon()                          (TRUE != FALSE)
#define SoAd_HasSocketRouteUsedOfSoCon()                              (TRUE != FALSE)
#define SoAd_HasTcpTxQueueIdxOfSoCon()                                (TRUE != FALSE)
#define SoAd_HasTcpTxQueueUsedOfSoCon()                               (TRUE != FALSE)
#define SoAd_HasTlsConfigIdxOfSoCon()                                 (TRUE != FALSE)
#define SoAd_HasTlsConfigUsedOfSoCon()                                (TRUE != FALSE)
#define SoAd_HasTpTxBufferConfigIdxOfSoCon()                          (TRUE != FALSE)
#define SoAd_HasTpTxBufferConfigUsedOfSoCon()                         (TRUE != FALSE)
#define SoAd_HasTxMgtIdxOfSoCon()                                     (TRUE != FALSE)
#define SoAd_HasTxMgtUsedOfSoCon()                                    (TRUE != FALSE)
#define SoAd_HasSoConDyn()                                            (SoAd_GetSoConDynOfPCConfig() != NULL_PTR)
#define SoAd_HasAbortOfSoConDyn()                                     (TRUE != FALSE)
#define SoAd_HasCloseModeOfSoConDyn()                                 (TRUE != FALSE)
#define SoAd_HasModeOfSoConDyn()                                      (TRUE != FALSE)
#define SoAd_HasOpenCloseCounterOfSoConDyn()                          (TRUE != FALSE)
#define SoAd_HasRemAddrDynOfSoConDyn()                                (TRUE != FALSE)
#define SoAd_HasRemAddrStateDynOfSoConDyn()                           (TRUE != FALSE)
#define SoAd_HasSoConGrp()                                            (SoAd_GetSoConGrpOfPCConfig() != NULL_PTR)
#define SoAd_HasBestMatchWithPduHeaderEnabledOfSoConGrp()             (TRUE != FALSE)
#define SoAd_HasBestMatchWithSockRouteEnabledOfSoConGrp()             (TRUE != FALSE)
#define SoAd_HasFramePriorityOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasLocalAddrIdxOfSoConGrp()                              (TRUE != FALSE)
#define SoAd_HasLocalAddrUsedOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasLocalPortOfSoConGrp()                                 (TRUE != FALSE)
#define SoAd_HasMsgAcceptFilterEnabledOfSoConGrp()                    (TRUE != FALSE)
#define SoAd_HasPduHdrEnabledOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasSoConEndIdxOfSoConGrp()                               (TRUE != FALSE)
#define SoAd_HasSoConStartIdxOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasSockAutoSoConSetupKeepOnlineOfSoConGrp()              (TRUE != FALSE)
#define SoAd_HasSockAutoSoConSetupOfSoConGrp()                        (TRUE != FALSE)
#define SoAd_HasSocketIdxOfSoConGrp()                                 (TRUE != FALSE)
#define SoAd_HasSocketTcpIdxOfSoConGrp()                              (TRUE != FALSE)
#define SoAd_HasSocketTcpUsedOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasSocketUdpIdxOfSoConGrp()                              (TRUE != FALSE)
#define SoAd_HasSocketUdpUsedOfSoConGrp()                             (TRUE != FALSE)
#define SoAd_HasSocketUsedOfSoConGrp()                                (TRUE != FALSE)
#define SoAd_HasSoConMap()                                            (SoAd_GetSoConMapOfPCConfig() != NULL_PTR)
#define SoAd_HasInvalidHndOfSoConMap()                                (TRUE != FALSE)
#define SoAd_HasSoConIdxOfSoConMap()                                  (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbk()                                     (SoAd_GetSoConModeChgCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConModeChgCbkInd()                                  (SoAd_GetSoConModeChgCbkIndOfPCConfig() != NULL_PTR)
#define SoAd_HasSocket()                                              (SoAd_GetSocketOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConEndIdxOfSocket()                                 (TRUE != FALSE)
#define SoAd_HasSoConStartIdxOfSocket()                               (TRUE != FALSE)
#define SoAd_HasSocketDyn()                                           (SoAd_GetSocketDynOfPCConfig() != NULL_PTR)
#define SoAd_HasLocalPortOfSocketDyn()                                (TRUE != FALSE)
#define SoAd_HasSkipBytesOfSocketDyn()                                (TRUE != FALSE)
#define SoAd_HasSoConTxActiveIdxOfSocketDyn()                         (TRUE != FALSE)
#define SoAd_HasSocketIdOfSocketDyn()                                 (TRUE != FALSE)
#define SoAd_HasStateOfSocketDyn()                                    (TRUE != FALSE)
#define SoAd_HasSocketReportErrorCbk()                                (SoAd_GetSocketReportErrorCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasSocketRoute()                                         (SoAd_GetSocketRouteOfPCConfig() != NULL_PTR)
#define SoAd_HasMetaDataRxEnabledOfSocketRoute()                      (TRUE != FALSE)
#define SoAd_HasRxPduHdrIdOfSocketRoute()                             (TRUE != FALSE)
#define SoAd_HasSoConIdxOfSocketRoute()                               (TRUE != FALSE)
#define SoAd_HasSocketRouteDestEndIdxOfSocketRoute()                  (TRUE != FALSE)
#define SoAd_HasSocketRouteDestStartIdxOfSocketRoute()                (TRUE != FALSE)
#define SoAd_HasUpperLayerApiOfSocketRoute()                          (TRUE != FALSE)
#define SoAd_HasSocketRouteDest()                                     (SoAd_GetSocketRouteDestOfPCConfig() != NULL_PTR)
#define SoAd_HasRouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDest() (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest() (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConBySocketRouteDestIndUsedOfSocketRouteDest() (TRUE != FALSE)
#define SoAd_HasRxPduIdOfSocketRouteDest()                            (TRUE != FALSE)
#define SoAd_HasSocketRouteIdxOfSocketRouteDest()                     (TRUE != FALSE)
#define SoAd_HasUpperLayerIdxOfSocketRouteDest()                      (TRUE != FALSE)
#define SoAd_HasSocketRouteInd()                                      (SoAd_GetSocketRouteIndOfPCConfig() != NULL_PTR)
#define SoAd_HasSocketTcp()                                           (SoAd_GetSocketTcpOfPCConfig() != NULL_PTR)
#define SoAd_HasImmedTpTxConfOfSocketTcp()                            (TRUE != FALSE)
#define SoAd_HasTcpInitiateOfSocketTcp()                              (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveIntervalOfSocketTcp()                     (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveOfSocketTcp()                             (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveProbesMaxOfSocketTcp()                    (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveTimeOfSocketTcp()                         (TRUE != FALSE)
#define SoAd_HasTcpNoDelayOfSocketTcp()                               (TRUE != FALSE)
#define SoAd_HasTcpRxBufMinOfSocketTcp()                              (TRUE != FALSE)
#define SoAd_HasTcpTxBufMinOfSocketTcp()                              (TRUE != FALSE)
#define SoAd_HasSocketUdp()                                           (SoAd_GetSocketUdpOfPCConfig() != NULL_PTR)
#define SoAd_HasAliveTimeoutMaxCntOfSocketUdp()                       (TRUE != FALSE)
#define SoAd_HasImmedIfTxConfListSizeOfSocketUdp()                    (TRUE != FALSE)
#define SoAd_HasImmedIfTxConfOfSocketUdp()                            (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBufferMinOfSocketUdp()                       (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueueSizeOfSocketUdp()                       (TRUE != FALSE)
#define SoAd_HasRetryQueueLimitOfSocketUdp()                          (TRUE != FALSE)
#define SoAd_HasUdpListenOnlyOfSocketUdp()                            (TRUE != FALSE)
#define SoAd_HasUdpStrictHdrLenCheckEnabledOfSocketUdp()              (TRUE != FALSE)
#define SoAd_HasUdpTriggerTimeoutOfSocketUdp()                        (TRUE != FALSE)
#define SoAd_HasTcpIpCtrl()                                           (SoAd_GetTcpIpCtrlOfPCConfig() != NULL_PTR)
#define SoAd_HasLocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl()            (TRUE != FALSE)
#define SoAd_HasLocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl()          (TRUE != FALSE)
#define SoAd_HasLocalAddrByTcpIpCtrlIndUsedOfTcpIpCtrl()              (TRUE != FALSE)
#define SoAd_HasRetryEnabledOfTcpIpCtrl()                             (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveGloballyEnabled()                         (SoAd_GetTcpKeepAliveGloballyEnabledOfPCConfig() != NULL_PTR)
#define SoAd_HasTcpTlsSocketCreatedNotificationCbk()                  (SoAd_GetTcpTlsSocketCreatedNotificationCbkOfPCConfig() != NULL_PTR)
#define SoAd_HasTcpTxQueue()                                          (SoAd_GetTcpTxQueueOfPCConfig() != NULL_PTR)
#define SoAd_HasTcpTxQueueDataEndIdxOfTcpTxQueue()                    (TRUE != FALSE)
#define SoAd_HasTcpTxQueueDataStartIdxOfTcpTxQueue()                  (TRUE != FALSE)
#define SoAd_HasTcpTxQueueData()                                      (SoAd_GetTcpTxQueueDataOfPCConfig() != NULL_PTR)
#define SoAd_HasLenOfTcpTxQueueData()                                 (TRUE != FALSE)
#define SoAd_HasPduRouteIdxOfTcpTxQueueData()                         (TRUE != FALSE)
#define SoAd_HasTcpTxQueueMgt()                                       (SoAd_GetTcpTxQueueMgtOfPCConfig() != NULL_PTR)
#define SoAd_HasLvlOfTcpTxQueueMgt()                                  (TRUE != FALSE)
#define SoAd_HasTcpTxQueueDataIdxOfTcpTxQueueMgt()                    (TRUE != FALSE)
#define SoAd_HasTotLenOfTcpTxQueueMgt()                               (TRUE != FALSE)
#define SoAd_HasTimeoutListDyn()                                      (SoAd_GetTimeoutListDynOfPCConfig() != NULL_PTR)
#define SoAd_HasLvlOfTimeoutListDyn()                                 (TRUE != FALSE)
#define SoAd_HasTimeoutListIdent()                                    (SoAd_GetTimeoutListIdentOfPCConfig() != NULL_PTR)
#define SoAd_HasTimeoutListDynNPduUdpTxIdxOfTimeoutListIdent()        (TRUE != FALSE)
#define SoAd_HasTimeoutListDynNPduUdpTxUsedOfTimeoutListIdent()       (TRUE != FALSE)
#define SoAd_HasTimeoutListDynUdpAliveIdxOfTimeoutListIdent()         (TRUE != FALSE)
#define SoAd_HasTimeoutListDynUdpAliveUsedOfTimeoutListIdent()        (TRUE != FALSE)
#define SoAd_HasTimeoutListNPduUdpTx()                                (SoAd_GetTimeoutListNPduUdpTxOfPCConfig() != NULL_PTR)
#define SoAd_HasNPduUdpTxIdxOfTimeoutListNPduUdpTx()                  (TRUE != FALSE)
#define SoAd_HasTimeoutOfTimeoutListNPduUdpTx()                       (TRUE != FALSE)
#define SoAd_HasTimeoutListNPduUdpTxMap()                             (SoAd_GetTimeoutListNPduUdpTxMapOfPCConfig() != NULL_PTR)
#define SoAd_HasTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap()    (TRUE != FALSE)
#define SoAd_HasTimeoutListUdpAlive()                                 (SoAd_GetTimeoutListUdpAliveOfPCConfig() != NULL_PTR)
#define SoAd_HasSoConIdxOfTimeoutListUdpAlive()                       (TRUE != FALSE)
#define SoAd_HasTimeoutOfTimeoutListUdpAlive()                        (TRUE != FALSE)
#define SoAd_HasTimeoutListUdpAliveMap()                              (SoAd_GetTimeoutListUdpAliveMapOfPCConfig() != NULL_PTR)
#define SoAd_HasTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap()      (TRUE != FALSE)
#define SoAd_HasTlsConfig()                                           (SoAd_GetTlsConfigOfPCConfig() != NULL_PTR)
#define SoAd_HasRxBufSizeOfTlsConfig()                                (TRUE != FALSE)
#define SoAd_HasTcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig()    (TRUE != FALSE)
#define SoAd_HasTcpTlsSocketCreatedNotificationCbkUsedOfTlsConfig()   (TRUE != FALSE)
#define SoAd_HasTxBufSizeOfTlsConfig()                                (TRUE != FALSE)
#define SoAd_HasTpRxBuffer()                                          (SoAd_GetTpRxBufferOfPCConfig() != NULL_PTR)
#define SoAd_HasTpTxBuffer()                                          (SoAd_GetTpTxBufferOfPCConfig() != NULL_PTR)
#define SoAd_HasTpTxBufferConfig()                                    (SoAd_GetTpTxBufferConfigOfPCConfig() != NULL_PTR)
#define SoAd_HasTpTxBufferEndIdxOfTpTxBufferConfig()                  (TRUE != FALSE)
#define SoAd_HasTpTxBufferStartIdxOfTpTxBufferConfig()                (TRUE != FALSE)
#define SoAd_HasTpTxBufferUsedOfTpTxBufferConfig()                    (TRUE != FALSE)
#define SoAd_HasTpTxBufferConfigDyn()                                 (SoAd_GetTpTxBufferConfigDynOfPCConfig() != NULL_PTR)
#define SoAd_HasTpTxBufferIdxOfTpTxBufferConfigDyn()                  (TRUE != FALSE)
#define SoAd_HasTriggerBuf()                                          (SoAd_GetTriggerBufOfPCConfig() != NULL_PTR)
#define SoAd_HasTriggerBufConfig()                                    (SoAd_GetTriggerBufConfigOfPCConfig() != NULL_PTR)
#define SoAd_HasTriggerBufEndIdxOfTriggerBufConfig()                  (TRUE != FALSE)
#define SoAd_HasTriggerBufStartIdxOfTriggerBufConfig()                (TRUE != FALSE)
#define SoAd_HasTriggerBufConfigDyn()                                 (SoAd_GetTriggerBufConfigDynOfPCConfig() != NULL_PTR)
#define SoAd_HasLengthOfTriggerBufConfigDyn()                         (TRUE != FALSE)
#define SoAd_HasPduRouteIdxOfTriggerBufConfigDyn()                    (TRUE != FALSE)
#define SoAd_HasTxMgt()                                               (SoAd_GetTxMgtOfPCConfig() != NULL_PTR)
#define SoAd_HasCancelRequestedOfTxMgt()                              (TRUE != FALSE)
#define SoAd_HasPduRouteDestIdxOfTxMgt()                              (TRUE != FALSE)
#define SoAd_HasTxBufPtrOfTxMgt()                                     (TRUE != FALSE)
#define SoAd_HasTxBytesLenOfTxMgt()                                   (TRUE != FALSE)
#define SoAd_HasTxBytesPendingOfTxMgt()                               (TRUE != FALSE)
#define SoAd_HasTxPduIdMap()                                          (SoAd_GetTxPduIdMapOfPCConfig() != NULL_PTR)
#define SoAd_HasInvalidHndOfTxPduIdMap()                              (TRUE != FALSE)
#define SoAd_HasPduRouteIdxOfTxPduIdMap()                             (TRUE != FALSE)
#define SoAd_HasUpperLayer()                                          (SoAd_GetUpperLayerOfPCConfig() != NULL_PTR)
#define SoAd_HasIfRxIndicationCbkOfUpperLayer()                       (TRUE != FALSE)
#define SoAd_HasIfTriggerTransmitCbkOfUpperLayer()                    (TRUE != FALSE)
#define SoAd_HasIfTxConfirmationCbkOfUpperLayer()                     (TRUE != FALSE)
#define SoAd_HasTpCopyRxDataCbkOfUpperLayer()                         (TRUE != FALSE)
#define SoAd_HasTpCopyRxDataConstCbkOfUpperLayer()                    (TRUE != FALSE)
#define SoAd_HasTpCopyTxDataCbkOfUpperLayer()                         (TRUE != FALSE)
#define SoAd_HasTpCopyTxDataConstCbkOfUpperLayer()                    (TRUE != FALSE)
#define SoAd_HasTpRxIndicationCbkOfUpperLayer()                       (TRUE != FALSE)
#define SoAd_HasTpStartOfReceptionCbkOfUpperLayer()                   (TRUE != FALSE)
#define SoAd_HasTpStartOfReceptionConstCbkOfUpperLayer()              (TRUE != FALSE)
#define SoAd_HasTpTxConfirmationCbkOfUpperLayer()                     (TRUE != FALSE)
#define SoAd_HasPCConfig()                                            (TRUE != FALSE)
#define SoAd_HasBestMatchSoConIdxListOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasDhcpEventCbkOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasEventQueueDynOfPCConfig()                             (TRUE != FALSE)
#define SoAd_HasEventQueueFlagOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasEventQueueIdentOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasEventQueueIfTxRouteGrpOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasEventQueueIfUdpPduRouteOfPCConfig()                   (TRUE != FALSE)
#define SoAd_HasEventQueueLocalAddrOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasEventQueueOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasEventQueueSocketIdxOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasEventQueueStateSoConOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasEventQueueTcpTxSoConOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasEventQueueTpRxSoConOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasEventQueueTpTxSoConOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasIfRxBufferOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasIpFragBufConfigDynOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasIpFragBufConfigOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasIpFragBufOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasIpFragMgtOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasLocalAddrByTcpIpCtrlIndOfPCConfig()                   (TRUE != FALSE)
#define SoAd_HasLocalAddrDynOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasLocalAddrIdMapOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasLocalAddrOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbkIndOfPCConfig()            (TRUE != FALSE)
#define SoAd_HasLocalIpAddrAssignmentChgCbkOfPCConfig()               (TRUE != FALSE)
#define SoAd_HasMaxIfRouteGrpTransmitPduSizeOfPCConfig()              (TRUE != FALSE)
#define SoAd_HasMetaDataRxBufOfPCConfig()                             (TRUE != FALSE)
#define SoAd_HasNPduUdpTxBufferOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasNPduUdpTxDynOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasNPduUdpTxOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasNPduUdpTxQueueOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasPduRouteDestBySoConIndOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasPduRouteDestIndOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasPduRouteDestOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasPduRouteDynOfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasPduRouteOfPCConfig()                                  (TRUE != FALSE)
#define SoAd_HasRcvRemAddrOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasRemAddrIpV4OfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasRemAddrIpV6OfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasRouteGrpIdMapOfPCConfig()                             (TRUE != FALSE)
#define SoAd_HasRouteGrpOfPCConfig()                                  (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConByPduRouteDestIndOfPCConfig()            (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConBySocketRouteDestIndOfPCConfig()         (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConDynOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasRouteGrpSoConOfPCConfig()                             (TRUE != FALSE)
#define SoAd_HasRxBufStructMgtOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasRxBufStructSegOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasRxBufferConfigDynOfPCConfig()                         (TRUE != FALSE)
#define SoAd_HasRxBufferConfigOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasRxMgtOfPCConfig()                                     (TRUE != FALSE)
#define SoAd_HasRxPduIdIdMapOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasShutdownFinishedCbkOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfBestMatchSoConIdxListOfPCConfig()               (TRUE != FALSE)
#define SoAd_HasSizeOfDhcpEventCbkOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueDynOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueFlagOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIdentOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIfTxRouteGrpOfPCConfig()              (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueIfUdpPduRouteOfPCConfig()             (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueLocalAddrOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueSocketIdxOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueStateSoConOfPCConfig()                (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTcpTxSoConOfPCConfig()                (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTpRxSoConOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfEventQueueTpTxSoConOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfIfRxBufferOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBufConfigDynOfPCConfig()                  (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBufConfigOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragBufOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfIpFragMgtOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrByTcpIpCtrlIndOfPCConfig()             (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrDynOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrIdMapOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfLocalAddrOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfLocalIpAddrAssignmentChgCbkIndOfPCConfig()      (TRUE != FALSE)
#define SoAd_HasSizeOfLocalIpAddrAssignmentChgCbkOfPCConfig()         (TRUE != FALSE)
#define SoAd_HasSizeOfMetaDataRxBufOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxBufferOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxDynOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfNPduUdpTxQueueOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDestBySoConIndOfPCConfig()              (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDestIndOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDestOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteDynOfPCConfig()                         (TRUE != FALSE)
#define SoAd_HasSizeOfPduRouteOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSizeOfRcvRemAddrOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfRemAddrIpV4OfPCConfig()                         (TRUE != FALSE)
#define SoAd_HasSizeOfRemAddrIpV6OfPCConfig()                         (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpIdMapOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConByPduRouteDestIndOfPCConfig()      (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConBySocketRouteDestIndOfPCConfig()   (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConDynOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasSizeOfRouteGrpSoConOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufStructMgtOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufStructSegOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufferConfigDynOfPCConfig()                   (TRUE != FALSE)
#define SoAd_HasSizeOfRxBufferConfigOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfRxMgtOfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasSizeOfRxPduIdIdMapOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSizeOfShutdownFinishedCbkOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfSoConDynOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSizeOfSoConGrpOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSizeOfSoConMapOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSizeOfSoConModeChgCbkIndOfPCConfig()                  (TRUE != FALSE)
#define SoAd_HasSizeOfSoConModeChgCbkOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfSoConOfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasSizeOfSocketDynOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfSocketOfPCConfig()                              (TRUE != FALSE)
#define SoAd_HasSizeOfSocketReportErrorCbkOfPCConfig()                (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRouteDestOfPCConfig()                     (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRouteIndOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfSocketRouteOfPCConfig()                         (TRUE != FALSE)
#define SoAd_HasSizeOfSocketTcpOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfSocketUdpOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTcpIpCtrlOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTcpKeepAliveGloballyEnabledOfPCConfig()         (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTlsSocketCreatedNotificationCbkOfPCConfig()  (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueueDataOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueueMgtOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasSizeOfTcpTxQueueOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListDynOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListIdentOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListNPduUdpTxMapOfPCConfig()             (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListNPduUdpTxOfPCConfig()                (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListUdpAliveMapOfPCConfig()              (TRUE != FALSE)
#define SoAd_HasSizeOfTimeoutListUdpAliveOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfTlsConfigOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSizeOfTpRxBufferOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBufferConfigDynOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBufferConfigOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasSizeOfTpTxBufferOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBufConfigDynOfPCConfig()                 (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBufConfigOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasSizeOfTriggerBufOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfTxMgtOfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasSizeOfTxPduIdMapOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSizeOfUpperLayerOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasSoConDynOfPCConfig()                                  (TRUE != FALSE)
#define SoAd_HasSoConGrpOfPCConfig()                                  (TRUE != FALSE)
#define SoAd_HasSoConMapOfPCConfig()                                  (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbkIndOfPCConfig()                        (TRUE != FALSE)
#define SoAd_HasSoConModeChgCbkOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSoConOfPCConfig()                                     (TRUE != FALSE)
#define SoAd_HasSocketDynOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasSocketOfPCConfig()                                    (TRUE != FALSE)
#define SoAd_HasSocketReportErrorCbkOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasSocketRouteDestOfPCConfig()                           (TRUE != FALSE)
#define SoAd_HasSocketRouteIndOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasSocketRouteOfPCConfig()                               (TRUE != FALSE)
#define SoAd_HasSocketTcpOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasSocketUdpOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasTcpIpCtrlOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasTcpKeepAliveGloballyEnabledOfPCConfig()               (TRUE != FALSE)
#define SoAd_HasTcpTlsSocketCreatedNotificationCbkOfPCConfig()        (TRUE != FALSE)
#define SoAd_HasTcpTxQueueDataOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasTcpTxQueueMgtOfPCConfig()                             (TRUE != FALSE)
#define SoAd_HasTcpTxQueueOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasTimeoutListDynOfPCConfig()                            (TRUE != FALSE)
#define SoAd_HasTimeoutListIdentOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasTimeoutListNPduUdpTxMapOfPCConfig()                   (TRUE != FALSE)
#define SoAd_HasTimeoutListNPduUdpTxOfPCConfig()                      (TRUE != FALSE)
#define SoAd_HasTimeoutListUdpAliveMapOfPCConfig()                    (TRUE != FALSE)
#define SoAd_HasTimeoutListUdpAliveOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasTlsConfigOfPCConfig()                                 (TRUE != FALSE)
#define SoAd_HasTpRxBufferOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasTpTxBufferConfigDynOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasTpTxBufferConfigOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasTpTxBufferOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasTriggerBufConfigDynOfPCConfig()                       (TRUE != FALSE)
#define SoAd_HasTriggerBufConfigOfPCConfig()                          (TRUE != FALSE)
#define SoAd_HasTriggerBufOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasTxMgtOfPCConfig()                                     (TRUE != FALSE)
#define SoAd_HasTxPduIdMapOfPCConfig()                                (TRUE != FALSE)
#define SoAd_HasUpperLayerOfPCConfig()                                (TRUE != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCIncrementDataMacros  SoAd Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/ 
#define SoAd_IncSoConIdxOfBestMatchSoConIdxList(Index)                SoAd_GetSoConIdxOfBestMatchSoConIdxList(Index)++
#define SoAd_IncIdxOfEventQueueDyn(Index)                             SoAd_GetIdxOfEventQueueDyn(Index)++
#define SoAd_IncLvlOfEventQueueDyn(Index)                             SoAd_GetLvlOfEventQueueDyn(Index)++
#define SoAd_IncEventQueueFlag(Index)                                 SoAd_GetEventQueueFlag(Index)++
#define SoAd_IncRouteGrpIdxOfEventQueueIfTxRouteGrp(Index)            SoAd_GetRouteGrpIdxOfEventQueueIfTxRouteGrp(Index)++
#define SoAd_IncPduRouteIdxOfEventQueueIfUdpPduRoute(Index)           SoAd_GetPduRouteIdxOfEventQueueIfUdpPduRoute(Index)++
#define SoAd_IncLocalAddrIdxOfEventQueueLocalAddr(Index)              SoAd_GetLocalAddrIdxOfEventQueueLocalAddr(Index)++
#define SoAd_IncSocketIdxOfEventQueueSocketIdx(Index)                 SoAd_GetSocketIdxOfEventQueueSocketIdx(Index)++
#define SoAd_IncSoConIdxOfEventQueueStateSoCon(Index)                 SoAd_GetSoConIdxOfEventQueueStateSoCon(Index)++
#define SoAd_IncSoConIdxOfEventQueueTcpTxSoCon(Index)                 SoAd_GetSoConIdxOfEventQueueTcpTxSoCon(Index)++
#define SoAd_IncSoConIdxOfEventQueueTpRxSoCon(Index)                  SoAd_GetSoConIdxOfEventQueueTpRxSoCon(Index)++
#define SoAd_IncSoConIdxOfEventQueueTpTxSoCon(Index)                  SoAd_GetSoConIdxOfEventQueueTpTxSoCon(Index)++
#define SoAd_IncIfRxBuffer(Index)                                     SoAd_GetIfRxBuffer(Index)++
#define SoAd_IncIpFragBuf(Index)                                      SoAd_GetIpFragBuf(Index)++
#define SoAd_IncLengthOfIpFragBufConfigDyn(Index)                     SoAd_GetLengthOfIpFragBufConfigDyn(Index)++
#define SoAd_IncIpFragBufConfigIdxOfIpFragMgt(Index)                  SoAd_GetIpFragBufConfigIdxOfIpFragMgt(Index)++
#define SoAd_IncIpAddrStateOfLocalAddrDyn(Index)                      SoAd_GetIpAddrStateOfLocalAddrDyn(Index)++
#define SoAd_IncMetaDataRxBuf(Index)                                  SoAd_GetMetaDataRxBuf(Index)++
#define SoAd_IncNPduUdpTxBuffer(Index)                                SoAd_GetNPduUdpTxBuffer(Index)++
#define SoAd_IncBufLenOfNPduUdpTxDyn(Index)                           SoAd_GetBufLenOfNPduUdpTxDyn(Index)++
#define SoAd_IncLvlOfNPduUdpTxDyn(Index)                              SoAd_GetLvlOfNPduUdpTxDyn(Index)++
#define SoAd_IncRetryCntOfNPduUdpTxDyn(Index)                         SoAd_GetRetryCntOfNPduUdpTxDyn(Index)++
#define SoAd_IncTotalLenOfNPduUdpTxDyn(Index)                         SoAd_GetTotalLenOfNPduUdpTxDyn(Index)++
#define SoAd_IncLenOfNPduUdpTxQueue(Index)                            SoAd_GetLenOfNPduUdpTxQueue(Index)++
#define SoAd_IncNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index)             SoAd_GetNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index)++
#define SoAd_IncPduRouteDestIdxOfNPduUdpTxQueue(Index)                SoAd_GetPduRouteDestIdxOfNPduUdpTxQueue(Index)++
#define SoAd_IncPendingTxConfNumOfPduRouteDyn(Index)                  SoAd_GetPendingTxConfNumOfPduRouteDyn(Index)++
#define SoAd_IncRcvRemAddr(Index)                                     SoAd_GetRcvRemAddr(Index)++
#define SoAd_IncRxBufStructSegIdxOfRxBufStructMgt(Index)              SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(Index)++
#define SoAd_IncRxBufStructSegLvlOfRxBufStructMgt(Index)              SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(Index)++
#define SoAd_IncDataPtrOfRxBufStructSeg(Index)                        SoAd_GetDataPtrOfRxBufStructSeg(Index)++
#define SoAd_IncLenOfRxBufStructSeg(Index)                            SoAd_GetLenOfRxBufStructSeg(Index)++
#define SoAd_IncIfRxBufferIdxOfRxBufferConfigDyn(Index)               SoAd_GetIfRxBufferIdxOfRxBufferConfigDyn(Index)++
#define SoAd_IncTpRxBufferIdxOfRxBufferConfigDyn(Index)               SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(Index)++
#define SoAd_IncRxBytesPendingOfRxMgt(Index)                          SoAd_GetRxBytesPendingOfRxMgt(Index)++
#define SoAd_IncSocketRouteDestIdxOfRxMgt(Index)                      SoAd_GetSocketRouteDestIdxOfRxMgt(Index)++
#define SoAd_IncCloseModeOfSoConDyn(Index)                            SoAd_GetCloseModeOfSoConDyn(Index)++
#define SoAd_IncModeOfSoConDyn(Index)                                 SoAd_GetModeOfSoConDyn(Index)++
#define SoAd_IncOpenCloseCounterOfSoConDyn(Index)                     SoAd_GetOpenCloseCounterOfSoConDyn(Index)++
#define SoAd_IncRemAddrDynOfSoConDyn(Index)                           SoAd_GetRemAddrDynOfSoConDyn(Index)++
#define SoAd_IncRemAddrStateDynOfSoConDyn(Index)                      SoAd_GetRemAddrStateDynOfSoConDyn(Index)++
#define SoAd_IncLocalPortOfSocketDyn(Index)                           SoAd_GetLocalPortOfSocketDyn(Index)++
#define SoAd_IncSkipBytesOfSocketDyn(Index)                           SoAd_GetSkipBytesOfSocketDyn(Index)++
#define SoAd_IncSoConTxActiveIdxOfSocketDyn(Index)                    SoAd_GetSoConTxActiveIdxOfSocketDyn(Index)++
#define SoAd_IncSocketIdOfSocketDyn(Index)                            SoAd_GetSocketIdOfSocketDyn(Index)++
#define SoAd_IncStateOfSocketDyn(Index)                               SoAd_GetStateOfSocketDyn(Index)++
#define SoAd_IncLenOfTcpTxQueueData(Index)                            SoAd_GetLenOfTcpTxQueueData(Index)++
#define SoAd_IncPduRouteIdxOfTcpTxQueueData(Index)                    SoAd_GetPduRouteIdxOfTcpTxQueueData(Index)++
#define SoAd_IncLvlOfTcpTxQueueMgt(Index)                             SoAd_GetLvlOfTcpTxQueueMgt(Index)++
#define SoAd_IncTcpTxQueueDataIdxOfTcpTxQueueMgt(Index)               SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(Index)++
#define SoAd_IncTotLenOfTcpTxQueueMgt(Index)                          SoAd_GetTotLenOfTcpTxQueueMgt(Index)++
#define SoAd_IncLvlOfTimeoutListDyn(Index)                            SoAd_GetLvlOfTimeoutListDyn(Index)++
#define SoAd_IncNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index)             SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index)++
#define SoAd_IncTimeoutOfTimeoutListNPduUdpTx(Index)                  SoAd_GetTimeoutOfTimeoutListNPduUdpTx(Index)++
#define SoAd_IncTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index) SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index)++
#define SoAd_IncSoConIdxOfTimeoutListUdpAlive(Index)                  SoAd_GetSoConIdxOfTimeoutListUdpAlive(Index)++
#define SoAd_IncTimeoutOfTimeoutListUdpAlive(Index)                   SoAd_GetTimeoutOfTimeoutListUdpAlive(Index)++
#define SoAd_IncTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index) SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index)++
#define SoAd_IncTpRxBuffer(Index)                                     SoAd_GetTpRxBuffer(Index)++
#define SoAd_IncTpTxBuffer(Index)                                     SoAd_GetTpTxBuffer(Index)++
#define SoAd_IncTpTxBufferIdxOfTpTxBufferConfigDyn(Index)             SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(Index)++
#define SoAd_IncTriggerBuf(Index)                                     SoAd_GetTriggerBuf(Index)++
#define SoAd_IncLengthOfTriggerBufConfigDyn(Index)                    SoAd_GetLengthOfTriggerBufConfigDyn(Index)++
#define SoAd_IncPduRouteIdxOfTriggerBufConfigDyn(Index)               SoAd_GetPduRouteIdxOfTriggerBufConfigDyn(Index)++
#define SoAd_IncPduRouteDestIdxOfTxMgt(Index)                         SoAd_GetPduRouteDestIdxOfTxMgt(Index)++
#define SoAd_IncTxBufPtrOfTxMgt(Index)                                SoAd_GetTxBufPtrOfTxMgt(Index)++
#define SoAd_IncTxBytesLenOfTxMgt(Index)                              SoAd_GetTxBytesLenOfTxMgt(Index)++
#define SoAd_IncTxBytesPendingOfTxMgt(Index)                          SoAd_GetTxBytesPendingOfTxMgt(Index)++
/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCDecrementDataMacros  SoAd Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/ 
#define SoAd_DecSoConIdxOfBestMatchSoConIdxList(Index)                SoAd_GetSoConIdxOfBestMatchSoConIdxList(Index)--
#define SoAd_DecIdxOfEventQueueDyn(Index)                             SoAd_GetIdxOfEventQueueDyn(Index)--
#define SoAd_DecLvlOfEventQueueDyn(Index)                             SoAd_GetLvlOfEventQueueDyn(Index)--
#define SoAd_DecEventQueueFlag(Index)                                 SoAd_GetEventQueueFlag(Index)--
#define SoAd_DecRouteGrpIdxOfEventQueueIfTxRouteGrp(Index)            SoAd_GetRouteGrpIdxOfEventQueueIfTxRouteGrp(Index)--
#define SoAd_DecPduRouteIdxOfEventQueueIfUdpPduRoute(Index)           SoAd_GetPduRouteIdxOfEventQueueIfUdpPduRoute(Index)--
#define SoAd_DecLocalAddrIdxOfEventQueueLocalAddr(Index)              SoAd_GetLocalAddrIdxOfEventQueueLocalAddr(Index)--
#define SoAd_DecSocketIdxOfEventQueueSocketIdx(Index)                 SoAd_GetSocketIdxOfEventQueueSocketIdx(Index)--
#define SoAd_DecSoConIdxOfEventQueueStateSoCon(Index)                 SoAd_GetSoConIdxOfEventQueueStateSoCon(Index)--
#define SoAd_DecSoConIdxOfEventQueueTcpTxSoCon(Index)                 SoAd_GetSoConIdxOfEventQueueTcpTxSoCon(Index)--
#define SoAd_DecSoConIdxOfEventQueueTpRxSoCon(Index)                  SoAd_GetSoConIdxOfEventQueueTpRxSoCon(Index)--
#define SoAd_DecSoConIdxOfEventQueueTpTxSoCon(Index)                  SoAd_GetSoConIdxOfEventQueueTpTxSoCon(Index)--
#define SoAd_DecIfRxBuffer(Index)                                     SoAd_GetIfRxBuffer(Index)--
#define SoAd_DecIpFragBuf(Index)                                      SoAd_GetIpFragBuf(Index)--
#define SoAd_DecLengthOfIpFragBufConfigDyn(Index)                     SoAd_GetLengthOfIpFragBufConfigDyn(Index)--
#define SoAd_DecIpFragBufConfigIdxOfIpFragMgt(Index)                  SoAd_GetIpFragBufConfigIdxOfIpFragMgt(Index)--
#define SoAd_DecIpAddrStateOfLocalAddrDyn(Index)                      SoAd_GetIpAddrStateOfLocalAddrDyn(Index)--
#define SoAd_DecMetaDataRxBuf(Index)                                  SoAd_GetMetaDataRxBuf(Index)--
#define SoAd_DecNPduUdpTxBuffer(Index)                                SoAd_GetNPduUdpTxBuffer(Index)--
#define SoAd_DecBufLenOfNPduUdpTxDyn(Index)                           SoAd_GetBufLenOfNPduUdpTxDyn(Index)--
#define SoAd_DecLvlOfNPduUdpTxDyn(Index)                              SoAd_GetLvlOfNPduUdpTxDyn(Index)--
#define SoAd_DecRetryCntOfNPduUdpTxDyn(Index)                         SoAd_GetRetryCntOfNPduUdpTxDyn(Index)--
#define SoAd_DecTotalLenOfNPduUdpTxDyn(Index)                         SoAd_GetTotalLenOfNPduUdpTxDyn(Index)--
#define SoAd_DecLenOfNPduUdpTxQueue(Index)                            SoAd_GetLenOfNPduUdpTxQueue(Index)--
#define SoAd_DecNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index)             SoAd_GetNPduUdpTxBufferIdxOfNPduUdpTxQueue(Index)--
#define SoAd_DecPduRouteDestIdxOfNPduUdpTxQueue(Index)                SoAd_GetPduRouteDestIdxOfNPduUdpTxQueue(Index)--
#define SoAd_DecPendingTxConfNumOfPduRouteDyn(Index)                  SoAd_GetPendingTxConfNumOfPduRouteDyn(Index)--
#define SoAd_DecRcvRemAddr(Index)                                     SoAd_GetRcvRemAddr(Index)--
#define SoAd_DecRxBufStructSegIdxOfRxBufStructMgt(Index)              SoAd_GetRxBufStructSegIdxOfRxBufStructMgt(Index)--
#define SoAd_DecRxBufStructSegLvlOfRxBufStructMgt(Index)              SoAd_GetRxBufStructSegLvlOfRxBufStructMgt(Index)--
#define SoAd_DecDataPtrOfRxBufStructSeg(Index)                        SoAd_GetDataPtrOfRxBufStructSeg(Index)--
#define SoAd_DecLenOfRxBufStructSeg(Index)                            SoAd_GetLenOfRxBufStructSeg(Index)--
#define SoAd_DecIfRxBufferIdxOfRxBufferConfigDyn(Index)               SoAd_GetIfRxBufferIdxOfRxBufferConfigDyn(Index)--
#define SoAd_DecTpRxBufferIdxOfRxBufferConfigDyn(Index)               SoAd_GetTpRxBufferIdxOfRxBufferConfigDyn(Index)--
#define SoAd_DecRxBytesPendingOfRxMgt(Index)                          SoAd_GetRxBytesPendingOfRxMgt(Index)--
#define SoAd_DecSocketRouteDestIdxOfRxMgt(Index)                      SoAd_GetSocketRouteDestIdxOfRxMgt(Index)--
#define SoAd_DecCloseModeOfSoConDyn(Index)                            SoAd_GetCloseModeOfSoConDyn(Index)--
#define SoAd_DecModeOfSoConDyn(Index)                                 SoAd_GetModeOfSoConDyn(Index)--
#define SoAd_DecOpenCloseCounterOfSoConDyn(Index)                     SoAd_GetOpenCloseCounterOfSoConDyn(Index)--
#define SoAd_DecRemAddrDynOfSoConDyn(Index)                           SoAd_GetRemAddrDynOfSoConDyn(Index)--
#define SoAd_DecRemAddrStateDynOfSoConDyn(Index)                      SoAd_GetRemAddrStateDynOfSoConDyn(Index)--
#define SoAd_DecLocalPortOfSocketDyn(Index)                           SoAd_GetLocalPortOfSocketDyn(Index)--
#define SoAd_DecSkipBytesOfSocketDyn(Index)                           SoAd_GetSkipBytesOfSocketDyn(Index)--
#define SoAd_DecSoConTxActiveIdxOfSocketDyn(Index)                    SoAd_GetSoConTxActiveIdxOfSocketDyn(Index)--
#define SoAd_DecSocketIdOfSocketDyn(Index)                            SoAd_GetSocketIdOfSocketDyn(Index)--
#define SoAd_DecStateOfSocketDyn(Index)                               SoAd_GetStateOfSocketDyn(Index)--
#define SoAd_DecLenOfTcpTxQueueData(Index)                            SoAd_GetLenOfTcpTxQueueData(Index)--
#define SoAd_DecPduRouteIdxOfTcpTxQueueData(Index)                    SoAd_GetPduRouteIdxOfTcpTxQueueData(Index)--
#define SoAd_DecLvlOfTcpTxQueueMgt(Index)                             SoAd_GetLvlOfTcpTxQueueMgt(Index)--
#define SoAd_DecTcpTxQueueDataIdxOfTcpTxQueueMgt(Index)               SoAd_GetTcpTxQueueDataIdxOfTcpTxQueueMgt(Index)--
#define SoAd_DecTotLenOfTcpTxQueueMgt(Index)                          SoAd_GetTotLenOfTcpTxQueueMgt(Index)--
#define SoAd_DecLvlOfTimeoutListDyn(Index)                            SoAd_GetLvlOfTimeoutListDyn(Index)--
#define SoAd_DecNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index)             SoAd_GetNPduUdpTxIdxOfTimeoutListNPduUdpTx(Index)--
#define SoAd_DecTimeoutOfTimeoutListNPduUdpTx(Index)                  SoAd_GetTimeoutOfTimeoutListNPduUdpTx(Index)--
#define SoAd_DecTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index) SoAd_GetTimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap(Index)--
#define SoAd_DecSoConIdxOfTimeoutListUdpAlive(Index)                  SoAd_GetSoConIdxOfTimeoutListUdpAlive(Index)--
#define SoAd_DecTimeoutOfTimeoutListUdpAlive(Index)                   SoAd_GetTimeoutOfTimeoutListUdpAlive(Index)--
#define SoAd_DecTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index) SoAd_GetTimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap(Index)--
#define SoAd_DecTpRxBuffer(Index)                                     SoAd_GetTpRxBuffer(Index)--
#define SoAd_DecTpTxBuffer(Index)                                     SoAd_GetTpTxBuffer(Index)--
#define SoAd_DecTpTxBufferIdxOfTpTxBufferConfigDyn(Index)             SoAd_GetTpTxBufferIdxOfTpTxBufferConfigDyn(Index)--
#define SoAd_DecTriggerBuf(Index)                                     SoAd_GetTriggerBuf(Index)--
#define SoAd_DecLengthOfTriggerBufConfigDyn(Index)                    SoAd_GetLengthOfTriggerBufConfigDyn(Index)--
#define SoAd_DecPduRouteIdxOfTriggerBufConfigDyn(Index)               SoAd_GetPduRouteIdxOfTriggerBufConfigDyn(Index)--
#define SoAd_DecPduRouteDestIdxOfTxMgt(Index)                         SoAd_GetPduRouteDestIdxOfTxMgt(Index)--
#define SoAd_DecTxBufPtrOfTxMgt(Index)                                SoAd_GetTxBufPtrOfTxMgt(Index)--
#define SoAd_DecTxBytesLenOfTxMgt(Index)                              SoAd_GetTxBytesLenOfTxMgt(Index)--
#define SoAd_DecTxBytesPendingOfTxMgt(Index)                          SoAd_GetTxBytesPendingOfTxMgt(Index)--
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
  \defgroup  SoAdPCIterableTypes  SoAd Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate SoAd_BestMatchSoConIdxList */
typedef uint8_least SoAd_BestMatchSoConIdxListIterType;

/**   \brief  type used to iterate SoAd_DhcpEventCbk */
typedef uint8_least SoAd_DhcpEventCbkIterType;

/**   \brief  type used to iterate SoAd_EventQueue */
typedef uint8_least SoAd_EventQueueIterType;

/**   \brief  type used to iterate SoAd_EventQueueFlag */
typedef uint8_least SoAd_EventQueueFlagIterType;

/**   \brief  type used to iterate SoAd_EventQueueIdent */
typedef uint8_least SoAd_EventQueueIdentIterType;

/**   \brief  type used to iterate SoAd_EventQueueIfTxRouteGrp */
typedef uint8_least SoAd_EventQueueIfTxRouteGrpIterType;

/**   \brief  type used to iterate SoAd_EventQueueIfUdpPduRoute */
typedef uint8_least SoAd_EventQueueIfUdpPduRouteIterType;

/**   \brief  type used to iterate SoAd_EventQueueLocalAddr */
typedef uint8_least SoAd_EventQueueLocalAddrIterType;

/**   \brief  type used to iterate SoAd_EventQueueSocketIdx */
typedef uint8_least SoAd_EventQueueSocketIdxIterType;

/**   \brief  type used to iterate SoAd_EventQueueStateSoCon */
typedef uint8_least SoAd_EventQueueStateSoConIterType;

/**   \brief  type used to iterate SoAd_EventQueueTcpTxSoCon */
typedef uint8_least SoAd_EventQueueTcpTxSoConIterType;

/**   \brief  type used to iterate SoAd_EventQueueTpRxSoCon */
typedef uint8_least SoAd_EventQueueTpRxSoConIterType;

/**   \brief  type used to iterate SoAd_EventQueueTpTxSoCon */
typedef uint8_least SoAd_EventQueueTpTxSoConIterType;

/**   \brief  type used to iterate SoAd_IfRxBuffer */
typedef uint8_least SoAd_IfRxBufferIterType;

/**   \brief  type used to iterate SoAd_IpFragBuf */
typedef uint8_least SoAd_IpFragBufIterType;

/**   \brief  type used to iterate SoAd_IpFragBufConfig */
typedef uint8_least SoAd_IpFragBufConfigIterType;

/**   \brief  type used to iterate SoAd_IpFragMgt */
typedef uint8_least SoAd_IpFragMgtIterType;

/**   \brief  type used to iterate SoAd_LocalAddr */
typedef uint8_least SoAd_LocalAddrIterType;

/**   \brief  type used to iterate SoAd_LocalAddrByTcpIpCtrlInd */
typedef uint8_least SoAd_LocalAddrByTcpIpCtrlIndIterType;

/**   \brief  type used to iterate SoAd_LocalAddrIdMap */
typedef uint8_least SoAd_LocalAddrIdMapIterType;

/**   \brief  type used to iterate SoAd_LocalIpAddrAssignmentChgCbk */
typedef uint8_least SoAd_LocalIpAddrAssignmentChgCbkIterType;

/**   \brief  type used to iterate SoAd_LocalIpAddrAssignmentChgCbkInd */
typedef uint8_least SoAd_LocalIpAddrAssignmentChgCbkIndIterType;

/**   \brief  type used to iterate SoAd_MetaDataRxBuf */
typedef uint8_least SoAd_MetaDataRxBufIterType;

/**   \brief  type used to iterate SoAd_NPduUdpTx */
typedef uint8_least SoAd_NPduUdpTxIterType;

/**   \brief  type used to iterate SoAd_NPduUdpTxBuffer */
typedef uint8_least SoAd_NPduUdpTxBufferIterType;

/**   \brief  type used to iterate SoAd_NPduUdpTxQueue */
typedef uint8_least SoAd_NPduUdpTxQueueIterType;

/**   \brief  type used to iterate SoAd_PduRoute */
typedef uint8_least SoAd_PduRouteIterType;

/**   \brief  type used to iterate SoAd_PduRouteDest */
typedef uint8_least SoAd_PduRouteDestIterType;

/**   \brief  type used to iterate SoAd_PduRouteDestBySoConInd */
typedef uint8_least SoAd_PduRouteDestBySoConIndIterType;

/**   \brief  type used to iterate SoAd_PduRouteDestInd */
typedef uint8_least SoAd_PduRouteDestIndIterType;

/**   \brief  type used to iterate SoAd_RcvRemAddr */
typedef uint8_least SoAd_RcvRemAddrIterType;

/**   \brief  type used to iterate SoAd_RemAddrIpV4 */
typedef uint8_least SoAd_RemAddrIpV4IterType;

/**   \brief  type used to iterate SoAd_RemAddrIpV6 */
typedef uint8_least SoAd_RemAddrIpV6IterType;

/**   \brief  type used to iterate SoAd_RouteGrp */
typedef uint8_least SoAd_RouteGrpIterType;

/**   \brief  type used to iterate SoAd_RouteGrpIdMap */
typedef uint8_least SoAd_RouteGrpIdMapIterType;

/**   \brief  type used to iterate SoAd_RouteGrpSoCon */
typedef uint8_least SoAd_RouteGrpSoConIterType;

/**   \brief  type used to iterate SoAd_RouteGrpSoConByPduRouteDestInd */
typedef uint8_least SoAd_RouteGrpSoConByPduRouteDestIndIterType;

/**   \brief  type used to iterate SoAd_RouteGrpSoConBySocketRouteDestInd */
typedef uint8_least SoAd_RouteGrpSoConBySocketRouteDestIndIterType;

/**   \brief  type used to iterate SoAd_RxBufStructMgt */
typedef uint8_least SoAd_RxBufStructMgtIterType;

/**   \brief  type used to iterate SoAd_RxBufStructSeg */
typedef uint8_least SoAd_RxBufStructSegIterType;

/**   \brief  type used to iterate SoAd_RxBufferConfig */
typedef uint8_least SoAd_RxBufferConfigIterType;

/**   \brief  type used to iterate SoAd_RxMgt */
typedef uint8_least SoAd_RxMgtIterType;

/**   \brief  type used to iterate SoAd_RxPduIdIdMap */
typedef uint8_least SoAd_RxPduIdIdMapIterType;

/**   \brief  type used to iterate SoAd_ShutdownFinishedCbk */
typedef uint8_least SoAd_ShutdownFinishedCbkIterType;

/**   \brief  type used to iterate SoAd_SoCon */
typedef uint8_least SoAd_SoConIterType;

/**   \brief  type used to iterate SoAd_SoConGrp */
typedef uint8_least SoAd_SoConGrpIterType;

/**   \brief  type used to iterate SoAd_SoConMap */
typedef uint8_least SoAd_SoConMapIterType;

/**   \brief  type used to iterate SoAd_SoConModeChgCbk */
typedef uint8_least SoAd_SoConModeChgCbkIterType;

/**   \brief  type used to iterate SoAd_SoConModeChgCbkInd */
typedef uint8_least SoAd_SoConModeChgCbkIndIterType;

/**   \brief  type used to iterate SoAd_Socket */
typedef uint8_least SoAd_SocketIterType;

/**   \brief  type used to iterate SoAd_SocketReportErrorCbk */
typedef uint8_least SoAd_SocketReportErrorCbkIterType;

/**   \brief  type used to iterate SoAd_SocketRoute */
typedef uint8_least SoAd_SocketRouteIterType;

/**   \brief  type used to iterate SoAd_SocketRouteDest */
typedef uint8_least SoAd_SocketRouteDestIterType;

/**   \brief  type used to iterate SoAd_SocketRouteInd */
typedef uint8_least SoAd_SocketRouteIndIterType;

/**   \brief  type used to iterate SoAd_SocketTcp */
typedef uint8_least SoAd_SocketTcpIterType;

/**   \brief  type used to iterate SoAd_SocketUdp */
typedef uint8_least SoAd_SocketUdpIterType;

/**   \brief  type used to iterate SoAd_TcpIpCtrl */
typedef uint8_least SoAd_TcpIpCtrlIterType;

/**   \brief  type used to iterate SoAd_TcpKeepAliveGloballyEnabled */
typedef uint8_least SoAd_TcpKeepAliveGloballyEnabledIterType;

/**   \brief  type used to iterate SoAd_TcpTlsSocketCreatedNotificationCbk */
typedef uint8_least SoAd_TcpTlsSocketCreatedNotificationCbkIterType;

/**   \brief  type used to iterate SoAd_TcpTxQueue */
typedef uint8_least SoAd_TcpTxQueueIterType;

/**   \brief  type used to iterate SoAd_TcpTxQueueData */
typedef uint8_least SoAd_TcpTxQueueDataIterType;

/**   \brief  type used to iterate SoAd_TimeoutListDyn */
typedef uint8_least SoAd_TimeoutListDynIterType;

/**   \brief  type used to iterate SoAd_TimeoutListIdent */
typedef uint8_least SoAd_TimeoutListIdentIterType;

/**   \brief  type used to iterate SoAd_TimeoutListNPduUdpTx */
typedef uint8_least SoAd_TimeoutListNPduUdpTxIterType;

/**   \brief  type used to iterate SoAd_TimeoutListNPduUdpTxMap */
typedef uint8_least SoAd_TimeoutListNPduUdpTxMapIterType;

/**   \brief  type used to iterate SoAd_TimeoutListUdpAlive */
typedef uint8_least SoAd_TimeoutListUdpAliveIterType;

/**   \brief  type used to iterate SoAd_TimeoutListUdpAliveMap */
typedef uint8_least SoAd_TimeoutListUdpAliveMapIterType;

/**   \brief  type used to iterate SoAd_TlsConfig */
typedef uint8_least SoAd_TlsConfigIterType;

/**   \brief  type used to iterate SoAd_TpRxBuffer */
typedef uint8_least SoAd_TpRxBufferIterType;

/**   \brief  type used to iterate SoAd_TpTxBuffer */
typedef uint8_least SoAd_TpTxBufferIterType;

/**   \brief  type used to iterate SoAd_TpTxBufferConfig */
typedef uint8_least SoAd_TpTxBufferConfigIterType;

/**   \brief  type used to iterate SoAd_TriggerBuf */
typedef uint8_least SoAd_TriggerBufIterType;

/**   \brief  type used to iterate SoAd_TriggerBufConfig */
typedef uint8_least SoAd_TriggerBufConfigIterType;

/**   \brief  type used to iterate SoAd_TxMgt */
typedef uint8_least SoAd_TxMgtIterType;

/**   \brief  type used to iterate SoAd_TxPduIdMap */
typedef uint8_least SoAd_TxPduIdMapIterType;

/**   \brief  type used to iterate SoAd_UpperLayer */
typedef uint8_least SoAd_UpperLayerIterType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCIterableTypesWithSizeRelations  SoAd Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate SoAd_EventQueueDyn */
typedef SoAd_EventQueueIterType SoAd_EventQueueDynIterType;

/**   \brief  type used to iterate SoAd_IpFragBufConfigDyn */
typedef SoAd_IpFragBufConfigIterType SoAd_IpFragBufConfigDynIterType;

/**   \brief  type used to iterate SoAd_LocalAddrDyn */
typedef SoAd_LocalAddrIterType SoAd_LocalAddrDynIterType;

/**   \brief  type used to iterate SoAd_NPduUdpTxDyn */
typedef SoAd_NPduUdpTxIterType SoAd_NPduUdpTxDynIterType;

/**   \brief  type used to iterate SoAd_PduRouteDyn */
typedef SoAd_PduRouteIterType SoAd_PduRouteDynIterType;

/**   \brief  type used to iterate SoAd_RouteGrpSoConDyn */
typedef SoAd_RouteGrpSoConIterType SoAd_RouteGrpSoConDynIterType;

/**   \brief  type used to iterate SoAd_RxBufferConfigDyn */
typedef SoAd_RxBufferConfigIterType SoAd_RxBufferConfigDynIterType;

/**   \brief  type used to iterate SoAd_SoConDyn */
typedef SoAd_SoConIterType SoAd_SoConDynIterType;

/**   \brief  type used to iterate SoAd_SocketDyn */
typedef SoAd_SocketIterType SoAd_SocketDynIterType;

/**   \brief  type used to iterate SoAd_TcpTxQueueMgt */
typedef SoAd_TcpTxQueueIterType SoAd_TcpTxQueueMgtIterType;

/**   \brief  type used to iterate SoAd_TpTxBufferConfigDyn */
typedef SoAd_TpTxBufferConfigIterType SoAd_TpTxBufferConfigDynIterType;

/**   \brief  type used to iterate SoAd_TriggerBufConfigDyn */
typedef SoAd_TriggerBufConfigIterType SoAd_TriggerBufConfigDynIterType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCValueTypes  SoAd Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for SoAd_SoConIdxOfBestMatchSoConIdxList */
typedef uint8 SoAd_SoConIdxOfBestMatchSoConIdxListType;

/**   \brief  value based type definition for SoAd_LimitOfEventQueue */
typedef uint8 SoAd_LimitOfEventQueueType;

/**   \brief  value based type definition for SoAd_IdxOfEventQueueDyn */
typedef uint16 SoAd_IdxOfEventQueueDynType;

/**   \brief  value based type definition for SoAd_LvlOfEventQueueDyn */
typedef uint16 SoAd_LvlOfEventQueueDynType;

/**   \brief  value based type definition for SoAd_EventQueueIfTxRouteGrpIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueIfTxRouteGrpIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueIfTxRouteGrpUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueIfTxRouteGrpUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueIfUdpPduRouteIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueIfUdpPduRouteIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueIfUdpPduRouteUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueIfUdpPduRouteUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueLocalAddrIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueLocalAddrIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueLocalAddrUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueLocalAddrUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueSockIdxIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueSockIdxIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueSockIdxUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueSockIdxUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueStateSoConIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueStateSoConIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTcpTxSoConIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueTcpTxSoConIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTcpTxSoConUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueTcpTxSoConUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTpRxSoConIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueTpRxSoConIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTpRxSoConUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueTpRxSoConUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTpTxSoConIdxOfEventQueueIdent */
typedef uint8 SoAd_EventQueueTpTxSoConIdxOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_EventQueueTpTxSoConUsedOfEventQueueIdent */
typedef boolean SoAd_EventQueueTpTxSoConUsedOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_RouteGrpIdxOfEventQueueIfTxRouteGrp */
typedef uint8 SoAd_RouteGrpIdxOfEventQueueIfTxRouteGrpType;

/**   \brief  value based type definition for SoAd_PduRouteIdxOfEventQueueIfUdpPduRoute */
typedef uint8 SoAd_PduRouteIdxOfEventQueueIfUdpPduRouteType;

/**   \brief  value based type definition for SoAd_LocalAddrIdxOfEventQueueLocalAddr */
typedef uint8 SoAd_LocalAddrIdxOfEventQueueLocalAddrType;

/**   \brief  value based type definition for SoAd_SocketIdxOfEventQueueSocketIdx */
typedef uint8 SoAd_SocketIdxOfEventQueueSocketIdxType;

/**   \brief  value based type definition for SoAd_SoConIdxOfEventQueueStateSoCon */
typedef uint8 SoAd_SoConIdxOfEventQueueStateSoConType;

/**   \brief  value based type definition for SoAd_SoConIdxOfEventQueueTcpTxSoCon */
typedef uint8 SoAd_SoConIdxOfEventQueueTcpTxSoConType;

/**   \brief  value based type definition for SoAd_SoConIdxOfEventQueueTpRxSoCon */
typedef uint8 SoAd_SoConIdxOfEventQueueTpRxSoConType;

/**   \brief  value based type definition for SoAd_SoConIdxOfEventQueueTpTxSoCon */
typedef uint8 SoAd_SoConIdxOfEventQueueTpTxSoConType;

/**   \brief  value based type definition for SoAd_IfRxBuffer */
typedef uint8 SoAd_IfRxBufferType;

/**   \brief  value based type definition for SoAd_IpFragBuf */
typedef uint8 SoAd_IpFragBufType;

/**   \brief  value based type definition for SoAd_IpFragBufEndIdxOfIpFragBufConfig */
typedef uint8 SoAd_IpFragBufEndIdxOfIpFragBufConfigType;

/**   \brief  value based type definition for SoAd_IpFragBufStartIdxOfIpFragBufConfig */
typedef uint8 SoAd_IpFragBufStartIdxOfIpFragBufConfigType;

/**   \brief  value based type definition for SoAd_LengthOfIpFragBufConfigDyn */
typedef uint16 SoAd_LengthOfIpFragBufConfigDynType;

/**   \brief  value based type definition for SoAd_IpFragBufConfigIdxOfIpFragMgt */
typedef uint8 SoAd_IpFragBufConfigIdxOfIpFragMgtType;

/**   \brief  value based type definition for SoAd_TcpIpCtrlIdxOfLocalAddr */
typedef uint8 SoAd_TcpIpCtrlIdxOfLocalAddrType;

/**   \brief  value based type definition for SoAd_LocalAddrByTcpIpCtrlInd */
typedef uint8 SoAd_LocalAddrByTcpIpCtrlIndType;

/**   \brief  value based type definition for SoAd_InvalidHndOfLocalAddrIdMap */
typedef boolean SoAd_InvalidHndOfLocalAddrIdMapType;

/**   \brief  value based type definition for SoAd_LocalAddrIdxOfLocalAddrIdMap */
typedef uint8 SoAd_LocalAddrIdxOfLocalAddrIdMapType;

/**   \brief  value based type definition for SoAd_LocalIpAddrAssignmentChgCbkInd */
typedef uint8 SoAd_LocalIpAddrAssignmentChgCbkIndType;

/**   \brief  value based type definition for SoAd_MaxIfRouteGrpTransmitPduSize */
typedef uint8 SoAd_MaxIfRouteGrpTransmitPduSizeType;

/**   \brief  value based type definition for SoAd_MetaDataRxBuf */
typedef uint8 SoAd_MetaDataRxBufType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBufferEndIdxOfNPduUdpTx */
typedef uint8 SoAd_NPduUdpTxBufferEndIdxOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBufferStartIdxOfNPduUdpTx */
typedef uint8 SoAd_NPduUdpTxBufferStartIdxOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBufferUsedOfNPduUdpTx */
typedef boolean SoAd_NPduUdpTxBufferUsedOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxQueueEndIdxOfNPduUdpTx */
typedef uint8 SoAd_NPduUdpTxQueueEndIdxOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxQueueStartIdxOfNPduUdpTx */
typedef uint8 SoAd_NPduUdpTxQueueStartIdxOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxQueueUsedOfNPduUdpTx */
typedef boolean SoAd_NPduUdpTxQueueUsedOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_SoConIdxOfNPduUdpTx */
typedef uint8 SoAd_SoConIdxOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBuffer */
typedef uint8 SoAd_NPduUdpTxBufferType;

/**   \brief  value based type definition for SoAd_BufLenOfNPduUdpTxDyn */
typedef uint16 SoAd_BufLenOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_LvlOfNPduUdpTxDyn */
typedef uint8 SoAd_LvlOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_RetryCntOfNPduUdpTxDyn */
typedef uint16 SoAd_RetryCntOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_TotalLenOfNPduUdpTxDyn */
typedef uint32 SoAd_TotalLenOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_TransmissionActiveOfNPduUdpTxDyn */
typedef boolean SoAd_TransmissionActiveOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_CopiedOfNPduUdpTxQueue */
typedef boolean SoAd_CopiedOfNPduUdpTxQueueType;

/**   \brief  value based type definition for SoAd_LenOfNPduUdpTxQueue */
typedef PduLengthType SoAd_LenOfNPduUdpTxQueueType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBufferIdxOfNPduUdpTxQueue */
typedef uint8 SoAd_NPduUdpTxBufferIdxOfNPduUdpTxQueueType;

/**   \brief  value based type definition for SoAd_PduRouteDestIdxOfNPduUdpTxQueue */
typedef uint8 SoAd_PduRouteDestIdxOfNPduUdpTxQueueType;

/**   \brief  value based type definition for SoAd_AllPduRouteDestWithPduHdrOfPduRoute */
typedef boolean SoAd_AllPduRouteDestWithPduHdrOfPduRouteType;

/**   \brief  value based type definition for SoAd_MetaDataTxEnabledOfPduRoute */
typedef boolean SoAd_MetaDataTxEnabledOfPduRouteType;

/**   \brief  value based type definition for SoAd_PduRouteDestEndIdxOfPduRoute */
typedef uint8 SoAd_PduRouteDestEndIdxOfPduRouteType;

/**   \brief  value based type definition for SoAd_PduRouteDestStartIdxOfPduRoute */
typedef uint8 SoAd_PduRouteDestStartIdxOfPduRouteType;

/**   \brief  value based type definition for SoAd_TxConfEnabledOfPduRoute */
typedef boolean SoAd_TxConfEnabledOfPduRouteType;

/**   \brief  value based type definition for SoAd_TxConfPduIdOfPduRoute */
typedef PduIdType SoAd_TxConfPduIdOfPduRouteType;

/**   \brief  value based type definition for SoAd_TxOptimizedOfPduRoute */
typedef boolean SoAd_TxOptimizedOfPduRouteType;

/**   \brief  value based type definition for SoAd_UpperLayerIdxOfPduRoute */
typedef uint8 SoAd_UpperLayerIdxOfPduRouteType;

/**   \brief  value based type definition for SoAd_PduRouteIdxOfPduRouteDest */
typedef uint8 SoAd_PduRouteIdxOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest */
typedef uint8 SoAd_RouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest */
typedef uint8 SoAd_RouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConByPduRouteDestIndUsedOfPduRouteDest */
typedef boolean SoAd_RouteGrpSoConByPduRouteDestIndUsedOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_SoConIdxOfPduRouteDest */
typedef uint8 SoAd_SoConIdxOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_TxPduHdrIdOfPduRouteDest */
typedef uint8 SoAd_TxPduHdrIdOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_UdpTriggerTimeoutOfPduRouteDest */
typedef uint8 SoAd_UdpTriggerTimeoutOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_PduRouteDestBySoConInd */
typedef uint8 SoAd_PduRouteDestBySoConIndType;

/**   \brief  value based type definition for SoAd_PduRouteDestInd */
typedef uint8 SoAd_PduRouteDestIndType;

/**   \brief  value based type definition for SoAd_PendingTxConfMainOfPduRouteDyn */
typedef boolean SoAd_PendingTxConfMainOfPduRouteDynType;

/**   \brief  value based type definition for SoAd_EnabledAtInitOfRouteGrp */
typedef boolean SoAd_EnabledAtInitOfRouteGrpType;

/**   \brief  value based type definition for SoAd_MultiInstanceOnGrpOfRouteGrp */
typedef boolean SoAd_MultiInstanceOnGrpOfRouteGrpType;

/**   \brief  value based type definition for SoAd_PduRouteDestIndEndIdxOfRouteGrp */
typedef uint8 SoAd_PduRouteDestIndEndIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_PduRouteDestIndStartIdxOfRouteGrp */
typedef uint8 SoAd_PduRouteDestIndStartIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_PduRouteDestIndUsedOfRouteGrp */
typedef boolean SoAd_PduRouteDestIndUsedOfRouteGrpType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConEndIdxOfRouteGrp */
typedef uint8 SoAd_RouteGrpSoConEndIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConStartIdxOfRouteGrp */
typedef uint8 SoAd_RouteGrpSoConStartIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConUsedOfRouteGrp */
typedef boolean SoAd_RouteGrpSoConUsedOfRouteGrpType;

/**   \brief  value based type definition for SoAd_SocketRouteIndEndIdxOfRouteGrp */
typedef uint8 SoAd_SocketRouteIndEndIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_SocketRouteIndStartIdxOfRouteGrp */
typedef uint8 SoAd_SocketRouteIndStartIdxOfRouteGrpType;

/**   \brief  value based type definition for SoAd_SocketRouteIndUsedOfRouteGrp */
typedef boolean SoAd_SocketRouteIndUsedOfRouteGrpType;

/**   \brief  value based type definition for SoAd_TxTriggerableOfRouteGrp */
typedef boolean SoAd_TxTriggerableOfRouteGrpType;

/**   \brief  value based type definition for SoAd_InvalidHndOfRouteGrpIdMap */
typedef boolean SoAd_InvalidHndOfRouteGrpIdMapType;

/**   \brief  value based type definition for SoAd_RouteGrpIdxOfRouteGrpIdMap */
typedef uint8 SoAd_RouteGrpIdxOfRouteGrpIdMapType;

/**   \brief  value based type definition for SoAd_RouteGrpIdxOfRouteGrpSoCon */
typedef uint8 SoAd_RouteGrpIdxOfRouteGrpSoConType;

/**   \brief  value based type definition for SoAd_SoConIdxOfRouteGrpSoCon */
typedef uint8 SoAd_SoConIdxOfRouteGrpSoConType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConByPduRouteDestInd */
typedef uint8 SoAd_RouteGrpSoConByPduRouteDestIndType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConBySocketRouteDestInd */
typedef uint8 SoAd_RouteGrpSoConBySocketRouteDestIndType;

/**   \brief  value based type definition for SoAd_EnabledOfRouteGrpSoConDyn */
typedef boolean SoAd_EnabledOfRouteGrpSoConDynType;

/**   \brief  value based type definition for SoAd_SentOfRouteGrpSoConDyn */
typedef boolean SoAd_SentOfRouteGrpSoConDynType;

/**   \brief  value based type definition for SoAd_TriggerOfRouteGrpSoConDyn */
typedef boolean SoAd_TriggerOfRouteGrpSoConDynType;

/**   \brief  value based type definition for SoAd_RxBufStructSegIdxOfRxBufStructMgt */
typedef uint8 SoAd_RxBufStructSegIdxOfRxBufStructMgtType;

/**   \brief  value based type definition for SoAd_RxBufStructSegLvlOfRxBufStructMgt */
typedef uint8 SoAd_RxBufStructSegLvlOfRxBufStructMgtType;

/**   \brief  value based type definition for SoAd_LenOfRxBufStructSeg */
typedef uint16 SoAd_LenOfRxBufStructSegType;

/**   \brief  value based type definition for SoAd_IfRxBufferEndIdxOfRxBufferConfig */
typedef uint8 SoAd_IfRxBufferEndIdxOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_IfRxBufferStartIdxOfRxBufferConfig */
typedef uint8 SoAd_IfRxBufferStartIdxOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_IfRxBufferUsedOfRxBufferConfig */
typedef boolean SoAd_IfRxBufferUsedOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpRxBufferEndIdxOfRxBufferConfig */
typedef uint8 SoAd_TpRxBufferEndIdxOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpRxBufferStartIdxOfRxBufferConfig */
typedef uint8 SoAd_TpRxBufferStartIdxOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpRxBufferUsedOfRxBufferConfig */
typedef boolean SoAd_TpRxBufferUsedOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_IfRxBufferIdxOfRxBufferConfigDyn */
typedef uint8 SoAd_IfRxBufferIdxOfRxBufferConfigDynType;

/**   \brief  value based type definition for SoAd_TpRxBufferIdxOfRxBufferConfigDyn */
typedef uint8 SoAd_TpRxBufferIdxOfRxBufferConfigDynType;

/**   \brief  value based type definition for SoAd_CancelRequestedOfRxMgt */
typedef boolean SoAd_CancelRequestedOfRxMgtType;

/**   \brief  value based type definition for SoAd_RxBytesPendingOfRxMgt */
typedef PduLengthType SoAd_RxBytesPendingOfRxMgtType;

/**   \brief  value based type definition for SoAd_SocketRouteDestIdxOfRxMgt */
typedef uint8 SoAd_SocketRouteDestIdxOfRxMgtType;

/**   \brief  value based type definition for SoAd_InvalidHndOfRxPduIdIdMap */
typedef boolean SoAd_InvalidHndOfRxPduIdIdMapType;

/**   \brief  value based type definition for SoAd_SocketRouteDestIdxOfRxPduIdIdMap */
typedef uint8 SoAd_SocketRouteDestIdxOfRxPduIdIdMapType;

/**   \brief  value based type definition for SoAd_SizeOfBestMatchSoConIdxList */
typedef uint8 SoAd_SizeOfBestMatchSoConIdxListType;

/**   \brief  value based type definition for SoAd_SizeOfDhcpEventCbk */
typedef uint8 SoAd_SizeOfDhcpEventCbkType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueue */
typedef uint8 SoAd_SizeOfEventQueueType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueDyn */
typedef uint8 SoAd_SizeOfEventQueueDynType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueFlag */
typedef uint8 SoAd_SizeOfEventQueueFlagType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueIdent */
typedef uint8 SoAd_SizeOfEventQueueIdentType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueIfTxRouteGrp */
typedef uint8 SoAd_SizeOfEventQueueIfTxRouteGrpType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueIfUdpPduRoute */
typedef uint8 SoAd_SizeOfEventQueueIfUdpPduRouteType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueLocalAddr */
typedef uint8 SoAd_SizeOfEventQueueLocalAddrType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueSocketIdx */
typedef uint8 SoAd_SizeOfEventQueueSocketIdxType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueStateSoCon */
typedef uint8 SoAd_SizeOfEventQueueStateSoConType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueTcpTxSoCon */
typedef uint8 SoAd_SizeOfEventQueueTcpTxSoConType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueTpRxSoCon */
typedef uint8 SoAd_SizeOfEventQueueTpRxSoConType;

/**   \brief  value based type definition for SoAd_SizeOfEventQueueTpTxSoCon */
typedef uint8 SoAd_SizeOfEventQueueTpTxSoConType;

/**   \brief  value based type definition for SoAd_SizeOfIfRxBuffer */
typedef uint8 SoAd_SizeOfIfRxBufferType;

/**   \brief  value based type definition for SoAd_SizeOfIpFragBuf */
typedef uint8 SoAd_SizeOfIpFragBufType;

/**   \brief  value based type definition for SoAd_SizeOfIpFragBufConfig */
typedef uint8 SoAd_SizeOfIpFragBufConfigType;

/**   \brief  value based type definition for SoAd_SizeOfIpFragBufConfigDyn */
typedef uint8 SoAd_SizeOfIpFragBufConfigDynType;

/**   \brief  value based type definition for SoAd_SizeOfIpFragMgt */
typedef uint8 SoAd_SizeOfIpFragMgtType;

/**   \brief  value based type definition for SoAd_SizeOfLocalAddr */
typedef uint8 SoAd_SizeOfLocalAddrType;

/**   \brief  value based type definition for SoAd_SizeOfLocalAddrByTcpIpCtrlInd */
typedef uint8 SoAd_SizeOfLocalAddrByTcpIpCtrlIndType;

/**   \brief  value based type definition for SoAd_SizeOfLocalAddrDyn */
typedef uint8 SoAd_SizeOfLocalAddrDynType;

/**   \brief  value based type definition for SoAd_SizeOfLocalAddrIdMap */
typedef uint8 SoAd_SizeOfLocalAddrIdMapType;

/**   \brief  value based type definition for SoAd_SizeOfLocalIpAddrAssignmentChgCbk */
typedef uint8 SoAd_SizeOfLocalIpAddrAssignmentChgCbkType;

/**   \brief  value based type definition for SoAd_SizeOfLocalIpAddrAssignmentChgCbkInd */
typedef uint8 SoAd_SizeOfLocalIpAddrAssignmentChgCbkIndType;

/**   \brief  value based type definition for SoAd_SizeOfMetaDataRxBuf */
typedef uint8 SoAd_SizeOfMetaDataRxBufType;

/**   \brief  value based type definition for SoAd_SizeOfNPduUdpTx */
typedef uint8 SoAd_SizeOfNPduUdpTxType;

/**   \brief  value based type definition for SoAd_SizeOfNPduUdpTxBuffer */
typedef uint8 SoAd_SizeOfNPduUdpTxBufferType;

/**   \brief  value based type definition for SoAd_SizeOfNPduUdpTxDyn */
typedef uint8 SoAd_SizeOfNPduUdpTxDynType;

/**   \brief  value based type definition for SoAd_SizeOfNPduUdpTxQueue */
typedef uint8 SoAd_SizeOfNPduUdpTxQueueType;

/**   \brief  value based type definition for SoAd_SizeOfPduRoute */
typedef uint8 SoAd_SizeOfPduRouteType;

/**   \brief  value based type definition for SoAd_SizeOfPduRouteDest */
typedef uint8 SoAd_SizeOfPduRouteDestType;

/**   \brief  value based type definition for SoAd_SizeOfPduRouteDestBySoConInd */
typedef uint8 SoAd_SizeOfPduRouteDestBySoConIndType;

/**   \brief  value based type definition for SoAd_SizeOfPduRouteDestInd */
typedef uint8 SoAd_SizeOfPduRouteDestIndType;

/**   \brief  value based type definition for SoAd_SizeOfPduRouteDyn */
typedef uint8 SoAd_SizeOfPduRouteDynType;

/**   \brief  value based type definition for SoAd_SizeOfRcvRemAddr */
typedef uint8 SoAd_SizeOfRcvRemAddrType;

/**   \brief  value based type definition for SoAd_SizeOfRemAddrIpV4 */
typedef uint8 SoAd_SizeOfRemAddrIpV4Type;

/**   \brief  value based type definition for SoAd_SizeOfRemAddrIpV6 */
typedef uint8 SoAd_SizeOfRemAddrIpV6Type;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrp */
typedef uint8 SoAd_SizeOfRouteGrpType;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrpIdMap */
typedef uint8 SoAd_SizeOfRouteGrpIdMapType;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrpSoCon */
typedef uint8 SoAd_SizeOfRouteGrpSoConType;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrpSoConByPduRouteDestInd */
typedef uint8 SoAd_SizeOfRouteGrpSoConByPduRouteDestIndType;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrpSoConBySocketRouteDestInd */
typedef uint8 SoAd_SizeOfRouteGrpSoConBySocketRouteDestIndType;

/**   \brief  value based type definition for SoAd_SizeOfRouteGrpSoConDyn */
typedef uint8 SoAd_SizeOfRouteGrpSoConDynType;

/**   \brief  value based type definition for SoAd_SizeOfRxBufStructMgt */
typedef uint8 SoAd_SizeOfRxBufStructMgtType;

/**   \brief  value based type definition for SoAd_SizeOfRxBufStructSeg */
typedef uint8 SoAd_SizeOfRxBufStructSegType;

/**   \brief  value based type definition for SoAd_SizeOfRxBufferConfig */
typedef uint8 SoAd_SizeOfRxBufferConfigType;

/**   \brief  value based type definition for SoAd_SizeOfRxBufferConfigDyn */
typedef uint8 SoAd_SizeOfRxBufferConfigDynType;

/**   \brief  value based type definition for SoAd_SizeOfRxMgt */
typedef uint8 SoAd_SizeOfRxMgtType;

/**   \brief  value based type definition for SoAd_SizeOfRxPduIdIdMap */
typedef uint8 SoAd_SizeOfRxPduIdIdMapType;

/**   \brief  value based type definition for SoAd_SizeOfShutdownFinishedCbk */
typedef uint8 SoAd_SizeOfShutdownFinishedCbkType;

/**   \brief  value based type definition for SoAd_SizeOfSoCon */
typedef uint8 SoAd_SizeOfSoConType;

/**   \brief  value based type definition for SoAd_SizeOfSoConDyn */
typedef uint8 SoAd_SizeOfSoConDynType;

/**   \brief  value based type definition for SoAd_SizeOfSoConGrp */
typedef uint8 SoAd_SizeOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SizeOfSoConMap */
typedef uint8 SoAd_SizeOfSoConMapType;

/**   \brief  value based type definition for SoAd_SizeOfSoConModeChgCbk */
typedef uint8 SoAd_SizeOfSoConModeChgCbkType;

/**   \brief  value based type definition for SoAd_SizeOfSoConModeChgCbkInd */
typedef uint8 SoAd_SizeOfSoConModeChgCbkIndType;

/**   \brief  value based type definition for SoAd_SizeOfSocket */
typedef uint8 SoAd_SizeOfSocketType;

/**   \brief  value based type definition for SoAd_SizeOfSocketDyn */
typedef uint8 SoAd_SizeOfSocketDynType;

/**   \brief  value based type definition for SoAd_SizeOfSocketReportErrorCbk */
typedef uint8 SoAd_SizeOfSocketReportErrorCbkType;

/**   \brief  value based type definition for SoAd_SizeOfSocketRoute */
typedef uint8 SoAd_SizeOfSocketRouteType;

/**   \brief  value based type definition for SoAd_SizeOfSocketRouteDest */
typedef uint8 SoAd_SizeOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_SizeOfSocketRouteInd */
typedef uint8 SoAd_SizeOfSocketRouteIndType;

/**   \brief  value based type definition for SoAd_SizeOfSocketTcp */
typedef uint8 SoAd_SizeOfSocketTcpType;

/**   \brief  value based type definition for SoAd_SizeOfSocketUdp */
typedef uint8 SoAd_SizeOfSocketUdpType;

/**   \brief  value based type definition for SoAd_SizeOfTcpIpCtrl */
typedef uint8 SoAd_SizeOfTcpIpCtrlType;

/**   \brief  value based type definition for SoAd_SizeOfTcpKeepAliveGloballyEnabled */
typedef uint8 SoAd_SizeOfTcpKeepAliveGloballyEnabledType;

/**   \brief  value based type definition for SoAd_SizeOfTcpTlsSocketCreatedNotificationCbk */
typedef uint8 SoAd_SizeOfTcpTlsSocketCreatedNotificationCbkType;

/**   \brief  value based type definition for SoAd_SizeOfTcpTxQueue */
typedef uint8 SoAd_SizeOfTcpTxQueueType;

/**   \brief  value based type definition for SoAd_SizeOfTcpTxQueueData */
typedef uint8 SoAd_SizeOfTcpTxQueueDataType;

/**   \brief  value based type definition for SoAd_SizeOfTcpTxQueueMgt */
typedef uint8 SoAd_SizeOfTcpTxQueueMgtType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListDyn */
typedef uint8 SoAd_SizeOfTimeoutListDynType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListIdent */
typedef uint8 SoAd_SizeOfTimeoutListIdentType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListNPduUdpTx */
typedef uint8 SoAd_SizeOfTimeoutListNPduUdpTxType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListNPduUdpTxMap */
typedef uint8 SoAd_SizeOfTimeoutListNPduUdpTxMapType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListUdpAlive */
typedef uint8 SoAd_SizeOfTimeoutListUdpAliveType;

/**   \brief  value based type definition for SoAd_SizeOfTimeoutListUdpAliveMap */
typedef uint8 SoAd_SizeOfTimeoutListUdpAliveMapType;

/**   \brief  value based type definition for SoAd_SizeOfTlsConfig */
typedef uint8 SoAd_SizeOfTlsConfigType;

/**   \brief  value based type definition for SoAd_SizeOfTpRxBuffer */
typedef uint8 SoAd_SizeOfTpRxBufferType;

/**   \brief  value based type definition for SoAd_SizeOfTpTxBuffer */
typedef uint8 SoAd_SizeOfTpTxBufferType;

/**   \brief  value based type definition for SoAd_SizeOfTpTxBufferConfig */
typedef uint8 SoAd_SizeOfTpTxBufferConfigType;

/**   \brief  value based type definition for SoAd_SizeOfTpTxBufferConfigDyn */
typedef uint8 SoAd_SizeOfTpTxBufferConfigDynType;

/**   \brief  value based type definition for SoAd_SizeOfTriggerBuf */
typedef uint8 SoAd_SizeOfTriggerBufType;

/**   \brief  value based type definition for SoAd_SizeOfTriggerBufConfig */
typedef uint8 SoAd_SizeOfTriggerBufConfigType;

/**   \brief  value based type definition for SoAd_SizeOfTriggerBufConfigDyn */
typedef uint8 SoAd_SizeOfTriggerBufConfigDynType;

/**   \brief  value based type definition for SoAd_SizeOfTxMgt */
typedef uint8 SoAd_SizeOfTxMgtType;

/**   \brief  value based type definition for SoAd_SizeOfTxPduIdMap */
typedef uint8 SoAd_SizeOfTxPduIdMapType;

/**   \brief  value based type definition for SoAd_SizeOfUpperLayer */
typedef uint8 SoAd_SizeOfUpperLayerType;

/**   \brief  value based type definition for SoAd_IpFragMgtIdxOfSoCon */
typedef uint8 SoAd_IpFragMgtIdxOfSoConType;

/**   \brief  value based type definition for SoAd_IpFragMgtUsedOfSoCon */
typedef boolean SoAd_IpFragMgtUsedOfSoConType;

/**   \brief  value based type definition for SoAd_LocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon */
typedef uint8 SoAd_LocalIpAddrAssignmentChgCbkIndEndIdxOfSoConType;

/**   \brief  value based type definition for SoAd_LocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon */
typedef uint8 SoAd_LocalIpAddrAssignmentChgCbkIndStartIdxOfSoConType;

/**   \brief  value based type definition for SoAd_LocalIpAddrAssignmentChgCbkIndUsedOfSoCon */
typedef boolean SoAd_LocalIpAddrAssignmentChgCbkIndUsedOfSoConType;

/**   \brief  value based type definition for SoAd_NPduUdpTxIdxOfSoCon */
typedef uint8 SoAd_NPduUdpTxIdxOfSoConType;

/**   \brief  value based type definition for SoAd_NPduUdpTxUsedOfSoCon */
typedef boolean SoAd_NPduUdpTxUsedOfSoConType;

/**   \brief  value based type definition for SoAd_PduRouteDestBySoConIndEndIdxOfSoCon */
typedef uint8 SoAd_PduRouteDestBySoConIndEndIdxOfSoConType;

/**   \brief  value based type definition for SoAd_PduRouteDestBySoConIndStartIdxOfSoCon */
typedef uint8 SoAd_PduRouteDestBySoConIndStartIdxOfSoConType;

/**   \brief  value based type definition for SoAd_PduRouteDestBySoConIndUsedOfSoCon */
typedef boolean SoAd_PduRouteDestBySoConIndUsedOfSoConType;

/**   \brief  value based type definition for SoAd_RcvRemAddrIdxOfSoCon */
typedef uint8 SoAd_RcvRemAddrIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RcvRemAddrUsedOfSoCon */
typedef boolean SoAd_RcvRemAddrUsedOfSoConType;

/**   \brief  value based type definition for SoAd_RemAddrIpV4IdxOfSoCon */
typedef uint8 SoAd_RemAddrIpV4IdxOfSoConType;

/**   \brief  value based type definition for SoAd_RemAddrIpV4UsedOfSoCon */
typedef boolean SoAd_RemAddrIpV4UsedOfSoConType;

/**   \brief  value based type definition for SoAd_RemAddrIpV6IdxOfSoCon */
typedef uint8 SoAd_RemAddrIpV6IdxOfSoConType;

/**   \brief  value based type definition for SoAd_RemAddrIpV6UsedOfSoCon */
typedef boolean SoAd_RemAddrIpV6UsedOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufStructMgtIdxOfSoCon */
typedef uint8 SoAd_RxBufStructMgtIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufStructMgtUsedOfSoCon */
typedef boolean SoAd_RxBufStructMgtUsedOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufStructSegEndIdxOfSoCon */
typedef uint8 SoAd_RxBufStructSegEndIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufStructSegStartIdxOfSoCon */
typedef uint8 SoAd_RxBufStructSegStartIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufStructSegUsedOfSoCon */
typedef boolean SoAd_RxBufStructSegUsedOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufferConfigIdxOfSoCon */
typedef uint8 SoAd_RxBufferConfigIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RxBufferConfigUsedOfSoCon */
typedef boolean SoAd_RxBufferConfigUsedOfSoConType;

/**   \brief  value based type definition for SoAd_RxMgtIdxOfSoCon */
typedef uint8 SoAd_RxMgtIdxOfSoConType;

/**   \brief  value based type definition for SoAd_RxMgtUsedOfSoCon */
typedef boolean SoAd_RxMgtUsedOfSoConType;

/**   \brief  value based type definition for SoAd_SoConGrpIdxOfSoCon */
typedef uint8 SoAd_SoConGrpIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SoConIdOfSoCon */
typedef uint8 SoAd_SoConIdOfSoConType;

/**   \brief  value based type definition for SoAd_SoConModeChgCbkIndEndIdxOfSoCon */
typedef uint8 SoAd_SoConModeChgCbkIndEndIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SoConModeChgCbkIndStartIdxOfSoCon */
typedef uint8 SoAd_SoConModeChgCbkIndStartIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SoConModeChgCbkIndUsedOfSoCon */
typedef boolean SoAd_SoConModeChgCbkIndUsedOfSoConType;

/**   \brief  value based type definition for SoAd_SocketIdxOfSoCon */
typedef uint8 SoAd_SocketIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SocketRouteEndIdxOfSoCon */
typedef uint8 SoAd_SocketRouteEndIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SocketRouteStartIdxOfSoCon */
typedef uint8 SoAd_SocketRouteStartIdxOfSoConType;

/**   \brief  value based type definition for SoAd_SocketRouteUsedOfSoCon */
typedef boolean SoAd_SocketRouteUsedOfSoConType;

/**   \brief  value based type definition for SoAd_TcpTxQueueIdxOfSoCon */
typedef uint8 SoAd_TcpTxQueueIdxOfSoConType;

/**   \brief  value based type definition for SoAd_TcpTxQueueUsedOfSoCon */
typedef boolean SoAd_TcpTxQueueUsedOfSoConType;

/**   \brief  value based type definition for SoAd_TlsConfigIdxOfSoCon */
typedef uint8 SoAd_TlsConfigIdxOfSoConType;

/**   \brief  value based type definition for SoAd_TlsConfigUsedOfSoCon */
typedef boolean SoAd_TlsConfigUsedOfSoConType;

/**   \brief  value based type definition for SoAd_TpTxBufferConfigIdxOfSoCon */
typedef uint8 SoAd_TpTxBufferConfigIdxOfSoConType;

/**   \brief  value based type definition for SoAd_TpTxBufferConfigUsedOfSoCon */
typedef boolean SoAd_TpTxBufferConfigUsedOfSoConType;

/**   \brief  value based type definition for SoAd_TxMgtIdxOfSoCon */
typedef uint8 SoAd_TxMgtIdxOfSoConType;

/**   \brief  value based type definition for SoAd_TxMgtUsedOfSoCon */
typedef boolean SoAd_TxMgtUsedOfSoConType;

/**   \brief  value based type definition for SoAd_AbortOfSoConDyn */
typedef boolean SoAd_AbortOfSoConDynType;

/**   \brief  value based type definition for SoAd_OpenCloseCounterOfSoConDyn */
typedef uint32 SoAd_OpenCloseCounterOfSoConDynType;

/**   \brief  value based type definition for SoAd_BestMatchWithPduHeaderEnabledOfSoConGrp */
typedef boolean SoAd_BestMatchWithPduHeaderEnabledOfSoConGrpType;

/**   \brief  value based type definition for SoAd_BestMatchWithSockRouteEnabledOfSoConGrp */
typedef boolean SoAd_BestMatchWithSockRouteEnabledOfSoConGrpType;

/**   \brief  value based type definition for SoAd_FramePriorityOfSoConGrp */
typedef uint8 SoAd_FramePriorityOfSoConGrpType;

/**   \brief  value based type definition for SoAd_LocalAddrIdxOfSoConGrp */
typedef uint8 SoAd_LocalAddrIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_LocalAddrUsedOfSoConGrp */
typedef boolean SoAd_LocalAddrUsedOfSoConGrpType;

/**   \brief  value based type definition for SoAd_MsgAcceptFilterEnabledOfSoConGrp */
typedef boolean SoAd_MsgAcceptFilterEnabledOfSoConGrpType;

/**   \brief  value based type definition for SoAd_PduHdrEnabledOfSoConGrp */
typedef boolean SoAd_PduHdrEnabledOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SoConEndIdxOfSoConGrp */
typedef uint8 SoAd_SoConEndIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SoConStartIdxOfSoConGrp */
typedef uint8 SoAd_SoConStartIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SockAutoSoConSetupKeepOnlineOfSoConGrp */
typedef boolean SoAd_SockAutoSoConSetupKeepOnlineOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SockAutoSoConSetupOfSoConGrp */
typedef boolean SoAd_SockAutoSoConSetupOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketIdxOfSoConGrp */
typedef uint8 SoAd_SocketIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketTcpIdxOfSoConGrp */
typedef uint8 SoAd_SocketTcpIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketTcpUsedOfSoConGrp */
typedef boolean SoAd_SocketTcpUsedOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketUdpIdxOfSoConGrp */
typedef uint8 SoAd_SocketUdpIdxOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketUdpUsedOfSoConGrp */
typedef boolean SoAd_SocketUdpUsedOfSoConGrpType;

/**   \brief  value based type definition for SoAd_SocketUsedOfSoConGrp */
typedef boolean SoAd_SocketUsedOfSoConGrpType;

/**   \brief  value based type definition for SoAd_InvalidHndOfSoConMap */
typedef boolean SoAd_InvalidHndOfSoConMapType;

/**   \brief  value based type definition for SoAd_SoConIdxOfSoConMap */
typedef uint8 SoAd_SoConIdxOfSoConMapType;

/**   \brief  value based type definition for SoAd_SoConModeChgCbkInd */
typedef uint8 SoAd_SoConModeChgCbkIndType;

/**   \brief  value based type definition for SoAd_SoConEndIdxOfSocket */
typedef uint8 SoAd_SoConEndIdxOfSocketType;

/**   \brief  value based type definition for SoAd_SoConStartIdxOfSocket */
typedef uint8 SoAd_SoConStartIdxOfSocketType;

/**   \brief  value based type definition for SoAd_SkipBytesOfSocketDyn */
typedef uint32 SoAd_SkipBytesOfSocketDynType;

/**   \brief  value based type definition for SoAd_SoConTxActiveIdxOfSocketDyn */
typedef uint8 SoAd_SoConTxActiveIdxOfSocketDynType;

/**   \brief  value based type definition for SoAd_MetaDataRxEnabledOfSocketRoute */
typedef boolean SoAd_MetaDataRxEnabledOfSocketRouteType;

/**   \brief  value based type definition for SoAd_RxPduHdrIdOfSocketRoute */
typedef uint8 SoAd_RxPduHdrIdOfSocketRouteType;

/**   \brief  value based type definition for SoAd_SoConIdxOfSocketRoute */
typedef uint8 SoAd_SoConIdxOfSocketRouteType;

/**   \brief  value based type definition for SoAd_SocketRouteDestEndIdxOfSocketRoute */
typedef uint8 SoAd_SocketRouteDestEndIdxOfSocketRouteType;

/**   \brief  value based type definition for SoAd_SocketRouteDestStartIdxOfSocketRoute */
typedef uint8 SoAd_SocketRouteDestStartIdxOfSocketRouteType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDest */
typedef uint8 SoAd_RouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest */
typedef uint8 SoAd_RouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_RouteGrpSoConBySocketRouteDestIndUsedOfSocketRouteDest */
typedef boolean SoAd_RouteGrpSoConBySocketRouteDestIndUsedOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_RxPduIdOfSocketRouteDest */
typedef PduIdType SoAd_RxPduIdOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_SocketRouteIdxOfSocketRouteDest */
typedef uint8 SoAd_SocketRouteIdxOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_UpperLayerIdxOfSocketRouteDest */
typedef uint8 SoAd_UpperLayerIdxOfSocketRouteDestType;

/**   \brief  value based type definition for SoAd_SocketRouteInd */
typedef uint8 SoAd_SocketRouteIndType;

/**   \brief  value based type definition for SoAd_ImmedTpTxConfOfSocketTcp */
typedef boolean SoAd_ImmedTpTxConfOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpInitiateOfSocketTcp */
typedef boolean SoAd_TcpInitiateOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpKeepAliveIntervalOfSocketTcp */
typedef uint8 SoAd_TcpKeepAliveIntervalOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpKeepAliveOfSocketTcp */
typedef boolean SoAd_TcpKeepAliveOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpKeepAliveProbesMaxOfSocketTcp */
typedef uint8 SoAd_TcpKeepAliveProbesMaxOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpKeepAliveTimeOfSocketTcp */
typedef uint8 SoAd_TcpKeepAliveTimeOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpRxBufMinOfSocketTcp */
typedef uint8 SoAd_TcpRxBufMinOfSocketTcpType;

/**   \brief  value based type definition for SoAd_TcpTxBufMinOfSocketTcp */
typedef uint8 SoAd_TcpTxBufMinOfSocketTcpType;

/**   \brief  value based type definition for SoAd_AliveTimeoutMaxCntOfSocketUdp */
typedef uint8 SoAd_AliveTimeoutMaxCntOfSocketUdpType;

/**   \brief  value based type definition for SoAd_ImmedIfTxConfListSizeOfSocketUdp */
typedef uint8 SoAd_ImmedIfTxConfListSizeOfSocketUdpType;

/**   \brief  value based type definition for SoAd_ImmedIfTxConfOfSocketUdp */
typedef boolean SoAd_ImmedIfTxConfOfSocketUdpType;

/**   \brief  value based type definition for SoAd_NPduUdpTxBufferMinOfSocketUdp */
typedef uint8 SoAd_NPduUdpTxBufferMinOfSocketUdpType;

/**   \brief  value based type definition for SoAd_NPduUdpTxQueueSizeOfSocketUdp */
typedef uint8 SoAd_NPduUdpTxQueueSizeOfSocketUdpType;

/**   \brief  value based type definition for SoAd_RetryQueueLimitOfSocketUdp */
typedef uint8 SoAd_RetryQueueLimitOfSocketUdpType;

/**   \brief  value based type definition for SoAd_UdpListenOnlyOfSocketUdp */
typedef boolean SoAd_UdpListenOnlyOfSocketUdpType;

/**   \brief  value based type definition for SoAd_UdpStrictHdrLenCheckEnabledOfSocketUdp */
typedef boolean SoAd_UdpStrictHdrLenCheckEnabledOfSocketUdpType;

/**   \brief  value based type definition for SoAd_UdpTriggerTimeoutOfSocketUdp */
typedef uint8 SoAd_UdpTriggerTimeoutOfSocketUdpType;

/**   \brief  value based type definition for SoAd_LocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl */
typedef uint8 SoAd_LocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrlType;

/**   \brief  value based type definition for SoAd_LocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl */
typedef uint8 SoAd_LocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrlType;

/**   \brief  value based type definition for SoAd_LocalAddrByTcpIpCtrlIndUsedOfTcpIpCtrl */
typedef boolean SoAd_LocalAddrByTcpIpCtrlIndUsedOfTcpIpCtrlType;

/**   \brief  value based type definition for SoAd_RetryEnabledOfTcpIpCtrl */
typedef boolean SoAd_RetryEnabledOfTcpIpCtrlType;

/**   \brief  value based type definition for SoAd_TcpKeepAliveGloballyEnabled */
typedef boolean SoAd_TcpKeepAliveGloballyEnabledType;

/**   \brief  value based type definition for SoAd_TcpTxQueueDataEndIdxOfTcpTxQueue */
typedef uint8 SoAd_TcpTxQueueDataEndIdxOfTcpTxQueueType;

/**   \brief  value based type definition for SoAd_TcpTxQueueDataStartIdxOfTcpTxQueue */
typedef uint8 SoAd_TcpTxQueueDataStartIdxOfTcpTxQueueType;

/**   \brief  value based type definition for SoAd_LenOfTcpTxQueueData */
typedef PduLengthType SoAd_LenOfTcpTxQueueDataType;

/**   \brief  value based type definition for SoAd_PduRouteIdxOfTcpTxQueueData */
typedef uint8 SoAd_PduRouteIdxOfTcpTxQueueDataType;

/**   \brief  value based type definition for SoAd_LvlOfTcpTxQueueMgt */
typedef uint16 SoAd_LvlOfTcpTxQueueMgtType;

/**   \brief  value based type definition for SoAd_TcpTxQueueDataIdxOfTcpTxQueueMgt */
typedef uint8 SoAd_TcpTxQueueDataIdxOfTcpTxQueueMgtType;

/**   \brief  value based type definition for SoAd_TotLenOfTcpTxQueueMgt */
typedef uint32 SoAd_TotLenOfTcpTxQueueMgtType;

/**   \brief  value based type definition for SoAd_LvlOfTimeoutListDyn */
typedef uint16 SoAd_LvlOfTimeoutListDynType;

/**   \brief  value based type definition for SoAd_TimeoutListDynNPduUdpTxIdxOfTimeoutListIdent */
typedef uint8 SoAd_TimeoutListDynNPduUdpTxIdxOfTimeoutListIdentType;

/**   \brief  value based type definition for SoAd_TimeoutListDynNPduUdpTxUsedOfTimeoutListIdent */
typedef boolean SoAd_TimeoutListDynNPduUdpTxUsedOfTimeoutListIdentType;

/**   \brief  value based type definition for SoAd_TimeoutListDynUdpAliveIdxOfTimeoutListIdent */
typedef uint8 SoAd_TimeoutListDynUdpAliveIdxOfTimeoutListIdentType;

/**   \brief  value based type definition for SoAd_TimeoutListDynUdpAliveUsedOfTimeoutListIdent */
typedef boolean SoAd_TimeoutListDynUdpAliveUsedOfTimeoutListIdentType;

/**   \brief  value based type definition for SoAd_NPduUdpTxIdxOfTimeoutListNPduUdpTx */
typedef uint8 SoAd_NPduUdpTxIdxOfTimeoutListNPduUdpTxType;

/**   \brief  value based type definition for SoAd_TimeoutOfTimeoutListNPduUdpTx */
typedef uint32 SoAd_TimeoutOfTimeoutListNPduUdpTxType;

/**   \brief  value based type definition for SoAd_TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap */
typedef uint8 SoAd_TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMapType;

/**   \brief  value based type definition for SoAd_SoConIdxOfTimeoutListUdpAlive */
typedef uint8 SoAd_SoConIdxOfTimeoutListUdpAliveType;

/**   \brief  value based type definition for SoAd_TimeoutOfTimeoutListUdpAlive */
typedef uint32 SoAd_TimeoutOfTimeoutListUdpAliveType;

/**   \brief  value based type definition for SoAd_TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap */
typedef uint8 SoAd_TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMapType;

/**   \brief  value based type definition for SoAd_RxBufSizeOfTlsConfig */
typedef uint8 SoAd_RxBufSizeOfTlsConfigType;

/**   \brief  value based type definition for SoAd_TcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig */
typedef uint8 SoAd_TcpTlsSocketCreatedNotificationCbkIdxOfTlsConfigType;

/**   \brief  value based type definition for SoAd_TcpTlsSocketCreatedNotificationCbkUsedOfTlsConfig */
typedef boolean SoAd_TcpTlsSocketCreatedNotificationCbkUsedOfTlsConfigType;

/**   \brief  value based type definition for SoAd_TxBufSizeOfTlsConfig */
typedef uint8 SoAd_TxBufSizeOfTlsConfigType;

/**   \brief  value based type definition for SoAd_TpRxBuffer */
typedef uint8 SoAd_TpRxBufferType;

/**   \brief  value based type definition for SoAd_TpTxBuffer */
typedef uint8 SoAd_TpTxBufferType;

/**   \brief  value based type definition for SoAd_TpTxBufferEndIdxOfTpTxBufferConfig */
typedef uint8 SoAd_TpTxBufferEndIdxOfTpTxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpTxBufferStartIdxOfTpTxBufferConfig */
typedef uint8 SoAd_TpTxBufferStartIdxOfTpTxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpTxBufferUsedOfTpTxBufferConfig */
typedef boolean SoAd_TpTxBufferUsedOfTpTxBufferConfigType;

/**   \brief  value based type definition for SoAd_TpTxBufferIdxOfTpTxBufferConfigDyn */
typedef uint8 SoAd_TpTxBufferIdxOfTpTxBufferConfigDynType;

/**   \brief  value based type definition for SoAd_TriggerBuf */
typedef uint8 SoAd_TriggerBufType;

/**   \brief  value based type definition for SoAd_TriggerBufEndIdxOfTriggerBufConfig */
typedef uint8 SoAd_TriggerBufEndIdxOfTriggerBufConfigType;

/**   \brief  value based type definition for SoAd_TriggerBufStartIdxOfTriggerBufConfig */
typedef uint8 SoAd_TriggerBufStartIdxOfTriggerBufConfigType;

/**   \brief  value based type definition for SoAd_LengthOfTriggerBufConfigDyn */
typedef uint16 SoAd_LengthOfTriggerBufConfigDynType;

/**   \brief  value based type definition for SoAd_PduRouteIdxOfTriggerBufConfigDyn */
typedef uint8 SoAd_PduRouteIdxOfTriggerBufConfigDynType;

/**   \brief  value based type definition for SoAd_CancelRequestedOfTxMgt */
typedef boolean SoAd_CancelRequestedOfTxMgtType;

/**   \brief  value based type definition for SoAd_PduRouteDestIdxOfTxMgt */
typedef uint8 SoAd_PduRouteDestIdxOfTxMgtType;

/**   \brief  value based type definition for SoAd_TxBytesLenOfTxMgt */
typedef PduLengthType SoAd_TxBytesLenOfTxMgtType;

/**   \brief  value based type definition for SoAd_TxBytesPendingOfTxMgt */
typedef PduLengthType SoAd_TxBytesPendingOfTxMgtType;

/**   \brief  value based type definition for SoAd_InvalidHndOfTxPduIdMap */
typedef boolean SoAd_InvalidHndOfTxPduIdMapType;

/**   \brief  value based type definition for SoAd_PduRouteIdxOfTxPduIdMap */
typedef uint8 SoAd_PduRouteIdxOfTxPduIdMapType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  SoAdPCStructTypes  SoAd Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in SoAd_BestMatchSoConIdxList */
typedef struct sSoAd_BestMatchSoConIdxListType
{
  SoAd_SoConIdxOfBestMatchSoConIdxListType SoConIdxOfBestMatchSoConIdxList;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
} SoAd_BestMatchSoConIdxListType;

/**   \brief  type used in SoAd_EventQueue */
typedef struct sSoAd_EventQueueType
{
  SoAd_LimitOfEventQueueType LimitOfEventQueue;  /**< the limit of events handled in a single main function call */
  SoAd_EventQueueBitPatternType BitPatternOfEventQueue;  /**< the bit pattern for event queue */
} SoAd_EventQueueType;

/**   \brief  type used in SoAd_EventQueueDyn */
typedef struct sSoAd_EventQueueDynType
{
  SoAd_IdxOfEventQueueDynType IdxOfEventQueueDyn;  /**< the index of oldest pending event. */
  SoAd_LvlOfEventQueueDynType LvlOfEventQueueDyn;  /**< the level of pending events */
} SoAd_EventQueueDynType;

/**   \brief  type used in SoAd_EventQueueIdent */
typedef struct sSoAd_EventQueueIdentType
{
  SoAd_EventQueueIfTxRouteGrpIdxOfEventQueueIdentType EventQueueIfTxRouteGrpIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueIfUdpPduRouteIdxOfEventQueueIdentType EventQueueIfUdpPduRouteIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueLocalAddrIdxOfEventQueueIdentType EventQueueLocalAddrIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueSockIdxIdxOfEventQueueIdentType EventQueueSockIdxIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueStateSoConIdxOfEventQueueIdentType EventQueueStateSoConIdxOfEventQueueIdent;  /**< the index of the 1:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueTcpTxSoConIdxOfEventQueueIdentType EventQueueTcpTxSoConIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueTpRxSoConIdxOfEventQueueIdentType EventQueueTpRxSoConIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
  SoAd_EventQueueTpTxSoConIdxOfEventQueueIdentType EventQueueTpTxSoConIdxOfEventQueueIdent;  /**< the index of the 0:1 relation pointing to SoAd_EventQueue */
} SoAd_EventQueueIdentType;

/**   \brief  type used in SoAd_EventQueueIfTxRouteGrp */
typedef struct sSoAd_EventQueueIfTxRouteGrpType
{
  SoAd_RouteGrpIdxOfEventQueueIfTxRouteGrpType RouteGrpIdxOfEventQueueIfTxRouteGrp;  /**< the index of the 0:1 relation pointing to SoAd_RouteGrp */
} SoAd_EventQueueIfTxRouteGrpType;

/**   \brief  type used in SoAd_EventQueueIfUdpPduRoute */
typedef struct sSoAd_EventQueueIfUdpPduRouteType
{
  SoAd_PduRouteIdxOfEventQueueIfUdpPduRouteType PduRouteIdxOfEventQueueIfUdpPduRoute;  /**< the index of the 0:1 relation pointing to SoAd_PduRoute */
} SoAd_EventQueueIfUdpPduRouteType;

/**   \brief  type used in SoAd_EventQueueLocalAddr */
typedef struct sSoAd_EventQueueLocalAddrType
{
  SoAd_LocalAddrIdxOfEventQueueLocalAddrType LocalAddrIdxOfEventQueueLocalAddr;  /**< the index of the 0:1 relation pointing to SoAd_LocalAddr */
} SoAd_EventQueueLocalAddrType;

/**   \brief  type used in SoAd_EventQueueSocketIdx */
typedef struct sSoAd_EventQueueSocketIdxType
{
  SoAd_SocketIdxOfEventQueueSocketIdxType SocketIdxOfEventQueueSocketIdx;  /**< the index of the 0:1 relation pointing to SoAd_Socket */
} SoAd_EventQueueSocketIdxType;

/**   \brief  type used in SoAd_EventQueueStateSoCon */
typedef struct sSoAd_EventQueueStateSoConType
{
  SoAd_SoConIdxOfEventQueueStateSoConType SoConIdxOfEventQueueStateSoCon;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
} SoAd_EventQueueStateSoConType;

/**   \brief  type used in SoAd_EventQueueTcpTxSoCon */
typedef struct sSoAd_EventQueueTcpTxSoConType
{
  SoAd_SoConIdxOfEventQueueTcpTxSoConType SoConIdxOfEventQueueTcpTxSoCon;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
} SoAd_EventQueueTcpTxSoConType;

/**   \brief  type used in SoAd_EventQueueTpRxSoCon */
typedef struct sSoAd_EventQueueTpRxSoConType
{
  SoAd_SoConIdxOfEventQueueTpRxSoConType SoConIdxOfEventQueueTpRxSoCon;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
} SoAd_EventQueueTpRxSoConType;

/**   \brief  type used in SoAd_EventQueueTpTxSoCon */
typedef struct sSoAd_EventQueueTpTxSoConType
{
  SoAd_SoConIdxOfEventQueueTpTxSoConType SoConIdxOfEventQueueTpTxSoCon;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
} SoAd_EventQueueTpTxSoConType;

/**   \brief  type used in SoAd_IpFragBufConfig */
typedef struct sSoAd_IpFragBufConfigType
{
  SoAd_IpFragBufEndIdxOfIpFragBufConfigType IpFragBufEndIdxOfIpFragBufConfig;  /**< the end index of the 1:n relation pointing to SoAd_IpFragBuf */
  SoAd_IpFragBufStartIdxOfIpFragBufConfigType IpFragBufStartIdxOfIpFragBufConfig;  /**< the start index of the 1:n relation pointing to SoAd_IpFragBuf */
} SoAd_IpFragBufConfigType;

/**   \brief  type used in SoAd_IpFragBufConfigDyn */
typedef struct sSoAd_IpFragBufConfigDynType
{
  SoAd_LengthOfIpFragBufConfigDynType LengthOfIpFragBufConfigDyn;  /**< the length of the used part of the IP fragmentation buffer */
} SoAd_IpFragBufConfigDynType;

/**   \brief  type used in SoAd_IpFragMgt */
typedef struct sSoAd_IpFragMgtType
{
  SoAd_IpFragBufConfigIdxOfIpFragMgtType IpFragBufConfigIdxOfIpFragMgt;  /**< the index of the 1:1 relation pointing to SoAd_IpFragBufConfig */
} SoAd_IpFragMgtType;

/**   \brief  type used in SoAd_LocalAddr */
typedef struct sSoAd_LocalAddrType
{
  SoAd_TcpIpCtrlIdxOfLocalAddrType TcpIpCtrlIdxOfLocalAddr;  /**< the index of the 1:1 relation pointing to SoAd_TcpIpCtrl */
  SoAd_AddressTypeType AddressTypeOfLocalAddr;  /**< address type (unicast/multicast) */
  SoAd_AssignTriggerType AssignTriggerOfLocalAddr;  /**< assignment trigger (automatic/manual) */
  SoAd_DomainType DomainOfLocalAddr;  /**< the IP domain (IPv4/6) */
  SoAd_IpAddrAssignmentType AssignTypeOfLocalAddr;  /**< assignment type (e.g. static/link-local/DHCP) */
  SoAd_LocalAddrIdType AddrIdOfLocalAddr;  /**< the address identifier to identify the local address at TcpIp */
} SoAd_LocalAddrType;

/**   \brief  type used in SoAd_LocalAddrDyn */
typedef struct sSoAd_LocalAddrDynType
{
  SoAd_IpAddrStateType IpAddrStateOfLocalAddrDyn;  /**< the local IP address assignment state */
} SoAd_LocalAddrDynType;

/**   \brief  type used in SoAd_LocalAddrIdMap */
typedef struct sSoAd_LocalAddrIdMapType
{
  SoAd_InvalidHndOfLocalAddrIdMapType InvalidHndOfLocalAddrIdMap;  /**< FALSE, if the handle of SoAd_LocalAddrIdMap is valid and can be used in the embedded code for further processing in the embedded code. */
  SoAd_LocalAddrIdxOfLocalAddrIdMapType LocalAddrIdxOfLocalAddrIdMap;  /**< the index of the 1:1 relation pointing to SoAd_LocalAddr */
} SoAd_LocalAddrIdMapType;

/**   \brief  type used in SoAd_NPduUdpTx */
typedef struct sSoAd_NPduUdpTxType
{
  SoAd_NPduUdpTxBufferEndIdxOfNPduUdpTxType NPduUdpTxBufferEndIdxOfNPduUdpTx;  /**< the end index of the 0:n relation pointing to SoAd_NPduUdpTxBuffer */
  SoAd_NPduUdpTxBufferStartIdxOfNPduUdpTxType NPduUdpTxBufferStartIdxOfNPduUdpTx;  /**< the start index of the 0:n relation pointing to SoAd_NPduUdpTxBuffer */
  SoAd_NPduUdpTxQueueEndIdxOfNPduUdpTxType NPduUdpTxQueueEndIdxOfNPduUdpTx;  /**< the end index of the 0:n relation pointing to SoAd_NPduUdpTxQueue */
  SoAd_NPduUdpTxQueueStartIdxOfNPduUdpTxType NPduUdpTxQueueStartIdxOfNPduUdpTx;  /**< the start index of the 0:n relation pointing to SoAd_NPduUdpTxQueue */
  SoAd_SoConIdxOfNPduUdpTxType SoConIdxOfNPduUdpTx;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
} SoAd_NPduUdpTxType;

/**   \brief  type used in SoAd_NPduUdpTxDyn */
typedef struct sSoAd_NPduUdpTxDynType
{
  SoAd_TotalLenOfNPduUdpTxDynType TotalLenOfNPduUdpTxDyn;  /**< the total length of nPdu */
  SoAd_BufLenOfNPduUdpTxDynType BufLenOfNPduUdpTxDyn;  /**< the total length of PDUs stored in buffer if queue is used */
  SoAd_RetryCntOfNPduUdpTxDynType RetryCntOfNPduUdpTxDyn;  /**< the retry counter for queue retransmission */
  SoAd_LvlOfNPduUdpTxDynType LvlOfNPduUdpTxDyn;  /**< the level of PDUs in nPdu */
  SoAd_TransmissionActiveOfNPduUdpTxDynType TransmissionActiveOfNPduUdpTxDyn;  /**< indicates if transmission is active */
} SoAd_NPduUdpTxDynType;

/**   \brief  type used in SoAd_NPduUdpTxQueue */
typedef struct sSoAd_NPduUdpTxQueueType
{
  SoAd_CopiedOfNPduUdpTxQueueType CopiedOfNPduUdpTxQueue;  /**< indicates if PDU is copied to transmission buffer or sent already */
  SoAd_LenOfNPduUdpTxQueueType LenOfNPduUdpTxQueue;  /**< the length of PDU */
  SoAd_NPduUdpTxBufferIdxOfNPduUdpTxQueueType NPduUdpTxBufferIdxOfNPduUdpTxQueue;  /**< the index of the 1:1 relation pointing to SoAd_NPduUdpTxBuffer */
  SoAd_PduRouteDestIdxOfNPduUdpTxQueueType PduRouteDestIdxOfNPduUdpTxQueue;  /**< the index of the 0:1 relation pointing to SoAd_PduRouteDest */
} SoAd_NPduUdpTxQueueType;

/**   \brief  type used in SoAd_PduRoute */
typedef struct sSoAd_PduRouteType
{
  SoAd_TxConfPduIdOfPduRouteType TxConfPduIdOfPduRoute;  /**< the TxPduId used to call upper layer */
  SoAd_AllPduRouteDestWithPduHdrOfPduRouteType AllPduRouteDestWithPduHdrOfPduRoute;  /**< indicates if all related SoAdPduRouteDests have a SoAdTxPduHeaderId */
  SoAd_MetaDataTxEnabledOfPduRouteType MetaDataTxEnabledOfPduRoute;  /**< indicates if transmission on specific socket connection via meta data is enabled */
  SoAd_TxConfEnabledOfPduRouteType TxConfEnabledOfPduRoute;  /**< indicates if TxConfirmation is enabled */
  SoAd_TxOptimizedOfPduRouteType TxOptimizedOfPduRoute;  /**< indicates if Tx optimized is enabled */
  SoAd_PduRouteDestEndIdxOfPduRouteType PduRouteDestEndIdxOfPduRoute;  /**< the end index of the 1:n relation pointing to SoAd_PduRouteDest */
  SoAd_PduRouteDestStartIdxOfPduRouteType PduRouteDestStartIdxOfPduRoute;  /**< the start index of the 1:n relation pointing to SoAd_PduRouteDest */
  SoAd_UpperLayerIdxOfPduRouteType UpperLayerIdxOfPduRoute;  /**< the index of the 1:1 relation pointing to SoAd_UpperLayer */
  SoAd_IfTriggerTransmitModeType IfTriggerTransmitModeOfPduRoute;  /**< the trigger transmit mode */
  SoAd_UpperLayerApiType UpperLayerApiOfPduRoute;  /**< the upper layer API type (IF/TP) */
} SoAd_PduRouteType;

/**   \brief  type used in SoAd_PduRouteDest */
typedef struct sSoAd_PduRouteDestType
{
  SoAd_PduRouteIdxOfPduRouteDestType PduRouteIdxOfPduRouteDest;  /**< the index of the 1:1 relation pointing to SoAd_PduRoute */
  SoAd_RouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDestType RouteGrpSoConByPduRouteDestIndEndIdxOfPduRouteDest;  /**< the end index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd */
  SoAd_RouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDestType RouteGrpSoConByPduRouteDestIndStartIdxOfPduRouteDest;  /**< the start index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd */
  SoAd_SoConIdxOfPduRouteDestType SoConIdxOfPduRouteDest;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
  SoAd_TxPduHdrIdOfPduRouteDestType TxPduHdrIdOfPduRouteDest;  /**< the PDU header ID */
  SoAd_UdpTriggerTimeoutOfPduRouteDestType UdpTriggerTimeoutOfPduRouteDest;  /**< the PduRouteDest specific timeout to send a nPdu */
  SoAd_TxUdpTriggerModeType TxUdpTriggerModeOfPduRouteDest;  /**< indicates if nPdu shall be sent on transmission request always or never */
} SoAd_PduRouteDestType;

/**   \brief  type used in SoAd_PduRouteDyn */
typedef struct sSoAd_PduRouteDynType
{
  SoAd_PendingTxConfMainOfPduRouteDynType PendingTxConfMainOfPduRouteDyn;  /**< indicates if transmission confirmation in main function context is pending */
  SoAd_SizeOfPduRouteDestType PendingTxConfNumOfPduRouteDyn;  /**< the number of pending transmission confirmation */
} SoAd_PduRouteDynType;

/**   \brief  type used in SoAd_RemAddrIpV4 */
typedef struct sSoAd_RemAddrIpV4Type
{
  SoAd_IpAddrInetType AddrOfRemAddrIpV4;  /**< the remote IPv4 address */
  SoAd_PortType PortOfRemAddrIpV4;  /**< the remote port */
} SoAd_RemAddrIpV4Type;

/**   \brief  type used in SoAd_RemAddrIpV6 */
typedef struct sSoAd_RemAddrIpV6Type
{
  SoAd_IpAddrInet6Type AddrOfRemAddrIpV6;  /**< the remote IPv6 address */
  SoAd_PortType PortOfRemAddrIpV6;  /**< the remote port */
} SoAd_RemAddrIpV6Type;

/**   \brief  type used in SoAd_RouteGrp */
typedef struct sSoAd_RouteGrpType
{
  SoAd_EnabledAtInitOfRouteGrpType EnabledAtInitOfRouteGrp;  /**< indicates if RoutingGroup is initially enabled */
  SoAd_MultiInstanceOnGrpOfRouteGrpType MultiInstanceOnGrpOfRouteGrp;  /**< indicates if RoutingGroup is used for the multi service instance use case on socket connection groups */
  SoAd_TxTriggerableOfRouteGrpType TxTriggerableOfRouteGrp;  /**< indicates if RoutingGroup can be sent */
  SoAd_PduRouteDestIndEndIdxOfRouteGrpType PduRouteDestIndEndIdxOfRouteGrp;  /**< the end index of the 0:n relation pointing to SoAd_PduRouteDestInd */
  SoAd_PduRouteDestIndStartIdxOfRouteGrpType PduRouteDestIndStartIdxOfRouteGrp;  /**< the start index of the 0:n relation pointing to SoAd_PduRouteDestInd */
  SoAd_RouteGrpSoConEndIdxOfRouteGrpType RouteGrpSoConEndIdxOfRouteGrp;  /**< the end index of the 0:n relation pointing to SoAd_RouteGrpSoCon */
  SoAd_RouteGrpSoConStartIdxOfRouteGrpType RouteGrpSoConStartIdxOfRouteGrp;  /**< the start index of the 0:n relation pointing to SoAd_RouteGrpSoCon */
  SoAd_SocketRouteIndEndIdxOfRouteGrpType SocketRouteIndEndIdxOfRouteGrp;  /**< the end index of the 0:n relation pointing to SoAd_SocketRouteInd */
  SoAd_SocketRouteIndStartIdxOfRouteGrpType SocketRouteIndStartIdxOfRouteGrp;  /**< the start index of the 0:n relation pointing to SoAd_SocketRouteInd */
} SoAd_RouteGrpType;

/**   \brief  type used in SoAd_RouteGrpIdMap */
typedef struct sSoAd_RouteGrpIdMapType
{
  SoAd_InvalidHndOfRouteGrpIdMapType InvalidHndOfRouteGrpIdMap;  /**< FALSE, if the handle of SoAd_RouteGrpIdMap is valid and can be used in the embedded code for further processing in the embedded code. */
  SoAd_RouteGrpIdxOfRouteGrpIdMapType RouteGrpIdxOfRouteGrpIdMap;  /**< the index of the 1:1 relation pointing to SoAd_RouteGrp */
} SoAd_RouteGrpIdMapType;

/**   \brief  type used in SoAd_RouteGrpSoCon */
typedef struct sSoAd_RouteGrpSoConType
{
  SoAd_RouteGrpIdxOfRouteGrpSoConType RouteGrpIdxOfRouteGrpSoCon;  /**< the index of the 1:1 relation pointing to SoAd_RouteGrp */
  SoAd_SoConIdxOfRouteGrpSoConType SoConIdxOfRouteGrpSoCon;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
} SoAd_RouteGrpSoConType;

/**   \brief  type used in SoAd_RouteGrpSoConDyn */
typedef struct sSoAd_RouteGrpSoConDynType
{
  SoAd_EnabledOfRouteGrpSoConDynType EnabledOfRouteGrpSoConDyn;  /**< the routing group state on the socket connection */
  SoAd_SentOfRouteGrpSoConDynType SentOfRouteGrpSoConDyn;  /**< the state which indicates if a routing group transmission is done for the socket connection */
  SoAd_TriggerOfRouteGrpSoConDynType TriggerOfRouteGrpSoConDyn;  /**< the state which indicates if a routing group transmission is triggered for the socket connection */
} SoAd_RouteGrpSoConDynType;

/**   \brief  type used in SoAd_RxBufStructMgt */
typedef struct sSoAd_RxBufStructMgtType
{
  SoAd_RxBufStructSegIdxOfRxBufStructMgtType RxBufStructSegIdxOfRxBufStructMgt;  /**< the index of the 1:1 relation pointing to SoAd_RxBufStructSeg */
  SoAd_RxBufStructSegLvlOfRxBufStructMgtType RxBufStructSegLvlOfRxBufStructMgt;  /**< the lvl of used SoAd_RxBufStructSegs */
} SoAd_RxBufStructMgtType;

/**   \brief  type used in SoAd_RxBufStructSeg */
typedef struct sSoAd_RxBufStructSegType
{
  SoAd_LenOfRxBufStructSegType LenOfRxBufStructSeg;  /**< the length of segment */
  SoAd_DataPtrType DataPtrOfRxBufStructSeg;  /**< the pointer to segment data */
} SoAd_RxBufStructSegType;

/**   \brief  type used in SoAd_RxBufferConfig */
typedef struct sSoAd_RxBufferConfigType
{
  SoAd_IfRxBufferEndIdxOfRxBufferConfigType IfRxBufferEndIdxOfRxBufferConfig;  /**< the end index of the 0:n relation pointing to SoAd_IfRxBuffer */
  SoAd_IfRxBufferStartIdxOfRxBufferConfigType IfRxBufferStartIdxOfRxBufferConfig;  /**< the start index of the 0:n relation pointing to SoAd_IfRxBuffer */
  SoAd_TpRxBufferEndIdxOfRxBufferConfigType TpRxBufferEndIdxOfRxBufferConfig;  /**< the end index of the 0:n relation pointing to SoAd_TpRxBuffer */
  SoAd_TpRxBufferStartIdxOfRxBufferConfigType TpRxBufferStartIdxOfRxBufferConfig;  /**< the start index of the 0:n relation pointing to SoAd_TpRxBuffer */
} SoAd_RxBufferConfigType;

/**   \brief  type used in SoAd_RxBufferConfigDyn */
typedef struct sSoAd_RxBufferConfigDynType
{
  SoAd_IfRxBufferIdxOfRxBufferConfigDynType IfRxBufferIdxOfRxBufferConfigDyn;  /**< the index of the 0:1 relation pointing to SoAd_IfRxBuffer */
  SoAd_TpRxBufferIdxOfRxBufferConfigDynType TpRxBufferIdxOfRxBufferConfigDyn;  /**< the index of the 0:1 relation pointing to SoAd_TpRxBuffer */
} SoAd_RxBufferConfigDynType;

/**   \brief  type used in SoAd_RxMgt */
typedef struct sSoAd_RxMgtType
{
  SoAd_CancelRequestedOfRxMgtType CancelRequestedOfRxMgt;  /**< indicates if reception cancellation is requested */
  SoAd_RxBytesPendingOfRxMgtType RxBytesPendingOfRxMgt;  /**< the length of pending data to be received */
  SoAd_SocketRouteDestIdxOfRxMgtType SocketRouteDestIdxOfRxMgt;  /**< the index of the 1:1 relation pointing to SoAd_SocketRouteDest */
} SoAd_RxMgtType;

/**   \brief  type used in SoAd_RxPduIdIdMap */
typedef struct sSoAd_RxPduIdIdMapType
{
  SoAd_InvalidHndOfRxPduIdIdMapType InvalidHndOfRxPduIdIdMap;  /**< FALSE, if the handle of SoAd_RxPduIdIdMap is valid and can be used in the embedded code for further processing in the embedded code. */
  SoAd_SocketRouteDestIdxOfRxPduIdIdMapType SocketRouteDestIdxOfRxPduIdIdMap;  /**< the index of the 1:1 relation pointing to SoAd_SocketRouteDest */
} SoAd_RxPduIdIdMapType;

/**   \brief  type used in SoAd_SoCon */
typedef struct sSoAd_SoConType
{
  SoAd_IpFragMgtIdxOfSoConType IpFragMgtIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_IpFragMgt */
  SoAd_LocalIpAddrAssignmentChgCbkIndEndIdxOfSoConType LocalIpAddrAssignmentChgCbkIndEndIdxOfSoCon;  /**< the end index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd */
  SoAd_LocalIpAddrAssignmentChgCbkIndStartIdxOfSoConType LocalIpAddrAssignmentChgCbkIndStartIdxOfSoCon;  /**< the start index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd */
  SoAd_NPduUdpTxIdxOfSoConType NPduUdpTxIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_NPduUdpTx */
  SoAd_PduRouteDestBySoConIndEndIdxOfSoConType PduRouteDestBySoConIndEndIdxOfSoCon;  /**< the end index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd */
  SoAd_PduRouteDestBySoConIndStartIdxOfSoConType PduRouteDestBySoConIndStartIdxOfSoCon;  /**< the start index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd */
  SoAd_RcvRemAddrIdxOfSoConType RcvRemAddrIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RcvRemAddr */
  SoAd_RemAddrIpV4IdxOfSoConType RemAddrIpV4IdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RemAddrIpV4 */
  SoAd_RemAddrIpV6IdxOfSoConType RemAddrIpV6IdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RemAddrIpV6 */
  SoAd_RxBufStructMgtIdxOfSoConType RxBufStructMgtIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RxBufStructMgt */
  SoAd_RxBufStructSegEndIdxOfSoConType RxBufStructSegEndIdxOfSoCon;  /**< the end index of the 0:n relation pointing to SoAd_RxBufStructSeg */
  SoAd_RxBufStructSegStartIdxOfSoConType RxBufStructSegStartIdxOfSoCon;  /**< the start index of the 0:n relation pointing to SoAd_RxBufStructSeg */
  SoAd_RxBufferConfigIdxOfSoConType RxBufferConfigIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RxBufferConfig */
  SoAd_RxMgtIdxOfSoConType RxMgtIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_RxMgt */
  SoAd_SoConGrpIdxOfSoConType SoConGrpIdxOfSoCon;  /**< the index of the 1:1 relation pointing to SoAd_SoConGrp */
  SoAd_SoConIdOfSoConType SoConIdOfSoCon;  /**< the SocketConnection identifier used in SoAd API */
  SoAd_SoConModeChgCbkIndEndIdxOfSoConType SoConModeChgCbkIndEndIdxOfSoCon;  /**< the end index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd */
  SoAd_SoConModeChgCbkIndStartIdxOfSoConType SoConModeChgCbkIndStartIdxOfSoCon;  /**< the start index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd */
  SoAd_SocketIdxOfSoConType SocketIdxOfSoCon;  /**< the index of the 1:1 relation pointing to SoAd_Socket */
  SoAd_SocketRouteEndIdxOfSoConType SocketRouteEndIdxOfSoCon;  /**< the end index of the 0:n relation pointing to SoAd_SocketRoute */
  SoAd_SocketRouteStartIdxOfSoConType SocketRouteStartIdxOfSoCon;  /**< the start index of the 0:n relation pointing to SoAd_SocketRoute */
  SoAd_TcpTxQueueIdxOfSoConType TcpTxQueueIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_TcpTxQueue */
  SoAd_TlsConfigIdxOfSoConType TlsConfigIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_TlsConfig */
  SoAd_TpTxBufferConfigIdxOfSoConType TpTxBufferConfigIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_TpTxBufferConfig */
  SoAd_TxMgtIdxOfSoConType TxMgtIdxOfSoCon;  /**< the index of the 0:1 relation pointing to SoAd_TxMgt */
  SoAd_RemAddrStateType RemAddrStateOfSoCon;  /**< the configured remote address state */
} SoAd_SoConType;

/**   \brief  type used in SoAd_SoConDyn */
typedef struct sSoAd_SoConDynType
{
  SoAd_OpenCloseCounterOfSoConDynType OpenCloseCounterOfSoConDyn;  /**< the open and close sequence counter */
  SoAd_AbortOfSoConDynType AbortOfSoConDyn;  /**< indicates if abort is requested */
  SoAd_SoConCloseModeType CloseModeOfSoConDyn;  /**< the mode of socket connection */
  SoAd_SoConModeType ModeOfSoConDyn;  /**< the mode of socket connection */
  SoAd_SockAddrInetXType RemAddrDynOfSoConDyn;  /**< the remote address for each socket connection */
  SoAd_RemAddrStateType RemAddrStateDynOfSoConDyn;  /**< the remote address state on socket connection */
} SoAd_SoConDynType;

/**   \brief  type used in SoAd_SoConGrp */
typedef struct sSoAd_SoConGrpType
{
  SoAd_BestMatchWithPduHeaderEnabledOfSoConGrpType BestMatchWithPduHeaderEnabledOfSoConGrp;  /**< indicates if best match algorithm considers PDU Header ID */
  SoAd_BestMatchWithSockRouteEnabledOfSoConGrpType BestMatchWithSockRouteEnabledOfSoConGrp;  /**< indicates if best match algorithm considers socket route availability */
  SoAd_MsgAcceptFilterEnabledOfSoConGrpType MsgAcceptFilterEnabledOfSoConGrp;  /**< indicates if message acceptance filter is enabled */
  SoAd_PduHdrEnabledOfSoConGrpType PduHdrEnabledOfSoConGrp;  /**< indicates if PDU header is enabled */
  SoAd_SockAutoSoConSetupOfSoConGrpType SockAutoSoConSetupOfSoConGrp;  /**< indicates if automatic socket connection setup is enabled */
  SoAd_SockAutoSoConSetupKeepOnlineOfSoConGrpType SockAutoSoConSetupKeepOnlineOfSoConGrp;  /**< indicates if it is enabled that socket connection stays online after transmission */
  SoAd_FramePriorityOfSoConGrpType FramePriorityOfSoConGrp;  /**< the frame priority (VLAN) */
  SoAd_LocalAddrIdxOfSoConGrpType LocalAddrIdxOfSoConGrp;  /**< the index of the 0:1 relation pointing to SoAd_LocalAddr */
  SoAd_SoConEndIdxOfSoConGrpType SoConEndIdxOfSoConGrp;  /**< the end index of the 1:n relation pointing to SoAd_SoCon */
  SoAd_SoConStartIdxOfSoConGrpType SoConStartIdxOfSoConGrp;  /**< the start index of the 1:n relation pointing to SoAd_SoCon */
  SoAd_SocketIdxOfSoConGrpType SocketIdxOfSoConGrp;  /**< the index of the 0:1 relation pointing to SoAd_Socket */
  SoAd_SocketTcpIdxOfSoConGrpType SocketTcpIdxOfSoConGrp;  /**< the index of the 0:1 relation pointing to SoAd_SocketTcp */
  SoAd_SocketUdpIdxOfSoConGrpType SocketUdpIdxOfSoConGrp;  /**< the index of the 0:1 relation pointing to SoAd_SocketUdp */
  SoAd_PortType LocalPortOfSoConGrp;  /**< the local port */
} SoAd_SoConGrpType;

/**   \brief  type used in SoAd_SoConMap */
typedef struct sSoAd_SoConMapType
{
  SoAd_InvalidHndOfSoConMapType InvalidHndOfSoConMap;  /**< FALSE, if the handle of SoAd_SoConMap is valid and can be used in the embedded code for further processing in the embedded code. */
  SoAd_SoConIdxOfSoConMapType SoConIdxOfSoConMap;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
} SoAd_SoConMapType;

/**   \brief  type used in SoAd_Socket */
typedef struct sSoAd_SocketType
{
  SoAd_SoConEndIdxOfSocketType SoConEndIdxOfSocket;  /**< the end index of the 1:n relation pointing to SoAd_SoCon */
  SoAd_SoConStartIdxOfSocketType SoConStartIdxOfSocket;  /**< the start index of the 1:n relation pointing to SoAd_SoCon */
} SoAd_SocketType;

/**   \brief  type used in SoAd_SocketDyn */
typedef struct sSoAd_SocketDynType
{
  SoAd_SkipBytesOfSocketDynType SkipBytesOfSocketDyn;  /**< the number of bytes to be skipped */
  SoAd_SoConTxActiveIdxOfSocketDynType SoConTxActiveIdxOfSocketDyn;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
  SoAd_PortType LocalPortOfSocketDyn;  /**< the local port */
  SoAd_SocketIdType SocketIdOfSocketDyn;  /**< the socket identifier */
  SoAd_SockStateType StateOfSocketDyn;  /**< the socket state */
} SoAd_SocketDynType;

/**   \brief  type used in SoAd_SocketRoute */
typedef struct sSoAd_SocketRouteType
{
  SoAd_MetaDataRxEnabledOfSocketRouteType MetaDataRxEnabledOfSocketRoute;  /**< indicates if SoConId is forwarded as meta data on reception */
  SoAd_RxPduHdrIdOfSocketRouteType RxPduHdrIdOfSocketRoute;  /**< the PDU header ID */
  SoAd_SoConIdxOfSocketRouteType SoConIdxOfSocketRoute;  /**< the index of the 1:1 relation pointing to SoAd_SoCon */
  SoAd_SocketRouteDestEndIdxOfSocketRouteType SocketRouteDestEndIdxOfSocketRoute;  /**< the end index of the 1:n relation pointing to SoAd_SocketRouteDest */
  SoAd_SocketRouteDestStartIdxOfSocketRouteType SocketRouteDestStartIdxOfSocketRoute;  /**< the start index of the 1:n relation pointing to SoAd_SocketRouteDest */
  SoAd_UpperLayerApiType UpperLayerApiOfSocketRoute;  /**< the upper layer API type (IF/TP) */
} SoAd_SocketRouteType;

/**   \brief  type used in SoAd_SocketRouteDest */
typedef struct sSoAd_SocketRouteDestType
{
  SoAd_RxPduIdOfSocketRouteDestType RxPduIdOfSocketRouteDest;  /**< the RxPduId used to call the upper layer */
  SoAd_RouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDestType RouteGrpSoConBySocketRouteDestIndEndIdxOfSocketRouteDest;  /**< the end index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd */
  SoAd_RouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDestType RouteGrpSoConBySocketRouteDestIndStartIdxOfSocketRouteDest;  /**< the start index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd */
  SoAd_SocketRouteIdxOfSocketRouteDestType SocketRouteIdxOfSocketRouteDest;  /**< the index of the 1:1 relation pointing to SoAd_SocketRoute */
  SoAd_UpperLayerIdxOfSocketRouteDestType UpperLayerIdxOfSocketRouteDest;  /**< the index of the 1:1 relation pointing to SoAd_UpperLayer */
} SoAd_SocketRouteDestType;

/**   \brief  type used in SoAd_SocketTcp */
typedef struct sSoAd_SocketTcpType
{
  SoAd_ImmedTpTxConfOfSocketTcpType ImmedTpTxConfOfSocketTcp;  /**< indicates if TP immediate TxConfirmation is used */
  SoAd_TcpInitiateOfSocketTcpType TcpInitiateOfSocketTcp;  /**< indicates if TCP connection is initiated by SoAd */
  SoAd_TcpKeepAliveOfSocketTcpType TcpKeepAliveOfSocketTcp;  /**< indicates if keepalive mechanism is used */
  SoAd_TcpKeepAliveIntervalOfSocketTcpType TcpKeepAliveIntervalOfSocketTcp;  /**< the interval time between keepalive probes */
  SoAd_TcpKeepAliveProbesMaxOfSocketTcpType TcpKeepAliveProbesMaxOfSocketTcp;  /**< the maximum number of keepalive probes */
  SoAd_TcpKeepAliveTimeOfSocketTcpType TcpKeepAliveTimeOfSocketTcp;  /**< the time between the last data packet sent and the first keepalive probe */
  SoAd_TcpRxBufMinOfSocketTcpType TcpRxBufMinOfSocketTcp;  /**< the size of TCP reception buffer */
  SoAd_TcpTxBufMinOfSocketTcpType TcpTxBufMinOfSocketTcp;  /**< the size of TCP transmission buffer */
  SoAd_TcpNoDelayType TcpNoDelayOfSocketTcp;  /**< indicates not to use the congestion control mechanism */
} SoAd_SocketTcpType;

/**   \brief  type used in SoAd_SocketUdp */
typedef struct sSoAd_SocketUdpType
{
  SoAd_ImmedIfTxConfOfSocketUdpType ImmedIfTxConfOfSocketUdp;
  SoAd_UdpListenOnlyOfSocketUdpType UdpListenOnlyOfSocketUdp;
  SoAd_UdpStrictHdrLenCheckEnabledOfSocketUdpType UdpStrictHdrLenCheckEnabledOfSocketUdp;
  SoAd_AliveTimeoutMaxCntOfSocketUdpType AliveTimeoutMaxCntOfSocketUdp;
  SoAd_ImmedIfTxConfListSizeOfSocketUdpType ImmedIfTxConfListSizeOfSocketUdp;
  SoAd_NPduUdpTxBufferMinOfSocketUdpType NPduUdpTxBufferMinOfSocketUdp;
  SoAd_NPduUdpTxQueueSizeOfSocketUdpType NPduUdpTxQueueSizeOfSocketUdp;
  SoAd_RetryQueueLimitOfSocketUdpType RetryQueueLimitOfSocketUdp;
  SoAd_UdpTriggerTimeoutOfSocketUdpType UdpTriggerTimeoutOfSocketUdp;
} SoAd_SocketUdpType;

/**   \brief  type used in SoAd_TcpIpCtrl */
typedef struct sSoAd_TcpIpCtrlType
{
  SoAd_RetryEnabledOfTcpIpCtrlType RetryEnabledOfTcpIpCtrl;  /**< indicates if transmission retry is available on controller/interface */
  SoAd_LocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrlType LocalAddrByTcpIpCtrlIndEndIdxOfTcpIpCtrl;  /**< the end index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd */
  SoAd_LocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrlType LocalAddrByTcpIpCtrlIndStartIdxOfTcpIpCtrl;  /**< the start index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd */
} SoAd_TcpIpCtrlType;

/**   \brief  type used in SoAd_TcpTxQueue */
typedef struct sSoAd_TcpTxQueueType
{
  SoAd_TcpTxQueueDataEndIdxOfTcpTxQueueType TcpTxQueueDataEndIdxOfTcpTxQueue;  /**< the end index of the 1:n relation pointing to SoAd_TcpTxQueueData */
  SoAd_TcpTxQueueDataStartIdxOfTcpTxQueueType TcpTxQueueDataStartIdxOfTcpTxQueue;  /**< the start index of the 1:n relation pointing to SoAd_TcpTxQueueData */
} SoAd_TcpTxQueueType;

/**   \brief  type used in SoAd_TcpTxQueueData */
typedef struct sSoAd_TcpTxQueueDataType
{
  SoAd_LenOfTcpTxQueueDataType LenOfTcpTxQueueData;  /**< the length of the queue element */
  SoAd_PduRouteIdxOfTcpTxQueueDataType PduRouteIdxOfTcpTxQueueData;  /**< the index of the 1:1 relation pointing to SoAd_PduRoute */
} SoAd_TcpTxQueueDataType;

/**   \brief  type used in SoAd_TcpTxQueueMgt */
typedef struct sSoAd_TcpTxQueueMgtType
{
  SoAd_TotLenOfTcpTxQueueMgtType TotLenOfTcpTxQueueMgt;  /**< the total length of all used elements */
  SoAd_LvlOfTcpTxQueueMgtType LvlOfTcpTxQueueMgt;  /**< the level of used elements */
  SoAd_TcpTxQueueDataIdxOfTcpTxQueueMgtType TcpTxQueueDataIdxOfTcpTxQueueMgt;  /**< the index of the 1:1 relation pointing to SoAd_TcpTxQueueData */
} SoAd_TcpTxQueueMgtType;

/**   \brief  type used in SoAd_TimeoutListDyn */
typedef struct sSoAd_TimeoutListDynType
{
  SoAd_LvlOfTimeoutListDynType LvlOfTimeoutListDyn;  /**< the level of pending timeouts */
} SoAd_TimeoutListDynType;

/**   \brief  type used in SoAd_TimeoutListIdent */
typedef struct sSoAd_TimeoutListIdentType
{
  SoAd_TimeoutListDynNPduUdpTxIdxOfTimeoutListIdentType TimeoutListDynNPduUdpTxIdxOfTimeoutListIdent;  /**< the index of the 0:1 relation pointing to SoAd_TimeoutListDyn */
  SoAd_TimeoutListDynUdpAliveIdxOfTimeoutListIdentType TimeoutListDynUdpAliveIdxOfTimeoutListIdent;  /**< the index of the 0:1 relation pointing to SoAd_TimeoutListDyn */
} SoAd_TimeoutListIdentType;

/**   \brief  type used in SoAd_TimeoutListNPduUdpTx */
typedef struct sSoAd_TimeoutListNPduUdpTxType
{
  SoAd_TimeoutOfTimeoutListNPduUdpTxType TimeoutOfTimeoutListNPduUdpTx;  /**< the timeout value */
  SoAd_NPduUdpTxIdxOfTimeoutListNPduUdpTxType NPduUdpTxIdxOfTimeoutListNPduUdpTx;  /**< the index of the 0:1 relation pointing to SoAd_NPduUdpTx */
} SoAd_TimeoutListNPduUdpTxType;

/**   \brief  type used in SoAd_TimeoutListNPduUdpTxMap */
typedef struct sSoAd_TimeoutListNPduUdpTxMapType
{
  SoAd_TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMapType TimeoutListNPduUdpTxIdxOfTimeoutListNPduUdpTxMap;  /**< the index of the 0:1 relation pointing to SoAd_TimeoutListNPduUdpTx */
} SoAd_TimeoutListNPduUdpTxMapType;

/**   \brief  type used in SoAd_TimeoutListUdpAlive */
typedef struct sSoAd_TimeoutListUdpAliveType
{
  SoAd_TimeoutOfTimeoutListUdpAliveType TimeoutOfTimeoutListUdpAlive;  /**< the timeout value */
  SoAd_SoConIdxOfTimeoutListUdpAliveType SoConIdxOfTimeoutListUdpAlive;  /**< the index of the 0:1 relation pointing to SoAd_SoCon */
} SoAd_TimeoutListUdpAliveType;

/**   \brief  type used in SoAd_TimeoutListUdpAliveMap */
typedef struct sSoAd_TimeoutListUdpAliveMapType
{
  SoAd_TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMapType TimeoutListUdpAliveIdxOfTimeoutListUdpAliveMap;  /**< the index of the 0:1 relation pointing to SoAd_TimeoutListUdpAlive */
} SoAd_TimeoutListUdpAliveMapType;

/**   \brief  type used in SoAd_TlsConfig */
typedef struct sSoAd_TlsConfigType
{
  SoAd_RxBufSizeOfTlsConfigType RxBufSizeOfTlsConfig;  /**< the TLS Rx buffer size */
  SoAd_TcpTlsSocketCreatedNotificationCbkIdxOfTlsConfigType TcpTlsSocketCreatedNotificationCbkIdxOfTlsConfig;  /**< the index of the 0:1 relation pointing to SoAd_TcpTlsSocketCreatedNotificationCbk */
  SoAd_TxBufSizeOfTlsConfigType TxBufSizeOfTlsConfig;  /**< the TLS Tx buffer size */
} SoAd_TlsConfigType;

/**   \brief  type used in SoAd_TpTxBufferConfig */
typedef struct sSoAd_TpTxBufferConfigType
{
  SoAd_TpTxBufferEndIdxOfTpTxBufferConfigType TpTxBufferEndIdxOfTpTxBufferConfig;  /**< the end index of the 0:n relation pointing to SoAd_TpTxBuffer */
  SoAd_TpTxBufferStartIdxOfTpTxBufferConfigType TpTxBufferStartIdxOfTpTxBufferConfig;  /**< the start index of the 0:n relation pointing to SoAd_TpTxBuffer */
} SoAd_TpTxBufferConfigType;

/**   \brief  type used in SoAd_TpTxBufferConfigDyn */
typedef struct sSoAd_TpTxBufferConfigDynType
{
  SoAd_TpTxBufferIdxOfTpTxBufferConfigDynType TpTxBufferIdxOfTpTxBufferConfigDyn;  /**< the index of the 1:1 relation pointing to SoAd_TpTxBuffer */
} SoAd_TpTxBufferConfigDynType;

/**   \brief  type used in SoAd_TriggerBufConfig */
typedef struct sSoAd_TriggerBufConfigType
{
  SoAd_TriggerBufEndIdxOfTriggerBufConfigType TriggerBufEndIdxOfTriggerBufConfig;  /**< the end index of the 1:n relation pointing to SoAd_TriggerBuf */
  SoAd_TriggerBufStartIdxOfTriggerBufConfigType TriggerBufStartIdxOfTriggerBufConfig;  /**< the start index of the 1:n relation pointing to SoAd_TriggerBuf */
} SoAd_TriggerBufConfigType;

/**   \brief  type used in SoAd_TriggerBufConfigDyn */
typedef struct sSoAd_TriggerBufConfigDynType
{
  SoAd_LengthOfTriggerBufConfigDynType LengthOfTriggerBufConfigDyn;  /**< the length of the used part of the buffer */
  SoAd_PduRouteIdxOfTriggerBufConfigDynType PduRouteIdxOfTriggerBufConfigDyn;  /**< the index of the 1:1 relation pointing to SoAd_PduRoute */
} SoAd_TriggerBufConfigDynType;

/**   \brief  type used in SoAd_TxMgt */
typedef struct sSoAd_TxMgtType
{
  SoAd_CancelRequestedOfTxMgtType CancelRequestedOfTxMgt;  /**< indicates if transmission cancellation is requested */
  SoAd_PduRouteDestIdxOfTxMgtType PduRouteDestIdxOfTxMgt;  /**< the index of the 1:1 relation pointing to SoAd_PduRouteDest */
  SoAd_TxBytesLenOfTxMgtType TxBytesLenOfTxMgt;  /**< the length of data to be transmitted */
  SoAd_TxBytesPendingOfTxMgtType TxBytesPendingOfTxMgt;  /**< the length of pending data to be transmitted */
  SduDataPtrType TxBufPtrOfTxMgt;  /**< the pointer to transmission data buffer */
} SoAd_TxMgtType;

/**   \brief  type used in SoAd_TxPduIdMap */
typedef struct sSoAd_TxPduIdMapType
{
  SoAd_InvalidHndOfTxPduIdMapType InvalidHndOfTxPduIdMap;  /**< FALSE, if the handle of SoAd_TxPduIdMap is valid and can be used in the embedded code for further processing in the embedded code. */
  SoAd_PduRouteIdxOfTxPduIdMapType PduRouteIdxOfTxPduIdMap;  /**< the index of the 1:1 relation pointing to SoAd_PduRoute */
} SoAd_TxPduIdMapType;

/**   \brief  type used in SoAd_UpperLayer */
typedef struct sSoAd_UpperLayerType
{
  SoAd_IfRxIndicationCbkType IfRxIndicationCbkOfUpperLayer;  /**< the callback Up_[SoAd][If]RxIndication */
  SoAd_IfTriggerTransmitCbkType IfTriggerTransmitCbkOfUpperLayer;  /**< the callback Up_[SoAd][If]TriggerTransmit */
  SoAd_IfTxConfirmationCbkType IfTxConfirmationCbkOfUpperLayer;  /**< the callback Up_[SoAd][If]TxConfirmation */
  SoAd_TpCopyRxDataCbkType TpCopyRxDataCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]CopyRxData */
  SoAd_TpCopyRxDataConstCbkType TpCopyRxDataConstCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]CopyRxData with const data pointer */
  SoAd_TpCopyTxDataCbkType TpCopyTxDataCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]CopyTxData */
  SoAd_TpCopyTxDataConstCbkType TpCopyTxDataConstCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]CopyTxData with const data pointer */
  SoAd_TpRxIndicationCbkType TpRxIndicationCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]RxIndication */
  SoAd_TpStartOfReceptionCbkType TpStartOfReceptionCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]StartOfReception */
  SoAd_TpStartOfReceptionConstCbkType TpStartOfReceptionConstCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]StartOfReception with const data pointer */
  SoAd_TpTxConfirmationCbkType TpTxConfirmationCbkOfUpperLayer;  /**< the callback Up_[SoAd][Tp]TxConfirmation */
} SoAd_UpperLayerType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCSymbolicStructTypes  SoAd Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to SoAd_EventQueueDyn */
typedef struct SoAd_EventQueueDynStructSTag
{
  SoAd_EventQueueDynType SoAdEventQueueStateSoCon;
  SoAd_EventQueueDynType SoAdEventQueueIfUdpPduRoute;
} SoAd_EventQueueDynStructSType;

/**   \brief  type to be used as symbolic data element access to SoAd_EventQueueIfUdpPduRoute */
typedef struct SoAd_EventQueueIfUdpPduRouteStructSTag
{
  SoAd_EventQueueIfUdpPduRouteType SoAd;
} SoAd_EventQueueIfUdpPduRouteStructSType;

/**   \brief  type to be used as symbolic data element access to SoAd_EventQueueStateSoCon */
typedef struct SoAd_EventQueueStateSoConStructSTag
{
  SoAd_EventQueueStateSoConType SoAd[2];
} SoAd_EventQueueStateSoConStructSType;

/**   \brief  type to be used as symbolic data element access to SoAd_PduRouteDyn */
typedef struct SoAd_PduRouteDynStructSTag
{
  SoAd_PduRouteDynType SoAdPduRoute_NM_Tx;
} SoAd_PduRouteDynStructSType;

/**   \brief  type to be used as symbolic data element access to SoAd_RxMgt */
typedef struct SoAd_RxMgtStructSTag
{
  SoAd_RxMgtType SC_UDP_ANY_DynPort_Remote;
} SoAd_RxMgtStructSType;

/**   \brief  type to be used as symbolic data element access to SoAd_TxMgt */
typedef struct SoAd_TxMgtStructSTag
{
  SoAd_TxMgtType SC_UDP_Multicast_Fixed_239_10_0_1_30000_Remote;
} SoAd_TxMgtStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCUnionIndexAndSymbolTypes  SoAd Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access SoAd_EventQueueDyn in an index and symbol based style. */
typedef union SoAd_EventQueueDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_EventQueueDynType raw[2];
  SoAd_EventQueueDynStructSType str;
} SoAd_EventQueueDynUType;

/**   \brief  type to access SoAd_EventQueueIfUdpPduRoute in an index and symbol based style. */
typedef union SoAd_EventQueueIfUdpPduRouteUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_EventQueueIfUdpPduRouteType raw[1];
  SoAd_EventQueueIfUdpPduRouteStructSType str;
} SoAd_EventQueueIfUdpPduRouteUType;

/**   \brief  type to access SoAd_EventQueueStateSoCon in an index and symbol based style. */
typedef union SoAd_EventQueueStateSoConUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_EventQueueStateSoConType raw[2];
  SoAd_EventQueueStateSoConStructSType str;
} SoAd_EventQueueStateSoConUType;

/**   \brief  type to access SoAd_PduRouteDyn in an index and symbol based style. */
typedef union SoAd_PduRouteDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_PduRouteDynType raw[1];
  SoAd_PduRouteDynStructSType str;
} SoAd_PduRouteDynUType;

/**   \brief  type to access SoAd_RxMgt in an index and symbol based style. */
typedef union SoAd_RxMgtUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_RxMgtType raw[1];
  SoAd_RxMgtStructSType str;
} SoAd_RxMgtUType;

/**   \brief  type to access SoAd_TxMgt in an index and symbol based style. */
typedef union SoAd_TxMgtUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  SoAd_TxMgtType raw[1];
  SoAd_TxMgtStructSType str;
} SoAd_TxMgtUType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCRootPointerTypes  SoAd Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to SoAd_BestMatchSoConIdxList */
typedef P2VAR(SoAd_BestMatchSoConIdxListType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_BestMatchSoConIdxListPtrType;

/**   \brief  type used to point to SoAd_DhcpEventCbk */
typedef P2CONST(SoAd_DhcpEventCbkType, TYPEDEF, SOAD_CONST) SoAd_DhcpEventCbkPtrType;

/**   \brief  type used to point to SoAd_EventQueue */
typedef P2CONST(SoAd_EventQueueType, TYPEDEF, SOAD_CONST) SoAd_EventQueuePtrType;

/**   \brief  type used to point to SoAd_EventQueueDyn */
typedef P2VAR(SoAd_EventQueueDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueDynPtrType;

/**   \brief  type used to point to SoAd_EventQueueFlag */
typedef P2VAR(SoAd_EventQueueFlagType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueFlagPtrType;

/**   \brief  type used to point to SoAd_EventQueueIdent */
typedef P2CONST(SoAd_EventQueueIdentType, TYPEDEF, SOAD_CONST) SoAd_EventQueueIdentPtrType;

/**   \brief  type used to point to SoAd_EventQueueIfTxRouteGrp */
typedef P2VAR(SoAd_EventQueueIfTxRouteGrpType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueIfTxRouteGrpPtrType;

/**   \brief  type used to point to SoAd_EventQueueIfUdpPduRoute */
typedef P2VAR(SoAd_EventQueueIfUdpPduRouteType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueIfUdpPduRoutePtrType;

/**   \brief  type used to point to SoAd_EventQueueLocalAddr */
typedef P2VAR(SoAd_EventQueueLocalAddrType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueLocalAddrPtrType;

/**   \brief  type used to point to SoAd_EventQueueSocketIdx */
typedef P2VAR(SoAd_EventQueueSocketIdxType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueSocketIdxPtrType;

/**   \brief  type used to point to SoAd_EventQueueStateSoCon */
typedef P2VAR(SoAd_EventQueueStateSoConType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueStateSoConPtrType;

/**   \brief  type used to point to SoAd_EventQueueTcpTxSoCon */
typedef P2VAR(SoAd_EventQueueTcpTxSoConType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueTcpTxSoConPtrType;

/**   \brief  type used to point to SoAd_EventQueueTpRxSoCon */
typedef P2VAR(SoAd_EventQueueTpRxSoConType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueTpRxSoConPtrType;

/**   \brief  type used to point to SoAd_EventQueueTpTxSoCon */
typedef P2VAR(SoAd_EventQueueTpTxSoConType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_EventQueueTpTxSoConPtrType;

/**   \brief  type used to point to SoAd_IfRxBuffer */
typedef P2VAR(SoAd_IfRxBufferType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_IfRxBufferPtrType;

/**   \brief  type used to point to SoAd_IpFragBuf */
typedef P2VAR(SoAd_IpFragBufType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_IpFragBufPtrType;

/**   \brief  type used to point to SoAd_IpFragBufConfig */
typedef P2CONST(SoAd_IpFragBufConfigType, TYPEDEF, SOAD_CONST) SoAd_IpFragBufConfigPtrType;

/**   \brief  type used to point to SoAd_IpFragBufConfigDyn */
typedef P2VAR(SoAd_IpFragBufConfigDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_IpFragBufConfigDynPtrType;

/**   \brief  type used to point to SoAd_IpFragMgt */
typedef P2VAR(SoAd_IpFragMgtType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_IpFragMgtPtrType;

/**   \brief  type used to point to SoAd_LocalAddr */
typedef P2CONST(SoAd_LocalAddrType, TYPEDEF, SOAD_CONST) SoAd_LocalAddrPtrType;

/**   \brief  type used to point to SoAd_LocalAddrByTcpIpCtrlInd */
typedef P2CONST(SoAd_LocalAddrByTcpIpCtrlIndType, TYPEDEF, SOAD_CONST) SoAd_LocalAddrByTcpIpCtrlIndPtrType;

/**   \brief  type used to point to SoAd_LocalAddrDyn */
typedef P2VAR(SoAd_LocalAddrDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_LocalAddrDynPtrType;

/**   \brief  type used to point to SoAd_LocalAddrIdMap */
typedef P2CONST(SoAd_LocalAddrIdMapType, TYPEDEF, SOAD_CONST) SoAd_LocalAddrIdMapPtrType;

/**   \brief  type used to point to SoAd_LocalIpAddrAssignmentChgCbk */
typedef P2CONST(SoAd_LocalIpAddrAssignmentChgCbkType, TYPEDEF, SOAD_CONST) SoAd_LocalIpAddrAssignmentChgCbkPtrType;

/**   \brief  type used to point to SoAd_LocalIpAddrAssignmentChgCbkInd */
typedef P2CONST(SoAd_LocalIpAddrAssignmentChgCbkIndType, TYPEDEF, SOAD_CONST) SoAd_LocalIpAddrAssignmentChgCbkIndPtrType;

/**   \brief  type used to point to SoAd_MetaDataRxBuf */
typedef P2VAR(SoAd_MetaDataRxBufType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_MetaDataRxBufPtrType;

/**   \brief  type used to point to SoAd_NPduUdpTx */
typedef P2CONST(SoAd_NPduUdpTxType, TYPEDEF, SOAD_CONST) SoAd_NPduUdpTxPtrType;

/**   \brief  type used to point to SoAd_NPduUdpTxBuffer */
typedef P2VAR(SoAd_NPduUdpTxBufferType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_NPduUdpTxBufferPtrType;

/**   \brief  type used to point to SoAd_NPduUdpTxDyn */
typedef P2VAR(SoAd_NPduUdpTxDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_NPduUdpTxDynPtrType;

/**   \brief  type used to point to SoAd_NPduUdpTxQueue */
typedef P2VAR(SoAd_NPduUdpTxQueueType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_NPduUdpTxQueuePtrType;

/**   \brief  type used to point to SoAd_PduRoute */
typedef P2CONST(SoAd_PduRouteType, TYPEDEF, SOAD_CONST) SoAd_PduRoutePtrType;

/**   \brief  type used to point to SoAd_PduRouteDest */
typedef P2CONST(SoAd_PduRouteDestType, TYPEDEF, SOAD_CONST) SoAd_PduRouteDestPtrType;

/**   \brief  type used to point to SoAd_PduRouteDestBySoConInd */
typedef P2CONST(SoAd_PduRouteDestBySoConIndType, TYPEDEF, SOAD_CONST) SoAd_PduRouteDestBySoConIndPtrType;

/**   \brief  type used to point to SoAd_PduRouteDestInd */
typedef P2CONST(SoAd_PduRouteDestIndType, TYPEDEF, SOAD_CONST) SoAd_PduRouteDestIndPtrType;

/**   \brief  type used to point to SoAd_PduRouteDyn */
typedef P2VAR(SoAd_PduRouteDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_PduRouteDynPtrType;

/**   \brief  type used to point to SoAd_RcvRemAddr */
typedef P2VAR(SoAd_SockAddrInetXType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RcvRemAddrPtrType;

/**   \brief  type used to point to SoAd_AddrOfRemAddrIpV4 */
typedef P2CONST(SoAd_IpAddrInetType, TYPEDEF, SOAD_CONST) SoAd_AddrOfRemAddrIpV4PtrType;

/**   \brief  type used to point to SoAd_RemAddrIpV4 */
typedef P2CONST(SoAd_RemAddrIpV4Type, TYPEDEF, SOAD_CONST) SoAd_RemAddrIpV4PtrType;

/**   \brief  type used to point to SoAd_AddrOfRemAddrIpV6 */
typedef P2CONST(SoAd_IpAddrInet6Type, TYPEDEF, SOAD_CONST) SoAd_AddrOfRemAddrIpV6PtrType;

/**   \brief  type used to point to SoAd_RemAddrIpV6 */
typedef P2CONST(SoAd_RemAddrIpV6Type, TYPEDEF, SOAD_CONST) SoAd_RemAddrIpV6PtrType;

/**   \brief  type used to point to SoAd_RouteGrp */
typedef P2CONST(SoAd_RouteGrpType, TYPEDEF, SOAD_CONST) SoAd_RouteGrpPtrType;

/**   \brief  type used to point to SoAd_RouteGrpIdMap */
typedef P2CONST(SoAd_RouteGrpIdMapType, TYPEDEF, SOAD_CONST) SoAd_RouteGrpIdMapPtrType;

/**   \brief  type used to point to SoAd_RouteGrpSoCon */
typedef P2CONST(SoAd_RouteGrpSoConType, TYPEDEF, SOAD_CONST) SoAd_RouteGrpSoConPtrType;

/**   \brief  type used to point to SoAd_RouteGrpSoConByPduRouteDestInd */
typedef P2CONST(SoAd_RouteGrpSoConByPduRouteDestIndType, TYPEDEF, SOAD_CONST) SoAd_RouteGrpSoConByPduRouteDestIndPtrType;

/**   \brief  type used to point to SoAd_RouteGrpSoConBySocketRouteDestInd */
typedef P2CONST(SoAd_RouteGrpSoConBySocketRouteDestIndType, TYPEDEF, SOAD_CONST) SoAd_RouteGrpSoConBySocketRouteDestIndPtrType;

/**   \brief  type used to point to SoAd_RouteGrpSoConDyn */
typedef P2VAR(SoAd_RouteGrpSoConDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RouteGrpSoConDynPtrType;

/**   \brief  type used to point to SoAd_RxBufStructMgt */
typedef P2VAR(SoAd_RxBufStructMgtType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RxBufStructMgtPtrType;

/**   \brief  type used to point to SoAd_RxBufStructSeg */
typedef P2VAR(SoAd_RxBufStructSegType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RxBufStructSegPtrType;

/**   \brief  type used to point to SoAd_DataPtrOfRxBufStructSeg */
typedef P2VAR(SoAd_DataPtrType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_DataPtrOfRxBufStructSegPtrType;

/**   \brief  type used to point to SoAd_RxBufferConfig */
typedef P2CONST(SoAd_RxBufferConfigType, TYPEDEF, SOAD_CONST) SoAd_RxBufferConfigPtrType;

/**   \brief  type used to point to SoAd_RxBufferConfigDyn */
typedef P2VAR(SoAd_RxBufferConfigDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RxBufferConfigDynPtrType;

/**   \brief  type used to point to SoAd_RxMgt */
typedef P2VAR(SoAd_RxMgtType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RxMgtPtrType;

/**   \brief  type used to point to SoAd_RxPduIdIdMap */
typedef P2CONST(SoAd_RxPduIdIdMapType, TYPEDEF, SOAD_CONST) SoAd_RxPduIdIdMapPtrType;

/**   \brief  type used to point to SoAd_ShutdownFinishedCbk */
typedef P2CONST(SoAd_ShutdownFinishedCbkType, TYPEDEF, SOAD_CONST) SoAd_ShutdownFinishedCbkPtrType;

/**   \brief  type used to point to SoAd_SoCon */
typedef P2CONST(SoAd_SoConType, TYPEDEF, SOAD_CONST) SoAd_SoConPtrType;

/**   \brief  type used to point to SoAd_SoConDyn */
typedef P2VAR(SoAd_SoConDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_SoConDynPtrType;

/**   \brief  type used to point to SoAd_RemAddrDynOfSoConDyn */
typedef P2VAR(SoAd_SockAddrInetXType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_RemAddrDynOfSoConDynPtrType;

/**   \brief  type used to point to SoAd_SoConGrp */
typedef P2CONST(SoAd_SoConGrpType, TYPEDEF, SOAD_CONST) SoAd_SoConGrpPtrType;

/**   \brief  type used to point to SoAd_SoConMap */
typedef P2CONST(SoAd_SoConMapType, TYPEDEF, SOAD_CONST) SoAd_SoConMapPtrType;

/**   \brief  type used to point to SoAd_SoConModeChgCbk */
typedef P2CONST(SoAd_SoConModeChgCbkType, TYPEDEF, SOAD_CONST) SoAd_SoConModeChgCbkPtrType;

/**   \brief  type used to point to SoAd_SoConModeChgCbkInd */
typedef P2CONST(SoAd_SoConModeChgCbkIndType, TYPEDEF, SOAD_CONST) SoAd_SoConModeChgCbkIndPtrType;

/**   \brief  type used to point to SoAd_Socket */
typedef P2CONST(SoAd_SocketType, TYPEDEF, SOAD_CONST) SoAd_SocketPtrType;

/**   \brief  type used to point to SoAd_SocketDyn */
typedef P2VAR(SoAd_SocketDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_SocketDynPtrType;

/**   \brief  type used to point to SoAd_SocketReportErrorCbk */
typedef P2CONST(SoAd_SocketReportErrorCbkType, TYPEDEF, SOAD_CONST) SoAd_SocketReportErrorCbkPtrType;

/**   \brief  type used to point to SoAd_SocketRoute */
typedef P2CONST(SoAd_SocketRouteType, TYPEDEF, SOAD_CONST) SoAd_SocketRoutePtrType;

/**   \brief  type used to point to SoAd_SocketRouteDest */
typedef P2CONST(SoAd_SocketRouteDestType, TYPEDEF, SOAD_CONST) SoAd_SocketRouteDestPtrType;

/**   \brief  type used to point to SoAd_SocketRouteInd */
typedef P2CONST(SoAd_SocketRouteIndType, TYPEDEF, SOAD_CONST) SoAd_SocketRouteIndPtrType;

/**   \brief  type used to point to SoAd_SocketTcp */
typedef P2CONST(SoAd_SocketTcpType, TYPEDEF, SOAD_CONST) SoAd_SocketTcpPtrType;

/**   \brief  type used to point to SoAd_SocketUdp */
typedef P2CONST(SoAd_SocketUdpType, TYPEDEF, SOAD_CONST) SoAd_SocketUdpPtrType;

/**   \brief  type used to point to SoAd_TcpIpCtrl */
typedef P2CONST(SoAd_TcpIpCtrlType, TYPEDEF, SOAD_CONST) SoAd_TcpIpCtrlPtrType;

/**   \brief  type used to point to SoAd_TcpKeepAliveGloballyEnabled */
typedef P2CONST(SoAd_TcpKeepAliveGloballyEnabledType, TYPEDEF, SOAD_CONST) SoAd_TcpKeepAliveGloballyEnabledPtrType;

/**   \brief  type used to point to SoAd_TcpTlsSocketCreatedNotificationCbk */
typedef P2CONST(SoAd_TcpTlsSocketCreatedNotificationCbkType, TYPEDEF, SOAD_CONST) SoAd_TcpTlsSocketCreatedNotificationCbkPtrType;

/**   \brief  type used to point to SoAd_TcpTxQueue */
typedef P2CONST(SoAd_TcpTxQueueType, TYPEDEF, SOAD_CONST) SoAd_TcpTxQueuePtrType;

/**   \brief  type used to point to SoAd_TcpTxQueueData */
typedef P2VAR(SoAd_TcpTxQueueDataType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TcpTxQueueDataPtrType;

/**   \brief  type used to point to SoAd_TcpTxQueueMgt */
typedef P2VAR(SoAd_TcpTxQueueMgtType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TcpTxQueueMgtPtrType;

/**   \brief  type used to point to SoAd_TimeoutListDyn */
typedef P2VAR(SoAd_TimeoutListDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TimeoutListDynPtrType;

/**   \brief  type used to point to SoAd_TimeoutListIdent */
typedef P2CONST(SoAd_TimeoutListIdentType, TYPEDEF, SOAD_CONST) SoAd_TimeoutListIdentPtrType;

/**   \brief  type used to point to SoAd_TimeoutListNPduUdpTx */
typedef P2VAR(SoAd_TimeoutListNPduUdpTxType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TimeoutListNPduUdpTxPtrType;

/**   \brief  type used to point to SoAd_TimeoutListNPduUdpTxMap */
typedef P2VAR(SoAd_TimeoutListNPduUdpTxMapType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TimeoutListNPduUdpTxMapPtrType;

/**   \brief  type used to point to SoAd_TimeoutListUdpAlive */
typedef P2VAR(SoAd_TimeoutListUdpAliveType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TimeoutListUdpAlivePtrType;

/**   \brief  type used to point to SoAd_TimeoutListUdpAliveMap */
typedef P2VAR(SoAd_TimeoutListUdpAliveMapType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TimeoutListUdpAliveMapPtrType;

/**   \brief  type used to point to SoAd_TlsConfig */
typedef P2CONST(SoAd_TlsConfigType, TYPEDEF, SOAD_CONST) SoAd_TlsConfigPtrType;

/**   \brief  type used to point to SoAd_TpRxBuffer */
typedef P2VAR(SoAd_TpRxBufferType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TpRxBufferPtrType;

/**   \brief  type used to point to SoAd_TpTxBuffer */
typedef P2VAR(SoAd_TpTxBufferType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TpTxBufferPtrType;

/**   \brief  type used to point to SoAd_TpTxBufferConfig */
typedef P2CONST(SoAd_TpTxBufferConfigType, TYPEDEF, SOAD_CONST) SoAd_TpTxBufferConfigPtrType;

/**   \brief  type used to point to SoAd_TpTxBufferConfigDyn */
typedef P2VAR(SoAd_TpTxBufferConfigDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TpTxBufferConfigDynPtrType;

/**   \brief  type used to point to SoAd_TriggerBuf */
typedef P2VAR(SoAd_TriggerBufType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TriggerBufPtrType;

/**   \brief  type used to point to SoAd_TriggerBufConfig */
typedef P2CONST(SoAd_TriggerBufConfigType, TYPEDEF, SOAD_CONST) SoAd_TriggerBufConfigPtrType;

/**   \brief  type used to point to SoAd_TriggerBufConfigDyn */
typedef P2VAR(SoAd_TriggerBufConfigDynType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TriggerBufConfigDynPtrType;

/**   \brief  type used to point to SoAd_TxMgt */
typedef P2VAR(SoAd_TxMgtType, TYPEDEF, SOAD_VAR_NOINIT) SoAd_TxMgtPtrType;

/**   \brief  type used to point to SoAd_TxPduIdMap */
typedef P2CONST(SoAd_TxPduIdMapType, TYPEDEF, SOAD_CONST) SoAd_TxPduIdMapPtrType;

/**   \brief  type used to point to SoAd_UpperLayer */
typedef P2CONST(SoAd_UpperLayerType, TYPEDEF, SOAD_CONST) SoAd_UpperLayerPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  SoAdPCRootValueTypes  SoAd Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in SoAd_PCConfig */
typedef struct sSoAd_PCConfigType
{
  SoAd_BestMatchSoConIdxListPtrType BestMatchSoConIdxListOfPCConfig;  /**< the pointer to SoAd_BestMatchSoConIdxList */
  SoAd_DhcpEventCbkPtrType DhcpEventCbkOfPCConfig;  /**< the pointer to SoAd_DhcpEventCbk */
  SoAd_EventQueuePtrType EventQueueOfPCConfig;  /**< the pointer to SoAd_EventQueue */
  SoAd_EventQueueDynPtrType EventQueueDynOfPCConfig;  /**< the pointer to SoAd_EventQueueDyn */
  SoAd_EventQueueFlagPtrType EventQueueFlagOfPCConfig;  /**< the pointer to SoAd_EventQueueFlag */
  SoAd_EventQueueIdentPtrType EventQueueIdentOfPCConfig;  /**< the pointer to SoAd_EventQueueIdent */
  SoAd_EventQueueIfTxRouteGrpPtrType EventQueueIfTxRouteGrpOfPCConfig;  /**< the pointer to SoAd_EventQueueIfTxRouteGrp */
  SoAd_EventQueueIfUdpPduRoutePtrType EventQueueIfUdpPduRouteOfPCConfig;  /**< the pointer to SoAd_EventQueueIfUdpPduRoute */
  SoAd_EventQueueLocalAddrPtrType EventQueueLocalAddrOfPCConfig;  /**< the pointer to SoAd_EventQueueLocalAddr */
  SoAd_EventQueueSocketIdxPtrType EventQueueSocketIdxOfPCConfig;  /**< the pointer to SoAd_EventQueueSocketIdx */
  SoAd_EventQueueStateSoConPtrType EventQueueStateSoConOfPCConfig;  /**< the pointer to SoAd_EventQueueStateSoCon */
  SoAd_EventQueueTcpTxSoConPtrType EventQueueTcpTxSoConOfPCConfig;  /**< the pointer to SoAd_EventQueueTcpTxSoCon */
  SoAd_EventQueueTpRxSoConPtrType EventQueueTpRxSoConOfPCConfig;  /**< the pointer to SoAd_EventQueueTpRxSoCon */
  SoAd_EventQueueTpTxSoConPtrType EventQueueTpTxSoConOfPCConfig;  /**< the pointer to SoAd_EventQueueTpTxSoCon */
  SoAd_IfRxBufferPtrType IfRxBufferOfPCConfig;  /**< the pointer to SoAd_IfRxBuffer */
  SoAd_IpFragBufPtrType IpFragBufOfPCConfig;  /**< the pointer to SoAd_IpFragBuf */
  SoAd_IpFragBufConfigPtrType IpFragBufConfigOfPCConfig;  /**< the pointer to SoAd_IpFragBufConfig */
  SoAd_IpFragBufConfigDynPtrType IpFragBufConfigDynOfPCConfig;  /**< the pointer to SoAd_IpFragBufConfigDyn */
  SoAd_IpFragMgtPtrType IpFragMgtOfPCConfig;  /**< the pointer to SoAd_IpFragMgt */
  SoAd_LocalAddrPtrType LocalAddrOfPCConfig;  /**< the pointer to SoAd_LocalAddr */
  SoAd_LocalAddrByTcpIpCtrlIndPtrType LocalAddrByTcpIpCtrlIndOfPCConfig;  /**< the pointer to SoAd_LocalAddrByTcpIpCtrlInd */
  SoAd_LocalAddrDynPtrType LocalAddrDynOfPCConfig;  /**< the pointer to SoAd_LocalAddrDyn */
  SoAd_LocalAddrIdMapPtrType LocalAddrIdMapOfPCConfig;  /**< the pointer to SoAd_LocalAddrIdMap */
  SoAd_LocalIpAddrAssignmentChgCbkPtrType LocalIpAddrAssignmentChgCbkOfPCConfig;  /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbk */
  SoAd_LocalIpAddrAssignmentChgCbkIndPtrType LocalIpAddrAssignmentChgCbkIndOfPCConfig;  /**< the pointer to SoAd_LocalIpAddrAssignmentChgCbkInd */
  SoAd_MetaDataRxBufPtrType MetaDataRxBufOfPCConfig;  /**< the pointer to SoAd_MetaDataRxBuf */
  SoAd_NPduUdpTxPtrType NPduUdpTxOfPCConfig;  /**< the pointer to SoAd_NPduUdpTx */
  SoAd_NPduUdpTxBufferPtrType NPduUdpTxBufferOfPCConfig;  /**< the pointer to SoAd_NPduUdpTxBuffer */
  SoAd_NPduUdpTxDynPtrType NPduUdpTxDynOfPCConfig;  /**< the pointer to SoAd_NPduUdpTxDyn */
  SoAd_NPduUdpTxQueuePtrType NPduUdpTxQueueOfPCConfig;  /**< the pointer to SoAd_NPduUdpTxQueue */
  SoAd_PduRoutePtrType PduRouteOfPCConfig;  /**< the pointer to SoAd_PduRoute */
  SoAd_PduRouteDestPtrType PduRouteDestOfPCConfig;  /**< the pointer to SoAd_PduRouteDest */
  SoAd_PduRouteDestBySoConIndPtrType PduRouteDestBySoConIndOfPCConfig;  /**< the pointer to SoAd_PduRouteDestBySoConInd */
  SoAd_PduRouteDestIndPtrType PduRouteDestIndOfPCConfig;  /**< the pointer to SoAd_PduRouteDestInd */
  SoAd_PduRouteDynPtrType PduRouteDynOfPCConfig;  /**< the pointer to SoAd_PduRouteDyn */
  SoAd_RcvRemAddrPtrType RcvRemAddrOfPCConfig;  /**< the pointer to SoAd_RcvRemAddr */
  SoAd_RemAddrIpV4PtrType RemAddrIpV4OfPCConfig;  /**< the pointer to SoAd_RemAddrIpV4 */
  SoAd_RemAddrIpV6PtrType RemAddrIpV6OfPCConfig;  /**< the pointer to SoAd_RemAddrIpV6 */
  SoAd_RouteGrpPtrType RouteGrpOfPCConfig;  /**< the pointer to SoAd_RouteGrp */
  SoAd_RouteGrpIdMapPtrType RouteGrpIdMapOfPCConfig;  /**< the pointer to SoAd_RouteGrpIdMap */
  SoAd_RouteGrpSoConPtrType RouteGrpSoConOfPCConfig;  /**< the pointer to SoAd_RouteGrpSoCon */
  SoAd_RouteGrpSoConByPduRouteDestIndPtrType RouteGrpSoConByPduRouteDestIndOfPCConfig;  /**< the pointer to SoAd_RouteGrpSoConByPduRouteDestInd */
  SoAd_RouteGrpSoConBySocketRouteDestIndPtrType RouteGrpSoConBySocketRouteDestIndOfPCConfig;  /**< the pointer to SoAd_RouteGrpSoConBySocketRouteDestInd */
  SoAd_RouteGrpSoConDynPtrType RouteGrpSoConDynOfPCConfig;  /**< the pointer to SoAd_RouteGrpSoConDyn */
  SoAd_RxBufStructMgtPtrType RxBufStructMgtOfPCConfig;  /**< the pointer to SoAd_RxBufStructMgt */
  SoAd_RxBufStructSegPtrType RxBufStructSegOfPCConfig;  /**< the pointer to SoAd_RxBufStructSeg */
  SoAd_RxBufferConfigPtrType RxBufferConfigOfPCConfig;  /**< the pointer to SoAd_RxBufferConfig */
  SoAd_RxBufferConfigDynPtrType RxBufferConfigDynOfPCConfig;  /**< the pointer to SoAd_RxBufferConfigDyn */
  SoAd_RxMgtPtrType RxMgtOfPCConfig;  /**< the pointer to SoAd_RxMgt */
  SoAd_RxPduIdIdMapPtrType RxPduIdIdMapOfPCConfig;  /**< the pointer to SoAd_RxPduIdIdMap */
  SoAd_ShutdownFinishedCbkPtrType ShutdownFinishedCbkOfPCConfig;  /**< the pointer to SoAd_ShutdownFinishedCbk */
  SoAd_SoConPtrType SoConOfPCConfig;  /**< the pointer to SoAd_SoCon */
  SoAd_SoConDynPtrType SoConDynOfPCConfig;  /**< the pointer to SoAd_SoConDyn */
  SoAd_SoConGrpPtrType SoConGrpOfPCConfig;  /**< the pointer to SoAd_SoConGrp */
  SoAd_SoConMapPtrType SoConMapOfPCConfig;  /**< the pointer to SoAd_SoConMap */
  SoAd_SoConModeChgCbkPtrType SoConModeChgCbkOfPCConfig;  /**< the pointer to SoAd_SoConModeChgCbk */
  SoAd_SoConModeChgCbkIndPtrType SoConModeChgCbkIndOfPCConfig;  /**< the pointer to SoAd_SoConModeChgCbkInd */
  SoAd_SocketPtrType SocketOfPCConfig;  /**< the pointer to SoAd_Socket */
  SoAd_SocketDynPtrType SocketDynOfPCConfig;  /**< the pointer to SoAd_SocketDyn */
  SoAd_SocketReportErrorCbkPtrType SocketReportErrorCbkOfPCConfig;  /**< the pointer to SoAd_SocketReportErrorCbk */
  SoAd_SocketRoutePtrType SocketRouteOfPCConfig;  /**< the pointer to SoAd_SocketRoute */
  SoAd_SocketRouteDestPtrType SocketRouteDestOfPCConfig;  /**< the pointer to SoAd_SocketRouteDest */
  SoAd_SocketRouteIndPtrType SocketRouteIndOfPCConfig;  /**< the pointer to SoAd_SocketRouteInd */
  SoAd_SocketTcpPtrType SocketTcpOfPCConfig;  /**< the pointer to SoAd_SocketTcp */
  SoAd_SocketUdpPtrType SocketUdpOfPCConfig;  /**< the pointer to SoAd_SocketUdp */
  SoAd_TcpIpCtrlPtrType TcpIpCtrlOfPCConfig;  /**< the pointer to SoAd_TcpIpCtrl */
  SoAd_TcpKeepAliveGloballyEnabledPtrType TcpKeepAliveGloballyEnabledOfPCConfig;  /**< the pointer to SoAd_TcpKeepAliveGloballyEnabled */
  SoAd_TcpTlsSocketCreatedNotificationCbkPtrType TcpTlsSocketCreatedNotificationCbkOfPCConfig;  /**< the pointer to SoAd_TcpTlsSocketCreatedNotificationCbk */
  SoAd_TcpTxQueuePtrType TcpTxQueueOfPCConfig;  /**< the pointer to SoAd_TcpTxQueue */
  SoAd_TcpTxQueueDataPtrType TcpTxQueueDataOfPCConfig;  /**< the pointer to SoAd_TcpTxQueueData */
  SoAd_TcpTxQueueMgtPtrType TcpTxQueueMgtOfPCConfig;  /**< the pointer to SoAd_TcpTxQueueMgt */
  SoAd_TimeoutListDynPtrType TimeoutListDynOfPCConfig;  /**< the pointer to SoAd_TimeoutListDyn */
  SoAd_TimeoutListIdentPtrType TimeoutListIdentOfPCConfig;  /**< the pointer to SoAd_TimeoutListIdent */
  SoAd_TimeoutListNPduUdpTxPtrType TimeoutListNPduUdpTxOfPCConfig;  /**< the pointer to SoAd_TimeoutListNPduUdpTx */
  SoAd_TimeoutListNPduUdpTxMapPtrType TimeoutListNPduUdpTxMapOfPCConfig;  /**< the pointer to SoAd_TimeoutListNPduUdpTxMap */
  SoAd_TimeoutListUdpAlivePtrType TimeoutListUdpAliveOfPCConfig;  /**< the pointer to SoAd_TimeoutListUdpAlive */
  SoAd_TimeoutListUdpAliveMapPtrType TimeoutListUdpAliveMapOfPCConfig;  /**< the pointer to SoAd_TimeoutListUdpAliveMap */
  SoAd_TlsConfigPtrType TlsConfigOfPCConfig;  /**< the pointer to SoAd_TlsConfig */
  SoAd_TpRxBufferPtrType TpRxBufferOfPCConfig;  /**< the pointer to SoAd_TpRxBuffer */
  SoAd_TpTxBufferPtrType TpTxBufferOfPCConfig;  /**< the pointer to SoAd_TpTxBuffer */
  SoAd_TpTxBufferConfigPtrType TpTxBufferConfigOfPCConfig;  /**< the pointer to SoAd_TpTxBufferConfig */
  SoAd_TpTxBufferConfigDynPtrType TpTxBufferConfigDynOfPCConfig;  /**< the pointer to SoAd_TpTxBufferConfigDyn */
  SoAd_TriggerBufPtrType TriggerBufOfPCConfig;  /**< the pointer to SoAd_TriggerBuf */
  SoAd_TriggerBufConfigPtrType TriggerBufConfigOfPCConfig;  /**< the pointer to SoAd_TriggerBufConfig */
  SoAd_TriggerBufConfigDynPtrType TriggerBufConfigDynOfPCConfig;  /**< the pointer to SoAd_TriggerBufConfigDyn */
  SoAd_TxMgtPtrType TxMgtOfPCConfig;  /**< the pointer to SoAd_TxMgt */
  SoAd_TxPduIdMapPtrType TxPduIdMapOfPCConfig;  /**< the pointer to SoAd_TxPduIdMap */
  SoAd_UpperLayerPtrType UpperLayerOfPCConfig;  /**< the pointer to SoAd_UpperLayer */
  SoAd_MaxIfRouteGrpTransmitPduSizeType MaxIfRouteGrpTransmitPduSizeOfPCConfig;  /**< the maximum length of all PDUs which can be sent via routing group transmit */
  SoAd_SizeOfBestMatchSoConIdxListType SizeOfBestMatchSoConIdxListOfPCConfig;  /**< the number of accomplishable value elements in SoAd_BestMatchSoConIdxList */
  SoAd_SizeOfDhcpEventCbkType SizeOfDhcpEventCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_DhcpEventCbk */
  SoAd_SizeOfEventQueueType SizeOfEventQueueOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueue */
  SoAd_SizeOfEventQueueFlagType SizeOfEventQueueFlagOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueFlag */
  SoAd_SizeOfEventQueueIdentType SizeOfEventQueueIdentOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueIdent */
  SoAd_SizeOfEventQueueIfTxRouteGrpType SizeOfEventQueueIfTxRouteGrpOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueIfTxRouteGrp */
  SoAd_SizeOfEventQueueIfUdpPduRouteType SizeOfEventQueueIfUdpPduRouteOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueIfUdpPduRoute */
  SoAd_SizeOfEventQueueLocalAddrType SizeOfEventQueueLocalAddrOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueLocalAddr */
  SoAd_SizeOfEventQueueSocketIdxType SizeOfEventQueueSocketIdxOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueSocketIdx */
  SoAd_SizeOfEventQueueStateSoConType SizeOfEventQueueStateSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueStateSoCon */
  SoAd_SizeOfEventQueueTcpTxSoConType SizeOfEventQueueTcpTxSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueTcpTxSoCon */
  SoAd_SizeOfEventQueueTpRxSoConType SizeOfEventQueueTpRxSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueTpRxSoCon */
  SoAd_SizeOfEventQueueTpTxSoConType SizeOfEventQueueTpTxSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_EventQueueTpTxSoCon */
  SoAd_SizeOfIfRxBufferType SizeOfIfRxBufferOfPCConfig;  /**< the number of accomplishable value elements in SoAd_IfRxBuffer */
  SoAd_SizeOfIpFragBufType SizeOfIpFragBufOfPCConfig;  /**< the number of accomplishable value elements in SoAd_IpFragBuf */
  SoAd_SizeOfIpFragBufConfigType SizeOfIpFragBufConfigOfPCConfig;  /**< the number of accomplishable value elements in SoAd_IpFragBufConfig */
  SoAd_SizeOfIpFragMgtType SizeOfIpFragMgtOfPCConfig;  /**< the number of accomplishable value elements in SoAd_IpFragMgt */
  SoAd_SizeOfLocalAddrType SizeOfLocalAddrOfPCConfig;  /**< the number of accomplishable value elements in SoAd_LocalAddr */
  SoAd_SizeOfLocalAddrByTcpIpCtrlIndType SizeOfLocalAddrByTcpIpCtrlIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_LocalAddrByTcpIpCtrlInd */
  SoAd_SizeOfLocalAddrIdMapType SizeOfLocalAddrIdMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_LocalAddrIdMap */
  SoAd_SizeOfLocalIpAddrAssignmentChgCbkType SizeOfLocalIpAddrAssignmentChgCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbk */
  SoAd_SizeOfLocalIpAddrAssignmentChgCbkIndType SizeOfLocalIpAddrAssignmentChgCbkIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbkInd */
  SoAd_SizeOfMetaDataRxBufType SizeOfMetaDataRxBufOfPCConfig;  /**< the number of accomplishable value elements in SoAd_MetaDataRxBuf */
  SoAd_SizeOfNPduUdpTxType SizeOfNPduUdpTxOfPCConfig;  /**< the number of accomplishable value elements in SoAd_NPduUdpTx */
  SoAd_SizeOfNPduUdpTxBufferType SizeOfNPduUdpTxBufferOfPCConfig;  /**< the number of accomplishable value elements in SoAd_NPduUdpTxBuffer */
  SoAd_SizeOfNPduUdpTxQueueType SizeOfNPduUdpTxQueueOfPCConfig;  /**< the number of accomplishable value elements in SoAd_NPduUdpTxQueue */
  SoAd_SizeOfPduRouteType SizeOfPduRouteOfPCConfig;  /**< the number of accomplishable value elements in SoAd_PduRoute */
  SoAd_SizeOfPduRouteDestType SizeOfPduRouteDestOfPCConfig;  /**< the number of accomplishable value elements in SoAd_PduRouteDest */
  SoAd_SizeOfPduRouteDestBySoConIndType SizeOfPduRouteDestBySoConIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_PduRouteDestBySoConInd */
  SoAd_SizeOfPduRouteDestIndType SizeOfPduRouteDestIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_PduRouteDestInd */
  SoAd_SizeOfRcvRemAddrType SizeOfRcvRemAddrOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RcvRemAddr */
  SoAd_SizeOfRemAddrIpV4Type SizeOfRemAddrIpV4OfPCConfig;  /**< the number of accomplishable value elements in SoAd_RemAddrIpV4 */
  SoAd_SizeOfRemAddrIpV6Type SizeOfRemAddrIpV6OfPCConfig;  /**< the number of accomplishable value elements in SoAd_RemAddrIpV6 */
  SoAd_SizeOfRouteGrpType SizeOfRouteGrpOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RouteGrp */
  SoAd_SizeOfRouteGrpIdMapType SizeOfRouteGrpIdMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RouteGrpIdMap */
  SoAd_SizeOfRouteGrpSoConType SizeOfRouteGrpSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RouteGrpSoCon */
  SoAd_SizeOfRouteGrpSoConByPduRouteDestIndType SizeOfRouteGrpSoConByPduRouteDestIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RouteGrpSoConByPduRouteDestInd */
  SoAd_SizeOfRouteGrpSoConBySocketRouteDestIndType SizeOfRouteGrpSoConBySocketRouteDestIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RouteGrpSoConBySocketRouteDestInd */
  SoAd_SizeOfRxBufStructMgtType SizeOfRxBufStructMgtOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RxBufStructMgt */
  SoAd_SizeOfRxBufStructSegType SizeOfRxBufStructSegOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RxBufStructSeg */
  SoAd_SizeOfRxBufferConfigType SizeOfRxBufferConfigOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RxBufferConfig */
  SoAd_SizeOfRxMgtType SizeOfRxMgtOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RxMgt */
  SoAd_SizeOfRxPduIdIdMapType SizeOfRxPduIdIdMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_RxPduIdIdMap */
  SoAd_SizeOfShutdownFinishedCbkType SizeOfShutdownFinishedCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_ShutdownFinishedCbk */
  SoAd_SizeOfSoConType SizeOfSoConOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SoCon */
  SoAd_SizeOfSoConGrpType SizeOfSoConGrpOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SoConGrp */
  SoAd_SizeOfSoConMapType SizeOfSoConMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SoConMap */
  SoAd_SizeOfSoConModeChgCbkType SizeOfSoConModeChgCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SoConModeChgCbk */
  SoAd_SizeOfSoConModeChgCbkIndType SizeOfSoConModeChgCbkIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SoConModeChgCbkInd */
  SoAd_SizeOfSocketType SizeOfSocketOfPCConfig;  /**< the number of accomplishable value elements in SoAd_Socket */
  SoAd_SizeOfSocketReportErrorCbkType SizeOfSocketReportErrorCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketReportErrorCbk */
  SoAd_SizeOfSocketRouteType SizeOfSocketRouteOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketRoute */
  SoAd_SizeOfSocketRouteDestType SizeOfSocketRouteDestOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketRouteDest */
  SoAd_SizeOfSocketRouteIndType SizeOfSocketRouteIndOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketRouteInd */
  SoAd_SizeOfSocketTcpType SizeOfSocketTcpOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketTcp */
  SoAd_SizeOfSocketUdpType SizeOfSocketUdpOfPCConfig;  /**< the number of accomplishable value elements in SoAd_SocketUdp */
  SoAd_SizeOfTcpIpCtrlType SizeOfTcpIpCtrlOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TcpIpCtrl */
  SoAd_SizeOfTcpKeepAliveGloballyEnabledType SizeOfTcpKeepAliveGloballyEnabledOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TcpKeepAliveGloballyEnabled */
  SoAd_SizeOfTcpTlsSocketCreatedNotificationCbkType SizeOfTcpTlsSocketCreatedNotificationCbkOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TcpTlsSocketCreatedNotificationCbk */
  SoAd_SizeOfTcpTxQueueType SizeOfTcpTxQueueOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TcpTxQueue */
  SoAd_SizeOfTcpTxQueueDataType SizeOfTcpTxQueueDataOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TcpTxQueueData */
  SoAd_SizeOfTimeoutListDynType SizeOfTimeoutListDynOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListDyn */
  SoAd_SizeOfTimeoutListIdentType SizeOfTimeoutListIdentOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListIdent */
  SoAd_SizeOfTimeoutListNPduUdpTxType SizeOfTimeoutListNPduUdpTxOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTx */
  SoAd_SizeOfTimeoutListNPduUdpTxMapType SizeOfTimeoutListNPduUdpTxMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTxMap */
  SoAd_SizeOfTimeoutListUdpAliveType SizeOfTimeoutListUdpAliveOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListUdpAlive */
  SoAd_SizeOfTimeoutListUdpAliveMapType SizeOfTimeoutListUdpAliveMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TimeoutListUdpAliveMap */
  SoAd_SizeOfTlsConfigType SizeOfTlsConfigOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TlsConfig */
  SoAd_SizeOfTpRxBufferType SizeOfTpRxBufferOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TpRxBuffer */
  SoAd_SizeOfTpTxBufferType SizeOfTpTxBufferOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TpTxBuffer */
  SoAd_SizeOfTpTxBufferConfigType SizeOfTpTxBufferConfigOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TpTxBufferConfig */
  SoAd_SizeOfTriggerBufType SizeOfTriggerBufOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TriggerBuf */
  SoAd_SizeOfTriggerBufConfigType SizeOfTriggerBufConfigOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TriggerBufConfig */
  SoAd_SizeOfTxMgtType SizeOfTxMgtOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TxMgt */
  SoAd_SizeOfTxPduIdMapType SizeOfTxPduIdMapOfPCConfig;  /**< the number of accomplishable value elements in SoAd_TxPduIdMap */
  SoAd_SizeOfUpperLayerType SizeOfUpperLayerOfPCConfig;  /**< the number of accomplishable value elements in SoAd_UpperLayer */
} SoAd_PCConfigType;  /* PRQA S 0639 */  /* MD_MSR_Dir1.1 */

typedef SoAd_PCConfigType SoAd_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access SoAd_PCConfig in a symbol based style. */
typedef struct sSoAd_PCConfigsType
{
  SoAd_PCConfigType Config;  /**< [Config] */
} SoAd_PCConfigsType;

/** 
  \}
*/ 



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  SoAd_EventQueue
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueue
  \brief  the configuration struct of all event queues
  \details
  Element       Description
  Limit         the limit of events handled in a single main function call
  BitPattern    the bit pattern for event queue
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_EventQueueType, SOAD_CONST) SoAd_EventQueue[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueIdent
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueIdent
  \brief  the event queue identification to get the index of a specific event queue
  \details
  Element                       Description
  EventQueueIfTxRouteGrpIdx     the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueIfUdpPduRouteIdx    the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueLocalAddrIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueSockIdxIdx          the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueStateSoConIdx       the index of the 1:1 relation pointing to SoAd_EventQueue
  EventQueueTcpTxSoConIdx       the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueTpRxSoConIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
  EventQueueTpTxSoConIdx        the index of the 0:1 relation pointing to SoAd_EventQueue
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_EventQueueIdentType, SOAD_CONST) SoAd_EventQueueIdent[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddr
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddr
  \brief  the local address configurations
  \details
  Element          Description
  TcpIpCtrlIdx     the index of the 1:1 relation pointing to SoAd_TcpIpCtrl
  AddressType      address type (unicast/multicast)
  AssignTrigger    assignment trigger (automatic/manual)
  Domain           the IP domain (IPv4/6)
  AssignType       assignment type (e.g. static/link-local/DHCP)
  AddrId           the address identifier to identify the local address at TcpIp
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_LocalAddrType, SOAD_CONST) SoAd_LocalAddr[3];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrByTcpIpCtrlInd
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrByTcpIpCtrlInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_LocalAddr
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_LocalAddrByTcpIpCtrlIndType, SOAD_CONST) SoAd_LocalAddrByTcpIpCtrlInd[1];
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrIdMap
  \brief  the LocalAddrId to LocalAddr mapping
  \details
  Element         Description
  InvalidHnd      FALSE, if the handle of SoAd_LocalAddrIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  LocalAddrIdx    the index of the 1:1 relation pointing to SoAd_LocalAddr
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_LocalAddrIdMapType, SOAD_CONST) SoAd_LocalAddrIdMap[3];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRoute
  \brief  the SoAdPduRoutes configuration
  \details
  Element                      Description
  TxConfPduId                  the TxPduId used to call upper layer
  AllPduRouteDestWithPduHdr    indicates if all related SoAdPduRouteDests have a SoAdTxPduHeaderId
  MetaDataTxEnabled            indicates if transmission on specific socket connection via meta data is enabled
  TxConfEnabled                indicates if TxConfirmation is enabled
  TxOptimized                  indicates if Tx optimized is enabled
  PduRouteDestEndIdx           the end index of the 1:n relation pointing to SoAd_PduRouteDest
  PduRouteDestStartIdx         the start index of the 1:n relation pointing to SoAd_PduRouteDest
  UpperLayerIdx                the index of the 1:1 relation pointing to SoAd_UpperLayer
  IfTriggerTransmitMode        the trigger transmit mode
  UpperLayerApi                the upper layer API type (IF/TP)
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_PduRouteType, SOAD_CONST) SoAd_PduRoute[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDest
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDest
  \brief  the PduRouteDests configuraion
  \details
  Element                                   Description
  PduRouteIdx                               the index of the 1:1 relation pointing to SoAd_PduRoute
  RouteGrpSoConByPduRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  RouteGrpSoConByPduRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_RouteGrpSoConByPduRouteDestInd
  SoConIdx                                  the index of the 1:1 relation pointing to SoAd_SoCon
  TxPduHdrId                                the PDU header ID
  UdpTriggerTimeout                         the PduRouteDest specific timeout to send a nPdu
  TxUdpTriggerMode                          indicates if nPdu shall be sent on transmission request always or never
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_PduRouteDestType, SOAD_CONST) SoAd_PduRouteDest[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDestBySoConInd
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDestBySoConInd
  \brief  the indexes of the 1:1 sorted relation pointing to SoAd_PduRouteDest
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_PduRouteDestBySoConIndType, SOAD_CONST) SoAd_PduRouteDestBySoConInd[1];
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RemAddrIpV4
**********************************************************************************************************************/
/** 
  \var    SoAd_RemAddrIpV4
  \brief  the configured IPv4 remote addresses for each IPv4 socket connection
  \details
  Element    Description
  Addr       the remote IPv4 address
  Port       the remote port
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_RemAddrIpV4Type, SOAD_CONST) SoAd_RemAddrIpV4[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxPduIdIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_RxPduIdIdMap
  \brief  the handle ID map for RxPduId
  \details
  Element               Description
  InvalidHnd            FALSE, if the handle of SoAd_RxPduIdIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  SocketRouteDestIdx    the index of the 1:1 relation pointing to SoAd_SocketRouteDest
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_RxPduIdIdMapType, SOAD_CONST) SoAd_RxPduIdIdMap[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_SoCon
  \brief  the socket connection configuration
  \details
  Element                                   Description
  IpFragMgtIdx                              the index of the 0:1 relation pointing to SoAd_IpFragMgt
  LocalIpAddrAssignmentChgCbkIndEndIdx      the end index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd
  LocalIpAddrAssignmentChgCbkIndStartIdx    the start index of the 0:n relation pointing to SoAd_LocalIpAddrAssignmentChgCbkInd
  NPduUdpTxIdx                              the index of the 0:1 relation pointing to SoAd_NPduUdpTx
  PduRouteDestBySoConIndEndIdx              the end index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd
  PduRouteDestBySoConIndStartIdx            the start index of the 0:n relation pointing to SoAd_PduRouteDestBySoConInd
  RcvRemAddrIdx                             the index of the 0:1 relation pointing to SoAd_RcvRemAddr
  RemAddrIpV4Idx                            the index of the 0:1 relation pointing to SoAd_RemAddrIpV4
  RemAddrIpV6Idx                            the index of the 0:1 relation pointing to SoAd_RemAddrIpV6
  RxBufStructMgtIdx                         the index of the 0:1 relation pointing to SoAd_RxBufStructMgt
  RxBufStructSegEndIdx                      the end index of the 0:n relation pointing to SoAd_RxBufStructSeg
  RxBufStructSegStartIdx                    the start index of the 0:n relation pointing to SoAd_RxBufStructSeg
  RxBufferConfigIdx                         the index of the 0:1 relation pointing to SoAd_RxBufferConfig
  RxMgtIdx                                  the index of the 0:1 relation pointing to SoAd_RxMgt
  SoConGrpIdx                               the index of the 1:1 relation pointing to SoAd_SoConGrp
  SoConId                                   the SocketConnection identifier used in SoAd API
  SoConModeChgCbkIndEndIdx                  the end index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd
  SoConModeChgCbkIndStartIdx                the start index of the 0:n relation pointing to SoAd_SoConModeChgCbkInd
  SocketIdx                                 the index of the 1:1 relation pointing to SoAd_Socket
  SocketRouteEndIdx                         the end index of the 0:n relation pointing to SoAd_SocketRoute
  SocketRouteStartIdx                       the start index of the 0:n relation pointing to SoAd_SocketRoute
  TcpTxQueueIdx                             the index of the 0:1 relation pointing to SoAd_TcpTxQueue
  TlsConfigIdx                              the index of the 0:1 relation pointing to SoAd_TlsConfig
  TpTxBufferConfigIdx                       the index of the 0:1 relation pointing to SoAd_TpTxBufferConfig
  TxMgtIdx                                  the index of the 0:1 relation pointing to SoAd_TxMgt
  RemAddrState                              the configured remote address state
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SoConType, SOAD_CONST) SoAd_SoCon[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConGrp
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConGrp
  \brief  the socket connection group configuration
  \details
  Element                          Description
  BestMatchWithPduHeaderEnabled    indicates if best match algorithm considers PDU Header ID
  BestMatchWithSockRouteEnabled    indicates if best match algorithm considers socket route availability
  MsgAcceptFilterEnabled           indicates if message acceptance filter is enabled
  PduHdrEnabled                    indicates if PDU header is enabled
  SockAutoSoConSetup               indicates if automatic socket connection setup is enabled
  SockAutoSoConSetupKeepOnline     indicates if it is enabled that socket connection stays online after transmission
  FramePriority                    the frame priority (VLAN)
  LocalAddrIdx                     the index of the 0:1 relation pointing to SoAd_LocalAddr
  SoConEndIdx                      the end index of the 1:n relation pointing to SoAd_SoCon
  SoConStartIdx                    the start index of the 1:n relation pointing to SoAd_SoCon
  SocketIdx                        the index of the 0:1 relation pointing to SoAd_Socket
  SocketTcpIdx                     the index of the 0:1 relation pointing to SoAd_SocketTcp
  SocketUdpIdx                     the index of the 0:1 relation pointing to SoAd_SocketUdp
  LocalPort                        the local port
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SoConGrpType, SOAD_CONST) SoAd_SoConGrp[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConMap
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConMap
  \brief  the handle ID map for SoAdSocketId
  \details
  Element       Description
  InvalidHnd    FALSE, if the handle of SoAd_SoConMap is valid and can be used in the embedded code for further processing in the embedded code.
  SoConIdx      the index of the 1:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SoConMapType, SOAD_CONST) SoAd_SoConMap[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_Socket
**********************************************************************************************************************/
/** 
  \var    SoAd_Socket
  \brief  the socket configuration
  \details
  Element          Description
  SoConEndIdx      the end index of the 1:n relation pointing to SoAd_SoCon
  SoConStartIdx    the start index of the 1:n relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SocketType, SOAD_CONST) SoAd_Socket[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketRoute
  \brief  the socket route configuration
  \details
  Element                    Description
  MetaDataRxEnabled          indicates if SoConId is forwarded as meta data on reception
  RxPduHdrId                 the PDU header ID
  SoConIdx                   the index of the 1:1 relation pointing to SoAd_SoCon
  SocketRouteDestEndIdx      the end index of the 1:n relation pointing to SoAd_SocketRouteDest
  SocketRouteDestStartIdx    the start index of the 1:n relation pointing to SoAd_SocketRouteDest
  UpperLayerApi              the upper layer API type (IF/TP)
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SocketRouteType, SOAD_CONST) SoAd_SocketRoute[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketRouteDest
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketRouteDest
  \brief  the socket route destination configuration
  \details
  Element                                      Description
  RxPduId                                      the RxPduId used to call the upper layer
  RouteGrpSoConBySocketRouteDestIndEndIdx      the end index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd
  RouteGrpSoConBySocketRouteDestIndStartIdx    the start index of the 0:n relation pointing to SoAd_RouteGrpSoConBySocketRouteDestInd
  SocketRouteIdx                               the index of the 1:1 relation pointing to SoAd_SocketRoute
  UpperLayerIdx                                the index of the 1:1 relation pointing to SoAd_UpperLayer
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SocketRouteDestType, SOAD_CONST) SoAd_SocketRouteDest[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketUdp
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketUdp
  \brief  the UDP socket configuration
  \details
  Element                        Description
  ImmedIfTxConf              
  UdpListenOnly              
  UdpStrictHdrLenCheckEnabled
  AliveTimeoutMaxCnt         
  ImmedIfTxConfListSize      
  NPduUdpTxBufferMin         
  NPduUdpTxQueueSize         
  RetryQueueLimit            
  UdpTriggerTimeout          
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_SocketUdpType, SOAD_CONST) SoAd_SocketUdp[2];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpIpCtrl
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpIpCtrl
  \brief  the TcpIp controller/interface
  \details
  Element                            Description
  RetryEnabled                       indicates if transmission retry is available on controller/interface
  LocalAddrByTcpIpCtrlIndEndIdx      the end index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd
  LocalAddrByTcpIpCtrlIndStartIdx    the start index of the 0:n relation pointing to SoAd_LocalAddrByTcpIpCtrlInd
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_TcpIpCtrlType, SOAD_CONST) SoAd_TcpIpCtrl[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TcpKeepAliveGloballyEnabled
**********************************************************************************************************************/
/** 
  \var    SoAd_TcpKeepAliveGloballyEnabled
  \brief  indicates if TCP keep alive is enabled at all
*/ 
#define SOAD_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_TcpKeepAliveGloballyEnabledType, SOAD_CONST) SoAd_TcpKeepAliveGloballyEnabled[1];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define SOAD_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TimeoutListIdent
**********************************************************************************************************************/
/** 
  \var    SoAd_TimeoutListIdent
  \brief  the timeout list identification to get the index of a specific timeout list
  \details
  Element                       Description
  TimeoutListDynNPduUdpTxIdx    the index of the 0:1 relation pointing to SoAd_TimeoutListDyn
  TimeoutListDynUdpAliveIdx     the index of the 0:1 relation pointing to SoAd_TimeoutListDyn
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_TimeoutListIdentType, SOAD_CONST) SoAd_TimeoutListIdent[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TxPduIdMap
**********************************************************************************************************************/
/** 
  \var    SoAd_TxPduIdMap
  \brief  the handle ID map for TxPduId
  \details
  Element        Description
  InvalidHnd     FALSE, if the handle of SoAd_TxPduIdMap is valid and can be used in the embedded code for further processing in the embedded code.
  PduRouteIdx    the index of the 1:1 relation pointing to SoAd_PduRoute
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_TxPduIdMapType, SOAD_CONST) SoAd_TxPduIdMap[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_UpperLayer
**********************************************************************************************************************/
/** 
  \var    SoAd_UpperLayer
  \brief  the upper layer configuration
  \details
  Element                       Description
  IfRxIndicationCbk             the callback Up_[SoAd][If]RxIndication
  IfTriggerTransmitCbk          the callback Up_[SoAd][If]TriggerTransmit
  IfTxConfirmationCbk           the callback Up_[SoAd][If]TxConfirmation
  TpCopyRxDataCbk               the callback Up_[SoAd][Tp]CopyRxData
  TpCopyRxDataConstCbk          the callback Up_[SoAd][Tp]CopyRxData with const data pointer
  TpCopyTxDataCbk               the callback Up_[SoAd][Tp]CopyTxData
  TpCopyTxDataConstCbk          the callback Up_[SoAd][Tp]CopyTxData with const data pointer
  TpRxIndicationCbk             the callback Up_[SoAd][Tp]RxIndication
  TpStartOfReceptionCbk         the callback Up_[SoAd][Tp]StartOfReception
  TpStartOfReceptionConstCbk    the callback Up_[SoAd][Tp]StartOfReception with const data pointer
  TpTxConfirmationCbk           the callback Up_[SoAd][Tp]TxConfirmation
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_UpperLayerType, SOAD_CONST) SoAd_UpperLayer[1];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_BestMatchSoConIdxList
**********************************************************************************************************************/
/** 
  \var    SoAd_BestMatchSoConIdxList
  \brief  the global list to store all matching socket connections if best match alogorithm is used
  \details
  Element     Description
  SoConIdx    the index of the 1:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_BestMatchSoConIdxListType, SOAD_VAR_NOINIT) SoAd_BestMatchSoConIdxList[1];
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueDyn
  \brief  the management struct of all event queues
  \details
  Element    Description
  Idx        the index of oldest pending event.
  Lvl        the level of pending events
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_EventQueueDynUType, SOAD_VAR_NOINIT) SoAd_EventQueueDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueFlag
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueFlag
  \brief  stores a flag for each handle index and event queue type to indicate if handle is in event queue (i.e. event active for handle)
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_EventQueueFlagType, SOAD_VAR_NOINIT) SoAd_EventQueueFlag[2];
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueIfUdpPduRoute
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueIfUdpPduRoute
  \brief  indicates if a IF confirmation is pending on a UDP socket connection
  \details
  Element        Description
  PduRouteIdx    the index of the 0:1 relation pointing to SoAd_PduRoute
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_EventQueueIfUdpPduRouteUType, SOAD_VAR_NOINIT) SoAd_EventQueueIfUdpPduRoute;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_EventQueueStateSoCon
**********************************************************************************************************************/
/** 
  \var    SoAd_EventQueueStateSoCon
  \brief  indicates if an event is active for socket connection state
  \details
  Element     Description
  SoConIdx    the index of the 0:1 relation pointing to SoAd_SoCon
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_EventQueueStateSoConUType, SOAD_VAR_NOINIT) SoAd_EventQueueStateSoCon;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_LocalAddrDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_LocalAddrDyn
  \details
  Element        Description
  IpAddrState    the local IP address assignment state
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_LocalAddrDynType, SOAD_VAR_NOINIT) SoAd_LocalAddrDyn[3];
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PduRouteDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_PduRouteDyn
  \brief  the SoAdPduRoute management structs
  \details
  Element              Description
  PendingTxConfMain    indicates if transmission confirmation in main function context is pending
  PendingTxConfNum     the number of pending transmission confirmation
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_PduRouteDynUType, SOAD_VAR_NOINIT) SoAd_PduRouteDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_RxMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_RxMgt
  \brief  the Rx management structs
  \details
  Element               Description
  CancelRequested       indicates if reception cancellation is requested
  RxBytesPending        the length of pending data to be received
  SocketRouteDestIdx    the index of the 1:1 relation pointing to SoAd_SocketRouteDest
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_RxMgtUType, SOAD_VAR_NOINIT) SoAd_RxMgt;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SoConDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_SoConDyn
  \brief  the socket connection managment structs
  \details
  Element             Description
  OpenCloseCounter    the open and close sequence counter
  Abort               indicates if abort is requested
  CloseMode           the mode of socket connection
  Mode                the mode of socket connection
  RemAddrDyn          the remote address for each socket connection
  RemAddrStateDyn     the remote address state on socket connection
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_SoConDynType, SOAD_VAR_NOINIT) SoAd_SoConDyn[2];
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_SocketDyn
**********************************************************************************************************************/
/** 
  \var    SoAd_SocketDyn
  \brief  the socket management structs
  \details
  Element             Description
  SkipBytes           the number of bytes to be skipped
  SoConTxActiveIdx    the index of the 0:1 relation pointing to SoAd_SoCon
  LocalPort           the local port
  SocketId            the socket identifier
  State               the socket state
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_SocketDynType, SOAD_VAR_NOINIT) SoAd_SocketDyn[2];
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_TxMgt
**********************************************************************************************************************/
/** 
  \var    SoAd_TxMgt
  \brief  the Tx management structs
  \details
  Element            Description
  CancelRequested    indicates if transmission cancellation is requested
  PduRouteDestIdx    the index of the 1:1 relation pointing to SoAd_PduRouteDest
  TxBytesLen         the length of data to be transmitted
  TxBytesPending     the length of pending data to be transmitted
  TxBufPtr           the pointer to transmission data buffer
*/ 
#define SOAD_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(SoAd_TxMgtUType, SOAD_VAR_NOINIT) SoAd_TxMgt;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define SOAD_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  SoAd_PCConfig
**********************************************************************************************************************/
/** 
  \var    SoAd_PCConfig
  \details
  Element                                     Description
  BestMatchSoConIdxList                       the pointer to SoAd_BestMatchSoConIdxList
  DhcpEventCbk                                the pointer to SoAd_DhcpEventCbk
  EventQueue                                  the pointer to SoAd_EventQueue
  EventQueueDyn                               the pointer to SoAd_EventQueueDyn
  EventQueueFlag                              the pointer to SoAd_EventQueueFlag
  EventQueueIdent                             the pointer to SoAd_EventQueueIdent
  EventQueueIfTxRouteGrp                      the pointer to SoAd_EventQueueIfTxRouteGrp
  EventQueueIfUdpPduRoute                     the pointer to SoAd_EventQueueIfUdpPduRoute
  EventQueueLocalAddr                         the pointer to SoAd_EventQueueLocalAddr
  EventQueueSocketIdx                         the pointer to SoAd_EventQueueSocketIdx
  EventQueueStateSoCon                        the pointer to SoAd_EventQueueStateSoCon
  EventQueueTcpTxSoCon                        the pointer to SoAd_EventQueueTcpTxSoCon
  EventQueueTpRxSoCon                         the pointer to SoAd_EventQueueTpRxSoCon
  EventQueueTpTxSoCon                         the pointer to SoAd_EventQueueTpTxSoCon
  IfRxBuffer                                  the pointer to SoAd_IfRxBuffer
  IpFragBuf                                   the pointer to SoAd_IpFragBuf
  IpFragBufConfig                             the pointer to SoAd_IpFragBufConfig
  IpFragBufConfigDyn                          the pointer to SoAd_IpFragBufConfigDyn
  IpFragMgt                                   the pointer to SoAd_IpFragMgt
  LocalAddr                                   the pointer to SoAd_LocalAddr
  LocalAddrByTcpIpCtrlInd                     the pointer to SoAd_LocalAddrByTcpIpCtrlInd
  LocalAddrDyn                                the pointer to SoAd_LocalAddrDyn
  LocalAddrIdMap                              the pointer to SoAd_LocalAddrIdMap
  LocalIpAddrAssignmentChgCbk                 the pointer to SoAd_LocalIpAddrAssignmentChgCbk
  LocalIpAddrAssignmentChgCbkInd              the pointer to SoAd_LocalIpAddrAssignmentChgCbkInd
  MetaDataRxBuf                               the pointer to SoAd_MetaDataRxBuf
  NPduUdpTx                                   the pointer to SoAd_NPduUdpTx
  NPduUdpTxBuffer                             the pointer to SoAd_NPduUdpTxBuffer
  NPduUdpTxDyn                                the pointer to SoAd_NPduUdpTxDyn
  NPduUdpTxQueue                              the pointer to SoAd_NPduUdpTxQueue
  PduRoute                                    the pointer to SoAd_PduRoute
  PduRouteDest                                the pointer to SoAd_PduRouteDest
  PduRouteDestBySoConInd                      the pointer to SoAd_PduRouteDestBySoConInd
  PduRouteDestInd                             the pointer to SoAd_PduRouteDestInd
  PduRouteDyn                                 the pointer to SoAd_PduRouteDyn
  RcvRemAddr                                  the pointer to SoAd_RcvRemAddr
  RemAddrIpV4                                 the pointer to SoAd_RemAddrIpV4
  RemAddrIpV6                                 the pointer to SoAd_RemAddrIpV6
  RouteGrp                                    the pointer to SoAd_RouteGrp
  RouteGrpIdMap                               the pointer to SoAd_RouteGrpIdMap
  RouteGrpSoCon                               the pointer to SoAd_RouteGrpSoCon
  RouteGrpSoConByPduRouteDestInd              the pointer to SoAd_RouteGrpSoConByPduRouteDestInd
  RouteGrpSoConBySocketRouteDestInd           the pointer to SoAd_RouteGrpSoConBySocketRouteDestInd
  RouteGrpSoConDyn                            the pointer to SoAd_RouteGrpSoConDyn
  RxBufStructMgt                              the pointer to SoAd_RxBufStructMgt
  RxBufStructSeg                              the pointer to SoAd_RxBufStructSeg
  RxBufferConfig                              the pointer to SoAd_RxBufferConfig
  RxBufferConfigDyn                           the pointer to SoAd_RxBufferConfigDyn
  RxMgt                                       the pointer to SoAd_RxMgt
  RxPduIdIdMap                                the pointer to SoAd_RxPduIdIdMap
  ShutdownFinishedCbk                         the pointer to SoAd_ShutdownFinishedCbk
  SoCon                                       the pointer to SoAd_SoCon
  SoConDyn                                    the pointer to SoAd_SoConDyn
  SoConGrp                                    the pointer to SoAd_SoConGrp
  SoConMap                                    the pointer to SoAd_SoConMap
  SoConModeChgCbk                             the pointer to SoAd_SoConModeChgCbk
  SoConModeChgCbkInd                          the pointer to SoAd_SoConModeChgCbkInd
  Socket                                      the pointer to SoAd_Socket
  SocketDyn                                   the pointer to SoAd_SocketDyn
  SocketReportErrorCbk                        the pointer to SoAd_SocketReportErrorCbk
  SocketRoute                                 the pointer to SoAd_SocketRoute
  SocketRouteDest                             the pointer to SoAd_SocketRouteDest
  SocketRouteInd                              the pointer to SoAd_SocketRouteInd
  SocketTcp                                   the pointer to SoAd_SocketTcp
  SocketUdp                                   the pointer to SoAd_SocketUdp
  TcpIpCtrl                                   the pointer to SoAd_TcpIpCtrl
  TcpKeepAliveGloballyEnabled                 the pointer to SoAd_TcpKeepAliveGloballyEnabled
  TcpTlsSocketCreatedNotificationCbk          the pointer to SoAd_TcpTlsSocketCreatedNotificationCbk
  TcpTxQueue                                  the pointer to SoAd_TcpTxQueue
  TcpTxQueueData                              the pointer to SoAd_TcpTxQueueData
  TcpTxQueueMgt                               the pointer to SoAd_TcpTxQueueMgt
  TimeoutListDyn                              the pointer to SoAd_TimeoutListDyn
  TimeoutListIdent                            the pointer to SoAd_TimeoutListIdent
  TimeoutListNPduUdpTx                        the pointer to SoAd_TimeoutListNPduUdpTx
  TimeoutListNPduUdpTxMap                     the pointer to SoAd_TimeoutListNPduUdpTxMap
  TimeoutListUdpAlive                         the pointer to SoAd_TimeoutListUdpAlive
  TimeoutListUdpAliveMap                      the pointer to SoAd_TimeoutListUdpAliveMap
  TlsConfig                                   the pointer to SoAd_TlsConfig
  TpRxBuffer                                  the pointer to SoAd_TpRxBuffer
  TpTxBuffer                                  the pointer to SoAd_TpTxBuffer
  TpTxBufferConfig                            the pointer to SoAd_TpTxBufferConfig
  TpTxBufferConfigDyn                         the pointer to SoAd_TpTxBufferConfigDyn
  TriggerBuf                                  the pointer to SoAd_TriggerBuf
  TriggerBufConfig                            the pointer to SoAd_TriggerBufConfig
  TriggerBufConfigDyn                         the pointer to SoAd_TriggerBufConfigDyn
  TxMgt                                       the pointer to SoAd_TxMgt
  TxPduIdMap                                  the pointer to SoAd_TxPduIdMap
  UpperLayer                                  the pointer to SoAd_UpperLayer
  MaxIfRouteGrpTransmitPduSize                the maximum length of all PDUs which can be sent via routing group transmit
  SizeOfBestMatchSoConIdxList                 the number of accomplishable value elements in SoAd_BestMatchSoConIdxList
  SizeOfDhcpEventCbk                          the number of accomplishable value elements in SoAd_DhcpEventCbk
  SizeOfEventQueue                            the number of accomplishable value elements in SoAd_EventQueue
  SizeOfEventQueueFlag                        the number of accomplishable value elements in SoAd_EventQueueFlag
  SizeOfEventQueueIdent                       the number of accomplishable value elements in SoAd_EventQueueIdent
  SizeOfEventQueueIfTxRouteGrp                the number of accomplishable value elements in SoAd_EventQueueIfTxRouteGrp
  SizeOfEventQueueIfUdpPduRoute               the number of accomplishable value elements in SoAd_EventQueueIfUdpPduRoute
  SizeOfEventQueueLocalAddr                   the number of accomplishable value elements in SoAd_EventQueueLocalAddr
  SizeOfEventQueueSocketIdx                   the number of accomplishable value elements in SoAd_EventQueueSocketIdx
  SizeOfEventQueueStateSoCon                  the number of accomplishable value elements in SoAd_EventQueueStateSoCon
  SizeOfEventQueueTcpTxSoCon                  the number of accomplishable value elements in SoAd_EventQueueTcpTxSoCon
  SizeOfEventQueueTpRxSoCon                   the number of accomplishable value elements in SoAd_EventQueueTpRxSoCon
  SizeOfEventQueueTpTxSoCon                   the number of accomplishable value elements in SoAd_EventQueueTpTxSoCon
  SizeOfIfRxBuffer                            the number of accomplishable value elements in SoAd_IfRxBuffer
  SizeOfIpFragBuf                             the number of accomplishable value elements in SoAd_IpFragBuf
  SizeOfIpFragBufConfig                       the number of accomplishable value elements in SoAd_IpFragBufConfig
  SizeOfIpFragMgt                             the number of accomplishable value elements in SoAd_IpFragMgt
  SizeOfLocalAddr                             the number of accomplishable value elements in SoAd_LocalAddr
  SizeOfLocalAddrByTcpIpCtrlInd               the number of accomplishable value elements in SoAd_LocalAddrByTcpIpCtrlInd
  SizeOfLocalAddrIdMap                        the number of accomplishable value elements in SoAd_LocalAddrIdMap
  SizeOfLocalIpAddrAssignmentChgCbk           the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbk
  SizeOfLocalIpAddrAssignmentChgCbkInd        the number of accomplishable value elements in SoAd_LocalIpAddrAssignmentChgCbkInd
  SizeOfMetaDataRxBuf                         the number of accomplishable value elements in SoAd_MetaDataRxBuf
  SizeOfNPduUdpTx                             the number of accomplishable value elements in SoAd_NPduUdpTx
  SizeOfNPduUdpTxBuffer                       the number of accomplishable value elements in SoAd_NPduUdpTxBuffer
  SizeOfNPduUdpTxQueue                        the number of accomplishable value elements in SoAd_NPduUdpTxQueue
  SizeOfPduRoute                              the number of accomplishable value elements in SoAd_PduRoute
  SizeOfPduRouteDest                          the number of accomplishable value elements in SoAd_PduRouteDest
  SizeOfPduRouteDestBySoConInd                the number of accomplishable value elements in SoAd_PduRouteDestBySoConInd
  SizeOfPduRouteDestInd                       the number of accomplishable value elements in SoAd_PduRouteDestInd
  SizeOfRcvRemAddr                            the number of accomplishable value elements in SoAd_RcvRemAddr
  SizeOfRemAddrIpV4                           the number of accomplishable value elements in SoAd_RemAddrIpV4
  SizeOfRemAddrIpV6                           the number of accomplishable value elements in SoAd_RemAddrIpV6
  SizeOfRouteGrp                              the number of accomplishable value elements in SoAd_RouteGrp
  SizeOfRouteGrpIdMap                         the number of accomplishable value elements in SoAd_RouteGrpIdMap
  SizeOfRouteGrpSoCon                         the number of accomplishable value elements in SoAd_RouteGrpSoCon
  SizeOfRouteGrpSoConByPduRouteDestInd        the number of accomplishable value elements in SoAd_RouteGrpSoConByPduRouteDestInd
  SizeOfRouteGrpSoConBySocketRouteDestInd     the number of accomplishable value elements in SoAd_RouteGrpSoConBySocketRouteDestInd
  SizeOfRxBufStructMgt                        the number of accomplishable value elements in SoAd_RxBufStructMgt
  SizeOfRxBufStructSeg                        the number of accomplishable value elements in SoAd_RxBufStructSeg
  SizeOfRxBufferConfig                        the number of accomplishable value elements in SoAd_RxBufferConfig
  SizeOfRxMgt                                 the number of accomplishable value elements in SoAd_RxMgt
  SizeOfRxPduIdIdMap                          the number of accomplishable value elements in SoAd_RxPduIdIdMap
  SizeOfShutdownFinishedCbk                   the number of accomplishable value elements in SoAd_ShutdownFinishedCbk
  SizeOfSoCon                                 the number of accomplishable value elements in SoAd_SoCon
  SizeOfSoConGrp                              the number of accomplishable value elements in SoAd_SoConGrp
  SizeOfSoConMap                              the number of accomplishable value elements in SoAd_SoConMap
  SizeOfSoConModeChgCbk                       the number of accomplishable value elements in SoAd_SoConModeChgCbk
  SizeOfSoConModeChgCbkInd                    the number of accomplishable value elements in SoAd_SoConModeChgCbkInd
  SizeOfSocket                                the number of accomplishable value elements in SoAd_Socket
  SizeOfSocketReportErrorCbk                  the number of accomplishable value elements in SoAd_SocketReportErrorCbk
  SizeOfSocketRoute                           the number of accomplishable value elements in SoAd_SocketRoute
  SizeOfSocketRouteDest                       the number of accomplishable value elements in SoAd_SocketRouteDest
  SizeOfSocketRouteInd                        the number of accomplishable value elements in SoAd_SocketRouteInd
  SizeOfSocketTcp                             the number of accomplishable value elements in SoAd_SocketTcp
  SizeOfSocketUdp                             the number of accomplishable value elements in SoAd_SocketUdp
  SizeOfTcpIpCtrl                             the number of accomplishable value elements in SoAd_TcpIpCtrl
  SizeOfTcpKeepAliveGloballyEnabled           the number of accomplishable value elements in SoAd_TcpKeepAliveGloballyEnabled
  SizeOfTcpTlsSocketCreatedNotificationCbk    the number of accomplishable value elements in SoAd_TcpTlsSocketCreatedNotificationCbk
  SizeOfTcpTxQueue                            the number of accomplishable value elements in SoAd_TcpTxQueue
  SizeOfTcpTxQueueData                        the number of accomplishable value elements in SoAd_TcpTxQueueData
  SizeOfTimeoutListDyn                        the number of accomplishable value elements in SoAd_TimeoutListDyn
  SizeOfTimeoutListIdent                      the number of accomplishable value elements in SoAd_TimeoutListIdent
  SizeOfTimeoutListNPduUdpTx                  the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTx
  SizeOfTimeoutListNPduUdpTxMap               the number of accomplishable value elements in SoAd_TimeoutListNPduUdpTxMap
  SizeOfTimeoutListUdpAlive                   the number of accomplishable value elements in SoAd_TimeoutListUdpAlive
  SizeOfTimeoutListUdpAliveMap                the number of accomplishable value elements in SoAd_TimeoutListUdpAliveMap
  SizeOfTlsConfig                             the number of accomplishable value elements in SoAd_TlsConfig
  SizeOfTpRxBuffer                            the number of accomplishable value elements in SoAd_TpRxBuffer
  SizeOfTpTxBuffer                            the number of accomplishable value elements in SoAd_TpTxBuffer
  SizeOfTpTxBufferConfig                      the number of accomplishable value elements in SoAd_TpTxBufferConfig
  SizeOfTriggerBuf                            the number of accomplishable value elements in SoAd_TriggerBuf
  SizeOfTriggerBufConfig                      the number of accomplishable value elements in SoAd_TriggerBufConfig
  SizeOfTxMgt                                 the number of accomplishable value elements in SoAd_TxMgt
  SizeOfTxPduIdMap                            the number of accomplishable value elements in SoAd_TxPduIdMap
  SizeOfUpperLayer                            the number of accomplishable value elements in SoAd_UpperLayer
*/ 
#define SOAD_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(SoAd_PCConfigsType, SOAD_CONST) SoAd_PCConfig;
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


#endif /* SOAD_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Lcfg.h
 *********************************************************************************************************************/

