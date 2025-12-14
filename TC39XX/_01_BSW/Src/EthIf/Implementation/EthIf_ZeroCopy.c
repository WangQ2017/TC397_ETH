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
/*!        \file  EthIf_ZeroCopy.c
 *        \brief  EthIf ZeroCopy public API source file
 *
 *      \details  Implementation of the public API of the sub-module ZeroCopy of EthIf.
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

#define ETHIF_ZEROCOPY_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_ZeroCopy.h"
#include "EthIf_ZeroCopy_Cbk.h"
#include "EthIf_ZeroCopy_Int.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

/* Check the version of Msn header file */
#if (  (ETHIF_SW_MAJOR_VERSION != (15u)) \
    || (ETHIF_SW_MINOR_VERSION != (0u)) \
    || (ETHIF_SW_PATCH_VERSION != (0u)) )
# error "Vendor specific version numbers of EthIf_ZeroCopy.c and EthIf.h are inconsistent"
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

#if !defined (ETHIF_ZEROCOPY_LOCAL)                                                                                     /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ZEROCOPY_LOCAL static
#endif

#if !defined (ETHIF_ZEROCOPY_LOCAL_INLINE)                                                                              /* COV_ETHIF_LOCAL_INLINE */
# define ETHIF_ZEROCOPY_LOCAL_INLINE LOCAL_INLINE
#endif

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
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_ENABLE_ZERO_COPY_EXTENSIONS == STD_ON )                                                                     /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ProvideExtTxBuffer
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
FUNC(BufReq_ReturnType, ETHIF_CODE) EthIf_ProvideExtTxBuffer(
        uint8                                                                       CtrlIdx,
        Eth_FrameType                                                               FrameType,
        uint8                                                                       Priority,
  P2VAR(uint8,                                          AUTOMATIC, ETHIF_APPL_VAR)  BufIdxPtr,
  P2VAR(P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR), AUTOMATIC, ETHIF_APPL_VAR)  BufPtr,
  P2VAR(uint16,                                         AUTOMATIC, ETHIF_APPL_VAR)  LenBytePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  BufReq_ReturnType  retVal  = BUFREQ_E_NOT_OK;
  uint8              errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
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
  else if( BufIdxPtr == NULL_PTR)
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( BufPtr == NULL_PTR)
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else if( LenBytePtr == NULL_PTR)
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #30 Check if the EthIf controller is active */
    if( EthIf_GetEthIfCtrlMode(CtrlIdx) == ETH_MODE_ACTIVE )
    {
      EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
      EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

      /* #300 Check if driver provides the API */
      if( EthIf_GetProvideExtTxBufferOfEthDrvApi(ethDrvApiIdx) != NULL_PTR)
      {
        /* #3000 Redirect call to the driver */
        retVal = EthIf_GetProvideExtTxBufferOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                      BufIdxPtr,
                                                                      BufPtr,
                                                                      LenBytePtr);                                      /* SBSW_ETHIF_DRVAPI_FCT_PTR_OPT_WITH_PUB_PARAM_PTR_CSL03 */

        /* #3010 Check if buffer was successfully provided by the driver and buffer index is in expected range */
        if( retVal == BUFREQ_OK )
        {
          if( (*BufIdxPtr) <= EthIf_GetMaxTxBufIdxForEthIfCtrl(CtrlIdx) )
          { /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            /* #30100 Trigger buffer provision finilazation if buffer index is in expected range */
            /* PRQA S 0310 7 */ /* MD_EthIf_310_Buffer */
            EthIf_FinalizeTxBufferProvision(CtrlIdx,
                                            ethCtrlIdx,
                                            FrameType,
                                            Priority,
                                            (*BufIdxPtr),
                                            LenBytePtr,
                                            (P2VAR(EthIf_FrameBufferPtrType, AUTOMATIC, ETHIF_APPL_VAR))BufPtr);        /* SBSW_ETHIF_INT_FCT_PUB_PARAM_PTR_PASS */
          }
          else
          { /* PRQA S 0715 */ /* MD_MSR_1.1_715 */
            /* #30110 Otherwise trigger release of buffer cause driver thinks everything was OK and locked its resources. */
            (void)EthIf_GetTransmitOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                             (*BufIdxPtr),
                                                             FrameType,
                                                             FALSE,
                                                             ETHIF_TX_BUFFER_RELEASE_LEN,
                                                             EthIf_BroadcastMac);                                       /* SBSW_ETHIF_DRVAPI_FCT_PTR_MAN_WITH_PUB_PARAM_PTR_CSL03 */
            retVal = BUFREQ_E_NOT_OK;
          }
        }
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
      else
      {
        errorId = ETHIF_E_INV_DRIVER_API_CALL;
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_PROVIDE_EXT_TX_BUFFER, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;

} /* EthIf_ProvideExtTxBuffer() */ /* PRQA S 6030, 6060, 6080 */ /* MD_MSR_STCYC, MD_MSR_STPAR, MD_MSR_STMIF */

/***********************************************************************************************************************
 *  EthIf_ReleaseRxBuffer
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
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ReleaseRxBuffer(
        uint8                                     CtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  BufPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType  retVal  = E_NOT_OK;
  uint8           errorId = ETHIF_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if (ETHIF_DEV_ERROR_DETECT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #10 Check module states */
  if( EthIf_ModuleInitialized == ETHIF_STATE_UNINIT )
  {
    errorId = ETHIF_E_NOT_INITIALIZED;
  }
  /* #20 Check input parameters for plausibility */
  else if( CtrlIdx >= EthIf_GetSizeOfEthIfCtrl() )
  {
    errorId = ETHIF_E_INV_CTRL_IDX;
  }
  else if( BufPtr == NULL_PTR)
  {
    errorId = ETHIF_E_INV_PARAM_POINTER;
  }
  else
# endif /* ETHIF_DEV_ERROR_DETECT */
  {
    /* ----- Implementation ----------------------------------------------- */
    EthIf_EthCtrlIdxOfEthIfCtrlType ethCtrlIdx = EthIf_GetEthCtrlIdxOfEthIfCtrl(CtrlIdx);
    EthIf_EthDrvApiIdxOfEthCtrlType ethDrvApiIdx = EthIf_GetEthDrvApiIdxOfEthCtrl(ethCtrlIdx);

    /* #300 Check if driver provides the API */
    if( EthIf_GetReleaseRxBufferOfEthDrvApi(ethDrvApiIdx) != NULL_PTR )
    {
      P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR) tagAwareBufPtr;

      tagAwareBufPtr = (P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))BufPtr; /* PRQA S 0310 */ /* MD_EthIf_310_Buffer */

      /* #3000 Check the EthIf controller type (non-tagged or tagged) and adapt the buffer pointer
       *       to the location the driver expects */
      if( EthIf_GetTypeOfEthIfCtrl(CtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
      {
        tagAwareBufPtr = &tagAwareBufPtr[-((sint8)ETHIF_VLAN_TAG_LEN_BYTE)]; /* PRQA S 3382 */ /* MD_EthIf_3382 */
      }

      /* #3010 Redirect call to the driver */
      /* PRQA S 0310, 3305 2 */ /* MD_EthIf_310_Buffer, MD_EthIf_3305_Buffer */
      retVal = EthIf_GetReleaseRxBufferOfEthDrvApi(ethDrvApiIdx)((uint8)EthIf_GetSnvOfEthCtrl(ethCtrlIdx),
                                                                 (P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR))tagAwareBufPtr);
    }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
    else
    {
      errorId = ETHIF_E_INV_DRIVER_API_CALL;
    }
# endif /* ETHIF_DEV_ERROR_DETECT */
  }

  /* ----- Development Error Report --------------------------------------- */
# if (ETHIF_DEV_ERROR_REPORT == STD_ON)                                                                                 /* COV_ETHIF_QM_FEAT_INNER */
  /* #40 Report default errors if any occurred */
  if (errorId != ETHIF_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID_DET, ETHIF_SID_RELEASE_RX_BUFFER, errorId);
  }
# else
  ETHIF_DUMMY_STATEMENT(errorId); /* PRQA S 1338, 2983, 3122 */ /* MD_MSR_DummyStmt */ /*lint !e438 */
# endif

  return retVal;
} /* EthIf_ReleaseRxBuffer() */ /* PRQA S 6080 */ /* MD_MSR_STMIF */
#endif /* ETHIF_ENABLE_ZERO_COPY_EXTENSIONS */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_ZeroCopy.c
 *********************************************************************************************************************/

