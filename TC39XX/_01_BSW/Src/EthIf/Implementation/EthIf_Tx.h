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
/*!        \file  EthIf_Tx.h
 *        \brief  EthIf Tx public API header
 *
 *      \details  Provides access to the public API of the sub-module Tx of EthIf.
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

#if !defined (ETHIF_TX_H)
# define ETHIF_TX_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Tx_Types.h"

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

/**********************************************************************************************************************
 *  EthIf_ProvideTxBuffer
 *********************************************************************************************************************/
/*! \brief          Provides a transmission buffer for an Ethernet frame
 *  \details        Function allows to acquire a buffer where a upper layer is able to insert the payload for the
 *                  Ethernet frame.
 *  \param[in]      CtrlIdx     EthIf controller index
 *  \param[in]      FrameType   EtherType to insert into the Ethernet frame header
 *  \param[in]      Priority    Priority of the Ethernet frame, which is coded into the PCP of the IEEE802.3Q
 *                              VLAN tag. If EthIf controller represents a physical data connection the
 *                              priority is ignored.
 *  \param[out]     BufIdxPtr   Index to identify the acquired buffer
 *  \param[out]     BufPtr      Buffer the payload can be written to
 *  \param[in,out]  LenBytePtr  Buffer length:
 *                              [in] - Length in byte needed for the payload, which shall be transmitted
 *                              [out] - Length of the buffer that is provided in byte (has at least the size of
 *                                      the requested length needed for the payload)
 *  \return         BUFREQ_OK - success
 *  \return         BUFREQ_E_NOT_OK - function has been called with invalid parameters
 *  \return         BUFREQ_E_BUSY - all buffers are in use
 *  \return         BUFREQ_E_OVFL - requested length is too large
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393631
 *  \trace          DSGN-EthIf22848
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, ETHIF_CODE) EthIf_ProvideTxBuffer(
        uint8                                                                       CtrlIdx,
        Eth_FrameType                                                               FrameType,
        uint8                                                                       Priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr);


/**********************************************************************************************************************
 *  EthIf_VTransmit
 *********************************************************************************************************************/
/*! \brief          Triggers transmission of an Ethernet frame with a given source MAC address
 *  \details        Function triggers the transmission of an Ethernet frame identified by the buffer and using the
 *                  provided MAC address as source MAC address of the Ethernet frame.
 *  \param[in]      CtrlIdx         EthIf controller index
 *  \param[in]      BufIdx          Index to identify the buffer for frame transmission
 *  \param[in]      FrameType       EtherType to insert into the Ethernet frame header
 *  \param[in]      TxConfirmation  Request for a transmission confirmation:
 *                                  FALSE - no confirmation desired
 *                                  TRUE - confirmation desired
 *  \param[in]      LenByte         Payload length to be transmitted
 *  \param[in]      DstMacAddrPtr   Destination MAC address
 *  \param[in]      SrcMacAddrPtr   Source MAC address:
 *                                  MAC address as defined by IEEE802.3 - using this MAC address as source MAC address
 *                                  NULL_PTR - using the Ethernet controllers MAC address as source MAC address
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            EthIf controller was set in ACTIVE state by EthIf_SetControllerMode()
 *  \pre            Buffer to be transmitted must be previously acquired by
 *                  EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer()
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          DSGN-EthIf22848, DSGN-EthIf22966, DSGN-EthIf22902
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VTransmit(
        uint8                                     CtrlIdx,
        uint8                                     BufIdx,
        Eth_FrameType                             FrameType,
        boolean                                   TxConfirmation,
        uint16                                    LenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  DstMacAddrPtr,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  SrcMacAddrPtr);

/**********************************************************************************************************************
 *  EthIf_Transmit
 *********************************************************************************************************************/
/*! \brief          Triggers transmission of an Ethernet frame with the Ethernet controllers source MAC address
 *  \details        Function triggers the transmission of an Ethernet frame identified by the buffer and using the
 *                  MAC address of the Ethernet controller as source MAC address of the Ethernet frame.
 *  \param[in]      CtrlIdx         EthIf controller index
 *  \param[in]      BufIdx          Index to identify the buffer for frame transmission
 *  \param[in]      FrameType       EtherType to insert into the Ethernet frame header
 *  \param[in]      TxConfirmation  Request for a transmission confirmation:
 *                                  FALSE - no confirmation desired
 *                                  TRUE - confirmation desired
 *  \param[in]      LenByte         Payload length to be transmitted
 *  \param[in]      PhysAddrPtr     Destination MAC address
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            EthIf controller was set in ACTIVE state by EthIf_SetControllerMode()
 *  \pre            Buffer to be transmitted must be previously acquired by
 *                  EthIf_ProvideTxBuffer()/EthIf_ProvideExtTxBuffer()
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393641
 *  \trace          DSGN-EthIf22848, DSGN-EthIf22966, DSGN-EthIf22902
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_Transmit(
        uint8                                     CtrlIdx,
        uint8                                     BufIdx,
        Eth_FrameType                             FrameType,
        boolean                                   TxConfirmation,
        uint16                                    LenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  PhysAddrPtr);


/**********************************************************************************************************************
 *  EthIf_MainFunctionTx
 *********************************************************************************************************************/
/*! \brief          Transmission confirmation Main Function
 *  \details        Main function to handle Ethernet frame transmission confirmation in polling mode.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393554, SPEC-2393669
 *  \trace          DSGN-EthIf22993
 *********************************************************************************************************************/
/* Function declaration is provided by SchM */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_TX_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Tx.h
 *********************************************************************************************************************/

