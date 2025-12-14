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
/*!        \file  EthIf_Tx.c
 *        \brief  EthIf Tx public API source file
 *
 *      \details  Implementation of the public API of the sub-module Tx of EthIf.
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

#define ETHIF_TX_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Tx.h"
#include "EthIf_Tx_Cbk.h"
#include "EthIf_Tx_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_Tx.c and EthIf.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (ETHIF_TX_LOCAL)                                                                                           /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_TX_LOCAL static
#endif

#if !defined (ETHIF_TX_LOCAL_INLINE)                                                                                    /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_TX_LOCAL_INLINE LOCAL_INLINE
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
/*! Data to handle transmission process */
typedef struct
{
  P2VAR(EthIf_FrameHdrType, TYPEDEF, ETHIF_APPL_VAR) FrameHdrPtr;
        EthIf_TxContextIterType                      TxCtxtIdx;
        EthIf_UserIterType                           OwnerIdx;
        Eth_FrameType                                EthLayerFrameType;
        Eth_FrameType                                EthIfLayerFrameType;
        uint16                                       EthLayerPayloadLen;
        uint16                                       EthIfLayerPayloadLen;
        uint8                                        BufIdx;
        boolean                                      IsTxConfRequested;
} EthIf_TxFrameHandlingType;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

#define ETHIF_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_IsTxAllowed
 *********************************************************************************************************************/
/*! \brief          Checks if the frame represented by the passed information is allowed to be transmitted
 *  \details        -
 *  \param[in]      txCtxtIdx          Transmission context
 *                                     [range: txCtxtIdx < EthIf_GetSizeOfTxContext()]
 *  \param[in]      ethLayerPayloadLen Ethernet layer payload length
 *  \return         TRUE -  Frame is allowed to be transmitted (including also pure buffer release activity as a TX
 *                          operation)
 *  \return         FALSE - Frame is not allowed to be transmitted
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(boolean, ETHIF_TX_INLINE_CODE) EthIf_IsTxAllowed(
  EthIf_TxContextIterType txCtxtIdx,
  uint16                  ethLayerPayloadLen);
#endif /* ETHIF_FIREWALL_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_RetrieveSrcMacAddr
 *********************************************************************************************************************/
/*! \brief          Retrieves the source MAC address of the Ethernet controller used in the tx context
 *  \details        -
 *  \param[in]      txCtxtIdx  Transmission context
 *                             [range: txCtxtIdx < EthIf_GetSizeOfTxContext()]
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_RetrieveSrcMacAddr(
  EthIf_TxContextIterType txContextIdx);

/**********************************************************************************************************************
 *  EthIf_TriggerTxOnDriver
 *********************************************************************************************************************/
/*! \brief          Triggers transmission of frame on driver
 *  \details        -
 *  \param[in]      ethCtrlIdx       Eth controller the frame shall be transmitted on
 *                                   [range: ethCtrlIdx < EthIf_GetSizeOfEthCtrl()]
 *  \param[in]      txFrameHandling  Transmission handling data
 *  \return         E_OK - Transmission tiggered successful
 *  \return         E_NOT_OK - Transmission wasn't triggered successful
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_TriggerTxOnDriver(
          EthIf_EthCtrlIterType                                  ethCtrlIdx,
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling);

#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_TearDownTransmission
 *********************************************************************************************************************/
/*! \brief          Tears down the transmission for the Ethernet frame silently
 *  \details        This function tears down the transmission of a Ethernet frame silently so upper layers don't notice
 *                  the discard of the frame and the buffer used for frame transmission is available again.
 *  \param[in]      txFrameHandling  Transmission handling data
 *  \return         E_OK - Transmission tear down successful
 *  \return         E_NOT_OK - Transmission tear down wasn't successful
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_TearDownTransmission(
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling);
#endif /* ETHIF_FIREWALL_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_Internal_ProvideTxBuffer
 *********************************************************************************************************************/
/*! \brief          Provides a tx buffer
 *  \details        See EthIf_ProvideTxBuffer() for details.
 *  \param[in]      ethIfCtrlIdx  EthIf controller index
 *                                [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      frameType     EtherType to insert into the Ethernet frame header
 *  \param[in]      priority      Priority of the Ethernet frame, which is coded into the PCP of the IEEE802.3Q
 *                                VLAN tag. If EthIf controller represents a physical data connection the
 *                                priority is ignored.
 *  \param[out]     bufIdxPtr     Index to identify the acquired buffer
 *  \param[out]     bufPtr        Buffer the payload can be written to
 *  \param[in,out]  lenBytePtr    Buffer length:
 *                                [in] - Length in byte needed for the payload, which shall be transmitted
 *                                [out] - Length of the buffer that is provided in byte (has at least the size of
 *                                        the requested length needed for the payload)
 *  \return         BUFREQ_OK - success
 *  \return         BUFREQ_E_NOT_OK - function has been called with invalid parameters
 *  \return         BUFREQ_E_BUSY - all buffers are in use
 *  \return         BUFREQ_E_OVFL - requested length is too large
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_Internal_ProvideTxBuffer(
        uint8                                                                       ethIfCtrlIdx,
        Eth_FrameType                                                               frameType,
        uint8                                                                       priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  bufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  lenBytePtr);

/**********************************************************************************************************************
 *  EthIf_PrepareTransmission
 *********************************************************************************************************************/
/*! \brief          Prepares the transmission of a frame
 *  \details        -
 *  \param[in]      txCtxtIdx          Transmission context for the frame
 *                                     [range: txCtxtIdx < EthIf_GetSizeOfTxContext()]
 *  \param[in]      frameType          EtherType of the frame
 *  \param[in]      lenByte            Length of the frame payload
 *  \param[in]      bufIdx             Buffer the frame is assigned to
 *  \param[in]      ownerIdx           Frame owner the frame belongs to
 *                                     [range: ownerIdx < EthIf_GetSizeOfUser()]
 *  \param[in]      isTxConfRequested  Indicator if Tx confirmation was requested for frame
 *  \param[in]      dstMacAddrPtr      Pointer to the destination MAC address of the frame
 *  \param[in]      srcMacAddrPtr      Pointer to the source MAC address of the frame
 *  \param[out]     txFrameHandling    Transmission handling data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_PrepareTransmission(
          EthIf_TxContextIterType                                txCtxtIdx,
          Eth_FrameType                                          frameType,
          uint16                                                 lenByte,
          uint8                                                  bufIdx,
          EthIf_UserIterType                                     ownerIdx,
          boolean                                                isTxConfRequested,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) dstMacAddrPtr,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) srcMacAddrPtr,
    P2VAR(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_VAR)  txFrameHandling);

/**********************************************************************************************************************
 *  EthIf_ProcessTransmission
 *********************************************************************************************************************/
/*! \brief          Processes the transmission of a frame
 *  \details        -
 *  \param[in]      txFrameHandling  Transmission handling data
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_ProcessTransmission(
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling);

/**********************************************************************************************************************
 *  EthIf_Internal_VTransmit
 *********************************************************************************************************************/
/*! \brief          Triggers transmission of an Ethernet frame with a given source MAC address
 *  \details        See EthIf_VTransmit() for details.
 *  \param[in]      ethIfCtrlIdx    EthIf controller index
 *                                  [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      bufIdx          Index to identify the buffer for frame transmission
 *                                  [range: bufIdx <= EthIf_GetMaxTxBufForEthIfCtrl(ethIfCtrlIdx)]
 *  \param[in]      frameType       EtherType to insert into the Ethernet frame header
 *  \param[in]      txConfirmation  Request for a transmission confirmation:
 *                                  FALSE - no confirmation desired
 *                                  TRUE - confirmation desired
 *  \param[in]      lenByte         Payload length to be transmitted
 *  \param[in]      dstMacAddrPtr   Destination MAC address
 *  \param[in]      srcMacAddrPtr   Source MAC address:
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
 *********************************************************************************************************************/
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_Internal_VTransmit(
        uint8                                     ethIfCtrlIdx,
        EthIf_UserIterType                        ownerIdx,
        uint8                                     bufIdx,
        Eth_FrameType                             frameType,
        boolean                                   txConfirmation,
        uint16                                    lenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  dstMacAddrPtr,  /* PRQA S 3673 */ /* MD_EthIf_3673 */
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  srcMacAddrPtr); /* PRQA S 3673 */ /* MD_EthIf_3673 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_IsTxAllowed
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_TX_LOCAL_INLINE FUNC(boolean, ETHIF_TX_INLINE_CODE) EthIf_IsTxAllowed(
  EthIf_TxContextIterType txCtxtIdx,
  uint16                  ethLayerPayloadLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean result;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if actually a pure buffer release activity is requested instead of a frame transmission */
  if (ethLayerPayloadLen == ETHIF_TX_BUFFER_RELEASE_LEN)
  {
    /* #110 Only a buffer release is requested as TX operation and therefore the firewall does not need not to be
     * involved */
    result = TRUE;
  }
  else /* #20 An actual frame transmission is requested by a TX operation */
  {
    /* #210 If firewall is enabled let it check if frame is allowed to be transmitted */
    result = EthFw_IsFrameTxAllowed((uint8)EthIf_GetSnvOfEthIfCtrl(EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx)),
                                    EthIf_GetAddrFrameHdrOfTxContext(txCtxtIdx),
                                    EthIf_GetPayloadPtrOfTxContext(txCtxtIdx),
                                    EthIf_GetPayloadLenOfTxContext(txCtxtIdx));                                         /* SBSW_ETHIF_TX_CONTEXT_FCT_CSL_MEM_PTR_PASS_WITH_FCT_PARAM_IDX */
  }

  return result;
} /* EthIf_IsTxAllowed() */
#endif /* ETHIF_FIREWALL_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_RetrieveSrcMacAddr
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_TX_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_RetrieveSrcMacAddr(
  EthIf_TxContextIterType txContextIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  EthIf_EthIfCtrlIdxOfTxContextType ethIfCtrlIdx = EthIf_GetEthIfCtrlIdxOfTxContext(txContextIdx);
  EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);
  P2VAR(EthIf_FrameHdrType, AUTOMATIC, ETHIF_APPL_VAR) frameHdr = EthIf_GetAddrFrameHdrOfTxContext(txContextIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if there is a valid source MAC address stored for the Ethernet controller. If this isn't the case
   *     retrieve and store it. */
  if( EthIf_IsValidOfSrcMacAddrBuffer(ethCtrlIdx) == FALSE )
  {
    EthIf_EthDrvApiIdxOfEthCtrlType ethCtrlDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    EthIf_GetGetPhysAddrOfEthDrvApi(ethCtrlDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                      EthIf_GetSrcMacOfSrcMacAddrBuffer(ethCtrlIdx));                   /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */

    EthIf_SetValidOfSrcMacAddrBuffer(ethCtrlIdx, TRUE);                                                                 /* SBSW_ETHIF_COMMON_CSL03 */
  }

  /* #20 Return MAC address in tx context element */
  frameHdr->SrcMacAddrPtr = EthIf_GetSrcMacOfSrcMacAddrBuffer(ethCtrlIdx);                                              /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_WITH_FCT_PARAM_IDX */
} /* EthIf_RetrieveSrcMacAddr() */

/**********************************************************************************************************************
 *  EthIf_TriggerTxOnDriver
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_TriggerTxOnDriver(
          EthIf_EthCtrlIterType                                  ethCtrlIdx,
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling)
{
  Std_ReturnType retVal;

  EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

  /* #10 Check if frame shall be transmitted with specific Source MAC address */
  if( (EthIf_GetVTransmitOfEthDrvApi(ethDrvApiIdx) != NULL_PTR) &&
      (txFrameHandling->FrameHdrPtr->SrcMacAddrPtr != NULL_PTR)    )
  {
    /* #100 Vector specific VTransmit API (with ability to pass Source MAC address) is used */
    /* \trace SPEC-2393643 */
    retVal = EthIf_GetVTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                         txFrameHandling->BufIdx,
                                                         txFrameHandling->EthLayerFrameType,
                                                         txFrameHandling->IsTxConfRequested,
                                                         txFrameHandling->EthLayerPayloadLen,
                                                         txFrameHandling->FrameHdrPtr->DstMacAddrPtr,
                                                         txFrameHandling->FrameHdrPtr->SrcMacAddrPtr);                  /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_INT_PARAM_PTR_CSL03 */
  }
  /* #20 Otherwise */
  else
  {
    /* #200 AUTOSAR transmit API is used */
    /* \trace SPEC-2393643 */
    retVal = EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                        txFrameHandling->BufIdx,
                                                        txFrameHandling->EthLayerFrameType,
                                                        txFrameHandling->IsTxConfRequested,
                                                        txFrameHandling->EthLayerPayloadLen,
                                                        txFrameHandling->FrameHdrPtr->DstMacAddrPtr);                   /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_INT_PARAM_PTR_CSL03 */
  }

  return retVal;
} /* EthIf_TriggerTxOnDriver() */

#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/**********************************************************************************************************************
 *  EthIf_TearDownTransmission
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_TearDownTransmission(
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;

  EthIf_EthIfCtrlIdxOfTxContextType ethIfCtrlIdx = EthIf_GetEthIfCtrlIdxOfTxContext(txFrameHandling->TxCtxtIdx);
  EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);
  EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Release buffer in Ethernet driver */
  retVal = EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                      txFrameHandling->BufIdx,
                                                      txFrameHandling->EthLayerFrameType,
                                                      txFrameHandling->IsTxConfRequested,
                                                      ETHIF_TX_BUFFER_RELEASE_LEN,
                                                      txFrameHandling->FrameHdrPtr->DstMacAddrPtr);                     /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_INT_PARAM_PTR_CSL03 */

  if( retVal == E_OK )
  {
    /* #20 Check if TxConfirmation was requested, if so call it so upper layer is informed about finish of transmission
     *     processing.
     *     Otherwise recharge state variables so transmission is also finished for EthIf. */
    if( txFrameHandling->IsTxConfRequested == TRUE )
    {
      EthIf_TxConfirmation((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx), txFrameHandling->BufIdx);
    }
    else
    {
      EthIf_SetTxPendingOfTxContext(txFrameHandling->TxCtxtIdx, FALSE);                                                 /* SBSW_ETHIF_CSL_IDX_STORED */
      EthIf_SetValidOfTxContext(txFrameHandling->TxCtxtIdx, FALSE);                                                     /* SBSW_ETHIF_CSL_IDX_STORED */
    }
  }

  return retVal;
} /* EthIf_TearDownTransmission() */
#endif /* ETHIF_FIREWALL_SUPPORT */

/**********************************************************************************************************************
 *  EthIf_Internal_ProvideTxBuffer
 *********************************************************************************************************************/
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
 */
ETHIF_TX_LOCAL_INLINE FUNC(BufReq_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_Internal_ProvideTxBuffer(
        uint8                                                                       ethIfCtrlIdx,
        Eth_FrameType                                                               frameType,
        uint8                                                                       priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  bufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  bufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  lenBytePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  /* #10 Check if the EthIf controller is active */
  if( EthIf_GetEthIfCtrlMode(ethIfCtrlIdx) == ETH_MODE_ACTIVE )
  {
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    /* #100 Check the EthIf controller type (non-tagged or tagged) and increase the needed buffer length
     *      by the amount of the tag if necessary */
    if( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
    {
      /* \trace SPEC-2393633 */
      (*lenBytePtr) += ETHIF_VLAN_TAG_LEN_BYTE;                                                                         /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    }

    /* #110 Redirect the buffer request call to the driver */
    /* \trace SPEC-2393634 */
    retVal = EthIf_GetProvideTxBufferOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                               bufIdxPtr,
                                                               bufPtr,
                                                               lenBytePtr);                                             /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_INT_PARAM_PTR_CSL03 */

    /* #120 Check if buffer was successfully provided by the driver and buffer index is in expected range */
    if( retVal == BUFREQ_OK )
    {
      if( (*bufIdxPtr) <= EthIf_GetMaxTxBufIdxForEthIfCtrl(ethIfCtrlIdx) )
      {
        /* #1200 Trigger buffer provision finilazation if buffer index is in expected range */
        /* PRQA S 0310 7 */ /* MD_EthIf_310_Buffer */
        EthIf_FinalizeTxBufferProvision(ethIfCtrlIdx,
                                        ethCtrlIdx,
                                        frameType,
                                        priority,
                                        (*bufIdxPtr),
                                        lenBytePtr,
                                        (P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR))bufPtr);            /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
      }
      else
      {
        /* #1210 Otherwise trigger release of buffer cause driver thinks everything was OK and locked its resources. */
        (void)EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                        (*bufIdxPtr),
                                                        frameType,
                                                        FALSE,
                                                        ETHIF_TX_BUFFER_RELEASE_LEN,
                                                        EthIf_BroadcastMac);                                            /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_INT_PARAM_PTR_CSL03 */
        retVal = BUFREQ_E_NOT_OK;
      }
    }
  }

  return retVal;
} /* EthIf_Internal_ProvideTxBuffer() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  EthIf_PrepareTransmission
 *********************************************************************************************************************/
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
ETHIF_TX_LOCAL_INLINE FUNC(void, ETHIF_TX_INLINE_CODE) EthIf_PrepareTransmission(
          EthIf_TxContextIterType                                txCtxtIdx,
          Eth_FrameType                                          frameType,
          uint16                                                 lenByte,
          uint8                                                  bufIdx,
          EthIf_UserIterType                                     ownerIdx,
          boolean                                                isTxConfRequested,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) dstMacAddrPtr,
  P2CONST(uint8,                     AUTOMATIC, ETHIF_APPL_DATA) srcMacAddrPtr,
    P2VAR(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_VAR)  txFrameHandling)
{
  EthIf_EthIfCtrlIdxOfTxContextType ethIfCtrlIdx = EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx);

  /* #10 Setup tx frame handling */
  txFrameHandling->FrameHdrPtr          = EthIf_GetAddrFrameHdrOfTxContext(txCtxtIdx);                                  /* SBSW_ETHIF_TX_CONTEXT_FCT_CSL_MEM_PTR_PASS_WITH_FCT_PARAM_IDX */
  txFrameHandling->EthIfLayerFrameType  = frameType;                                                                    /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->EthIfLayerPayloadLen = lenByte;                                                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->EthLayerFrameType    = frameType;                                                                    /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->EthLayerPayloadLen   = lenByte;                                                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->TxCtxtIdx            = txCtxtIdx;                                                                    /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->BufIdx               = bufIdx;                                                                       /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  txFrameHandling->IsTxConfRequested    = isTxConfRequested;                                                            /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */

  /* #20 Retrieve source and destination MAC addresses */
  EthIf_SetPayloadLenOfTxContext(txCtxtIdx, lenByte);                                                                   /* SBSW_ETHIF_TX_CONTEXT_FCT_CSL_MEM_PTR_PASS_WITH_FCT_PARAM_IDX */
  txFrameHandling->FrameHdrPtr->DstMacAddrPtr = dstMacAddrPtr;                                                          /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  if( srcMacAddrPtr != NULL_PTR )
  {
    txFrameHandling->FrameHdrPtr->SrcMacAddrPtr = srcMacAddrPtr;                                                        /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }
  else
  {
    EthIf_RetrieveSrcMacAddr(txCtxtIdx);
  }

  if( lenByte == 0u )
  {
    txFrameHandling->IsTxConfRequested = FALSE;                                                                         /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }

  /* #30 Check if Tx Confirmation is requested and if so setup information to be able to call correct user in
   *     EthIf_TxConfirmation() */
  if ( txFrameHandling->IsTxConfRequested == TRUE )
  {
    EthIf_SetUserIdxOfTxContext(txCtxtIdx, (EthIf_UserIdxOfTxContextType)ownerIdx);                                     /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_WITH_FCT_PARAM_IDX */
  }

  /* #40 Check the EthIf controller type (non-tagged or tagged) and if buffer release is requested and
   *     adapt the EtherType and payload length passed to driver if necessary */
  if( ( EthIf_GetTypeOfEthIfCtrl(ethIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL ) &&
      ( lenByte != 0u )                                                                              )
  {
    /* \trace SPEC-2393642 */
    txFrameHandling->EthLayerFrameType   = (uint16)ETHIF_VLAN_TPID;                                                     /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
    txFrameHandling->EthLayerPayloadLen += (uint16)ETHIF_VLAN_TAG_LEN_BYTE;                                             /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
  }
} /* EthIf_PrepareTransmission() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  EthIf_ProcessTransmission
 *********************************************************************************************************************/
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
 */
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_ProcessTransmission(
  P2CONST(EthIf_TxFrameHandlingType, AUTOMATIC, ETHIF_APPL_DATA) txFrameHandling)
{
  Std_ReturnType retVal;

  EthIf_EthIfCtrlIdxOfTxContextType ethIfCtrlIdx = EthIf_GetEthIfCtrlIdxOfTxContext(txFrameHandling->TxCtxtIdx);

  /* #10 Setup tx context data for possible EthIf_TxConfirmation(). If not requested discard tx context. */
  if( txFrameHandling->IsTxConfRequested == TRUE )
  {
    EthIf_SetTxPendingOfTxContext(txFrameHandling->TxCtxtIdx, TRUE);                                                    /* SBSW_ETHIF_CSL_IDX_STORED */
  }
  else
  {
    EthIf_SetTxPendingOfTxContext(txFrameHandling->TxCtxtIdx, FALSE);                                                   /* SBSW_ETHIF_CSL_IDX_STORED */
    EthIf_SetValidOfTxContext(txFrameHandling->TxCtxtIdx, FALSE);                                                       /* SBSW_ETHIF_CSL_IDX_STORED */
  }

  /* #20 Trigger transmission by utilizing the driver */
  retVal = EthIf_TriggerTxOnDriver(EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx), txFrameHandling);                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */

  /* #30 Check if transmission was successfully triggered */
  if( retVal == E_OK )
  {
    /* #300 Update transmission statistics */
    EthIf_UpdateTxStats(ethIfCtrlIdx, txFrameHandling->EthIfLayerPayloadLen);

#if   ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
    /* #310 Pass frame to the mirroring sub component */
    EthIf_MirrorTxTraffic(ethIfCtrlIdx,
                          txFrameHandling->BufIdx,
                          txFrameHandling->EthLayerFrameType,
                          txFrameHandling->EthLayerPayloadLen,
                          txFrameHandling->FrameHdrPtr->DstMacAddrPtr);                                                 /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
  }
  /* #40 Otherwise */
  else
  {
    /* #400 Revert discard of tx context if triggering transmission failed so it is possible that user triggers
     *      transmission again or releases the buffer */
    EthIf_SetTxPendingOfTxContext(txFrameHandling->TxCtxtIdx, FALSE);                                                   /* SBSW_ETHIF_CSL_IDX_STORED */
    EthIf_SetValidOfTxContext(txFrameHandling->TxCtxtIdx, TRUE);                                                        /* SBSW_ETHIF_CSL_IDX_STORED */
  }

  return retVal;
} /* EthIf_ProcessTransmission() */

/**********************************************************************************************************************
 *  EthIf_Internal_VTransmit
 *********************************************************************************************************************/
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
 */
ETHIF_TX_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_TX_INLINE_CODE) EthIf_Internal_VTransmit(
        uint8                                     ethIfCtrlIdx,
        EthIf_UserIterType                        ownerIdx,
        uint8                                     bufIdx,
        Eth_FrameType                             frameType,
        boolean                                   txConfirmation,
        uint16                                    lenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  dstMacAddrPtr,  /* PRQA S 3673 */ /* MD_EthIf_3673 */
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  srcMacAddrPtr)  /* PRQA S 3673 */ /* MD_EthIf_3673 */
{
   Std_ReturnType retVal = E_NOT_OK;

  /* #10 Check if the EthIf controller is active */
  if( EthIf_GetEthIfCtrlMode(ethIfCtrlIdx) == (Eth_ModeType)ETH_MODE_ACTIVE )
  {
    EthIf_TxContextIterType txCtxtIdx;
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(ethIfCtrlIdx);

    txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, bufIdx);

    /* \trace SPEC-2393648 */
    /* #100 Check that buffer passed for transmission was previously acquired by a call to EthIf_ProvideTxBuffer() */
    if ( (EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE)         &&
         (EthIf_IsTxPendingOfTxContext(txCtxtIdx) == FALSE)    &&
         (EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx) == ethIfCtrlIdx)    )
    {
      EthIf_TxFrameHandlingType txFrameHandling;

      /* #1000 Trigger preparation of transmission */
      EthIf_PrepareTransmission(txCtxtIdx,
                                frameType,
                                lenByte,
                                bufIdx,
                                ownerIdx,
                                txConfirmation,
                                dstMacAddrPtr,
                                srcMacAddrPtr,
                                &txFrameHandling);                                                                      /* SBSW_ETHIF_INT_FCT_PARAM_PTR_PASS_AND_REF_OF_STACK_VAR */

#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
      /* #1020 Check if transmission is allowed */
      if( EthIf_IsTxAllowed(txCtxtIdx, txFrameHandling.EthLayerPayloadLen) == TRUE )
      {
#endif /* ETHIF_FIREWALL_SUPPORT */
        /* #10200 Trigger processing of transmission */
        retVal = EthIf_ProcessTransmission(&txFrameHandling);                                                           /* SBSW_ETHIF_REF_OF_STACK_VAR */
#if ( ETHIF_FIREWALL_SUPPORT == STD_ON )                                                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
      }
      /* #1030 Otherwise */
      else
      {
        /* #10300 Transmission wasn't allowed -> silently discard transmission */
        retVal = EthIf_TearDownTransmission(&txFrameHandling);                                                          /* SBSW_ETHIF_REF_OF_STACK_VAR */
      }
#endif /* ETHIF_FIREWALL_SUPPORT */
    }
  }

  return retVal;
} /* EthIf_Internal_VTransmit() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_ProvideTxBuffer
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(BufReq_ReturnType, ETHIF_CODE) EthIf_ProvideTxBuffer(
        uint8                                                                       CtrlIdx,
        Eth_FrameType                                                               FrameType,
        uint8                                                                       Priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType  retVal;
  uint8              errorId = ETHIF_E_NO_ERROR;

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal  = BUFREQ_E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393635 */
    /* \trace SPEC-2393640 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393636 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( EthIf_QueryForFrameOwner(FrameType) >= EthIf_GetSizeOfUser() )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( Priority > ETHIF_VLAN_PCP_MAX_VAL )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( (EthIf_GetTypeOfEthIfCtrl(CtrlIdx) == ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL) &&
           (Priority                          != 0u)                                               )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( BufIdxPtr == NULL_PTR)
  {
    /* \trace SPEC-2393637 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( BufPtr == NULL_PTR)
  {
    /* \trace SPEC-2393638 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( LenBytePtr == NULL_PTR)
  {
    /* \trace SPEC-2393639 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( (*LenBytePtr) > EthIf_GetMtuOfEthIfCtrl(CtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Trigger buffer provision */
    retVal = EthIf_Internal_ProvideTxBuffer(CtrlIdx,
                                            FrameType,
                                            Priority,
                                            BufIdxPtr,
                                            BufPtr,
                                            LenBytePtr);                                                                /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_PROVIDE_TX_BUFFER, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_ProvideTxBuffer() */ /* PRQA S 6030, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_VTransmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VTransmit(
        uint8                                     CtrlIdx,
        uint8                                     BufIdx,
        Eth_FrameType                             FrameType,
        boolean                                   TxConfirmation,
        uint16                                    LenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  DstMacAddrPtr,  /* PRQA S 3673 */ /* MD_EthIf_3673 */
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  SrcMacAddrPtr)  /* PRQA S 3673 */ /* MD_EthIf_3673 */
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType     retVal;
  uint8              errorId  = ETHIF_E_NO_ERROR;
  EthIf_UserIterType ownerIdx = EthIf_QueryForFrameOwner(FrameType);

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  retVal = E_NOT_OK;
#endif /* ETHIF_DEV_ERROR_DETECT */

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393644 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    /* \trace SPEC-2393645 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthIfCtrl(CtrlIdx) )
  {
    /* \trace SPEC-2393646 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( ownerIdx >= EthIf_GetSizeOfUser() )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( LenByte > EthIf_GetMtuOfEthIfCtrl(CtrlIdx) )
  {
    errorId = ETHIF_E_INV_PARAM;
  }
  else if( DstMacAddrPtr == NULL_PTR )
  {
    /* \trace SPEC-2393647 */
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Trigger transmission */
    retVal = EthIf_Internal_VTransmit(CtrlIdx,
                                      ownerIdx,
                                      BufIdx,
                                      FrameType,
                                      TxConfirmation,
                                      LenByte,
                                      DstMacAddrPtr,
                                      SrcMacAddrPtr);                                                                   /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS */
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_TRANSMIT, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

  return retVal;
} /* EthIf_VTransmit() */ /* PRQA S 6060, 6080 */ /* MD_MSR_STPAR, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_Transmit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_Transmit(
        uint8                                     CtrlIdx,
        uint8                                     BufIdx,
        Eth_FrameType                             FrameType,
        boolean                                   TxConfirmation,
        uint16                                    LenByte,
  P2VAR(uint8,        AUTOMATIC, ETHIF_APPL_VAR)  PhysAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Redirect call to generalized transmit API */
  return EthIf_VTransmit(CtrlIdx,
                         BufIdx,
                         FrameType,
                         TxConfirmation,
                         LenByte,
                         PhysAddrPtr,
                         NULL_PTR);                                                                                     /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS */
} /* EthIf_Transmit() */ /* PRQA S 6060 */ /* MD_MSR_STPAR */

/**********************************************************************************************************************
 *  EthIf_TxConfirmation
 *********************************************************************************************************************/
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
FUNC(void, ETHIF_CODE) EthIf_TxConfirmation(
    uint8  CtrlIdx,
    uint8  BufIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHIF_E_NO_ERROR;
  EthIf_EthCtrlIterType ethCtrlIdx = EthIf_QueryForEthIfEthCtrl(CtrlIdx);

  /* ----- Development Error Checks ------------------------------------- */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                  /* COV_ETHIF_SAFE_FEAT */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    /* \trace SPEC-2393660 */
    /* \trace SPEC-2393663 */
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( ethCtrlIdx >= EthIf_GetSizeOfEthCtrl() )
  {
    /* \trace SPEC-2393661 */
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufIdx > EthIf_GetMaxTxBufIdxForEthCtrl(ethCtrlIdx) )
  {
    /* \trace SPEC-2393662 */
    errorId = ETHIF_E_INV_PARAM;
  }
  else
#endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_TxContextIterType txCtxtIdx;

    txCtxtIdx = EthIf_CalcTxCtxtIdx(ethCtrlIdx, BufIdx);

    /* #30 Check if a Tx confirmation was requested for the buffer */
    if ( EthIf_IsValidOfTxContext(txCtxtIdx) == TRUE )
    {
      EthIf_TxConfirmationsIndIterType indIdx;
      EthIf_UserIdxOfTxContextType userIdx = EthIf_GetUserIdxOfTxContext(txCtxtIdx);

      /* #300 Call Tx confirmation of users */
      /* \trace SPEC-2393682 */
      for( indIdx = EthIf_GetTxConfirmationsIndStartIdxOfUser(userIdx);
           indIdx < EthIf_GetTxConfirmationsIndEndIdxOfUser(userIdx);
           indIdx++ )
      {
        EthIf_TxConfirmationsIndType txConfIdx = EthIf_GetTxConfirmationsInd(indIdx);
        EthIf_GetTxConfirmations(txConfIdx)((uint8)EthIf_GetSnvOfEthIfCtrl(EthIf_GetEthIfCtrlIdxOfTxContext(txCtxtIdx)),
                                            BufIdx);                                                                    /* SBSW_ETHIF_USERAPI_FCT_PTR_CSL03 */
      }
      /* #310 Invalidate the Tx context */
      EthIf_SetTxPendingOfTxContext(txCtxtIdx, FALSE);                                                                  /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV */
      EthIf_SetValidOfTxContext(txCtxtIdx, FALSE);                                                                      /* SBSW_ETHIF_CSL_PTR_WRITE_TX_CONTEXT_IDX_CALL_CONV */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#if (ETHIF_DEV_ERROR_REPORT == STD_ON)
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_TX_CONFIRMATION, errorId);
  }
#else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
#endif

} /* EthIf_TxConfirmation() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthIf_MainFunctionTx
 *********************************************************************************************************************/
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
 */
FUNC(void, ETHIF_CODE) EthIf_MainFunctionTx( void )
{
  /* #10 Check if module is initialized */
  if ( EthIf_ModuleInitialized == ETHIF_STATE_INIT )
  {
    /* #100 If feature transmission confirmation polling is enabled */
    /* \trace SPEC-2393671 */
#if ( ETHIF_ENABLE_TX_INTERRUPT == STD_OFF )
    EthIf_EthCtrlIterType ethCtrlIdx;

    /* #1000 Tx confirmation polling for each Eth controller used */
    /* \trace SPEC-2393681 */
    for( ethCtrlIdx = 0;
         ethCtrlIdx < EthIf_GetSizeOfEthCtrl();
         ethCtrlIdx++ )
    {
      /* #10000 Check if controller is active */
      if( EthIf_GetEthCtrlModeCnt(ethCtrlIdx) > 0u )
      {
        EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
        /* #100000 Trigger tx confirmation */
        EthIf_GetTxConfOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx));                             /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_CSL03 */
      }
    }
#endif /* ETHIF_ENABLE_TX_INTERRUPT */

    /* #110 If feauture explicit main function state is disabled */
#if ( ETHIF_ENABLE_MAIN_FUNCTION_STATE == STD_OFF )
    /* #120 Check if main function state has to be called */
    /* \trace SPEC-2393672 */
    if( EthIf_GetMainFuncStateDecoupleFreqCnt() == 0u )
    {
      /* #1200 Call main function state and reset polling frequency counter */
      EthIf_MainFunctionState();
      /* Restart counter */
      EthIf_SetMainFuncStateDecoupleFreqCnt(EthIf_GetLinkStateChgMainReload());                                         /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
    }
    /* #130 Decrease polling frequency counter */
    EthIf_DecMainFuncStateDecoupleFreqCnt();                                                                            /* SBSW_ETHIF_COMMON_CFG_PTR_INT_FCT_PREV_MODULE_INIT_CHECK */
#endif /* ETHIF_ENABLE_MAIN_FUNCTION_STATE */
  }
} /* EthIf_MainFunctionTx() */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Tx.c
 *********************************************************************************************************************/

