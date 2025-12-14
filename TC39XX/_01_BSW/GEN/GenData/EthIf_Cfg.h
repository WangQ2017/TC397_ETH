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
 *            Module: EthIf
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthIf_Cfg.h
 *   Generation Time: 2025-12-14 17:03:56
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETHIF_CFG_H)
# define ETHIF_CFG_H

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#ifndef ETHIF_USE_DUMMY_STATEMENT
#define ETHIF_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHIF_DUMMY_STATEMENT
#define ETHIF_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHIF_DUMMY_STATEMENT_CONST
#define ETHIF_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHIF_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ETHIF_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ETHIF_ATOMIC_VARIABLE_ACCESS
#define ETHIF_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef ETHIF_PROCESSOR_TC397X_STEPB
#define ETHIF_PROCESSOR_TC397X_STEPB
#endif
#ifndef ETHIF_COMP_TASKING
#define ETHIF_COMP_TASKING
#endif
#ifndef ETHIF_GEN_GENERATOR_MSR
#define ETHIF_GEN_GENERATOR_MSR
#endif
#ifndef ETHIF_CPUTYPE_BITORDER_LSB2MSB
#define ETHIF_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef ETHIF_CONFIGURATION_VARIANT_PRECOMPILE
#define ETHIF_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ETHIF_CONFIGURATION_VARIANT_LINKTIME
#define ETHIF_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ETHIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ETHIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ETHIF_CONFIGURATION_VARIANT
#define ETHIF_CONFIGURATION_VARIANT ETHIF_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ETHIF_POSTBUILD_VARIANT_SUPPORT
#define ETHIF_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
 *  SNVS (SYMBOLIC NAME DEFINES)
 *********************************************************************************************************************/
#define EthIfConf_EthIfController_EthIfController_Vlan10 (0uL)
#define EthIfConf_EthIfFrameOwnerConfig_TcpIp_IPv4 (0uL)
#define EthIfConf_EthIfFrameOwnerConfig_TcpIp_ARP (1uL)
#define EthIfConf_EthIfFrameOwnerConfig_EthTSyn (2uL)

/**********************************************************************************************************************
 *  FEATURE SWITCHES
 *********************************************************************************************************************/
# define ETHIF_DEV_ERROR_DETECT                 (STD_ON)
# define ETHIF_DEV_ERROR_REPORT                 (STD_ON)
# define ETHIF_ENABLE_RX_INTERRUPT              (STD_OFF)
# define ETHIF_ENABLE_TX_INTERRUPT              (STD_ON)
# define ETHIF_VERSION_INFO_API                 (STD_OFF)
# define ETHIF_ENABLE_UPDATE_PHYS_ADDR_FILTER   (STD_ON)
# define ETHIF_ENABLE_MAIN_FUNCTION_STATE       (STD_ON)
# define ETHIF_ENABLE_SIGNAL_QUALITY_API        (STD_OFF)
# define ETHIF_ENABLE_ZERO_COPY_EXTENSIONS      (STD_OFF)
# define ETHIF_ENABLE_HEADER_ACCESS_API         (STD_OFF)
# define ETHIF_GLOBAL_TIME_SUPPORT              (STD_ON)
# define ETHIF_WAKEUP_SUPPORT                   (STD_OFF)
# define ETHIF_DYNAMIC_TRAFFIC_SHAPING_SUPPORT  (STD_OFF)
# define ETHIF_SWT_PORT_GROUP_MODE_REQ_SUPPORT  (STD_OFF)
# define ETHIF_FIREWALL_SUPPORT                 (STD_OFF)
# define ETHIF_MEASUREMENT_DATA_SUPPORT         (STD_OFF)
# define ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE   ETHIF_NO_EXTENDED_TRAFFIC_HANDLING
# define ETHIF_ENABLE_SECURITY_EVENT_REPORTING  (STD_OFF)
# define ETHIF_MULTI_CORE_SUPPORT               (STD_OFF)

/**********************************************************************************************************************
 *  ETHERNET TRANSCEIVER DEFINES
 *********************************************************************************************************************/
# define ETHIF_ETHTRCV_USED                        (STD_ON)

/**********************************************************************************************************************
 *  ETHERNET SWITCH DEFINES
 *********************************************************************************************************************/
# define ETHIF_ETHSWT_USED                         (STD_OFF)
# define ETHIF_STORE_CONFIG_API                    (STD_OFF)
# define ETHIF_RESET_CONFIG_API                    (STD_OFF)
# define ETHIF_GET_DROP_COUNT_API                  (STD_OFF)
# define ETHIF_GET_BUFFER_LEVEL_API                (STD_OFF)
# define ETHIF_GET_ARL_TABLE_API                   (STD_OFF)
# define ETHIF_GET_PORT_MAC_ADDR_API               (STD_OFF)
# define ETHIF_SWITCH_UPDATE_MCAST_PORT_ASSIGN_API (STD_OFF)
# define ETHIF_ETHSWT_FRAME_MANAGEMENT_SUPPORT     (STD_OFF)
# define ETHIF_ETHSWT_TIME_STAMP_SUPPORT           (STD_OFF)
# define ETHIF_SWITCH_ENABLE_VLAN_API              (STD_OFF)

/**********************************************************************************************************************
 *  References to security events for the IdsM
 *********************************************************************************************************************/
# define ETHIF_SEV_INVALID                             (0xFFFFu)
# define ETHIF_SEV_DROPPED_UNKNOWN_ETHERTYPE_DATAGRAM  ETHIF_SEV_INVALID
# define ETHIF_SEV_DROPPED_VLAN_DOUBLE_TAG_DATAGRAM    ETHIF_SEV_INVALID
# define ETHIF_SEV_DROPPED_INVALID_CTRLIDX_DATAGRAM    ETHIF_SEV_INVALID
# define ETHIF_SEV_ETH_MAC_COLLISION                   ETHIF_SEV_INVALID


#endif /* ETHIF_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Cfg.h
 *********************************************************************************************************************/


