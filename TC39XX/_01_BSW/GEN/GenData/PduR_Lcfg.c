/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *
 *                 This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                 Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                 All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: PduR
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: PduR_Lcfg.c
 *   Generation Time: 2026-02-08 21:29:39
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

#define PDUR_LCFG_SOURCE

/**********************************************************************************************************************
 * MISRA / PCLINT JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PduR.h"
#include "PduR_Fm.h"
#include "PduR_IFQ.h"
#include "PduR_Sm.h"
#include "PduR_RmIf.h"
#include "PduR_RmTp.h"
#include "PduR_RmTp_TxInst.h"
#include "SchM_PduR.h"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
# include "PduR_Lcfg.h"



/* Include headers with callbacks */
#include "PduR_Com.h"
#include "PduR_UdpNm.h"
#include "PduR_SoAd.h"
#include "PduR_LdCom.h"
#include "PduR_Dcm.h"
#include "PduR_DoIP.h"


/**********************************************************************************************************************
 * LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/* Exclusive Area Wrapper functions */
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void);
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void);
  
/**********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/
/* \trace SPEC-663, SPEC-661 */

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  PduR_ExclusiveAreaRom
**********************************************************************************************************************/
/** 
  \var    PduR_ExclusiveAreaRom
  \brief  PduR Exclusive Area Locks
  \details
  Element    Description
  Lock       Lock function
  Unlock     Unlock function
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Lock                                        Unlock                                           Referable Keys */
  { /*     0 */ PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0, PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0 }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRLock_PduRExclusiveArea] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_GeneralPropertiesRom
**********************************************************************************************************************/
/** 
  \var    PduR_GeneralPropertiesRom
  \brief  General Properties Switches of the PduR.
  \details
  Element         Description
  hasIfRouting
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_GeneralPropertiesRomType, PDUR_CONST) PduR_GeneralPropertiesRom[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    hasIfRouting        Referable Keys */
  { /*     0 */         TRUE }   /* [/ActiveEcuC/PduR] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_MmRom
**********************************************************************************************************************/
/** 
  \var    PduR_MmRom
  \brief  Module manager: Contains all function pointers of the bordering modules.
  \details
  Element                         Description
  DestApplicationManagerRomIdx    the index of the 1:1 relation pointing to PduR_DestApplicationManagerRom
  MaskedBits                      contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_LoTpOfMmRom, PduR_RmGDestRomUsedOfMmRom, PduR_UpIfOfMmRom, PduR_UpTpOfMmRom
  RmGDestRomEndIdx                the end index of the 0:n relation pointing to PduR_RmGDestRom
  RmGDestRomStartIdx              the start index of the 0:n relation pointing to PduR_RmGDestRom
  UpTpCopyRxDataFctPtr            Transport protocol CopyRxData function pointers
  UpTpCopyTxDataFctPtr            Transport protocol CopyTxData function pointers
  UpIfRxIndicationFctPtr          Upper layer communication interface Rx indication function pointers.
  UpIfTxConfirmationFctPtr        Upper layer communication interface Tx confimation function pointers
  UpTpStartOfReceptionFctPtr      Transport protocol StartOfReception function pointers
  UpTpTpRxIndicationFctPtr        Transport protocol TpRxIndication function pointers
  UpTpTpTxConfirmationFctPtr      Transport protocol TpTxConfimation function pointers
  LoIfTransmitFctPtr              Lower layer If transmit function pointers
  LoTpTransmitFctPtr              Lower layer Tp transmit function pointers
  UpIfTriggerTransmitFctPtr       Upper layer trigger transmit function pointers
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[6] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DestApplicationManagerRomIdx  MaskedBits  RmGDestRomEndIdx  RmGDestRomStartIdx  UpTpCopyRxDataFctPtr  UpTpCopyTxDataFctPtr  UpIfRxIndicationFctPtr  UpIfTxConfirmationFctPtr  UpTpStartOfReceptionFctPtr  UpTpTpRxIndicationFctPtr  UpTpTpTxConfirmationFctPtr  LoIfTransmitFctPtr  LoTpTransmitFctPtr  UpIfTriggerTransmitFctPtr        Comment                        Referable Keys */
  { /*     0 */                           0u,      0x06u,               2u,                 0u, NULL_PTR            , NULL_PTR            , Com_RxIndication      , Com_TxConfirmation      , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , NULL_PTR          , Com_TriggerTransmit       },  /* [BswModule: Com]   */  /* [/ActiveEcuC/PduR/Com, /ActiveEcuC/PduR] */
  { /*     1 */                           0u,      0x05u,               4u,                 2u, Dcm_CopyRxData      , Dcm_CopyTxData      , NULL_PTR              , NULL_PTR                , Dcm_StartOfReception      , Dcm_TpRxIndication      , Dcm_TpTxConfirmation      , NULL_PTR          , NULL_PTR          , NULL_PTR                  },  /* [BswModule: Dcm]   */  /* [/ActiveEcuC/PduR/Dcm, /ActiveEcuC/PduR] */
  { /*     2 */                           0u,      0x0Cu,               5u,                 4u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , DoIP_TpTransmit   , NULL_PTR                  },  /* [BswModule: DoIP]  */  /* [/ActiveEcuC/PduR/DoIP, /ActiveEcuC/PduR] */
  { /*     3 */                           0u,      0x06u,               7u,                 5u, NULL_PTR            , NULL_PTR            , LdCom_RxIndication    , LdCom_TxConfirmation    , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , NULL_PTR          , NULL_PTR          , NULL_PTR                  },  /* [BswModule: LdCom] */  /* [/ActiveEcuC/PduR/LdCom, /ActiveEcuC/PduR] */
  { /*     4 */                           0u,      0x14u,              10u,                 7u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , SoAd_IfTransmit   , NULL_PTR          , NULL_PTR                  },  /* [BswModule: SoAd]  */  /* [/ActiveEcuC/PduR/SoAd, /ActiveEcuC/PduR] */
  { /*     5 */                           0u,      0x14u,              11u,                10u, NULL_PTR            , NULL_PTR            , NULL_PTR              , NULL_PTR                , NULL_PTR                  , NULL_PTR                , NULL_PTR                  , UdpNm_Transmit    , NULL_PTR          , NULL_PTR                  }   /* [BswModule: UdpNm] */  /* [/ActiveEcuC/PduR/UdpNm, /ActiveEcuC/PduR] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_PartitionIdentifiers
**********************************************************************************************************************/
/** 
  \var    PduR_PartitionIdentifiers
  \brief  the partition context in Config
  \details
  Element         Description
  PartitionSNV
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_PartitionIdentifiersType, PDUR_CONST) PduR_PartitionIdentifiers[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionSNV       */
  { /*     0 */ CommonSharedMemory }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRom
  \brief  PduR RoutiongPathManager destPdu Table
  \details
  Element                      Description
  PartitionIndexOfCsl      
  PduLengthHandlingStrategy    The strategy how larger than configured If Pdus are handled.
  RmDestRpgRomIdx              the index of the 0:1 relation pointing to PduR_RmDestRpgRom
  RmGDestRomIdx                the index of the 1:1 relation pointing to PduR_RmGDestRom
  RmSrcRomIdx                  the index of the 1:1 relation pointing to PduR_RmSrcRom
  RoutingType                  Type of the Routing (API Forwarding, Gateway).
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[11] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                            PduLengthHandlingStrategy                         RmDestRpgRomIdx                     RmGDestRomIdx  RmSrcRomIdx  RoutingType                                                 Comment                                                 Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            2u,          4u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_DoIPFuncReqRx]    */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPFuncReqRx/PduRSrcPdu_DoIPFuncReqRx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPFuncReqRx/PduRDestPdu_DoIPFuncReqRx] */
  { /*     1 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            3u,          5u, PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_DoIPPhyReqRx]     */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyReqRx/PduRSrcPdu_DoIPPhyReqRx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyReqRx/PduRDestPdu_DoIPPhyReqRx] */
  { /*     2 */                  0u  /* CommonSharedMemory */, PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            4u,          6u, PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_DoIPPhyResTx]     */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyResTx/PduRSrcPdu_DoIPPhyResTx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyResTx/PduRDestPdu_DoIPPhyResTx] */
  { /*     3 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            7u,          7u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_EcuStateTx]       */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_EcuStateTx/PduRSrcPdu_EcuStateTx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_EcuStateTx/PduRDestPdu_EcuStateTx] */
  { /*     4 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,                                 0u,            0u,          0u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_Eira_ETH_Rx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRSrcPdu_Eira_ETH_Rx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu_Eira_ETH_Rx] */
  { /*     5 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM,                                 1u,           10u,          8u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_Eira_ETH_Tx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRSrcPdu_Eira_ETH_Tx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu_Eira_ETH_Tx] */
  { /*     6 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            8u,          9u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_FalutInfoTx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_FalutInfoTx/PduRSrcPdu_FalutInfoTx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_FalutInfoTx/PduRDestPdu_FalutInfoTx] */
  { /*     7 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            9u,         10u, PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_SenStateTx]       */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_SenStateTx/PduRSrcPdu_SenStateTx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_SenStateTx/PduRDestPdu_SenStateTx] */
  { /*     8 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            1u,          1u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_VechicleInfoRx]   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleInfoRx/PduRSrcPdu_VechicleInfoRx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleInfoRx/PduRDestPdu_VechicleInfoRx] */
  { /*     9 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            5u,          2u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu_VechicleSpeedRx]  */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleSpeedRx/PduRSrcPdu_VechicleSpeedRx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleSpeedRx/PduRDestPdu_VechicleSpeedRx] */
  { /*    10 */                  0u  /* CommonSharedMemory */, PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM, PDUR_NO_RMDESTRPGROMIDXOFRMDESTROM,            6u,          3u, PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM }   /* [PduRDestPdu: PduRDestPdu_VechicleStatusRx] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleStatusRx/PduRSrcPdu_VechicleStatusRx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleStatusRx/PduRDestPdu_VechicleStatusRx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRpgRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRpgRom
  \brief  PduRDestPdu specific PduRRoutingPathGroup information.
  \details
  Element              Description
  InitialEnabledCnt    Amount of initially enabled PduRRoutingPathGroups
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRpgRomType, PDUR_CONST) PduR_RmDestRpgRom[2] = {  /* PRQA S 1514, 1533, 1504 */  /* MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ExternalMcData */
    /* Index    InitialEnabledCnt        Referable Keys */
  { /*     0 */                0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu_Eira_ETH_Rx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
  { /*     1 */                0u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu_Eira_ETH_Tx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRpgRomInd
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRpgRomInd
  \brief  the indexes of the 1:1 sorted relation pointing to PduR_RmDestRpgRom
*/ 
#define PDUR_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRpgRomIndType, PDUR_CONST) PduR_RmDestRpgRomInd[2] = {  /* PRQA S 1514, 1533, 1504 */  /* MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ExternalMcData */
  /* Index     RmDestRpgRomInd      Referable Keys */
  /*     0 */               1u,  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
  /*     1 */               0u   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
};
#define PDUR_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmGDestRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmGDestRom
  \brief  PduR RoutingPathManager global destPdu Table
  \details
  Element                Description
  MaxPduLength           Configured PduLength + metadata length.
  DestHnd                handle to be used as parameter for the StartOfReception, CopyRxData, Transmit or RxIndication function call.
  Direction              Direction of this Pdu: Rx or Tx
  MmRomIdx               the index of the 1:1 relation pointing to PduR_MmRom
  PartitionIndexOfCsl
  RmDestRomIdx           the index of the 1:1 relation pointing to PduR_RmDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[11] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaxPduLength  DestHnd                                                  Direction                      MmRomIdx  PartitionIndexOfCsl                            RmDestRomIdx        Comment                                                           Referable Keys */
  { /*     0 */           7u,                  ComConf_ComIPdu_ComIPduPnc_EIRA_ETH_Rx, PDUR_RX_DIRECTIONOFRMGDESTROM,       0u,                  0u  /* CommonSharedMemory */,           4u },  /* [Global PduRDestPdu: PncEiraEthRxPdu]                 */  /* [/ActiveEcuC/EcuC/EcucPduCollection/PncEiraEthRxPdu, /ActiveEcuC/PduR/Com] */
  { /*     1 */           8u,                  ComConf_ComIPdu_ComIPdu_VechicleInfoRx, PDUR_RX_DIRECTIONOFRMGDESTROM,       0u,                  0u  /* CommonSharedMemory */,           8u },  /* [Global PduRDestPdu: SomeIpVechicleInfoRxPdu_Com]     */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpVechicleInfoRxPdu_Com, /ActiveEcuC/PduR/Com] */
  { /*     2 */        4095u, DcmConf_DcmDslProtocolRx_DcmDslProtocolRx_DoIP_Func_Req, PDUR_RX_DIRECTIONOFRMGDESTROM,       1u,                  0u  /* CommonSharedMemory */,           0u },  /* [Global PduRDestPdu: DoIPFuncReqRxPdu_PduR2Dcm]       */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DoIPFuncReqRxPdu_PduR2Dcm, /ActiveEcuC/PduR/Dcm] */
  { /*     3 */        4095u,  DcmConf_DcmDslProtocolRx_DcmDslProtocolRx_DoIP_Phy_Req, PDUR_RX_DIRECTIONOFRMGDESTROM,       1u,                  0u  /* CommonSharedMemory */,           1u },  /* [Global PduRDestPdu: DoIPPhyReqRxPdu_PduR2Dcm]        */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DoIPPhyReqRxPdu_PduR2Dcm, /ActiveEcuC/PduR/Dcm] */
  { /*     4 */        4095u,            DoIPConf_DoIPPduRTxPdu_DoIPPduRTxPdu_Phy_Res, PDUR_TX_DIRECTIONOFRMGDESTROM,       2u,                  0u  /* CommonSharedMemory */,           2u },  /* [Global PduRDestPdu: DoIPPhyResTxPdu_PduR2DoIP]       */  /* [/ActiveEcuC/EcuC/EcucPduCollection/DoIPPhyResTxPdu_PduR2DoIP, /ActiveEcuC/PduR/DoIP] */
  { /*     5 */          14u,           LdComConf_LdComIPdu_LdComIPdu_VechicleSpeedRx, PDUR_RX_DIRECTIONOFRMGDESTROM,       3u,                  0u  /* CommonSharedMemory */,           9u },  /* [Global PduRDestPdu: SomeIpVechicleSpeedRxPdu_Ldcom]  */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpVechicleSpeedRxPdu_Ldcom, /ActiveEcuC/PduR/LdCom] */
  { /*     6 */           8u,          LdComConf_LdComIPdu_LdComIPdu_VechicleStatusRx, PDUR_RX_DIRECTIONOFRMGDESTROM,       3u,                  0u  /* CommonSharedMemory */,          10u },  /* [Global PduRDestPdu: SomeIpVechicleStatusRxPdu_Ldcom] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpVechicleStatusRxPdu_Ldcom, /ActiveEcuC/PduR/LdCom] */
  { /*     7 */           8u,    SoAdConf_SoAdPduRoute_SoAdPduRoute_SD_TCP_EcuStateTx, PDUR_TX_DIRECTIONOFRMGDESTROM,       4u,                  0u  /* CommonSharedMemory */,           3u },  /* [Global PduRDestPdu: SomeIpEcuStateTxPdu_SoAd]        */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpEcuStateTxPdu_SoAd, /ActiveEcuC/PduR/SoAd] */
  { /*     8 */           8u,  SoAdConf_SoAdPduRoute_SoAdPduRoute_SD_UDP_FaultInfo_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,       4u,                  0u  /* CommonSharedMemory */,           6u },  /* [Global PduRDestPdu: SomeIpFalutInfoTxPdu_SoAd]       */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpFalutInfoTxPdu_SoAd, /ActiveEcuC/PduR/SoAd] */
  { /*     9 */           8u,   SoAdConf_SoAdPduRoute_SoAdPduRoute_SD_UDP_SenState_Tx, PDUR_TX_DIRECTIONOFRMGDESTROM,       4u,                  0u  /* CommonSharedMemory */,           7u },  /* [Global PduRDestPdu: SomeIpSenStateTxPdu_SoAd]        */  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpSenStateTxPdu_SoAd, /ActiveEcuC/PduR/SoAd] */
  { /*    10 */           7u,         UdpNmConf_UdpNmUserDataTxPdu_UdpNmUserDataTxPdu, PDUR_TX_DIRECTIONOFRMGDESTROM,       5u,                  0u  /* CommonSharedMemory */,           5u }   /* [Global PduRDestPdu: PncEiraEthTxPdu]                 */  /* [/ActiveEcuC/EcuC/EcucPduCollection/PncEiraEthTxPdu, /ActiveEcuC/PduR/UdpNm] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmSrcRom
**********************************************************************************************************************/
/** 
  \var    PduR_RmSrcRom
  \brief  PduR RoutiongManager SrcPdu Table
  \details
  Element                Description
  MaskedBits             contains bitcoded the boolean data of PduR_TriggerTransmitSupportedOfRmSrcRom, PduR_TxConfirmationSupportedOfRmSrcRom
  MmRomIdx               the index of the 1:1 relation pointing to PduR_MmRom
  PartitionIndexOfCsl
  RmDestRomStartIdx      the start index of the 1:n relation pointing to PduR_RmDestRom
  SrcHnd                 handle to be used as parameter for the TxConfirmation or TriggerTransmit function call.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[11] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MaskedBits  MmRomIdx  PartitionIndexOfCsl                            RmDestRomStartIdx  SrcHnd                                                        Comment                                               Referable Keys */
  { /*     0 */      0x00u,       5u,                  0u  /* CommonSharedMemory */,                4u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_Eira_ETH_Rx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRSrcPdu_Eira_ETH_Rx] */
  { /*     1 */      0x00u,       4u,                  0u  /* CommonSharedMemory */,                8u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_VechicleInfoRx]   */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleInfoRx/PduRSrcPdu_VechicleInfoRx] */
  { /*     2 */      0x00u,       4u,                  0u  /* CommonSharedMemory */,                9u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_VechicleSpeedRx]  */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleSpeedRx/PduRSrcPdu_VechicleSpeedRx] */
  { /*     3 */      0x00u,       4u,                  0u  /* CommonSharedMemory */,               10u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_VechicleStatusRx] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleStatusRx/PduRSrcPdu_VechicleStatusRx] */
  { /*     4 */      0x00u,       2u,                  0u  /* CommonSharedMemory */,                0u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_DoIPFuncReqRx]    */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPFuncReqRx/PduRSrcPdu_DoIPFuncReqRx] */
  { /*     5 */      0x00u,       2u,                  0u  /* CommonSharedMemory */,                1u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_DoIPPhyReqRx]     */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyReqRx/PduRSrcPdu_DoIPPhyReqRx] */
  { /*     6 */      0x00u,       1u,                  0u  /* CommonSharedMemory */,                2u, DcmConf_DcmDslProtocolTx_DcmDslProtocolTx_DoIP_Phy_Res },  /* [PduRSrcPdu: PduRSrcPdu_DoIPPhyResTx]     */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyResTx/PduRSrcPdu_DoIPPhyResTx] */
  { /*     7 */      0x00u,       3u,                  0u  /* CommonSharedMemory */,                3u,                               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu_EcuStateTx]       */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_EcuStateTx/PduRSrcPdu_EcuStateTx] */
  { /*     8 */      0x02u,       0u,                  0u  /* CommonSharedMemory */,                5u,                 ComConf_ComIPdu_ComIPduPnc_EIRA_ETH_Tx },  /* [PduRSrcPdu: PduRSrcPdu_Eira_ETH_Tx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRSrcPdu_Eira_ETH_Tx] */
  { /*     9 */      0x01u,       0u,                  0u  /* CommonSharedMemory */,                6u,                    ComConf_ComIPdu_ComIPdu_FalutInfoTx },  /* [PduRSrcPdu: PduRSrcPdu_FalutInfoTx]      */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_FalutInfoTx/PduRSrcPdu_FalutInfoTx] */
  { /*    10 */      0x01u,       3u,                  0u  /* CommonSharedMemory */,                7u,               LdComConf_LdComIPdu_LdComIPdu_SenStateTx }   /* [PduRSrcPdu: PduRSrcPdu_SenStateTx]       */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_SenStateTx/PduRSrcPdu_SenStateTx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmTransmitFctPtr
**********************************************************************************************************************/
/** 
  \var    PduR_RmTransmitFctPtr
  \brief  Internal routing manager Transmit functions.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RmTransmitFctPtr                  Referable Keys */
  /*     0 */ PduR_RmIf_RoutePdu           ,  /* [PduR_RmIf_RoutePdu] */
  /*     1 */ PduR_RmTp_Transmit_MultiDest    /* [PduR_RmTp_Transmit_MultiDest] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RpgExtIdRom
**********************************************************************************************************************/
/** 
  \var    PduR_RpgExtIdRom
  \brief  PduRRoutingPathGroup specific ROM information.
  \details
  Element                Description
  PartitionIndexOfCsl
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RpgExtIdRomType, PDUR_CONST) PduR_RpgExtIdRom[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                                  Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
  { /*     1 */                  0u  /* CommonSharedMemory */ }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RpgRom
**********************************************************************************************************************/
/** 
  \var    PduR_RpgRom
  \brief  PduRRoutingPathGroup specific RAM information.
  \details
  Element       Description
  MaskedBits    contains bitcoded the boolean data of PduR_EnabledAtInitOfRpgRom, PduR_RmDestRpgRomIndUsedOfRpgRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RpgRomType, PDUR_CONST) PduR_RpgRom[2] = {  /* PRQA S 1514, 1533, 1504 */  /* MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ExternalMcData */
    /* Index    MaskedBits        Referable Keys */
  { /*     0 */      0x01u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
  { /*     1 */      0x01u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RxIf2Dest
**********************************************************************************************************************/
/** 
  \var    PduR_RxIf2Dest
  \brief  This table contains all routing information to perform the Rx handling of an interface routing. Used in the &lt;LLIf&gt;_RxIndication
  \details
  Element                Description
  PartitionIndexOfCsl
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RxIf2DestType, PDUR_CONST) PduR_RxIf2Dest[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                                  Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRSrcPdu_Eira_ETH_Rx] */
  { /*     1 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleInfoRx/PduRSrcPdu_VechicleInfoRx] */
  { /*     2 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleSpeedRx/PduRSrcPdu_VechicleSpeedRx] */
  { /*     3 */                  0u  /* CommonSharedMemory */ }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_VechicleStatusRx/PduRSrcPdu_VechicleStatusRx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RxTp2Dest
**********************************************************************************************************************/
/** 
  \var    PduR_RxTp2Dest
  \brief  This table contains all routing information to perform the Rx handling of a Tp Routing. Used in the PduR_&lt;LLTp&gt;_StartOfReception, PduR_&lt;LLTp&gt;_CopyRxData and PduR_&lt;LLTp&gt;_RxIndication.
  \details
  Element                Description
  PartitionIndexOfCsl
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RxTp2DestType, PDUR_CONST) PduR_RxTp2Dest[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                                  Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */ },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPFuncReqRx/PduRSrcPdu_DoIPFuncReqRx] */
  { /*     1 */                  0u  /* CommonSharedMemory */ }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyReqRx/PduRSrcPdu_DoIPPhyReqRx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Tx2Lo
**********************************************************************************************************************/
/** 
  \var    PduR_Tx2Lo
  \brief  Contains all information to route a Pdu from a upper layer to a lower layer module, or to cancel a transmission
  \details
  Element                Description
  PartitionIndexOfCsl
  RmTransmitFctPtrIdx    the index of the 1:1 relation pointing to PduR_RmTransmitFctPtr
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_Tx2LoType, PDUR_CONST) PduR_Tx2Lo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PartitionIndexOfCsl                            RmTransmitFctPtrIdx        Referable Keys */
  { /*     0 */                  0u  /* CommonSharedMemory */,                  1u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_DoIPPhyResTx/PduRSrcPdu_DoIPPhyResTx] */
  { /*     1 */                  0u  /* CommonSharedMemory */,                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_EcuStateTx/PduRSrcPdu_EcuStateTx] */
  { /*     2 */                  0u  /* CommonSharedMemory */,                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRSrcPdu_Eira_ETH_Tx] */
  { /*     3 */                  0u  /* CommonSharedMemory */,                  0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_FalutInfoTx/PduRSrcPdu_FalutInfoTx] */
  { /*     4 */                  0u  /* CommonSharedMemory */,                  0u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_SenStateTx/PduRSrcPdu_SenStateTx] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_TxIf2Up
**********************************************************************************************************************/
/** 
  \var    PduR_TxIf2Up
  \brief  This table contains all routing information to perform the Tx handling of an interface routing. Used in the &lt;LLIf&gt;_TriggerTransmit and &lt;LLIf&gt;_TxConfirmation
  \details
  Element                Description
  TxConfirmationUsed     True, if any of the source PduRDestPdus uses a TxConfirmation.
  PartitionIndexOfCsl
  RmGDestRomIdx          the index of the 1:1 relation pointing to PduR_RmGDestRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_TxIf2UpType, PDUR_CONST) PduR_TxIf2Up[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxConfirmationUsed  PartitionIndexOfCsl                            RmGDestRomIdx        Referable Keys */
  { /*     0 */              FALSE,                  0u  /* CommonSharedMemory */,           10u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/PncEiraEthTxPdu] */
  { /*     1 */              FALSE,                  0u  /* CommonSharedMemory */,            7u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpEcuStateTxPdu_SoAd] */
  { /*     2 */               TRUE,                  0u  /* CommonSharedMemory */,            8u },  /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpFalutInfoTxPdu_SoAd] */
  { /*     3 */               TRUE,                  0u  /* CommonSharedMemory */,            9u }   /* [/ActiveEcuC/EcuC/EcucPduCollection/SomeIpSenStateTxPdu_SoAd] */
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_Initialized
**********************************************************************************************************************/
/** 
  \var    PduR_Initialized
  \brief  Initialization state of PduR. TRUE, if PduR_Init() has been called, else FALSE
*/ 
#define PDUR_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(PduR_InitializedType, PDUR_VAR_ZERO_INIT) PduR_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define PDUR_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RmDestRpgRam
**********************************************************************************************************************/
/** 
  \var    PduR_RmDestRpgRam
  \brief  PduRDestPdu specific PduRRoutingPathGroup information.
  \details
  Element       Description
  EnabledCnt
*/ 
#define PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(PduR_RmDestRpgRamType, PDUR_VAR_NOINIT) PduR_RmDestRpgRam[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu_Eira_ETH_Rx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
  /*     1 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu_Eira_ETH_Tx, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */

#define PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_RpgRam
**********************************************************************************************************************/
/** 
  \var    PduR_RpgRam
  \brief  PduRRoutingPathGroup specific RAM information.
  \details
  Element    Description
  Enabled    TRUE, if the PduRRoutingPathGroup is active
*/ 
#define PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(PduR_RpgRamUType, PDUR_VAR_NOINIT) PduR_RpgRam;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
  /*     1 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */

#define PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_PCPartitionConfig
**********************************************************************************************************************/
/** 
  \var    PduR_PCPartitionConfig
  \details
  Element            Description
  Initialized        the pointer to PduR_Initialized
  RmDestRpgRam       the pointer to PduR_RmDestRpgRam
  RmDestRpgRom       the pointer to PduR_RmDestRpgRom
  RmDestRpgRomInd    the pointer to PduR_RmDestRpgRomInd
  RpgRam             the pointer to PduR_RpgRam
  RpgRom             the pointer to PduR_RpgRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_PCPartitionConfigType, PDUR_CONST) PduR_PCPartitionConfig[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  { /* Index: 0 Keys: [] */
      (&(PduR_Initialized))  /**< the pointer to PduR_Initialized */
    , PduR_RmDestRpgRam      /**< the pointer to PduR_RmDestRpgRam */
    , PduR_RmDestRpgRom      /**< the pointer to PduR_RmDestRpgRom */
    , PduR_RmDestRpgRomInd   /**< the pointer to PduR_RmDestRpgRomInd */
    , PduR_RpgRam.raw        /**< the pointer to PduR_RpgRam */
    , PduR_RpgRom            /**< the pointer to PduR_RpgRom */
  }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if(PDUR_USE_INIT_POINTER == STD_ON)
P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
#endif

#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#define PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

VAR(boolean, PDUR_VAR_NOINIT) PduR_PreInitialized;

#define PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */
  
/**********************************************************************************************************************
 * LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
#define PDUR_START_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "PduR_MemMap.h"

/* Exclusive Area Wrapper functions */

/**********************************************************************************************************************
 * PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  enter the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/**********************************************************************************************************************
 * PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0
 *********************************************************************************************************************/
/*!
 * \internal
 * -  exit the EA  
 * \endinternal
 *********************************************************************************************************************/
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
}


/* Upper Layer Interface APIs */

/**********************************************************************************************************************
 * PduR_ComTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_LdComTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_LdComTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_DcmTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call upper layer Transmit function. 
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
  Std_ReturnType retVal = E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_TX2LO == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_UpTransmit(id, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_TX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/* Communication Interface APIs */

/**********************************************************************************************************************
 * PduR_UdpNmRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * -  call internal general IfRxIndication function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_UdpNmRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXIF2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoIfRxIndication(RxPduId, info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_IFRXIND, PDUR_E_PDU_ID_INVALID);
#endif
  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_SoAdIfRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * -  call internal general IfRxIndication function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_SoAdIfRxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXIF2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoIfRxIndication(RxPduId, info);  /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_IFRXIND, PDUR_E_PDU_ID_INVALID);
#endif
  PDUR_DUMMY_STATEMENT(RxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_SoAdIfTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general communication interface TxConfirmation function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_SoAdIfTxConfirmation(PduIdType TxPduId) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXCONFIRMATIONUSEDOFTXIF2UP == STD_ON)
  PduR_LoIfTxConfirmation(TxPduId);
#endif
  PDUR_DUMMY_STATEMENT(TxPduId);        /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}




/**********************************************************************************************************************
 * PduR_UdpNmTriggerTransmit
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general TriggerTransmit function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_UdpNmTriggerTransmit(PduIdType TxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  return PduR_LoIfTriggerTransmit(TxPduId, info); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
}


/* Transport Protocol APIs */

/**********************************************************************************************************************
 * PduR_DoIPTpStartOfReception
 *********************************************************************************************************************/
 /*!
 * \internal
 * - call transport protocoll StartOfReception function.  
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DoIPTpStartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */

#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpStartOfReception(id, info, TpSduLength, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_SOR, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);   		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(TpSduLength);    /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */

  return retVal;
}


/**********************************************************************************************************************
 * PduR_DoIPTpCopyRxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyRxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DoIPTpCopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyRxData(id, info, bufferSizePtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYRX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     		/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  			/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(bufferSizePtr);  /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_DoIPTpCopyTxData
 *********************************************************************************************************************/
/*!
 * \internal
 * - call internal general CopyTxData.
 * \endinternal
 *********************************************************************************************************************/
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_DoIPTpCopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr) /* COV_PDUR_WRAPPER_FUNC */
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;        /* PRQA S 2981 */ /* MD_MSR_RetVal */
  
#if(PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  retVal = PduR_LoTpCopyTxData(id, info, retry, availableDataPtr); /* SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY */
#else
  PduR_Det_ReportError(PDUR_FCT_CPYTX, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(info);  					/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(retry);  				/* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(availableDataPtr);       /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  
  return retVal;
}


/**********************************************************************************************************************
 * PduR_DoIPTpRxIndication
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp RxIndication function.
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_DoIPTpRxIndication(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_RXTP2DEST == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpRxIndication(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPRXIND, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/**********************************************************************************************************************
 * PduR_DoIPTpTxConfirmation
 *********************************************************************************************************************/
/*!
 * \internal
 * - call Tp TxConfirmation function 
 * \endinternal
 *********************************************************************************************************************/
FUNC(void, PDUR_CODE) PduR_DoIPTpTxConfirmation(PduIdType id, Std_ReturnType result) /* COV_PDUR_WRAPPER_FUNC */
{
#if (PDUR_TXTP2SRC == STD_ON) /* COV_PDUR_RX_OR_TX_ONLY_CONFIG */
  PduR_LoTpTxConfirmation(id, result);
#else
  PduR_Det_ReportError(PDUR_FCT_TPTXCFM, PDUR_E_PDU_ID_INVALID);
#endif

  PDUR_DUMMY_STATEMENT(id);     /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
  PDUR_DUMMY_STATEMENT(result); /* PRQA S 1338, 2983, 3112 */ /* MD_MSR_DummyStmt */ /* lint -e{438} */
}


/* CancelReceive global without UseTag API */

/* ChangeParameter global without UseTag  API */

/* Communication Interface / Transport Protocol APIs */

/* Communication Interface / Transport Protocol APIs */

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/


#define PDUR_STOP_SEC_CODE
/* PRQA S 5087 1 */ /* MD_MSR_MemMap */
#include "PduR_MemMap.h"

/* SBSW_JUSTIFICATION_BEGIN

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_AND_PTR
    \DESCRIPTION    The API is called with an Id and a pointer.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \N The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       The pointer is provided by the lower layer and is assumed to be valid. It is passed as is to the corresponding function. 

  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ID_ONLY
    \DESCRIPTION    The API is called with an Id.
                    The API call is forwarded using a function pointer which is read using ComStackLib macros.
                    
    \COUNTERMEASURE \R The function pointer is read using the passed Id (and ComStackLib macros). 
                       The Id is a SNV provided by the lower layer. 
                       It is checked at runtime if it is in the valid range.
                       
  \ID SBSW_PDUR_EXTERNAL_API_CALL_FORWARDING_ONLY
    \DESCRIPTION    The API call is forwarded to an internal function.
    \COUNTERMEASURE \N The parameter are checked in the called function.

 SBSW_JUSTIFICATION_END */
 
 /* COV_JUSTIFICATION_BEGIN
 
  \ID COV_PDUR_WRAPPER_FUNC
    \ACCEPT X
    \REASON Each neighbouring module call the same internal function. The call is covered by an other module. 
    
  \ID COV_PDUR_RX_OR_TX_ONLY_CONFIG
    \ACCEPT TX
    \REASON The API is mandatory if this Bsw module exists. In case of Rx or Tx only configs the API call is not forwarded to the internal function. 
 
 COV_JUSTIFICATION_END */
 

/**********************************************************************************************************************
 * END OF FILE: PduR_Lcfg.c
 *********************************************************************************************************************/

