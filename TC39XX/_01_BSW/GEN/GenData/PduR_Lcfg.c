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
 *   Generation Time: 2025-12-20 09:29:01
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
  MaskedBits                      contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_RmGDestRomUsedOfMmRom, PduR_UpIfOfMmRom
  UpIfRxIndicationFctPtr          Upper layer communication interface Rx indication function pointers.
  LoIfTransmitFctPtr              Lower layer If transmit function pointers
  UpIfTriggerTransmitFctPtr       Upper layer trigger transmit function pointers
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DestApplicationManagerRomIdx  MaskedBits  UpIfRxIndicationFctPtr  LoIfTransmitFctPtr  UpIfTriggerTransmitFctPtr        Comment                        Referable Keys */
  { /*     0 */                           0u,      0x03u, Com_RxIndication      , NULL_PTR          , Com_TriggerTransmit       },  /* [BswModule: Com]   */  /* [/ActiveEcuC/PduR/Com, /ActiveEcuC/PduR] */
  { /*     1 */                           0u,      0x06u, NULL_PTR              , UdpNm_Transmit    , NULL_PTR                  }   /* [BswModule: UdpNm] */  /* [/ActiveEcuC/PduR/UdpNm, /ActiveEcuC/PduR] */
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
  PduLengthHandlingStrategy    The strategy how larger than configured If Pdus are handled.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    PduLengthHandlingStrategy                               Comment                                Referable Keys */
  { /*     0 */ PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM },  /* [PduRDestPdu: PduRDestPdu] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRSrcPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu] */
  { /*     1 */ PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM }   /* [PduRDestPdu: PduRDestPdu] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRSrcPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu] */
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
  { /*     0 */                0u },  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
  { /*     1 */                0u }   /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */
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
  Element       Description
  LockRomIdx    the index of the 1:1 relation pointing to PduR_LockRom
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    LockRomIdx        Comment                                           Referable Keys */
  { /*     0 */         0u },  /* [Global PduRDestPdu: PncEiraEthRxPdu] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/PncEiraEthRxPdu, /ActiveEcuC/PduR/Com] */
  { /*     1 */         0u }   /* [Global PduRDestPdu: PncEiraEthTxPdu] */  /* [/ActiveEcuC/EcuC/EcucPduCollection/PncEiraEthTxPdu, /ActiveEcuC/PduR/UdpNm] */
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
  MmRomIdx               the index of the 1:1 relation pointing to PduR_MmRom
  PartitionIndexOfCsl
  SrcHnd                 handle to be used as parameter for the TxConfirmation or TriggerTransmit function call.
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    MmRomIdx  PartitionIndexOfCsl                            SrcHnd                                        Comment                              Referable Keys */
  { /*     0 */       1u,                  0u  /* CommonSharedMemory */,               PDUR_NO_SRCHNDOFRMSRCROM },  /* [PduRSrcPdu: PduRSrcPdu] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRSrcPdu] */
  { /*     1 */       0u,                  0u  /* CommonSharedMemory */, ComConf_ComIPdu_ComIPduPnc_EIRA_ETH_Tx }   /* [PduRSrcPdu: PduRSrcPdu] */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRSrcPdu] */
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
CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RmTransmitFctPtr        Referable Keys */
  /*     0 */ PduR_RmIf_RoutePdu    /* [PduR_RmIf_RoutePdu] */
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
  /*     0 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Rx/PduRDestPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Rx] */
  /*     1 */  /* [/ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingTable/PduRRoutingPath_Eira_ETH_Tx/PduRDestPdu, /ActiveEcuC/PduR/PduRRoutingTables/PduRRoutingPathGroup_Tx] */

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

