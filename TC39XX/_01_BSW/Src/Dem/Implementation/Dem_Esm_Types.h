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
/*! \addtogroup Dem_Esm
 *  \{
 *  \file       Dem_Esm_Types.h
 *  \brief      Diagnostic Event Manager (Dem) header file
 *  \details    
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

#if !defined (DEM_ESM_TYPES_H)
#define DEM_ESM_TYPES_H

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
 * \defgroup  Dem_Esm_PermanentDtcStatus  Macros encoding status values for permanent DTCs
 * Macros encoding status values for permanent DTCs. Low byte is used for the state and the high byte is used for the visibility and the clear conditions
 * \{
 */
# define DEM_ESM_PERMANENT_STATES                (0x03U)  /*!< range of valid permanent states */
# define DEM_ESM_PERMANENT_STATEMASK             (0xfcU)  /*!< inverted DEM_ESM_PERMANENT_STATES */

# define DEM_ESM_PERMANENT_NONE                  (0x00U)  /*!< Permanent entry not used */
# define DEM_ESM_PERMANENT_ACTIVE                (0x01U)  /*!< Permanent entry active */
# define DEM_ESM_PERMANENT_PASSIVE               (0x02U)  /*!< Permanent entry not active */

# define DEM_ESM_PERMANENT_VISIBLE               (0x80U)  /*!< Permanent entry visible in mode 0xa */
# define DEM_ESM_PERMANENT_VISIBLEMASK           (0x7fU)  /*!< Mask to reset DEM_ESM_PERMANENT_VISIBLE */
# define DEM_ESM_PERMANENT_CONDITION_TESTED      (0x40U)  /*!< Permanent entry DTC tested this DCY */
# define DEM_ESM_PERMANENT_CONDITION_TESTEDMASK  (0xbfU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_TESTED */
# define DEM_ESM_PERMANENT_CONDITION_PFC         (0x20U)  /*!< Permanent entry PFC condition fulfilled */
# define DEM_ESM_PERMANENT_CONDITION_PFCMASK     (0xdfU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_PFC */
# define DEM_ESM_PERMANENT_CONDITION_DCY         (0x10U)  /*!< Permanent entry DCY qualified */
# define DEM_ESM_PERMANENT_CONDITION_DCYMASK     (0xefU)  /*!< Mask to reset DEM_ESM_PERMANENT_CONDITION_DCY */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Esm_WwhObdClass  Macros encoding WWHOBD DTC Classes
 * Macros encoding WWHOBD DTC Classes
 * \{
 */
# define DEM_ESM_WWHOBD_NUMBER_DTCCLASS          5U  /*!< Number of WWH-OBD DTC classes */

# define DEM_ESM_WWHOBD_DTCCLASS_NO              0U  /*!< No WWH-OBD DTC class */
# define DEM_ESM_WWHOBD_DTCCLASS_C               1U  /*!< WWH-OBD DTC class C */
# define DEM_ESM_WWHOBD_DTCCLASS_B2              2U  /*!< WWH-OBD DTC class B2 */
# define DEM_ESM_WWHOBD_DTCCLASS_B1              3U  /*!< WWH-OBD DTC class B1 */
# define DEM_ESM_WWHOBD_DTCCLASS_A               4U  /*!< WWH-OBD DTC class A */
/*!
 * \}
 */

/*! Aging timer 200 hour threshold value */
#define DEM_ESM_AGINGTIME_200h                   (0x00002ee0U)

#if (DEM_CFG_STORAGE_AT_CONFIRMED == STD_ON)                                                                                     /* PRQA S 0883 */ /* MD_DEM_19.15 */
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           DEM_CFG_TRIGGER_CONFIRMED
#elif (DEM_CFG_STORAGE_AT_FAILED == STD_ON) || (DEM_CFG_STORAGE_AT_PENDING == STD_ON)
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)
#elif (DEM_CFG_STORAGE_AT_FDC == STD_ON)                                                                                         /* COV_MSR_CONFIG TX */
/*! Trigger mask for creation of an event memory entry */
# define DEM_ESM_EVENT_STORAGE_TRIGGER           (DEM_CFG_TRIGGER_FDC|DEM_CFG_TRIGGER_TESTFAILED)
#else
# error "No event storage trigger defined"
#endif

#if ( (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)   \
   || (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)   \
   || (DEM_CFG_PROCESS_TFSLC_STOREDONLY == STD_ON) )
/*! Option setting if status bits depend on creation of an event memory entry */
# define DEM_FEATURE_NEED_STOREDONLY_BITS        STD_ON
#else
/*! Option setting if status bits depend on creation of an event memory entry */
# define DEM_FEATURE_NEED_STOREDONLY_BITS        STD_OFF
#endif

#if (DEM_CFG_PROCESS_PDTC_STOREDONLY == STD_ON)
/*! Mask for stored only Pending DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_PENDING        DEM_CFG_TRIGGER_PENDING
#else
/*! Mask for stored only Pending DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_PENDING        0x00U
#endif
#if (DEM_CFG_PROCESS_CDTC_STOREDONLY == STD_ON)
/*! Mask for stored only Confirmed DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED      DEM_CFG_TRIGGER_CONFIRMED
#else
/*! Mask for stored only Confirmed DTC trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED      0x00U
#endif
#if (DEM_CFG_PROCESS_WIR_STOREDONLY == STD_ON)
/*! Mask for stored only Warning Indicator Requested trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_INDICATOR      DEM_CFG_TRIGGER_INDICATOR
#else
/*! Mask for stored only Warning Indicator Requested trigger */
# define DEM_ESM_EVENT_NO_TRIGGER_INDICATOR      0x00U
#endif


#if (DEM_FEATURE_NEED_OEM_EXTENSIONS_VCC == STD_ON)
/*! Trigger Mask for event occurence */
#define DEM_ESM_EVENT_OCCURENCE_TRIGGER             (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_TESTFAILEDTHISCYCLE)
#else
/*! Trigger Mask for event updates */
#define DEM_ESM_EVENT_OCCURENCE_TRIGGER             DEM_CFG_TRIGGER_TESTFAILED
#endif

/*! Trigger Mask for enviromental data that could not be stored previously
    (due to missing event entry) and have a configured trigger inclued in TF transition*/
#define DEM_ESM_EVENT_CATCHUP_TRIGGER             (DEM_CFG_TRIGGER_TESTFAILED|DEM_CFG_TRIGGER_FDC|DEM_CFG_TRIGGER_FIRSTTHISCYCLE|DEM_CFG_TRIGGER_PENDING)

/*! Reset Mask for stored only triggers */
#define DEM_ESM_EVENT_RESET_TRIGGER_MASK         ((uint8)(0xffU ^ (DEM_ESM_EVENT_NO_TRIGGER_PENDING   \
                                                                 | DEM_ESM_EVENT_NO_TRIGGER_CONFIRMED \
                                                                 | DEM_ESM_EVENT_NO_TRIGGER_INDICATOR)))

                                                    /* PID01 PID41 Readiness */
/* ------------------------------------------------------------------------- */

/*!
 * \defgroup  Dem_Readiness_Initialize  Macros encoding initial values
 * Macros encoding initial values depending on engine type
 * \{
 */
/*!< Readiness initialization for spark engines */
#define DEM_READINESS_INITIALIZE_UPDATE_SPARK                  ( ((uint16)1 << DEM_CFG_READINESS_CAT ) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_HTCAT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_EVAP)  \
                                                               | ((uint16)1 << DEM_CFG_READINESS_SECAIR) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_O2SENS) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_O2SENSHT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_CMPRCMPT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_EGR) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_FLSYS_NONCONT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_MISF) )  

/*!< Readiness initialization for compression engines */
#define DEM_READINESS_INITIALIZE_UPDATE_COMPRESSION            ( ((uint16)1 << DEM_CFG_READINESS_HCCAT ) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_NOXCAT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_BOOSTPR) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_PMFLT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_EGSENS) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_CMPRCMPT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_EGR) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_FLSYS_NONCONT) \
                                                               | ((uint16)1 << DEM_CFG_READINESS_MISF) ) 

#define DEM_READINESS_INITIALIZE_PID01COMPLETED_SPARK          (0xFFFFFFEFUL)  /*!< Readiness initialization for spark engines */
#define DEM_READINESS_INITIALIZE_PID01COMPLETED_COMPRESSION    (0xFFFFFFEBUL)  /*!< Readiness initialization for compression engines */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Readiness_Support_State  Macros encoding assignment of readiness group supported state
 * Macros encoding assignment of readiness group supported state to 32-bit mask
 * \{
 */
#define DEM_READINESS_SUPPORT_NONE_MASK               (0x00000000UL)             /*!< Used to initialze local variables */
#define DEM_READINESS_SUPPORT_MISF_MASK               (0x00010000UL)             /*!< Bit encoding for DEM_OBD_RDY_MISF supported state */
#define DEM_READINESS_SUPPORT_FLSYS_MASK              (0x00020000UL)             /*!< Bit encoding for DEM_OBD_RDY_FLSYS and DEM_OBD_RDY_FLSYS_NONCONT supported state */
#define DEM_READINESS_SUPPORT_CMPRCMPT                (0x00040000UL)             /*!< Bit encoding for DEM_OBD_RDY_CMPRCMPT supported state */
#define DEM_READINESS_SUPPORT_CAT_MASK                (0x00000100UL)             /*!< Bit encoding for DEM_OBD_RDY_CAT supported state */
#define DEM_READINESS_SUPPORT_HCCAT_MASK              (0x00000100UL)             /*!< Bit encoding for DEM_OBD_RDY_HCCAT supported state */
#define DEM_READINESS_SUPPORT_HTCAT_MASK              (0x00000200UL)             /*!< Bit encoding for DEM_OBD_RDY_HTCAT supported state */
#define DEM_READINESS_SUPPORT_NOXCAT_MASK             (0x00000200UL)             /*!< Bit encoding for DEM_OBD_RDY_NOXCAT supported state */
#define DEM_READINESS_SUPPORT_EVAP_MASK               (0x00000400UL)             /*!< Bit encoding for DEM_OBD_RDY_EVAP supported state */
#define DEM_READINESS_SUPPORT_SECAIR_MASK             (0x00000800UL)             /*!< Bit encoding for DEM_OBD_RDY_SECAIR supported state */
#define DEM_READINESS_SUPPORT_BOOSTPR_MASK            (0x00000800UL)             /*!< Bit encoding for DEM_OBD_RDY_BOOSTPR supported state */
#define DEM_READINESS_SUPPORT_O2SENS_MASK             (0x00002000UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENS supported state */
#define DEM_READINESS_SUPPORT_EGSENS_MASK             (0x00002000UL)             /*!< Bit encoding for DEM_OBD_RDY_EGSENS supported state */
#define DEM_READINESS_SUPPORT_O2SENSHT_MASK           (0x00004000UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENSHT supported state */
#define DEM_READINESS_SUPPORT_PMFLT_MASK              (0x00004000UL)             /*!< Bit encoding for DEM_OBD_RDY_PMFLT supported state */
#define DEM_READINESS_SUPPORT_EGR_MASK                (0x00008000UL)             /*!< Bit encoding for DEM_OBD_RDY_ERG supported state */
#define DEM_READINESS_SUPPORT_COMPRESSION             (0x00080000UL)             /*!< Bit encoding for engine type compression ignition supported state */
/*!
 * \}
 */

/*!
 * \defgroup  Dem_Readiness_Completed_State  Macros encoding assignment of readiness group completed state
 * Macros encoding assignment of readiness group completed state to 32-bit mask
 * \{
 */
#define DEM_READINESS_COMPLETE_MISF_MASK              (0x00100000UL)             /*!< Bit encoding for DEM_OBD_RDY_MISF completed state */
#define DEM_READINESS_COMPLETE_FLSYS_MASK             (0x00200000UL)             /*!< Bit encoding for DEM_OBD_RDY_FLSYS and DEM_OBD_RDY_FLSYS_NONCONT completed state */
#define DEM_READINESS_COMPLETE_CMPRCMPT               (0x00400000UL)             /*!< Bit encoding for DEM_OBD_RDY_CMPRCMPT completed state */
#define DEM_READINESS_COMPLETE_CAT_MASK               (0x00000001UL)             /*!< Bit encoding for DEM_OBD_RDY_CAT completed state */
#define DEM_READINESS_COMPLETE_HCCAT_MASK             (0x00000001UL)             /*!< Bit encoding for DEM_OBD_RDY_HCCAT completed state */
#define DEM_READINESS_COMPLETE_HTCAT_MASK             (0x00000002UL)             /*!< Bit encoding for DEM_OBD_RDY_HTCAT completed state */
#define DEM_READINESS_COMPLETE_NOXCAT_MASK            (0x00000002UL)             /*!< Bit encoding for DEM_OBD_RDY_NOXCAT completed state */
#define DEM_READINESS_COMPLETE_EVAP_MASK              (0x00000004UL)             /*!< Bit encoding for DEM_OBD_RDY_EVAP completed state */
#define DEM_READINESS_COMPLETE_SECAIR_MASK            (0x00000008UL)             /*!< Bit encoding for DEM_OBD_RDY_SECAIR completed state */
#define DEM_READINESS_COMPLETE_BOOSTPR_MASK           (0x00000008UL)             /*!< Bit encoding for DEM_OBD_RDY_BOOSTPR completed state */
#define DEM_READINESS_COMPLETE_O2SENS_MASK            (0x00000020UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENS completed state */
#define DEM_READINESS_COMPLETE_EGSENS_MASK            (0x00000020UL)             /*!< Bit encoding for DEM_OBD_RDY_EGSENS completed state */
#define DEM_READINESS_COMPLETE_O2SENSHT_MASK          (0x00000040UL)             /*!< Bit encoding for DEM_OBD_RDY_O2SENSHT completed state */
#define DEM_READINESS_COMPLETE_PMFLT_MASK             (0x00000040UL)             /*!< Bit encoding for DEM_OBD_RDY_PMFLT completed state */
#define DEM_READINESS_COMPLETE_EGR_MASK               (0x00000080UL)             /*!< Bit encoding for DEM_OBD_RDY_ERG completed state */
/*!
 * \}
 */

/* ********************************************************************************************************************
 *  SUBCOMPONENT FUNCTION MACROS
 *********************************************************************************************************************/

#if (DEM_CFG_SUPPORT_PERMANENT == STD_ON)
/* Permanent status bit 'event visible in permanent memory' ---------------- */
/*! Test permanent entry visible in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_VISIBLE(Var)        (((Var) & DEM_ESM_PERMANENT_VISIBLE) != 0u)
/*! Set permanent entry visible in permanent entry state */
# define DEM_ESM_SET_PERMANENT_VISIBLE(Status)      ((uint8)((Status) | DEM_ESM_PERMANENT_VISIBLE))
/*! Reset permanent entry visible in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_VISIBLE(Status)    ((uint8)((Status) & DEM_ESM_PERMANENT_VISIBLEMASK))

/* Permanent status bit 'tested condition' ---------------- */
/*! Test permanent condition tested in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_TESTED(Var)        (((Var) & DEM_ESM_PERMANENT_CONDITION_TESTED) != 0u)
/*! Set permanent condition tested in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_TESTED(Status)      ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_TESTED))
/*! Reset permanent condition tested in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_TESTED(Status)    ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_TESTEDMASK))

/* Permanent status bit 'PFC condition' ---------------- */
/*! Test permanent condition PFC in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_PFC(Var)           (((Var) & DEM_ESM_PERMANENT_CONDITION_PFC) != 0u)
/*! Set permanent condition PFC in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_PFC(Status)         ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_PFC))
/*! Reset permanent condition PFC in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_PFC(Status)       ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_PFCMASK))

/* Permanent status bit 'DCY condition' ---------------- */
/*! Test permanent condition DCY in permanent entry state */
# define DEM_ESM_TEST_PERMANENT_CONDITION_DCY(Var)           (((Var) & DEM_ESM_PERMANENT_CONDITION_DCY) != 0u)
/*! Set permanent condition DCY in permanent entry state */
# define DEM_ESM_SET_PERMANENT_CONDITION_DCY(Status)         ((uint8)((Status) | DEM_ESM_PERMANENT_CONDITION_DCY))
/*! Reset permanent condition DCY in permanent entry state */
# define DEM_ESM_RESET_PERMANENT_CONDITION_DCY(Status)       ((uint8)((Status) & DEM_ESM_PERMANENT_CONDITION_DCYMASK))

/* Permanent entry current FSM status -------------------------------------- */
/*! Get permanent state part of permanent entry condition byte */
# define DEM_ESM_GET_PERMANENT_STATE(Status)        ((uint8)((Status) & DEM_ESM_PERMANENT_STATES))
/*! Set permanent state part of permanent entry condition byte */
# define DEM_ESM_SET_PERMANENT_STATE(Var, Status)   ((uint8)(((uint8)((Var) & DEM_ESM_PERMANENT_STATEMASK)) | ((uint8)((Status) & DEM_ESM_PERMANENT_STATES))))
#endif /* DEM_CFG_SUPPORT_PERMANENT == STD_ON */




/* ********************************************************************************************************************
 *  SUBCOMPONENT DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#endif /* DEM_ESM_TYPES_H */

/*!
 * \}
 */
/* ********************************************************************************************************************
 *  END OF FILE: Dem_Esm_Types.h
 *********************************************************************************************************************/
