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
 *            Module: Eth_30_Tc3xx
 *           Program: MSR_Vector_SLP4
 *          Customer: Aptiv (China) Technology Company Ltd.
 *       Expiry Date: Not restricted
 *  Ordered Derivat.: TC397 
 *    License Scope : The usage is restricted to CBD2000642_D01
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Eth_30_Tc3xx_Lcfg.h
 *   Generation Time: 2025-12-14 16:26:31
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETH_30_TC3XX_LCFG_H)
# define ETH_30_TC3XX_LCFG_H

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_GenTypes.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined (ETH_30_TC3XX_LOCAL_INLINE)
#  define ETH_30_TC3XX_LOCAL_INLINE LOCAL_INLINE
# endif
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/**********************************************************************************************************************
  Eth_30_Tc3xx_ConfigDataPtr
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_ConfigDataPtr
  \brief  Points to the currently active configuration for Eth_30_Tc3xx
  \details
  Pointer is intialized during Eth_30_Tc3xx_Init() and holds the active configuration for Eth_30_Tc3xx
  were all configuration data is retrieved from during runtime.
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_VAR_NOINIT, ETH_30_TC3XX_INIT_DATA) Eth_30_Tc3xx_ConfigDataPtr;
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/ 
  /* PRQA S 3453 MACROS_3453 */  /* MD_CSL_3453 */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Eth_30_Tc3xxPCGetRootDataMacros  Eth_30_Tc3xx Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->ActiveMacAddressOfPCConfig
#define Eth_30_Tc3xx_GetEthCtrlOfPCConfig()                           Eth_30_Tc3xx_ConfigDataPtr->EthCtrlOfPCConfig
#define Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->EthCtrlStateOfPCConfig
#define Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->EthCtrlTc3xxOfPCConfig
#define Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()                 Eth_30_Tc3xx_ConfigDataPtr->EthCtrlTc3xxStateOfPCConfig
#define Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->EthMeasDataCounterOfPCConfig
#define Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()           Eth_30_Tc3xx_ConfigDataPtr->EthMeasDataCounterResetOfPCConfig
#define Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()                         Eth_30_Tc3xx_ConfigDataPtr->EthSwtIfcOfPCConfig
#define Eth_30_Tc3xx_GetInitialMacAddressOfPCConfig()                 Eth_30_Tc3xx_ConfigDataPtr->InitialMacAddressOfPCConfig
#define Eth_30_Tc3xx_GetIsrInfosOfPCConfig()                          Eth_30_Tc3xx_ConfigDataPtr->IsrInfosOfPCConfig
#define Eth_30_Tc3xx_GetIsrIrqEventFuncsOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->IsrIrqEventFuncsOfPCConfig
#define Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()           Eth_30_Tc3xx_ConfigDataPtr->MulticastBucketCountersOfPCConfig
#define Eth_30_Tc3xx_GetOptCalloutsOfPCConfig()                       Eth_30_Tc3xx_ConfigDataPtr->OptCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->PromiscuousModeCounterOfPCConfig
#define Eth_30_Tc3xx_GetQosHandlingOfPCConfig()                       Eth_30_Tc3xx_ConfigDataPtr->QosHandlingOfPCConfig
#define Eth_30_Tc3xx_GetRegDataOfPCConfig()                           Eth_30_Tc3xx_ConfigDataPtr->RegDataOfPCConfig
#define Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->RxBufferHandlingOfPCConfig
#define Eth_30_Tc3xx_GetRxBufferOfPCConfig()                          Eth_30_Tc3xx_ConfigDataPtr->RxBufferOfPCConfig
#define Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->RxDescrHandlingOfPCConfig
#define Eth_30_Tc3xx_GetRxDescrOfPCConfig()                           Eth_30_Tc3xx_ConfigDataPtr->RxDescrOfPCConfig
#define Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->RxDescrRingProcOfPCConfig
#define Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->RxDescrStateOfPCConfig
#define Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->RxTsContextStackOfPCConfig
#define Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()               Eth_30_Tc3xx_ConfigDataPtr->RxTsContextStackPosOfPCConfig
#define Eth_30_Tc3xx_GetRxTxNotificationCalloutsOfPCConfig()          Eth_30_Tc3xx_ConfigDataPtr->RxTxNotificationCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetShaperAvailableOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->ShaperAvailableOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfActiveMacAddressOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfActiveMacAddressOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig()                     Eth_30_Tc3xx_ConfigDataPtr->SizeOfEthCtrlOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->SizeOfEthCtrlTc3xxOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfEthSwtIfcOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->SizeOfEthSwtIfcOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfInitialMacAddressOfPCConfig()           Eth_30_Tc3xx_ConfigDataPtr->SizeOfInitialMacAddressOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfIsrInfosOfPCConfig()                    Eth_30_Tc3xx_ConfigDataPtr->SizeOfIsrInfosOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfIsrIrqEventFuncsOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfIsrIrqEventFuncsOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfMulticastBucketCountersOfPCConfig()     Eth_30_Tc3xx_ConfigDataPtr->SizeOfMulticastBucketCountersOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfOptCalloutsOfPCConfig()                 Eth_30_Tc3xx_ConfigDataPtr->SizeOfOptCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfQosHandlingOfPCConfig()                 Eth_30_Tc3xx_ConfigDataPtr->SizeOfQosHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRegDataOfPCConfig()                     Eth_30_Tc3xx_ConfigDataPtr->SizeOfRegDataOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxBufferHandlingOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxBufferHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxBufferOfPCConfig()                    Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxBufferOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxDescrHandlingOfPCConfig()             Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxDescrHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxDescrOfPCConfig()                     Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxDescrOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxDescrRingProcOfPCConfig()             Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxDescrRingProcOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxDescrStateOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxDescrStateOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxTsContextStackOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxTsContextStackOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxTsContextStackPosOfPCConfig()         Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxTsContextStackPosOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfRxTxNotificationCalloutsOfPCConfig()    Eth_30_Tc3xx_ConfigDataPtr->SizeOfRxTxNotificationCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfShaperAvailableOfPCConfig()             Eth_30_Tc3xx_ConfigDataPtr->SizeOfShaperAvailableOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTimeHandlingOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->SizeOfTimeHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTsHandlingOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->SizeOfTsHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxBufferDataOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxBufferDataOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxBufferFreeElemNumOfPCConfig()         Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxBufferFreeElemNumOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxBufferHandlingOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxBufferHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxBufferOfPCConfig()                    Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxBufferOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxBufferStateOfPCConfig()               Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxBufferStateOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxDescrHandlingOfPCConfig()             Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxDescrHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxDescrOfPCConfig()                     Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxDescrOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxDescrRingProcOfPCConfig()             Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxDescrRingProcOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxDescrStateOfPCConfig()                Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxDescrStateOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfTxTsContextOfPCConfig()                 Eth_30_Tc3xx_ConfigDataPtr->SizeOfTxTsContextOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfUserInitCalloutsOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->SizeOfUserInitCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfVlanIdBasedQueuingHandlingOfPCConfig()  Eth_30_Tc3xx_ConfigDataPtr->SizeOfVlanIdBasedQueuingHandlingOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfVlanIdRxDescrRingMapOfPCConfig()        Eth_30_Tc3xx_ConfigDataPtr->SizeOfVlanIdRxDescrRingMapOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfVlanIdTxDescrRingMapOfPCConfig()        Eth_30_Tc3xx_ConfigDataPtr->SizeOfVlanIdTxDescrRingMapOfPCConfig
#define Eth_30_Tc3xx_GetSizeOfVlanPrioTxDescrRingMapOfPCConfig()      Eth_30_Tc3xx_ConfigDataPtr->SizeOfVlanPrioTxDescrRingMapOfPCConfig
#define Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->TimeHandlingOfPCConfig
#define Eth_30_Tc3xx_GetTsHandlingOfPCConfig()                        Eth_30_Tc3xx_ConfigDataPtr->TsHandlingOfPCConfig
#define Eth_30_Tc3xx_GetTxBufferDataOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->TxBufferDataOfPCConfig
#define Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()               Eth_30_Tc3xx_ConfigDataPtr->TxBufferFreeElemNumOfPCConfig
#define Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->TxBufferHandlingOfPCConfig
#define Eth_30_Tc3xx_GetTxBufferOfPCConfig()                          Eth_30_Tc3xx_ConfigDataPtr->TxBufferOfPCConfig
#define Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()                     Eth_30_Tc3xx_ConfigDataPtr->TxBufferStateOfPCConfig
#define Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->TxDescrHandlingOfPCConfig
#define Eth_30_Tc3xx_GetTxDescrOfPCConfig()                           Eth_30_Tc3xx_ConfigDataPtr->TxDescrOfPCConfig
#define Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()                   Eth_30_Tc3xx_ConfigDataPtr->TxDescrRingProcOfPCConfig
#define Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()                      Eth_30_Tc3xx_ConfigDataPtr->TxDescrStateOfPCConfig
#define Eth_30_Tc3xx_GetTxTsContextOfPCConfig()                       Eth_30_Tc3xx_ConfigDataPtr->TxTsContextOfPCConfig
#define Eth_30_Tc3xx_GetUserInitCalloutsOfPCConfig()                  Eth_30_Tc3xx_ConfigDataPtr->UserInitCalloutsOfPCConfig
#define Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()        Eth_30_Tc3xx_ConfigDataPtr->VlanIdBasedQueuingHandlingOfPCConfig
#define Eth_30_Tc3xx_GetVlanIdRxDescrRingMapOfPCConfig()              Eth_30_Tc3xx_ConfigDataPtr->VlanIdRxDescrRingMapOfPCConfig
#define Eth_30_Tc3xx_GetVlanIdTxDescrRingMapOfPCConfig()              Eth_30_Tc3xx_ConfigDataPtr->VlanIdTxDescrRingMapOfPCConfig
#define Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapOfPCConfig()            Eth_30_Tc3xx_ConfigDataPtr->VlanPrioTxDescrRingMapOfPCConfig
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCGetDuplicatedRootDataMacros  Eth_30_Tc3xx Get Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated root data elements.
  \{
*/ 
#define Eth_30_Tc3xx_GetSizeOfEthCtrlStateOfPCConfig()                Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig()  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrlState */
#define Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxStateOfPCConfig()           Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxOfPCConfig()  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrlTc3xxState */
#define Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterOfPCConfig()          Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig()  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthMeasDataCounter */
#define Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterResetOfPCConfig()     Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig()  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthMeasDataCounterReset */
#define Eth_30_Tc3xx_GetSizeOfPromiscuousModeCounterOfPCConfig()      Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig()  /**< the number of accomplishable value elements in Eth_30_Tc3xx_PromiscuousModeCounter */
/** 
  \}
*/ 

  /* PRQA L:MACROS_3453 */
/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL ACCESS FUNCTION MACROS
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTION PROTOTYPES
**********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetDataInlineFunctionPrototypes  Get Data Inline Function Prototypes
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAutosarRtmRegBaseAddrOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDemEAccessEventIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_FqtssEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFqtssEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddressEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddressStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsIpChecksumOffloadingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrInfosEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrInfosStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_NvMBlockIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsProtocolChecksumOffloadingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsQosEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQosHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegDataEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegDataStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxInterruptEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TimeSynEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TrcvSpeedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTsHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ModeType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsArmPpsOnTimeEnabledOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthCtrlMiiInterfaceOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPinRoutingOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_RxStatsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthAdaptBufferLengthFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthPrepareTxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthProcessRxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthProcessTxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthRxFinishedIndicationFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthTxFinishedIndicationFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddress(Eth_30_Tc3xx_InitialMacAddressIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncsEndIdxOfIsrInfos(Eth_30_Tc3xx_IsrInfosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncsStartIdxOfIsrInfos(Eth_30_Tc3xx_IsrInfosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IrqEventFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncs(Eth_30_Tc3xx_IsrIrqEventFuncsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserRxBufWarnLvlCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(Eth_30_Tc3xx_OptCalloutsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PromiscuousModeCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetShaperAvailableEndIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetShaperAvailableStartIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapEndIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapStartIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AccessModeOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAccessModeOfRegData(Eth_30_Tc3xx_RegDataIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_OffsetOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetOffsetOfRegData(Eth_30_Tc3xx_RegDataIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ValueOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetValueOfRegData(Eth_30_Tc3xx_RegDataIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedLastSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrNumOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMaxFrameSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferEndIdxOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SegNumOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetUnalignedSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescriptorType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescr(Eth_30_Tc3xx_RxDescrIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStateEndIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStateStartIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfRxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RingIdxOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxIndicationCalloutOfRxTxNotificationCallouts(Eth_30_Tc3xx_RxTxNotificationCalloutsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxConfirmationCalloutOfRxTxNotificationCallouts(Eth_30_Tc3xx_RxTxNotificationCalloutsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsShaperAvailable(Eth_30_Tc3xx_ShaperAvailableIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_TimeStampType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_TimeStampType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RateRatioOfTimeHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackEndIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackPosIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackStartIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TimeHandlingIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTimeHandlingIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxTsContextEndIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxTsContextStartIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LengthOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLengthOfTxBufferData(Eth_30_Tc3xx_TxBufferDataIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_StartPosOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetStartPosOfTxBufferData(Eth_30_Tc3xx_TxBufferDataIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedSegSizeOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_BufferNumOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrNumOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrNumOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMaxBufferLenOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferDataEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferDataStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferFreeElemNumIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_BusyOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBusyOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsRequestedOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTsRequestedOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescriptorType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescr(Eth_30_Tc3xx_TxDescrIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStateEndIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStateStartIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_FreePosOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxReadyOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrIdxOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RingIdxOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPostInitUserCalloutOfUserInitCallouts(Eth_30_Tc3xx_UserInitCalloutsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPreInitUserCalloutOfUserInitCallouts(Eth_30_Tc3xx_UserInitCalloutsIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQueueIndexOfVlanIdRxDescrRingMap(Eth_30_Tc3xx_VlanIdRxDescrRingMapIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdOfVlanIdRxDescrRingMap(Eth_30_Tc3xx_VlanIdRxDescrRingMapIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQueueIndexOfVlanIdTxDescrRingMap(Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdOfVlanIdTxDescrRingMap(Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMap(Eth_30_Tc3xx_VlanPrioTxDescrRingMapIterType Index);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetDeduplicatedInlineFunctionPrototypes  Get Deduplicated Inline Function Prototypes
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtIfcUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsIsrInfosUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsQosHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRegDataUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTsHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsVlanIdBasedQueuingHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfActiveMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfActiveMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlTc3xxStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthMeasDataCounterResetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterReset(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthSwtIfcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfInitialMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfInitialMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfIsrInfos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfIsrIrqEventFuncsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfIsrIrqEventFuncs(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfMulticastBucketCountersType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfMulticastBucketCounters(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfOptCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfOptCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfPromiscuousModeCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfPromiscuousModeCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTsContextStack(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTsContextStackPosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTsContextStackPos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTxNotificationCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTxNotificationCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfShaperAvailableType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfShaperAvailable(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTimeHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferFreeElemNumType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferFreeElemNum(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxTsContext(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfUserInitCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfUserInitCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdRxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanPrioTxDescrRingMap(void);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCSetDataInlineFunctionPrototypes  Set Data Inline Function Prototypes
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index, Eth_30_Tc3xx_ActiveMacAddressType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_ModeType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_RegBaseAddrType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index, Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index, Eth_RxStatsType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index, Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index, Eth_30_Tc3xx_MulticastBucketCountersType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index, Eth_30_Tc3xx_PromiscuousModeCounterType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index, Eth_30_Tc3xx_RxBufferType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxDescr(Eth_30_Tc3xx_RxDescrIterType Index, Eth_30_Tc3xx_RxDescriptorType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index, Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index, Eth_30_Tc3xx_MappedBufferOfRxDescrStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index, Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index, Eth_30_Tc3xx_RingIdxOfRxTsContextStackType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index, Eth_30_Tc3xx_RxTsContextStackPosType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_TimeStampType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_TimeStampType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_30_Tc3xx_RateRatioOfTimeHandlingType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index, Eth_30_Tc3xx_TxBufferType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index, Eth_30_Tc3xx_TxBufferFreeElemNumType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetBusyOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_BusyOfTxBufferStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_TsRequestedOfTxBufferStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxDescr(Eth_30_Tc3xx_TxDescrIterType Index, Eth_30_Tc3xx_TxDescriptorType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index, Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index, Eth_30_Tc3xx_FreePosOfTxDescrRingProcType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index, Eth_30_Tc3xx_MappedBufferOfTxDescrStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index, Eth_30_Tc3xx_TxReadyOfTxDescrStateType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index, Eth_30_Tc3xx_DescrIdxOfTxTsContextType Value);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index, Eth_30_Tc3xx_RingIdxOfTxTsContextType Value);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetAddressOfDataInlineFunctionPrototypes  Get Address Of Data Inline Function Prototypes
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CtrlModeOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxStatsOfEthCtrlTc3xxStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PromiscuousModeCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxDescr(Eth_30_Tc3xx_RxDescrIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfRxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LatestCorrTimeOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LatestHwTimeOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RateRatioOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UlTxConfStateOfTxBufferStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxDescr(Eth_30_Tc3xx_TxDescrIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfTxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxReadyOfTxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCHasInlineFunctionPrototypes  Has Inline Function Prototypes
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAutosarRtmRegBaseAddrOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDemEAccessEventIdOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasFqtssEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIpChecksumOffloadingEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLoopCyclesOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMiiLoopCyclesOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMultiQueueConfigEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasNvMBlockIdOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasProtectedAreaIdOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasProtocolChecksumOffloadingEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasResetLoopCyclesOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxInterruptEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCalloutsIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeSynEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTrcvSpeedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandlingIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingEndIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingStartIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxInterruptEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedFrameQueuingEnabledOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingIdxOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingUsedOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCtrlModeOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPendingRxEventsOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPendingTxEventsOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegBaseAddrOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAmountOfRxQueuesOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAmountOfTxQueuesOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasArmPpsOnTimeEnabledOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCsrClockRangeOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlMiiInterfaceOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPinRoutingOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasReadMiiResultOfEthCtrlTc3xxState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxStatsOfEthCtrlTc3xxState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffRxBuffOfEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffTxBuffOfEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasWarnFullRxBuffOfEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterReset(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffRxBuffResetOfEthMeasDataCounterReset(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthAdaptBufferLengthOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthPrepareTxFrameOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthProcessRxFrameOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthProcessTxFrameOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthRxFinishedIndicationOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthTxFinishedIndicationOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsEndIdxOfIsrInfos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsStartIdxOfIsrInfos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncs(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCounters(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOptCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufWarnLvlCalloutOfOptCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPromiscuousModeCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableEndIdxOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableStartIdxOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingIdxOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapEndIdxOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapStartIdxOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAccessModeOfRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOffsetOfRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasValueOfRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedLastSegSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedSegSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrNumOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMaxFrameSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferEndIdxOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferStartIdxOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSegNumOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUnalignedSegSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrEndIdxOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProcIdxOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStartIdxOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateEndIdxOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateStartIdxOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCurProcPosOfRxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMappedBufferOfRxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStack(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrIdxOfRxTsContextStack(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRingIdxOfRxTsContextStack(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxIndicationCalloutOfRxTxNotificationCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxConfirmationCalloutOfRxTxNotificationCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailable(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfActiveMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrl(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xx(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterReset(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthSwtIfc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfInitialMacAddress(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrInfos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrIrqEventFuncs(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfMulticastBucketCounters(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfOptCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfPromiscuousModeCounter(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfQosHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRegData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStack(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackPos(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTxNotificationCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfShaperAvailable(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferFreeElemNum(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxTsContext(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfUserInitCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdRxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanPrioTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLatestCorrTimeOfTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLatestHwTimeOfTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRateRatioOfTimeHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackEndIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPosIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackStartIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandlingIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextEndIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextStartIdxOfTsHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBuffer(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLengthOfTxBufferData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasStartPosOfTxBufferData(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNum(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedSegSizeOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasBufferNumOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrNumOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMaxBufferLenOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataEndIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataStartIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferEndIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNumIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStartIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateEndIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateStartIdxOfTxBufferHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasBusyOfTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsRequestedOfTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUlTxConfStateOfTxBufferState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescr(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrEndIdxOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProcIdxOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStartIdxOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateEndIdxOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateStartIdxOfTxDescrHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCurProcPosOfTxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasFreePosOfTxDescrRingProc(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMappedBufferOfTxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxReadyOfTxDescrState(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContext(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrIdxOfTxTsContext(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRingIdxOfTxTsContext(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUserInitCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPostInitUserCalloutOfUserInitCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPreInitUserCalloutOfUserInitCallouts(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQueueIndexOfVlanIdRxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdOfVlanIdRxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQueueIndexOfVlanIdTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdOfVlanIdTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMap(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterResetOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOptCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPromiscuousModeCounterOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPosOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfActiveMacAddressOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterResetOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthSwtIfcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfInitialMacAddressOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrInfosOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrIrqEventFuncsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfMulticastBucketCountersOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfOptCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfPromiscuousModeCounterOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfQosHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRegDataOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrRingProcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackPosOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTxNotificationCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfShaperAvailableOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTimeHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTsHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferDataOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferFreeElemNumOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrRingProcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxTsContextOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfUserInitCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdBasedQueuingHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdRxDescrRingMapOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdTxDescrRingMapOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanPrioTxDescrRingMapOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNumOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProcOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUserInitCalloutsOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapOfPCConfig(void);
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapOfPCConfig(void);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCIncrementInlineFunctionPrototypes  Increment Inline Function Prototypes
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCDecrementInlineFunctionPrototypes  Decrement Inline Function Prototypes
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index);
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


# if !defined(ETH_30_TC3XX_UNIT_TEST)
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL INLINE FUNCTIONS
**********************************************************************************************************************/
#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetDataInlineFunctions  Eth_30_Tc3xx Get Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to read CONST and VAR data.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ActiveMacAddressType) Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddressEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].ActiveMacAddressEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetActiveMacAddressStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].ActiveMacAddressStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAutosarRtmRegBaseAddrOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegBaseAddrType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].AutosarRtmRegBaseAddrOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDemEAccessEventIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].DemEAccessEventIdOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].EthSwtIfcIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_FqtssEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsFqtssEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_FqtssEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].FqtssEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddressEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].InitialMacAddressEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddressStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].InitialMacAddressStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsIpChecksumOffloadingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].IpChecksumOffloadingEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrInfosEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].IsrInfosEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrInfosStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].IsrInfosStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_LoopCyclesOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].LoopCyclesOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMiiLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].MiiLoopCyclesOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsMultiQueueConfigEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].MultiQueueConfigEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCountersEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].MulticastBucketCountersEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCountersStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].MulticastBucketCountersStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_NvMBlockIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetNvMBlockIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_NvMBlockIdOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].NvMBlockIdOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetProtectedAreaIdOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].ProtectedAreaIdOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsProtocolChecksumOffloadingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].ProtocolChecksumOffloadingEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsQosEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_QosEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].QosEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQosHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].QosHandlingIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegDataEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegDataEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RegDataEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegDataStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegDataStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RegDataStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetResetLoopCyclesOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].ResetLoopCyclesOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxBufferHandlingEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxBufferHandlingStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxDescrHandlingEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxDescrHandlingStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRxInterruptEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxInterruptEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTxNotificationCalloutsIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].RxTxNotificationCalloutsIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TimeSynEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTimeSynEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TimeSynEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TimeSynEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TrcvSpeedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTrcvSpeedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TrcvSpeedOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TrcvSpeedOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTsHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TsHandlingIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TsHandlingIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TxBufferHandlingIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingEndIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TxDescrHandlingEndIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingStartIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TxDescrHandlingStartIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTxInterruptEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].TxInterruptEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsVlanIdBasedFrameQueuingEnabledOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrlType) ((Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].VlanIdBasedFrameQueuingEnabledOfEthCtrl) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType) Eth_30_Tc3xx_GetEthCtrlOfPCConfig()[(Index)].VlanIdBasedQueuingHandlingIdxOfEthCtrl;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_ModeType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_ModeType) Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].CtrlModeOfEthCtrlState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType) Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingRxEventsOfEthCtrlState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType) Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingTxEventsOfEthCtrlState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegBaseAddrType) Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].RegBaseAddrOfEthCtrlState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAmountOfRxQueuesOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].AmountOfRxQueuesOfEthCtrlTc3xx;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAmountOfTxQueuesOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].AmountOfTxQueuesOfEthCtrlTc3xx;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsArmPpsOnTimeEnabledOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xxType) ((Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].ArmPpsOnTimeEnabledOfEthCtrlTc3xx) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCsrClockRangeOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].CsrClockRangeOfEthCtrlTc3xx;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthCtrlMiiInterfaceOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].EthCtrlMiiInterfaceOfEthCtrlTc3xx;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPinRoutingOfEthCtrlTc3xx(Eth_30_Tc3xx_EthCtrlTc3xxIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig()[(Index)].PinRoutingOfEthCtrlTc3xx;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType) Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].ReadMiiResultOfEthCtrlTc3xxState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_RxStatsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].RxStatsOfEthCtrlTc3xxState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType) Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffRxBuffOfEthMeasDataCounter;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType) Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffTxBuffOfEthMeasDataCounter;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType) Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].WarnFullRxBuffOfEthMeasDataCounter;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType) Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()[(Index)].DropInsuffRxBuffResetOfEthMeasDataCounterReset;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthAdaptBufferLengthFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthAdaptBufferLengthOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthAdaptBufferLengthFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthAdaptBufferLengthOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthPrepareTxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthPrepareTxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthPrepareTxFrameFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthPrepareTxFrameOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthProcessRxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthProcessRxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthProcessRxFrameFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthProcessRxFrameOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthProcessTxFrameFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthProcessTxFrameOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthProcessTxFrameFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthProcessTxFrameOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthRxFinishedIndicationFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthRxFinishedIndicationOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthRxFinishedIndicationFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthRxFinishedIndicationOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtEthTxFinishedIndicationFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetEthTxFinishedIndicationOfEthSwtIfc(Eth_30_Tc3xx_EthSwtIfcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtEthTxFinishedIndicationFctPtrType) Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig()[(Index)].EthTxFinishedIndicationOfEthSwtIfc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_InitialMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetInitialMacAddress(Eth_30_Tc3xx_InitialMacAddressIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_InitialMacAddressType) Eth_30_Tc3xx_GetInitialMacAddressOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncsEndIdxOfIsrInfos(Eth_30_Tc3xx_IsrInfosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfosType) Eth_30_Tc3xx_GetIsrInfosOfPCConfig()[(Index)].IsrIrqEventFuncsEndIdxOfIsrInfos;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncsStartIdxOfIsrInfos(Eth_30_Tc3xx_IsrInfosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfosType) Eth_30_Tc3xx_GetIsrInfosOfPCConfig()[(Index)].IsrIrqEventFuncsStartIdxOfIsrInfos;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IrqEventFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetIsrIrqEventFuncs(Eth_30_Tc3xx_IsrIrqEventFuncsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IrqEventFctPtrType) Eth_30_Tc3xx_GetIsrIrqEventFuncsOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MulticastBucketCountersType) Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserRxBufWarnLvlCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufWarnLvlCalloutOfOptCallouts(Eth_30_Tc3xx_OptCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UserRxBufWarnLvlCalloutFctPtrType) Eth_30_Tc3xx_GetOptCalloutsOfPCConfig()[(Index)].RxBufWarnLvlCalloutOfOptCallouts;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PromiscuousModeCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PromiscuousModeCounterType) Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetShaperAvailableEndIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandlingType) Eth_30_Tc3xx_GetQosHandlingOfPCConfig()[(Index)].ShaperAvailableEndIdxOfQosHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetShaperAvailableStartIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandlingType) Eth_30_Tc3xx_GetQosHandlingOfPCConfig()[(Index)].ShaperAvailableStartIdxOfQosHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandlingType) Eth_30_Tc3xx_GetQosHandlingOfPCConfig()[(Index)].TxDescrHandlingIdxOfQosHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapEndIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandlingType) Eth_30_Tc3xx_GetQosHandlingOfPCConfig()[(Index)].VlanPrioTxDescrRingMapEndIdxOfQosHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapStartIdxOfQosHandling(Eth_30_Tc3xx_QosHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType) Eth_30_Tc3xx_GetQosHandlingOfPCConfig()[(Index)].VlanPrioTxDescrRingMapStartIdxOfQosHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AccessModeOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAccessModeOfRegData(Eth_30_Tc3xx_RegDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AccessModeOfRegDataType) Eth_30_Tc3xx_GetRegDataOfPCConfig()[(Index)].AccessModeOfRegData;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_OffsetOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetOffsetOfRegData(Eth_30_Tc3xx_RegDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_OffsetOfRegDataType) Eth_30_Tc3xx_GetRegDataOfPCConfig()[(Index)].OffsetOfRegData;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ValueOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetValueOfRegData(Eth_30_Tc3xx_RegDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ValueOfRegDataType) Eth_30_Tc3xx_GetRegDataOfPCConfig()[(Index)].ValueOfRegData;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferType) Eth_30_Tc3xx_GetRxBufferOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedLastSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].AlignedLastSegSizeOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].AlignedSegSizeOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrNumOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].DescrNumOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMaxFrameSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].MaxFrameSizeOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferEndIdxOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].RxBufferEndIdxOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxBufferStartIdxOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].RxBufferStartIdxOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SegNumOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSegNumOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SegNumOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].SegNumOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetUnalignedSegSizeOfRxBufferHandling(Eth_30_Tc3xx_RxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandlingType) Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig()[(Index)].UnalignedSegSizeOfRxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescriptorType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescr(Eth_30_Tc3xx_RxDescrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return Eth_30_Tc3xx_GetRxDescrOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrEndIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType) Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()[(Index)].RxDescrEndIdxOfRxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrRingProcIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType) Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()[(Index)].RxDescrRingProcIdxOfRxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStartIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType) Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()[(Index)].RxDescrStartIdxOfRxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStateEndIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandlingType) Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()[(Index)].RxDescrStateEndIdxOfRxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxDescrStateStartIdxOfRxDescrHandling(Eth_30_Tc3xx_RxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandlingType) Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig()[(Index)].RxDescrStateStartIdxOfRxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType) Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfRxDescrRingProc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfRxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MappedBufferOfRxDescrStateType) Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()[(Index)].MappedBufferOfRxDescrState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType) Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].DescrIdxOfRxTsContextStack;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RingIdxOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RingIdxOfRxTsContextStackType) Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].RingIdxOfRxTsContextStack;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTsContextStackPosType) Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxIndicationCalloutOfRxTxNotificationCallouts(Eth_30_Tc3xx_RxTxNotificationCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType) Eth_30_Tc3xx_GetRxTxNotificationCalloutsOfPCConfig()[(Index)].RxIndicationCalloutOfRxTxNotificationCallouts;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxConfirmationCalloutOfRxTxNotificationCallouts(Eth_30_Tc3xx_RxTxNotificationCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType) Eth_30_Tc3xx_GetRxTxNotificationCalloutsOfPCConfig()[(Index)].TxConfirmationCalloutOfRxTxNotificationCallouts;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ShaperAvailableType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsShaperAvailable(Eth_30_Tc3xx_ShaperAvailableIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ShaperAvailableType) ((Eth_30_Tc3xx_GetShaperAvailableOfPCConfig()[(Index)]) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_TimeStampType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestCorrTimeOfTimeHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_TimeStampType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestHwTimeOfTimeHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RateRatioOfTimeHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RateRatioOfTimeHandlingType) Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].RateRatioOfTimeHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackEndIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].RxTsContextStackEndIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackPosIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].RxTsContextStackPosIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRxTsContextStackStartIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].RxTsContextStackStartIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TimeHandlingIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTimeHandlingIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TimeHandlingIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].TimeHandlingIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxTsContextEndIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].TxTsContextEndIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxTsContextStartIdxOfTsHandling(Eth_30_Tc3xx_TsHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandlingType) Eth_30_Tc3xx_GetTsHandlingOfPCConfig()[(Index)].TxTsContextStartIdxOfTsHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferType) Eth_30_Tc3xx_GetTxBufferOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LengthOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetLengthOfTxBufferData(Eth_30_Tc3xx_TxBufferDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_LengthOfTxBufferDataType) Eth_30_Tc3xx_GetTxBufferDataOfPCConfig()[(Index)].LengthOfTxBufferData;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_StartPosOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetStartPosOfTxBufferData(Eth_30_Tc3xx_TxBufferDataIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_StartPosOfTxBufferDataType) Eth_30_Tc3xx_GetTxBufferDataOfPCConfig()[(Index)].StartPosOfTxBufferData;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferFreeElemNumType) Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAlignedSegSizeOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].AlignedSegSizeOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_BufferNumOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetBufferNumOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_BufferNumOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].BufferNumOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrNumOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrNumOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DescrNumOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].DescrNumOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMaxBufferLenOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].MaxBufferLenOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferDataEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferDataEndIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferDataStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferDataStartIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferEndIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferFreeElemNumIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferFreeElemNumIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferStartIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStateEndIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferStateEndIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxBufferStateStartIdxOfTxBufferHandling(Eth_30_Tc3xx_TxBufferHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType) Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig()[(Index)].TxBufferStateStartIdxOfTxBufferHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_BusyOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsBusyOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_BusyOfTxBufferStateType) ((Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].BusyOfTxBufferState) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsRequestedOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTsRequestedOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TsRequestedOfTxBufferStateType) ((Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].TsRequestedOfTxBufferState) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType) Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].UlTxConfStateOfTxBufferState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescriptorType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescr(Eth_30_Tc3xx_TxDescrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return Eth_30_Tc3xx_GetTxDescrOfPCConfig()[(Index)];
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrEndIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandlingType) Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()[(Index)].TxDescrEndIdxOfTxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrRingProcIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType) Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()[(Index)].TxDescrRingProcIdxOfTxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStartIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType) Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()[(Index)].TxDescrStartIdxOfTxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStateEndIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandlingType) Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()[(Index)].TxDescrStateEndIdxOfTxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrStateStartIdxOfTxDescrHandling(Eth_30_Tc3xx_TxDescrHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandlingType) Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig()[(Index)].TxDescrStateStartIdxOfTxDescrHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType) Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfTxDescrRingProc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_FreePosOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_FreePosOfTxDescrRingProcType) Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].FreePosOfTxDescrRingProc;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MappedBufferOfTxDescrStateType) Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].MappedBufferOfTxDescrState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxReadyOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxReadyOfTxDescrStateType) Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].TxReadyOfTxDescrState;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DescrIdxOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DescrIdxOfTxTsContextType) Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].DescrIdxOfTxTsContext;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RingIdxOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RingIdxOfTxTsContextType) Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].RingIdxOfTxTsContext;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPostInitUserCalloutOfUserInitCallouts(Eth_30_Tc3xx_UserInitCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType) Eth_30_Tc3xx_GetUserInitCalloutsOfPCConfig()[(Index)].PostInitUserCalloutOfUserInitCallouts;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetPreInitUserCalloutOfUserInitCallouts(Eth_30_Tc3xx_UserInitCalloutsIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType) Eth_30_Tc3xx_GetUserInitCalloutsOfPCConfig()[(Index)].PreInitUserCalloutOfUserInitCallouts;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()[(Index)].TxDescrHandlingIdxOfVlanIdBasedQueuingHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()[(Index)].VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()[(Index)].VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()[(Index)].VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig()[(Index)].VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQueueIndexOfVlanIdRxDescrRingMap(Eth_30_Tc3xx_VlanIdRxDescrRingMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMapType) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapOfPCConfig()[(Index)].QueueIndexOfVlanIdRxDescrRingMap;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdOfVlanIdRxDescrRingMap(Eth_30_Tc3xx_VlanIdRxDescrRingMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMapType) Eth_30_Tc3xx_GetVlanIdRxDescrRingMapOfPCConfig()[(Index)].VlanIdOfVlanIdRxDescrRingMap;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetQueueIndexOfVlanIdTxDescrRingMap(Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMapType) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapOfPCConfig()[(Index)].QueueIndexOfVlanIdTxDescrRingMap;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanIdOfVlanIdTxDescrRingMap(Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMapType) Eth_30_Tc3xx_GetVlanIdTxDescrRingMapOfPCConfig()[(Index)].VlanIdOfVlanIdTxDescrRingMap;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanPrioTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMap(Eth_30_Tc3xx_VlanPrioTxDescrRingMapIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanPrioTxDescrRingMapType) Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapOfPCConfig()[(Index)];
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetDeduplicatedInlineFunctions  Eth_30_Tc3xx Get Deduplicated Inline Functions (PRE_COMPILE)
  \brief  These inline functions  can be used to read deduplicated data elements.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_EthSwtIfcUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsEthSwtIfcUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_EthSwtIfcUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetEthSwtIfcIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_ETHSWTIFCIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_IsrInfosUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsIsrInfosUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_IsrInfosUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetIsrInfosStartIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_ISRINFOSSTARTIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_QosHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsQosHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_QosHandlingUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetQosHandlingIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_QOSHANDLINGIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegDataUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsRegDataUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegDataUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetRegDataStartIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_REGDATASTARTIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TsHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsTsHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TsHandlingUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetTsHandlingIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_TSHANDLINGIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingUsedOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IsVlanIdBasedQueuingHandlingUsedOfEthCtrl(Eth_30_Tc3xx_EthCtrlIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_VlanIdBasedQueuingHandlingUsedOfEthCtrlType) (((boolean)(Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingIdxOfEthCtrl(Index) != ETH_30_TC3XX_NO_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL)) != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfActiveMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfActiveMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfActiveMacAddressType) Eth_30_Tc3xx_GetSizeOfActiveMacAddressOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthCtrlType) Eth_30_Tc3xx_GetSizeOfEthCtrlOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthCtrlStateType) Eth_30_Tc3xx_GetSizeOfEthCtrlStateOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlTc3xxType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthCtrlTc3xxType) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthCtrlTc3xxStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthCtrlTc3xxStateType) Eth_30_Tc3xx_GetSizeOfEthCtrlTc3xxStateOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthMeasDataCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthMeasDataCounterType) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthMeasDataCounterResetType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterReset(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthMeasDataCounterResetType) Eth_30_Tc3xx_GetSizeOfEthMeasDataCounterResetOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfEthSwtIfcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfEthSwtIfcType) Eth_30_Tc3xx_GetSizeOfEthSwtIfcOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfInitialMacAddressType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfInitialMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfInitialMacAddressType) Eth_30_Tc3xx_GetSizeOfInitialMacAddressOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfIsrInfosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfIsrInfos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfIsrInfosType) Eth_30_Tc3xx_GetSizeOfIsrInfosOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfIsrIrqEventFuncsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfIsrIrqEventFuncs(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfIsrIrqEventFuncsType) Eth_30_Tc3xx_GetSizeOfIsrIrqEventFuncsOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfMulticastBucketCountersType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfMulticastBucketCounters(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfMulticastBucketCountersType) Eth_30_Tc3xx_GetSizeOfMulticastBucketCountersOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfOptCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfOptCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfOptCalloutsType) Eth_30_Tc3xx_GetSizeOfOptCalloutsOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfPromiscuousModeCounterType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfPromiscuousModeCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfPromiscuousModeCounterType) Eth_30_Tc3xx_GetSizeOfPromiscuousModeCounterOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfQosHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfQosHandlingType) Eth_30_Tc3xx_GetSizeOfQosHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRegDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRegDataType) Eth_30_Tc3xx_GetSizeOfRegDataOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxBufferType) Eth_30_Tc3xx_GetSizeOfRxBufferOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxBufferHandlingType) Eth_30_Tc3xx_GetSizeOfRxBufferHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxDescrType) Eth_30_Tc3xx_GetSizeOfRxDescrOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxDescrHandlingType) Eth_30_Tc3xx_GetSizeOfRxDescrHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxDescrRingProcType) Eth_30_Tc3xx_GetSizeOfRxDescrRingProcOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxDescrStateType) Eth_30_Tc3xx_GetSizeOfRxDescrStateOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTsContextStackType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTsContextStack(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxTsContextStackType) Eth_30_Tc3xx_GetSizeOfRxTsContextStackOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTsContextStackPosType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTsContextStackPos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxTsContextStackPosType) Eth_30_Tc3xx_GetSizeOfRxTsContextStackPosOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfRxTxNotificationCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfRxTxNotificationCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfRxTxNotificationCalloutsType) Eth_30_Tc3xx_GetSizeOfRxTxNotificationCalloutsOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfShaperAvailableType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfShaperAvailable(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfShaperAvailableType) Eth_30_Tc3xx_GetSizeOfShaperAvailableOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTimeHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTimeHandlingType) Eth_30_Tc3xx_GetSizeOfTimeHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTsHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTsHandlingType) Eth_30_Tc3xx_GetSizeOfTsHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxBufferType) Eth_30_Tc3xx_GetSizeOfTxBufferOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferDataType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxBufferDataType) Eth_30_Tc3xx_GetSizeOfTxBufferDataOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferFreeElemNumType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferFreeElemNum(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxBufferFreeElemNumType) Eth_30_Tc3xx_GetSizeOfTxBufferFreeElemNumOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxBufferHandlingType) Eth_30_Tc3xx_GetSizeOfTxBufferHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxBufferStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxBufferStateType) Eth_30_Tc3xx_GetSizeOfTxBufferStateOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxDescrType) Eth_30_Tc3xx_GetSizeOfTxDescrOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxDescrHandlingType) Eth_30_Tc3xx_GetSizeOfTxDescrHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrRingProcType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxDescrRingProcType) Eth_30_Tc3xx_GetSizeOfTxDescrRingProcOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxDescrStateType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxDescrStateType) Eth_30_Tc3xx_GetSizeOfTxDescrStateOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfTxTsContextType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfTxTsContext(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfTxTsContextType) Eth_30_Tc3xx_GetSizeOfTxTsContextOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfUserInitCalloutsType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfUserInitCalloutsType) Eth_30_Tc3xx_GetSizeOfUserInitCalloutsOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandlingType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandlingType) Eth_30_Tc3xx_GetSizeOfVlanIdBasedQueuingHandlingOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdRxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMapType) Eth_30_Tc3xx_GetSizeOfVlanIdRxDescrRingMapOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanIdTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMapType) Eth_30_Tc3xx_GetSizeOfVlanIdTxDescrRingMapOfPCConfig();
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMapType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetSizeOfVlanPrioTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMapType) Eth_30_Tc3xx_GetSizeOfVlanPrioTxDescrRingMapOfPCConfig();
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCSetDataInlineFunctions  Eth_30_Tc3xx Set Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to write data.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index, Eth_30_Tc3xx_ActiveMacAddressType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_ModeType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].CtrlModeOfEthCtrlState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingRxEventsOfEthCtrlState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingTxEventsOfEthCtrlState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index, Eth_30_Tc3xx_RegBaseAddrType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].RegBaseAddrOfEthCtrlState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index, Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].ReadMiiResultOfEthCtrlTc3xxState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index, Eth_RxStatsType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].RxStatsOfEthCtrlTc3xxState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffRxBuffOfEthMeasDataCounter = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffTxBuffOfEthMeasDataCounter = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index, Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].WarnFullRxBuffOfEthMeasDataCounter = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index, Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()[(Index)].DropInsuffRxBuffResetOfEthMeasDataCounterReset = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index, Eth_30_Tc3xx_MulticastBucketCountersType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index, Eth_30_Tc3xx_PromiscuousModeCounterType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index, Eth_30_Tc3xx_RxBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxBufferOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxDescr(Eth_30_Tc3xx_RxDescrIterType Index, Eth_30_Tc3xx_RxDescriptorType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index, Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfRxDescrRingProc = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index, Eth_30_Tc3xx_MappedBufferOfRxDescrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()[(Index)].MappedBufferOfRxDescrState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index, Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].DescrIdxOfRxTsContextStack = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index, Eth_30_Tc3xx_RingIdxOfRxTsContextStackType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].RingIdxOfRxTsContextStack = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index, Eth_30_Tc3xx_RxTsContextStackPosType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_TimeStampType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestCorrTimeOfTimeHandling = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_TimeStampType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestHwTimeOfTimeHandling = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index, Eth_30_Tc3xx_RateRatioOfTimeHandlingType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].RateRatioOfTimeHandling = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index, Eth_30_Tc3xx_TxBufferType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index, Eth_30_Tc3xx_TxBufferFreeElemNumType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetBusyOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_BusyOfTxBufferStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].BusyOfTxBufferState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTsRequestedOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_TsRequestedOfTxBufferStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].TsRequestedOfTxBufferState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index, Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].UlTxConfStateOfTxBufferState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxDescr(Eth_30_Tc3xx_TxDescrIterType Index, Eth_30_Tc3xx_TxDescriptorType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrOfPCConfig()[(Index)] = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index, Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfTxDescrRingProc = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index, Eth_30_Tc3xx_FreePosOfTxDescrRingProcType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].FreePosOfTxDescrRingProc = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index, Eth_30_Tc3xx_MappedBufferOfTxDescrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].MappedBufferOfTxDescrState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index, Eth_30_Tc3xx_TxReadyOfTxDescrStateType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].TxReadyOfTxDescrState = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index, Eth_30_Tc3xx_DescrIdxOfTxTsContextType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].DescrIdxOfTxTsContext = (Value);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_SetRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index, Eth_30_Tc3xx_RingIdxOfTxTsContextType Value)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].RingIdxOfTxTsContext = (Value);
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCGetAddressOfDataInlineFunctions  Eth_30_Tc3xx Get Address Of Data Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to get the data by the address operator.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ActiveMacAddressPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ActiveMacAddressPtrType) (&(Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_CtrlModeOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_CtrlModeOfEthCtrlStatePtrType) (&(Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].CtrlModeOfEthCtrlState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStatePtrType) (&(Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingRxEventsOfEthCtrlState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStatePtrType) (&(Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingTxEventsOfEthCtrlState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RegBaseAddrOfEthCtrlStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RegBaseAddrOfEthCtrlStatePtrType) (&(Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].RegBaseAddrOfEthCtrlState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStatePtrType) (&(Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].ReadMiiResultOfEthCtrlTc3xxState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxStatsOfEthCtrlTc3xxStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxStatsOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (&(Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].RxStatsOfEthCtrlTc3xxState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterPtrType) (&(Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffRxBuffOfEthMeasDataCounter));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterPtrType) (&(Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffTxBuffOfEthMeasDataCounter));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterPtrType) (&(Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].WarnFullRxBuffOfEthMeasDataCounter));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetPtrType) (&(Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()[(Index)].DropInsuffRxBuffResetOfEthMeasDataCounterReset));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MulticastBucketCountersPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MulticastBucketCountersPtrType) (&(Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_PromiscuousModeCounterPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_PromiscuousModeCounterPtrType) (&(Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxBufferPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxBufferPtrType) (&(Eth_30_Tc3xx_GetRxBufferOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxDescrPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxDescr(Eth_30_Tc3xx_RxDescrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (&(Eth_30_Tc3xx_GetRxDescrOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfRxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MappedBufferOfRxDescrStatePtrType) (&(Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()[(Index)].MappedBufferOfRxDescrState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RxTsContextStackPosPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RxTsContextStackPosPtrType) (&(Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LatestCorrTimeOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrLatestCorrTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (&(Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestCorrTimeOfTimeHandling));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_LatestHwTimeOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrLatestHwTimeOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (&(Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].LatestHwTimeOfTimeHandling));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_RateRatioOfTimeHandlingPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrRateRatioOfTimeHandling(Eth_30_Tc3xx_TimeHandlingIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_RateRatioOfTimeHandlingPtrType) (&(Eth_30_Tc3xx_GetTimeHandlingOfPCConfig()[(Index)].RateRatioOfTimeHandling));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferPtrType) (&(Eth_30_Tc3xx_GetTxBufferOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxBufferFreeElemNumPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxBufferFreeElemNumPtrType) (&(Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_UlTxConfStateOfTxBufferStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_UlTxConfStateOfTxBufferStatePtrType) (&(Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].UlTxConfStateOfTxBufferState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxDescrPtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxDescr(Eth_30_Tc3xx_TxDescrIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (&(Eth_30_Tc3xx_GetTxDescrOfPCConfig()[(Index)]));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_MappedBufferOfTxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_MappedBufferOfTxDescrStatePtrType) (&(Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].MappedBufferOfTxDescrState));
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(Eth_30_Tc3xx_TxReadyOfTxDescrStatePtrType, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_GetAddrTxReadyOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (Eth_30_Tc3xx_TxReadyOfTxDescrStatePtrType) (&(Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].TxReadyOfTxDescrState));
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCHasInlineFunctions  Eth_30_Tc3xx Has Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthCtrlOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAutosarRtmRegBaseAddrOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDemEAccessEventIdOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasFqtssEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIpChecksumOffloadingEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLoopCyclesOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMiiLoopCyclesOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMultiQueueConfigEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasNvMBlockIdOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasProtectedAreaIdOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasProtocolChecksumOffloadingEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasResetLoopCyclesOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxInterruptEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCalloutsIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeSynEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTrcvSpeedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandlingIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingEndIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingStartIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxInterruptEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedFrameQueuingEnabledOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingIdxOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingUsedOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCtrlModeOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPendingRxEventsOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPendingTxEventsOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegBaseAddrOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthCtrlTc3xxOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAmountOfRxQueuesOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAmountOfTxQueuesOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasArmPpsOnTimeEnabledOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCsrClockRangeOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlMiiInterfaceOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPinRoutingOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasReadMiiResultOfEthCtrlTc3xxState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxStatsOfEthCtrlTc3xxState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffRxBuffOfEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffTxBuffOfEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasWarnFullRxBuffOfEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterReset(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDropInsuffRxBuffResetOfEthMeasDataCounterReset(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetEthSwtIfcOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthAdaptBufferLengthOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthPrepareTxFrameOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthProcessRxFrameOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthProcessTxFrameOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthRxFinishedIndicationOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthTxFinishedIndicationOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetInitialMacAddressOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetIsrInfosOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsEndIdxOfIsrInfos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsStartIdxOfIsrInfos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncs(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetIsrIrqEventFuncsOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCounters(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOptCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetOptCalloutsOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufWarnLvlCalloutOfOptCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPromiscuousModeCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetQosHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableEndIdxOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableStartIdxOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingIdxOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapEndIdxOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapStartIdxOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRegDataOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAccessModeOfRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOffsetOfRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasValueOfRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxBufferOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxBufferHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedLastSegSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedSegSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrNumOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMaxFrameSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferEndIdxOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferStartIdxOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSegNumOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUnalignedSegSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxDescrOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxDescrHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrEndIdxOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProcIdxOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStartIdxOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateEndIdxOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateStartIdxOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCurProcPosOfRxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxDescrStateOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMappedBufferOfRxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStack(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrIdxOfRxTsContextStack(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRingIdxOfRxTsContextStack(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetRxTxNotificationCalloutsOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxIndicationCalloutOfRxTxNotificationCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxConfirmationCalloutOfRxTxNotificationCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailable(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetShaperAvailableOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfActiveMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrl(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xx(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterReset(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthSwtIfc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfInitialMacAddress(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrInfos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrIrqEventFuncs(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfMulticastBucketCounters(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfOptCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfPromiscuousModeCounter(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfQosHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRegData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStack(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackPos(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTxNotificationCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfShaperAvailable(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferFreeElemNum(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxTsContext(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdRxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanPrioTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTimeHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLatestCorrTimeOfTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLatestHwTimeOfTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRateRatioOfTimeHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTsHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackEndIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPosIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackStartIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandlingIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextEndIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextStartIdxOfTsHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBuffer(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxBufferOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxBufferDataOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasLengthOfTxBufferData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasStartPosOfTxBufferData(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNum(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxBufferHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasAlignedSegSizeOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasBufferNumOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrNumOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMaxBufferLenOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataEndIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataStartIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferEndIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNumIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStartIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateEndIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateStartIdxOfTxBufferHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxBufferStateOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasBusyOfTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsRequestedOfTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUlTxConfStateOfTxBufferState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescr(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxDescrOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxDescrHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrEndIdxOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProcIdxOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStartIdxOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateEndIdxOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateStartIdxOfTxDescrHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasCurProcPosOfTxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasFreePosOfTxDescrRingProc(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxDescrStateOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMappedBufferOfTxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxReadyOfTxDescrState(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContext(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetTxTsContextOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasDescrIdxOfTxTsContext(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRingIdxOfTxTsContext(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetUserInitCalloutsOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPostInitUserCalloutOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPreInitUserCalloutOfUserInitCallouts(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetVlanIdBasedQueuingHandlingOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingIdxOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetVlanIdRxDescrRingMapOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQueueIndexOfVlanIdRxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdOfVlanIdRxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetVlanIdTxDescrRingMapOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQueueIndexOfVlanIdTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdOfVlanIdTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMap(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (Eth_30_Tc3xx_GetVlanPrioTxDescrRingMapOfPCConfig() != NULL_PTR);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasActiveMacAddressOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthCtrlTc3xxStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthMeasDataCounterResetOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasEthSwtIfcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasInitialMacAddressOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrInfosOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasIsrIrqEventFuncsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasMulticastBucketCountersOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasOptCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasPromiscuousModeCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasQosHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRegDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrRingProcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxDescrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTsContextStackPosOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasRxTxNotificationCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasShaperAvailableOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfActiveMacAddressOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthCtrlTc3xxStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthMeasDataCounterResetOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfEthSwtIfcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfInitialMacAddressOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrInfosOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfIsrIrqEventFuncsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfMulticastBucketCountersOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfOptCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfPromiscuousModeCounterOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfQosHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRegDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrRingProcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxDescrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTsContextStackPosOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfRxTxNotificationCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfShaperAvailableOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTimeHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTsHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferFreeElemNumOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxBufferStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrRingProcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxDescrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfTxTsContextOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfUserInitCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdBasedQueuingHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdRxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanIdTxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasSizeOfVlanPrioTxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTimeHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTsHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferDataOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferFreeElemNumOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxBufferStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrRingProcOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxDescrStateOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasTxTsContextOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasUserInitCalloutsOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdBasedQueuingHandlingOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdRxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanIdTxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(boolean, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_HasVlanPrioTxDescrRingMapOfPCConfig(void)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  return (boolean) (TRUE != FALSE);
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCIncrementInlineFunctions  Eth_30_Tc3xx Increment Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to increment VAR data with numerical nature.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].CtrlModeOfEthCtrlState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingRxEventsOfEthCtrlState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingTxEventsOfEthCtrlState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].RegBaseAddrOfEthCtrlState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].ReadMiiResultOfEthCtrlTc3xxState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffRxBuffOfEthMeasDataCounter++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffTxBuffOfEthMeasDataCounter++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].WarnFullRxBuffOfEthMeasDataCounter++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()[(Index)].DropInsuffRxBuffResetOfEthMeasDataCounterReset++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxBufferOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfRxDescrRingProc++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()[(Index)].MappedBufferOfRxDescrState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].DescrIdxOfRxTsContextStack++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].RingIdxOfRxTsContextStack++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()[(Index)]++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].UlTxConfStateOfTxBufferState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfTxDescrRingProc++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].FreePosOfTxDescrRingProc++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].MappedBufferOfTxDescrState++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].DescrIdxOfTxTsContext++;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_IncRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].RingIdxOfTxTsContext++;
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

#define ETH_30_TC3XX_START_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/** 
  \defgroup  Eth_30_Tc3xxPCDecrementInlineFunctions  Eth_30_Tc3xx Decrement Inline Functions (PRE_COMPILE)
  \brief  These inline functions can be used to decrement VAR data with numerical nature.
  \{
*/ 
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecActiveMacAddress(Eth_30_Tc3xx_ActiveMacAddressIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetActiveMacAddressOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCtrlModeOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].CtrlModeOfEthCtrlState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPendingRxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingRxEventsOfEthCtrlState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPendingTxEventsOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].PendingTxEventsOfEthCtrlState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRegBaseAddrOfEthCtrlState(Eth_30_Tc3xx_EthCtrlStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlStateOfPCConfig()[(Index)].RegBaseAddrOfEthCtrlState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecReadMiiResultOfEthCtrlTc3xxState(Eth_30_Tc3xx_EthCtrlTc3xxStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthCtrlTc3xxStateOfPCConfig()[(Index)].ReadMiiResultOfEthCtrlTc3xxState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffRxBuffOfEthMeasDataCounter--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffTxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].DropInsuffTxBuffOfEthMeasDataCounter--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecWarnFullRxBuffOfEthMeasDataCounter(Eth_30_Tc3xx_EthMeasDataCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterOfPCConfig()[(Index)].WarnFullRxBuffOfEthMeasDataCounter--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDropInsuffRxBuffResetOfEthMeasDataCounterReset(Eth_30_Tc3xx_EthMeasDataCounterResetIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetEthMeasDataCounterResetOfPCConfig()[(Index)].DropInsuffRxBuffResetOfEthMeasDataCounterReset--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMulticastBucketCounters(Eth_30_Tc3xx_MulticastBucketCountersIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetMulticastBucketCountersOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecPromiscuousModeCounter(Eth_30_Tc3xx_PromiscuousModeCounterIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetPromiscuousModeCounterOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRxBuffer(Eth_30_Tc3xx_RxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxBufferOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCurProcPosOfRxDescrRingProc(Eth_30_Tc3xx_RxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfRxDescrRingProc--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMappedBufferOfRxDescrState(Eth_30_Tc3xx_RxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxDescrStateOfPCConfig()[(Index)].MappedBufferOfRxDescrState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDescrIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].DescrIdxOfRxTsContextStack--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRingIdxOfRxTsContextStack(Eth_30_Tc3xx_RxTsContextStackIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackOfPCConfig()[(Index)].RingIdxOfRxTsContextStack--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRxTsContextStackPos(Eth_30_Tc3xx_RxTsContextStackPosIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetRxTsContextStackPosOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecTxBuffer(Eth_30_Tc3xx_TxBufferIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecTxBufferFreeElemNum(Eth_30_Tc3xx_TxBufferFreeElemNumIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferFreeElemNumOfPCConfig()[(Index)]--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecUlTxConfStateOfTxBufferState(Eth_30_Tc3xx_TxBufferStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxBufferStateOfPCConfig()[(Index)].UlTxConfStateOfTxBufferState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecCurProcPosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].CurProcPosOfTxDescrRingProc--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecFreePosOfTxDescrRingProc(Eth_30_Tc3xx_TxDescrRingProcIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrRingProcOfPCConfig()[(Index)].FreePosOfTxDescrRingProc--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecMappedBufferOfTxDescrState(Eth_30_Tc3xx_TxDescrStateIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxDescrStateOfPCConfig()[(Index)].MappedBufferOfTxDescrState--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecDescrIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].DescrIdxOfTxTsContext--;
}
ETH_30_TC3XX_LOCAL_INLINE FUNC(void, ETH_30_TC3XX_CODE) Eth_30_Tc3xx_DecRingIdxOfTxTsContext(Eth_30_Tc3xx_TxTsContextIterType Index)  /* PRQA S 3219 */  /* MD_MSR_8.10 */
{
  Eth_30_Tc3xx_GetTxTsContextOfPCConfig()[(Index)].RingIdxOfTxTsContext--;
}
/** 
  \}
*/ 

#define ETH_30_TC3XX_STOP_SEC_CODE
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */


# endif /* ETH_30_TC3XX_UNIT_TEST */

#endif  /* ETH_30_TC3XX_LCFG_H */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Lcfg.h
 *********************************************************************************************************************/
 
