/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn_Cbk.h
 *        \brief  EthTSyn Callback header file
 *      \details  Contains all callback function declarations with respect to the EthTSyn module
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/


#if !defined(ETHTSYN_CBK_H)
# define ETHTSYN_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /*lint !e451 */  /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_RxIndication
 *********************************************************************************************************************/
/*! \brief        Processing of received EthTSyn frames.
 *  \details      By this API service the EthTSyn gets an indication and the data of a received frame.
 *  \param[in]    CtrlIdx      EthIf controller index
 *  \param[in]    FrameType    Frame type of received Ethernet frame
 *  \param[in]    IsBroadcast  Broadcast indication:
 *                             FALSE - frame is not a broadcast frame
 *                             TRUE - frame is a broadcast frame
 *  \param[in]    PhysAddrPtr  Pointer to the Physical source address (MAC address in network byte order) of received
 *                             Ethernet frame
 *  \param[in]    DataPtr      Pointer to payload of the received Ethernet frame (i.e. Ethernet header is not provided)
 *  \param[in]    LenByte      Length of received data
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_RxIndication(
                uint8         CtrlIdx,
                Eth_FrameType FrameType,
                boolean       IsBroadcast,
  EthTSyn_PhyAddrPtrType      PhysAddrPtr,
  ETHTSYN_P2VAR(uint8)        DataPtr,
                uint16        LenByte);

/**********************************************************************************************************************
 *  EthTSyn_TxConfirmation
 *********************************************************************************************************************/
/*! \brief        Confirms the transmission of an Ethernet frame.
 *  \details      This callback function is called by lower layer (EthIf) if a message has been transmitted by the
 *                hardware.
 *  \param[in]    CtrlIdx  EthIf controller index
 *  \param[in]    BufIdx   Index of the buffer resource
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different Controller and/or Buffer indices
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TxConfirmation(
  uint8 CtrlIdx,
  uint8 BufIdx);

/**********************************************************************************************************************
 *  EthTSyn_TrcvLinkStateChg
 *********************************************************************************************************************/
/*! \brief        Callback function that notifies a changed state of the transceiver link
 *  \details      Allows resetting state machine in case of unexpected Link loss to avoid inconsistent
                  Sync and Follow_Up sequences
 *  \param[in]    CtrlIdx        Index of the Ethernet controller
 *  \param[in]    TrcvLinkState  New link state of the transceiver
 *                               ETHTRCV_LINK_STATE_DOWN - Link Down
 *                               ETHTRCV_LINK_STATE_ACTIVE - Link Up
 *  \pre          -
 *  \context      TASK|ISR2
 *  \reentrant    TRUE for different controller indices
 *  \synchronous  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TrcvLinkStateChg(
  uint8                 CtrlIdx,
  EthTrcv_LinkStateType TrcvLinkState);

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /*lint !e451 */  /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif
 /* ETHTSYN_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Cbk.h
 *********************************************************************************************************************/
