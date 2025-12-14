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
/*         \file  EthTrcv_30_Tja1100_Types.h
 *        \brief  Ethernet transceiver driver hardware specific types header
 *
 *      \details  Header file containing the transceiver specific types
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
#if !defined (ETHTRCV_30_TJA1100_TYPES_H)
# define ETHTRCV_30_TJA1100_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_GeneralTypes.h"

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* EthTrcv_30_Tja1100_Diagnostic State */
typedef EthTrcv_ModeType EthTrcv_30_Tja1100_DiagnosticState;

/* EthTrcv_30_Tja1100_HardwareAccessibilityType */
typedef uint8 EthTrcv_30_Tja1100_HardwareAccessibilityType;

/* EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType */
typedef uint8  EthTrcv_30_Tja1100_HwAccessMonitorFailureDebounceCounterType;

/* EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType */
typedef uint8  EthTrcv_30_Tja1100_HwAccessMonitorRecoveryDebounceCounterType;

#endif
  /* ETHTRCV_30_TJA1100_TYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_Types.h
 *********************************************************************************************************************/
