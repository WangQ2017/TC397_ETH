/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_Stats_Types.h
 *        \brief  EthIf Stats public types header
 *
 *      \details  Provides access to the public types of the sub-module Stats of EthIf.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (ETHIF_STATS_TYPES_H)
# define ETHIF_STATS_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_GenTypes.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ETHIF measurement idx types */
# define ETHIF_MEAS_DROP_CTRLIDX                    (0x01u)
# define ETHIF_MEAS_VLAN_DOUBLE_TAGGED              (0x80u)
# define ETHIF_MEAS_UNKNOWN_ETHERTYPE               (0x81u)
# define ETHIF_MEAS_ALL                             (0xFFu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*! Index to select specific measurement data
 *  ETHIF_MEAS_DROP_CRTLIDX  0x01      Measurement index of dropped datagrams caused by invalid CrtlIdx/VLAN
 *  ETHIF_MEAS_RESERVED_1    0x02-0x7F reserved by AUTOSAR
 *  ETHIF_MEAS_RESERVED_2    0x80-0xEF Vendor specific range
 *  ETHIF_MEAS_RESERVED_3    0xF0-0xFE reserved by AUTOSAR (future use)
 *  ETHIF_MEAS_ALL           0xFF      represents all measurement indexes
 */
typedef uint8 EthIf_MeasurementIdxType;

/*! Transmission statistic counters of an EthIf-controller */
typedef struct
{
  uint32  NumTxPkts;   /*!< Pakets transmitted on the EthIf-controller */
  uint32  NumTxBytes;  /*!< Bytes transmitted on the EthIf-controller */
} EthIf_TxStatsType;
/*! Reception statistic counters of an EthIf-controller */
typedef struct
{
  uint32  NumRxPkts;   /*!< Packets received on the EthIf-controller */
  uint32  NumRxBytes;  /*!< Bytes received on the EthIf-controller */
} EthIf_RxStatsType;

#endif /* ETHIF_STATS_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Stats_Types.h
 *********************************************************************************************************************/

