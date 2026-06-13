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
/*!        \file  EthIf_Rx_Cbk.h
 *        \brief  EthIf Rx public callback API header
 *
 *      \details  Provides access to the public callback API of the sub-module Rx of EthIf.
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

#if !defined (ETHIF_RX_CBK_H)
# define ETHIF_RX_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Rx_Types.h"

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
 *  EthIf_RxIndication
 *********************************************************************************************************************/
/*! \brief          Notifies the EthIf about a received Ethernet frame
 *  \details        Functions takes the given Ethernet frame data, analysis the Ethernet header for VLAN and EtherType
 *                  information and decides whether to drop the frame or pass it to a known EthIf user.
 *  \param[in]      CtrlIdx      Ethernet controller index
 *  \param[in]      FrameType    EtherType the Ethernet frame is related to
 *  \param[in]      IsBroadcast  Broadcast indication:
 *                               FALSE - frame isn't a broadcast frame
 *                               TRUE - frame is a broadcast frame
 *  \param[in]      PhysAddrPtr  Source MAC address of the Ethernet frame
 *  \param[out]     DataPtr      Location of the Ethernet frame payload (no VLAN tag considered)
 *  \param[in]      LenByte      Length of the Ethernet frame payload (no VLAN tag considered)
 *  \pre            -
 *  \context        TASK|ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2393651, SPEC-2393655, SPEC-2393933, SPEC-2393658
 *  \trace          DSGN-EthIf22856, DSGN-EthIf22966, DSGN-EthIf22881
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_RxIndication(
        uint8                                     CtrlIdx,
        Eth_FrameType                             FrameType,
        boolean                                   IsBroadcast,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  PhysAddrPtr,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  DataPtr,
        uint16                                    LenByte);

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_RX_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Rx_Cbk.h
 *********************************************************************************************************************/

