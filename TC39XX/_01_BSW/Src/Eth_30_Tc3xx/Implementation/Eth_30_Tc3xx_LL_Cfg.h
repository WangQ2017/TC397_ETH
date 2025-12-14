/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  Eth_30_Tc3xx_LL_Cfg.h
 *        \brief  Lower layer core configuration
 *
 *      \details  Core configuration defined by lower layer.
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

#if !defined (ETH_30_TC3XX_LL_CFG_H)
# define ETH_30_TC3XX_LL_CFG_H

# define ETH_30_TC3XX_IMPLEMENTATION_INIT                             (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_INIT_MEMORY                      (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_CONTROLLER_INIT                  (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_SET_CONTROLLER_MODE              (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_CONTROLLER_MODE              (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_PHYS_ADDR                    (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_SET_PHYS_ADDR                    (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_UPDATE_PHYS_ADDR_FILTER          (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_WRITE_MII                        (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_READ_MII                         (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_COUNTER_STATE                (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_PROVIDE_TX_BUFFER                (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_TRANSMIT                         (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_VTRANSMIT                        (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_RECEIVE                          (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_TX_CONFIRMATION                  (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_GLOBAL_TIME                  (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_SET_GLOBAL_TIME                  (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_SET_CORRECTION_TIME              (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_ENABLE_EGRESS_TIMESTAMP          (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_EGRESS_TIMESTAMP             (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_INGRESS_TIMESTAMP            (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_SET_BANDWIDTH_LIMIT              (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_BANDWIDTH_LIMIT              (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_MAINFUNCTION                     (STD_ON)
# define ETH_30_TC3XX_IMPLEMENTATION_GET_VERSION_INFO                 (STD_ON)

#endif /* ETH_30_TC3XX_LL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_Cfg.h
 *********************************************************************************************************************/

