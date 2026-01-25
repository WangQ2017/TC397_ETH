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
 *            Module: Com
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Com_Lcfg.c
 *   Generation Time: 2026-01-24 23:52:00
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
  MISRA / PClint JUSTIFICATIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  INCLUDES
**********************************************************************************************************************/
#define V_IL_ASRCOMCFG5_LCFG_SOURCE

#include "Com.h"

#include "Com_Lcfg.h"

#include "Appl_Cbk.h"

#include "SchM_Com.h"

/**********************************************************************************************************************
  LOCAL CONSTANT MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/

/**********************************************************************************************************************
  LOCAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Com_CbkTxAckDefFuncPtr
**********************************************************************************************************************/
/** 
  \var    Com_CbkTxAckDefFuncPtr
  \brief  Function pointer table for deferred Tx confirmation notification functions.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(ComCbkTxAckDefType, COM_CONST) Com_CbkTxAckDefFuncPtr[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     CbkTxAckDefFuncPtr       Referable Keys */
  /*     0 */ Com_Cbk_FalutInfoTx    /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_ConstValueArrayBased
**********************************************************************************************************************/
/** 
  \var    Com_ConstValueArrayBased
  \brief  Optimized array of commonly used values like initial or invalid values. (UINT8_N, UINT8_DYN)
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_ConstValueArrayBasedType, COM_CONST) Com_ConstValueArrayBased[7] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     ConstValueArrayBased      Referable Keys */
  /*     0 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     1 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     2 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     3 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     4 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     5 */                 0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
  /*     6 */                 0x00u   /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxInitValue] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_ConstValueUInt8
**********************************************************************************************************************/
/** 
  \var    Com_ConstValueUInt8
  \brief  Optimized array of commonly used values like initial or invalid values. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_ConstValueUInt8Type, COM_CONST) Com_ConstValueUInt8[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     ConstValueUInt8      Referable Keys */
  /*     0 */            0x00u   /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0InitValue, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1InitValue, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2InitValue, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3InitValue] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_PduGrpVector
**********************************************************************************************************************/
/** 
  \var    Com_PduGrpVector
  \brief  Contains an I-PDU-Group vector for each I-PDU, mapping the I-PDU to the corresponding I-PDU-Groups.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_PduGrpVectorType, COM_CONST) Com_PduGrpVector[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     PduGrpVector      Referable Keys */
  /*     0 */         0x03u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*     1 */         0x0Cu   /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxAccessInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxAccessInfo
  \brief  Contains all signal layout information necessary for signal access within an I-PDU.
  \details
  Element                                  Description
  InitValueUsed                            TRUE, if the 0:1 relation has minimum 1 relation pointing to Com_ConstValueUInt8,Com_ConstValueUInt16,Com_ConstValueUInt32,Com_ConstValueUInt64,Com_ConstValueSInt8,Com_ConstValueSInt16,Com_ConstValueSInt32,Com_ConstValueSInt64,Com_ConstValueFloat32,Com_ConstValueFloat64
  RxSigBufferArrayBasedBufferUsed          TRUE, if the 0:n relation has 1 relation pointing to Com_RxSigBufferArrayBased
  ApplType                                 Application data type.
  BitLength                                Bit length of the signal or group signal.
  BitPosition                              Little endian bit position of the signal or group signal within the I-PDU.
  BufferIdx                                the index of the 0:1 relation pointing to Com_RxSigBufferUInt8,Com_RxSigBufferUInt16,Com_RxSigBufferUInt32,Com_RxSigBufferUInt64,Com_RxSigBufferZeroBit,Com_RxSigBufferSInt8,Com_RxSigBufferSInt16,Com_RxSigBufferSInt32,Com_RxSigBufferSInt64,Com_RxSigBufferFloat32,Com_RxSigBufferFloat64
  BusAcc                                   BUS access algorithm for signal or group signal packing / un-packing.
  ByteLength                               Byte length of the signal or group signal.
  ConstValueArrayBasedInitValueEndIdx      the end index of the 0:n relation pointing to Com_ConstValueArrayBased
  ConstValueArrayBasedInitValueStartIdx    the start index of the 0:n relation pointing to Com_ConstValueArrayBased
  InitValueIdx                             the index of the 0:1 relation pointing to Com_ConstValueUInt8,Com_ConstValueUInt16,Com_ConstValueUInt32,Com_ConstValueUInt64,Com_ConstValueSInt8,Com_ConstValueSInt16,Com_ConstValueSInt32,Com_ConstValueSInt64,Com_ConstValueFloat32,Com_ConstValueFloat64
  RxPduInfoIdx                             the index of the 1:1 relation pointing to Com_RxPduInfo
  RxSigBufferArrayBasedBufferEndIdx        the end index of the 0:n relation pointing to Com_RxSigBufferArrayBased
  RxSigBufferArrayBasedBufferStartIdx      the start index of the 0:n relation pointing to Com_RxSigBufferArrayBased
  ShdBufferIdx                             the index of the 0:1 relation pointing to Com_RxSigBufferUInt8,Com_RxSigBufferUInt16,Com_RxSigBufferUInt32,Com_RxSigBufferUInt64,Com_RxSigBufferZeroBit,Com_RxSigBufferSInt8,Com_RxSigBufferSInt16,Com_RxSigBufferSInt32,Com_RxSigBufferSInt64,Com_RxSigBufferFloat32,Com_RxSigBufferFloat64
  StartByteInPduPosition                   Start Byte position of the signal or group signal within the I-PDU.
  TmpBufferIdx                             the index of the 0:1 relation pointing to Com_TmpRxShdBufferUInt8,Com_TmpRxShdBufferUInt16,Com_TmpRxShdBufferUInt32,Com_TmpRxShdBufferUInt64,Com_TmpRxShdBufferSInt8,Com_TmpRxShdBufferSInt16,Com_TmpRxShdBufferSInt32,Com_TmpRxShdBufferSInt64,Com_TmpRxShdBufferFloat32,Com_TmpRxShdBufferFloat64
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxAccessInfoType, COM_CONST) Com_RxAccessInfo[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitValueUsed  RxSigBufferArrayBasedBufferUsed  ApplType                            BitLength  BitPosition  BufferIdx                       BusAcc                                ByteLength  ConstValueArrayBasedInitValueEndIdx                       ConstValueArrayBasedInitValueStartIdx                       InitValueIdx                       RxPduInfoIdx  RxSigBufferArrayBasedBufferEndIdx                       RxSigBufferArrayBasedBufferStartIdx                       ShdBufferIdx                       StartByteInPduPosition  TmpBufferIdx                             Referable Keys */
  { /*     0 */          TRUE,                           FALSE,   COM_UINT8_APPLTYPEOFRXACCESSINFO,        8u,          0u,                             0u,        COM_BYTE_BUSACCOFRXACCESSINFO,         1u, COM_NO_CONSTVALUEARRAYBASEDINITVALUEENDIDXOFRXACCESSINFO, COM_NO_CONSTVALUEARRAYBASEDINITVALUESTARTIDXOFRXACCESSINFO,                                0u,           1u, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERENDIDXOFRXACCESSINFO, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERSTARTIDXOFRXACCESSINFO,                                1u,                     0u,                                0u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0, /ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx] */
  { /*     1 */          TRUE,                           FALSE,   COM_UINT8_APPLTYPEOFRXACCESSINFO,        8u,          8u,                             2u,        COM_BYTE_BUSACCOFRXACCESSINFO,         1u, COM_NO_CONSTVALUEARRAYBASEDINITVALUEENDIDXOFRXACCESSINFO, COM_NO_CONSTVALUEARRAYBASEDINITVALUESTARTIDXOFRXACCESSINFO,                                0u,           1u, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERENDIDXOFRXACCESSINFO, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERSTARTIDXOFRXACCESSINFO,                                3u,                     1u,                                1u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1, /ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx] */
  { /*     2 */          TRUE,                           FALSE,   COM_UINT8_APPLTYPEOFRXACCESSINFO,        8u,         16u,                             4u,        COM_BYTE_BUSACCOFRXACCESSINFO,         1u, COM_NO_CONSTVALUEARRAYBASEDINITVALUEENDIDXOFRXACCESSINFO, COM_NO_CONSTVALUEARRAYBASEDINITVALUESTARTIDXOFRXACCESSINFO,                                0u,           1u, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERENDIDXOFRXACCESSINFO, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERSTARTIDXOFRXACCESSINFO,                                5u,                     2u,                                3u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2, /ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx] */
  { /*     3 */          TRUE,                           FALSE,   COM_UINT8_APPLTYPEOFRXACCESSINFO,        8u,         24u,                             6u,        COM_BYTE_BUSACCOFRXACCESSINFO,         1u, COM_NO_CONSTVALUEARRAYBASEDINITVALUEENDIDXOFRXACCESSINFO, COM_NO_CONSTVALUEARRAYBASEDINITVALUESTARTIDXOFRXACCESSINFO,                                0u,           1u, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERENDIDXOFRXACCESSINFO, COM_NO_RXSIGBUFFERARRAYBASEDBUFFERSTARTIDXOFRXACCESSINFO,                                7u,                     3u,                                2u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3, /ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx] */
  { /*     4 */         FALSE,                            TRUE, COM_UINT8_N_APPLTYPEOFRXACCESSINFO,       56u,          0u, COM_NO_BUFFERIDXOFRXACCESSINFO, COM_ARRAY_BASED_BUSACCOFRXACCESSINFO,         7u,                                                       7u,                                                         0u, COM_NO_INITVALUEIDXOFRXACCESSINFO,           0u,                                                     7u,                                                       0u, COM_NO_SHDBUFFERIDXOFRXACCESSINFO,                     0u, COM_NO_TMPBUFFERIDXOFRXACCESSINFO }   /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxAccessInfoInd
**********************************************************************************************************************/
/** 
  \var    Com_RxAccessInfoInd
  \brief  the indexes of the 1:1 sorted relation pointing to Com_RxAccessInfo
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxAccessInfoIndType, COM_CONST) Com_RxAccessInfoInd[5] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RxAccessInfoInd      Referable Keys */
  /*     0 */               4u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*     1 */               0u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
  /*     2 */               1u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
  /*     3 */               2u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
  /*     4 */               3u   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxCbkFuncPtr
**********************************************************************************************************************/
/** 
  \var    Com_RxCbkFuncPtr
  \brief  Function pointer table containing configured notification and invalid notifications function pointer for signals and signal groups.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(ComRxCbkType, COM_CONST) Com_RxCbkFuncPtr[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     RxCbkFuncPtr                              Referable Keys */
  /*     0 */ ComM_ComCbk_ComSignalPnc_EIRA_ETH_Rx ,  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_RxAck] */
  /*     1 */ Com_Cbk_VechicleInfoRx                  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRxAck] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxPduInfo
  \brief  Contains all relevant common information for Rx I-PDUs.
  \details
  Element                    Description
  RxAccessInfoIndUsed        TRUE, if the 0:n relation has 1 relation pointing to Com_RxAccessInfoInd
  RxSigInfoUsed              TRUE, if the 0:n relation has 1 relation pointing to Com_RxSigInfo
  RxAccessInfoIndEndIdx      the end index of the 0:n relation pointing to Com_RxAccessInfoInd
  RxDefPduBufferEndIdx       the end index of the 0:n relation pointing to Com_RxDefPduBuffer
  RxDefPduBufferStartIdx     the start index of the 0:n relation pointing to Com_RxDefPduBuffer
  RxSigGrpInfoIndEndIdx      the end index of the 0:n relation pointing to Com_RxSigGrpInfoInd
  RxSigGrpInfoIndStartIdx    the start index of the 0:n relation pointing to Com_RxSigGrpInfoInd
  RxSigInfoEndIdx            the end index of the 0:n relation pointing to Com_RxSigInfo
  RxSigInfoStartIdx          the start index of the 0:n relation pointing to Com_RxSigInfo
  Type                       Defines whether rx Pdu is a NORMAL or TP IPdu.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxPduInfoType, COM_CONST) Com_RxPduInfo[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxAccessInfoIndUsed  RxSigInfoUsed  RxAccessInfoIndEndIdx  RxDefPduBufferEndIdx  RxDefPduBufferStartIdx  RxSigGrpInfoIndEndIdx                    RxSigGrpInfoIndStartIdx                    RxSigInfoEndIdx                    RxSigInfoStartIdx                    Type                              Referable Keys */
  { /*     0 */                TRUE,          TRUE,                    1u,                   7u,                     0u, COM_NO_RXSIGGRPINFOINDENDIDXOFRXPDUINFO, COM_NO_RXSIGGRPINFOINDSTARTIDXOFRXPDUINFO,                                1u,                                  0u, COM_NORMAL_TYPEOFRXPDUINFO },  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Rx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Rx_PNC_All_Active] */
  { /*     1 */                TRUE,         FALSE,                    5u,                  15u,                     7u,                                      1u,                                        0u, COM_NO_RXSIGINFOENDIDXOFRXPDUINFO, COM_NO_RXSIGINFOSTARTIDXOFRXPDUINFO, COM_NORMAL_TYPEOFRXPDUINFO }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigGrpInfo
**********************************************************************************************************************/
/** 
  \var    Com_RxSigGrpInfo
  \brief  Contains all relevant information for Rx signal groups.
  \details
  Element                Description
  RxCbkFuncPtrAckUsed    TRUE, if the 0:1 relation has minimum 1 relation pointing to Com_RxCbkFuncPtr
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_RxSigGrpInfoType, COM_CONST) Com_RxSigGrpInfo[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    RxCbkFuncPtrAckUsed        Referable Keys */
  { /*     0 */                TRUE }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxModeInfo
  \brief  Contains all relevant information for transmission mode handling.
  \details
  Element     Description
  InitMode    Initial transmission mode selector of the Tx I-PDU.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeInfoType, COM_CONST) Com_TxModeInfo[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    InitMode        Referable Keys */
  { /*     0 */     TRUE },  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  { /*     1 */     TRUE }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxModeTrue
**********************************************************************************************************************/
/** 
  \var    Com_TxModeTrue
  \brief  Contains all relevant information for transmission mode true.
  \details
  Element    Description
  Direct     TRUE if transmission mode contains a direct part.
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxModeTrueType, COM_CONST) Com_TxModeTrue[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    Direct        Referable Keys */
  { /*     0 */  FALSE },  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  { /*     1 */   TRUE }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInfo
  \brief  Contains all relevant information for Tx I-PDUs.
  \details
  Element                          Description
  TxPduInitValueUsed               TRUE, if the 0:n relation has 1 relation pointing to Com_TxPduInitValue
  TxSigGrpInfoIndUsed              TRUE, if the 0:n relation has 1 relation pointing to Com_TxSigGrpInfoInd
  CbkTxAckDefFuncPtrIndEndIdx      the end index of the 0:n relation pointing to Com_CbkTxAckDefFuncPtrInd
  CbkTxAckDefFuncPtrIndStartIdx    the start index of the 0:n relation pointing to Com_CbkTxAckDefFuncPtrInd
  MetaDataLength                   Length of MetaData.
  PduGrpVectorEndIdx               the end index of the 0:n relation pointing to Com_PduGrpVector
  PduGrpVectorStartIdx             the start index of the 0:n relation pointing to Com_PduGrpVector
  TxPduInitValueEndIdx             the end index of the 0:n relation pointing to Com_TxPduInitValue
  TxPduInitValueStartIdx           the start index of the 0:n relation pointing to Com_TxPduInitValue
  TxSigGrpInfoIndEndIdx            the end index of the 0:n relation pointing to Com_TxSigGrpInfoInd
  TxSigGrpInfoIndStartIdx          the start index of the 0:n relation pointing to Com_TxSigGrpInfoInd
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInfoType, COM_CONST) Com_TxPduInfo[2] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxPduInitValueUsed  TxSigGrpInfoIndUsed  CbkTxAckDefFuncPtrIndEndIdx                    CbkTxAckDefFuncPtrIndStartIdx                    MetaDataLength  PduGrpVectorEndIdx                    PduGrpVectorStartIdx                    TxPduInitValueEndIdx  TxPduInitValueStartIdx  TxSigGrpInfoIndEndIdx                    TxSigGrpInfoIndStartIdx                          Referable Keys */
  { /*     0 */               TRUE,               FALSE, COM_NO_CBKTXACKDEFFUNCPTRINDENDIDXOFTXPDUINFO, COM_NO_CBKTXACKDEFFUNCPTRINDSTARTIDXOFTXPDUINFO,             0u,                                   2u,                                     1u,                   7u,                     0u, COM_NO_TXSIGGRPINFOINDENDIDXOFTXPDUINFO, COM_NO_TXSIGGRPINFOINDSTARTIDXOFTXPDUINFO },  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  { /*     1 */               TRUE,                TRUE,                                            1u,                                              0u,             0u, COM_NO_PDUGRPVECTORENDIDXOFTXPDUINFO, COM_NO_PDUGRPVECTORSTARTIDXOFTXPDUINFO,                  15u,                     7u,                                      1u,                                        0u }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduInitValue
**********************************************************************************************************************/
/** 
  \var    Com_TxPduInitValue
  \brief  Initial values used for Tx I-PDU buffer initialization.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxPduInitValueType, COM_CONST) Com_TxPduInitValue[15] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxPduInitValue      Referable Keys */
  /*     0 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     1 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     2 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     3 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     4 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     5 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     6 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
  /*     7 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*     8 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*     9 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    10 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    11 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    12 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    13 */           0x00u,  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    14 */           0x00u   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSigGrpInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxSigGrpInfo
  \brief  Contains all relevant information for Tx Signal Groups.
  \details
  Element             Description
  TxSigGrpMaskUsed    TRUE, if the 0:n relation has 1 relation pointing to Com_TxSigGrpMask
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxSigGrpInfoType, COM_CONST) Com_TxSigGrpInfo[1] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxSigGrpMaskUsed        Referable Keys */
  { /*     0 */             TRUE }   /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte0, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte1, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte2] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSigGrpMask
**********************************************************************************************************************/
/** 
  \var    Com_TxSigGrpMask
  \brief  Signal group mask needed to copy interlaced signal groups to the Tx PDU buffer.
*/ 
#define COM_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxSigGrpMaskType, COM_CONST) Com_TxSigGrpMask[3] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index     TxSigGrpMask      Referable Keys */
  /*     0 */         0xFFu,  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx] */
  /*     1 */         0xFFu,  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx] */
  /*     2 */         0xFFu   /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx] */
};
#define COM_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSigInfo
**********************************************************************************************************************/
/** 
  \var    Com_TxSigInfo
  \brief  Contains all relevant information for Tx signals and group signals.
  \details
  Element                   Description
  TxSigGrpInfoUsed          TRUE, if the 0:1 relation has minimum 1 relation pointing to Com_TxSigGrpInfo
  ApplType                  Application data type.
  BitLength                 Bit length of the signal or group signal.
  BitPosition               Little endian bit position of the signal or group signal within the I-PDU.
  BusAcc                    BUS access algorithm for signal or group signal packing / un-packing.
  StartByteInPduPosition    Start Byte position of the signal or group signal within the I-PDU.
  TxBufferEndIdx            the end index of the 0:n relation pointing to Com_TxBuffer
  TxBufferStartIdx          the start index of the 0:n relation pointing to Com_TxBuffer
  TxPduInfoIdx              the index of the 1:1 relation pointing to Com_TxPduInfo
  TxSigGrpInfoIdx           the index of the 0:1 relation pointing to Com_TxSigGrpInfo
*/ 
#define COM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
CONST(Com_TxSigInfoType, COM_CONST) Com_TxSigInfo[4] = {  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    TxSigGrpInfoUsed  ApplType                         BitLength  BitPosition  BusAcc                             StartByteInPduPosition  TxBufferEndIdx  TxBufferStartIdx  TxPduInfoIdx  TxSigGrpInfoIdx                          Referable Keys */
  { /*     0 */             TRUE,   COM_UINT8_APPLTYPEOFTXSIGINFO,        8u,          0u,        COM_BYTE_BUSACCOFTXSIGINFO,                     0u,            16u,              15u,           1u,                                0u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte0, /ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  { /*     1 */             TRUE,   COM_UINT8_APPLTYPEOFTXSIGINFO,        8u,          8u,        COM_BYTE_BUSACCOFTXSIGINFO,                     1u,            17u,              16u,           1u,                                0u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte1, /ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  { /*     2 */             TRUE,   COM_UINT8_APPLTYPEOFTXSIGINFO,        8u,         16u,        COM_BYTE_BUSACCOFTXSIGINFO,                     2u,            18u,              17u,           1u,                                0u },  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte2, /ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  { /*     3 */            FALSE, COM_UINT8_N_APPLTYPEOFTXSIGINFO,       56u,          0u, COM_ARRAY_BASED_BUSACCOFTXSIGINFO,                     0u,             7u,               0u,           0u, COM_NO_TXSIGGRPINFOIDXOFTXSIGINFO }   /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx] */
};
#define COM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_CurrentTxMode
**********************************************************************************************************************/
/** 
  \var    Com_CurrentTxMode
  \brief  Current transmission mode state of all Tx I-PDUs.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_CurrentTxModeType, COM_VAR_NOINIT) Com_CurrentTxMode[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_HandleRxPduDeferred
**********************************************************************************************************************/
/** 
  \var    Com_HandleRxPduDeferred
  \brief  Array indicating received Rx I-PDUs to be processed deferred within the next call of Com_MainfunctionRx().
*/ 
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_HandleRxPduDeferredUType, COM_VAR_NOINIT) Com_HandleRxPduDeferred;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */

#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_HandleTxPduDeferred
**********************************************************************************************************************/
/** 
  \var    Com_HandleTxPduDeferred
  \brief  Flag array used for deferred Tx confirmation handling.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_HandleTxPduDeferredType, COM_VAR_NOINIT) Com_HandleTxPduDeferred[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_Initialized
**********************************************************************************************************************/
/** 
  \var    Com_Initialized
  \brief  Initialization state of Com. TRUE, if Com_Init() has been called, else FALSE.
*/ 
#define COM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_InitializedType, COM_VAR_ZERO_INIT) Com_Initialized = FALSE;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDefPduBuffer
**********************************************************************************************************************/
/** 
  \var    Com_RxDefPduBuffer
  \brief  Rx I-PDU buffer for deferred signal processing.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDefPduBufferUType, COM_VAR_NOINIT) Com_RxDefPduBuffer;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*     6 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx] */
  /*     7 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */
  /*    14 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeferredFctPtrCache
**********************************************************************************************************************/
/** 
  \var    Com_RxDeferredFctPtrCache
  \brief  Cache for deferred Rx (invalid) notification.
*/ 
#define COM_START_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeferredFctPtrCacheType, COM_VAR_NOINIT) Com_RxDeferredFctPtrCache[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_32BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxDeferredProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxDeferredProcessingISRLockCounterType, COM_VAR_NOINIT) Com_RxDeferredProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_RxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_RxPduGrpActive
  \brief  Rx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxPduGrpActiveType, COM_VAR_NOINIT) Com_RxPduGrpActive[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Rx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Rx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_VechicleInfoRx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigBufferArrayBased
**********************************************************************************************************************/
/** 
  \var    Com_RxSigBufferArrayBased
  \brief  Rx Signal and Group Signal Buffer. (UINT8_N, UINT8_DYN)
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxSigBufferArrayBasedType, COM_VAR_NOINIT) Com_RxSigBufferArrayBased[7];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx_RxSignalBufferRouting] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx_RxSignalBufferRouting] */
  /*     6 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Rx_RxSignalBufferRouting] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_RxSigBufferUInt8
**********************************************************************************************************************/
/** 
  \var    Com_RxSigBufferUInt8
  \brief  Rx Signal and Group Signal Buffer. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_RxSigBufferUInt8Type, COM_VAR_NOINIT) Com_RxSigBufferUInt8[8];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0_RxGroupSignalShadowBuffer, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0_RxSignalBufferRouting] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1_RxGroupSignalShadowBuffer, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1_RxSignalBufferRouting] */
  /*     4 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2] */
  /*     5 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2_RxGroupSignalShadowBuffer, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2_RxSignalBufferRouting] */
  /*     6 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3] */
  /*     7 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3_RxGroupSignalShadowBuffer, /ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3_RxSignalBufferRouting] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_SigGrpEventFlag
**********************************************************************************************************************/
/** 
  \var    Com_SigGrpEventFlag
  \brief  Flag is set if a group signal write access caused a triggered event.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_SigGrpEventFlagType, COM_VAR_NOINIT) Com_SigGrpEventFlag[1];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TmpRxBuffer
**********************************************************************************************************************/
/** 
  \var    Com_TmpRxBuffer
  \brief  Temporary buffer for Rx UINT8_N and UINT8_DYN signals.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TmpRxBufferType, COM_VAR_NOINIT) Com_TmpRxBuffer[7];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TmpRxShdBufferUInt8
**********************************************************************************************************************/
/** 
  \var    Com_TmpRxShdBufferUInt8
  \brief  Temporary Rx Group Signal Shadow Buffer. (BOOLEAN, UINT8)
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TmpRxShdBufferUInt8UType, COM_VAR_NOINIT) Com_TmpRxShdBufferUInt8;  /* PRQA S 0759, 1514, 1533 */  /* MD_CSL_Union, MD_CSL_ObjectOnlyAccessedOnce, MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte0] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte1] */
  /*     2 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte3] */
  /*     3 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_VechicleInfoRx/ComGroupSignal_VechicleInfoRx_byte2] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TransmitRequest
**********************************************************************************************************************/
/** 
  \var    Com_TransmitRequest
  \brief  Transmit request flag used for decoupled Tx I-PDU tranmission.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TransmitRequestType, COM_VAR_NOINIT) Com_TransmitRequest[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxBuffer
**********************************************************************************************************************/
/** 
  \var    Com_TxBuffer
  \brief  Shared uint8 buffer for Tx I-PDUs and ComSignalGroup shadow buffer.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxBufferType, COM_VAR_NOINIT) Com_TxBuffer[18];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Tx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Tx] */
  /*     6 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComSignalPnc_EIRA_ETH_Tx] */
  /*     7 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTxSigGrpInTxIPDU] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTxSigGrpInTxIPDU] */
  /*     9 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTxSigGrpInTxIPDU] */
  /*    10 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*   ... */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    14 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */
  /*    15 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte0] */
  /*    16 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte1] */
  /*    17 */  /* [/ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx, /ActiveEcuC/Com/ComConfig/ComSignalGroup_FalutInfoTx/ComGroupSignal_FalutInfoTx_byte2] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxIPduGroupISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxIPduGroupISRLockCounterType, COM_VAR_NOINIT) Com_TxIPduGroupISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxPduGrpActive
**********************************************************************************************************************/
/** 
  \var    Com_TxPduGrpActive
  \brief  Tx I-PDU based state (started/stopped) of the corresponding I-PDU-Group.
*/ 
#define COM_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxPduGrpActiveType, COM_VAR_NOINIT) Com_TxPduGrpActive[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */

#define COM_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxProcessingISRLockCounter
**********************************************************************************************************************/
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxProcessingISRLockCounterType, COM_VAR_NOINIT) Com_TxProcessingISRLockCounter;  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  Com_TxSduLength
**********************************************************************************************************************/
/** 
  \var    Com_TxSduLength
  \brief  This var Array contains the Com Ipdu Length.
*/ 
#define COM_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
VAR(Com_TxSduLengthType, COM_VAR_NOINIT) Com_TxSduLength[2];  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Com/ComConfig/ComIPduPnc_EIRA_ETH_Tx, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC00, /ActiveEcuC/Com/ComConfig/ComIPduGroup_Tx_PNC_All_Active] */
  /*     1 */  /* [/ActiveEcuC/Com/ComConfig/ComIPdu_FalutInfoTx] */

#define COM_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  LOCAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



/**********************************************************************************************************************
  LOCAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  GLOBAL FUNCTIONS
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTIONS
**********************************************************************************************************************/






/**********************************************************************************************************************
  END OF FILE: Com_Lcfg.c
**********************************************************************************************************************/

