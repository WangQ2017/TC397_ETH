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
 *              File: DoIP_Cfg.h
 *   Generation Time: 2026-02-08 21:29:40
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#if !defined(DOIP_CFG_H)
# define DOIP_CFG_H

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP PDUR RX PDU (CHANNEL)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPPduRRxPdu_DoIPPduRRxPdu_Func_Req                 1u
#define DoIPConf_DoIPPduRRxPdu_DoIPPduRRxPdu_Phy_Req                  0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP PDUR TX PDU (CHANNEL)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPPduRTxPdu_DoIPPduRTxPdu_Phy_Res                  0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP SOAD TCP RX PDU (CONNECTION)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPSoAdTcpRxPdu_DoIPSoAdTcpRxPdu_TCP_DATA1_Rx       1u
#define DoIPConf_DoIPSoAdTcpRxPdu_DoIPSoAdTcpRxPdun_TCP_DATA0_Rx      0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP SOAD TCP TX PDU (CONNECTION)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPSoAdTcpTxPdu_DoIPSoAdTcpTxPdu_TCP_DATA1_Tx       1u
#define DoIPConf_DoIPSoAdTcpTxPdu_DoIPSoAdTcpTxPdun_TCP_DATA0_Tx      0u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP SOAD UDP RX PDU (CONNECTION)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPSoAdUdpRxPdu_DoIPSoAdUdpRxPdu_UDP_TEST_EQUIPMENT_REQUEST_Rx 2u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP SOAD UDP TX PDU (CONNECTION)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPSoAdUdpTxPdu_DoIPSoAdUdpTxPdu_UDP_TEST_EQUIPMENT_REQUEST_Tx 2u
/**\} */

/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES: DOIP SOAD UDP VEHICLE ANNOUNCEMENT TX PDU (CONNECTION)
 *********************************************************************************************************************/



/**
 * \defgroup DoIPHandleIds Handle IDs.
 * \{
 */

/* Handle IDs active in all predefined variants (the application has not to take the active variant into account) */
/*      Symbolic Name                                                 Value   Active in predefined variant(s) */
#define DoIPConf_DoIPSoAdUdpVehicleAnnouncementTxPdu_DoIPSoAdUdpVehicleAnnouncementTxPdu_UDP_DISCOVERY_Tx 3u
/**\} */

/**********************************************************************************************************************
 *  MODULE SPECIFIC DEFINES
 *********************************************************************************************************************/
#ifndef DOIP_USE_DUMMY_STATEMENT
#define DOIP_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DOIP_DUMMY_STATEMENT
#define DOIP_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DOIP_DUMMY_STATEMENT_CONST
#define DOIP_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef DOIP_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define DOIP_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef DOIP_ATOMIC_VARIABLE_ACCESS
#define DOIP_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef DOIP_PROCESSOR_TC397X_STEPB
#define DOIP_PROCESSOR_TC397X_STEPB
#endif
#ifndef DOIP_COMP_TASKING
#define DOIP_COMP_TASKING
#endif
#ifndef DOIP_GEN_GENERATOR_MSR
#define DOIP_GEN_GENERATOR_MSR
#endif
#ifndef DOIP_CPUTYPE_BITORDER_LSB2MSB
#define DOIP_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef DOIP_CONFIGURATION_VARIANT_PRECOMPILE
#define DOIP_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef DOIP_CONFIGURATION_VARIANT_LINKTIME
#define DOIP_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef DOIP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define DOIP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef DOIP_CONFIGURATION_VARIANT
#define DOIP_CONFIGURATION_VARIANT DOIP_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef DOIP_POSTBUILD_VARIANT_SUPPORT
#define DOIP_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
 *  SWITCH DEFINES
 *********************************************************************************************************************/
# define DOIP_DEV_ERROR_DETECT                   STD_ON
# define DOIP_DEV_ERROR_REPORT                   STD_ON
# define DOIP_SUPPORT_SHUTDOWN                   STD_OFF
# define DOIP_SHUTDOWN_FINISHED_CBK_SUPPORT      STD_OFF
# define DOIP_NACK_APPEND_REQ                    STD_ON
# define DOIP_ENTITY_STATE_SUPPORT               STD_OFF
# define DOIP_ENTITY_STATUS_MAX_BYTE_FIELD_USE   STD_OFF
# define DOIP_VIN_GID_SYNC                       STD_OFF
# define DOIP_GID_SYNC_ENABLED                   STD_OFF
# define DOIP_VEHICLE_IDENT_EID_SUPPORT          STD_OFF
# define DOIP_SUPPORT_PDU_SIZE_ROUTING           STD_OFF
# define DOIP_PROVIDE_CANCEL_TRANSMIT_API        STD_OFF
# define DOIP_PROVIDE_CANCEL_RECEIVE_API         STD_OFF
# define DOIP_VERSION_INFO_API                   STD_OFF
# define DOIP_DEFAULT_TESTER_ENABLED             STD_OFF
# define DOIP_USE_MAC_ADDR_FOR_IDENT             STD_OFF
# define DOIP_USE_EID_AS_GID                     STD_OFF
# define DOIP_VIN_GID_MASTER                     STD_OFF
# define DOIP_GID_AVAILABLE                      STD_ON
# define DOIP_TESTER_WITH_CEN_SEC_AVAILABLE      STD_OFF
# define DOIP_DHCP_OPTION_VIN_USE_ENABLED        STD_OFF
# define DOIP_ACTIV_LINE_DEFAULT_ACTIVE          STD_ON
# define DOIP_ACTIV_LINE_CALLBACK_ENABLED        STD_OFF
# define DOIP_OEM_PAYLOAD_TYPE_ENABLED           STD_OFF
# define DOIP_TARGET_ADDR_BIT_MASK_ENABLED       STD_OFF
# define DOIP_VERIFY_TARGET_ADDR_ENABLED         STD_OFF
# define DOIP_TP_OPTIMIZED_ENABLED               STD_OFF
# define DOIP_ROUT_ACT_AUTH_REM_ADDR_ENABLED     STD_OFF
# define DOIP_ROUT_ACT_CONF_REM_ADDR_ENABLED     STD_OFF
# define DOIP_VERIFY_RX_PDU_ENABLED              STD_OFF
# define DOIP_IPV4_ENABLED                       STD_ON
# define DOIP_IPV6_ENABLED                       STD_OFF
# define DOIP_CONTROL_IP_ASSIGNMENT              STD_OFF
# define DOIP_TCP_RX_MULTI_MSG                   STD_OFF
# define DOIP_IPADDR_ASSIGN_STATIC               STD_ON
# define DOIP_IPADDR_ASSIGN_LINKLOCAL            STD_OFF
# define DOIP_IPADDR_ASSIGN_LINKLOCAL_DOIP       STD_OFF
# define DOIP_IPADDR_ASSIGN_DHCP                 STD_ON
# define DOIP_DHCP_OPT_VENDOR_CLASS              STD_OFF
# define DOIP_GET_RESET_MEASUREMENT_DATA         STD_OFF

/**********************************************************************************************************************
 *  INTEGER DEFINES
 *********************************************************************************************************************/
# define DOIP_GATEWAY                            0U
# define DOIP_NODE                               1U
# define DOIP_NODE_TYPE                          DOIP_NODE

/**********************************************************************************************************************
 *  VARIANT DEPENDEND
 *********************************************************************************************************************/
# define DOIP_CONNECTION_TCP_UDP_TOTAL           3u
# define DOIP_ADDR                               0x1212u
# define DOIP_MAX_REQUEST_BYTES                  0x00001006uL
# define DOIP_INIT_INACTIV_WAIT                  400u
# define DOIP_GEN_INACTIV_WAIT                   60000uL
# define DOIP_ALIVE_CHECK_WAIT                   100u
# define DOIP_ANNOUNCE_WAIT                      100u
# define DOIP_ANNOUNCE_INTERVAL                  100u
# define DOIP_ANNOUNCE_NUM                       3u
# define DOIP_VIN_INV_PATTERN                    0x00u
# define DOIP_GID_INV_PATTERN                    0x00u
# define DOIP_MAX_CONS_PER_LOC_ADDR              0u
# define DOIP_MAX_HOST_NAME_SIZE                 5u
# define DOIP_MAX_UDP_REQ_PER_MSG                1u
# define DOIP_VERIFY_RX_PDU_MAX_DATA_LENGTH      0u
# define DOIP_MAX_PDU_LENGTH                     0x0000FFFFuL
# define DOIP_UDP_MAX_RETRY_CNT                  12000u /* main function cycle retry count - retry time 60s */
# define DOIP_TCP_TX_QUEUE_PROCESS_LIMIT         2u
# define DOIP_8_BIT_NET_MASK                     0x000000FFu /* 8-Bit Netmask (reverse) */

/**********************************************************************************************************************
 *  USER CONFIG FILE CONTENT
 *********************************************************************************************************************/
/* User Config File Start */

/* User Config File End */

#endif /* DOIP_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: DoIP_Cfg.h
 *********************************************************************************************************************/

