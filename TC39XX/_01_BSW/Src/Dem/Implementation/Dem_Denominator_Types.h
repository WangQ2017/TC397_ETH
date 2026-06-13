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
/*! \addtogroup Dem_Denominator
 *  \{
 *  \file       Dem_Denominator_Types.h
 *  \brief      IUMPR Ratio Denominator subcomponent.
 *  \details    Provides functionality to manipulate IUMPR ratio denominators, and react to denominator condition changes.
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

#if !defined (DEM_DENOMINATOR_TYPES_H)
#define DEM_DENOMINATOR_TYPES_H

/* ********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

                                                  /* Own subcomponent header */
/* ------------------------------------------------------------------------- */
#include "Dem_Int.h"

/* ********************************************************************************************************************
 *  SUBCOMPONENT CONSTANT MACROS
 *********************************************************************************************************************/

/*!
 * \defgroup  DEM_IUMPRDenominatorStatus  Macros encoding ratio specific denominator states
 * Macros encoding ratio specific denominator states
 * \{
 */
# define DEM_DENOMINATOR_INCREMENTED                       ((uint8)(0x01u))  /*!< Denominator incremented this DCY */
# define DEM_DENOMINATOR_INCREMENTED_MASK                  ((uint8)(0xfeU))  /*!< Reset mask for denominator incremented this DCY */
# define DEM_DENOMINATOR_LOCKED                            ((uint8)(0x02U))  /*!< Denominator status 'locked this DCY' */
# define DEM_DENOMINATOR_LOCKED_MASK                       ((uint8)(0xfdU))  /*!< Reset mask for denominator status 'locked this DCY' */
# define DEM_DENOMINATOR_CONDITIONS_REACHED                ((uint8)(0x04U))  /*!< Ratio specific denominator conditions reached this DCY */
# define DEM_DENOMINATOR_CONDITIONS_REACHED_MASK           ((uint8)(0xfbU))  /*!< Reset mask for ratio specific denominator conditions reached this DCY */
# define DEM_RATIO_FID_PENDING                             ((uint8)(0x08U))  /*!< Ratio blocked by pending FID */
# define DEM_RATIO_FID_PENDING_MASK                        ((uint8)(0xf7U))  /*!< Reset mask for ratio blocked by pending FID */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Iumpr_DenominatorStatus  Macros encoding ratio specific denominator states
 * Macros encoding ratio specific denominator states
 * \{
 */
# define DEM_DENOMINATOR_INDIGENDEN_CONDITIONS_REACHED       ((uint8)(0x80U))  /*!< General Individual Denominator Conditions is fulfilled */
# define DEM_DENOMINATOR_INDIGENDEN_CONDITIONS_REACHED_MASK  ((uint8)(0x7fU))  /*!< Reset mask for General Individual Denominator Condiitons */
/*!
 * \}
 */

 /* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#endif /* DEM_DENOMINATOR_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Denominator_Types.h
 *********************************************************************************************************************/
