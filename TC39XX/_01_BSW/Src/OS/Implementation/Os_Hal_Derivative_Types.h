/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2019 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \ingroup      Os_Hal
 *  \defgroup     Os_Hal_Derivative HAL Derivative
 *  \brief        Defines derivative specific functionality.
 *  \details
 *  This modules decides which HAL specific sub components are needed to implement HAL functionality on a specific
 *  derivative.
 *
 *  \{
 *
 * \file          Os_Hal_Derivative_Types.h
 *  \brief        Selects a derivative specific header and includes it.
 *
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/


#ifndef OS_HAL_DERIVATIVE_TYPES_H
# define OS_HAL_DERIVATIVE_TYPES_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Cfg.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
# if defined(OS_CFG_DERIVATIVEGROUP_TC21X)                                                                              /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC21x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC22X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC22x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC23X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC23x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC24X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC24x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC26X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC26x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC27X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC27x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC29X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC29x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC32XL)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC32xL_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC33X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC33x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC33XD)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC33xD_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC35X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC35x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC36X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC36x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC37X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC37x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC37XD)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC37xD_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC38X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC38x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC38XT)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC38xT_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC39X)                                                                            /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC39x_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC39XQ)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC39xQ_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC3EXQ)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC3ExQ_Types.h"
# elif defined(OS_CFG_DERIVATIVEGROUP_TC49X)                                                                           /* COV_OS_DERIVATIVEGROUP */
#  include "Os_Hal_Derivative_TC49x_Types.h"
# else
#  error "The selected derivative is not supported!"
# endif /* OS_CFG_DERIVATIVEGROUP_<> */

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_DERIVATIVE_TYPES_H */

/*!
 * \}
 */
/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Derivative_Types.h
 **********************************************************************************************************************/
