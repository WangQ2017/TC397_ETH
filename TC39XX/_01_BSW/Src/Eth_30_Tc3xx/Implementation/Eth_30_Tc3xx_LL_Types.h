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
/*!        \file  Eth_30_Tc3xx_LL_Types.h
 *        \brief  Public header file of Ethernet driver for data type access
 *
 *      \details  Contains data type declaration that shall be accessible in a public manner.
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the version history in Eth_30_Tc3xx_LL.h
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the newest version in Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/

#if !defined (ETH_30_TC3XX_LL_TYPES_H)
# define ETH_30_TC3XX_LL_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "Platform_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*! Amount of words (32 bit) defining one reception descriptor */
# define ETH_30_TC3XX_LL_RX_DESCR_WORD_NUM                            (8u)
/*! Amount of words (32 bit) defining one transmission descriptor */
# define ETH_30_TC3XX_LL_TX_DESCR_WORD_NUM                            (4u)
/*! Defines to access the words (32 bit) of a descriptor */
# define ETH_30_TC3XX_DES0_IDX                                        (0u)
# define ETH_30_TC3XX_DES1_IDX                                        (1u)
# define ETH_30_TC3XX_DES2_IDX                                        (2u)
# define ETH_30_TC3XX_DES3_IDX                                        (3u)
# define ETH_30_TC3XX_CNTXT_DES0_IDX                                  (4u)
# define ETH_30_TC3XX_CNTXT_DES1_IDX                                  (5u)
# define ETH_30_TC3XX_CNTXT_DES2_IDX                                  (6u)
# define ETH_30_TC3XX_CNTXT_DES3_IDX                                  (7u)

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef volatile uint32 Eth_30_Tc3xx_DescriptorWordType;

/*! Structure of one descriptor of the reception descriptor ring */
typedef struct
{
  Eth_30_Tc3xx_DescriptorWordType RxDescrWord[ETH_30_TC3XX_LL_RX_DESCR_WORD_NUM];
} Eth_30_Tc3xx_RxDescriptorType;

/*! Structure of one descriptor of the transmission descriptor ring */
typedef struct
{
  Eth_30_Tc3xx_DescriptorWordType TxDescrWord[ETH_30_TC3XX_LL_TX_DESCR_WORD_NUM];
} Eth_30_Tc3xx_TxDescriptorType;

#endif /* ETH_30_TC3XX_LL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Types.h
 *********************************************************************************************************************/
