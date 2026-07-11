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
 *             File:  Rte_BswM_Type.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application types header file for SW-C <BswM>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_BSWM_TYPE_H
# define RTE_BSWM_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef STARTUP
#   define STARTUP (0U)
#  endif

#  ifndef RUN
#   define RUN (1U)
#  endif

#  ifndef POSTRUN
#   define POSTRUN (2U)
#  endif

#  ifndef WAKEUP
#   define WAKEUP (3U)
#  endif

#  ifndef SHUTDOWN
#   define SHUTDOWN (4U)
#  endif

#  ifndef RELEASED
#   define RELEASED (0U)
#  endif

#  ifndef REQUESTED
#   define REQUESTED (1U)
#  endif

#  ifndef SDC_CLIENT_RELEASED
#   define SDC_CLIENT_RELEASED (0U)
#  endif

#  ifndef SDC_CLIENT_REQUESTED
#   define SDC_CLIENT_REQUESTED (1U)
#  endif

#  ifndef SDC_CLIENT_DOWN
#   define SDC_CLIENT_DOWN (0U)
#  endif

#  ifndef SDC_CLIENT_AVAILABLE
#   define SDC_CLIENT_AVAILABLE (1U)
#  endif

#  ifndef SDC_CEG_RELEASED
#   define SDC_CEG_RELEASED (0U)
#  endif

#  ifndef SDC_CEG_REQUESTED
#   define SDC_CEG_REQUESTED (1U)
#  endif

#  ifndef SDC_CEG_DOWN
#   define SDC_CEG_DOWN (0U)
#  endif

#  ifndef SDC_CEG_AVAILABLE
#   define SDC_CEG_AVAILABLE (1U)
#  endif

#  ifndef SDC_EH_RELEASED
#   define SDC_EH_RELEASED (0U)
#  endif

#  ifndef SDC_EH_REQUESTED
#   define SDC_EH_REQUESTED (1U)
#  endif

#  ifndef SDC_SERVER_DOWN
#   define SDC_SERVER_DOWN (0U)
#  endif

#  ifndef SDC_SERVER_AVAILABE
#   define SDC_SERVER_AVAILABE (1U)
#  endif

# endif /* RTE_CORE */


/**********************************************************************************************************************
 * Definitions for Mode Management
 *********************************************************************************************************************/
# ifndef RTE_MODETYPE_ESH_Mode
#  define RTE_MODETYPE_ESH_Mode
typedef BswM_ESH_Mode Rte_ModeType_ESH_Mode;
# endif
# ifndef RTE_MODETYPE_ESH_RunRequest
#  define RTE_MODETYPE_ESH_RunRequest
typedef BswM_ESH_RunRequest Rte_ModeType_ESH_RunRequest;
# endif
# ifndef RTE_MODETYPE_SDC_SdClientServiceRequest
#  define RTE_MODETYPE_SDC_SdClientServiceRequest
typedef BswM_SDC_SdClientServiceRequest Rte_ModeType_SDC_SdClientServiceRequest;
# endif
# ifndef RTE_MODETYPE_SDC_SdClientServiceState
#  define RTE_MODETYPE_SDC_SdClientServiceState
typedef BswM_SDC_SdClientServiceState Rte_ModeType_SDC_SdClientServiceState;
# endif
# ifndef RTE_MODETYPE_SDC_SdConsumedEventGroupRequest
#  define RTE_MODETYPE_SDC_SdConsumedEventGroupRequest
typedef BswM_SDC_SdConsumedEventGroupRequest Rte_ModeType_SDC_SdConsumedEventGroupRequest;
# endif
# ifndef RTE_MODETYPE_SDC_SdConsumedEventGroupState
#  define RTE_MODETYPE_SDC_SdConsumedEventGroupState
typedef BswM_SDC_SdConsumedEventGroupState Rte_ModeType_SDC_SdConsumedEventGroupState;
# endif
# ifndef RTE_MODETYPE_SDC_SdEventHandlerState
#  define RTE_MODETYPE_SDC_SdEventHandlerState
typedef BswM_SDC_SdEventHandlerState Rte_ModeType_SDC_SdEventHandlerState;
# endif
# ifndef RTE_MODETYPE_SDC_SdServerServiceRequest
#  define RTE_MODETYPE_SDC_SdServerServiceRequest
typedef BswM_SDC_SdServerServiceRequest Rte_ModeType_SDC_SdServerServiceRequest;
# endif

# define RTE_MODE_BswM_ESH_Mode_STARTUP (0U)
# ifndef RTE_MODE_ESH_Mode_STARTUP
#  define RTE_MODE_ESH_Mode_STARTUP (0U)
# endif
# define RTE_MODE_BswM_ESH_Mode_RUN (1U)
# ifndef RTE_MODE_ESH_Mode_RUN
#  define RTE_MODE_ESH_Mode_RUN (1U)
# endif
# define RTE_MODE_BswM_ESH_Mode_POSTRUN (2U)
# ifndef RTE_MODE_ESH_Mode_POSTRUN
#  define RTE_MODE_ESH_Mode_POSTRUN (2U)
# endif
# define RTE_MODE_BswM_ESH_Mode_WAKEUP (3U)
# ifndef RTE_MODE_ESH_Mode_WAKEUP
#  define RTE_MODE_ESH_Mode_WAKEUP (3U)
# endif
# define RTE_MODE_BswM_ESH_Mode_SHUTDOWN (4U)
# ifndef RTE_MODE_ESH_Mode_SHUTDOWN
#  define RTE_MODE_ESH_Mode_SHUTDOWN (4U)
# endif
# define RTE_TRANSITION_BswM_ESH_Mode (5U)
# ifndef RTE_TRANSITION_ESH_Mode
#  define RTE_TRANSITION_ESH_Mode (5U)
# endif

# define RTE_MODE_BswM_ESH_RunRequest_RELEASED (0U)
# ifndef RTE_MODE_ESH_RunRequest_RELEASED
#  define RTE_MODE_ESH_RunRequest_RELEASED (0U)
# endif
# define RTE_MODE_BswM_ESH_RunRequest_REQUESTED (1U)
# ifndef RTE_MODE_ESH_RunRequest_REQUESTED
#  define RTE_MODE_ESH_RunRequest_REQUESTED (1U)
# endif
# define RTE_TRANSITION_BswM_ESH_RunRequest (2U)
# ifndef RTE_TRANSITION_ESH_RunRequest
#  define RTE_TRANSITION_ESH_RunRequest (2U)
# endif

# define RTE_MODE_BswM_SDC_SdClientServiceRequest_SDC_CLIENT_RELEASED (0U)
# ifndef RTE_MODE_SDC_SdClientServiceRequest_SDC_CLIENT_RELEASED
#  define RTE_MODE_SDC_SdClientServiceRequest_SDC_CLIENT_RELEASED (0U)
# endif
# define RTE_MODE_BswM_SDC_SdClientServiceRequest_SDC_CLIENT_REQUESTED (1U)
# ifndef RTE_MODE_SDC_SdClientServiceRequest_SDC_CLIENT_REQUESTED
#  define RTE_MODE_SDC_SdClientServiceRequest_SDC_CLIENT_REQUESTED (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdClientServiceRequest (2U)
# ifndef RTE_TRANSITION_SDC_SdClientServiceRequest
#  define RTE_TRANSITION_SDC_SdClientServiceRequest (2U)
# endif

# define RTE_MODE_BswM_SDC_SdClientServiceState_SDC_CLIENT_DOWN (0U)
# ifndef RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN
#  define RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_DOWN (0U)
# endif
# define RTE_MODE_BswM_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE (1U)
# ifndef RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE
#  define RTE_MODE_SDC_SdClientServiceState_SDC_CLIENT_AVAILABLE (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdClientServiceState (2U)
# ifndef RTE_TRANSITION_SDC_SdClientServiceState
#  define RTE_TRANSITION_SDC_SdClientServiceState (2U)
# endif

# define RTE_MODE_BswM_SDC_SdConsumedEventGroupRequest_SDC_CEG_RELEASED (0U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupRequest_SDC_CEG_RELEASED
#  define RTE_MODE_SDC_SdConsumedEventGroupRequest_SDC_CEG_RELEASED (0U)
# endif
# define RTE_MODE_BswM_SDC_SdConsumedEventGroupRequest_SDC_CEG_REQUESTED (1U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupRequest_SDC_CEG_REQUESTED
#  define RTE_MODE_SDC_SdConsumedEventGroupRequest_SDC_CEG_REQUESTED (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdConsumedEventGroupRequest (2U)
# ifndef RTE_TRANSITION_SDC_SdConsumedEventGroupRequest
#  define RTE_TRANSITION_SDC_SdConsumedEventGroupRequest (2U)
# endif

# define RTE_MODE_BswM_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN (0U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN
#  define RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_DOWN (0U)
# endif
# define RTE_MODE_BswM_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE (1U)
# ifndef RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE
#  define RTE_MODE_SDC_SdConsumedEventGroupState_SDC_CEG_AVAILABLE (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdConsumedEventGroupState (2U)
# ifndef RTE_TRANSITION_SDC_SdConsumedEventGroupState
#  define RTE_TRANSITION_SDC_SdConsumedEventGroupState (2U)
# endif

# define RTE_MODE_BswM_SDC_SdEventHandlerState_SDC_EH_RELEASED (0U)
# ifndef RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED
#  define RTE_MODE_SDC_SdEventHandlerState_SDC_EH_RELEASED (0U)
# endif
# define RTE_MODE_BswM_SDC_SdEventHandlerState_SDC_EH_REQUESTED (1U)
# ifndef RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED
#  define RTE_MODE_SDC_SdEventHandlerState_SDC_EH_REQUESTED (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdEventHandlerState (2U)
# ifndef RTE_TRANSITION_SDC_SdEventHandlerState
#  define RTE_TRANSITION_SDC_SdEventHandlerState (2U)
# endif

# define RTE_MODE_BswM_SDC_SdServerServiceRequest_SDC_SERVER_DOWN (0U)
# ifndef RTE_MODE_SDC_SdServerServiceRequest_SDC_SERVER_DOWN
#  define RTE_MODE_SDC_SdServerServiceRequest_SDC_SERVER_DOWN (0U)
# endif
# define RTE_MODE_BswM_SDC_SdServerServiceRequest_SDC_SERVER_AVAILABE (1U)
# ifndef RTE_MODE_SDC_SdServerServiceRequest_SDC_SERVER_AVAILABE
#  define RTE_MODE_SDC_SdServerServiceRequest_SDC_SERVER_AVAILABE (1U)
# endif
# define RTE_TRANSITION_BswM_SDC_SdServerServiceRequest (2U)
# ifndef RTE_TRANSITION_SDC_SdServerServiceRequest
#  define RTE_TRANSITION_SDC_SdServerServiceRequest (2U)
# endif

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_BSWM_TYPE_H */
