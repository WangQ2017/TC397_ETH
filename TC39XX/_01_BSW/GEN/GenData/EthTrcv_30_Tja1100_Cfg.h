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
 *            Module: EthTrcv_30_Tja1100
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: EthTrcv_30_Tja1100_Cfg.h
 *   Generation Time: 2025-12-14 15:58:18
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETHTRCV_30_TJA1100_CFG_H)
# define ETHTRCV_30_TJA1100_CFG_H
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"

/**********************************************************************************************************************
 *  GENERAL DEFINES
 *********************************************************************************************************************/
#ifndef ETHTRCV_30_TJA1100_USE_DUMMY_STATEMENT
#define ETHTRCV_30_TJA1100_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTRCV_30_TJA1100_DUMMY_STATEMENT
#define ETHTRCV_30_TJA1100_DUMMY_STATEMENT(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTRCV_30_TJA1100_DUMMY_STATEMENT_CONST
#define ETHTRCV_30_TJA1100_DUMMY_STATEMENT_CONST(v)  /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */  /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef ETHTRCV_30_TJA1100_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define ETHTRCV_30_TJA1100_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef ETHTRCV_30_TJA1100_ATOMIC_VARIABLE_ACCESS
#define ETHTRCV_30_TJA1100_ATOMIC_VARIABLE_ACCESS 32u /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef ETHTRCV_30_TJA1100_PROCESSOR_TC397X_STEPB
#define ETHTRCV_30_TJA1100_PROCESSOR_TC397X_STEPB
#endif
#ifndef ETHTRCV_30_TJA1100_COMP_TASKING
#define ETHTRCV_30_TJA1100_COMP_TASKING
#endif
#ifndef ETHTRCV_30_TJA1100_GEN_GENERATOR_MSR
#define ETHTRCV_30_TJA1100_GEN_GENERATOR_MSR
#endif
#ifndef ETHTRCV_30_TJA1100_CPUTYPE_BITORDER_LSB2MSB
#define ETHTRCV_30_TJA1100_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
#ifndef ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_PRECOMPILE
#define ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_LINKTIME
#define ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT
#define ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT ETHTRCV_30_TJA1100_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef ETHTRCV_30_TJA1100_POSTBUILD_VARIANT_SUPPORT
#define ETHTRCV_30_TJA1100_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif


/**********************************************************************************************************************
 *  SYMBOLIC NAME DEFINES
 *********************************************************************************************************************/
#define EthTrcvConf_EthTrcvConfig_EthTrcvConfig (0uL)

/**********************************************************************************************************************
 *  CONFIGURATION VERSION
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_CFG_MAJOR_VERSION                       (4u)
# define ETHTRCV_30_TJA1100_CFG_MINOR_VERSION                       (0u)

/**********************************************************************************************************************
 *  SWITCH DEFINES
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_DEV_ERROR_DETECT                        (STD_OFF)
# define ETHTRCV_30_TJA1100_DEV_ERROR_REPORT                        (STD_OFF)
# define ETHTRCV_30_TJA1100_PROD_ERROR_REPORTING                    (STD_OFF)
# define ETHTRCV_30_TJA1100_VERSION_INFO_API                        (STD_OFF)
# define ETHTRCV_30_TJA1100_ENABLE_GET_TRCV_MODE                    (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_SET_TRCV_MODE                    (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG                   (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_GET_LINK_STATE                   (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE                    (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE                  (STD_ON)
# define ETHTRCV_30_TJA1100_ENABLE_GET_TRANSCEIVER_WAKEUP_MODE_API  (STD_OFF)
# define ETHTRCV_30_TJA1100_WAKEUP_TYPE                             (ETHTRCV_WAKEUP_NOT_SUPPORTED)


#endif /* ETHTRCV_30_TJA1100_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Cfg.h
 *********************************************************************************************************************/
 

