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
/*!        \file  Eth_30_Tc3xx_LL_Regs.h
 *        \brief  Register header of the TC3xx Ethernet controller driver
 *
 *      \details  Defines macros and data types representing and abstracting the register layout of the Core
 *                Ethernet controller.
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

#if !defined (ETH_30_TC3XX_LL_REGS_H)
# define ETH_30_TC3XX_LL_REGS_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Platform_Types.h"
# include "Eth_30_Tc3xx_GenTypes.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * 
 */

/* register address offsets */
# define ETH_30_TC3XX_REG_OFFS_MAC_CFG                                (0x0000u)
# define ETH_30_TC3XX_REG_OFFS_MAC_EXT_CFG                            (0x0004u)
# define ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER                      (0x0008u)

# define ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_CTRL                      (0x0050u)
# define ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_DATA                      (0x0054u)

# define ETH_30_TC3XX_REG_OFFS_MAC_Q0_TX_FLOW_CNTRL                   (0x0070u)

# define ETH_30_TC3XX_REG_OFFS_MAC_RX_FLOW_CTRL                       (0x0090u)

# define ETH_30_TC3XX_REG_OFFS_MAC_RXQ_CTRL0                          (0x00A0u)
# define ETH_30_TC3XX_REG_OFFS_MAC_RXQ_CTRL1                          (0x00A4u)
# define ETH_30_TC3XX_REG_OFFS_MAC_RXQ_CTRL2                          (0x00A8u)
# define ETH_30_TC3XX_REG_OFFS_MAC_INT_STATUS                         (0x00B0u)
# define ETH_30_TC3XX_REG_OFFS_MAC_INT_EN                             (0x00B4u)
# define ETH_30_TC3XX_REG_OFFS_MAC_RX_TX_STATUS                       (0x00B8u)

# define ETH_30_TC3XX_REG_OFFS_PMT_CTRL                               (0x00C0u)

# define ETH_30_TC3XX_REG_OFFS_MAC_DEBUG                              (0x0114u)

# define ETH_30_TC3XX_REG_OFFS_HW_FEATURE0                            (0x011Cu)
# define ETH_30_TC3XX_REG_OFFS_HW_FEATURE1                            (0x0120u)
# define ETH_30_TC3XX_REG_OFFS_HW_FEATURE2                            (0x0124u)

# define ETH_30_TC3XX_REG_OFFS_MDIO_ADDR                              (0x0200u)
# define ETH_30_TC3XX_REG_OFFS_MDIO_DATA                              (0x0204u)

# define ETH_30_TC3XX_REG_OFFS_ADDR0_HIGH                             (0x0300u)
# define ETH_30_TC3XX_REG_OFFS_ADDR0_LOW                              (0x0304u)
# define ETH_30_TC3XX_REG_OFFS_ADDR1_HIGH                             (0x0308u)
# define ETH_30_TC3XX_REG_OFFS_ADDR1_LOW                              (0x030Cu)

# define ETH_30_TC3XX_REG_OFFS_MMC_CNTRL                              (0x0700u)

# define ETH_30_TC3XX_REG_OFFS_MMC_TX_OCTETS_GB                       (0x0714u)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_UNICASTS_GB                     (0x073Cu)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTICASTS_GB                   (0x0740u)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_BROADCASTS_GB                   (0x0744u)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_SINGLE_COL                      (0x074Cu)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTI_COL                       (0x0750u)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_LATE_COL                        (0x0758u)
# define ETH_30_TC3XX_REG_OFFS_MMC_TX_EXC_COL                         (0x075Cu)

# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES                          (0x0780u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_OCTETS_GB                       (0x0784u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_BROADCAST_FRAMES                (0x078Cu)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_MULTICAST_FRAMES                (0x0790u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR                       (0x0794u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN                           (0x0798u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT                            (0x079Cu)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER                          (0x07A0u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G                     (0x07A4u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G                      (0x07A8u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64                       (0x07ACu)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64_TO_127                (0x07B0u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_128_TO_255               (0x07B4u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_256_TO_511               (0x07B8u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_512_TO_1023              (0x07BCu)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_1024_TO_MAX              (0x07C0u)
# define ETH_30_TC3XX_REG_OFFS_MMC_RX_UNICAST_G_FRAMES                (0x07C4u)

# define ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL                       (0x07D4u)

# define ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_CONTROL                  (0x0B00u)
# define ETH_30_TC3XX_REG_OFFS_MAC_SUB_SECOND_INCREMENT               (0x0B04u)
# define ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS                (0x0B08u)
# define ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS            (0x0B0Cu)
# define ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_SECONDS_UPDATE         (0x0B10u)
# define ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE     (0x0B14u)
# define ETH_30_TC3XX_REG_OFFS_MAC_TIMESTAMP_ADDEND                   (0x0B18u)
# define ETH_30_TC3XX_REG_OFFS_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS    (0x0B1Cu)

/* PPS related register offset */
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG                    (0x0B70u)
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_SECONDS           (0x0B80u)
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS0_TARGET_TIME_NANOSECONDS       (0x0B84u)
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS0_INTERVAL                      (0x0B88u)
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS0_WIDTH                         (0x0B8Cu)

# define ETH_30_TC3XX_REG_OFFS_MTL_OP_MODE                            (0x0C00u)

# define ETH_30_TC3XX_REG_OFFS_MTL_INT_ST                             (0x0C20u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ_DMA_MAP0                       (0x0C30u)

# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_OP_MODE                       (0x0D00u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_OP_MODE                       (0x0D40u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_OP_MODE                       (0x0D80u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_OP_MODE                       (0x0DC0u)

# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_DEBUG                         (0x0D08u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_DEBUG                         (0x0D48u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_DEBUG                         (0x0D88u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_DEBUG                         (0x0DC8u)

# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_QUANTUM_WEIGHT                (0x0D58u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_QUANTUM_WEIGHT                (0x0D98u)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_QUANTUM_WEIGHT                (0x0DD8u)

# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_OP_MODE                       (0x0D30u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_OP_MODE                       (0x0D70u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_OP_MODE                       (0x0DB0u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_OP_MODE                       (0x0DF0u)

# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_DEBUG                         (0x0D38u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_DEBUG                         (0x0D78u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_DEBUG                         (0x0DB8u)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_DEBUG                         (0x0DF8u)

# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_INTCTRL_STS                   (0x0D2Cu)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_INTCTRL_STS                   (0x0D6Cu)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_INTCTRL_STS                   (0x0DACu)
# define ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_INTCTRL_STS                   (0x0DECu)

# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_CTRL                          (0x0D3Cu)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_CTRL                          (0x0D7Cu)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_CTRL                          (0x0DBCu)
# define ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_CTRL                          (0x0DFCu)

# define ETH_30_TC3XX_REG_OFFS_DMA_MODE                               (0x1000u)
# define ETH_30_TC3XX_REG_OFFS_DMA_SYSBUS_MODE                        (0x1004u)
# define ETH_30_TC3XX_REG_OFFS_DMA_INT_STATUS                         (0x1008u)

# define ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS0                      (0x100Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS1                      (0x1010u)

/* DMA Channel 0 */
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_CNTRL                          (0x1100u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL                       (0x1104u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL                       (0x1108u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_LIST_ADDR              (0x1114u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_LIST_ADDR              (0x111Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR               (0x1120u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR               (0x1128u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_RING_LEN               (0x112Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_RING_LEN               (0x1130u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_INT_EN                         (0x1134u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_WATCHDG_TIMER                  (0x1138u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CUR_DESC                    (0x1144u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CUR_DESC                    (0x114Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CUR_BUF                     (0x1154u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CUR_BUF                     (0x115Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH0_STATUS                         (0x1160u)

/* DMA Channel 1 - QoS only */
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_CNTRL                          (0x1180u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL                       (0x1184u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL                       (0x1188u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_LIST_ADDR              (0x1194u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_LIST_ADDR              (0x119Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR               (0x11A0u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR               (0x11A8u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_RING_LEN               (0x11ACu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_RING_LEN               (0x11B0u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_INT_EN                         (0x11B4u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_WATCHDG_TIMER                  (0x11B8u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CUR_DESC                    (0x11C4u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CUR_DESC                    (0x11CCu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CUR_BUF                     (0x11D4u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CUR_BUF                     (0x11DCu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH1_STATUS                         (0x11E0u)
/* DMA Channel 2 - QoS only */
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_CNTRL                          (0x1200u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL                       (0x1204u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL                       (0x1208u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_LIST_ADDR              (0x1214u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_LIST_ADDR              (0x121Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR               (0x1220u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR               (0x1228u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_RING_LEN               (0x122Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_RING_LEN               (0x1230u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_INT_EN                         (0x1234u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH2_STATUS                         (0x1260u)
/* DMA Channel 3 - QoS only */
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_CNTRL                          (0x1280u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL                       (0x1284u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL                       (0x1288u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_LIST_ADDR              (0x1294u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_LIST_ADDR              (0x129Cu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR               (0x12A0u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR               (0x12A8u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_RING_LEN               (0x12ACu)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_RING_LEN               (0x12B0u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_INT_EN                         (0x12B4u)
# define ETH_30_TC3XX_REG_OFFS_DMA_CH3_STATUS                         (0x12E0u)

# define ETH_30_TC3XX_REG_OFFS_CLC                                    (0x2000u)
# define ETH_30_TC3XX_REG_OFFS_ETH_GPCTL                              (0x2008u)
# define ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER0                 (0x2014u)
# define ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER1                 (0x2018u)
# define ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR              (0x201Cu)
# define ETH_30_TC3XX_REG_OFFS_SKEWCTL                                (0x2040u)


/* ETH_MAC_CONFIGURATION register access (MAC Configuration Register) */
# define ETH_30_TC3XX_REG_CFG_RE                                      (0x00000001ul)
# define ETH_30_TC3XX_REG_CFG_TE                                      (0x00000002ul)
# define ETH_30_TC3XX_REG_CFG_RE_TE                                   (0x00000003ul)

/* ETH_MAC_FRAME_FILTER register access (MAC Frame Register) */
# define ETH_30_TC3XX_REG_PACKET_FILTER_PR                            (0x00000001ul)
# define ETH_30_TC3XX_REG_PACKET_FILTER_PM                            (0x00000010ul)

/* ETH_PMT_CONTROL_STATUS register access (PMT Control and Status Register) */
# define ETH_30_TC3XX_REG_PMT_CTRL_PWR_DOWN                           (0x00000001ul)

/* ETH_MDIO_ADDRESS register access (MDIO Address Register) */
# define ETH_30_TC3XX_REG_MDIO_ADDR_GB                                (0x00000001ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_C45E                              (0x00000002ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_GOC0                              (0x00000004ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_GOC1                              (0x00000008ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_GOC0_GOC1_MASK                    (0x0000000Cul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_GOC0_GOC1_SHIFT                   (0x00000002ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_SKAP                              (0x00000010ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK                           (0x00000F00ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_CR_SHIFT                          (8u)
# define ETH_30_TC3XX_REG_MDIO_ADDR_WRITE                             (ETH_30_TC3XX_REG_MDIO_ADDR_GOC0 )
# define ETH_30_TC3XX_REG_MDIO_ADDR_READ                              (ETH_30_TC3XX_REG_MDIO_ADDR_GOC0 | ETH_30_TC3XX_REG_MDIO_ADDR_GOC1)
# define ETH_30_TC3XX_REG_MDIO_ADDR_NTC_MASK                          (0x00007000ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_NTC_SHIFT                         (12u)
# define ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK                          (0x001F0000ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT                         (16u)
# define ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK                           (0x03E00000ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT                          (21u)
# define ETH_30_TC3XX_REG_MDIO_ADDR_BTB                               (0x04000000ul)
# define ETH_30_TC3XX_REG_MDIO_ADDR_PSE                               (0x08000000ul)

/* ETH_MDIO_DATA register access (MDIO Data Register) */
# define ETH_30_TC3XX_REG_MDIO_DATA_MASK                              (0x0000FFFFul)

/* ETH_MAC_ADDRESS_HIGH register access (MAC Address High Register) */
# define ETH_30_TC3XX_REG_MAC_HIGH_AE                                 (0x80000000ul)
# define ETH_30_TC3XX_REG_MAC_HIGH_SA                                 (0x40000000ul)
# define ETH_30_TC3XX_REG_MAC_HIGH_DCS_MASK                           (0x00030000ul) /* Select DMA-Channel 0, 1 ... */
# define ETH_30_TC3XX_REG_MAC_HIGH_ADDRHI_MASK                        (0x0000FFFFul)

/* ETH_MMC_CNTRL register access (MMC Control Register) */
# define ETH_30_TC3XX_REG_MMC_CNTRL_RST                               (0x00000001ul)

/* ETH_MAC_TIMESTAMP_CONTROL register access (MAC Timestamp Control Register) */
# define ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSINIT_MASK           (0x00000004u)
# define ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSUPDT_MASK           (0x00000008u)
# define ETH_30_TC3XX_REG_MAC_TIMESTAMP_CONTROL_TSADDREG              (0x00000020u)

/* ETH_MAC_SYSTEM_TIME_SECONDS register access (MAC System Time Seconds Register) */
# define ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_SECONDS_TSS_MASK            (0xFFFFFFFFul)

/* ETH_MAC_SYSTEM_TIME_NANOSECONDS register access (MAC System Time Nanoseconds Register) */
# define ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_NANOSECONDS_TSSS_MASK       (0x7FFFFFFFul)

/* ETH_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS register access (MAC System Time Higher Word Seconds Register) */
# define ETH_30_TC3XX_REG_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR_MASK (0x0000FFFFul)

/* ETH_MTL_TXQ_X_QUANTUM_WEIGHT register access */
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK         (0x0000FFFFul)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CBS_SCALING        (1024u)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_1GB     (8u)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_100MB   (40u)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_1GB   (0x00002000ul)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_100MB (0x00001000ul)

/* ETH_MTL_TXQ0_DEBUG register access */
# define ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_ALL_NOT_RESERVED_MASK       (0x0077003Ful)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK                 (0x00000006ul)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE              (0x00000002ul)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK                 (0x00000010ul)
# define ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY                   (0x00000000ul)

/* ETH_MTL_RXQ0_DEBUG register access */
# define ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_ALL_NOT_RESERVED_MASK       (0x3FFF0037ul)
# define ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK            (0x3FFF0030ul)
# define ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQSTS_MASK                 (0x00000030ul)
# define ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY                   (0x00000000ul)

/* ETH_DMA_MODE register access (DMA Bus Mode Register) */
# define ETH_30_TC3XX_REG_DMA_MODE_INTM_MASK                          (0x00030000ul)
# define ETH_30_TC3XX_REG_DMA_MODE_INTM_SHIFT                         (16u)
# define ETH_30_TC3XX_REG_DMA_MODE_SWR                                (0x00000001ul)

/* ETH_DMA_DEBUG_STATUS0 register access (DMA Debug Status 0 Register) */
# define ETH_30_TC3XX_REG_DMA_DEBUG_STATUS0_TPS_RPS_MASK              (0xFFFFFF00ul)

/* ETH_DMA_DEBUG_STATUS1 register access (DMA Debug Status 1 Register) */
# define ETH_30_TC3XX_REG_DMA_DEBUG_STATUS1_TPS_RPS_MASK              (0x000000FFul)

/* ETH_DMA_CHN_TX_CONTROL register access (DMA Channel N TX Control Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST                         (0x00000001ul)

/* ETH_DMA_CHN_RX_CONTROL register access (DMA Channel N RX Control Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR                         (0x00000001ul)
# define ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_RBSZ_MASK                  (0x00007FF8ul)
# define ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_RBSZ_SHIFT                 (3u)

/* ETH_DMA_CHN_TX_DESC_RING_LEN register access (DMA Channel N TX Descriptor Ring Length Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_TX_DESC_RING_LEN                    (0x03FFul)

/* ETH_DMA_CHN_RX_DESC_RING_LEN register access (DMA Channel N RX Descriptor Ring Length Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_RX_DESC_RING_LEN                    (0x03FFul)

/* ETH_DMA_CHN_STATUS register access (DMA Channel Status Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_NIS                          (0x00008000ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_AIS                          (0x00004000ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_TI                           (0x00000001ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_TPS                          (0x00000002ul) /* transmit stopped */
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_TI_TPS                       (0x00000003ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_TBU                          (0x00000004ul) /* transmit suspended */
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RI                           (0x00000040ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RBU                          (0x00000080ul) /* receive suspended */
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RPS                          (0x00000100ul) /* receive stopped */
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RI_RBU                       (0x000000C0ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RI_RBU_RPS                   (0x000001C0ul)
# define ETH_30_TC3XX_REG_DMA_CHN_STATUS_RX_ERROR_COMPOUND            (ETH_30_TC3XX_REG_DMA_CHN_STATUS_RBU)

/* ETH_DMA_CHN_MFC register access (DMA Channel Miss Frame Counter Register) */
# define ETH_30_TC3XX_REG_DMA_CHN_MISS_FRAME_CNT_MFC                  (0x000003FFul)

/* ETH_KERNEL_RESET_REGISTER0 register access (Kernel Reset Register 0) */
# define ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RST                  (0x00000001ul)
# define ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RSTSTAT              (0x00000002ul)

/* ETH_KERNEL_RESET_REGISTER1 register access (Kernel Reset Register 1) */
# define ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER1_RST                  (0x00000001ul)

/* ETH_KERNEL_RESET_STATUS_CLEAR register access (Kernel Reset Status Clear) */
# define ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR_CLR          (0x00000001ul)

/* PPS related registers fields */
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG_TRGTMODSEL         (0x00000060ul)
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS_CONTROL_REG_PPSCMD             (0x00000051ul) /* Single pulse generation */
# define ETH_30_TC3XX_REG_OFFS_MAC_PPS_NANOSECOND_TRGTBUSY0           (0x80000000ul) /* Target busy bit of nanoscecond timer */

/* TX Descriptor fields */
# define ETH_30_TC3XX_TX0_DESC_BUF1_ADDR_MASK                         (0xFFFFFFFFul)
# define ETH_30_TC3XX_TX1_DESC_BUF2_OR_BUF1_ADDR_MASK                 (0xFFFFFFFFul)
# define ETH_30_TC3XX_TX2_DESC_IOC                                    (0x80000000ul) /* TI interrupt on completion */
# define ETH_30_TC3XX_TX2_DESC_TTSE                                   (0x40000000ul) /* Transmit timestamp enable */
# define ETH_30_TC3XX_TX2_DESC_BUF2_LEN_MASK                          (0x3FFF0000ul)
# define ETH_30_TC3XX_TX2_DESC_BUF2_LEN_SHIFT                         (16u)
# define ETH_30_TC3XX_TX2_DESC_VTIR                                   (0x0000C000ul) /* VLAN Tag insertion or replacement */
# define ETH_30_TC3XX_TX2_DESC_BUF1_LEN_MASK                          (0x00003FFFul)
# define ETH_30_TC3XX_TX2_DESC_BUF1_LEN_SHIFT                         (0u)
# define ETH_30_TC3XX_TX3_DESC_OWN                                    (0x80000000ul) /* 0=Application owns, 1=DMA owns desc. */
# define ETH_30_TC3XX_TX3_DESC_FD                                     (0x20000000ul) /* First descriptor of a packet */
# define ETH_30_TC3XX_TX3_DESC_LD                                     (0x10000000ul) /* Last descriptor of a packet, Buf1 or Buf2 length must be set */
/* TX Descriptor fields - read format */
# define ETH_30_TC3XX_TX3_DESC_CPC_MASK                               (0x0C000000ul) /* CRC Pad Control */
# define ETH_30_TC3XX_TX3_DESC_CPC_SHIFT                              (26u)
# define ETH_30_TC3XX_TX3_DESC_SAIC_MASK                              (0x03800000ul) /* Source address insertion */
# define ETH_30_TC3XX_TX3_DESC_SAIC_SHIFT                             (23u)
# define ETH_30_TC3XX_TX3_DESC_FL_MASK                                (0x00007FFFul) /* Frame length */
# define ETH_30_TC3XX_TX3_DESC_IP_OFFLOAD                             (0x00000001ul)
# define ETH_30_TC3XX_TX3_DESC_TRANSPORT_OFFLOAD                      (0x00000003ul)
# define ETH_30_TC3XX_TX3_DESC_CIC_SHIFT                              (16u)
/* TX Descriptor fields - write back status bits of DMA */
# define ETH_30_TC3XX_TX0_DESC_TIMESTAMP_LOW_INVALID_MASK             (0xFFFFFFFFul)
# define ETH_30_TC3XX_TX1_DESC_TIMESTAMP_HIGH_INVALID_MASK            (0xFFFFFFFFul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_LD                              (1ul << 28u)
# define ETH_30_TC3XX_TX3_DESC_STATUS_TTSS                            (1ul << 17u)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES                              (0x00008000ul) /* Error Summary */
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_JT                           (0x00004000ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_FF                           (0x00002000ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_PCE                          (0x00001000ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_LOC                          (0x00000800ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_NC                           (0x00000400ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_LC                           (0x00000200ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_EC                           (0x00000100ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_CC_MASK                         (0x000000F0ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_CC_SHIFT                        (4u)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_ED                           (0x00000008ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_UF                           (0x00000004ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_DB                           (0x00000002ul)
# define ETH_30_TC3XX_TX3_DESC_STATUS_ES_IHE                          (0x00000001ul)

/* RX Descriptor fields */
# define ETH_30_TC3XX_RX0_DESC_BUF1_ADDR_MASK                         (0xFFFFFFFFul)
# define ETH_30_TC3XX_RX2_DESC_BUF2_ADDR_MASK                         (0xFFFFFFFFul)
# define ETH_30_TC3XX_RX3_DESC_OWN                                    (0x80000000ul) /* 0=Application owns, 1=DMA owns desc. */
# define ETH_30_TC3XX_RX3_DESC_IOC                                    (0x40000000ul) /* RI interrupt on completion */
# define ETH_30_TC3XX_RX3_DESC_BUF2V                                  (1ul << 25u) /* Buffer 2 Address Valid */
# define ETH_30_TC3XX_RX3_DESC_BUF1V                                  (1ul << 24u) /* Buffer 1 Address Valid */
/* RX Descriptor fields - after a packet has received, the write back of DMA fields are */
# define ETH_30_TC3XX_RX1_DESC_TSA                                    (1ul << 14u)
# define ETH_30_TC3XX_RX1_DESC_TD                                     (1ul << 15u)
# define ETH_30_TC3XX_RX3_DESC_CTXT                                   (0x40000000ul) /* Context descriptor */
# define ETH_30_TC3XX_RX3_DESC_FD                                     (0x20000000ul) /* First descriptor of a packet */
# define ETH_30_TC3XX_RX3_DESC_LD                                     (0x10000000ul) /* Last descriptor of a packet, Buf1 or Buf2 length must be set */
# define ETH_30_TC3XX_RX3_DESC_OE                                     (0x00200000ul) /* Overflow error */
# define ETH_30_TC3XX_RX3_DESC_RE                                     (0x00100000ul) /* Receive error */
# define ETH_30_TC3XX_RX3_DESC_DE                                     (0x00080000ul) /* Dribble-Bit error */
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_MASK                           (0x00070000ul) /* Length or Type packet */
# define ETH_30_TC3XX_RX3_DESC_ES                                     (0x00008000ul) /* Error Summary */
# define ETH_30_TC3XX_RX3_DESC_FL_MASK                                (0x00007FFFul) /* Frame length */
/* RX Descriptor fields - RX3_DESC Len/Type field values */
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_LEN                            (0u)
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_TYPE                           (1u)
/* RX Descriptor fields - RX3_DESC Len/Type field values - 2U is reserved */
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_ARP                            (3u)
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_TYPE_VLAN                      (4u)
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_TYPE_DVLAN                     (5u)
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_MACCTRL                        (6u)
# define ETH_30_TC3XX_RX3_DESC_LENTYPE_OAM                            (7u)

/* VLAN-ID based frame queuing control and data register masks */
# define ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_MASK                         (0x00000000ul)
# define ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OFS_SHIFT                    (2u)
# define ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_CT_MASK                      (0x00000002ul)
# define ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK                      (0x00000001ul)

# define ETH_30_TC3XX_MAC_VLAN_TAG_DATA_MASK                         (0x01070000ul)
# define ETH_30_TC3XX_MAC_VLAN_TAG_DATA_VLANID_MASK                  (0x0000FFFFul)
# define ETH_30_TC3XX_MAC_VLAN_TAG_DATA_DMACHN_SHIFT                 (25u)
#endif /* ETH_30_TC3XX_LL_REGS_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Regs.h
 *********************************************************************************************************************/
