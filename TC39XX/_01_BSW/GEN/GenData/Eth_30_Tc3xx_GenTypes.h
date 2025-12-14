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
 *              File: Eth_30_Tc3xx_GenTypes.h
 *   Generation Time: 2025-12-14 16:26:31
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (ETH_30_TC3XX_GENTYPES_H)
# define ETH_30_TC3XX_GENTYPES_H

/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 *  INCLUDE
 *********************************************************************************************************************/
# include "Eth_30_Tc3xx_Types.h"
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA TYPES AND STRUCTURES (NOT COMSTACKLIB GENERATED)
**********************************************************************************************************************/
/** 
  \defgroup  Eth_30_Tc3xxPCNonComStackLibTypes  Eth_30_Tc3xx Non ComStackLib Types (PRE_COMPILE)
  \brief  These type definitions are provided by the Eth_30_Tc3xx itself.
  \{
*/ 

/**   \brief  no protected area used */
# define ETH_30_TC3XX_PROTECTED_AREA_DISABLED (0u)

/**  \brief  no static register address used */
# define ETH_30_TC3XX_REGADDR_DYNAMIC         (0u)

/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
/**  \brief  macro for runtime measurement start trigger */
# define Eth_30_Tc3xx_Rtm_Start(Type)

/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
/**  \brief  macro for runtime measurement stop trigger */
# define Eth_30_Tc3xx_Rtm_Stop(Type)

/**  \brief  register base address type abstracting addressable memory space of micro controller */
typedef uint32 Eth_30_Tc3xx_RegBaseAddrType;

/**   \brief  function pointer type defintion for <User>_PreTransceiverInitCallout() */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_PostTransceiverInitCallout() */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType)(uint8);

/**   \brief  function pointer type defintion for <User>_RxBufWarnLvlCallout() */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_UserRxBufWarnLvlCalloutFctPtrType)(uint8, uint8);

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_IrqEventFctPtrType)(uint8);

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(Std_ReturnType, ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthProcessRxFrameFctPtrType)(uint8, Eth_BufIdxType, P2VAR(P2VAR(uint8, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC), P2VAR(uint16, AUTOMATIC, AUTOMATIC), P2VAR(boolean, AUTOMATIC, AUTOMATIC));

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthRxFinishedIndicationFctPtrType)(uint8, Eth_BufIdxType);

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(Std_ReturnType, ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthAdaptBufferLengthFctPtrType)(P2VAR(uint16, AUTOMATIC, AUTOMATIC));

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(Std_ReturnType, ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthPrepareTxFrameFctPtrType)(uint8, Eth_BufIdxType, P2VAR(P2VAR(uint8, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC), P2VAR(uint16, AUTOMATIC, AUTOMATIC));

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(Std_ReturnType, ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthProcessTxFrameFctPtrType)(uint8, Eth_BufIdxType, P2VAR(P2VAR(uint8, AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC), P2VAR(uint16, AUTOMATIC, AUTOMATIC));

/**   \brief  function pointer type defintion for functions called within the interrupt service routine */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthSwtEthTxFinishedIndicationFctPtrType)(uint8, Eth_BufIdxType);

/**   \brief  function pointer type defintion for the Rx-Indication callout */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType)(uint8, Eth_FrameType, boolean, P2VAR(uint8, AUTOMATIC, AUTOMATIC), P2VAR(Eth_DataType, AUTOMATIC, AUTOMATIC), uint16);

/**   \brief  function pointer type defintion for the Tx-Confirmation callout */
typedef P2FUNC(void,           ETH_30_TC3XX_APPL_CODE, Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType)(uint8, uint8);




/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  Eth_30_Tc3xxPCDataSwitches  Eth_30_Tc3xx Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define ETH_30_TC3XX_ACTIVEMACADDRESS                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRL                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ACTIVEMACADDRESSENDIDXOFETHCTRL                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ACTIVEMACADDRESSSTARTIDXOFETHCTRL                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_AUTOSARRTMREGBASEADDROFETHCTRL                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DEMEACCESSEVENTIDOFETHCTRL                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHSWTIFCIDXOFETHCTRL                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHSWTIFCUSEDOFETHCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_FQTSSENABLEDOFETHCTRL                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_INITIALMACADDRESSENDIDXOFETHCTRL                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_INITIALMACADDRESSSTARTIDXOFETHCTRL               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_IPCHECKSUMOFFLOADINGENABLEDOFETHCTRL             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRINFOSENDIDXOFETHCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRINFOSSTARTIDXOFETHCTRL                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRINFOSUSEDOFETHCTRL                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_LOOPCYCLESOFETHCTRL                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MIILOOPCYCLESOFETHCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MULTIQUEUECONFIGENABLEDOFETHCTRL                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MULTICASTBUCKETCOUNTERSENDIDXOFETHCTRL           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MULTICASTBUCKETCOUNTERSSTARTIDXOFETHCTRL         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_NVMBLOCKIDOFETHCTRL                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PROTECTEDAREAIDOFETHCTRL                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PROTOCOLCHECKSUMOFFLOADINGENABLEDOFETHCTRL       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QOSENABLEDOFETHCTRL                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QOSHANDLINGIDXOFETHCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QOSHANDLINGUSEDOFETHCTRL                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGDATAENDIDXOFETHCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGDATASTARTIDXOFETHCTRL                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGDATAUSEDOFETHCTRL                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RESETLOOPCYCLESOFETHCTRL                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERHANDLINGENDIDXOFETHCTRL                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERHANDLINGSTARTIDXOFETHCTRL                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRHANDLINGENDIDXOFETHCTRL                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRHANDLINGSTARTIDXOFETHCTRL                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXINTERRUPTENABLEDOFETHCTRL                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTXNOTIFICATIONCALLOUTSIDXOFETHCTRL             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TIMESYNENABLEDOFETHCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TRCVSPEEDOFETHCTRL                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TSHANDLINGIDXOFETHCTRL                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TSHANDLINGUSEDOFETHCTRL                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERHANDLINGIDXOFETHCTRL                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLINGENDIDXOFETHCTRL                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLINGSTARTIDXOFETHCTRL                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXINTERRUPTENABLEDOFETHCTRL                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDBASEDFRAMEQUEUINGENABLEDOFETHCTRL          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDBASEDQUEUINGHANDLINGUSEDOFETHCTRL          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLSTATE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_CTRLMODEOFETHCTRLSTATE                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PENDINGRXEVENTSOFETHCTRLSTATE                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PENDINGTXEVENTSOFETHCTRLSTATE                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGBASEADDROFETHCTRLSTATE                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLTC3XX                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_AMOUNTOFRXQUEUESOFETHCTRLTC3XX                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_AMOUNTOFTXQUEUESOFETHCTRLTC3XX                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ARMPPSONTIMEENABLEDOFETHCTRLTC3XX                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_CSRCLOCKRANGEOFETHCTRLTC3XX                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLMIIINTERFACEOFETHCTRLTC3XX                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PINROUTINGOFETHCTRLTC3XX                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLTC3XXSTATE                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_READMIIRESULTOFETHCTRLTC3XXSTATE                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXSTATSOFETHCTRLTC3XXSTATE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHMEASDATACOUNTER                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DROPINSUFFRXBUFFOFETHMEASDATACOUNTER             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DROPINSUFFTXBUFFOFETHMEASDATACOUNTER             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_WARNFULLRXBUFFOFETHMEASDATACOUNTER               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHMEASDATACOUNTERRESET                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DROPINSUFFRXBUFFRESETOFETHMEASDATACOUNTERRESET   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHSWTIFC                                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHADAPTBUFFERLENGTHOFETHSWTIFC                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHPREPARETXFRAMEOFETHSWTIFC                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHPROCESSRXFRAMEOFETHSWTIFC                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHPROCESSTXFRAMEOFETHSWTIFC                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHRXFINISHEDINDICATIONOFETHSWTIFC               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHTXFINISHEDINDICATIONOFETHSWTIFC               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_FINALMAGICNUMBER                                 STD_OFF  /**< Deactivateable: 'Eth_30_Tc3xx_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETH_30_TC3XX_INITDATAHASHCODE                                 STD_OFF  /**< Deactivateable: 'Eth_30_Tc3xx_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETH_30_TC3XX_INITIALMACADDRESS                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRINFOS                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRIRQEVENTFUNCSENDIDXOFISRINFOS                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRIRQEVENTFUNCSSTARTIDXOFISRINFOS               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRIRQEVENTFUNCS                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MULTICASTBUCKETCOUNTERS                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_OPTCALLOUTS                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFWARNLVLCALLOUTOFOPTCALLOUTS                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PROMISCUOUSMODECOUNTER                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QOSHANDLING                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SHAPERAVAILABLEENDIDXOFQOSHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SHAPERAVAILABLESTARTIDXOFQOSHANDLING             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLINGIDXOFQOSHANDLING                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANPRIOTXDESCRRINGMAPENDIDXOFQOSHANDLING        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANPRIOTXDESCRRINGMAPSTARTIDXOFQOSHANDLING      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGDATA                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ACCESSMODEOFREGDATA                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_OFFSETOFREGDATA                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VALUEOFREGDATA                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERHANDLING                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ALIGNEDLASTSEGSIZEOFRXBUFFERHANDLING             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ALIGNEDSEGSIZEOFRXBUFFERHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DESCRNUMOFRXBUFFERHANDLING                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MAXFRAMESIZEOFRXBUFFERHANDLING                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERENDIDXOFRXBUFFERHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERSTARTIDXOFRXBUFFERHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SEGNUMOFRXBUFFERHANDLING                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_UNALIGNEDSEGSIZEOFRXBUFFERHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCR                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRHANDLING                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRENDIDXOFRXDESCRHANDLING                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRRINGPROCIDXOFRXDESCRHANDLING              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRSTARTIDXOFRXDESCRHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRSTATEENDIDXOFRXDESCRHANDLING              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRSTATESTARTIDXOFRXDESCRHANDLING            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRRINGPROC                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_CURPROCPOSOFRXDESCRRINGPROC                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRSTATE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MAPPEDBUFFEROFRXDESCRSTATE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACK                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DESCRIDXOFRXTSCONTEXTSTACK                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RINGIDXOFRXTSCONTEXTSTACK                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKPOS                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTXNOTIFICATIONCALLOUTS                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXINDICATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXCONFIRMATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SHAPERAVAILABLE                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFACTIVEMACADDRESS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRL                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLSTATE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLTC3XX                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLTC3XXSTATE                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHMEASDATACOUNTER                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHMEASDATACOUNTERRESET                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHSWTIFC                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFINITIALMACADDRESS                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFISRINFOS                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFISRIRQEVENTFUNCS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFMULTICASTBUCKETCOUNTERS                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFOPTCALLOUTS                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFPROMISCUOUSMODECOUNTER                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFQOSHANDLING                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFREGDATA                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXBUFFER                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXBUFFERHANDLING                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCR                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRHANDLING                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRRINGPROC                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRSTATE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTSCONTEXTSTACK                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTSCONTEXTSTACKPOS                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTXNOTIFICATIONCALLOUTS                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFSHAPERAVAILABLE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTIMEHANDLING                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTSHANDLING                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFER                                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERDATA                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERFREEELEMNUM                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERHANDLING                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERSTATE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCR                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRHANDLING                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRRINGPROC                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRSTATE                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXTSCONTEXT                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFUSERINITCALLOUTS                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDBASEDQUEUINGHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDRXDESCRRINGMAP                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDTXDESCRRINGMAP                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANPRIOTXDESCRRINGMAP                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TIMEHANDLING                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_LATESTCORRTIMEOFTIMEHANDLING                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_LATESTHWTIMEOFTIMEHANDLING                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RATERATIOOFTIMEHANDLING                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TSHANDLING                                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKENDIDXOFTSHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKPOSIDXOFTSHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKSTARTIDXOFTSHANDLING             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TIMEHANDLINGIDXOFTSHANDLING                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXTSCONTEXTENDIDXOFTSHANDLING                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXTSCONTEXTSTARTIDXOFTSHANDLING                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFER                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERDATA                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_LENGTHOFTXBUFFERDATA                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_STARTPOSOFTXBUFFERDATA                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERFREEELEMNUM                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERHANDLING                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ALIGNEDSEGSIZEOFTXBUFFERHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_BUFFERNUMOFTXBUFFERHANDLING                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DESCRNUMOFTXBUFFERHANDLING                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MAXBUFFERLENOFTXBUFFERHANDLING                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERDATAENDIDXOFTXBUFFERHANDLING             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERDATASTARTIDXOFTXBUFFERHANDLING           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERENDIDXOFTXBUFFERHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERFREEELEMNUMIDXOFTXBUFFERHANDLING         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERSTARTIDXOFTXBUFFERHANDLING               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERSTATEENDIDXOFTXBUFFERHANDLING            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERSTATESTARTIDXOFTXBUFFERHANDLING          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERSTATE                                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_BUSYOFTXBUFFERSTATE                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TSREQUESTEDOFTXBUFFERSTATE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ULTXCONFSTATEOFTXBUFFERSTATE                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCR                                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLING                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRENDIDXOFTXDESCRHANDLING                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRRINGPROCIDXOFTXDESCRHANDLING              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRSTARTIDXOFTXDESCRHANDLING                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRSTATEENDIDXOFTXDESCRHANDLING              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRSTATESTARTIDXOFTXDESCRHANDLING            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRRINGPROC                                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_CURPROCPOSOFTXDESCRRINGPROC                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_FREEPOSOFTXDESCRRINGPROC                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRSTATE                                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MAPPEDBUFFEROFTXDESCRSTATE                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXREADYOFTXDESCRSTATE                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXTSCONTEXT                                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_DESCRIDXOFTXTSCONTEXT                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RINGIDXOFTXTSCONTEXT                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_USERINITCALLOUTS                                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_POSTINITUSERCALLOUTOFUSERINITCALLOUTS            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PREINITUSERCALLOUTOFUSERINITCALLOUTS             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDBASEDQUEUINGHANDLING                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLINGIDXOFVLANIDBASEDQUEUINGHANDLING   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDRXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDRXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDTXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDTXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDRXDESCRRINGMAP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QUEUEINDEXOFVLANIDRXDESCRRINGMAP                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDOFVLANIDRXDESCRRINGMAP                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDTXDESCRRINGMAP                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QUEUEINDEXOFVLANIDTXDESCRRINGMAP                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDOFVLANIDTXDESCRRINGMAP                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANPRIOTXDESCRRINGMAP                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PCCONFIG                                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ACTIVEMACADDRESSOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLSTATEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLTC3XXOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHCTRLTC3XXSTATEOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHMEASDATACOUNTEROFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHMEASDATACOUNTERRESETOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ETHSWTIFCOFPCCONFIG                              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_FINALMAGICNUMBEROFPCCONFIG                       STD_OFF  /**< Deactivateable: 'Eth_30_Tc3xx_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define ETH_30_TC3XX_INITDATAHASHCODEOFPCCONFIG                       STD_OFF  /**< Deactivateable: 'Eth_30_Tc3xx_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define ETH_30_TC3XX_INITIALMACADDRESSOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRINFOSOFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_ISRIRQEVENTFUNCSOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_MULTICASTBUCKETCOUNTERSOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_OPTCALLOUTSOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_PROMISCUOUSMODECOUNTEROFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_QOSHANDLINGOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_REGDATAOFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFERHANDLINGOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXBUFFEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRHANDLINGOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCROFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRRINGPROCOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXDESCRSTATEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTSCONTEXTSTACKPOSOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_RXTXNOTIFICATIONCALLOUTSOFPCCONFIG               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SHAPERAVAILABLEOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFACTIVEMACADDRESSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLSTATEOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLTC3XXOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHCTRLTC3XXSTATEOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHMEASDATACOUNTEROFPCCONFIG               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHMEASDATACOUNTERRESETOFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFETHSWTIFCOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFINITIALMACADDRESSOFPCCONFIG                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFISRINFOSOFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFISRIRQEVENTFUNCSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFMULTICASTBUCKETCOUNTERSOFPCCONFIG          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFOPTCALLOUTSOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFPROMISCUOUSMODECOUNTEROFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFQOSHANDLINGOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFREGDATAOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXBUFFERHANDLINGOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXBUFFEROFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRHANDLINGOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCROFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRRINGPROCOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXDESCRSTATEOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTSCONTEXTSTACKOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTSCONTEXTSTACKPOSOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFRXTXNOTIFICATIONCALLOUTSOFPCCONFIG         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFSHAPERAVAILABLEOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTIMEHANDLINGOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTSHANDLINGOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERDATAOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERFREEELEMNUMOFPCCONFIG              STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERHANDLINGOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFEROFPCCONFIG                         STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXBUFFERSTATEOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRHANDLINGOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCROFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRRINGPROCOFPCCONFIG                  STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXDESCRSTATEOFPCCONFIG                     STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFTXTSCONTEXTOFPCCONFIG                      STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFUSERINITCALLOUTSOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDBASEDQUEUINGHANDLINGOFPCCONFIG       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDRXDESCRRINGMAPOFPCCONFIG             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANIDTXDESCRRINGMAPOFPCCONFIG             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_SIZEOFVLANPRIOTXDESCRRINGMAPOFPCCONFIG           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TIMEHANDLINGOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TSHANDLINGOFPCCONFIG                             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERDATAOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERFREEELEMNUMOFPCCONFIG                    STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERHANDLINGOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFEROFPCCONFIG                               STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXBUFFERSTATEOFPCCONFIG                          STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRHANDLINGOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCROFPCCONFIG                                STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRRINGPROCOFPCCONFIG                        STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXDESCRSTATEOFPCCONFIG                           STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_TXTSCONTEXTOFPCCONFIG                            STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_USERINITCALLOUTSOFPCCONFIG                       STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDBASEDQUEUINGHANDLINGOFPCCONFIG             STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDRXDESCRRINGMAPOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANIDTXDESCRRINGMAPOFPCCONFIG                   STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
#define ETH_30_TC3XX_VLANPRIOTXDESCRRINGMAPOFPCCONFIG                 STD_ON  /**< This preprocessing switch is always STD_ON because the PrecompilePreprocessingStrategy is RUNTIME_CHECKING and feature deactivation conditions are not available. */
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCMinNumericValueDefines  Eth_30_Tc3xx Min Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the minimum value in numerical based data.
  \{
*/ 
#define ETH_30_TC3XX_MIN_ACTIVEMACADDRESS                             0u
#define ETH_30_TC3XX_MIN_PENDINGRXEVENTSOFETHCTRLSTATE                0u
#define ETH_30_TC3XX_MIN_PENDINGTXEVENTSOFETHCTRLSTATE                0u
#define ETH_30_TC3XX_MIN_READMIIRESULTOFETHCTRLTC3XXSTATE             0u
#define ETH_30_TC3XX_MIN_DROPINSUFFRXBUFFOFETHMEASDATACOUNTER         0uL
#define ETH_30_TC3XX_MIN_DROPINSUFFTXBUFFOFETHMEASDATACOUNTER         0uL
#define ETH_30_TC3XX_MIN_WARNFULLRXBUFFOFETHMEASDATACOUNTER           0uL
#define ETH_30_TC3XX_MIN_DROPINSUFFRXBUFFRESETOFETHMEASDATACOUNTERRESET 0uL
#define ETH_30_TC3XX_MIN_MULTICASTBUCKETCOUNTERS                      0u
#define ETH_30_TC3XX_MIN_PROMISCUOUSMODECOUNTER                       0u
#define ETH_30_TC3XX_MIN_RXBUFFER                                     0u
#define ETH_30_TC3XX_MIN_CURPROCPOSOFRXDESCRRINGPROC                  0u
#define ETH_30_TC3XX_MIN_MAPPEDBUFFEROFRXDESCRSTATE                   0u
#define ETH_30_TC3XX_MIN_DESCRIDXOFRXTSCONTEXTSTACK                   0u
#define ETH_30_TC3XX_MIN_RINGIDXOFRXTSCONTEXTSTACK                    0u
#define ETH_30_TC3XX_MIN_RXTSCONTEXTSTACKPOS                          -128
#define ETH_30_TC3XX_MIN_TXBUFFER                                     0u
#define ETH_30_TC3XX_MIN_TXBUFFERFREEELEMNUM                          0u
#define ETH_30_TC3XX_MIN_ULTXCONFSTATEOFTXBUFFERSTATE                 0u
#define ETH_30_TC3XX_MIN_CURPROCPOSOFTXDESCRRINGPROC                  0u
#define ETH_30_TC3XX_MIN_FREEPOSOFTXDESCRRINGPROC                     0u
#define ETH_30_TC3XX_MIN_MAPPEDBUFFEROFTXDESCRSTATE                   0u
#define ETH_30_TC3XX_MIN_DESCRIDXOFTXTSCONTEXT                        0u
#define ETH_30_TC3XX_MIN_RINGIDXOFTXTSCONTEXT                         0u
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCMaxNumericValueDefines  Eth_30_Tc3xx Max Numeric Value Defines (PRE_COMPILE)
  \brief  These defines are used to implement against the maximum value in numerical based data.
  \{
*/ 
#define ETH_30_TC3XX_MAX_ACTIVEMACADDRESS                             255u
#define ETH_30_TC3XX_MAX_PENDINGRXEVENTSOFETHCTRLSTATE                65535u
#define ETH_30_TC3XX_MAX_PENDINGTXEVENTSOFETHCTRLSTATE                65535u
#define ETH_30_TC3XX_MAX_READMIIRESULTOFETHCTRLTC3XXSTATE             65535u
#define ETH_30_TC3XX_MAX_DROPINSUFFRXBUFFOFETHMEASDATACOUNTER         4294967295uL
#define ETH_30_TC3XX_MAX_DROPINSUFFTXBUFFOFETHMEASDATACOUNTER         4294967295uL
#define ETH_30_TC3XX_MAX_WARNFULLRXBUFFOFETHMEASDATACOUNTER           4294967295uL
#define ETH_30_TC3XX_MAX_DROPINSUFFRXBUFFRESETOFETHMEASDATACOUNTERRESET 4294967295uL
#define ETH_30_TC3XX_MAX_MULTICASTBUCKETCOUNTERS                      255u
#define ETH_30_TC3XX_MAX_PROMISCUOUSMODECOUNTER                       255u
#define ETH_30_TC3XX_MAX_RXBUFFER                                     255u
#define ETH_30_TC3XX_MAX_CURPROCPOSOFRXDESCRRINGPROC                  255u
#define ETH_30_TC3XX_MAX_MAPPEDBUFFEROFRXDESCRSTATE                   65535u
#define ETH_30_TC3XX_MAX_DESCRIDXOFRXTSCONTEXTSTACK                   255u
#define ETH_30_TC3XX_MAX_RINGIDXOFRXTSCONTEXTSTACK                    255u
#define ETH_30_TC3XX_MAX_RXTSCONTEXTSTACKPOS                          127
#define ETH_30_TC3XX_MAX_TXBUFFER                                     255u
#define ETH_30_TC3XX_MAX_TXBUFFERFREEELEMNUM                          65535u
#define ETH_30_TC3XX_MAX_ULTXCONFSTATEOFTXBUFFERSTATE                 255u
#define ETH_30_TC3XX_MAX_CURPROCPOSOFTXDESCRRINGPROC                  255u
#define ETH_30_TC3XX_MAX_FREEPOSOFTXDESCRRINGPROC                     255u
#define ETH_30_TC3XX_MAX_MAPPEDBUFFEROFTXDESCRSTATE                   255u
#define ETH_30_TC3XX_MAX_DESCRIDXOFTXTSCONTEXT                        255u
#define ETH_30_TC3XX_MAX_RINGIDXOFTXTSCONTEXT                         255u
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCNoReferenceDefines  Eth_30_Tc3xx No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define ETH_30_TC3XX_NO_DEMEACCESSEVENTIDOFETHCTRL                    255u
#define ETH_30_TC3XX_NO_ETHSWTIFCIDXOFETHCTRL                         255u
#define ETH_30_TC3XX_NO_ISRINFOSENDIDXOFETHCTRL                       255u
#define ETH_30_TC3XX_NO_ISRINFOSSTARTIDXOFETHCTRL                     255u
#define ETH_30_TC3XX_NO_LOOPCYCLESOFETHCTRL                           65535u
#define ETH_30_TC3XX_NO_MIILOOPCYCLESOFETHCTRL                        65535u
#define ETH_30_TC3XX_NO_NVMBLOCKIDOFETHCTRL                           255u
#define ETH_30_TC3XX_NO_QOSHANDLINGIDXOFETHCTRL                       255u
#define ETH_30_TC3XX_NO_REGDATAENDIDXOFETHCTRL                        255u
#define ETH_30_TC3XX_NO_REGDATASTARTIDXOFETHCTRL                      255u
#define ETH_30_TC3XX_NO_RESETLOOPCYCLESOFETHCTRL                      65535u
#define ETH_30_TC3XX_NO_TRCVSPEEDOFETHCTRL                            4294967295uL
#define ETH_30_TC3XX_NO_TSHANDLINGIDXOFETHCTRL                        255u
#define ETH_30_TC3XX_NO_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL        255u
#define ETH_30_TC3XX_NO_AMOUNTOFRXQUEUESOFETHCTRLTC3XX                255u
#define ETH_30_TC3XX_NO_AMOUNTOFTXQUEUESOFETHCTRLTC3XX                255u
#define ETH_30_TC3XX_NO_CSRCLOCKRANGEOFETHCTRLTC3XX                   65535u
#define ETH_30_TC3XX_NO_PINROUTINGOFETHCTRLTC3XX                      4294967295uL
#define ETH_30_TC3XX_NO_OFFSETOFREGDATA                               65535u
#define ETH_30_TC3XX_NO_VALUEOFREGDATA                                4294967295uL
#define ETH_30_TC3XX_NO_ALIGNEDLASTSEGSIZEOFRXBUFFERHANDLING          65535u
#define ETH_30_TC3XX_NO_ALIGNEDSEGSIZEOFRXBUFFERHANDLING              65535u
#define ETH_30_TC3XX_NO_DESCRNUMOFRXBUFFERHANDLING                    255u
#define ETH_30_TC3XX_NO_MAXFRAMESIZEOFRXBUFFERHANDLING                65535u
#define ETH_30_TC3XX_NO_SEGNUMOFRXBUFFERHANDLING                      255u
#define ETH_30_TC3XX_NO_UNALIGNEDSEGSIZEOFRXBUFFERHANDLING            65535u
#define ETH_30_TC3XX_NO_LENGTHOFTXBUFFERDATA                          65535u
#define ETH_30_TC3XX_NO_STARTPOSOFTXBUFFERDATA                        65535u
#define ETH_30_TC3XX_NO_ALIGNEDSEGSIZEOFTXBUFFERHANDLING              65535u
#define ETH_30_TC3XX_NO_BUFFERNUMOFTXBUFFERHANDLING                   255u
#define ETH_30_TC3XX_NO_DESCRNUMOFTXBUFFERHANDLING                    255u
#define ETH_30_TC3XX_NO_MAXBUFFERLENOFTXBUFFERHANDLING                65535u
#define ETH_30_TC3XX_NO_QUEUEINDEXOFVLANIDRXDESCRRINGMAP              255u
#define ETH_30_TC3XX_NO_VLANIDOFVLANIDRXDESCRRINGMAP                  255u
#define ETH_30_TC3XX_NO_QUEUEINDEXOFVLANIDTXDESCRRINGMAP              255u
#define ETH_30_TC3XX_NO_VLANIDOFVLANIDTXDESCRRINGMAP                  255u
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCEnumExistsDefines  Eth_30_Tc3xx Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define ETH_30_TC3XX_EXISTS_USER_MODE_ACCESSMODEOFREGDATA             STD_ON
#define ETH_30_TC3XX_EXISTS_SUPERVISOR_MODE_ACCESSMODEOFREGDATA       STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCEnumDefines  Eth_30_Tc3xx Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define ETH_30_TC3XX_USER_MODE_ACCESSMODEOFREGDATA                    0x00u
#define ETH_30_TC3XX_SUPERVISOR_MODE_ACCESSMODEOFREGDATA              0x01u
#define ETH_30_TC3XX_DESCRIPTOR_NOT_READY_TXREADYOFTXDESCRSTATE       0x00u
#define ETH_30_TC3XX_DESCRIPTOR_READY_TXREADYOFTXDESCRSTATE           0x01u
#define ETH_30_TC3XX_DESCRIPTOR_TRANSMITTED_TXREADYOFTXDESCRSTATE     0x02u
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCIsReducedToDefineDefines  Eth_30_Tc3xx Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define ETH_30_TC3XX_ISDEF_ACTIVEMACADDRESSENDIDXOFETHCTRL            STD_OFF
#define ETH_30_TC3XX_ISDEF_ACTIVEMACADDRESSSTARTIDXOFETHCTRL          STD_OFF
#define ETH_30_TC3XX_ISDEF_AUTOSARRTMREGBASEADDROFETHCTRL             STD_OFF
#define ETH_30_TC3XX_ISDEF_DEMEACCESSEVENTIDOFETHCTRL                 STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHSWTIFCIDXOFETHCTRL                      STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHSWTIFCUSEDOFETHCTRL                     STD_OFF
#define ETH_30_TC3XX_ISDEF_FQTSSENABLEDOFETHCTRL                      STD_OFF
#define ETH_30_TC3XX_ISDEF_INITIALMACADDRESSENDIDXOFETHCTRL           STD_OFF
#define ETH_30_TC3XX_ISDEF_INITIALMACADDRESSSTARTIDXOFETHCTRL         STD_OFF
#define ETH_30_TC3XX_ISDEF_IPCHECKSUMOFFLOADINGENABLEDOFETHCTRL       STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRINFOSENDIDXOFETHCTRL                    STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRINFOSSTARTIDXOFETHCTRL                  STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRINFOSUSEDOFETHCTRL                      STD_OFF
#define ETH_30_TC3XX_ISDEF_LOOPCYCLESOFETHCTRL                        STD_OFF
#define ETH_30_TC3XX_ISDEF_MIILOOPCYCLESOFETHCTRL                     STD_OFF
#define ETH_30_TC3XX_ISDEF_MULTIQUEUECONFIGENABLEDOFETHCTRL           STD_OFF
#define ETH_30_TC3XX_ISDEF_MULTICASTBUCKETCOUNTERSENDIDXOFETHCTRL     STD_OFF
#define ETH_30_TC3XX_ISDEF_MULTICASTBUCKETCOUNTERSSTARTIDXOFETHCTRL   STD_OFF
#define ETH_30_TC3XX_ISDEF_NVMBLOCKIDOFETHCTRL                        STD_OFF
#define ETH_30_TC3XX_ISDEF_PROTECTEDAREAIDOFETHCTRL                   STD_OFF
#define ETH_30_TC3XX_ISDEF_PROTOCOLCHECKSUMOFFLOADINGENABLEDOFETHCTRL STD_OFF
#define ETH_30_TC3XX_ISDEF_QOSENABLEDOFETHCTRL                        STD_OFF
#define ETH_30_TC3XX_ISDEF_QOSHANDLINGIDXOFETHCTRL                    STD_OFF
#define ETH_30_TC3XX_ISDEF_QOSHANDLINGUSEDOFETHCTRL                   STD_OFF
#define ETH_30_TC3XX_ISDEF_REGDATAENDIDXOFETHCTRL                     STD_OFF
#define ETH_30_TC3XX_ISDEF_REGDATASTARTIDXOFETHCTRL                   STD_OFF
#define ETH_30_TC3XX_ISDEF_REGDATAUSEDOFETHCTRL                       STD_OFF
#define ETH_30_TC3XX_ISDEF_RESETLOOPCYCLESOFETHCTRL                   STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFERHANDLINGENDIDXOFETHCTRL            STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFERHANDLINGSTARTIDXOFETHCTRL          STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRHANDLINGENDIDXOFETHCTRL             STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRHANDLINGSTARTIDXOFETHCTRL           STD_OFF
#define ETH_30_TC3XX_ISDEF_RXINTERRUPTENABLEDOFETHCTRL                STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTXNOTIFICATIONCALLOUTSIDXOFETHCTRL       STD_OFF
#define ETH_30_TC3XX_ISDEF_TIMESYNENABLEDOFETHCTRL                    STD_OFF
#define ETH_30_TC3XX_ISDEF_TRCVSPEEDOFETHCTRL                         STD_OFF
#define ETH_30_TC3XX_ISDEF_TSHANDLINGIDXOFETHCTRL                     STD_OFF
#define ETH_30_TC3XX_ISDEF_TSHANDLINGUSEDOFETHCTRL                    STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERHANDLINGIDXOFETHCTRL               STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRHANDLINGENDIDXOFETHCTRL             STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRHANDLINGSTARTIDXOFETHCTRL           STD_OFF
#define ETH_30_TC3XX_ISDEF_TXINTERRUPTENABLEDOFETHCTRL                STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDBASEDFRAMEQUEUINGENABLEDOFETHCTRL    STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL     STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDBASEDQUEUINGHANDLINGUSEDOFETHCTRL    STD_OFF
#define ETH_30_TC3XX_ISDEF_AMOUNTOFRXQUEUESOFETHCTRLTC3XX             STD_OFF
#define ETH_30_TC3XX_ISDEF_AMOUNTOFTXQUEUESOFETHCTRLTC3XX             STD_OFF
#define ETH_30_TC3XX_ISDEF_ARMPPSONTIMEENABLEDOFETHCTRLTC3XX          STD_OFF
#define ETH_30_TC3XX_ISDEF_CSRCLOCKRANGEOFETHCTRLTC3XX                STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHCTRLMIIINTERFACEOFETHCTRLTC3XX          STD_OFF
#define ETH_30_TC3XX_ISDEF_PINROUTINGOFETHCTRLTC3XX                   STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHADAPTBUFFERLENGTHOFETHSWTIFC            STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHPREPARETXFRAMEOFETHSWTIFC               STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHPROCESSRXFRAMEOFETHSWTIFC               STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHPROCESSTXFRAMEOFETHSWTIFC               STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHRXFINISHEDINDICATIONOFETHSWTIFC         STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHTXFINISHEDINDICATIONOFETHSWTIFC         STD_OFF
#define ETH_30_TC3XX_ISDEF_INITIALMACADDRESS                          STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRIRQEVENTFUNCSENDIDXOFISRINFOS           STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRIRQEVENTFUNCSSTARTIDXOFISRINFOS         STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRIRQEVENTFUNCS                           STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFWARNLVLCALLOUTOFOPTCALLOUTS           STD_OFF
#define ETH_30_TC3XX_ISDEF_SHAPERAVAILABLEENDIDXOFQOSHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_SHAPERAVAILABLESTARTIDXOFQOSHANDLING       STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRHANDLINGIDXOFQOSHANDLING            STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANPRIOTXDESCRRINGMAPENDIDXOFQOSHANDLING  STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANPRIOTXDESCRRINGMAPSTARTIDXOFQOSHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_ACCESSMODEOFREGDATA                        STD_OFF
#define ETH_30_TC3XX_ISDEF_OFFSETOFREGDATA                            STD_OFF
#define ETH_30_TC3XX_ISDEF_VALUEOFREGDATA                             STD_OFF
#define ETH_30_TC3XX_ISDEF_ALIGNEDLASTSEGSIZEOFRXBUFFERHANDLING       STD_OFF
#define ETH_30_TC3XX_ISDEF_ALIGNEDSEGSIZEOFRXBUFFERHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_DESCRNUMOFRXBUFFERHANDLING                 STD_OFF
#define ETH_30_TC3XX_ISDEF_MAXFRAMESIZEOFRXBUFFERHANDLING             STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFERENDIDXOFRXBUFFERHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFERSTARTIDXOFRXBUFFERHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_SEGNUMOFRXBUFFERHANDLING                   STD_OFF
#define ETH_30_TC3XX_ISDEF_UNALIGNEDSEGSIZEOFRXBUFFERHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRENDIDXOFRXDESCRHANDLING             STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRRINGPROCIDXOFRXDESCRHANDLING        STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRSTARTIDXOFRXDESCRHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRSTATEENDIDXOFRXDESCRHANDLING        STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRSTATESTARTIDXOFRXDESCRHANDLING      STD_OFF
#define ETH_30_TC3XX_ISDEF_RXINDICATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS STD_OFF
#define ETH_30_TC3XX_ISDEF_TXCONFIRMATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS STD_OFF
#define ETH_30_TC3XX_ISDEF_SHAPERAVAILABLE                            STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTSCONTEXTSTACKENDIDXOFTSHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTSCONTEXTSTACKPOSIDXOFTSHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTSCONTEXTSTACKSTARTIDXOFTSHANDLING       STD_OFF
#define ETH_30_TC3XX_ISDEF_TIMEHANDLINGIDXOFTSHANDLING                STD_OFF
#define ETH_30_TC3XX_ISDEF_TXTSCONTEXTENDIDXOFTSHANDLING              STD_OFF
#define ETH_30_TC3XX_ISDEF_TXTSCONTEXTSTARTIDXOFTSHANDLING            STD_OFF
#define ETH_30_TC3XX_ISDEF_LENGTHOFTXBUFFERDATA                       STD_OFF
#define ETH_30_TC3XX_ISDEF_STARTPOSOFTXBUFFERDATA                     STD_OFF
#define ETH_30_TC3XX_ISDEF_ALIGNEDSEGSIZEOFTXBUFFERHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_BUFFERNUMOFTXBUFFERHANDLING                STD_OFF
#define ETH_30_TC3XX_ISDEF_DESCRNUMOFTXBUFFERHANDLING                 STD_OFF
#define ETH_30_TC3XX_ISDEF_MAXBUFFERLENOFTXBUFFERHANDLING             STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERDATAENDIDXOFTXBUFFERHANDLING       STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERDATASTARTIDXOFTXBUFFERHANDLING     STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERENDIDXOFTXBUFFERHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERFREEELEMNUMIDXOFTXBUFFERHANDLING   STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERSTARTIDXOFTXBUFFERHANDLING         STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERSTATEENDIDXOFTXBUFFERHANDLING      STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERSTATESTARTIDXOFTXBUFFERHANDLING    STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRENDIDXOFTXDESCRHANDLING             STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRRINGPROCIDXOFTXDESCRHANDLING        STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRSTARTIDXOFTXDESCRHANDLING           STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRSTATEENDIDXOFTXDESCRHANDLING        STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRSTATESTARTIDXOFTXDESCRHANDLING      STD_OFF
#define ETH_30_TC3XX_ISDEF_POSTINITUSERCALLOUTOFUSERINITCALLOUTS      STD_OFF
#define ETH_30_TC3XX_ISDEF_PREINITUSERCALLOUTOFUSERINITCALLOUTS       STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRHANDLINGIDXOFVLANIDBASEDQUEUINGHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDRXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDRXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDTXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDTXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING STD_OFF
#define ETH_30_TC3XX_ISDEF_QUEUEINDEXOFVLANIDRXDESCRRINGMAP           STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDOFVLANIDRXDESCRRINGMAP               STD_OFF
#define ETH_30_TC3XX_ISDEF_QUEUEINDEXOFVLANIDTXDESCRRINGMAP           STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDOFVLANIDTXDESCRRINGMAP               STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANPRIOTXDESCRRINGMAP                     STD_OFF
#define ETH_30_TC3XX_ISDEF_ACTIVEMACADDRESSOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHCTRLOFPCCONFIG                          STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHCTRLSTATEOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHCTRLTC3XXOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHCTRLTC3XXSTATEOFPCCONFIG                STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHMEASDATACOUNTEROFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHMEASDATACOUNTERRESETOFPCCONFIG          STD_OFF
#define ETH_30_TC3XX_ISDEF_ETHSWTIFCOFPCCONFIG                        STD_OFF
#define ETH_30_TC3XX_ISDEF_INITIALMACADDRESSOFPCCONFIG                STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRINFOSOFPCCONFIG                         STD_OFF
#define ETH_30_TC3XX_ISDEF_ISRIRQEVENTFUNCSOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_MULTICASTBUCKETCOUNTERSOFPCCONFIG          STD_OFF
#define ETH_30_TC3XX_ISDEF_OPTCALLOUTSOFPCCONFIG                      STD_OFF
#define ETH_30_TC3XX_ISDEF_PROMISCUOUSMODECOUNTEROFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_QOSHANDLINGOFPCCONFIG                      STD_OFF
#define ETH_30_TC3XX_ISDEF_REGDATAOFPCCONFIG                          STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFERHANDLINGOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_RXBUFFEROFPCCONFIG                         STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRHANDLINGOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCROFPCCONFIG                          STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRRINGPROCOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_RXDESCRSTATEOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTSCONTEXTSTACKOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTSCONTEXTSTACKPOSOFPCCONFIG              STD_OFF
#define ETH_30_TC3XX_ISDEF_RXTXNOTIFICATIONCALLOUTSOFPCCONFIG         STD_OFF
#define ETH_30_TC3XX_ISDEF_SHAPERAVAILABLEOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFACTIVEMACADDRESSOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFETHCTRLOFPCCONFIG                    STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFETHCTRLTC3XXOFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFETHSWTIFCOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFINITIALMACADDRESSOFPCCONFIG          STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFISRINFOSOFPCCONFIG                   STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFISRIRQEVENTFUNCSOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFMULTICASTBUCKETCOUNTERSOFPCCONFIG    STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFOPTCALLOUTSOFPCCONFIG                STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFQOSHANDLINGOFPCCONFIG                STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFREGDATAOFPCCONFIG                    STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXBUFFERHANDLINGOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXBUFFEROFPCCONFIG                   STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXDESCRHANDLINGOFPCCONFIG            STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXDESCROFPCCONFIG                    STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXDESCRRINGPROCOFPCCONFIG            STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXDESCRSTATEOFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXTSCONTEXTSTACKOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXTSCONTEXTSTACKPOSOFPCCONFIG        STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFRXTXNOTIFICATIONCALLOUTSOFPCCONFIG   STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFSHAPERAVAILABLEOFPCCONFIG            STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTIMEHANDLINGOFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTSHANDLINGOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXBUFFERDATAOFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXBUFFERFREEELEMNUMOFPCCONFIG        STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXBUFFERHANDLINGOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXBUFFEROFPCCONFIG                   STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXBUFFERSTATEOFPCCONFIG              STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXDESCRHANDLINGOFPCCONFIG            STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXDESCROFPCCONFIG                    STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXDESCRRINGPROCOFPCCONFIG            STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXDESCRSTATEOFPCCONFIG               STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFTXTSCONTEXTOFPCCONFIG                STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFUSERINITCALLOUTSOFPCCONFIG           STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFVLANIDBASEDQUEUINGHANDLINGOFPCCONFIG STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFVLANIDRXDESCRRINGMAPOFPCCONFIG       STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFVLANIDTXDESCRRINGMAPOFPCCONFIG       STD_OFF
#define ETH_30_TC3XX_ISDEF_SIZEOFVLANPRIOTXDESCRRINGMAPOFPCCONFIG     STD_OFF
#define ETH_30_TC3XX_ISDEF_TIMEHANDLINGOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_TSHANDLINGOFPCCONFIG                       STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERDATAOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERFREEELEMNUMOFPCCONFIG              STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERHANDLINGOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFEROFPCCONFIG                         STD_OFF
#define ETH_30_TC3XX_ISDEF_TXBUFFERSTATEOFPCCONFIG                    STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRHANDLINGOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCROFPCCONFIG                          STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRRINGPROCOFPCCONFIG                  STD_OFF
#define ETH_30_TC3XX_ISDEF_TXDESCRSTATEOFPCCONFIG                     STD_OFF
#define ETH_30_TC3XX_ISDEF_TXTSCONTEXTOFPCCONFIG                      STD_OFF
#define ETH_30_TC3XX_ISDEF_USERINITCALLOUTSOFPCCONFIG                 STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDBASEDQUEUINGHANDLINGOFPCCONFIG       STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDRXDESCRRINGMAPOFPCCONFIG             STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANIDTXDESCRRINGMAPOFPCCONFIG             STD_OFF
#define ETH_30_TC3XX_ISDEF_VLANPRIOTXDESCRRINGMAPOFPCCONFIG           STD_OFF
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCEqualsAlwaysToDefines  Eth_30_Tc3xx Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define ETH_30_TC3XX_EQ2_ACTIVEMACADDRESSENDIDXOFETHCTRL              
#define ETH_30_TC3XX_EQ2_ACTIVEMACADDRESSSTARTIDXOFETHCTRL            
#define ETH_30_TC3XX_EQ2_AUTOSARRTMREGBASEADDROFETHCTRL               
#define ETH_30_TC3XX_EQ2_DEMEACCESSEVENTIDOFETHCTRL                   
#define ETH_30_TC3XX_EQ2_ETHSWTIFCIDXOFETHCTRL                        
#define ETH_30_TC3XX_EQ2_ETHSWTIFCUSEDOFETHCTRL                       
#define ETH_30_TC3XX_EQ2_FQTSSENABLEDOFETHCTRL                        
#define ETH_30_TC3XX_EQ2_INITIALMACADDRESSENDIDXOFETHCTRL             
#define ETH_30_TC3XX_EQ2_INITIALMACADDRESSSTARTIDXOFETHCTRL           
#define ETH_30_TC3XX_EQ2_IPCHECKSUMOFFLOADINGENABLEDOFETHCTRL         
#define ETH_30_TC3XX_EQ2_ISRINFOSENDIDXOFETHCTRL                      
#define ETH_30_TC3XX_EQ2_ISRINFOSSTARTIDXOFETHCTRL                    
#define ETH_30_TC3XX_EQ2_ISRINFOSUSEDOFETHCTRL                        
#define ETH_30_TC3XX_EQ2_LOOPCYCLESOFETHCTRL                          
#define ETH_30_TC3XX_EQ2_MIILOOPCYCLESOFETHCTRL                       
#define ETH_30_TC3XX_EQ2_MULTIQUEUECONFIGENABLEDOFETHCTRL             
#define ETH_30_TC3XX_EQ2_MULTICASTBUCKETCOUNTERSENDIDXOFETHCTRL       
#define ETH_30_TC3XX_EQ2_MULTICASTBUCKETCOUNTERSSTARTIDXOFETHCTRL     
#define ETH_30_TC3XX_EQ2_NVMBLOCKIDOFETHCTRL                          
#define ETH_30_TC3XX_EQ2_PROTECTEDAREAIDOFETHCTRL                     
#define ETH_30_TC3XX_EQ2_PROTOCOLCHECKSUMOFFLOADINGENABLEDOFETHCTRL   
#define ETH_30_TC3XX_EQ2_QOSENABLEDOFETHCTRL                          
#define ETH_30_TC3XX_EQ2_QOSHANDLINGIDXOFETHCTRL                      
#define ETH_30_TC3XX_EQ2_QOSHANDLINGUSEDOFETHCTRL                     
#define ETH_30_TC3XX_EQ2_REGDATAENDIDXOFETHCTRL                       
#define ETH_30_TC3XX_EQ2_REGDATASTARTIDXOFETHCTRL                     
#define ETH_30_TC3XX_EQ2_REGDATAUSEDOFETHCTRL                         
#define ETH_30_TC3XX_EQ2_RESETLOOPCYCLESOFETHCTRL                     
#define ETH_30_TC3XX_EQ2_RXBUFFERHANDLINGENDIDXOFETHCTRL              
#define ETH_30_TC3XX_EQ2_RXBUFFERHANDLINGSTARTIDXOFETHCTRL            
#define ETH_30_TC3XX_EQ2_RXDESCRHANDLINGENDIDXOFETHCTRL               
#define ETH_30_TC3XX_EQ2_RXDESCRHANDLINGSTARTIDXOFETHCTRL             
#define ETH_30_TC3XX_EQ2_RXINTERRUPTENABLEDOFETHCTRL                  
#define ETH_30_TC3XX_EQ2_RXTXNOTIFICATIONCALLOUTSIDXOFETHCTRL         
#define ETH_30_TC3XX_EQ2_TIMESYNENABLEDOFETHCTRL                      
#define ETH_30_TC3XX_EQ2_TRCVSPEEDOFETHCTRL                           
#define ETH_30_TC3XX_EQ2_TSHANDLINGIDXOFETHCTRL                       
#define ETH_30_TC3XX_EQ2_TSHANDLINGUSEDOFETHCTRL                      
#define ETH_30_TC3XX_EQ2_TXBUFFERHANDLINGIDXOFETHCTRL                 
#define ETH_30_TC3XX_EQ2_TXDESCRHANDLINGENDIDXOFETHCTRL               
#define ETH_30_TC3XX_EQ2_TXDESCRHANDLINGSTARTIDXOFETHCTRL             
#define ETH_30_TC3XX_EQ2_TXINTERRUPTENABLEDOFETHCTRL                  
#define ETH_30_TC3XX_EQ2_VLANIDBASEDFRAMEQUEUINGENABLEDOFETHCTRL      
#define ETH_30_TC3XX_EQ2_VLANIDBASEDQUEUINGHANDLINGIDXOFETHCTRL       
#define ETH_30_TC3XX_EQ2_VLANIDBASEDQUEUINGHANDLINGUSEDOFETHCTRL      
#define ETH_30_TC3XX_EQ2_AMOUNTOFRXQUEUESOFETHCTRLTC3XX               
#define ETH_30_TC3XX_EQ2_AMOUNTOFTXQUEUESOFETHCTRLTC3XX               
#define ETH_30_TC3XX_EQ2_ARMPPSONTIMEENABLEDOFETHCTRLTC3XX            
#define ETH_30_TC3XX_EQ2_CSRCLOCKRANGEOFETHCTRLTC3XX                  
#define ETH_30_TC3XX_EQ2_ETHCTRLMIIINTERFACEOFETHCTRLTC3XX            
#define ETH_30_TC3XX_EQ2_PINROUTINGOFETHCTRLTC3XX                     
#define ETH_30_TC3XX_EQ2_ETHADAPTBUFFERLENGTHOFETHSWTIFC              
#define ETH_30_TC3XX_EQ2_ETHPREPARETXFRAMEOFETHSWTIFC                 
#define ETH_30_TC3XX_EQ2_ETHPROCESSRXFRAMEOFETHSWTIFC                 
#define ETH_30_TC3XX_EQ2_ETHPROCESSTXFRAMEOFETHSWTIFC                 
#define ETH_30_TC3XX_EQ2_ETHRXFINISHEDINDICATIONOFETHSWTIFC           
#define ETH_30_TC3XX_EQ2_ETHTXFINISHEDINDICATIONOFETHSWTIFC           
#define ETH_30_TC3XX_EQ2_INITIALMACADDRESS                            
#define ETH_30_TC3XX_EQ2_ISRIRQEVENTFUNCSENDIDXOFISRINFOS             
#define ETH_30_TC3XX_EQ2_ISRIRQEVENTFUNCSSTARTIDXOFISRINFOS           
#define ETH_30_TC3XX_EQ2_ISRIRQEVENTFUNCS                             
#define ETH_30_TC3XX_EQ2_RXBUFWARNLVLCALLOUTOFOPTCALLOUTS             
#define ETH_30_TC3XX_EQ2_SHAPERAVAILABLEENDIDXOFQOSHANDLING           
#define ETH_30_TC3XX_EQ2_SHAPERAVAILABLESTARTIDXOFQOSHANDLING         
#define ETH_30_TC3XX_EQ2_TXDESCRHANDLINGIDXOFQOSHANDLING              
#define ETH_30_TC3XX_EQ2_VLANPRIOTXDESCRRINGMAPENDIDXOFQOSHANDLING    
#define ETH_30_TC3XX_EQ2_VLANPRIOTXDESCRRINGMAPSTARTIDXOFQOSHANDLING  
#define ETH_30_TC3XX_EQ2_ACCESSMODEOFREGDATA                          
#define ETH_30_TC3XX_EQ2_OFFSETOFREGDATA                              
#define ETH_30_TC3XX_EQ2_VALUEOFREGDATA                               
#define ETH_30_TC3XX_EQ2_ALIGNEDLASTSEGSIZEOFRXBUFFERHANDLING         
#define ETH_30_TC3XX_EQ2_ALIGNEDSEGSIZEOFRXBUFFERHANDLING             
#define ETH_30_TC3XX_EQ2_DESCRNUMOFRXBUFFERHANDLING                   
#define ETH_30_TC3XX_EQ2_MAXFRAMESIZEOFRXBUFFERHANDLING               
#define ETH_30_TC3XX_EQ2_RXBUFFERENDIDXOFRXBUFFERHANDLING             
#define ETH_30_TC3XX_EQ2_RXBUFFERSTARTIDXOFRXBUFFERHANDLING           
#define ETH_30_TC3XX_EQ2_SEGNUMOFRXBUFFERHANDLING                     
#define ETH_30_TC3XX_EQ2_UNALIGNEDSEGSIZEOFRXBUFFERHANDLING           
#define ETH_30_TC3XX_EQ2_RXDESCRENDIDXOFRXDESCRHANDLING               
#define ETH_30_TC3XX_EQ2_RXDESCRRINGPROCIDXOFRXDESCRHANDLING          
#define ETH_30_TC3XX_EQ2_RXDESCRSTARTIDXOFRXDESCRHANDLING             
#define ETH_30_TC3XX_EQ2_RXDESCRSTATEENDIDXOFRXDESCRHANDLING          
#define ETH_30_TC3XX_EQ2_RXDESCRSTATESTARTIDXOFRXDESCRHANDLING        
#define ETH_30_TC3XX_EQ2_RXINDICATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS 
#define ETH_30_TC3XX_EQ2_TXCONFIRMATIONCALLOUTOFRXTXNOTIFICATIONCALLOUTS 
#define ETH_30_TC3XX_EQ2_SHAPERAVAILABLE                              
#define ETH_30_TC3XX_EQ2_RXTSCONTEXTSTACKENDIDXOFTSHANDLING           
#define ETH_30_TC3XX_EQ2_RXTSCONTEXTSTACKPOSIDXOFTSHANDLING           
#define ETH_30_TC3XX_EQ2_RXTSCONTEXTSTACKSTARTIDXOFTSHANDLING         
#define ETH_30_TC3XX_EQ2_TIMEHANDLINGIDXOFTSHANDLING                  
#define ETH_30_TC3XX_EQ2_TXTSCONTEXTENDIDXOFTSHANDLING                
#define ETH_30_TC3XX_EQ2_TXTSCONTEXTSTARTIDXOFTSHANDLING              
#define ETH_30_TC3XX_EQ2_LENGTHOFTXBUFFERDATA                         
#define ETH_30_TC3XX_EQ2_STARTPOSOFTXBUFFERDATA                       
#define ETH_30_TC3XX_EQ2_ALIGNEDSEGSIZEOFTXBUFFERHANDLING             
#define ETH_30_TC3XX_EQ2_BUFFERNUMOFTXBUFFERHANDLING                  
#define ETH_30_TC3XX_EQ2_DESCRNUMOFTXBUFFERHANDLING                   
#define ETH_30_TC3XX_EQ2_MAXBUFFERLENOFTXBUFFERHANDLING               
#define ETH_30_TC3XX_EQ2_TXBUFFERDATAENDIDXOFTXBUFFERHANDLING         
#define ETH_30_TC3XX_EQ2_TXBUFFERDATASTARTIDXOFTXBUFFERHANDLING       
#define ETH_30_TC3XX_EQ2_TXBUFFERENDIDXOFTXBUFFERHANDLING             
#define ETH_30_TC3XX_EQ2_TXBUFFERFREEELEMNUMIDXOFTXBUFFERHANDLING     
#define ETH_30_TC3XX_EQ2_TXBUFFERSTARTIDXOFTXBUFFERHANDLING           
#define ETH_30_TC3XX_EQ2_TXBUFFERSTATEENDIDXOFTXBUFFERHANDLING        
#define ETH_30_TC3XX_EQ2_TXBUFFERSTATESTARTIDXOFTXBUFFERHANDLING      
#define ETH_30_TC3XX_EQ2_TXDESCRENDIDXOFTXDESCRHANDLING               
#define ETH_30_TC3XX_EQ2_TXDESCRRINGPROCIDXOFTXDESCRHANDLING          
#define ETH_30_TC3XX_EQ2_TXDESCRSTARTIDXOFTXDESCRHANDLING             
#define ETH_30_TC3XX_EQ2_TXDESCRSTATEENDIDXOFTXDESCRHANDLING          
#define ETH_30_TC3XX_EQ2_TXDESCRSTATESTARTIDXOFTXDESCRHANDLING        
#define ETH_30_TC3XX_EQ2_POSTINITUSERCALLOUTOFUSERINITCALLOUTS        
#define ETH_30_TC3XX_EQ2_PREINITUSERCALLOUTOFUSERINITCALLOUTS         
#define ETH_30_TC3XX_EQ2_TXDESCRHANDLINGIDXOFVLANIDBASEDQUEUINGHANDLING 
#define ETH_30_TC3XX_EQ2_VLANIDRXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING 
#define ETH_30_TC3XX_EQ2_VLANIDRXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING 
#define ETH_30_TC3XX_EQ2_VLANIDTXDESCRRINGMAPENDIDXOFVLANIDBASEDQUEUINGHANDLING 
#define ETH_30_TC3XX_EQ2_VLANIDTXDESCRRINGMAPSTARTIDXOFVLANIDBASEDQUEUINGHANDLING 
#define ETH_30_TC3XX_EQ2_QUEUEINDEXOFVLANIDRXDESCRRINGMAP             
#define ETH_30_TC3XX_EQ2_VLANIDOFVLANIDRXDESCRRINGMAP                 
#define ETH_30_TC3XX_EQ2_QUEUEINDEXOFVLANIDTXDESCRRINGMAP             
#define ETH_30_TC3XX_EQ2_VLANIDOFVLANIDTXDESCRRINGMAP                 
#define ETH_30_TC3XX_EQ2_VLANPRIOTXDESCRRINGMAP                       
#define ETH_30_TC3XX_EQ2_ACTIVEMACADDRESSOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_ETHCTRLOFPCCONFIG                            
#define ETH_30_TC3XX_EQ2_ETHCTRLSTATEOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_ETHCTRLTC3XXOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_ETHCTRLTC3XXSTATEOFPCCONFIG                  
#define ETH_30_TC3XX_EQ2_ETHMEASDATACOUNTEROFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_ETHMEASDATACOUNTERRESETOFPCCONFIG            
#define ETH_30_TC3XX_EQ2_ETHSWTIFCOFPCCONFIG                          
#define ETH_30_TC3XX_EQ2_INITIALMACADDRESSOFPCCONFIG                  
#define ETH_30_TC3XX_EQ2_ISRINFOSOFPCCONFIG                           
#define ETH_30_TC3XX_EQ2_ISRIRQEVENTFUNCSOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_MULTICASTBUCKETCOUNTERSOFPCCONFIG            
#define ETH_30_TC3XX_EQ2_OPTCALLOUTSOFPCCONFIG                        
#define ETH_30_TC3XX_EQ2_PROMISCUOUSMODECOUNTEROFPCCONFIG             
#define ETH_30_TC3XX_EQ2_QOSHANDLINGOFPCCONFIG                        
#define ETH_30_TC3XX_EQ2_REGDATAOFPCCONFIG                            
#define ETH_30_TC3XX_EQ2_RXBUFFERHANDLINGOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_RXBUFFEROFPCCONFIG                           
#define ETH_30_TC3XX_EQ2_RXDESCRHANDLINGOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_RXDESCROFPCCONFIG                            
#define ETH_30_TC3XX_EQ2_RXDESCRRINGPROCOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_RXDESCRSTATEOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_RXTSCONTEXTSTACKOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_RXTSCONTEXTSTACKPOSOFPCCONFIG                
#define ETH_30_TC3XX_EQ2_RXTXNOTIFICATIONCALLOUTSOFPCCONFIG           
#define ETH_30_TC3XX_EQ2_SHAPERAVAILABLEOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_SIZEOFACTIVEMACADDRESSOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFETHCTRLOFPCCONFIG                      
#define ETH_30_TC3XX_EQ2_SIZEOFETHCTRLTC3XXOFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_SIZEOFETHSWTIFCOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_SIZEOFINITIALMACADDRESSOFPCCONFIG            
#define ETH_30_TC3XX_EQ2_SIZEOFISRINFOSOFPCCONFIG                     
#define ETH_30_TC3XX_EQ2_SIZEOFISRIRQEVENTFUNCSOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFMULTICASTBUCKETCOUNTERSOFPCCONFIG      
#define ETH_30_TC3XX_EQ2_SIZEOFOPTCALLOUTSOFPCCONFIG                  
#define ETH_30_TC3XX_EQ2_SIZEOFQOSHANDLINGOFPCCONFIG                  
#define ETH_30_TC3XX_EQ2_SIZEOFREGDATAOFPCCONFIG                      
#define ETH_30_TC3XX_EQ2_SIZEOFRXBUFFERHANDLINGOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFRXBUFFEROFPCCONFIG                     
#define ETH_30_TC3XX_EQ2_SIZEOFRXDESCRHANDLINGOFPCCONFIG              
#define ETH_30_TC3XX_EQ2_SIZEOFRXDESCROFPCCONFIG                      
#define ETH_30_TC3XX_EQ2_SIZEOFRXDESCRRINGPROCOFPCCONFIG              
#define ETH_30_TC3XX_EQ2_SIZEOFRXDESCRSTATEOFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_SIZEOFRXTSCONTEXTSTACKOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFRXTSCONTEXTSTACKPOSOFPCCONFIG          
#define ETH_30_TC3XX_EQ2_SIZEOFRXTXNOTIFICATIONCALLOUTSOFPCCONFIG     
#define ETH_30_TC3XX_EQ2_SIZEOFSHAPERAVAILABLEOFPCCONFIG              
#define ETH_30_TC3XX_EQ2_SIZEOFTIMEHANDLINGOFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_SIZEOFTSHANDLINGOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_SIZEOFTXBUFFERDATAOFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_SIZEOFTXBUFFERFREEELEMNUMOFPCCONFIG          
#define ETH_30_TC3XX_EQ2_SIZEOFTXBUFFERHANDLINGOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFTXBUFFEROFPCCONFIG                     
#define ETH_30_TC3XX_EQ2_SIZEOFTXBUFFERSTATEOFPCCONFIG                
#define ETH_30_TC3XX_EQ2_SIZEOFTXDESCRHANDLINGOFPCCONFIG              
#define ETH_30_TC3XX_EQ2_SIZEOFTXDESCROFPCCONFIG                      
#define ETH_30_TC3XX_EQ2_SIZEOFTXDESCRRINGPROCOFPCCONFIG              
#define ETH_30_TC3XX_EQ2_SIZEOFTXDESCRSTATEOFPCCONFIG                 
#define ETH_30_TC3XX_EQ2_SIZEOFTXTSCONTEXTOFPCCONFIG                  
#define ETH_30_TC3XX_EQ2_SIZEOFUSERINITCALLOUTSOFPCCONFIG             
#define ETH_30_TC3XX_EQ2_SIZEOFVLANIDBASEDQUEUINGHANDLINGOFPCCONFIG   
#define ETH_30_TC3XX_EQ2_SIZEOFVLANIDRXDESCRRINGMAPOFPCCONFIG         
#define ETH_30_TC3XX_EQ2_SIZEOFVLANIDTXDESCRRINGMAPOFPCCONFIG         
#define ETH_30_TC3XX_EQ2_SIZEOFVLANPRIOTXDESCRRINGMAPOFPCCONFIG       
#define ETH_30_TC3XX_EQ2_TIMEHANDLINGOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_TSHANDLINGOFPCCONFIG                         
#define ETH_30_TC3XX_EQ2_TXBUFFERDATAOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_TXBUFFERFREEELEMNUMOFPCCONFIG                
#define ETH_30_TC3XX_EQ2_TXBUFFERHANDLINGOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_TXBUFFEROFPCCONFIG                           
#define ETH_30_TC3XX_EQ2_TXBUFFERSTATEOFPCCONFIG                      
#define ETH_30_TC3XX_EQ2_TXDESCRHANDLINGOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_TXDESCROFPCCONFIG                            
#define ETH_30_TC3XX_EQ2_TXDESCRRINGPROCOFPCCONFIG                    
#define ETH_30_TC3XX_EQ2_TXDESCRSTATEOFPCCONFIG                       
#define ETH_30_TC3XX_EQ2_TXTSCONTEXTOFPCCONFIG                        
#define ETH_30_TC3XX_EQ2_USERINITCALLOUTSOFPCCONFIG                   
#define ETH_30_TC3XX_EQ2_VLANIDBASEDQUEUINGHANDLINGOFPCCONFIG         
#define ETH_30_TC3XX_EQ2_VLANIDRXDESCRRINGMAPOFPCCONFIG               
#define ETH_30_TC3XX_EQ2_VLANIDTXDESCRRINGMAPOFPCCONFIG               
#define ETH_30_TC3XX_EQ2_VLANPRIOTXDESCRRINGMAPOFPCCONFIG             
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCSymbolicInitializationPointers  Eth_30_Tc3xx Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define Eth_30_Tc3xx_Config_Ptr                                       &(Eth_30_Tc3xx_PCConfig.Config)  /**< symbolic identifier which shall be used to initialize 'Eth_30_Tc3xx' */
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCInitializationSymbols  Eth_30_Tc3xx Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define Eth_30_Tc3xx_Config                                           Eth_30_Tc3xx_PCConfig.Config  /**< symbolic identifier which could be used to initialize 'Eth_30_Tc3xx */
/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCGeneral  Eth_30_Tc3xx General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define ETH_30_TC3XX_CHECK_INIT_POINTER                               STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define ETH_30_TC3XX_FINAL_MAGIC_NUMBER                               0x581Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of Eth_30_Tc3xx */
#define ETH_30_TC3XX_INDIVIDUAL_POSTBUILD                             STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'Eth_30_Tc3xx' is not configured to be postbuild capable. */
#define ETH_30_TC3XX_INIT_DATA                                        ETH_30_TC3XX_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define ETH_30_TC3XX_INIT_DATA_HASH_CODE                              789202146L  /**< the precompile constant to validate the initialization structure at initialization time of Eth_30_Tc3xx with a hashcode. The seed value is '0x581Eu' */
#define ETH_30_TC3XX_USE_ECUM_BSW_ERROR_HOOK                          STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define ETH_30_TC3XX_USE_INIT_POINTER                                 STD_ON  /**< STD_ON if the init pointer Eth_30_Tc3xx shall be used. */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Eth_30_Tc3xxPCIterableTypes  Eth_30_Tc3xx Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate Eth_30_Tc3xx_ActiveMacAddress */
typedef uint8_least Eth_30_Tc3xx_ActiveMacAddressIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthCtrl */
typedef uint8_least Eth_30_Tc3xx_EthCtrlIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthCtrlTc3xx */
typedef uint8_least Eth_30_Tc3xx_EthCtrlTc3xxIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthSwtIfc */
typedef uint8_least Eth_30_Tc3xx_EthSwtIfcIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_InitialMacAddress */
typedef uint8_least Eth_30_Tc3xx_InitialMacAddressIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_IsrInfos */
typedef uint8_least Eth_30_Tc3xx_IsrInfosIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_IsrIrqEventFuncs */
typedef uint8_least Eth_30_Tc3xx_IsrIrqEventFuncsIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_MulticastBucketCounters */
typedef uint8_least Eth_30_Tc3xx_MulticastBucketCountersIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_OptCallouts */
typedef uint8_least Eth_30_Tc3xx_OptCalloutsIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_QosHandling */
typedef uint8_least Eth_30_Tc3xx_QosHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RegData */
typedef uint8_least Eth_30_Tc3xx_RegDataIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxBuffer */
typedef uint16_least Eth_30_Tc3xx_RxBufferIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxBufferHandling */
typedef uint8_least Eth_30_Tc3xx_RxBufferHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxDescr */
typedef uint8_least Eth_30_Tc3xx_RxDescrIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxDescrHandling */
typedef uint8_least Eth_30_Tc3xx_RxDescrHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxDescrRingProc */
typedef uint8_least Eth_30_Tc3xx_RxDescrRingProcIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxDescrState */
typedef uint8_least Eth_30_Tc3xx_RxDescrStateIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxTsContextStack */
typedef uint8_least Eth_30_Tc3xx_RxTsContextStackIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxTsContextStackPos */
typedef uint8_least Eth_30_Tc3xx_RxTsContextStackPosIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_RxTxNotificationCallouts */
typedef uint8_least Eth_30_Tc3xx_RxTxNotificationCalloutsIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_ShaperAvailable */
typedef uint8_least Eth_30_Tc3xx_ShaperAvailableIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TimeHandling */
typedef uint8_least Eth_30_Tc3xx_TimeHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TsHandling */
typedef uint8_least Eth_30_Tc3xx_TsHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxBuffer */
typedef uint16_least Eth_30_Tc3xx_TxBufferIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxBufferData */
typedef uint8_least Eth_30_Tc3xx_TxBufferDataIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxBufferFreeElemNum */
typedef uint8_least Eth_30_Tc3xx_TxBufferFreeElemNumIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxBufferHandling */
typedef uint8_least Eth_30_Tc3xx_TxBufferHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxBufferState */
typedef uint8_least Eth_30_Tc3xx_TxBufferStateIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxDescr */
typedef uint8_least Eth_30_Tc3xx_TxDescrIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxDescrHandling */
typedef uint8_least Eth_30_Tc3xx_TxDescrHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxDescrRingProc */
typedef uint8_least Eth_30_Tc3xx_TxDescrRingProcIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxDescrState */
typedef uint8_least Eth_30_Tc3xx_TxDescrStateIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_TxTsContext */
typedef uint8_least Eth_30_Tc3xx_TxTsContextIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_UserInitCallouts */
typedef uint8_least Eth_30_Tc3xx_UserInitCalloutsIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
typedef uint8_least Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_VlanIdRxDescrRingMap */
typedef uint8_least Eth_30_Tc3xx_VlanIdRxDescrRingMapIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_VlanIdTxDescrRingMap */
typedef uint8_least Eth_30_Tc3xx_VlanIdTxDescrRingMapIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
typedef uint8_least Eth_30_Tc3xx_VlanPrioTxDescrRingMapIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCIterableTypesWithSizeRelations  Eth_30_Tc3xx Iterable Types With Size Relations (PRE_COMPILE)
  \brief  These type definitions are used to iterate over a VAR based array with the same iterator as the related CONST array.
  \{
*/ 
/**   \brief  type used to iterate Eth_30_Tc3xx_EthCtrlState */
typedef Eth_30_Tc3xx_EthCtrlIterType Eth_30_Tc3xx_EthCtrlStateIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthCtrlTc3xxState */
typedef Eth_30_Tc3xx_EthCtrlTc3xxIterType Eth_30_Tc3xx_EthCtrlTc3xxStateIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthMeasDataCounter */
typedef Eth_30_Tc3xx_EthCtrlIterType Eth_30_Tc3xx_EthMeasDataCounterIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_EthMeasDataCounterReset */
typedef Eth_30_Tc3xx_EthCtrlIterType Eth_30_Tc3xx_EthMeasDataCounterResetIterType;

/**   \brief  type used to iterate Eth_30_Tc3xx_PromiscuousModeCounter */
typedef Eth_30_Tc3xx_EthCtrlIterType Eth_30_Tc3xx_PromiscuousModeCounterIterType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCValueTypes  Eth_30_Tc3xx Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for Eth_30_Tc3xx_ActiveMacAddress */
typedef uint8 Eth_30_Tc3xx_ActiveMacAddressType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_EthSwtIfcUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_EthSwtIfcUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_FqtssEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_FqtssEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IsrInfosUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_IsrInfosUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_LoopCyclesOfEthCtrl */
typedef uint16 Eth_30_Tc3xx_LoopCyclesOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrl */
typedef uint16 Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_NvMBlockIdOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_NvMBlockIdOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrl */
typedef uint16 Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_QosEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_QosEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_QosHandlingIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_QosHandlingUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_QosHandlingUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RegDataEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RegDataEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RegDataStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RegDataStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RegDataUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_RegDataUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrl */
typedef uint16 Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TimeSynEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_TimeSynEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TrcvSpeedOfEthCtrl */
typedef uint32 Eth_30_Tc3xx_TrcvSpeedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TsHandlingIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_TsHandlingIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TsHandlingUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_TsHandlingUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrl */
typedef boolean Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdBasedQueuingHandlingUsedOfEthCtrl */
typedef boolean Eth_30_Tc3xx_VlanIdBasedQueuingHandlingUsedOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_PendingRxEventsOfEthCtrlState */
typedef uint16 Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_PendingTxEventsOfEthCtrlState */
typedef uint16 Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xx */
typedef uint8 Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xx */
typedef uint8 Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xx */
typedef boolean Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xx */
typedef uint16 Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xx */
typedef uint16 Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xx */
typedef uint32 Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxState */
typedef uint16 Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounter */
typedef uint32 Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounter */
typedef uint32 Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounter */
typedef uint32 Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterReset */
typedef uint32 Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType;

/**   \brief  value based type definition for Eth_30_Tc3xx_InitialMacAddress */
typedef uint8 Eth_30_Tc3xx_InitialMacAddressType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfos */
typedef uint8 Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfosType;

/**   \brief  value based type definition for Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfos */
typedef uint8 Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfosType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MulticastBucketCounters */
typedef uint8 Eth_30_Tc3xx_MulticastBucketCountersType;

/**   \brief  value based type definition for Eth_30_Tc3xx_PromiscuousModeCounter */
typedef uint8 Eth_30_Tc3xx_PromiscuousModeCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandling */
typedef uint8 Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandling */
typedef uint8 Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandling */
typedef uint8 Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandling */
typedef uint8 Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AccessModeOfRegData */
typedef uint8 Eth_30_Tc3xx_AccessModeOfRegDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_OffsetOfRegData */
typedef uint16 Eth_30_Tc3xx_OffsetOfRegDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ValueOfRegData */
typedef uint32 Eth_30_Tc3xx_ValueOfRegDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxBuffer */
typedef uint8 Eth_30_Tc3xx_RxBufferType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DescrNumOfRxBufferHandling */
typedef uint8 Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SegNumOfRxBufferHandling */
typedef uint8 Eth_30_Tc3xx_SegNumOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandling */
typedef uint16 Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_CurProcPosOfRxDescrRingProc */
typedef uint8 Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MappedBufferOfRxDescrState */
typedef uint16 Eth_30_Tc3xx_MappedBufferOfRxDescrStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DescrIdxOfRxTsContextStack */
typedef uint8 Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RingIdxOfRxTsContextStack */
typedef uint8 Eth_30_Tc3xx_RingIdxOfRxTsContextStackType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxTsContextStackPos */
typedef sint8 Eth_30_Tc3xx_RxTsContextStackPosType;

/**   \brief  value based type definition for Eth_30_Tc3xx_ShaperAvailable */
typedef boolean Eth_30_Tc3xx_ShaperAvailableType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfActiveMacAddress */
typedef uint8 Eth_30_Tc3xx_SizeOfActiveMacAddressType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthCtrl */
typedef uint8 Eth_30_Tc3xx_SizeOfEthCtrlType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthCtrlState */
typedef uint8 Eth_30_Tc3xx_SizeOfEthCtrlStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthCtrlTc3xx */
typedef uint8 Eth_30_Tc3xx_SizeOfEthCtrlTc3xxType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthCtrlTc3xxState */
typedef uint8 Eth_30_Tc3xx_SizeOfEthCtrlTc3xxStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthMeasDataCounter */
typedef uint8 Eth_30_Tc3xx_SizeOfEthMeasDataCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthMeasDataCounterReset */
typedef uint8 Eth_30_Tc3xx_SizeOfEthMeasDataCounterResetType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfEthSwtIfc */
typedef uint8 Eth_30_Tc3xx_SizeOfEthSwtIfcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfInitialMacAddress */
typedef uint8 Eth_30_Tc3xx_SizeOfInitialMacAddressType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfIsrInfos */
typedef uint8 Eth_30_Tc3xx_SizeOfIsrInfosType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfIsrIrqEventFuncs */
typedef uint8 Eth_30_Tc3xx_SizeOfIsrIrqEventFuncsType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfMulticastBucketCounters */
typedef uint8 Eth_30_Tc3xx_SizeOfMulticastBucketCountersType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfOptCallouts */
typedef uint8 Eth_30_Tc3xx_SizeOfOptCalloutsType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfPromiscuousModeCounter */
typedef uint8 Eth_30_Tc3xx_SizeOfPromiscuousModeCounterType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfQosHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfQosHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRegData */
typedef uint8 Eth_30_Tc3xx_SizeOfRegDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxBuffer */
typedef uint16 Eth_30_Tc3xx_SizeOfRxBufferType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxBufferHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfRxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxDescr */
typedef uint8 Eth_30_Tc3xx_SizeOfRxDescrType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxDescrHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfRxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxDescrRingProc */
typedef uint8 Eth_30_Tc3xx_SizeOfRxDescrRingProcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxDescrState */
typedef uint8 Eth_30_Tc3xx_SizeOfRxDescrStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxTsContextStack */
typedef uint8 Eth_30_Tc3xx_SizeOfRxTsContextStackType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxTsContextStackPos */
typedef uint8 Eth_30_Tc3xx_SizeOfRxTsContextStackPosType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfRxTxNotificationCallouts */
typedef uint8 Eth_30_Tc3xx_SizeOfRxTxNotificationCalloutsType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfShaperAvailable */
typedef uint8 Eth_30_Tc3xx_SizeOfShaperAvailableType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTimeHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfTimeHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTsHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxBuffer */
typedef uint16 Eth_30_Tc3xx_SizeOfTxBufferType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxBufferData */
typedef uint8 Eth_30_Tc3xx_SizeOfTxBufferDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxBufferFreeElemNum */
typedef uint8 Eth_30_Tc3xx_SizeOfTxBufferFreeElemNumType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxBufferState */
typedef uint8 Eth_30_Tc3xx_SizeOfTxBufferStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxDescr */
typedef uint8 Eth_30_Tc3xx_SizeOfTxDescrType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxDescrRingProc */
typedef uint8 Eth_30_Tc3xx_SizeOfTxDescrRingProcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxDescrState */
typedef uint8 Eth_30_Tc3xx_SizeOfTxDescrStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfTxTsContext */
typedef uint8 Eth_30_Tc3xx_SizeOfTxTsContextType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfUserInitCallouts */
typedef uint8 Eth_30_Tc3xx_SizeOfUserInitCalloutsType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RateRatioOfTimeHandling */
typedef float64 Eth_30_Tc3xx_RateRatioOfTimeHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TimeHandlingIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_TimeHandlingIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandling */
typedef uint8 Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBuffer */
typedef uint8 Eth_30_Tc3xx_TxBufferType;

/**   \brief  value based type definition for Eth_30_Tc3xx_LengthOfTxBufferData */
typedef uint16 Eth_30_Tc3xx_LengthOfTxBufferDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_StartPosOfTxBufferData */
typedef uint16 Eth_30_Tc3xx_StartPosOfTxBufferDataType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferFreeElemNum */
typedef uint16 Eth_30_Tc3xx_TxBufferFreeElemNumType;

/**   \brief  value based type definition for Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandling */
typedef uint16 Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_BufferNumOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_BufferNumOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DescrNumOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_DescrNumOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandling */
typedef uint16 Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandling */
typedef uint16 Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandling */
typedef uint16 Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandling */
typedef uint8 Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_BusyOfTxBufferState */
typedef boolean Eth_30_Tc3xx_BusyOfTxBufferStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TsRequestedOfTxBufferState */
typedef boolean Eth_30_Tc3xx_TsRequestedOfTxBufferStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_UlTxConfStateOfTxBufferState */
typedef uint8 Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_CurProcPosOfTxDescrRingProc */
typedef uint8 Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_FreePosOfTxDescrRingProc */
typedef uint8 Eth_30_Tc3xx_FreePosOfTxDescrRingProcType;

/**   \brief  value based type definition for Eth_30_Tc3xx_MappedBufferOfTxDescrState */
typedef uint8 Eth_30_Tc3xx_MappedBufferOfTxDescrStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxReadyOfTxDescrState */
typedef uint8 Eth_30_Tc3xx_TxReadyOfTxDescrStateType;

/**   \brief  value based type definition for Eth_30_Tc3xx_DescrIdxOfTxTsContext */
typedef uint8 Eth_30_Tc3xx_DescrIdxOfTxTsContextType;

/**   \brief  value based type definition for Eth_30_Tc3xx_RingIdxOfTxTsContext */
typedef uint8 Eth_30_Tc3xx_RingIdxOfTxTsContextType;

/**   \brief  value based type definition for Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling */
typedef uint8 Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType;

/**   \brief  value based type definition for Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMapType;

/**   \brief  value based type definition for Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
typedef uint8 Eth_30_Tc3xx_VlanPrioTxDescrRingMapType;

/** 
  \}
*/ 

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  Eth_30_Tc3xxPCStructTypes  Eth_30_Tc3xx Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in Eth_30_Tc3xx_EthCtrl */
typedef struct sEth_30_Tc3xx_EthCtrlType
{
  Eth_30_Tc3xx_TrcvSpeedOfEthCtrlType TrcvSpeedOfEthCtrl;  /**< Transceiver speed */
  Eth_30_Tc3xx_LoopCyclesOfEthCtrlType LoopCyclesOfEthCtrl;  /**< Maximum tries till a general hardware access is assumed as failed */
  Eth_30_Tc3xx_MiiLoopCyclesOfEthCtrlType MiiLoopCyclesOfEthCtrl;  /**< Maximum tries till MII access is assumed as failed */
  Eth_30_Tc3xx_ProtectedAreaIdOfEthCtrlType ProtectedAreaIdOfEthCtrl;  /**< Id of area in case driver has to access proteced memory for register access */
  Eth_30_Tc3xx_ResetLoopCyclesOfEthCtrlType ResetLoopCyclesOfEthCtrl;  /**< Maximum tries till reset is assumed as failed */
  Eth_30_Tc3xx_FqtssEnabledOfEthCtrlType FqtssEnabledOfEthCtrl;  /**< FQTSS enabled */
  Eth_30_Tc3xx_IpChecksumOffloadingEnabledOfEthCtrlType IpChecksumOffloadingEnabledOfEthCtrl;  /**< IP checksum offloading enabled */
  Eth_30_Tc3xx_MultiQueueConfigEnabledOfEthCtrlType MultiQueueConfigEnabledOfEthCtrl;  /**< Qos/VLAN-ID based frame queuing enabled */
  Eth_30_Tc3xx_ProtocolChecksumOffloadingEnabledOfEthCtrlType ProtocolChecksumOffloadingEnabledOfEthCtrl;  /**< Protocol checksum offloading enabled */
  Eth_30_Tc3xx_QosEnabledOfEthCtrlType QosEnabledOfEthCtrl;  /**< Qos configuration */
  Eth_30_Tc3xx_RxInterruptEnabledOfEthCtrlType RxInterruptEnabledOfEthCtrl;  /**< Rx interrupt configuration */
  Eth_30_Tc3xx_TimeSynEnabledOfEthCtrlType TimeSynEnabledOfEthCtrl;  /**< TimeSync configuraiton */
  Eth_30_Tc3xx_TxInterruptEnabledOfEthCtrlType TxInterruptEnabledOfEthCtrl;  /**< Tx interrupt configuration */
  Eth_30_Tc3xx_VlanIdBasedFrameQueuingEnabledOfEthCtrlType VlanIdBasedFrameQueuingEnabledOfEthCtrl;  /**< Vlan-ID based frame queuing configuration */
  Eth_30_Tc3xx_ActiveMacAddressEndIdxOfEthCtrlType ActiveMacAddressEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_ActiveMacAddress */
  Eth_30_Tc3xx_ActiveMacAddressStartIdxOfEthCtrlType ActiveMacAddressStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_ActiveMacAddress */
  Eth_30_Tc3xx_DemEAccessEventIdOfEthCtrlType DemEAccessEventIdOfEthCtrl;  /**< ETH_E_ACCESS DEM event */
  Eth_30_Tc3xx_EthSwtIfcIdxOfEthCtrlType EthSwtIfcIdxOfEthCtrl;  /**< the index of the 0:1 relation pointing to Eth_30_Tc3xx_EthSwtIfc */
  Eth_30_Tc3xx_InitialMacAddressEndIdxOfEthCtrlType InitialMacAddressEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_InitialMacAddress */
  Eth_30_Tc3xx_InitialMacAddressStartIdxOfEthCtrlType InitialMacAddressStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_InitialMacAddress */
  Eth_30_Tc3xx_IsrInfosEndIdxOfEthCtrlType IsrInfosEndIdxOfEthCtrl;  /**< the end index of the 0:n relation pointing to Eth_30_Tc3xx_IsrInfos */
  Eth_30_Tc3xx_IsrInfosStartIdxOfEthCtrlType IsrInfosStartIdxOfEthCtrl;  /**< the start index of the 0:n relation pointing to Eth_30_Tc3xx_IsrInfos */
  Eth_30_Tc3xx_MulticastBucketCountersEndIdxOfEthCtrlType MulticastBucketCountersEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_MulticastBucketCounters */
  Eth_30_Tc3xx_MulticastBucketCountersStartIdxOfEthCtrlType MulticastBucketCountersStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_MulticastBucketCounters */
  Eth_30_Tc3xx_NvMBlockIdOfEthCtrlType NvMBlockIdOfEthCtrl;  /**< NvM Block Id for storage of MAC address */
  Eth_30_Tc3xx_QosHandlingIdxOfEthCtrlType QosHandlingIdxOfEthCtrl;  /**< the index of the 0:1 relation pointing to Eth_30_Tc3xx_QosHandling */
  Eth_30_Tc3xx_RegDataEndIdxOfEthCtrlType RegDataEndIdxOfEthCtrl;  /**< the end index of the 0:n relation pointing to Eth_30_Tc3xx_RegData */
  Eth_30_Tc3xx_RegDataStartIdxOfEthCtrlType RegDataStartIdxOfEthCtrl;  /**< the start index of the 0:n relation pointing to Eth_30_Tc3xx_RegData */
  Eth_30_Tc3xx_RxBufferHandlingEndIdxOfEthCtrlType RxBufferHandlingEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxBufferHandling */
  Eth_30_Tc3xx_RxBufferHandlingStartIdxOfEthCtrlType RxBufferHandlingStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxBufferHandling */
  Eth_30_Tc3xx_RxDescrHandlingEndIdxOfEthCtrlType RxDescrHandlingEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrHandling */
  Eth_30_Tc3xx_RxDescrHandlingStartIdxOfEthCtrlType RxDescrHandlingStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrHandling */
  Eth_30_Tc3xx_RxTxNotificationCalloutsIdxOfEthCtrlType RxTxNotificationCalloutsIdxOfEthCtrl;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxTxNotificationCallouts */
  Eth_30_Tc3xx_TsHandlingIdxOfEthCtrlType TsHandlingIdxOfEthCtrl;  /**< the index of the 0:1 relation pointing to Eth_30_Tc3xx_TsHandling */
  Eth_30_Tc3xx_TxBufferHandlingIdxOfEthCtrlType TxBufferHandlingIdxOfEthCtrl;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxBufferHandling */
  Eth_30_Tc3xx_TxDescrHandlingEndIdxOfEthCtrlType TxDescrHandlingEndIdxOfEthCtrl;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_TxDescrHandlingStartIdxOfEthCtrlType TxDescrHandlingStartIdxOfEthCtrl;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_VlanIdBasedQueuingHandlingIdxOfEthCtrlType VlanIdBasedQueuingHandlingIdxOfEthCtrl;  /**< the index of the 0:1 relation pointing to Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
  Eth_30_Tc3xx_RegBaseAddrType AutosarRtmRegBaseAddrOfEthCtrl;  /**< Register base address of the Ethernet controller when running in AUTOSAR OS environment */
} Eth_30_Tc3xx_EthCtrlType;

/**   \brief  type used in Eth_30_Tc3xx_EthCtrlState */
typedef struct sEth_30_Tc3xx_EthCtrlStateType
{
  Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType PendingRxEventsOfEthCtrlState;  /**< Bitmask tracking reception events where each bit represents the respective queue the event has occured on (highest bit -&gt; highest prio queue, lowest bit -&gt; lowest prio queue) */
  Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType PendingTxEventsOfEthCtrlState;  /**< Bitmask tracking tx confirmation events where each bit represents the respective queue the event has occured on (highest bit -&gt; highest prio queue, lowest bit -&gt; lowest prio queue) */
  Eth_ModeType CtrlModeOfEthCtrlState;  /**< Mode of Ethernet controller */
  Eth_30_Tc3xx_RegBaseAddrType RegBaseAddrOfEthCtrlState;  /**< Register base address used to access register space of respective driver */
} Eth_30_Tc3xx_EthCtrlStateType;

/**   \brief  type used in Eth_30_Tc3xx_EthCtrlTc3xx */
typedef struct sEth_30_Tc3xx_EthCtrlTc3xxType
{
  Eth_30_Tc3xx_PinRoutingOfEthCtrlTc3xxType PinRoutingOfEthCtrlTc3xx;  /**< Pin routing configuration */
  Eth_30_Tc3xx_CsrClockRangeOfEthCtrlTc3xxType CsrClockRangeOfEthCtrlTc3xx;  /**< CsrClockRange configuration */
  Eth_30_Tc3xx_EthCtrlMiiInterfaceOfEthCtrlTc3xxType EthCtrlMiiInterfaceOfEthCtrlTc3xx;  /**< MiiInterface of the controller */
  Eth_30_Tc3xx_ArmPpsOnTimeEnabledOfEthCtrlTc3xxType ArmPpsOnTimeEnabledOfEthCtrlTc3xx;  /**< ArmPpsOnTime configuration */
  Eth_30_Tc3xx_AmountOfRxQueuesOfEthCtrlTc3xxType AmountOfRxQueuesOfEthCtrlTc3xx;  /**< Amount of configured QoS Rx queues */
  Eth_30_Tc3xx_AmountOfTxQueuesOfEthCtrlTc3xxType AmountOfTxQueuesOfEthCtrlTc3xx;  /**< Amount of configured QoS Tx queues */
} Eth_30_Tc3xx_EthCtrlTc3xxType;

/**   \brief  type used in Eth_30_Tc3xx_EthCtrlTc3xxState */
typedef struct sEth_30_Tc3xx_EthCtrlTc3xxStateType
{
  Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType ReadMiiResultOfEthCtrlTc3xxState;  /**< Result of a read operation on MII interface */
  Eth_RxStatsType RxStatsOfEthCtrlTc3xxState;  /**< Reception statistics */
} Eth_30_Tc3xx_EthCtrlTc3xxStateType;

/**   \brief  type used in Eth_30_Tc3xx_EthMeasDataCounter */
typedef struct sEth_30_Tc3xx_EthMeasDataCounterType
{
  Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType DropInsuffRxBuffOfEthMeasDataCounter;  /**< Count of Rx frames drop due to insufficient Tx Buffers */
  Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType DropInsuffTxBuffOfEthMeasDataCounter;  /**< Count of Tx frames drop due to insufficient Tx Buffers */
  Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType WarnFullRxBuffOfEthMeasDataCounter;  /**< Number of times no free Rx buffer encountered */
} Eth_30_Tc3xx_EthMeasDataCounterType;

/**   \brief  type used in Eth_30_Tc3xx_EthMeasDataCounterReset */
typedef struct sEth_30_Tc3xx_EthMeasDataCounterResetType
{
  Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType DropInsuffRxBuffResetOfEthMeasDataCounterReset;  /**< Reset value for Rx MeasDataCounter */
} Eth_30_Tc3xx_EthMeasDataCounterResetType;

/**   \brief  type used in Eth_30_Tc3xx_EthSwtIfc */
typedef struct sEth_30_Tc3xx_EthSwtIfcType
{
  Eth_30_Tc3xx_EthSwtEthAdaptBufferLengthFctPtrType EthAdaptBufferLengthOfEthSwtIfc;  /**< EthSwt_EthAdaptBufferLength() */
  Eth_30_Tc3xx_EthSwtEthPrepareTxFrameFctPtrType EthPrepareTxFrameOfEthSwtIfc;  /**< EthSwt_EthPrepareTxFrame() */
  Eth_30_Tc3xx_EthSwtEthProcessRxFrameFctPtrType EthProcessRxFrameOfEthSwtIfc;  /**< EthSwt_EthProcessRxFrame() */
  Eth_30_Tc3xx_EthSwtEthProcessTxFrameFctPtrType EthProcessTxFrameOfEthSwtIfc;  /**< EthSwt_EthProcessTxFrame() */
  Eth_30_Tc3xx_EthSwtEthRxFinishedIndicationFctPtrType EthRxFinishedIndicationOfEthSwtIfc;  /**< EthSwt_EthRxFinishedIndication() */
  Eth_30_Tc3xx_EthSwtEthTxFinishedIndicationFctPtrType EthTxFinishedIndicationOfEthSwtIfc;  /**< EthSwt_EthTxFinishedIndication() */
} Eth_30_Tc3xx_EthSwtIfcType;

/**   \brief  type used in Eth_30_Tc3xx_IsrInfos */
typedef struct sEth_30_Tc3xx_IsrInfosType
{
  Eth_30_Tc3xx_IsrIrqEventFuncsEndIdxOfIsrInfosType IsrIrqEventFuncsEndIdxOfIsrInfos;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_IsrIrqEventFuncs */
  Eth_30_Tc3xx_IsrIrqEventFuncsStartIdxOfIsrInfosType IsrIrqEventFuncsStartIdxOfIsrInfos;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_IsrIrqEventFuncs */
} Eth_30_Tc3xx_IsrInfosType;

/**   \brief  type used in Eth_30_Tc3xx_OptCallouts */
typedef struct sEth_30_Tc3xx_OptCalloutsType
{
  Eth_30_Tc3xx_UserRxBufWarnLvlCalloutFctPtrType RxBufWarnLvlCalloutOfOptCallouts;  /**< Rx buffer warning level user callout */
} Eth_30_Tc3xx_OptCalloutsType;

/**   \brief  type used in Eth_30_Tc3xx_QosHandling */
typedef struct sEth_30_Tc3xx_QosHandlingType
{
  Eth_30_Tc3xx_ShaperAvailableEndIdxOfQosHandlingType ShaperAvailableEndIdxOfQosHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_ShaperAvailable */
  Eth_30_Tc3xx_ShaperAvailableStartIdxOfQosHandlingType ShaperAvailableStartIdxOfQosHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_ShaperAvailable */
  Eth_30_Tc3xx_TxDescrHandlingIdxOfQosHandlingType TxDescrHandlingIdxOfQosHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_VlanPrioTxDescrRingMapEndIdxOfQosHandlingType VlanPrioTxDescrRingMapEndIdxOfQosHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
  Eth_30_Tc3xx_VlanPrioTxDescrRingMapStartIdxOfQosHandlingType VlanPrioTxDescrRingMapStartIdxOfQosHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
} Eth_30_Tc3xx_QosHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_RegData */
typedef struct sEth_30_Tc3xx_RegDataType
{
  Eth_30_Tc3xx_ValueOfRegDataType ValueOfRegData;  /**< Value of register */
  Eth_30_Tc3xx_OffsetOfRegDataType OffsetOfRegData;  /**< Offset of register relative to register base address */
  Eth_30_Tc3xx_AccessModeOfRegDataType AccessModeOfRegData;  /**< Mode of microcontroller where register is allowed to be modified */
} Eth_30_Tc3xx_RegDataType;

/**   \brief  type used in Eth_30_Tc3xx_RxBufferHandling */
typedef struct sEth_30_Tc3xx_RxBufferHandlingType
{
  Eth_30_Tc3xx_AlignedLastSegSizeOfRxBufferHandlingType AlignedLastSegSizeOfRxBufferHandling;  /**< Size of last segment including alignment, padding bytes, etc */
  Eth_30_Tc3xx_AlignedSegSizeOfRxBufferHandlingType AlignedSegSizeOfRxBufferHandling;  /**< Segment size including alignment, padding bytes, etc. */
  Eth_30_Tc3xx_MaxFrameSizeOfRxBufferHandlingType MaxFrameSizeOfRxBufferHandling;  /**< Maximum frame size as configured */
  Eth_30_Tc3xx_RxBufferEndIdxOfRxBufferHandlingType RxBufferEndIdxOfRxBufferHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxBuffer */
  Eth_30_Tc3xx_RxBufferStartIdxOfRxBufferHandlingType RxBufferStartIdxOfRxBufferHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxBuffer */
  Eth_30_Tc3xx_UnalignedSegSizeOfRxBufferHandlingType UnalignedSegSizeOfRxBufferHandling;  /**< Segment size as configured */
  Eth_30_Tc3xx_DescrNumOfRxBufferHandlingType DescrNumOfRxBufferHandling;  /**< Number of descriptors used in that descriptor ring */
  Eth_30_Tc3xx_SegNumOfRxBufferHandlingType SegNumOfRxBufferHandling;  /**< Number of segments contained in the descriptor ring */
} Eth_30_Tc3xx_RxBufferHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_RxDescrHandling */
typedef struct sEth_30_Tc3xx_RxDescrHandlingType
{
  Eth_30_Tc3xx_RxDescrEndIdxOfRxDescrHandlingType RxDescrEndIdxOfRxDescrHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescr */
  Eth_30_Tc3xx_RxDescrRingProcIdxOfRxDescrHandlingType RxDescrRingProcIdxOfRxDescrHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescrRingProc */
  Eth_30_Tc3xx_RxDescrStartIdxOfRxDescrHandlingType RxDescrStartIdxOfRxDescrHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescr */
  Eth_30_Tc3xx_RxDescrStateEndIdxOfRxDescrHandlingType RxDescrStateEndIdxOfRxDescrHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrState */
  Eth_30_Tc3xx_RxDescrStateStartIdxOfRxDescrHandlingType RxDescrStateStartIdxOfRxDescrHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxDescrState */
} Eth_30_Tc3xx_RxDescrHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_RxDescrRingProc */
typedef struct sEth_30_Tc3xx_RxDescrRingProcType
{
  Eth_30_Tc3xx_CurProcPosOfRxDescrRingProcType CurProcPosOfRxDescrRingProc;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescr */
} Eth_30_Tc3xx_RxDescrRingProcType;

/**   \brief  type used in Eth_30_Tc3xx_RxDescrState */
typedef struct sEth_30_Tc3xx_RxDescrStateType
{
  Eth_30_Tc3xx_MappedBufferOfRxDescrStateType MappedBufferOfRxDescrState;  /**< Rx buffer mapped to descriptor */
} Eth_30_Tc3xx_RxDescrStateType;

/**   \brief  type used in Eth_30_Tc3xx_RxTsContextStack */
typedef struct sEth_30_Tc3xx_RxTsContextStackType
{
  Eth_30_Tc3xx_DescrIdxOfRxTsContextStackType DescrIdxOfRxTsContextStack;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescr */
  Eth_30_Tc3xx_RingIdxOfRxTsContextStackType RingIdxOfRxTsContextStack;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxDescrHandling */
} Eth_30_Tc3xx_RxTsContextStackType;

/**   \brief  type used in Eth_30_Tc3xx_RxTxNotificationCallouts */
typedef struct sEth_30_Tc3xx_RxTxNotificationCalloutsType
{
  Eth_30_Tc3xx_EthRxIndicationCalloutFctPtrType RxIndicationCalloutOfRxTxNotificationCallouts;  /**< Rx-Indication Callout */
  Eth_30_Tc3xx_EthTxConfirmationCalloutFctPtrType TxConfirmationCalloutOfRxTxNotificationCallouts;  /**< Tx-Confirmation callout */
} Eth_30_Tc3xx_RxTxNotificationCalloutsType;

/**   \brief  type used in Eth_30_Tc3xx_TimeHandling */
typedef struct sEth_30_Tc3xx_TimeHandlingType
{
  Eth_30_Tc3xx_RateRatioOfTimeHandlingType RateRatioOfTimeHandling;  /**< Current drift correction factor */
  Eth_TimeStampType LatestCorrTimeOfTimeHandling;  /**< Latest time corrected by drift correction */
  Eth_TimeStampType LatestHwTimeOfTimeHandling;  /**< Latest time captured by hardware */
} Eth_30_Tc3xx_TimeHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_TsHandling */
typedef struct sEth_30_Tc3xx_TsHandlingType
{
  Eth_30_Tc3xx_RxTsContextStackEndIdxOfTsHandlingType RxTsContextStackEndIdxOfTsHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_RxTsContextStack */
  Eth_30_Tc3xx_RxTsContextStackPosIdxOfTsHandlingType RxTsContextStackPosIdxOfTsHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_RxTsContextStackPos */
  Eth_30_Tc3xx_RxTsContextStackStartIdxOfTsHandlingType RxTsContextStackStartIdxOfTsHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_RxTsContextStack */
  Eth_30_Tc3xx_TimeHandlingIdxOfTsHandlingType TimeHandlingIdxOfTsHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TimeHandling */
  Eth_30_Tc3xx_TxTsContextEndIdxOfTsHandlingType TxTsContextEndIdxOfTsHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxTsContext */
  Eth_30_Tc3xx_TxTsContextStartIdxOfTsHandlingType TxTsContextStartIdxOfTsHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxTsContext */
} Eth_30_Tc3xx_TsHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_TxBufferData */
typedef struct sEth_30_Tc3xx_TxBufferDataType
{
  Eth_30_Tc3xx_LengthOfTxBufferDataType LengthOfTxBufferData;  /**< Length of the Tx buffer */
  Eth_30_Tc3xx_StartPosOfTxBufferDataType StartPosOfTxBufferData;  /**< Position of Tx buffer within buffer pool */
} Eth_30_Tc3xx_TxBufferDataType;

/**   \brief  type used in Eth_30_Tc3xx_TxBufferHandling */
typedef struct sEth_30_Tc3xx_TxBufferHandlingType
{
  Eth_30_Tc3xx_AlignedSegSizeOfTxBufferHandlingType AlignedSegSizeOfTxBufferHandling;  /**< Segment size including alignment, padding bytes, etc. */
  Eth_30_Tc3xx_MaxBufferLenOfTxBufferHandlingType MaxBufferLenOfTxBufferHandling;  /**< Length of the greates buffer */
  Eth_30_Tc3xx_TxBufferEndIdxOfTxBufferHandlingType TxBufferEndIdxOfTxBufferHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBuffer */
  Eth_30_Tc3xx_TxBufferStartIdxOfTxBufferHandlingType TxBufferStartIdxOfTxBufferHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBuffer */
  Eth_30_Tc3xx_BufferNumOfTxBufferHandlingType BufferNumOfTxBufferHandling;  /**< Number of tx buffers */
  Eth_30_Tc3xx_DescrNumOfTxBufferHandlingType DescrNumOfTxBufferHandling;  /**< Numer of tx descriptors */
  Eth_30_Tc3xx_TxBufferDataEndIdxOfTxBufferHandlingType TxBufferDataEndIdxOfTxBufferHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferData */
  Eth_30_Tc3xx_TxBufferDataStartIdxOfTxBufferHandlingType TxBufferDataStartIdxOfTxBufferHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferData */
  Eth_30_Tc3xx_TxBufferFreeElemNumIdxOfTxBufferHandlingType TxBufferFreeElemNumIdxOfTxBufferHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxBufferFreeElemNum */
  Eth_30_Tc3xx_TxBufferStateEndIdxOfTxBufferHandlingType TxBufferStateEndIdxOfTxBufferHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferState */
  Eth_30_Tc3xx_TxBufferStateStartIdxOfTxBufferHandlingType TxBufferStateStartIdxOfTxBufferHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxBufferState */
} Eth_30_Tc3xx_TxBufferHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_TxBufferState */
typedef struct sEth_30_Tc3xx_TxBufferStateType
{
  Eth_30_Tc3xx_BusyOfTxBufferStateType BusyOfTxBufferState;  /**< Busy state */
  Eth_30_Tc3xx_TsRequestedOfTxBufferStateType TsRequestedOfTxBufferState;  /**< Time stamping request state */
  Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType UlTxConfStateOfTxBufferState;  /**< Upper layer tx confirmation state */
} Eth_30_Tc3xx_TxBufferStateType;

/**   \brief  type used in Eth_30_Tc3xx_TxDescrHandling */
typedef struct sEth_30_Tc3xx_TxDescrHandlingType
{
  Eth_30_Tc3xx_TxDescrEndIdxOfTxDescrHandlingType TxDescrEndIdxOfTxDescrHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_TxDescrRingProcIdxOfTxDescrHandlingType TxDescrRingProcIdxOfTxDescrHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrRingProc */
  Eth_30_Tc3xx_TxDescrStartIdxOfTxDescrHandlingType TxDescrStartIdxOfTxDescrHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_TxDescrStateEndIdxOfTxDescrHandlingType TxDescrStateEndIdxOfTxDescrHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrState */
  Eth_30_Tc3xx_TxDescrStateStartIdxOfTxDescrHandlingType TxDescrStateStartIdxOfTxDescrHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_TxDescrState */
} Eth_30_Tc3xx_TxDescrHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_TxDescrRingProc */
typedef struct sEth_30_Tc3xx_TxDescrRingProcType
{
  Eth_30_Tc3xx_CurProcPosOfTxDescrRingProcType CurProcPosOfTxDescrRingProc;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_FreePosOfTxDescrRingProcType FreePosOfTxDescrRingProc;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr */
} Eth_30_Tc3xx_TxDescrRingProcType;

/**   \brief  type used in Eth_30_Tc3xx_TxDescrState */
typedef struct sEth_30_Tc3xx_TxDescrStateType
{
  Eth_30_Tc3xx_MappedBufferOfTxDescrStateType MappedBufferOfTxDescrState;  /**< Tx buffer mapped to descriptor */
  Eth_30_Tc3xx_TxReadyOfTxDescrStateType TxReadyOfTxDescrState;  /**< Tx ready state */
} Eth_30_Tc3xx_TxDescrStateType;

/**   \brief  type used in Eth_30_Tc3xx_TxTsContext */
typedef struct sEth_30_Tc3xx_TxTsContextType
{
  Eth_30_Tc3xx_DescrIdxOfTxTsContextType DescrIdxOfTxTsContext;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_RingIdxOfTxTsContextType RingIdxOfTxTsContext;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrHandling */
} Eth_30_Tc3xx_TxTsContextType;

/**   \brief  type used in Eth_30_Tc3xx_UserInitCallouts */
typedef struct sEth_30_Tc3xx_UserInitCalloutsType
{
  Eth_30_Tc3xx_UserPostCtrlInitCalloutFctPtrType PostInitUserCalloutOfUserInitCallouts;  /**< Post-Controller-Initialization callout */
  Eth_30_Tc3xx_UserPreCtrlInitCalloutFctPtrType PreInitUserCalloutOfUserInitCallouts;  /**< Pre-Controller-Initialization callout */
} Eth_30_Tc3xx_UserInitCalloutsType;

/**   \brief  type used in Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
typedef struct sEth_30_Tc3xx_VlanIdBasedQueuingHandlingType
{
  Eth_30_Tc3xx_TxDescrHandlingIdxOfVlanIdBasedQueuingHandlingType TxDescrHandlingIdxOfVlanIdBasedQueuingHandling;  /**< the index of the 1:1 relation pointing to Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType VlanIdRxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_VlanIdRxDescrRingMap */
  Eth_30_Tc3xx_VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType VlanIdRxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_VlanIdRxDescrRingMap */
  Eth_30_Tc3xx_VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandlingType VlanIdTxDescrRingMapEndIdxOfVlanIdBasedQueuingHandling;  /**< the end index of the 1:n relation pointing to Eth_30_Tc3xx_VlanIdTxDescrRingMap */
  Eth_30_Tc3xx_VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandlingType VlanIdTxDescrRingMapStartIdxOfVlanIdBasedQueuingHandling;  /**< the start index of the 1:n relation pointing to Eth_30_Tc3xx_VlanIdTxDescrRingMap */
} Eth_30_Tc3xx_VlanIdBasedQueuingHandlingType;

/**   \brief  type used in Eth_30_Tc3xx_VlanIdRxDescrRingMap */
typedef struct sEth_30_Tc3xx_VlanIdRxDescrRingMapType
{
  Eth_30_Tc3xx_QueueIndexOfVlanIdRxDescrRingMapType QueueIndexOfVlanIdRxDescrRingMap;  /**< Rx Queue index associated with the corresponding VLAN-ID */
  Eth_30_Tc3xx_VlanIdOfVlanIdRxDescrRingMapType VlanIdOfVlanIdRxDescrRingMap;  /**< VLAN-ID to be filtered */
} Eth_30_Tc3xx_VlanIdRxDescrRingMapType;

/**   \brief  type used in Eth_30_Tc3xx_VlanIdTxDescrRingMap */
typedef struct sEth_30_Tc3xx_VlanIdTxDescrRingMapType
{
  Eth_30_Tc3xx_QueueIndexOfVlanIdTxDescrRingMapType QueueIndexOfVlanIdTxDescrRingMap;  /**< Tx Queue index associated with the corresponding VLAN-ID */
  Eth_30_Tc3xx_VlanIdOfVlanIdTxDescrRingMapType VlanIdOfVlanIdTxDescrRingMap;  /**< VLAN-ID to be filtered */
} Eth_30_Tc3xx_VlanIdTxDescrRingMapType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCSymbolicStructTypes  Eth_30_Tc3xx Symbolic Struct Types (PRE_COMPILE)
  \brief  These structs are used in unions to have a symbol based data representation style.
  \{
*/ 
/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_ActiveMacAddress */
typedef struct Eth_30_Tc3xx_ActiveMacAddressStructSTag
{
  Eth_30_Tc3xx_ActiveMacAddressType EthCtrlConfig[6];
} Eth_30_Tc3xx_ActiveMacAddressStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_MulticastBucketCounters */
typedef struct Eth_30_Tc3xx_MulticastBucketCountersStructSTag
{
  Eth_30_Tc3xx_MulticastBucketCountersType EthCtrlConfig[64];
} Eth_30_Tc3xx_MulticastBucketCountersStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxBuffer */
typedef struct Eth_30_Tc3xx_RxBufferStructSTag
{
  Eth_30_Tc3xx_RxBufferType EthCtrlConfig_EthRxBufConfig[3072];
} Eth_30_Tc3xx_RxBufferStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxDescr */
typedef struct Eth_30_Tc3xx_RxDescrStructSTag
{
  Eth_30_Tc3xx_RxDescriptorType EthCtrlConfig[2];
} Eth_30_Tc3xx_RxDescrStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxDescrRingProc */
typedef struct Eth_30_Tc3xx_RxDescrRingProcStructSTag
{
  Eth_30_Tc3xx_RxDescrRingProcType EthCtrlConfig[1];
} Eth_30_Tc3xx_RxDescrRingProcStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxDescrState */
typedef struct Eth_30_Tc3xx_RxDescrStateStructSTag
{
  Eth_30_Tc3xx_RxDescrStateType EthCtrlConfig[2];
} Eth_30_Tc3xx_RxDescrStateStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxTsContextStack */
typedef struct Eth_30_Tc3xx_RxTsContextStackStructSTag
{
  Eth_30_Tc3xx_RxTsContextStackType EthCtrlConfig[1];
} Eth_30_Tc3xx_RxTsContextStackStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_RxTsContextStackPos */
typedef struct Eth_30_Tc3xx_RxTsContextStackPosStructSTag
{
  Eth_30_Tc3xx_RxTsContextStackPosType EthCtrlConfig[1];
} Eth_30_Tc3xx_RxTsContextStackPosStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TimeHandling */
typedef struct Eth_30_Tc3xx_TimeHandlingStructSTag
{
  Eth_30_Tc3xx_TimeHandlingType EthCtrlConfig[1];
} Eth_30_Tc3xx_TimeHandlingStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxBuffer */
typedef struct Eth_30_Tc3xx_TxBufferStructSTag
{
  Eth_30_Tc3xx_TxBufferType EthCtrlConfig[6144];
} Eth_30_Tc3xx_TxBufferStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxBufferFreeElemNum */
typedef struct Eth_30_Tc3xx_TxBufferFreeElemNumStructSTag
{
  Eth_30_Tc3xx_TxBufferFreeElemNumType EthCtrlConfig[1];
} Eth_30_Tc3xx_TxBufferFreeElemNumStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxBufferState */
typedef struct Eth_30_Tc3xx_TxBufferStateStructSTag
{
  Eth_30_Tc3xx_TxBufferStateType EthCtrlConfig[4];
} Eth_30_Tc3xx_TxBufferStateStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxDescr */
typedef struct Eth_30_Tc3xx_TxDescrStructSTag
{
  Eth_30_Tc3xx_TxDescriptorType EthCtrlConfig[4];
} Eth_30_Tc3xx_TxDescrStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxDescrRingProc */
typedef struct Eth_30_Tc3xx_TxDescrRingProcStructSTag
{
  Eth_30_Tc3xx_TxDescrRingProcType EthCtrlConfig[1];
} Eth_30_Tc3xx_TxDescrRingProcStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxDescrState */
typedef struct Eth_30_Tc3xx_TxDescrStateStructSTag
{
  Eth_30_Tc3xx_TxDescrStateType EthCtrlConfig[4];
} Eth_30_Tc3xx_TxDescrStateStructSType;

/**   \brief  type to be used as symbolic data element access to Eth_30_Tc3xx_TxTsContext */
typedef struct Eth_30_Tc3xx_TxTsContextStructSTag
{
  Eth_30_Tc3xx_TxTsContextType EthCtrlConfig[4];
} Eth_30_Tc3xx_TxTsContextStructSType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCUnionIndexAndSymbolTypes  Eth_30_Tc3xx Union Index And Symbol Types (PRE_COMPILE)
  \brief  These unions are used to access arrays in an index and symbol based style.
  \{
*/ 
/**   \brief  type to access Eth_30_Tc3xx_ActiveMacAddress in an index and symbol based style. */
typedef union Eth_30_Tc3xx_ActiveMacAddressUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_ActiveMacAddressType raw[6];
  Eth_30_Tc3xx_ActiveMacAddressStructSType str;
} Eth_30_Tc3xx_ActiveMacAddressUType;

/**   \brief  type to access Eth_30_Tc3xx_MulticastBucketCounters in an index and symbol based style. */
typedef union Eth_30_Tc3xx_MulticastBucketCountersUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_MulticastBucketCountersType raw[64];
  Eth_30_Tc3xx_MulticastBucketCountersStructSType str;
} Eth_30_Tc3xx_MulticastBucketCountersUType;

/**   \brief  type to access Eth_30_Tc3xx_RxBuffer in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxBufferUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxBufferType raw[3072];
  Eth_30_Tc3xx_RxBufferStructSType str;
} Eth_30_Tc3xx_RxBufferUType;

/**   \brief  type to access Eth_30_Tc3xx_RxDescr in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxDescrUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxDescriptorType raw[2];
  Eth_30_Tc3xx_RxDescrStructSType str;
} Eth_30_Tc3xx_RxDescrUType;

/**   \brief  type to access Eth_30_Tc3xx_RxDescrRingProc in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxDescrRingProcUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxDescrRingProcType raw[1];
  Eth_30_Tc3xx_RxDescrRingProcStructSType str;
} Eth_30_Tc3xx_RxDescrRingProcUType;

/**   \brief  type to access Eth_30_Tc3xx_RxDescrState in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxDescrStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxDescrStateType raw[2];
  Eth_30_Tc3xx_RxDescrStateStructSType str;
} Eth_30_Tc3xx_RxDescrStateUType;

/**   \brief  type to access Eth_30_Tc3xx_RxTsContextStack in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxTsContextStackUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxTsContextStackType raw[1];
  Eth_30_Tc3xx_RxTsContextStackStructSType str;
} Eth_30_Tc3xx_RxTsContextStackUType;

/**   \brief  type to access Eth_30_Tc3xx_RxTsContextStackPos in an index and symbol based style. */
typedef union Eth_30_Tc3xx_RxTsContextStackPosUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_RxTsContextStackPosType raw[1];
  Eth_30_Tc3xx_RxTsContextStackPosStructSType str;
} Eth_30_Tc3xx_RxTsContextStackPosUType;

/**   \brief  type to access Eth_30_Tc3xx_TimeHandling in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TimeHandlingUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TimeHandlingType raw[1];  /* PRQA S 3629 */  /* MD_CSL_3629 */
  Eth_30_Tc3xx_TimeHandlingStructSType str;
} Eth_30_Tc3xx_TimeHandlingUType;

/**   \brief  type to access Eth_30_Tc3xx_TxBuffer in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxBufferUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxBufferType raw[6144];
  Eth_30_Tc3xx_TxBufferStructSType str;
} Eth_30_Tc3xx_TxBufferUType;

/**   \brief  type to access Eth_30_Tc3xx_TxBufferFreeElemNum in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxBufferFreeElemNumUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxBufferFreeElemNumType raw[1];
  Eth_30_Tc3xx_TxBufferFreeElemNumStructSType str;
} Eth_30_Tc3xx_TxBufferFreeElemNumUType;

/**   \brief  type to access Eth_30_Tc3xx_TxBufferState in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxBufferStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxBufferStateType raw[4];
  Eth_30_Tc3xx_TxBufferStateStructSType str;
} Eth_30_Tc3xx_TxBufferStateUType;

/**   \brief  type to access Eth_30_Tc3xx_TxDescr in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxDescrUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxDescriptorType raw[4];
  Eth_30_Tc3xx_TxDescrStructSType str;
} Eth_30_Tc3xx_TxDescrUType;

/**   \brief  type to access Eth_30_Tc3xx_TxDescrRingProc in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxDescrRingProcUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxDescrRingProcType raw[1];
  Eth_30_Tc3xx_TxDescrRingProcStructSType str;
} Eth_30_Tc3xx_TxDescrRingProcUType;

/**   \brief  type to access Eth_30_Tc3xx_TxDescrState in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxDescrStateUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxDescrStateType raw[4];
  Eth_30_Tc3xx_TxDescrStateStructSType str;
} Eth_30_Tc3xx_TxDescrStateUType;

/**   \brief  type to access Eth_30_Tc3xx_TxTsContext in an index and symbol based style. */
typedef union Eth_30_Tc3xx_TxTsContextUTag
{  /* PRQA S 0750 */  /* MD_CSL_18.4 */
  Eth_30_Tc3xx_TxTsContextType raw[4];
  Eth_30_Tc3xx_TxTsContextStructSType str;
} Eth_30_Tc3xx_TxTsContextUType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCRootPointerTypes  Eth_30_Tc3xx Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to Eth_30_Tc3xx_ActiveMacAddress */
typedef P2VAR(Eth_30_Tc3xx_ActiveMacAddressType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ActiveMacAddressPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthCtrl */
typedef P2CONST(Eth_30_Tc3xx_EthCtrlType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrlPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthCtrlState */
typedef P2VAR(Eth_30_Tc3xx_EthCtrlStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_CtrlModeOfEthCtrlState */
typedef P2VAR(Eth_ModeType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_CtrlModeOfEthCtrlStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_PendingRxEventsOfEthCtrlState */
typedef P2VAR(Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PendingRxEventsOfEthCtrlStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_PendingTxEventsOfEthCtrlState */
typedef P2VAR(Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PendingTxEventsOfEthCtrlStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RegBaseAddrOfEthCtrlState */
typedef P2VAR(Eth_30_Tc3xx_RegBaseAddrType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RegBaseAddrOfEthCtrlStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthCtrlTc3xx */
typedef P2CONST(Eth_30_Tc3xx_EthCtrlTc3xxType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrlTc3xxPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthCtrlTc3xxState */
typedef P2VAR(Eth_30_Tc3xx_EthCtrlTc3xxStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlTc3xxStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxState */
typedef P2VAR(Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ReadMiiResultOfEthCtrlTc3xxStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxStatsOfEthCtrlTc3xxState */
typedef P2VAR(Eth_RxStatsType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxStatsOfEthCtrlTc3xxStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthMeasDataCounter */
typedef P2VAR(Eth_30_Tc3xx_EthMeasDataCounterType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounterPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounter */
typedef P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_DropInsuffRxBuffOfEthMeasDataCounterPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounter */
typedef P2VAR(Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_DropInsuffTxBuffOfEthMeasDataCounterPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounter */
typedef P2VAR(Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_WarnFullRxBuffOfEthMeasDataCounterPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthMeasDataCounterReset */
typedef P2VAR(Eth_30_Tc3xx_EthMeasDataCounterResetType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounterResetPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterReset */
typedef P2VAR(Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_DropInsuffRxBuffResetOfEthMeasDataCounterResetPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_EthSwtIfc */
typedef P2CONST(Eth_30_Tc3xx_EthSwtIfcType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthSwtIfcPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_InitialMacAddress */
typedef P2CONST(Eth_30_Tc3xx_InitialMacAddressType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_InitialMacAddressPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_IsrInfos */
typedef P2CONST(Eth_30_Tc3xx_IsrInfosType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrInfosPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_IsrIrqEventFuncs */
typedef P2CONST(Eth_30_Tc3xx_IrqEventFctPtrType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrIrqEventFuncsPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_MulticastBucketCounters */
typedef P2VAR(Eth_30_Tc3xx_MulticastBucketCountersType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_MulticastBucketCountersPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_OptCallouts */
typedef P2CONST(Eth_30_Tc3xx_OptCalloutsType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_OptCalloutsPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_PromiscuousModeCounter */
typedef P2VAR(Eth_30_Tc3xx_PromiscuousModeCounterType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PromiscuousModeCounterPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_QosHandling */
typedef P2CONST(Eth_30_Tc3xx_QosHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_QosHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RegData */
typedef P2CONST(Eth_30_Tc3xx_RegDataType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RegDataPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxBuffer */
typedef P2VAR(Eth_30_Tc3xx_RxBufferType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxBufferPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxBufferHandling */
typedef P2CONST(Eth_30_Tc3xx_RxBufferHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxBufferHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxDescr */
typedef P2VAR(Eth_30_Tc3xx_RxDescriptorType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxDescrHandling */
typedef P2CONST(Eth_30_Tc3xx_RxDescrHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxDescrHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxDescrRingProc */
typedef P2VAR(Eth_30_Tc3xx_RxDescrRingProcType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrRingProcPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxDescrState */
typedef P2VAR(Eth_30_Tc3xx_RxDescrStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_MappedBufferOfRxDescrState */
typedef P2VAR(Eth_30_Tc3xx_MappedBufferOfRxDescrStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_MappedBufferOfRxDescrStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxTsContextStack */
typedef P2VAR(Eth_30_Tc3xx_RxTsContextStackType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStackPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxTsContextStackPos */
typedef P2VAR(Eth_30_Tc3xx_RxTsContextStackPosType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStackPosPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RxTxNotificationCallouts */
typedef P2CONST(Eth_30_Tc3xx_RxTxNotificationCalloutsType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxTxNotificationCalloutsPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_ShaperAvailable */
typedef P2CONST(Eth_30_Tc3xx_ShaperAvailableType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_ShaperAvailablePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TimeHandling */
typedef P2VAR(Eth_30_Tc3xx_TimeHandlingType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TimeHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_LatestCorrTimeOfTimeHandling */
typedef P2VAR(Eth_TimeStampType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_LatestCorrTimeOfTimeHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_LatestHwTimeOfTimeHandling */
typedef P2VAR(Eth_TimeStampType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_LatestHwTimeOfTimeHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_RateRatioOfTimeHandling */
typedef P2VAR(Eth_30_Tc3xx_RateRatioOfTimeHandlingType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RateRatioOfTimeHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TsHandling */
typedef P2CONST(Eth_30_Tc3xx_TsHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TsHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxBuffer */
typedef P2VAR(Eth_30_Tc3xx_TxBufferType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxBufferData */
typedef P2CONST(Eth_30_Tc3xx_TxBufferDataType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferDataPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxBufferFreeElemNum */
typedef P2VAR(Eth_30_Tc3xx_TxBufferFreeElemNumType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferFreeElemNumPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxBufferHandling */
typedef P2CONST(Eth_30_Tc3xx_TxBufferHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxBufferState */
typedef P2VAR(Eth_30_Tc3xx_TxBufferStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_UlTxConfStateOfTxBufferState */
typedef P2VAR(Eth_30_Tc3xx_UlTxConfStateOfTxBufferStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_UlTxConfStateOfTxBufferStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxDescr */
typedef P2VAR(Eth_30_Tc3xx_TxDescriptorType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxDescrHandling */
typedef P2CONST(Eth_30_Tc3xx_TxDescrHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxDescrHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxDescrRingProc */
typedef P2VAR(Eth_30_Tc3xx_TxDescrRingProcType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrRingProcPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxDescrState */
typedef P2VAR(Eth_30_Tc3xx_TxDescrStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_MappedBufferOfTxDescrState */
typedef P2VAR(Eth_30_Tc3xx_MappedBufferOfTxDescrStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_MappedBufferOfTxDescrStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxReadyOfTxDescrState */
typedef P2VAR(Eth_30_Tc3xx_TxReadyOfTxDescrStateType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxReadyOfTxDescrStatePtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_TxTsContext */
typedef P2VAR(Eth_30_Tc3xx_TxTsContextType, TYPEDEF, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxTsContextPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_UserInitCallouts */
typedef P2CONST(Eth_30_Tc3xx_UserInitCalloutsType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_UserInitCalloutsPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
typedef P2CONST(Eth_30_Tc3xx_VlanIdBasedQueuingHandlingType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_VlanIdBasedQueuingHandlingPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_VlanIdRxDescrRingMap */
typedef P2CONST(Eth_30_Tc3xx_VlanIdRxDescrRingMapType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_VlanIdRxDescrRingMapPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_VlanIdTxDescrRingMap */
typedef P2CONST(Eth_30_Tc3xx_VlanIdTxDescrRingMapType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_VlanIdTxDescrRingMapPtrType;

/**   \brief  type used to point to Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
typedef P2CONST(Eth_30_Tc3xx_VlanPrioTxDescrRingMapType, TYPEDEF, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_VlanPrioTxDescrRingMapPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  Eth_30_Tc3xxPCRootValueTypes  Eth_30_Tc3xx Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in Eth_30_Tc3xx_PCConfig */
typedef struct sEth_30_Tc3xx_PCConfigType
{
  Eth_30_Tc3xx_ActiveMacAddressPtrType ActiveMacAddressOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_ActiveMacAddress */
  Eth_30_Tc3xx_EthCtrlPtrType EthCtrlOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthCtrl */
  Eth_30_Tc3xx_EthCtrlStatePtrType EthCtrlStateOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthCtrlState */
  Eth_30_Tc3xx_EthCtrlTc3xxPtrType EthCtrlTc3xxOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthCtrlTc3xx */
  Eth_30_Tc3xx_EthCtrlTc3xxStatePtrType EthCtrlTc3xxStateOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthCtrlTc3xxState */
  Eth_30_Tc3xx_EthMeasDataCounterPtrType EthMeasDataCounterOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthMeasDataCounter */
  Eth_30_Tc3xx_EthMeasDataCounterResetPtrType EthMeasDataCounterResetOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthMeasDataCounterReset */
  Eth_30_Tc3xx_EthSwtIfcPtrType EthSwtIfcOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_EthSwtIfc */
  Eth_30_Tc3xx_InitialMacAddressPtrType InitialMacAddressOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_InitialMacAddress */
  Eth_30_Tc3xx_IsrInfosPtrType IsrInfosOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_IsrInfos */
  Eth_30_Tc3xx_IsrIrqEventFuncsPtrType IsrIrqEventFuncsOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_IsrIrqEventFuncs */
  Eth_30_Tc3xx_MulticastBucketCountersPtrType MulticastBucketCountersOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_MulticastBucketCounters */
  Eth_30_Tc3xx_OptCalloutsPtrType OptCalloutsOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_OptCallouts */
  Eth_30_Tc3xx_PromiscuousModeCounterPtrType PromiscuousModeCounterOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_PromiscuousModeCounter */
  Eth_30_Tc3xx_QosHandlingPtrType QosHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_QosHandling */
  Eth_30_Tc3xx_RegDataPtrType RegDataOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RegData */
  Eth_30_Tc3xx_RxBufferPtrType RxBufferOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxBuffer */
  Eth_30_Tc3xx_RxBufferHandlingPtrType RxBufferHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxBufferHandling */
  Eth_30_Tc3xx_RxDescrPtrType RxDescrOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxDescr */
  Eth_30_Tc3xx_RxDescrHandlingPtrType RxDescrHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxDescrHandling */
  Eth_30_Tc3xx_RxDescrRingProcPtrType RxDescrRingProcOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxDescrRingProc */
  Eth_30_Tc3xx_RxDescrStatePtrType RxDescrStateOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxDescrState */
  Eth_30_Tc3xx_RxTsContextStackPtrType RxTsContextStackOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxTsContextStack */
  Eth_30_Tc3xx_RxTsContextStackPosPtrType RxTsContextStackPosOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxTsContextStackPos */
  Eth_30_Tc3xx_RxTxNotificationCalloutsPtrType RxTxNotificationCalloutsOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_RxTxNotificationCallouts */
  Eth_30_Tc3xx_ShaperAvailablePtrType ShaperAvailableOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_ShaperAvailable */
  Eth_30_Tc3xx_TimeHandlingPtrType TimeHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TimeHandling */
  Eth_30_Tc3xx_TsHandlingPtrType TsHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TsHandling */
  Eth_30_Tc3xx_TxBufferPtrType TxBufferOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxBuffer */
  Eth_30_Tc3xx_TxBufferDataPtrType TxBufferDataOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxBufferData */
  Eth_30_Tc3xx_TxBufferFreeElemNumPtrType TxBufferFreeElemNumOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxBufferFreeElemNum */
  Eth_30_Tc3xx_TxBufferHandlingPtrType TxBufferHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxBufferHandling */
  Eth_30_Tc3xx_TxBufferStatePtrType TxBufferStateOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxBufferState */
  Eth_30_Tc3xx_TxDescrPtrType TxDescrOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_TxDescrHandlingPtrType TxDescrHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_TxDescrRingProcPtrType TxDescrRingProcOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxDescrRingProc */
  Eth_30_Tc3xx_TxDescrStatePtrType TxDescrStateOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxDescrState */
  Eth_30_Tc3xx_TxTsContextPtrType TxTsContextOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_TxTsContext */
  Eth_30_Tc3xx_UserInitCalloutsPtrType UserInitCalloutsOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_UserInitCallouts */
  Eth_30_Tc3xx_VlanIdBasedQueuingHandlingPtrType VlanIdBasedQueuingHandlingOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
  Eth_30_Tc3xx_VlanIdRxDescrRingMapPtrType VlanIdRxDescrRingMapOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_VlanIdRxDescrRingMap */
  Eth_30_Tc3xx_VlanIdTxDescrRingMapPtrType VlanIdTxDescrRingMapOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_VlanIdTxDescrRingMap */
  Eth_30_Tc3xx_VlanPrioTxDescrRingMapPtrType VlanPrioTxDescrRingMapOfPCConfig;  /**< the pointer to Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
  Eth_30_Tc3xx_SizeOfRxBufferType SizeOfRxBufferOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxBuffer */
  Eth_30_Tc3xx_SizeOfTxBufferType SizeOfTxBufferOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxBuffer */
  Eth_30_Tc3xx_SizeOfActiveMacAddressType SizeOfActiveMacAddressOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_ActiveMacAddress */
  Eth_30_Tc3xx_SizeOfEthCtrlType SizeOfEthCtrlOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrl */
  Eth_30_Tc3xx_SizeOfEthCtrlTc3xxType SizeOfEthCtrlTc3xxOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthCtrlTc3xx */
  Eth_30_Tc3xx_SizeOfEthSwtIfcType SizeOfEthSwtIfcOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_EthSwtIfc */
  Eth_30_Tc3xx_SizeOfInitialMacAddressType SizeOfInitialMacAddressOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_InitialMacAddress */
  Eth_30_Tc3xx_SizeOfIsrInfosType SizeOfIsrInfosOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_IsrInfos */
  Eth_30_Tc3xx_SizeOfIsrIrqEventFuncsType SizeOfIsrIrqEventFuncsOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_IsrIrqEventFuncs */
  Eth_30_Tc3xx_SizeOfMulticastBucketCountersType SizeOfMulticastBucketCountersOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_MulticastBucketCounters */
  Eth_30_Tc3xx_SizeOfOptCalloutsType SizeOfOptCalloutsOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_OptCallouts */
  Eth_30_Tc3xx_SizeOfQosHandlingType SizeOfQosHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_QosHandling */
  Eth_30_Tc3xx_SizeOfRegDataType SizeOfRegDataOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RegData */
  Eth_30_Tc3xx_SizeOfRxBufferHandlingType SizeOfRxBufferHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxBufferHandling */
  Eth_30_Tc3xx_SizeOfRxDescrType SizeOfRxDescrOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxDescr */
  Eth_30_Tc3xx_SizeOfRxDescrHandlingType SizeOfRxDescrHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrHandling */
  Eth_30_Tc3xx_SizeOfRxDescrRingProcType SizeOfRxDescrRingProcOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrRingProc */
  Eth_30_Tc3xx_SizeOfRxDescrStateType SizeOfRxDescrStateOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxDescrState */
  Eth_30_Tc3xx_SizeOfRxTsContextStackType SizeOfRxTsContextStackOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxTsContextStack */
  Eth_30_Tc3xx_SizeOfRxTsContextStackPosType SizeOfRxTsContextStackPosOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxTsContextStackPos */
  Eth_30_Tc3xx_SizeOfRxTxNotificationCalloutsType SizeOfRxTxNotificationCalloutsOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_RxTxNotificationCallouts */
  Eth_30_Tc3xx_SizeOfShaperAvailableType SizeOfShaperAvailableOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_ShaperAvailable */
  Eth_30_Tc3xx_SizeOfTimeHandlingType SizeOfTimeHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TimeHandling */
  Eth_30_Tc3xx_SizeOfTsHandlingType SizeOfTsHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TsHandling */
  Eth_30_Tc3xx_SizeOfTxBufferDataType SizeOfTxBufferDataOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferData */
  Eth_30_Tc3xx_SizeOfTxBufferFreeElemNumType SizeOfTxBufferFreeElemNumOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferFreeElemNum */
  Eth_30_Tc3xx_SizeOfTxBufferHandlingType SizeOfTxBufferHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferHandling */
  Eth_30_Tc3xx_SizeOfTxBufferStateType SizeOfTxBufferStateOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxBufferState */
  Eth_30_Tc3xx_SizeOfTxDescrType SizeOfTxDescrOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxDescr */
  Eth_30_Tc3xx_SizeOfTxDescrHandlingType SizeOfTxDescrHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrHandling */
  Eth_30_Tc3xx_SizeOfTxDescrRingProcType SizeOfTxDescrRingProcOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrRingProc */
  Eth_30_Tc3xx_SizeOfTxDescrStateType SizeOfTxDescrStateOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxDescrState */
  Eth_30_Tc3xx_SizeOfTxTsContextType SizeOfTxTsContextOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_TxTsContext */
  Eth_30_Tc3xx_SizeOfUserInitCalloutsType SizeOfUserInitCalloutsOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_UserInitCallouts */
  Eth_30_Tc3xx_SizeOfVlanIdBasedQueuingHandlingType SizeOfVlanIdBasedQueuingHandlingOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdBasedQueuingHandling */
  Eth_30_Tc3xx_SizeOfVlanIdRxDescrRingMapType SizeOfVlanIdRxDescrRingMapOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdRxDescrRingMap */
  Eth_30_Tc3xx_SizeOfVlanIdTxDescrRingMapType SizeOfVlanIdTxDescrRingMapOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_VlanIdTxDescrRingMap */
  Eth_30_Tc3xx_SizeOfVlanPrioTxDescrRingMapType SizeOfVlanPrioTxDescrRingMapOfPCConfig;  /**< the number of accomplishable value elements in Eth_30_Tc3xx_VlanPrioTxDescrRingMap */
} Eth_30_Tc3xx_PCConfigType;

typedef Eth_30_Tc3xx_PCConfigType Eth_30_Tc3xx_ConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/**   \brief  type to access Eth_30_Tc3xx_PCConfig in a symbol based style. */
typedef struct sEth_30_Tc3xx_PCConfigsType
{
  Eth_30_Tc3xx_PCConfigType Config;  /**< [Config] */
} Eth_30_Tc3xx_PCConfigsType;

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(Eth_30_Tc3xx_EthCtrlType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrl[1];
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
  PinRouting             Pin routing configuration
  CsrClockRange          CsrClockRange configuration
  EthCtrlMiiInterface    MiiInterface of the controller
  ArmPpsOnTimeEnabled    ArmPpsOnTime configuration
  AmountOfRxQueues       Amount of configured QoS Rx queues
  AmountOfTxQueues       Amount of configured QoS Tx queues
*/ 
#define ETH_30_TC3XX_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */
extern CONST(Eth_30_Tc3xx_EthCtrlTc3xxType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_EthCtrlTc3xx[1];
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
extern CONST(Eth_30_Tc3xx_InitialMacAddressType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_InitialMacAddress[6];
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
extern CONST(Eth_30_Tc3xx_IsrInfosType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrInfos[1];
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
extern CONST(Eth_30_Tc3xx_IrqEventFctPtrType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_IsrIrqEventFuncs[3];
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
extern CONST(Eth_30_Tc3xx_OptCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_OptCallouts[1];
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
extern CONST(Eth_30_Tc3xx_RegDataType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RegData[29];
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
extern CONST(Eth_30_Tc3xx_RxBufferHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxBufferHandling[1];
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
extern CONST(Eth_30_Tc3xx_RxDescrHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxDescrHandling[1];
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
extern CONST(Eth_30_Tc3xx_RxTxNotificationCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_RxTxNotificationCallouts[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern CONST(Eth_30_Tc3xx_TsHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TsHandling[1];
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
extern CONST(Eth_30_Tc3xx_TxBufferDataType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferData[4];
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
extern CONST(Eth_30_Tc3xx_TxBufferHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxBufferHandling[1];
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
extern CONST(Eth_30_Tc3xx_TxDescrHandlingType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_TxDescrHandling[1];
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
extern CONST(Eth_30_Tc3xx_UserInitCalloutsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_UserInitCallouts[1];
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
extern VAR(Eth_30_Tc3xx_ActiveMacAddressUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_ActiveMacAddress;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_EthCtrlStateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlState[1];
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
extern VAR(Eth_30_Tc3xx_EthCtrlTc3xxStateType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthCtrlTc3xxState[1];
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
extern VAR(Eth_30_Tc3xx_EthMeasDataCounterType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounter[1];
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
extern VAR(Eth_30_Tc3xx_EthMeasDataCounterResetType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_EthMeasDataCounterReset[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern VAR(Eth_30_Tc3xx_MulticastBucketCountersUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_MulticastBucketCounters;  /* PRQA S 0777, 0759 */  /* MD_MSR_5.1_777, MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_PromiscuousModeCounterType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_PromiscuousModeCounter[1];  /* PRQA S 0777 */  /* MD_MSR_5.1_777 */
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
extern VAR(Eth_30_Tc3xx_RxBufferUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxBuffer;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_RxDescrUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescr;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_RxDescrRingProcUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrRingProc;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_RxDescrStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxDescrState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_RxTsContextStackUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStack;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_RxTsContextStackPosUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_RxTsContextStackPos;  /* PRQA S 0777, 0759 */  /* MD_MSR_5.1_777, MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TimeHandlingUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TimeHandling;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxBufferUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBuffer;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxBufferFreeElemNumUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferFreeElemNum;  /* PRQA S 0777, 0759 */  /* MD_MSR_5.1_777, MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxBufferStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxBufferState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxDescrUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescr;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxDescrRingProcUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrRingProc;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxDescrStateUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxDescrState;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern VAR(Eth_30_Tc3xx_TxTsContextUType, ETH_30_TC3XX_VAR_NOINIT) Eth_30_Tc3xx_TxTsContext;  /* PRQA S 0759 */  /* MD_CSL_18.4 */
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
extern CONST(Eth_30_Tc3xx_PCConfigsType, ETH_30_TC3XX_CONST) Eth_30_Tc3xx_PCConfig;
#define ETH_30_TC3XX_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_19.1 */
/*lint -restore */



#endif  /* ETH_30_TC3XX_GENTYPES_H */
/**********************************************************************************************************************
 *  END OF FILE: Eth_30_Tc3xx_GenTypes.h
 *********************************************************************************************************************/
