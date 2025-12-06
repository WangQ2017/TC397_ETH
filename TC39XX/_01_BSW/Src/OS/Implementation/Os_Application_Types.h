/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 * \addtogroup Os_Application
 * \{
 *
 * \file
 * \brief       Type definitions of the Application module.
 * \details     --no details--
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os.h.
 **********************************************************************************************************************/

#ifndef OS_APPLICATION_TYPES_H
# define OS_APPLICATION_TYPES_H
                                                                                                                         /* PRQA S 0388 EOF */ /* MD_MSR_Dir1.1 */
/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Types_Lcfg.h"


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Empty application bit mask. */
# define OS_APPMASK_NONE            ((Os_AppMaskType)(0))

/*! The bit width of Os_AppMaskType. */
# define OS_APPMASK_BITWIDTH        (32u)

/*! The number of bits needed to address each bit in Os_AppMaskType. */
# define OS_APPMASK_INDEXBITWIDTH   (5u)

/*! \brief   The number of entries in the OS object application access array.
 *  \details Only used if the number of configured OS Applications is larger than OS_APPMASK_BITWIDTH. */
# define OS_APPMASK_ARRAY_SIZE      ((OS_APPID_COUNT / OS_APPMASK_BITWIDTH) + 1u)


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  OS_APPID2MASK()
 **********************************************************************************************************************/
/*! \brief      Transform application ID to access mask.
 *  \details    The access mask is used for application access checking.
 *
 *  \param[in]  AppId    Application to transform.
 *
 *  \return     Access mask of this application.
 *
 *  \context    OS_INTERNAL
 *
 *  \pre        -
 **********************************************************************************************************************/
# define OS_APPID2MASK(AppId)   ((Os_AppMaskType)(1uL << ((Os_AppMaskType)(AppId) % OS_APPMASK_BITWIDTH)))

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/*! Access mask to store accessing applications to an OS object. */
typedef uint32 Os_AppMaskType;

struct Os_AppConfigType_Tag;
typedef struct Os_AppConfigType_Tag Os_AppConfigType;


/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/




#endif /* OS_APPLICATION_TYPES_H */

/* module specific MISRA deviations:
 */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Application_Types.h
 **********************************************************************************************************************/
