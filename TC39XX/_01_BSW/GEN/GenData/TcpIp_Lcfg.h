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
 *            Module: TcpIp
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: TcpIp_Lcfg.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined (TCPIP_LCFG_H)
#define TCPIP_LCFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/
/* PRQA S 0784 EOF */ /* MD_TEST_Rule5.5_Wrapper */
/* PRQA S 0789 EOF */ /* MD_TCPIP_CERT-DCL40-C_0789 */
/* PRQA S 2842 EOF */ /* MD_TCPIP_CERT-ARR30-C_2842 */
/* PRQA S 0777, 0779 EOF */ /* MD_MSR_5.1 */
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IpBase.h"
#include "TcpIp_Cfg.h"
#include "TcpIp_Types.h"



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/* lower layer APIs used by TcpIp */
#define TCPIP_LL_GetPhysAddr          EthIf_GetPhysAddr
#define TCPIP_LL_UpdatePhysAddrFilter EthIf_UpdatePhysAddrFilter
#define TCPIP_LL_Transmit             EthIf_Transmit
#define TCPIP_LL_ProvideTxBuffer      EthIf_ProvideTxBuffer

/**********************************************************************************************************************
  GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#define TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_LIFETIME_STORE    0x80u
#define TCPIP_IPV4_ADDR_ASSIGNMENT_FLAG_AUTO_TRIGGER      0x40u

#define IPV6_DHCPV6_MODE_DISABLED                0U
#define IPV6_DHCPV6_MODE_MANUAL                  1U
#define IPV6_DHCPV6_MODE_AUTOMATIC               2U

#define TCPIP_DHCPV6_DUID_MAX_LEN             130U /* A DUID can be no more than 128 octets long (not including the type code (2 byte)). [RFC3315 9.1. DUID Contents] */
#define TCPIP_DHCPV6_OPT_STACK_SIZE             2U /* E.g. IA_NA ( IAADDR ( STATUS_CODE ) ) */  /* maximum depth of option nesting. */


#define TCPIP_IPV6GENERAL_IDX              0
#define TCPIP_IPV4GENERAL_IDX              0
#define TCPIP_UDP_TX_RETRY_QUEUE_POOL_IDX  0
#define TCPIP_TCPCONFIG_IDX                0
#define TCPIP_ICMPV4CONFIG_IDX             0

#define TcpIp_GetRandomNumber() TcpIp_GetRandomNumberFctPtr()()

#define TCPIP_INV_DEM_ID 0xFFu

#define TCPIP_DHCPV4SERVER_ANY_SWITCH_OR_PORT_IDX   0xFFU


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  TcpIpPCDataSwitches  TcpIp Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define TCPIP_ADDRASSIGNMENTCFGBYPRIO                                                               STD_ON
#define TCPIP_ARPCONFIG                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ENTRYTIMEOUTOFARPCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NUMGRATUITOUSARPONSTARTUPOFARPCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PACKETQUEUEENABLEDOFARPCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REQUESTTIMEOUTOFARPCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_RETRYINTERVALOFARPCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_RETRYTIMEOFARPCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TABLESIZEOFARPCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ARPTABLEENTRY                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_CREATIONTIMESTAMPOFARPTABLEENTRY                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDROFARPTABLEENTRY                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PHYSADDROFARPTABLEENTRY                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATUSOFARPTABLEENTRY                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TIMESTAMPOFARPTABLEENTRY                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_AUTOIPCONFIG                                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ADDRCALLOUTFUNCOFAUTOIPCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ANNOUNCEINTERVALMSOFAUTOIPCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ANNOUNCENUMOFAUTOIPCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ANNOUNCEWAITMSOFAUTOIPCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFENDINTERVALMSOFAUTOIPCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_MAXCONFLICTSOFAUTOIPCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBEMAXMSOFAUTOIPCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBEMINMSOFAUTOIPCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBENUMOFAUTOIPCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBEWAITMAXMSOFAUTOIPCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBEWAITMINMSOFAUTOIPCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_RATELIMITINTERVALMSOFAUTOIPCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_BUF2TXREQMAP                                                                          STD_ON
#define TCPIP_ETHBUFIDXNEXTOFBUF2TXREQMAP                                                           STD_ON
#define TCPIP_ETHBUFLENOFBUF2TXREQMAP                                                               STD_ON
#define TCPIP_ETHBUFPTROFBUF2TXREQMAP                                                               STD_ON
#define TCPIP_SOCKETDYNIDXOFBUF2TXREQMAP                                                            STD_ON
#define TCPIP_ULTXREQIDXOFBUF2TXREQMAP                                                              STD_ON
#define TCPIP_DEFAULTMULTICASTADDRV4                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDROFDEFAULTMULTICASTADDRV4                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFAULTUNICASTADDRV4                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFGWADDROFDEFAULTUNICASTADDRV4                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDROFDEFAULTUNICASTADDRV4                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETMASKOFDEFAULTUNICASTADDRV4                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPCONFIG                                                                            STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_DISCOVERINTERVALMAXOFDHCPCONFIG                                                       STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.DiscoverIntervalMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DISCOVERINTERVALMINOFDHCPCONFIG                                                       STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.DiscoverIntervalMin' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DISCOVERMAXNUMOFDHCPCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.DiscoverMaxNum' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_HOSTNAMELENMAXOFDHCPCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.HostNameLenMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INITWAITMAXOFDHCPCONFIG                                                               STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.InitWaitMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INITWAITMINOFDHCPCONFIG                                                               STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.InitWaitMin' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REBINDINTERVALMINOFDHCPCONFIG                                                         STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RebindIntervalMin' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RENEWINTERVALMINOFDHCPCONFIG                                                          STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RenewIntervalMin' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REQADDRCALLOUTFUNCOFDHCPCONFIG                                                        STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.ReqAddrCalloutFunc' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REQUESTINTERVALOFDHCPCONFIG                                                           STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RequestInterval' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REQUESTMAXNUMOFDHCPCONFIG                                                             STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RequestMaxNum' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RESTARTONFAILOFDHCPCONFIG                                                             STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RestartOnFail' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RXREQOPTIONCNTOFDHCPCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_DhcpConfig.RxReqOptionCnt' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPHOSTNAME                                                                          STD_OFF  /**< Deactivateable: 'TcpIp_DhcpHostname' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPSTATUS                                                                            STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_CTRLSTATEOFDHCPSTATUS                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.CtrlState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DATASTRUCTOFDHCPSTATUS                                                                STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.DataStruct' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_HOSTNAMELENOFDHCPSTATUS                                                               STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.HostNameLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_LASTDISCOVERSECSOFDHCPSTATUS                                                          STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.LastDiscoverSecs' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_MSTIMEROFDHCPSTATUS                                                                   STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.MsTimer' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REQIPADDROFDHCPSTATUS                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.ReqIpAddr' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RETRYCOUNTEROFDHCPSTATUS                                                              STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.RetryCounter' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SECELAPSEDOFDHCPSTATUS                                                                STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.SecElapsed' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SECNEXTEVENTOFDHCPSTATUS                                                              STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.SecNextEvent' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SECNEXTINTERVALOFDHCPSTATUS                                                           STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.SecNextInterval' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SECTIMEROFDHCPSTATUS                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.SecTimer' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TIMEOUTOCCURREDOFDHCPSTATUS                                                           STD_OFF  /**< Deactivateable: 'TcpIp_DhcpStatus.TimeoutOccurred' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DHCPUSEROPTION                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_CODEOFDHCPUSEROPTION                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONBUFFERENDIDXOFDHCPUSEROPTION                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONBUFFERLENGTHOFDHCPUSEROPTION                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONBUFFERSTARTIDXOFDHCPUSEROPTION                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DIRECTIONOFDHCPUSEROPTION                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONBUFFER                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONDYN                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_LENGTHOFDHCPUSEROPTIONDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPV4SERVERADDRLEASERECS                                                             STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddrLeaseRecs' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPV4SERVERADDRESSASSIGNMENTCONFIG                                                   STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddressAssignmentConfig' Reason: 'DHCPv4 Server is disabled.' */
#define TCPIP_DHCPADDRFIRSTOFDHCPV4SERVERADDRESSASSIGNMENTCONFIG                                    STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddressAssignmentConfig.DhcpAddrFirst' Reason: 'DHCPv4 Server is disabled.' */
#define TCPIP_DHCPV4SERVERADDRLEASERECSENDIDXOFDHCPV4SERVERADDRESSASSIGNMENTCONFIG                  STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddressAssignmentConfig.DhcpV4ServerAddrLeaseRecsEndIdx' Reason: 'DHCPv4 Server is disabled.' */
#define TCPIP_DHCPV4SERVERADDRLEASERECSSTARTIDXOFDHCPV4SERVERADDRESSASSIGNMENTCONFIG                STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddressAssignmentConfig.DhcpV4ServerAddrLeaseRecsStartIdx' Reason: 'DHCPv4 Server is disabled.' */
#define TCPIP_ETHSWITCHPORTIDXOFDHCPV4SERVERADDRESSASSIGNMENTCONFIG                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerAddressAssignmentConfig.EthSwitchPortIdx' Reason: 'DHCPv4 Server is disabled.' */
#define TCPIP_DHCPV4SERVERCONFIG                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_ADDRPREFIXLENGTHOFDHCPV4SERVERCONFIG                                                  STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.AddrPrefixLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DEFAULTROUTERADDROFDHCPV4SERVERCONFIG                                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DefaultRouterAddr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPV4SERVERADDRESSASSIGNMENTCONFIGENDIDXOFDHCPV4SERVERCONFIG                         STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerAddressAssignmentConfigEndIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define TCPIP_DHCPV4SERVERADDRESSASSIGNMENTCONFIGSTARTIDXOFDHCPV4SERVERCONFIG                       STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerAddressAssignmentConfigStartIdx' Reason: 'All indirection targets are deactivated in all variants.' */
#define TCPIP_DHCPV4SERVERADDRESSASSIGNMENTCONFIGUSEDOFDHCPV4SERVERCONFIG                           STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerAddressAssignmentConfigUsed' Reason: 'All indirection targets are deactivated in all variants.' */
#define TCPIP_DHCPV4SERVERHOSTNAMEENDIDXOFDHCPV4SERVERCONFIG                                        STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerHostnameEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPV4SERVERHOSTNAMESTARTIDXOFDHCPV4SERVERCONFIG                                      STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerHostnameStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPV4SERVERHOSTNAMEUSEDOFDHCPV4SERVERCONFIG                                          STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.DhcpV4ServerHostnameUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_ETHIFSWITCHIDXOFDHCPV4SERVERCONFIG                                                    STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.EthIfSwitchIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LEASETIMESECDEFAULTOFDHCPV4SERVERCONFIG                                               STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.LeaseTimeSecDefault' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LEASETIMESECMAXOFDHCPV4SERVERCONFIG                                                   STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.LeaseTimeSecMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LEASETIMESECMINOFDHCPV4SERVERCONFIG                                                   STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.LeaseTimeSecMin' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LOCALADDRV4IDXOFDHCPV4SERVERCONFIG                                                    STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.LocalAddrV4Idx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_MAXCLIENTIDLENOFDHCPV4SERVERCONFIG                                                    STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.MaxClientIdLen' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_OFFERVALIDTIMESECOFDHCPV4SERVERCONFIG                                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfig.OfferValidTimeSec' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DHCPV4SERVERCONFIGDYN                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfigDyn' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_IPADDRASSIGNMENTSTATEOFDHCPV4SERVERCONFIGDYN                                          STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfigDyn.IpAddrAssignmentState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKETIDOFDHCPV4SERVERCONFIGDYN                                                       STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerConfigDyn.SocketId' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DHCPV4SERVERHOSTNAME                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_DhcpV4ServerHostname' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_DUPLICATEADDRDETECTIONFCTPTR                                                          STD_ON
#define TCPIP_ETHIFCTRL                                                                             STD_ON
#define TCPIP_IPV4CTRLIDXOFETHIFCTRL                                                                STD_ON
#define TCPIP_IPV4CTRLUSEDOFETHIFCTRL                                                               STD_ON
#define TCPIP_FINALMAGICNUMBER                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define TCPIP_FRAGMENTATIONCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_INORDERREASSEMBLYOFFRAGMENTATIONCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_MAXPACKETSIZEOFFRAGMENTATIONCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCENDIDXOFFRAGMENTATIONCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCLENGTHOFFRAGMENTATIONCONFIG                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCSTARTIDXOFFRAGMENTATIONCONFIG                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCUSEDOFFRAGMENTATIONCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYTIMEOUTMSOFFRAGMENTATIONCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_GRATUITOUSARP                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NEXTTRANSMISSIONMSOFGRATUITOUSARP                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TRANSMISSIONCNTOFGRATUITOUSARP                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ICMPCONFIG                                                                            STD_OFF  /**< Deactivateable: 'TcpIp_IcmpConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_TIMETOLIVEOFICMPCONFIG                                                                STD_OFF  /**< Deactivateable: 'TcpIp_IcmpConfig.TimeToLive' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_ICMPDESTUNREACHABLEMSG                                                                STD_OFF  /**< Deactivateable: 'TcpIp_IcmpDestUnreachableMsg' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_ICMPECHOREPLYDATA                                                                     STD_OFF  /**< Deactivateable: 'TcpIp_IcmpEchoReplyData' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_ICMPMSGHANDLERCBKFCTPTR                                                               STD_ON
#define TCPIP_INITDATAHASHCODE                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define TCPIP_INTEGRITYALGORITHM                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityAlgorithm' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_ICVLENGTHOFINTEGRITYALGORITHM                                                         STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityAlgorithm.IcvLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYJOBPAIRENDIDXOFINTEGRITYALGORITHM                                            STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityAlgorithm.IntegrityJobPairEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYJOBPAIRSTARTIDXOFINTEGRITYALGORITHM                                          STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityAlgorithm.IntegrityJobPairStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYTRANSFORMIDENTOFINTEGRITYALGORITHM                                           STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityAlgorithm.IntegrityTransformIdent' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYJOBPAIR                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_GENERATEJOBIDOFINTEGRITYJOBPAIR                                                       STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair.GenerateJobId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_GENERATEKEYIDOFINTEGRITYJOBPAIR                                                       STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair.GenerateKeyId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYALGORITHMIDXOFINTEGRITYJOBPAIR                                               STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair.IntegrityAlgorithmIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_VERIFYJOBIDOFINTEGRITYJOBPAIR                                                         STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair.VerifyJobId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_VERIFYKEYIDOFINTEGRITYJOBPAIR                                                         STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPair.VerifyKeyId' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYJOBPAIRDYN                                                                   STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPairDyn' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_STATUSOFINTEGRITYJOBPAIRDYN                                                           STD_OFF  /**< Deactivateable: 'TcpIp_IntegrityJobPairDyn.Status' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_IPSECCONFIGSET                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_AUDITEVENTCALLOUTFUNCTIONOFIPSECCONFIGSET                                             STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.AuditEventCalloutFunction' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYALGORITHMENDIDXOFIPSECCONFIGSET                                              STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.IntegrityAlgorithmEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_INTEGRITYALGORITHMSTARTIDXOFIPSECCONFIGSET                                            STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.IntegrityAlgorithmStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_SPDCALLOUTFUNCTIONOFIPSECCONFIGSET                                                    STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.SpdCalloutFunction' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_SPDENTRYENDIDXOFIPSECCONFIGSET                                                        STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.SpdEntryEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_SPDENTRYSTARTIDXOFIPSECCONFIGSET                                                      STD_OFF  /**< Deactivateable: 'TcpIp_IpSecConfigSet.SpdEntryStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_IPV4CTRL                                                                              STD_ON
#define TCPIP_ADDRASSIGNMENTCFGBYPRIOENDIDXOFIPV4CTRL                                               STD_ON
#define TCPIP_ADDRASSIGNMENTCFGBYPRIOSTARTIDXOFIPV4CTRL                                             STD_ON
#define TCPIP_ADDRASSIGNMENTPRIOBYTYPEOFIPV4CTRL                                                    STD_ON
#define TCPIP_ARPCONFIGIDXOFIPV4CTRL                                                                STD_ON
#define TCPIP_ARPCONFIGUSEDOFIPV4CTRL                                                               STD_ON
#define TCPIP_ARPTABLEENTRYENDIDXOFIPV4CTRL                                                         STD_ON
#define TCPIP_ARPTABLEENTRYSTARTIDXOFIPV4CTRL                                                       STD_ON
#define TCPIP_ARPTABLEENTRYUSEDOFIPV4CTRL                                                           STD_ON
#define TCPIP_AUTOIPCONFIGIDXOFIPV4CTRL                                                             STD_ON
#define TCPIP_AUTOIPCONFIGUSEDOFIPV4CTRL                                                            STD_ON
#define TCPIP_BUF2TXREQMAPENDIDXOFIPV4CTRL                                                          STD_ON
#define TCPIP_BUF2TXREQMAPSTARTIDXOFIPV4CTRL                                                        STD_ON
#define TCPIP_DEFAULTTTLOFIPV4CTRL                                                                  STD_ON
#define TCPIP_DHCPCONFIGIDXOFIPV4CTRL                                                               STD_ON
#define TCPIP_DHCPCONFIGUSEDOFIPV4CTRL                                                              STD_ON
#define TCPIP_DHCPHOSTNAMEENDIDXOFIPV4CTRL                                                          STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.DhcpHostnameEndIdx' Reason: 'the optional indirection is deactivated because DhcpHostnameUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_DHCPHOSTNAMESTARTIDXOFIPV4CTRL                                                        STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.DhcpHostnameStartIdx' Reason: 'the optional indirection is deactivated because DhcpHostnameUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_DHCPHOSTNAMEUSEDOFIPV4CTRL                                                            STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.DhcpHostnameUsed' Reason: 'the optional indirection is deactivated because DhcpHostnameUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_DHCPSTATUSIDXOFIPV4CTRL                                                               STD_ON
#define TCPIP_DHCPSTATUSUSEDOFIPV4CTRL                                                              STD_ON
#define TCPIP_DHCPUSEROPTIONENDIDXOFIPV4CTRL                                                        STD_ON
#define TCPIP_DHCPUSEROPTIONSTARTIDXOFIPV4CTRL                                                      STD_ON
#define TCPIP_DHCPUSEROPTIONUSEDOFIPV4CTRL                                                          STD_ON
#define TCPIP_ETHIFCTRLIDXOFIPV4CTRL                                                                STD_ON
#define TCPIP_FRAGMENTATIONCONFIGIDXOFIPV4CTRL                                                      STD_ON
#define TCPIP_FRAGMENTATIONCONFIGUSEDOFIPV4CTRL                                                     STD_ON
#define TCPIP_FRAMEPRIODEFAULTOFIPV4CTRL                                                            STD_ON
#define TCPIP_GRATUITOUSARPIDXOFIPV4CTRL                                                            STD_ON
#define TCPIP_GRATUITOUSARPUSEDOFIPV4CTRL                                                           STD_ON
#define TCPIP_HWCHECKSUMICMPOFIPV4CTRL                                                              STD_ON
#define TCPIP_HWCHECKSUMIPOFIPV4CTRL                                                                STD_ON
#define TCPIP_HWCHECKSUMTCPOFIPV4CTRL                                                               STD_ON
#define TCPIP_HWCHECKSUMUDPOFIPV4CTRL                                                               STD_ON
#define TCPIP_IPSECCONFIGSETIDXOFIPV4CTRL                                                           STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.IpSecConfigSetIdx' Reason: 'the optional indirection is deactivated because IpSecConfigSetUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_IPSECCONFIGSETUSEDOFIPV4CTRL                                                          STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.IpSecConfigSetUsed' Reason: 'the optional indirection is deactivated because IpSecConfigSetUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_LLADDRSTATEIDXOFIPV4CTRL                                                              STD_ON
#define TCPIP_LLADDRSTATEUSEDOFIPV4CTRL                                                             STD_ON
#define TCPIP_LOCALADDRV4BROADCASTIDXOFIPV4CTRL                                                     STD_ON
#define TCPIP_LOCALADDRV4DHCPIDXOFIPV4CTRL                                                          STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.LocalAddrV4DhcpIdx' Reason: 'the optional indirection is deactivated because LocalAddrV4DhcpUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_LOCALADDRV4DHCPUSEDOFIPV4CTRL                                                         STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.LocalAddrV4DhcpUsed' Reason: 'the optional indirection is deactivated because LocalAddrV4DhcpUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_LOCALADDRV4UNICASTIDXOFIPV4CTRL                                                       STD_ON
#define TCPIP_MAXTXMSGSIZEOFIPV4CTRL                                                                STD_ON
#define TCPIP_MTUTXOFIPV4CTRL                                                                       STD_ON
#define TCPIP_MULTICASTADDRV4ENDIDXOFIPV4CTRL                                                       STD_ON
#define TCPIP_MULTICASTADDRV4STARTIDXOFIPV4CTRL                                                     STD_ON
#define TCPIP_MULTICASTADDRV4USEDOFIPV4CTRL                                                         STD_ON
#define TCPIP_NVMDATAIDXOFIPV4CTRL                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.NvmDataIdx' Reason: 'the optional indirection is deactivated because NvmDataUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_NVMDATAUSEDOFIPV4CTRL                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.NvmDataUsed' Reason: 'the optional indirection is deactivated because NvmDataUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_RECEIVEALLMULTICASTSOFIPV4CTRL                                                        STD_ON
#define TCPIP_SAENTRYENDIDXOFIPV4CTRL                                                               STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.SaEntryEndIdx' Reason: 'the optional indirection is deactivated because SaEntryUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_SAENTRYSTARTIDXOFIPV4CTRL                                                             STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.SaEntryStartIdx' Reason: 'the optional indirection is deactivated because SaEntryUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_SAENTRYUSEDOFIPV4CTRL                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_IpV4Ctrl.SaEntryUsed' Reason: 'the optional indirection is deactivated because SaEntryUsedOfIpV4Ctrl is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define TCPIP_STATICARPTABLEIDXOFIPV4CTRL                                                           STD_ON
#define TCPIP_STATICARPTABLEUSEDOFIPV4CTRL                                                          STD_ON
#define TCPIP_TYPEOFSERVICEDEFAULTOFIPV4CTRL                                                        STD_ON
#define TCPIP_UNICASTADDRV4IDXOFIPV4CTRL                                                            STD_ON
#define TCPIP_IPV4CTRLDYN                                                                           STD_ON
#define TCPIP_ACTIVEADDRASSIGNMENTMETHODOFIPV4CTRLDYN                                               STD_ON
#define TCPIP_ACTIVEDEFGWADDROFIPV4CTRLDYN                                                          STD_ON
#define TCPIP_ACTIVENETADDROFIPV4CTRLDYN                                                            STD_ON
#define TCPIP_ACTIVENETMASKOFIPV4CTRLDYN                                                            STD_ON
#define TCPIP_ADDRASSIGNMENTREADYCHANGEDOFIPV4CTRLDYN                                               STD_ON
#define TCPIP_ADDRASSIGNMENTTRIGGEREDFLAGSOFIPV4CTRLDYN                                             STD_ON
#define TCPIP_LASTBCADDROFIPV4CTRLDYN                                                               STD_ON
#define TCPIP_PHYSLINKACTIVEOFIPV4CTRLDYN                                                           STD_ON
#define TCPIP_STATEOFIPV4CTRLDYN                                                                    STD_ON
#define TCPIP_IPV4GENERAL                                                                           STD_ON
#define TCPIP_IPV4CTRLDEFAULTIDXOFIPV4GENERAL                                                       STD_ON
#define TCPIP_IPV4CTRLDEFAULTUSEDOFIPV4GENERAL                                                      STD_ON
#define TCPIP_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL                                                     STD_ON
#define TCPIP_IPV4SOCKETDYNDHCPUSEDOFIPV4GENERAL                                                    STD_ON
#define TCPIP_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL                                                     STD_ON
#define TCPIP_IPV4SOCKETDYNICMPUSEDOFIPV4GENERAL                                                    STD_ON
#define TCPIP_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL                                                   STD_ON
#define TCPIP_IPV4SOCKETDYNTCPRSTUSEDOFIPV4GENERAL                                                  STD_ON
#define TCPIP_IPV4SOCKETDYN                                                                         STD_ON
#define TCPIP_ARPTABLEENTRYIDXOFIPV4SOCKETDYN                                                       STD_ON
#define TCPIP_ETHIFFRAMEPRIOOFIPV4SOCKETDYN                                                         STD_ON
#define TCPIP_FLAGSOFIPV4SOCKETDYN                                                                  STD_ON
#define TCPIP_IPV4CTRLIDXOFIPV4SOCKETDYN                                                            STD_ON
#define TCPIP_LOCSOCKOFIPV4SOCKETDYN                                                                STD_ON
#define TCPIP_PHYSDESTADDROFIPV4SOCKETDYN                                                           STD_ON
#define TCPIP_PROTOCOLOFIPV4SOCKETDYN                                                               STD_ON
#define TCPIP_TIMETOLIVEOFIPV4SOCKETDYN                                                             STD_ON
#define TCPIP_TRANSFERBLOCKOFIPV4SOCKETDYN                                                          STD_ON
#define TCPIP_TXDESCRIPTORPROTOCOLOFIPV4SOCKETDYN                                                   STD_ON
#define TCPIP_TYPEOFSERVICEOFIPV4SOCKETDYN                                                          STD_ON
#define TCPIP_LLADDRSTATE                                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ADDRCONFLICTOFLLADDRSTATE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ADDRCONFLICTTIMEOUTOFLLADDRSTATE                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ADDRFOUNDOFLLADDRSTATE                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ANNSTATEOFLLADDRSTATE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ANNOUNCENUMOFLLADDRSTATE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_CONFLICTSNUMOFLLADDRSTATE                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_MSECCNTOFLLADDRSTATE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDRCANDOFLLADDRSTATE                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBENUMOFLLADDRSTATE                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBENUMSINCECONFOFLLADDRSTATE                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PROBESTATEOFLLADDRSTATE                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATEOFLLADDRSTATE                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_WAITUNTILTIMEOFLLADDRSTATE                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_LOCALADDR                                                                             STD_ON
#define TCPIP_ASSIGNMENTSTATEOFLOCALADDR                                                            STD_ON
#define TCPIP_LOCALADDRV4                                                                           STD_ON
#define TCPIP_IPV4CTRLIDXOFLOCALADDRV4                                                              STD_ON
#define TCPIP_MULTICASTADDRV4IDXOFLOCALADDRV4                                                       STD_ON
#define TCPIP_MULTICASTADDRV4USEDOFLOCALADDRV4                                                      STD_ON
#define TCPIP_UNICASTADDRV4IDXOFLOCALADDRV4                                                         STD_ON
#define TCPIP_UNICASTADDRV4USEDOFLOCALADDRV4                                                        STD_ON
#define TCPIP_MEASUREMENTDATA                                                                       STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDIPV4PACKETSINSUFFREASSEMBLYBUFOFMEASUREMENTDATA                                STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedIpV4PacketsInsuffReassemblyBuf' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDIPV4PACKETSOFMEASUREMENTDATA                                                   STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedIpV4Packets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDIPV6PACKETSOFMEASUREMENTDATA                                                   STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedIpV6Packets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDTCPPACKETSINSUFFRXBUFOFMEASUREMENTDATA                                         STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedTcpPacketsInsuffRxBuf' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDTCPPACKETSINSUFFTXBUFOFMEASUREMENTDATA                                         STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedTcpPacketsInsuffTxBuf' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDTCPPACKETSOFMEASUREMENTDATA                                                    STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedTcpPackets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDUDPPACKETSOFMEASUREMENTDATA                                                    STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedUdpPackets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDVNDRIPV6PACKETSOFMEASUREMENTDATA                                               STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedVndrIpV6Packets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DROPPEDVNDRLAYER4PACKETSOFMEASUREMENTDATA                                             STD_OFF  /**< Deactivateable: 'TcpIp_MeasurementData.DroppedVndrLayer4Packets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_MULTICASTADDRV4                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFAULTMULTICASTADDRV4IDXOFMULTICASTADDRV4                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_LOCALADDRV4IDXOFMULTICASTADDRV4                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_MULTICASTADDRV4REQUESTED                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDROFMULTICASTADDRV4REQUESTED                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NVMDATA                                                                               STD_OFF  /**< Deactivateable: 'TcpIp_NvmData' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_NVMDATAROM                                                                            STD_OFF  /**< Deactivateable: 'TcpIp_NvmDataRom' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_PHYSADDRCONFIG                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_CHGDISCARDEDFUNCPTROFPHYSADDRCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_CHGFUNCPTROFPHYSADDRCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_RANDOMNUMBERFCTPTR                                                                    STD_ON
#define TCPIP_REASSEMBLYBUFFER                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESC                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERENDIDXOFREASSEMBLYBUFFERDESC                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERSTARTIDXOFREASSEMBLYBUFFERDESC                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCDYN                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SAENTRY                                                                               STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_DIRECTIONOFSAENTRY                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.Direction' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_ESNSUPPORTOFSAENTRY                                                                   STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.EsnSupport' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_INUSEFLAGOFSAENTRY                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.InUseFlag' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_INTEGRITYCHKLENOFSAENTRY                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.IntegrityChkLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_INTEGRITYJOBPAIRIDXOFSAENTRY                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.IntegrityJobPairIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_INTEGRITYTRANSFORMIDENTOFSAENTRY                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.IntegrityTransformIdent' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_IPSECHDRTYPEOFSAENTRY                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.IpSecHdrType' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_LOCIPV4ADDROFSAENTRY                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.LocIpV4Addr' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_LOCPORTENDOFSAENTRY                                                                   STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.LocPortEnd' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_LOCPORTSTARTOFSAENTRY                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.LocPortStart' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_NONCEOFSAENTRY                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.Nonce' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REMIPV4ADDROFSAENTRY                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.RemIpV4Addr' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REMPORTENDOFSAENTRY                                                                   STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.RemPortEnd' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REMPORTSTARTOFSAENTRY                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.RemPortStart' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SAENTRYPAIRIDXOFSAENTRY                                                               STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.SaEntryPairIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SEQNUMHOFSAENTRY                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.SeqNumH' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SEQNUMLOFSAENTRY                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.SeqNumL' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SPIOFSAENTRY                                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.Spi' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_UWNDHOFSAENTRY                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.UWndH' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_UWNDLOFSAENTRY                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.UWndL' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_WNDBITSOFSAENTRY                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.WndBits' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_XPTPROTOFSAENTRY                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SaEntry.XptProt' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SIZEOFADDRASSIGNMENTCFGBYPRIO                                                         STD_ON
#define TCPIP_SIZEOFARPCONFIG                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFARPTABLEENTRY                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFAUTOIPCONFIG                                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFBUF2TXREQMAP                                                                    STD_ON
#define TCPIP_SIZEOFDEFAULTMULTICASTADDRV4                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDEFAULTUNICASTADDRV4                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTION                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTIONBUFFER                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTIONDYN                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFETHIFCTRL                                                                       STD_ON
#define TCPIP_SIZEOFFRAGMENTATIONCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFGRATUITOUSARP                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFIPV4CTRL                                                                        STD_ON
#define TCPIP_SIZEOFIPV4CTRLDYN                                                                     STD_ON
#define TCPIP_SIZEOFIPV4GENERAL                                                                     STD_ON
#define TCPIP_SIZEOFIPV4SOCKETDYN                                                                   STD_ON
#define TCPIP_SIZEOFLLADDRSTATE                                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFLOCALADDR                                                                       STD_ON
#define TCPIP_SIZEOFLOCALADDRV4                                                                     STD_ON
#define TCPIP_SIZEOFMULTICASTADDRV4                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFMULTICASTADDRV4REQUESTED                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFPHYSADDRCONFIG                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFER                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFERDESC                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFERDESCDYN                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSOCKETDYN                                                                       STD_ON
#define TCPIP_SIZEOFSOCKETOWNERCONFIG                                                               STD_ON
#define TCPIP_SIZEOFSOCKETUDPDYN                                                                    STD_ON
#define TCPIP_SIZEOFSTATICARPENTRY                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSTATICARPTABLE                                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSTATICUNICASTADDRV4REQUESTED                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEM                                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEMLIST                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEMLISTDYN                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEELEMENTCHAIN                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEELEMENTS                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEPOOLDESC                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUNICASTADDRV4                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SOCKETDYN                                                                             STD_ON
#define TCPIP_LISTENACTIVECONNSTATOFSOCKETDYN                                                       STD_ON
#define TCPIP_LOCSOCKOFSOCKETDYN                                                                    STD_ON
#define TCPIP_LOCALADDRBINDIDXOFSOCKETDYN                                                           STD_ON
#define TCPIP_REMSOCKOFSOCKETDYN                                                                    STD_ON
#define TCPIP_SOCKETOWNERCONFIGIDXOFSOCKETDYN                                                       STD_ON
#define TCPIP_TXBUFREQUESTEDOFSOCKETDYN                                                             STD_ON
#define TCPIP_TXIPADDRIDXOFSOCKETDYN                                                                STD_ON
#define TCPIP_SOCKETOWNERCONFIG                                                                     STD_ON
#define TCPIP_COPYTXDATADYNFUNCPTROFSOCKETOWNERCONFIG                                               STD_ON
#define TCPIP_COPYTXDATAFUNCPTROFSOCKETOWNERCONFIG                                                  STD_ON
#define TCPIP_DHCPEVENTFUNCPTROFSOCKETOWNERCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_LOCALIPADDRASSIGNMENTCHGFUNCPTROFSOCKETOWNERCONFIG                                    STD_ON
#define TCPIP_RXINDICATIONFUNCPTROFSOCKETOWNERCONFIG                                                STD_ON
#define TCPIP_TCPACCEPTEDFUNCPTROFSOCKETOWNERCONFIG                                                 STD_ON
#define TCPIP_TCPCONNECTEDFUNCPTROFSOCKETOWNERCONFIG                                                STD_ON
#define TCPIP_TCPIPEVENTFUNCPTROFSOCKETOWNERCONFIG                                                  STD_ON
#define TCPIP_TLSVALIDATIONRESULTFUNCPTROFSOCKETOWNERCONFIG                                         STD_ON
#define TCPIP_TXCONFIRMATIONFUNCPTROFSOCKETOWNERCONFIG                                              STD_ON
#define TCPIP_SOCKETTCPCONGCTRLDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpCongCtrlDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETTCPDYN                                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_BACKLOGARRAYOFSOCKETTCPDYN                                                            STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.BackLogArray' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_EVENTINDICATIONPENDINGOFSOCKETTCPDYN                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.EventIndicationPending' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_FINWAIT2TIMEOUTOFSOCKETTCPDYN                                                         STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.FinWait2Timeout' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_IDLETIMEOUTSHORTOFSOCKETTCPDYN                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.IdleTimeoutShort' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_ISSOFSOCKETTCPDYN                                                                     STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.Iss' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_MAXNUMLISTENSOCKETSOFSOCKETTCPDYN                                                     STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.MaxNumListenSockets' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_MSLTIMEOUTOFSOCKETTCPDYN                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.MslTimeout' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_PATHMTUCHANGEDOFSOCKETTCPDYN                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.PathMtuChanged' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_PATHMTUNEWSIZEOFSOCKETTCPDYN                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.PathMtuNewSize' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RCVNXTOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RcvNxt' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RCVWNDOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RcvWnd' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REQUESTEDRXBUFFERSIZEOFSOCKETTCPDYN                                                   STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RequestedRxBufferSize' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_REQUESTEDTXBUFFERSIZEOFSOCKETTCPDYN                                                   STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RequestedTxBufferSize' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RETRANSMITTIMEOUTOFSOCKETTCPDYN                                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RetransmitTimeout' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RETRYQFILLNUMOFSOCKETTCPDYN                                                           STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RetryQFillNum' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RSTRECEIVEDOFSOCKETTCPDYN                                                             STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RstReceived' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RTORELOADVALUEOFSOCKETTCPDYN                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RtoReloadValue' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RXBUFFERINDPOSOFSOCKETTCPDYN                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RxBufferIndPos' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_RXBUFFERREMINDLENOFSOCKETTCPDYN                                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.RxBufferRemIndLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SENDLASTHSACKOFSOCKETTCPDYN                                                           STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SendLastHsAck' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SNDNXTOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SndNxt' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SNDUNAOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SndUna' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SNDWL1OFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SndWl1' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SNDWL2OFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SndWl2' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SNDWNDOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SndWnd' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKISSERVEROFSOCKETTCPDYN                                                            STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SockIsServer' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKSTATENEXTOFSOCKETTCPDYN                                                           STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SockStateNext' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKSTATEOFSOCKETTCPDYN                                                               STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SockState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKETTCPDYNMASTERLISTENSOCKETIDXOFSOCKETTCPDYN                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.SocketTcpDynMasterListenSocketIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPRETRYQELEMENTFIRSTIDXOFSOCKETTCPDYN                                                STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TcpRetryQElementFirstIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPRETRYQELEMENTLASTIDXOFSOCKETTCPDYN                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TcpRetryQElementLastIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPRXBUFFERDESCIDXOFSOCKETTCPDYN                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TcpRxBufferDescIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPTXBUFFERDESCIDXOFSOCKETTCPDYN                                                      STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TcpTxBufferDescIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXFLAGSOFSOCKETTCPDYN                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxFlags' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXLENBYTETXOFSOCKETTCPDYN                                                             STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxLenByteTx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXMAXSEGLENBYTEOFSOCKETTCPDYN                                                         STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxMaxSegLenByte' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXMSSAGREEDOFSOCKETTCPDYN                                                             STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxMssAgreed' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXNEXTSENDSEQNOOFSOCKETTCPDYN                                                         STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxNextSendSeqNo' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXONETIMEOPTSLENOFSOCKETTCPDYN                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxOneTimeOptsLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXONETIMEOPTSOFSOCKETTCPDYN                                                           STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxOneTimeOpts' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXOPTLENOFSOCKETTCPDYN                                                                STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxOptLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQDATABUFSTARTIDXOFSOCKETTCPDYN                                                    STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxReqDataBufStartIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQDATALENBYTEOFSOCKETTCPDYN                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxReqDataLenByte' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQFULLYQUEUEDOFSOCKETTCPDYN                                                        STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxReqFullyQueued' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQQUEUEDLENOFSOCKETTCPDYN                                                          STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxReqQueuedLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQSEQNOOFSOCKETTCPDYN                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxReqSeqNo' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXTOTNOTQUEUEDLENOFSOCKETTCPDYN                                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.TxTotNotQueuedLen' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_USETLSOFSOCKETTCPDYN                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpDyn.UseTls' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKETTCPKEEPALIVEDYN                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpKeepAliveDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETTCPNAGLEDYN                                                                     STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpNagleDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETTCPOOODYN                                                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpOooDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETTCPTSOPTDYN                                                                     STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpTsOptDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETTCPUTODYN                                                                       STD_OFF  /**< Deactivateable: 'TcpIp_SocketTcpUtoDyn' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_SOCKETUDPDYN                                                                          STD_ON
#define TCPIP_IPTXREQUESTDESCRIPTOROFSOCKETUDPDYN                                                   STD_ON
#define TCPIP_TXREQELEMLISTIDXOFSOCKETUDPDYN                                                        STD_ON
#define TCPIP_TXREQIPBUFPTROFSOCKETUDPDYN                                                           STD_ON
#define TCPIP_TXRETRQUEUEMAXNUMOFSOCKETUDPDYN                                                       STD_ON
#define TCPIP_TXRETRQUEUEOFSOCKETUDPDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SPDENTRY                                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_IPSECHDRTYPEOFSPDENTRY                                                                STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.IpSecHdrType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LOCIPV4ADDRENDOFSPDENTRY                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.LocIpV4AddrEnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LOCIPV4ADDRSTARTOFSPDENTRY                                                            STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.LocIpV4AddrStart' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LOCPORTENDOFSPDENTRY                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.LocPortEnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_LOCPORTSTARTOFSPDENTRY                                                                STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.LocPortStart' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_POLICYTYPEOFSPDENTRY                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.PolicyType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_PRIORITYOFSPDENTRY                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.Priority' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REMIPV4ADDRENDOFSPDENTRY                                                              STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.RemIpV4AddrEnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REMIPV4ADDRSTARTOFSPDENTRY                                                            STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.RemIpV4AddrStart' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REMPORTENDOFSPDENTRY                                                                  STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.RemPortEnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_REMPORTSTARTOFSPDENTRY                                                                STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.RemPortStart' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_XPTPROTOCOLOFSPDENTRY                                                                 STD_OFF  /**< Deactivateable: 'TcpIp_SpdEntry.XptProtocol' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_STATICARPENTRY                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_IPADDROFSTATICARPENTRY                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PHYSADDROFSTATICARPENTRY                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICARPTABLE                                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICARPENTRYENDIDXOFSTATICARPTABLE                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICARPENTRYSTARTIDXOFSTATICARPTABLE                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICUNICASTADDRV4REQUESTED                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFGWADDROFSTATICUNICASTADDRV4REQUESTED                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETADDROFSTATICUNICASTADDRV4REQUESTED                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_NETMASKOFSTATICUNICASTADDRV4REQUESTED                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TCPCONFIG                                                                             STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_FINWAIT2TIMEOUTOFTCPCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.FinWait2Timeout' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_KEEPALIVEINTERVALOFTCPCONFIG                                                          STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.KeepAliveInterval' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_KEEPALIVEPROBESMAXOFTCPCONFIG                                                         STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.KeepAliveProbesMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_KEEPALIVETIMEOFTCPCONFIG                                                              STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.KeepAliveTime' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_MSLOFTCPCONFIG                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.Msl' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_NAGLETIMEOUTOFTCPCONFIG                                                               STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.NagleTimeout' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RETRANSTIMEOUTMAXOFTCPCONFIG                                                          STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.RetransTimeoutMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RETRANSTIMEOUTOFTCPCONFIG                                                             STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.RetransTimeout' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_RXMSSOFTCPCONFIG                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.RxMss' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPOOOQSIZEPERSOCKETAVGOFTCPCONFIG                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.TcpOooQSizePerSocketAvg' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPOOOQSIZEPERSOCKETMAXOFTCPCONFIG                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.TcpOooQSizePerSocketMax' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRETRYQSIZEOFTCPCONFIG                                                              STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.TcpRetryQSize' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TIMETOLIVEDEFAULTOFTCPCONFIG                                                          STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.TimeToLiveDefault' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TXMSSOFTCPCONFIG                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.TxMss' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_USERTIMEOUTDEFCYCLESOFTCPCONFIG                                                       STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.UserTimeoutDefCycles' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_USERTIMEOUTMAXCYCLESOFTCPCONFIG                                                       STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.UserTimeoutMaxCycles' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_USERTIMEOUTMINCYCLESOFTCPCONFIG                                                       STD_OFF  /**< Deactivateable: 'TcpIp_TcpConfig.UserTimeoutMinCycles' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPOOOQELEMENT                                                                        STD_OFF  /**< Deactivateable: 'TcpIp_TcpOooQElement' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRETRYQELEMENT                                                                      STD_OFF  /**< Deactivateable: 'TcpIp_TcpRetryQElement' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRXBUFFER                                                                           STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBuffer' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRXBUFFERDESC                                                                       STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDesc' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_TCPRXBUFFERENDIDXOFTCPRXBUFFERDESC                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDesc.TcpRxBufferEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRXBUFFERLENGTHOFTCPRXBUFFERDESC                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDesc.TcpRxBufferLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRXBUFFERSTARTIDXOFTCPRXBUFFERDESC                                                  STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDesc.TcpRxBufferStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPRXBUFFERDESCDYN                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDescDyn' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_FILLLEVELOFTCPRXBUFFERDESCDYN                                                         STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDescDyn.FillLevel' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKETTCPDYNIDXOFTCPRXBUFFERDESCDYN                                                   STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDescDyn.SocketTcpDynIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPRXBUFFERWRITEIDXOFTCPRXBUFFERDESCDYN                                               STD_OFF  /**< Deactivateable: 'TcpIp_TcpRxBufferDescDyn.TcpRxBufferWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPTXBUFFER                                                                           STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBuffer' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPTXBUFFERDESC                                                                       STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDesc' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define TCPIP_TCPTXBUFFERENDIDXOFTCPTXBUFFERDESC                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDesc.TcpTxBufferEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPTXBUFFERLENGTHOFTCPTXBUFFERDESC                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDesc.TcpTxBufferLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPTXBUFFERSTARTIDXOFTCPTXBUFFERDESC                                                  STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDesc.TcpTxBufferStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define TCPIP_TCPTXBUFFERDESCDYN                                                                    STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDescDyn' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_FILLLEVELOFTCPTXBUFFERDESCDYN                                                         STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDescDyn.FillLevel' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_SOCKETTCPDYNIDXOFTCPTXBUFFERDESCDYN                                                   STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDescDyn.SocketTcpDynIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TCPTXBUFFERWRITEIDXOFTCPTXBUFFERDESCDYN                                               STD_OFF  /**< Deactivateable: 'TcpIp_TcpTxBufferDescDyn.TcpTxBufferWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define TCPIP_TXREQELEM                                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMDATALENBYTEOFTXREQELEM                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMTRANSMITTEDOFTXREQELEM                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMLIST                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMENDIDXOFTXREQELEMLIST                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMLENGTHOFTXREQELEMLIST                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMSTARTIDXOFTXREQELEMLIST                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMLISTDYN                                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_FILLNUMOFTXREQELEMLISTDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_READPOSOFTXREQELEMLISTDYN                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_WRITEPOSOFTXREQELEMLISTDYN                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEELEMENTCHAIN                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEELEMENTS                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEPOOLDESC                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UNICASTADDRV4                                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFAULTUNICASTADDRV4USEDOFUNICASTADDRV4                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICUNICASTADDRV4REQUESTEDUSEDOFUNICASTADDRV4                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PCCONFIG                                                                              STD_ON
#define TCPIP_ADDRASSIGNMENTCFGBYPRIOOFPCCONFIG                                                     STD_ON
#define TCPIP_ARPCONFIGOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ARPTABLEENTRYOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_AUTOIPCONFIGOFPCCONFIG                                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_BUF2TXREQMAPOFPCCONFIG                                                                STD_ON
#define TCPIP_DEFAULTMULTICASTADDRV4OFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DEFAULTUNICASTADDRV4OFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONBUFFEROFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONDYNOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DHCPUSEROPTIONOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_DUPLICATEADDRDETECTIONFCTPTROFPCCONFIG                                                STD_ON
#define TCPIP_ETHIFCTRLOFPCCONFIG                                                                   STD_ON
#define TCPIP_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define TCPIP_FRAGMENTATIONCONFIGOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_GRATUITOUSARPOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_ICMPMSGHANDLERCBKFCTPTROFPCCONFIG                                                     STD_ON
#define TCPIP_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'TcpIp_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define TCPIP_IPV4CTRLDYNOFPCCONFIG                                                                 STD_ON
#define TCPIP_IPV4CTRLOFPCCONFIG                                                                    STD_ON
#define TCPIP_IPV4GENERALOFPCCONFIG                                                                 STD_ON
#define TCPIP_IPV4SOCKETDYNOFPCCONFIG                                                               STD_ON
#define TCPIP_LLADDRSTATEOFPCCONFIG                                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_LOCALADDROFPCCONFIG                                                                   STD_ON
#define TCPIP_LOCALADDRV4OFPCCONFIG                                                                 STD_ON
#define TCPIP_MULTICASTADDRV4OFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_MULTICASTADDRV4REQUESTEDOFPCCONFIG                                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_PHYSADDRCONFIGOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_RANDOMNUMBERFCTPTROFPCCONFIG                                                          STD_ON
#define TCPIP_REASSEMBLYBUFFERDESCDYNOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFERDESCOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_REASSEMBLYBUFFEROFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFADDRASSIGNMENTCFGBYPRIOOFPCCONFIG                                               STD_ON
#define TCPIP_SIZEOFARPCONFIGOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFARPTABLEENTRYOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFAUTOIPCONFIGOFPCCONFIG                                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFBUF2TXREQMAPOFPCCONFIG                                                          STD_ON
#define TCPIP_SIZEOFDEFAULTMULTICASTADDRV4OFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDEFAULTUNICASTADDRV4OFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTIONBUFFEROFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTIONDYNOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFDHCPUSEROPTIONOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFETHIFCTRLOFPCCONFIG                                                             STD_ON
#define TCPIP_SIZEOFFRAGMENTATIONCONFIGOFPCCONFIG                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFGRATUITOUSARPOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFIPV4CTRLDYNOFPCCONFIG                                                           STD_ON
#define TCPIP_SIZEOFIPV4CTRLOFPCCONFIG                                                              STD_ON
#define TCPIP_SIZEOFIPV4GENERALOFPCCONFIG                                                           STD_ON
#define TCPIP_SIZEOFIPV4SOCKETDYNOFPCCONFIG                                                         STD_ON
#define TCPIP_SIZEOFLLADDRSTATEOFPCCONFIG                                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFLOCALADDROFPCCONFIG                                                             STD_ON
#define TCPIP_SIZEOFLOCALADDRV4OFPCCONFIG                                                           STD_ON
#define TCPIP_SIZEOFMULTICASTADDRV4OFPCCONFIG                                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFMULTICASTADDRV4REQUESTEDOFPCCONFIG                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFPHYSADDRCONFIGOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFERDESCDYNOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFERDESCOFPCCONFIG                                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFREASSEMBLYBUFFEROFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSOCKETDYNOFPCCONFIG                                                             STD_ON
#define TCPIP_SIZEOFSOCKETOWNERCONFIGOFPCCONFIG                                                     STD_ON
#define TCPIP_SIZEOFSOCKETUDPDYNOFPCCONFIG                                                          STD_ON
#define TCPIP_SIZEOFSTATICARPENTRYOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSTATICARPTABLEOFPCCONFIG                                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFSTATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEMLISTDYNOFPCCONFIG                                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEMLISTOFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFTXREQELEMOFPCCONFIG                                                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SIZEOFUNICASTADDRV4OFPCCONFIG                                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_SOCKETDYNOFPCCONFIG                                                                   STD_ON
#define TCPIP_SOCKETOWNERCONFIGOFPCCONFIG                                                           STD_ON
#define TCPIP_SOCKETUDPDYNOFPCCONFIG                                                                STD_ON
#define TCPIP_STATICARPENTRYOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICARPTABLEOFPCCONFIG                                                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_STATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMLISTDYNOFPCCONFIG                                                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMLISTOFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_TXREQELEMOFPCCONFIG                                                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define TCPIP_UNICASTADDRV4OFPCCONFIG                                                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCMinNumericValueDefines  TcpIp Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define TCPIP_MIN_CREATIONTIMESTAMPOFARPTABLEENTRY                                                  0u
#define TCPIP_MIN_STATUSOFARPTABLEENTRY                                                             0u
#define TCPIP_MIN_TIMESTAMPOFARPTABLEENTRY                                                          0u
#define TCPIP_MIN_ETHBUFIDXNEXTOFBUF2TXREQMAP                                                       0u
#define TCPIP_MIN_ETHBUFLENOFBUF2TXREQMAP                                                           0u
#define TCPIP_MIN_SOCKETDYNIDXOFBUF2TXREQMAP                                                        0u
#define TCPIP_MIN_ULTXREQIDXOFBUF2TXREQMAP                                                          0u
#define TCPIP_MIN_DHCPUSEROPTIONBUFFER                                                              0u
#define TCPIP_MIN_LENGTHOFDHCPUSEROPTIONDYN                                                         0u
#define TCPIP_MIN_NEXTTRANSMISSIONMSOFGRATUITOUSARP                                                 0u
#define TCPIP_MIN_TRANSMISSIONCNTOFGRATUITOUSARP                                                    0u
#define TCPIP_MIN_ACTIVEADDRASSIGNMENTMETHODOFIPV4CTRLDYN                                           0u
#define TCPIP_MIN_ADDRASSIGNMENTTRIGGEREDFLAGSOFIPV4CTRLDYN                                         0u
#define TCPIP_MIN_STATEOFIPV4CTRLDYN                                                                0u
#define TCPIP_MIN_ARPTABLEENTRYIDXOFIPV4SOCKETDYN                                                   0u
#define TCPIP_MIN_ETHIFFRAMEPRIOOFIPV4SOCKETDYN                                                     0u
#define TCPIP_MIN_FLAGSOFIPV4SOCKETDYN                                                              0u
#define TCPIP_MIN_IPV4CTRLIDXOFIPV4SOCKETDYN                                                        0u
#define TCPIP_MIN_PROTOCOLOFIPV4SOCKETDYN                                                           0u
#define TCPIP_MIN_TIMETOLIVEOFIPV4SOCKETDYN                                                         0u
#define TCPIP_MIN_TXDESCRIPTORPROTOCOLOFIPV4SOCKETDYN                                               0u
#define TCPIP_MIN_TYPEOFSERVICEOFIPV4SOCKETDYN                                                      0u
#define TCPIP_MIN_ADDRCONFLICTTIMEOUTOFLLADDRSTATE                                                  0u
#define TCPIP_MIN_ANNSTATEOFLLADDRSTATE                                                             0u
#define TCPIP_MIN_ANNOUNCENUMOFLLADDRSTATE                                                          0u
#define TCPIP_MIN_CONFLICTSNUMOFLLADDRSTATE                                                         0u
#define TCPIP_MIN_MSECCNTOFLLADDRSTATE                                                              0u
#define TCPIP_MIN_PROBENUMOFLLADDRSTATE                                                             0u
#define TCPIP_MIN_PROBENUMSINCECONFOFLLADDRSTATE                                                    0u
#define TCPIP_MIN_PROBESTATEOFLLADDRSTATE                                                           0u
#define TCPIP_MIN_STATEOFLLADDRSTATE                                                                0u
#define TCPIP_MIN_WAITUNTILTIMEOFLLADDRSTATE                                                        0u
#define TCPIP_MIN_ASSIGNMENTSTATEOFLOCALADDR                                                        0u
#define TCPIP_MIN_REASSEMBLYBUFFER                                                                  0u
#define TCPIP_MIN_LISTENACTIVECONNSTATOFSOCKETDYN                                                   0u
#define TCPIP_MIN_LOCALADDRBINDIDXOFSOCKETDYN                                                       0u
#define TCPIP_MIN_SOCKETOWNERCONFIGIDXOFSOCKETDYN                                                   0u
#define TCPIP_MIN_TXIPADDRIDXOFSOCKETDYN                                                            0u
#define TCPIP_MIN_TXREQELEMLISTIDXOFSOCKETUDPDYN                                                    0u
#define TCPIP_MIN_TXRETRQUEUEMAXNUMOFSOCKETUDPDYN                                                   0u
#define TCPIP_MIN_TXREQELEMDATALENBYTEOFTXREQELEM                                                   0u
#define TCPIP_MIN_FILLNUMOFTXREQELEMLISTDYN                                                         0u
#define TCPIP_MIN_READPOSOFTXREQELEMLISTDYN                                                         0u
#define TCPIP_MIN_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN                                                 0u
#define TCPIP_MIN_WRITEPOSOFTXREQELEMLISTDYN                                                        0u
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCMaxNumericValueDefines  TcpIp Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define TCPIP_MAX_CREATIONTIMESTAMPOFARPTABLEENTRY                                                  4294967295u
#define TCPIP_MAX_STATUSOFARPTABLEENTRY                                                             255u
#define TCPIP_MAX_TIMESTAMPOFARPTABLEENTRY                                                          4294967295u
#define TCPIP_MAX_ETHBUFIDXNEXTOFBUF2TXREQMAP                                                       255u
#define TCPIP_MAX_ETHBUFLENOFBUF2TXREQMAP                                                           65535u
#define TCPIP_MAX_SOCKETDYNIDXOFBUF2TXREQMAP                                                        255u
#define TCPIP_MAX_ULTXREQIDXOFBUF2TXREQMAP                                                          255u
#define TCPIP_MAX_DHCPUSEROPTIONBUFFER                                                              255u
#define TCPIP_MAX_LENGTHOFDHCPUSEROPTIONDYN                                                         65535u
#define TCPIP_MAX_NEXTTRANSMISSIONMSOFGRATUITOUSARP                                                 4294967295u
#define TCPIP_MAX_TRANSMISSIONCNTOFGRATUITOUSARP                                                    255u
#define TCPIP_MAX_ACTIVEADDRASSIGNMENTMETHODOFIPV4CTRLDYN                                           255u
#define TCPIP_MAX_ADDRASSIGNMENTTRIGGEREDFLAGSOFIPV4CTRLDYN                                         255u
#define TCPIP_MAX_STATEOFIPV4CTRLDYN                                                                255u
#define TCPIP_MAX_ARPTABLEENTRYIDXOFIPV4SOCKETDYN                                                   255u
#define TCPIP_MAX_ETHIFFRAMEPRIOOFIPV4SOCKETDYN                                                     255u
#define TCPIP_MAX_FLAGSOFIPV4SOCKETDYN                                                              255u
#define TCPIP_MAX_IPV4CTRLIDXOFIPV4SOCKETDYN                                                        255u
#define TCPIP_MAX_PROTOCOLOFIPV4SOCKETDYN                                                           255u
#define TCPIP_MAX_TIMETOLIVEOFIPV4SOCKETDYN                                                         255u
#define TCPIP_MAX_TXDESCRIPTORPROTOCOLOFIPV4SOCKETDYN                                               255u
#define TCPIP_MAX_TYPEOFSERVICEOFIPV4SOCKETDYN                                                      255u
#define TCPIP_MAX_ADDRCONFLICTTIMEOUTOFLLADDRSTATE                                                  65535u
#define TCPIP_MAX_ANNSTATEOFLLADDRSTATE                                                             255u
#define TCPIP_MAX_ANNOUNCENUMOFLLADDRSTATE                                                          255u
#define TCPIP_MAX_CONFLICTSNUMOFLLADDRSTATE                                                         255u
#define TCPIP_MAX_MSECCNTOFLLADDRSTATE                                                              4294967295u
#define TCPIP_MAX_PROBENUMOFLLADDRSTATE                                                             65535u
#define TCPIP_MAX_PROBENUMSINCECONFOFLLADDRSTATE                                                    255u
#define TCPIP_MAX_PROBESTATEOFLLADDRSTATE                                                           255u
#define TCPIP_MAX_STATEOFLLADDRSTATE                                                                255u
#define TCPIP_MAX_WAITUNTILTIMEOFLLADDRSTATE                                                        4294967295u
#define TCPIP_MAX_ASSIGNMENTSTATEOFLOCALADDR                                                        255u
#define TCPIP_MAX_REASSEMBLYBUFFER                                                                  255u
#define TCPIP_MAX_LISTENACTIVECONNSTATOFSOCKETDYN                                                   255u
#define TCPIP_MAX_LOCALADDRBINDIDXOFSOCKETDYN                                                       255u
#define TCPIP_MAX_SOCKETOWNERCONFIGIDXOFSOCKETDYN                                                   255u
#define TCPIP_MAX_TXIPADDRIDXOFSOCKETDYN                                                            255u
#define TCPIP_MAX_TXREQELEMLISTIDXOFSOCKETUDPDYN                                                    255u
#define TCPIP_MAX_TXRETRQUEUEMAXNUMOFSOCKETUDPDYN                                                   255u
#define TCPIP_MAX_TXREQELEMDATALENBYTEOFTXREQELEM                                                   65535u
#define TCPIP_MAX_FILLNUMOFTXREQELEMLISTDYN                                                         255u
#define TCPIP_MAX_READPOSOFTXREQELEMLISTDYN                                                         255u
#define TCPIP_MAX_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN                                                 255u
#define TCPIP_MAX_WRITEPOSOFTXREQELEMLISTDYN                                                        255u
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCNoReferenceDefines  TcpIp No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define TCPIP_NO_SOCKETDYNIDXOFBUF2TXREQMAP                                                         255u
#define TCPIP_NO_IPV4CTRLIDXOFETHIFCTRL                                                             255u
#define TCPIP_NO_REASSEMBLYBUFFERDESCENDIDXOFFRAGMENTATIONCONFIG                                    255u
#define TCPIP_NO_REASSEMBLYBUFFERDESCSTARTIDXOFFRAGMENTATIONCONFIG                                  255u
#define TCPIP_NO_ARPCONFIGIDXOFIPV4CTRL                                                             255u
#define TCPIP_NO_ARPTABLEENTRYENDIDXOFIPV4CTRL                                                      255u
#define TCPIP_NO_ARPTABLEENTRYSTARTIDXOFIPV4CTRL                                                    255u
#define TCPIP_NO_AUTOIPCONFIGIDXOFIPV4CTRL                                                          255u
#define TCPIP_NO_DHCPCONFIGIDXOFIPV4CTRL                                                            255u
#define TCPIP_NO_DHCPSTATUSIDXOFIPV4CTRL                                                            255u
#define TCPIP_NO_DHCPUSEROPTIONENDIDXOFIPV4CTRL                                                     255u
#define TCPIP_NO_DHCPUSEROPTIONSTARTIDXOFIPV4CTRL                                                   255u
#define TCPIP_NO_FRAGMENTATIONCONFIGIDXOFIPV4CTRL                                                   255u
#define TCPIP_NO_GRATUITOUSARPIDXOFIPV4CTRL                                                         255u
#define TCPIP_NO_LLADDRSTATEIDXOFIPV4CTRL                                                           255u
#define TCPIP_NO_MULTICASTADDRV4ENDIDXOFIPV4CTRL                                                    255u
#define TCPIP_NO_MULTICASTADDRV4STARTIDXOFIPV4CTRL                                                  255u
#define TCPIP_NO_STATICARPTABLEIDXOFIPV4CTRL                                                        255u
#define TCPIP_NO_IPV4CTRLDEFAULTIDXOFIPV4GENERAL                                                    255u
#define TCPIP_NO_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL                                                  255u
#define TCPIP_NO_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL                                                  255u
#define TCPIP_NO_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL                                                255u
#define TCPIP_NO_ARPTABLEENTRYIDXOFIPV4SOCKETDYN                                                    255u
#define TCPIP_NO_IPV4CTRLIDXOFIPV4SOCKETDYN                                                         255u
#define TCPIP_NO_MULTICASTADDRV4IDXOFLOCALADDRV4                                                    255u
#define TCPIP_NO_UNICASTADDRV4IDXOFLOCALADDRV4                                                      255u
#define TCPIP_NO_LOCALADDRBINDIDXOFSOCKETDYN                                                        255u
#define TCPIP_NO_SOCKETOWNERCONFIGIDXOFSOCKETDYN                                                    255u
#define TCPIP_NO_TXREQELEMLISTIDXOFSOCKETUDPDYN                                                     255u
#define TCPIP_NO_SOCKETUDPDYNIDXOFTXREQELEMLISTDYN                                                  255u
#define TCPIP_NO_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4                                             255u
#define TCPIP_NO_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4                                     255u
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCIsReducedToDefineDefines  TcpIp Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define TCPIP_ISDEF_ADDRASSIGNMENTCFGBYPRIO                                                         STD_OFF
#define TCPIP_ISDEF_ENTRYTIMEOUTOFARPCONFIG                                                         STD_OFF
#define TCPIP_ISDEF_NUMGRATUITOUSARPONSTARTUPOFARPCONFIG                                            STD_OFF
#define TCPIP_ISDEF_PACKETQUEUEENABLEDOFARPCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_REQUESTTIMEOUTOFARPCONFIG                                                       STD_OFF
#define TCPIP_ISDEF_RETRYINTERVALOFARPCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_RETRYTIMEOFARPCONFIG                                                            STD_OFF
#define TCPIP_ISDEF_TABLESIZEOFARPCONFIG                                                            STD_OFF
#define TCPIP_ISDEF_ADDRCALLOUTFUNCOFAUTOIPCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_ANNOUNCEINTERVALMSOFAUTOIPCONFIG                                                STD_OFF
#define TCPIP_ISDEF_ANNOUNCENUMOFAUTOIPCONFIG                                                       STD_OFF
#define TCPIP_ISDEF_ANNOUNCEWAITMSOFAUTOIPCONFIG                                                    STD_OFF
#define TCPIP_ISDEF_DEFENDINTERVALMSOFAUTOIPCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_MAXCONFLICTSOFAUTOIPCONFIG                                                      STD_OFF
#define TCPIP_ISDEF_PROBEMAXMSOFAUTOIPCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_PROBEMINMSOFAUTOIPCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_PROBENUMOFAUTOIPCONFIG                                                          STD_OFF
#define TCPIP_ISDEF_PROBEWAITMAXMSOFAUTOIPCONFIG                                                    STD_OFF
#define TCPIP_ISDEF_PROBEWAITMINMSOFAUTOIPCONFIG                                                    STD_OFF
#define TCPIP_ISDEF_RATELIMITINTERVALMSOFAUTOIPCONFIG                                               STD_OFF
#define TCPIP_ISDEF_NETADDROFDEFAULTMULTICASTADDRV4                                                 STD_OFF
#define TCPIP_ISDEF_DEFGWADDROFDEFAULTUNICASTADDRV4                                                 STD_OFF
#define TCPIP_ISDEF_NETADDROFDEFAULTUNICASTADDRV4                                                   STD_OFF
#define TCPIP_ISDEF_NETMASKOFDEFAULTUNICASTADDRV4                                                   STD_OFF
#define TCPIP_ISDEF_CODEOFDHCPUSEROPTION                                                            STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONBUFFERENDIDXOFDHCPUSEROPTION                                      STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONBUFFERLENGTHOFDHCPUSEROPTION                                      STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONBUFFERSTARTIDXOFDHCPUSEROPTION                                    STD_OFF
#define TCPIP_ISDEF_DIRECTIONOFDHCPUSEROPTION                                                       STD_OFF
#define TCPIP_ISDEF_IPV4CTRLIDXOFETHIFCTRL                                                          STD_OFF
#define TCPIP_ISDEF_IPV4CTRLUSEDOFETHIFCTRL                                                         STD_OFF
#define TCPIP_ISDEF_INORDERREASSEMBLYOFFRAGMENTATIONCONFIG                                          STD_OFF
#define TCPIP_ISDEF_MAXPACKETSIZEOFFRAGMENTATIONCONFIG                                              STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCENDIDXOFFRAGMENTATIONCONFIG                                 STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCLENGTHOFFRAGMENTATIONCONFIG                                 STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCSTARTIDXOFFRAGMENTATIONCONFIG                               STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCUSEDOFFRAGMENTATIONCONFIG                                   STD_OFF
#define TCPIP_ISDEF_REASSEMBLYTIMEOUTMSOFFRAGMENTATIONCONFIG                                        STD_OFF
#define TCPIP_ISDEF_ADDRASSIGNMENTCFGBYPRIOENDIDXOFIPV4CTRL                                         STD_OFF
#define TCPIP_ISDEF_ADDRASSIGNMENTCFGBYPRIOSTARTIDXOFIPV4CTRL                                       STD_OFF
#define TCPIP_ISDEF_ADDRASSIGNMENTPRIOBYTYPEOFIPV4CTRL                                              STD_OFF
#define TCPIP_ISDEF_ARPCONFIGIDXOFIPV4CTRL                                                          STD_OFF
#define TCPIP_ISDEF_ARPCONFIGUSEDOFIPV4CTRL                                                         STD_OFF
#define TCPIP_ISDEF_ARPTABLEENTRYENDIDXOFIPV4CTRL                                                   STD_OFF
#define TCPIP_ISDEF_ARPTABLEENTRYSTARTIDXOFIPV4CTRL                                                 STD_OFF
#define TCPIP_ISDEF_ARPTABLEENTRYUSEDOFIPV4CTRL                                                     STD_OFF
#define TCPIP_ISDEF_AUTOIPCONFIGIDXOFIPV4CTRL                                                       STD_OFF
#define TCPIP_ISDEF_AUTOIPCONFIGUSEDOFIPV4CTRL                                                      STD_OFF
#define TCPIP_ISDEF_BUF2TXREQMAPENDIDXOFIPV4CTRL                                                    STD_OFF
#define TCPIP_ISDEF_BUF2TXREQMAPSTARTIDXOFIPV4CTRL                                                  STD_OFF
#define TCPIP_ISDEF_DEFAULTTTLOFIPV4CTRL                                                            STD_OFF
#define TCPIP_ISDEF_DHCPCONFIGIDXOFIPV4CTRL                                                         STD_OFF
#define TCPIP_ISDEF_DHCPCONFIGUSEDOFIPV4CTRL                                                        STD_OFF
#define TCPIP_ISDEF_DHCPSTATUSIDXOFIPV4CTRL                                                         STD_OFF
#define TCPIP_ISDEF_DHCPSTATUSUSEDOFIPV4CTRL                                                        STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONENDIDXOFIPV4CTRL                                                  STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONSTARTIDXOFIPV4CTRL                                                STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONUSEDOFIPV4CTRL                                                    STD_OFF
#define TCPIP_ISDEF_ETHIFCTRLIDXOFIPV4CTRL                                                          STD_OFF
#define TCPIP_ISDEF_FRAGMENTATIONCONFIGIDXOFIPV4CTRL                                                STD_OFF
#define TCPIP_ISDEF_FRAGMENTATIONCONFIGUSEDOFIPV4CTRL                                               STD_OFF
#define TCPIP_ISDEF_FRAMEPRIODEFAULTOFIPV4CTRL                                                      STD_OFF
#define TCPIP_ISDEF_GRATUITOUSARPIDXOFIPV4CTRL                                                      STD_OFF
#define TCPIP_ISDEF_GRATUITOUSARPUSEDOFIPV4CTRL                                                     STD_OFF
#define TCPIP_ISDEF_HWCHECKSUMICMPOFIPV4CTRL                                                        STD_OFF
#define TCPIP_ISDEF_HWCHECKSUMIPOFIPV4CTRL                                                          STD_OFF
#define TCPIP_ISDEF_HWCHECKSUMTCPOFIPV4CTRL                                                         STD_OFF
#define TCPIP_ISDEF_HWCHECKSUMUDPOFIPV4CTRL                                                         STD_OFF
#define TCPIP_ISDEF_LLADDRSTATEIDXOFIPV4CTRL                                                        STD_OFF
#define TCPIP_ISDEF_LLADDRSTATEUSEDOFIPV4CTRL                                                       STD_OFF
#define TCPIP_ISDEF_LOCALADDRV4BROADCASTIDXOFIPV4CTRL                                               STD_OFF
#define TCPIP_ISDEF_LOCALADDRV4UNICASTIDXOFIPV4CTRL                                                 STD_OFF
#define TCPIP_ISDEF_MAXTXMSGSIZEOFIPV4CTRL                                                          STD_OFF
#define TCPIP_ISDEF_MTUTXOFIPV4CTRL                                                                 STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4ENDIDXOFIPV4CTRL                                                 STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4STARTIDXOFIPV4CTRL                                               STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4USEDOFIPV4CTRL                                                   STD_OFF
#define TCPIP_ISDEF_RECEIVEALLMULTICASTSOFIPV4CTRL                                                  STD_OFF
#define TCPIP_ISDEF_STATICARPTABLEIDXOFIPV4CTRL                                                     STD_OFF
#define TCPIP_ISDEF_STATICARPTABLEUSEDOFIPV4CTRL                                                    STD_OFF
#define TCPIP_ISDEF_TYPEOFSERVICEDEFAULTOFIPV4CTRL                                                  STD_OFF
#define TCPIP_ISDEF_UNICASTADDRV4IDXOFIPV4CTRL                                                      STD_OFF
#define TCPIP_ISDEF_IPV4CTRLDEFAULTIDXOFIPV4GENERAL                                                 STD_OFF
#define TCPIP_ISDEF_IPV4CTRLDEFAULTUSEDOFIPV4GENERAL                                                STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL                                               STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNDHCPUSEDOFIPV4GENERAL                                              STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL                                               STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNICMPUSEDOFIPV4GENERAL                                              STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL                                             STD_OFF
#define TCPIP_ISDEF_IPV4SOCKETDYNTCPRSTUSEDOFIPV4GENERAL                                            STD_OFF
#define TCPIP_ISDEF_IPV4CTRLIDXOFLOCALADDRV4                                                        STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4IDXOFLOCALADDRV4                                                 STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4USEDOFLOCALADDRV4                                                STD_OFF
#define TCPIP_ISDEF_UNICASTADDRV4IDXOFLOCALADDRV4                                                   STD_OFF
#define TCPIP_ISDEF_UNICASTADDRV4USEDOFLOCALADDRV4                                                  STD_OFF
#define TCPIP_ISDEF_DEFAULTMULTICASTADDRV4IDXOFMULTICASTADDRV4                                      STD_OFF
#define TCPIP_ISDEF_LOCALADDRV4IDXOFMULTICASTADDRV4                                                 STD_OFF
#define TCPIP_ISDEF_CHGDISCARDEDFUNCPTROFPHYSADDRCONFIG                                             STD_OFF
#define TCPIP_ISDEF_CHGFUNCPTROFPHYSADDRCONFIG                                                      STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERENDIDXOFREASSEMBLYBUFFERDESC                                    STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERSTARTIDXOFREASSEMBLYBUFFERDESC                                  STD_OFF
#define TCPIP_ISDEF_COPYTXDATADYNFUNCPTROFSOCKETOWNERCONFIG                                         STD_OFF
#define TCPIP_ISDEF_COPYTXDATAFUNCPTROFSOCKETOWNERCONFIG                                            STD_OFF
#define TCPIP_ISDEF_DHCPEVENTFUNCPTROFSOCKETOWNERCONFIG                                             STD_OFF
#define TCPIP_ISDEF_LOCALIPADDRASSIGNMENTCHGFUNCPTROFSOCKETOWNERCONFIG                              STD_OFF
#define TCPIP_ISDEF_RXINDICATIONFUNCPTROFSOCKETOWNERCONFIG                                          STD_OFF
#define TCPIP_ISDEF_TCPACCEPTEDFUNCPTROFSOCKETOWNERCONFIG                                           STD_OFF
#define TCPIP_ISDEF_TCPCONNECTEDFUNCPTROFSOCKETOWNERCONFIG                                          STD_OFF
#define TCPIP_ISDEF_TCPIPEVENTFUNCPTROFSOCKETOWNERCONFIG                                            STD_OFF
#define TCPIP_ISDEF_TLSVALIDATIONRESULTFUNCPTROFSOCKETOWNERCONFIG                                   STD_OFF
#define TCPIP_ISDEF_TXCONFIRMATIONFUNCPTROFSOCKETOWNERCONFIG                                        STD_OFF
#define TCPIP_ISDEF_IPADDROFSTATICARPENTRY                                                          STD_OFF
#define TCPIP_ISDEF_PHYSADDROFSTATICARPENTRY                                                        STD_OFF
#define TCPIP_ISDEF_STATICARPENTRYENDIDXOFSTATICARPTABLE                                            STD_OFF
#define TCPIP_ISDEF_STATICARPENTRYSTARTIDXOFSTATICARPTABLE                                          STD_OFF
#define TCPIP_ISDEF_TXREQELEMENDIDXOFTXREQELEMLIST                                                  STD_OFF
#define TCPIP_ISDEF_TXREQELEMLENGTHOFTXREQELEMLIST                                                  STD_OFF
#define TCPIP_ISDEF_TXREQELEMSTARTIDXOFTXREQELEMLIST                                                STD_OFF
#define TCPIP_ISDEF_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4                                          STD_OFF
#define TCPIP_ISDEF_DEFAULTUNICASTADDRV4USEDOFUNICASTADDRV4                                         STD_OFF
#define TCPIP_ISDEF_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4                                  STD_OFF
#define TCPIP_ISDEF_STATICUNICASTADDRV4REQUESTEDUSEDOFUNICASTADDRV4                                 STD_OFF
#define TCPIP_ISDEF_ADDRASSIGNMENTCFGBYPRIOOFPCCONFIG                                               STD_ON
#define TCPIP_ISDEF_ARPCONFIGOFPCCONFIG                                                             STD_OFF
#define TCPIP_ISDEF_ARPTABLEENTRYOFPCCONFIG                                                         STD_OFF
#define TCPIP_ISDEF_AUTOIPCONFIGOFPCCONFIG                                                          STD_OFF
#define TCPIP_ISDEF_BUF2TXREQMAPOFPCCONFIG                                                          STD_ON
#define TCPIP_ISDEF_DEFAULTMULTICASTADDRV4OFPCCONFIG                                                STD_OFF
#define TCPIP_ISDEF_DEFAULTUNICASTADDRV4OFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONBUFFEROFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONDYNOFPCCONFIG                                                     STD_OFF
#define TCPIP_ISDEF_DHCPUSEROPTIONOFPCCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_DUPLICATEADDRDETECTIONFCTPTROFPCCONFIG                                          STD_ON
#define TCPIP_ISDEF_ETHIFCTRLOFPCCONFIG                                                             STD_ON
#define TCPIP_ISDEF_FRAGMENTATIONCONFIGOFPCCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_GRATUITOUSARPOFPCCONFIG                                                         STD_OFF
#define TCPIP_ISDEF_ICMPMSGHANDLERCBKFCTPTROFPCCONFIG                                               STD_ON
#define TCPIP_ISDEF_IPV4CTRLDYNOFPCCONFIG                                                           STD_ON
#define TCPIP_ISDEF_IPV4CTRLOFPCCONFIG                                                              STD_ON
#define TCPIP_ISDEF_IPV4GENERALOFPCCONFIG                                                           STD_ON
#define TCPIP_ISDEF_IPV4SOCKETDYNOFPCCONFIG                                                         STD_ON
#define TCPIP_ISDEF_LLADDRSTATEOFPCCONFIG                                                           STD_OFF
#define TCPIP_ISDEF_LOCALADDROFPCCONFIG                                                             STD_ON
#define TCPIP_ISDEF_LOCALADDRV4OFPCCONFIG                                                           STD_ON
#define TCPIP_ISDEF_MULTICASTADDRV4OFPCCONFIG                                                       STD_OFF
#define TCPIP_ISDEF_MULTICASTADDRV4REQUESTEDOFPCCONFIG                                              STD_OFF
#define TCPIP_ISDEF_PHYSADDRCONFIGOFPCCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_RANDOMNUMBERFCTPTROFPCCONFIG                                                    STD_ON
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCDYNOFPCCONFIG                                               STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFERDESCOFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_REASSEMBLYBUFFEROFPCCONFIG                                                      STD_OFF
#define TCPIP_ISDEF_SIZEOFARPCONFIGOFPCCONFIG                                                       STD_OFF
#define TCPIP_ISDEF_SIZEOFARPTABLEENTRYOFPCCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_SIZEOFAUTOIPCONFIGOFPCCONFIG                                                    STD_OFF
#define TCPIP_ISDEF_SIZEOFDEFAULTMULTICASTADDRV4OFPCCONFIG                                          STD_OFF
#define TCPIP_ISDEF_SIZEOFDEFAULTUNICASTADDRV4OFPCCONFIG                                            STD_OFF
#define TCPIP_ISDEF_SIZEOFDHCPUSEROPTIONBUFFEROFPCCONFIG                                            STD_OFF
#define TCPIP_ISDEF_SIZEOFDHCPUSEROPTIONOFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_SIZEOFFRAGMENTATIONCONFIGOFPCCONFIG                                             STD_OFF
#define TCPIP_ISDEF_SIZEOFGRATUITOUSARPOFPCCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_SIZEOFLLADDRSTATEOFPCCONFIG                                                     STD_OFF
#define TCPIP_ISDEF_SIZEOFMULTICASTADDRV4OFPCCONFIG                                                 STD_OFF
#define TCPIP_ISDEF_SIZEOFPHYSADDRCONFIGOFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_SIZEOFREASSEMBLYBUFFERDESCOFPCCONFIG                                            STD_OFF
#define TCPIP_ISDEF_SIZEOFREASSEMBLYBUFFEROFPCCONFIG                                                STD_OFF
#define TCPIP_ISDEF_SIZEOFSTATICARPENTRYOFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_SIZEOFSTATICARPTABLEOFPCCONFIG                                                  STD_OFF
#define TCPIP_ISDEF_SIZEOFSTATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                    STD_OFF
#define TCPIP_ISDEF_SIZEOFTXREQELEMLISTOFPCCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_SIZEOFTXREQELEMOFPCCONFIG                                                       STD_OFF
#define TCPIP_ISDEF_SIZEOFUDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                     STD_OFF
#define TCPIP_ISDEF_SIZEOFUDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                         STD_OFF
#define TCPIP_ISDEF_SIZEOFUDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                         STD_OFF
#define TCPIP_ISDEF_SIZEOFUNICASTADDRV4OFPCCONFIG                                                   STD_OFF
#define TCPIP_ISDEF_SOCKETDYNOFPCCONFIG                                                             STD_ON
#define TCPIP_ISDEF_SOCKETOWNERCONFIGOFPCCONFIG                                                     STD_ON
#define TCPIP_ISDEF_SOCKETUDPDYNOFPCCONFIG                                                          STD_ON
#define TCPIP_ISDEF_STATICARPENTRYOFPCCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_STATICARPTABLEOFPCCONFIG                                                        STD_OFF
#define TCPIP_ISDEF_STATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                          STD_OFF
#define TCPIP_ISDEF_TXREQELEMLISTDYNOFPCCONFIG                                                      STD_OFF
#define TCPIP_ISDEF_TXREQELEMLISTOFPCCONFIG                                                         STD_OFF
#define TCPIP_ISDEF_TXREQELEMOFPCCONFIG                                                             STD_OFF
#define TCPIP_ISDEF_UDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                           STD_OFF
#define TCPIP_ISDEF_UDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                               STD_OFF
#define TCPIP_ISDEF_UDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                               STD_OFF
#define TCPIP_ISDEF_UNICASTADDRV4OFPCCONFIG                                                         STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCEqualsAlwaysToDefines  TcpIp Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define TCPIP_EQ2_ADDRASSIGNMENTCFGBYPRIO                                                           
#define TCPIP_EQ2_ENTRYTIMEOUTOFARPCONFIG                                                           
#define TCPIP_EQ2_NUMGRATUITOUSARPONSTARTUPOFARPCONFIG                                              
#define TCPIP_EQ2_PACKETQUEUEENABLEDOFARPCONFIG                                                     
#define TCPIP_EQ2_REQUESTTIMEOUTOFARPCONFIG                                                         
#define TCPIP_EQ2_RETRYINTERVALOFARPCONFIG                                                          
#define TCPIP_EQ2_RETRYTIMEOFARPCONFIG                                                              
#define TCPIP_EQ2_TABLESIZEOFARPCONFIG                                                              
#define TCPIP_EQ2_ADDRCALLOUTFUNCOFAUTOIPCONFIG                                                     
#define TCPIP_EQ2_ANNOUNCEINTERVALMSOFAUTOIPCONFIG                                                  
#define TCPIP_EQ2_ANNOUNCENUMOFAUTOIPCONFIG                                                         
#define TCPIP_EQ2_ANNOUNCEWAITMSOFAUTOIPCONFIG                                                      
#define TCPIP_EQ2_DEFENDINTERVALMSOFAUTOIPCONFIG                                                    
#define TCPIP_EQ2_MAXCONFLICTSOFAUTOIPCONFIG                                                        
#define TCPIP_EQ2_PROBEMAXMSOFAUTOIPCONFIG                                                          
#define TCPIP_EQ2_PROBEMINMSOFAUTOIPCONFIG                                                          
#define TCPIP_EQ2_PROBENUMOFAUTOIPCONFIG                                                            
#define TCPIP_EQ2_PROBEWAITMAXMSOFAUTOIPCONFIG                                                      
#define TCPIP_EQ2_PROBEWAITMINMSOFAUTOIPCONFIG                                                      
#define TCPIP_EQ2_RATELIMITINTERVALMSOFAUTOIPCONFIG                                                 
#define TCPIP_EQ2_NETADDROFDEFAULTMULTICASTADDRV4                                                   
#define TCPIP_EQ2_DEFGWADDROFDEFAULTUNICASTADDRV4                                                   
#define TCPIP_EQ2_NETADDROFDEFAULTUNICASTADDRV4                                                     
#define TCPIP_EQ2_NETMASKOFDEFAULTUNICASTADDRV4                                                     
#define TCPIP_EQ2_CODEOFDHCPUSEROPTION                                                              
#define TCPIP_EQ2_DHCPUSEROPTIONBUFFERENDIDXOFDHCPUSEROPTION                                        
#define TCPIP_EQ2_DHCPUSEROPTIONBUFFERLENGTHOFDHCPUSEROPTION                                        
#define TCPIP_EQ2_DHCPUSEROPTIONBUFFERSTARTIDXOFDHCPUSEROPTION                                      
#define TCPIP_EQ2_DIRECTIONOFDHCPUSEROPTION                                                         
#define TCPIP_EQ2_IPV4CTRLIDXOFETHIFCTRL                                                            
#define TCPIP_EQ2_IPV4CTRLUSEDOFETHIFCTRL                                                           
#define TCPIP_EQ2_INORDERREASSEMBLYOFFRAGMENTATIONCONFIG                                            
#define TCPIP_EQ2_MAXPACKETSIZEOFFRAGMENTATIONCONFIG                                                
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCENDIDXOFFRAGMENTATIONCONFIG                                   
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCLENGTHOFFRAGMENTATIONCONFIG                                   
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCSTARTIDXOFFRAGMENTATIONCONFIG                                 
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCUSEDOFFRAGMENTATIONCONFIG                                     
#define TCPIP_EQ2_REASSEMBLYTIMEOUTMSOFFRAGMENTATIONCONFIG                                          
#define TCPIP_EQ2_ADDRASSIGNMENTCFGBYPRIOENDIDXOFIPV4CTRL                                           
#define TCPIP_EQ2_ADDRASSIGNMENTCFGBYPRIOSTARTIDXOFIPV4CTRL                                         
#define TCPIP_EQ2_ADDRASSIGNMENTPRIOBYTYPEOFIPV4CTRL                                                
#define TCPIP_EQ2_ARPCONFIGIDXOFIPV4CTRL                                                            
#define TCPIP_EQ2_ARPCONFIGUSEDOFIPV4CTRL                                                           
#define TCPIP_EQ2_ARPTABLEENTRYENDIDXOFIPV4CTRL                                                     
#define TCPIP_EQ2_ARPTABLEENTRYSTARTIDXOFIPV4CTRL                                                   
#define TCPIP_EQ2_ARPTABLEENTRYUSEDOFIPV4CTRL                                                       
#define TCPIP_EQ2_AUTOIPCONFIGIDXOFIPV4CTRL                                                         
#define TCPIP_EQ2_AUTOIPCONFIGUSEDOFIPV4CTRL                                                        
#define TCPIP_EQ2_BUF2TXREQMAPENDIDXOFIPV4CTRL                                                      
#define TCPIP_EQ2_BUF2TXREQMAPSTARTIDXOFIPV4CTRL                                                    
#define TCPIP_EQ2_DEFAULTTTLOFIPV4CTRL                                                              
#define TCPIP_EQ2_DHCPCONFIGIDXOFIPV4CTRL                                                           
#define TCPIP_EQ2_DHCPCONFIGUSEDOFIPV4CTRL                                                          
#define TCPIP_EQ2_DHCPSTATUSIDXOFIPV4CTRL                                                           
#define TCPIP_EQ2_DHCPSTATUSUSEDOFIPV4CTRL                                                          
#define TCPIP_EQ2_DHCPUSEROPTIONENDIDXOFIPV4CTRL                                                    
#define TCPIP_EQ2_DHCPUSEROPTIONSTARTIDXOFIPV4CTRL                                                  
#define TCPIP_EQ2_DHCPUSEROPTIONUSEDOFIPV4CTRL                                                      
#define TCPIP_EQ2_ETHIFCTRLIDXOFIPV4CTRL                                                            
#define TCPIP_EQ2_FRAGMENTATIONCONFIGIDXOFIPV4CTRL                                                  
#define TCPIP_EQ2_FRAGMENTATIONCONFIGUSEDOFIPV4CTRL                                                 
#define TCPIP_EQ2_FRAMEPRIODEFAULTOFIPV4CTRL                                                        
#define TCPIP_EQ2_GRATUITOUSARPIDXOFIPV4CTRL                                                        
#define TCPIP_EQ2_GRATUITOUSARPUSEDOFIPV4CTRL                                                       
#define TCPIP_EQ2_HWCHECKSUMICMPOFIPV4CTRL                                                          
#define TCPIP_EQ2_HWCHECKSUMIPOFIPV4CTRL                                                            
#define TCPIP_EQ2_HWCHECKSUMTCPOFIPV4CTRL                                                           
#define TCPIP_EQ2_HWCHECKSUMUDPOFIPV4CTRL                                                           
#define TCPIP_EQ2_LLADDRSTATEIDXOFIPV4CTRL                                                          
#define TCPIP_EQ2_LLADDRSTATEUSEDOFIPV4CTRL                                                         
#define TCPIP_EQ2_LOCALADDRV4BROADCASTIDXOFIPV4CTRL                                                 
#define TCPIP_EQ2_LOCALADDRV4UNICASTIDXOFIPV4CTRL                                                   
#define TCPIP_EQ2_MAXTXMSGSIZEOFIPV4CTRL                                                            
#define TCPIP_EQ2_MTUTXOFIPV4CTRL                                                                   
#define TCPIP_EQ2_MULTICASTADDRV4ENDIDXOFIPV4CTRL                                                   
#define TCPIP_EQ2_MULTICASTADDRV4STARTIDXOFIPV4CTRL                                                 
#define TCPIP_EQ2_MULTICASTADDRV4USEDOFIPV4CTRL                                                     
#define TCPIP_EQ2_RECEIVEALLMULTICASTSOFIPV4CTRL                                                    
#define TCPIP_EQ2_STATICARPTABLEIDXOFIPV4CTRL                                                       
#define TCPIP_EQ2_STATICARPTABLEUSEDOFIPV4CTRL                                                      
#define TCPIP_EQ2_TYPEOFSERVICEDEFAULTOFIPV4CTRL                                                    
#define TCPIP_EQ2_UNICASTADDRV4IDXOFIPV4CTRL                                                        
#define TCPIP_EQ2_IPV4CTRLDEFAULTIDXOFIPV4GENERAL                                                   
#define TCPIP_EQ2_IPV4CTRLDEFAULTUSEDOFIPV4GENERAL                                                  
#define TCPIP_EQ2_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL                                                 
#define TCPIP_EQ2_IPV4SOCKETDYNDHCPUSEDOFIPV4GENERAL                                                
#define TCPIP_EQ2_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL                                                 
#define TCPIP_EQ2_IPV4SOCKETDYNICMPUSEDOFIPV4GENERAL                                                
#define TCPIP_EQ2_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL                                               
#define TCPIP_EQ2_IPV4SOCKETDYNTCPRSTUSEDOFIPV4GENERAL                                              
#define TCPIP_EQ2_IPV4CTRLIDXOFLOCALADDRV4                                                          
#define TCPIP_EQ2_MULTICASTADDRV4IDXOFLOCALADDRV4                                                   
#define TCPIP_EQ2_MULTICASTADDRV4USEDOFLOCALADDRV4                                                  
#define TCPIP_EQ2_UNICASTADDRV4IDXOFLOCALADDRV4                                                     
#define TCPIP_EQ2_UNICASTADDRV4USEDOFLOCALADDRV4                                                    
#define TCPIP_EQ2_DEFAULTMULTICASTADDRV4IDXOFMULTICASTADDRV4                                        
#define TCPIP_EQ2_LOCALADDRV4IDXOFMULTICASTADDRV4                                                   
#define TCPIP_EQ2_CHGDISCARDEDFUNCPTROFPHYSADDRCONFIG                                               
#define TCPIP_EQ2_CHGFUNCPTROFPHYSADDRCONFIG                                                        
#define TCPIP_EQ2_REASSEMBLYBUFFERENDIDXOFREASSEMBLYBUFFERDESC                                      
#define TCPIP_EQ2_REASSEMBLYBUFFERSTARTIDXOFREASSEMBLYBUFFERDESC                                    
#define TCPIP_EQ2_COPYTXDATADYNFUNCPTROFSOCKETOWNERCONFIG                                           
#define TCPIP_EQ2_COPYTXDATAFUNCPTROFSOCKETOWNERCONFIG                                              
#define TCPIP_EQ2_DHCPEVENTFUNCPTROFSOCKETOWNERCONFIG                                               
#define TCPIP_EQ2_LOCALIPADDRASSIGNMENTCHGFUNCPTROFSOCKETOWNERCONFIG                                
#define TCPIP_EQ2_RXINDICATIONFUNCPTROFSOCKETOWNERCONFIG                                            
#define TCPIP_EQ2_TCPACCEPTEDFUNCPTROFSOCKETOWNERCONFIG                                             
#define TCPIP_EQ2_TCPCONNECTEDFUNCPTROFSOCKETOWNERCONFIG                                            
#define TCPIP_EQ2_TCPIPEVENTFUNCPTROFSOCKETOWNERCONFIG                                              
#define TCPIP_EQ2_TLSVALIDATIONRESULTFUNCPTROFSOCKETOWNERCONFIG                                     
#define TCPIP_EQ2_TXCONFIRMATIONFUNCPTROFSOCKETOWNERCONFIG                                          
#define TCPIP_EQ2_IPADDROFSTATICARPENTRY                                                            
#define TCPIP_EQ2_PHYSADDROFSTATICARPENTRY                                                          
#define TCPIP_EQ2_STATICARPENTRYENDIDXOFSTATICARPTABLE                                              
#define TCPIP_EQ2_STATICARPENTRYSTARTIDXOFSTATICARPTABLE                                            
#define TCPIP_EQ2_TXREQELEMENDIDXOFTXREQELEMLIST                                                    
#define TCPIP_EQ2_TXREQELEMLENGTHOFTXREQELEMLIST                                                    
#define TCPIP_EQ2_TXREQELEMSTARTIDXOFTXREQELEMLIST                                                  
#define TCPIP_EQ2_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4                                            
#define TCPIP_EQ2_DEFAULTUNICASTADDRV4USEDOFUNICASTADDRV4                                           
#define TCPIP_EQ2_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4                                    
#define TCPIP_EQ2_STATICUNICASTADDRV4REQUESTEDUSEDOFUNICASTADDRV4                                   
#define TCPIP_EQ2_ADDRASSIGNMENTCFGBYPRIOOFPCCONFIG                                                 TcpIp_AddrAssignmentCfgByPrio
#define TCPIP_EQ2_ARPCONFIGOFPCCONFIG                                                               
#define TCPIP_EQ2_ARPTABLEENTRYOFPCCONFIG                                                           
#define TCPIP_EQ2_AUTOIPCONFIGOFPCCONFIG                                                            
#define TCPIP_EQ2_BUF2TXREQMAPOFPCCONFIG                                                            TcpIp_Buf2TxReqMap.raw
#define TCPIP_EQ2_DEFAULTMULTICASTADDRV4OFPCCONFIG                                                  
#define TCPIP_EQ2_DEFAULTUNICASTADDRV4OFPCCONFIG                                                    
#define TCPIP_EQ2_DHCPUSEROPTIONBUFFEROFPCCONFIG                                                    
#define TCPIP_EQ2_DHCPUSEROPTIONDYNOFPCCONFIG                                                       
#define TCPIP_EQ2_DHCPUSEROPTIONOFPCCONFIG                                                          
#define TCPIP_EQ2_DUPLICATEADDRDETECTIONFCTPTROFPCCONFIG                                            (&(TcpIp_DuplicateAddrDetectionFctPtr))
#define TCPIP_EQ2_ETHIFCTRLOFPCCONFIG                                                               TcpIp_EthIfCtrl
#define TCPIP_EQ2_FRAGMENTATIONCONFIGOFPCCONFIG                                                     
#define TCPIP_EQ2_GRATUITOUSARPOFPCCONFIG                                                           
#define TCPIP_EQ2_ICMPMSGHANDLERCBKFCTPTROFPCCONFIG                                                 (&(TcpIp_IcmpMsgHandlerCbkFctPtr))
#define TCPIP_EQ2_IPV4CTRLDYNOFPCCONFIG                                                             TcpIp_IpV4CtrlDyn.raw
#define TCPIP_EQ2_IPV4CTRLOFPCCONFIG                                                                TcpIp_IpV4Ctrl
#define TCPIP_EQ2_IPV4GENERALOFPCCONFIG                                                             TcpIp_IpV4General
#define TCPIP_EQ2_IPV4SOCKETDYNOFPCCONFIG                                                           TcpIp_IpV4SocketDyn.raw
#define TCPIP_EQ2_LLADDRSTATEOFPCCONFIG                                                             
#define TCPIP_EQ2_LOCALADDROFPCCONFIG                                                               TcpIp_LocalAddr.raw
#define TCPIP_EQ2_LOCALADDRV4OFPCCONFIG                                                             TcpIp_LocalAddrV4
#define TCPIP_EQ2_MULTICASTADDRV4OFPCCONFIG                                                         
#define TCPIP_EQ2_MULTICASTADDRV4REQUESTEDOFPCCONFIG                                                
#define TCPIP_EQ2_PHYSADDRCONFIGOFPCCONFIG                                                          
#define TCPIP_EQ2_RANDOMNUMBERFCTPTROFPCCONFIG                                                      (&(TcpIp_RandomNumberFctPtr))
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCDYNOFPCCONFIG                                                 
#define TCPIP_EQ2_REASSEMBLYBUFFERDESCOFPCCONFIG                                                    
#define TCPIP_EQ2_REASSEMBLYBUFFEROFPCCONFIG                                                        
#define TCPIP_EQ2_SIZEOFARPCONFIGOFPCCONFIG                                                         
#define TCPIP_EQ2_SIZEOFARPTABLEENTRYOFPCCONFIG                                                     
#define TCPIP_EQ2_SIZEOFAUTOIPCONFIGOFPCCONFIG                                                      
#define TCPIP_EQ2_SIZEOFDEFAULTMULTICASTADDRV4OFPCCONFIG                                            
#define TCPIP_EQ2_SIZEOFDEFAULTUNICASTADDRV4OFPCCONFIG                                              
#define TCPIP_EQ2_SIZEOFDHCPUSEROPTIONBUFFEROFPCCONFIG                                              
#define TCPIP_EQ2_SIZEOFDHCPUSEROPTIONOFPCCONFIG                                                    
#define TCPIP_EQ2_SIZEOFFRAGMENTATIONCONFIGOFPCCONFIG                                               
#define TCPIP_EQ2_SIZEOFGRATUITOUSARPOFPCCONFIG                                                     
#define TCPIP_EQ2_SIZEOFLLADDRSTATEOFPCCONFIG                                                       
#define TCPIP_EQ2_SIZEOFMULTICASTADDRV4OFPCCONFIG                                                   
#define TCPIP_EQ2_SIZEOFPHYSADDRCONFIGOFPCCONFIG                                                    
#define TCPIP_EQ2_SIZEOFREASSEMBLYBUFFERDESCOFPCCONFIG                                              
#define TCPIP_EQ2_SIZEOFREASSEMBLYBUFFEROFPCCONFIG                                                  
#define TCPIP_EQ2_SIZEOFSTATICARPENTRYOFPCCONFIG                                                    
#define TCPIP_EQ2_SIZEOFSTATICARPTABLEOFPCCONFIG                                                    
#define TCPIP_EQ2_SIZEOFSTATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                      
#define TCPIP_EQ2_SIZEOFTXREQELEMLISTOFPCCONFIG                                                     
#define TCPIP_EQ2_SIZEOFTXREQELEMOFPCCONFIG                                                         
#define TCPIP_EQ2_SIZEOFUDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                       
#define TCPIP_EQ2_SIZEOFUDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                           
#define TCPIP_EQ2_SIZEOFUDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                           
#define TCPIP_EQ2_SIZEOFUNICASTADDRV4OFPCCONFIG                                                     
#define TCPIP_EQ2_SOCKETDYNOFPCCONFIG                                                               TcpIp_SocketDyn.raw
#define TCPIP_EQ2_SOCKETOWNERCONFIGOFPCCONFIG                                                       TcpIp_SocketOwnerConfig
#define TCPIP_EQ2_SOCKETUDPDYNOFPCCONFIG                                                            TcpIp_SocketUdpDyn
#define TCPIP_EQ2_STATICARPENTRYOFPCCONFIG                                                          
#define TCPIP_EQ2_STATICARPTABLEOFPCCONFIG                                                          
#define TCPIP_EQ2_STATICUNICASTADDRV4REQUESTEDOFPCCONFIG                                            
#define TCPIP_EQ2_TXREQELEMLISTDYNOFPCCONFIG                                                        
#define TCPIP_EQ2_TXREQELEMLISTOFPCCONFIG                                                           
#define TCPIP_EQ2_TXREQELEMOFPCCONFIG                                                               
#define TCPIP_EQ2_UDPTXRETRYQUEUEELEMENTCHAINOFPCCONFIG                                             
#define TCPIP_EQ2_UDPTXRETRYQUEUEELEMENTSOFPCCONFIG                                                 
#define TCPIP_EQ2_UDPTXRETRYQUEUEPOOLDESCOFPCCONFIG                                                 
#define TCPIP_EQ2_UNICASTADDRV4OFPCCONFIG                                                           
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCSymbolicInitializationPointers  TcpIp Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define TcpIp_Config_Ptr                                                                            &(TcpIp_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'TcpIp' */
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCInitializationSymbols  TcpIp Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define TcpIp_Config                                                                                TcpIp_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'TcpIp */
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCGeneral  TcpIp General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define TCPIP_CHECK_INIT_POINTER                                                                    STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define TCPIP_FINAL_MAGIC_NUMBER                                                                    0xAA1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of TcpIp */
#define TCPIP_INDIVIDUAL_POSTBUILD                                                                  STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'TcpIp' is not configured to be postbuild capable. */
#define TCPIP_INIT_DATA                                                                             TCPIP_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define TCPIP_INIT_DATA_HASH_CODE                                                                   557150583  /**< the precompile constant to validate the initialization structure at initialization time of TcpIp with a hashcode. The seed value is '0xAA1Eu' */
#define TCPIP_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define TCPIP_USE_INIT_POINTER                                                                      STD_ON  /**< STD_ON if the init pointer TcpIp shall be used. */
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
  \defgroup  TcpIpPCGetRootDataMacros  TcpIp Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define TcpIp_GetArpConfigOfPCConfig()                                                              TcpIp_ConfigDataPtr->ArpConfigOfPCConfig
#define TcpIp_GetArpTableEntryOfPCConfig()                                                          TcpIp_ConfigDataPtr->ArpTableEntryOfPCConfig
#define TcpIp_GetAutoIpConfigOfPCConfig()                                                           TcpIp_ConfigDataPtr->AutoIpConfigOfPCConfig
#define TcpIp_GetDefaultMulticastAddrV4OfPCConfig()                                                 TcpIp_ConfigDataPtr->DefaultMulticastAddrV4OfPCConfig
#define TcpIp_GetDefaultUnicastAddrV4OfPCConfig()                                                   TcpIp_ConfigDataPtr->DefaultUnicastAddrV4OfPCConfig
#define TcpIp_GetDhcpUserOptionBufferOfPCConfig()                                                   TcpIp_ConfigDataPtr->DhcpUserOptionBufferOfPCConfig
#define TcpIp_GetDhcpUserOptionDynOfPCConfig()                                                      TcpIp_ConfigDataPtr->DhcpUserOptionDynOfPCConfig
#define TcpIp_GetDhcpUserOptionOfPCConfig()                                                         TcpIp_ConfigDataPtr->DhcpUserOptionOfPCConfig
#define TcpIp_GetFragmentationConfigOfPCConfig()                                                    TcpIp_ConfigDataPtr->FragmentationConfigOfPCConfig
#define TcpIp_GetGratuitousArpOfPCConfig()                                                          TcpIp_ConfigDataPtr->GratuitousArpOfPCConfig
#define TcpIp_GetLlAddrStateOfPCConfig()                                                            TcpIp_ConfigDataPtr->LlAddrStateOfPCConfig
#define TcpIp_GetMulticastAddrV4OfPCConfig()                                                        TcpIp_ConfigDataPtr->MulticastAddrV4OfPCConfig
#define TcpIp_GetMulticastAddrV4RequestedOfPCConfig()                                               TcpIp_ConfigDataPtr->MulticastAddrV4RequestedOfPCConfig
#define TcpIp_GetPhysAddrConfigOfPCConfig()                                                         TcpIp_ConfigDataPtr->PhysAddrConfigOfPCConfig
#define TcpIp_GetReassemblyBufferDescDynOfPCConfig()                                                TcpIp_ConfigDataPtr->ReassemblyBufferDescDynOfPCConfig
#define TcpIp_GetReassemblyBufferDescOfPCConfig()                                                   TcpIp_ConfigDataPtr->ReassemblyBufferDescOfPCConfig
#define TcpIp_GetReassemblyBufferOfPCConfig()                                                       TcpIp_ConfigDataPtr->ReassemblyBufferOfPCConfig
#define TcpIp_GetSizeOfArpConfigOfPCConfig()                                                        TcpIp_ConfigDataPtr->SizeOfArpConfigOfPCConfig
#define TcpIp_GetSizeOfArpTableEntryOfPCConfig()                                                    TcpIp_ConfigDataPtr->SizeOfArpTableEntryOfPCConfig
#define TcpIp_GetSizeOfAutoIpConfigOfPCConfig()                                                     TcpIp_ConfigDataPtr->SizeOfAutoIpConfigOfPCConfig
#define TcpIp_GetSizeOfDefaultMulticastAddrV4OfPCConfig()                                           TcpIp_ConfigDataPtr->SizeOfDefaultMulticastAddrV4OfPCConfig
#define TcpIp_GetSizeOfDefaultUnicastAddrV4OfPCConfig()                                             TcpIp_ConfigDataPtr->SizeOfDefaultUnicastAddrV4OfPCConfig
#define TcpIp_GetSizeOfDhcpUserOptionBufferOfPCConfig()                                             TcpIp_ConfigDataPtr->SizeOfDhcpUserOptionBufferOfPCConfig
#define TcpIp_GetSizeOfDhcpUserOptionOfPCConfig()                                                   TcpIp_ConfigDataPtr->SizeOfDhcpUserOptionOfPCConfig
#define TcpIp_GetSizeOfFragmentationConfigOfPCConfig()                                              TcpIp_ConfigDataPtr->SizeOfFragmentationConfigOfPCConfig
#define TcpIp_GetSizeOfGratuitousArpOfPCConfig()                                                    TcpIp_ConfigDataPtr->SizeOfGratuitousArpOfPCConfig
#define TcpIp_GetSizeOfLlAddrStateOfPCConfig()                                                      TcpIp_ConfigDataPtr->SizeOfLlAddrStateOfPCConfig
#define TcpIp_GetSizeOfMulticastAddrV4OfPCConfig()                                                  TcpIp_ConfigDataPtr->SizeOfMulticastAddrV4OfPCConfig
#define TcpIp_GetSizeOfPhysAddrConfigOfPCConfig()                                                   TcpIp_ConfigDataPtr->SizeOfPhysAddrConfigOfPCConfig
#define TcpIp_GetSizeOfReassemblyBufferDescOfPCConfig()                                             TcpIp_ConfigDataPtr->SizeOfReassemblyBufferDescOfPCConfig
#define TcpIp_GetSizeOfReassemblyBufferOfPCConfig()                                                 TcpIp_ConfigDataPtr->SizeOfReassemblyBufferOfPCConfig
#define TcpIp_GetSizeOfStaticArpEntryOfPCConfig()                                                   TcpIp_ConfigDataPtr->SizeOfStaticArpEntryOfPCConfig
#define TcpIp_GetSizeOfStaticArpTableOfPCConfig()                                                   TcpIp_ConfigDataPtr->SizeOfStaticArpTableOfPCConfig
#define TcpIp_GetSizeOfStaticUnicastAddrV4RequestedOfPCConfig()                                     TcpIp_ConfigDataPtr->SizeOfStaticUnicastAddrV4RequestedOfPCConfig
#define TcpIp_GetSizeOfTxReqElemListOfPCConfig()                                                    TcpIp_ConfigDataPtr->SizeOfTxReqElemListOfPCConfig
#define TcpIp_GetSizeOfTxReqElemOfPCConfig()                                                        TcpIp_ConfigDataPtr->SizeOfTxReqElemOfPCConfig
#define TcpIp_GetSizeOfUdpTxRetryQueueElementChainOfPCConfig()                                      TcpIp_ConfigDataPtr->SizeOfUdpTxRetryQueueElementChainOfPCConfig
#define TcpIp_GetSizeOfUdpTxRetryQueueElementsOfPCConfig()                                          TcpIp_ConfigDataPtr->SizeOfUdpTxRetryQueueElementsOfPCConfig
#define TcpIp_GetSizeOfUdpTxRetryQueuePoolDescOfPCConfig()                                          TcpIp_ConfigDataPtr->SizeOfUdpTxRetryQueuePoolDescOfPCConfig
#define TcpIp_GetSizeOfUnicastAddrV4OfPCConfig()                                                    TcpIp_ConfigDataPtr->SizeOfUnicastAddrV4OfPCConfig
#define TcpIp_GetStaticArpEntryOfPCConfig()                                                         TcpIp_ConfigDataPtr->StaticArpEntryOfPCConfig
#define TcpIp_GetStaticArpTableOfPCConfig()                                                         TcpIp_ConfigDataPtr->StaticArpTableOfPCConfig
#define TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()                                           TcpIp_ConfigDataPtr->StaticUnicastAddrV4RequestedOfPCConfig
#define TcpIp_GetTxReqElemListDynOfPCConfig()                                                       TcpIp_ConfigDataPtr->TxReqElemListDynOfPCConfig
#define TcpIp_GetTxReqElemListOfPCConfig()                                                          TcpIp_ConfigDataPtr->TxReqElemListOfPCConfig
#define TcpIp_GetTxReqElemOfPCConfig()                                                              TcpIp_ConfigDataPtr->TxReqElemOfPCConfig
#define TcpIp_GetUdpTxRetryQueueElementChainOfPCConfig()                                            TcpIp_ConfigDataPtr->UdpTxRetryQueueElementChainOfPCConfig
#define TcpIp_GetUdpTxRetryQueueElementsOfPCConfig()                                                TcpIp_ConfigDataPtr->UdpTxRetryQueueElementsOfPCConfig
#define TcpIp_GetUdpTxRetryQueuePoolDescOfPCConfig()                                                TcpIp_ConfigDataPtr->UdpTxRetryQueuePoolDescOfPCConfig
#define TcpIp_GetUnicastAddrV4OfPCConfig()                                                          TcpIp_ConfigDataPtr->UnicastAddrV4OfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCGetConstantDuplicatedRootDataMacros  TcpIp Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define TcpIp_GetAddrAssignmentCfgByPrioOfPCConfig()                                                TcpIp_AddrAssignmentCfgByPrio  /**< the pointer to TcpIp_AddrAssignmentCfgByPrio */
#define TcpIp_GetBuf2TxReqMapOfPCConfig()                                                           TcpIp_Buf2TxReqMap.raw  /**< the pointer to TcpIp_Buf2TxReqMap */
#define TcpIp_GetDuplicateAddrDetectionFctPtrOfPCConfig()                                           (&(TcpIp_DuplicateAddrDetectionFctPtr))  /**< the pointer to TcpIp_DuplicateAddrDetectionFctPtr */
#define TcpIp_GetEthIfCtrlOfPCConfig()                                                              TcpIp_EthIfCtrl  /**< the pointer to TcpIp_EthIfCtrl */
#define TcpIp_GetIcmpMsgHandlerCbkFctPtrOfPCConfig()                                                (&(TcpIp_IcmpMsgHandlerCbkFctPtr))  /**< the pointer to TcpIp_IcmpMsgHandlerCbkFctPtr */
#define TcpIp_GetIpV4CtrlDynOfPCConfig()                                                            TcpIp_IpV4CtrlDyn.raw  /**< the pointer to TcpIp_IpV4CtrlDyn */
#define TcpIp_GetIpV4CtrlOfPCConfig()                                                               TcpIp_IpV4Ctrl  /**< the pointer to TcpIp_IpV4Ctrl */
#define TcpIp_GetIpV4GeneralOfPCConfig()                                                            TcpIp_IpV4General  /**< the pointer to TcpIp_IpV4General */
#define TcpIp_GetIpV4SocketDynOfPCConfig()                                                          TcpIp_IpV4SocketDyn.raw  /**< the pointer to TcpIp_IpV4SocketDyn */
#define TcpIp_GetLocalAddrOfPCConfig()                                                              TcpIp_LocalAddr.raw  /**< the pointer to TcpIp_LocalAddr */
#define TcpIp_GetLocalAddrV4OfPCConfig()                                                            TcpIp_LocalAddrV4  /**< the pointer to TcpIp_LocalAddrV4 */
#define TcpIp_GetRandomNumberFctPtrOfPCConfig()                                                     (&(TcpIp_RandomNumberFctPtr))  /**< the pointer to TcpIp_RandomNumberFctPtr */
#define TcpIp_GetSizeOfAddrAssignmentCfgByPrioOfPCConfig()                                          1u  /**< the number of accomplishable value elements in TcpIp_AddrAssignmentCfgByPrio */
#define TcpIp_GetSizeOfBuf2TxReqMapOfPCConfig()                                                     4u  /**< the number of accomplishable value elements in TcpIp_Buf2TxReqMap */
#define TcpIp_GetSizeOfEthIfCtrlOfPCConfig()                                                        1u  /**< the number of accomplishable value elements in TcpIp_EthIfCtrl */
#define TcpIp_GetSizeOfIpV4CtrlOfPCConfig()                                                         1u  /**< the number of accomplishable value elements in TcpIp_IpV4Ctrl */
#define TcpIp_GetSizeOfIpV4GeneralOfPCConfig()                                                      1u  /**< the number of accomplishable value elements in TcpIp_IpV4General */
#define TcpIp_GetSizeOfIpV4SocketDynOfPCConfig()                                                    2u  /**< the number of accomplishable value elements in TcpIp_IpV4SocketDyn */
#define TcpIp_GetSizeOfLocalAddrOfPCConfig()                                                        3u  /**< the number of accomplishable value elements in TcpIp_LocalAddr */
#define TcpIp_GetSizeOfLocalAddrV4OfPCConfig()                                                      3u  /**< the number of accomplishable value elements in TcpIp_LocalAddrV4 */
#define TcpIp_GetSizeOfSocketDynOfPCConfig()                                                        2u  /**< the number of accomplishable value elements in TcpIp_SocketDyn */
#define TcpIp_GetSizeOfSocketOwnerConfigOfPCConfig()                                                1u  /**< the number of accomplishable value elements in TcpIp_SocketOwnerConfig */
#define TcpIp_GetSizeOfSocketUdpDynOfPCConfig()                                                     2u  /**< the number of accomplishable value elements in TcpIp_SocketUdpDyn */
#define TcpIp_GetSocketDynOfPCConfig()                                                              TcpIp_SocketDyn.raw  /**< the pointer to TcpIp_SocketDyn */
#define TcpIp_GetSocketOwnerConfigOfPCConfig()                                                      TcpIp_SocketOwnerConfig  /**< the pointer to TcpIp_SocketOwnerConfig */
#define TcpIp_GetSocketUdpDynOfPCConfig()                                                           TcpIp_SocketUdpDyn  /**< the pointer to TcpIp_SocketUdpDyn */
/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCGetDuplicatedRootDataMacros  TcpIp Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define TcpIp_GetSizeOfDhcpUserOptionDynOfPCConfig()                                                TcpIp_GetSizeOfDhcpUserOptionOfPCConfig()  /**< the number of accomplishable value elements in TcpIp_DhcpUserOptionDyn */
#define TcpIp_GetSizeOfIpV4CtrlDynOfPCConfig()                                                      TcpIp_GetSizeOfIpV4CtrlOfPCConfig()  /**< the number of accomplishable value elements in TcpIp_IpV4CtrlDyn */
#define TcpIp_GetSizeOfMulticastAddrV4RequestedOfPCConfig()                                         TcpIp_GetSizeOfMulticastAddrV4OfPCConfig()  /**< the number of accomplishable value elements in TcpIp_MulticastAddrV4Requested */
#define TcpIp_GetSizeOfReassemblyBufferDescDynOfPCConfig()                                          TcpIp_GetSizeOfReassemblyBufferDescOfPCConfig()  /**< the number of accomplishable value elements in TcpIp_ReassemblyBufferDescDyn */
#define TcpIp_GetSizeOfTxReqElemListDynOfPCConfig()                                                 TcpIp_GetSizeOfTxReqElemListOfPCConfig()  /**< the number of accomplishable value elements in TcpIp_TxReqElemListDyn */
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
  GLOBAL DATA TYPES - SIMPLE
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  TcpIpPCIterableTypes  TcpIp Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate TcpIp_AddrAssignmentCfgByPrio */
typedef uint8_least TcpIp_AddrAssignmentCfgByPrioIterType;

/**   \brief  type used to iterate TcpIp_ArpConfig */
typedef uint8_least TcpIp_ArpConfigIterType;

/**   \brief  type used to iterate TcpIp_ArpTableEntry */
typedef uint8_least TcpIp_ArpTableEntryIterType;

/**   \brief  type used to iterate TcpIp_AutoIpConfig */
typedef uint8_least TcpIp_AutoIpConfigIterType;

/**   \brief  type used to iterate TcpIp_Buf2TxReqMap */
typedef uint8_least TcpIp_Buf2TxReqMapIterType;

/**   \brief  type used to iterate TcpIp_DefaultMulticastAddrV4 */
typedef uint8_least TcpIp_DefaultMulticastAddrV4IterType;

/**   \brief  type used to iterate TcpIp_DefaultUnicastAddrV4 */
typedef uint8_least TcpIp_DefaultUnicastAddrV4IterType;

/**   \brief  type used to iterate TcpIp_DhcpUserOption */
typedef uint8_least TcpIp_DhcpUserOptionIterType;

/**   \brief  type used to iterate TcpIp_DhcpUserOptionBuffer */
typedef uint8_least TcpIp_DhcpUserOptionBufferIterType;

/**   \brief  type used to iterate TcpIp_EthIfCtrl */
typedef uint8_least TcpIp_EthIfCtrlIterType;

/**   \brief  type used to iterate TcpIp_FragmentationConfig */
typedef uint8_least TcpIp_FragmentationConfigIterType;

/**   \brief  type used to iterate TcpIp_GratuitousArp */
typedef uint8_least TcpIp_GratuitousArpIterType;

/**   \brief  type used to iterate TcpIp_IpV4Ctrl */
typedef uint8_least TcpIp_IpV4CtrlIterType;

/**   \brief  type used to iterate TcpIp_IpV4General */
typedef uint8_least TcpIp_IpV4GeneralIterType;

/**   \brief  type used to iterate TcpIp_IpV4SocketDyn */
typedef uint8_least TcpIp_IpV4SocketDynIterType;

/**   \brief  type used to iterate TcpIp_LlAddrState */
typedef uint8_least TcpIp_LlAddrStateIterType;

/**   \brief  type used to iterate TcpIp_LocalAddr */
typedef uint8_least TcpIp_LocalAddrIterType;

/**   \brief  type used to iterate TcpIp_LocalAddrV4 */
typedef uint8_least TcpIp_LocalAddrV4IterType;

/**   \brief  type used to iterate TcpIp_MulticastAddrV4 */
typedef uint8_least TcpIp_MulticastAddrV4IterType;

/**   \brief  type used to iterate TcpIp_PhysAddrConfig */
typedef uint8_least TcpIp_PhysAddrConfigIterType;

/**   \brief  type used to iterate TcpIp_ReassemblyBuffer */
typedef uint8_least TcpIp_ReassemblyBufferIterType;

/**   \brief  type used to iterate TcpIp_ReassemblyBufferDesc */
typedef uint8_least TcpIp_ReassemblyBufferDescIterType;

/**   \brief  type used to iterate TcpIp_SocketDyn */
typedef uint8_least TcpIp_SocketDynIterType;

/**   \brief  type used to iterate TcpIp_SocketOwnerConfig */
typedef uint8_least TcpIp_SocketOwnerConfigIterType;

/**   \brief  type used to iterate TcpIp_SocketUdpDyn */
typedef uint8_least TcpIp_SocketUdpDynIterType;

/**   \brief  type used to iterate TcpIp_StaticArpEntry */
typedef uint8_least TcpIp_StaticArpEntryIterType;

/**   \brief  type used to iterate TcpIp_StaticArpTable */
typedef uint8_least TcpIp_StaticArpTableIterType;

/**   \brief  type used to iterate TcpIp_StaticUnicastAddrV4Requested */
typedef uint8_least TcpIp_StaticUnicastAddrV4RequestedIterType;

/**   \brief  type used to iterate TcpIp_TxReqElem */
typedef uint8_least TcpIp_TxReqElemIterType;

/**   \brief  type used to iterate TcpIp_TxReqElemList */
typedef uint8_least TcpIp_TxReqElemListIterType;

/**   \brief  type used to iterate TcpIp_UdpTxRetryQueueElementChain */
typedef uint8_least TcpIp_UdpTxRetryQueueElementChainIterType;

/**   \brief  type used to iterate TcpIp_UdpTxRetryQueueElements */
typedef uint8_least TcpIp_UdpTxRetryQueueElementsIterType;

/**   \brief  type used to iterate TcpIp_UdpTxRetryQueuePoolDesc */
typedef uint8_least TcpIp_UdpTxRetryQueuePoolDescIterType;

/**   \brief  type used to iterate TcpIp_UnicastAddrV4 */
typedef uint8_least TcpIp_UnicastAddrV4IterType;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCIterableTypesWithSizeRelations  TcpIp Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate TcpIp_DhcpUserOptionDyn */
typedef TcpIp_DhcpUserOptionIterType TcpIp_DhcpUserOptionDynIterType;

/**   \brief  type used to iterate TcpIp_IpV4CtrlDyn */
typedef TcpIp_IpV4CtrlIterType TcpIp_IpV4CtrlDynIterType;

/**   \brief  type used to iterate TcpIp_MulticastAddrV4Requested */
typedef TcpIp_MulticastAddrV4IterType TcpIp_MulticastAddrV4RequestedIterType;

/**   \brief  type used to iterate TcpIp_ReassemblyBufferDescDyn */
typedef TcpIp_ReassemblyBufferDescIterType TcpIp_ReassemblyBufferDescDynIterType;

/**   \brief  type used to iterate TcpIp_TxReqElemListDyn */
typedef TcpIp_TxReqElemListIterType TcpIp_TxReqElemListDynIterType;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCValueTypes  TcpIp Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for TcpIp_AddrAssignmentCfgByPrio */
typedef uint8 TcpIp_AddrAssignmentCfgByPrioType;

/**   \brief  value based type definition for TcpIp_EntryTimeoutOfArpConfig */
typedef uint16 TcpIp_EntryTimeoutOfArpConfigType;

/**   \brief  value based type definition for TcpIp_NumGratuitousArpOnStartupOfArpConfig */
typedef uint8 TcpIp_NumGratuitousArpOnStartupOfArpConfigType;

/**   \brief  value based type definition for TcpIp_PacketQueueEnabledOfArpConfig */
typedef boolean TcpIp_PacketQueueEnabledOfArpConfigType;

/**   \brief  value based type definition for TcpIp_RequestTimeoutOfArpConfig */
typedef uint8 TcpIp_RequestTimeoutOfArpConfigType;

/**   \brief  value based type definition for TcpIp_RetryIntervalOfArpConfig */
typedef uint16 TcpIp_RetryIntervalOfArpConfigType;

/**   \brief  value based type definition for TcpIp_RetryTimeOfArpConfig */
typedef uint16 TcpIp_RetryTimeOfArpConfigType;

/**   \brief  value based type definition for TcpIp_TableSizeOfArpConfig */
typedef uint8 TcpIp_TableSizeOfArpConfigType;

/**   \brief  value based type definition for TcpIp_CreationTimeStampOfArpTableEntry */
typedef uint32 TcpIp_CreationTimeStampOfArpTableEntryType;

/**   \brief  value based type definition for TcpIp_StatusOfArpTableEntry */
typedef uint8 TcpIp_StatusOfArpTableEntryType;

/**   \brief  value based type definition for TcpIp_TimeStampOfArpTableEntry */
typedef uint32 TcpIp_TimeStampOfArpTableEntryType;

/**   \brief  value based type definition for TcpIp_AnnounceIntervalMsOfAutoIpConfig */
typedef uint8 TcpIp_AnnounceIntervalMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_AnnounceNumOfAutoIpConfig */
typedef uint8 TcpIp_AnnounceNumOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_AnnounceWaitMsOfAutoIpConfig */
typedef uint8 TcpIp_AnnounceWaitMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_DefendIntervalMsOfAutoIpConfig */
typedef uint8 TcpIp_DefendIntervalMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_MaxConflictsOfAutoIpConfig */
typedef uint8 TcpIp_MaxConflictsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_ProbeMaxMsOfAutoIpConfig */
typedef uint8 TcpIp_ProbeMaxMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_ProbeMinMsOfAutoIpConfig */
typedef uint8 TcpIp_ProbeMinMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_ProbeNumOfAutoIpConfig */
typedef uint8 TcpIp_ProbeNumOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_ProbeWaitMaxMsOfAutoIpConfig */
typedef uint8 TcpIp_ProbeWaitMaxMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_ProbeWaitMinMsOfAutoIpConfig */
typedef uint8 TcpIp_ProbeWaitMinMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_RateLimitIntervalMsOfAutoIpConfig */
typedef uint8 TcpIp_RateLimitIntervalMsOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_EthBufIdxNextOfBuf2TxReqMap */
typedef uint8 TcpIp_EthBufIdxNextOfBuf2TxReqMapType;

/**   \brief  value based type definition for TcpIp_EthBufLenOfBuf2TxReqMap */
typedef uint16 TcpIp_EthBufLenOfBuf2TxReqMapType;

/**   \brief  value based type definition for TcpIp_SocketDynIdxOfBuf2TxReqMap */
typedef uint8 TcpIp_SocketDynIdxOfBuf2TxReqMapType;

/**   \brief  value based type definition for TcpIp_UlTxReqIdxOfBuf2TxReqMap */
typedef uint8 TcpIp_UlTxReqIdxOfBuf2TxReqMapType;

/**   \brief  value based type definition for TcpIp_CodeOfDhcpUserOption */
typedef uint8 TcpIp_CodeOfDhcpUserOptionType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOption */
typedef uint8 TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOptionType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOption */
typedef uint8 TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOptionType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOption */
typedef uint8 TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOptionType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionBuffer */
typedef uint8 TcpIp_DhcpUserOptionBufferType;

/**   \brief  value based type definition for TcpIp_LengthOfDhcpUserOptionDyn */
typedef uint16 TcpIp_LengthOfDhcpUserOptionDynType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlIdxOfEthIfCtrl */
typedef uint8 TcpIp_IpV4CtrlIdxOfEthIfCtrlType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlUsedOfEthIfCtrl */
typedef boolean TcpIp_IpV4CtrlUsedOfEthIfCtrlType;

/**   \brief  value based type definition for TcpIp_InOrderReassemblyOfFragmentationConfig */
typedef boolean TcpIp_InOrderReassemblyOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_MaxPacketSizeOfFragmentationConfig */
typedef uint8 TcpIp_MaxPacketSizeOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfig */
typedef uint8 TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferDescLengthOfFragmentationConfig */
typedef uint8 TcpIp_ReassemblyBufferDescLengthOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfig */
typedef uint8 TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferDescUsedOfFragmentationConfig */
typedef boolean TcpIp_ReassemblyBufferDescUsedOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_ReassemblyTimeoutMsOfFragmentationConfig */
typedef uint8 TcpIp_ReassemblyTimeoutMsOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_NextTransmissionMsOfGratuitousArp */
typedef uint32 TcpIp_NextTransmissionMsOfGratuitousArpType;

/**   \brief  value based type definition for TcpIp_TransmissionCntOfGratuitousArp */
typedef uint8 TcpIp_TransmissionCntOfGratuitousArpType;

/**   \brief  value based type definition for TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl */
typedef uint8 TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl */
typedef uint8 TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_AddrAssignmentPrioByTypeOfIpV4Ctrl */
typedef uint8 TcpIp_AddrAssignmentPrioByTypeOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ArpConfigIdxOfIpV4Ctrl */
typedef uint8 TcpIp_ArpConfigIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ArpConfigUsedOfIpV4Ctrl */
typedef boolean TcpIp_ArpConfigUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ArpTableEntryEndIdxOfIpV4Ctrl */
typedef uint8 TcpIp_ArpTableEntryEndIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ArpTableEntryStartIdxOfIpV4Ctrl */
typedef uint8 TcpIp_ArpTableEntryStartIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ArpTableEntryUsedOfIpV4Ctrl */
typedef boolean TcpIp_ArpTableEntryUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_AutoIpConfigIdxOfIpV4Ctrl */
typedef uint8 TcpIp_AutoIpConfigIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_AutoIpConfigUsedOfIpV4Ctrl */
typedef boolean TcpIp_AutoIpConfigUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_Buf2TxReqMapEndIdxOfIpV4Ctrl */
typedef uint8 TcpIp_Buf2TxReqMapEndIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_Buf2TxReqMapStartIdxOfIpV4Ctrl */
typedef uint8 TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DefaultTtlOfIpV4Ctrl */
typedef uint8 TcpIp_DefaultTtlOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpConfigIdxOfIpV4Ctrl */
typedef uint8 TcpIp_DhcpConfigIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpConfigUsedOfIpV4Ctrl */
typedef boolean TcpIp_DhcpConfigUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpStatusIdxOfIpV4Ctrl */
typedef uint8 TcpIp_DhcpStatusIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpStatusUsedOfIpV4Ctrl */
typedef boolean TcpIp_DhcpStatusUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionEndIdxOfIpV4Ctrl */
typedef uint8 TcpIp_DhcpUserOptionEndIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionStartIdxOfIpV4Ctrl */
typedef uint8 TcpIp_DhcpUserOptionStartIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_DhcpUserOptionUsedOfIpV4Ctrl */
typedef boolean TcpIp_DhcpUserOptionUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_EthIfCtrlIdxOfIpV4Ctrl */
typedef uint8 TcpIp_EthIfCtrlIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_FragmentationConfigIdxOfIpV4Ctrl */
typedef uint8 TcpIp_FragmentationConfigIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_FragmentationConfigUsedOfIpV4Ctrl */
typedef boolean TcpIp_FragmentationConfigUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_FramePrioDefaultOfIpV4Ctrl */
typedef uint8 TcpIp_FramePrioDefaultOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_GratuitousArpIdxOfIpV4Ctrl */
typedef uint8 TcpIp_GratuitousArpIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_GratuitousArpUsedOfIpV4Ctrl */
typedef boolean TcpIp_GratuitousArpUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_HwChecksumIcmpOfIpV4Ctrl */
typedef boolean TcpIp_HwChecksumIcmpOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_HwChecksumIpOfIpV4Ctrl */
typedef boolean TcpIp_HwChecksumIpOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_HwChecksumTcpOfIpV4Ctrl */
typedef boolean TcpIp_HwChecksumTcpOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_HwChecksumUdpOfIpV4Ctrl */
typedef boolean TcpIp_HwChecksumUdpOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_LlAddrStateIdxOfIpV4Ctrl */
typedef uint8 TcpIp_LlAddrStateIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_LlAddrStateUsedOfIpV4Ctrl */
typedef boolean TcpIp_LlAddrStateUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_LocalAddrV4BroadcastIdxOfIpV4Ctrl */
typedef uint8 TcpIp_LocalAddrV4BroadcastIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_LocalAddrV4UnicastIdxOfIpV4Ctrl */
typedef uint8 TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_MaxTxMsgSizeOfIpV4Ctrl */
typedef uint16 TcpIp_MaxTxMsgSizeOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_MtuTxOfIpV4Ctrl */
typedef uint16 TcpIp_MtuTxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_MulticastAddrV4EndIdxOfIpV4Ctrl */
typedef uint8 TcpIp_MulticastAddrV4EndIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_MulticastAddrV4StartIdxOfIpV4Ctrl */
typedef uint8 TcpIp_MulticastAddrV4StartIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_MulticastAddrV4UsedOfIpV4Ctrl */
typedef boolean TcpIp_MulticastAddrV4UsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ReceiveAllMulticastsOfIpV4Ctrl */
typedef boolean TcpIp_ReceiveAllMulticastsOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_StaticArpTableIdxOfIpV4Ctrl */
typedef uint8 TcpIp_StaticArpTableIdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_StaticArpTableUsedOfIpV4Ctrl */
typedef boolean TcpIp_StaticArpTableUsedOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_TypeOfServiceDefaultOfIpV4Ctrl */
typedef uint8 TcpIp_TypeOfServiceDefaultOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_UnicastAddrV4IdxOfIpV4Ctrl */
typedef uint8 TcpIp_UnicastAddrV4IdxOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDyn */
typedef uint8 TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDyn */
typedef boolean TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn */
typedef uint8 TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_PhysLinkActiveOfIpV4CtrlDyn */
typedef boolean TcpIp_PhysLinkActiveOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_StateOfIpV4CtrlDyn */
typedef uint8 TcpIp_StateOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlDefaultIdxOfIpV4General */
typedef uint8 TcpIp_IpV4CtrlDefaultIdxOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlDefaultUsedOfIpV4General */
typedef boolean TcpIp_IpV4CtrlDefaultUsedOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynDhcpIdxOfIpV4General */
typedef uint8 TcpIp_IpV4SocketDynDhcpIdxOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynDhcpUsedOfIpV4General */
typedef boolean TcpIp_IpV4SocketDynDhcpUsedOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynIcmpIdxOfIpV4General */
typedef uint8 TcpIp_IpV4SocketDynIcmpIdxOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynIcmpUsedOfIpV4General */
typedef boolean TcpIp_IpV4SocketDynIcmpUsedOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynTcpRstIdxOfIpV4General */
typedef uint8 TcpIp_IpV4SocketDynTcpRstIdxOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_IpV4SocketDynTcpRstUsedOfIpV4General */
typedef boolean TcpIp_IpV4SocketDynTcpRstUsedOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_ArpTableEntryIdxOfIpV4SocketDyn */
typedef uint8 TcpIp_ArpTableEntryIdxOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_EthIfFramePrioOfIpV4SocketDyn */
typedef uint8 TcpIp_EthIfFramePrioOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_FlagsOfIpV4SocketDyn */
typedef uint8 TcpIp_FlagsOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlIdxOfIpV4SocketDyn */
typedef uint8 TcpIp_IpV4CtrlIdxOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_ProtocolOfIpV4SocketDyn */
typedef uint8 TcpIp_ProtocolOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_TimeToLiveOfIpV4SocketDyn */
typedef uint8 TcpIp_TimeToLiveOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_TxDescriptorProtocolOfIpV4SocketDyn */
typedef uint8 TcpIp_TxDescriptorProtocolOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_TypeOfServiceOfIpV4SocketDyn */
typedef uint8 TcpIp_TypeOfServiceOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_AddrConflictOfLlAddrState */
typedef boolean TcpIp_AddrConflictOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_AddrConflictTimeoutOfLlAddrState */
typedef uint16 TcpIp_AddrConflictTimeoutOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_AnnStateOfLlAddrState */
typedef uint8 TcpIp_AnnStateOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_AnnounceNumOfLlAddrState */
typedef uint8 TcpIp_AnnounceNumOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_ConflictsNumOfLlAddrState */
typedef uint8 TcpIp_ConflictsNumOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_MsecCntOfLlAddrState */
typedef uint32 TcpIp_MsecCntOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_ProbeNumOfLlAddrState */
typedef uint16 TcpIp_ProbeNumOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_ProbeNumSinceConfOfLlAddrState */
typedef uint8 TcpIp_ProbeNumSinceConfOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_ProbeStateOfLlAddrState */
typedef uint8 TcpIp_ProbeStateOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_StateOfLlAddrState */
typedef uint8 TcpIp_StateOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_WaitUntilTimeOfLlAddrState */
typedef uint32 TcpIp_WaitUntilTimeOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_AssignmentStateOfLocalAddr */
typedef uint8 TcpIp_AssignmentStateOfLocalAddrType;

/**   \brief  value based type definition for TcpIp_IpV4CtrlIdxOfLocalAddrV4 */
typedef uint8 TcpIp_IpV4CtrlIdxOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_MulticastAddrV4IdxOfLocalAddrV4 */
typedef uint8 TcpIp_MulticastAddrV4IdxOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_MulticastAddrV4UsedOfLocalAddrV4 */
typedef boolean TcpIp_MulticastAddrV4UsedOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_UnicastAddrV4IdxOfLocalAddrV4 */
typedef uint8 TcpIp_UnicastAddrV4IdxOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_UnicastAddrV4UsedOfLocalAddrV4 */
typedef boolean TcpIp_UnicastAddrV4UsedOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4 */
typedef uint8 TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4Type;

/**   \brief  value based type definition for TcpIp_LocalAddrV4IdxOfMulticastAddrV4 */
typedef uint8 TcpIp_LocalAddrV4IdxOfMulticastAddrV4Type;

/**   \brief  value based type definition for TcpIp_ReassemblyBuffer */
typedef uint8 TcpIp_ReassemblyBufferType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDesc */
typedef uint8 TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDescType;

/**   \brief  value based type definition for TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDesc */
typedef uint8 TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType;

/**   \brief  value based type definition for TcpIp_SizeOfAddrAssignmentCfgByPrio */
typedef uint8 TcpIp_SizeOfAddrAssignmentCfgByPrioType;

/**   \brief  value based type definition for TcpIp_SizeOfArpConfig */
typedef uint8 TcpIp_SizeOfArpConfigType;

/**   \brief  value based type definition for TcpIp_SizeOfArpTableEntry */
typedef uint8 TcpIp_SizeOfArpTableEntryType;

/**   \brief  value based type definition for TcpIp_SizeOfAutoIpConfig */
typedef uint8 TcpIp_SizeOfAutoIpConfigType;

/**   \brief  value based type definition for TcpIp_SizeOfBuf2TxReqMap */
typedef uint8 TcpIp_SizeOfBuf2TxReqMapType;

/**   \brief  value based type definition for TcpIp_SizeOfDefaultMulticastAddrV4 */
typedef uint8 TcpIp_SizeOfDefaultMulticastAddrV4Type;

/**   \brief  value based type definition for TcpIp_SizeOfDefaultUnicastAddrV4 */
typedef uint8 TcpIp_SizeOfDefaultUnicastAddrV4Type;

/**   \brief  value based type definition for TcpIp_SizeOfDhcpUserOption */
typedef uint8 TcpIp_SizeOfDhcpUserOptionType;

/**   \brief  value based type definition for TcpIp_SizeOfDhcpUserOptionBuffer */
typedef uint8 TcpIp_SizeOfDhcpUserOptionBufferType;

/**   \brief  value based type definition for TcpIp_SizeOfDhcpUserOptionDyn */
typedef uint8 TcpIp_SizeOfDhcpUserOptionDynType;

/**   \brief  value based type definition for TcpIp_SizeOfEthIfCtrl */
typedef uint8 TcpIp_SizeOfEthIfCtrlType;

/**   \brief  value based type definition for TcpIp_SizeOfFragmentationConfig */
typedef uint8 TcpIp_SizeOfFragmentationConfigType;

/**   \brief  value based type definition for TcpIp_SizeOfGratuitousArp */
typedef uint8 TcpIp_SizeOfGratuitousArpType;

/**   \brief  value based type definition for TcpIp_SizeOfIpV4Ctrl */
typedef uint8 TcpIp_SizeOfIpV4CtrlType;

/**   \brief  value based type definition for TcpIp_SizeOfIpV4CtrlDyn */
typedef uint8 TcpIp_SizeOfIpV4CtrlDynType;

/**   \brief  value based type definition for TcpIp_SizeOfIpV4General */
typedef uint8 TcpIp_SizeOfIpV4GeneralType;

/**   \brief  value based type definition for TcpIp_SizeOfIpV4SocketDyn */
typedef uint8 TcpIp_SizeOfIpV4SocketDynType;

/**   \brief  value based type definition for TcpIp_SizeOfLlAddrState */
typedef uint8 TcpIp_SizeOfLlAddrStateType;

/**   \brief  value based type definition for TcpIp_SizeOfLocalAddr */
typedef uint8 TcpIp_SizeOfLocalAddrType;

/**   \brief  value based type definition for TcpIp_SizeOfLocalAddrV4 */
typedef uint8 TcpIp_SizeOfLocalAddrV4Type;

/**   \brief  value based type definition for TcpIp_SizeOfMulticastAddrV4 */
typedef uint8 TcpIp_SizeOfMulticastAddrV4Type;

/**   \brief  value based type definition for TcpIp_SizeOfMulticastAddrV4Requested */
typedef uint8 TcpIp_SizeOfMulticastAddrV4RequestedType;

/**   \brief  value based type definition for TcpIp_SizeOfPhysAddrConfig */
typedef uint8 TcpIp_SizeOfPhysAddrConfigType;

/**   \brief  value based type definition for TcpIp_SizeOfReassemblyBuffer */
typedef uint8 TcpIp_SizeOfReassemblyBufferType;

/**   \brief  value based type definition for TcpIp_SizeOfReassemblyBufferDesc */
typedef uint8 TcpIp_SizeOfReassemblyBufferDescType;

/**   \brief  value based type definition for TcpIp_SizeOfReassemblyBufferDescDyn */
typedef uint8 TcpIp_SizeOfReassemblyBufferDescDynType;

/**   \brief  value based type definition for TcpIp_SizeOfSocketDyn */
typedef uint8 TcpIp_SizeOfSocketDynType;

/**   \brief  value based type definition for TcpIp_SizeOfSocketOwnerConfig */
typedef uint8 TcpIp_SizeOfSocketOwnerConfigType;

/**   \brief  value based type definition for TcpIp_SizeOfSocketUdpDyn */
typedef uint8 TcpIp_SizeOfSocketUdpDynType;

/**   \brief  value based type definition for TcpIp_SizeOfStaticArpEntry */
typedef uint8 TcpIp_SizeOfStaticArpEntryType;

/**   \brief  value based type definition for TcpIp_SizeOfStaticArpTable */
typedef uint8 TcpIp_SizeOfStaticArpTableType;

/**   \brief  value based type definition for TcpIp_SizeOfStaticUnicastAddrV4Requested */
typedef uint8 TcpIp_SizeOfStaticUnicastAddrV4RequestedType;

/**   \brief  value based type definition for TcpIp_SizeOfTxReqElem */
typedef uint8 TcpIp_SizeOfTxReqElemType;

/**   \brief  value based type definition for TcpIp_SizeOfTxReqElemList */
typedef uint8 TcpIp_SizeOfTxReqElemListType;

/**   \brief  value based type definition for TcpIp_SizeOfTxReqElemListDyn */
typedef uint8 TcpIp_SizeOfTxReqElemListDynType;

/**   \brief  value based type definition for TcpIp_SizeOfUdpTxRetryQueueElementChain */
typedef uint8 TcpIp_SizeOfUdpTxRetryQueueElementChainType;

/**   \brief  value based type definition for TcpIp_SizeOfUdpTxRetryQueueElements */
typedef uint8 TcpIp_SizeOfUdpTxRetryQueueElementsType;

/**   \brief  value based type definition for TcpIp_SizeOfUdpTxRetryQueuePoolDesc */
typedef uint8 TcpIp_SizeOfUdpTxRetryQueuePoolDescType;

/**   \brief  value based type definition for TcpIp_SizeOfUnicastAddrV4 */
typedef uint8 TcpIp_SizeOfUnicastAddrV4Type;

/**   \brief  value based type definition for TcpIp_ListenActiveConnStatOfSocketDyn */
typedef uint8 TcpIp_ListenActiveConnStatOfSocketDynType;

/**   \brief  value based type definition for TcpIp_LocalAddrBindIdxOfSocketDyn */
typedef uint8 TcpIp_LocalAddrBindIdxOfSocketDynType;

/**   \brief  value based type definition for TcpIp_SocketOwnerConfigIdxOfSocketDyn */
typedef uint8 TcpIp_SocketOwnerConfigIdxOfSocketDynType;

/**   \brief  value based type definition for TcpIp_TxBufRequestedOfSocketDyn */
typedef boolean TcpIp_TxBufRequestedOfSocketDynType;

/**   \brief  value based type definition for TcpIp_TxIpAddrIdxOfSocketDyn */
typedef uint8 TcpIp_TxIpAddrIdxOfSocketDynType;

/**   \brief  value based type definition for TcpIp_TxReqElemListIdxOfSocketUdpDyn */
typedef uint8 TcpIp_TxReqElemListIdxOfSocketUdpDynType;

/**   \brief  value based type definition for TcpIp_TxRetrQueueMaxNumOfSocketUdpDyn */
typedef uint8 TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType;

/**   \brief  value based type definition for TcpIp_StaticArpEntryEndIdxOfStaticArpTable */
typedef uint8 TcpIp_StaticArpEntryEndIdxOfStaticArpTableType;

/**   \brief  value based type definition for TcpIp_StaticArpEntryStartIdxOfStaticArpTable */
typedef uint8 TcpIp_StaticArpEntryStartIdxOfStaticArpTableType;

/**   \brief  value based type definition for TcpIp_TxReqElemDataLenByteOfTxReqElem */
typedef uint16 TcpIp_TxReqElemDataLenByteOfTxReqElemType;

/**   \brief  value based type definition for TcpIp_TxReqElemTransmittedOfTxReqElem */
typedef boolean TcpIp_TxReqElemTransmittedOfTxReqElemType;

/**   \brief  value based type definition for TcpIp_TxReqElemEndIdxOfTxReqElemList */
typedef uint8 TcpIp_TxReqElemEndIdxOfTxReqElemListType;

/**   \brief  value based type definition for TcpIp_TxReqElemLengthOfTxReqElemList */
typedef uint8 TcpIp_TxReqElemLengthOfTxReqElemListType;

/**   \brief  value based type definition for TcpIp_TxReqElemStartIdxOfTxReqElemList */
typedef uint8 TcpIp_TxReqElemStartIdxOfTxReqElemListType;

/**   \brief  value based type definition for TcpIp_FillNumOfTxReqElemListDyn */
typedef uint8 TcpIp_FillNumOfTxReqElemListDynType;

/**   \brief  value based type definition for TcpIp_ReadPosOfTxReqElemListDyn */
typedef uint8 TcpIp_ReadPosOfTxReqElemListDynType;

/**   \brief  value based type definition for TcpIp_SocketUdpDynIdxOfTxReqElemListDyn */
typedef uint8 TcpIp_SocketUdpDynIdxOfTxReqElemListDynType;

/**   \brief  value based type definition for TcpIp_WritePosOfTxReqElemListDyn */
typedef uint8 TcpIp_WritePosOfTxReqElemListDynType;

/**   \brief  value based type definition for TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4 */
typedef uint8 TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type;

/**   \brief  value based type definition for TcpIp_DefaultUnicastAddrV4UsedOfUnicastAddrV4 */
typedef boolean TcpIp_DefaultUnicastAddrV4UsedOfUnicastAddrV4Type;

/**   \brief  value based type definition for TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4 */
typedef uint8 TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type;

/**   \brief  value based type definition for TcpIp_StaticUnicastAddrV4RequestedUsedOfUnicastAddrV4 */
typedef boolean TcpIp_StaticUnicastAddrV4RequestedUsedOfUnicastAddrV4Type;

/** 
  \}
*/ 




/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES (TCPIP)
 *********************************************************************************************************************/


#if !defined (TCPIP_LOCAL_INLINE)
# define TCPIP_LOCAL_INLINE LOCAL_INLINE
#endif

typedef union 
{ /* PRQA S 750 */ /* MD_MSR_Union */
  uint8  data[4];
  uint32 data32;
} TcpIp_NvmDataBlockType;

typedef union 
{ /* PRQA S 750 */ /* MD_MSR_Union */
  uint8 data[6];
  uint16 data16[3];
} TcpIp_PhysAddrType;

typedef void (*IpV4_LinkLocalAddrCalloutFuncType)(TcpIp_LocalAddrIdType LocalAddrId, uint8 ConflictCount, IpBase_AddrInType *AddrCandidatePtr);
typedef void (*IpV4_DhcpV4RequestedAddrCalloutFuncType)(TcpIp_LocalAddrIdType LocalAddrId, IpBase_AddrInType *RequestedAddrPtr);


typedef void(*TcpIp_PhysAddrTableChgDiscardedCbkType)(uint8 CtrlIdx, TCPIP_P2C(TcpIp_SockAddrType) IpAddrPtr);

typedef struct
{
  IpBase_AddrInType MatchIpSrcAddr;       /* IP source address of fragments (used to find reassembly buffer) */
  IpBase_AddrInType MatchIpDstAddr;       /* IP destination address of fragments (used to find reassembly buffer) */
  uint32            TimeMs;               /* Value of IpV4_Ip_TimeMs when the reassembly of this packet was started. */
  uint16            MatchIdentification;  /* Value of IP header identification field of fragments (used to find reassembly buffer) */
  uint16            NextGapOfs;           /* Offset (bytes) of the next gap in the reassembly buffer */
  uint16            FragmentLen;          /* length of the reassembly packet in bytes (will be 0 until last fragment has been received) */
  uint8             MatchIpProtocol;      /* Value of IP header protocal field of fragments (used to find reassembly buffer) */
  uint8             Status;               /* Status of this fragment buffer (UNUSED, REASSEMBLY_IN_PROGRESS, REASSEMBLY_COMPLETE, REASSEMBLY_ABORTED) */
  uint8             ReassemblyBufDescIdx; /* Index of the reassembly buffer descriptor itself (Accessed only in case the descriptor is given by a pointer) */
  uint8             Flags;                /* FIRST_FRAG_RECEIVED, LAST_FRAG_RECEIVED */
} IpV4_Ip_ReassemblyBufferDescType;

typedef struct
{
  uint8             Flags;
  uint8             TimeToLive;
  uint8             TypeOfService;
  uint8             EthIfFramePrio;
  uint8             PhysDestAddr[IPBASE_ETH_PHYS_ADDR_LEN_BYTE];
} IpV4_Ip_TransferBlockType;

typedef struct
{
  uint32                    DestAddrV4;       /*<! IPv4 destination address */
  IpBase_FamilyType         AddressFamily;    /*<! IP Family (INET or INET6) */
  uint16                    EthPayloadLen;    /*<! Length of ethernet payload (buffer) in bytes */
  uint16                    IpPayloadOfs;     /*<! Offset of IP payload (length of IP header) inside ethernet payload in bytes */
# if (TCPIP_SUPPORT_IPSEC == STD_ON)                                                                                    /* COV_MSR_UNSUPPORTED */
  uint16                    ExtHdrLenBytes;   /*<! Length of the IpSec header in bytes */
  TcpIp_IpSecPolicyType     IpSecPolicy;      /*<! Indicates the Ip security Policy of the packet */
  TcpIp_SizeOfSaEntryType   SaEntryIdx;       /*<! Security Association to be used for authentication of this packet */
  TcpIp_IpProtocolType      XptProtocol;      /*<! Next layer protocol type */
  uint8                     MessageType;      /*<! In case of XptProtocol == ICMP, the MessageType specifies the ICMP type. */
# endif
  boolean                   IsEthBufV6;       /*<! Indicates whether BufIdx refers to an EthIf buffer or an internal IPv6 fragment buffer */
  uint8                    *EthPayloadPtr;    /*<! Pointer to ethernet payload */
  uint8                     BufIdx;           /*<! Index of the first ethernet buffer for the IP packet. */
  uint8                     SrcAddrIdx;       /*<! IP address identifier of the address that will be used as source address */
  uint8                     CtrlIdx;          /*<! Index of the EthIf controller */
  uint8                     CurBufIdxV4;      /*<! Index of the currently active ethernet buffer. (Only used for IPv4 fragmentation.) */
  TcpIp_SizeOfSocketDynType SockIdx;          /*<! Index of the TcpIp socket this request belongs to. */
} TcpIp_IpTxRequestDescriptorType;

typedef struct
{
  TcpIp_IpTxRequestDescriptorType IpTxRequestDesc;  /* IP TX request descriptor */
  TcpIp_SockAddrBaseType          Destination;      /* IP destination address of the pending packet */
  uint16                          UdpPayloadLen;    /* length of the UDP payload in bytes */
  uint8                           UdpTxReqTabIdx;   /* UDP tx request table index (used for TxConfirmation) */
} TcpIp_Udp_RetryQueueElementType;  /* Used for UDP tx chache in case of PhysAddrMiss */


typedef struct
{
  uint32 Xid;                     /* Transaction ID */
  uint16 Secs;
  uint16 Flags;
  TcpIp_NetAddrType Ciaddr;       /* Client IP address */
  TcpIp_NetAddrType NetMask;      /* Network Mask */
  TcpIp_NetAddrType DhcpSiaddr;   /* DHCP-server IP address */
  TcpIp_NetAddrType DefGWiaddr;   /* Default-GW IP address */
  TcpIp_NetAddrType DnsServAddr;  /* DNS-server IP address */
  uint32 T1;
  uint32 T2;
  uint32 LeaseTime;
} TcpIp_DhcpV4_DataStructType;



/**********************************************************************************************************************
  GLOBAL DATA TYPES - COMPLEX
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  TcpIpPCStructTypes  TcpIp Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in TcpIp_ArpConfig */
typedef struct sTcpIp_ArpConfigType
{
  TcpIp_EntryTimeoutOfArpConfigType EntryTimeoutOfArpConfig;  /**< Table Entry Timeout - Value of configuration parameter TcpIpArpTableEntryTimeout [MAIN_FUNCTION_CYCLES] */
  TcpIp_RetryIntervalOfArpConfigType RetryIntervalOfArpConfig;  /**< Retry Interval - Value of configuration parameter TcpIpArpRetryInterval [MAIN_FUNCTION_CYCLES] */
  TcpIp_RetryTimeOfArpConfigType RetryTimeOfArpConfig;  /**< Retry Timeout - Value of configuration parameter TcpIpArpRetryTime [MAIN_FUNCTION_CYCLES] */
  TcpIp_PacketQueueEnabledOfArpConfigType PacketQueueEnabledOfArpConfig;  /**< Packet Queue Enabled - Value of configuration parameter TcpIpArpPacketQueueEnabled [BOOLEAN] */
  TcpIp_NumGratuitousArpOnStartupOfArpConfigType NumGratuitousArpOnStartupOfArpConfig;  /**< Num Gratuitous ARP On Startup - Value of configuration parameter TcpIpArpNumGratuitousARPonStartup */
  TcpIp_RequestTimeoutOfArpConfigType RequestTimeoutOfArpConfig;  /**< Value of configuration parameter TcpIpArpRequestTimeout [MAIN_FUNCTION_CYCLES] */
  TcpIp_TableSizeOfArpConfigType TableSizeOfArpConfig;  /**< Table Size Max - Value of configuration parameter TcpIpArpTableSizeMax */
} TcpIp_ArpConfigType;

/**   \brief  type used in TcpIp_ArpTableEntry */
typedef struct sTcpIp_ArpTableEntryType
{
  TcpIp_CreationTimeStampOfArpTableEntryType CreationTimeStampOfArpTableEntry;  /**< Time when this entry was created [MAIN_FUNCTION_CYCLES] */
  TcpIp_TimeStampOfArpTableEntryType TimeStampOfArpTableEntry;  /**< Time when this entry was marked as valid [MAIN_FUNCTION_CYCLES] */
  TcpIp_StatusOfArpTableEntryType StatusOfArpTableEntry;  /**< Status of this ARP entry (INVALID, INPROGRESS, VALID, PROBE) */
  IpBase_AddrInType NetAddrOfArpTableEntry;  /**< Network (IP) address of the neighbor node */
  TcpIp_PhysAddrType PhysAddrOfArpTableEntry;  /**< Physical (MAC) address of the neighbor node */
} TcpIp_ArpTableEntryType;

/**   \brief  type used in TcpIp_AutoIpConfig */
typedef struct sTcpIp_AutoIpConfigType
{
  TcpIp_AnnounceIntervalMsOfAutoIpConfigType AnnounceIntervalMsOfAutoIpConfig;  /**< Announce Interval - Value of configuration parameter TcpIpAutoIpAnnounceInterval [MILLISECONDS] */
  TcpIp_AnnounceNumOfAutoIpConfigType AnnounceNumOfAutoIpConfig;  /**< Announce Number - Value of configuration parameter TcpIpAutoIpAnnounceNum */
  TcpIp_AnnounceWaitMsOfAutoIpConfigType AnnounceWaitMsOfAutoIpConfig;  /**< Announce Wait - Value of configuration parameter TcpIpAutoIpAnnounceWait [MILLISECONDS] */
  TcpIp_DefendIntervalMsOfAutoIpConfigType DefendIntervalMsOfAutoIpConfig;  /**< Defend Interval - Value of configuration parameter TcpIpAutoIpDefendInterval [MILLISECONDS] */
  TcpIp_MaxConflictsOfAutoIpConfigType MaxConflictsOfAutoIpConfig;  /**< Max Number Of Conflicts - Value of configuration parameter TcpIpAutoIpMaxConflicts */
  TcpIp_ProbeMaxMsOfAutoIpConfigType ProbeMaxMsOfAutoIpConfig;  /**< Probe Max Delay - Value of configuration parameter TcpIpAutoIpProbeMax [MILLISECONDS] */
  TcpIp_ProbeMinMsOfAutoIpConfigType ProbeMinMsOfAutoIpConfig;  /**< Probe Min Delay - Value of configuration parameter TcpIpAutoIpProbeMin [MILLISECONDS] */
  TcpIp_ProbeNumOfAutoIpConfigType ProbeNumOfAutoIpConfig;  /**< Probe Number - Value of configuration parameter TcpIpAutoIpProbeNum */
  TcpIp_ProbeWaitMaxMsOfAutoIpConfigType ProbeWaitMaxMsOfAutoIpConfig;  /**< Probe Wait Max - Value of configuration parameter TcpIpAutoIpProbeWaitMax [MILLISECONDS] */
  TcpIp_ProbeWaitMinMsOfAutoIpConfigType ProbeWaitMinMsOfAutoIpConfig;  /**< Init Timeout - Value of configuration parameter TcpIpAutoIpInitTimeout [MILLISECONDS] */
  TcpIp_RateLimitIntervalMsOfAutoIpConfigType RateLimitIntervalMsOfAutoIpConfig;  /**< Rate Limit Interval - Value of configuration parameter TcpIpAutoIpRateLimitInterval [MILLISECONDS] */
  IpV4_LinkLocalAddrCalloutFuncType AddrCalloutFuncOfAutoIpConfig;  /**< - */
} TcpIp_AutoIpConfigType;

/**   \brief  type used in TcpIp_Buf2TxReqMap */
typedef struct sTcpIp_Buf2TxReqMapType
{
  TcpIp_EthBufLenOfBuf2TxReqMapType EthBufLenOfBuf2TxReqMap;  /**< - */
  TcpIp_EthBufIdxNextOfBuf2TxReqMapType EthBufIdxNextOfBuf2TxReqMap;  /**< - */
  TcpIp_SocketDynIdxOfBuf2TxReqMapType SocketDynIdxOfBuf2TxReqMap;  /**< the index of the 0:1 relation pointing to TcpIp_SocketDyn */
  TcpIp_UlTxReqIdxOfBuf2TxReqMapType UlTxReqIdxOfBuf2TxReqMap;  /**< - */
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) EthBufPtrOfBuf2TxReqMap;  /**< - */
} TcpIp_Buf2TxReqMapType;

/**   \brief  type used in TcpIp_DefaultMulticastAddrV4 */
typedef struct sTcpIp_DefaultMulticastAddrV4Type
{
  IpBase_AddrInType NetAddrOfDefaultMulticastAddrV4;  /**< - */
} TcpIp_DefaultMulticastAddrV4Type;

/**   \brief  type used in TcpIp_DefaultUnicastAddrV4 */
typedef struct sTcpIp_DefaultUnicastAddrV4Type
{
  IpBase_AddrInType DefGwAddrOfDefaultUnicastAddrV4;  /**< - */
  IpBase_AddrInType NetAddrOfDefaultUnicastAddrV4;  /**< - */
  IpBase_AddrInType NetMaskOfDefaultUnicastAddrV4;  /**< - */
} TcpIp_DefaultUnicastAddrV4Type;

/**   \brief  type used in TcpIp_DhcpUserOption */
/*! \spec weak type invariant () { 
 * (self.DhcpUserOptionBufferStartIdxOfDhcpUserOption < TcpIp_GetSizeOfDhcpUserOptionBuffer()) &&
 * (self.DhcpUserOptionBufferEndIdxOfDhcpUserOption < TcpIp_GetSizeOfDhcpUserOptionBuffer())
 * } */
typedef struct sTcpIp_DhcpUserOptionType
{
  TcpIp_CodeOfDhcpUserOptionType CodeOfDhcpUserOption;  /**< Code of the user option. */
  TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOptionType DhcpUserOptionBufferEndIdxOfDhcpUserOption;  /**< the end index of the 1:n relation pointing to TcpIp_DhcpUserOptionBuffer */
  TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOptionType DhcpUserOptionBufferLengthOfDhcpUserOption;  /**< the number of relations pointing to TcpIp_DhcpUserOptionBuffer */
  TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOptionType DhcpUserOptionBufferStartIdxOfDhcpUserOption;  /**< the start index of the 1:n relation pointing to TcpIp_DhcpUserOptionBuffer */
  TcpIp_DhcpUserOptionDirectionType DirectionOfDhcpUserOption;  /**< Direction of the user option. */
} TcpIp_DhcpUserOptionType;

/**   \brief  type used in TcpIp_DhcpUserOptionDyn */
typedef struct sTcpIp_DhcpUserOptionDynType
{
  TcpIp_LengthOfDhcpUserOptionDynType LengthOfDhcpUserOptionDyn;
} TcpIp_DhcpUserOptionDynType;

/**   \brief  type used in TcpIp_EthIfCtrl */
/*! \spec weak type invariant () { 
 * (!((self.IpV4CtrlIdxOfEthIfCtrl != TCPIP_NO_IPV4CTRLIDXOFETHIFCTRL)) || (self.IpV4CtrlIdxOfEthIfCtrl < TcpIp_GetSizeOfIpV4Ctrl()))
 * } */
typedef struct sTcpIp_EthIfCtrlType
{
  TcpIp_IpV4CtrlIdxOfEthIfCtrlType IpV4CtrlIdxOfEthIfCtrl;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl */
} TcpIp_EthIfCtrlType;

/**   \brief  type used in TcpIp_FragmentationConfig */
/*! \spec weak type invariant () { 
 * (!(self.ReassemblyBufferDescUsedOfFragmentationConfig) || (self.ReassemblyBufferDescStartIdxOfFragmentationConfig < TcpIp_GetSizeOfReassemblyBufferDesc())) &&
 * (!(self.ReassemblyBufferDescUsedOfFragmentationConfig) || (self.ReassemblyBufferDescEndIdxOfFragmentationConfig < TcpIp_GetSizeOfReassemblyBufferDesc()))
 * } */
typedef struct sTcpIp_FragmentationConfigType
{
  TcpIp_ReassemblyBufferDescUsedOfFragmentationConfigType ReassemblyBufferDescUsedOfFragmentationConfig;  /**< TRUE, if the 0:n relation has 1 relation pointing to TcpIp_ReassemblyBufferDesc */
  TcpIp_MaxPacketSizeOfFragmentationConfigType MaxPacketSizeOfFragmentationConfig;  /**< Reassembly Buffer Size - Value of configuration parameter TcpIpIpMaxReassDgramSize */
  TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType ReassemblyBufferDescEndIdxOfFragmentationConfig;  /**< the end index of the 0:n relation pointing to TcpIp_ReassemblyBufferDesc */
  TcpIp_ReassemblyBufferDescLengthOfFragmentationConfigType ReassemblyBufferDescLengthOfFragmentationConfig;  /**< the number of relations pointing to TcpIp_ReassemblyBufferDesc */
  TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType ReassemblyBufferDescStartIdxOfFragmentationConfig;  /**< the start index of the 0:n relation pointing to TcpIp_ReassemblyBufferDesc */
  TcpIp_ReassemblyTimeoutMsOfFragmentationConfigType ReassemblyTimeoutMsOfFragmentationConfig;  /**< Reassembly Timeout - Value of configuration parameter TcpIpIpReassTimeout [MILLISECONDS] */
} TcpIp_FragmentationConfigType;

/**   \brief  type used in TcpIp_GratuitousArp */
typedef struct sTcpIp_GratuitousArpType
{
  TcpIp_NextTransmissionMsOfGratuitousArpType NextTransmissionMsOfGratuitousArp;  /**< Time of next gratuitous ARP transmission. */
  TcpIp_TransmissionCntOfGratuitousArpType TransmissionCntOfGratuitousArp;  /**< Number of transmitted gratuitous ARPs. */
} TcpIp_GratuitousArpType;

/**   \brief  type used in TcpIp_IpV4Ctrl */
/*! \spec weak type invariant () { 
 * (self.UnicastAddrV4IdxOfIpV4Ctrl < TcpIp_GetSizeOfUnicastAddrV4()) &&
 * (self.Buf2TxReqMapStartIdxOfIpV4Ctrl < TcpIp_GetSizeOfBuf2TxReqMap()) &&
 * (self.Buf2TxReqMapEndIdxOfIpV4Ctrl < TcpIp_GetSizeOfBuf2TxReqMap()) &&
 * (self.LocalAddrV4UnicastIdxOfIpV4Ctrl < TcpIp_GetSizeOfLocalAddrV4()) &&
 * (self.LocalAddrV4BroadcastIdxOfIpV4Ctrl < TcpIp_GetSizeOfLocalAddrV4()) &&
 * (self.AddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl < TcpIp_GetSizeOfAddrAssignmentCfgByPrio()) &&
 * (self.AddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl < TcpIp_GetSizeOfAddrAssignmentCfgByPrio()) &&
 * (!((!(self.AutoIpConfigUsedOfIpV4Ctrl))) || (self.ArpConfigIdxOfIpV4Ctrl < TcpIp_GetSizeOfArpConfig())) &&
 * (!((!(self.AutoIpConfigUsedOfIpV4Ctrl))) || (self.ArpTableEntryStartIdxOfIpV4Ctrl < TcpIp_GetSizeOfArpTableEntry())) &&
 * (!((!(self.AutoIpConfigUsedOfIpV4Ctrl))) || (self.ArpTableEntryEndIdxOfIpV4Ctrl < TcpIp_GetSizeOfArpTableEntry())) &&
 * (!(self.AutoIpConfigUsedOfIpV4Ctrl) || (self.AutoIpConfigIdxOfIpV4Ctrl < TcpIp_GetSizeOfAutoIpConfig())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.GratuitousArpIdxOfIpV4Ctrl < TcpIp_GetSizeOfGratuitousArp())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.FragmentationConfigIdxOfIpV4Ctrl < TcpIp_GetSizeOfFragmentationConfig())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.StaticArpTableIdxOfIpV4Ctrl < TcpIp_GetSizeOfStaticArpTable())) &&
 * (!((!(self.AutoIpConfigUsedOfIpV4Ctrl))) || (self.MulticastAddrV4StartIdxOfIpV4Ctrl < TcpIp_GetSizeOfMulticastAddrV4())) &&
 * (!((!(self.AutoIpConfigUsedOfIpV4Ctrl))) || (self.MulticastAddrV4EndIdxOfIpV4Ctrl < TcpIp_GetSizeOfMulticastAddrV4())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.LlAddrStateIdxOfIpV4Ctrl < TcpIp_GetSizeOfLlAddrState())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.DhcpUserOptionStartIdxOfIpV4Ctrl < TcpIp_GetSizeOfDhcpUserOption())) &&
 * (!((!(self.HwChecksumIcmpOfIpV4Ctrl))) || (self.DhcpUserOptionEndIdxOfIpV4Ctrl < TcpIp_GetSizeOfDhcpUserOption()))
 * } */
typedef struct sTcpIp_IpV4CtrlType
{
  TcpIp_MaxTxMsgSizeOfIpV4CtrlType MaxTxMsgSizeOfIpV4Ctrl;  /**< - */
  TcpIp_MtuTxOfIpV4CtrlType MtuTxOfIpV4Ctrl;  /**< Value of configuration parameter EthIfCtrlMtu */
  TcpIp_AutoIpConfigUsedOfIpV4CtrlType AutoIpConfigUsedOfIpV4Ctrl;  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to TcpIp_AutoIpConfig */
  TcpIp_HwChecksumIcmpOfIpV4CtrlType HwChecksumIcmpOfIpV4Ctrl;  /**< Defines if harware supports calculation of IPv4 ICMP checksum. */
  TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4CtrlType AddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl;  /**< the end index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio */
  TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType AddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl;  /**< the start index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio */
  TcpIp_AddrAssignmentPrioByTypeOfIpV4CtrlType AddrAssignmentPrioByTypeOfIpV4Ctrl;  /**< - */
  TcpIp_ArpConfigIdxOfIpV4CtrlType ArpConfigIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_ArpConfig */
  TcpIp_ArpTableEntryEndIdxOfIpV4CtrlType ArpTableEntryEndIdxOfIpV4Ctrl;  /**< the end index of the 0:n relation pointing to TcpIp_ArpTableEntry */
  TcpIp_ArpTableEntryStartIdxOfIpV4CtrlType ArpTableEntryStartIdxOfIpV4Ctrl;  /**< the start index of the 0:n relation pointing to TcpIp_ArpTableEntry */
  TcpIp_AutoIpConfigIdxOfIpV4CtrlType AutoIpConfigIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_AutoIpConfig */
  TcpIp_Buf2TxReqMapEndIdxOfIpV4CtrlType Buf2TxReqMapEndIdxOfIpV4Ctrl;  /**< the end index of the 1:n relation pointing to TcpIp_Buf2TxReqMap */
  TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType Buf2TxReqMapStartIdxOfIpV4Ctrl;  /**< the start index of the 1:n relation pointing to TcpIp_Buf2TxReqMap */
  TcpIp_DefaultTtlOfIpV4CtrlType DefaultTtlOfIpV4Ctrl;  /**< Default Time To Live - Value of configuration parameter TcpIpIpDefaultTtl */
  TcpIp_DhcpConfigIdxOfIpV4CtrlType DhcpConfigIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_DhcpConfig */
  TcpIp_DhcpStatusIdxOfIpV4CtrlType DhcpStatusIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_DhcpStatus */
  TcpIp_DhcpUserOptionEndIdxOfIpV4CtrlType DhcpUserOptionEndIdxOfIpV4Ctrl;  /**< the end index of the 0:n relation pointing to TcpIp_DhcpUserOption */
  TcpIp_DhcpUserOptionStartIdxOfIpV4CtrlType DhcpUserOptionStartIdxOfIpV4Ctrl;  /**< the start index of the 0:n relation pointing to TcpIp_DhcpUserOption */
  TcpIp_EthIfCtrlIdxOfIpV4CtrlType EthIfCtrlIdxOfIpV4Ctrl;  /**< - */
  TcpIp_FragmentationConfigIdxOfIpV4CtrlType FragmentationConfigIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_FragmentationConfig */
  TcpIp_FramePrioDefaultOfIpV4CtrlType FramePrioDefaultOfIpV4Ctrl;  /**< IP Frame Prio Default - Value of configuration parameter TcpIpIpFramePrioDefault */
  TcpIp_GratuitousArpIdxOfIpV4CtrlType GratuitousArpIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_GratuitousArp */
  TcpIp_LlAddrStateIdxOfIpV4CtrlType LlAddrStateIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_LlAddrState */
  TcpIp_LocalAddrV4BroadcastIdxOfIpV4CtrlType LocalAddrV4BroadcastIdxOfIpV4Ctrl;  /**< the index of the 1:1 relation pointing to TcpIp_LocalAddrV4 */
  TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType LocalAddrV4UnicastIdxOfIpV4Ctrl;  /**< the index of the 1:1 relation pointing to TcpIp_LocalAddrV4 */
  TcpIp_MulticastAddrV4EndIdxOfIpV4CtrlType MulticastAddrV4EndIdxOfIpV4Ctrl;  /**< the end index of the 0:n relation pointing to TcpIp_MulticastAddrV4 */
  TcpIp_MulticastAddrV4StartIdxOfIpV4CtrlType MulticastAddrV4StartIdxOfIpV4Ctrl;  /**< the start index of the 0:n relation pointing to TcpIp_MulticastAddrV4 */
  TcpIp_StaticArpTableIdxOfIpV4CtrlType StaticArpTableIdxOfIpV4Ctrl;  /**< the index of the 0:1 relation pointing to TcpIp_StaticArpTable */
  TcpIp_TypeOfServiceDefaultOfIpV4CtrlType TypeOfServiceDefaultOfIpV4Ctrl;  /**< IP Type Of Service Default - Value of configuration parameter TcpIpIpTypeOfServiceDefault */
  TcpIp_UnicastAddrV4IdxOfIpV4CtrlType UnicastAddrV4IdxOfIpV4Ctrl;  /**< the index of the 1:1 relation pointing to TcpIp_UnicastAddrV4 */
} TcpIp_IpV4CtrlType;

/**   \brief  type used in TcpIp_IpV4CtrlDyn */
typedef struct sTcpIp_IpV4CtrlDynType
{
  TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType ActiveAddrAssignmentMethodOfIpV4CtrlDyn;  /**< - */
  TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType AddrAssignmentReadyChangedOfIpV4CtrlDyn;  /**< - */
  TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn;  /**< - */
  TcpIp_PhysLinkActiveOfIpV4CtrlDynType PhysLinkActiveOfIpV4CtrlDyn;  /**< - */
  TcpIp_StateOfIpV4CtrlDynType StateOfIpV4CtrlDyn;  /**< - */
  IpBase_AddrInType ActiveDefGwAddrOfIpV4CtrlDyn;  /**< - */
  IpBase_AddrInType ActiveNetAddrOfIpV4CtrlDyn;  /**< - */
  IpBase_AddrInType ActiveNetMaskOfIpV4CtrlDyn;  /**< - */
  IpBase_AddrInType LastBcAddrOfIpV4CtrlDyn;  /**< - */
} TcpIp_IpV4CtrlDynType;

/**   \brief  type used in TcpIp_IpV4General */
/*! \spec weak type invariant () { 
 * (!((self.IpV4CtrlDefaultIdxOfIpV4General != TCPIP_NO_IPV4CTRLDEFAULTIDXOFIPV4GENERAL)) || (self.IpV4CtrlDefaultIdxOfIpV4General < TcpIp_GetSizeOfIpV4Ctrl())) &&
 * (!((self.IpV4SocketDynTcpRstIdxOfIpV4General != TCPIP_NO_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL)) || (self.IpV4SocketDynTcpRstIdxOfIpV4General < TcpIp_GetSizeOfIpV4SocketDyn())) &&
 * (!((self.IpV4SocketDynIcmpIdxOfIpV4General != TCPIP_NO_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL)) || (self.IpV4SocketDynIcmpIdxOfIpV4General < TcpIp_GetSizeOfIpV4SocketDyn())) &&
 * (!((self.IpV4SocketDynDhcpIdxOfIpV4General != TCPIP_NO_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL)) || (self.IpV4SocketDynDhcpIdxOfIpV4General < TcpIp_GetSizeOfIpV4SocketDyn()))
 * } */
typedef struct sTcpIp_IpV4GeneralType
{
  TcpIp_IpV4CtrlDefaultIdxOfIpV4GeneralType IpV4CtrlDefaultIdxOfIpV4General;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl */
  TcpIp_IpV4SocketDynDhcpIdxOfIpV4GeneralType IpV4SocketDynDhcpIdxOfIpV4General;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn */
  TcpIp_IpV4SocketDynIcmpIdxOfIpV4GeneralType IpV4SocketDynIcmpIdxOfIpV4General;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn */
  TcpIp_IpV4SocketDynTcpRstIdxOfIpV4GeneralType IpV4SocketDynTcpRstIdxOfIpV4General;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn */
} TcpIp_IpV4GeneralType;

/**   \brief  type used in TcpIp_IpV4SocketDyn */
typedef struct sTcpIp_IpV4SocketDynType
{
  TcpIp_ArpTableEntryIdxOfIpV4SocketDynType ArpTableEntryIdxOfIpV4SocketDyn;  /**< the index of the 0:1 relation pointing to TcpIp_ArpTableEntry */
  TcpIp_EthIfFramePrioOfIpV4SocketDynType EthIfFramePrioOfIpV4SocketDyn;  /**< - */
  TcpIp_FlagsOfIpV4SocketDynType FlagsOfIpV4SocketDyn;  /**< - */
  TcpIp_IpV4CtrlIdxOfIpV4SocketDynType IpV4CtrlIdxOfIpV4SocketDyn;  /**< the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl */
  TcpIp_ProtocolOfIpV4SocketDynType ProtocolOfIpV4SocketDyn;  /**< - */
  TcpIp_TimeToLiveOfIpV4SocketDynType TimeToLiveOfIpV4SocketDyn;  /**< - */
  TcpIp_TxDescriptorProtocolOfIpV4SocketDynType TxDescriptorProtocolOfIpV4SocketDyn;  /**< - */
  TcpIp_TypeOfServiceOfIpV4SocketDynType TypeOfServiceOfIpV4SocketDyn;  /**< - */
  TcpIp_SockAddrBaseType LocSockOfIpV4SocketDyn;
  IpBase_AddrInType PhysDestAddrOfIpV4SocketDyn;  /**< - */
  IpV4_Ip_TransferBlockType TransferBlockOfIpV4SocketDyn;  /**< - */
} TcpIp_IpV4SocketDynType;

/**   \brief  type used in TcpIp_LlAddrState */
typedef struct sTcpIp_LlAddrStateType
{
  TcpIp_MsecCntOfLlAddrStateType MsecCntOfLlAddrState;  /**< - */
  TcpIp_WaitUntilTimeOfLlAddrStateType WaitUntilTimeOfLlAddrState;  /**< - */
  TcpIp_AddrConflictTimeoutOfLlAddrStateType AddrConflictTimeoutOfLlAddrState;  /**< - */
  TcpIp_ProbeNumOfLlAddrStateType ProbeNumOfLlAddrState;  /**< - */
  TcpIp_AddrConflictOfLlAddrStateType AddrConflictOfLlAddrState;  /**< - */
  TcpIp_AnnStateOfLlAddrStateType AnnStateOfLlAddrState;  /**< - */
  TcpIp_AnnounceNumOfLlAddrStateType AnnounceNumOfLlAddrState;  /**< - */
  TcpIp_ConflictsNumOfLlAddrStateType ConflictsNumOfLlAddrState;  /**< - */
  TcpIp_ProbeNumSinceConfOfLlAddrStateType ProbeNumSinceConfOfLlAddrState;  /**< - */
  TcpIp_ProbeStateOfLlAddrStateType ProbeStateOfLlAddrState;  /**< - */
  TcpIp_StateOfLlAddrStateType StateOfLlAddrState;  /**< - */
  IpBase_AddrInType AddrFoundOfLlAddrState;  /**< - */
  IpBase_AddrInType NetAddrCandOfLlAddrState;  /**< - */
} TcpIp_LlAddrStateType;

/**   \brief  type used in TcpIp_LocalAddr */
typedef struct sTcpIp_LocalAddrType
{
  TcpIp_AssignmentStateOfLocalAddrType AssignmentStateOfLocalAddr;  /**< - */
} TcpIp_LocalAddrType;

/**   \brief  type used in TcpIp_LocalAddrV4 */
/*! \spec weak type invariant () { 
 * (self.IpV4CtrlIdxOfLocalAddrV4 < TcpIp_GetSizeOfIpV4Ctrl()) &&
 * (!((self.UnicastAddrV4IdxOfLocalAddrV4 != TCPIP_NO_UNICASTADDRV4IDXOFLOCALADDRV4)) || (self.UnicastAddrV4IdxOfLocalAddrV4 < TcpIp_GetSizeOfUnicastAddrV4())) &&
 * (!((self.MulticastAddrV4IdxOfLocalAddrV4 != TCPIP_NO_MULTICASTADDRV4IDXOFLOCALADDRV4)) || (self.MulticastAddrV4IdxOfLocalAddrV4 < TcpIp_GetSizeOfMulticastAddrV4()))
 * } */
typedef struct sTcpIp_LocalAddrV4Type
{
  TcpIp_IpV4CtrlIdxOfLocalAddrV4Type IpV4CtrlIdxOfLocalAddrV4;  /**< the index of the 1:1 relation pointing to TcpIp_IpV4Ctrl */
  TcpIp_MulticastAddrV4IdxOfLocalAddrV4Type MulticastAddrV4IdxOfLocalAddrV4;  /**< the index of the 0:1 relation pointing to TcpIp_MulticastAddrV4 */
  TcpIp_UnicastAddrV4IdxOfLocalAddrV4Type UnicastAddrV4IdxOfLocalAddrV4;  /**< the index of the 0:1 relation pointing to TcpIp_UnicastAddrV4 */
} TcpIp_LocalAddrV4Type;

/**   \brief  type used in TcpIp_MulticastAddrV4 */
/*! \spec weak type invariant () { 
 * (self.DefaultMulticastAddrV4IdxOfMulticastAddrV4 < TcpIp_GetSizeOfDefaultMulticastAddrV4()) &&
 * (self.LocalAddrV4IdxOfMulticastAddrV4 < TcpIp_GetSizeOfLocalAddrV4())
 * } */
typedef struct sTcpIp_MulticastAddrV4Type
{
  TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4Type DefaultMulticastAddrV4IdxOfMulticastAddrV4;  /**< the index of the 1:1 relation pointing to TcpIp_DefaultMulticastAddrV4 */
  TcpIp_LocalAddrV4IdxOfMulticastAddrV4Type LocalAddrV4IdxOfMulticastAddrV4;  /**< the index of the 1:1 relation pointing to TcpIp_LocalAddrV4 */
} TcpIp_MulticastAddrV4Type;

/**   \brief  type used in TcpIp_MulticastAddrV4Requested */
typedef struct sTcpIp_MulticastAddrV4RequestedType
{
  IpBase_AddrInType NetAddrOfMulticastAddrV4Requested;  /**< - */
} TcpIp_MulticastAddrV4RequestedType;

/**   \brief  type used in TcpIp_PhysAddrConfig */
typedef struct sTcpIp_PhysAddrConfigType
{
  TcpIp_PhysAddrTableChgCbkType ChgFuncPtrOfPhysAddrConfig;  /**< - */
  TcpIp_PhysAddrTableChgDiscardedCbkType ChgDiscardedFuncPtrOfPhysAddrConfig;  /**< - */
} TcpIp_PhysAddrConfigType;

/**   \brief  type used in TcpIp_ReassemblyBufferDesc */
/*! \spec weak type invariant () { 
 * (self.ReassemblyBufferStartIdxOfReassemblyBufferDesc < TcpIp_GetSizeOfReassemblyBuffer()) &&
 * (self.ReassemblyBufferEndIdxOfReassemblyBufferDesc < TcpIp_GetSizeOfReassemblyBuffer())
 * } */
typedef struct sTcpIp_ReassemblyBufferDescType
{
  TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDescType ReassemblyBufferEndIdxOfReassemblyBufferDesc;  /**< the end index of the 1:n relation pointing to TcpIp_ReassemblyBuffer */
  TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType ReassemblyBufferStartIdxOfReassemblyBufferDesc;  /**< the start index of the 1:n relation pointing to TcpIp_ReassemblyBuffer */
} TcpIp_ReassemblyBufferDescType;

/**   \brief  type used in TcpIp_SocketDyn */
typedef struct sTcpIp_SocketDynType
{
  TcpIp_ListenActiveConnStatOfSocketDynType ListenActiveConnStatOfSocketDyn;  /**< Current state of the socket */
  TcpIp_LocalAddrBindIdxOfSocketDynType LocalAddrBindIdxOfSocketDyn;  /**< the index of the 0:1 relation pointing to TcpIp_LocalAddr */
  TcpIp_SocketOwnerConfigIdxOfSocketDynType SocketOwnerConfigIdxOfSocketDyn;  /**< the index of the 0:1 relation pointing to TcpIp_SocketOwnerConfig */
  TcpIp_TxBufRequestedOfSocketDynType TxBufRequestedOfSocketDyn;  /**< TX buffer request semaphore */
  TcpIp_TxIpAddrIdxOfSocketDynType TxIpAddrIdxOfSocketDyn;  /**< Index of local IPxV address that is used for transmission */
  TcpIp_SockAddrBaseType LocSockOfSocketDyn;  /**< IP address and port of the local host */
  TcpIp_SockAddrBaseType RemSockOfSocketDyn;  /**< IP address and port of the remote host */
} TcpIp_SocketDynType;

/**   \brief  type used in TcpIp_SocketOwnerConfig */
typedef struct sTcpIp_SocketOwnerConfigType
{
  TcpIp_SocketOwnerCopyTxDataDynType CopyTxDataDynFuncPtrOfSocketOwnerConfig;  /**< [User]_CopyTxDataDyn Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.) */
  TcpIp_SocketOwnerCopyTxDataType CopyTxDataFuncPtrOfSocketOwnerConfig;  /**< [User]_CopyTxData Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.) */
  TcpIp_SocketOwnerDhcpEventType DhcpEventFuncPtrOfSocketOwnerConfig;  /**< Callout triggered on reception and transmission of client DHCP messages. */
  TcpIp_SocketOwnerLocalIpAddrAssignmentChgType LocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig;  /**< - */
  TcpIp_SocketOwnerRxIndicationType RxIndicationFuncPtrOfSocketOwnerConfig;  /**< [User]_RxIndication Callback Function. (required for socket owner that recieves packets.) */
  TcpIp_SocketOwnerTcpAcceptedType TcpAcceptedFuncPtrOfSocketOwnerConfig;  /**< [User]_TcpAccepted Callback Function. (only required if socker passively accepts TCP connections.) */
  TcpIp_SocketOwnerTcpConnectedType TcpConnectedFuncPtrOfSocketOwnerConfig;  /**< [User]_TcpConnected Callback Function. (only required if socker owner actively opens TCP connections.) */
  TcpIp_SocketOwnerTcpIpEventType TcpIpEventFuncPtrOfSocketOwnerConfig;  /**< [User]_TcpIpEvent Callback Function. (required for every socket owner) */
  TcpIp_SocketOwnerTlsValidationResultType TlsValidationResultFuncPtrOfSocketOwnerConfig;  /**< [User]_TlsValidationResult Callback Function. */
  TcpIp_SocketOwnerTxConfirmationType TxConfirmationFuncPtrOfSocketOwnerConfig;  /**< [User]_TxConfirmation Callback Function. (optional for every socket owner) */
} TcpIp_SocketOwnerConfigType;

/**   \brief  type used in TcpIp_SocketUdpDyn */
typedef struct sTcpIp_SocketUdpDynType
{
  TcpIp_TxReqElemListIdxOfSocketUdpDynType TxReqElemListIdxOfSocketUdpDyn;  /**< the index of the 0:1 relation pointing to TcpIp_TxReqElemList */
  TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType TxRetrQueueMaxNumOfSocketUdpDyn;  /**< Maximum number of TX retry queue elements for the socket. */
  TcpIp_IpTxRequestDescriptorType IpTxRequestDescriptorOfSocketUdpDyn;  /**< TX request descriptor required for the IP layer */
  P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) TxReqIpBufPtrOfSocketUdpDyn;  /**< Pointer to the provided TX buffer of the IP layer */
  TcpIp_DListType TxRetrQueueOfSocketUdpDyn;  /**< TX retry queue */
} TcpIp_SocketUdpDynType;

/**   \brief  type used in TcpIp_StaticArpEntry */
typedef struct sTcpIp_StaticArpEntryType
{
  IpBase_AddrInType IpAddrOfStaticArpEntry;  /**< - */
  TcpIp_PhysAddrType PhysAddrOfStaticArpEntry;  /**< - */
} TcpIp_StaticArpEntryType;

/**   \brief  type used in TcpIp_StaticArpTable */
/*! \spec weak type invariant () { 
 * (self.StaticArpEntryStartIdxOfStaticArpTable < TcpIp_GetSizeOfStaticArpEntry()) &&
 * (self.StaticArpEntryEndIdxOfStaticArpTable < TcpIp_GetSizeOfStaticArpEntry())
 * } */
typedef struct sTcpIp_StaticArpTableType
{
  TcpIp_StaticArpEntryEndIdxOfStaticArpTableType StaticArpEntryEndIdxOfStaticArpTable;  /**< the end index of the 1:n relation pointing to TcpIp_StaticArpEntry */
  TcpIp_StaticArpEntryStartIdxOfStaticArpTableType StaticArpEntryStartIdxOfStaticArpTable;  /**< the start index of the 1:n relation pointing to TcpIp_StaticArpEntry */
} TcpIp_StaticArpTableType;

/**   \brief  type used in TcpIp_StaticUnicastAddrV4Requested */
typedef struct sTcpIp_StaticUnicastAddrV4RequestedType
{
  IpBase_AddrInType DefGwAddrOfStaticUnicastAddrV4Requested;  /**< - */
  IpBase_AddrInType NetAddrOfStaticUnicastAddrV4Requested;  /**< - */
  IpBase_AddrInType NetMaskOfStaticUnicastAddrV4Requested;  /**< - */
} TcpIp_StaticUnicastAddrV4RequestedType;

/**   \brief  type used in TcpIp_TxReqElem */
typedef struct sTcpIp_TxReqElemType
{
  TcpIp_TxReqElemDataLenByteOfTxReqElemType TxReqElemDataLenByteOfTxReqElem;  /**< - */
  TcpIp_TxReqElemTransmittedOfTxReqElemType TxReqElemTransmittedOfTxReqElem;  /**< - */
} TcpIp_TxReqElemType;

/**   \brief  type used in TcpIp_TxReqElemList */
/*! \spec weak type invariant () { 
 * (self.TxReqElemStartIdxOfTxReqElemList < TcpIp_GetSizeOfTxReqElem()) &&
 * (self.TxReqElemEndIdxOfTxReqElemList < TcpIp_GetSizeOfTxReqElem())
 * } */
typedef struct sTcpIp_TxReqElemListType
{
  TcpIp_TxReqElemEndIdxOfTxReqElemListType TxReqElemEndIdxOfTxReqElemList;  /**< the end index of the 1:n relation pointing to TcpIp_TxReqElem */
  TcpIp_TxReqElemLengthOfTxReqElemListType TxReqElemLengthOfTxReqElemList;  /**< the number of relations pointing to TcpIp_TxReqElem */
  TcpIp_TxReqElemStartIdxOfTxReqElemListType TxReqElemStartIdxOfTxReqElemList;  /**< the start index of the 1:n relation pointing to TcpIp_TxReqElem */
} TcpIp_TxReqElemListType;

/**   \brief  type used in TcpIp_TxReqElemListDyn */
typedef struct sTcpIp_TxReqElemListDynType
{
  TcpIp_FillNumOfTxReqElemListDynType FillNumOfTxReqElemListDyn;  /**< Number of elements currently stored in TX request ring buffer */
  TcpIp_ReadPosOfTxReqElemListDynType ReadPosOfTxReqElemListDyn;  /**< Read position of TX request ring buffer */
  TcpIp_SocketUdpDynIdxOfTxReqElemListDynType SocketUdpDynIdxOfTxReqElemListDyn;  /**< the index of the 0:1 relation pointing to TcpIp_SocketUdpDyn */
  TcpIp_WritePosOfTxReqElemListDynType WritePosOfTxReqElemListDyn;  /**< Write position in TX request ring buffer */
} TcpIp_TxReqElemListDynType;

/**   \brief  type used in TcpIp_UnicastAddrV4 */
/*! \spec weak type invariant () { 
 * (!((self.DefaultUnicastAddrV4IdxOfUnicastAddrV4 != TCPIP_NO_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4)) || (self.DefaultUnicastAddrV4IdxOfUnicastAddrV4 < TcpIp_GetSizeOfDefaultUnicastAddrV4())) &&
 * (!((self.StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4 != TCPIP_NO_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4)) || (self.StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4 < TcpIp_GetSizeOfStaticUnicastAddrV4Requested()))
 * } */
typedef struct sTcpIp_UnicastAddrV4Type
{
  TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type DefaultUnicastAddrV4IdxOfUnicastAddrV4;  /**< the index of the 0:1 relation pointing to TcpIp_DefaultUnicastAddrV4 */
  TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4;  /**< the index of the 0:1 relation pointing to TcpIp_StaticUnicastAddrV4Requested */
} TcpIp_UnicastAddrV4Type;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCSymbolicStructTypes  TcpIp Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to TcpIp_ArpTableEntry */
typedef struct TcpIp_ArpTableEntryStructSTag
{
  TcpIp_ArpTableEntryType TcpIpCtrl_Vlan10[10];
} TcpIp_ArpTableEntryStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_Buf2TxReqMap */
typedef struct TcpIp_Buf2TxReqMapStructSTag
{
  TcpIp_Buf2TxReqMapType EthCtrlConfig[4];
} TcpIp_Buf2TxReqMapStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_IpV4CtrlDyn */
typedef struct TcpIp_IpV4CtrlDynStructSTag
{
  TcpIp_IpV4CtrlDynType TcpIpCtrl_Vlan10;
} TcpIp_IpV4CtrlDynStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_IpV4SocketDyn */
typedef struct TcpIp_IpV4SocketDynStructSTag
{
  TcpIp_IpV4SocketDynType UDP[2];
} TcpIp_IpV4SocketDynStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_LocalAddr */
typedef struct TcpIp_LocalAddrStructSTag
{
  TcpIp_LocalAddrType TcpIpLocalAddr_NE_Fixed_10_10_7_33;
  TcpIp_LocalAddrType TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1;
  TcpIp_LocalAddrType TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast;
} TcpIp_LocalAddrStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_SocketDyn */
typedef struct TcpIp_SocketDynStructSTag
{
  TcpIp_SocketDynType UDP[2];
} TcpIp_SocketDynStructSType;

/**   \brief  type to be used as symbolic data element access to TcpIp_StaticUnicastAddrV4Requested */
typedef struct TcpIp_StaticUnicastAddrV4RequestedStructSTag
{
  TcpIp_StaticUnicastAddrV4RequestedType TcpIpLocalAddr_NE_Fixed_10_10_7_33;
} TcpIp_StaticUnicastAddrV4RequestedStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCUnionIndexAndSymbolTypes  TcpIp Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access TcpIp_ArpTableEntry in an index and symbol based style. */
typedef union TcpIp_ArpTableEntryUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_ArpTableEntryType raw[10];
  TcpIp_ArpTableEntryStructSType str;
} TcpIp_ArpTableEntryUType;

/**   \brief  type to access TcpIp_Buf2TxReqMap in an index and symbol based style. */
typedef union TcpIp_Buf2TxReqMapUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_Buf2TxReqMapType raw[4];
  TcpIp_Buf2TxReqMapStructSType str;
} TcpIp_Buf2TxReqMapUType;

/**   \brief  type to access TcpIp_IpV4CtrlDyn in an index and symbol based style. */
typedef union TcpIp_IpV4CtrlDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_IpV4CtrlDynType raw[1];
  TcpIp_IpV4CtrlDynStructSType str;
} TcpIp_IpV4CtrlDynUType;

/**   \brief  type to access TcpIp_IpV4SocketDyn in an index and symbol based style. */
typedef union TcpIp_IpV4SocketDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_IpV4SocketDynType raw[2];
  TcpIp_IpV4SocketDynStructSType str;
} TcpIp_IpV4SocketDynUType;

/**   \brief  type to access TcpIp_LocalAddr in an index and symbol based style. */
typedef union TcpIp_LocalAddrUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_LocalAddrType raw[3];
  TcpIp_LocalAddrStructSType str;
} TcpIp_LocalAddrUType;

/**   \brief  type to access TcpIp_SocketDyn in an index and symbol based style. */
typedef union TcpIp_SocketDynUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_SocketDynType raw[2];
  TcpIp_SocketDynStructSType str;
} TcpIp_SocketDynUType;

/**   \brief  type to access TcpIp_StaticUnicastAddrV4Requested in an index and symbol based style. */
typedef union TcpIp_StaticUnicastAddrV4RequestedUTag
{  /* PRQA S 0750 */  /* MD_CSL_Union */
  TcpIp_StaticUnicastAddrV4RequestedType raw[1];
  TcpIp_StaticUnicastAddrV4RequestedStructSType str;
} TcpIp_StaticUnicastAddrV4RequestedUType;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCRootPointerTypes  TcpIp Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to TcpIp_AddrAssignmentCfgByPrio */
typedef P2CONST(TcpIp_AddrAssignmentCfgByPrioType, TYPEDEF, TCPIP_CONST) TcpIp_AddrAssignmentCfgByPrioPtrType;

/**   \brief  type used to point to TcpIp_ArpConfig */
typedef P2CONST(TcpIp_ArpConfigType, TYPEDEF, TCPIP_CONST) TcpIp_ArpConfigPtrType;

/**   \brief  type used to point to TcpIp_ArpTableEntry */
typedef P2VAR(TcpIp_ArpTableEntryType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_ArpTableEntryPtrType;

/**   \brief  type used to point to TcpIp_PhysAddrOfArpTableEntry */
typedef P2VAR(TcpIp_PhysAddrType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_PhysAddrOfArpTableEntryPtrType;

/**   \brief  type used to point to TcpIp_AutoIpConfig */
typedef P2CONST(TcpIp_AutoIpConfigType, TYPEDEF, TCPIP_CONST) TcpIp_AutoIpConfigPtrType;

/**   \brief  type used to point to TcpIp_Buf2TxReqMap */
typedef P2VAR(TcpIp_Buf2TxReqMapType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_Buf2TxReqMapPtrType;

/**   \brief  type used to point to TcpIp_DefaultMulticastAddrV4 */
typedef P2CONST(TcpIp_DefaultMulticastAddrV4Type, TYPEDEF, TCPIP_CONST) TcpIp_DefaultMulticastAddrV4PtrType;

/**   \brief  type used to point to TcpIp_DefaultUnicastAddrV4 */
typedef P2CONST(TcpIp_DefaultUnicastAddrV4Type, TYPEDEF, TCPIP_CONST) TcpIp_DefaultUnicastAddrV4PtrType;

/**   \brief  type used to point to TcpIp_DhcpUserOption */
typedef P2CONST(TcpIp_DhcpUserOptionType, TYPEDEF, TCPIP_CONST) TcpIp_DhcpUserOptionPtrType;

/**   \brief  type used to point to TcpIp_DhcpUserOptionBuffer */
typedef P2VAR(TcpIp_DhcpUserOptionBufferType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_DhcpUserOptionBufferPtrType;

/**   \brief  type used to point to TcpIp_DhcpUserOptionDyn */
typedef P2VAR(TcpIp_DhcpUserOptionDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_DhcpUserOptionDynPtrType;

/**   \brief  type used to point to TcpIp_DuplicateAddrDetectionFctPtr */
typedef P2CONST(TcpIp_DuplicateAddrDetectionCbkType, TYPEDEF, TCPIP_CONST) TcpIp_DuplicateAddrDetectionFctPtrPtrType;

/**   \brief  type used to point to TcpIp_EthIfCtrl */
typedef P2CONST(TcpIp_EthIfCtrlType, TYPEDEF, TCPIP_CONST) TcpIp_EthIfCtrlPtrType;

/**   \brief  type used to point to TcpIp_FragmentationConfig */
typedef P2CONST(TcpIp_FragmentationConfigType, TYPEDEF, TCPIP_CONST) TcpIp_FragmentationConfigPtrType;

/**   \brief  type used to point to TcpIp_GratuitousArp */
typedef P2VAR(TcpIp_GratuitousArpType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_GratuitousArpPtrType;

/**   \brief  type used to point to TcpIp_IcmpMsgHandlerCbkFctPtr */
typedef P2CONST(TcpIp_IcmpMsgHandlerCbkType, TYPEDEF, TCPIP_CONST) TcpIp_IcmpMsgHandlerCbkFctPtrPtrType;

/**   \brief  type used to point to TcpIp_IpV4Ctrl */
typedef P2CONST(TcpIp_IpV4CtrlType, TYPEDEF, TCPIP_CONST) TcpIp_IpV4CtrlPtrType;

/**   \brief  type used to point to TcpIp_IpV4CtrlDyn */
typedef P2VAR(TcpIp_IpV4CtrlDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_IpV4CtrlDynPtrType;

/**   \brief  type used to point to TcpIp_IpV4General */
typedef P2CONST(TcpIp_IpV4GeneralType, TYPEDEF, TCPIP_CONST) TcpIp_IpV4GeneralPtrType;

/**   \brief  type used to point to TcpIp_IpV4SocketDyn */
typedef P2VAR(TcpIp_IpV4SocketDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_IpV4SocketDynPtrType;

/**   \brief  type used to point to TcpIp_LocSockOfIpV4SocketDyn */
typedef P2VAR(TcpIp_SockAddrBaseType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_LocSockOfIpV4SocketDynPtrType;

/**   \brief  type used to point to TcpIp_TransferBlockOfIpV4SocketDyn */
typedef P2VAR(IpV4_Ip_TransferBlockType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_TransferBlockOfIpV4SocketDynPtrType;

/**   \brief  type used to point to TcpIp_LlAddrState */
typedef P2VAR(TcpIp_LlAddrStateType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_LlAddrStatePtrType;

/**   \brief  type used to point to TcpIp_LocalAddr */
typedef P2VAR(TcpIp_LocalAddrType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_LocalAddrPtrType;

/**   \brief  type used to point to TcpIp_LocalAddrV4 */
typedef P2CONST(TcpIp_LocalAddrV4Type, TYPEDEF, TCPIP_CONST) TcpIp_LocalAddrV4PtrType;

/**   \brief  type used to point to TcpIp_MulticastAddrV4 */
typedef P2CONST(TcpIp_MulticastAddrV4Type, TYPEDEF, TCPIP_CONST) TcpIp_MulticastAddrV4PtrType;

/**   \brief  type used to point to TcpIp_MulticastAddrV4Requested */
typedef P2VAR(TcpIp_MulticastAddrV4RequestedType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_MulticastAddrV4RequestedPtrType;

/**   \brief  type used to point to TcpIp_PhysAddrConfig */
typedef P2CONST(TcpIp_PhysAddrConfigType, TYPEDEF, TCPIP_CONST) TcpIp_PhysAddrConfigPtrType;

/**   \brief  type used to point to TcpIp_RandomNumberFctPtr */
typedef P2CONST(TcpIp_GetRandomNumberType, TYPEDEF, TCPIP_CONST) TcpIp_RandomNumberFctPtrPtrType;

/**   \brief  type used to point to TcpIp_ReassemblyBuffer */
typedef P2VAR(TcpIp_ReassemblyBufferType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_ReassemblyBufferPtrType;

/**   \brief  type used to point to TcpIp_ReassemblyBufferDesc */
typedef P2CONST(TcpIp_ReassemblyBufferDescType, TYPEDEF, TCPIP_CONST) TcpIp_ReassemblyBufferDescPtrType;

/**   \brief  type used to point to TcpIp_ReassemblyBufferDescDyn */
typedef P2VAR(IpV4_Ip_ReassemblyBufferDescType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_ReassemblyBufferDescDynPtrType;

/**   \brief  type used to point to TcpIp_SocketDyn */
typedef P2VAR(TcpIp_SocketDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_SocketDynPtrType;

/**   \brief  type used to point to TcpIp_LocSockOfSocketDyn */
typedef P2VAR(TcpIp_SockAddrBaseType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_LocSockOfSocketDynPtrType;

/**   \brief  type used to point to TcpIp_RemSockOfSocketDyn */
typedef P2VAR(TcpIp_SockAddrBaseType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_RemSockOfSocketDynPtrType;

/**   \brief  type used to point to TcpIp_SocketOwnerConfig */
typedef P2CONST(TcpIp_SocketOwnerConfigType, TYPEDEF, TCPIP_CONST) TcpIp_SocketOwnerConfigPtrType;

/**   \brief  type used to point to TcpIp_SocketUdpDyn */
typedef P2VAR(TcpIp_SocketUdpDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_SocketUdpDynPtrType;

/**   \brief  type used to point to TcpIp_IpTxRequestDescriptorOfSocketUdpDyn */
typedef P2VAR(TcpIp_IpTxRequestDescriptorType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_IpTxRequestDescriptorOfSocketUdpDynPtrType;

/**   \brief  type used to point to TcpIp_TxRetrQueueOfSocketUdpDyn */
typedef P2VAR(TcpIp_DListType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_TxRetrQueueOfSocketUdpDynPtrType;

/**   \brief  type used to point to TcpIp_PhysAddrOfStaticArpEntry */
typedef P2CONST(TcpIp_PhysAddrType, TYPEDEF, TCPIP_CONST) TcpIp_PhysAddrOfStaticArpEntryPtrType;

/**   \brief  type used to point to TcpIp_StaticArpEntry */
typedef P2CONST(TcpIp_StaticArpEntryType, TYPEDEF, TCPIP_CONST) TcpIp_StaticArpEntryPtrType;

/**   \brief  type used to point to TcpIp_StaticArpTable */
typedef P2CONST(TcpIp_StaticArpTableType, TYPEDEF, TCPIP_CONST) TcpIp_StaticArpTablePtrType;

/**   \brief  type used to point to TcpIp_StaticUnicastAddrV4Requested */
typedef P2VAR(TcpIp_StaticUnicastAddrV4RequestedType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_StaticUnicastAddrV4RequestedPtrType;

/**   \brief  type used to point to TcpIp_TxReqElem */
typedef P2VAR(TcpIp_TxReqElemType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_TxReqElemPtrType;

/**   \brief  type used to point to TcpIp_TxReqElemList */
typedef P2CONST(TcpIp_TxReqElemListType, TYPEDEF, TCPIP_CONST) TcpIp_TxReqElemListPtrType;

/**   \brief  type used to point to TcpIp_TxReqElemListDyn */
typedef P2VAR(TcpIp_TxReqElemListDynType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_TxReqElemListDynPtrType;

/**   \brief  type used to point to TcpIp_UdpTxRetryQueueElementChain */
typedef P2VAR(TcpIp_DListNodeType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElementChainPtrType;

/**   \brief  type used to point to TcpIp_UdpTxRetryQueueElements */
typedef P2VAR(TcpIp_Udp_RetryQueueElementType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElementsPtrType;

/**   \brief  type used to point to TcpIp_UdpTxRetryQueuePoolDesc */
typedef P2VAR(TcpIp_DListDescType, TYPEDEF, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueuePoolDescPtrType;

/**   \brief  type used to point to TcpIp_UnicastAddrV4 */
typedef P2CONST(TcpIp_UnicastAddrV4Type, TYPEDEF, TCPIP_CONST) TcpIp_UnicastAddrV4PtrType;

/** 
  \}
*/ 

/** 
  \defgroup  TcpIpPCRootValueTypes  TcpIp Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in TcpIp_PCConfig */
typedef struct sTcpIp_PCConfigType
{
  TcpIp_ArpConfigPtrType ArpConfigOfPCConfig;  /**< the pointer to TcpIp_ArpConfig */
  TcpIp_ArpTableEntryPtrType ArpTableEntryOfPCConfig;  /**< the pointer to TcpIp_ArpTableEntry */
  TcpIp_AutoIpConfigPtrType AutoIpConfigOfPCConfig;  /**< the pointer to TcpIp_AutoIpConfig */
  TcpIp_DefaultMulticastAddrV4PtrType DefaultMulticastAddrV4OfPCConfig;  /**< the pointer to TcpIp_DefaultMulticastAddrV4 */
  TcpIp_DefaultUnicastAddrV4PtrType DefaultUnicastAddrV4OfPCConfig;  /**< the pointer to TcpIp_DefaultUnicastAddrV4 */
  TcpIp_DhcpUserOptionPtrType DhcpUserOptionOfPCConfig;  /**< the pointer to TcpIp_DhcpUserOption */
  TcpIp_DhcpUserOptionBufferPtrType DhcpUserOptionBufferOfPCConfig;  /**< the pointer to TcpIp_DhcpUserOptionBuffer */
  TcpIp_DhcpUserOptionDynPtrType DhcpUserOptionDynOfPCConfig;  /**< the pointer to TcpIp_DhcpUserOptionDyn */
  TcpIp_FragmentationConfigPtrType FragmentationConfigOfPCConfig;  /**< the pointer to TcpIp_FragmentationConfig */
  TcpIp_GratuitousArpPtrType GratuitousArpOfPCConfig;  /**< the pointer to TcpIp_GratuitousArp */
  TcpIp_LlAddrStatePtrType LlAddrStateOfPCConfig;  /**< the pointer to TcpIp_LlAddrState */
  TcpIp_MulticastAddrV4PtrType MulticastAddrV4OfPCConfig;  /**< the pointer to TcpIp_MulticastAddrV4 */
  TcpIp_MulticastAddrV4RequestedPtrType MulticastAddrV4RequestedOfPCConfig;  /**< the pointer to TcpIp_MulticastAddrV4Requested */
  TcpIp_PhysAddrConfigPtrType PhysAddrConfigOfPCConfig;  /**< the pointer to TcpIp_PhysAddrConfig */
  TcpIp_ReassemblyBufferPtrType ReassemblyBufferOfPCConfig;  /**< the pointer to TcpIp_ReassemblyBuffer */
  TcpIp_ReassemblyBufferDescPtrType ReassemblyBufferDescOfPCConfig;  /**< the pointer to TcpIp_ReassemblyBufferDesc */
  TcpIp_ReassemblyBufferDescDynPtrType ReassemblyBufferDescDynOfPCConfig;  /**< the pointer to TcpIp_ReassemblyBufferDescDyn */
  TcpIp_StaticArpEntryPtrType StaticArpEntryOfPCConfig;  /**< the pointer to TcpIp_StaticArpEntry */
  TcpIp_StaticArpTablePtrType StaticArpTableOfPCConfig;  /**< the pointer to TcpIp_StaticArpTable */
  TcpIp_StaticUnicastAddrV4RequestedPtrType StaticUnicastAddrV4RequestedOfPCConfig;  /**< the pointer to TcpIp_StaticUnicastAddrV4Requested */
  TcpIp_TxReqElemPtrType TxReqElemOfPCConfig;  /**< the pointer to TcpIp_TxReqElem */
  TcpIp_TxReqElemListPtrType TxReqElemListOfPCConfig;  /**< the pointer to TcpIp_TxReqElemList */
  TcpIp_TxReqElemListDynPtrType TxReqElemListDynOfPCConfig;  /**< the pointer to TcpIp_TxReqElemListDyn */
  TcpIp_UdpTxRetryQueueElementChainPtrType UdpTxRetryQueueElementChainOfPCConfig;  /**< the pointer to TcpIp_UdpTxRetryQueueElementChain */
  TcpIp_UdpTxRetryQueueElementsPtrType UdpTxRetryQueueElementsOfPCConfig;  /**< the pointer to TcpIp_UdpTxRetryQueueElements */
  TcpIp_UdpTxRetryQueuePoolDescPtrType UdpTxRetryQueuePoolDescOfPCConfig;  /**< the pointer to TcpIp_UdpTxRetryQueuePoolDesc */
  TcpIp_UnicastAddrV4PtrType UnicastAddrV4OfPCConfig;  /**< the pointer to TcpIp_UnicastAddrV4 */
  TcpIp_SizeOfArpConfigType SizeOfArpConfigOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_ArpConfig */
  TcpIp_SizeOfArpTableEntryType SizeOfArpTableEntryOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_ArpTableEntry */
  TcpIp_SizeOfAutoIpConfigType SizeOfAutoIpConfigOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_AutoIpConfig */
  TcpIp_SizeOfDefaultMulticastAddrV4Type SizeOfDefaultMulticastAddrV4OfPCConfig;  /**< the number of accomplishable value elements in TcpIp_DefaultMulticastAddrV4 */
  TcpIp_SizeOfDefaultUnicastAddrV4Type SizeOfDefaultUnicastAddrV4OfPCConfig;  /**< the number of accomplishable value elements in TcpIp_DefaultUnicastAddrV4 */
  TcpIp_SizeOfDhcpUserOptionType SizeOfDhcpUserOptionOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_DhcpUserOption */
  TcpIp_SizeOfDhcpUserOptionBufferType SizeOfDhcpUserOptionBufferOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_DhcpUserOptionBuffer */
  TcpIp_SizeOfFragmentationConfigType SizeOfFragmentationConfigOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_FragmentationConfig */
  TcpIp_SizeOfGratuitousArpType SizeOfGratuitousArpOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_GratuitousArp */
  TcpIp_SizeOfLlAddrStateType SizeOfLlAddrStateOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_LlAddrState */
  TcpIp_SizeOfMulticastAddrV4Type SizeOfMulticastAddrV4OfPCConfig;  /**< the number of accomplishable value elements in TcpIp_MulticastAddrV4 */
  TcpIp_SizeOfPhysAddrConfigType SizeOfPhysAddrConfigOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_PhysAddrConfig */
  TcpIp_SizeOfReassemblyBufferType SizeOfReassemblyBufferOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_ReassemblyBuffer */
  TcpIp_SizeOfReassemblyBufferDescType SizeOfReassemblyBufferDescOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_ReassemblyBufferDesc */
  TcpIp_SizeOfStaticArpEntryType SizeOfStaticArpEntryOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_StaticArpEntry */
  TcpIp_SizeOfStaticArpTableType SizeOfStaticArpTableOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_StaticArpTable */
  TcpIp_SizeOfStaticUnicastAddrV4RequestedType SizeOfStaticUnicastAddrV4RequestedOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_StaticUnicastAddrV4Requested */
  TcpIp_SizeOfTxReqElemType SizeOfTxReqElemOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_TxReqElem */
  TcpIp_SizeOfTxReqElemListType SizeOfTxReqElemListOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_TxReqElemList */
  TcpIp_SizeOfUdpTxRetryQueueElementChainType SizeOfUdpTxRetryQueueElementChainOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElementChain */
  TcpIp_SizeOfUdpTxRetryQueueElementsType SizeOfUdpTxRetryQueueElementsOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElements */
  TcpIp_SizeOfUdpTxRetryQueuePoolDescType SizeOfUdpTxRetryQueuePoolDescOfPCConfig;  /**< the number of accomplishable value elements in TcpIp_UdpTxRetryQueuePoolDesc */
  TcpIp_SizeOfUnicastAddrV4Type SizeOfUnicastAddrV4OfPCConfig;  /**< the number of accomplishable value elements in TcpIp_UnicastAddrV4 */
} TcpIp_PCConfigType;

typedef TcpIp_PCConfigType TcpIp_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access TcpIp_PCConfig in a symbol based style. */
typedef struct sTcpIp_PCConfigsType
{
  TcpIp_PCConfigType Config;  /**< [Config] */
} TcpIp_PCConfigsType;

/** 
  \}
*/ 



/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
# define TCPIP_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

extern TCPIP_P2C(TcpIp_ConfigType) TcpIp_ConfigDataPtr;

# define TCPIP_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  TcpIp_AddrAssignmentCfgByPrio
**********************************************************************************************************************/
/** 
  \var    TcpIp_AddrAssignmentCfgByPrio
  \brief  -
*/ 
#define TCPIP_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_AddrAssignmentCfgByPrioType, TCPIP_CONST) TcpIp_AddrAssignmentCfgByPrio[1];
#define TCPIP_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_ArpConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_ArpConfig
  \details
  Element                      Description
  EntryTimeout                 Table Entry Timeout - Value of configuration parameter TcpIpArpTableEntryTimeout [MAIN_FUNCTION_CYCLES]
  RetryInterval                Retry Interval - Value of configuration parameter TcpIpArpRetryInterval [MAIN_FUNCTION_CYCLES]
  RetryTime                    Retry Timeout - Value of configuration parameter TcpIpArpRetryTime [MAIN_FUNCTION_CYCLES]
  PacketQueueEnabled           Packet Queue Enabled - Value of configuration parameter TcpIpArpPacketQueueEnabled [BOOLEAN]
  NumGratuitousArpOnStartup    Num Gratuitous ARP On Startup - Value of configuration parameter TcpIpArpNumGratuitousARPonStartup
  RequestTimeout               Value of configuration parameter TcpIpArpRequestTimeout [MAIN_FUNCTION_CYCLES]
  TableSize                    Table Size Max - Value of configuration parameter TcpIpArpTableSizeMax
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_ArpConfigType, TCPIP_CONST) TcpIp_ArpConfig[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DefaultMulticastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_DefaultMulticastAddrV4
  \brief  -
  \details
  Element    Description
  NetAddr    -
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_DefaultMulticastAddrV4Type, TCPIP_CONST) TcpIp_DefaultMulticastAddrV4[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DefaultUnicastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_DefaultUnicastAddrV4
  \brief  -
  \details
  Element      Description
  DefGwAddr    -
  NetAddr      -
  NetMask      -
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_DefaultUnicastAddrV4Type, TCPIP_CONST) TcpIp_DefaultUnicastAddrV4[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_DuplicateAddrDetectionFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_DuplicateAddrDetectionCbkType, TCPIP_CONST) TcpIp_DuplicateAddrDetectionFctPtr;  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_EthIfCtrl
**********************************************************************************************************************/
/** 
  \var    TcpIp_EthIfCtrl
  \brief  Array mapping from EthIfCtrlIdx to IpCtrlIdx
  \details
  Element        Description
  IpV4CtrlIdx    the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_EthIfCtrlType, TCPIP_CONST) TcpIp_EthIfCtrl[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IcmpMsgHandlerCbkFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_IcmpMsgHandlerCbkType, TCPIP_CONST) TcpIp_IcmpMsgHandlerCbkFctPtr;
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4Ctrl
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4Ctrl
  \details
  Element                            Description
  MaxTxMsgSize                       -
  MtuTx                              Value of configuration parameter EthIfCtrlMtu
  AutoIpConfigUsed                   TRUE, if the 0:1 relation has minimum 1 relation pointing to TcpIp_AutoIpConfig
  HwChecksumIcmp                     Defines if harware supports calculation of IPv4 ICMP checksum.
  AddrAssignmentCfgByPrioEndIdx      the end index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio
  AddrAssignmentCfgByPrioStartIdx    the start index of the 1:n relation pointing to TcpIp_AddrAssignmentCfgByPrio
  AddrAssignmentPrioByType           -
  ArpConfigIdx                       the index of the 0:1 relation pointing to TcpIp_ArpConfig
  ArpTableEntryEndIdx                the end index of the 0:n relation pointing to TcpIp_ArpTableEntry
  ArpTableEntryStartIdx              the start index of the 0:n relation pointing to TcpIp_ArpTableEntry
  AutoIpConfigIdx                    the index of the 0:1 relation pointing to TcpIp_AutoIpConfig
  Buf2TxReqMapEndIdx                 the end index of the 1:n relation pointing to TcpIp_Buf2TxReqMap
  Buf2TxReqMapStartIdx               the start index of the 1:n relation pointing to TcpIp_Buf2TxReqMap
  DefaultTtl                         Default Time To Live - Value of configuration parameter TcpIpIpDefaultTtl
  DhcpConfigIdx                      the index of the 0:1 relation pointing to TcpIp_DhcpConfig
  DhcpStatusIdx                      the index of the 0:1 relation pointing to TcpIp_DhcpStatus
  DhcpUserOptionEndIdx               the end index of the 0:n relation pointing to TcpIp_DhcpUserOption
  DhcpUserOptionStartIdx             the start index of the 0:n relation pointing to TcpIp_DhcpUserOption
  EthIfCtrlIdx                       -
  FragmentationConfigIdx             the index of the 0:1 relation pointing to TcpIp_FragmentationConfig
  FramePrioDefault                   IP Frame Prio Default - Value of configuration parameter TcpIpIpFramePrioDefault
  GratuitousArpIdx                   the index of the 0:1 relation pointing to TcpIp_GratuitousArp
  LlAddrStateIdx                     the index of the 0:1 relation pointing to TcpIp_LlAddrState
  LocalAddrV4BroadcastIdx            the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
  LocalAddrV4UnicastIdx              the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
  MulticastAddrV4EndIdx              the end index of the 0:n relation pointing to TcpIp_MulticastAddrV4
  MulticastAddrV4StartIdx            the start index of the 0:n relation pointing to TcpIp_MulticastAddrV4
  StaticArpTableIdx                  the index of the 0:1 relation pointing to TcpIp_StaticArpTable
  TypeOfServiceDefault               IP Type Of Service Default - Value of configuration parameter TcpIpIpTypeOfServiceDefault
  UnicastAddrV4Idx                   the index of the 1:1 relation pointing to TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_IpV4CtrlType, TCPIP_CONST) TcpIp_IpV4Ctrl[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4General
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4General
  \details
  Element                   Description
  IpV4CtrlDefaultIdx        the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
  IpV4SocketDynDhcpIdx      the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
  IpV4SocketDynIcmpIdx      the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
  IpV4SocketDynTcpRstIdx    the index of the 0:1 relation pointing to TcpIp_IpV4SocketDyn
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_IpV4GeneralType, TCPIP_CONST) TcpIp_IpV4General[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_LocalAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_LocalAddrV4
  \brief  -
  \details
  Element               Description
  IpV4CtrlIdx           the index of the 1:1 relation pointing to TcpIp_IpV4Ctrl
  MulticastAddrV4Idx    the index of the 0:1 relation pointing to TcpIp_MulticastAddrV4
  UnicastAddrV4Idx      the index of the 0:1 relation pointing to TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_LocalAddrV4Type, TCPIP_CONST) TcpIp_LocalAddrV4[3];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_MulticastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_MulticastAddrV4
  \brief  Structure containing all statically configured IP address information.
  \details
  Element                      Description
  DefaultMulticastAddrV4Idx    the index of the 1:1 relation pointing to TcpIp_DefaultMulticastAddrV4
  LocalAddrV4Idx               the index of the 1:1 relation pointing to TcpIp_LocalAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_MulticastAddrV4Type, TCPIP_CONST) TcpIp_MulticastAddrV4[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_RandomNumberFctPtr
**********************************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_GetRandomNumberType, TCPIP_CONST) TcpIp_RandomNumberFctPtr;
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketOwnerConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketOwnerConfig
  \brief  -
  \details
  Element                            Description
  CopyTxDataDynFuncPtr               [User]_CopyTxDataDyn Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.)
  CopyTxDataFuncPtr                  [User]_CopyTxData Callback Function. (only required if socket owner uses indirect data provistion in Tcp/UdpTransmit.)
  DhcpEventFuncPtr                   Callout triggered on reception and transmission of client DHCP messages.
  LocalIpAddrAssignmentChgFuncPtr    -
  RxIndicationFuncPtr                [User]_RxIndication Callback Function. (required for socket owner that recieves packets.)
  TcpAcceptedFuncPtr                 [User]_TcpAccepted Callback Function. (only required if socker passively accepts TCP connections.)
  TcpConnectedFuncPtr                [User]_TcpConnected Callback Function. (only required if socker owner actively opens TCP connections.)
  TcpIpEventFuncPtr                  [User]_TcpIpEvent Callback Function. (required for every socket owner)
  TlsValidationResultFuncPtr         [User]_TlsValidationResult Callback Function.
  TxConfirmationFuncPtr              [User]_TxConfirmation Callback Function. (optional for every socket owner)
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_SocketOwnerConfigType, TCPIP_CONST) TcpIp_SocketOwnerConfig[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UnicastAddrV4
**********************************************************************************************************************/
/** 
  \var    TcpIp_UnicastAddrV4
  \brief  Structure containing all statically configured IP address information.
  \details
  Element                            Description
  DefaultUnicastAddrV4Idx            the index of the 0:1 relation pointing to TcpIp_DefaultUnicastAddrV4
  StaticUnicastAddrV4RequestedIdx    the index of the 0:1 relation pointing to TcpIp_StaticUnicastAddrV4Requested
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_UnicastAddrV4Type, TCPIP_CONST) TcpIp_UnicastAddrV4[1];
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_ArpTableEntry
**********************************************************************************************************************/
/** 
  \var    TcpIp_ArpTableEntry
  \brief  -
  \details
  Element              Description
  CreationTimeStamp    Time when this entry was created [MAIN_FUNCTION_CYCLES]
  TimeStamp            Time when this entry was marked as valid [MAIN_FUNCTION_CYCLES]
  Status               Status of this ARP entry (INVALID, INPROGRESS, VALID, PROBE)
  NetAddr              Network (IP) address of the neighbor node
  PhysAddr             Physical (MAC) address of the neighbor node
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_ArpTableEntryUType, TCPIP_VAR_NOINIT) TcpIp_ArpTableEntry;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_Buf2TxReqMap
**********************************************************************************************************************/
/** 
  \var    TcpIp_Buf2TxReqMap
  \brief  -
  \details
  Element          Description
  EthBufLen        -
  EthBufIdxNext    -
  SocketDynIdx     the index of the 0:1 relation pointing to TcpIp_SocketDyn
  UlTxReqIdx       -
  EthBufPtr        -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_Buf2TxReqMapUType, TCPIP_VAR_NOINIT) TcpIp_Buf2TxReqMap;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4CtrlDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4CtrlDyn
  \brief  -
  \details
  Element                         Description
  ActiveAddrAssignmentMethod      -
  AddrAssignmentReadyChanged      -
  AddrAssignmentTriggeredFlags    -
  PhysLinkActive                  -
  State                           -
  ActiveDefGwAddr                 -
  ActiveNetAddr                   -
  ActiveNetMask                   -
  LastBcAddr                      -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_IpV4CtrlDynUType, TCPIP_VAR_NOINIT) TcpIp_IpV4CtrlDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_IpV4SocketDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_IpV4SocketDyn
  \brief  -
  \details
  Element                 Description
  ArpTableEntryIdx        the index of the 0:1 relation pointing to TcpIp_ArpTableEntry
  EthIfFramePrio          -
  Flags                   -
  IpV4CtrlIdx             the index of the 0:1 relation pointing to TcpIp_IpV4Ctrl
  Protocol                -
  TimeToLive              -
  TxDescriptorProtocol    -
  TypeOfService           -
  LocSock             
  PhysDestAddr            -
  TransferBlock           -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_IpV4SocketDynUType, TCPIP_VAR_NOINIT) TcpIp_IpV4SocketDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_LocalAddr
**********************************************************************************************************************/
/** 
  \var    TcpIp_LocalAddr
  \details
  Element            Description
  AssignmentState    -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_LocalAddrUType, TCPIP_VAR_NOINIT) TcpIp_LocalAddr;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_MulticastAddrV4Requested
**********************************************************************************************************************/
/** 
  \var    TcpIp_MulticastAddrV4Requested
  \brief  -
  \details
  Element    Description
  NetAddr    -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_MulticastAddrV4RequestedType, TCPIP_VAR_NOINIT) TcpIp_MulticastAddrV4Requested[1];
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketDyn
  \brief  Generic (TCP/UDP) socket variables
  \details
  Element                 Description
  ListenActiveConnStat    Current state of the socket
  LocalAddrBindIdx        the index of the 0:1 relation pointing to TcpIp_LocalAddr
  SocketOwnerConfigIdx    the index of the 0:1 relation pointing to TcpIp_SocketOwnerConfig
  TxBufRequested          TX buffer request semaphore
  TxIpAddrIdx             Index of local IPxV address that is used for transmission
  LocSock                 IP address and port of the local host
  RemSock                 IP address and port of the remote host
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_SocketDynUType, TCPIP_VAR_NOINIT) TcpIp_SocketDyn;  /* PRQA S 0759 */  /* MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_SocketUdpDyn
**********************************************************************************************************************/
/** 
  \var    TcpIp_SocketUdpDyn
  \brief  UDP socket specific variables
  \details
  Element                  Description
  TxReqElemListIdx         the index of the 0:1 relation pointing to TcpIp_TxReqElemList
  TxRetrQueueMaxNum        Maximum number of TX retry queue elements for the socket.
  IpTxRequestDescriptor    TX request descriptor required for the IP layer
  TxReqIpBufPtr            Pointer to the provided TX buffer of the IP layer
  TxRetrQueue              TX retry queue
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_SocketUdpDynType, TCPIP_VAR_NOINIT) TcpIp_SocketUdpDyn[2];
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_StaticUnicastAddrV4Requested
**********************************************************************************************************************/
/** 
  \var    TcpIp_StaticUnicastAddrV4Requested
  \brief  -
  \details
  Element      Description
  DefGwAddr    -
  NetAddr      -
  NetMask      -
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_StaticUnicastAddrV4RequestedUType, TCPIP_VAR_NOINIT) TcpIp_StaticUnicastAddrV4Requested;  /* PRQA S 0777, 0759 */  /* MD_MSR_Rule5.1, MD_CSL_Union */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueueElementChain
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueueElementChain
  \brief  UDP TX retry queue element chain
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_DListNodeType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElementChain[3];  /* PRQA S 0777 */  /* MD_MSR_Rule5.1 */
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueueElements
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueueElements
  \brief  UDP TX retry queue elements
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_Udp_RetryQueueElementType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueueElements[3];
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_UdpTxRetryQueuePoolDesc
**********************************************************************************************************************/
/** 
  \var    TcpIp_UdpTxRetryQueuePoolDesc
  \brief  UDP TX retry queue element pool
*/ 
#define TCPIP_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(TcpIp_DListDescType, TCPIP_VAR_NOINIT) TcpIp_UdpTxRetryQueuePoolDesc[1];
#define TCPIP_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  TcpIp_PCConfig
**********************************************************************************************************************/
/** 
  \var    TcpIp_PCConfig
  \details
  Element                               Description
  ArpConfig                             the pointer to TcpIp_ArpConfig
  ArpTableEntry                         the pointer to TcpIp_ArpTableEntry
  AutoIpConfig                          the pointer to TcpIp_AutoIpConfig
  DefaultMulticastAddrV4                the pointer to TcpIp_DefaultMulticastAddrV4
  DefaultUnicastAddrV4                  the pointer to TcpIp_DefaultUnicastAddrV4
  DhcpUserOption                        the pointer to TcpIp_DhcpUserOption
  DhcpUserOptionBuffer                  the pointer to TcpIp_DhcpUserOptionBuffer
  DhcpUserOptionDyn                     the pointer to TcpIp_DhcpUserOptionDyn
  FragmentationConfig                   the pointer to TcpIp_FragmentationConfig
  GratuitousArp                         the pointer to TcpIp_GratuitousArp
  LlAddrState                           the pointer to TcpIp_LlAddrState
  MulticastAddrV4                       the pointer to TcpIp_MulticastAddrV4
  MulticastAddrV4Requested              the pointer to TcpIp_MulticastAddrV4Requested
  PhysAddrConfig                        the pointer to TcpIp_PhysAddrConfig
  ReassemblyBuffer                      the pointer to TcpIp_ReassemblyBuffer
  ReassemblyBufferDesc                  the pointer to TcpIp_ReassemblyBufferDesc
  ReassemblyBufferDescDyn               the pointer to TcpIp_ReassemblyBufferDescDyn
  StaticArpEntry                        the pointer to TcpIp_StaticArpEntry
  StaticArpTable                        the pointer to TcpIp_StaticArpTable
  StaticUnicastAddrV4Requested          the pointer to TcpIp_StaticUnicastAddrV4Requested
  TxReqElem                             the pointer to TcpIp_TxReqElem
  TxReqElemList                         the pointer to TcpIp_TxReqElemList
  TxReqElemListDyn                      the pointer to TcpIp_TxReqElemListDyn
  UdpTxRetryQueueElementChain           the pointer to TcpIp_UdpTxRetryQueueElementChain
  UdpTxRetryQueueElements               the pointer to TcpIp_UdpTxRetryQueueElements
  UdpTxRetryQueuePoolDesc               the pointer to TcpIp_UdpTxRetryQueuePoolDesc
  UnicastAddrV4                         the pointer to TcpIp_UnicastAddrV4
  SizeOfArpConfig                       the number of accomplishable value elements in TcpIp_ArpConfig
  SizeOfArpTableEntry                   the number of accomplishable value elements in TcpIp_ArpTableEntry
  SizeOfAutoIpConfig                    the number of accomplishable value elements in TcpIp_AutoIpConfig
  SizeOfDefaultMulticastAddrV4          the number of accomplishable value elements in TcpIp_DefaultMulticastAddrV4
  SizeOfDefaultUnicastAddrV4            the number of accomplishable value elements in TcpIp_DefaultUnicastAddrV4
  SizeOfDhcpUserOption                  the number of accomplishable value elements in TcpIp_DhcpUserOption
  SizeOfDhcpUserOptionBuffer            the number of accomplishable value elements in TcpIp_DhcpUserOptionBuffer
  SizeOfFragmentationConfig             the number of accomplishable value elements in TcpIp_FragmentationConfig
  SizeOfGratuitousArp                   the number of accomplishable value elements in TcpIp_GratuitousArp
  SizeOfLlAddrState                     the number of accomplishable value elements in TcpIp_LlAddrState
  SizeOfMulticastAddrV4                 the number of accomplishable value elements in TcpIp_MulticastAddrV4
  SizeOfPhysAddrConfig                  the number of accomplishable value elements in TcpIp_PhysAddrConfig
  SizeOfReassemblyBuffer                the number of accomplishable value elements in TcpIp_ReassemblyBuffer
  SizeOfReassemblyBufferDesc            the number of accomplishable value elements in TcpIp_ReassemblyBufferDesc
  SizeOfStaticArpEntry                  the number of accomplishable value elements in TcpIp_StaticArpEntry
  SizeOfStaticArpTable                  the number of accomplishable value elements in TcpIp_StaticArpTable
  SizeOfStaticUnicastAddrV4Requested    the number of accomplishable value elements in TcpIp_StaticUnicastAddrV4Requested
  SizeOfTxReqElem                       the number of accomplishable value elements in TcpIp_TxReqElem
  SizeOfTxReqElemList                   the number of accomplishable value elements in TcpIp_TxReqElemList
  SizeOfUdpTxRetryQueueElementChain     the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElementChain
  SizeOfUdpTxRetryQueueElements         the number of accomplishable value elements in TcpIp_UdpTxRetryQueueElements
  SizeOfUdpTxRetryQueuePoolDesc         the number of accomplishable value elements in TcpIp_UdpTxRetryQueuePoolDesc
  SizeOfUnicastAddrV4                   the number of accomplishable value elements in TcpIp_UnicastAddrV4
*/ 
#define TCPIP_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(TcpIp_PCConfigsType, TCPIP_CONST) TcpIp_PCConfig;
#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
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
#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetDataInlineFunctionPrototypes  Get Data Inline Function Prototypes
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrio(TcpIp_AddrAssignmentCfgByPrioIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_EntryTimeoutOfArpConfigType, TCPIP_CODE) TcpIp_GetEntryTimeoutOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_NumGratuitousArpOnStartupOfArpConfigType, TCPIP_CODE) TcpIp_GetNumGratuitousArpOnStartupOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PacketQueueEnabledOfArpConfigType, TCPIP_CODE) TcpIp_IsPacketQueueEnabledOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_RequestTimeoutOfArpConfigType, TCPIP_CODE) TcpIp_GetRequestTimeoutOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_RetryIntervalOfArpConfigType, TCPIP_CODE) TcpIp_GetRetryIntervalOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_RetryTimeOfArpConfigType, TCPIP_CODE) TcpIp_GetRetryTimeOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TableSizeOfArpConfigType, TCPIP_CODE) TcpIp_GetTableSizeOfArpConfig(TcpIp_ArpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_CreationTimeStampOfArpTableEntryType, TCPIP_CODE) TcpIp_GetCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrType, TCPIP_CODE) TcpIp_GetPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StatusOfArpTableEntryType, TCPIP_CODE) TcpIp_GetStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TimeStampOfArpTableEntryType, TCPIP_CODE) TcpIp_GetTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpV4_LinkLocalAddrCalloutFuncType, TCPIP_CODE) TcpIp_GetAddrCalloutFuncOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceNumOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceNumOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceWaitMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceWaitMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefendIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetDefendIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxConflictsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetMaxConflictsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeMaxMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeMaxMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeMinMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeMinMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeNumOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeWaitMaxMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeWaitMaxMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeWaitMinMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeWaitMinMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_RateLimitIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetRateLimitIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthBufIdxNextOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthBufLenOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR), TCPIP_CODE) TcpIp_GetEthBufPtrOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketDynIdxOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UlTxReqIdxOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfDefaultMulticastAddrV4(TcpIp_DefaultMulticastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetDefGwAddrOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetMaskOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_CodeOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetCodeOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferEndIdxOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionDirectionType, TCPIP_CODE) TcpIp_GetDirectionOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LengthOfDhcpUserOptionDynType, TCPIP_CODE) TcpIp_GetLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DuplicateAddrDetectionCbkType, TCPIP_CODE) TcpIp_GetDuplicateAddrDetectionFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfEthIfCtrlType, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(TcpIp_EthIfCtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxPacketSizeOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetMaxPacketSizeOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescEndIdxOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescLengthOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescLengthOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescStartIdxOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescUsedOfFragmentationConfigType, TCPIP_CODE) TcpIp_IsReassemblyBufferDescUsedOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyTimeoutMsOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyTimeoutMsOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_NextTransmissionMsOfGratuitousArpType, TCPIP_CODE) TcpIp_GetNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TransmissionCntOfGratuitousArpType, TCPIP_CODE) TcpIp_GetTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IcmpMsgHandlerCbkType, TCPIP_CODE) TcpIp_GetIcmpMsgHandlerCbkFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentPrioByTypeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentPrioByTypeOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AutoIpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAutoIpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AutoIpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_Buf2TxReqMapEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultTtlOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDefaultTtlOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpStatusIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthIfCtrlIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_FragmentationConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_FramePrioDefaultOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetFramePrioDefaultOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_GratuitousArpIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetGratuitousArpIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumIcmpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LlAddrStateIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4BroadcastIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxTxMsgSizeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMaxTxMsgSizeOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MtuTxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMtuTxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4EndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4StartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpTableIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetStaticArpTableIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TypeOfServiceDefaultOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetTypeOfServiceDefaultOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4IdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetUnicastAddrV4IdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveDefGwAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_IsAddrAssignmentReadyChangedOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetLastBcAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysLinkActiveOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_IsPhysLinkActiveOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StateOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlDefaultIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4CtrlDefaultIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynDhcpIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynIcmpIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynIcmpIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynTcpRstIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryIdxOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthIfFramePrioOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_FlagsOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetPhysDestAddrOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProtocolOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TimeToLiveOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpV4_Ip_TransferBlockType, TCPIP_CODE) TcpIp_GetTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxDescriptorProtocolOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TypeOfServiceOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrConflictOfLlAddrStateType, TCPIP_CODE) TcpIp_IsAddrConflictOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrConflictTimeoutOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetAddrFoundOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnStateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ConflictsNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MsecCntOfLlAddrStateType, TCPIP_CODE) TcpIp_GetMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrCandOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumSinceConfOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeStateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_WaitUntilTimeOfLlAddrStateType, TCPIP_CODE) TcpIp_GetWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_AssignmentStateOfLocalAddrType, TCPIP_CODE) TcpIp_GetAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4IdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4IdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetUnicastAddrV4IdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4(TcpIp_MulticastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4IdxOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4(TcpIp_MulticastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfMulticastAddrV4Requested(TcpIp_MulticastAddrV4RequestedIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrTableChgDiscardedCbkType, TCPIP_CODE) TcpIp_GetChgDiscardedFuncPtrOfPhysAddrConfig(TcpIp_PhysAddrConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrTableChgCbkType, TCPIP_CODE) TcpIp_GetChgFuncPtrOfPhysAddrConfig(TcpIp_PhysAddrConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_GetRandomNumberType, TCPIP_CODE) TcpIp_GetRandomNumberFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferType, TCPIP_CODE) TcpIp_GetReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferEndIdxOfReassemblyBufferDesc(TcpIp_ReassemblyBufferDescIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferStartIdxOfReassemblyBufferDesc(TcpIp_ReassemblyBufferDescIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpV4_Ip_ReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ListenActiveConnStatOfSocketDynType, TCPIP_CODE) TcpIp_GetListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetLocSockOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrBindIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetRemSockOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerConfigIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxBufRequestedOfSocketDynType, TCPIP_CODE) TcpIp_IsTxBufRequestedOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxIpAddrIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerCopyTxDataDynType, TCPIP_CODE) TcpIp_GetCopyTxDataDynFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerCopyTxDataType, TCPIP_CODE) TcpIp_GetCopyTxDataFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerDhcpEventType, TCPIP_CODE) TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerLocalIpAddrAssignmentChgType, TCPIP_CODE) TcpIp_GetLocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerRxIndicationType, TCPIP_CODE) TcpIp_GetRxIndicationFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpAcceptedType, TCPIP_CODE) TcpIp_GetTcpAcceptedFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpConnectedType, TCPIP_CODE) TcpIp_GetTcpConnectedFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpIpEventType, TCPIP_CODE) TcpIp_GetTcpIpEventFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTlsValidationResultType, TCPIP_CODE) TcpIp_GetTlsValidationResultFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTxConfirmationType, TCPIP_CODE) TcpIp_GetTxConfirmationFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpTxRequestDescriptorType, TCPIP_CODE) TcpIp_GetIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemListIdxOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR), TCPIP_CODE) TcpIp_GetTxReqIpBufPtrOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListType, TCPIP_CODE) TcpIp_GetTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetIpAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrType, TCPIP_CODE) TcpIp_GetPhysAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpEntryEndIdxOfStaticArpTableType, TCPIP_CODE) TcpIp_GetStaticArpEntryEndIdxOfStaticArpTable(TcpIp_StaticArpTableIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpEntryStartIdxOfStaticArpTableType, TCPIP_CODE) TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(TcpIp_StaticArpTableIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetDefGwAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index);
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetMaskOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemDataLenByteOfTxReqElemType, TCPIP_CODE) TcpIp_GetTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemTransmittedOfTxReqElemType, TCPIP_CODE) TcpIp_IsTxReqElemTransmittedOfTxReqElem(TcpIp_TxReqElemIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemEndIdxOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemEndIdxOfTxReqElemList(TcpIp_TxReqElemListIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemLengthOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemLengthOfTxReqElemList(TcpIp_TxReqElemListIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemStartIdxOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemStartIdxOfTxReqElemList(TcpIp_TxReqElemListIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_FillNumOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReadPosOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketUdpDynIdxOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_WritePosOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListNodeType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_Udp_RetryQueueElementType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListDescType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetDeduplicatedInlineFunctionPrototypes  Get Deduplicated Inline Function Prototypes
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlUsedOfEthIfCtrlType, TCPIP_CODE) TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(TcpIp_EthIfCtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_InOrderReassemblyOfFragmentationConfigType, TCPIP_CODE) TcpIp_IsInOrderReassemblyOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsArpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsArpTableEntryUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpStatusUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_FragmentationConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsFragmentationConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_GratuitousArpUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsGratuitousArpUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumIpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumIpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumTcpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumTcpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumUdpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumUdpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LlAddrStateUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4UsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsMulticastAddrV4UsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReceiveAllMulticastsOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpTableUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsStaticArpTableUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlDefaultUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4CtrlDefaultUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynDhcpUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynDhcpUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynIcmpUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynIcmpUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynTcpRstUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynTcpRstUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4UsedOfLocalAddrV4Type, TCPIP_CODE) TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4UsedOfLocalAddrV4Type, TCPIP_CODE) TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfAddrAssignmentCfgByPrioType, TCPIP_CODE) TcpIp_GetSizeOfAddrAssignmentCfgByPrio(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfArpConfigType, TCPIP_CODE) TcpIp_GetSizeOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfArpTableEntryType, TCPIP_CODE) TcpIp_GetSizeOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetSizeOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetSizeOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDefaultMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfDefaultMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDefaultUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionBufferType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOptionBuffer(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionDynType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOptionDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfEthIfCtrlType, TCPIP_CODE) TcpIp_GetSizeOfEthIfCtrl(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetSizeOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfGratuitousArpType, TCPIP_CODE) TcpIp_GetSizeOfGratuitousArp(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetSizeOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetSizeOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetSizeOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetSizeOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLlAddrStateType, TCPIP_CODE) TcpIp_GetSizeOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrType, TCPIP_CODE) TcpIp_GetSizeOfLocalAddr(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfMulticastAddrV4RequestedType, TCPIP_CODE) TcpIp_GetSizeOfMulticastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfPhysAddrConfigType, TCPIP_CODE) TcpIp_GetSizeOfPhysAddrConfig(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBuffer(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBufferDesc(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescDynType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBufferDescDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketDynType, TCPIP_CODE) TcpIp_GetSizeOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketOwnerConfigType, TCPIP_CODE) TcpIp_GetSizeOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetSizeOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticArpEntryType, TCPIP_CODE) TcpIp_GetSizeOfStaticArpEntry(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticArpTableType, TCPIP_CODE) TcpIp_GetSizeOfStaticArpTable(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticUnicastAddrV4RequestedType, TCPIP_CODE) TcpIp_GetSizeOfStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElem(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemListType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueueElementChainType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueueElementChain(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueueElementsType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueueElements(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueuePoolDescType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueuePoolDesc(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultUnicastAddrV4UsedOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_IsDefaultUnicastAddrV4UsedOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticUnicastAddrV4RequestedUsedOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_IsStaticUnicastAddrV4RequestedUsedOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCSetDataInlineFunctionPrototypes  Set Data Inline Function Prototypes
  \brief  These inline functions can be used to write data.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_PhysAddrType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufPtrOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrAssignmentReadyChangedOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLastBcAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysLinkActiveOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_PhysLinkActiveOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_SockAddrBaseType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysDestAddrOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, IpV4_Ip_TransferBlockType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrConflictOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrFoundOfLlAddrState(TcpIp_LlAddrStateIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrCandOfLlAddrState(TcpIp_LlAddrStateIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfMulticastAddrV4Requested(TcpIp_MulticastAddrV4RequestedIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index, IpV4_Ip_ReassemblyBufferDescType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocSockOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SockAddrBaseType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetRemSockOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SockAddrBaseType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxBufRequestedOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxBufRequestedOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_IpTxRequestDescriptorType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqIpBufPtrOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_DListType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetDefGwAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetMaskOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemTransmittedOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemTransmittedOfTxReqElemType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index, TcpIp_DListNodeType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index, TcpIp_Udp_RetryQueueElementType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index, TcpIp_DListDescType Value);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetAddressOfDataInlineFunctionPrototypes  Get Address Of Data Inline Function Prototypes
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrOfArpTableEntryPtrType, TCPIP_CODE) TcpIp_GetAddrPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferPtrType, TCPIP_CODE) TcpIp_GetAddrDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocSockOfIpV4SocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TransferBlockOfIpV4SocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferPtrType, TCPIP_CODE) TcpIp_GetAddrReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescDynPtrType, TCPIP_CODE) TcpIp_GetAddrReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocSockOfSocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrLocSockOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_RemSockOfSocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrRemSockOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpTxRequestDescriptorOfSocketUdpDynPtrType, TCPIP_CODE) TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxRetrQueueOfSocketUdpDynPtrType, TCPIP_CODE) TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrOfStaticArpEntryPtrType, TCPIP_CODE) TcpIp_GetAddrPhysAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueueElementChainPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueueElementsPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index);
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueuePoolDescPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCHasInlineFunctionPrototypes  Has Inline Function Prototypes
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrio(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEntryTimeoutOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNumGratuitousArpOnStartupOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPacketQueueEnabledOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRequestTimeoutOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRetryIntervalOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRetryTimeOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTableSizeOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCreationTimeStampOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStatusOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTimeStampOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrCalloutFuncOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceIntervalMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceNumOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceWaitMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefendIntervalMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxConflictsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeMaxMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeMinMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeWaitMaxMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeWaitMinMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRateLimitIntervalMsOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufIdxNextOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufLenOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufPtrOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDynIdxOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUlTxReqIdxOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfDefaultMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefGwAddrOfDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetMaskOfDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCodeOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferEndIdxOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferLengthOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferStartIdxOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDirectionOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBuffer(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLengthOfDhcpUserOptionDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDuplicateAddrDetectionFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfEthIfCtrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlUsedOfEthIfCtrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasInOrderReassemblyOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxPacketSizeOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescEndIdxOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescLengthOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescStartIdxOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescUsedOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyTimeoutMsOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArp(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNextTransmissionMsOfGratuitousArp(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTransmissionCntOfGratuitousArp(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIcmpMsgHandlerCbkFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentPrioByTypeOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryEndIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryStartIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapEndIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapStartIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultTtlOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpConfigIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpConfigUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpStatusIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpStatusUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionEndIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionStartIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrlIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFramePrioDefaultOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumIcmpOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumIpOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumTcpOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumUdpOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4BroadcastIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4UnicastIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxTxMsgSizeOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMtuTxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4EndIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4StartIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4UsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReceiveAllMulticastsOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableIdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableUsedOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTypeOfServiceDefaultOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4IdxOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveAddrAssignmentMethodOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveDefGwAddrOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveNetAddrOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveNetMaskOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentReadyChangedOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLastBcAddrOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysLinkActiveOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStateOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDefaultIdxOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDefaultUsedOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynDhcpIdxOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynDhcpUsedOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynIcmpIdxOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynIcmpUsedOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynTcpRstIdxOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynTcpRstUsedOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryIdxOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfFramePrioOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFlagsOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocSockOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysDestAddrOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProtocolOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTimeToLiveOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTransferBlockOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxDescriptorProtocolOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTypeOfServiceOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrConflictOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrConflictTimeoutOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrFoundOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnStateOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceNumOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasConflictsNumOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMsecCntOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrCandOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumSinceConfOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeStateOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStateOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasWaitUntilTimeOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAssignmentStateOfLocalAddr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4IdxOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4UsedOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4IdxOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4UsedOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4IdxOfMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4IdxOfMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfMulticastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasChgDiscardedFuncPtrOfPhysAddrConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasChgFuncPtrOfPhysAddrConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRandomNumberFctPtr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBuffer(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferEndIdxOfReassemblyBufferDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferStartIdxOfReassemblyBufferDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAddrAssignmentCfgByPrio(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpTableEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAutoIpConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfBuf2TxReqMap(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOption(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionBuffer(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfEthIfCtrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfFragmentationConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfGratuitousArp(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4Ctrl(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4General(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4SocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLlAddrState(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddr(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfPhysAddrConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBuffer(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpTable(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElem(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementChain(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElements(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueuePoolDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasListenActiveConnStatOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocSockOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrBindIdxOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRemSockOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfigIdxOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxBufRequestedOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxIpAddrIdxOfSocketDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCopyTxDataDynFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCopyTxDataFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpEventFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRxIndicationFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpAcceptedFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpConnectedFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpIpEventFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTlsValidationResultFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxConfirmationFuncPtrOfSocketOwnerConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpTxRequestDescriptorOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListIdxOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqIpBufPtrOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxRetrQueueMaxNumOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxRetrQueueOfSocketUdpDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpAddrOfStaticArpEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrOfStaticArpEntry(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTable(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryEndIdxOfStaticArpTable(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryStartIdxOfStaticArpTable(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefGwAddrOfStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetMaskOfStaticUnicastAddrV4Requested(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElem(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemDataLenByteOfTxReqElem(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemTransmittedOfTxReqElem(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemEndIdxOfTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemLengthOfTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemStartIdxOfTxReqElemList(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFillNumOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReadPosOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDynIdxOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasWritePosOfTxReqElemListDyn(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementChain(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElements(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueuePoolDesc(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4IdxOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4UsedOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedUsedOfUnicastAddrV4(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDuplicateAddrDetectionFctPtrOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrlOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIcmpMsgHandlerCbkFctPtrOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4GeneralOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4RequestedOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRandomNumberFctPtrOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAddrAssignmentCfgByPrioOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpTableEntryOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAutoIpConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfBuf2TxReqMapOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultMulticastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultUnicastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionBufferOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfEthIfCtrlOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfFragmentationConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfGratuitousArpOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4GeneralOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4SocketDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLlAddrStateOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4RequestedOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfPhysAddrConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketOwnerConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketUdpDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpEntryOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpTableOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticUnicastAddrV4RequestedOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementChainOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementsOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueuePoolDescOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUnicastAddrV4OfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfigOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListDynOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementChainOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementsOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueuePoolDescOfPCConfig(void);
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4OfPCConfig(void);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCIncrementInlineFunctionPrototypes  Increment Inline Function Prototypes
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCDecrementInlineFunctionPrototypes  Decrement Inline Function Prototypes
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStateOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCAddInlineFunctionPrototypes  Add Inline Function Prototypes
  \brief  These inline functions can be used to add VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCSubstractInlineFunctionPrototypes  Substract Inline Function Prototypes
  \brief  These inline functions can be used to substract VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value);
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value);
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */



#if !defined(NO_INLINE_FUNCTION_DEFINITIONS)
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTIONS
**********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetDataInlineFunctions  TcpIp Get Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrio(TcpIp_AddrAssignmentCfgByPrioIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentCfgByPrioType) (TcpIp_GetAddrAssignmentCfgByPrioOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_EntryTimeoutOfArpConfigType, TCPIP_CODE) TcpIp_GetEntryTimeoutOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_EntryTimeoutOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].EntryTimeoutOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_NumGratuitousArpOnStartupOfArpConfigType, TCPIP_CODE) TcpIp_GetNumGratuitousArpOnStartupOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_NumGratuitousArpOnStartupOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].NumGratuitousArpOnStartupOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PacketQueueEnabledOfArpConfigType, TCPIP_CODE) TcpIp_IsPacketQueueEnabledOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_PacketQueueEnabledOfArpConfigType) ((TcpIp_GetArpConfigOfPCConfig()[(Index)].PacketQueueEnabledOfArpConfig) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_RequestTimeoutOfArpConfigType, TCPIP_CODE) TcpIp_GetRequestTimeoutOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_RequestTimeoutOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].RequestTimeoutOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_RetryIntervalOfArpConfigType, TCPIP_CODE) TcpIp_GetRetryIntervalOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_RetryIntervalOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].RetryIntervalOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_RetryTimeOfArpConfigType, TCPIP_CODE) TcpIp_GetRetryTimeOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_RetryTimeOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].RetryTimeOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TableSizeOfArpConfigType, TCPIP_CODE) TcpIp_GetTableSizeOfArpConfig(TcpIp_ArpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TableSizeOfArpConfigType) (TcpIp_GetArpConfigOfPCConfig()[(Index)].TableSizeOfArpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_CreationTimeStampOfArpTableEntryType, TCPIP_CODE) TcpIp_GetCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_CreationTimeStampOfArpTableEntryType) (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].NetAddrOfArpTableEntry);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrType, TCPIP_CODE) TcpIp_GetPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].PhysAddrOfArpTableEntry);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StatusOfArpTableEntryType, TCPIP_CODE) TcpIp_GetStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StatusOfArpTableEntryType) (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TimeStampOfArpTableEntryType, TCPIP_CODE) TcpIp_GetTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TimeStampOfArpTableEntryType) (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry);
}
TCPIP_LOCAL_INLINE FUNC(IpV4_LinkLocalAddrCalloutFuncType, TCPIP_CODE) TcpIp_GetAddrCalloutFuncOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (IpV4_LinkLocalAddrCalloutFuncType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].AddrCalloutFuncOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AnnounceIntervalMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].AnnounceIntervalMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceNumOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceNumOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AnnounceNumOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].AnnounceNumOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceWaitMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetAnnounceWaitMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AnnounceWaitMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].AnnounceWaitMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefendIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetDefendIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DefendIntervalMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].DefendIntervalMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxConflictsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetMaxConflictsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MaxConflictsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].MaxConflictsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeMaxMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeMaxMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeMaxMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].ProbeMaxMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeMinMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeMinMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeMinMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].ProbeMinMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeNumOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeNumOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].ProbeNumOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeWaitMaxMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeWaitMaxMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeWaitMaxMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].ProbeWaitMaxMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeWaitMinMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetProbeWaitMinMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeWaitMinMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].ProbeWaitMinMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_RateLimitIntervalMsOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetRateLimitIntervalMsOfAutoIpConfig(TcpIp_AutoIpConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_RateLimitIntervalMsOfAutoIpConfigType) (TcpIp_GetAutoIpConfigOfPCConfig()[(Index)].RateLimitIntervalMsOfAutoIpConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthBufIdxNextOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_EthBufIdxNextOfBuf2TxReqMapType) (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthBufLenOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_EthBufLenOfBuf2TxReqMapType) (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap);
}
TCPIP_LOCAL_INLINE FUNC(P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR), TCPIP_CODE) TcpIp_GetEthBufPtrOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufPtrOfBuf2TxReqMap);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketDynIdxOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketDynIdxOfBuf2TxReqMapType) (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UlTxReqIdxOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_UlTxReqIdxOfBuf2TxReqMapType) (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfDefaultMulticastAddrV4(TcpIp_DefaultMulticastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetDefaultMulticastAddrV4OfPCConfig()[(Index)].NetAddrOfDefaultMulticastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetDefGwAddrOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetDefaultUnicastAddrV4OfPCConfig()[(Index)].DefGwAddrOfDefaultUnicastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetDefaultUnicastAddrV4OfPCConfig()[(Index)].NetAddrOfDefaultUnicastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetMaskOfDefaultUnicastAddrV4(TcpIp_DefaultUnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetDefaultUnicastAddrV4OfPCConfig()[(Index)].NetMaskOfDefaultUnicastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_CodeOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetCodeOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_CodeOfDhcpUserOptionType) (TcpIp_GetDhcpUserOptionOfPCConfig()[(Index)].CodeOfDhcpUserOption);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferEndIdxOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionBufferEndIdxOfDhcpUserOptionType) (TcpIp_GetDhcpUserOptionOfPCConfig()[(Index)].DhcpUserOptionBufferEndIdxOfDhcpUserOption);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferLengthOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionBufferLengthOfDhcpUserOptionType) (TcpIp_GetDhcpUserOptionOfPCConfig()[(Index)].DhcpUserOptionBufferLengthOfDhcpUserOption);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBufferStartIdxOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionBufferStartIdxOfDhcpUserOptionType) (TcpIp_GetDhcpUserOptionOfPCConfig()[(Index)].DhcpUserOptionBufferStartIdxOfDhcpUserOption);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionDirectionType, TCPIP_CODE) TcpIp_GetDirectionOfDhcpUserOption(TcpIp_DhcpUserOptionIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionDirectionType) (TcpIp_GetDhcpUserOptionOfPCConfig()[(Index)].DirectionOfDhcpUserOption);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferType, TCPIP_CODE) TcpIp_GetDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionBufferType) (TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LengthOfDhcpUserOptionDynType, TCPIP_CODE) TcpIp_GetLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LengthOfDhcpUserOptionDynType) (TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DuplicateAddrDetectionCbkType, TCPIP_CODE) TcpIp_GetDuplicateAddrDetectionFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DuplicateAddrDetectionCbkType) ((*(TcpIp_GetDuplicateAddrDetectionFctPtrOfPCConfig())));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfEthIfCtrlType, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(TcpIp_EthIfCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlIdxOfEthIfCtrlType) (TcpIp_GetEthIfCtrlOfPCConfig()[(Index)].IpV4CtrlIdxOfEthIfCtrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxPacketSizeOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetMaxPacketSizeOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MaxPacketSizeOfFragmentationConfigType) (TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].MaxPacketSizeOfFragmentationConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescEndIdxOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferDescEndIdxOfFragmentationConfigType) (TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].ReassemblyBufferDescEndIdxOfFragmentationConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescLengthOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescLengthOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferDescLengthOfFragmentationConfigType) (TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].ReassemblyBufferDescLengthOfFragmentationConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescStartIdxOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferDescStartIdxOfFragmentationConfigType) (TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].ReassemblyBufferDescStartIdxOfFragmentationConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescUsedOfFragmentationConfigType, TCPIP_CODE) TcpIp_IsReassemblyBufferDescUsedOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferDescUsedOfFragmentationConfigType) ((TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].ReassemblyBufferDescUsedOfFragmentationConfig) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyTimeoutMsOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetReassemblyTimeoutMsOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyTimeoutMsOfFragmentationConfigType) (TcpIp_GetFragmentationConfigOfPCConfig()[(Index)].ReassemblyTimeoutMsOfFragmentationConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_NextTransmissionMsOfGratuitousArpType, TCPIP_CODE) TcpIp_GetNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_NextTransmissionMsOfGratuitousArpType) (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TransmissionCntOfGratuitousArpType, TCPIP_CODE) TcpIp_GetTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TransmissionCntOfGratuitousArpType) (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IcmpMsgHandlerCbkType, TCPIP_CODE) TcpIp_GetIcmpMsgHandlerCbkFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IcmpMsgHandlerCbkType) ((*(TcpIp_GetIcmpMsgHandlerCbkFctPtrOfPCConfig())));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentCfgByPrioEndIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].AddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentCfgByPrioStartIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].AddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentPrioByTypeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAddrAssignmentPrioByTypeOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentPrioByTypeOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].AddrAssignmentPrioByTypeOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpConfigIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].ArpConfigIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpTableEntryEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpTableEntryEndIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].ArpTableEntryEndIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetArpTableEntryStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpTableEntryStartIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].ArpTableEntryStartIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AutoIpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetAutoIpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AutoIpConfigIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].AutoIpConfigIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AutoIpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AutoIpConfigUsedOfIpV4CtrlType) ((TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].AutoIpConfigUsedOfIpV4Ctrl) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_Buf2TxReqMapEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetBuf2TxReqMapEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_Buf2TxReqMapEndIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].Buf2TxReqMapEndIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetBuf2TxReqMapStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_Buf2TxReqMapStartIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].Buf2TxReqMapStartIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultTtlOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDefaultTtlOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DefaultTtlOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].DefaultTtlOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpConfigIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].DhcpConfigIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpStatusIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpStatusIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpStatusIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].DhcpStatusIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionEndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpUserOptionEndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionEndIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].DhcpUserOptionEndIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionStartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetDhcpUserOptionStartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionStartIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].DhcpUserOptionStartIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthIfCtrlIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetEthIfCtrlIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_EthIfCtrlIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].EthIfCtrlIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_FragmentationConfigIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetFragmentationConfigIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_FragmentationConfigIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].FragmentationConfigIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_FramePrioDefaultOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetFramePrioDefaultOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_FramePrioDefaultOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].FramePrioDefaultOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_GratuitousArpIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetGratuitousArpIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GratuitousArpIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].GratuitousArpIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumIcmpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_HwChecksumIcmpOfIpV4CtrlType) ((TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].HwChecksumIcmpOfIpV4Ctrl) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LlAddrStateIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLlAddrStateIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LlAddrStateIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].LlAddrStateIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4BroadcastIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLocalAddrV4BroadcastIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LocalAddrV4BroadcastIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].LocalAddrV4BroadcastIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetLocalAddrV4UnicastIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LocalAddrV4UnicastIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].LocalAddrV4UnicastIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MaxTxMsgSizeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMaxTxMsgSizeOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MaxTxMsgSizeOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].MaxTxMsgSizeOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MtuTxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMtuTxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MtuTxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].MtuTxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4EndIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMulticastAddrV4EndIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MulticastAddrV4EndIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].MulticastAddrV4EndIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4StartIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetMulticastAddrV4StartIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MulticastAddrV4StartIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].MulticastAddrV4StartIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpTableIdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetStaticArpTableIdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticArpTableIdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].StaticArpTableIdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TypeOfServiceDefaultOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetTypeOfServiceDefaultOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TypeOfServiceDefaultOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].TypeOfServiceDefaultOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4IdxOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetUnicastAddrV4IdxOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_UnicastAddrV4IdxOfIpV4CtrlType) (TcpIp_GetIpV4CtrlOfPCConfig()[(Index)].UnicastAddrV4IdxOfIpV4Ctrl);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType) (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveDefGwAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveDefGwAddrOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveNetAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveNetAddrOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetActiveNetMaskOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveNetMaskOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_IsAddrAssignmentReadyChangedOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType) ((TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentReadyChangedOfIpV4CtrlDyn) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType) (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetLastBcAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].LastBcAddrOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysLinkActiveOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_IsPhysLinkActiveOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_PhysLinkActiveOfIpV4CtrlDynType) ((TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].PhysLinkActiveOfIpV4CtrlDyn) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StateOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StateOfIpV4CtrlDynType) (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlDefaultIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4CtrlDefaultIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlDefaultIdxOfIpV4GeneralType) (TcpIp_GetIpV4GeneralOfPCConfig()[(Index)].IpV4CtrlDefaultIdxOfIpV4General);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynDhcpIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynDhcpIdxOfIpV4GeneralType) (TcpIp_GetIpV4GeneralOfPCConfig()[(Index)].IpV4SocketDynDhcpIdxOfIpV4General);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynIcmpIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynIcmpIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynIcmpIdxOfIpV4GeneralType) (TcpIp_GetIpV4GeneralOfPCConfig()[(Index)].IpV4SocketDynIcmpIdxOfIpV4General);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynTcpRstIdxOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynTcpRstIdxOfIpV4GeneralType) (TcpIp_GetIpV4GeneralOfPCConfig()[(Index)].IpV4SocketDynTcpRstIdxOfIpV4General);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryIdxOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpTableEntryIdxOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_EthIfFramePrioOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_EthIfFramePrioOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_FlagsOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_FlagsOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlIdxOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].LocSockOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetPhysDestAddrOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].PhysDestAddrOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProtocolOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProtocolOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TimeToLiveOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TimeToLiveOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpV4_Ip_TransferBlockType, TCPIP_CODE) TcpIp_GetTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TransferBlockOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxDescriptorProtocolOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxDescriptorProtocolOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TypeOfServiceOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TypeOfServiceOfIpV4SocketDynType) (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrConflictOfLlAddrStateType, TCPIP_CODE) TcpIp_IsAddrConflictOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrConflictOfLlAddrStateType) ((TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictOfLlAddrState) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AddrConflictTimeoutOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AddrConflictTimeoutOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetAddrFoundOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrFoundOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnStateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AnnStateOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AnnounceNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AnnounceNumOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ConflictsNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ConflictsNumOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MsecCntOfLlAddrStateType, TCPIP_CODE) TcpIp_GetMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MsecCntOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrCandOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].NetAddrCandOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeNumOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeNumSinceConfOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeNumSinceConfOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ProbeStateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ProbeStateOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StateOfLlAddrStateType, TCPIP_CODE) TcpIp_GetStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StateOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_WaitUntilTimeOfLlAddrStateType, TCPIP_CODE) TcpIp_GetWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_WaitUntilTimeOfLlAddrStateType) (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_AssignmentStateOfLocalAddrType, TCPIP_CODE) TcpIp_GetAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_AssignmentStateOfLocalAddrType) (TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlIdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetIpV4CtrlIdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlIdxOfLocalAddrV4Type) (TcpIp_GetLocalAddrV4OfPCConfig()[(Index)].IpV4CtrlIdxOfLocalAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4IdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MulticastAddrV4IdxOfLocalAddrV4Type) (TcpIp_GetLocalAddrV4OfPCConfig()[(Index)].MulticastAddrV4IdxOfLocalAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4IdxOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetUnicastAddrV4IdxOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_UnicastAddrV4IdxOfLocalAddrV4Type) (TcpIp_GetLocalAddrV4OfPCConfig()[(Index)].UnicastAddrV4IdxOfLocalAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetDefaultMulticastAddrV4IdxOfMulticastAddrV4(TcpIp_MulticastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DefaultMulticastAddrV4IdxOfMulticastAddrV4Type) (TcpIp_GetMulticastAddrV4OfPCConfig()[(Index)].DefaultMulticastAddrV4IdxOfMulticastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrV4IdxOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetLocalAddrV4IdxOfMulticastAddrV4(TcpIp_MulticastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LocalAddrV4IdxOfMulticastAddrV4Type) (TcpIp_GetMulticastAddrV4OfPCConfig()[(Index)].LocalAddrV4IdxOfMulticastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfMulticastAddrV4Requested(TcpIp_MulticastAddrV4RequestedIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetMulticastAddrV4RequestedOfPCConfig()[(Index)].NetAddrOfMulticastAddrV4Requested);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrTableChgDiscardedCbkType, TCPIP_CODE) TcpIp_GetChgDiscardedFuncPtrOfPhysAddrConfig(TcpIp_PhysAddrConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_PhysAddrTableChgDiscardedCbkType) (TcpIp_GetPhysAddrConfigOfPCConfig()[(Index)].ChgDiscardedFuncPtrOfPhysAddrConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrTableChgCbkType, TCPIP_CODE) TcpIp_GetChgFuncPtrOfPhysAddrConfig(TcpIp_PhysAddrConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_PhysAddrTableChgCbkType) (TcpIp_GetPhysAddrConfigOfPCConfig()[(Index)].ChgFuncPtrOfPhysAddrConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_GetRandomNumberType, TCPIP_CODE) TcpIp_GetRandomNumberFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetRandomNumberType) ((*(TcpIp_GetRandomNumberFctPtrOfPCConfig())));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferType, TCPIP_CODE) TcpIp_GetReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferType) (TcpIp_GetReassemblyBufferOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferEndIdxOfReassemblyBufferDesc(TcpIp_ReassemblyBufferDescIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferEndIdxOfReassemblyBufferDescType) (TcpIp_GetReassemblyBufferDescOfPCConfig()[(Index)].ReassemblyBufferEndIdxOfReassemblyBufferDesc);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferStartIdxOfReassemblyBufferDesc(TcpIp_ReassemblyBufferDescIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferStartIdxOfReassemblyBufferDescType) (TcpIp_GetReassemblyBufferDescOfPCConfig()[(Index)].ReassemblyBufferStartIdxOfReassemblyBufferDesc);
}
TCPIP_LOCAL_INLINE FUNC(IpV4_Ip_ReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetReassemblyBufferDescDynOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ListenActiveConnStatOfSocketDynType, TCPIP_CODE) TcpIp_GetListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ListenActiveConnStatOfSocketDynType) (TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetLocSockOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetSocketDynOfPCConfig()[(Index)].LocSockOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocalAddrBindIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LocalAddrBindIdxOfSocketDynType) (TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SockAddrBaseType, TCPIP_CODE) TcpIp_GetRemSockOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetSocketDynOfPCConfig()[(Index)].RemSockOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerConfigIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerConfigIdxOfSocketDynType) (TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxBufRequestedOfSocketDynType, TCPIP_CODE) TcpIp_IsTxBufRequestedOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxBufRequestedOfSocketDynType) ((TcpIp_GetSocketDynOfPCConfig()[(Index)].TxBufRequestedOfSocketDyn) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxIpAddrIdxOfSocketDynType, TCPIP_CODE) TcpIp_GetTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxIpAddrIdxOfSocketDynType) (TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerCopyTxDataDynType, TCPIP_CODE) TcpIp_GetCopyTxDataDynFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerCopyTxDataDynType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].CopyTxDataDynFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerCopyTxDataType, TCPIP_CODE) TcpIp_GetCopyTxDataFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerCopyTxDataType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].CopyTxDataFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerDhcpEventType, TCPIP_CODE) TcpIp_GetDhcpEventFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerDhcpEventType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].DhcpEventFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerLocalIpAddrAssignmentChgType, TCPIP_CODE) TcpIp_GetLocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerLocalIpAddrAssignmentChgType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].LocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerRxIndicationType, TCPIP_CODE) TcpIp_GetRxIndicationFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerRxIndicationType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].RxIndicationFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpAcceptedType, TCPIP_CODE) TcpIp_GetTcpAcceptedFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerTcpAcceptedType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].TcpAcceptedFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpConnectedType, TCPIP_CODE) TcpIp_GetTcpConnectedFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerTcpConnectedType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].TcpConnectedFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTcpIpEventType, TCPIP_CODE) TcpIp_GetTcpIpEventFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerTcpIpEventType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].TcpIpEventFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTlsValidationResultType, TCPIP_CODE) TcpIp_GetTlsValidationResultFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerTlsValidationResultType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].TlsValidationResultFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketOwnerTxConfirmationType, TCPIP_CODE) TcpIp_GetTxConfirmationFuncPtrOfSocketOwnerConfig(TcpIp_SocketOwnerConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketOwnerTxConfirmationType) (TcpIp_GetSocketOwnerConfigOfPCConfig()[(Index)].TxConfirmationFuncPtrOfSocketOwnerConfig);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpTxRequestDescriptorType, TCPIP_CODE) TcpIp_GetIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].IpTxRequestDescriptorOfSocketUdpDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemListIdxOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemListIdxOfSocketUdpDynType) (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn);
}
TCPIP_LOCAL_INLINE FUNC(P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR), TCPIP_CODE) TcpIp_GetTxReqIpBufPtrOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqIpBufPtrOfSocketUdpDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType) (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListType, TCPIP_CODE) TcpIp_GetTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueOfSocketUdpDyn);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetIpAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetStaticArpEntryOfPCConfig()[(Index)].IpAddrOfStaticArpEntry);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrType, TCPIP_CODE) TcpIp_GetPhysAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetStaticArpEntryOfPCConfig()[(Index)].PhysAddrOfStaticArpEntry);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpEntryEndIdxOfStaticArpTableType, TCPIP_CODE) TcpIp_GetStaticArpEntryEndIdxOfStaticArpTable(TcpIp_StaticArpTableIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticArpEntryEndIdxOfStaticArpTableType) (TcpIp_GetStaticArpTableOfPCConfig()[(Index)].StaticArpEntryEndIdxOfStaticArpTable);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpEntryStartIdxOfStaticArpTableType, TCPIP_CODE) TcpIp_GetStaticArpEntryStartIdxOfStaticArpTable(TcpIp_StaticArpTableIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticArpEntryStartIdxOfStaticArpTableType) (TcpIp_GetStaticArpTableOfPCConfig()[(Index)].StaticArpEntryStartIdxOfStaticArpTable);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetDefGwAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].DefGwAddrOfStaticUnicastAddrV4Requested);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].NetAddrOfStaticUnicastAddrV4Requested);
}
TCPIP_LOCAL_INLINE FUNC(IpBase_AddrInType, TCPIP_CODE) TcpIp_GetNetMaskOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].NetMaskOfStaticUnicastAddrV4Requested);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemDataLenByteOfTxReqElemType, TCPIP_CODE) TcpIp_GetTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemDataLenByteOfTxReqElemType) (TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemTransmittedOfTxReqElemType, TCPIP_CODE) TcpIp_IsTxReqElemTransmittedOfTxReqElem(TcpIp_TxReqElemIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemTransmittedOfTxReqElemType) ((TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemTransmittedOfTxReqElem) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemEndIdxOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemEndIdxOfTxReqElemList(TcpIp_TxReqElemListIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemEndIdxOfTxReqElemListType) (TcpIp_GetTxReqElemListOfPCConfig()[(Index)].TxReqElemEndIdxOfTxReqElemList);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemLengthOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemLengthOfTxReqElemList(TcpIp_TxReqElemListIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemLengthOfTxReqElemListType) (TcpIp_GetTxReqElemListOfPCConfig()[(Index)].TxReqElemLengthOfTxReqElemList);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxReqElemStartIdxOfTxReqElemListType, TCPIP_CODE) TcpIp_GetTxReqElemStartIdxOfTxReqElemList(TcpIp_TxReqElemListIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_TxReqElemStartIdxOfTxReqElemListType) (TcpIp_GetTxReqElemListOfPCConfig()[(Index)].TxReqElemStartIdxOfTxReqElemList);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_FillNumOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_FillNumOfTxReqElemListDynType) (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReadPosOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReadPosOfTxReqElemListDynType) (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SocketUdpDynIdxOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SocketUdpDynIdxOfTxReqElemListDynType) (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_WritePosOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_WritePosOfTxReqElemListDynType) (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListNodeType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetUdpTxRetryQueueElementChainOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_Udp_RetryQueueElementType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetUdpTxRetryQueueElementsOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DListDescType, TCPIP_CODE) TcpIp_GetUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GetUdpTxRetryQueuePoolDescOfPCConfig()[(Index)]);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DefaultUnicastAddrV4IdxOfUnicastAddrV4Type) (TcpIp_GetUnicastAddrV4OfPCConfig()[(Index)].DefaultUnicastAddrV4IdxOfUnicastAddrV4);
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4Type) (TcpIp_GetUnicastAddrV4OfPCConfig()[(Index)].StaticUnicastAddrV4RequestedIdxOfUnicastAddrV4);
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetDeduplicatedInlineFunctions  TcpIp Get Deduplicated Inline Functions (PRE_COMPILE)
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlUsedOfEthIfCtrlType, TCPIP_CODE) TcpIp_IsIpV4CtrlUsedOfEthIfCtrl(TcpIp_EthIfCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlUsedOfEthIfCtrlType) (((boolean)(TcpIp_GetIpV4CtrlIdxOfEthIfCtrl(Index) != TCPIP_NO_IPV4CTRLIDXOFETHIFCTRL)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_InOrderReassemblyOfFragmentationConfigType, TCPIP_CODE) TcpIp_IsInOrderReassemblyOfFragmentationConfig(TcpIp_FragmentationConfigIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_InOrderReassemblyOfFragmentationConfigType) (((!(TcpIp_IsReassemblyBufferDescUsedOfFragmentationConfig(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsArpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpConfigUsedOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ArpTableEntryUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsArpTableEntryUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ArpTableEntryUsedOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpConfigUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpStatusUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpStatusUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpStatusUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsDhcpUserOptionUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_FragmentationConfigUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsFragmentationConfigUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_FragmentationConfigUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_GratuitousArpUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsGratuitousArpUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_GratuitousArpUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumIpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumIpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_HwChecksumIpOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumTcpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumTcpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_HwChecksumTcpOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_HwChecksumUdpOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsHwChecksumUdpOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_HwChecksumUdpOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LlAddrStateUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsLlAddrStateUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_LlAddrStateUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4UsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsMulticastAddrV4UsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MulticastAddrV4UsedOfIpV4CtrlType) (((!(TcpIp_IsAutoIpConfigUsedOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReceiveAllMulticastsOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsReceiveAllMulticastsOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReceiveAllMulticastsOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticArpTableUsedOfIpV4CtrlType, TCPIP_CODE) TcpIp_IsStaticArpTableUsedOfIpV4Ctrl(TcpIp_IpV4CtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticArpTableUsedOfIpV4CtrlType) (((!(TcpIp_IsHwChecksumIcmpOfIpV4Ctrl(Index)))) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4CtrlDefaultUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4CtrlDefaultUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4CtrlDefaultUsedOfIpV4GeneralType) (((boolean)(TcpIp_GetIpV4CtrlDefaultIdxOfIpV4General(Index) != TCPIP_NO_IPV4CTRLDEFAULTIDXOFIPV4GENERAL)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynDhcpUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynDhcpUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynDhcpUsedOfIpV4GeneralType) (((boolean)(TcpIp_GetIpV4SocketDynDhcpIdxOfIpV4General(Index) != TCPIP_NO_IPV4SOCKETDYNDHCPIDXOFIPV4GENERAL)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynIcmpUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynIcmpUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynIcmpUsedOfIpV4GeneralType) (((boolean)(TcpIp_GetIpV4SocketDynIcmpIdxOfIpV4General(Index) != TCPIP_NO_IPV4SOCKETDYNICMPIDXOFIPV4GENERAL)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpV4SocketDynTcpRstUsedOfIpV4GeneralType, TCPIP_CODE) TcpIp_IsIpV4SocketDynTcpRstUsedOfIpV4General(TcpIp_IpV4GeneralIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_IpV4SocketDynTcpRstUsedOfIpV4GeneralType) (((boolean)(TcpIp_GetIpV4SocketDynTcpRstIdxOfIpV4General(Index) != TCPIP_NO_IPV4SOCKETDYNTCPRSTIDXOFIPV4GENERAL)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_MulticastAddrV4UsedOfLocalAddrV4Type, TCPIP_CODE) TcpIp_IsMulticastAddrV4UsedOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_MulticastAddrV4UsedOfLocalAddrV4Type) (((boolean)(TcpIp_GetMulticastAddrV4IdxOfLocalAddrV4(Index) != TCPIP_NO_MULTICASTADDRV4IDXOFLOCALADDRV4)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UnicastAddrV4UsedOfLocalAddrV4Type, TCPIP_CODE) TcpIp_IsUnicastAddrV4UsedOfLocalAddrV4(TcpIp_LocalAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_UnicastAddrV4UsedOfLocalAddrV4Type) (((boolean)(TcpIp_GetUnicastAddrV4IdxOfLocalAddrV4(Index) != TCPIP_NO_UNICASTADDRV4IDXOFLOCALADDRV4)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfAddrAssignmentCfgByPrioType, TCPIP_CODE) TcpIp_GetSizeOfAddrAssignmentCfgByPrio(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfAddrAssignmentCfgByPrioType) TcpIp_GetSizeOfAddrAssignmentCfgByPrioOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfArpConfigType, TCPIP_CODE) TcpIp_GetSizeOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfArpConfigType) TcpIp_GetSizeOfArpConfigOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfArpTableEntryType, TCPIP_CODE) TcpIp_GetSizeOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfArpTableEntryType) TcpIp_GetSizeOfArpTableEntryOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfAutoIpConfigType, TCPIP_CODE) TcpIp_GetSizeOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfAutoIpConfigType) TcpIp_GetSizeOfAutoIpConfigOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfBuf2TxReqMapType, TCPIP_CODE) TcpIp_GetSizeOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfBuf2TxReqMapType) TcpIp_GetSizeOfBuf2TxReqMapOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDefaultMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfDefaultMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfDefaultMulticastAddrV4Type) TcpIp_GetSizeOfDefaultMulticastAddrV4OfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDefaultUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfDefaultUnicastAddrV4Type) TcpIp_GetSizeOfDefaultUnicastAddrV4OfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfDhcpUserOptionType) TcpIp_GetSizeOfDhcpUserOptionOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionBufferType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOptionBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfDhcpUserOptionBufferType) TcpIp_GetSizeOfDhcpUserOptionBufferOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfDhcpUserOptionDynType, TCPIP_CODE) TcpIp_GetSizeOfDhcpUserOptionDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfDhcpUserOptionDynType) TcpIp_GetSizeOfDhcpUserOptionDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfEthIfCtrlType, TCPIP_CODE) TcpIp_GetSizeOfEthIfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfEthIfCtrlType) TcpIp_GetSizeOfEthIfCtrlOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfFragmentationConfigType, TCPIP_CODE) TcpIp_GetSizeOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfFragmentationConfigType) TcpIp_GetSizeOfFragmentationConfigOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfGratuitousArpType, TCPIP_CODE) TcpIp_GetSizeOfGratuitousArp(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfGratuitousArpType) TcpIp_GetSizeOfGratuitousArpOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4CtrlType, TCPIP_CODE) TcpIp_GetSizeOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfIpV4CtrlType) TcpIp_GetSizeOfIpV4CtrlOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4CtrlDynType, TCPIP_CODE) TcpIp_GetSizeOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfIpV4CtrlDynType) TcpIp_GetSizeOfIpV4CtrlDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4GeneralType, TCPIP_CODE) TcpIp_GetSizeOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfIpV4GeneralType) TcpIp_GetSizeOfIpV4GeneralOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfIpV4SocketDynType, TCPIP_CODE) TcpIp_GetSizeOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfIpV4SocketDynType) TcpIp_GetSizeOfIpV4SocketDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLlAddrStateType, TCPIP_CODE) TcpIp_GetSizeOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfLlAddrStateType) TcpIp_GetSizeOfLlAddrStateOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrType, TCPIP_CODE) TcpIp_GetSizeOfLocalAddr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfLocalAddrType) TcpIp_GetSizeOfLocalAddrOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfLocalAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfLocalAddrV4Type) TcpIp_GetSizeOfLocalAddrV4OfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfMulticastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfMulticastAddrV4Type) TcpIp_GetSizeOfMulticastAddrV4OfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfMulticastAddrV4RequestedType, TCPIP_CODE) TcpIp_GetSizeOfMulticastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfMulticastAddrV4RequestedType) TcpIp_GetSizeOfMulticastAddrV4RequestedOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfPhysAddrConfigType, TCPIP_CODE) TcpIp_GetSizeOfPhysAddrConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfPhysAddrConfigType) TcpIp_GetSizeOfPhysAddrConfigOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfReassemblyBufferType) TcpIp_GetSizeOfReassemblyBufferOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBufferDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfReassemblyBufferDescType) TcpIp_GetSizeOfReassemblyBufferDescOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfReassemblyBufferDescDynType, TCPIP_CODE) TcpIp_GetSizeOfReassemblyBufferDescDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfReassemblyBufferDescDynType) TcpIp_GetSizeOfReassemblyBufferDescDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketDynType, TCPIP_CODE) TcpIp_GetSizeOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfSocketDynType) TcpIp_GetSizeOfSocketDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketOwnerConfigType, TCPIP_CODE) TcpIp_GetSizeOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfSocketOwnerConfigType) TcpIp_GetSizeOfSocketOwnerConfigOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfSocketUdpDynType, TCPIP_CODE) TcpIp_GetSizeOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfSocketUdpDynType) TcpIp_GetSizeOfSocketUdpDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticArpEntryType, TCPIP_CODE) TcpIp_GetSizeOfStaticArpEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfStaticArpEntryType) TcpIp_GetSizeOfStaticArpEntryOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticArpTableType, TCPIP_CODE) TcpIp_GetSizeOfStaticArpTable(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfStaticArpTableType) TcpIp_GetSizeOfStaticArpTableOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfStaticUnicastAddrV4RequestedType, TCPIP_CODE) TcpIp_GetSizeOfStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfStaticUnicastAddrV4RequestedType) TcpIp_GetSizeOfStaticUnicastAddrV4RequestedOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElem(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfTxReqElemType) TcpIp_GetSizeOfTxReqElemOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemListType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfTxReqElemListType) TcpIp_GetSizeOfTxReqElemListOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfTxReqElemListDynType, TCPIP_CODE) TcpIp_GetSizeOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfTxReqElemListDynType) TcpIp_GetSizeOfTxReqElemListDynOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueueElementChainType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueueElementChain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfUdpTxRetryQueueElementChainType) TcpIp_GetSizeOfUdpTxRetryQueueElementChainOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueueElementsType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueueElements(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfUdpTxRetryQueueElementsType) TcpIp_GetSizeOfUdpTxRetryQueueElementsOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUdpTxRetryQueuePoolDescType, TCPIP_CODE) TcpIp_GetSizeOfUdpTxRetryQueuePoolDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfUdpTxRetryQueuePoolDescType) TcpIp_GetSizeOfUdpTxRetryQueuePoolDescOfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_SizeOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_GetSizeOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_SizeOfUnicastAddrV4Type) TcpIp_GetSizeOfUnicastAddrV4OfPCConfig();
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DefaultUnicastAddrV4UsedOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_IsDefaultUnicastAddrV4UsedOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DefaultUnicastAddrV4UsedOfUnicastAddrV4Type) (((boolean)(TcpIp_GetDefaultUnicastAddrV4IdxOfUnicastAddrV4(Index) != TCPIP_NO_DEFAULTUNICASTADDRV4IDXOFUNICASTADDRV4)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_StaticUnicastAddrV4RequestedUsedOfUnicastAddrV4Type, TCPIP_CODE) TcpIp_IsStaticUnicastAddrV4RequestedUsedOfUnicastAddrV4(TcpIp_UnicastAddrV4IterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_StaticUnicastAddrV4RequestedUsedOfUnicastAddrV4Type) (((boolean)(TcpIp_GetStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(Index) != TCPIP_NO_STATICUNICASTADDRV4REQUESTEDIDXOFUNICASTADDRV4)) != FALSE);   /* PRQA S 4304 */  /* MD_MSR_AutosarBoolean */
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCSetDataInlineFunctions  TcpIp Set Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to write data.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].NetAddrOfArpTableEntry = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_PhysAddrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].PhysAddrOfArpTableEntry = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthBufPtrOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufPtrOfBuf2TxReqMap = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)] = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveDefGwAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveDefGwAddrOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveNetAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveNetAddrOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetActiveNetMaskOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveNetMaskOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrAssignmentReadyChangedOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentReadyChangedOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentReadyChangedOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLastBcAddrOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].LastBcAddrOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysLinkActiveOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_PhysLinkActiveOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].PhysLinkActiveOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_SockAddrBaseType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].LocSockOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetPhysDestAddrOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].PhysDestAddrOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, IpV4_Ip_TransferBlockType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TransferBlockOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrConflictOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAddrFoundOfLlAddrState(TcpIp_LlAddrStateIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrFoundOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrCandOfLlAddrState(TcpIp_LlAddrStateIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].NetAddrCandOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfMulticastAddrV4Requested(TcpIp_MulticastAddrV4RequestedIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetMulticastAddrV4RequestedOfPCConfig()[(Index)].NetAddrOfMulticastAddrV4Requested = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetReassemblyBufferOfPCConfig()[(Index)] = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index, IpV4_Ip_ReassemblyBufferDescType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetReassemblyBufferDescDynOfPCConfig()[(Index)] = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocSockOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SockAddrBaseType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].LocSockOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetRemSockOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SockAddrBaseType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].RemSockOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxBufRequestedOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxBufRequestedOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].TxBufRequestedOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_IpTxRequestDescriptorType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].IpTxRequestDescriptorOfSocketUdpDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqIpBufPtrOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, P2VAR(uint8, AUTOMATIC, IPV4_APPL_VAR) Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqIpBufPtrOfSocketUdpDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_DListType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueOfSocketUdpDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetDefGwAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].DefGwAddrOfStaticUnicastAddrV4Requested = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetAddrOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].NetAddrOfStaticUnicastAddrV4Requested = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetNetMaskOfStaticUnicastAddrV4Requested(TcpIp_StaticUnicastAddrV4RequestedIterType Index, IpBase_AddrInType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig()[(Index)].NetMaskOfStaticUnicastAddrV4Requested = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetTxReqElemTransmittedOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemTransmittedOfTxReqElemType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemTransmittedOfTxReqElem = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index, TcpIp_DListNodeType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetUdpTxRetryQueueElementChainOfPCConfig()[(Index)] = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index, TcpIp_Udp_RetryQueueElementType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetUdpTxRetryQueueElementsOfPCConfig()[(Index)] = (Value);
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SetUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index, TcpIp_DListDescType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetUdpTxRetryQueuePoolDescOfPCConfig()[(Index)] = (Value);
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCGetAddressOfDataInlineFunctions  TcpIp Get Address Of Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrOfArpTableEntryPtrType, TCPIP_CODE) TcpIp_GetAddrPhysAddrOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetArpTableEntryOfPCConfig()[(Index)].PhysAddrOfArpTableEntry));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_DhcpUserOptionBufferPtrType, TCPIP_CODE) TcpIp_GetAddrDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_DhcpUserOptionBufferPtrType) (&(TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)]));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocSockOfIpV4SocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrLocSockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].LocSockOfIpV4SocketDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TransferBlockOfIpV4SocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrTransferBlockOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TransferBlockOfIpV4SocketDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferPtrType, TCPIP_CODE) TcpIp_GetAddrReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (TcpIp_ReassemblyBufferPtrType) (&(TcpIp_GetReassemblyBufferOfPCConfig()[(Index)]));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_ReassemblyBufferDescDynPtrType, TCPIP_CODE) TcpIp_GetAddrReassemblyBufferDescDyn(TcpIp_ReassemblyBufferDescDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetReassemblyBufferDescDynOfPCConfig()[(Index)]));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_LocSockOfSocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrLocSockOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetSocketDynOfPCConfig()[(Index)].LocSockOfSocketDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_RemSockOfSocketDynPtrType, TCPIP_CODE) TcpIp_GetAddrRemSockOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetSocketDynOfPCConfig()[(Index)].RemSockOfSocketDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_IpTxRequestDescriptorOfSocketUdpDynPtrType, TCPIP_CODE) TcpIp_GetAddrIpTxRequestDescriptorOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].IpTxRequestDescriptorOfSocketUdpDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_TxRetrQueueOfSocketUdpDynPtrType, TCPIP_CODE) TcpIp_GetAddrTxRetrQueueOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueOfSocketUdpDyn));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_PhysAddrOfStaticArpEntryPtrType, TCPIP_CODE) TcpIp_GetAddrPhysAddrOfStaticArpEntry(TcpIp_StaticArpEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetStaticArpEntryOfPCConfig()[(Index)].PhysAddrOfStaticArpEntry));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueueElementChainPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueueElementChain(TcpIp_UdpTxRetryQueueElementChainIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetUdpTxRetryQueueElementChainOfPCConfig()[(Index)]));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueueElementsPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueueElements(TcpIp_UdpTxRetryQueueElementsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetUdpTxRetryQueueElementsOfPCConfig()[(Index)]));
}
TCPIP_LOCAL_INLINE FUNC(TcpIp_UdpTxRetryQueuePoolDescPtrType, TCPIP_CODE) TcpIp_GetAddrUdpTxRetryQueuePoolDesc(TcpIp_UdpTxRetryQueuePoolDescIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (&(TcpIp_GetUdpTxRetryQueuePoolDescOfPCConfig()[(Index)]));
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCHasInlineFunctions  TcpIp Has Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrio(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetArpConfigOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEntryTimeoutOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNumGratuitousArpOnStartupOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPacketQueueEnabledOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRequestTimeoutOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRetryIntervalOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRetryTimeOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTableSizeOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetArpTableEntryOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCreationTimeStampOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStatusOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTimeStampOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetAutoIpConfigOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrCalloutFuncOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceIntervalMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceNumOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceWaitMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefendIntervalMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxConflictsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeMaxMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeMinMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeWaitMaxMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeWaitMinMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRateLimitIntervalMsOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufIdxNextOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufLenOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthBufPtrOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDynIdxOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUlTxReqIdxOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetDefaultMulticastAddrV4OfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfDefaultMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetDefaultUnicastAddrV4OfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefGwAddrOfDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetMaskOfDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetDhcpUserOptionOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCodeOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferEndIdxOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferLengthOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferStartIdxOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDirectionOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetDhcpUserOptionBufferOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetDhcpUserOptionDynOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLengthOfDhcpUserOptionDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDuplicateAddrDetectionFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfEthIfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlUsedOfEthIfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetFragmentationConfigOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasInOrderReassemblyOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxPacketSizeOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescEndIdxOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescLengthOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescStartIdxOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescUsedOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyTimeoutMsOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArp(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetGratuitousArpOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNextTransmissionMsOfGratuitousArp(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTransmissionCntOfGratuitousArp(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIcmpMsgHandlerCbkFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioEndIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioStartIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentPrioByTypeOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryEndIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryStartIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapEndIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapStartIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultTtlOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpConfigIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpConfigUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpStatusIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpStatusUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionEndIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionStartIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrlIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFramePrioDefaultOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumIcmpOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumIpOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumTcpOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasHwChecksumUdpOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4BroadcastIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4UnicastIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMaxTxMsgSizeOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMtuTxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4EndIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4StartIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4UsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReceiveAllMulticastsOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableIdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableUsedOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTypeOfServiceDefaultOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4IdxOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveAddrAssignmentMethodOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveDefGwAddrOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveNetAddrOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasActiveNetMaskOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentReadyChangedOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLastBcAddrOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysLinkActiveOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStateOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDefaultIdxOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDefaultUsedOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynDhcpIdxOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynDhcpUsedOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynIcmpIdxOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynIcmpUsedOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynTcpRstIdxOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynTcpRstUsedOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryIdxOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfFramePrioOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFlagsOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocSockOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysDestAddrOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProtocolOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTimeToLiveOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTransferBlockOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxDescriptorProtocolOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTypeOfServiceOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetLlAddrStateOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrConflictOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrConflictTimeoutOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrFoundOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnStateOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAnnounceNumOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasConflictsNumOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMsecCntOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrCandOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeNumSinceConfOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasProbeStateOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStateOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasWaitUntilTimeOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAssignmentStateOfLocalAddr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlIdxOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4IdxOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4UsedOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4IdxOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4UsedOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetMulticastAddrV4OfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4IdxOfMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4IdxOfMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetMulticastAddrV4RequestedOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfMulticastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetPhysAddrConfigOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasChgDiscardedFuncPtrOfPhysAddrConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasChgFuncPtrOfPhysAddrConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRandomNumberFctPtr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetReassemblyBufferOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetReassemblyBufferDescOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferEndIdxOfReassemblyBufferDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferStartIdxOfReassemblyBufferDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetReassemblyBufferDescDynOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAddrAssignmentCfgByPrio(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpTableEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAutoIpConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfBuf2TxReqMap(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOption(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfEthIfCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfFragmentationConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfGratuitousArp(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4Ctrl(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4General(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4SocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLlAddrState(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddr(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfPhysAddrConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpTable(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElem(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementChain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElements(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueuePoolDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasListenActiveConnStatOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocSockOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrBindIdxOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRemSockOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfigIdxOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxBufRequestedOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxIpAddrIdxOfSocketDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCopyTxDataDynFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasCopyTxDataFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpEventFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalIpAddrAssignmentChgFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRxIndicationFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpAcceptedFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpConnectedFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTcpIpEventFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTlsValidationResultFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxConfirmationFuncPtrOfSocketOwnerConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpTxRequestDescriptorOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListIdxOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqIpBufPtrOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxRetrQueueMaxNumOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxRetrQueueOfSocketUdpDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetStaticArpEntryOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpAddrOfStaticArpEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrOfStaticArpEntry(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTable(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetStaticArpTableOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryEndIdxOfStaticArpTable(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryStartIdxOfStaticArpTable(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetStaticUnicastAddrV4RequestedOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefGwAddrOfStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetAddrOfStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasNetMaskOfStaticUnicastAddrV4Requested(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElem(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetTxReqElemOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemDataLenByteOfTxReqElem(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemTransmittedOfTxReqElem(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetTxReqElemListOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemEndIdxOfTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemLengthOfTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemStartIdxOfTxReqElemList(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetTxReqElemListDynOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFillNumOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReadPosOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDynIdxOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasWritePosOfTxReqElemListDyn(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementChain(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetUdpTxRetryQueueElementChainOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElements(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetUdpTxRetryQueueElementsOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueuePoolDesc(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetUdpTxRetryQueuePoolDescOfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TcpIp_GetUnicastAddrV4OfPCConfig() != NULL_PTR);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4IdxOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4UsedOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedIdxOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedUsedOfUnicastAddrV4(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAddrAssignmentCfgByPrioOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasArpTableEntryOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasAutoIpConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasBuf2TxReqMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultMulticastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDefaultUnicastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDhcpUserOptionOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasDuplicateAddrDetectionFctPtrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasEthIfCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasFragmentationConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasGratuitousArpOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIcmpMsgHandlerCbkFctPtrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4CtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4GeneralOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasIpV4SocketDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLlAddrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasLocalAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasMulticastAddrV4RequestedOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasPhysAddrConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasRandomNumberFctPtrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferDescOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasReassemblyBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAddrAssignmentCfgByPrioOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfArpTableEntryOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfAutoIpConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfBuf2TxReqMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultMulticastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDefaultUnicastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfDhcpUserOptionOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfEthIfCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfFragmentationConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfGratuitousArpOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4CtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4GeneralOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfIpV4SocketDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLlAddrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfLocalAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfMulticastAddrV4RequestedOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfPhysAddrConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferDescOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfReassemblyBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketOwnerConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfSocketUdpDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpEntryOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticArpTableOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfStaticUnicastAddrV4RequestedOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfTxReqElemOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementChainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueueElementsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUdpTxRetryQueuePoolDescOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSizeOfUnicastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketOwnerConfigOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasSocketUdpDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpEntryOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticArpTableOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasStaticUnicastAddrV4RequestedOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListDynOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemListOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasTxReqElemOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementChainOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueueElementsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUdpTxRetryQueuePoolDescOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
TCPIP_LOCAL_INLINE FUNC(boolean, TCPIP_CODE) TcpIp_HasUnicastAddrV4OfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  return (boolean) (TRUE != FALSE);   /* PRQA S 2995, 4304 */  /* MD_MSR_ConstantCondition, MD_MSR_AutosarBoolean */
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCIncrementInlineFunctions  TcpIp Increment Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)]++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetReassemblyBufferOfPCConfig()[(Index)]++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_IncWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn++;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCDecrementInlineFunctions  TcpIp Decrement Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)]--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecStateOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetReassemblyBufferOfPCConfig()[(Index)]--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_DecWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn--;  /* PRQA S 3387 */  /* MD_CSL_InlineFunction_IncrementDecrement */
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCAddInlineFunctions  TcpIp Add Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to add VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetCreationTimeStampOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStatusOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTimeStampOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthBufLenOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketDynIdxOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetUlTxReqIdxOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetDhcpUserOptionBuffer(Index, (TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)] + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetLengthOfDhcpUserOptionDyn(Index, (TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetNextTransmissionMsOfGratuitousArp(Index, (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTransmissionCntOfGratuitousArp(Index, (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStateOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthIfFramePrioOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetFlagsOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProtocolOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTimeToLiveOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxDescriptorProtocolOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTypeOfServiceOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAddrConflictTimeoutOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAnnStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAnnounceNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetConflictsNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetMsecCntOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeNumSinceConfOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetWaitUntilTimeOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAssignmentStateOfLocalAddr(Index, (TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetReassemblyBuffer(Index, (TcpIp_GetReassemblyBufferOfPCConfig()[(Index)] + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetListenActiveConnStatOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetLocalAddrBindIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxIpAddrIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(Index, (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(Index, (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxReqElemDataLenByteOfTxReqElem(Index, (TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetFillNumOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetReadPosOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn + Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_AddWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetWritePosOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn + Value));
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

#define TCPIP_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/** 
  \defgroup  TcpIpPCSubstractInlineFunctions  TcpIp Substract Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to substract VAR data with numerical nature.
  \{
*/ 
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubCreationTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_CreationTimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetCreationTimeStampOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].CreationTimeStampOfArpTableEntry - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStatusOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_StatusOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStatusOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].StatusOfArpTableEntry - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTimeStampOfArpTableEntry(TcpIp_ArpTableEntryIterType Index, TcpIp_TimeStampOfArpTableEntryType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTimeStampOfArpTableEntry(Index, (TcpIp_GetArpTableEntryOfPCConfig()[(Index)].TimeStampOfArpTableEntry - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthBufIdxNextOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufIdxNextOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthBufIdxNextOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufIdxNextOfBuf2TxReqMap - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthBufLenOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_EthBufLenOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthBufLenOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].EthBufLenOfBuf2TxReqMap - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketDynIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_SocketDynIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketDynIdxOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].SocketDynIdxOfBuf2TxReqMap - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubUlTxReqIdxOfBuf2TxReqMap(TcpIp_Buf2TxReqMapIterType Index, TcpIp_UlTxReqIdxOfBuf2TxReqMapType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetUlTxReqIdxOfBuf2TxReqMap(Index, (TcpIp_GetBuf2TxReqMapOfPCConfig()[(Index)].UlTxReqIdxOfBuf2TxReqMap - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubDhcpUserOptionBuffer(TcpIp_DhcpUserOptionBufferIterType Index, TcpIp_DhcpUserOptionBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetDhcpUserOptionBuffer(Index, (TcpIp_GetDhcpUserOptionBufferOfPCConfig()[(Index)] - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubLengthOfDhcpUserOptionDyn(TcpIp_DhcpUserOptionDynIterType Index, TcpIp_LengthOfDhcpUserOptionDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetLengthOfDhcpUserOptionDyn(Index, (TcpIp_GetDhcpUserOptionDynOfPCConfig()[(Index)].LengthOfDhcpUserOptionDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubNextTransmissionMsOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_NextTransmissionMsOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetNextTransmissionMsOfGratuitousArp(Index, (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].NextTransmissionMsOfGratuitousArp - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTransmissionCntOfGratuitousArp(TcpIp_GratuitousArpIterType Index, TcpIp_TransmissionCntOfGratuitousArpType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTransmissionCntOfGratuitousArp(Index, (TcpIp_GetGratuitousArpOfPCConfig()[(Index)].TransmissionCntOfGratuitousArp - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubActiveAddrAssignmentMethodOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_ActiveAddrAssignmentMethodOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetActiveAddrAssignmentMethodOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].ActiveAddrAssignmentMethodOfIpV4CtrlDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_AddrAssignmentTriggeredFlagsOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAddrAssignmentTriggeredFlagsOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].AddrAssignmentTriggeredFlagsOfIpV4CtrlDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStateOfIpV4CtrlDyn(TcpIp_IpV4CtrlDynIterType Index, TcpIp_StateOfIpV4CtrlDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStateOfIpV4CtrlDyn(Index, (TcpIp_GetIpV4CtrlDynOfPCConfig()[(Index)].StateOfIpV4CtrlDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubArpTableEntryIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ArpTableEntryIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetArpTableEntryIdxOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ArpTableEntryIdxOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubEthIfFramePrioOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_EthIfFramePrioOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetEthIfFramePrioOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].EthIfFramePrioOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubFlagsOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_FlagsOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetFlagsOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].FlagsOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubIpV4CtrlIdxOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_IpV4CtrlIdxOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetIpV4CtrlIdxOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].IpV4CtrlIdxOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_ProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProtocolOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].ProtocolOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTimeToLiveOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TimeToLiveOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTimeToLiveOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TimeToLiveOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxDescriptorProtocolOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TxDescriptorProtocolOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxDescriptorProtocolOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TxDescriptorProtocolOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTypeOfServiceOfIpV4SocketDyn(TcpIp_IpV4SocketDynIterType Index, TcpIp_TypeOfServiceOfIpV4SocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTypeOfServiceOfIpV4SocketDyn(Index, (TcpIp_GetIpV4SocketDynOfPCConfig()[(Index)].TypeOfServiceOfIpV4SocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAddrConflictTimeoutOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AddrConflictTimeoutOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAddrConflictTimeoutOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AddrConflictTimeoutOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAnnStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAnnStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnStateOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAnnounceNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_AnnounceNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAnnounceNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].AnnounceNumOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubConflictsNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ConflictsNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetConflictsNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ConflictsNumOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubMsecCntOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_MsecCntOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetMsecCntOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].MsecCntOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeNumOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeNumOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeNumSinceConfOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeNumSinceConfOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeNumSinceConfOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeNumSinceConfOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubProbeStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_ProbeStateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetProbeStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].ProbeStateOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubStateOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_StateOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetStateOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].StateOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubWaitUntilTimeOfLlAddrState(TcpIp_LlAddrStateIterType Index, TcpIp_WaitUntilTimeOfLlAddrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetWaitUntilTimeOfLlAddrState(Index, (TcpIp_GetLlAddrStateOfPCConfig()[(Index)].WaitUntilTimeOfLlAddrState - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubAssignmentStateOfLocalAddr(TcpIp_LocalAddrIterType Index, TcpIp_AssignmentStateOfLocalAddrType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetAssignmentStateOfLocalAddr(Index, (TcpIp_GetLocalAddrOfPCConfig()[(Index)].AssignmentStateOfLocalAddr - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubReassemblyBuffer(TcpIp_ReassemblyBufferIterType Index, TcpIp_ReassemblyBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetReassemblyBuffer(Index, (TcpIp_GetReassemblyBufferOfPCConfig()[(Index)] - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubListenActiveConnStatOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_ListenActiveConnStatOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetListenActiveConnStatOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].ListenActiveConnStatOfSocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubLocalAddrBindIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_LocalAddrBindIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetLocalAddrBindIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].LocalAddrBindIdxOfSocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketOwnerConfigIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_SocketOwnerConfigIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketOwnerConfigIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].SocketOwnerConfigIdxOfSocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxIpAddrIdxOfSocketDyn(TcpIp_SocketDynIterType Index, TcpIp_TxIpAddrIdxOfSocketDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxIpAddrIdxOfSocketDyn(Index, (TcpIp_GetSocketDynOfPCConfig()[(Index)].TxIpAddrIdxOfSocketDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxReqElemListIdxOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxReqElemListIdxOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxReqElemListIdxOfSocketUdpDyn(Index, (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxReqElemListIdxOfSocketUdpDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxRetrQueueMaxNumOfSocketUdpDyn(TcpIp_SocketUdpDynIterType Index, TcpIp_TxRetrQueueMaxNumOfSocketUdpDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxRetrQueueMaxNumOfSocketUdpDyn(Index, (TcpIp_GetSocketUdpDynOfPCConfig()[(Index)].TxRetrQueueMaxNumOfSocketUdpDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubTxReqElemDataLenByteOfTxReqElem(TcpIp_TxReqElemIterType Index, TcpIp_TxReqElemDataLenByteOfTxReqElemType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetTxReqElemDataLenByteOfTxReqElem(Index, (TcpIp_GetTxReqElemOfPCConfig()[(Index)].TxReqElemDataLenByteOfTxReqElem - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubFillNumOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_FillNumOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetFillNumOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].FillNumOfTxReqElemListDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubReadPosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_ReadPosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetReadPosOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].ReadPosOfTxReqElemListDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubSocketUdpDynIdxOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_SocketUdpDynIdxOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetSocketUdpDynIdxOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].SocketUdpDynIdxOfTxReqElemListDyn - Value));
}
TCPIP_LOCAL_INLINE FUNC(void, TCPIP_CODE) TcpIp_SubWritePosOfTxReqElemListDyn(TcpIp_TxReqElemListDynIterType Index, TcpIp_WritePosOfTxReqElemListDynType Value)  /* PRQA S 3219 */  /* MD_MSR_Unreachable */
{
  TcpIp_SetWritePosOfTxReqElemListDyn(Index, (TcpIp_GetTxReqElemListDynOfPCConfig()[(Index)].WritePosOfTxReqElemListDyn - Value));
}
/** 
  \}
*/ 

#define TCPIP_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


#endif

/**********************************************************************************************************************
 *  USER FUNCTIONS
 *********************************************************************************************************************/
 #define TCPIP_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/* TcpIp_<Up>GetSocket ----------------------------------------------------- */
extern FUNC(Std_ReturnType, TCPIP_CODE) TcpIp_SoAdGetSocket(
    TcpIp_DomainType                                      Domain,
    TcpIp_ProtocolType                                    Protocol,
    P2VAR(TcpIp_SocketIdType, AUTOMATIC, TCPIP_APPL_DATA) SocketIdPtr);
 

#define TCPIP_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           <USERBLOCK TCPIP>
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           </USERBLOCK>
 *********************************************************************************************************************/


#endif  /* TCPIP_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Lcfg.h
 *********************************************************************************************************************/
