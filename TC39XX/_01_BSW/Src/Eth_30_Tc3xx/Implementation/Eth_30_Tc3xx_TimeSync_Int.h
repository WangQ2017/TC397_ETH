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
/*!        \file  Eth_30_Tc3xx_TimeSync_Int.h
 *        \brief  Private timer sub-module header of the Ethernet controller driver
 *
 *      \details  Provides access to the hardware timer related API of the Ethernet controller driver.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx.h
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_TIME_SYNC_INT_H)
# define ETH_30_TC3XX_TIME_SYNC_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_TimeSync.h"
# include "Eth_30_Tc3xx_LL_TimeSync.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* Timer constants */
# define ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC                           (1000000000ul)

/* IEEE1588 time stamp */
/*! Seconds that can be represented by IEEE1588 time stamp */
# define ETH_30_TC3XX_TIME_IEEE1588_MAX_SECONDS                        (0x0000FFFFFFFFFFFFull)
/*! Nanoseconds that can be represented by IEEE1588 time stamp */
# define ETH_30_TC3XX_TIME_IEEE1588_MAX_NANOSECONDS                    (ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC)
/*! ETH Min/Max values for Eth_TimestampType and Eth_TimediffType */
/* 32 bit seconds */
# define ETH_30_TC3XX_TIMESTAMP_MAX_SECONDS                            (0xFFFFFFFFul)
# define ETH_30_TC3XX_TIMESTAMP_SECONDS_64BIT_MASK                     (0x00000000FFFFFFFFull)
/* 16 bit seconds hi */
# define ETH_30_TC3XX_TIMESTAMP_MAX_SECONDS_HI                         (0xFFFFu)
# define ETH_30_TC3XX_TIMESTAMP_SECONDS_HI_64BIT_MASK                  (0x0000FFFF00000000ull)
# define ETH_30_TC3XX_TIMESTAMP_SECONDS_HI_64BIT_SHIFT                 (32u)
/* 10^9 nanoseconds per second */
# define ETH_30_TC3XX_TIMESTAMP_MAX_NANOSECONDS                        (ETH_30_TC3XX_TIME_SYNC_NSEC_PER_SEC)
/* 63 bit max timediff in nanoseconds */
# define ETH_30_TC3XX_TIMEDIFF_MAX_NANOSECONDS                         (0x7FFFFFFFFFFFFFFFull)
/* Seconds portion of a timediff */
# define ETH_30_TC3XX_TIMEDIFF_MAX_SECONDS                             \
                                                                      (ETH_30_TC3XX_TIMEDIFF_MAX_NANOSECONDS / ETH_30_TC3XX_TIMESTAMP_MAX_NANOSECONDS)

# if !defined(ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE                          LOCAL_INLINE
# endif /* ETH_30_TC3XX_TIME_SYNC_LOCAL_INLINE */

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif /* ETH_30_TC3XX_TIME_SYNC_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync.h
 *********************************************************************************************************************/
