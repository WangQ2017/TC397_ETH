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
/*! \addtogroup Dem_Satellite
 *  \{
 *  \file       Dem_Satellite_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    Public types of the Satellite subcomponent
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

#if !defined (DEM_SATELLITE_TYPES_H)
#define DEM_SATELLITE_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                        /* Dem module header */
/* ------------------------------------------------------------------------- */
#include "Dem_ExtCom_Types.h"
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"
/* ------------------------------------------------------------------------- */


/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/
#define DEM_SATELLITE_APPLICATION_ZERO           0

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 /*! Iterator type for iteration over all high resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Satellite_DebounceHiResIterType;
/*! Iterator type for iteration over all low resolution debounce timers */
typedef struct Dem_Cfg_ComplexIterType_s Dem_Satellite_DebounceLoResIterType;

/*! Type for the current value of the satellite specific low resolution tick timer */
typedef uint8 Dem_Satellite_DebounceLoResTimerType;

/*! Handle of Satellite instances. Valid range [0 .. Dem_Cfg_GlobalSatelliteCount()[ . */
typedef Dem_SatelliteInfoType  Dem_Satellite_IdType;
/*! Handle of Monitors within satellite instances. Valid range [0 .. Dem_Cfg_GetEventCountOfSatelliteInfo(SatelliteId)[ . */
typedef uint16 Dem_Satellite_MonitorIdType;

/*! OS Application type wrapper. The type must be provided by the Os */
typedef Dem_ExtCom_ApplicationType Dem_Satellite_ApplicationType;


#endif /* DEM_SATELLITE_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Satellite_Types.h
 *********************************************************************************************************************/
