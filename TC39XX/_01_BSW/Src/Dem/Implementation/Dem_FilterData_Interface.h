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
/*! \ingroup    Dem_Master
 *  \defgroup   Dem_FilterData DCM Filter Data
 *  \{
 *  \file       Dem_FilterData_Interface.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public interface of FilterData subcomponent
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

#if !defined (DEM_FILTERDATA_INTERFACE_H)
#define DEM_FILTERDATA_INTERFACE_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_FilterData_Types.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT OBJECT FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FilterData_PublicProperties Public Properties
 * \{
 */

/* ****************************************************************************
 * Dem_FilterData_TestFilterSet()
 *****************************************************************************/
/*!
 * \brief         Test if a distinct DTC filter has been set.
 *
 * \details       Test if a distinct DTC filter has been set.
 *
 * \param[in]     FilterId
 *                The object to read from.
 * \param[in]     Filter
 *                Filter to test.
 *
 * \return        TRUE
 *                Queried filter set.
 * \return        FALSE
 *                Queried filter not set.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestFilterSet(
  CONST(Dem_FilterData_HandleType, AUTOMATIC) FilterId,
  CONST(Dem_FilterData_FilterType, DEM_CODE) Filter
  );


/* ****************************************************************************
 * Dem_FilterData_TestUseFdc()
 *****************************************************************************/
/*!
 * \brief         Get the UseFdc flag of the given filter flags.
 *
 * \details       Get the UseFdc flag of the given filter flags.
 *
 * \param[in]     FilterId
 *                The Filter object handle.
 *
 * \return        The state of the UseFdc flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseFdc(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );

/* ****************************************************************************
 * Dem_FilterData_TestUseSeverity()
 *****************************************************************************/
/*!
 * \brief         Get the UseSeverity flag of the given filter flags.
 *
 * \details       Get the UseSeverity flag of the given filter flags.
 *
 * \param[in]     FilterId
 *                The Filter object handle.
 *
 * \return        The state of the UseSeverity flag.
 *
 * \pre           -
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(boolean, DEM_CODE)
Dem_FilterData_TestUseSeverity(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );



/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

/* ********************************************************************************************************************
 *  SUBCOMPONENT API FUNCTION DECLARATIONS
 *********************************************************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */
/*!
 * \defgroup Dem_FilterData_Public Public Methods
 * \{
 */

#if ( (DEM_CFG_SUPPORT_DCM == STD_ON) || (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON) )
/* ****************************************************************************
 * Dem_FilterData_InitDefault()
 *****************************************************************************/
/*!
 * \brief         Initialize a filter.
 *
 * \details       Initializes a filter, the filter does not contain filter
 *                data afterwards.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON ||
 *                DEM_CFG_SUPPORT_J1939_DM31 == STD_ON || 
 *                DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(void, DEM_CODE)
 Dem_FilterData_InitDefault(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_SetDTCFilter()
 *****************************************************************************/
/*!
 * \brief         Initialize a DTC filter.
 *
 * \details       Initializes a DTC filter based on the passed filter information.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \param[in]     DTCStatusMask
 *                The status byte mask for DTC status byte filtering.
 *
 * \param[in]     DTCFormat
 *                The DTC number format (OBD/UDS/J1939).
 *
 * \param[in]     MemoryId
 *                The event memory handle.
 *
 * \param[in]     FilterForOBD
 *                Defines if filtering is restricted to OBD relevant DTCs.
 *
 * \param[in]     FilterWithSeverity
 *                Defines if severity information is used for filtering.
 *
 * \param[in]     DTCSeverityMask
 *                The severity mask for severity filtering (only evaluated
 *                if severity information is used for filtering).
 *
 * \param[in]     FilterForFDC
 *                Defines if FDC information is used for filtering.
 *
 * \return        E_OK
 *                Filter was accepted.
 *                E_NOT_OK
 *                Filter was not accepted due to unconfigured memory.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_SetDTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  DTCStatusMask,
  CONST(Dem_DTCFormatType, AUTOMATIC)  DTCFormat,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(boolean, AUTOMATIC)  FilterForOBD,
  CONST(boolean, AUTOMATIC)  FilterWithSeverity,
  CONST(Dem_DTCSeverityType, AUTOMATIC)  DTCSeverityMask,
  CONST(boolean, AUTOMATIC)  FilterForFDC
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_CountMatchingDTCs
 *****************************************************************************/
/*!
 * \brief         Calculates the number of filtered events.
 *
 * \details       Calculates the number of filtered events.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \return        Number of DTCs matching the filter criteria.
 *
 * \pre           The client specific filter has been set.
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_FilterData_CountMatchingDTCs(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif

#if (DEM_CFG_SUPPORT_DCM == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_GetNextFilteredDTC
 *****************************************************************************/
/*!
 * \brief         Get the next matching event.
 *
 * \details       Get the next event matching the filter criteria set with 
 *                Dem_ClientAccess_SetDTCFilter.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event.
 *                FilterResult->DTC : 
 *                              The DTC of the matching event.
 *                FilterResult->FDC : 
 *                              The FDC of the matching event, updated only 
 *                              when FilterForFDC is TRUE.
 *                FilterResult->DTCStatus : 
 *                              The DTC status of the matching event.
 *                FilterResult->Severity : 
 *                              The severity of the matching event, updated 
 *                              only when FilterWithSeverity is true.
 *                FilterResult->FunctionalUnit : 
 *                              The functional unit of the matching event, 
 *                              updated only when FilterWithSeverity is true.

 *
 * \return        E_OK
 *                Matching element returned in FilterResult.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No more matching elements, FilterResult not modified.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_DCM == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) Dem_FilterData_GetNextFilteredDTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_SetFirstDTCWithLampStatus()
 *****************************************************************************/
/*!
 * \brief         Initialize a 'DTC with lamp status' filter.
 *
 * \details       Initialize a 'DTC with lamp status' filter.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \param[in]     NodeId
 *                The node Id 
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_DM31 == STD_ON || DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_FilterData_SetFirstDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_DM31 == STD_ON) || (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_GetNextDTCWithLampStatus
 *****************************************************************************/
/*!
 * \brief         Get the next matching event.
 *
 * \details       Get the next event matching the filter criteria set with 
 *                Dem_FilterData_SetFirstDTCWithLampStatus.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event.
 *                FilterResult->DTC : 
 *                              The J1939 DTC of the matching event.
 *                FilterResult->OccurrenceCounter : 
 *                              The occurrence counter of the matching event.
 *                FilterResult->LampStatus : 
 *                              The lamp status of the matching event.
 *
 * \return        E_OK
 *                Matching element returned in FilterResult.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No more matching elements, FilterResult not modified.
 *
 * \pre           The client specific filter has been set.
 * \config        DEM_CFG_SUPPORT_J1939_DM31 == STD_ON || DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_FilterData_GetNextDTCWithLampStatus(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_SetJ1939DTCFilter()
 *****************************************************************************/
/*!
 * \brief         Initialize a J1939 DTC filter.
 *
 * \details       Initializes a J1939 DTC filter based on the passed filter 
 *                information.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 * \param[in]     DTCStatusFilter
 *                The DTC status filter type.
 * \param[in]     DTCKind
 *                DTC kind to filter.
 * \param[in]     MemoryId
 *                The event memory handle.
 * \param[in]     NodeId
 *                The node Id.
 * \param[out]    LampStatus
 *                Pointer to receive the Lamp status for the node.
 *
 * \return        E_OK
 *                Filter was accepted.
 *                E_NOT_OK
 *                Filter was not accepted due to invalid parameters.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE)
Dem_FilterData_SetJ1939DTCFilter(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(Dem_J1939DcmDTCStatusFilterType, AUTOMATIC)  DTCStatusFilter,
  CONST(Dem_DTCKindType, AUTOMATIC)  DTCKind,
  CONST(uint8, AUTOMATIC)  MemoryId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmLampStatusType, AUTOMATIC, DEM_J1939DCM_DATA)  LampStatus
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_GetNumberOfFilteredJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Calculates the number of events matching the J1939 DTC filter.
 *
 * \details       Calculates the number of events matching the J1939 DTC filter.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \return        Number of DTCs matching the J1939 DTC filter criteria.
 *
 * \pre           The client specific filter has been set.
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK
 * \synchronous   TRUE
 * \reentrant     FALSE
 *****************************************************************************/
DEM_LOCAL FUNC(uint16, DEM_CODE)
Dem_FilterData_GetNumberOfFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_GetNextFilteredJ1939DTC
 *****************************************************************************/
/*!
 * \brief         Get the next matching event.
 *
 * \details       Get the next event matching the filter criteria set with 
 *                Dem_FilterData_SetJ1939DTCFilter.
 *
 * \param[in]     FilterId
 *                The filter to modify.
 *
 * \param[out]    FilterResult
 *                Pointer to receive the next matching event.
 *                FilterResult->DTC : 
 *                              The J1939 DTC of the matching event.
 *                FilterResult->OccurrenceCounter : 
 *                              The occurrence counter of the matching event.
 *
 * \return        E_OK
 *                Matching element returned in FilterResult.
 * \return        DEM_NO_SUCH_ELEMENT
 *                No more matching elements, FilterResult not modified.
 * \return        DEM_PENDING
 *                Filtering is currently in progress and runtime limit
 *                was reached, FilterResult not modified.
 *
 * \pre           The client specific filter has been set.
 * \config        DEM_CFG_SUPPORT_J1939_READ_DTC == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE for different ClientIds
 *****************************************************************************/
DEM_LOCAL_INLINE FUNC(Std_ReturnType, DEM_CODE) 
Dem_FilterData_GetNextFilteredJ1939DTC(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONSTP2VAR(Dem_FilterData_ResultType, AUTOMATIC, AUTOMATIC)  FilterResult
  );
#endif

#if (DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON)
/* ****************************************************************************
 * Dem_FilterData_GetDiagnosticReadiness()
 *****************************************************************************/
/*!
 * \brief         Calculates the diagnostic readiness value for the given node
 *
 * \details       Calculates the diagnostic readiness value for the given node
 *
 * \param[in]     FilterId
 *                The filter to modify.
 * \param[in]     NodeId
 *                The node Id.
 * \param[out]    DiagnosticReadiness
 *                Pointer to receive the diagnostic readiness value.
 *
 * \pre           -
 * \config        DEM_CFG_SUPPORT_J1939_READINESS1 == STD_ON
 *
 * \context       TASK|ISR2
 * \synchronous   TRUE
 * \reentrant     TRUE, for different FilterIds
 *****************************************************************************/
DEM_LOCAL FUNC(void, DEM_CODE)
Dem_FilterData_GetDiagnosticReadiness(
  CONST(Dem_FilterData_HandleType, AUTOMATIC)  FilterId,
  CONST(uint8, AUTOMATIC)  NodeId,
  CONSTP2VAR(Dem_J1939DcmDiagnosticReadiness1Type, AUTOMATIC, DEM_J1939DCM_DATA)  DiagnosticReadiness
  );
#endif

/*!
 * \}
 */
#define DEM_STOP_SEC_CODE
#include "MemMap.h"                                                                                                              /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* DEM_FILTERDATA_INTERFACE_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_FilterData_Interface.h
 *********************************************************************************************************************/
