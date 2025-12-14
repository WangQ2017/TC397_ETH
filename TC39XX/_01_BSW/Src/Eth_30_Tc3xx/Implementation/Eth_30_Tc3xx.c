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
/*!        \file  Eth_30_Tc3xx.c
 *        \brief  Ethernet controller driver implementation
 *
 *      \details  Core part of the Ethernet controller driver implementation.
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

/*lint -e438 */ /* Suppress ID438 because Config pointer only used in Post-Build Variant */
/*lint -e506 */ /* Suppress ID506 due to MD_MSR_14.1 */
/*lint -e537 */ /* Suppress ID537 due to MD_MSR_19.1 */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#define ETH_30_TC3XX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_LL.h"
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
# include "Eth_30_Tc3xx_LL_TimeSync.h"
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
#include "Eth_30_Tc3xx_Cbk.h"
#include "EthIf_Cbk.h"
#if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
# include "NvM.h"
#endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
#if (ETH_30_TC3XX_DEM_ERROR_DETECT == STD_ON)
# include "Dem.h"
#endif /* ETH_30_TC3XX_DEM_ERROR_DETECT */

/**********************************************************************************************************************
 * DEFINE CHECKS
 *********************************************************************************************************************/

#if((ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX +0) < 1)
# error "The difference to the previous descriptor has to be defined for ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX!"
#endif

/**********************************************************************************************************************
 *  END OF DEFINE CHECKS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_LOCAL /* COV_ETH_COMPATIBILITY */
# define ETH_30_TC3XX_LOCAL                                            LOCAL
#endif

#ifndef ETH_30_TC3XX_LOCAL_INLINE /* COV_ETH_COMPATIBILITY */
# define ETH_30_TC3XX_LOCAL_INLINE                                     LOCAL_INLINE
#endif
/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
VAR(Eth_StateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ModuleInitialized;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

#define ETH_30_TC3XX_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! \brief      Checks whether the MAC address is the broadcast address
 *  \details    -
 *  \param[in]  macAddrPtr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't broadcast address
 *  \return     TRUE  - MAC address is broadcast address
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! \brief      Checks whether the MAC address is all-zero
 *  \details    -
 *  \param[in]  macAddrPtr  MAC address that shall be checked
 *  \return     FALSE - MAC address isn't all zero
 *  \return     TRUE  - MAC address is all zero
 *  \context    ANY
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
 **********************************************************************************************************************/
/*! \brief      Initializes the transmission and reception buffers, descriptors and structures
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \context    TASK
 *  \reentrant  TRUE for different Ethernet controllers
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a reception descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the reception descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxDescrRingPrevPos
 **********************************************************************************************************************/
/*! \brief      Retrieves the index of the previous descriptor in the given ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the reception descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]  currDescrIdx  Identifier of the current reception descriptor ring position the previous position
 *              shall be retrieved for 
 *              [range: 0 <= currDescrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different reception descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrIterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingPrevPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         currDescrIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! \brief      Increments the processing position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! \brief      Increments the free position in a transmission descriptor ring
 *  \details    -
 *  \param[in]  descrRingIdx  Identifier of the transmission descriptor ring
 *              [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfTxDescrHandling()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission descriptor rings
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! \brief          Checks if transmission buffer provision can be processed
 *  \details        Function performs a pre-check if TX buffer provision is possible.
 *  \param[in]      ctrlIdx  Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in,out]  lenPtr   Buffer to determine the requested length and the actual needed length of the buffer:
 *                           [in]  Length of the buffer as requested by the upper layer
 *                           [out] Length of the buffer needed due to other constraints like insertion of switch
 *                                 management data by the EthSwt driver
 *  \return         TRUE  - TX Buffer provision is possible
 *  \return         FALSE - TX Buffer provision is not possible, operation failed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different Ethernet controllers
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk
 **********************************************************************************************************************/
/*! \brief          Performs a pre-preparation of the buffer that shall be provided to the upper layer
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the transmission buffer segment
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                              [out] Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (adaption of position could be needed due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Actual length of the buffer segment
 *                              [out] Available length of the buffer segment
 *                                    (adaption of the actual length could be needed due to insertion of an additional
 *                                     header between MAC addresses an Ether Type like in a EthSwt management use case)
 *  \return         TRUE  - TX Buffer pre preparation is OK
 *  \return         FALSE - TX pre preparation operation failed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if triggering of transmission of a Ethernet frame is possible
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the transmission buffer segment
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (position could be shifted due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *                              [out] Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Available length of the buffer segment
 *                                    (actual length could be decreased due to insertion of an additional
 *                                     header between MAC addresses an Ether Type like in a EthSwt management use case)
 *                              [out] Actual length of the buffer segment
 *  \return         TRUE  - Frame transmission allowed
 *  \return         FALSE - Frame transmission not allowed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different transmission buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! \brief      Finishes the transmission triggering of a Ethernet frame
 *  \details    -
 *  \param[in]  ctrlIdx  Identifier of the Ethernet controller
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]  bufIdx   Identifier of the transmission buffer segment
 *              [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE for different transmission buffer segments
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
 **********************************************************************************************************************/
/*! \brief          Checks if reception of an Ethernet frame is allowed
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]      bufIdx      Identifier of the related RX buffer
 *                  [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \param[in,out]  dataPtr     Buffer provided to the upper layer later on:
 *                              [in]  Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame
 *                              [out] Pointer pointing to the Ether Type position of the resulting Ethernet frame
 *                                    (adaption of position could be needed due to insertion of an additional header
 *                                     between MAC addresses and Ether Type like in a EthSwt management use case)
 *  \param[in,out]  dataLenPtr  Length of the buffer provided to the upper layer later on:
 *                              [in]  Actual length of the Ethernet frame contained in the buffer
 *                              [out] Available length of the Ethernet frame contained in the buffer
 *                                    (adaption of the actual length of the Ethernet frame could be needed due to
 *                                     insertion of an additional header between MAC addresses an Ether Type like in
 *                                     a EthSwt management use case)
 *  \return         TRUE  - Frame reception allowed
 *  \return         FALSE - Frame reception not allowed
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE for different reception buffer segments
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! \brief         Finishes the reception of a Ethernet frame
 *  \details       -
 *  \param[in]     ctrlIdx  Identifier of the Ethernet controller
 *                 [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]     bufIdx   Identifier of the related RX buffer
 *                 [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \context       TASK|ISR1|ISR2
 *  \reentrant     TRUE for different transmission buffer segments
 *  \pre           -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx);

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidAlignment
 **********************************************************************************************************************/
/*! \brief      Check if all RX \ TX Descriptors and Buffers fulfill minimum alignment requirements.
 *  \details    -
 *  \param[out] ctrlIdxPtr  Identifier of the Ethernet controller in case alignment is not fulfilled and return
 *                          value is FALSE.
 *              [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return     TRUE  - Alignment of controller with index ctrlIdx is valid
 *  \return     FALSE - Alignment of controller with index ctrlIdx is invalid
 *  \context    TASK|ISR1|ISR2
 *  \reentrant  TRUE
 *  \pre        -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidAlignment(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ctrlIdxPtr);
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes an Ethernet controller
 *  \details     Function initializes a Ethernet controller and the related variables
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   cfgIdx   Identifier of the configuration (only 0 supported)
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ControllerInit(
  uint8 ctrlIdx,
  uint8 cfgIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ValidControllerInit
 **********************************************************************************************************************/
/*! \brief       Initializes a successfully reset Ethernet controller
 *  \details     Function performs the initialization steps for a successfully reset Ethernet controller and the
 *               corresponding variables so it is possible to set it in operation afterwards.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \return      E_NOT_OK - Initialization of Ethernet controller failed
 *  \return      E_OK - Ethernet controller initialized
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ValidControllerInit(
  uint8 ctrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetControllerMode
 **********************************************************************************************************************/
/*! \brief       Sets the operation mode of an Ethernet controller
 *  \details     Function sets the operation mode of the Ethernet controller so it is either turned off (no frame
 *               reception and transmission) or turned on (frames can be transmitted and received).
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ctrlMode  Operation mode that shall be applied:
 *                         ETH_MODE_DOWN - Ethernet controller shall be turned off
 *                         ETH_MODE_ACTIVE - Ethernet controller shall be turned on
 *  \return      E_NOT_OK - Operation mode couldn't be applied
 *  \return      E_OK - Operation mode successfully applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetControllerMode(
  uint8        ctrlIdx,
  Eth_ModeType ctrlMode);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetControllerMode
 **********************************************************************************************************************/
/*! \brief       Retrieves the current operation mode of an Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  ctrlModePtr  Operation mode retrieved
 *  \return      E_NOT_OK - Retrieval of operation mode failed
 *  \return      E_OK - Operation mode successfully retrieved
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetControllerMode(
        uint8                               ctrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) ctrlModePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetPhysAddr
 **********************************************************************************************************************/
/*! \brief       Retrieves the currently active MAC address of an Ethernet controller
 *  \details     -
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  physAddrPtr  Buffer of at least 6 byte to pass the MAC address
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetPhysAddr(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetPhysAddr
 *********************************************************************************************************************/
/*! \brief       Sets the MAC address of an Ethernet controller
 *  \details     Function sets the MAC address of an Ethernet controller. Dependent on the configuration of the "Write
 *               MAC address" feature the change is persisted in non-volatile RAM and also available after a power-
 *               cycle of the MCU.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   physAddrPtr  Buffer holding the MAC address that shall be applied
 *  \context     TASK
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         Module is initialized
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetPhysAddr(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr);

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of a Ethernet controller
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    ctrlIdx               Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    physAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    action                Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return       E_NOT_OK - Filter modification failed
 *  \return       E_OK - Filter successfully updated
 *  \context      TASK
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          -
 *********************************************************************************************************************/
ETH_30_TC3XX_LOCAL_INLINE FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(
          uint8                                      ctrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                       action);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC
 *********************************************************************************************************************/
/*! \brief        Updates the reception MAC address filter of a Ethernet controller for a normal MAC
 *  \details      Function allows to add or remove MAC address from the reception filter of the Ethernet controller
 *                so Ethernet frames addressed to the respective MAC address can be received or will be blocked from
 *                reception.
 *  \param[in]    ctrlIdx               Identifier of the Ethernet controller
 *                [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]    physAddrPtr           Buffer holding the MAC address the filter shall be adapted for
 *  \param[in]    action                Action that shall be applied for the filter:
 *                                      ETH_REMOVE_FROM_FILTER - MAC address shall be blocked
 *                                      ETH_ADD_TO_FILTER - MAC address shall be allowed
 *  \return       E_NOT_OK - Filter modification failed
 *  \return       E_OK - Filter successfully updated
 *  \context      TASK
 *  \reentrant    TRUE for different Ethernet controllers
 *  \synchronous  TRUE
 *  \pre          ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 *********************************************************************************************************************/
ETH_30_TC3XX_LOCAL_INLINE FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(
          uint8                                       ctrlIdx,
  P2CONST(uint8,                AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                        action);
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_WriteMii
 **********************************************************************************************************************/
/*! \brief       Triggers a write command on the MDIO interface of a Ethernet controller
 *  \details     Function triggers a write command on the MDIO interface according to clause 22 of the IEEE
 *               specification.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx  5-Bit address of the counter part on MDIO interface (MII address)
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx   5-Bit address of the register that shall be written
 *               [range: 0 <= regIdx < 32]
 *  \param[in]   regVal   Value that shall be written to the register
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK - Write command was triggered successfully
 *  \context     ANY
 *  \reentrant   TRUE for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_WriteMii(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ReadMii
 **********************************************************************************************************************/
/*! \brief       Triggers a read command on the MDIO interface of a Ethernet controller an provides the result
 *  \details     Function triggers a read command on the MDIO interface according to clause 22 of the IEEE
 *               specification and provides the result of the read.
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   trcvIdx   5-Bit address of the counter part on MDIO interface (MII address)
 *               [range: 0 <= trcvIdx < 32]
 *  \param[in]   regIdx    5-Bit address of the register that shall be read
 *               [range: 0 <= regIdx < 32]
 *  \param[out]  regValPtr  Buffer to store the result of the read command
 *  \return      ETH_E_NOT_OK - Service call failed due to invalid module state or function parameters
 *  \return      ETH_E_NO_ACCESS - Access to the MDIO interface timed out
 *  \return      ETH_OK -
 *  \context     ANY
 *  \reentrant   TRUE  for different MDIO interfaces
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ReadMii(
        uint8                         ctrlIdx,
        uint8                         trcvIdx,
        uint8                         regIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr);
# endif /* ETH_30_TC3XX_MII_INTERFACE */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetCounterState
 **********************************************************************************************************************/
/*! \brief       Retrieves the value of an Ethernet statistics counter
 *  \details     Function retrieves the value of an Ethernet statistics counter by addressing the counter with the help
 *               of an offset into the Ethernet statistics counter register space.
 *  \param[in]   ctrlIdx    Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   ctrOffs    Offset of the counter into the Ethernet statistics counter register space
 *  \param[out]  ctrValPtr  Buffer to store the counter value
 *  \return      E_NOT_OK - Counter retrieval failed
 *  \return      E_OK - Counter successfully retrieved
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Ethernet controller is initialized
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetCounterState(
        uint8                         ctrlIdx,
        uint16                        ctrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) ctrValPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ProvideTxBuffer
 **********************************************************************************************************************/
/*! \brief          Provides a buffer that can be used to transmit a Ethernet frame
 *  \details        Function provides a buffer that can be used to transmit a Ethernet frame. The buffer is locked and
 *                  therefore protected against reuse until the transmission of the frame is confirmed after transmission
 *                  was triggered (Eth_Transmit() and consecutive Eth_TxConfirmation()) or buffer is intentionally released
 *                  by calling Eth_Transmit() with LenByte=0.
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]     bufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     bufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  lenBytePtr  Pointer to variable used to determine the requested and actually provided length of the
 *                              transmission buffer requested:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ProvideTxBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer
 **********************************************************************************************************************/
/*! \brief          Helper for ProvideTxBuffer
 *  \details        -
 *  \param[in]      ctrlIdx     Identifier of the Ethernet controller
 *                  [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]     bufIdxPtr   Identifier of the buffer provided on successful buffer provision
 *  \param[out]     bufPtr      Pointer to the buffer provided on successful buffer provision
 *  \param[in,out]  lenBytePtr  Pointer to variable used to determine the requested and actually provided length of the
 *                              transmission buffer requested:
 *                              [in]  Length of the data the caller wants to transmit (Payload length)
 *                              [out] Actual length of the buffer provided
 *  \param[in]      txBufferBusyIdx  Identifier of the buffer provided on successful buffer provision
 *                  [range: 0 <= txBufferBusyIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \return         BUFREQ_E_NOT_OK - Service was called
 *  \return         BUFREQ_E_OVFL - No buffer with the requested length available by configuration
 *  \return         BUFREQ_E_BUSY - Any buffer able to hold the requested length is already in use
 *  \return         BUFREQ_OK - Buffer successfully provided
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr,
              uint8                                                      txBufferBusyIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_VTransmit
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame created from the passed buffer with a specific source MAC
 *  \details     Function takes the buffer previously provided by Eth_ProvideTxBuffer() enhances it with the Ethernet
 *               header (using a specific source MAC address instead of the Ethernet controllers one) and triggers the
 *               transmission of the Ethernet frame.
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   frameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   txConfirmation  Request for a transmission confirmation:
 *                               FALSE - No transmission confirmation desired
 *                               TRUE - Transmission confirmation desired
 *  \param[in]   lenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   physAddrDstPtr  Destination MAC address
 *  \param[in]   physAddrSrcPtr  Source MAC address
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_VTransmit(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          boolean                             txConfirmation,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrSrcPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit_ProcessValidFrame
 **********************************************************************************************************************/
/*! \brief       Trigger the transmission of an Ethernet frame
 *  \details     Function as helper for the frame transmission triggering
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   bufIdx          Identifier of the buffer provided by Eth_ProvideTxBuffer()
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSizeOfTxBufferState()]
 *  \param[in]   frameType       Ethernet type, according to type field of IEEE802.3
 *  \param[in]   lenByte         Length of the data to be transmitted (Payload length)
 *  \param[in]   bufPtr          Pointer pointing to the Ether Type position of a IEEE conform Ethernet frame with
 *                               a size of at least 60 Bytes.
 *  \param[in]   bufStartPtr     Pointer pointing to the destination MAC position of a IEEE conform Ethernet frame
 *  \return      E_NOT_OK - Triggering of frame transmission wasn't possible
 *  \return      E_OK - Frame transmission triggered
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit_ProcessValidFrame(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufStartPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_Receive
 **********************************************************************************************************************/
/*! \brief       Triggers the reception of an Ethernet frame
 *  \details     -
 *  \param[in]   ctrlIdx      Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx      Index of the Queue(DMA) to be processes. Set to invalid(ETH_30_CORE_INVALID_FIFO_IDX) in
 *                            case of VLAN-ID based frame queuing disabled.
 *  \param[out]  rxStatusPtr  Indicates the result of the reception trigger:
 *                            ETH_RECEIVED - Ethernet frame was received and no more frames are waiting to be received
 *                            ETH_NOT_RECEIVED - No Ethernet frame was received because non was waiting to be received
 *                            ETH_RECEIVED_MORE_DATA_AVAILABLE - Ethernet frame was received and at least one more
 *                                                               frame is waiting to be received
 *                            ETH_RECEIVED_FRAMES_LOST - will currently not reported
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_Receive(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive_ProcessValidFrame
 **********************************************************************************************************************/
/*! \brief       Helper for reception of an valid Ethernet frame
 *  \details     -
 *  \param[in]   ctrlIdx        Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   descrRingIdx   Identifier of the reception descriptor ring
 *               [range: 0 <= descrRingIdx < Eth_30_Tc3xx_GetSizeOfRxDescrHandling()]
 *  \param[in]   descrIdx  Identifier of the reception descriptor ring position
 *               [range: 0 <= descrIdx < Eth_30_Tc3xx_GetSizeOfRxDescr()]
 *  \param[in]   bufIdx         Identifier of the related RX buffer
 *               [range: 0 <= bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx)]
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive_ProcessValidFrame(
  uint8                                      ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent
 **********************************************************************************************************************/
/*! \brief       Helper to set reception events and optionally  retrieve the index of a reception ring in which the
 *               highest priority pending event occurred.
 *  \details     -
 *  \param[in]   ctrlIdx         Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  descrRingIdxPtr Pointer to the retrieved highest priority pending receive event descriptor ring index
 *  \param[in]   isClearRequired Indicates if the highest prio pending event's descriptor ring index should be cleared
 *                 TRUE - The highest prio pending event should be cleared
 *                 FALSE - The highest prio pending event should not be cleared
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         ETH_30_TC3XX_EXCLUSIVE_AREA_DATA must be entered.
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) descrRingIdxPtr,
        boolean                      isClearRequired);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_TxConfirmation
 **********************************************************************************************************************/
/*! \brief       Triggers the transmission confirmation of a previously transmitted Ethernet frame
 *  \details     Function triggers the transmission confirmation of a previously Ethernet frame transmitted and unlocks
 *               the buffer associated to the Ethernet frame so it is able to be used for frame transmission again.
 *  \param[in]   ctrlIdx  Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   fifoIdx  Index of the Queue(DMA) to be processes. Set to invalid(ETH_30_TC3XX_INVALID_FIFO_IDX) in case
 *                        of VLAN-ID based frame queuing disabled.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_TxConfirmation(
  uint8 ctrlIdx,
  uint8 fifoIdx);

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetRxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of reception statistics
 *  \details     Function returns the list of reception statistics from IETF RFC1213.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  rxStatsPtr  List of read statistics values for reception
 *  \return      E_OK:     Success
 *               E_NOT_OK: RX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetTxStats()
 *********************************************************************************************************************/
/*! \brief       Returns list of transmission statistics
 *  \details     Function returns the list of transmission statistics from IETF RFC1213.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[out]  txStatsPtr  List of read statistics values for transmission
 *  \return      E_OK:     Success
 *               E_NOT_OK: TX-statistics could not be obtained
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr);
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if ( ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON )
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*! \brief       To Get and/or Reset the Measurement statistics.
 *  \details     This function can be used to retrieve and/or reset the measurement data counter statistics that are
 *               supported.
 *  \param[in]   ctrlIdx     Identifier of the Ethernet controller
 *               [range: 0 <= ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl()]
 *  \param[in]   measIdx         Identifier of the type of measurement data to be retrieved or reset
 *  \param[in]   resetNeeded     Controls if the data determined by MeasIdx should be reset
 *                               FALSE - Reset of the data not requested
 *                               TRUE  - Reset of the data requested
 *  \param[out]  measurementData Pointer to store the the measurement data if Reset is set to FALSE
 *  \return      E_OK: Measurement data successfully retrieved or reset
 *               E_NOT_OK: Measurement data could not be retrieved or reset
 *  \context     TASK|ISR1|ISR2
 *  \reentrant   TRUE for different Ethernet controllers
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(
        uint8                         ctrlIdx,
        Eth_MeasurementIdxType        measIdx,
        boolean                       resetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) measurementData);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter
 **********************************************************************************************************************/
/*! \brief       Retrieve and optionally reset a specific measurement data counter.
 *  \details     -
 *
 *  \param[out]  measurementDataPtr   Pointer to retrieve a measurement data counter value or
 *                                    NULL_PTR if no retrieval is intended
 *  \param[in]   measDataStatsCtrPtr  Pointer to a specific global measurement data statistics counter
 *  \param[in]   ResetNeeded          Controls if the data in measDataStatsCtrPtr should be reset
 *                                      FALSE - Reset of the data not requested
 *                                      TRUE  - Reset of the data requested
 *  \context     TASK
 *  \synchronous TRUE
 *  \pre         -
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measDataStatsCtrPtr,
        boolean                        ResetNeeded);

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ClearMeasurementData
 *********************************************************************************************************************/
/*! \brief       Clears all measurement data statistic counters of the Eth Core
 *  \details     -
 *  \param[in]   CtrlIdx Identifier of the Ethernet controller
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE
 *********************************************************************************************************************/
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ClearMeasurementData(
  uint8 ctrlIdx);
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsBroadcast
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBroadcast(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least addrIdx;
  boolean     isBroadcast = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all six bytes of the given MAC address */
  for (addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++)
  {
    /* #110 The currently checked byte is not equal to 0xFF */
    if (macAddrPtr[(uint8)addrIdx] != 0xFF)
    {
      /* #1110 Return that the given MAC-address is no broadcast address */
      isBroadcast = FALSE;
      break;
    }
  }
  return isBroadcast;
} /* Eth_30_Tc3xx_IsBroadcast() */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsZeroAddress
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsZeroAddress(
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) macAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least addrIdx;
  boolean     isZeroAddress = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Iterate over all six bytes of the given MAC address */
  for (addrIdx = 0; addrIdx < ETH_PHYS_ADDR_LEN_BYTE; addrIdx++)
  {
    /* #110 The currently checked byte is not equal to zero */
    if (macAddrPtr[(uint8)addrIdx] != 0x00)
    {
      /* #1110 Return that the given MAC-address is no zero-address */
      isZeroAddress = FALSE;
      break;
    }
  }
  return isZeroAddress;
} /* Eth_30_Tc3xx_IsZeroAddress() */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitBuffersAndDescriptors
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitBuffersAndDescriptors(
  uint8 ctrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_TxDescrHandlingIterType  txDescrHandlingIdx;
  Eth_30_Tc3xx_RxDescrHandlingIterType  rxDescrHandlingIdx;
  Eth_30_Tc3xx_TxBufferStateIterType    txBufferStateIdx;
  Eth_30_Tc3xx_TxBufferHandlingIterType txBufferHandlingIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop over all TX descriptor rings */
  for (txDescrHandlingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
       txDescrHandlingIdx++)
  {
    Eth_30_Tc3xx_TxDescrIterType         txDescrIdx;
    Eth_30_Tc3xx_TxDescrRingProcIterType txDescrRingProcIdx;

    /* #110 Loop over all TX descriptors in the current ring */
    for (txDescrIdx = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(txDescrHandlingIdx);
         txDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(txDescrHandlingIdx);
         txDescrIdx++)
    {
      /* #1110 Initialize the current TX descriptor */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_InitializeTxDescriptor(ctrlIdx, txDescrHandlingIdx, txDescrIdx);
      /* same number of elements */
      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(txDescrIdx, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);                               /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    }

    /* #120 Set the state variable for the ring position for the current TX descriptor ring the initial value */
    txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(txDescrHandlingIdx);
    Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(txDescrRingProcIdx, 0);                                                     /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx, 0);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }
  /* #20 Loop over all RX descriptor rings */
  for (rxDescrHandlingIdx = Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
       rxDescrHandlingIdx  < Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx);
       rxDescrHandlingIdx++)
  {
    Eth_30_Tc3xx_RxDescrIterType                rxDescrIdx;
    Eth_30_Tc3xx_RxDescrRingProcIterType        rxDescrRingProcIdx;
    Eth_30_Tc3xx_SegNumOfRxBufferHandlingType   segNumOfRxBufferHandling;
    Eth_30_Tc3xx_MappedBufferOfRxDescrStateType rxBufferIdx = 0;

    segNumOfRxBufferHandling = Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(rxDescrHandlingIdx);

    /* #210 Loop over all RX descriptors in the current ring */
    for (rxDescrIdx = Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(rxDescrHandlingIdx);
         rxDescrIdx < Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(rxDescrHandlingIdx);
         rxDescrIdx++)
    {
      /* #2110 Initialize the current RX descriptor */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_InitializeRxDescriptor(ctrlIdx, rxDescrHandlingIdx, rxDescrIdx, rxBufferIdx);

      /* #2120 Set the global state variables for the current RX descriptor to map descriptors and buffers */
      if (rxBufferIdx < segNumOfRxBufferHandling)
      {
        Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(rxDescrIdx, rxBufferIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
      }
      else
      {
        Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(rxDescrIdx, ETH_30_TC3XX_RX_DESCRIPTOR_TO_BUFFER_NOT_MAPPED);          /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
      }
      rxBufferIdx++;
    }
    /* #220 Set the state variable for the ring position for the current RX descriptor ring to the initial value */
    rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(rxDescrHandlingIdx);
    Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx, 0);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }

  /* #30 Loop over all transmission buffers */
  txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
  for (txBufferStateIdx = Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(txBufferHandlingIdx);
       txBufferStateIdx < Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(txBufferHandlingIdx);
       txBufferStateIdx++)
  {
    /* #310 Initialize the buffer busy state of the current transmission buffer */
    Eth_30_Tc3xx_SetBusyOfTxBufferState(txBufferStateIdx, FALSE);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    /* #320 Initialize the upper layer confirmation state of the current transmission buffer */
    Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(txBufferStateIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);       /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

    /* #330 If timeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #3310 Initialize the state variable indicating if a time stamp is requested for the current transmission
       *       buffer */
      Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(txBufferStateIdx, ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);               /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    }
  }

  /* #40 Initialize HW specific global Descriptor state variables */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_InitDescriptorStateVariables(ctrlIdx);

  /* #50 Announce descriptor lists to hardware */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_SetDescriptorBaseAddresses(ctrlIdx);
} /* Eth_30_Tc3xx_InitBuffersAndDescriptors() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncRxDescrRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxDescrRingProcPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType procPos;
  Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType rxDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(descrRingIdx);
  procPos            = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx);
  /* #10 Increment current read position in RX descriptor ring */
  procPos++;

  /* #20 If the current read position in the RX descriptor ring is equal to the first invalid position */
  if (procPos >= (Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current read position in the RX descriptor ring to 0 to perform a wrap-around */
    procPos = 0u;
  }

  Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx, procPos);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncRxDescrRingProcPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxDescrRingPrevPos
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrIterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingPrevPos(
  Eth_30_Tc3xx_RxDescrHandlingIterType descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType         currDescrIdx)
{
  Eth_30_Tc3xx_RxDescrIterType prevDescrIdx;
  Eth_30_Tc3xx_SegNumOfRxBufferHandlingType numOfSegments;
  Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType numOfDescr;
  Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType rxDescEndIdx;

  rxDescEndIdx   = Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(descrRingIdx);

  numOfDescr     = Eth_30_Tc3xx_GetDescrNumOfRxBufferHandling(descrRingIdx);
  numOfSegments  = Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(descrRingIdx);

  /* #10 If there are additional descriptors configured that are not mapped to buffers, e.g. link descriptors */
  if(numOfDescr > numOfSegments)
  {
    /* #110 Calculate the actual end of the descriptor ring by subtracting the number of additional descriptors */
    rxDescEndIdx = rxDescEndIdx - (Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType)(numOfDescr - numOfSegments);
  }

  /* #20 Calculate the previous descriptor index */
  prevDescrIdx = ((currDescrIdx + rxDescEndIdx) - (uint8)ETH_30_TC3XX_LL_DESCRIDX_DELTA_TO_PREVIDX) % rxDescEndIdx;

  return prevDescrIdx;
} /* Eth_30_Tc3xx_GetRxDescrRingPrevPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingProcPos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingProcPos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType procPos;
  Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(descrRingIdx);
  procPos            = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
  /* #10 Increment current transmission position in TX descriptor ring */
  procPos++;

  /* #20 If the current read position in the TX descriptor ring is equal to the first invalid position */
  if (procPos >= (Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current read position in the TX descriptor ring to 0 to perform a wrap-around */
    procPos = 0u;
  }

  Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx, procPos);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncTxDescRingProcPos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IncTxDescRingFreePos
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxDescRingFreePos(
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_FreePosOfTxDescrRingProcType freePos;
  Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;

  /* ----- Implementation ----------------------------------------------- */
  txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(descrRingIdx);
  freePos            = Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(txDescrRingProcIdx);
  /* #10 Increment free position in TX descriptor ring */
  freePos++;

  /* #20 If the current free position in the TX descriptor ring is equal to the first invalid position */
  if (freePos >= (Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(descrRingIdx) -
                  Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx)))
  {
    /* #210 Set the current free position in the TX descriptor ring to 0 to perform a wrap-around */
    freePos = 0u;
  }
  Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(txDescrRingProcIdx, freePos);                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
} /* Eth_30_Tc3xx_IncTxDescRingFreePos() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsTxBufProvisonPossible
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxBufProvisonPossible(
        uint8                         ctrlIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) lenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for buffer length adaption */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for buffer length adaption */
    if (Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The result of the operation indicates an error */
      if (Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(ethSwtIfcIdx)(lenPtr) == E_NOT_OK)                             /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
      {
        /* #1210 Return that the TX buffer provision is not possible */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_IsTxBufProvisonPossible() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for TX frame preparation */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for TX frame preparation */
    if (Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The operation failed because the EthSwt driver interface returns E_NOT_OK */
      if (Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr) ==               /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
          E_NOT_OK)
      {
        /* #1210 Return that the pre-preparation of the Tx frame is not OK */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_PrePrepareTxFrame() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameTxAllowed
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameTxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for TX frame processing */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface for TX frame processing */
    if (Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      /* #120 The operation failed because the EthSwt driver interface returns E_NOT_OK */
      if (Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr) ==               /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS */
          E_NOT_OK)
      {
        /* #1210 Return that the frame transmission is not allowed */
        result = FALSE;
      }
    }
  }
  return result;
} /* Eth_30_Tc3xx_IsFrameTxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameTx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameTx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface to indicate finish of transmission */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface to indicate finish of transmission */
    if (Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx);                                 /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03 */
    }
  }
} /* Eth_30_Tc3xx_FinishFrameTx() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsFrameRxAllowed
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFrameRxAllowed(
              uint8                                                        ctrlIdx,
              Eth_BufIdxType                                               bufIdx,
  P2VAR(P2VAR(uint8,          AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) dataPtr,
        P2VAR(uint16,         AUTOMATIC, AUTOMATIC)                        dataLenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface for RX frame processing */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    boolean isMgmtFrameOnly = TRUE;

    /* #110 Perform the call of the EthSwt driver interface for RX frame processing */
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #120 If the operation performed by the EthSwt driver interface fails */
    if (Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      if (Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx, dataPtr, dataLenPtr, &isMgmtFrameOnly)/* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_AND_STACK_REF_PASS */
          == E_NOT_OK)
      {
        /* #1210 Return that the fram reception is not allowed */
        result = FALSE;
      }
      /* #130 If the operation performed by the EthSwt driver interface is successful */
      else
      {
        /* #1310 If the EthSwt driver signals that frame shall not be received by stack (EthSwt management frame only) */
        if (isMgmtFrameOnly == TRUE)
        {
          /* #13110 Return that the fram reception is not allowed */
          result = FALSE;
        }
      }
    }
  }

  return result;
} /* Eth_30_Tc3xx_IsFrameRxAllowed() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_FinishFrameRx
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_FinishFrameRx(
  uint8           ctrlIdx,
  Eth_BufIdxType  bufIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the driver has to call the EthSwt driver interface to indicate the end of reception */
  if (Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType ethSwtIfcIdx = Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(ctrlIdx);
    /* #110 Perform the call of the EthSwt driver interface to indicate the end of reception */
    if (Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx) != NULL_PTR)
    {
      Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(ethSwtIfcIdx)(ctrlIdx, bufIdx);                                 /* SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03 */
    }
  }
} /* Eth_30_Tc3xx_FinishFrameRx() */

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_IsValidAlignment
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsValidAlignment(
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ctrlIdxPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_SizeOfEthCtrlType ethCtrlIdx;
  boolean result = TRUE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Loop over all controllers */
  for (ethCtrlIdx = 0; ethCtrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl(); ethCtrlIdx++)
  {
     Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType  rxDescrHandlingIdx;
     Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType rxBufferHandlingIdx;
     Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType  txDescrHandlingIdx;
     Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
     Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType txBufferStartIdx;

     /* #110 Loop over all RX Descriptor rings */
    for (rxDescrHandlingIdx = Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ethCtrlIdx);
         rxDescrHandlingIdx < Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ethCtrlIdx);
         rxDescrHandlingIdx++)
    {
      /* PRQA S 0303, 0306 1 */ /* MD_Eth_30_Tc3xx_0303, MD_Eth_30_Tc3xx_0306 */
      uint32 rxDescAddr = (uint32)Eth_30_Tc3xx_GetAddrRxDescr(
                                  Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(rxDescrHandlingIdx));
      /* #1110 If the currently checked RX descriptor ring does not fulfill the minimum alignment requirement */
      if ((rxDescAddr % (uint32)ETH_30_TC3XX_LL_DESC_ALIGN_BYTE) != 0u)
      {
        /* #11110 Return that the alignment is not valid */
        result = FALSE;
        break;
      }
    }

    /* #120 Loop over all RX Buffer queues */
    for (rxBufferHandlingIdx = Eth_30_Tc3xx_GetRxBufferHandlingStartIdxOfEthCtrl(ethCtrlIdx);
         rxBufferHandlingIdx < Eth_30_Tc3xx_GetRxBufferHandlingEndIdxOfEthCtrl(ethCtrlIdx);
         rxBufferHandlingIdx++)
    {
      /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
      uint32 rxBufferAddr = (uint32)(Eth_30_Tc3xx_GetAddrRxBuffer(
                                     Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(rxBufferHandlingIdx)));

      /* #1210 If the currently checked RX buffer queue does not fulfill the minimum alignment requirement */
      if (((rxBufferAddr % (uint32)ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE) != 0u))
      {
        /* #12110 Return that the alignment is not valid */
        result = FALSE;
        break;
      }
    }

    /* #130 Loop over all TX Descriptor rings */
    for (txDescrHandlingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ethCtrlIdx);
         txDescrHandlingIdx < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ethCtrlIdx);
         txDescrHandlingIdx++)
    {
      /* PRQA S 0303, 0306 1 */ /* MD_Eth_30_Tc3xx_0303, MD_Eth_30_Tc3xx_0306 */
      uint32 txDescAddr = (uint32)Eth_30_Tc3xx_GetAddrTxDescr(
                                  Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(txDescrHandlingIdx));

      /* #1310 If the currently checked TX descriptor ring does not fulfill the minimum alignment requirement */
      if ((txDescAddr % (uint32)ETH_30_TC3XX_LL_DESC_ALIGN_BYTE) != 0u)
      {
        /* #13110 Return that the alignment is not valid */
        result = FALSE;
        break;
      }
    }

    txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ethCtrlIdx);
    txBufferStartIdx = Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);

    /* #140 Check the TX buffer list for the minimum alignment requirement */
    /* PRQA S 0306 1 */ /* MD_Eth_30_Tc3xx_0306 */
    if (((uint32)Eth_30_Tc3xx_GetAddrTxBuffer(txBufferStartIdx) % (uint32)ETH_30_TC3XX_LL_BUFF_ALIGN_BYTE) != 0u)
    {
      result = FALSE;
    }

    /* #150 If one of the previous checks failed */
    if(result == FALSE)
    {
      /* #1510 Leave the loop so the result can be reported */
      break;
    }
  }

  /* #20 Return the first controller index for which the alignment was not valid */
  *ctrlIdxPtr = (uint8)ethCtrlIdx;                                                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  return result;
} /* Eth_30_Tc3xx_IsValidAlignment() */ /* PRQA S 6010, 6050 */ /* MD_MSR_STPTH, MD_MSR_STCAL */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ControllerInit
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
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ControllerInit(
  uint8 ctrlIdx,
  uint8 cfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* PRQA S 3197 */ /* MD_Eth_30_Tc3xx_3197 */
  Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType hwLoopTimeout = 0;
  Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType userPreCtrlInitCalloutFctPtr;
  Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType userPostCtrlInitCalloutFctPtr;

  ETH_30_TC3XX_DUMMY_STATEMENT(cfgIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If a user callout to be executed before the actions in Eth_ControllerInit are performed is configured */
  userPreCtrlInitCalloutFctPtr = Eth_30_Tc3xx_GetPreInitUserCalloutOfUserInitCallouts(0);
  if (userPreCtrlInitCalloutFctPtr != NULL_PTR)
  {
    /* #110 Call the configured user function */
    userPreCtrlInitCalloutFctPtr(ctrlIdx);                                                                              /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
  }

  /* #20 Perform hardware configuration which needs to be done before MAC reset */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_PreResetMac(ctrlIdx);

  /* #30 Call the hardware dependent interface to perform a soft reset */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ResetMac(ctrlIdx);

  /* #40 While the soft-reset is not finished yet */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsResetMacFinished(ctrlIdx) == FALSE)
  {
    /* #410 If the timeout for the soft-reset has occurred */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #4110 If configured, report the error E_ACCESS to the DEM and return with E_NOT_OK from Eth_ControllerInit */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
      break;
    }
    /* #420 Otherwise the timeout has not yet occurred, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #50 If the previously performed software reset was successful */
  if (retVal == E_OK)
  {
    /* #510 Call the internal interface to proceed with the controller initialization after software reset */
    retVal = Eth_30_Tc3xx_Internal_ValidControllerInit(ctrlIdx);
  }
  /* #60 If a user callout to be executed after the actions in Eth_ControllerInit are performed is configured */
  userPostCtrlInitCalloutFctPtr = Eth_30_Tc3xx_GetPostInitUserCalloutOfUserInitCallouts(0);
  if (userPostCtrlInitCalloutFctPtr != NULL_PTR)
  {
    /* #610 Call the configured user function */
    userPostCtrlInitCalloutFctPtr(ctrlIdx);                                                                             /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_ControllerInit() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ValidControllerInit
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ValidControllerInit(
  uint8 ctrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK; /* PRQA S 3197 */ /* MD_Eth_30_Tc3xx_3197 */
  Eth_30_Tc3xx_RegDataIterType regDataIdx;
  Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType activeMacAddrStartIdx;

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
  Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the global mode variable */
  Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ETH_MODE_DOWN);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

  /* #20 Loop over all registers to be initialized or configured */
  for (regDataIdx = Eth_30_Tc3xx_GetRegDataStartIdxOfEthCtrl(ctrlIdx);
       regDataIdx < Eth_30_Tc3xx_GetRegDataEndIdxOfEthCtrl(ctrlIdx);
       regDataIdx++)
  {
    /* #210 If the current register to be initialized or configured shall be accessed in user mode */
    if (Eth_30_Tc3xx_GetAccessModeOfRegData(regDataIdx) == ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA)
    {
      /* #2110 Call the internal interface to write a controller register in user mode to write the
       *       configured value */
      Eth_30_Tc3xx_Reg_Write(ctrlIdx, Eth_30_Tc3xx_GetOffsetOfRegData(regDataIdx),
                                     Eth_30_Tc3xx_GetValueOfRegData(regDataIdx));
    }
    /* #220 If the current register to be initialized or configured shall be accessed in protected mode */
    else
    {
      /* #2210 Call the internal interface to write a controller register in protected mode to write the
       *       configured value */
      Eth_30_Tc3xx_Reg_Write_Protected(ctrlIdx, Eth_30_Tc3xx_GetOffsetOfRegData(regDataIdx),
                                               Eth_30_Tc3xx_GetValueOfRegData(regDataIdx));
    }
  }

  /* #30 Initialize the pending RX and TX frame event state variables */
  Eth_30_Tc3xx_SetPendingTxEventsOfEthCtrlState(ctrlIdx, 0);                                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
  Eth_30_Tc3xx_SetPendingRxEventsOfEthCtrlState(ctrlIdx, 0);                                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

  /* #40 Call the internal interface to Initialize all buffers and descriptors */
  Eth_30_Tc3xx_InitBuffersAndDescriptors(ctrlIdx);

  activeMacAddrStartIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
  /* #50 Call the hardware dependent interface to write the configured MAC address to the MAC address registers */
  /* PRQA S 0310 1 */ /* MD_Eth_30_Tc3xx_0310 */ /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMacAddressToRegister(ctrlIdx,                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_GEN_PTR_PASS_CSL03 */
      (const uint8*)Eth_30_Tc3xx_GetAddrActiveMacAddress(activeMacAddrStartIdx));

  /* #60 Call the hardware dependent interface to reset the frame counters */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ResetCounters(ctrlIdx);

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
  (void)Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);
# endif

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
  /* #70 If TimeSync is enabled */
  if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #710 Initialize the TimeSync settings */
    Eth_30_Tc3xx_SetRxTsContextStackPos(ctrlIdx, ETH_30_TC3XX_RX_TS_CONTEXT_STACK_EMPTY_POS);                             /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
    retVal |= Eth_30_Tc3xx_TimeSync_Init(ctrlIdx);
  }
# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
  /* #80 Loop over all multicast bucket counters */
  for (multicastBucketCountersIdx = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
       multicastBucketCountersIdx < Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
       multicastBucketCountersIdx++)
  {
    /* #810 Set the current multicast bucket counter to its initial value */
    Eth_30_Tc3xx_SetMulticastBucketCounters(multicastBucketCountersIdx, 0);                                              /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
  }
  /* #90 Set the promiscuous mode counter to its initial value */
  Eth_30_Tc3xx_SetPromiscuousModeCounter(ctrlIdx, 0);                                                                    /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

  retVal |= Eth_30_Tc3xx_LL_PerformAdditionalHwConfig(ctrlIdx);

  return retVal;
} /* Eth_30_Tc3xx_Internal_ValidControllerInit() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetControllerMode
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
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetControllerMode(
  uint8        ctrlIdx,
  Eth_ModeType ctrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the mode the controller should be set to is ACTIVE */
  if (ctrlMode == ETH_MODE_ACTIVE)
  {
    /* #110 Call the hardware dependent interface to enable the MAC */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_EnableMac(ctrlIdx);

    /* #120 If the activation of the MAC did not finish correctly */
    /*lint -e{522} */
    if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == FALSE)
    {
      /* #1210 If configured, report the error code E_ACCESS to the DEM and return E_NOT_OK */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
    }
    else
    {
      retVal = E_OK;
    }
# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
    /* #130 If TimeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #1310 Start the time synchronization clock */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_TimeSync_StartTimesyncClock(ctrlIdx);
    }
# endif
  }
  /* #20 If the mode the controller should be set to is DOWN */
  else
  {
    /* #210 Call the hardware dependent interface to disable the MAC */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_DisableMac(ctrlIdx);
    /* #220 Shutting down he MAC did not finish correctly */
    /*lint -e{522} */
    if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
    {
      /* #2210 If configured, report the error code E_ACCESS to the DEM and return E_NOT_OK */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = E_NOT_OK;
    }
    else
    {
      retVal = E_OK;
    }
  }
  if (retVal == E_OK)
  {
    /* #30 Update the global mode variable if the function was successfully executed */
    Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ctrlMode);                                                        /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_SetControllerMode */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetControllerMode(
        uint8                               ctrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) ctrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the hardware returns that the MAC is enabled */
  /*lint -e{522} */
  if (Eth_30_Tc3xx_LL_IsMacEnabled(ctrlIdx) == TRUE)
  {
    /* #110 Report the mode of the controller to be ACTIVE */
    (*ctrlModePtr) = ETH_MODE_ACTIVE;                                                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #20 If the hardware returns that the MAC is disabled */
  else
  {
    /* #210 Report the mode of the controller to be DOWN */
    (*ctrlModePtr) = ETH_MODE_DOWN;                                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetControllerMode */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetPhysAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetPhysAddr(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least physAddrPtrIdx;
  Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Return the configured physical address of the controller */
  for (physAddrPtrIdx = 0; physAddrPtrIdx < ETH_PHYS_ADDR_LEN_BYTE; physAddrPtrIdx++)
  {
    activeMacAddrIdx = physAddrPtrIdx + Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);

    physAddrPtr[physAddrPtrIdx] = Eth_30_Tc3xx_GetActiveMacAddress(activeMacAddrIdx);                                 /* SBSW_ETH_30_TC3XX_PHYS_ADDR_PTR_ACCESS */
  }
} /* Eth_30_Tc3xx_Internal_GetPhysAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetPhysAddr(
          uint8                        ctrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) physAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least physAddrPtrIdx = 0;
  Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write the given physical address into the corresponding RAM variable */
  for (activeMacAddrIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
       activeMacAddrIdx < Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(ctrlIdx);
       activeMacAddrIdx++)
  {
    Eth_30_Tc3xx_SetActiveMacAddress(activeMacAddrIdx, physAddrPtr[physAddrPtrIdx]);                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

    physAddrPtrIdx++;
  }

  /* #20 Write the physical address to registers */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMacAddressToRegister(ctrlIdx, physAddrPtr);                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

# if (ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS == STD_ON)
  {
    /* #30 Request the NvM to perform a write to the non-volatile memory, if enabled */
    uint8 status = NVM_REQ_PENDING;
    Std_ReturnType retVal;

    retVal = NvM_GetErrorStatus(Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(ctrlIdx), &status);                               /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */

    if ((retVal == E_OK) && (status != NVM_REQ_PENDING))
    {
      /* set block Status to true */
      NvM_SetRamBlockStatus(Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(ctrlIdx), TRUE);
    }
  }
# endif /* ETH_30_TC3XX_ENABLE_MAC_WRITE_ACCESS */

} /* Eth_30_Tc3xx_Internal_SetPhysAddr() */

# if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(
          uint8                                       ctrlIdx,
  P2CONST(uint8,                AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                        action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent interface to perform hardware specific filter mode settings for hash filtering */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_SetMulticastFilteringMode(ctrlIdx);

  /* #20 Enter exclusive area (Reason: Consistency of global counter variables and number of corresponding calls) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #30 If a broadcast address is given as parameter into the function */
  if (Eth_30_Tc3xx_IsBroadcast(physAddrPtr) == TRUE)                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    /* #310 If the action parameter given into the function indicates that the address should be added to the filter */
    if (action == ETH_ADD_TO_FILTER)
    {
      /* #3110 If the parameter combination corresponds to a request to enable the promiscuous mode and the
       *       corresponding counter has not yet overflown */
      if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) < ETH_30_TC3XX_UINT8_MAX)
      {
        /* #31110 Increment the promiscuous mode counter */
        Eth_30_Tc3xx_IncPromiscuousModeCounter(ctrlIdx);                                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
        retVal = E_OK;

        /* #31120 If the request to enable the promiscuous mode was the first one since it was disabled or after
         *        reset */
        if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) == 1)
        {
          /* #311210 Enable the promiscuous mode */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_EnablePromiscuousMode(ctrlIdx);
        }
      }
      /* #3120 If the parameter combination corresponds to a request to enable the promiscuous mode and the
       *       corresponding counter has overflown */
      else
      {
        /* #31210 Too much activations of promiscuous mode, the request is denied */
      }
    }
    /* #320 If the action parameter given into the function indicates that the address should be removed from the
     *      filter */
    else /* ETH_30_TC3XX_REMOVE_FROM_FILTER */
    {
      /* #3210 If the parameter combination corresponds to a request to disable the promiscuous mode and the
       *       corresponding counter is still bigger than zero */
      if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) > 0)
      {
        /* #32110 Decrement the promiscuous mode counter */
        Eth_30_Tc3xx_DecPromiscuousModeCounter(ctrlIdx);                                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
        retVal = E_OK;

        /* #32120 If the promiscuous mode counter is zero again, which means that all requests to enable the
         *        promiscuous mode were withdrawn */
        if (Eth_30_Tc3xx_GetPromiscuousModeCounter(ctrlIdx) == 0)
        {
          /* #321210 Disable the promiscuous mode */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_DisablePromiscuousMode(ctrlIdx);
        }
      }
      /* #3220 If the parameter combination corresponds to a request to disable the promiscuous mode and the
       *       corresponding counter is already zero */
      else
      {
        /* #32210 The request to disable the promiscuous mode is denied because it was not enabled */
      }
    }
  }
  /* #40 If a zero address is given as parameter into the function to indicate that all filters should be closed */
  else if (Eth_30_Tc3xx_IsZeroAddress(physAddrPtr) == TRUE)                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;

    /* #410 Disable  promiscuous mode */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_DisablePromiscuousMode(ctrlIdx);

    /* #420 Close all multicast filters */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_CloseAllMulticastFilters(ctrlIdx);

    /* #430 set all filter bucket counters to their initial value */
    for (multicastBucketCountersIdx = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx);
         multicastBucketCountersIdx < Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
         multicastBucketCountersIdx++)
    {
      Eth_30_Tc3xx_SetMulticastBucketCounters(multicastBucketCountersIdx, 0);                                            /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
    }

    /* #440 Set the promiscuous mode counter to its initial value */
    Eth_30_Tc3xx_SetPromiscuousModeCounter(ctrlIdx, 0);                                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

    retVal = E_OK;
  }
  /* #50 If a MAC address without special function defined by AUTOSAR shall be handled */
  else
  {
    /* #510 Call the internal interface to handle normal MAC addresses */
    retVal = Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(ctrlIdx, physAddrPtr, action);                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }
  /* #60 Leave the exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC(
          uint8                                      ctrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) physAddrPtr,
          Eth_FilterActionType                       action)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 hash;
  uint32 bucketMask;
  boolean isUpperReg;
  Eth_30_Tc3xx_MulticastBucketCountersType multicastBucketCountersIdx;
  Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType multicastBucketCountersEndIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent interface to calculate the multicast filter register hash */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_CalculateMulticastFilterRegisterHash(ctrlIdx, physAddrPtr, &hash, &isUpperReg, &bucketMask);           /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */
  /* #20 Retrieve the index of the corresponding bucket counter with the returned hash */
  multicastBucketCountersIdx    = Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(ctrlIdx) + hash;
  multicastBucketCountersEndIdx = Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(ctrlIdx);
  /* #30 If the retrieved index is correct */
  if (multicastBucketCountersIdx < multicastBucketCountersEndIdx)
  {
    /* #310 If the action parameter given into the function indicates that the address shall be added to the filter */
    if (ETH_ADD_TO_FILTER == action)
    {
      /* #3110 If the multicast bucket counter for the corresponding register is still below its max value */
      if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) < ETH_30_TC3XX_BUCKET_MAX_CNT)
      {
        /* #31110 Increment the multicast bucket counter */
        Eth_30_Tc3xx_IncMulticastBucketCounters(multicastBucketCountersIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

        /* #31120 If the multicast bucket counter for the corresponding register is equal to one, the address is
         *        requested for the first time after it was removed or reset */
        if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) == 1)
        {
          /* #311210 If the hardware dependent interface to calculate the multicast filter register has indicated
           *         that the upper multicast filter register needs to be written */
          if (isUpperReg == TRUE)
          {
            /* #3112110 Write the previously retrieved bucket mask  into the upper bucket register */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_SetUpperMulticastFilterBucketRegister(ctrlIdx, bucketMask);
          }
          /* #311220 If the hardware dependent interface to calculate the multicast filter register has indicated
           *         that the lower multicast filter register needs to be written */
          else
          {
            /* #3112210 Write the previously retrieved bucket mask into the lower bucket register */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_SetLowerMulticastFilterBucketRegister(ctrlIdx, bucketMask);
          }
        }
        /* #31130 Return that the request was successful */
        retVal = E_OK;
      }
    }
    /* #320 If the action parameter given into the function indicates that the address shall be removed from the
     *      filter */
    else
    {
      /* #3210 If the multicast bucket counter for the corresponding register is still greater than zero */
      if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) > 0)
      {
        /* #32110 Decrement the multicast bucket counter */
        Eth_30_Tc3xx_DecMulticastBucketCounters(multicastBucketCountersIdx);                                             /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */

        /* #32120 If the counter reaches zero, indicating that enough requests to remove the address from the filter
         *        were performed */
        if (Eth_30_Tc3xx_GetMulticastBucketCounters(multicastBucketCountersIdx) == 0)
        {
          /* #321210 If the hardware dependent interface to calculate the multicast filter register indicates that
           *         the upper multicast filter register needs to be modified */
          if (TRUE == isUpperReg)
          {
            /* #3212110 Clear the previously retrieved bucket mask from the upper bucket register */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_ResetUpperMulticastFilterBucketRegister(ctrlIdx, bucketMask);
          }
          /* #321220 If the hardware dependent interface to calculate the multicast filter register indicates that
           *         the lower multicast filter register needs to be modified */
          else
          {
            /* #3212210 Clear the previously retrieved bucket mask from the lower bucket register */
            /*lint -e{522} */
            Eth_30_Tc3xx_LL_ResetLowerMulticastFilterBucketRegister(ctrlIdx, bucketMask);
          }
        }
        /* #32130 Return that the request was successful */
        retVal = E_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_UpdatePhysAddrFilter_NormalMAC() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */
# endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_WriteMii
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
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_WriteMii(
  uint8  ctrlIdx,
  uint8  trcvIdx,
  uint8  regIdx,
  uint16 regVal)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType hwLoopTimeout = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Prevention of another trigger for the same action while it is not completed yet) */
  Eth_30_Tc3xx_EnterExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Call the hardware dependent interface to trigger a MII-Management write opration */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_WriteMiiTrigger(ctrlIdx, trcvIdx, regIdx, regVal);

  /* #30 If the MII-Management write operation is still pending */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsMiiOperationPending(ctrlIdx) == TRUE)
  {
    /* #310 If the timeout for the MII-Management write operation is reached */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #3110 If configured, report the error code E_ACCESS to the DEM and return that the management access is not
       *       working correctly */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = ETH_E_NO_ACCESS;
      break;
    }
    /* #320 If the timeout value is not yet reached, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #40 If the MII-Management write operation has completed without timeout */
  if (hwLoopTimeout <= Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
  {
    /* #410 Return that the management access is OK */
    retVal = ETH_OK;
  }

  /* #50 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_WriteMii() */
# endif /* ETH_30_TC3XX_MII_INTERFACE */

# if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ReadMii
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
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ReadMii(
        uint8                         ctrlIdx,
        uint8                         trcvIdx,
        uint8                         regIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) regValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType hwLoopTimeout = 0;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Prevention of another trigger for the same action while it is not completed yet
   *                                   and consistency of triggered event and retrieved result) */
  Eth_30_Tc3xx_EnterExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Call the hardware dependent interface to trigger a MII-Management read opration */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_ReadMiiTrigger(ctrlIdx, trcvIdx, regIdx);

  /* 30 If the MII-Management read operation is still pending */
  /*lint -e{522} */
  while (Eth_30_Tc3xx_LL_IsMiiOperationPending(ctrlIdx) == TRUE)
  {
    /* #310 If the timeout for the MII-Management read operation is reached */
    if (hwLoopTimeout > Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
    {
      /* #3110 If configured, report the error code E_ACCESS to the DEM and return that the management access is not
       *       working correctly */
      ETH_30_TC3XX_DEM_REPORT_ERROR_STATUS_ETH_E_ACCESS(ctrlIdx);
      retVal = ETH_E_NO_ACCESS;
      break;
    }
    /* #320 If the timeout value is not yet reached, increment the timeout counter */
    hwLoopTimeout++;
  }

  /* #40 If the MII-Management read operation has completed without timeout */
  if (hwLoopTimeout <= Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(ctrlIdx))
  {
    /* #410 Retrieve the read result */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_GetReadMiiResult(ctrlIdx, regValPtr);                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
    /* #420 Return that the management access is OK */
    retVal = ETH_OK;
  }

  /* #50 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(MII); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_ReadMii() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */
# endif /* ETH_30_TC3XX_MII_INTERFACE */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetCounterState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetCounterState(
        uint8                         ctrlIdx,
        uint16                        ctrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) ctrValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the counter offset to be read from is in the supported range of the hardware */
  /*lint -e{522} */
  if (Eth_30_Tc3xx_LL_GetMaxCounterOffset(ctrlIdx) >= ctrOffs)
  {
    /* #110 Call the hardware dependent interface to read the counter value */
    /*lint -e{522} */
    retVal = Eth_30_Tc3xx_LL_GetCounterValue(ctrlIdx, ctrOffs, ctrValPtr);                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetCounterState */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ProvideTxBuffer
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ProvideTxBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If TX buffer provision is possible */
  if (Eth_30_Tc3xx_IsTxBufProvisonPossible(ctrlIdx, lenBytePtr) == TRUE)                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  {
    uint16 requestedLen;
    Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
    Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType maxTxBufferLen;

    txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
    maxTxBufferLen      = Eth_30_Tc3xx_GetMaxBufferLenOfTxBufferHandling(txBufferHandlingIdx);
    /* #110 If the maximum size of all available buffers is not big enough for the requested payload plus header and FCS
     *      (total frame length) */
    requestedLen = (*lenBytePtr) + ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE;

    if (maxTxBufferLen < requestedLen)
    {
      /* #1110 The buffer provision fails */
      retVal = BUFREQ_E_OVFL;
    }
    /* #120 If at least one buffer is big enough for the requested total frame lenth */
    else
    {
      Eth_30_Tc3xx_TxBufferStateIterType txBufferStateIdx;
      Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType txBufferStateEndIdx;
      Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType txBufferStateStartIdx;

      /* #1210 Enter exclusive area (Reason: Consistency between found buffer and locked buffer indices) */
      Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

      txBufferStateStartIdx = Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(txBufferHandlingIdx);
      txBufferStateEndIdx   = Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(txBufferHandlingIdx);
      /* #1220 loop over all available transmission buffers */
      for (txBufferStateIdx = txBufferStateStartIdx; txBufferStateIdx < txBufferStateEndIdx; txBufferStateIdx++)
      {
        /* #12210 The current buffer is not in use (busy) and its size is big enough for the requested frame length */
        /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */
        if ((Eth_30_Tc3xx_IsBusyOfTxBufferState(txBufferStateIdx)   == FALSE) &&
            (Eth_30_Tc3xx_GetLengthOfTxBufferData(txBufferStateIdx) >= requestedLen))
        {
          /* #122110 Leave the loop */
          break;
        }
      }
      /* #1230 If a suitable buffer could be found in the previous loop */
      if ((txBufferStateIdx - txBufferStateStartIdx) < Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(txBufferHandlingIdx))
      {
        /* #12310 Call the internal interface to proceed the buffer provision for a valid buffer */
        retVal = Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
                  ctrlIdx, bufIdxPtr, bufPtr, lenBytePtr, (uint8)txBufferStateIdx);
      }
      /* #1240 If no suitable buffer could be found in the previous loop */
      else
      {
        /* #12410 Return that all big enough buffers are in use (busy) */
        retVal = BUFREQ_E_BUSY;
        /* #12420 Increment the measurement counter */
        Eth_30_Tc3xx_IncDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx);                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      }

      /* #1250 Leave exclusive area */
      Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    }
  }

  return retVal;
} /* Eth_30_Tc3xx_Internal_ProvideTxBuffer() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer
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
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer(
              uint8                                                      ctrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) bufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        lenBytePtr,
              uint8                                                      txBufferBusyIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_TxBufferIterType globalStartOffset;
  Eth_30_Tc3xx_StartPosOfTxBufferDataType localStartOffset;
  Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
  Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType txBufferEndIdx;
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
  txBufferEndIdx      = Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(txBufferHandlingIdx);

  /* #10 Retrieve the index of the valid buffer to be provided to the caller */
  localStartOffset    = Eth_30_Tc3xx_GetStartPosOfTxBufferData(txBufferBusyIdx);
  globalStartOffset   = localStartOffset + Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);

  /* #20 If the retrieved buffer index offset position has enough distance to the end index for a valid buffer */
  if ((globalStartOffset + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) < txBufferEndIdx)
  {
    Eth_30_Tc3xx_TxBufferPtrType bufAddrFrameType;
    Eth_30_Tc3xx_TxBufferIterType frameTypeOffset;
    Eth_30_Tc3xx_LengthOfTxBufferDataType lenByte;
    Eth_30_Tc3xx_LengthOfTxBufferDataType txBufferLength;

    frameTypeOffset = globalStartOffset +
        (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE;

    bufAddrFrameType = Eth_30_Tc3xx_GetAddrTxBuffer(frameTypeOffset);

    txBufferLength   = Eth_30_Tc3xx_GetLengthOfTxBufferData(txBufferBusyIdx);

    lenByte          = (Eth_30_Tc3xx_LengthOfTxBufferDataType)(txBufferLength -
                        ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE -
                        ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE);

    /* #210 If the pre-preparation of the TX frame is OK */
    if (Eth_30_Tc3xx_IsPrePreparationOfTxFrameOk(ctrlIdx, txBufferBusyIdx, &bufAddrFrameType, &lenByte) == TRUE)         /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X */
    {
      /* #2110 Adjust the returned length to exclude the frame type length */
      lenByte -= ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE;
      /* #2120 If the modified length is valid */
      if ((globalStartOffset + lenByte) < txBufferEndIdx)
      {
        Eth_30_Tc3xx_TxBufferPtrType bufAddrPayload;
        /* #21210 Adjust the returned buffer pointer to point at the start of the payload */
        bufAddrPayload = &bufAddrFrameType[ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE];
        /* #21220 Set the buffers state to busy to lock it */
        Eth_30_Tc3xx_SetBusyOfTxBufferState(txBufferBusyIdx, TRUE);                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

        /* #21230 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
        {
          /* #212310 Reset the global buffer state variable indicating if a timestamp is requested */
          Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(txBufferBusyIdx, FALSE);                                            /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        }
        /* #21240 Return the length, buffer pointer and buffer index to the caller */
        (*lenBytePtr) = lenByte;                                                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        /* PRQA S 3305, 0310 1 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
        (*bufPtr)     = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))bufAddrPayload;                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

        (*bufIdxPtr)  = txBufferBusyIdx;                                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        /* #21250 Return that the buffer provision was successful */
        retVal        = BUFREQ_OK;
      }
    }
  }
  return retVal;
} /* Eth_30_Tc3xx_ProvideTxBuffer_HandleValidBuffer() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_VTransmit
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_VTransmit(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          boolean                             txConfirmation,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) physAddrSrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Consistency between transmitted and unlocked buffer indices and synchronization
   *                                   between hardware and software) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 If the buffer the transmission was requested for is locked which indicates that its provision was successful */
  if (Eth_30_Tc3xx_IsBusyOfTxBufferState(bufIdx) == TRUE)
  {
    /* #210 Retrieve the buffer offset and start pointer out of the buffer index parameter */
    Eth_30_Tc3xx_TxBufferIterType bufStartOffset;
    Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType txBufferEndIdx;
    Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType txBufferHandlingIdx;
    Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType txBufferStartIdx;

    txBufferHandlingIdx = Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(ctrlIdx);
    txBufferStartIdx    = Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(txBufferHandlingIdx);
    txBufferEndIdx      = Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(txBufferHandlingIdx);
    bufStartOffset      = Eth_30_Tc3xx_GetStartPosOfTxBufferData(bufIdx) + txBufferStartIdx;

    if ((bufStartOffset + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) < txBufferEndIdx )
    {
      uint8 physAddrPtrIterator;
      Eth_30_Tc3xx_TxBufferIterType bufSrcMacOffset;
      Eth_30_Tc3xx_TxBufferIterType bufDstMacOffset;
      Eth_30_Tc3xx_TxBufferIterType bufEtherTypeOffset;
      Eth_30_Tc3xx_TxBufferIterType macAddressIterator;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufStartPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufDstMacPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufSrcMacPtr;
      P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufEthTypePtr;

      bufDstMacOffset    = bufStartOffset + (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_DST;
      bufSrcMacOffset    = bufStartOffset + (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_SRC;
      bufEtherTypeOffset = bufStartOffset + (Eth_30_Tc3xx_TxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_TX_TYPE;

      bufStartPtr        = Eth_30_Tc3xx_GetAddrTxBuffer(bufStartOffset);
      bufEthTypePtr      = Eth_30_Tc3xx_GetAddrTxBuffer(bufEtherTypeOffset);

      /* #220 If the transmission was requested for a zero length buffer indicating that only the buffer should be
       *      released */
      if (lenByte == 0u)
      {
        /* #2210 Release the buffer so it can be provided again and return that the request was successful */
        Eth_30_Tc3xx_SetBusyOfTxBufferState(bufIdx, FALSE);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        retVal = E_OK;
      }
      /* #230 If the requested transmission length is greater than 0 indicating that a transmission shall be
       *      performed */
      else
      {
        /* #2310 Write source and destination MAC-address into the buffer */
        /* Assemble Ethernet Header */
        /* Physical destination address */
        physAddrPtrIterator = 0;
        for (macAddressIterator = bufDstMacOffset; macAddressIterator < bufSrcMacOffset; macAddressIterator++)
        {
          bufDstMacPtr  = Eth_30_Tc3xx_GetAddrTxBuffer(macAddressIterator);
          *bufDstMacPtr = physAddrDstPtr[physAddrPtrIterator];                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X */
          physAddrPtrIterator++;
        }
        /* Physical source address */
        physAddrPtrIterator = 0;
        for (macAddressIterator = bufSrcMacOffset; macAddressIterator < bufEtherTypeOffset; macAddressIterator++)
        {
          bufSrcMacPtr  = Eth_30_Tc3xx_GetAddrTxBuffer(macAddressIterator);
          *bufSrcMacPtr = physAddrSrcPtr[physAddrPtrIterator];                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X */
          physAddrPtrIterator++;
        }

        /* #2320 Write the frame type to the buffer */
        bufEthTypePtr[ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX] = (uint8)(frameType >> ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_RSHIFT);/* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS */
        bufEthTypePtr[ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX] = (uint8)frameType;                                           /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS */
        /* #2330 If frame transmission is allowed */
        if (Eth_30_Tc3xx_IsFrameTxAllowed(ctrlIdx, bufIdx, &bufEthTypePtr, &lenByte) == TRUE)                            /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_PARAM_PASS_CSL0X */
        {
          /* #23310 If a upper layer TX-confirmation is requested */
          if (TRUE == txConfirmation)
          {
            /* #233110 Set the global state variable of the transmission buffer to indicate that a confirmation is
             *         pending */
            Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(bufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING);             /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
          }
          /* #23320 Call the internal interface to proceed the frame transmission for a valid frame */
          Eth_30_Tc3xx_VTransmit_ProcessValidFrame(ctrlIdx, bufIdx, frameType, lenByte, bufEthTypePtr, bufStartPtr);     /* SBSW_ETH_30_TC3XX_INT_FCT_SHIFTED_LOCAL_BUF_PTR_WITH_LENGTH_PASS_SWT_IFC */
          /* #23330 Return that the request was successful */
          retVal = E_OK;
        }
      }
      /* #240 Perform finishing steps after transmission */
      Eth_30_Tc3xx_FinishFrameTx(ctrlIdx, bufIdx);
    }
  }
  /* #30 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_VTransmit() */ /* PRQA S 6050, 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit_ProcessValidFrame
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
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit_ProcessValidFrame(
          uint8                               ctrlIdx,
          uint8                               bufIdx,
          Eth_FrameType                       frameType,
          uint16                              lenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) bufStartPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 vlanIdTxDescrRing = 0;
  Eth_30_Tc3xx_TxDescrIterType curPos;
  Eth_30_Tc3xx_TxDescrIterType globalDescrIdx;
  Eth_30_Tc3xx_TxDescrHandlingIterType descrRingIdx;
  Eth_30_Tc3xx_VlanPrioTxDescrRingMapType vlanPrioTxDescrRing;
  Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType txDescrStartIdx;
  Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType vlanIdTxDescrRingMapIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Initialize the descriptor ring index to match the queue the transmission shall be performed with in case of
   *     untagged traffic */
  descrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);

  /* #20 Increase the passed length by the Ethernet frame header length */
  lenByte += ETH_30_TC3XX_HDR_LEN_BYTE;

  /* #30 If Quality of Service is enabled */
  if (Eth_30_Tc3xx_IsQosEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType qosHandlingIdx = Eth_30_Tc3xx_GetQosHandlingIdxOfEthCtrl(ctrlIdx);
    /* #310 If the frame type indicates that the frame to be transmitted is a VLAN frame */
    if (frameType == ETH_30_TC3XX_VLAN_ETHER_TYPE)  /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
    {
      /* #3110 Retrieve the VLAN-priority of the frame */
      uint8 vlanPrio;
      Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType vlanPrioTxDescrRingMapStartIdx;

      vlanPrioTxDescrRingMapStartIdx = Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapStartIdxOfQosHandling(qosHandlingIdx);

      vlanPrio = (uint8)((bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET] & ETH_30_TC3XX_VLAN_PCP_BYTE_MASK) >>
                                 ETH_30_TC3XX_VLAN_PCP_BYTE_SHIFT);

      /* #3120 Retrieve the transmission queue and descriptor ring index a frame with the retrieved VLAN-priority shall
       *       be transmitted in */
      vlanPrioTxDescrRing = Eth_30_Tc3xx_GetVlanPrioTxDescrRingMap(vlanPrioTxDescrRingMapStartIdx + vlanPrio);

      /* #3130 If the retrieved VLAN prio leads to a valid global descriptor ring index */
      if ((descrRingIdx + vlanPrioTxDescrRing) < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx))
      {
        /* #31310 Overwrite the previously initialized descriptor ring index with the retrieved ring index */
        descrRingIdx = (descrRingIdx + vlanPrioTxDescrRing);
      }
    }
    else
    {
      /* #320 For untagged frames get configured queue and associated descriptor ring index */
      descrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfQosHandling(qosHandlingIdx);
    }
  }
  /* #40 If VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType vlanIdBasesQueuingHandlingIdx = Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(ctrlIdx);
    /* #410 If the frame type indicates that the frame to be transmitted is a VLAN frame */
    if(frameType == ETH_30_TC3XX_VLAN_ETHER_TYPE)
    {
      uint16 vlanId;
      const Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapStartIdx = Eth_30_Tc3xx_GetVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
      const Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType vlanIdTxDescrRingMapEndIdx = Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);

      /* #4110 Retrieve the VLAN-ID of the frame */
      vlanId  = (uint16)(((uint16)bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET]) << 8u);
      vlanId |= (uint16)bufPtr[ETH_30_TC3XX_VLAN_TCI_UPPER_BYTE_OFFSET + 1U];
      vlanId &= (uint16)ETH_30_TC3XX_VLAN_ID_BYTE_MASK;

      /* #4120 If exists, retrieve the descriptor ring index mapped for the frame with the retrieved VLAN-ID */
      for (vlanIdTxDescrRingMapIdx = vlanIdTxDescrRingMapStartIdx; vlanIdTxDescrRingMapIdx < vlanIdTxDescrRingMapEndIdx; vlanIdTxDescrRingMapIdx++)
      {
        if ( Eth_30_Tc3xx_GetVlanIdOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx) == vlanId )
        {
          vlanIdTxDescrRing = Eth_30_Tc3xx_GetQueueIndexOfVlanIdTxDescrRingMap(vlanIdTxDescrRingMapIdx);
          break;
        }
      }

      if(vlanIdTxDescrRingMapIdx < Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx))
      {
        /* #41210 If the retrieved descriptor ring index leads to a valid global descriptor ring index */
        if ((descrRingIdx + vlanIdTxDescrRing) < Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx))
        {
          /* #412110 Overwrite the previously initialized descriptor ring index with the retrieved ring index */
          descrRingIdx = (descrRingIdx + vlanIdTxDescrRing);
        }
      }
      /* #4130 If no descriptor ring index mapping exists for the retrieved VLAN-ID */
      else
      {
        /* #41310 Use the descriptor ring index associated with untagged frames  */
        descrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
      }
    }
    else
    {
      /* #420 For untagged frames get configured queue and associated descriptor ring index */
      descrRingIdx = Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(vlanIdBasesQueuingHandlingIdx);
    }
  }
  /* #50 Retrieve the next free position in the descriptor ring used for this transmission */
  curPos          = Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(descrRingIdx);
  txDescrStartIdx = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(descrRingIdx);

  /* #60 Calculate the global descriptor index out of the global start index and the current position in the ring */
  globalDescrIdx = curPos + txDescrStartIdx;

  /* #70 If the global index was calculated correctly and is within the correct range of the descriptor ring */
  if (globalDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(descrRingIdx))
  {
    /* #710 Call the hardware dependent interface to prepare the free transmission descriptor for transmission */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_PrepareTxDescriptorForTransmission(
      ctrlIdx, descrRingIdx, globalDescrIdx, bufIdx, lenByte, bufStartPtr);                                             /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

    /* #720 Save the buffer mapped to the transmission deescriptor */
    Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(globalDescrIdx, bufIdx);                                                  /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

    /* #730 Indicate that the descriptor is ready for transmission in the corresponding global state variable */
    Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_READY);                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

    /* #740 TimeSync is enabled */
    if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #7410 If a timestamp is requested for the buffer to be transmitted */
      if (Eth_30_Tc3xx_IsTsRequestedOfTxBufferState(bufIdx) == TRUE)
      {
        /* #74110 Set up the time stamp context by saving the used descriptor ring index and descriptor position in the
         *        corresponding global variable */
        Eth_30_Tc3xx_SetRingIdxOfTxTsContext(bufIdx, (Eth_30_Tc3xx_RingIdxOfTxTsContextType)descrRingIdx);                /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        Eth_30_Tc3xx_SetDescrIdxOfTxTsContext(bufIdx, (Eth_30_Tc3xx_DescrIdxOfTxTsContextType)curPos);                    /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

        /* #74120 Call the hardware dependent interface to prepare the transmission descriptor for timestamping */
        /*lint -e{522} */
        Eth_30_Tc3xx_LL_PrepareTxDescriptorForTimestamping(ctrlIdx, descrRingIdx, globalDescrIdx, bufIdx);
      }
    }

    /* #750 If IP checksum offloading is enabled */
    if (Eth_30_Tc3xx_IsIpChecksumOffloadingEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #7510 Call the hardware dependent interface to prepare the transmission descriptor for IP checksum
       *       offloading */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_PrepareTxDescriptorForIpChecksumOffloading(ctrlIdx, descrRingIdx, globalDescrIdx);
    }
    /* #760 If Protocol checksum offloading is enabled */
    if (Eth_30_Tc3xx_IsProtocolChecksumOffloadingEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* #7610 Call the hardware dependent interface to prepare the transmission descriptor for protocol checksum
       *       offloading */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_PrepareTxDescriptorForProtocolChecksumOffloading(ctrlIdx, descrRingIdx, globalDescrIdx);
    }

    /* #770 Synchronize the RAM and peripheral register access */
    Appl_Eth_30_Tc3xx_MemoryBarrier();
    /* #780 Call the hardware dependent interface to trigger the transmission and increment the position of the next
     *      free descriptor */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_TriggerTransmission(ctrlIdx, descrRingIdx, globalDescrIdx);

    Eth_30_Tc3xx_IncTxDescRingFreePos(descrRingIdx);

# ifdef ETH_TEST_SUITE_CODE
#  ifndef _ETH_TEST_SUITE_CDK_RUN_ /* COV_ETH_TEST_SUITE */
  if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
    {
      /* Test code used for QoS/VLAN_ID based frame queuing reception queue tests */
      EthClient_TxQueueCounter[ctrlIdx][descrRingIdx]++;
    }
#  endif /* _ETH_TEST_SUITE_CDK_RUN_ */
# endif /* ETH_TEST_SUITE_CODE */
  }
} /* Eth_30_Tc3xx_VTransmit_ProcessValidFrame() */ /* PRQA S 6010, 6030, 6050, 6060, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_Receive
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_Receive(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Synchronization of hardware and software) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  (*rxStatusPtr) = ETH_NOT_RECEIVED;                                                                                    /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Check if VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #210 Assign the fifoIdx to descriptor ring index only if it is in the valid range */
    if (fifoIdx < (Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)))
    {
      descrRingIdx = fifoIdx;
    }
  }
  else
  {
    /* #220 Check for a new event in all reception rings and clear it if one is found */
    Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(ctrlIdx, &descrRingIdx, TRUE);                                           /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  }

  /* #30 If a descriptor ring with a pending reception event could be retrieved */
  if (descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
  {
    /* #310 Retrieve the next descriptor to be processed in the ring and the mapped buffer */
    Eth_30_Tc3xx_RxDescrIterType prevDescrIdx;
    Eth_30_Tc3xx_RxDescrIterType globalRxDescrIdx;
    Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx;
    Eth_30_Tc3xx_RxDescrHandlingIterType globalDescrRingIdx;
    Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType rxDescRingStartPos;
    Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType rxDescRingLocalProcPos;

    globalDescrRingIdx     = descrRingIdx + Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
    rxDescRingStartPos     = Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(globalDescrRingIdx);
    rxDescRingLocalProcPos = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(globalDescrRingIdx);
    globalRxDescrIdx       = rxDescRingStartPos + rxDescRingLocalProcPos;

    /* #320 If the retrieved rx descriptor index is valid for the descriptor ring */
    if (globalRxDescrIdx < Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(globalDescrRingIdx))
    {
      bufIdx = Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(globalRxDescrIdx);

      /* #3210 If the retrieved buffer index is valid  */
      if (bufIdx < Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(globalDescrRingIdx))
      {
        /* #32110 Synchronize the RAM and peripheral register access */
        Appl_Eth_30_Tc3xx_MemoryBarrier();

        /* #32120 If the hardware is finished with processing the descriptor holding the frame to be received */
        /*lint -e{522} */
        if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == TRUE)
        {
          prevDescrIdx = Eth_30_Tc3xx_GetRxDescrRingPrevPos(globalDescrRingIdx, globalRxDescrIdx);

          /* #321210 If there is no error flag set in the descriptor status flags */
          /*lint -e{522} */
          if (Eth_30_Tc3xx_LL_IsErrorInRxDescriptor(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == FALSE)
          {
            /* #3212110 Call the internal interface to proceed with a valid frame reception */
            Eth_30_Tc3xx_Receive_ProcessValidFrame(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx, bufIdx);
          }
          /* #321220 If an error flag is set in the descriptor status flags */
          else
          {
            /* #3212210 Discard the frame because it is invalid */
          }
          /* #321230 If the previous descriptor of the one currently operated is also still owned by the driver
           *         which means that all buffers in the currently processed ring are blocked by the software */
          if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, prevDescrIdx) == TRUE)
          {
            /* #3212310  Increment the warning counter*/
            Eth_30_Tc3xx_IncWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

            /* #3212320 If a callout is configured to be notified when the reception buffers are all in use */
            if(Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(0) != NULL_PTR)
            {
              /* #32123210 Call the configured callout to notify the user that all reception buffers are in use in the
               *           currently processed buffer ring */
              Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(0)(ctrlIdx, descrRingIdx);                                /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01 */
            }
          }
          /* #321240 Recharge the current descriptor so that the next frame can be received in it */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RechargeRxDescriptor(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx);

          /* #321250 Adapt the descriptor ring after descriptor processing has been finished */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_AdaptRxDescriptorRingAfterReception(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx);

          /* #321260 Increment the position of the current descriptor to check if already more data is available */
          Eth_30_Tc3xx_IncRxDescrRingProcPos(globalDescrRingIdx);

          /* #321270 Perform additional hardware dependent steps to rearm the MAC for further reception */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_RearmMacForReception(ctrlIdx, globalDescrRingIdx);

          /* Frames may have been lost because of a buffer overflow or unavailable buffers.
          Nevertheless no error is returned to the EthIf.
          Otherwise congestion could happen in polling mode because ETH_RECEIVED_MORE_DATA_AVAILABLE  can not be
          returned to the EthIf anymore and a maximum of one frame per mainfunction can be processed. */
          rxDescRingLocalProcPos = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(globalDescrRingIdx);
          globalRxDescrIdx       = rxDescRingStartPos + rxDescRingLocalProcPos;

          if (globalRxDescrIdx < Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(globalDescrRingIdx))
          {
            /* #321280 If the next descriptor is also already processed by the DMA and holding frame data */
            /*lint -e{522} */
            if (Eth_30_Tc3xx_LL_IsRxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalRxDescrIdx) == TRUE)
            {
              /* #3212810 Set another reception event on the corresponding descriptor ring and set the reception status
               *          to indicate that more data is available on the current reception queue only when VLAN-ID based
               *          frame queuing in not enabled since there is no need for explicit event when VLAN-ID based frame
               *          queuing is enabled */
              if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
              {
                Eth_30_Tc3xx_SetRxEvent(ctrlIdx, descrRingIdx);
              }

              (*rxStatusPtr) = ETH_RECEIVED_MORE_DATA_AVAILABLE;                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
            }
            /* #321290 If the next descriptor is not processed yet by the DMA */
            else
            {
              /* #3212910 Check for other reception rings only when VLAN-ID based frame queuing is not enabled */
              if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) != TRUE)
              {
                /* #32129110 If there was no event in any other reception ring */
                Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(ctrlIdx, &descrRingIdx, FALSE);                              /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */

                if(descrRingIdx == ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
                { /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
                  /* #321291110 Set the reception status to indicate that the reception has successfully finished */
                  (*rxStatusPtr) = ETH_RECEIVED;                                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                }
                /* #32129120 If there was a event in any other reception ring and the rx-interrupt is disabled */
                else
                { /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
                  /* #321291210 Set the reception status to indicate that more data is available */
                  (*rxStatusPtr) = ETH_RECEIVED_MORE_DATA_AVAILABLE;                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
                }
              }
              else
              {
                (*rxStatusPtr) = ETH_RECEIVED;                                                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
              }
            }

          }
        }
        /* #32130 If the hardware is not yet finished with processing the descriptor holding the frame to be received */
        else
        {
          /* #321310 Set the reception status to indicate that the reception has failed */
          (*rxStatusPtr) = ETH_NOT_RECEIVED;                                                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
        }
      }
    }
  }
  /* #40 Leave the exclusive area for data consistency */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* Eth_30_Tc3xx_Internal_Receive() */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive_ProcessValidFrame
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
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive_ProcessValidFrame(
  uint8                                      ctrlIdx,
  Eth_30_Tc3xx_RxDescrHandlingIterType        descrRingIdx,
  Eth_30_Tc3xx_RxDescrIterType                descrIdx,
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType bufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_30_Tc3xx_RxBufferIterType bufferOffsetStart;
  Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType rxBufferAlignedSegSize;
  Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType rxBufferEndIdx;
  Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType rxBufferStartIdx;

  /* ----- Implementation ----------------------------------------------- */
  rxBufferAlignedSegSize = Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(descrRingIdx);
  rxBufferStartIdx       = Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(descrRingIdx);
  rxBufferEndIdx         = Eth_30_Tc3xx_GetRxBufferEndIdxOfRxBufferHandling(descrRingIdx);

  bufferOffsetStart      = rxBufferStartIdx + (bufIdx * rxBufferAlignedSegSize);
  /* #10 If the end-index of reception buffer and the retrieved buffer start index are
   *     at least one minimum frame size apart */
  if ((bufferOffsetStart + ETH_30_TC3XX_MIN_ETH_FRAME_LEN_BYTE) <= rxBufferEndIdx)
  {
    uint16 lenByte;
    boolean isBroadcast;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetDstMac;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetSrcMac;
    Eth_30_Tc3xx_RxBufferIterType bufferOffsetEtherType;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtrDstMac;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtrSrcMac;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC) bufPtrEtherType;

    bufferOffsetDstMac    = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_DST;
    bufferOffsetSrcMac    = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_SRC;
    bufferOffsetEtherType = bufferOffsetStart + (Eth_30_Tc3xx_RxBufferIterType)ETH_30_TC3XX_LL_OFFSET_U8_LT60B_RX_TYPE;
    /* #110 Extract the received frame's length from the corresponding descriptor */
    /*lint -e{522} */
    lenByte = Eth_30_Tc3xx_LL_GetFrameLengthFromRxDescriptor(ctrlIdx, descrRingIdx, descrIdx);

    /* #120 Retrieve pointers to the positions of source and destination MAC address, the Ethernet type field and the
     *      payload data */
    bufPtrDstMac    = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetDstMac);
    bufPtrSrcMac    = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetSrcMac);
    bufPtrEtherType = Eth_30_Tc3xx_GetAddrRxBuffer(bufferOffsetEtherType);

    /* #130 Check whether the received frame is a broadcast */
    isBroadcast = Eth_30_Tc3xx_IsBroadcast(bufPtrDstMac);                                                                /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_PASS_CSL0X */

    lenByte -= ETH_30_TC3XX_LL_OFFSET_U8_LT60B_DEST_SRC_MACS_LEN_BYTE;

    /* #140 If the reception of the frame is allowed */
    if (Eth_30_Tc3xx_IsFrameRxAllowed(ctrlIdx, (Eth_BufIdxType)bufIdx, &bufPtrEtherType, &lenByte) == TRUE)              /* SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X */
    {
      /* #1410 If the returned buffer length of the switch management interface is valid for a frame holding a payload */
      if ((bufferOffsetStart + lenByte) < rxBufferEndIdx)
      {
        uint16 frameType;
        P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC)            bufPtrData;
        Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType         rxIndCallout;
        Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType rxTxCalloutsIdx;

        /* #14310 Retrieve the frame type */
        frameType  = (uint16)((uint16)bufPtrEtherType[ETH_30_TC3XX_FRAME_TYPE_LS_BYTE_IDX]
                                                   << ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_LSHIFT);
        frameType |=          (uint16)bufPtrEtherType[ETH_30_TC3XX_FRAME_TYPE_MS_BYTE_IDX];

        /* #14320 retrieve a pointer to the payload of the frame */
        /* PRQA S 3305, 0310 1 */ /* MD_Eth_30_Tc3xx_3305, MD_Eth_30_Tc3xx_0310 */
        bufPtrData = (P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC))(&bufPtrEtherType[ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE]);

        /* #14330 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) /* PRQA S 0715 1 */ /* MD_MSR_1.1_715 */
        {
          Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType procPos;
          Eth_30_Tc3xx_RxDescrRingProcIterType rxDescrRingProcIdx;
          Eth_30_Tc3xx_RxTsContextStackPosType rxTsContextStackPos;
          Eth_30_Tc3xx_RxTsContextStackIterType rxTsContextStackIdx;
          Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType rxTsContextEndIdx;
          Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType rxTsContextStackStartIdx;

          rxDescrRingProcIdx = Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(descrRingIdx);
          procPos            = Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(rxDescrRingProcIdx);

          /* #143310 Increment the reception timestamp context stack position and save descriptor and ring index in the
           *         global context variable */
          Eth_30_Tc3xx_IncRxTsContextStackPos(ctrlIdx);                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

          rxTsContextStackPos      = Eth_30_Tc3xx_GetRxTsContextStackPos(ctrlIdx);
          rxTsContextStackStartIdx = Eth_30_Tc3xx_GetRxTsContextStackStartIdxOfTsHandling(ctrlIdx);
          rxTsContextEndIdx        = Eth_30_Tc3xx_GetRxTsContextStackEndIdxOfTsHandling(ctrlIdx);
          rxTsContextStackIdx      = rxTsContextStackStartIdx + rxTsContextStackPos;

          if (rxTsContextStackIdx < rxTsContextEndIdx)
          {
            Eth_30_Tc3xx_SetRingIdxOfRxTsContextStack(rxTsContextStackIdx,                                               /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK */
                (Eth_30_Tc3xx_RingIdxOfRxTsContextStackType)descrRingIdx);
            Eth_30_Tc3xx_SetDescrIdxOfRxTsContextStack(rxTsContextStackIdx, procPos);                                    /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK */
          }
        }

        rxTxCalloutsIdx = Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(ctrlIdx);
        rxIndCallout    = Eth_30_Tc3xx_GetRxIndicationCalloutOfRxTxNotificationCallouts(rxTxCalloutsIdx);
        /* #14340 Leave the exclusive area for data consistency for the upper layer call to be performed next */
        Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

# ifdef ETH_TEST_SUITE_CODE
#  ifndef _ETH_TEST_SUITE_CDK_RUN_ /* COV_ETH_TEST_SUITE */
        if (Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(ctrlIdx) == TRUE)
        {
          /* Test code used for QoS/VLAN_ID based frame queuing reception queue tests */
          EthClient_RxQueueCounter[ctrlIdx][descrRingIdx]++;
        }
#  endif /* _ETH_TEST_SUITE_CDK_RUN_ */
# endif /* ETH_TEST_SUITE_CODE */

        /* #14350 If no user callout to be called instead of the Rx-Indication is configured */
        if (rxIndCallout == NULL_PTR)
        {
          /* #143510 Call the EthIf Rx-Indication */
          EthIf_RxIndication(                                                                                           /* SBSW_ETH_30_TC3XX_PUB_FCT_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC */
              Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx),
              frameType,
              isBroadcast,
              bufPtrSrcMac,
              bufPtrData,
              (uint16)(lenByte - ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE));
        }
        /* #14360 If a user callout to be called instead of the Rx-Indication is configured */
        else
        {
          /* #143610 Call the user callout */
          rxIndCallout(                                                                                                 /* SBSW_ETH_30_TC3XX_OPT_API_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC_CSL03 */
              Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx),
              frameType,
              isBroadcast,
              bufPtrSrcMac,
              bufPtrData,
              (uint16)(lenByte - ETH_30_TC3XX_LT60B_FRAME_TYPE_LEN_BYTE));
        }
        /* #14370 Enter the exclusive area for data consistency again (Reason: Hardware and software synchronization) */
        Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #14380 If TimeSync is enabled */
        if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE) /* PRQA S 0715 1 */ /* MD_MSR_1.1_715 */
        {
          /* #143810 Decrement the current reception timestamp context stack position */
          Eth_30_Tc3xx_DecRxTsContextStackPos(ctrlIdx);                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
        }
      }
    }
    /* #150 Finish the frame reception */
    Eth_30_Tc3xx_FinishFrameRx(ctrlIdx, (Eth_BufIdxType)bufIdx);
  }
} /* Eth_30_Tc3xx_Receive_ProcessValidFrame() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */


/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent(
        uint8                        ctrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) descrRingIdxPtr,
        boolean                      isClearRequired)
{
  /* #10 If the reception interrupt is disabled */
  if (Eth_30_Tc3xx_IsRxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
  {
    /* #110 Set pending reception events in the software if they are pending on the hardware */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_SetRxEvents(ctrlIdx);
  }

  /* #20 If the caller requests that a check and clear for the highest priority reception event is made */
  if(isClearRequired == TRUE)
  {
    /* #210 Check for the highest priority reception event and clear it */
    *descrRingIdxPtr = Eth_30_Tc3xx_GetAndClearHighestPrioPendingRxEventDescrRing(ctrlIdx);                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 If no clear is required */
  else
  {
    /* #310 Only check for an occurred event */
    *descrRingIdxPtr = Eth_30_Tc3xx_GetHighestPrioPendingRxEventDescrRing(ctrlIdx);                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
} /* Eth_30_Tc3xx_Internal_SetAndCheckForRingEvent */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_TxConfirmation
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
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_TxConfirmation(
  uint8 ctrlIdx,
  uint8 fifoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 descrRingIdx = ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 If the frame transmission interrupt is disabled */
  if (Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
  {
    /* #110 Set pending transmission events in the software if they are pending on the hardware */
    /*lint -e{522} */
    Eth_30_Tc3xx_LL_SetTxEvents(ctrlIdx);
  }

  /* #20 Check if VLAN-ID based frame queuing is enabled */
  if (Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(ctrlIdx) == TRUE)
  {
    /* #210 Assign the fifoIdx to descriptor ring index if it is in the valid range */
    if (fifoIdx < (Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(ctrlIdx) - Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx)))
    {
      descrRingIdx = fifoIdx;
    }
  }
  else
  {
    /* #220 Retrieve the descriptor ring index of the highest priority transmission queue with a pending event */
    descrRingIdx = Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(ctrlIdx);
  }

  /* #30 If a descriptor ring with a pending reception event could be retrieved */
  if (descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
  {
    Eth_30_Tc3xx_TxDescrIterType globalDescrIdx;
    Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType curDescrPos;
    Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType txDescrStartIdx;
    Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType txDescrRingProcIdx;
    Eth_30_Tc3xx_TxDescrHandlingIterType globalDescrRingIdx;

    /* #310 Retrieve the last processed descriptor index */
    globalDescrRingIdx = descrRingIdx + Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
    txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(globalDescrRingIdx);
    txDescrStartIdx    = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);
    curDescrPos        = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);

    globalDescrIdx = txDescrStartIdx + curDescrPos;
    /* #320 Enter exclusive area (Reason: Hardware and software synchronization)  */
    Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #330 Repeat while the currently checked descriptor is owned by the driver, indicating that the hardware
     *      processing is finished */
    /* PRQA S 3415 2 */ /* MD_Eth_30_Tc3xx_3415 */ /*lint -e{522} */
    while ((Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalDescrIdx) == TRUE) &&
           (Eth_30_Tc3xx_GetTxReadyOfTxDescrState(globalDescrIdx) == ETH_30_TC3XX_DESCRIPTOR_READY)      &&
           (globalDescrIdx < Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(globalDescrRingIdx)))
    {
      Eth_30_Tc3xx_MappedBufferOfTxDescrStateType relatedBufIdx;
      /* #3310 Retrieve the mapped buffer of the currently checked descriptor */
      relatedBufIdx = Eth_30_Tc3xx_GetMappedBufferOfTxDescrState(globalDescrIdx);

      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED);                         /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

      /* #3320 If the upper layer requested to be notified about the finished transmission */
      if (Eth_30_Tc3xx_GetUlTxConfStateOfTxBufferState(relatedBufIdx) == ETH_30_TC3XX_TX_STATE_CONFIRMATION_PENDING)
      {
        Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType       txConfCallout;
        Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType rxTxCalloutsIdx;

        rxTxCalloutsIdx = Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(ctrlIdx);
        txConfCallout   = Eth_30_Tc3xx_GetTxConfirmationCalloutOfRxTxNotificationCallouts(rxTxCalloutsIdx);

        /* #33210 Leave the exclusive area for data consistency for the upper layer call to be performed next */
        Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        /* #33220 If no user callout was configured to be called instead of the EthIf_TxConfirmation */
        if (txConfCallout == NULL_PTR)
        {
          /* #332210 Call the EthIf TxConfirmation */
          EthIf_TxConfirmation(Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx), relatedBufIdx);
        }
        /* #33230 If a user callout was configured to be called instead of the EthIf TxConfirmation */
        else
        {
          /* #332310 Call the user callout */
          txConfCallout(Eth_30_Tc3xx_TransformToGlobalCtrlIdx(ctrlIdx), relatedBufIdx);                                  /* SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL03 */
        }

        /* #33240 Enter the exclusive area for data consistency again (Reason: Hardware and software synchronization) */
        Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

        Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(relatedBufIdx, ETH_30_TC3XX_TX_STATE_CONFIRMATION_NOT_PENDING);      /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */
      }

      /* #3330 If TimeSync is enabled */
      if (Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(ctrlIdx) == TRUE)
      {
        /* #33310 Reset the buffer state variable indicating if a timestamp is requested */
        Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(relatedBufIdx, ETH_30_TC3XX_TIMESYNC_TS_NOT_REQUESTED);                /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */

        /* #33320 Call the hardware dependent interface to reset the timestamp in the transmission descriptor */
        /*lint -e{522} */
        Eth_30_Tc3xx_LL_ResetTimestampingInTxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx);
      }

      /* #3340 Release the mapped buffer so it can be used for transmission again */
      Eth_30_Tc3xx_SetTxReadyOfTxDescrState(globalDescrIdx, ETH_30_TC3XX_DESCRIPTOR_NOT_READY);                           /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */
      Eth_30_Tc3xx_SetBusyOfTxBufferState(relatedBufIdx, FALSE);                                                         /* SBSW_ETH_30_TC3XX_COMMON_CSL01 */
      Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(globalDescrIdx, 0);                                                     /* SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING */

      /* #3350 Recharge the transmission descriptor so it can be used for transmission again */
      Eth_30_Tc3xx_LL_RechargeTxDescriptor(ctrlIdx, globalDescrRingIdx, globalDescrIdx);

      /* #3360 Increment the descriptor index to check the next descriptor */
      Eth_30_Tc3xx_IncTxDescRingProcPos(globalDescrRingIdx);
      curDescrPos = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
      globalDescrIdx = txDescrStartIdx + curDescrPos;

      /* #3370 In polling mode */
      if (Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(ctrlIdx) == FALSE)
      {
        /* #33710 If the currently checked ring is finished processing */
        if(Eth_30_Tc3xx_LL_IsTxDescriptorOwnedByDriver(ctrlIdx, globalDescrRingIdx, globalDescrIdx) == FALSE)
        {
          /* #337110 Check for events of other queues */
          /*lint -e{522} */
          Eth_30_Tc3xx_LL_SetTxEvents(ctrlIdx);
          descrRingIdx = Eth_30_Tc3xx_GetAndClearHighestPrioPendingTxEventDescrRing(ctrlIdx);

          /* #337120 If another event has occurred */
          if(descrRingIdx != ETH_30_TC3XX_UNDEFINED_DESCRIPTOR_RING)
          {
            /* #3371210 Calculate the indices of the descriptor to be checked */
            globalDescrRingIdx = descrRingIdx + Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(ctrlIdx);
            txDescrRingProcIdx = Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(globalDescrRingIdx);
            txDescrStartIdx    = Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(globalDescrRingIdx);
            curDescrPos        = Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(txDescrRingProcIdx);
            globalDescrIdx     = txDescrStartIdx + curDescrPos;
          }
          /* #337130 Otherwise */
          else
          {
            /* #3371310 Leave the loop */
            break;
          }
        }
      }
    }
    /* #340 Leave the exclusive area for data consistency */
    Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
} /* Eth_30_Tc3xx_Internal_TxConfirmation() */ /* PRQA S 6010, 6030, 6050, 6080 */ /* MD_MSR_STPTH, MD_MSR_STCYC, MD_MSR_STCAL, MD_MSR_STMIF */

# if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetRxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetRxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) rxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all statistics to invalid values */
  rxStatsPtr->RxStatsDropEvents           = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsOctets               = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts                 = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsBroadcastPkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsMulticastPkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsCrcAlignErrors       = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsUndersizePkts        = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsOversizePkts         = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsFragments            = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsJabbers              = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsCollisions           = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts64Octets         = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts65to127Octets    = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts128to255Octets   = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts256to511Octets   = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts512to1023Octets  = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxStatsPkts1024to1518Octets = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  rxStatsPtr->RxUnicastFrames             = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                               /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Enter exclusive area (Reason: Consistent result for the counters) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Read the RX statistics counter registers and report the results */
  retVal = Eth_30_Tc3xx_LL_GetRxStats(ctrlIdx, rxStatsPtr);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */
  /* #40 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetRxStats */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetTxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetTxStats(
        uint8                                  ctrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) txStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all statistics to invalid values */
  txStatsPtr->TxNumberOfOctets = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxNUcastPkts     = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  txStatsPtr->TxUniCastPkts    = ETH_30_TC3XX_TXRX_STATS_INVALID_COUNTER_VALUE;                                          /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Enter exclusive area (Reason: Consistent result for the counters) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  /* #30 Read the TX statistics counter registers and report the results */
  retVal = Eth_30_Tc3xx_LL_GetTxStats(ctrlIdx, txStatsPtr);                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS */

  /* #40 Leave exclusive area  */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetTxStats */
# endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

# if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
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
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(
        uint8                         ctrlIdx,
        Eth_MeasurementIdxType        measIdx,
        boolean                       resetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) measurementData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  boolean isHwCtrResetOnRead;
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType rxDropCounter;
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType readCounterValue;

  /* #10 Enter exclusive area (Reason: Update statistic counters in a consistent manner) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 If the MeasurementIdx is set to ETH_MEAS_ALL */
  if (measIdx == ETH_MEAS_ALL)
  {
    /* #210 If a reset of the counter values is requested */
    if (resetNeeded == TRUE)
    {
      /* #2110 Reset all measurement data statistics */
      Eth_30_Tc3xx_Internal_ClearMeasurementData(ctrlIdx);
    }
    /* #220 If Reset needed is set to false */
    else
    {
      /* #2210 Return Not OK since MeasrementIdx ETH_MEAS_ALL only supported for reset of all statistics */
      retVal = E_NOT_OK;
    }
  }
  /* #30 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER */
  else if (measIdx == ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER)
  {
    /* #310 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_TX_BUFFER counter */
    Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
        measurementData,
        Eth_30_Tc3xx_GetAddrDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx),
        resetNeeded);
  }
  /* #40 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER */
  else if (measIdx == ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER)
  {
    /* #410 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_WARN_FULL_RX_BUFFER counter */
    Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(                                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
        measurementData,
        Eth_30_Tc3xx_GetAddrWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx),
        resetNeeded);
  }
  /* #50 If the MeasurementIdx is set to ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER */
  else if (measIdx == ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER)
  {
    /* #510 Try to read the counter value from the hardware */
    retVal = Eth_30_Tc3xx_LL_GetDropInsuffRxBuffHwCounter(                                                               /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
        ctrlIdx,
        &readCounterValue,
        &isHwCtrResetOnRead);

    /* #5110 If the hardware counter could be read successfully */
    if(retVal == E_OK)
    {
      /* #51110 If the hardware counter is reset on read */
      if(isHwCtrResetOnRead == TRUE)
      {
        rxDropCounter = Eth_30_Tc3xx_GetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx);

        /* #511110 The current software counter value of the counter has to be added to the read value */
        Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, rxDropCounter + readCounterValue);                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      }
      /* #5120 If the hardware counter is not reset on read */
      else
      {
        /* #51210 Set the software counter variable to the read value */
        Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, readCounterValue);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */

        /* #51220 If a reset is requested for the counter */
        if(resetNeeded == TRUE)
        {
          /* #512210 Make sure the hardware counter is reset as well since it is not reset on read */
          retVal = Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);
        }
      }

      /* #5130 Call the internal api to get and/or reset ETH_MEAS_VENDOR_SPECIFIC_DROP_INSUFF_RX_BUFFER counter */
      Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
          measurementData,
          Eth_30_Tc3xx_GetAddrDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx) ,                                            /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA */
          resetNeeded);
    }
  }
  /* #60 Measurement index is not supported / unknown */
  else
  {
    retVal = E_NOT_OK;
  }
  /* #70 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* Eth_30_Tc3xx_Internal_GetAndResetMeasurementData() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_GetAndResetMeasurementDataSwCounter
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_GetAndResetMeasDataSwCounter(
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measurementDataPtr,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC)  measDataStatsCtrPtr,
        boolean                        ResetNeeded)
{
  /* #20 Only provide measurement data statistics value if pointer is no NULL_PTR */
  if (measurementDataPtr != NULL_PTR)
  {
    (*measurementDataPtr) = (*measDataStatsCtrPtr);                                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_ACCESS_POSSIBLE_NULL_PTR_AFTER_NULL_PTR_CHECK */
  }
  /* #30 Only reset measurement data statistics value if reset is requested */
  if (ResetNeeded == TRUE)
  {
    (*measDataStatsCtrPtr) = 0u;                                                                                        /* SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE */
  }
} /* Eth_30_Tc3xx_Internal_GetAndResetMeasurementDataSwCounter */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_Internal_ClearMeasurementData
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Internal_ClearMeasurementData(uint8 ctrlIdx)
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Enter exclusive area (Reason: Clear statistic counters in an atomic operation) */
  Eth_30_Tc3xx_EnterExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 Clear all measurement data statistic counters */
  Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                       /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
  (void)Eth_30_Tc3xx_LL_ResetDropInsuffRxBuffHwCounter(ctrlIdx);

  /* #30 Leave exclusive area */
  Eth_30_Tc3xx_ExitExclusiveArea(DATA); /* PRQA S 3109 */ /* MD_MSR_14.3 */
} /* Eth_30_Tc3xx_Internal_ClearMeasurementData() */
# endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  {
    /* #10 Initialize state variables for DET checks */
    Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_UNINIT;
  }
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
} /* Eth_30_Tc3xx_InitMemory() */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Init
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
 *
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Init(
  P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_CONST, ETH_30_TC3XX_CONST) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least ctrlIdx = 0;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  uint8 ctrlIdxNoValidAlignment;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* #10 Assign the parameter config pointer to the global config data pointer variable */
  Eth_30_Tc3xx_ConfigDataPtr = CfgPtr;

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #20 Initialize the controller index for the alignment check */
  if (Eth_30_Tc3xx_ConfigDataPtr != NULL_PTR)
  {
    ctrlIdxNoValidAlignment = Eth_30_Tc3xx_GetSizeOfEthCtrl();
  }
  else
  {
    ctrlIdxNoValidAlignment = 0;
  }

  /* #30 Check plausibility of the input parameter */
  if (CfgPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
  /* #40 If the descriptor and/or buffer alignment is invalid */
  else if (Eth_30_Tc3xx_IsValidAlignment(&ctrlIdxNoValidAlignment) == FALSE)                                          /* SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR */
  {
    /* #410 Set the local controller index to the returned value for which the alignment was invalid */
    ctrlIdx = ctrlIdxNoValidAlignment;
    errorId = ETH_30_TC3XX_E_INV_ALIGNMENT;
  }
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
      Eth_30_Tc3xx_ModuleInitialized = ETH_STATE_INIT;
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

    /* #50 Loop over all configured controllers */
    for (ctrlIdx = 0; ctrlIdx < Eth_30_Tc3xx_GetSizeOfEthCtrl(); ctrlIdx++)
    {
      Eth_30_Tc3xx_InitialMacAddressIterType initialMacAddrIdx;
      Eth_30_Tc3xx_ActiveMacAddressIterType activeMacAddrIdx;
      /* #510 Initialize global mode variables */
      Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(ctrlIdx, ETH_MODE_DOWN);                                                 /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */

      /* #520 Copy physical address from ROM to RAM variable */
      initialMacAddrIdx = Eth_30_Tc3xx_GetInitialMacAddressStartIdxOfEthCtrl(ctrlIdx);

      for (activeMacAddrIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(ctrlIdx);
           activeMacAddrIdx < Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(ctrlIdx);
           activeMacAddrIdx++)
      {
        Eth_30_Tc3xx_SetActiveMacAddress(activeMacAddrIdx,                                                            /* SBSW_ETH_30_TC3XX_COMMON_CSL03 */
            Eth_30_Tc3xx_GetInitialMacAddress(initialMacAddrIdx));

        initialMacAddrIdx++;
      }
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
      /* #530 Copy register base address from ROM to RAM variable */
      Eth_30_Tc3xx_SetRegBaseAddrOfEthCtrlState((uint8)ctrlIdx,                                                       /* SBSW_ETH_30_TC3XX_COMMON_CSL02 */
          Eth_30_Tc3xx_GetAutosarRtmRegBaseAddrOfEthCtrl((uint8)ctrlIdx));
      /* #540 Enable MII Access so that Transceiver can be initialized during VSwitchInit */
      /*lint -e{522} */
      Eth_30_Tc3xx_LL_EnableMiiAccess((uint8)ctrlIdx);
#else
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
      ETH_30_TC3XX_DUMMY_STATEMENT_CONST(ctrlIdxNoValidAlignment); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */

      /* #550 Initialize the measurement counters */
      Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                   /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
      Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(ctrlIdx, 0u);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS */
    }
  }

  ETH_30_TC3XX_DUMMY_STATEMENT_CONST(CfgPtr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID, Eth_30_Tc3xx_TransformToGlobalCtrlIdx((uint8)ctrlIdx), ETH_30_TC3XX_SID_INIT, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  ETH_30_TC3XX_DUMMY_STATEMENT(ctrlIdx); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_Init() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ControllerInit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ControllerInit(
  uint8 CtrlIdx,
  uint8 CfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CfgIdx > ETH_30_TC3XX_MAX_CFGS_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_CONFIG;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* trigger start of runtime measurement */
    Eth_30_Tc3xx_Rtm_Start(ControllerInit);
    /* #20 Call the internal or host controller interface to initialize an Ethernet controller */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ControllerInit(localCtrlIdx, CfgIdx);
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ControllerInit(localCtrlIdx, CfgIdx);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
    /* trigger stop of runtime measurement */
    Eth_30_Tc3xx_Rtm_Stop(ControllerInit);
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_CONTROLLER_INIT, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ControllerInit */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_SetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetControllerMode(
  uint8        CtrlIdx,
  Eth_ModeType CtrlMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface set the Ethernet controller's mode */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_SetControllerMode(localCtrlIdx, CtrlMode);
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_SetControllerMode(localCtrlIdx, CtrlMode);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_SET_CONTROLLER_MODE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_SetControllerMode */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetControllerMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetControllerMode(
        uint8                               CtrlIdx,
  P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) CtrlModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;

  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrlModePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #20 Call the internal or host controller interface set the Ethernet controller's mode */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetControllerMode(localCtrlIdx, CtrlModePtr);                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetControllerMode(localCtrlIdx, CtrlModePtr);                                   /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_CONTROLLER_MODE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_GetControllerMode */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetPhysAddr
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPhysAddr(
        uint8                        CtrlIdx,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)

{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

   /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  /* ----- Implementation ----------------------------------------------- */
  {
    /* #20 Call the internal or host controller interface get the Ethernet controller's physical address */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_GetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_GetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
/* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_PHYS_ADDR, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_GetPhysAddr() */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_SetPhysAddr
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC (void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPhysAddr(
          uint8                        CtrlIdx,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface set the Ethernet controller's physical address */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_SetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                     /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_SetPhysAddr(localCtrlIdx, PhysAddrPtr);                                                  /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_SET_PHYS_ADDR, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_SetPhysAddr() */

#if (ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC (Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_UpdatePhysAddrFilter(
          uint8                                      CtrlIdx,
  P2CONST(uint8,               AUTOMATIC, AUTOMATIC) PhysAddrPtr,
          Eth_FilterActionType                       Action)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (PhysAddrPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to update the physical address filter  */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_UpdatePhysAddrFilter(localCtrlIdx, PhysAddrPtr, Action);                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_UpdatePhysAddrFilter(localCtrlIdx, PhysAddrPtr, Action);                        /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_UPDATE_PHYS_ADDR_FILTER, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
  return retVal;
} /* Eth_30_Tc3xx_UpdatePhysAddrFilter */
#endif /* ETH_30_TC3XX_ENABLE_UPDATE_PHYS_ADDR_FILTER */

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_WriteMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_WriteMii(
  uint8  CtrlIdx,
  uint8  TrcvIdx,
  uint8  RegIdx,
  uint16 RegVal)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (RegIdx >= ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to write on the MII-management interface */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_WriteMii(localCtrlIdx, TrcvIdx, RegIdx, RegVal);
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_WriteMii(localCtrlIdx, TrcvIdx, RegIdx, RegVal);
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_WRITE_MII, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_WriteMii */
#endif /* ETH_30_TC3XX_MII_INTERFACE */

#if (ETH_30_TC3XX_MII_INTERFACE == STD_ON) /* COV_ETH_MII_INTERFACE */
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ReadMii
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Eth_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReadMii(
        uint8                         CtrlIdx,
        uint8                         TrcvIdx,
        uint8                         RegIdx,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Eth_ReturnType retVal = ETH_E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (RegIdx > ETH_30_TC3XX_MAX_MII_REG_TOTAL)
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (RegValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to read on the MII-management interface */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ReadMii(localCtrlIdx, TrcvIdx, RegIdx, RegValPtr);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ReadMii(localCtrlIdx, TrcvIdx, RegIdx, RegValPtr);                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
   (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_READ_MII, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ReadMii */
#endif /* ETH_30_TC3XX_MII_INTERFACE */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetCounterState
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCounterState(
        uint8                         CtrlIdx,
        uint16                        CtrOffs,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) CtrValPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  Std_ReturnType retVal = E_NOT_OK;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (CtrValPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to read a statistic counter value */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetCounterState(localCtrlIdx, CtrOffs, CtrValPtr);                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetCounterState(localCtrlIdx, CtrOffs, CtrValPtr);                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_COUNTER_STATE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_GetCounterState */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_ProvideTxBuffer
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(BufReq_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ProvideTxBuffer(
              uint8                                                      CtrlIdx,
        P2VAR(uint8,        AUTOMATIC, AUTOMATIC)                        BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC) BufPtr,
        P2VAR(uint16,       AUTOMATIC, AUTOMATIC)                        LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (BufIdxPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (BufPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (LenBytePtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to provide a transmission buffer */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_ProvideTxBuffer(localCtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_ProvideTxBuffer(localCtrlIdx, BufIdxPtr, BufPtr, LenBytePtr);                   /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_PROVIDE_TX_BUFFER, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_ProvideTxBuffer */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Transmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Transmit(
          uint8                        CtrlIdx,
          uint8                        BufIdx,
          Eth_FrameType                FrameType,
          boolean                      TxConfirmation,
          uint16                       LenByte,
  P2CONST(uint8, AUTOMATIC, AUTOMATIC) PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* ----- Implementation ----------------------------------------------- */
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);
  Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType activeMacAddrStartIdx;

  activeMacAddrStartIdx = Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(localCtrlIdx);
  /* #10 Call Eth_30_Tc3xx_VTransmit() function with the ECUs own source MAC address as PhysAddrSrcPtr parameter */
  /* no transformation between local and global controller index necessary */
  return Eth_30_Tc3xx_VTransmit(CtrlIdx,                                                                              /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_AND_CSL_PTR_PASS */
                               BufIdx,
                               FrameType,
                               TxConfirmation,
                               LenByte,
                               PhysAddrPtr, /* PRQA S 0310 1 */ /* MD_Eth_30_Tc3xx_0310 */
                               (const uint8*)Eth_30_Tc3xx_GetAddrActiveMacAddress(activeMacAddrStartIdx)); /*lint !e545 */
} /* Eth_30_Tc3xx_Transmit */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_VTransmit
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_VTransmit(
          uint8                               CtrlIdx,
          uint8                               BufIdx,
          Eth_FrameType                       FrameType,
          boolean                             TxConfirmation,
          uint16                              LenByte,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrDstPtr,
  P2CONST(uint8,        AUTOMATIC, AUTOMATIC) PhysAddrSrcPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_NOT_OK;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_OFF)
  ETH_30_TC3XX_DUMMY_STATEMENT(retVal); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
  else if(BufIdx >= Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(localCtrlIdx)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
  else if (LenByte > (Eth_30_Tc3xx_GetLengthOfTxBufferData(BufIdx) -
                        (ETH_30_TC3XX_HDR_LEN_BYTE + ETH_30_TC3XX_LL_OFFSET_U8_LT60B_USED_FCS_LEN_BYTE)))
  {
    errorId = ETH_30_TC3XX_E_INV_PARAM;
  }
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  else if (PhysAddrDstPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else if (PhysAddrSrcPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to transmit a frame */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_VTransmit(
        localCtrlIdx, BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrDstPtr, PhysAddrSrcPtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_VTransmit(
        localCtrlIdx, BufIdx, FrameType, TxConfirmation, LenByte, PhysAddrDstPtr, PhysAddrSrcPtr);                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */

  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_TRANSMIT, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */

  return retVal;
} /* Eth_30_Tc3xx_VTransmit */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_Receive
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_Receive(
        uint8                                   CtrlIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) RxStatusPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else if (RxStatusPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to receive a frame */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_Receive(localCtrlIdx, ETH_30_TC3XX_INVALID_FIFO_IDX, RxStatusPtr);                                                         /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_Receive(localCtrlIdx, RxStatusPtr);                                                      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_RECEIVE, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_Receive */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmation
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmation(
  uint8 CtrlIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check plausibility of input parameters and initialization state */
  if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  else if (Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(localCtrlIdx) == ETH_MODE_DOWN)
  {
    errorId = ETH_30_TC3XX_E_INV_MODE;
  }
  else
#endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to confirm a frame transmission */
#if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    Eth_30_Tc3xx_Internal_TxConfirmation(localCtrlIdx, ETH_30_TC3XX_INVALID_FIFO_IDX);
#else
    Eth_30_Tc3xx_LL_HostCtrlIfc_TxConfirmation(localCtrlIdx);
#endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
#if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_TX_CONFIRMATION, errorId);
  }
#else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_TxConfirmation */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_MainFunction
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_MainFunction( void )
{
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Call the hardware dependent main function */
  /*lint -e{522} */
  Eth_30_Tc3xx_LL_MainFunction();
} /* Eth_30_Tc3xx_MainFunction */

#if (ETH_30_TC3XX_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVersionInfo(
  P2VAR(Std_VersionInfoType, ETH_30_TC3XX_APPL_DATA, ETH_30_TC3XX_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
   uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check parameter for plausibility */
  if (VersionInfoPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif /* ETH_30_TC3XX_DEV_ERROR_DETECT */
  {
    /* #20 Return Vendor Id, Module Id and SW version number */
    VersionInfoPtr->vendorID = ETH_30_TC3XX_VENDOR_ID;                                                                /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->moduleID = ETH_30_TC3XX_MODULE_ID;                                                                /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_major_version = ETH_30_TC3XX_SW_MAJOR_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_minor_version = ETH_30_TC3XX_SW_MINOR_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
    VersionInfoPtr->sw_patch_version = ETH_30_TC3XX_SW_PATCH_VERSION;                                                 /* SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, 0, ETH_30_TC3XX_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif /* ETH_30_TC3XX_DEV_ERROR_REPORT */
} /* Eth_30_Tc3xx_GetVersionInfo() */
#endif /* ETH_30_TC3XX_VERSION_INFO_API */

#if (ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API == STD_ON)
/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetRxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_RxStatsType, AUTOMATIC, AUTOMATIC) RxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'RxStatsPtr' */
  else if (RxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to retrieve the reception statistics */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetRxStats(localCtrlIdx, RxStatsPtr);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetRxStats(localCtrlIdx, RxStatsPtr);                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_RX_STATS, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetRxStats */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_GetTxStats()
 *********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxStats(
        uint8                                  CtrlIdx,
  P2VAR(Eth_TxStatsType, AUTOMATIC, AUTOMATIC) TxStatsPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (localCtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  /* Check parameter 'TxStatsPtr' */
  else if (TxStatsPtr == NULL_PTR)
  {
    errorId = ETH_30_TC3XX_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #20 Call the internal or host controller interface to retrieve the transmission statistics */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetTxStats(localCtrlIdx, TxStatsPtr);                                                 /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetTxStats(localCtrlIdx, TxStatsPtr);                                           /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(ETH_30_TC3XX_MODULE_ID, CtrlIdx, ETH_30_TC3XX_SID_GET_TX_STATS, errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetTxStats() */
#endif /* ETH_30_TC3XX_ENABLE_GET_ETHER_STATS_API */

#if (ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API == STD_ON)
/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetAndResetMeasurementData
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAndResetMeasurementData(
  uint8                               CtrlIdx,
  Eth_MeasurementIdxType              MeasIdx,
  boolean                             ResetNeeded,
  P2VAR(uint32, AUTOMATIC, AUTOMATIC) MeasurementData)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8 errorId = ETH_30_TC3XX_E_NO_ERROR;
  uint8 localCtrlIdx = Eth_30_Tc3xx_TransformToLocalCtrlIdx(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_DETECT == STD_ON)
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  /* Check initialization state of the component */
  if (Eth_30_Tc3xx_ModuleInitialized == ETH_STATE_UNINIT)
  {
    errorId = ETH_30_TC3XX_E_NOT_INITIALIZED;
  }
  /* Check parameter 'CtrlIdx' */
  else if (CtrlIdx >= Eth_30_Tc3xx_GetSizeOfEthCtrl())
  {
    errorId = ETH_30_TC3XX_E_INV_CTRL_IDX;
  }
  else
# endif
  {
    /* #20 Call the internal or host controller interface to retrieve and/or reset the measurement data */
# if (ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE == STD_OFF) /* COV_ETH_HOST_CTRL_INTERFACE */
    retVal = Eth_30_Tc3xx_Internal_GetAndResetMeasurementData(localCtrlIdx, MeasIdx, ResetNeeded, MeasurementData);      /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# else
    retVal = Eth_30_Tc3xx_LL_HostCtrlIfc_GetAndResetMeasurementData(localCtrlIdx, MeasIdx, ResetNeeded, MeasurementData);/* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
# endif /* ETH_30_TC3XX_ENABLE_HOST_CTRL_INTERFACE */
  }
  /* ----- Development Error Report --------------------------------------- */
# if (ETH_30_TC3XX_DEV_ERROR_REPORT == STD_ON)
  if (errorId != ETH_30_TC3XX_E_NO_ERROR)
  {
    (void)Det_ReportError(
        ETH_30_TC3XX_MODULE_ID,
        Eth_30_Tc3xx_TransformToGlobalCtrlIdx(CtrlIdx),
        ETH_30_TC3XX_SID_GET_AND_RESET_MEASUREMENT_DATA_API,
        errorId);
  }
# else
  ETH_30_TC3XX_DUMMY_STATEMENT(errorId); /* PRQA S 3112 */ /* MD_MSR_14.2 */
# endif

  return retVal;
} /* Eth_30_Tc3xx_GetAndResetMeasurementData() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */
#endif /* ETH_30_TC3XX_GET_AND_RESET_MEASUREMENT_DATA_API */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_ReceiveFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_ReceiveFifo(
        uint8                                   ctrlIdx,
        uint8                                   fifoIdx,
  P2VAR(Eth_RxStatusType, AUTOMATIC, AUTOMATIC) rxStatusPtr)
{
  /* #10 Call internal receive Confirmation with passed fifoIdx */
  Eth_30_Tc3xx_Internal_Receive(ctrlIdx, fifoIdx, rxStatusPtr);                                /* SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS */
} /* Eth_30_Tc3xx_ReceiveFifo */

/**********************************************************************************************************************
 *  Eth_30_Tc3xx_TxConfirmationFifo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TxConfirmationFifo(
  uint8 ctrlIdx,
  uint8 fifoIdx)
{
  /* #10 Call internal Tx Confirmation with passed fifoIdx */
  Eth_30_Tc3xx_Internal_TxConfirmation(ctrlIdx, fifoIdx);
} /* Eth_30_Tc3xx_TxConfirmationFifo */

#define ETH_30_TC3XX_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* module specific MISRA deviations:
  MD_Eth_30_Tc3xx_0303:
    Reason:     Hardware accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk as the register is mapped to the respective memory address.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_0310:
    Reason:     The pointer where the cast led to has a less stricter alignment. The cast
                is necessary since the array represents a continuous data buffer.
    Risk:       There is no risk since the array is a continuous data buffer.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3305:
    Reason:     The cast is necessary since the array represents a continuous data buffer and the Ethernet header
                has a length of 14 bytes
    Risk:       There is no risk since the array is a continuous data buffer. which is not divisible by 4.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3197:
    Reason:     First read/write access is variant depending. Possible initialization before possible write access
                does not harm but improves code readability.
    Risk:       There is no risk.
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3219:
    Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                by all implementation files which include this header file.
    Risk:       None.
    Prevention: None.

  MD_Eth_30_Tc3xx_3415:
   Reason:      Avoid nesting of control structures.
   Risk:        There is no risk because the functions called only retrieve data and don't manipulate them.
   Prevention:  Covered by component tests.

  MD_Eth_30_Tc3xx_0306:
    Reason:     Descriptor word accesses need a cast from integral type to a pointer to object.
    Risk:       There is no risk because descriptor pointers are only available with 32 bit length
    Prevention: Covered by code review.

  MD_Eth_30_Tc3xx_3673:
    Reason:     Type of parameter is specified by AUTOSAR and cannot be changed to const.
    Risk:       Caller of function isn't able to optimize memory usage by placing the respective variable in ROM.
    Prevention: None.
*/

/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETH_COMPATIBILITY
    \ACCEPT XF xf
    \ACCEPT TX tx
    \REASON [MSR_COV_COMPATIBILITY]

  \ID COV_ETH_MII_INTERFACE
    \ACCEPT TX
    \REASON Switching off this feature is not supported and therefore it is always active. The related service API
            should be configurable by AUTOSAR but this is not supported by using MICROSAR EthIf which
            always needs the MII interface.

  \ID COV_ETH_PERIPHERAL_ACCESS
    \ACCEPT XF
    \REASON This feature is not used by this derivative and therefore it is always deactivated.

  \ID COV_ETH_TEST_SUITE
    \ACCEPT TX
    \REASON This code is only used by ETH test suite for testing purpose and therefore excluded from (MISRA) metrics.

  \ID COV_ETH_TEST_SUITE_UNIT_TESTS
    \ACCEPT TX
    \REASON This code is only deactivated by ETH test suite for unit testing purpose.

  \ID COV_ETH_HOST_CTRL_INTERFACE
    \ACCEPT XF
    \ACCEPT TX
    \REASON This is only relevant for drivers which are wrapping a host controller driver. For all other Ethernet
            drivers, it has to be turned off.

 COV_JUSTIFICATION_END */

/* SBSW_JUSTIFICATION_BEGIN
   \ID SBSW_ETH_30_TC3XX_COMMON_CSL01
     \DESCRIPTION Access of generated data by usage of index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL01]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL02
     \DESCRIPTION Access of generated data that is referred to over another index that is limited to the data's size
                  (via an indirection) using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL02]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL03
     \DESCRIPTION Access of generated data by usage of indirection index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL03]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_RING
     \DESCRIPTION Access of generated data in ring structure by usage of start-index plus an index referring to the
                  current position, both provided by ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_GLOBAL_DESCR_IDX]

   \ID SBSW_ETH_30_TC3XX_COMMON_CSL_CALCULATED_STACK
     \DESCRIPTION Access of generated data in a stack structure by usage of start-index plus an index referring to the
                  current position, both provided by ComStackLib.
     \COUNTERMEASURE \R The retrieved index is checked to not exceed the end index provided by ComStackLib.
                        [CM_ETH_30_TC3XX_CSL03] for the correctness of the index.

   \ID SBSW_ETH_30_TC3XX_REF_OF_STACK_VAR
     \DESCRIPTION Pointer to stack variable passed as function argument.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_REF_OF_STACK_VAR]

   \ID SBSW_ETH_30_TC3XX_PUB_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to a public API.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a function to an internal function
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_PASS_CSL0X
     \DESCRIPTION Passing a local pointer variable referencing an Ethernet transmission or reception buffer pointer
                  provided by offset calculation with offsets obtained through ComStackLib shifted by a constant
                  positive offset of less than 60 Bytes as parameter to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet transmission buffer array and at least
                        60 valid Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the
                        correctness of the start offset.

   \ID SBSW_ETH_30_TC3XX_PUB_FCT_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to an external function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The shift position of the buffer adjusted by the switch interface is verified
                        with another runtime-check and the length returned by the switch interface after the buffer was
                        adjusted.

   \ID SBSW_ETH_30_TC3XX_OPT_API_SHIFTED_LOCAL_BUF_PTR_PASS_SWT_IFC_CSL03
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to a configurable function pointer obtained with ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset and the retrieval of the function pointer. The shift position of the buffer
                        adjusted by the switch interface is verified with another runtime-check and the length returned
                        by the switch interface after the buffer was adjusted. [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03] for
                        the correctness of the function pointer.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_SHIFTED_LOCAL_BUF_PTR_WITH_LENGTH_PASS_SWT_IFC
     \DESCRIPTION Passing one or more local pointer variables with immediate value assignment referencing the same
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib and adjusted by the switch interface shifted by a constant positive offset of
                  less than 60 Bytes as parameter to an internal function alongside with the returned length of the
                  switch interface.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for an Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The length returned by the switch interface after the adjustment of the buffer
                        is passed to the function as well.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_STACK_VAR_PASS_CSL0X
     \DESCRIPTION Passing a reference to a local pointer variable with immediate value assignment referencing an
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes  and a reference to a
                  stack variable as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The passed reference is obtained by using the address operator.
                        [CM_ETH_30_TC3XX_REF_OF_STACK_VAR] for the reference to the stack variable.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_REF_AND_REF_OF_PARAM_PASS_CSL0X
     \DESCRIPTION Passing a reference to a local pointer variable with immediate value assignment referencing an
                  Ethernet transmission or reception buffer pointer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes  and a reference to a
                  function parameter as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after. [CM_ETH_30_TC3XX_CSL03] for the correctness of
                        the start offset. The passed references are obtained by using the address operator. The caller
                        has to make sure that the parameter is in valid memory.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_CSL0X
     \DESCRIPTION Accessing a local pointer variable with immediate value assignment referencing an Ethernet 
                  transmission or reception buffer provided by offset calculation with offsets obtained
                  through ComStackLib shifted by a constant positive offset of less than 60 Bytes.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK] for a Ethernet buffer array and at least 60 valid
                        Byte-index positions that can be accessed after.[CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the
                        index used for getting the start offset and [CM_ETH_30_TC3XX_CSL03]. The obtained pointer is
                        immediately assigned to the variable that is accessed.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_LOCAL_BUF_PTR_ACCESS_DESCR
     \DESCRIPTION Accessing a local pointer variable with immediate value assignment referencing an Ethernet
                  transmission or reception buffer pointer provided by the content of a descriptor variable referenced
                  by a local pointer provided by ComStackLib over a parameter given into the accessing function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the index used for getting the descriptor pointer.
                        The obtained buffer pointer is immediately assigned to the local variable that is accessed.
                        The initialization of the descriptor ensures that a valid buffer is assigned to the descriptor
                        so that the access at byte-positions at less than 60 Bytes are valid.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_LT60B_SHIFTED_PARAM_BUF_PTR_ACCESS
     \DESCRIPTION Accessing a variable provided by reference as parameter upon the call of the function referencing an
                  Ethernet transmission or reception buffer pointer at a Byte-index  position of less than 60 Bytes.
     \COUNTERMEASURE \N The caller is responsible to provide a valid pointer to a buffer variable according to the CDD.
                        The access at a Byte-index position at less than 60 Bytes is valid.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR
     \DESCRIPTION Passing a pointer provided during a call to a function and a pointer to a stack variable as parameters
                  to an internal function
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR] and [CM_ETH_30_TC3XX_REF_OF_STACK_VAR].

   \ID SBSW_ETH_30_TC3XX_PHYS_ADDR_PTR_ACCESS
     \DESCRIPTION Accessing an array containing a 6-Byte physical address provided as pointer parameter to a internal
                  function.
     \COUNTERMEASURE \R The caller of the function has to make sure no null pointer is passed. The called function makes
                        sure that only 6 bytes are accessed since the passed variable shall be an IEEE 802.3 compliant
                        Ethernet physical address.

   \ID SBSW_ETH_30_TC3XX_INT_FCT_GEN_PTR_PASS_CSL03
     \DESCRIPTION Passing a pointer provided by ComStackLib according to CSL03
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL03]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_PASS
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib passing a pointer as
     parameter which is provided as parameter to the function calling the function pointer.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03], [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_OPT_API_FCT_PTR_CSL03_PARAM_PTR_AND_STACK_REF_PASS
     \DESCRIPTION Access of a function pointer of optional API abstraction using ComStackLib passing a pointer which is
                  provided as parameter to the function calling the function pointer and a reference
                  to a stack variable as parameters
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03], [CM_ETH_30_TC3XX_CALLER_PARAM_PTR] and
                        [CM_ETH_30_TC3XX_REF_OF_STACK_VAR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_AND_CSL_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function and a pointer provided by ComStackLib
                  from an index given as parameter in the calling function as parameters to an internal function.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK], [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] for the index with
                        which the pointer is retrieved.

   \ID SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL01
     \DESCRIPTION Accessing a local pointer variable whose value is provided by ComStackLib with an index given
                  as parameter into the accessing internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL01] for the index parameter, the
                        local pointer variable is declared and initialized in advance of the access.

   \ID SBSW_ETH_30_TC3XX_LOCAL_PTR_ACCESS_CSL_PARAM_IDX_CSL03
     \DESCRIPTION Accessing a local pointer variable whose value is provided by ComStackLib with an index given
                  as parameter into the accessing internal function by providing the access index over an indirection.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL03] for the index parameter, the
                        local pointer variable is declared and initialized in advance of the access.

   \ID SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL03
     \DESCRIPTION Accessing a global variable provided by ComStackLib with an index given
                  as parameter into the accessing internal function by providing the access index over an indirection.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL03].

   \ID SBSW_ETH_30_TC3XX_GLOBAL_VAR_ACCESS_CSL_PARAM_IDX_CSL02
     \DESCRIPTION Accessing a global variable provided by ComStackLib directly with an index given as parameter into the
                  accessing internal function. The accessed array has the same size as the array for which the index
                  parameter is valid according to the CDD which is ensured by an indirection in the ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD] and [CM_ETH_30_TC3XX_CSL02].

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_PASS_CSL02
     \DESCRIPTION Pass of a pointer which is accessed from generated data that is referred to over an index that is
                  limited to the same size (via an indirection) using ComStackLib.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CSL02]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_IDX_PASS
     \DESCRIPTION Write access to data using index passed as function argument during call of a internal function.
     \COUNTERMEASURE \N [CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD]

   \ID SBSW_ETH_30_TC3XX_REGISTER_ACCESS
     \DESCRIPTION The function accesses a hardware register using a reference calculated out of a generated base address
                  and a pre-defined additional register offset given as a parameter into the function
     \COUNTERMEASURE \T The code inspection and tests on hardware ensure that the memory location
                        referenced contains the registers with the same offsets as specified.

   \ID SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL01
     \DESCRIPTION Access of optional function pointer using ComStackLib.
     \COUNTERMEASURE \R Index used according to [CM_ETH_30_TC3XX_CSL01] to resolve respective function-pointer,
                        additional runtime check for NULL_PTR performed. Signature of the function used to define
                        function-pointer checked by compiler. The User has to check generated function-pointer according
                        to SMI-8. Due toCSL limitation a workaround is applied to generate an array of size one for this
                        structure. Therefore the index is fixed to 0.

   \ID SBSW_ETH_30_TC3XX_FCT_PTR_OPT_CSL03
     \DESCRIPTION Access of optional function pointer using ComStackLib over an indirection.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PUB_PARAM_PTR_AND_CSL_MEM_PTR_PASS_MEASUREMENT_DATA
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function
                  and passing of a pointer provided by the ComStackLib when accessing a measurement data structure
                  element.
     \COUNTERMEASURE \N For the public function parameter pass [CM_ETH_30_TC3XX_CALLER_PARAM_PTR]
                        For the pointer provided by CSL [CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_NULL_PARAM_PTR_AND_CSL_MEM_PTR_PASS_CSL_DATA
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function
                  and passing of a pointer provided by the ComStackLib when accessing a measurement data structure
                  element.
     \COUNTERMEASURE \N For the null pointer parameter pass [CM_ETH_30_TC3XX_NULL_PARAM_PTR]
                        For the pointer provided by CSL [CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX]

   \ID SBSW_ETH_30_TC3XX_INT_FCT_PARAM_PTR_ACCESS_POSSIBLE_NULL_PTR_AFTER_NULL_PTR_CHECK
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function with
                  possible NULL pointer after NULL pointer check.
     \COUNTERMEASURE \R [CM_ETH_30_TC3XX_NULL_PARAM_PTR]

   SBSW_JUSTIFICATION_END */

/*
  \CM CM_ETH_30_TC3XX_CSL01                   Qualified use-case CSL01 of ComStackLib.

  \CM CM_ETH_30_TC3XX_CSL02                   Qualified use-case CSL02 of ComStackLib.

  \CM CM_ETH_30_TC3XX_CSL03                   Qualified use-case CSL03 of ComStackLib.

  \CM CM_ETH_30_TC3XX_FCT_PTR_CSL03           Index according to [CM_ETH_30_TC3XX_CSL03] used to resolve respective
                                             function-pointer, signature of function used to define function-pointer
                                             checked by compiler and user must check generated function-pointer
                                             according to SMI-8.

  \CM CM_ETH_30_TC3XX_FCT_PTR_OPT_CSL03       In addition to [CM_ETH_30_TC3XX_FCT_PTR_CSL03] the function pointer is
                                             checked for being not NULL pointer (what indicates that function isn't
                                             present) before calling the function by using the function pointer.

  \CM CM_ETH_30_TC3XX_PUB_PARAM_PTR_CHECK     Parameter pointer provided to public API is checked for not being NULL
                                             pointer before usage.

  \CM CM_ETH_30_TC3XX_CALLER_PARAM_PTR        The caller of the function passing the pointer to the other function
                                             ensures that the pointer is valid according to functions CDD.

  \CM CM_ETH_30_TC3XX_CALLER_IDX_RANGE_CDD    The caller passing the index to the callee ensures that the index is
                                             within the range given in CDD.

  \CM CM_ETH_30_TC3XX_REF_OF_STACK_VAR        Pointer is generated by referencing a stack variable by the address
                                             operator.

  \CM CM_ETH_30_TC3XX_ETH_BUF_VALIDITY_CHECK  A runtime check prevents invalid pointer or array accesses to be
                                             performed in the program flow after the check. The validity is checked by
                                             addition of a defined, positive and constant valid offset to a start
                                             index of a  ComStackLibArray obtained by using the ComStackLib and
                                             comparing the calculated offset to the end offset of the same array also
                                             obtained by  the ComStackLib. All operations performed at addresses
                                             corresponding to smaller offsets to the start offset than the checked
                                             offset are then as well within the valid borders of the accessed array
                                             and thus valid themselves. The addresses corresponding to the constant
                                             offsets to the start index are as well obtained by using the ComStackLib.
                                             The defines used to obtain the valid positive shifted offsets are protected
                                             by using preprocessor checks with error directives becoming active, if the
                                             offsets exceed the valid range.

   \CM CM_ETH_30_TC3XX_GLOBAL_DESCR_IDX       A runtime check prevents invalid use of a index variable to be performed
                                             in the program flow after the check. The index is referring to a
                                             transmission or reception descriptor variable. These variables are
                                             organized in rings with a global start index for every first descriptor
                                             in the ring that can be obtained by using the ComStackLib. This global
                                             start index is added to a ring-local processing position as well provided
                                             by ComStackLib to obtain the unique or global descriptor index of the
                                             currently processed descriptor.
                                             The index is checked to be smaller than the global end index of the
                                             currently processed descriptor ring to be considered valid.

  \CM CM_ETH_30_TC3XX_MEASUREMENT_DATA_IDX    Due to CSL limitation a workaround is applied to generate an array of size
                                             one for the measurement data structure. Therefore the index is fixed to 0
                                             and defined as constant macro. According to C standard zero size array
                                             declarations are not allowed.
  \CM CM_ETH_30_TC3XX_NULL_PARAM_PTR          The null pointer is intentionally passed and it is checked before
                                             accessing in the called functions CDD.
*/

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx.c
 *********************************************************************************************************************/
