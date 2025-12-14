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
/*!        \file  EthIf_Tx_Int.c
 *        \brief  EthIf Tx internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module Tx of EthIf
 *                only to be used EthIf internal.
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

#define ETHIF_TX_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Tx_Int.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_PrepareVlanTag
 *********************************************************************************************************************/
/*! \brief          Prepares the VLAN tag in the location provided
 *  \details        This function inserts the VLAN tag with its TCI and the desired EtherType at the data location
 *                  provided and returns the new location of the payload.
 *  \param[in]      frameHdr    Ethernet header information
 *  \param[in]      tagPtr      Pointer to the position where the VLAN tag shall be insert within the Ethernet Tx buffer
 *                              [range: tagPtr must point to a location where 4 bytes can be accessed]
 *  \param[in]      lenPtr      Length that shall be adapted for VLAN tag insertion
 *                              [range: 4 <= 1504 byte]
 *  \return         New location of the payload
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_INT_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_PrepareVlanTag( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2CONST(EthIf_FrameHdrType,       AUTOMATIC, ETHIF_APPL_DATA)  frameHdr,
    P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR)   tagPtr,
    P2VAR(uint16,                   AUTOMATIC, ETHIF_APPL_VAR)   lenPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_PrepareVlanTag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_TX_INT_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_PrepareVlanTag( /* PRQA S 3219 */ /* MD_EthIf_3219 */
  P2CONST(EthIf_FrameHdrType,       AUTOMATIC, ETHIF_APPL_DATA)  frameHdr,
    P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR)   tagPtr,
    P2VAR(uint16,                   AUTOMATIC, ETHIF_APPL_VAR)   lenPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 tci;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Reduce the buffer length provided by the driver for tag insertion */
  (*lenPtr) -= ETHIF_VLAN_TAG_LEN_BYTE;                                                                                 /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Prepare TCI */
  tci  = (uint16)frameHdr->VlanId;
  tci |= (uint16)((uint32)frameHdr->Priority << ETHIF_VLAN_TCI_PCP_SHIFT);
  (*tagPtr)[0] = (uint8)((tci & ETHIF_UINT16_UPPER_BYTE_MASK) >> ETHIF_BYTE_SHIFT_VAL);                                 /* SBSW_ETHIF_VLAN_TAG_WRITE */
  (*tagPtr)[1] = (uint8)( tci & ETHIF_UINT16_LOWER_BYTE_MASK);                                                          /* SBSW_ETHIF_VLAN_TAG_WRITE */

  /* #30 Prepare original EtherType */
  (*tagPtr)[2] = (uint8)((frameHdr->EtherType & ETHIF_UINT16_UPPER_BYTE_MASK) >> ETHIF_BYTE_SHIFT_VAL);                 /* SBSW_ETHIF_VLAN_TAG_WRITE */
  (*tagPtr)[3] = (uint8)( frameHdr->EtherType & ETHIF_UINT16_LOWER_BYTE_MASK);                                          /* SBSW_ETHIF_VLAN_TAG_WRITE */

  /* #30 Relocate buffer position for caller  */
  (*tagPtr) = &(*tagPtr)[ETHIF_VLAN_TAG_LEN_BYTE];                                                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
} /* EthIf_PrepareVlanTag() */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_Tx_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_Tx_Init( void )
{
  EthIf_TxContextIterType txContextIdx;
  EthIf_EthCtrlIterType   ethCtrlIdx;

  /* #10 Initialize the tx context elements */
  for( txContextIdx = 0;
       txContextIdx < EthIf_GetSizeOfTxContext();
       txContextIdx++ )
  {
    EthIf_SetTxPendingOfTxContext(txContextIdx, FALSE);                                                                 /* SBSW_ETHIF_COMMON_CSL01 */
    EthIf_SetValidOfTxContext(txContextIdx, FALSE);                                                                     /* SBSW_ETHIF_COMMON_CSL01 */
  }

  /* #20 Initialize the source MAC address buffer for each Ethernet controller */
  for( ethCtrlIdx = 0;
       ethCtrlIdx < EthIf_GetSizeOfEthCtrl();
       ethCtrlIdx++ )
  {
    EthIf_SetValidOfSrcMacAddrBuffer(ethCtrlIdx, FALSE);                                                                /* SBSW_ETHIF_COMMON_CSL01 */
  }
} /* EthIf_Tx_Init() */

/**********************************************************************************************************************
 *  EthIf_FinalizeTxBufferProvision
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_FinalizeTxBufferProvision(
        EthIf_EthIfCtrlIterType                              ethIfCtrlIdx,
        EthIf_EthCtrlIterType                                ethCtrlIdx,
        Eth_FrameType                                        frameType,
        uint8                                                priority,
        uint8                                                bufIdx,
  P2VAR(uint16,                   AUTOMATIC, ETHIF_APPL_VAR) bufLenPtr,
  P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR) bufPtr)
{
   EthIf_TxContextIterType txCtxtIdx;
   P2VAR(EthIf_FrameHdrType, AUTOMATIC, ETHIF_APPL_VAR) frameHdr;
#if   ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
   EthIf_FrameBufferPtrType mirroringSrcPayloadPtr;
   uint16                   llPayloadLen;

   mirroringSrcPayloadPtr = *bufPtr;
   llPayloadLen           = *bufLenPtr;
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

   /* #10 Store Tx context for later use in EthIf_Transmit() and EthIf_TxConfirmation() */
   txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, bufIdx);

   frameHdr = EthIf_GetAddrFrameHdrOfTxContext(txCtxtIdx);
   EthIf_SetEthIfCtrlIdxOfTxContext(txCtxtIdx, (EthIf_EthIfCtrlIdxOfTxContextType)ethIfCtrlIdx);                        /* SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV */
   frameHdr->EtherType = frameType;                                                                                     /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV */
   frameHdr->Priority  = priority;                                                                                      /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV */
   frameHdr->VlanId    = EthIf_GetVlanIdOfEthIfCtrl(ethIfCtrlIdx);                                                      /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV */
   EthIf_SetTxPendingOfTxContext(txCtxtIdx, FALSE);                                                                     /* SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV */
   EthIf_SetValidOfTxContext(txCtxtIdx, TRUE);                                                                          /* SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV */

   /* #20 Check if the EthIf controller represents a tagged data path */
   /* \trace SPEC-2393632 */
   if( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
   { /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
     /* #200 Prepare VLAN tag */
     /* \trace SPEC-2393633 */
     /* \trace SPEC-2393569 */
     EthIf_PrepareVlanTag((P2CONST(EthIf_FrameHdrType, AUTOMATIC, ETHIF_APPL_DATA))frameHdr,
                          bufPtr,
                          bufLenPtr);                                                                                   /* SBSW_ETHIF_PREPARE_VLAN_TAG_PTR_PASS */
   }

   EthIf_SetPayloadPtrOfTxContext(txCtxtIdx, (*bufPtr));                                                                /* SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV_AND_PARAM_PTR_PASS */
   EthIf_SetPayloadLenOfTxContext(txCtxtIdx, (*bufLenPtr));                                                             /* SBSW_ETHIF_TX_CONTEXT_IDX_CALL_CONV_AND_PARAM_PTR_PASS */

#if   ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
   /* #40 Pass provide buffer request to mirroring sub component */
   /* PRQA S 0310, 3305 4 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
   EthIf_ProvideTxMirroringBuffer(ethIfCtrlIdx,
                                  (P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR))mirroringSrcPayloadPtr,
                                  bufIdx,
                                  llPayloadLen);                                                                        /* SBSW_ETHIF_STACK_PARAM_PTR */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
} /* EthIf_FinalizeTxBufferProvision() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Tx_Int.c
 *********************************************************************************************************************/

