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
/*!        \file  Eth_30_Tc3xx_Int.h
 *        \brief  Component private header file
 *
 *      \details  Internal global data declaration and macro defines
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_INT_H)
# define ETH_30_TC3XX_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_LL_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# define ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING                        (0xFFu)

# define ETH_30_TC3XX_ISR_NO_OS_SUPPORT                                (0u)
# define ETH_30_TC3XX_ISR_CATEGORY_1                                   (1u)
# define ETH_30_TC3XX_ISR_CATEGORY_2                                   (2u)

/* Frame attributes */

# define ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE                        (2u)
# define ETH_30_TC3XX_HDR_LEN_BYTE                                     (14u)
# define ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE                           (12u)
# define ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE                           (60u)
# define ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE                         (ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE - \
                                                                      ETH_30_TC3XX_DEST_SRC_MACS_LEN_BYTE - \
                                                                      ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE)
/**********************************************************************************************************************
 *  CHECK OF LT60B OFFSET DEFINES
 *********************************************************************************************************************/
# if(ETH_30_TC3XX_HDR_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_HDR_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DATA > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DATA is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DATA > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DATA is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE is too high!"
# endif
# if(ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE > ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE)
#  error "The value defined for ETH_30_TC3XX_MIN_ETH_PAYLOAD_LEN_BYTE is too high!"
# endif
/**********************************************************************************************************************
 *  END OF CHECK OF LT60B OFFSET DEFINES CHECK
 *********************************************************************************************************************/
/* Ethertype indices and shifts */
# define ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX                           (0u)
# define ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX                           (1u)
# define ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_RSHIFT                        (8u)
# define ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_LSHIFT                        (8u)

/* Tx Confirmation */
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING                (0u)
# define ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING                    (1u)

/* Descriptor status */
# define ETH_30_TC3XX_DESCRIPTOR_NOT_READY                             (0u)
# define ETH_30_TC3XX_DESCRIPTOR_READY                                 (1u)
# define ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED                           (2u)

# define ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED               (ETH_30_TC3XX_UINT16_MAX)

# define ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED                        (0u)
# define ETH_30_TC3XX_TIMESYNC_TS_REQUESTED                            (1u)


# define ETH_30_TC3XX_MAX_CFGS_TOTAL                                   (1u)

# define ETH_30_TC3XX_MAX_MII_REG_TOTAL                                (32u)

# define ETH_30_TC3XX_MULTICAST_BUCKET_COUNTERS                        (64u)
# define ETH_30_TC3XX_BUCKET_MAX_CNT                                   (0xFFu)

# define ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS                    (-1)

# define ETH_30_TC3XX_VLAN_ETHER_TYPE                                  (0x8100u)
# define ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET                       (2u)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_MASK                               (0xE0u)
# define ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT                              (5u)

# define ETH_30_TC3XX_VLAN_ID_BYTE_MASK                                (0x0FFFu)

# define ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE                 (0xFFFFFFFFu)

# define ETH_30_TC3XX_INVALID_FIFO_IDX                                 (0xFFu)

# ifndef ETH_30_TC3XX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LOCAL_INLINE                                    LOCAL_INLINE
# endif /* ETH_30_TC3XX_LOCAL_INLINE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define Eth_30_Tc3xx_TransformToLocalCtrlIdx(GlobalCtrlIdx)           (uint8)((GlobalCtrlIdx) - ETH_30_TC3XX_CTRL_IDX_OFFSET)
# define Eth_30_Tc3xx_TransformToGlobalCtrlIdx(LocalCtrlIdx)           (uint8)((LocalCtrlIdx) + ETH_30_TC3XX_CTRL_IDX_OFFSET)

/* PRQA S 3453, 0342 2 */ /* MD_MSR_19.7, MD_MSR_19.13_0342 */
# define Eth_30_Tc3xx_EnterExclusiveArea(Area)                         SchM_Enter_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area()
# define Eth_30_Tc3xx_ExitExclusiveArea(Area)                          SchM_Exit_Eth_30_Tc3xx_ETH_30_TC3XX_EXCLUSIVE_AREA_##Area()

/* Diagnostic Event Manager */
# if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx)   \
                                                                      (Dem_ReportErrorStatus(Eth_30_Tc3xx_GetDemEAccessEventIdOfEthCtrl(CtrlIdx), DEM_EVENT_STATUS_FAILED))
# else
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(CtrlIdx)
# endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
# define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
extern VAR(Eth_StateType, ETH_30_TC3XX_VAR_ZERO_INIT) Eth_30_Tc3xx_ModuleInitialized;
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

# define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Int.h
 *********************************************************************************************************************/
