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
/*!        \file  Eth_30_Tc3xx_LL_TrafficHandling.h
 *        \brief  Lower layer part of the traffic handling sub-module of the driver
 *
 *      \details  Contains the derivative specific implementation of the traffic handling sub-module of the Tc3xx
 *                Ethernet driver.
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_LL_TRAFFIC_HANDLING_H)
# define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Int.h"
# include "Eth_30_Tc3xx_LL.h"
# if (ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#  if !defined (ETH_30_TC3XX_LL_TRAFFICH_HANDLING_LOCAL) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TRAFFICH_HANDLING_LOCAL                    LOCAL
#  endif /* ETH_30_TC3XX_LL_TRAFFICH_HANDLING_LOCAL */

#  if !defined (ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE) /* COV_ETH_COMPATIBILITY */
#   define ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE              LOCAL_INLINE
#  endif /* ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth
 **********************************************************************************************************************/
/*! \brief       Transforms the register representation of the bandwidth into value represented in Bit/s
 *  \details     -
 *  \param[in]   regValue     Bandwidth in register representation
 *  \param[in]   trcvSpeed    Link speed related to the respective Ethernet controller
 *  \return      Bandwidth in Bit/s
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 *  \pre         -
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth(
  uint32 regValue,
  uint32 trcvSpeed);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal
 **********************************************************************************************************************/
/*! \brief       Transforms the bandwidth represented in Bit/s into register value
 *  \details     -
 *  \param[in]   bandwidth    Bandwidth in Bit/s
 *  \param[in]   trcvSpeed    Link speed related to the respective Ethernet controller
 *  \return      Bandwidth in register representation
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 *  \note        Value bandwidth must not exceed the value of trcvSpeed.
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal(
  uint32 bandwidth,
  uint32 trcvSpeed); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITION
 *********************************************************************************************************************/
#  ifndef ETH_30_TC3XX_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint32 regValue,
  uint32 trcvSpeed)
{
  uint32 bandwidth;
  float64 cycleTime = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_100MB;

  /* #10 Set cycle time according to the set transceiver speed (100MBit / 1GBit) */
  if (trcvSpeed == ETH_TRCV_SPEED_1000MBITS_IN_BITS)
  {
    cycleTime = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_1GB;
  }

  /* #20 Transform the register representation of the bandwidth to Bit/s */
  bandwidth = (uint32)((((float64)(regValue)) * ETH_30_TC3XX_NSEC_PER_SEC)/
                                   (cycleTime * ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CBS_SCALING));

  return bandwidth;
} /* Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint32 bandwidth,
  uint32 trcvSpeed)
{
  uint32  regValue;
  uint32  regValueMax = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_100MB;
  float64 cycleTime   = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_100MB;

  /* #10 Set maximal possible register value and cycle time according the the set transceiver speec */
  if (trcvSpeed == ETH_TRCV_SPEED_1000MBITS_IN_BITS)
  {
    regValueMax = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_PORT_TX_RATE_1GB;
    cycleTime   = ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CYCLE_TIME_1GB;
  }

  /* #20 Transform bandwidth fraction resulting from given bandwidth and link speed into idle slope */
  regValue = (uint32)((((float64)(bandwidth)) * cycleTime * ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_CBS_SCALING)/
                                  ETH_30_TC3XX_NSEC_PER_SEC);

  /* #30 If the calculated register value exceeds the maximal possible value, use the maximal possible value instead */
  if (regValue > regValueMax)
  {
    regValue = regValueMax;
  }

  return regValue;
} /* Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal() */

#  endif /* ETH_30_TC3XX_UNIT_TEST */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Sets the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx            Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bandwidth     Bandwidth that shall be applied
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE for different descriptor ring
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth(
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! \brief       Retrieves the bandwidth of the shaper related to the descriptor ring
 *  \details     -
 *  \param[in]   ctrlIdx       Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx  Descriptor ring the shaper is related to
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \return      Current bandwidth of the shaper
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth(
  uint8 ctrlIdx,
  uint8 descrRingIdx); /* PRQA S 0779 */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION DEFINITION
 *********************************************************************************************************************/

#  ifndef ETH_30_TC3XX_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8  ctrlIdx,
  uint8  descrRingIdx,
  uint32 bandwidth)
{
  /* #10 Transform bandwidth into register representation */
  bandwidth = Eth_30_Tc3xx_LL_TrafficHandling_TransformBandwidthToRegVal(bandwidth, Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(ctrlIdx));

  /* #20 Check if shaper of mid 0 priority descriptor ring is addressed */
  if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    /* #210 Adapt bandwidth of shaper related to mid 0 priority descriptor ring */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_QUANTUM_WEIGHT, bandwidth);
  }
  /* #30 Check if shaper of mid 1 priority descriptor ring is addressed */
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    /* 310 Adapt bandwidth of shaper related to mid 1 priority descriptor ring */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_QUANTUM_WEIGHT, bandwidth);
  }
  else
  {
    /* #40 Adapt bandwidth of shaper related to high priority descriptor ring */
    /* * (core ensures that only high priority descriptor ring is addressed here) */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_QUANTUM_WEIGHT, bandwidth);
  }
} /* Eth_30_Tc3xx_LL_TrafficHandling_SetShaperBandwidth() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
ETH_30_TC3XX_LL_TRAFFIC_HANDLING_LOCAL_INLINE FUNC(uint32, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
  uint8 ctrlIdx,
  uint8 descrRingIdx)
{
  uint32 bandwidth;

  /* #10 Check if shaper of mid 0 priority descriptor ring is addressed */
  if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    /* #110 Retrieve register value of shaper of mid priority descriptor ring */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }
  /* #20 Check if shaper of mid 1 priority descriptor ring is addressed */
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    /* #210 Retrieve register value of shaper of mid priority descriptor ring */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }
  else
  {
    /* #30 Retrieve register value of shaper of high priority descriptor ring */
    /* (core ensures that only high priority descriptor ring is addressed here) */
    bandwidth = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_QUANTUM_WEIGHT) &
        ETH_30_TC3XX_REG_MTL_TXQ_X_QUANTUM_WEIGHT_ISCQW_MASK;
  }

  /* #40 Transform register representation of bandwidth into Bit/s */
  bandwidth = Eth_30_Tc3xx_LL_TrafficHandling_TransformRegValToBandwidth(bandwidth, Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(ctrlIdx));

  return bandwidth;
} /* Eth_30_Tc3xx_LL_TrafficHandling_GetCurrentShaperBandwidth() */

#  endif /* ETH_30_TC3XX_UNIT_TEST */

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */
#endif /* ETH_30_TC3XX_LL_TRAFFIC_HANDLING_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL_TrafficHandling.h
 *********************************************************************************************************************/
