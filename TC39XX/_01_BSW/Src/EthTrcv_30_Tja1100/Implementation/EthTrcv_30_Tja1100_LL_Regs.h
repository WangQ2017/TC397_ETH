/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTrcv_30_Tja1100_LL_Regs.h
 *        \brief  Ethernet transceiver driver lower layer header file
 *
 *      \details  Header file containing the Register offset, mask and shift information for the Ethernet Transceiver
 *                driver lower layer
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
#if !defined (ETHTRCV_30_TJA1100_LL_REGS_H)
# define ETHTRCV_30_TJA1100_LL_REGS_H
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
 *
 *
 *
 *
 *
 *
 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* register adress offsets */
# define ETHTRCV_30_TJA1100_REG_OFFS_BMCR                                       (0x0000U)
# define ETHTRCV_30_TJA1100_REG_OFFS_BMSR                                       (0x0001U)
# define ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR1                                    (0x0002U)
# define ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR2                                    (0x0003U)
# define ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR3                                    (0x0010U)
# define ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL                                     (0x0011U)
# define ETHTRCV_30_TJA1100_REG_OFFS_CFG1                                       (0x0012U)
# define ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT                                   (0x0017U)
# define ETHTRCV_30_TJA1100_REG_OFFS_EXT_STAT                                   (0x0019U)
# define ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG                                 (0x001BU)
# define ETHTRCV_30_TJA1100_REG_OFFS_CFG_3                                      (0x001CU)

/* BMCR register access (Basic Mode Control Register) */
# define ETHTRCV_30_TJA1100_REG_BMCR_RESET                                      (0x8000U)
# define ETHTRCV_30_TJA1100_REG_BMCR_LOOPBACK                                   (0x4000U)
# define ETHTRCV_30_TJA1100_REG_BMCR_SPEED_SELECTION_LSB                        (0x2000U)
# define ETHTRCV_30_TJA1100_REG_BMCR_ENABLE_AUTO_NEG                            (0x1000U)
# define ETHTRCV_30_TJA1100_REG_BMCR_POWER_DOWN                                 (0x0800U)
# define ETHTRCV_30_TJA1100_REG_BMCR_RESTART_AUTO_NEG                           (0x0200U)
# define ETHTRCV_30_TJA1100_REG_BMCR_DUPLEX_MODE_FULL                           (0x0100U)

/* BMSR register access (Basic Mode Status Register) */
# define ETHTRCV_30_TJA1100_REG_BMSR_LINK_STATE                                 (0x0004U)

/* PHYIDR1 register access (PHY Identifier Register #1) */
# define ETHTRCV_30_TJA1100_REG_PHYIDR1_NXP_OUI_MSB                             (0x0180U)


/* EXTCTRL register access (Extended control register) */
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_CONFIG_EN                               (0x0004U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_MODE_MASK                               (0x7800U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_NORMAL_MODE                             (0x1800U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_STANDBY_MODE                            (0x6000U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL                            (0x8000U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_TEST_MODE_MASK                          (0x01C0U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_TEST_MODE_SHIFT                         (0x6U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_CLEAR                     (0xFFE7U)
/* For external loopback the bits 3 (0x0008) or 4 (0x0010) are usable, both lead to the same mode. */
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_EXT                       (0x0008U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_REM                       (0x0018U)
# define ETHTRCV_30_TJA1100_REG_EXTCTRL_CABLE_TEST_ENABLE                       (0x0020U)

/* COM_STAT register access (Communication Status register) */
# define ETHTRCV_30_TJA1100_REG_COM_STAT_LINK_STATE_UP_MASK                     (0x9C00U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_SIGNAL_QUALITY_MASK                    (0x00E0U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_SIGNAL_QUALITY_SHIFT                   (0x5U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_PHY_ACTIVE                             (0x0004U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_CABLE_TEST_ACTIVE                      (0x0006U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_TX_MODE_MASK                           (0x6000U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_TX_MODE_SEND_N                         (0x2000U)
# define ETHTRCV_30_TJA1100_REG_COM_STAT_TX_MODE_SEND_I                         (0x4000U)

/* CFG1 register access (Configuration Register 1)    */
# define ETHTRCV_30_TJA1100_REG_CFG1_MASTER_SLAVE                               (0x8000U)
# define ETHTRCV_30_TJA1100_REG_CFG1_AUTO_OP_TJA1100                            (0x4000U)
# define ETHTRCV_30_TJA1100_REG_CFG1_MII_MODE                                   (0x0000U)
# define ETHTRCV_30_TJA1100_REG_CFG1_RMII_MODE                                  (0x0100U)
# define ETHTRCV_30_TJA1100_REG_CFG1_RMII_MODE_XTAL                             (0x0200U)
# define ETHTRCV_30_TJA1100_REG_CFG1_REVERSE_MII_MODE                           (0x0300U)
# define ETHTRCV_30_TJA1100_REG_CFG1_MII_MODE_MASK                              (0x0300U)
# define ETHTRCV_30_TJA1100_REG_CFG1_MII_DRIVER                                 (0x0080U)
# define ETHTRCV_30_TJA1100_REG_CFG1_CLEAR_SETTINGS                             (0x3C31U)

/* EXT_STAT register access (External Status Register) */
# define ETHTRCV_30_TJA1100_REG_EXT_STAT_CABLE_DIAG_RESULT_MASK                 (0x0180U)
# define ETHTRCV_30_TJA1100_REG_EXT_STAT_SHORT_DETECT                           (0x0100U)
# define ETHTRCV_30_TJA1100_REG_EXT_STAT_OPEN_DETECT                            (0x0080U)
# define ETHTRCV_30_TJA1100_REG_EXT_STAT_OK                                     (0x0000U)

/* COMMON_CFG Common configuration register access*/
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_AUTO_OP_TJA1102                      (0x8000U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_MODE_MASK_TJA1102                (0x3000U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_25MHZ_XTAL_OUT_TJA1102           (0x1000U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_25MHZ_EXT_CLK_TJA1102            (0x2000U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_50MHZ_REF_CLK_TJA1102            (0x3000U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_LDO_MODE_DISABLED                    (0x0800U)
# define ETHTRCV_30_TJA1100_REG_COMMON_CFG_INT_REV_MII_ENABLED                  (0x4000U)

/* CFG_3 register access (Configuration register 3) */
#define ETHTRCV_30_TJA1100_REG_CFG_3_PHY_EN                                     (0x0001U)

#endif /* ETHTRCV_30_TJA1100_LL_REGS_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_Tja1100_LL_Regs.h
 *********************************************************************************************************************/
