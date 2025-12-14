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
/*!        \file  EthIf_Gw_Int.c
 *        \brief  EthIf Gw internal source file
 *
 *      \details  Contains the definition of data and implementation of functions of the sub-module Gw of EthIf
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

#define ETHIF_GW_INT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
#include "EthIf_Gw_Int.h"

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
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_IsMacOnGwBlackList
 **********************************************************************************************************************/
/*! \brief          Checks if the MAC address is on the gateway black list
 *  \details        This function checks if the passed MAC address is on the gateway black list.
 *  \param[in]      srcMacAddrPtr      EthIf controller index
 *  \return         TRUE - MAC address is on the gateway black list
 *  \return         FALSE - MAC address isn't on the gateway black list
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 **********************************************************************************************************************/
ETHIF_GW_INT_LOCAL_INLINE FUNC(boolean, ETHIF_GW_INLINE_CODE) EthIf_IsMacOnGwBlackList(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  srcMacAddrPtr);
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_IsMacOnGwBlackList
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHIF_GW_INT_LOCAL_INLINE FUNC(boolean, ETHIF_GW_INLINE_CODE) EthIf_IsMacOnGwBlackList(
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  srcMacAddrPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  boolean      result;
  EthIf_GatewaySrcMacBlackListIterType  gatewaySrcMacBlackListIdx;

  /* ----- Implementation ----------------------------------------------- */
  result = FALSE;

  /* #10 For each entry of the black list */
  for( gatewaySrcMacBlackListIdx = 0;
       gatewaySrcMacBlackListIdx < EthIf_GetSizeOfGatewaySrcMacBlackList();
       gatewaySrcMacBlackListIdx++ )
  {
      uint8_least macAddrPartIdx;
      boolean     isEntryFound;

      isEntryFound = TRUE;

      /* #100 Check if MAC address is on black list */
      for( macAddrPartIdx = 0; macAddrPartIdx < ETH_PHYS_ADDR_LEN_BYTE; macAddrPartIdx++ )
      {
          if( srcMacAddrPtr[macAddrPartIdx] != EthIf_GetMacAddrOfGatewaySrcMacBlackList(gatewaySrcMacBlackListIdx)[macAddrPartIdx] )
          {
              isEntryFound = FALSE;
              break;
          }
      }

      if( isEntryFound == TRUE )
      {
        /* #1000 Indicate that MAC address is on black list */
        result = TRUE;
        break;
      }
  }

  return result;
} /* EthIf_IsMacOnGwBlackList() */
#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthIf_Gw_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHIF_CODE) EthIf_Gw_Init( void )
{

} /* EthIf_Gw_Init() */

#if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_GATEWAY )                                                   /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_GatewayTraffic
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
FUNC(boolean, ETHIF_CODE) EthIf_GatewayTraffic(
          EthIf_EthIfCtrlIterType                    srcEthIfCtrlIdx,
          Eth_FrameType                              srcFrameType,
          uint16                                     srcFrameLen,
  P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA)  srcDataPtr)
{
  /* ----- Local data declaration --------------------------------------- */
  boolean isTrafficGateway;
  uint8   additionalHdrLen;

  /* ----- Local data definition ---------------------------------------- */
  isTrafficGateway = FALSE;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if EthIf controller is involved in a traffic gateway route */
  if( EthIf_IsGatewayDestEthIfCtrlIdxUsedOfEthIfCtrl(srcEthIfCtrlIdx) )
  {
      additionalHdrLen = 0;

    /* #100 Take VLAN tag into account for buffer length required if needed */
    if( EthIf_GetTypeOfEthIfCtrl(srcEthIfCtrlIdx) != ETHIF_ETHIFCTRL_TYPE_PHYSICAL_TYPEOFETHIFCTRL )
    {
        additionalHdrLen += ETHIF_VLAN_TAG_LEN_BYTE;
    }

    /* #110 Check if MAC address is on the gateway blacklist */
    /* PRQA S 0310, 0311 1 */ /* MD_EthIf_310_Buffer, MD_EthIf_311_Buffer */
    if( EthIf_IsMacOnGwBlackList(&((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))srcDataPtr)[EthIf_GetSrcMacAddrOffset()])   /* SBSW_ETHIF_NON_SAFE_REF_OF_ARRAY_ELEM */
         == FALSE )
    {
      P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  destBufPtr;
            uint8                                     destBufIdx;
            uint16                                    destLenOrg;
            uint16                                    destLenBuf;
      EthIf_GatewayDestEthIfCtrlIdxIdxOfEthIfCtrlType gatewayEthIfCtrlIdx;

      gatewayEthIfCtrlIdx = EthIf_GetGatewayDestEthIfCtrlIdxIdxOfEthIfCtrl(srcEthIfCtrlIdx);
      isTrafficGateway  = TRUE;
      destLenOrg        = srcFrameLen;
      /* Adapt frame length dependent on outcome of VLAN tag check */
      destLenOrg       -= additionalHdrLen;
      destLenBuf        = destLenOrg;

      /* #1000 Check if buffer allocation on gateway route destination is successful */
      if( EthIf_ProvideTxBuffer((uint8)EthIf_GetSnvOfEthIfCtrl(gatewayEthIfCtrlIdx),
                                srcFrameType,
                                0u,
                                &destBufIdx,
                                &destBufPtr,
                                &destLenBuf) == BUFREQ_OK )                                                             /* SBSW_ETHIF_REF_OF_STACK_VAR */
      {
        /* #10000 Copy frame to be routed */
        /* PRQA S 0314 3 */ /* MD_MSR_VStdLibCopy */
        VStdLib_MemCpy((P2VAR(void, AUTOMATIC, VSTDLIB_VAR_FAR))destBufPtr,                                              /* SBSW_ETHIF_TX_BUF_PTR_PASS */
                       (P2CONST(void, AUTOMATIC, VSTDLIB_VAR_FAR))&((P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA))srcDataPtr)[additionalHdrLen],
                       destLenOrg);

        /* #10010 Trigger transmission */
        /* PRQA S 0310, 0311 7 */ /* MD_EthIf_310_Buffer, MD_EthIf_311_Buffer */
        (void)EthIf_VTransmit((uint8)EthIf_GetSnvOfEthIfCtrl(gatewayEthIfCtrlIdx),
                              destBufIdx,
                              srcFrameType,
                              FALSE,
                              destLenOrg,
                              &((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))srcDataPtr)[EthIf_GetDestMacAddrOffset()],
                              &((P2VAR(uint8, AUTOMATIC, ETHIF_APPL_VAR))srcDataPtr)[EthIf_GetSrcMacAddrOffset()]);     /* SBSW_ETHIF_NON_SAFE_REF_OF_ARRAY_ELEM */
      }
# if ( ETHIF_DEV_ERROR_DETECT == STD_ON )                                                                               /* COV_ETHIF_QM_FEAT_INNER */
      else
      {
        /* No buffer provided -> traffic can't be routed */
        (void)Det_ReportError(ETHIF_MODULE_ID,
                              ETHIF_INSTANCE_ID_DET,
                              ETHIF_SID_GATEWAY_GATEWAY_TRAFFIC,
                              ETHIF_TRAFFIC_GATEWAY_E_NO_BUFFER);
      }
# endif /* ETHIF_DEV_ERROR_DETECT */
    }
  }

  return isTrafficGateway;
} /* EthIf_GatewayTraffic() */

#endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

#define ETHIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Gw_Int.c
 *********************************************************************************************************************/

