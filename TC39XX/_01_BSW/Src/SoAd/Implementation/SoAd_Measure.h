/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SoAd_Measure.h
 *        \brief  Socket Adaptor header file
 *
 *      \details  Vector static code header file for AUTOSAR Socket Adaptor sub-component Measure.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's main source file.
 *********************************************************************************************************************/

#if !defined (SOAD_MEASURE_H)
# define SOAD_MEASURE_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

# include "SoAd.h"
# include "SoAd_Priv.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define SOAD_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

# if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Measure_Init()
 *********************************************************************************************************************/
/*! \brief          Initializes the count of dropped TCP/UDP PDUs, dropped TCP connections, dropped UDP frames 
 *                  to zero.
 *  \details        - 
 *  \pre            - 
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \config         SOAD_GET_RESET_MEASUREMENT_DATA_API
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Measure_Init(void);

/**********************************************************************************************************************
 *  SoAd_Measure_Inc()
 *********************************************************************************************************************/
/*! \brief          Increments the count of dropped TCP/UDP PDUs, dropped TCP connections, dropped UDP frames.
 *  \details        -
 *  \param[in]      MeasurementIdx  The measurement index of the counter type to be incremented.
 *                                  [range: SOAD_MEAS_DROP_TCP, SOAD_MEAS_DROP_UDP,
 *                                          SOAD_MEAS_DROP_TCP_CONNECTION, SOAD_MEAS_DROP_UDP_FRAME]
 *  \param[in]      Count           The count of increments to be made.
 *                                  [range: 0 - 65535]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         SOAD_GET_RESET_MEASUREMENT_DATA
 *********************************************************************************************************************/
FUNC(void, SOAD_CODE) SoAd_Measure_Inc(
  SoAd_MeasurementIdxType MeasurementIdx,
  uint16 Count);

/**********************************************************************************************************************
 *  SoAd_Measure_GetAndReset()
 *********************************************************************************************************************/
/*! \brief          Gets and Resets (if requested) the counter for dropped TCP/UDP PDUs, dropped TCP connections or
 *                  dropped UDP frames.
 *  \details        -
 *  \param[in]      MeasurementIdx          The index to select specific measurement data.
 *                                          [range: SOAD_MEAS_DROP_TCP, SOAD_MEAS_DROP_UDP,
 *                                                  SOAD_MEAS_DROP_TCP_CONNECTION, SOAD_MEAS_DROP_UDP_FRAME,
 *                                                  SOAD_MEAS_ALL]
 *  \param[in]      MeasurementResetNeeded  Flag to indicate if the counter needs to be reset.
 *                                          [range: TRUE, FALSE]
 *  \param[out]     MeasurementDataPtr      Buffer where the value of the counter is to be copied into.
 *                                          [range: POINTER may be NULL_PTR]
 *  \pre            -
 *  \return         E_OK                    The operations were successful.
 *  \return         E_NOT_OK                The operations failed.
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         SOAD_GET_RESET_MEASUREMENT_DATA_API
 *********************************************************************************************************************/
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Measure_GetAndReset(
  SoAd_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) MeasurementDataPtr);
# endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

# define SOAD_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_Rule20.10_0342 */

#endif /* !defined(SOAD_MEASURE_H) */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Measure.h
 *********************************************************************************************************************/
