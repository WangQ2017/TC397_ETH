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
 *             File:  Rte_StbM_Type.h
 *           Config:  TC397_BSW.dpa
 *      ECU-Project:  TC397_BSW
 *
 *        Generator:  MICROSAR RTE Generator Version 4.23.0
 *                    RTE Core Version 1.23.0
 *          License:  CBD2000642
 *
 *      Description:  Application types header file for SW-C <StbM>
 *********************************************************************************************************************/

/* double include prevention */
#ifndef RTE_STBM_TYPE_H
# define RTE_STBM_TYPE_H

# ifdef __cplusplus
extern "C"
{
# endif /* __cplusplus */

# include "Rte_Type.h"

# ifndef RTE_CORE

/**********************************************************************************************************************
 * Range, Invalidation, Enumeration and Bit Field Definitions
 *********************************************************************************************************************/

#  ifndef STBM_SYSTEM_WIDE_MASTER_DISABLED
#   define STBM_SYSTEM_WIDE_MASTER_DISABLED (0U)
#  endif

#  ifndef STBM_SYSTEM_WIDE_MASTER_ENABLED
#   define STBM_SYSTEM_WIDE_MASTER_ENABLED (1U)
#  endif

#  ifndef EV_GLOBAL_TIME__FALSE
#   define EV_GLOBAL_TIME__FALSE (0U)
#  endif

#  ifndef EV_GLOBAL_TIME_BflMask
#   define EV_GLOBAL_TIME_BflMask 1U
#  endif

#  ifndef EV_GLOBAL_TIME_BflPn
#   define EV_GLOBAL_TIME_BflPn 0U
#  endif

#  ifndef EV_GLOBAL_TIME_BflLn
#   define EV_GLOBAL_TIME_BflLn 1U
#  endif

#  ifndef EV_GLOBAL_TIME
#   define EV_GLOBAL_TIME (1U)
#  endif

#  ifndef EV_TIMEOUT_OCCURRED__FALSE
#   define EV_TIMEOUT_OCCURRED__FALSE (0U)
#  endif

#  ifndef EV_TIMEOUT_OCCURRED_BflMask
#   define EV_TIMEOUT_OCCURRED_BflMask 2U
#  endif

#  ifndef EV_TIMEOUT_OCCURRED_BflPn
#   define EV_TIMEOUT_OCCURRED_BflPn 1U
#  endif

#  ifndef EV_TIMEOUT_OCCURRED_BflLn
#   define EV_TIMEOUT_OCCURRED_BflLn 1U
#  endif

#  ifndef EV_TIMEOUT_OCCURRED
#   define EV_TIMEOUT_OCCURRED (2U)
#  endif

#  ifndef EV_TIMEOUT_REMOVED__FALSE
#   define EV_TIMEOUT_REMOVED__FALSE (0U)
#  endif

#  ifndef EV_TIMEOUT_REMOVED_BflMask
#   define EV_TIMEOUT_REMOVED_BflMask 4U
#  endif

#  ifndef EV_TIMEOUT_REMOVED_BflPn
#   define EV_TIMEOUT_REMOVED_BflPn 2U
#  endif

#  ifndef EV_TIMEOUT_REMOVED_BflLn
#   define EV_TIMEOUT_REMOVED_BflLn 1U
#  endif

#  ifndef EV_TIMEOUT_REMOVED
#   define EV_TIMEOUT_REMOVED (4U)
#  endif

#  ifndef EV_TIMELEAP_FUTURE__FALSE
#   define EV_TIMELEAP_FUTURE__FALSE (0U)
#  endif

#  ifndef EV_TIMELEAP_FUTURE_BflMask
#   define EV_TIMELEAP_FUTURE_BflMask 8U
#  endif

#  ifndef EV_TIMELEAP_FUTURE_BflPn
#   define EV_TIMELEAP_FUTURE_BflPn 3U
#  endif

#  ifndef EV_TIMELEAP_FUTURE_BflLn
#   define EV_TIMELEAP_FUTURE_BflLn 1U
#  endif

#  ifndef EV_TIMELEAP_FUTURE
#   define EV_TIMELEAP_FUTURE (8U)
#  endif

#  ifndef EV_TIMELEAP_FUTURE_REMOVED__FALSE
#   define EV_TIMELEAP_FUTURE_REMOVED__FALSE (0U)
#  endif

#  ifndef EV_TIMELEAP_FUTURE_REMOVED_BflMask
#   define EV_TIMELEAP_FUTURE_REMOVED_BflMask 16U
#  endif

#  ifndef EV_TIMELEAP_FUTURE_REMOVED_BflPn
#   define EV_TIMELEAP_FUTURE_REMOVED_BflPn 4U
#  endif

#  ifndef EV_TIMELEAP_FUTURE_REMOVED_BflLn
#   define EV_TIMELEAP_FUTURE_REMOVED_BflLn 1U
#  endif

#  ifndef EV_TIMELEAP_FUTURE_REMOVED
#   define EV_TIMELEAP_FUTURE_REMOVED (16U)
#  endif

#  ifndef EV_TIMELEAP_PAST__FALSE
#   define EV_TIMELEAP_PAST__FALSE (0U)
#  endif

#  ifndef EV_TIMELEAP_PAST_BflMask
#   define EV_TIMELEAP_PAST_BflMask 32U
#  endif

#  ifndef EV_TIMELEAP_PAST_BflPn
#   define EV_TIMELEAP_PAST_BflPn 5U
#  endif

#  ifndef EV_TIMELEAP_PAST_BflLn
#   define EV_TIMELEAP_PAST_BflLn 1U
#  endif

#  ifndef EV_TIMELEAP_PAST
#   define EV_TIMELEAP_PAST (32U)
#  endif

#  ifndef EV_TIMELEAP_PAST_REMOVED__FALSE
#   define EV_TIMELEAP_PAST_REMOVED__FALSE (0U)
#  endif

#  ifndef EV_TIMELEAP_PAST_REMOVED_BflMask
#   define EV_TIMELEAP_PAST_REMOVED_BflMask 64U
#  endif

#  ifndef EV_TIMELEAP_PAST_REMOVED_BflPn
#   define EV_TIMELEAP_PAST_REMOVED_BflPn 6U
#  endif

#  ifndef EV_TIMELEAP_PAST_REMOVED_BflLn
#   define EV_TIMELEAP_PAST_REMOVED_BflLn 1U
#  endif

#  ifndef EV_TIMELEAP_PAST_REMOVED
#   define EV_TIMELEAP_PAST_REMOVED (64U)
#  endif

#  ifndef EV_SYNC_TO_SUBDOMAIN__FALSE
#   define EV_SYNC_TO_SUBDOMAIN__FALSE (0U)
#  endif

#  ifndef EV_SYNC_TO_SUBDOMAIN_BflMask
#   define EV_SYNC_TO_SUBDOMAIN_BflMask 128U
#  endif

#  ifndef EV_SYNC_TO_SUBDOMAIN_BflPn
#   define EV_SYNC_TO_SUBDOMAIN_BflPn 7U
#  endif

#  ifndef EV_SYNC_TO_SUBDOMAIN_BflLn
#   define EV_SYNC_TO_SUBDOMAIN_BflLn 1U
#  endif

#  ifndef EV_SYNC_TO_SUBDOMAIN
#   define EV_SYNC_TO_SUBDOMAIN (128U)
#  endif

#  ifndef EV_SYNC_TO_GLOBAL_MASTER__FALSE
#   define EV_SYNC_TO_GLOBAL_MASTER__FALSE (0U)
#  endif

#  ifndef EV_SYNC_TO_GLOBAL_MASTER_BflMask
#   define EV_SYNC_TO_GLOBAL_MASTER_BflMask 256U
#  endif

#  ifndef EV_SYNC_TO_GLOBAL_MASTER_BflPn
#   define EV_SYNC_TO_GLOBAL_MASTER_BflPn 8U
#  endif

#  ifndef EV_SYNC_TO_GLOBAL_MASTER_BflLn
#   define EV_SYNC_TO_GLOBAL_MASTER_BflLn 1U
#  endif

#  ifndef EV_SYNC_TO_GLOBAL_MASTER
#   define EV_SYNC_TO_GLOBAL_MASTER (256U)
#  endif

#  ifndef EV_RESYNC__FALSE
#   define EV_RESYNC__FALSE (0U)
#  endif

#  ifndef EV_RESYNC_BflMask
#   define EV_RESYNC_BflMask 512U
#  endif

#  ifndef EV_RESYNC_BflPn
#   define EV_RESYNC_BflPn 9U
#  endif

#  ifndef EV_RESYNC_BflLn
#   define EV_RESYNC_BflLn 1U
#  endif

#  ifndef EV_RESYNC
#   define EV_RESYNC (512U)
#  endif

#  ifndef EV_RATECORRECTION__FALSE
#   define EV_RATECORRECTION__FALSE (0U)
#  endif

#  ifndef EV_RATECORRECTION_BflMask
#   define EV_RATECORRECTION_BflMask 1024U
#  endif

#  ifndef EV_RATECORRECTION_BflPn
#   define EV_RATECORRECTION_BflPn 10U
#  endif

#  ifndef EV_RATECORRECTION_BflLn
#   define EV_RATECORRECTION_BflLn 1U
#  endif

#  ifndef EV_RATECORRECTION
#   define EV_RATECORRECTION (1024U)
#  endif

#  ifndef TIMEOUT__FALSE
#   define TIMEOUT__FALSE (0U)
#  endif

#  ifndef TIMEOUT_BflMask
#   define TIMEOUT_BflMask 1U
#  endif

#  ifndef TIMEOUT_BflPn
#   define TIMEOUT_BflPn 0U
#  endif

#  ifndef TIMEOUT_BflLn
#   define TIMEOUT_BflLn 1U
#  endif

#  ifndef TIMEOUT
#   define TIMEOUT (1U)
#  endif

#  ifndef Reserved__FALSE
#   define Reserved__FALSE (0U)
#  endif

#  ifndef Reserved_BflMask
#   define Reserved_BflMask 2U
#  endif

#  ifndef Reserved_BflPn
#   define Reserved_BflPn 1U
#  endif

#  ifndef Reserved_BflLn
#   define Reserved_BflLn 1U
#  endif

#  ifndef Reserved
#   define Reserved (2U)
#  endif

#  ifndef SYNC_TO_GATEWAY__FALSE
#   define SYNC_TO_GATEWAY__FALSE (0U)
#  endif

#  ifndef SYNC_TO_GATEWAY_BflMask
#   define SYNC_TO_GATEWAY_BflMask 4U
#  endif

#  ifndef SYNC_TO_GATEWAY_BflPn
#   define SYNC_TO_GATEWAY_BflPn 2U
#  endif

#  ifndef SYNC_TO_GATEWAY_BflLn
#   define SYNC_TO_GATEWAY_BflLn 1U
#  endif

#  ifndef SYNC_TO_GATEWAY
#   define SYNC_TO_GATEWAY (4U)
#  endif

#  ifndef GLOBAL_TIME_BASE__FALSE
#   define GLOBAL_TIME_BASE__FALSE (0U)
#  endif

#  ifndef GLOBAL_TIME_BASE_BflMask
#   define GLOBAL_TIME_BASE_BflMask 8U
#  endif

#  ifndef GLOBAL_TIME_BASE_BflPn
#   define GLOBAL_TIME_BASE_BflPn 3U
#  endif

#  ifndef GLOBAL_TIME_BASE_BflLn
#   define GLOBAL_TIME_BASE_BflLn 1U
#  endif

#  ifndef GLOBAL_TIME_BASE
#   define GLOBAL_TIME_BASE (8U)
#  endif

#  ifndef TIMELEAP_FUTURE__FALSE
#   define TIMELEAP_FUTURE__FALSE (0U)
#  endif

#  ifndef TIMELEAP_FUTURE_BflMask
#   define TIMELEAP_FUTURE_BflMask 16U
#  endif

#  ifndef TIMELEAP_FUTURE_BflPn
#   define TIMELEAP_FUTURE_BflPn 4U
#  endif

#  ifndef TIMELEAP_FUTURE_BflLn
#   define TIMELEAP_FUTURE_BflLn 1U
#  endif

#  ifndef TIMELEAP_FUTURE
#   define TIMELEAP_FUTURE (16U)
#  endif

#  ifndef TIMELEAP_PAST__FALSE
#   define TIMELEAP_PAST__FALSE (0U)
#  endif

#  ifndef TIMELEAP_PAST_BflMask
#   define TIMELEAP_PAST_BflMask 32U
#  endif

#  ifndef TIMELEAP_PAST_BflPn
#   define TIMELEAP_PAST_BflPn 5U
#  endif

#  ifndef TIMELEAP_PAST_BflLn
#   define TIMELEAP_PAST_BflLn 1U
#  endif

#  ifndef TIMELEAP_PAST
#   define TIMELEAP_PAST (32U)
#  endif

# endif /* RTE_CORE */

# ifdef __cplusplus
} /* extern "C" */
# endif /* __cplusplus */

#endif /* RTE_STBM_TYPE_H */
