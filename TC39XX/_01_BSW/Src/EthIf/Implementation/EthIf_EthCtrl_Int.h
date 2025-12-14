/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_EthCtrl_Int.h
 *        \brief  EthIf EthCtrl internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module EthCtrl of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
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

#if !defined (ETHIF_ETHCTRL_INT_H)
# define ETHIF_ETHCTRL_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthCtrl_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */
# include "EthIf_Tx_Int.h"

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to <User> resolved through EthIf_Lcfg.h -> no include needed */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_ETHCTRL_INT_LOCAL)                                                                                 /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_ETHCTRL_INT_LOCAL static
# endif

# if !defined (ETHIF_ETHCTRL_INT_LOCAL_INLINE)                                                                          /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_ETHCTRL_INT_LOCAL_INLINE LOCAL_INLINE
# endif

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if !defined(ETHIF_UNIT_TEST)                                                                                          /* COV_ETHIF_UNIT_TEST */

# endif /* ETHIF_UNIT_TEST */

/**********************************************************************************************************************
 *  EthIf_EthCtrl_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf EthCtrl sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_EthCtrl_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ETHCTRL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthCtrl_Int.h
 *********************************************************************************************************************/

