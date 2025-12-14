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
/*!        \file  Eth_30_Tc3xx_TimeSync.h
 *        \brief  Timer sub-module header of the Ethernet controller driver
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

/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

#if !defined (ETH_30_TC3XX_TIME_SYNC_H)
# define ETH_30_TC3XX_TIME_SYNC_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"

# if (ETH_30_TC3XX_ENABLE_TIMESYNC == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* ----- ETH API service IDs ----- */
/*!< Service ID: Eth_30_Tc3xx_GetGlobalTime() */
#  define ETH_30_TC3XX_TIME_SYNC_SID_GET_GLOBAL_TIME                   (0x30u)
/*!< Service ID: Eth_30_Tc3xx_EnableEgressTimestamp() */
#  define ETH_30_TC3XX_TIME_SYNC_SID_ENABLE_EGRESS_TIMESTAMP           (0x31u)
/*!< Service ID: Eth_30_Tc3xx_GetEgressTimestamp() */
#  define ETH_30_TC3XX_TIME_SYNC_SID_GET_EGRESS_TIMESTAMP              (0x32u)
/*!< Service ID: Eth_30_Tc3xx_GetIngressTimestamp() */
#  define ETH_30_TC3XX_TIME_SYNC_SID_GET_INGRESS_TIMESTAMP             (0x33u)

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#  define ETH_30_TC3XX_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_TimeSync_Init
 **********************************************************************************************************************/
/*! \brief       Initializes the time synchronization structures
 *  \details     -
 *  \param[in]   CtrlIdx              Identifier of the Eth controller
 *  \return      E_OK - Initialization finished successfully
 *  \return      E_NOT_OK - Initialization failed
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \pre         -
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_TimeSync_Init(
  uint8 CtrlIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetGlobalTime
 **********************************************************************************************************************/
/*! \brief       Retrieves the current time of the Eth controllers timer
 *  \details     -
 *  \param[in]   CtrlIdx              Identifier of the Eth controller
 *  \param[out]  TimestampPtr         Retrieve time stamp
 *  \param[out]  TimestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different Eth controllers
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetGlobalTime(
        uint8                                           CtrlIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Enables time stamping for the given frame on transmission
 *  \details     -
 *  \param[in]   CtrlIdx  Identifier of the Eth controller
 *  \param[in]   BufIdx   Identifier of the buffer holding the frame to be transmitted
 *  \return      E_OK - Time stamping of frame successfully enabled
 *  \return      E_NOT_OK - Time stamping of the frame wasn't enabled
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         Ethernet controller is operational in mode ACTIVE
 *  \pre         Buffer was previously allocated by Eth_30_Tc3xx_ProvideTxBuffer() and no transmission was triggered by
 *               Eth_30_Tc3xx_Transmit() yet
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_EnableEgressTimestamp(
  uint8 CtrlIdx,
  uint8 BufIdx);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetEgressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame transmitted
 *  \details     -
 *  \param[in]   CtrlIdx              Identifier of the Eth controller
 *  \param[in]   BufIdx               Identifier of the buffer used to transmit the frame
 *  \param[out]  TimestampPtr         Time stamp taken on transmission
 *  \param[out]  TimestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEgressTimestamp(
    uint8                                               CtrlIdx,
    uint8                                               BufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr);

/***********************************************************************************************************************
 *  Eth_30_Tc3xx_GetIngressTimestamp
 **********************************************************************************************************************/
/*! \brief       Retrieves the time stamp for a frame received
 *  \details     -
 *  \param[in]   CtrlIdx              Identifier of the Eth controller
 *  \param[in]   DataPtr              Memory space the frame is located (as given in <Eth_UL>_RxIndication)
 *  \param[out]  TimestampPtr         Time stamp taken on reception
 *  \param[out]  TimestampQualityPtr  Quality of the time stamp
 *                                    ETH_TIMESTAMP_VALID: Time stamp is valid
 *                                    ETH_TIMESTAMP_INVALID: Time stamp is not valid
 *                                    ETH_TIMESTAMP_UNCERTAIN: Time stamp is uncertain
 *  \return      E_OK - Time stamp successfully retrieved
 *  \return      E_NOT_OK - Time stamp couldn't be retrieved
 *  \context     ANY
 *  \reentrant   TRUE for different frames
 *  \synchronous TRUE
 *  \config      ETH_30_TC3XX_TIME_SYNC_ENABLED
 *  \pre         Ethernet controller is operational in mode ACTIVE
 */
FUNC(Std_ReturnType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIngressTimestamp(
        uint8                                           CtrlIdx,
  P2VAR(Eth_DataType,             AUTOMATIC, AUTOMATIC) DataPtr,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, AUTOMATIC) TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, AUTOMATIC) TimestampQualityPtr);

#  define ETH_30_TC3XX_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

# endif /* ETH_30_TC3XX_ENABLE_TIMESYNC */
#endif /* ETH_30_TC3XX_TIME_SYNC_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_TimeSync.h
 *********************************************************************************************************************/
