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
/**        \file  SoAd_Measure.c
 *        \brief  Socket Adaptor source file
 *
 *      \details  Vector static code implementation for AUTOSAR Socket Adaptor sub-component Measure.
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

/* PRQA S 1881 EOF */ /* MD_MSR_AutosarBoolean */
/* PRQA S 4304 EOF */ /* MD_MSR_AutosarBoolean */

#define SOAD_MEASURE_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SoAd_Measure.h"

#if ( SOAD_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif /* SOAD_DEV_ERROR_REPORT == STD_ON */

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (SOAD_LOCAL) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL static
#endif

#if !defined (SOAD_LOCAL_INLINE) /* COV_SOAD_COMPATIBILITY */
# define SOAD_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
# if ( SOAD_TCP == STD_ON )
/*! Counter for the number of dropped TCP PDUs. */
SOAD_LOCAL VAR(uint32, SOAD_VAR_ZERO_INIT) SoAd_Measure_DroppedTcpPduCtr;

/*! Counter for the number of dropped TCP connections. */
SOAD_LOCAL VAR(uint32, SOAD_VAR_ZERO_INIT) SoAd_Measure_DroppedTcpConCtr;
# endif /* SOAD_TCP == STD_ON */

/*! Counter for the number of dropped UDP PDUs. */
SOAD_LOCAL VAR(uint32, SOAD_VAR_ZERO_INIT) SoAd_Measure_DroppedUdpPduCtr;

/*! Counter for the number of dropped UDP frames. */
SOAD_LOCAL VAR(uint32, SOAD_VAR_ZERO_INIT) SoAd_Measure_DroppedUdpFrmCtr;
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

#define SOAD_STOP_SEC_VAR_NOINIT_32BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define SOAD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Measure_IncCtrValue()
 *********************************************************************************************************************/
/*! \brief          Increments the provided counter by a specified count.
 *  \details        - 
 *  \param[in]      CounterPtr The pointer to the counter to be incremented.
 *                             [range: pointer should not be null pointer]
 *  \param[in]      Count      The count of increments to be made.
 *                             [range: 0 - 65535]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         SOAD_GET_RESET_MEASUREMENT_DATA_API
 *********************************************************************************************************************/
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_Measure_IncCtrValue(
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) CounterPtr,
  uint16 Count);
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Measure_IncCtrValue()
 *********************************************************************************************************************/
/*!
 * Internal comment removed. *
 *
 *
 *
 *
 *
 */
SOAD_LOCAL FUNC(void, SOAD_CODE) SoAd_Measure_IncCtrValue(
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) CounterPtr,
  uint16 Count)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter critical section to prevent inconsistent reads and writes on the counter. */
  SOAD_BEGIN_CRITICAL_SECTION();

  /* #20 Check if the counter has not overflowed. */
  if ( ((*CounterPtr) + Count) < SOAD_MEASURE_COUNTER_MAX_VALUE )
  {
    /* #30 Increment the counter. */
    *CounterPtr = ((*CounterPtr) + Count);                                                                             /* SBSW_SOAD_POINTER_WRITE */
  }
  else
  {
    *CounterPtr = SOAD_MEASURE_COUNTER_MAX_VALUE;                                                                      /* SBSW_SOAD_POINTER_WRITE */
  }
  /* #40 Leave critical section. */
  SOAD_END_CRITICAL_SECTION();
} /* SoAd_Measure_IncCtrValue() */
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON )
/**********************************************************************************************************************
 *  SoAd_Measure_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Measure_Init(void)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reset the measurement counters to zero. */
# if ( SOAD_TCP == STD_ON )
  SoAd_Measure_DroppedTcpPduCtr = 0u;
  SoAd_Measure_DroppedTcpConCtr = 0u;
# endif /* SOAD_TCP == STD_ON */

  SoAd_Measure_DroppedUdpPduCtr = 0u;
  SoAd_Measure_DroppedUdpFrmCtr = 0u;
} /* SoAd_Measure_Init() */

/**********************************************************************************************************************
 *  SoAd_Measure_Inc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC(void, SOAD_CODE) SoAd_Measure_Inc(
  SoAd_MeasurementIdxType MeasurementIdx,
  uint16 Count)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Select the type of counter to be incremented. */
  switch ( MeasurementIdx )
  {
# if ( SOAD_TCP == STD_ON )
    case SOAD_MEAS_DROP_TCP:
    {
      /* #20 Increment the dropped TCP PDU counter. */
      SoAd_Measure_IncCtrValue(&SoAd_Measure_DroppedTcpPduCtr, Count);                                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
# endif /* SOAD_TCP == STD_ON */
    case SOAD_MEAS_DROP_UDP:
    {
      /* #30 Increment the dropped UDP PDU counter. */
      SoAd_Measure_IncCtrValue(&SoAd_Measure_DroppedUdpPduCtr, Count);                                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
# if ( SOAD_TCP == STD_ON )
    case SOAD_MEAS_DROP_TCP_CONNECTION:
    {
      /* #40 Increment the dropped TCP connection counter. */
      SoAd_Measure_IncCtrValue(&SoAd_Measure_DroppedTcpConCtr, Count);                                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
# endif /* SOAD_TCP == STD_ON */
    case SOAD_MEAS_DROP_UDP_FRAME:
    {
      /* #50 Increment the dropped UDP frame counter. */
      SoAd_Measure_IncCtrValue(&SoAd_Measure_DroppedUdpFrmCtr, Count);                                                 /* SBSW_SOAD_VARIABLE_POINTER_FORWARD */
      break;
    }
    default:
    {
      /* Nothing to do. */
      break;
    }
  }
} /* SoAd_Measure_Inc() */

/**********************************************************************************************************************
 *  SoAd_Measure_GetAndReset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_Measure_GetAndReset(
  SoAd_MeasurementIdxType MeasurementIdx,
  boolean MeasurementResetNeeded,
  P2VAR(uint32, AUTOMATIC, SOAD_APPL_VAR) MeasurementDataPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  switch ( MeasurementIdx )
  {
# if ( SOAD_TCP == STD_ON )
    /* #10 Check if the measurement index is that of the dropped TCP PDU counter. */
    case SOAD_MEAS_DROP_TCP:
    {
      /* #20 Enter critical section to prevent inconsistent reads and writes on the counter. */
      SOAD_BEGIN_CRITICAL_SECTION();

      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #30 Copy the dropped TCP PDU counter value to a buffer, if measurement data pointer is not NULL_PTR. */
        *MeasurementDataPtr = SoAd_Measure_DroppedTcpPduCtr;                                                           /* SBSW_SOAD_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #40 Reset the dropped TCP PDU counter to zero if the reset flag is set to true. */
        SoAd_Measure_DroppedTcpPduCtr = 0u;
      }

      /* #50 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }
# endif /* SOAD_TCP == STD_ON */

    /* #60 Check if the measurement index is that of the dropped UDP PDU counter. */
    case SOAD_MEAS_DROP_UDP:
    {
      /* #70 Enter critical section to prevent inconsistent reads and writes on the counter. */
      SOAD_BEGIN_CRITICAL_SECTION();

      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #80 Copy the dropped UDP PDU counter value to a buffer, if measurement data pointer is not NULL_PTR. */
        *MeasurementDataPtr = SoAd_Measure_DroppedUdpPduCtr;                                                           /* SBSW_SOAD_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #90 Reset the dropped UDP PDU counter to zero if the reset flag is set to true. */
        SoAd_Measure_DroppedUdpPduCtr = 0u;
      }

      /* #100 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }

# if ( SOAD_TCP == STD_ON )
    /* #110 Check if the measurement index is that of the dropped TCP connections counter. */
    case SOAD_MEAS_DROP_TCP_CONNECTION:
    {
      /* #120 Enter critical section to prevent inconsistent reads and writes on the counter. */
      SOAD_BEGIN_CRITICAL_SECTION();

      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #130 Copy the dropped TCP connections counter value to a buffer, if measurement data pointer is 
         * not NULL_PTR. */
        *MeasurementDataPtr = SoAd_Measure_DroppedTcpConCtr;                                                           /* SBSW_SOAD_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #140 Reset the dropped TCP connections counter to zero if the reset flag is set to true. */
        SoAd_Measure_DroppedTcpConCtr = 0u;
      }

      /* #150 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }
# endif /* SOAD_TCP == STD_ON */

    /* #160 Check if the measurement index is that of the dropped UDP frames counter. */
    case SOAD_MEAS_DROP_UDP_FRAME:
    {
      /* #170 Enter critical section to prevent inconsistent reads and writes on the counter. */
      SOAD_BEGIN_CRITICAL_SECTION();

      if ( MeasurementDataPtr != NULL_PTR )
      {
        /* #180 Copy the dropped UDP frames counter value to a buffer, if measurement data pointer is 
         * not NULL_PTR. */
        *MeasurementDataPtr = SoAd_Measure_DroppedUdpFrmCtr;                                                           /* SBSW_SOAD_POINTER_WRITE */
      }

      if ( MeasurementResetNeeded == TRUE )
      {
        /* #190 Reset the dropped UDP frames counter to zero if the reset flag is set to true. */
        SoAd_Measure_DroppedUdpFrmCtr = 0u;
      }

      /* #200 Leave critical section. */
      SOAD_END_CRITICAL_SECTION();

      retVal = E_OK;
      break;
    }

    /* #210 Check if the measurement index is that of ALL. */
    case SOAD_MEAS_ALL:
    {
      if ( MeasurementResetNeeded == TRUE )
      {
        /* #220 Enter critical section to prevent inconsistent reads and writes on the counter. */
        SOAD_BEGIN_CRITICAL_SECTION();

        /* #230 Reset all the measurement data counters to zero if the reset flag is set to true. */
# if ( SOAD_TCP == STD_ON )
        SoAd_Measure_DroppedTcpPduCtr = 0u;
        SoAd_Measure_DroppedTcpConCtr = 0u;
# endif /* SOAD_TCP == STD_ON */

        SoAd_Measure_DroppedUdpPduCtr = 0u;
        SoAd_Measure_DroppedUdpFrmCtr = 0u;

        /* #240 Leave critical section. */
        SOAD_END_CRITICAL_SECTION();
      }

      retVal = E_OK;
      break;
    }

    default:
    {
      /* #250 Return E_NOT_OK as the requested measurement index is not supported. */
      break;
    }
  }

  return retVal;
} /* SoAd_Measure_GetAndReset() */ /* PRQA S 6030 */ /* MD_MSR_STCYC */
#endif /* SOAD_GET_RESET_MEASUREMENT_DATA_API == STD_ON */

#define SOAD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_Rule20.10_0342 */

/* Justification for module-specific MISRA deviations:
 * see file SoAd.c
 */

/**********************************************************************************************************************
 *  END OF FILE: SoAd_Measure.c
 *********************************************************************************************************************/
