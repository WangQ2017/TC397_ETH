/**********************************************************************************************************************
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
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  StbM_Types.h
 *        \brief  Vector AUTOSAR StbM Types header file
 *
 *      \details  This header file contains the type definitions of the Vector AUTOSAR module StbM.

 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (STBM_TYPES_H)
# define STBM_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Std_Types.h"
# include "Rte_Type.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define STBM_NO_LOCALTIME                       (0U)
# define STBM_OS_LOCALTIME                       (1U)
# define STBM_GPT_LOCALTIME                      (2U)

# define STBM_NO_LOCALTIME_ID                    (0U)
# define STBM_NO_GPT_CHANNEL_IDX                 (0U)
# define STBM_NO_LOCALTIME_NSPERTICK             (0U)
# define STBM_NO_LOCALTIME_MAXVALUE              (0U)

# define STBM_NO_TIMEDOMAINID                    (255U)
# define STBM_NO_TIMEBASEID                      (65535U)

# define StbM_Timeout_BflMask                    (0x01U)
# define StbM_TimeLeapFuture_BflMask             (0x10U)
# define StbM_TimeLeapPast_BflMask               (0x20U)
# define StbM_Sync_To_Gateway_BflMask            (0x04U)
# define StbM_Global_Time_Base_BflMask           (0x08U)

/* Status event masks */
# define STBM_EV_GLOBAL_TIME_BASE_MASK           (0x01U) /* Bit 0 */
# define STBM_EV_TIMEOUT_OCCURRED_MASK           (0x02U) /* Bit 1 */
# define STBM_EV_TIMEOUT_REMOVED_MASK            (0x04U) /* Bit 2 */
# define STBM_EV_TIMELEAP_FUTURE_MASK            (0x08U) /* Bit 3 */
# define STBM_EV_TIMELEAP_FUTURE_REMOVED_MASK    (0x10U) /* Bit 4 */
# define STBM_EV_TIMELEAP_PAST_MASK              (0x20U) /* Bit 5 */
# define STBM_EV_TIMELEAP_PAST_REMOVED_MASK      (0x40U) /* Bit 6 */
# define STBM_EV_SYNC_TO_SUBDOMAIN_MASK          (0x80U) /* Bit 7 */
# define STBM_EV_SYNC_TO_GLOBAL_MASTER_MASK     (0x100U) /* Bit 8 */
# define STBM_EV_RESYNC_MASK                    (0x200U) /* Bit 9 */
# define STBM_EV_RATECORRECTION_MASK            (0x400U) /* Bit 10 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef struct
{
  uint32 pathDelay;
} StbM_MeasurementType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* STBM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: StbM_Types.h
 *********************************************************************************************************************/
