/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *             File:  Rte_Cdd_SomeIP_Type.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application types header file for SW-C <Cdd_SomeIP>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_CDD_SOMEIP_TYPE_H
# define RTE_CDD_SOMEIP_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

# endif /* RTE_CORE */


/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
# ifndef RTE_MODETYPE_SDC_SdClientServiceState
#  define RTE_MODETYPE_SDC_SdClientServiceState
typedef uint8 Rte_ModeType_SDC_SdClientServiceState;
# endif
# ifndef RTE_MODETYPE_SDC_SdConsumedEventGroupState
#  define RTE_MODETYPE_SDC_SdConsumedEventGroupState
typedef uint8 Rte_ModeType_SDC_SdConsumedEventGroupState;
# endif
# ifndef RTE_MODETYPE_SDC_SdEventHandlerState
#  define RTE_MODETYPE_SDC_SdEventHandlerState
typedef uint8 Rte_ModeType_SDC_SdEventHandlerState;
# endif

# define RTE_MODE_Cdd_SomeIP_SDC_SdClientServiceState_SDC_CLIENT_DOWN (0U)
# ifndef RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN
#  define RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN (0U)
# endif
# define RTE_MODE_Cdd_SomeIP_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE (1U)
# ifndef RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE
#  define RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE (1U)
# endif
# define RTE_TRANSITION_Cdd_SomeIP_SDC_SdClientServiceState (2U)
# ifndef RTE_TRANSITION_SDC_SdClientServiceState
#  define RTE_TRANSITION_SDC_SdClientServiceState (2U)
# endif

# define RTE_MODE_Cdd_SomeIP_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN (0U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN
#  define RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN (0U)
# endif
# define RTE_MODE_Cdd_SomeIP_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE (1U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE
#  define RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE (1U)
# endif
# define RTE_TRANSITION_Cdd_SomeIP_SDC_SdConsumedEventGroupState (2U)
# ifndef RTE_TRANSITION_SDC_SdConsumedEventGroupState
#  define RTE_TRANSITION_SDC_SdConsumedEventGroupState (2U)
# endif

# define RTE_MODE_Cdd_SomeIP_SDC_SdEventHandlerState_SDC_EH_RELEASED (0U)
# ifndef RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED
#  define RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED (0U)
# endif
# define RTE_MODE_Cdd_SomeIP_SDC_SdEventHandlerState_SDC_EH_REQUESTED (1U)
# ifndef RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED
#  define RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED (1U)
# endif
# define RTE_TRANSITION_Cdd_SomeIP_SDC_SdEventHandlerState (2U)
# ifndef RTE_TRANSITION_SDC_SdEventHandlerState
#  define RTE_TRANSITION_SDC_SdEventHandlerState (2U)
# endif

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_CDD_SOMEIP_TYPE_H */
