/* ********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 */
/*! \addtogroup Dem_IntDataElementIF
 *  \{
 *  \file       Dem_IntDataElementIF_Implementation.h
 *  \brief      Module fetches internal data elements during an on-going read operation.
 *  \details    Module fetches the values for specific internal data elements. The statistical data are calculated
 *              'live' and provided for an on-going read operation.
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials            Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Savas Ates                    vissat              Vector Informatik GmbH
 *  Anna Bosch                    visanh              Vector Informatik GmbH
 *  Stefan Huebner                vishrs              Vector Informatik GmbH
 *  Thomas Dedler                 visdth              Vector Informatik GmbH
 *  Alexander Ditte               visade              Vector Informatik GmbH
 *  Matthias Heil                 vismhe              Vector Informatik GmbH
 *  Erik Jeglorz                  visejz              Vector Informatik GmbH
 *  Friederike Hitzler            visfrs              Vector Informatik GmbH
 *  Aswin Vijayamohanan Nair      visavi              Vector Informatik GmbH
 *  Fabian Wild                   viszfa              Vector Informatik GmbH
 *  Erwin Stamm                   visern              Vector Informatik GmbH
 *  Laura Henze                   visera              Vector Informatik GmbH
 *  Sebastian Kobbe               vissko              Vector Informatik GmbH
 *  Xu Lin                        visxli              Vector Informatik GmbH
 *  Simeon Ivanov                 vsarcsiiv           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  REFER TO DEM.H
 *********************************************************************************************************************/

#if !defined (DEM_INTDATAELEMENTIF_IMPLEMENTATION_H)
#define DEM_INTDATAELEMENTIF_IMPLEMENTATION_H

/* ********************************************************************************************************************
 *  GLOBAL MISRA JUSTIFICATIONS
 *********************************************************************************************************************/
/* PRQA S 2880 EOF */ /* MD_DEM_2.1_UNREACHABLE_STATEMENT */
/* PRQA S 2982 EOF */ /* MD_DEM_2982 */
/* PRQA S 2983 EOF */ /* MD_DEM_2983 */
/* PRQA S 2985 EOF */ /* MD_DEM_2985 */
/* PRQA S 2986 EOF */ /* MD_DEM_2986 */
/* PRQA S 2987 EOF */ /* MD_DEM_2987 */
/* PRQA S 2991 EOF */ /* MD_DEM_2991 */
/* PRQA S 2992 EOF */ /* MD_DEM_2992 */
/* PRQA S 2995 EOF */ /* MD_DEM_2995 */
/* PRQA S 2996 EOF */ /* MD_DEM_2996 */
/* PRQA S 0759 EOF */ /* MD_MSR_Union */

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_IntDataElementIF_Interface.h"

                                                    /* Used subcomponent API */
/* ------------------------------------------------------------------------- */
#include "Dem_MemoryEntry_Implementation.h"
#include "Dem_Data_Implementation.h"
#include "Dem_Statistics_Implementation.h"
#include "Dem_Cfg_Definitions.h"
#include "Dem_DTC_Implementation.h"
#include "Dem_OperationCycle_Implementation.h"
#include "Dem_Iumpr_Implementation.h"

                                                  /* Subcomponents callbacks */
/* ------------------------------------------------------------------------- */
#include "Dem_Error_Interface.h"
#include "Dem_Memory_Interface.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*! Filename declaration */
#define DEM_INTDATAELEMENTIF_IMPLEMENTATION_FILENAME "Dem_IntDataElementIF_Implementation.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DEFINITIONS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_IntDataElementIF_Private Private Methods
 * \{
 */


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyUpwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the upward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \details       Retrieves the upward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied          
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUpwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_Copy1ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the occurrence counter of the event holding the
 *                event memory entry as 1 byte data element.
 *
 * \details       Retrieves the occurrence counter of the event holding the
 *                event memory entry as 1 byte data element. An occurrence 
 *                counter that will not fit 1 byte is written as 255.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy1ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_Copy2ByteOccurrenceCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the occurrence counter of the event holding the
 *                event memory entry as 2 byte data element
 *
 * \details       Retrieves the occurrence counter of the event holding the
 *                event memory entry as 2 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy2ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyOverflowIndication
 *****************************************************************************/
/*!
 * \brief         Retrieves the event memory overflow state.
 *
 * \details       Retrieves the event memory overflow state.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyOverflowIndication(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventSignificance
 *****************************************************************************/
/*!
 * \brief         Retrieves the significance configuration of the event.
 *
 * \details       Retrieves the significance configuration of the event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventSignificance(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventPriority
 *****************************************************************************/
/*!
 * \brief         Retrieves the priority configuration of the event holding
 *                the event memory entry.
 *
 * \details       Retrieves the priority configuration of the event holding
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventPriority(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyDownwardsAgingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the downward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \details       Retrieves the downward counting aging counter of the event 
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyDownwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyMaxFdcSinceLastClear
 *****************************************************************************/
/*!
 * \brief         Retrieves the maximum fault detection counter since last
 *                clear of the event holding the event memory entry.
 *
 * \details       Retrieves the maximum fault detection counter since last
 *                clear of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcSinceLastClear(                                                                                   
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyMaxFdcThisCycle
 *****************************************************************************/
/*!
 * \brief         Retrieves the maximum fault detection counter this cycle
 *                of the event holding the event memory entry.
 *
 * \details       Retrieves the maximum fault detection counter this cycle
 *                of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcThisCycle(                                                                                        
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the cycle count since last failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the cycle count since last failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the cycle count since first failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the cycle count since first failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );                                                                         
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
* Dem_IntDataElementIF_CopyWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* \brief         Retrieves the WarmUp cycle count since last failed of the
*                event holding the event memory entry.
*
* \details       Retrieves the WarmUp cycle count since last failed of the
*                event holding the event memory entry.
*
* \param[in,out] CopyDidInfoPtr
*                CopyDid context
*
* \return        TRUE
*                Data was copied
* \return        FALSE
*                No data was copied
*
* \pre           -
* \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
*                DEM_FEATURE_NEED_OBD == STD_ON)
*
* \context       TASK|ISR2
* \synchronous   TRUE
* \reentrant     TRUE
*****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyWarmUpCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyFailedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested failed of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested failed of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyConsecutiveFailedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of consecutive cycles tested failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of consecutive cycles tested failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyConsecutiveFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyFaultPendingCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the 'fault pending counter' of the event holding 
 *                the event memory entry.
 *
 * \details         Retrieves the 'fault pending counter' of the event holding 
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFaultPendingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested since first failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested since first failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested since last failed of
 *                the event holding the event memory entry.
 *
 * \details       Retrieves the number of cycles tested since last failed of
 *                the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyHealingCounterDownwards
 *****************************************************************************/
/*!
 * \brief         Retrieves the inverted healing counter of the event holding 
 *                the event memory entry.
 *
 * \details       Retrieves the inverted healing counter of the event holding 
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyHealingCounterDownwards(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyRootCauseEventId
 *****************************************************************************/
/*!
 * \brief         Retrieves the event that caused event memory storage as
 *                2 byte data element
 *
 * \details       Retrieves the event that caused event memory storage as
 *                2 byte data element. For combined events, this is the exact
 *                sub-event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyRootCauseEventId(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdDtc
 *****************************************************************************/
/*!
 * \brief         Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 2 byte data element
 *
 * \details       Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 2 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdDtc_3Byte
 *****************************************************************************/
/*!
 * \brief         Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 3 byte data element with trailing 0
 *
 * \details       Retrieves the OBD DTC of the event that stored the
 *                event memory entry as 3 byte data element with trailing 0
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc_3Byte(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyEventObdRatio
 *****************************************************************************/
/*!
 * \brief         Retrieves the the ratio/IUMPR attached to the event
 *
 * \details       If ratio availabe copies
 *                [NumeratorHighByte] [NumeratorLowByte] [DenominatorHighByte] [DenominatorLowByte]
 *                If ratio is not available copies
 *                [0x00] [0x00] [0x00] [0x00]
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdRatio(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles since the last fdc threshold
 *                was exceeded.
 *
 * \details       Retrieves the number of cycles since the last fdc threshold
 *                was exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles tested passed since the last
 *                fdc threshold was exceeded.
 *
 * \details       Retrieves the number of cycles tested passed since the last
 *                fdc threshold was exceeded, of the event holding the event
 *                memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles since the first fdc threshold
 *                was exceeded.
 *
 * \details       Retrieves the number of cycles since the first fdc threshold
 *                was exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyUnconfirmedCycles
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles in which the fdc threshold was
 *                exceeded.
 *
 * \details       Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, of the event holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUnconfirmedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed
 *****************************************************************************/
/*!
 * \brief         Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, or a passed result was reported.
 *
 * \details       Retrieves the number of cycles in which the fdc threshold was
 *                exceeded, or a passed result was reported, of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyCurrentFdc
 *****************************************************************************/
/*!
 * \brief         Retrieves the current fault detection counter of the event
 *                holding the event memory entry.
 *
 * \details       Retrieves the current fault detection counter of the event
 *                holding the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCurrentFdc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyAgedCounter
 *****************************************************************************/
/*!
 * \brief         Retrieves the aged counter of the event.
 *
 * \details       Retrieves the aged counter of the event.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyAgedCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyPreConfirmedStatus
 *****************************************************************************/
/*!
 * \brief         Retrieves the preconfirmed status byte of the event holding
 *                the event memory entry.
 *
 * \details       Retrieves the preconfirmed status byte of the event holding
 *                the event memory entry.
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        TRUE
 *                Data was copied
 * \return        FALSE
 *                No data was copied
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) 
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyPreConfirmedStatus(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyStandardEnvData_Dag
 *****************************************************************************/
/*!
 * \brief         Writes a Daimler standard environment data object as 7 byte
 *                data element
 *
 * \details       Writes a Daimler standard environment data object as 7 byte
 *                data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Always TRUE
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON ||
 *                DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyStandardEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 * Dem_IntDataElementIF_CopyExtendedEnvData_Dag
 *****************************************************************************/
/*!
 * \brief         Writes a Daimler standard environment data object and
 *                operating time as 12 byte data element
 *
 * \details       Writes a Daimler standard environment data object and
 *                operating time as 12 byte data element
 *
 * \param[in,out] CopyDidInfoPtr
 *                CopyDid context
 *
 * \return        Always TRUE
 *
 * \pre           -
 * \config        (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON ||
 *                DEM_FEATURE_NEED_OBD == STD_ON) &&
 *                DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyExtendedEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr
  );
#endif

/* ********************************************************************************************************************
 *  SUBCOMPONENT PRIVATE FUNCTION DEFINITIONS
 *********************************************************************************************************************/

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyUpwardsAgingCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUpwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_AGINGCTR == STD_ON)
  uint8 lAgingCounter;
#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
#  endif

#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if(CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
  {
    /* aging counter is copied to readout buffer */
    lAgingCounter = CopyDidInfoPtr->MemIndeCounterPtr->AgingCounter;
  }
  else
#  endif
  {
    lAgingCounter = Dem_Statistics_CalculateUpwardsAgingCounter(CopyDidInfoPtr->MemoryEntryId, CopyDidInfoPtr->EventId);
  }

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lAgingCounter);                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_Copy1ByteOccurrenceCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy1ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_OCCCTR == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE)
  {
    lReturnValue = FALSE;
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                         Dem_Statistics_Calculate1ByteOccurrenceCounter(CopyDidInfoPtr));                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_Copy2ByteOccurrenceCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_Copy2ByteOccurrenceCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_OCCCTR_2BYTE == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE)
  {
    lReturnValue = FALSE;
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint16(CopyDidInfoPtr->DestinationBuffer,                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                          Dem_MemoryEntry_GetOccurrenceCounter2Byte(CopyDidInfoPtr->MemoryEntryId));

    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyOverflowIndication
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyOverflowIndication(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_OVFLIND == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                      (uint8)Dem_Memory_GetOverflow(                                                             /* PRQA S 4304 */ /* MD_MSR_AutosarBoolean */
                                             Dem_Cfg_EventDestination(CopyDidInfoPtr->EventId)));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyEventSignificance
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventSignificance(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_SIGNIFICANCE == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_Statistics_CalculateEventSignificance(CopyDidInfoPtr));                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyEventPriority
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventPriority(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_PRIORITY == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                      (uint8)Dem_Cfg_EventPriority(CopyDidInfoPtr->EventId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

    return lReturnValue;

}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyDownwardsAgingCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyDownwardsAgingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_AGINGCTR_INVERTED == STD_ON)
  uint8 lDownwardAgingCounter;
#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_OFF)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
#  endif

#  if (DEM_CFG_SUPPORT_AGING_FOR_ALL_DTCS == STD_ON)
  if (CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
  {
    /* Get aging counter previously calculated and copied to readout buffer */
    lDownwardAgingCounter = CopyDidInfoPtr->MemIndeCounterPtr->AgingCounterInvert;
  }
  else
#  endif
  {
    /* Calculated aging counter from current data */
    lDownwardAgingCounter = Dem_Statistics_CalculateDownwardsAgingCounter(CopyDidInfoPtr->MemoryEntryId, CopyDidInfoPtr->EventId);
  }
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lDownwardAgingCounter);                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyMaxFdcSinceLastClear
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcSinceLastClear(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_MAX_FDC_SINCE_LAST_CLEAR == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE)
  {
    lReturnValue = FALSE;
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                         (uint8)Dem_Statistics_CalculateMaxFdcSinceLastClear(CopyDidInfoPtr));                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyMaxFdcThisCycle
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyMaxFdcThisCycle(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_MAX_FDC_DURING_CURRENT_CYCLE == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       (uint8)Dem_Statistics_CalculateMaxFdcThisCycle(CopyDidInfoPtr));                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesSinceLastFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CYCLES_SINCE_LAST_FAILED == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_Statistics_CalculateCyclesSinceLastFailed(CopyDidInfoPtr));                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesSinceFirstFailed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CYCLES_SINCE_FIRST_FAILED == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_Statistics_CalculateCyclesSinceFirstFailed(CopyDidInfoPtr));                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;

}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
% Dem_IntDataElementIF_CopyWarmUpCyclesSinceLastFailed
*****************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyWarmUpCyclesSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_WUC_SINCE_LAST_FAILED == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                         Dem_Statistics_CalculateWarmUpCyclesSinceLastFailed(CopyDidInfoPtr));                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyFailedCycles
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_FAILED_CYCLES == STD_ON)

  if (Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE)
  {
    Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  }

  if ( (Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE) 
    && (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE) )                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    lReturnValue = FALSE;
  }
  else
  {
    uint8 lFailedCycleCounter;
# if (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
    if (CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
    {
      /* Get failed counter previously calculated and copied to readout buffer */
      lFailedCycleCounter = CopyDidInfoPtr->MemIndeCounterPtr->FailedCycles;
    }
    else
# endif
    {
      /* Calculate failed cycle counter from current data */
      lFailedCycleCounter = Dem_Statistics_CalculateFailedCycleCounter(CopyDidInfoPtr->MemoryEntryId, CopyDidInfoPtr->EventId);
    }

    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lFailedCycleCounter);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = TRUE;
}

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
    lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyConsecutiveFailedCycles
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyConsecutiveFailedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CONSECUTIVE_FAILED_CYCLES == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE)
  {
    lReturnValue = FALSE;
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                        Dem_MemoryEntry_GetConsecutiveFailedCycleCounter(CopyDidInfoPtr->MemoryEntryId));
    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyFaultPendingCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyFaultPendingCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_FAULT_PENDING_COUNTER == STD_ON)

  if(Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE)
  {
    Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  }

  if ( (Dem_DTC_IsMemIndependentCycleCounterEnabled() == FALSE) 
    && (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE) )                                             /* PRQA S 3415 */ /* MD_DEM_13.5_cf */
  {
    lReturnValue = FALSE;
  }
  else
  {
    uint8 lFaultPendingCounter;
# if (DEM_CFG_SUPPORT_MEM_INDEPENDENT_CYCLE_COUNTERS == STD_ON)
    if (CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
    {
      /* Get fault pending counter previously calculated and copied to readout buffer */
      lFaultPendingCounter = CopyDidInfoPtr->MemIndeCounterPtr->FaultPendingCounter;
    }
    else
# endif
    {
      /* Calculated fault pending counter from current data */
      lFaultPendingCounter = Dem_Statistics_CalculateFaultPendingCounter(CopyDidInfoPtr->MemoryEntryId, CopyDidInfoPtr->EventId);
    }

    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lFaultPendingCounter);                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MMD_DEM_16.7_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_FIRST_FAILED == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_MemoryEntry_TestAgingOnlyEntry(CopyDidInfoPtr->MemoryEntryId) == TRUE)
  {
    lReturnValue = FALSE;
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                        Dem_MemoryEntry_GetTestedCyclesSinceFirstFailed(CopyDidInfoPtr->MemoryEntryId));
    lReturnValue = TRUE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CYCLES_TESTED_SINCE_LAST_FAILED == STD_ON)
  uint8 lCyclesTestedSinceLastFailed;
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  if (CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
  {
    /* Get cycles tested since last failed counter previously calculated and copied to readout buffer */
    lCyclesTestedSinceLastFailed = CopyDidInfoPtr->MemIndeCounterPtr->CyclesTestSinceLastFailed;
  }
  else
  {
    /* Calculate cycles tested since last failed counter from current data */
    lCyclesTestedSinceLastFailed = Dem_Statistics_CalculateCyclesTestedSinceLastFailed(CopyDidInfoPtr->EventId);
  }
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lCyclesTestedSinceLastFailed);                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyHealingCounterDownwards
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyHealingCounterDownwards(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_HEALINGCTR_DOWNCNT == STD_ON)
  uint8 lDownwardHealingCounter;
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  if (CopyDidInfoPtr->MemIndeCounterPtr != NULL_PTR)
  {
    /* Get downward healing counter previously calculated and copied to readout buffer */
    lDownwardHealingCounter = CopyDidInfoPtr->MemIndeCounterPtr->DownwardHealingCounter;
  }
  else
  {
    /* Calculate downward healing counter from current data */
    lDownwardHealingCounter = Dem_Statistics_CalculateInvertedHealingCounter(CopyDidInfoPtr->EventId);
  }
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lDownwardHealingCounter);                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;
# endif

  return lReturnValue;

}
#endif


#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyRootCauseEventId
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyRootCauseEventId(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_ROOTCAUSE_EVENTID == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->SourceBuffer != NULL_PTR, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBuffer(CopyDidInfoPtr->DestinationBuffer, &CopyDidInfoPtr->SourceBuffer[CopyDidInfoPtr->ReadIndex], 2); /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  CopyDidInfoPtr->ReadIndex += 2u;                                                                                                  /* SBSW_DEM_POINTER_WRITE_ARGUMENT */

  lReturnValue =  TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyEventObdDtc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_OBDDTC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint16(CopyDidInfoPtr->DestinationBuffer, Dem_Cfg_EventObdDtc(CopyDidInfoPtr->EventId));        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyEventObdDtc_3Byte
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdDtc_3Byte(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_OBDDTC_3BYTE == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint16(CopyDidInfoPtr->DestinationBuffer, Dem_Cfg_EventObdDtc(CopyDidInfoPtr->EventId));        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, 0x00);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;

}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyEventObdRatio
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyEventObdRatio(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  uint16 lNumerator;
  uint16 lDenominator;

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Iumpr_CalculateObdRatio(CopyDidInfoPtr->EventId, &lNumerator, &lDenominator);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */ /* SBSW_DEM_POINTER_FORWARD_STACK */
  Dem_Data_WriteDestinationBufferUint16(CopyDidInfoPtr->DestinationBuffer, lNumerator);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  Dem_Data_WriteDestinationBufferUint16(CopyDidInfoPtr->DestinationBuffer, lDenominator);                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return TRUE;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_MemoryEntry_GetOccurrenceCounter1(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_MemoryEntry_GetOccurrenceCounter2(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                      Dem_MemoryEntry_GetOccurrenceCounter3(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyUnconfirmedCycles
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyUnconfirmedCycles(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_MemoryEntry_GetOccurrenceCounter4(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                       Dem_MemoryEntry_GetOccurrenceCounter7(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyCurrentFdc
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyCurrentFdc(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_CURRENT_FDC == STD_ON)

  sint8 lFdc;
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  if (Dem_DTC_GetFaultDetectionCounter(CopyDidInfoPtr->EventId, &lFdc) == E_OK)                                                  /* SBSW_DEM_POINTER_FORWARD_STACK */
  {
    lReturnValue = TRUE;
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, (uint8)lFdc);                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    lReturnValue = FALSE;
  }

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyAgedCounter
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyAgedCounter(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_CFG_DATA_AGED_COUNTER == STD_ON)
  lReturnValue = TRUE;
  if (Dem_Cfg_EventSupportAgedCounter(CopyDidInfoPtr->EventId) == TRUE)
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,
      Dem_DTC_GetAgedCounter(CopyDidInfoPtr->EventId));                                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
  else
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, DEM_DTC_AGED_COUNTER_INIT_VALUE);                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }
# else
  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif
  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyPreConfirmedStatus
 *****************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyPreConfirmedStatus(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  boolean lReturnValue;

# if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)

  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                      Dem_MemoryEntry_GetPreConfirmedStatus(CopyDidInfoPtr->MemoryEntryId));
  lReturnValue = TRUE;

# else

  DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                               /* PRQA S 3112 */ /* MD_DEM_14.2 */
  lReturnValue = FALSE;

# endif

  return lReturnValue;
}
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && \
( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyStandardEnvData_Dag
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyStandardEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->MemoryEntryId != DEM_MEMORYENTRY_HANDLE_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)
  Dem_Internal_AssertReturnValue(CopyDidInfoPtr->EventId != DEM_EVENT_INVALID, DEM_E_INCONSISTENT_STATE, FALSE)

  /* Buffer Layout:
      [0]:    Status, 0.0 Presence Flag (Distinguish initial entry from updates)
                      0.1 external tester present
      [1][2]: Original Odometer Value
      [3][4]: MostRecent Odometer Value
  */
  uint8 lDataIndex;
  uint8 lData;

  {
    uint8 lEventSignificance;
    uint8 lExternalTesterPresent;

    if(Dem_Cfg_EventSignificance(CopyDidInfoPtr->EventId) == DEM_CFG_EVENT_SIGNIFICANCE_OCCURRENCE)                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    {
      lEventSignificance = (uint8)1;
    }
    else
    {
      lEventSignificance = (uint8)0;
    }

    lExternalTesterPresent =
      (uint8)(Dem_MemoryEntry_GetStdEnvData(CopyDidInfoPtr->MemoryEntryId, 0) & 0x02U);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

    lData = (uint8)(lEventSignificance | lExternalTesterPresent);
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lData);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  }

  for (lDataIndex = 1u; lDataIndex <= 4u; lDataIndex++)
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                         Dem_MemoryEntry_GetStdEnvData(CopyDidInfoPtr->MemoryEntryId, lDataIndex));
  }
  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                      (uint8)Dem_MemoryEntry_GetOccurrenceCounter(CopyDidInfoPtr->MemoryEntryId));

  lData = Dem_Statistics_CalculateDAGAgingCounter(CopyDidInfoPtr);                                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer, lData);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */

  return TRUE;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) || (DEM_FEATURE_NEED_OBD == STD_ON) ) && (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyExtendedEnvData_Dag
 *****************************************************************************/
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
 */
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyExtendedEnvData_Dag(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr                                                          /* PRQA S 3673 */ /* MD_DEM_8.13_Design */
  )
{
  /* Buffer Layout:
    [0-4]:  See StandardEnvData
    [5-8]:  Operating Time*
    [9]:    Operating Time Status*
  */
  uint8 lDataIndex;
  (void)Dem_IntDataElementIF_CopyStandardEnvData_Dag(CopyDidInfoPtr);                                                            /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
  for (lDataIndex = 0u; lDataIndex < 5u; lDataIndex++)
  {
    Dem_Data_WriteDestinationBufferUint8(CopyDidInfoPtr->DestinationBuffer,                                                      /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
                                         Dem_MemoryEntry_GetStdEnvData(CopyDidInfoPtr->MemoryEntryId, lDataIndex + 5u));
  }
  return TRUE;
}
#endif


/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DEFINITIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \addtogroup Dem_IntDataElementIF_Public
 * \{
 */

#if ( (DEM_FEATURE_NEED_STATISTICAL_DATA == STD_ON) \
   || (DEM_FEATURE_NEED_OBD == STD_ON) )
/* ****************************************************************************
 % Dem_IntDataElementIF_CopyInternalDataElement
 *****************************************************************************/
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
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_IntDataElementIF_CopyInternalDataElement(
  CONST(Dem_DataReportIF_CopyDidInfoPtrType, AUTOMATIC)  CopyDidInfoPtr,
  CONST(Dem_Cfg_DataIndexType, AUTOMATIC)  DataIndex
  )
{
  boolean lReturnValue;
  uint8 lDataCallbackType;

  lDataCallbackType = Dem_Cfg_DataCallbackType(DataIndex);
  switch (lDataCallbackType)
  {
  case DEM_CFG_DATA_FROM_AGINGCTR:
    lReturnValue = Dem_IntDataElementIF_CopyUpwardsAgingCounter(CopyDidInfoPtr);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OCCCTR:
    lReturnValue = Dem_IntDataElementIF_Copy1ByteOccurrenceCounter(CopyDidInfoPtr);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OCCCTR_2BYTE:
    lReturnValue = Dem_IntDataElementIF_Copy2ByteOccurrenceCounter(CopyDidInfoPtr);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OVFLIND:
    lReturnValue = Dem_IntDataElementIF_CopyOverflowIndication(CopyDidInfoPtr);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_SIGNIFICANCE:
    lReturnValue = Dem_IntDataElementIF_CopyEventSignificance(CopyDidInfoPtr);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_PRIORITY:
    lReturnValue = Dem_IntDataElementIF_CopyEventPriority(CopyDidInfoPtr);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_AGINGCTR_INVERTED:
    lReturnValue = Dem_IntDataElementIF_CopyDownwardsAgingCounter(CopyDidInfoPtr);                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_MAX_FDC_SINCE_LAST_CLEAR:
    lReturnValue = Dem_IntDataElementIF_CopyMaxFdcSinceLastClear(CopyDidInfoPtr);                                                /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_MAX_FDC_DURING_CURRENT_CYCLE:
    lReturnValue = Dem_IntDataElementIF_CopyMaxFdcThisCycle(CopyDidInfoPtr);                                                     /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_FAILED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesSinceLastFailed(CopyDidInfoPtr);                                               /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_FAILED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesSinceFirstFailed(CopyDidInfoPtr);                                              /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_WUC_SINCE_LAST_FAILED:
      lReturnValue = Dem_IntDataElementIF_CopyWarmUpCyclesSinceLastFailed(CopyDidInfoPtr);                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
      break;

  case DEM_CFG_DATA_FROM_FAILED_CYCLES:
    lReturnValue = Dem_IntDataElementIF_CopyFailedCycles(CopyDidInfoPtr);                                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CONSECUTIVE_FAILED_CYCLES:
    lReturnValue = Dem_IntDataElementIF_CopyConsecutiveFailedCycles(CopyDidInfoPtr);                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_FAULT_PENDING_COUNTER:
    lReturnValue = Dem_IntDataElementIF_CopyFaultPendingCounter(CopyDidInfoPtr);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_FIRST_FAILED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesTestedSinceFirstFailed(CopyDidInfoPtr);                                        /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_TESTED_SINCE_LAST_FAILED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesTestedSinceLastFailed(CopyDidInfoPtr);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_HEALINGCTR_DOWNCNT:
    lReturnValue = Dem_IntDataElementIF_CopyHealingCounterDownwards(CopyDidInfoPtr);                                             /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_ROOTCAUSE_EVENTID:
    lReturnValue = Dem_IntDataElementIF_CopyRootCauseEventId(CopyDidInfoPtr);                                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OBDDTC:
    lReturnValue = Dem_IntDataElementIF_CopyEventObdDtc(CopyDidInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OBDDTC_3BYTE:
    lReturnValue = Dem_IntDataElementIF_CopyEventObdDtc_3Byte(CopyDidInfoPtr);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_OBD_RATIO:
    lReturnValue = Dem_IntDataElementIF_CopyEventObdRatio(CopyDidInfoPtr);                                                       /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_SINCE_LAST_UNCONFIRMED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesSinceLastUnconfirmed(CopyDidInfoPtr);                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_PASSED_SINCE_LAST_UNCONFIRMED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesPassedSinceLastUnconfirmed(CopyDidInfoPtr);                                    /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_SINCE_FIRST_UNCONFIRMED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesSinceFirstUnconfirmed(CopyDidInfoPtr);                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_UNCONFIRMED_CYCLES:
    lReturnValue = Dem_IntDataElementIF_CopyUnconfirmedCycles(CopyDidInfoPtr);                                                   /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CYCLES_PASSED_OR_UNCONFIRMED_SINCE_FIRST_UNCONFIRMED:
    lReturnValue = Dem_IntDataElementIF_CopyCyclesPassedOrUnconfirmed(CopyDidInfoPtr);                                           /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_CURRENT_FDC:
    lReturnValue = Dem_IntDataElementIF_CopyCurrentFdc(CopyDidInfoPtr);                                                          /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_AGED_COUNTER:
    lReturnValue = Dem_IntDataElementIF_CopyAgedCounter(CopyDidInfoPtr);                                                         /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

  case DEM_CFG_DATA_FROM_DTC_STATUS_INDICATOR:
    lReturnValue = Dem_IntDataElementIF_CopyPreConfirmedStatus(CopyDidInfoPtr);                                                  /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;

# if ( (DEM_CFG_DATA_DAG_STANDARD_ENV_DATA == STD_ON) || (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON) )
  case DEM_CFG_DATA_FROM_DAG_STANDARD_ENV_DATA:
    lReturnValue = Dem_IntDataElementIF_CopyStandardEnvData_Dag(CopyDidInfoPtr);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;
# endif

# if (DEM_CFG_DATA_DAG_EXTENDED_ENV_DATA == STD_ON)
  case DEM_CFG_DATA_FROM_DAG_EXTENDED_ENV_DATA:
    lReturnValue = Dem_IntDataElementIF_CopyExtendedEnvData_Dag(CopyDidInfoPtr);                                                 /* SBSW_DEM_POINTER_FORWARD_ARGUMENT */
    break;
# endif

  default:
    lReturnValue = FALSE;
    DEM_IGNORE_UNUSED_CONST_ARGUMENT(CopyDidInfoPtr)                                                                             /* PRQA S 3112 */ /* MD_DEM_14.2 */
    break;
  }
  return lReturnValue;
}                                                                                                                                /* PRQA S 6030, 6050 */ /* MD_MSR_STCYC, MD_MSR_STCAL */
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_INTDATAELEMENTIF_IMPLEMENTATION_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_IntDataElementIF_Implementation.h
 *********************************************************************************************************************/
