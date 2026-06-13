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
 *            Module: LdCom
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: LdCom_Lcfg.h
 *   Generation Time: 2026-05-30 23:48:29
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * WARNING: This code has been generated with reduced-severity errors. 
 * The created output files contain errors that have been ignored. Usage of the created files can lead to unpredictable behavior of the embedded code.
 * Usage of the created files happens at own risk!
 * 
 * [Warning] Cfg00022 - Missing parameter value 
 * - [Reduced Severity due to User-Defined Parameter] The value of reference LdComSystemTemplateSignalRef is missing or empty.
 * Erroneous configuration elements:
 * /ActiveEcuC/LdCom/LdComConfig/LdComIPdu_udplog_Tx[0:LdComSystemTemplateSignalRef](value={empty}) (DefRef: /MICROSAR/LdCom/LdComConfig/LdComIPdu/LdComSystemTemplateSignalRef)
 *********************************************************************************************************************/

#if !defined (LDCOM_LCFG_H)
# define LDCOM_LCFG_H
/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "ComStack_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  LdComPCDataSwitches  LdCom Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define LDCOM_FINALMAGICNUMBER                                                                      STD_OFF  /**< Deactivateable: 'LdCom_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define LDCOM_IFRXINDICATIONFCTPTR                                                                  STD_OFF  /**< Deactivateable: 'LdCom_IfRxIndicationFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_IFTXCONFIRMATIONFCTPTR                                                                STD_OFF  /**< Deactivateable: 'LdCom_IfTxConfirmationFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_IFTXTRIGGERTRANSMITFCTPTR                                                             STD_OFF  /**< Deactivateable: 'LdCom_IfTxTriggerTransmitFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_INITDATAHASHCODE                                                                      STD_OFF  /**< Deactivateable: 'LdCom_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define LDCOM_INITIALIZED                                                                           STD_ON
#define LDCOM_RXTXPDUINFO                                                                           STD_ON
#define LDCOM_IFPDUOFRXTXPDUINFO                                                                    STD_ON
#define LDCOM_IFRXINDICATIONFCTPTRIDXOFRXTXPDUINFO                                                  STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfRxIndicationFctPtrIdx' Reason: 'the optional indirection is deactivated because IfRxIndicationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_IFRXINDICATIONFCTPTRUSEDOFRXTXPDUINFO                                                 STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfRxIndicationFctPtrUsed' Reason: 'the optional indirection is deactivated because IfRxIndicationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_IFTXCONFIRMATIONFCTPTRIDXOFRXTXPDUINFO                                                STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfTxConfirmationFctPtrIdx' Reason: 'the optional indirection is deactivated because IfTxConfirmationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_IFTXCONFIRMATIONFCTPTRUSEDOFRXTXPDUINFO                                               STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfTxConfirmationFctPtrUsed' Reason: 'the optional indirection is deactivated because IfTxConfirmationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_IFTXTRIGGERTRANSMITFCTPTRIDXOFRXTXPDUINFO                                             STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfTxTriggerTransmitFctPtrIdx' Reason: 'the optional indirection is deactivated because IfTxTriggerTransmitFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_IFTXTRIGGERTRANSMITFCTPTRUSEDOFRXTXPDUINFO                                            STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.IfTxTriggerTransmitFctPtrUsed' Reason: 'the optional indirection is deactivated because IfTxTriggerTransmitFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_INVALIDHNDOFRXTXPDUINFO                                                               STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.InvalidHnd' Reason: 'the value of LdCom_InvalidHndOfRxTxPduInfo is always 'false' due to this, the array is deactivated.' */
#define LDCOM_PDURTXHANDLEIDOFRXTXPDUINFO                                                           STD_ON
#define LDCOM_TPCOPYRXDATAFCTPTRIDXOFRXTXPDUINFO                                                    STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpCopyRxDataFctPtrIdx' Reason: 'the optional indirection is deactivated because TpCopyRxDataFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPCOPYRXDATAFCTPTRUSEDOFRXTXPDUINFO                                                   STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpCopyRxDataFctPtrUsed' Reason: 'the optional indirection is deactivated because TpCopyRxDataFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPCOPYTXDATAFCTPTRIDXOFRXTXPDUINFO                                                    STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpCopyTxDataFctPtrIdx' Reason: 'the optional indirection is deactivated because TpCopyTxDataFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPCOPYTXDATAFCTPTRUSEDOFRXTXPDUINFO                                                   STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpCopyTxDataFctPtrUsed' Reason: 'the optional indirection is deactivated because TpCopyTxDataFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPRXINDICATIONFCTPTRIDXOFRXTXPDUINFO                                                  STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpRxIndicationFctPtrIdx' Reason: 'the optional indirection is deactivated because TpRxIndicationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPRXINDICATIONFCTPTRUSEDOFRXTXPDUINFO                                                 STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpRxIndicationFctPtrUsed' Reason: 'the optional indirection is deactivated because TpRxIndicationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPSTARTOFRECEPTIONFCTPTRIDXOFRXTXPDUINFO                                              STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpStartOfReceptionFctPtrIdx' Reason: 'the optional indirection is deactivated because TpStartOfReceptionFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPSTARTOFRECEPTIONFCTPTRUSEDOFRXTXPDUINFO                                             STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpStartOfReceptionFctPtrUsed' Reason: 'the optional indirection is deactivated because TpStartOfReceptionFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPTXCONFIRMATIONFCTPTRIDXOFRXTXPDUINFO                                                STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpTxConfirmationFctPtrIdx' Reason: 'the optional indirection is deactivated because TpTxConfirmationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TPTXCONFIRMATIONFCTPTRUSEDOFRXTXPDUINFO                                               STD_OFF  /**< Deactivateable: 'LdCom_RxTxPduInfo.TpTxConfirmationFctPtrUsed' Reason: 'the optional indirection is deactivated because TpTxConfirmationFctPtrUsedOfRxTxPduInfo is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define LDCOM_TXPDUOFRXTXPDUINFO                                                                    STD_ON
#define LDCOM_SIZEOFRXTXPDUINFO                                                                     STD_ON
#define LDCOM_TPCOPYRXDATAFCTPTR                                                                    STD_OFF  /**< Deactivateable: 'LdCom_TpCopyRxDataFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_TPCOPYTXDATAFCTPTR                                                                    STD_OFF  /**< Deactivateable: 'LdCom_TpCopyTxDataFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_TPRXINDICATIONFCTPTR                                                                  STD_OFF  /**< Deactivateable: 'LdCom_TpRxIndicationFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_TPSTARTOFRECEPTIONFCTPTR                                                              STD_OFF  /**< Deactivateable: 'LdCom_TpStartOfReceptionFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_TPTXCONFIRMATIONFCTPTR                                                                STD_OFF  /**< Deactivateable: 'LdCom_TpTxConfirmationFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define LDCOM_PCCONFIG                                                                              STD_ON
#define LDCOM_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'LdCom_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define LDCOM_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF  /**< Deactivateable: 'LdCom_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define LDCOM_INITIALIZEDOFPCCONFIG                                                                 STD_ON
#define LDCOM_RXTXPDUINFOOFPCCONFIG                                                                 STD_ON
#define LDCOM_SIZEOFRXTXPDUINFOOFPCCONFIG                                                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCIsReducedToDefineDefines  LdCom Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define LDCOM_ISDEF_IFPDUOFRXTXPDUINFO                                                              STD_OFF
#define LDCOM_ISDEF_PDURTXHANDLEIDOFRXTXPDUINFO                                                     STD_OFF
#define LDCOM_ISDEF_TXPDUOFRXTXPDUINFO                                                              STD_OFF
#define LDCOM_ISDEF_INITIALIZEDOFPCCONFIG                                                           STD_ON
#define LDCOM_ISDEF_RXTXPDUINFOOFPCCONFIG                                                           STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCEqualsAlwaysToDefines  LdCom Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define LDCOM_EQ2_IFPDUOFRXTXPDUINFO                                                                
#define LDCOM_EQ2_PDURTXHANDLEIDOFRXTXPDUINFO                                                       
#define LDCOM_EQ2_TXPDUOFRXTXPDUINFO                                                                
#define LDCOM_EQ2_INITIALIZEDOFPCCONFIG                                                             (&(LdCom_Initialized))
#define LDCOM_EQ2_RXTXPDUINFOOFPCCONFIG                                                             LdCom_RxTxPduInfo
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCSymbolicInitializationPointers  LdCom Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define LdCom_Config_Ptr                                                                            NULL_PTR  /**< symbolic identifier which shall be used to initialize 'LdCom' */
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCInitializationSymbols  LdCom Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define LdCom_Config                                                                                NULL_PTR  /**< symbolic identifier which could be used to initialize 'LdCom */
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCGeneral  LdCom General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define LDCOM_CHECK_INIT_POINTER                                                                    STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define LDCOM_FINAL_MAGIC_NUMBER                                                                    0xFF1Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of LdCom */
#define LDCOM_INDIVIDUAL_POSTBUILD                                                                  STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'LdCom' is not configured to be postbuild capable. */
#define LDCOM_INIT_DATA                                                                             LDCOM_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define LDCOM_INIT_DATA_HASH_CODE                                                                   -392515026  /**< the precompile constant to validate the initialization structure at initialization time of LdCom with a hashcode. The seed value is '0xFF1Eu' */
#define LDCOM_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define LDCOM_USE_INIT_POINTER                                                                      STD_OFF  /**< STD_ON if the init pointer LdCom shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  LdComLTDataSwitches  LdCom Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define LDCOM_LTCONFIG                                                                              STD_OFF  /**< Deactivateable: 'LdCom_LTConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  LdComPCGetConstantDuplicatedRootDataMacros  LdCom Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define LdCom_GetInitializedOfPCConfig()                                                            (&(LdCom_Initialized))  /**< the pointer to LdCom_Initialized */
#define LdCom_GetRxTxPduInfoOfPCConfig()                                                            LdCom_RxTxPduInfo  /**< the pointer to LdCom_RxTxPduInfo */
#define LdCom_GetSizeOfRxTxPduInfoOfPCConfig()                                                      1u  /**< the number of accomplishable value elements in LdCom_RxTxPduInfo */
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCGetDataMacros  LdCom Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define LdCom_IsInitialized()                                                                       (((*(LdCom_GetInitializedOfPCConfig()))) != FALSE)
#define LdCom_IsTxPduOfRxTxPduInfo(Index)                                                           ((LdCom_GetRxTxPduInfoOfPCConfig()[(Index)].TxPduOfRxTxPduInfo) != FALSE)
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCGetDeduplicatedDataMacros  LdCom Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define LdCom_IsIfPduOfRxTxPduInfo(Index)                                                           LdCom_IsTxPduOfRxTxPduInfo(Index)
#define LdCom_GetPduRTxHandleIdOfRxTxPduInfo(Index)                                                 ((LdCom_PduRTxHandleIdOfRxTxPduInfoType)((((LdCom_PduRTxHandleIdOfRxTxPduInfoType)(Index)) + 1u)))  /**< Handle ID used to call PduR_LdComTransmit() */
#define LdCom_GetSizeOfRxTxPduInfo()                                                                LdCom_GetSizeOfRxTxPduInfoOfPCConfig()
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCSetDataMacros  LdCom Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define LdCom_SetInitialized(Value)                                                                 (*(LdCom_GetInitializedOfPCConfig())) = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  LdComPCHasMacros  LdCom Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define LdCom_HasInitialized()                                                                      (TRUE != FALSE)
#define LdCom_HasRxTxPduInfo()                                                                      (TRUE != FALSE)
#define LdCom_HasIfPduOfRxTxPduInfo()                                                               (TRUE != FALSE)
#define LdCom_HasPduRTxHandleIdOfRxTxPduInfo()                                                      (TRUE != FALSE)
#define LdCom_HasTxPduOfRxTxPduInfo()                                                               (TRUE != FALSE)
#define LdCom_HasSizeOfRxTxPduInfo()                                                                (TRUE != FALSE)
#define LdCom_HasPCConfig()                                                                         (TRUE != FALSE)
#define LdCom_HasInitializedOfPCConfig()                                                            (TRUE != FALSE)
#define LdCom_HasRxTxPduInfoOfPCConfig()                                                            (TRUE != FALSE)
#define LdCom_HasSizeOfRxTxPduInfoOfPCConfig()                                                      (TRUE != FALSE)
/** 
  \}
*/ 

  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
  /* PRQA L:Macros_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  LdComPCIterableTypes  LdCom Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate LdCom_RxTxPduInfo */
typedef uint8_least LdCom_RxTxPduInfoIterType;

/** 
  \}
*/ 

/** 
  \defgroup  LdComPCValueTypes  LdCom Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for LdCom_Initialized */
typedef boolean LdCom_InitializedType;

/**   \brief  value based type definition for LdCom_IfPduOfRxTxPduInfo */
typedef boolean LdCom_IfPduOfRxTxPduInfoType;

/**   \brief  value based type definition for LdCom_PduRTxHandleIdOfRxTxPduInfo */
typedef uint8 LdCom_PduRTxHandleIdOfRxTxPduInfoType;

/**   \brief  value based type definition for LdCom_TxPduOfRxTxPduInfo */
typedef boolean LdCom_TxPduOfRxTxPduInfoType;

/**   \brief  value based type definition for LdCom_SizeOfRxTxPduInfo */
typedef uint8 LdCom_SizeOfRxTxPduInfoType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  LdComPCStructTypes  LdCom Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in LdCom_RxTxPduInfo */
typedef struct sLdCom_RxTxPduInfoType
{
  LdCom_TxPduOfRxTxPduInfoType TxPduOfRxTxPduInfo;
} LdCom_RxTxPduInfoType;

/** 
  \}
*/ 

/** 
  \defgroup  LdComPCRootPointerTypes  LdCom Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to LdCom_Initialized */
typedef P2VAR(LdCom_InitializedType, TYPEDEF, LDCOM_VAR_ZERO_INIT) LdCom_InitializedPtrType;

/**   \brief  type used to point to LdCom_RxTxPduInfo */
typedef P2CONST(LdCom_RxTxPduInfoType, TYPEDEF, LDCOM_CONST) LdCom_RxTxPduInfoPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  LdComPCRootValueTypes  LdCom Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in LdCom_PCConfig */
typedef struct sLdCom_PCConfigType
{
  uint8 LdCom_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} LdCom_PCConfigType;

typedef LdCom_PCConfigType LdCom_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  LdCom_RxTxPduInfo
**********************************************************************************************************************/
/** 
  \var    LdCom_RxTxPduInfo
  \brief  Table containing mapping data from Input handles to PduR Tx handles/RTE callbacks.
  \details
  Element    Description
  TxPdu  
*/ 
#define LDCOM_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(LdCom_RxTxPduInfoType, LDCOM_CONST) LdCom_RxTxPduInfo[1];
#define LDCOM_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  LdCom_Initialized
**********************************************************************************************************************/
/** 
  \var    LdCom_Initialized
  \brief  Initialization state of LdCom. TRUE, if initialized.
*/ 
#define LDCOM_START_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern VAR(LdCom_InitializedType, LDCOM_VAR_ZERO_INIT) LdCom_Initialized;
#define LDCOM_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/



#endif  /* LDCOM_LCFG_H */
/**********************************************************************************************************************
 *  END OF FILE: LdCom_Lcfg.h
 *********************************************************************************************************************/
