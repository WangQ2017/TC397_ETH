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
/*!        \file  EthIf_EthCtrl.h
 *        \brief  EthIf EthCtrl public API header
 *
 *      \details  Provides access to the public API of the sub-module EthCtrl of EthIf.
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

#if !defined (ETHIF_ETHCTRL_H)
# define ETHIF_ETHCTRL_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthCtrl_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/***********************************************************************************************************************
 *  EthIf_GetPhysAddr
 **********************************************************************************************************************/
/*! \brief          Retrieves the MAC address related to the EthIf controller
 *  \details        Function retrieves the MAC address that is used as source MAC address by the Ethernet controller
 *                  mapped to the EthIf controller.
 *  \param[in]      CtrlIdx      EthIf controller the MAC shall be retrieved for
 *  \param[out]     PhysAddrPtr  Pointer to the buffer where MAC shall be stored in
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393613
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_GetPhysAddr(
        uint8                              CtrlIdx,
  P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR)  PhysAddrPtr);

/**********************************************************************************************************************
 *  EthIf_SetPhysAddr
 *********************************************************************************************************************/
/*! \brief          Sets the MAC address related to the EthIf controller
 *  \details        Function alters the MAC address that is used as source MAC address by the Ethernet controller
 *                  mapped to the EthIf controller.
 *  \param[in]      CtrlIdx      EthIf controller the MAC shall be set for
 *  \param[in]      PhysAddrPtr  Pointer to the MAC to set
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393619
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_SetPhysAddr(
          uint8                               CtrlIdx,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  PhysAddrPtr);

# if ( ETHIF_ENABLE_UPDATE_PHYS_ADDR_FILTER == STD_ON )
/**********************************************************************************************************************
 *  EthIf_UpdatePhysAddrFilter
 *********************************************************************************************************************/
/*! \brief          Modifies the receive MAC address filter related to the EthIf Controller
 *  \details        Function modifies the receive MAC address filter of the Ethernet controller mapped to the EthIf
 *                  controller by adding/removing the MAC address to/from the receive MAC address filter.
 *  \param[in]      CtrlIdx      EthIf controller the filter shall be adatped for
 *  \param[in]      PhysAddrPtr  MAC address that shall be added/removed from filter
 *  \param[in]      Action       Action that shall be applied on the MAC address filter:
 *                               ETH_ADD_TO_FILTER - adapt filter to be able to receive frames with the given
 *                                                   MAC address as destination MAC address
 *                               ETH_REMOVE_FROM_FILTER - adapt filter to prevent reception of frames with the
 *                                                        given MAC address as destination MAC address
 *  \return         E_OK - filter successfully adapted
 *                  E_NOT_OK - no filter adaption performed
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ENABLE_UPDATE_PHYS_ADDR_FILTER
 *  \trace          SPEC-2393625
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_UpdatePhysAddrFilter(
          uint8                                             CtrlIdx,
  P2CONST(uint8,               AUTOMATIC, ETHIF_APPL_DATA)  PhysAddrPtr,
          Eth_FilterActionType                              Action);
# endif /* ETHIF_ENABLE_UPDATE_PHYS_ADDR_FILTER */

# if ( ETHIF_GLOBAL_TIME_SUPPORT == STD_ON )
/***********************************************************************************************************************
 *  EthIf_GetCurrentTime
 **********************************************************************************************************************/
/*! \brief          Retrieves the current time of the Ethernet controllers timer module
 *  \details        Function redirects the call to the Ethernet controller driver to retrieve the current time
 *                  of the controllers timer module.
 *  \param[in]      CtrlIdx       EthIf controller the current time shall be retrieved from
 *  \param[out]     timeQualPtr   Pointer to the buffer the quality of the time retrieved shall be stored to
 *  \param[out]     timeStampPtr  Pointer to the buffer the current time shall be stored to
 *  \return         E_OK - current time successfully retrieved
 *  \return         E_NOT_OK - current time not retrieved
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_GLOBAL_TIME_SUPPORT
 *  \trace          SPEC-2393901, SPEC-2393905
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetCurrentTime(
        uint8                                              CtrlIdx,
  P2VAR(Eth_TimeStampQualType, AUTOMATIC, ETHIF_APPL_VAR)  timeQualPtr,
  P2VAR(Eth_TimeStampType,     AUTOMATIC, ETHIF_APPL_VAR)  timeStampPtr);

/***********************************************************************************************************************
 *  EthIf_EnableEgressTimestamp
 **********************************************************************************************************************/
/*! \brief          Enables timestamping for a frame
 *  \details        Function redirects the call to the Ethernet controller driver to enable egress timestamping of
 *                  a frame.
 *  \param[in]      CtrlIdx  EthIf controller the frame is assigned to
 *  \param[in]      BufIdx   Buffer used for the frame
 *  \return         E_OK - timestamping enabled successfully
 *  \return         E_NOT_OK - timestamping couldn't be enabled
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_GLOBAL_TIME_SUPPORT
 *  \note           Further restriction of context:
 *                  Call only allowed between EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer() and
 *                  EthIf_Transmit()/EthIf_VTransmit() for a specific frame (identified by the BufIdx)
 *  \trace          SPEC-2394055, SPEC-2393909
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_EnableEgressTimestamp(
  uint8  CtrlIdx,
  uint8  BufIdx);

/***********************************************************************************************************************
 *  EthIf_GetEgressTimestamp
 **********************************************************************************************************************/
/*! \brief          Retrieves the egress timestamp of a frame
 *  \details        Function redirects the call to the Ethernet controller driver to retrieve the egress timestamp of
 *                  a frame.
 *  \param[in]      CtrlIdx              EthIf controller the frame is assigned to
 *  \param[in]      BufIdx               Buffer used for the frame
 *  \param[out]     TimestampPtr         Pointer to buffer the timestamp shalle be stored to
 *  \param[out]     TimestampQualityPtr  Pointer to buffer the quality shall be stored to
 *  \return         E_OK - timestamp successfully retrieved
 *  \return         E_NOT_OK - timestamp couldn't be retrieved
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_GLOBAL_TIME_SUPPORT
 *  \note           Further restriction of context:
 *                  Call only allowed in <User>_TxConfirmation()
 *  \tace           SPEC-2393911, SPEC-2393915
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetEgressTimestamp(
        uint8                                                 CtrlIdx,
        uint8                                                 BufIdx,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, ETHIF_APPL_VAR)  TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, ETHIF_APPL_VAR)  TimestampQualityPtr);

/***********************************************************************************************************************
 *  EthIf_GetIngressTimestamp
 **********************************************************************************************************************/
/*! \brief          Retrieves the ingress timestamp of a frame
 *  \details        Function redirects the call to the Ethernet controller driver to retrieve the ingress timestamp of
 *                  a frame.
 *  \param[in]      CtrlIdx              EthIf controller the frame is assigned to
 *  \param[in]      DataPtr              Pointer to the frame payload for identifying the frame
 *  \param[out]     TimestampPtr         Pointer to buffer the timestamp shalle be stored to
 *  \param[out]     TimestampQualityPtr  Pointer to buffer the quality shall be stored to
 *  \return         E_OK - timestamp successfully retrieved
 *  \return         E_NOT_OK - timestamp couldn't be retrieved
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_GLOBAL_TIME_SUPPORT
 *  \note           Further restriction of context:
 *                  Call only allowed in <User>_RxIndication()
 *  \trace          SPEC-2394057, SPEC-2393920
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetIngressTimestamp(
        uint8                                                 CtrlIdx,
  P2VAR(Eth_DataType,             AUTOMATIC, ETHIF_APPL_VAR)  DataPtr,
  P2VAR(Eth_TimeStampType,        AUTOMATIC, ETHIF_APPL_VAR)  TimestampPtr,
  P2VAR(Eth_TimestampQualityType, AUTOMATIC, ETHIF_APPL_VAR)  TimestampQualityPtr);

# endif /* ETHIF_GLOBAL_TIME_SUPPORT */

# if ( ETHIF_ENABLE_HEADER_ACCESS_API == STD_ON )                                                                       /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_GetTxHeaderPtr
 **********************************************************************************************************************/
/*! \brief          Retrieves the location of the Ethernet header for a given transmission buffer
 *  \details        Function retrieves the location of the Ethernet header for a given transmission buffer.
 *  \param[in]      CtrlIdx       EthIf controller the buffer is assigned to
 *  \param[in]      BufIdx        Index to identify the buffer the Ethernet header location shall be retrieved for
 *  \param[out]     BufPtr        Location of the Ethernet header
 *  \param[out]     LenBytPtr     Length of the Ethernet header in byte:
 *                                14 byte - non VLAN enabled EthIf controller
 *                                18 byte - VLAN enable EthIf controller
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            Buffer to retrieve the Ethernet header location for must be previously acquired by
 *                  EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer()
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ENABLE_HEADER_ACCESS_API
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTxHeaderPtr(
        uint8                                                                       CtrlIdx,
        uint8                                                                       BufIdx,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr);

/***********************************************************************************************************************
 *  EthIf_GetRxHeaderPtr
 **********************************************************************************************************************/
/*! \brief          Retrieves the location of the Ethernet header for a given reception buffer
 *  \details        Function retrieves the location of the Ethernet header for a given reception buffer.
 *  \param[in]      CtrlIdx    EthIf controller the buffer is assigned to
 *  \param[in,out]  BufPtr     Pointer to reception buffer:
 *                             [in] - Location of the payload of the Ethernet frame within the reception buffer
 *                             [out] - Location of the Ethernet header
 *  \param[out]     LenBytPtr  Length of the Ethernet header in byte:
 *                             14 byte - non VLAN enabled EthIf controller
 *                             18 byte - VLAN enable EthIf controller
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_ENABLE_HEADER_ACCESS_API
 *  \note           Further restriction of context:
 *                  Call only allowed during <User>_RxIndication()
 *  \trace          DSGN-EthIf22934
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetRxHeaderPtr(
        uint8                                                                       CtrlIdx,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr);
# endif /* ETHIF_ENABLE_HEADER_ACCESS_API */

# if ( ETHIF_DYNAMIC_TRAFFIC_SHAPING_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief          Manipulates the maximum bandwidth of a traffic queue.
 *  \details        Function allows to manipulate the maximum amount of bandwidth the indexed traffic queue is allowed
 *                  to acquire.
 *  \param[in]      CtrlIdx         EthIf controller the bandwidth shall be set for
 *  \param[in]      QueuePrio       Transmission queue the bandwidth shall be set for
 *  \param[in]      BandwidthLimit  New bandwidth limit [bit/s]
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_DYNAMIC_TRAFFIC_SHAPING_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetBandwidthLimit(
  uint8   CtrlIdx,
  uint8   QueuePrio,
  uint32  BandwidthLimit);

/**********************************************************************************************************************
 * EthIf_GetBandwidthLimit
 **********************************************************************************************************************/
/*! \brief          Retrieves the current maximum bandwidth of a traffic queue.
 *  \details        Function allows to retrieve the maximum amount of bandwidth the indexed traffic queue is allowed
 *                  to acquire currently.
 *  \param[in]      CtrlIdx            EthIf controller the bandwidth shall be retrieved from
 *  \param[in]      QueuePrio          Transmission queue the bandwidth shall be retrieved from
 *  \param[out]     BandwidthLimitPtr  Bandwidth limit retrieved [bit/s]
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_DYNAMIC_TRAFFIC_SHAPING_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetBandwidthLimit(
        uint8                               CtrlIdx,
        uint8                               QueuePrio,
  P2VAR(uint32, AUTOMATIC, ETHIF_APPL_VAR)  BandwidthLimitPtr);

# endif /* ETHIF_DYNAMIC_TRAFFIC_SHAPING_SUPPORT */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ETHCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthCtrl.h
 *********************************************************************************************************************/

