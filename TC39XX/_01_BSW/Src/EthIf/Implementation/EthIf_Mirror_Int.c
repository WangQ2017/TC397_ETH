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
/*!        \file  EthIf_Mirror_Int.c
 *        \brief  EthIf Mirror internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module Mirror of EthIf
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

#define ETHIF_MIRROR_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Mirror_Int.h"

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

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_GetFreeMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*! \brief          Retrieves a free Tx traffic info element
 *  \details        This function retrieves a Tx traffic info element used to store context between buffer request and
 *                  transmit of a frame to be mirrored.
 *  \param[out]     txTrafficInfoIdx  Index of related tx traffic info object
 *  \return         E_OK - free element found -> txTrafficInfoIdx has valid value
 *  \return         E_NOT_OK - no free element available -> txTrafficInfoIdx must not be used
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MIRROR_INLINE_CODE) EthIf_GetFreeMirrorTxTrafficInfo(
  P2VAR(EthIf_MirrorTxInfoIterType, AUTOMATIC, ETHIF_APPL_VAR)  txTrafficInfoIdx);

/***********************************************************************************************************************
 *  EthIf_ReleaseMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*! \brief          Releases Tx traffic info element
 *  \details        This function releases a previously allocated Tx traffic info element.
 *  \param[in]      txTrafficInfoIdx  Tx Traffic info element to be released
 *                                    [range: txTrafficInfoIdx < EthIf_GetSizeOfMirrorTxInfo()]
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(void, ETHIF_MIRROR_INLINE_CODE) EthIf_ReleaseMirrorTxTrafficInfo(
  EthIf_MirrorTxInfoIterType  txTrafficInfoIdx);

/***********************************************************************************************************************
 *  EthIf_GetRelatedMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*! \brief          Retrieves a allocated Tx traffic info element
 *  \details        This function retrieves a allocated Tx traffic info element to get access to the information of
 *                  the buffer request context in transmit context.
 *  \param[in]      ethIfCtrlIdx      EthIf controller index
 *                                    [range: ethIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      ethTxBufIdx       Tx buffer index
 *  \param[out]     txTrafficInfoIdx  Inde of the retrieved element
 *  \return         E_OK - a Tx traffic info element was retrieved
 *  \return         E_NOT_OK - no Tx traffic info element available for the given transmit procedure context
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MIRROR_INLINE_CODE) EthIf_GetRelatedMirrorTxTrafficInfo(
        EthIf_EthIfCtrlIterType                                 ethIfCtrlIdx,
        uint8                                                   ethTxBufIdx,
  P2VAR(EthIf_MirrorTxInfoIterType, AUTOMATIC, ETHIF_APPL_VAR)  txTrafficInfoIdx);
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_GetFreeMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MIRROR_INLINE_CODE) EthIf_GetFreeMirrorTxTrafficInfo(
  P2VAR(EthIf_MirrorTxInfoIterType, AUTOMATIC, ETHIF_APPL_VAR)  txTrafficInfoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  EthIf_MirrorTxInfoIterType mirrorTxInfoIdx;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;

  /* #10 Enter exclusive area (Reason: Ensure that a Tx traffic info element can only be allocated once) */
  EthIf_EnterExclusiveArea(TX_MIRROR_ELEMENT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 For each Tx traffic info element */
  for( mirrorTxInfoIdx = 0;
       mirrorTxInfoIdx < EthIf_GetSizeOfMirrorTxInfo();
       mirrorTxInfoIdx++ )
  {
    /* #200 Check if element is free */
    if( EthIf_IsUsedOfMirrorTxInfo(mirrorTxInfoIdx) == FALSE )
    {
      /* #2000 Allocate free element and pass it to caller */
      EthIf_SetUsedOfMirrorTxInfo(mirrorTxInfoIdx, TRUE);                                                               /* SBSW_ETHIF_COMMON_CSL01 */
      (*txTrafficInfoIdx) = mirrorTxInfoIdx;                                                                            /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      retVal = E_OK;
      break;
    }
  }

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(TX_MIRROR_ELEMENT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* EthIf_GetFreeMirrorTxTrafficInfo() */

/***********************************************************************************************************************
 *  EthIf_ReleaseMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(void, ETHIF_MIRROR_INLINE_CODE) EthIf_ReleaseMirrorTxTrafficInfo(
  EthIf_MirrorTxInfoIterType txTrafficInfoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Release Tx traffic info element if it is in use */
  if( EthIf_IsUsedOfMirrorTxInfo(txTrafficInfoIdx) == TRUE )
  {
    EthIf_SetInfoValidOfMirrorTxInfo(txTrafficInfoIdx, FALSE);                                                          /* SBSW_ETHIF_INT_FCT_IDX_PASS */
    EthIf_SetUsedOfMirrorTxInfo(txTrafficInfoIdx, FALSE);                                                               /* SBSW_ETHIF_INT_FCT_IDX_PASS */
  }
} /* EthIf_ReleaseMirrorTxTrafficInfo() */

/***********************************************************************************************************************
 *  EthIf_GetRelatedMirrorTxTrafficInfo
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHIF_MIRROR_INT_LOCAL_INLINE FUNC(Std_ReturnType, ETHIF_MIRROR_INLINE_CODE) EthIf_GetRelatedMirrorTxTrafficInfo(
        EthIf_EthIfCtrlIterType                                 ethIfCtrlIdx,
        uint8                                                   ethTxBufIdx,
  P2VAR(EthIf_MirrorTxInfoIterType, AUTOMATIC, ETHIF_APPL_VAR)  txTrafficInfoIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  EthIf_MirrorTxInfoIterType mirrorTxInfoIdx;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;

  /* #10 Enter exclusive area (Reason: Ensure that a Tx traffic info element is retrieved in a constent manner) */
  EthIf_EnterExclusiveArea(TX_MIRROR_ELEMENT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  /* #20 For each Tx traffic info element */
  for( mirrorTxInfoIdx = 0;
       mirrorTxInfoIdx < EthIf_GetSizeOfMirrorTxInfo();
       mirrorTxInfoIdx++ )
  {
    /* #200 Check if the element is related to the context queried for */
    if( (EthIf_IsUsedOfMirrorTxInfo(mirrorTxInfoIdx)               == TRUE)         &&
        (EthIf_IsInfoValidOfMirrorTxInfo(mirrorTxInfoIdx)          == TRUE)         &&
        (EthIf_GetEthIfCtrlIdxOfMirrorTxInfo(mirrorTxInfoIdx)      == ethIfCtrlIdx) &&
        (EthIf_GetSrcEthTxBufferIdxOfMirrorTxInfo(mirrorTxInfoIdx) == ethTxBufIdx)     )
    {
      /* #2000 Pass related element to the caller */
      (*txTrafficInfoIdx) = mirrorTxInfoIdx;                                                                            /* SBSW_ETHIF_INT_FCT_PARAM_PTR_WRITE */
      retVal = E_OK;
      break;
    }
  }

  /* #30 Leave exclusive area */
  EthIf_ExitExclusiveArea(TX_MIRROR_ELEMENT); /* PRQA S 3109 */ /* MD_MSR_14.3 */

  return retVal;
} /* EthIf_GetRelatedMirrorTxTrafficInfo() */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_Mirror_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_Mirror_Init( void )
{
#if   ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                               /* COV_ETHIF_QM_FEAT_CHECK_ON */
  EthIf_MirrorTxInfoIterType mirrorTxInfoIdx;

  /* #10 Initalize tx mirroring information elements by marking them as invalid. */
  for( mirrorTxInfoIdx = 0;
       mirrorTxInfoIdx < EthIf_GetSizeOfMirrorTxInfo();
       mirrorTxInfoIdx++ )
  {
    EthIf_SetInfoValidOfMirrorTxInfo(mirrorTxInfoIdx, FALSE);                                                           /* SBSW_ETHIF_COMMON_CSL01 */
    EthIf_SetUsedOfMirrorTxInfo(mirrorTxInfoIdx, FALSE);                                                                /* SBSW_ETHIF_COMMON_CSL01 */
  }
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */
} /* EthIf_Mirror_Init() */

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                                 /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ProvideTxMirroringBuffer
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
FUNC(void, ETHIF_CODE) EthIf_ProvideTxMirroringBuffer(
        EthIf_EthIfCtrlIterType                   srcEthIfCtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  srcDataPtr,
        uint8                                     srcDataBufIdx,
        uint16                                    srcFrameLen)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint16 frmLen = srcFrameLen;

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Tx traffic must be mirrored */
  if( EthIf_IsMirrorTxDestIdxUsedOfEthIfCtrl(srcEthIfCtrlIdx) )
  {
    EthIf_MirrorTxInfoIterType mirrorTxInfoIdx;
    EthIf_MirrorDestIterType   mirroringDestIdx = EthIf_GetMirrorTxDestIdxIdxOfEthIfCtrl(srcEthIfCtrlIdx);

    /* #100 Check if a Tx traffic mirror info element for buffer request context storage is available */
    if( EthIf_GetFreeMirrorTxTrafficInfo(&mirrorTxInfoIdx) == E_OK )                                                    /* SBSW_ETHIF_REF_OF_STACK_VAR */
    {
      P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR) destBufPtr;
      EthIf_EthCtrlIdxOfMirrorDestType ethCtrlIdx = EthIf_GetEthCtrlIdxOfMirrorDest(mirroringDestIdx);
      EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);
      destBufPtr = (P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR))EthIf_GetAddrDestPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx); /* PRQA S 0310 */ /* MD_EthIf_310_Buffer */

      /* #1000 Check if buffer allocation on mirroring destination is successful */
      /* PRQA S 0310, 3305 4 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
      if( EthIf_GetProvideTxBufferOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                            EthIf_GetAddrDestEthTxBufferIdxOfMirrorTxInfo(mirrorTxInfoIdx),
                                                            &destBufPtr,
                                                            &frmLen) == BUFREQ_OK )                                     /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
      {
        /* #10000 Store buffer request context in Tx traffic info element to be able to retrieve it in transmit context */
        /* PRQA S 0310 2 */ /* MD_EthIf_310_Buffer */
        EthIf_SetSrcPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx, (EthIf_FrameBufferPtrType)srcDataPtr);                    /* SBSW_ETHIF_CSL_IDX_RET_BY_FCT */
        EthIf_SetDestPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx, (EthIf_FrameBufferPtrType)destBufPtr);                   /* SBSW_ETHIF_CSL_IDX_RET_BY_FCT */
        EthIf_SetEthIfCtrlIdxOfMirrorTxInfo(mirrorTxInfoIdx, (EthIf_EthIfCtrlIdxOfMirrorTxInfoType)srcEthIfCtrlIdx);    /* SBSW_ETHIF_CSL_IDX_RET_BY_FCT */
        EthIf_SetSrcEthTxBufferIdxOfMirrorTxInfo(mirrorTxInfoIdx, srcDataBufIdx);                                       /* SBSW_ETHIF_CSL_IDX_RET_BY_FCT */
        EthIf_SetInfoValidOfMirrorTxInfo(mirrorTxInfoIdx, TRUE);                                                        /* SBSW_ETHIF_CSL_IDX_RET_BY_FCT */
      }
      /* #1010 Otherwise (no buffer for mirroring could be allocated) */
      else
      {
        /* #10100 Release the allocated Tx traffic mirror element */
        EthIf_ReleaseMirrorTxTrafficInfo(mirrorTxInfoIdx);
      }
    }
  }
} /* EthIf_ProvideTxMirroringBuffer() */

/***********************************************************************************************************************
 *  EthIf_MirrorTxTraffic
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
 */
FUNC(void, ETHIF_CODE) EthIf_MirrorTxTraffic(
          EthIf_EthIfCtrlIterType             srcEthIfCtrlIdx,
          uint8                               srcBufIdx,
          Eth_FrameType                       srcFrameType,
          uint16                              srcFrameLen,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  destMacAddr)
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Tx traffic must be mirrored */
  if( EthIf_IsMirrorTxDestIdxUsedOfEthIfCtrl(srcEthIfCtrlIdx) )
  {
    EthIf_MirrorTxInfoIterType mirrorTxInfoIdx;
    EthIf_MirrorTxDestIdxIdxOfEthIfCtrlType mirrorDestsIdx = EthIf_GetMirrorTxDestIdxIdxOfEthIfCtrl(srcEthIfCtrlIdx);

    /* #100 Check if a Tx traffic mirroring element of the related buffer request conexts can be retrieved */
    if( EthIf_GetRelatedMirrorTxTrafficInfo(srcEthIfCtrlIdx, srcBufIdx, &mirrorTxInfoIdx) == E_OK )                     /* SBSW_ETHIF_REF_OF_STACK_VAR */
    {
      /* #1000 Check if a transmit is triggered */
      if( srcFrameLen != 0u )
      {
        EthIf_EthCtrlIdxOfMirrorDestType ethCtrlIdx = EthIf_GetEthCtrlIdxOfMirrorDest(mirrorDestsIdx);
        EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

        /* #10000 Copy frame to mirroring destination buffer */
        /* PRQA S 0314 3 */ /* MD_MSR_VStdLibCopy */
        VStdLib_MemCpy((P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR))EthIf_GetDestPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx),
                       (P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR))EthIf_GetSrcPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx),
                       srcFrameLen);

        /* #10010 Check if source MAC address of original frame shall be preserved and driver supports this */
        if( (EthIf_IsKeepSrcMacEnabledOfMirrorDest(mirrorDestsIdx) == TRUE) &&
            (EthIf_GetVTransmitOfEthDrvApi(ethDrvApiIdx) != NULL_PTR) )
        {
          P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR) srcMacAddr;

          srcMacAddr = &((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))EthIf_GetSrcPayloadPtrOfMirrorTxInfo(mirrorTxInfoIdx))[EthIf_GetSrcMacAddrOffset()];

          /* #100100 Trigger transmission with original source MAC address */
          (void)EthIf_GetVTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                            EthIf_GetDestEthTxBufferIdxOfMirrorTxInfo(mirrorTxInfoIdx),
                                                            srcFrameType,
                                                            FALSE,
                                                            srcFrameLen,
                                                            destMacAddr,
                                                            srcMacAddr);
        }
        /* #10020 Otherwise (source MAC address shall not be preserved) */
        else
        {
          /* #100200 Trigger transmission with the MAC address of the mirroring destination Ethernet controller */
          (void)EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                           EthIf_GetDestEthTxBufferIdxOfMirrorTxInfo(mirrorTxInfoIdx),
                                                           srcFrameType,
                                                           FALSE,
                                                           srcFrameLen,
                                                           destMacAddr);
        }
      }

      /* #1010 Release Tx traffic mirror info element */
      EthIf_ReleaseMirrorTxTrafficInfo(mirrorTxInfoIdx);
    }
  }
} /* EthIf_MirrorTxTraffic() */

/***********************************************************************************************************************
 *  EthIf_MirrorRxTraffic
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
 */
FUNC(void, ETHIF_CODE) EthIf_MirrorRxTraffic(
          EthIf_EthIfCtrlIterType                    srcEthIfCtrlIdx,
          Eth_FrameType                              srcFrameType,
          uint16                                     srcFrameLen,
  P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA)  srcDataPtr)
{
  /* ----- Local data declaration --------------------------------------- */

  /* ----- Local data definition ---------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if Rx traffic must be mirrored */
  if( EthIf_IsMirrorRxDestIdxUsedOfEthIfCtrl(srcEthIfCtrlIdx) )
  {

    P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  dstBufPtr;
          uint8                                     dstBufIdx;
          uint16                                    lenByte = srcFrameLen;
    EthIf_MirrorRxDestIdxIdxOfEthIfCtrlType         mirrorDestIdx = EthIf_GetMirrorRxDestIdxIdxOfEthIfCtrl(srcEthIfCtrlIdx);
    EthIf_EthCtrlIdxOfMirrorDestType                ethCtrlIdx = EthIf_GetEthCtrlIdxOfMirrorDest(mirrorDestIdx);
    EthIf_EthDrvApiIdxOfEthCtrlType                 ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    /* #100 Check if buffer allocation on mirroring destination is successful */
    if( EthIf_GetProvideTxBufferOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                          &dstBufIdx,
                                                          &dstBufPtr,
                                                          &lenByte) == BUFREQ_OK )                                      /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_REF_OF_STACK_VAR_PARAM_PTR_CSL03 */
    {
      P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR) destMacAddr;

      destMacAddr = &((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))srcDataPtr)[EthIf_GetDestMacAddrOffset()]; /* PRQA S 0310, 0311 */ /* MD_EthIf_310_Buffer */

      /* #1000 Copy frame to mirroring destination buffer */
      /* PRQA S 0314 3 */ /* MD_MSR_VStdLibCopy */
      VStdLib_MemCpy((P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR))dstBufPtr,                                                 /* SBSW_ETHIF_TX_BUF_PTR_PASS */
                     (P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR))srcDataPtr,
                     srcFrameLen);

      /* #1010 Check if source MAC address of original frame shall be preserved */
      if(EthIf_IsKeepSrcMacEnabledOfMirrorDest(mirrorDestIdx) == TRUE )
      {
        P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR) srcMacAddr;

        srcMacAddr = &((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))srcDataPtr)[EthIf_GetSrcMacAddrOffset()]; /* PRQA S 0310, 0311 */ /* MD_EthIf_310_Buffer */

        /* #10100 Trigger transmission with original source MAC address */
        /* PRQA S 0310, 0311 7 */ /* MD_EthIf_310_Buffer, MD_EthIf_311_Buffer */
        (void)EthIf_GetVTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                          dstBufIdx,
                                                          srcFrameType,
                                                          FALSE,
                                                          srcFrameLen,
                                                          destMacAddr,
                                                          srcMacAddr);
      }
      /* #1020 Otherwise */
      else
      {
        /* #10200 Trigger transmission with the MAC address of the mirroring destination Ethernet controller */
        /* PRQA S 0310, 0311 6 */ /* MD_EthIf_310_Buffer, MD_EthIf_311_Buffer */
        (void)EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                         dstBufIdx,
                                                         srcFrameType,
                                                         FALSE,
                                                         srcFrameLen,
                                                         destMacAddr);
      }
    }
  }
} /* EthIf_MirrorRxTraffic() */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Mirror_Int.c
 *********************************************************************************************************************/

