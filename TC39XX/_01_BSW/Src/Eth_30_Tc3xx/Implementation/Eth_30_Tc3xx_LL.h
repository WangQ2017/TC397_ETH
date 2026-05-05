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
/*!        \file  Eth_30_Tc3xx_LL.h
 *        \brief  Lower layer header file
 *
 *      \details  Declaration and definition of lower layer part of Ethernet driver.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  00.01.00  2017-08-01  visbgr  -             Initial creation
 *  00.02.00  2018-01-03  visbgr  STORY-3570    TASK-60515 Provide DrvETh_Tc3xx Beta version using TriBoard TC3X9 V2.0
 *  01.00.00  2018-02-19  visbgr  STORY-4098    TASK-65966 Review Integration and Core Update
 *  02.00.00  2018-05-14  visbgr  STORYC-5156   TASK-73499 Implement prototype QoS support in implementation
 *                                STORYC-5967   TASK-82306 Testing and bugfixing of QoS RX prototype implementation
 *                                STORYC-5968   TASK-82307 Testing and bugfixing of FQTSS prototype implementation
 *                                STORYC-5155   TASK-73501 Finalize QoS support implementation
 *  02.01.00  2019-02-18  visbgr  STORY-10652   Update Core DrvEth_Tc3xxEthAsr
 *  03.00.00  2019-03-18  visbgr  ESCAN00101437 Possible memory violation in case of multi Eth driver configuration
 *                                ESCAN00101808 Compiler warning: Calling function without prototype
 *                                              Appl_UnlockEndinit / Appl_LockEndinit
 *                                ESCAN00101709 Missing overflow handling during global time retrieval
 *  03.00.01  2019-04-02  visbgr  STORYC-8019   Review Integration of DMA Review for TC3xx
 *                                ESCAN00101663 Memory corruption possible if RX buffers are configured smaller than
 *                                              1522 bytes
 *                                ESCAN00102625 Possible loss of interrupt could lead to stuck communication on
 *                                              Ethernet
 *  04.00.00  2019-08-27  viskha  ETH-786       Update DrvEth_Tc3xxEthAsr to MSR4-R23 DrvEth__coreAsr
 *  04.00.01  2020-02-11  visken  ESCAN00103315 Not considered Application Hint GETH_AI.H001 Preparation for Software
 *                                              Reset (GETH_TC.002 update)
 *                                ETH-1694      Introduce further handling that is needed for bugfix of ESCAN00103315
 *                                ESCAN00105289 Possible Endless-Loop in IRQ handler in case frame is received during 
 *                                              mode transition from ACTIVE to DOWN
 *                                ESCAN00105184 Update Core DrvEth_Tc3xxEthAsr
 *  04.00.02  2020-04-14  viskha  ESCAN00106019 Compiler error: undeclared identifier "CtrlIdx"
 *                                ESCAN00105914 Not considered Application Hint GETH_AI.H001 together with
 *                                              GETH_TC.002 - Preparation for Software Reset
 *  04.01.00  2020-05-11  viskha  ETH-2057      Allow triggering PPS signal from TC3xx to external chip on a given
 *                                              timer value in the MAC
 *  05.00.00  2020-03-23  vircnt  ETH-1899      Update to latest DrvEth__coreAsr
 *            2020-06-17  virstl  ETH-2367      Check CDD for consistency
 *            2020-06-25  vircnt  ETH-1905      Integrate bugfixes and features from main development branch
 *            2020-07-15  vircnt  ETH-2716      Update DrvEth_Tc3xxAsr to trunk of DrvEth__coreAsr
 *  06.00.00  2020-09-25  virbks  ETH-3270      Update DrvEth_Tc3xxEthAsr to DrvEth__coreAsr[9.01.04]
 *            2020-09-28  virstl  ETH-3244      Safety ready DrvEth_Tc3xxEthAsr (Silent)
 *  06.01.00  2020-10-22  virbks  ETH-3295      Support QoS and checksum offloading enabled at the same time
 *  06.02.00  2021-03-17  visdep  ETHCIF-138    Introduce assignment of Ethernet frames to queues based on VLAN ID
 *********************************************************************************************************************/

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_LL_H)
# define ETH_30_TC3XX_LL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Cfg.h"
# include "Eth_30_Tc3xx_IrqHandler_Int.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# ifndef ETH_30_TC3XX_LOCAL           /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_LOCAL                                       static
# endif

# ifndef ETH_30_TC3XX_LL_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
#  define ETH_30_TC3XX_LL_LOCAL_INLINE                                LOCAL_INLINE
# endif /* ETH_30_TC3XX_LL_LOCAL_INLINE */

# define ETH_30_TC3XX_SW_MAJOR_VERSION                                (6u)
# define ETH_30_TC3XX_SW_MINOR_VERSION                                (2u)
# define ETH_30_TC3XX_SW_PATCH_VERSION                                (0u)

# define ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX                    (2u)

# define ETH_30_TC3XX_FRAME_TYPE_LEN_BYTE                             (2u)
# define ETH_30_TC3XX_USED_FCS_LEN_BYTE                               (0u)
# define ETH_30_TC3XX_FCS_LEN_BYTE                                    (4u)

# define ETH_30_TC3XX_ALIGN_PADDING                                   (2u)


# define ETH_30_TC3XX_MMC_COUNTER_MAX_OFFSET                          (0x0170u)
# define ETH_30_TC3XX_MMC_COUNTER_BASE_OFFSET                         (0x0714u)

/*! Shaper/Descriptor ring identifier */
# define ETH_30_TC3XX_LL_LOW_PRIO_QUEUE_IDX                           (0u)
# define ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX                         (1u)
# define ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX                         (2u)
# define ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX                          (3u)

# define ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED                      (2u)
# define ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED                      (3u)


/*! Descriptor and Buffer Alignment restrictions */
# define ETH_30_TC3XX_LL_DESC_ALIGN_BYTE                              (16u)
# define ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE                              (16u)

/*! Maximal value of Rx FIFO overflow counter register */
# define ETH_30_TC3XX_RX_FIFO_OVERFLOW_PACKETS_COUNT_MAX              (65535u)

/*! PPS identifiers */
# define ETH_30_TC3XX_PPS_TIME_SECONDS_HI                             (0x0u)
# define ETH_30_TC3XX_PPS_TIME_NANOSECONDS_RANGE                      (0x7FFFFFFFu)

/* ETH ApiIds */
# define ETH_30_TC3XX_SID_ARM_PPS_EVENT_ON_TIME                       (0x45u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETH_30_TC3XX_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Tx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Tx event pending that must be confirmed
 *  \return      TRUE - There is at least one Tx event pending that must be confirmed
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
    uint8 ctrlIdx);

 /**********************************************************************************************************************
  *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
 /*! \brief       Checks for pending Tx Queue events
  *  \details     The function checks for pending Tx Queue events and sets respective Tx event flags
  *  \param[in]   ctrlIdx       Identifier of the Ethernet controller.
  *  \param[in]   descrRingIdx  Index of descriptor ring.
  *  \return      FALSE - There is no Tx event pending that must be confirmed
  *  \return      TRUE - There is at least one Tx Queue event pending that must be confirmed
  *  \context     TASK|ISR1|ISR2
  *  \synchronous TRUE
  *  \reentrant   FALSE
  *  \pre         -
  */
 ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
     uint8 ctrlIdx,
     Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx events
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! \brief       Checks for pending Rx Queue events
 *  \details     The function checks for pending Rx Queue events and sets respective Rx event flags
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller.
 *  \param[in]   descrRingIdx  Index of descriptor ring.
 *  \return      FALSE - There is no Rx event pending that must be notified
 *  \return      TRUE - There is at least one Rx event pending that must be notified
 *  \context     TASK|ISR1|ISR2
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    Eth_30_Tc3xx_RxDescrRingProcIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief        Function for initializing an RX descriptor
 *  \details      -
 *  \param[in]    ctrlIdx          Index of Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    descrRingIdx     Index of descriptor ring to be initialized
 *                [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]    descrIdx         Index of descriptor to be initialized
 *                [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[in]    rxBufIdx         Index of buffer to be mapped to the reception descriptor to be initialized
 *                [range: 0 <= rxBufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(rxBufferHandlingIdx)]
 *  \context      TASK
 *  \synchronous  TRUE
 *  \reentrant    FALSE
 *  \pre          -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor(
  uint8                                       ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitializeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for initializing a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring to be initialized
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor to be initialized
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous  TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses()
 *********************************************************************************************************************/
/*! \brief       Function for announcing the descriptor base addresses to hardware
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which descriptors shall be announced
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_InitDescriptorStateVariables()
 *********************************************************************************************************************/
/*! \brief       Function for initializing descriptor state variables, if needed by the lower layer
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnableMiiAccess()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MII access (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller where the MII access shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMiiAccess(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetCounters()
 *********************************************************************************************************************/
/*! \brief       Function for resetting statistic counters of the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which statistic counters should be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the IP checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the Protocol checksum offload option in a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which checksum offloading shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which checksum offloading shall be enabled
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which checksum offloading shall be enabled
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_TriggerTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for starting the transmission of a already prepared buffer an descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the transmission shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the transmission shall be triggered
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the transmission shall be triggered
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the timestamping option for a TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which timestamping shall be prepared
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which timestamping shall be prepared
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which timestamping shall be prepared
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer for which timestamping shall be prepared
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx,
  Eth_30_Tc3xx_TxBufferStateIterType   bufIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission()
 *********************************************************************************************************************/
/*! \brief       Function for doing all necessary settings to prepare a TX descriptor for transmission
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be used for transmission
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring to be used for transmission
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor to be transmitted
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \param[in]   bufIdx           Index of buffer to be transmitted
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   lenByte          Length of frame to be transmitted
 *  \param[in]   bufPtr           Pointer to buffer to be transmitted
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
          uint8                                                                   ctrlIdx,
          Eth_30_Tc3xx_TxDescrHandlingIterType                                    descrRingIdx,
          Eth_30_Tc3xx_TxDescrIterType                                            descrIdx,
          Eth_30_Tc3xx_TxBufferStateIterType                                      bufIdx,
          uint16                                                                  lenByte,
  P2CONST(uint8,                              AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bufPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeTxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a TX descriptor, after the transmission of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! \brief       Resets the timestamping request for the given TX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the timestamping request shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the timestamping request shall be reset
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the timestamping request shall be reset
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnableMac()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTransmissionComplete()
 *********************************************************************************************************************/
/*! \brief       Function for checking if previous frame transmission completed
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for completed frame transmission
 *  \return      E_NOT_OK - Previous frame transmission not completed within time out
 *  \return      E_OK - Previous frame transmission completed within time out
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTransmissionComplete(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem()
 *********************************************************************************************************************/
/*! \brief       Function for checking if data in Rx FIFO is transferred to system memory
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked if data in Rx FIFO is transferred to system memory
 *  \return      E_NOT_OK - Data in Rx FIFO was not transferred to system within time out
 *  \return      E_OK - Data in Rx FIFO was transferred to system within time out
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem(
    uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisableMac()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the MAC
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMacEnabled()
 *********************************************************************************************************************/
/*! \brief       Function for checking the mode of the MAC (enabled, disabled)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller to be checked for mode
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC is enabled
 *  \return      FALSE - MAC is disabled
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMacEnabled(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMacAddressToRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the configured MAC address to the hardware register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MAC address shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to physical address to be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister(
          uint8                                      ctrlIdx,
  P2CONST(uint8, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PreResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for hardware specific operations which need to be executed before MAC reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be initialized
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WaitfSPBCycles()
 *********************************************************************************************************************/
/*! \brief       The function provides the necessary fSPB cycles delay
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   fspbcycles       fSPB cycles count for delay
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WaitfSPBCycles(
    uint8 ctrlIdx,
    uint8 fspbcycles );

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty()
 *********************************************************************************************************************/
/*! \brief       This function checks whether the RxQi Debug registers are empty or not
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   debugRegMask     Register Mask to check status of reg
 *  \return      E_OK - RxQi Debug registers contents are empty
 *  \return      E_NOT_OK - RxQi Debug registers contents are not empty
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask );

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty()
 *********************************************************************************************************************/
/*! \brief       This function checks whether the TxQi Debug registers are empty or not
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *  \param[in]   debugRegMask     Register Mask to check status of reg
 *  \return      E_OK - TxQi Debug registers contents are empty
 *  \return      E_NOT_OK - TxQi Debug registers contents are not empty
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask );

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetMac()
 *********************************************************************************************************************/
/*! \brief       Function for resetting the MAC (if needed by hardware)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsResetMacFinished()
 *********************************************************************************************************************/
/*! \brief       Function for checking for the completion of the reset
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller which shall be checked for completion of reset
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      TRUE - MAC reset is finished
 *  \return      FALSE - MAC reset is not finished yet
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished(
  uint8 ctrlIdx);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_EnablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be enabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_DisablePromiscuousMode()
 *********************************************************************************************************************/
/*! \brief       Function for disabling the promiscuous mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which promiscuous mode shall be disabled
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CloseAllMulticastFilters()
 *********************************************************************************************************************/
/*! \brief       Function for closing all multicast filters
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which all multicast filters shall be closed
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config     ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetMulticastFilteringMode()
 *********************************************************************************************************************/
/*! \brief       Function for enabling a certain multicast filter mode
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast filter mode shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function for writing the lower multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be set
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the upper multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister()
 *********************************************************************************************************************/
/*! \brief       Function writing resetting bits in the lower multicast filter bucket register
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bucketMask       Mask which shall be reset
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash()
 *********************************************************************************************************************/
/*! \brief       Function for calculating a multicast filter hash value
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the multicast bucket register shall be set
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   macAddrPtr       Pointer to the physical address for which a hash shall be calculated
 *  \param[out]  hashPtr          Pointer to the variable which contains the calculated hash
 *  \param[out]  isUpperRegPtr    Pointer to the variable which contains the decision which filter register shall be
 *                                used
 *  \param[out]  bucketMaskPtr    Pointer to the variable which contains the mask for the filter register
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 *  \config      ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(
          uint8                                        ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) hashPtr,
    P2VAR(boolean, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bucketMaskPtr);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_WriteMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a write operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller  for which the MII write operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII write operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII write operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \param[in]   regVal           Register value that shall be written
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ReadMiiTrigger()
 *********************************************************************************************************************/
/*! \brief       Function for triggering a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation shall be triggered
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx          Index of transceiver for which the MII read operation shall be triggered
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx           Index of register for which the MII read operation shall be triggered
 *               [range: 0 <= regIdx < 32]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetReadMiiResult()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the result of a read operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII read operation result shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  regValPtr        Pointer to buffer where register value shall be stored
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult(
        uint8                                       ctrlIdx,
  P2VAR(uint16, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) regValPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsMiiOperationPending()
 *********************************************************************************************************************/
/*! \brief       Function for checking the completion of an operation on the MII Interface (MDIO line)
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the MII operation completion shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_MII must be entered.
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetTxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the TX events for the respective descriptor rings
 *  \details     Function sets TX events by calling Eth_30_Tc3xx_SetTxEvent() for each TX descriptor ring having a
 *               pending TX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending TX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a RX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= ringIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfEthRxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a TX descriptor is owned by DMA or driver
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfTxDescr()]
 *  \return      TRUE - descriptor is owned by driver
 *  \return      FALSE - descriptor is owned by DMA
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsErrorInRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the information, if a error flag was set in a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the owner of a descriptor shall be checked
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the owner of a descriptor shall be checked
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the owner shall be checked
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \return      TRUE - error flag is set in descriptor
 *  \return      FALSE - no error flags is set in descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_SetRxEvents()
 *********************************************************************************************************************/
/*! \brief       Sets the RX events for the respective descriptor rings
 *  \details     Functions sets RX events by calling Eth_30_Tc3xx_SetRxEvent() for each RX descriptor ring having a
 *               pending RX event (respective interrupt flag set).
 *  \param[in]   ctrlIdx          Index of controller pending RX events shall be queried for
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*! \brief       Rearms the MAC for being able to receive frames on the respective descriptor ring again
 *  \details     Function sets registers that rearm the RX DMA to receive frames on the respective RX descriptor
 *               ring again.
 *  \param[in]   ctrlIdx          Index of controller that shall be rearmed for reception
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring that shall be rearmed for reception
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \context     ANY
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Eth controllers
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_RechargeRxDescriptor()
 *********************************************************************************************************************/
/*! \brief       Function for recharging a RX descriptor, after the reception of a frame was finished
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be recharged
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be recharged
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor which shall be recharged
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 *********************************************************************************************************************/
/*! \brief       Function for HW specific RX descriptor operations which are necessary after a frame has been received
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the descriptor shall be adapted
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the descriptor shall be adapted
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx        Index of descriptor which shall be adapted
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 *********************************************************************************************************************/
/*! \brief       Function for retrieving the frame length of a received frame from a RX descriptor
 *  \details     -
 *  \param[in]   ctrlIdx          Index of controller for which the frame length shall be retrieved
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx     Index of descriptor ring for which the frame length shall be retrieved
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx         Index of descriptor for which the frame length shall be retrieved
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \return      Length extracted from a RX descriptor
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! \brief       Returns the maximum counter offset within the statistic counter register block
 *  \details     Function returns the maximum counter offset of the Ethernet controllers statistic counters register
 *               block.
 *               during retrieval of the counter value.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      Amount of statistic counters
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! \brief       Retrieves the value of the given statistics counter
 *  \details     Function checks if a valid statistics counter is addressed within the counter register block and if
 *               so returns its value.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   counterOffset    Offset into the statistic counter register block
 *  \param[out]  counterValPtr    Value of the statistics counter
 *  \return      E_OK - Counter value successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers and counters
 *  \pre         counterIdx must have been checked for being inbound of the statistics counter register block
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue(
        uint8                                       ctrlIdx,
        Eth_30_Tc3xx_RegOffsetType                  counterOffset,
  P2VAR(uint32, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) counterValPtr);

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of RX statistics counters
 *  \details     Function reads a set of reception statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  rxStatsPtr Pointer to the address where the RX statistics counter values are stored
 *  \return      E_OK - RX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *  \config      ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! \brief       Retrieves the values of TX statistics counters
 *  \details     Function reads a set of transmission statistics counters and returns their values.
 *  \param[in]   ctrlIdx    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  txStatsPtr Pointer to the address where the TX statistics counter values are stored
 *  \return      E_OK - TX statistics counters successfully retrieved
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   TRUE - for different Ethernet controllers
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *  \config      ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function returns the number of reception drop events due to insufficient buffers.
 *  \details     Read the Hw counter of reception drop events due to insufficient buffers if exists and return the 
 *               counter value and if the counter is reset on read or not.
 *  \param[in]   ctrlIdx                    Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  isHwCtrResetOnReadPtr  Pointer to variable to store if the Hw counter is reset on read
 *  \param[out]  readCtrValuePtr        Pointer to variable where the read count of Rx frame drop is stored
 *  \return      E_OK - Hardware counter values are retrieved successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to get the counter value
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                        ctrlIdx,
  P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC) readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC)  isHwCtrResetOnReadPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter()
 *********************************************************************************************************************/
/*! \brief       This function resets the counter for reception drop events due to insufficient buffers
 *  \details     Reset the Hw counter used to store the count of number of reception drop events due to insufficient rx
 *               buffers. If the reset is not possible, it will be indicated to the caller.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware counter reset successfully
 *  \return      E_NOT_OK - Hardware counter is not available or unable to reset the counter
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx);
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_PerformAdditionalHwConfig()
 *********************************************************************************************************************/
/*! \brief       This function performs the controller specific additional configurations.
 *  \details     This function can be used to perform additional hardware specific configurations such as Indirect 
 *               register access, VLAN-ID based frame queuing configurations etc.
 *  \param[in]   ctrlIdx          Index of controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_OK - Hardware specific configuration successful
 *  \return      E_NOT_OK - Hardware specific configuration not successful
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ArmPpsEventOnTime
 *********************************************************************************************************************/
/*! \brief       Configures the controller to trigger the Pps single pulse on the given time.
 *  \details     -
 *  \param[in]   CtrlIdx       Index of controller
 *  \param[in]   TimestampPtr  Pointer to the provided time stamp
 *  \return      E_NOT_OK - PPS signal trigger configuration failed
 *  \return      E_OK - PPS signal trigger configuration successful / not enabled
 *  \context     TASK
 *  \reentrant   TRUE - for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ArmPpsEventOnTime(
            uint8                                    CtrlIdx,
    P2CONST(Eth_TimeStampType, AUTOMATIC, AUTOMATIC) TimestampPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_MainFunction()
 *********************************************************************************************************************/
/*! \brief       MainFunction for hardware specific cyclic operations
 *  \details     -
 *  \context     TASK
 *  \synchronous TRUE
 *  \reentrant   FALSE
 *  \pre         -
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_MainFunction( void );

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

# ifndef ETH_30_TC3XX_UNIT_TEST /* COV_ETH_TEST_SUITE_UNIT_TESTS */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxPending(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_TxDescrRingProcIterType descrRingCount;
  boolean isTxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (descrRingCount = (Eth_30_Tc3xx_TxDescrRingProcIterType)Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); descrRingCount > Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx); descrRingCount--)
  {
    Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx = (uint8)(descrRingCount - 1u);

    /* #110 If any checked TX queue has pending TX frames */
    if (Eth_30_Tc3xx_LL_IsTxQueuePending(ctrlIdx, descrRingIdx) == TRUE)
    {
      /* #1110 Return that a TX event is pending */
      isTxPend = TRUE;
    }
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsTxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQueuePending(
  uint8 ctrlIdx,
  Eth_30_Tc3xx_TxDescrRingProcIterType descrRingIdx)
{
  boolean isTxPend = FALSE;
  Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType curTxDescrIdx = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(descrRingIdx)
                                                               + Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx);

  /* PRQA S 3415 3 */ /* MD_Eth_30_Tc3xx_3415 */
  /* #10 Check if next descriptor to process is passed to driver already */
  if ((Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, descrRingIdx, curTxDescrIdx) == TRUE) &&
      (Eth_30_Tc3xx_GetTxReadyOfTxDescrState(curTxDescrIdx) == ETH_30_TC3XX_DESCRIPTOR_READY))
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor only when VLAN-ID based frame queuing is disabled,
     *      when VLAN-ID based frame queuing is enabled, the DMA Idx is retained and only the corresponding
     *      descriptor ring is processed and not based on Tx event. */
    if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
    {
      Eth_30_Tc3xx_SetTxEvent(ctrlIdx, descrRingIdx);
    }
    isTxPend = TRUE;
  }

  return isTxPend;
} /* Eth_30_Tc3xx_LL_IsTxQueuePending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxPending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxPending(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_RxDescrRingProcIterType descrRingCount;
  boolean isRxPend = FALSE;

  /* #10 Iterate over all used queues */
  for (descrRingCount = (Eth_30_Tc3xx_RxDescrRingProcIterType)Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx); descrRingCount > Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx); descrRingCount--)
  {
    uint8 queueIdx = (uint8)(descrRingCount - 1u);

    /* #110 If any checked RX queue has pending RX frames */
    if (Eth_30_Tc3xx_LL_IsRxQueuePending(ctrlIdx, queueIdx) == TRUE)
    {
      /* #1110 Return that a RX event is pending */
      isRxPend = TRUE;
    }
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxPending() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_IsRxQueuePending
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQueuePending(
    uint8 ctrlIdx,
    Eth_30_Tc3xx_RxDescrRingProcIterType descrRingIdx)
{
  boolean isRxPend = FALSE;
  Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType curRxDescrIdx = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(descrRingIdx)
                                               + Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx);

  /* #10 Check if next descriptor to process is passed to driver already */
  if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, descrRingIdx, curRxDescrIdx) == TRUE)
  {
    /* #110 Is passed, set respective events for the core and signal the caller that he should trigger a re-check
     *      after processing of the checked descriptor only when VLAN-ID based frame queuing is disabled because,
     *      when VLAN-ID based frame queuing is enabled, the DMA Idx is retained and the only the corresponding
     *      descriptor ring is processed and not based on Rx event. */
    if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
    {
      Eth_30_Tc3xx_SetRxEvent(ctrlIdx, descrRingIdx);
    }
    isRxPend = TRUE;
  }

  return isRxPend;
} /* Eth_30_Tc3xx_LL_IsRxQueuePending() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeRxDescriptor(
  uint8                                      ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufIdx)
{
  /* #10 Write buffer address to descriptor */
  P2VAR(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxDescr = Eth_30_Tc3xx_GetAddrRxDescr(descrIdx);
  Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType rxBufOffset = Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(descrRingIdx) +
       (rxBufIdx * Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(descrRingIdx)) +
      ETH_30_TC3XX_ALIGN_PADDING;

  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES0_IDX] = ((uint32) Eth_30_Tc3xx_GetAddrRxBuffer(rxBufOffset));   /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0ul;                                                    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0ul;                                                    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

/* #20 Set descriptor as owned by DMA, enable interrupt on completion */
  rxDescr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_RX3_DESC_OWN |                    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                         ETH_30_TC3XX_RX3_DESC_IOC |
                                                         ETH_30_TC3XX_RX3_DESC_BUF1V);

  /* #30 Initialize context descriptor to be able to capture timestamps */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES0_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES1_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES2_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  rxDescr->RxDescrWord[ETH_30_TC3XX_CNTXT_DES3_IDX] = (uint32)ETH_30_TC3XX_RX3_DESC_OWN;                /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_InitializeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitializeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitializeTxDescriptor(
  uint8                               ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(descrIdx);

  /* #10 Reset TX descriptor, set as owned by driver. No context descriptor needed for TX */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES1_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = 0ul;                                              /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_InitializeTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(
  uint8 ctrlIdx)
{
  uint8_least queueIdx;
  /* #10 Use queue count according to configuration - TX/RX descriptor number is always equal to each other */
  uint8_least queueCount = (uint8_least)Eth_30_Tc3xx_GetSizeOfTxDescrRingProc();

  /* #20 Iterate over used queues */
  for (queueIdx = 0u; queueIdx < queueCount; queueIdx++)
  {
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescRingLen;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescStartAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetRxDescTailAddr;
    Eth_30_Tc3xx_RegOffsetType regOffsetTxDescTailAddr;

    /* #30 Get TX/RX descriptor counts and addresses */
    uint16 rxDescCount = Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(queueIdx) - Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(queueIdx);
    uint16 txDescCount = Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(queueIdx) - Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(queueIdx);

    /* PRQA S 0306 3 */ /* MD_Eth_30_Tc3xx_0306 */
    uint32 rxDescAddr = (uint32) Eth_30_Tc3xx_GetAddrRxDescr(Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(queueIdx));
    uint32 txDescAddr = (uint32) Eth_30_Tc3xx_GetAddrTxDescr(Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(queueIdx));
    uint32 rxDescLastAddr = (uint32) Eth_30_Tc3xx_GetAddrRxDescr(Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(queueIdx));

    switch ((uint8)queueIdx)
    {
    case ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
      break;
    case ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
      break;
    default:
      regOffsetRxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_RING_LEN;
      regOffsetTxDescRingLen   = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_RING_LEN;
      regOffsetRxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_LIST_ADDR;
      regOffsetTxDescStartAddr = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_LIST_ADDR;
      regOffsetRxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
      regOffsetTxDescTailAddr  = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
    }

    /* #40 Announce ring length to hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_RX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)((2u * rxDescCount) - 1u)); /* -1 described in manual */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescRingLen, ETH_30_TC3XX_REG_DMA_CHN_TX_DESC_RING_LEN &
                            (Eth_30_Tc3xx_RegWidthType)(txDescCount - 1u)); /* -1 described in manual */

    /* #50 Announce descriptor ring to the hardware */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescStartAddr, rxDescAddr);
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescStartAddr, txDescAddr);

    /* #60 RX Tail Pointer points to the last descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetRxDescTailAddr, rxDescLastAddr);

    /* #70 TX Tail Pointer points to the first descriptor */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffsetTxDescTailAddr, txDescAddr);
  }
} /* Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_InitDescriptorStateVariables
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_InitDescriptorStateVariables(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_InitDescriptorStateVariables() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnableMiiAccess
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMiiAccess(
  uint8 ctrlIdx)
{
  /* Register is writable in supervisor mode only and is ENDINIT protected */
  Appl_UnlockEndinit();

  /* #10 Delete Disable Request Bit in ETH_CLC register - otherwise module is not active */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_CLC, 0ul);

  /* #20 configure MII mode and pin muxing configuration */
  Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL,
                                   Eth_30_Tc3xx_GetPinRoutingOfEthCtrlTc3xx(ctrlIdx));

  Appl_LockEndinit();
} /* Eth_30_Tc3xx_LL_EnableMiiAccess() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetCounters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetCounters(
  uint8 ctrlIdx)
{
  /* #10 Reset statistic counters */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_CNTRL, ETH_30_TC3XX_REG_MMC_CNTRL_RST);
} /* Eth_30_Tc3xx_LL_ResetCounters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
          uint8                                                                   ctrlIdx,
          Eth_30_Tc3xx_TxDescrHandlingIterType                                    descrRingIdx,
          Eth_30_Tc3xx_TxDescrIterType                                            descrIdx,
          Eth_30_Tc3xx_TxBufferStateIterType                                      bufIdx,
          uint16                                                                  lenByte,
  P2CONST(uint8,                              AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bufPtr)
{
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(descrIdx);

  /* #10 Set buffer address, interrupt on completion, first + last descriptor */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX] = (uint32)(bufPtr);                       /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  txDescr->TxDescrWord[ETH_30_TC3XX_DES2_IDX] = (uint32)(ETH_30_TC3XX_TX2_DESC_IOC |    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                        (ETH_30_TC3XX_TX2_DESC_BUF1_LEN_MASK & lenByte));

  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] = (uint32)(ETH_30_TC3XX_TX3_DESC_FD |     /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                         ETH_30_TC3XX_TX3_DESC_LD |
                                                        (ETH_30_TC3XX_TX3_DESC_FL_MASK & (lenByte +
                                                                                          ETH_30_TC3XX_HDR_LEN_BYTE)));

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeTxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_RechargeTxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  /* #10 Reset PTP descriptor flag */
  Eth_30_Tc3xx_GetAddrTxDescr(descrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] &=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
      (uint32)~ETH_30_TC3XX_TX2_DESC_TTSE;

  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  /* #10 Enable checksum offloading for IPv4-Header */
  Eth_30_Tc3xx_GetAddrTxDescr(descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
      (ETH_30_TC3XX_TX3_DESC_IP_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);

  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  /* #10 Enable transport protocol offloading for this descriptor */
  Eth_30_Tc3xx_GetAddrTxDescr(descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |=    /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
      (ETH_30_TC3XX_TX3_DESC_TRANSPORT_OFFLOAD << ETH_30_TC3XX_TX3_DESC_CIC_SHIFT);

  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_TriggerTransmission
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_TriggerTransmission(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset;
  P2VAR(Eth_30_Tc3xx_TxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txDescr =
      Eth_30_Tc3xx_GetAddrTxDescr(descrIdx);

  /* #10 Set descriptor as owned by DMA */
  txDescr->TxDescrWord[ETH_30_TC3XX_DES3_IDX] |= ETH_30_TC3XX_TX3_DESC_OWN;   /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */

  /* #20 Calculate next tail pointer address with regard to wraparound */
  if (descrIdx < (Eth_30_Tc3xx_GetDescrNumOfTxBufferHandling(descrRingIdx) - 1u))
  {
    descrIdx++;
  }
  else
  {
    descrIdx = 0u;
  }
  txDescr = Eth_30_Tc3xx_GetAddrTxDescr(descrIdx);

  /* #30 Set tail pointer to start transmission depending on the used descriptor ring index */
  if (descrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_DESC_TAIL_PTR;
  }
  else if (descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_DESC_TAIL_PTR;
  }
  else if (descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_DESC_TAIL_PTR;
  }
  /* PRQA S 0303 1 */ /* MD_Eth_30_Tc3xx_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)(&(txDescr->TxDescrWord[ETH_30_TC3XX_DES0_IDX])));
} /* Eth_30_Tc3xx_LL_TriggerTransmission() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx,
  Eth_30_Tc3xx_TxBufferStateIterType   bufIdx)
{

  /* #10 Enable timestamping for the given descriptor */
  Eth_30_Tc3xx_GetAddrTxDescr(descrIdx)->TxDescrWord[ETH_30_TC3XX_DES2_IDX] |=        /* SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01 */
                                                                            ETH_30_TC3XX_TX2_DESC_TTSE;

  ETH_30_TC3XX_DUMMY_STATEMENT(bufIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnableMac(
  uint8 ctrlIdx)
{

  /* #10 Enable MAC */
   Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_PMT_CTRL, ETH_30_TC3XX_REG_PMT_CTRL_PWR_DOWN);

  /* #20 Enable frame transmission and reception in DMA module */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  /* #30 If QoS/VLAN_ID based frame queuing feature is enabled configure DMA (transmission/reception) channes for all
   *     descriptor rings */
  if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }

    if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
  }

  /* #40 Enable frame transmission and reception in MAC */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_EnableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTransmissionComplete
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTransmissionComplete( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32_least hwLoopTimeout;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ0 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ1 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ2 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValTxQ3 = 0;

  for(hwLoopTimeout = 0u; hwLoopTimeout < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); hwLoopTimeout++)
  {
    /* #10 Read all used MTL_TXQi_DEBUG registers (default TXQ0, with QoS/VLAN-ID based frame queuing all available) */
    regValTxQ0 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_DEBUG);
    if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      regValTxQ1 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_DEBUG);

      if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
         regValTxQ2 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_DEBUG);
      }
      if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
         regValTxQ3 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_DEBUG);
      }
    }

    /* #20 Check the appropriate bits if transmission is complete */
    if(((regValTxQ0 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ1 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ2 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ3 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TRCSTS_MASK) != ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_READ_STATE) &&
       ((regValTxQ0 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ1 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ2 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY)      &&
       ((regValTxQ3 & ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_TXQ_EMPTY))
    {
      /* #210 Set return value to E_OK if completed for every TX queue, 
       *      otherwise check again if timeout cycle counter not exceeded */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_LL_IsTransmissionComplete() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem( /* PRQA S 3219 */ /* MD_Eth_30_Tc3xx_3219 */
    uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_NOT_OK;
  uint32_least hwLoopTimeout;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ0 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ1 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ2 = 0;
  volatile Eth_30_Tc3xx_RegWidthType regValRxQ3 = 0;

  for(hwLoopTimeout = 0u; hwLoopTimeout < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); hwLoopTimeout++)
  {
    /* #10 Read all used MTL_RXQi_DEBUG registers (default RXQ0, with QoS/VLAN-ID based frame queuing all available) */
    regValRxQ0 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_DEBUG);
    if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      regValRxQ1 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_DEBUG);
      if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
         regValRxQ2 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_DEBUG);
      }
      if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
         regValRxQ3 = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_DEBUG);
      }
    }

    /* #20 Check the appropriate bits if data in Rx FIFO is transferred to system memory */
    if(((regValRxQ0 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ1 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ2 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY) &&
       ((regValRxQ3 & ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK) == ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_RXQ_EMPTY))
    {
      /* #210 Set return value to E_OK if data is transferred to system memory,
       *      otherwise check again if timeout cycle counter not exceeded */
      retVal = E_OK;
      break;
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisableMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisableMac(
  uint8 ctrlIdx)
{
  /* #10 Disable frame transmission in DMA module */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_TX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);

  if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
    if(Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
        Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_TX_CNTRL,
                                           ETH_30_TC3XX_REG_DMA_CHN_TX_CNTRL_ST);
    }
  }

  /* #20 Only continue if previous frame transmissions completed within timeout */
  if(Eth_30_Tc3xx_LL_IsTransmissionComplete(ctrlIdx) == E_OK)
  {
    /* #210 Disable the MAC transmitter and receiver */
    Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);

    /* #220 Only continue if data in Rx Fifo was transfered within timeout */
    if(Eth_30_Tc3xx_LL_IsRxFifoTransferredToSystem(ctrlIdx) == E_OK)
    {
      /* #2210 Disable frame reception in DMA module */
      Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_CNTRL, ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
      if(Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
      {
        Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_CNTRL,
                                               ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
            Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_CNTRL,
                                               ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        }
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
            Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_CNTRL,
                                               ETH_30_TC3XX_REG_DMA_CHN_RX_CNTRL_SR);
        }
      }
    }
  }
} /* Eth_30_Tc3xx_LL_DisableMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMacEnabled
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE)  Eth_30_Tc3xx_LL_IsMacEnabled(
  uint8 ctrlIdx)
{
  /* #10 Return status of MAC transmission / reception enabled bits */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_CFG, ETH_30_TC3XX_REG_CFG_RE_TE);
} /* Eth_30_Tc3xx_LL_IsMacEnabled() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMacAddressToRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMacAddressToRegister(
  uint8                                ctrlIdx,
  P2CONST(uint8, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr)
{
  /* #10 Write Mac address to registers */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ADDR0_HIGH,
    (uint32)((uint32)macAddrPtr[5] <<  8u) |
            ((uint32)macAddrPtr[4] <<  0u) );
  Eth_30_Tc3xx_Reg_Write(ctrlIdx,  ETH_30_TC3XX_REG_OFFS_ADDR0_LOW,
    (uint32)((uint32)macAddrPtr[3] << 24u) |
            ((uint32)macAddrPtr[2] << 16u) |
            ((uint32)macAddrPtr[1] <<  8u) |
            ((uint32)macAddrPtr[0] <<  0u) );
} /* Eth_30_Tc3xx_LL_WriteMacAddressToRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PreResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PreResetMac(
  uint8 ctrlIdx)
{
  /* #10 Check if MAC is enabled */
  if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
  {
    /* #110 If MAC is enabled, disable MAC first for a following reset */
    Eth_30_Tc3xx_LL_DisableMac(ctrlIdx);
  }

} /* Eth_30_Tc3xx_LL_PreResetMac() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WaitfSPBCycles
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WaitfSPBCycles(
    uint8 ctrlIdx,
    uint8 fspbcycles )
{
  uint8_least fSPBCyclesCounter;
  Eth_30_Tc3xx_RegWidthType regVal;
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Provides the necessary fspB cycles delay */
  for (fSPBCyclesCounter = 0; fSPBCyclesCounter <= fspbcycles; fSPBCyclesCounter++)
  {
    regVal = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_HW_FEATURE0);
    ETH_30_TC3XX_DUMMY_STATEMENT(regVal); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  }
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask )
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Tc3xx_RegWidthType mtlRxq0Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq1Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq2Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlRxq3Debugbits;

  /* #10 Read RxQiDebug register bits */
  mtlRxq0Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ0_DEBUG,
                                                        debugRegMask);
  mtlRxq1Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ1_DEBUG,
                                                        debugRegMask);
  mtlRxq2Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ2_DEBUG,
                                                        debugRegMask);
  mtlRxq3Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_RXQ3_DEBUG,
                                                        debugRegMask);
  if((mtlRxq0Debugbits == 0ul) && (mtlRxq1Debugbits == 0ul) &&
     (mtlRxq2Debugbits == 0ul) && (mtlRxq3Debugbits == 0ul))
  {
    /* #110 Return E_OK on RxQi registers are empty */
    retVal = E_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(
    uint8 ctrlIdx,
    uint32 debugRegMask )
{
  Std_ReturnType retVal = E_NOT_OK;
  Eth_30_Tc3xx_RegWidthType mtlTxq0Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq1Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq2Debugbits;
  Eth_30_Tc3xx_RegWidthType mtlTxq3Debugbits;

  /* #10 Read TxQiDebug register bits */
  mtlTxq0Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ0_DEBUG,
                                                        debugRegMask);
  mtlTxq1Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ1_DEBUG,
                                                        debugRegMask);
  mtlTxq2Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ2_DEBUG,
                                                        debugRegMask);
  mtlTxq3Debugbits = Eth_30_Tc3xx_Reg_ReadBits(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MTL_TXQ3_DEBUG,
                                                        debugRegMask);

  if((mtlTxq0Debugbits == 0ul) && (mtlTxq1Debugbits == 0ul) &&
     (mtlTxq2Debugbits == 0ul) && (mtlTxq3Debugbits == 0ul))
  {
    /* #110 Return E_OK on TxQi registers are empty */
    retVal = E_OK;
  }
  return retVal;
}

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetMac
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
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
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetMac(
  uint8 ctrlIdx)
{
  Eth_30_Tc3xx_RegWidthType rpsxStatusBit;
  Eth_30_Tc3xx_RegWidthType tpsxStatusBit;
  Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType miiModeType = Eth_30_Tc3xx_GetEthCtrlMiiInterfaceOfEthCtrlTc3xx(ctrlIdx);
  /* #10 Check the RPSx and TPSx status bit fields in register DMA_DEBUG_STATUS0/1 (Finish active transfers and make
   *     sure that transmitters and receivers are set to stopped state is done -> MAC is already disabled by previous
   *     LL_PreResetMac() function call from the driver core part) */
  rpsxStatusBit = Eth_30_Tc3xx_Reg_ReadBits(
         ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS0, ETH_30_TC3XX_REG_DMA_DEBUG_STATUS0_TPS_RPS_MASK);

  tpsxStatusBit = Eth_30_Tc3xx_Reg_ReadBits(
         ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_DEBUG_STATUS1, ETH_30_TC3XX_REG_DMA_DEBUG_STATUS1_TPS_RPS_MASK);
  if ((rpsxStatusBit == 0ul) && (tpsxStatusBit == 0ul))
  {
    const uint8 fSPBCycles70 = 70ul;
    uint8 isTxQiRegempty;
    uint8 isRxQiRegempty;

    /* #110 It may be required to wait 70 fSPB cycles after the last reset before checking if RXQSTS in MTL_RXQ0_DEBUG
     *      and MTL_RXQi_DEBUG are zero (one register read of ETH_30_TC3XX_REG_OFFS_HW_FEATURE0 takes more than one fSPB
     *      cycle of time) */
    Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles70);

    /* #120 Check that content all MTL_RXQi_DEBUG and MTL_TXQi_DEBUG registers is equal to zero */
    isRxQiRegempty = Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_ALL_NOT_RESERVED_MASK);
    isTxQiRegempty = Eth_30_Tc3xx_LL_IsTxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_TXQ_X_DEBUG_ALL_NOT_RESERVED_MASK);

    if ((isTxQiRegempty == E_OK) && (isRxQiRegempty == E_OK))
    {
      uint32_least hwLoopTimeout = 0ul;
      Std_ReturnType tmpVal = E_OK;
      /* #1210 Globally disable interrupts
       *       (No Eth-ISR pending/running at the moment this function is called) */
      Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_INT_EN, 0ul);
      Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH0_INT_EN, 0ul);
      if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
      {
        Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH1_INT_EN, 0ul);
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_2_QUEUES_CONFIGURED){
           Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH2_INT_EN, 0ul);
        }
        if(Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(ctrlIdx) > ETH_30_TC3XX_LL_QOS_3_QUEUES_CONFIGURED){
            Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_CH3_INT_EN, 0ul);
        }
      }

      /* #1220 Deactivate Endinit protection */
      Appl_UnlockEndinit();

      /* #1230 If RGMII mode is used ensure GETH_GPCTL.EPR = 000B and GETH_SKEWCTL = 0x0 */
      if(miiModeType == ETH_RGMII_MODE)
      {
        Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL, 0ul);
        Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_SKEWCTL, 0ul);
      }
      /* #1240 Apply a kernel reset to the GETH module:
       *       Write to corresponding RST bits of KRST0/1 registers to request a kernel reset. */
      Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER0,
                                                ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RST);
      Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER1,
                                                ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER1_RST);

      /* #1250 Check if kernel reset is finished */
      while (Eth_30_Tc3xx_Reg_ReadBits_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_REGISTER0,
                                                          ETH_30_TC3XX_REG_KERNEL_RESET_REGISTER0_RSTSTAT) == 0ul)
      {
        /* still busy */
        if (hwLoopTimeout > Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx))
        {
          ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
          tmpVal = E_NOT_OK;
          break;
        }
        hwLoopTimeout++;
      }

      /* #1260 The reset status flag KRST0.RSTSTAT may be cleared afterwards by writing to bit CLR in the KRSTCLR
       *       register */
      Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR,
                                                ETH_30_TC3XX_REG_OFFS_KERNEL_RESET_STATUS_CLEAR_CLR);

      /* #1270 Re-activate Endinit protection. */
      Appl_LockEndinit();

      /* #1280 Continue further reset procedure only if kernel reset was successful */
      if (tmpVal == E_OK)
      {
        const uint8 fSPBCycles4  =  4ul;
        const uint8 fSPBCycles35 = 35ul;

        /* #12810 Wait 35 fSPB cycles */
        Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles35);
        /* #12820 Check the Mii Mode is  MII/RMII mode */
        if((miiModeType == ETH_MII_MODE) || (miiModeType == ETH_RMII_MODE))
        {
          /* #128210 Wait again 35 fSPB cycles ( making it 70fSPB for RMII and MII mode) */
          Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles35);
          /* #128220 Check if RXQSTS in MTL_RXQ0_DEBUG and MTL_RXQi_DEBUG are zero */
          tmpVal = Eth_30_Tc3xx_LL_IsRxQiDebugRegEmpty(ctrlIdx, ETH_30_TC3XX_REG_MTL_RXQ_X_DEBUG_PRXQ_RXQSTS_MASK);
        }
        /* #12830 Continue if RXQSTS in MTL_RXQ0_DEBUG and MTL_RXQi_DEBUG are empty  */
        if(tmpVal == E_OK)
        {
          /* #128310 Set GETH_GPCTL.EPR and GETH_SKEWCTL if required (GETH_SKEWCTL will be set afterwards by the
           *         default register initialization) */
          Appl_UnlockEndinit();
          Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, ETH_30_TC3XX_REG_OFFS_ETH_GPCTL,
                                                    Eth_30_Tc3xx_GetPinRoutingOfEthCtrlTc3xx(ctrlIdx));
          Appl_LockEndinit();

          /* #128320 Perform a software reset by writing to the DMA_MODE.SWR bit */
          Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE, ETH_30_TC3XX_REG_DMA_MODE_SWR);

          /* #128330 Wait 4 fSPB cycles */
          Eth_30_Tc3xx_LL_WaitfSPBCycles(ctrlIdx, fSPBCycles4);
        }
        /* #12840 Then check if DMA_MODE.SWR = 0B -> this will be done in the consecutive
         *        LL_IsResetMacFinished() function call from the driver core part */
      }
    }
  }
}  /* Eth_30_Tc3xx_LL_ResetMac() */ /* PRQA S 6010, 6030, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsResetMacFinished
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsResetMacFinished(
  uint8 ctrlIdx)
{
  /* #10 Return status of MAC reset bit */
  return (boolean)((Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_DMA_MODE) &
                                                   ETH_30_TC3XX_REG_DMA_MODE_SWR) == 0ul);
} /* Eth_30_Tc3xx_LL_IsResetMacFinished() */

#  if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_EnablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_EnablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Enable promiscuous mode */
  Eth_30_Tc3xx_Reg_SetBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_EnablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_DisablePromiscuousMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_DisablePromiscuousMode(
  uint8 ctrlIdx)
{
  /* #10 Disable promiscuous mode */
  Eth_30_Tc3xx_Reg_ClearBitMask(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_PACKET_FILTER, ETH_30_TC3XX_REG_PACKET_FILTER_PR);
} /* Eth_30_Tc3xx_LL_DisablePromiscuousMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CloseAllMulticastFilters
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CloseAllMulticastFilters(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_CloseAllMulticastFilters() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetMulticastFilteringMode
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetMulticastFilteringMode(
  uint8 ctrlIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_SetMulticastFilteringMode() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister(
  uint8  ctrlIdx,
  uint32 bucketMask)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(bucketMask); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(
          uint8                                        ctrlIdx,
  P2CONST(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) macAddrPtr,
    P2VAR(uint8,   AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) hashPtr,
    P2VAR(boolean, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) isUpperRegPtr,
    P2VAR(uint32,  AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) bucketMaskPtr)
{
  /* #10 Return dummy values */
  *hashPtr = 0u;                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  *bucketMaskPtr = 0ul;                                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  *isUpperRegPtr = FALSE;                                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  ETH_30_TC3XX_DUMMY_STATEMENT(macAddrPtr); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
} /* Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash() */
#  endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_WriteMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_WriteMiiTrigger(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_WRITE |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(ctrlIdx) & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a write command with the prepared values */
  /* PRQA S 0306 2 */ /* MD_Eth_30_Tc3xx_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA, ((uint32)regVal) & ETH_30_TC3XX_REG_MDIO_DATA_MASK);
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_WriteMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ReadMiiTrigger
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ReadMiiTrigger(
  uint8 ctrlIdx,
  uint8 trcvIdx,
  uint8 regIdx)
{
  /* #10 Prepare MII register value */
  uint32 ctrlRegVal = ETH_30_TC3XX_REG_MDIO_ADDR_GB | ETH_30_TC3XX_REG_MDIO_ADDR_READ |
  ((((uint32)regIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_RDA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_RDA_MASK) |
  ((((uint32)trcvIdx) << ETH_30_TC3XX_REG_MDIO_ADDR_PA_SHIFT) & ETH_30_TC3XX_REG_MDIO_ADDR_PA_MASK) |
  (Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(ctrlIdx) & ETH_30_TC3XX_REG_MDIO_ADDR_CR_MASK);

  /* #20 Trigger a read operation */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ctrlRegVal);
} /* Eth_30_Tc3xx_LL_ReadMiiTrigger() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetReadMiiResult
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetReadMiiResult(
        uint8                                       ctrlIdx,
  P2VAR(uint16, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) regValPtr)
{
  /* #10 Read back the result of a Mii read operation */
  *regValPtr = (uint16)(Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_DATA) &     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                                                       ETH_30_TC3XX_REG_MDIO_DATA_MASK);
} /* Eth_30_Tc3xx_LL_GetReadMiiResult() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsMiiOperationPending
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsMiiOperationPending(
  uint8 ctrlIdx)
{
  /* #10 Return status of MII interface busy bit */
  return Eth_30_Tc3xx_Reg_IsBitMaskSet(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MDIO_ADDR, ETH_30_TC3XX_REG_MDIO_ADDR_GB);
} /* Eth_30_Tc3xx_LL_IsMiiOperationPending() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetTxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetTxEvents(
  uint8 ctrlIdx)
{
  /* #10 Trigger Tx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsTxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetTxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */

  /* #10 Return status of OWN bit in Rx descriptor */
  return (boolean)((ETH_30_TC3XX_RX3_DESC_OWN &
           Eth_30_Tc3xx_GetAddrRxDescr(descrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX]) == 0ul);

} /* Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_TxDescrIterType         descrIdx)
{

  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */

  /* #10 Return status of OWN bit in Tx descriptor */
  return (boolean)(((uint32)(ETH_30_TC3XX_TX3_DESC_OWN &
          Eth_30_Tc3xx_GetAddrTxDescr(descrIdx)->TxDescrWord[ETH_30_TC3XX_DES3_IDX])) == 0ul);
} /* Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_IsErrorInRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx)
{
  boolean errorInDescriptor;
  uint16 FrameLen = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(ctrlIdx, descrRingIdx, descrIdx);
  CONSTP2CONST(Eth_30_Tc3xx_RxDescriptorType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxDescPtr = Eth_30_Tc3xx_GetAddrRxDescr(descrIdx);

  /* #10 Check whether descriptor was split into more than one descriptor (FD+LD not set, e.g. because frame is larger
   *     than the default HW limit of 1518/1522(VLAN tagged) bytes for normal frames or a configured lower limit in
   *     the DMA_CHi_RX_CONTROL register) or error flags are set */
  if(((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_FD)   == 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_LD)   == 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_ES)   != 0ul) ||
     ((rxDescPtr->RxDescrWord[ETH_30_TC3XX_DES3_IDX] & ETH_30_TC3XX_RX3_DESC_CTXT) != 0ul))
  {
    errorInDescriptor = TRUE;
  }
  /* #20 Check whether received frame size exceeds configured frame size because of buffer alignment and size
   *     requirements (e.g. DMA_CHi_RX_CONTROL register with fields RBSZ_13_y and RBSZ_x_0 the actual buffer size in
   *     the memory can be larger so these frames have to blocked by software!) */
  else if((FrameLen + ETH_30_TC3XX_FCS_LEN_BYTE)
  /* FCS not copied to memory / included in FrameLen therefore adding constant FCS length value here! */
                   > ( Eth_30_Tc3xx_GetMaxFrameSizeOfRxBufferHandling(descrRingIdx)))
  {
    errorInDescriptor = TRUE;
  }
  else
  {
    errorInDescriptor = FALSE;
  }

  return errorInDescriptor;
} /* Eth_30_Tc3xx_LL_IsErrorInRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_SetRxEvents
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_SetRxEvents(
  uint8 ctrlIdx)
{
  /* #10 Trigger Rx event evaluation */
  (void)Eth_30_Tc3xx_LL_IsRxPending(ctrlIdx);
} /* Eth_30_Tc3xx_LL_SetRxEvents() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RearmMacForReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RearmMacForReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx)
{
  /* #10 Nothing to do here */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
} /* Eth_30_Tc3xx_LL_RearmMacForReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_RechargeRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_RechargeRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx)
{
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx;

  /* #10 Retrieve the mapped buffer of the descriptor to be recharged */
  bufIdx = Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(descrIdx);

  /* #20 Recharge the descriptor by initializing it */
  Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, descrRingIdx, descrIdx, bufIdx);
} /* Eth_30_Tc3xx_LL_RechargeRxDescriptor() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx)
{
  Eth_30_Tc3xx_RegOffsetType regOffset;

  if(descrRingIdx == ETH_30_TC3XX_LL_HIGH_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH3_RX_DESC_TAIL_PTR;
  }
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_1_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH2_RX_DESC_TAIL_PTR;
  }
  else if(descrRingIdx == ETH_30_TC3XX_LL_MID_0_PRIO_QUEUE_IDX)
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH1_RX_DESC_TAIL_PTR;
  }
  else
  {
    regOffset = ETH_30_TC3XX_REG_OFFS_DMA_CH0_RX_DESC_TAIL_PTR;
  }

  /* #10 Set tail pointer to next descriptor depending on current descrRingIdx */
  /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0303 */
  Eth_30_Tc3xx_Reg_Write(ctrlIdx, regOffset, (uint32)
      Eth_30_Tc3xx_GetAddrRxDescr(descrIdx));
} /* Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(
  uint8                                ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         descrIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(descrRingIdx); /* PRQA S 3112 3199 */ /* MD_MSR_14.2 */

  /* #10 Extract length of a received frame from a descriptor */
  return (uint16)(Eth_30_Tc3xx_GetAddrRxDescr(descrIdx)->RxDescrWord[ETH_30_TC3XX_DES3_IDX] &
                    ETH_30_TC3XX_RX3_DESC_FL_MASK);
} /* Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetMaxCounterOffset
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(uint16, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetMaxCounterOffset(
  uint8 ctrlIdx)
{
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Return max counter offset */
  return ETH_30_TC3XX_MMC_COUNTER_MAX_OFFSET;
} /* Eth_30_Tc3xx_LL_GetMaxCounterOffset() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetCounterValue
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetCounterValue(
        uint8                                       ctrlIdx,
  Eth_30_Tc3xx_RegOffsetType                        counterOffset,
  P2VAR(uint32, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) counterValPtr)
{
  /* #10 Get statistics register with related offset */
  Eth_30_Tc3xx_RegOffsetType regOffset = ETH_30_TC3XX_MMC_COUNTER_BASE_OFFSET + counterOffset;
  (*counterValPtr) = Eth_30_Tc3xx_Reg_Read(ctrlIdx, regOffset);                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetCounterValue() */

#  if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetRxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetRxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) rxStatsPtr)
{
  /* #10 Read the reception statistics counter values */
  rxStatsPtr->RxStatsDropEvents =                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G));
  rxStatsPtr->RxStatsOctets =                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OCTETS_GB);
  rxStatsPtr->RxStatsPkts =                                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES);
  rxStatsPtr->RxStatsBroadcastPkts =                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_BROADCAST_FRAMES);
  rxStatsPtr->RxStatsMulticastPkts =                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_MULTICAST_FRAMES);
  rxStatsPtr->RxStatsCrcAlignErrors =                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_CRC_ERROR)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_ALIGN));
  rxStatsPtr->RxStatsUndersizePkts =                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNDERSIZE_G);
  rxStatsPtr->RxStatsOversizePkts =                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_OVERSIZE_G);
  rxStatsPtr->RxStatsFragments =                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_RUNT);
  rxStatsPtr->RxStatsJabbers =                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_JABBER);
  rxStatsPtr->RxStatsPkts64Octets =                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64);
  rxStatsPtr->RxStatsPkts65to127Octets =                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_64_TO_127);
  rxStatsPtr->RxStatsPkts128to255Octets =                                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_128_TO_255);
  rxStatsPtr->RxStatsPkts256to511Octets =                                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_256_TO_511);
  rxStatsPtr->RxStatsPkts512to1023Octets =                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_512_TO_1023);
  rxStatsPtr->RxStatsPkts1024to1518Octets =                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FRAMES_1024_TO_MAX);
  rxStatsPtr->RxUnicastFrames =                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
       Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_UNICAST_G_FRAMES);
  rxStatsPtr->RxStatsCollisions =                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
      (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_SINGLE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTI_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_LATE_COL)
     + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_EXC_COL));

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetRxStats() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_LL_GetTxStats
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetTxStats(
        uint8                                                ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, ETH_30_TC3XX_VAR_NOINIT) txStatsPtr)
{
  /* #10 Read the transmission statistics counter values */
  txStatsPtr->TxNumberOfOctets = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_OCTETS_GB);        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxNUcastPkts    = (Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_BROADCASTS_GB)     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                               + Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_MULTICASTS_GB));
  txStatsPtr->TxUniCastPkts    = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_TX_UNICASTS_GB);      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return E_OK;
} /* Eth_30_Tc3xx_LL_GetTxStats() */
#  endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#  if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(
        uint8                                                                       ctrlIdx,
  P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, AUTOMATIC, AUTOMATIC) readCtrValuePtr,
  P2VAR(boolean,                                              AUTOMATIC, AUTOMATIC) isHwCtrResetOnReadPtr)
{
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType rxDropCounterValue;

  *isHwCtrResetOnReadPtr = FALSE;                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #10 Retrieve the hardware counter of Rx frame drops due to insufficient Rx buffers */
  rxDropCounterValue = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL);

  /* #20 Check for the wrap around condition */
  if(rxDropCounterValue < Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx))
  {
    /* #210 Calculate the Rx frame drop counter wrt the reset value considerig the wrap arount correction */
    (*readCtrValuePtr) = (ETH_30_TC3XX_RX_FIFO_OVERFLOW_PACKETS_COUNT_MAX - Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx))    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                              + rxDropCounterValue;
  }
  else
  {
    /* #220 Calculate the Rx frame drop counter wrt the reset value */
    (*readCtrValuePtr) = (rxDropCounterValue - Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx));    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  return E_OK;
} /* Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter() */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(
  uint8 ctrlIdx)
{
  /* #10 Only Read is allowed and Reset is not supported by the Tc3xx. Thus, the current counter value is stored in a
   *     reset value variable and E_OK is send*/
  Eth_30_Tc3xx_SetDropInsuffRxBuffResetOfEthMeasDataCounterReset(ctrlIdx, Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MMC_RX_FIFO_OVFL));    /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */
  return E_OK;
} /* Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter() */
#  endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_PerformAdditionalHwConfig
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(
  uint8 ctrlIdx)
{
  Std_ReturnType retVal = E_OK;

/* #10 Perform VLAN-ID based frame queuing configuration if enabled */
#  if (ETH_30_TC3XX_ENABLE_VLANID_BASED_FRAME_QUEUING == STD_ON)

  Eth_30_Tc3xx_RegWidthType vlanTagDataVal;
  Eth_30_Tc3xx_RegWidthType vlanTagCtrlVal;
  uint8 vlanFilterIdx;
  uint16 vlanId;
  uint32 queueIdx;
  uint8 retryCountIdx;

  const Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrMapStartIdx = Eth_30_Tc3xx_GetVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(ctrlIdx);
  const Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdRxDescrMapEndIdx = Eth_30_Tc3xx_GetVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(ctrlIdx);


  for (vlanFilterIdx = vlanIdRxDescrMapStartIdx; vlanFilterIdx < vlanIdRxDescrMapEndIdx; vlanFilterIdx++)
  {
    retVal = E_NOT_OK;

    /* #110 Retrieve the VLAN ID and its corresponding queue mapping from configuration */
    vlanId = Eth_30_Tc3xx_GetVlanIdOfVlanIdRxDescrRingMap(vlanFilterIdx);
    queueIdx = (uint32)Eth_30_Tc3xx_GetQueueIndexOfVlanIdRxDescrRingMap(vlanFilterIdx);

    /* #120 Prepare MAC_VLAN_TAG_DATA register value with VLAN_ID filter information */
    vlanTagDataVal = ETH_30_TC3XX_MAC_VLAN_TAG_DATA_MASK;
    vlanTagDataVal |= (queueIdx << ETH_30_TC3XX_MAC_VLAN_TAG_DATA_DMACHN_SHIFT);
    vlanTagDataVal |= vlanId;

    /* #140 Write the VLAN-ID filter information to VLAN_TAG_DATA register */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_DATA, vlanTagDataVal);

    /* #150 Prepare MAC_VLAN_TAG_CONTROL register value */
    vlanTagCtrlVal = ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_MASK;
    vlanTagCtrlVal |= (vlanFilterIdx << ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OFS_SHIFT);
    vlanTagCtrlVal &= ~(ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_CT_MASK);
    vlanTagCtrlVal |= ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK;

    /* #160 Create VLAN ID Filter bank based on the filter info written to VLAN_TAG_DATA register */
    Eth_30_Tc3xx_Reg_Write(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_CTRL, vlanTagCtrlVal);

    /* #170 Wait for indirect write to be finished */
    for (retryCountIdx = 0u; retryCountIdx < Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx); retryCountIdx++ )
    {
      vlanTagCtrlVal = Eth_30_Tc3xx_Reg_Read(ctrlIdx, ETH_30_TC3XX_REG_OFFS_MAC_VLAN_TAG_CTRL);
      if ((vlanTagCtrlVal & ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK) != ETH_30_TC3XX_MAC_VLAN_TAG_CTRL_OB_MASK)
      {
        retVal = E_OK;
        break;
      }
    }

    if (retVal != E_OK)
    {
      break;
    }
  }
#  endif /* ETH_30_TC3XX_ENABLE_VLANID_BASED_FRAME_QUEUING */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
} /* Eth_30_Tc3xx_LL_PerformAdditionalHwConfig */

/**********************************************************************************************************************
 * Eth_30_Tc3xx_LL_MainFunction
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */ /* PRQA S 3219 1 */ /* MD_Eth_30_Tc3xx_3219 */
ETH_30_TC3XX_LL_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_LL_MainFunction( void )
{
  /* #10 Nothing to do here */
} /* Eth_30_Tc3xx_LL_MainFunction() */

# endif /* ETH_30_TC3XX_UNIT_TEST */

# define ETH_30_TC3XX_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ETH_30_TC3XX_LL_H */

/* Module-specific exclusive areas: */

/* module specific MISRA deviations:
  MD_Eth_30_Tc3xx_0306:
    Reason:     Descriptor word accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk because descriptor pointers are only available with 32 bit length
    Prevention: Covered by code review.
 */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_LL.h
 *********************************************************************************************************************/
