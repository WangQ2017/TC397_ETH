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
/*!        \file  Eth_30_Tc3xx_LL_Int.h
 *        \brief  Lower layer private header file
 *
 *      \details  Private data of lower layer part of component.
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
#if !defined (ETH_30_TC3XX_LL_INT_H)
# define ETH_30_TC3XX_LL_INT_H

# include "Eth_30_Tc3xx_HwAccess_Int.h"
# include "SchM_Eth_30_Tc3xx.h"

# if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
#  include "Dem.h"
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/*------- ETH Frame offsets as byte index offsets ------------------------- */
/*! Reception frame: Byte index offset of destination MAC-Address */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST                       (2u)
/*! Reception frame: Byte index offset of source MAC-Address */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC                       (8u)
/*! Reception frame: Byte index offset of Ethertype */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE                      (14u)
/*! Reception frame: Byte index offset of Payload */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DATA                      (16u)
/*! Transmission frame: Byte index offset destination MAC-Address */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST                       (0u)
/*! Transmission frame: Byte index offset of source MAC-Address */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC                       (6u)
/*! Transmission frame: Byte index offset of Ethertype */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE                      (12u)
/*! Transmission frame: Byte index offset of Payload */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DATA                      (14u)
/*! Definition of the buffer space in Bytes occupied by the FCS */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE            (0u)
/*! Definition of the length of destination and source MAC address */
# define ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE       (12u)

# define ETH_30_TC3XX_BEGIN_CRITICAL_SECTION_XXX()                    \
                                                                      SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_XXX()
# define ETH_30_TC3XX_END_CRITICAL_SECTION_XXX()                      \
                                                                      SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_XXX()

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ISR related */
# define ETH_30_TC3XX_TXQ0                                            (0x0u)
# define ETH_30_TC3XX_RXQ0                                            (0x0u)
# define ETH_30_TC3XX_TXQ1                                            (0x1u)
# define ETH_30_TC3XX_RXQ1                                            (0x1u)
# define ETH_30_TC3XX_TXQ2                                            (0x2u)
# define ETH_30_TC3XX_RXQ2                                            (0x2u)
# define ETH_30_TC3XX_TXQ3                                            (0x3u)
# define ETH_30_TC3XX_RXQ3                                            (0x3u)

# define ETH_30_TC3XX_NSEC_PER_SEC                                    (1000000000ul)
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Appl_UnlockEndinit()
 *********************************************************************************************************************/
/*! \brief       Appl_UnlockEndinit
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_APPL_CODE) Appl_UnlockEndinit(void);

/**********************************************************************************************************************
 *  Appl_LockEndinit()
 *********************************************************************************************************************/
/*! \brief       Appl_LockEndinit
 *  \details     -
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(void, ETH_30_TC3XX_APPL_CODE) Appl_LockEndinit(void);

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Int.h
 *********************************************************************************************************************/
