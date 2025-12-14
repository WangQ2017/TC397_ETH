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
 *              File: TcpIp_Cfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined(TCPIP_CFG_H)
#define TCPIP_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  TCPIP SWITCH DEFINES
 *********************************************************************************************************************/
#define TCPIP_VERSION_INFO_API                     STD_OFF
#define TCPIP_DEV_ERROR_DETECT                     STD_ON
#define TCPIP_DEV_ERROR_REPORT                     STD_ON

#define TCPIP_SUPPORT_DHCPV4                       STD_OFF

#define TCPIP_SUPPORT_DHCPV6                       STD_OFF
#define TCPIP_SUPPORT_DHCPV6_OPTIONS               STD_OFF

#define TCPIP_SUPPORT_TCP                          STD_OFF
#define TCPIP_SUPPORT_DNS                          STD_OFF
#define TCPIP_SUPPORT_DEM                          STD_OFF
#define TCPIP_SUPPORT_IPV4                         STD_ON
#define TCPIP_SUPPORT_IPV6                         STD_OFF
#define TCPIP_SUPPORT_SOAD                         STD_ON
#define TCPIP_SUPPORT_TLS                          STD_OFF
#define TCPIP_SUPPORT_ICMPV4                       STD_OFF
#define TCPIP_SUPPORT_DHCPV4SERVER                 STD_OFF
#define TCPIP_SUPPORT_DIAG_ACCESS_EXTENSIONS       STD_OFF
#define TCPIP_SUPPORT_MEASUREMENT_DATA             STD_OFF
#define TCPIP_SUPPORT_IPSEC                        STD_OFF

#define TCPIP_SINGLE_MAIN_FUNCTION_ENABLED         STD_ON


#define TCPIP_SUPPORT_IP_ETHIF_ADDR_FILTER_API     STD_ON
#define TCPIP_SUPPORT_IP_ADDR_NVM_STORAGE          STD_OFF

#define TCPIP_SUPPORT_ICMPV4_DST_UNREACHABLE_MSG   STD_OFF

#define TCPIP_SUPPORT_ARP_DISCARDED_ENTRY_HANDLING STD_OFF



#define TCPIP_TCP_DIAG_READ_ACK_SEQ_NUM_ENABLED    STD_OFF


#define TCPIP_MAIN_FCT_PERIOD_MSEC                 5u



/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: LOCAL ADRESSES
 *********************************************************************************************************************/
#define TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Fixed_10_10_7_33 (0uL)
#define TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_TcpIpCtrl_Vlan10_Broadcast (2uL)
#define TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr_NE_Multicast_Rx_fixed_239_10_0_1 (1uL)

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: SOCKET USERS
 *********************************************************************************************************************/
#define TcpIpConf_TcpIpSocketOwner_SoAd (0uL)

/**********************************************************************************************************************
 *  MODULE SPECIFIC DEFINES
 *********************************************************************************************************************/
#ifndef TCPIP_USE_DUMMY_STATEMENT
#define TCPIP_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef TCPIP_DUMMY_STATEMENT
#define TCPIP_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef TCPIP_DUMMY_STATEMENT_CONST
#define TCPIP_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef TCPIP_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define TCPIP_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef TCPIP_ATOMIC_VARIABLE_ACCESS
#define TCPIP_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef TCPIP_PROCESSOR_TC397X_STEPB
#define TCPIP_PROCESSOR_TC397X_STEPB
#endif
#ifndef TCPIP_COMP_TASKING
#define TCPIP_COMP_TASKING
#endif
#ifndef TCPIP_GEN_GENERATOR_MSR
#define TCPIP_GEN_GENERATOR_MSR
#endif
#ifndef TCPIP_CPUTYPE_BITORDER_LSB2MSB
#define TCPIP_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef TCPIP_CONFIGURATION_VARIANT_PRECOMPILE
#define TCPIP_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef TCPIP_CONFIGURATION_VARIANT_LINKTIME
#define TCPIP_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef TCPIP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define TCPIP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef TCPIP_CONFIGURATION_VARIANT
#define TCPIP_CONFIGURATION_VARIANT TCPIP_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef TCPIP_POSTBUILD_VARIANT_SUPPORT
#define TCPIP_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/* User Config File Start */

/* User Config File End */


#endif /* TCPIP_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: TcpIp_Cfg.h
 *********************************************************************************************************************/
