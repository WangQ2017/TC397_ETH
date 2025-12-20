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
 *              File: Eth_30_Tc3xx_Lcfg.c
 *   Generation Time: 2025-12-20 21:04:57
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#define ETH_30_TC3XX_LCFG_SOURCE

/* PRQA S 0810 EOF */ /* MD_MSR_1.1_810 */
/* PRQA S 0828 EOF */ /* MD_MSR_1.1_828 */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
#include "Eth_30_Tc3xx_IrqHandler_Int.h"


/**********************************************************************************************************************
 *  LOCAL MACROS
 *********************************************************************************************************************/
#ifndef ETH_30_TC3XX_REGADDR_ETHCTRLCONFIG_MAIN
# define ETH_30_TC3XX_REGADDR_ETHCTRLCONFIG_MAIN (0xF001D000uL)
#endif

/**********************************************************************************************************************
 *  COM STACK LIB DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: LOCAL DATA
**********************************************************************************************************************/


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
/**********************************************************************************************************************
  Eth_30_Tc3xx_EthCtrl
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthCtrl
  \brief  Ethernet controller configuration
  \details
  Element                              Description
  TrcvSpeed                            Transceiver speed
  LoopCycles                           Maximum tries till a general hardware access is assumed as failed
  MiiLoopCycles                        Maximum tries till MII access is assumed as failed
  ProtectedAreaId                      Id of area in case driver has to access proteced memory for register access
  ResetLoopCycles                      Maximum tries till reset is assumed as failed
  FqtssEnabled                         FQTSS enabled
  IpChecksumOffloadingEnabled          IP checksum offloading enabled
  MultiQueueConfigEnabled              Qos/VLAN-ID based frame queuing enabled
  ProtocolChecksumOffloadingEnabled    Protocol checksum offloading enabled
  QosEnabled                           Qos configuration
  RxInterruptEnabled                   Rx interrupt configuration
  TimeSynEnabled                       TimeSync configuraiton
  TxInterruptEnabled                   Tx interrupt configuration
  VlanIdBasedFrameQueuingEnabled       Vlan-ID based frame queuing configuration
  ActiveMacAddressEndIdx               the end index of the 1:n relation pointing to Eth_30_Tc3xx_ActiveMacAddress
  ActiveMacAddressStartIdx             the start index of the 1:n relation pointing to Eth_30_Tc3xx_ActiveMacAddress
  DemEAccessEventId                    ETH_E_ACCESS DEM event
  EthSwtIfcIdx                         the index of the 0:1 relation pointing to Eth_30_Tc3xx_EthSwtIfc
  InitialMacAddressEndIdx              the end index of the 1:n relation pointing to Eth_30_Tc3xx_InitialMacAddress
  InitialMacAddressStartIdx            the start index of the 1:n relation pointing to Eth_30_Tc3xx_InitialMacAddress
  IsrInfosEndIdx                       the end index of the 0:n relation pointing to Eth_30_Tc3xx_IsrInfos
  IsrInfosStartIdx                     the start index of the 0:n relation pointing to Eth_30_Tc3xx_IsrInfos
  MulticastBucketCountersEndIdx        the end index of the 1:n relation pointing to Eth_30_Tc3xx_MulticastBucketCounters
  MulticastBucketCountersStartIdx      the start index of the 1:n relation pointing to Eth_30_Tc3xx_MulticastBucketCounters
  NvMBlockId                           NvM Block Id for storage of MAC address
  QosHandlingIdx                       the index of the 0:1 relation pointing to Eth_30_Tc3xx_QosHandling
  RegDataEndIdx                        the end index of the 0:n relation pointing to Eth_30_Tc3xx_RegData
  RegDataStartIdx                      the start index of the 0:n relation pointing to Eth_30_Tc3xx_RegData
  RxBufferHandlingEndIdx               the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxBufferHandling
  RxBufferHandlingStartIdx             the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxBufferHandling
  RxDescrHandlingEndIdx                the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrHandling
  RxDescrHandlingStartIdx              the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrHandling
  RxTxNotificationCalloutsIdx          the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxTxNotificationCallouts
  TsHandlingIdx                        the index of the 0:1 relation pointing to Eth_30_Tc3xx_TsHandling
  TxBufferHandlingIdx                  the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxBufferHandling
  TxDescrHandlingEndIdx                the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrHandling
  TxDescrHandlingStartIdx              the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrHandling
  VlanIdBasedQueuingHandlingIdx        the index of the 0:1 relation pointing to Eth_30_Tc3xx_VlanIdBasedQueuingHandling
  AutosarRtmRegBaseAddr                Register base address of the Ethernet controller when running in AUTOSAR OS environment
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_EthCtrlType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrl[1] = {
    /* Index    TrcvSpeed                        LoopCycles  MiiLoopCycles  ProtectedAreaId                       ResetLoopCycles  FqtssEnabled  IpChecksumOffloadingEnabled  MultiQueueConfigEnabled  ProtocolChecksumOffloadingEnabled  QosEnabled  RxInterruptEnabled  TimeSynEnabled  TxInterruptEnabled  VlanIdBasedFrameQueuingEnabled  ActiveMacAddressEndIdx                                                         ActiveMacAddressStartIdx                                                         DemEAccessEventId                           EthSwtIfcIdx                                                                                  InitialMacAddressEndIdx                                                         InitialMacAddressStartIdx                                                         IsrInfosEndIdx                                                         IsrInfosStartIdx                                                         MulticastBucketCountersEndIdx                                                         MulticastBucketCountersStartIdx                                                         NvMBlockId                           QosHandlingIdx                                                                                  RegDataEndIdx                                                         RegDataStartIdx                                                         RxBufferHandlingEndIdx                                                         RxBufferHandlingStartIdx                                                         RxDescrHandlingEndIdx                                                         RxDescrHandlingStartIdx                                                         RxTxNotificationCalloutsIdx                                                         TsHandlingIdx                                                         TxBufferHandlingIdx                                                         TxDescrHandlingEndIdx                                                         TxDescrHandlingStartIdx                                                         VlanIdBasedQueuingHandlingIdx                                                                                  AutosarRtmRegBaseAddr                   */
  { /*     0 */ ETH_TRCV_SPEED_100MBITS_IN_BITS,      1000u,         1000u, ETH_30_TC3XX_PROTECTED_AREA_DISABLED,           1000u,        FALSE,                        TRUE,                   FALSE,                              TRUE,      FALSE,              FALSE,           TRUE,               TRUE,                          FALSE,                     6u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                       0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */, ETH_30_TC3XX_NO_DEMEACCESSEVENTIDOFETHCTRL, ETH_30_TC3XX_NO_ETHSWTIFCIDXOFETHCTRL  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                      6u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                        0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,             1u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,               0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                           64u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                              0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */, ETH_30_TC3XX_NO_NVMBLOCKIDOFETHCTRL, ETH_30_TC3XX_NO_QOSHANDLINGIDXOFETHCTRL  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,           29u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,              0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                     1u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                       0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                    1u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                      0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                          0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,            0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                  0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                    1u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                      0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */, ETH_30_TC3XX_NO_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */, ETH_30_TC3XX_REGADDR_ETHCTRLCONFIG_MAIN }
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_EthCtrlTc3xx
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthCtrlTc3xx
  \brief  Tc3xx Ethernet controller specific configuration
  \details
  Element                Description
  CsrClockRange          CsrClockRange configuration
  EthCtrlMiiInterface    MiiInterface of the controller
  ArmPpsOnTimeEnabled    ArmPpsOnTime configuration
  AmountOfRxQueues       Amount of configured QoS Rx queues
  AmountOfTxQueues       Amount of configured QoS Tx queues
  PinRouting             Pin routing configuration
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_EthCtrlTc3xxType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrlTc3xx[1] = {
    /* Index    CsrClockRange  EthCtrlMiiInterface  ArmPpsOnTimeEnabled  AmountOfRxQueues  AmountOfTxQueues  PinRouting */
  { /*     0 */       0x0500u, ETH_MII_MODE       ,                TRUE,               0u,               0u,      0x02u }
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_InitialMacAddress
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_InitialMacAddress
  \brief  Initially used MAC address of the Ethernet controller
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_InitialMacAddressType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_InitialMacAddress[6] = {
  /* Index     InitialMacAddress      Referable Keys */
  /*     0 */                60u,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     1 */                 2u,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     2 */                23u,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     3 */                 2u,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     4 */                 2u,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     5 */                23u   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_IsrInfos
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_IsrInfos
  \brief  Mapping information for processing the respective interrupt service routine
  \details
  Element                     Description
  IsrIrqEventFuncsEndIdx      the end index of the 1:n relation pointing to Eth_30_Tc3xx_IsrIrqEventFuncs
  IsrIrqEventFuncsStartIdx    the start index of the 1:n relation pointing to Eth_30_Tc3xx_IsrIrqEventFuncs
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_IsrInfosType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrInfos[1] = {
    /* Index    IsrIrqEventFuncsEndIdx                                                                                                        IsrIrqEventFuncsStartIdx                                                                                                              Referable Keys */
  { /*     0 */                     3u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthInterruptMapping_EthInterruptServiceRoutine */,                       0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthInterruptMapping_EthInterruptServiceRoutine */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_IsrIrqEventFuncs
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_IsrIrqEventFuncs
  \brief  Functions processed during interrupt service routines
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_IrqEventFctPtrType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrIrqEventFuncs[3] = {
  /* Index     IsrIrqEventFuncs              Referable Keys */
  /*     0 */ NULL_PTR                 ,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthInterruptMapping_EthInterruptServiceRoutine] */
  /*     1 */ Eth_30_Tc3xx_IrqHdlrQ0Tx ,  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthInterruptMapping_EthInterruptServiceRoutine] */
  /*     2 */ NULL_PTR                    /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthInterruptMapping_EthInterruptServiceRoutine] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_OptCallouts
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_OptCallouts
  \brief  Optional callouts to application.
  \details
  Element                Description
  RxBufWarnLvlCallout    Rx buffer warning level user callout
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_OptCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_OptCallouts[1] = {
    /* Index    RxBufWarnLvlCallout */
  { /*     0 */ NULL_PTR            }
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RegData
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RegData
  \brief  Register data of the Ethernet controllers.
  \details
  Element       Description
  Value         Value of register
  Offset        Offset of register relative to register base address
  AccessMode    Mode of microcontroller where register is allowed to be modified
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_RegDataType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RegData[29] = {
    /* Index    Value         Offset   AccessMode                                        Referable Keys */
  { /*     0 */ 0x0820E440uL, 0x0000u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     1 */ 0x00000000uL, 0x0004u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     2 */ 0x00000010uL, 0x0008u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     3 */ 0x00000000uL, 0x0070u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     4 */ 0x00000000uL, 0x0090u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     5 */ 0x00000002uL, 0x00A0u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     6 */ 0x00000000uL, 0x00A4u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     7 */ 0x000000FFuL, 0x00A8u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     8 */ 0x00002000uL, 0x00B4u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     9 */ 0x00000001uL, 0x0700u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    10 */ 0x0FFFFFFFuL, 0x070Cu, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    11 */ 0x0FFFFFFFuL, 0x0710u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    12 */ 0x3FFF3FFFuL, 0x0800u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    13 */ 0x00000301uL, 0x0B00u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    14 */ 0x000A0000uL, 0x0B04u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    15 */ 0x00000000uL, 0x0B18u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    16 */ 0x00000009uL, 0x0B88u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    17 */ 0x00000007uL, 0x0B8Cu, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    18 */ 0x00000260uL, 0x0C00u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    19 */ 0x00000000uL, 0x0C30u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    20 */ 0x000F000AuL, 0x0D00u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    21 */ 0x01F00020uL, 0x0D30u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    22 */ 0x00000009uL, 0x0D3Cu, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    23 */ 0x00000000uL, 0x1000u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    24 */ 0x00001001uL, 0x1004u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    25 */ 0x00000000uL, 0x1100u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    26 */ 0x00080010uL, 0x1104u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    27 */ 0x00080C00uL, 0x1108u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*    28 */ 0x00008001uL, 0x1134u, ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxBufferHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxBufferHandling
  \brief  Rx buffer handling
  \details
  Element               Description
  AlignedLastSegSize    Size of last segment including alignment, padding bytes, etc
  AlignedSegSize        Segment size including alignment, padding bytes, etc.
  MaxFrameSize          Maximum frame size as configured
  RxBufferEndIdx        the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxBuffer
  RxBufferStartIdx      the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxBuffer
  UnalignedSegSize      Segment size as configured
  DescrNum              Number of descriptors used in that descriptor ring
  SegNum                Number of segments contained in the descriptor ring
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_RxBufferHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxBufferHandling[1] = {
    /* Index    AlignedLastSegSize  AlignedSegSize  MaxFrameSize  RxBufferEndIdx                                                                        RxBufferStartIdx                                                                        UnalignedSegSize  DescrNum  SegNum        Referable Keys */
  { /*     0 */              1536u,          1536u,        1522u,          3072u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthRxBufConfig */,               0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN_EthRxBufConfig */,            1522u,       2u,     2u }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxDescrHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxDescrHandling
  \brief  Rx descriptor handling
  \details
  Element                 Description
  RxDescrEndIdx           the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescr
  RxDescrRingProcIdx      the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescrRingProc
  RxDescrStartIdx         the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescr
  RxDescrStateEndIdx      the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrState
  RxDescrStateStartIdx    the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrState
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_RxDescrHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxDescrHandling[1] = {
    /* Index    RxDescrEndIdx                                                         RxDescrRingProcIdx                                                         RxDescrStartIdx                                                         RxDescrStateEndIdx                                                         RxDescrStateStartIdx                                                               Referable Keys */
  { /*     0 */            2u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                 0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,              0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                 2u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                   0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxTxNotificationCallouts
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxTxNotificationCallouts
  \brief  Rx or Tx Notification callouts to application.
  \details
  Element                  Description
  RxIndicationCallout      Rx-Indication Callout
  TxConfirmationCallout    Tx-Confirmation callout
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_RxTxNotificationCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxTxNotificationCallouts[1] = {
    /* Index    RxIndicationCallout  TxConfirmationCallout        Referable Keys */
  { /*     0 */ NULL_PTR           , NULL_PTR              }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TsHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TsHandling
  \brief  Timestamping handling
  \details
  Element                     Description
  RxTsContextStackEndIdx      the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxTsContextStack
  RxTsContextStackPosIdx      the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxTsContextStackPos
  RxTsContextStackStartIdx    the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxTsContextStack
  TimeHandlingIdx             the index of the 1:1 relation pointing to Eth_30_Tc3xx_TimeHandling
  TxTsContextEndIdx           the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxTsContext
  TxTsContextStartIdx         the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxTsContext
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_TsHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TsHandling[1] = {
    /* Index    RxTsContextStackEndIdx                                                         RxTsContextStackPosIdx                                                         RxTsContextStackStartIdx                                                         TimeHandlingIdx                                                         TxTsContextEndIdx                                                         TxTsContextStartIdx                                                               Referable Keys */
  { /*     0 */                     1u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                     0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                       0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,              0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                4u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                  0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxBufferData
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxBufferData
  \brief  Tx buffer configuration data
  \details
  Element     Description
  Length      Length of the Tx buffer
  StartPos    Position of Tx buffer within buffer pool
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_TxBufferDataType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferData[4] = {
    /* Index    Length  StartPos        Referable Keys */
  { /*     0 */  1518u,       2u },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     1 */  1518u,    1538u },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     2 */  1518u,    3074u },  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  { /*     3 */  1518u,    4610u }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxBufferHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxBufferHandling
  \brief  Tx buffer handling
  \details
  Element                   Description
  AlignedSegSize            Segment size including alignment, padding bytes, etc.
  MaxBufferLen              Length of the greates buffer
  TxBufferEndIdx            the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBuffer
  TxBufferStartIdx          the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBuffer
  BufferNum                 Number of tx buffers
  DescrNum                  Numer of tx descriptors
  TxBufferDataEndIdx        the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferData
  TxBufferDataStartIdx      the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferData
  TxBufferFreeElemNumIdx    the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxBufferFreeElemNum
  TxBufferStateEndIdx       the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferState
  TxBufferStateStartIdx     the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferState
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_TxBufferHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferHandling[1] = {
    /* Index    AlignedSegSize  MaxBufferLen  TxBufferEndIdx                                                         TxBufferStartIdx                                                         BufferNum  DescrNum  TxBufferDataEndIdx                                                         TxBufferDataStartIdx                                                         TxBufferFreeElemNumIdx                                                         TxBufferStateEndIdx                                                         TxBufferStateStartIdx                                                               Referable Keys */
  { /*     0 */          1536u,      0x05EEu,          6144u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,               0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,        4u,       4u,                 4u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                   0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                     0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                  4u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                    0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxDescrHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxDescrHandling
  \brief  Tx descriptor handling
  \details
  Element                 Description
  TxDescrEndIdx           the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescr
  TxDescrRingProcIdx      the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrRingProc
  TxDescrStartIdx         the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescr
  TxDescrStateEndIdx      the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrState
  TxDescrStateStartIdx    the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrState
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_TxDescrHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxDescrHandling[1] = {
    /* Index    TxDescrEndIdx                                                         TxDescrRingProcIdx                                                         TxDescrStartIdx                                                         TxDescrStateEndIdx                                                         TxDescrStateStartIdx                                                               Referable Keys */
  { /*     0 */            4u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                 0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,              0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                 4u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */,                   0u  /* /ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN */ }   /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_UserInitCallouts
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_UserInitCallouts
  \brief  Pre-/Post-Controller-Initialization callouts to application.
  \details
  Element                Description
  PostInitUserCallout    Post-Controller-Initialization callout
  PreInitUserCallout     Pre-Controller-Initialization callout
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_UserInitCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_UserInitCallouts[1] = {
    /* Index    PostInitUserCallout  PreInitUserCallout */
  { /*     0 */ NULL_PTR           , NULL_PTR           }
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_ActiveMacAddress
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_ActiveMacAddress
  \brief  Currently used MAC address of the Ethernet controller
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_ActiveMacAddressUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ActiveMacAddress;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     5 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_EthCtrlState
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthCtrlState
  \brief  State of the Ethernet controller
  \details
  Element            Description
  PendingRxEvents    Bitmask tracking reception events where each bit represents the respective queue the event has occured on (highest bit -&gt; highest prio queue, lowest bit -&gt; lowest prio queue)
  PendingTxEvents    Bitmask tracking tx confirmation events where each bit represents the respective queue the event has occured on (highest bit -&gt; highest prio queue, lowest bit -&gt; lowest prio queue)
  CtrlMode           Mode of Ethernet controller
  RegBaseAddr        Register base address used to access register space of respective driver
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_EthCtrlStateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlState[1];
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_EthCtrlTc3xxState
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthCtrlTc3xxState
  \brief  Runtime states of Tc3xx
  \details
  Element          Description
  ReadMiiResult    Result of a read operation on MII interface
  RxStats          Reception statistics
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_EthCtrlTc3xxStateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlTc3xxState[1];
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_EthMeasDataCounter
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthMeasDataCounter
  \brief  Vendor specific measurement counters for Rx and Tx frame drop due to insufficient buffers
  \details
  Element             Description
  DropInsuffRxBuff    Count of Rx frames drop due to insufficient Tx Buffers
  DropInsuffTxBuff    Count of Tx frames drop due to insufficient Tx Buffers
  WarnFullRxBuff      Number of times no free Rx buffer encountered
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_EthMeasDataCounterType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounter[1];
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_EthMeasDataCounterReset
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_EthMeasDataCounterReset
  \brief  Reset value for EthMeasDataCounter, as Tc3xx hardware does not provide a reset
  \details
  Element                  Description
  DropInsuffRxBuffReset    Reset value for Rx MeasDataCounter
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_EthMeasDataCounterResetType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounterReset[1];
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_MulticastBucketCounters
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_MulticastBucketCounters
  \brief  Hash table containing the request count for specific multicast groups
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_MulticastBucketCountersUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_MulticastBucketCounters;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*    63 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_PromiscuousModeCounter
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_PromiscuousModeCounter
  \brief  Promiscuous mode request count
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_PromiscuousModeCounterType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PromiscuousModeCounter[1];
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxBuffer
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxBuffer
  \brief  Reception buffers of Ethernet controllers
*/ 
#define ETH_30_TC3XX_START_SEC_RX_BUFFER_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxBufferUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxBuffer;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
#define ETH_30_TC3XX_STOP_SEC_RX_BUFFER_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxDescr
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxDescr
  \brief  Rx descriptors
*/ 
#define ETH_30_TC3XX_START_SEC_RX_DESCRIPTOR_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxDescrUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescr;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     1 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_RX_DESCRIPTOR_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxDescrRingProc
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxDescrRingProc
  \brief  Rx descriptor ring processing data
  \details
  Element       Description
  CurProcPos    the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescr
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxDescrRingProcUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrRingProc;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxDescrState
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxDescrState
  \brief  States of the rx descriptors.
  \details
  Element         Description
  MappedBuffer    Rx buffer mapped to descriptor
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxDescrStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     1 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxTsContextStack
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxTsContextStack
  \brief  Rx timestamping context stack
  \details
  Element     Description
  DescrIdx    the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescr
  RingIdx     the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescrHandling
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxTsContextStackUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStack;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_RxTsContextStackPos
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_RxTsContextStackPos
  \brief  Rx timestamping context stack position
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_RxTsContextStackPosUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStackPos;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TimeHandling
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TimeHandling
  \brief  Software time handling for time synchronization
  \details
  Element           Description
  RateRatio         Current drift correction factor
  LatestCorrTime    Latest time corrected by drift correction
  LatestHwTime      Latest time captured by hardware
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TimeHandlingUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TimeHandling;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxBuffer
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxBuffer
  \brief  Transmission buffers of Ethernet controllers
*/ 
#define ETH_30_TC3XX_START_SEC_TX_BUFFER_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxBufferUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBuffer;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
#define ETH_30_TC3XX_STOP_SEC_TX_BUFFER_VAR_NOINIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxBufferFreeElemNum
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxBufferFreeElemNum
  \brief  Free elements left in tx buffer pool
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxBufferFreeElemNumUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferFreeElemNum;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_16BIT
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxBufferState
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxBufferState
  \brief  States of the tx buffers
  \details
  Element          Description
  Busy             Busy state
  TsRequested      Time stamping request state
  UlTxConfState    Upper layer tx confirmation state
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxBufferStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     3 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxDescr
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxDescr
  \brief  Tx descriptors
*/ 
#define ETH_30_TC3XX_START_SEC_TX_DESCRIPTOR_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxDescrUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescr;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     3 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_TX_DESCRIPTOR_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxDescrRingProc
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxDescrRingProc
  \brief  Tx descriptor ring processing data
  \details
  Element       Description
  CurProcPos    the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr
  FreePos       the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxDescrRingProcUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrRingProc;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxDescrState
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxDescrState
  \brief  States of the tx descriptors.
  \details
  Element         Description
  MappedBuffer    Tx buffer mapped to descriptor
  TxReady         Tx ready state
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxDescrStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     3 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_TxTsContext
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_TxTsContext
  \brief  Tx timestamping context
  \details
  Element     Description
  DescrIdx    the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr
  RingIdx     the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrHandling
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
VAR(Eth_30_Tc3xx_TxTsContextUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxTsContext;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
  /* Index        Referable Keys */
  /*     0 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*   ... */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */
  /*     3 */  /* [/ActiveEcuC/Eth/EthConfigSet/EthCtrlConfig_MAIN] */

#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
  Eth_30_Tc3xx_PCConfig
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_PCConfig
  \details
  Element                             Description
  ActiveMacAddress                    the pointer to Eth_30_Tc3xx_ActiveMacAddress
  EthCtrl                             the pointer to Eth_30_Tc3xx_EthCtrl
  EthCtrlState                        the pointer to Eth_30_Tc3xx_EthCtrlState
  EthCtrlTc3xx                        the pointer to Eth_30_Tc3xx_EthCtrlTc3xx
  EthCtrlTc3xxState                   the pointer to Eth_30_Tc3xx_EthCtrlTc3xxState
  EthMeasDataCounter                  the pointer to Eth_30_Tc3xx_EthMeasDataCounter
  EthMeasDataCounterReset             the pointer to Eth_30_Tc3xx_EthMeasDataCounterReset
  EthSwtIfc                           the pointer to Eth_30_Tc3xx_EthSwtIfc
  InitialMacAddress                   the pointer to Eth_30_Tc3xx_InitialMacAddress
  IsrInfos                            the pointer to Eth_30_Tc3xx_IsrInfos
  IsrIrqEventFuncs                    the pointer to Eth_30_Tc3xx_IsrIrqEventFuncs
  MulticastBucketCounters             the pointer to Eth_30_Tc3xx_MulticastBucketCounters
  OptCallouts                         the pointer to Eth_30_Tc3xx_OptCallouts
  PromiscuousModeCounter              the pointer to Eth_30_Tc3xx_PromiscuousModeCounter
  QosHandling                         the pointer to Eth_30_Tc3xx_QosHandling
  RegData                             the pointer to Eth_30_Tc3xx_RegData
  RxBuffer                            the pointer to Eth_30_Tc3xx_RxBuffer
  RxBufferHandling                    the pointer to Eth_30_Tc3xx_RxBufferHandling
  RxDescr                             the pointer to Eth_30_Tc3xx_RxDescr
  RxDescrHandling                     the pointer to Eth_30_Tc3xx_RxDescrHandling
  RxDescrRingProc                     the pointer to Eth_30_Tc3xx_RxDescrRingProc
  RxDescrState                        the pointer to Eth_30_Tc3xx_RxDescrState
  RxTsContextStack                    the pointer to Eth_30_Tc3xx_RxTsContextStack
  RxTsContextStackPos                 the pointer to Eth_30_Tc3xx_RxTsContextStackPos
  RxTxNotificationCallouts            the pointer to Eth_30_Tc3xx_RxTxNotificationCallouts
  ShaperAvailable                     the pointer to Eth_30_Tc3xx_ShaperAvailable
  TimeHandling                        the pointer to Eth_30_Tc3xx_TimeHandling
  TsHandling                          the pointer to Eth_30_Tc3xx_TsHandling
  TxBuffer                            the pointer to Eth_30_Tc3xx_TxBuffer
  TxBufferData                        the pointer to Eth_30_Tc3xx_TxBufferData
  TxBufferFreeElemNum                 the pointer to Eth_30_Tc3xx_TxBufferFreeElemNum
  TxBufferHandling                    the pointer to Eth_30_Tc3xx_TxBufferHandling
  TxBufferState                       the pointer to Eth_30_Tc3xx_TxBufferState
  TxDescr                             the pointer to Eth_30_Tc3xx_TxDescr
  TxDescrHandling                     the pointer to Eth_30_Tc3xx_TxDescrHandling
  TxDescrRingProc                     the pointer to Eth_30_Tc3xx_TxDescrRingProc
  TxDescrState                        the pointer to Eth_30_Tc3xx_TxDescrState
  TxTsContext                         the pointer to Eth_30_Tc3xx_TxTsContext
  UserInitCallouts                    the pointer to Eth_30_Tc3xx_UserInitCallouts
  VlanIdBasedQueuingHandling          the pointer to Eth_30_Tc3xx_VlanIdBasedQueuingHandling
  VlanIdRxDescrRingMap                the pointer to Eth_30_Tc3xx_VlanIdRxDescrRingMap
  VlanIdTxDescrRingMap                the pointer to Eth_30_Tc3xx_VlanIdTxDescrRingMap
  VlanPrioTxDescrRingMap              the pointer to Eth_30_Tc3xx_VlanPrioTxDescrRingMap
  SizeOfRxBuffer                      the number of accomplishable value elements in Eth_30_Tc3xx_RxBuffer
  SizeOfTxBuffer                      the number of accomplishable value elements in Eth_30_Tc3xx_TxBuffer
  SizeOfActiveMacAddress              the number of accomplishable value elements in Eth_30_Tc3xx_ActiveMacAddress
  SizeOfEthCtrl                       the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrl
  SizeOfEthCtrlTc3xx                  the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrlTc3xx
  SizeOfEthSwtIfc                     the number of accomplishable value elements in Eth_30_Tc3xx_EthSwtIfc
  SizeOfInitialMacAddress             the number of accomplishable value elements in Eth_30_Tc3xx_InitialMacAddress
  SizeOfIsrInfos                      the number of accomplishable value elements in Eth_30_Tc3xx_IsrInfos
  SizeOfIsrIrqEventFuncs              the number of accomplishable value elements in Eth_30_Tc3xx_IsrIrqEventFuncs
  SizeOfMulticastBucketCounters       the number of accomplishable value elements in Eth_30_Tc3xx_MulticastBucketCounters
  SizeOfOptCallouts                   the number of accomplishable value elements in Eth_30_Tc3xx_OptCallouts
  SizeOfQosHandling                   the number of accomplishable value elements in Eth_30_Tc3xx_QosHandling
  SizeOfRegData                       the number of accomplishable value elements in Eth_30_Tc3xx_RegData
  SizeOfRxBufferHandling              the number of accomplishable value elements in Eth_30_Tc3xx_RxBufferHandling
  SizeOfRxDescr                       the number of accomplishable value elements in Eth_30_Tc3xx_RxDescr
  SizeOfRxDescrHandling               the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrHandling
  SizeOfRxDescrRingProc               the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrRingProc
  SizeOfRxDescrState                  the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrState
  SizeOfRxTsContextStack              the number of accomplishable value elements in Eth_30_Tc3xx_RxTsContextStack
  SizeOfRxTsContextStackPos           the number of accomplishable value elements in Eth_30_Tc3xx_RxTsContextStackPos
  SizeOfRxTxNotificationCallouts      the number of accomplishable value elements in Eth_30_Tc3xx_RxTxNotificationCallouts
  SizeOfShaperAvailable               the number of accomplishable value elements in Eth_30_Tc3xx_ShaperAvailable
  SizeOfTimeHandling                  the number of accomplishable value elements in Eth_30_Tc3xx_TimeHandling
  SizeOfTsHandling                    the number of accomplishable value elements in Eth_30_Tc3xx_TsHandling
  SizeOfTxBufferData                  the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferData
  SizeOfTxBufferFreeElemNum           the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferFreeElemNum
  SizeOfTxBufferHandling              the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferHandling
  SizeOfTxBufferState                 the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferState
  SizeOfTxDescr                       the number of accomplishable value elements in Eth_30_Tc3xx_TxDescr
  SizeOfTxDescrHandling               the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrHandling
  SizeOfTxDescrRingProc               the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrRingProc
  SizeOfTxDescrState                  the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrState
  SizeOfTxTsContext                   the number of accomplishable value elements in Eth_30_Tc3xx_TxTsContext
  SizeOfUserInitCallouts              the number of accomplishable value elements in Eth_30_Tc3xx_UserInitCallouts
  SizeOfVlanIdBasedQueuingHandling    the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdBasedQueuingHandling
  SizeOfVlanIdRxDescrRingMap          the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdRxDescrRingMap
  SizeOfVlanIdTxDescrRingMap          the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdTxDescrRingMap
  SizeOfVlanPrioTxDescrRingMap        the number of accomplishable value elements in Eth_30_Tc3xx_VlanPrioTxDescrRingMap
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
CONST(Eth_30_Tc3xx_PCConfigsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_PCConfig = {
  { /* Index: 0 Keys: [Config] */
      Eth_30_Tc3xx_ActiveMacAddress.raw         /**< the pointer to Eth_30_Tc3xx_ActiveMacAddress */
    , Eth_30_Tc3xx_EthCtrl                      /**< the pointer to Eth_30_Tc3xx_EthCtrl */
    , Eth_30_Tc3xx_EthCtrlState                 /**< the pointer to Eth_30_Tc3xx_EthCtrlState */
    , Eth_30_Tc3xx_EthCtrlTc3xx                 /**< the pointer to Eth_30_Tc3xx_EthCtrlTc3xx */
    , Eth_30_Tc3xx_EthCtrlTc3xxState            /**< the pointer to Eth_30_Tc3xx_EthCtrlTc3xxState */
    , Eth_30_Tc3xx_EthMeasDataCounter           /**< the pointer to Eth_30_Tc3xx_EthMeasDataCounter */
    , Eth_30_Tc3xx_EthMeasDataCounterReset      /**< the pointer to Eth_30_Tc3xx_EthMeasDataCounterReset */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_EthSwtIfc */
    , Eth_30_Tc3xx_InitialMacAddress            /**< the pointer to Eth_30_Tc3xx_InitialMacAddress */
    , Eth_30_Tc3xx_IsrInfos                     /**< the pointer to Eth_30_Tc3xx_IsrInfos */
    , Eth_30_Tc3xx_IsrIrqEventFuncs             /**< the pointer to Eth_30_Tc3xx_IsrIrqEventFuncs */
    , Eth_30_Tc3xx_MulticastBucketCounters.raw  /**< the pointer to Eth_30_Tc3xx_MulticastBucketCounters */
    , Eth_30_Tc3xx_OptCallouts                  /**< the pointer to Eth_30_Tc3xx_OptCallouts */
    , Eth_30_Tc3xx_PromiscuousModeCounter       /**< the pointer to Eth_30_Tc3xx_PromiscuousModeCounter */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_QosHandling */
    , Eth_30_Tc3xx_RegData                      /**< the pointer to Eth_30_Tc3xx_RegData */
    , Eth_30_Tc3xx_RxBuffer.raw                 /**< the pointer to Eth_30_Tc3xx_RxBuffer */
    , Eth_30_Tc3xx_RxBufferHandling             /**< the pointer to Eth_30_Tc3xx_RxBufferHandling */
    , Eth_30_Tc3xx_RxDescr.raw                  /**< the pointer to Eth_30_Tc3xx_RxDescr */
    , Eth_30_Tc3xx_RxDescrHandling              /**< the pointer to Eth_30_Tc3xx_RxDescrHandling */
    , Eth_30_Tc3xx_RxDescrRingProc.raw          /**< the pointer to Eth_30_Tc3xx_RxDescrRingProc */
    , Eth_30_Tc3xx_RxDescrState.raw             /**< the pointer to Eth_30_Tc3xx_RxDescrState */
    , Eth_30_Tc3xx_RxTsContextStack.raw         /**< the pointer to Eth_30_Tc3xx_RxTsContextStack */
    , Eth_30_Tc3xx_RxTsContextStackPos.raw      /**< the pointer to Eth_30_Tc3xx_RxTsContextStackPos */
    , Eth_30_Tc3xx_RxTxNotificationCallouts     /**< the pointer to Eth_30_Tc3xx_RxTxNotificationCallouts */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_ShaperAvailable */
    , Eth_30_Tc3xx_TimeHandling.raw             /**< the pointer to Eth_30_Tc3xx_TimeHandling */
    , Eth_30_Tc3xx_TsHandling                   /**< the pointer to Eth_30_Tc3xx_TsHandling */
    , Eth_30_Tc3xx_TxBuffer.raw                 /**< the pointer to Eth_30_Tc3xx_TxBuffer */
    , Eth_30_Tc3xx_TxBufferData                 /**< the pointer to Eth_30_Tc3xx_TxBufferData */
    , Eth_30_Tc3xx_TxBufferFreeElemNum.raw      /**< the pointer to Eth_30_Tc3xx_TxBufferFreeElemNum */
    , Eth_30_Tc3xx_TxBufferHandling             /**< the pointer to Eth_30_Tc3xx_TxBufferHandling */
    , Eth_30_Tc3xx_TxBufferState.raw            /**< the pointer to Eth_30_Tc3xx_TxBufferState */
    , Eth_30_Tc3xx_TxDescr.raw                  /**< the pointer to Eth_30_Tc3xx_TxDescr */
    , Eth_30_Tc3xx_TxDescrHandling              /**< the pointer to Eth_30_Tc3xx_TxDescrHandling */
    , Eth_30_Tc3xx_TxDescrRingProc.raw          /**< the pointer to Eth_30_Tc3xx_TxDescrRingProc */
    , Eth_30_Tc3xx_TxDescrState.raw             /**< the pointer to Eth_30_Tc3xx_TxDescrState */
    , Eth_30_Tc3xx_TxTsContext.raw              /**< the pointer to Eth_30_Tc3xx_TxTsContext */
    , Eth_30_Tc3xx_UserInitCallouts             /**< the pointer to Eth_30_Tc3xx_UserInitCallouts */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_VlanIdRxDescrRingMap */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_VlanIdTxDescrRingMap */
    , NULL_PTR                                  /**< the pointer to Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
    , 3072u                                     /**< the number of elements in Eth_30_Tc3xx_RxBuffer */
    , 6144u                                     /**< the number of elements in Eth_30_Tc3xx_TxBuffer */
    , 6u                                        /**< the number of elements in Eth_30_Tc3xx_ActiveMacAddress */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_EthCtrl */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_EthCtrlTc3xx */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_EthSwtIfc */
    , 6u                                        /**< the number of elements in Eth_30_Tc3xx_InitialMacAddress */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_IsrInfos */
    , 3u                                        /**< the number of elements in Eth_30_Tc3xx_IsrIrqEventFuncs */
    , 64u                                       /**< the number of elements in Eth_30_Tc3xx_MulticastBucketCounters */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_OptCallouts */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_QosHandling */
    , 29u                                       /**< the number of elements in Eth_30_Tc3xx_RegData */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxBufferHandling */
    , 2u                                        /**< the number of elements in Eth_30_Tc3xx_RxDescr */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxDescrHandling */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxDescrRingProc */
    , 2u                                        /**< the number of elements in Eth_30_Tc3xx_RxDescrState */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxTsContextStack */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxTsContextStackPos */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_RxTxNotificationCallouts */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_ShaperAvailable */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TimeHandling */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TsHandling */
    , 4u                                        /**< the number of elements in Eth_30_Tc3xx_TxBufferData */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TxBufferFreeElemNum */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TxBufferHandling */
    , 4u                                        /**< the number of elements in Eth_30_Tc3xx_TxBufferState */
    , 4u                                        /**< the number of elements in Eth_30_Tc3xx_TxDescr */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TxDescrHandling */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_TxDescrRingProc */
    , 4u                                        /**< the number of elements in Eth_30_Tc3xx_TxDescrState */
    , 4u                                        /**< the number of elements in Eth_30_Tc3xx_TxTsContext */
    , 1u                                        /**< the number of elements in Eth_30_Tc3xx_UserInitCallouts */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_VlanIdRxDescrRingMap */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_VlanIdTxDescrRingMap */
    , 0u                                        /**< the number of elements in Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
  }
};
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */



/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/**********************************************************************************************************************
  Eth_30_Tc3xx_ConfigDataPtr
**********************************************************************************************************************/
/** 
  \var    Eth_30_Tc3xx_ConfigDataPtr
  \brief  Points to the currently active configuration for Eth_30_Tc3xx
*/ 
#define ETH_30_TC3XX_START_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
P2CONST(Eth_30_Tc3xx_ConfigType, ETH_30_TC3XX_VAR_NOINIT, ETH_30_TC3XX_INIT_DATA) Eth_30_Tc3xx_ConfigDataPtr;
#define ETH_30_TC3XX_STOP_SEC_VAR_NOINIT_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */

/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_Lcfg.c
 *********************************************************************************************************************/


