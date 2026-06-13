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
/*!        \file  EthIf_EthCtrl_Types.h
 *        \brief  EthIf EthCtrl public types header
 *
 *      \details  Provides access to the public types of the sub-module EthCtrl of EthIf.
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

#if !defined (ETHIF_ETHCTRL_TYPES_H)
# define ETHIF_ETHCTRL_TYPES_H

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
# if ( ETHIF_GLOBAL_TIME_SUPPORT == STD_ON )
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*! Eth_TimeStampQualType mapping for Vector specific Pre-ASR define to ASR4.3 define ETH_VALID */
#  define ETH_VALID      ETH_TIMESTAMP_VALID
/*! Eth_TimeStampQualType mapping for Vector specific Pre-ASR define to ASR4.3 define ETH_INVALID */
#  define ETH_INVALID    ETH_TIMESTAMP_INVALID
/*! Eth_TimeStampQualType mapping for Vector specific Pre-ASR define to ASR4.3 define ETH_UNCERTAIN */
#  define ETH_UNCERTAIN  ETH_TIMESTAMP_UNCERTAIN
# endif /* ETHIF_GLOBAL_TIME_SUPPORT */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
# if ( ETHIF_GLOBAL_TIME_SUPPORT == STD_ON )
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
/*! Quality of the time stamp */
typedef Eth_TimestampQualityType  Eth_TimeStampQualType;  /* Mapping of Vector specific Pre-ASR type to ASR4.3 type */
# endif /* ETHIF_GLOBAL_TIME_SUPPORT */

#endif /* ETHIF_ETHCTRL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthCtrl_Types.h
 *********************************************************************************************************************/

