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
/*!        \file  EthIf_Mirror_Int.h
 *        \brief  EthIf Mirror internal header file
 *
 *      \details  Provides access to types/functions/data of the sub-module Mirror of EthIf only to be used internally,
 *                where functions are intended to be linked by linker.
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

#if !defined (ETHIF_MIRROR_INT_H)
# define ETHIF_MIRROR_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_Mirror_Types_Int.h"

# include "EthIf.h"      /* access to DET error IDs */
# include "EthIf_Int.h"  /* access to components/utils shared with all EthIf modules */

/*********************************************************************************************************
 * Predefined file includes based on usage of other components/sub-modules within this sub-module
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
/* Dependency to Eth resolved through EthIf_Lcfg.h -> no include needed */

/*********************************************************************************************************
 * Predefined file includes based on usage of this sub-module by other components/sub-modules
 * defined in \trace DSGN-EthIfDiag1937
 *********************************************************************************************************/
# include "EthIf_Rx_Types_Int.h"
# include "EthIf_Tx_Types_Int.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

# if !defined (ETHIF_MIRROR_INT_LOCAL)                                                                                  /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_MIRROR_INT_LOCAL static
# endif

# if !defined (ETHIF_MIRROR_INT_LOCAL_INLINE)                                                                           /* COV_ETHIF_LOCAL_INLINE */
#  define ETHIF_MIRROR_INT_LOCAL_INLINE LOCAL_INLINE
# endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE != ETHIF_NO_EXTENDED_TRAFFIC_HANDLING )                                     /* COV_ETHIF_QM_FEAT_CHECK_ON */

#  define EthIf_GetDestMacAddrOffset() (-(sint8)ETHIF_HDR_LEN_BYTE)
#  define EthIf_GetSrcMacAddrOffset()  (-(sint8)(ETHIF_HDR_LEN_BYTE - ETH_PHYS_ADDR_LEN_BYTE) )

# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

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

# if ( ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE == ETHIF_TRAFFIC_MIRRORING )                                                /* COV_ETHIF_QM_FEAT_CHECK_ON */
/***********************************************************************************************************************
 *  EthIf_ProvideTxMirroringBuffer
 **********************************************************************************************************************/
/*! \brief          Allocates a transmission buffer at the destination Ethernet controller if the EthIf controller is
 *                  involved in transmission traffic mirroring
 *  \details        Function checks if the EthIf controller is involved in transmission traffic mirroring and, if this
 *                  is the case, allocates a transmission buffer on the mirroring destination Ethernet controller. The
 *                  information is then stored in an data object which can be used during transmission trigger for the
 *                  frame to be mirrored.
 *  \param[in]      srcEthIfCtrlIdx  EthIf Controller Index of mirroring source
 *                                   [range: srcEthIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      srcDataPtr       Pointer to the Ethernet payload data of mirroring source
 *  \param[in]      srcDataBufIdx    Buffer index acquired by mirroring source
 *  \param[in]      srcFrameLen      Frame length of mirroring source
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_ProvideTxMirroringBuffer(
        EthIf_EthIfCtrlIterType                   srcEthIfCtrlIdx,
  P2VAR(Eth_DataType, AUTOMATIC, ETHIF_APPL_VAR)  srcDataPtr,
        uint8                                     srcDataBufIdx,
        uint16                                    srcFrameLen);

/***********************************************************************************************************************
 *  EthIf_MirrorTxTraffic
 **********************************************************************************************************************/
/*! \brief          Mirrors transmission traffic to the destination Ethernet controller if the EthIf controller is
 *                  involved in transmission traffic mirroring
 *  \details        Function checks if the EthIf controller is involved in transmission traffic mirroring and, if this
 *                  is the case, uses the data object setup by EthIf_ProvideTxMirroringBuffer() to mirror the
 *                  frame on the destination Ethernet controller.
 *  \param[in]      srcEthIfCtrlIdx  EthIf Controller Index of mirroring source
 *                                   [range: srcEthIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      srcBufIdx        Buffer index acquired by mirroring source
 *  \param[in]      srcFrameType     Frame type of mirroring source
 *  \param[in]      srcFrameLen      Frame length of mirroring source
 *  \param[in]      destMacAddr      Destination MAC of mirroring source
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_MirrorTxTraffic(
          EthIf_EthIfCtrlIterType             srcEthIfCtrlIdx,
          uint8                               srcBufIdx,
          Eth_FrameType                       srcFrameType,
          uint16                              srcFrameLen,
  P2CONST(uint8, AUTOMATIC, ETHIF_APPL_DATA)  destMacAddr);

/***********************************************************************************************************************
 *  EthIf_MirrorRxTraffic
 **********************************************************************************************************************/
/*! \brief          Mirrors reception traffic to the destination Ethernet controller if the EthIf controller is
 *                  involved in transmission traffic mirroring
 *  \details        Function checks if the EthIf controller is involved in reception traffic mirroring and, if this
 *                  is the case, allocates buffer and transmits the frame to be mirrored on the destination Ethernet
 *                  controller.
 *  \param[in]      srcEthIfCtrlIdx  EthIf Controller Index of mirroring source
 *                                   [range: srcEthIfCtrlIdx < EthIf_GetSizeOfEthIfCtrl()]
 *  \param[in]      srcFrameType     Frame type of mirroring source
 *  \param[in]      srcFrameLen      Frame length of mirroring source
 *  \param[in]      srcDataPtr       Pointer to the Ethernet payload data of mirroring source
 *  \pre            -
 *  \context        ANY
 *  \reentrant      FALSE
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_MirrorRxTraffic(
          EthIf_EthIfCtrlIterType                    srcEthIfCtrlIdx,
          Eth_FrameType                              srcFrameType,
          uint16                                     srcFrameLen,
  P2CONST(Eth_DataType, AUTOMATIC, ETHIF_APPL_DATA)  srcDataPtr);
# endif /* ETHIF_EXTENDED_TRAFFIC_HANDLING_TYPE */

/**********************************************************************************************************************
 *  EthIf_Mirror_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the EthIf Mirror sub-module
 *  \details        -
 *  \pre            Configuration pointer must have been initialized
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_Mirror_Init( void );

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_MIRROR_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_Mirror_Int.h
 *********************************************************************************************************************/

