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
 *            Module: Eth_30_Tc3xx
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Eth_30_Tc3xx_Cfg.h
 *   Generation Time: 2025-12-14 16:26:31
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined(ETH_30_TC3XX_CFG_H)
# define ETH_30_TC3XX_CFG_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_USE_DUMMY_STATEMENT
#define ETH_30_TC3XX_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETH_30_TC3XX_DUMMY_STATEMENT
#define ETH_30_TC3XX_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETH_30_TC3XX_DUMMY_STATEMENT_CONST
#define ETH_30_TC3XX_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETH_30_TC3XX_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ETH_30_TC3XX_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ETH_30_TC3XX_ATOMIC_VARIABLE_ACCESS
#define ETH_30_TC3XX_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef ETH_30_TC3XX_PROCESSOR_TC397X_STEPB
#define ETH_30_TC3XX_PROCESSOR_TC397X_STEPB
#endif
#ifndef ETH_30_TC3XX_COMP_TASKING
#define ETH_30_TC3XX_COMP_TASKING
#endif
#ifndef ETH_30_TC3XX_GEN_GENERATOR_MSR
#define ETH_30_TC3XX_GEN_GENERATOR_MSR
#endif
#ifndef ETH_30_TC3XX_CPUTYPE_BITORDER_LSB2MSB
#define ETH_30_TC3XX_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef ETH_30_TC3XX_CONFIGURATION_VARIANT_PRECOMPILE
#define ETH_30_TC3XX_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ETH_30_TC3XX_CONFIGURATION_VARIANT_LINKTIME
#define ETH_30_TC3XX_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ETH_30_TC3XX_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ETH_30_TC3XX_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ETH_30_TC3XX_CONFIGURATION_VARIANT
#define ETH_30_TC3XX_CONFIGURATION_VARIANT ETH_30_TC3XX_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ETH_30_TC3XX_POSTBUILD_VARIANT_SUPPORT
#define ETH_30_TC3XX_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
 *  SYMBOLIC NAME VALUES
 *********************************************************************************************************************/
#define EthConf_EthCtrlConfig_EthCtrlConfig (0uL)

/**********************************************************************************************************************
 *  CONFIGURATION VERSION
 *********************************************************************************************************************/
# define ETH_30_TC3XX_CFG_MAJOR_VERSION       (7u)
# define ETH_30_TC3XX_CFG_MINOR_VERSION       (0u)

/**********************************************************************************************************************
 *  SWITCH DEFINES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_DEV_ERROR_DETECT                     (STD_OFF)
# define ETH_30_TC3XX_DEV_ERROR_REPORT                     (STD_OFF)
# define ETH_30_TC3XX_DEM_ERROR_DETECT                     (STD_OFF)
# define ETH_30_TC3XX_ENABLE_RX_INTERRUPT                  (STD_OFF)
# define ETH_30_TC3XX_ENABLE_TX_INTERRUPT                  (STD_ON)
# define ETH_30_TC3XX_MII_INTERFACE                        (STD_ON)
# define ETH_30_TC3XX_VERSION_INFO_API                     (STD_OFF)
# define ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER       (STD_ON)
# define ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS              (STD_OFF)
# define ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT      (STD_OFF)
# define ETH_30_TC3XX_ENABLE_CHECKSUM_OFFLOADING           (STD_ON)
# define ETH_30_TC3XX_ENABLE_QOS                           (STD_OFF)
# define ETH_30_TC3XX_ENABLE_TIMESYNC                      (STD_ON)
# define ETH_30_TC3XX_ZERO_COPY_EXTENSIONS_SUPPORT         (STD_OFF)
# define ETH_30_TC3XX_HEADER_ACCESS_API_SUPPORT            (STD_OFF)
# define ETH_30_TC3XX_USE_PERIPHERAL_ACCESS_API            (STD_OFF)
# define ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API           (STD_OFF)
# define ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE           (STD_OFF)
# define ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API   (STD_ON)
# define ETH_30_TC3XX_ENABLE_VLANID_BASED_FRAME_QUEUING    (STD_OFF)
/**********************************************************************************************************************
 *  NUMERICAL DEFINES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_CTRL_IDX_OFFSET                  (0u)


#endif /* ETH_30_TC3XX_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Cfg.h
 *********************************************************************************************************************/


