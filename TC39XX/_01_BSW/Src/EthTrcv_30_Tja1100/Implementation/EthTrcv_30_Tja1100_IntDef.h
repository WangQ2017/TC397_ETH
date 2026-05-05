/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  EthTrcv_30_Tja1100_IntDef.h
 *        \brief  Ethernet transceiver driver internal header
 *
 *      \details  Header file containing the private type and data declarations of the Ethernet Transceiver driver
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK in the module's header file
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_TJA1100_INTDEF_H)
# define ETHTRCV_30_TJA1100_INTDEF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "SchM_EthTrcv_30_Tja1100.h"
# include "EthTrcv_30_Tja1100_GenTypes.h"
# if (ETHTRCV_30_TJA1100_PROD_ERROR_REPORTING == STD_ON)
#  include "Dem.h"
# endif /* ETHTRCV_30_TJA1100_PROD_ERROR_REPORTING */
# if (ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON)
#  include "Det.h"
# endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

# define ETHTRCV_30_TJA1100_MAX_CFGS_TOTAL                            (1U)
/**************************************************************************************************
* GLOBAL CONSTANT MACROS
**************************************************************************************************/
# define ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE()         SchM_Enter_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE()
# define ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE()           SchM_Exit_EthTrcv_30_Tja1100_ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE()

/* Common register masks */
# define ETHTRCV_30_TJA1100_REG_PHYIDR1_OUI_MASK                      (0xFFFFU) /*!< OUI Bitmask for PHY identifier register 1 */
# define ETHTRCV_30_TJA1100_REG_PHYIDR2_OUI_MASK                      (0xFC00U) /*!< OUI Bitmask for PHY identifier register 2 */
# define ETHTRCV_30_TJA1100_REG_PHYIDR2_TYPE_NR_MASK                  (0x03F0U) /*!< Type number Bitmask for PHY identifier register 2 */
# define ETHTRCV_30_TJA1100_REG_PHYIDR2_REV_NR_MASK                   (0x000FU) /*!< Revision number Bitmask for PHY identifier register 2 */
# define ETHTRCV_30_TJA1100_PHYIDR1_TO_OUIPTR_SHIFT_LEFT              (6U)      /*!< Amount of bit-positions to shift the OUI content of PHYIDR1 register left in the output containing the OUI */
# define ETHTRCV_30_TJA1100_PHYIDR2_TO_OUIPTR_SHIFT_RIGHT             (10U)     /*!< Amount of bit-positions to shift the OUI content of PHYIDR2 register right in the output containing the OUI */
# define ETHTRCV_30_TJA1100_PHYIDR2_TO_MODELPTR_SHIFT_RIGHT           (4U)      /*!< Amount of bit-positions to shift the Model number content of PHYIDR2 register right in the output containing the model number */

/* Phy Test Modes */
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_NORMAL                      (0x0U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_1                           (0x1U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_2                           (0x2U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_3                           (0x3U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_4                           (0x4U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_5                           (0x5U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_6                           (0x6U)
# define ETHTRCV_30_TJA1100_PHY_TEST_MODE_7                           (0x7U)

/* Transceiver Register Access Methods */
# define ETHTRCV_30_TJA1100_MII_ACCESS                                (0x0U)
# define ETHTRCV_30_TJA1100_RDB_ACCESS                                (0x1U)
# define ETHTRCV_30_TJA1100_SHADOW_ACCESS                             (0x2U)
# define ETHTRCV_30_TJA1100_INTEGRATED_PHY_ACCESS                     (0x3U)

/* Diagnostic states */
# define ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_CABLE_DIAG                (4U)
# define ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TEST_MODE                 (5U)
# define ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_LOOPBACK_MODE             (6U)
# define ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TX_MODE                   (7U)

# define ETHTRCV_30_TJA1100_INVALID_REGVAL                            (0xFFFFU)
# define ETHTRCV_30_TJA1100_USER_CALLOUT_IDX                          (0x0U)

/* Transceiver Accessibility Status */
# define ETHTRCV_30_TJA1100_ACCESSIBILITY_OK                          (0x00U) /* Trcv hardware accessible */
# define ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK                      (0x01U) /* Trcv hardware not accessible */

/* Diagnostic Event Manager */
# if ( ETHTRCV_30_TJA1100_PROD_ERROR_REPORTING == STD_ON )
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define ETHTRCV_30_TJA1100_DEM_REPORT_ERROR_STATUS_ETHTRCV_E_ACCESS(TrcvIdx) \
                                                                              (Dem_ReportErrorStatus(EthTrcv_30_Tja1100_GetDemEAccessEventIdOfEthTrcv(TrcvIdx), DEM_EVENT_STATUS_FAILED))
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define ETHTRCV_30_TJA1100_DEM_REPORT_PASSED_STATUS_ETHTRCV_E_ACCESS(TrcvIdx) \
                                                                              (Dem_ReportErrorStatus(EthTrcv_30_Tja1100_GetDemEAccessEventIdOfEthTrcv(TrcvIdx), DEM_EVENT_STATUS_PASSED))

# else
#  define ETHTRCV_30_TJA1100_DEM_REPORT_ERROR_STATUS_ETHTRCV_E_ACCESS(TrcvIdx)
#  define ETHTRCV_30_TJA1100_DEM_REPORT_PASSED_STATUS_ETHTRCV_E_ACCESS(TrcvIdx)
# endif /* ETHTRCV_30_TJA1100_PROD_ERROR_REPORTING */

/**********************************************************************************************************************
 *  PRIVATE DATA
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#  if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )
extern VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_ZERO_INIT) EthTrcv_30_Tja1100_ModuleState;
#  endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
# define ETHTRCV_30_TJA1100_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

#endif /* ETHTRCV_30_TJA1100_INTDEF_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_IntDef.h
 *********************************************************************************************************************/
