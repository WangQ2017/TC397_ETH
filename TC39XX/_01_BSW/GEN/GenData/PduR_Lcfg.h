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
 *              File: PduR_Lcfg.h
 *   Generation Time: 2025-12-14 17:03:55
 *           Project: TC397_BSW - Version 1.0
 *          Delivery: CBD2000642_D01
 *      Tool Version: DaVinci Configurator  5.22.45 SP3
 *
 *
 *********************************************************************************************************************/


#if !defined (PDUR_LCFG_H)
# define PDUR_LCFG_H

/**********************************************************************************************************************
 * MISRA JUSTIFICATION
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
# include "PduR_Types.h"
# include "PduR_Cfg.h"
# include "Os.h"
# include "PduR_PBcfg.h"

/* include headers with symbolic name values */
/* \trace SPEC-2020167 */

#include "Com_Cbk.h"
#include "UdpNm.h"


/**********************************************************************************************************************
 * GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCDataSwitches  PduR Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define PDUR_APPLICATIONID2DESTAPPLICATIONMANAGERROM                                                STD_OFF  /**< Deactivateable: 'PduR_ApplicationId2DestApplicationManagerRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_DESTAPPLICATIONMANAGERROMIDXOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                  STD_OFF  /**< Deactivateable: 'PduR_ApplicationId2DestApplicationManagerRom.DestApplicationManagerRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_DESTAPPLICATIONMANAGERROMUSEDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                 STD_OFF  /**< Deactivateable: 'PduR_ApplicationId2DestApplicationManagerRom.DestApplicationManagerRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INVALIDHNDOFAPPLICATIONID2DESTAPPLICATIONMANAGERROM                                    STD_OFF  /**< Deactivateable: 'PduR_ApplicationId2DestApplicationManagerRom.InvalidHnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' and Deactivateable: 'PduR_ApplicationId2DestApplicationManagerRom.InvalidHnd' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERARRAYRAM                                                                     STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferArrayRam' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROM                                                                       STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferIndRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINDROM                                                     STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferIndRom.BmTxBufferRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCERAM                                                                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMREADIDXOFBMTXBUFFERINSTANCERAM                                       STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRam.BmTxBufferArrayRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERINSTANCEROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERROMIDXOFBMTXBUFFERINSTANCEROM                                                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferInstanceRom.BmTxBufferRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERRAM                                                                          STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ALLOCATEDOFBMTXBUFFERRAM                                                               STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.Allocated' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERARRAYRAMWRITEIDXOFBMTXBUFFERRAM                                              STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.BmTxBufferArrayRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RXLENGTHOFBMTXBUFFERRAM                                                                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRam.RxLength' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERROM                                                                          STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERARRAYRAMENDIDXOFBMTXBUFFERROM                                                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERARRAYRAMLENGTHOFBMTXBUFFERROM                                                STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERARRAYRAMSTARTIDXOFBMTXBUFFERROM                                              STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferArrayRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCEROMENDIDXOFBMTXBUFFERROM                                             STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferInstanceRomEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINSTANCEROMSTARTIDXOFBMTXBUFFERROM                                           STD_OFF  /**< Deactivateable: 'PduR_BmTxBufferRom.BmTxBufferInstanceRomStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_CONFIGID                                                                               STD_ON
#define PDUR_DEFERREDEVENTCACHEARRAYRAM                                                             STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheArrayRam' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_RMGDESTROMIDXOFDEFERREDEVENTCACHEARRAYRAM                                              STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheArrayRam.RmGDestRomIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHERAM                                                                  STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRam' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEARRAYRAMREADIDXOFDEFERREDEVENTCACHERAM                               STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRam.DeferredEventCacheArrayRamReadIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEARRAYRAMWRITEIDXOFDEFERREDEVENTCACHERAM                              STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRam.DeferredEventCacheArrayRamWriteIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRom' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEARRAYRAMENDIDXOFDEFERREDEVENTCACHEROM                                STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRom.DeferredEventCacheArrayRamEndIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEARRAYRAMLENGTHOFDEFERREDEVENTCACHEROM                                STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRom.DeferredEventCacheArrayRamLength' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEARRAYRAMSTARTIDXOFDEFERREDEVENTCACHEROM                              STD_OFF  /**< Deactivateable: 'PduR_DeferredEventCacheRom.DeferredEventCacheArrayRamStartIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DESTAPPLICATIONMANAGERROM                                                              STD_ON
#define PDUR_MMROMINDENDIDXOFDESTAPPLICATIONMANAGERROM                                              STD_ON
#define PDUR_MMROMINDSTARTIDXOFDESTAPPLICATIONMANAGERROM                                            STD_ON
#define PDUR_MMROMINDUSEDOFDESTAPPLICATIONMANAGERROM                                                STD_ON
#define PDUR_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                                     STD_ON
#define PDUR_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                                   STD_ON
#define PDUR_EXCLUSIVEAREAROM                                                                       STD_ON
#define PDUR_LOCKOFEXCLUSIVEAREAROM                                                                 STD_ON
#define PDUR_UNLOCKOFEXCLUSIVEAREAROM                                                               STD_ON
#define PDUR_FINALMAGICNUMBER                                                                       STD_OFF  /**< Deactivateable: 'PduR_FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_FMFIFOELEMENTRAM                                                                       STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERROMIDXOFFMFIFOELEMENTRAM                                                     STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.BmTxBufferRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTROMIDXOFFMFIFOELEMENTRAM                                                         STD_OFF  /**< Deactivateable: 'PduR_FmFifoElementRam.RmDestRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOINSTANCERAM                                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_BMTXBUFFERINSTANCEROMIDXOFFMFIFOINSTANCERAM                                            STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRam.BmTxBufferInstanceRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOINSTANCEROM                                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FMFIFOROMIDXOFFMFIFOINSTANCEROM                                                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoInstanceRom.FmFifoRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFORAM                                                                              STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FILLLEVELOFFMFIFORAM                                                                   STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FillLevel' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOELEMENTRAMREADIDXOFFMFIFORAM                                                     STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FmFifoElementRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOELEMENTRAMWRITEIDXOFFMFIFORAM                                                    STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.FmFifoElementRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_PENDINGCONFIRMATIONSOFFMFIFORAM                                                        STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.PendingConfirmations' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TPTXSMSTATEOFFMFIFORAM                                                                 STD_OFF  /**< Deactivateable: 'PduR_FmFifoRam.TpTxSmState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FMFIFOROM                                                                              STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_BMTXBUFFERINDROMENDIDXOFFMFIFOROM                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.BmTxBufferIndRomEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROMLENGTHOFFMFIFOROM                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.BmTxBufferIndRomLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_BMTXBUFFERINDROMSTARTIDXOFFMFIFOROM                                                    STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.BmTxBufferIndRomStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFOELEMENTRAMENDIDXOFFMFIFOROM                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFOELEMENTRAMLENGTHOFFMFIFOROM                                                      STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_FMFIFOELEMENTRAMSTARTIDXOFFMFIFOROM                                                    STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.FmFifoElementRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_LOCKROMIDXOFFMFIFOROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.LockRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_LOCKROMUSEDOFFMFIFOROM                                                                 STD_OFF  /**< Deactivateable: 'PduR_FmFifoRom.LockRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_GENERALPROPERTIESROM                                                                   STD_ON
#define PDUR_SPINLOCKRETRYCOUNTEROFGENERALPROPERTIESROM                                             STD_OFF  /**< Deactivateable: 'PduR_GeneralPropertiesRom.SpinlockRetryCounter' Reason: 'No Spinlocks used.' */
#define PDUR_HASIFROUTINGOFGENERALPROPERTIESROM                                                     STD_ON
#define PDUR_HASIFTXFIFOOFGENERALPROPERTIESROM                                                      STD_OFF  /**< Deactivateable: 'PduR_GeneralPropertiesRom.hasIfTxFifo' Reason: 'the value of PduR_hasIfTxFifoOfGeneralPropertiesRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_HASTPTXBUFFEREDFORWARDINGOFGENERALPROPERTIESROM                                        STD_OFF  /**< Deactivateable: 'PduR_GeneralPropertiesRom.hasTpTxBufferedForwarding' Reason: 'No Transport Protocol BswModule active.' */
#define PDUR_INITDATAHASHCODE                                                                       STD_OFF  /**< Deactivateable: 'PduR_InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_INITIALIZED                                                                            STD_ON
#define PDUR_INTERFACEFIFOQUEUEARRAYRAM                                                             STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueArrayRam' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAM                                                           STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueElementRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ACTUALLENGTHOFINTERFACEFIFOQUEUEELEMENTRAM                                             STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueElementRam.ActualLength' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_INTERFACEFIFOQUEUERAM                                                                  STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_FIFOFULLOFINTERFACEFIFOQUEUERAM                                                        STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRam.FifoFull' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMREADIDXOFINTERFACEFIFOQUEUERAM                             STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRam.InterfaceFifoQueueElementRamReadIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMWRITEIDXOFINTERFACEFIFOQUEUERAM                            STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRam.InterfaceFifoQueueElementRamWriteIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_INTERFACEFIFOQUEUEROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_INTERFACEFIFOQUEUEARRAYRAMENDIDXOFINTERFACEFIFOQUEUEROM                                STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.InterfaceFifoQueueArrayRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEARRAYRAMSTARTIDXOFINTERFACEFIFOQUEUEROM                              STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.InterfaceFifoQueueArrayRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMENDIDXOFINTERFACEFIFOQUEUEROM                              STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.InterfaceFifoQueueElementRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEELEMENTRAMSTARTIDXOFINTERFACEFIFOQUEUEROM                            STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.InterfaceFifoQueueElementRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_MAXPDULENGTHOFINTERFACEFIFOQUEUEROM                                                    STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.MaxPduLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMIDXOFINTERFACEFIFOQUEUEROM                                                    STD_OFF  /**< Deactivateable: 'PduR_InterfaceFifoQueueRom.RmDestRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_LOCKROM                                                                                STD_ON
#define PDUR_EXCLUSIVEAREAROMIDXOFLOCKROM                                                           STD_ON
#define PDUR_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                          STD_ON
#define PDUR_SPINLOCKRAMIDXOFLOCKROM                                                                STD_OFF  /**< Deactivateable: 'PduR_LockRom.SpinlockRamIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_SPINLOCKRAMUSEDOFLOCKROM                                                               STD_OFF  /**< Deactivateable: 'PduR_LockRom.SpinlockRamUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAM                                                                      STD_OFF  /**< Deactivateable: 'PduR_McQBufferArrayRam' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERRAM                                                                           STD_OFF  /**< Deactivateable: 'PduR_McQBufferRam' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMPENDINGREADIDXOFMCQBUFFERRAM                                          STD_OFF  /**< Deactivateable: 'PduR_McQBufferRam.McQBufferArrayRamPendingReadIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMPENDINGWRITEIDXOFMCQBUFFERRAM                                         STD_OFF  /**< Deactivateable: 'PduR_McQBufferRam.McQBufferArrayRamPendingWriteIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMREADIDXOFMCQBUFFERRAM                                                 STD_OFF  /**< Deactivateable: 'PduR_McQBufferRam.McQBufferArrayRamReadIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMWRITEIDXOFMCQBUFFERRAM                                                STD_OFF  /**< Deactivateable: 'PduR_McQBufferRam.McQBufferArrayRamWriteIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERROM                                                                           STD_OFF  /**< Deactivateable: 'PduR_McQBufferRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMENDIDXOFMCQBUFFERROM                                                  STD_OFF  /**< Deactivateable: 'PduR_McQBufferRom.McQBufferArrayRamEndIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMLENGTHOFMCQBUFFERROM                                                  STD_OFF  /**< Deactivateable: 'PduR_McQBufferRom.McQBufferArrayRamLength' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERARRAYRAMSTARTIDXOFMCQBUFFERROM                                                STD_OFF  /**< Deactivateable: 'PduR_McQBufferRom.McQBufferArrayRamStartIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MMROM                                                                                  STD_ON
#define PDUR_CANCELRECEIVESUPPORTEDOFMMROM                                                          STD_OFF  /**< Deactivateable: 'PduR_MmRom.CancelReceiveSupported' Reason: 'the value of PduR_CancelReceiveSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM                                                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.ChangeParameterSupported' Reason: 'the value of PduR_ChangeParameterSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_DESTAPPLICATIONMANAGERROMIDXOFMMROM                                                    STD_ON
#define PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM                                                       STD_OFF  /**< Deactivateable: 'PduR_MmRom.IfCancelTransmitSupported' Reason: 'the value of PduR_IfCancelTransmitSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_LOIFCANCELTRANSMITFCTPTROFMMROM                                                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoIfCancelTransmitFctPtr' Reason: 'the value of PduR_LoIfCancelTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOIFOFMMROM                                                                            STD_ON
#define PDUR_LOIFTRANSMITFCTPTROFMMROM                                                              STD_ON
#define PDUR_LOTPCANCELRECEIVEFCTPTROFMMROM                                                         STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpCancelReceiveFctPtr' Reason: 'the value of PduR_LoTpCancelReceiveFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPCANCELTRANSMITFCTPTROFMMROM                                                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpCancelTransmitFctPtr' Reason: 'the value of PduR_LoTpCancelTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPCHANGEPARAMETERFCTPTROFMMROM                                                       STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpChangeParameterFctPtr' Reason: 'the value of PduR_LoTpChangeParameterFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_LOTPOFMMROM                                                                            STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTp' Reason: 'the value of PduR_LoTpOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_LOTPTRANSMITFCTPTROFMMROM                                                              STD_OFF  /**< Deactivateable: 'PduR_MmRom.LoTpTransmitFctPtr' Reason: 'the value of PduR_LoTpTransmitFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_MASKEDBITSOFMMROM                                                                      STD_ON
#define PDUR_RMGDESTROMENDIDXOFMMROM                                                                STD_ON
#define PDUR_RMGDESTROMSTARTIDXOFMMROM                                                              STD_ON
#define PDUR_RMGDESTROMUSEDOFMMROM                                                                  STD_ON
#define PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM                                                       STD_OFF  /**< Deactivateable: 'PduR_MmRom.TpCancelTransmitSupported' Reason: 'the value of PduR_TpCancelTransmitSupportedOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_UPIFOFMMROM                                                                            STD_ON
#define PDUR_UPIFRXINDICATIONFCTPTROFMMROM                                                          STD_ON
#define PDUR_UPIFTRIGGERTRANSMITFCTPTROFMMROM                                                       STD_ON
#define PDUR_UPIFTXCONFIRMATIONFCTPTROFMMROM                                                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpIfTxConfirmationFctPtr' Reason: 'the value of PduR_UpIfTxConfirmationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPCOPYRXDATAFCTPTROFMMROM                                                            STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpCopyRxDataFctPtr' Reason: 'the value of PduR_UpTpCopyRxDataFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPCOPYTXDATAFCTPTROFMMROM                                                            STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpCopyTxDataFctPtr' Reason: 'the value of PduR_UpTpCopyTxDataFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPOFMMROM                                                                            STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTp' Reason: 'the value of PduR_UpTpOfMmRom is always 'false' due to this, the array is deactivated.' */
#define PDUR_UPTPSTARTOFRECEPTIONFCTPTROFMMROM                                                      STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpStartOfReceptionFctPtr' Reason: 'the value of PduR_UpTpStartOfReceptionFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPTPRXINDICATIONFCTPTROFMMROM                                                        STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpTpRxIndicationFctPtr' Reason: 'the value of PduR_UpTpTpRxIndicationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_UPTPTPTXCONFIRMATIONFCTPTROFMMROM                                                      STD_OFF  /**< Deactivateable: 'PduR_MmRom.UpTpTpTxConfirmationFctPtr' Reason: 'the value of PduR_UpTpTpTxConfirmationFctPtrOfMmRom is always 'NULL_PTR' due to this, the array is deactivated.' */
#define PDUR_MMROMIND                                                                               STD_ON
#define PDUR_PARTITIONIDENTIFIERS                                                                   STD_ON
#define PDUR_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                             STD_ON
#define PDUR_PARTITIONSNVOFPARTITIONIDENTIFIERS                                                     STD_ON
#define PDUR_PARTITIONLOOKUPTABLERAM                                                                STD_OFF  /**< Deactivateable: 'PduR_PartitionLookupTableRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_OSAPPLICATIONTOPDUROFPARTITIONLOOKUPTABLERAM                                           STD_OFF  /**< Deactivateable: 'PduR_PartitionLookupTableRam.OsApplicationToPduR' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_QUEUEFCTPTRROM                                                                         STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_FLUSHFCTPTROFQUEUEFCTPTRROM                                                            STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom.FlushFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_GETFCTPTROFQUEUEFCTPTRROM                                                              STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom.GetFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_GETFILLLEVELFCTPTROFQUEUEFCTPTRROM                                                     STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom.GetFillLevelFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_PUTFCTPTROFQUEUEFCTPTRROM                                                              STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom.PutFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_REMOVEFCTPTROFQUEUEFCTPTRROM                                                           STD_OFF  /**< Deactivateable: 'PduR_QueueFctPtrRom.RemoveFctPtr' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMBUFFEREDIFPROPERTIESRAM                                                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_IFSMSTATEOFRMBUFFEREDIFPROPERTIESRAM                                                   STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRam.IfSmState' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMBUFFEREDIFPROPERTIESROM                                                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM                                          STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.ImplementationType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEROMIDXOFRMBUFFEREDIFPROPERTIESROM                                    STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.InterfaceFifoQueueRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_INTERFACEFIFOQUEUEROMUSEDOFRMBUFFEREDIFPROPERTIESROM                                   STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.InterfaceFifoQueueRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM                                      STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueDataProvisionType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_QUEUEFCTPTRROMIDXOFRMBUFFEREDIFPROPERTIESROM                                           STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueFctPtrRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                                   STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERROMIDXOFRMBUFFEREDIFPROPERTIESROM                                          STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.SingleBufferRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERROMUSEDOFRMBUFFEREDIFPROPERTIESROM                                         STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.SingleBufferRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMBUFFEREDTPPROPERTIESRAM                                                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_FMFIFOELEMENTRAMIDXOFRMBUFFEREDTPPROPERTIESRAM                                         STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam.FmFifoElementRamIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPRXSMSTATEOFRMBUFFEREDTPPROPERTIESRAM                                                 STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRam.TpRxSmState' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMBUFFEREDTPPROPERTIESROM                                                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_FMFIFOROMIDXOFRMBUFFEREDTPPROPERTIESROM                                                STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.FmFifoRomIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_METADATALENGTHOFRMBUFFEREDTPPROPERTIESROM                                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.MetaDataLength' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_METADATALENGTHUSEDOFRMBUFFEREDTPPROPERTIESROM                                          STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.MetaDataLengthUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_QUEUEDDESTCNTOFRMBUFFEREDTPPROPERTIESROM                                               STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.QueuedDestCnt' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPTHRESHOLDOFRMBUFFEREDTPPROPERTIESROM                                                 STD_OFF  /**< Deactivateable: 'PduR_RmBufferedTpPropertiesRom.TpThreshold' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMDESTROM                                                                              STD_ON
#define PDUR_BSWMPDURPRETRANSMITCALLBACKOFRMDESTROM                                                 STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.BswMPduRPreTransmitCallback' Reason: 'Callback Support is not active' */
#define PDUR_PARTITIONINDEXOFCSLOFRMDESTROM                                                         STD_ON
#define PDUR_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                                   STD_ON
#define PDUR_RMDESTRPGROMIDXOFRMDESTROM                                                             STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.RmDestRpgRomIdx' Reason: 'the optional indirection is deactivated because RmDestRpgRomUsedOfRmDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMDESTRPGROMUSEDOFRMDESTROM                                                            STD_OFF  /**< Deactivateable: 'PduR_RmDestRom.RmDestRpgRomUsed' Reason: 'the optional indirection is deactivated because RmDestRpgRomUsedOfRmDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTROMIDXOFRMDESTROM                                                               STD_ON
#define PDUR_RMSRCROMIDXOFRMDESTROM                                                                 STD_ON
#define PDUR_ROUTINGTYPEOFRMDESTROM                                                                 STD_ON
#define PDUR_RMDESTRPGRAM                                                                           STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ENABLEDCNTOFRMDESTRPGRAM                                                               STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRam.EnabledCnt' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTRPGROM                                                                           STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_INITIALENABLEDCNTOFRMDESTRPGROM                                                        STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.InitialEnabledCnt' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMIDXOFRMDESTRPGROM                                                             STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTROMUSEDOFRMDESTRPGROM                                                            STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRom.RmDestRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMIND                                                                        STD_OFF  /**< Deactivateable: 'PduR_RmDestRpgRomInd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMGDESTNTO1INFORAM                                                                     STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMDESTROMIDXOFRMGDESTNTO1INFORAM                                                       STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam.RmDestRomIdx' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_TRANSMISSIONACTIVEOFRMGDESTNTO1INFORAM                                                 STD_OFF  /**< Deactivateable: 'PduR_RmGDestNto1InfoRam.TransmissionActive' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RMGDESTROM                                                                             STD_ON
#define PDUR_DESTHNDOFRMGDESTROM                                                                    STD_ON
#define PDUR_DIRECTIONOFRMGDESTROM                                                                  STD_ON
#define PDUR_FMFIFOINSTANCEROMIDXOFRMGDESTROM                                                       STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.FmFifoInstanceRomIdx' Reason: 'the optional indirection is deactivated because FmFifoInstanceRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_FMFIFOINSTANCEROMUSEDOFRMGDESTROM                                                      STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.FmFifoInstanceRomUsed' Reason: 'the optional indirection is deactivated because FmFifoInstanceRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_LOCKROMIDXOFRMGDESTROM                                                                 STD_ON
#define PDUR_MAXPDULENGTHOFRMGDESTROM                                                               STD_ON
#define PDUR_MMROMIDXOFRMGDESTROM                                                                   STD_ON
#define PDUR_PARTITIONINDEXOFCSLOFRMGDESTROM                                                        STD_ON
#define PDUR_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                      STD_ON
#define PDUR_RMBUFFEREDIFPROPERTIESROMIDXOFRMGDESTROM                                               STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmBufferedIfPropertiesRomIdx' Reason: 'the optional indirection is deactivated because RmBufferedIfPropertiesRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMBUFFEREDIFPROPERTIESROMUSEDOFRMGDESTROM                                              STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmBufferedIfPropertiesRomUsed' Reason: 'the optional indirection is deactivated because RmBufferedIfPropertiesRomUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMDESTROMIDXOFRMGDESTROM                                                               STD_ON
#define PDUR_RMGDESTNTO1INFORAMIDXOFRMGDESTROM                                                      STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestNto1InfoRamIdx' Reason: 'the optional indirection is deactivated because RmGDestNto1InfoRamUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTNTO1INFORAMUSEDOFRMGDESTROM                                                     STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestNto1InfoRamUsed' Reason: 'the optional indirection is deactivated because RmGDestNto1InfoRamUsedOfRmGDestRom is always 'FALSE' and the target of the indirection is of the Configuration Class 'PRE_COMPILE'.' */
#define PDUR_RMGDESTTPTXSTATERAMIDXOFRMGDESTROM                                                     STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestTpTxStateRamIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMGDESTTPTXSTATERAMUSEDOFRMGDESTROM                                                    STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.RmGDestTpTxStateRamUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_SMGDESTROMIDXOFRMGDESTROM                                                              STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.SmGDestRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTROMUSEDOFRMGDESTROM                                                             STD_OFF  /**< Deactivateable: 'PduR_RmGDestRom.SmGDestRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_TXIF2UPIDXOFRMGDESTROM                                                                 STD_ON
#define PDUR_RMGDESTTPTXSTATERAM                                                                    STD_OFF  /**< Deactivateable: 'PduR_RmGDestTpTxStateRam' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_TPTXINSTSMSTATEOFRMGDESTTPTXSTATERAM                                                   STD_OFF  /**< Deactivateable: 'PduR_RmGDestTpTxStateRam.TpTxInstSmState' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMSRCROM                                                                               STD_ON
#define PDUR_LOCKROMIDXOFRMSRCROM                                                                   STD_ON
#define PDUR_MMROMIDXOFRMSRCROM                                                                     STD_ON
#define PDUR_PARTITIONINDEXOFCSLOFRMSRCROM                                                          STD_ON
#define PDUR_RMBUFFEREDTPPROPERTIESROMIDXOFRMSRCROM                                                 STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.RmBufferedTpPropertiesRomIdx' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMBUFFEREDTPPROPERTIESROMUSEDOFRMSRCROM                                                STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.RmBufferedTpPropertiesRomUsed' Reason: 'No TransportProtocol BswModule active.' */
#define PDUR_RMDESTROMENDIDXOFRMSRCROM                                                              STD_ON
#define PDUR_RMDESTROMLENGTHOFRMSRCROM                                                              STD_ON
#define PDUR_RMDESTROMSTARTIDXOFRMSRCROM                                                            STD_ON
#define PDUR_SMSRCROMIDXOFRMSRCROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.SmSrcRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCROMUSEDOFRMSRCROM                                                                 STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.SmSrcRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SRCHNDOFRMSRCROM                                                                       STD_ON
#define PDUR_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                                     STD_ON
#define PDUR_TXCONFIRMATIONSUPPORTEDOFRMSRCROM                                                      STD_OFF  /**< Deactivateable: 'PduR_RmSrcRom.TxConfirmationSupported' Reason: 'No BswModule with TxConfirmation active.' */
#define PDUR_RMTRANSMITFCTPTR                                                                       STD_ON
#define PDUR_RPGEXTIDROM                                                                            STD_OFF  /**< Deactivateable: 'PduR_RpgExtIdRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_INVALIDHNDOFRPGEXTIDROM                                                                STD_OFF  /**< Deactivateable: 'PduR_RpgExtIdRom.InvalidHnd' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' and Deactivateable: 'PduR_RpgExtIdRom.InvalidHnd' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_PARTITIONINDEXOFCSLOFRPGEXTIDROM                                                       STD_OFF  /**< Deactivateable: 'PduR_RpgExtIdRom.PartitionIndexOfCsl' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RPGROMIDXOFRPGEXTIDROM                                                                 STD_OFF  /**< Deactivateable: 'PduR_RpgExtIdRom.RpgRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RPGROMUSEDOFRPGEXTIDROM                                                                STD_OFF  /**< Deactivateable: 'PduR_RpgExtIdRom.RpgRomUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RPGRAM                                                                                 STD_OFF  /**< Deactivateable: 'PduR_RpgRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ENABLEDOFRPGRAM                                                                        STD_OFF  /**< Deactivateable: 'PduR_RpgRam.Enabled' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_RPGROM                                                                                 STD_OFF  /**< Deactivateable: 'PduR_RpgRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_ENABLEDATINITOFRPGROM                                                                  STD_OFF  /**< Deactivateable: 'PduR_RpgRom.EnabledAtInit' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDENDIDXOFRPGROM                                                          STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDSTARTIDXOFRPGROM                                                        STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RMDESTRPGROMINDUSEDOFRPGROM                                                            STD_OFF  /**< Deactivateable: 'PduR_RpgRom.RmDestRpgRomIndUsed' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_RXIF2DEST                                                                              STD_ON
#define PDUR_BSWMPDURRXINDICATIONCALLBACKOFRXIF2DEST                                                STD_OFF  /**< Deactivateable: 'PduR_RxIf2Dest.BswMPduRRxIndicationCallback' Reason: 'Callback Support is not active' */
#define PDUR_INVALIDHNDOFRXIF2DEST                                                                  STD_OFF  /**< Deactivateable: 'PduR_RxIf2Dest.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfRxIf2Dest is always 'false' due to this, the array is deactivated.' and Deactivateable: 'PduR_RxIf2Dest.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfRxIf2Dest is always 'false' due to this, the array is deactivated.' */
#define PDUR_PARTITIONINDEXOFCSLOFRXIF2DEST                                                         STD_ON
#define PDUR_RMSRCROMIDXOFRXIF2DEST                                                                 STD_ON
#define PDUR_RXTP2DEST                                                                              STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPRXINDICATIONCALLBACKOFRXTP2DEST                                              STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.BswMPduRTpRxIndicationCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPSTARTOFRECEPTIONCALLBACKOFRXTP2DEST                                          STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.BswMPduRTpStartOfReceptionCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_INVALIDHNDOFRXTP2DEST                                                                  STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' and Deactivateable: 'PduR_RxTp2Dest.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_PARTITIONINDEXOFCSLSTRINGSNVOFRXTP2DEST                                                STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.PartitionIndexOfCslStringSNV' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RMSRCROMIDXOFRXTP2DEST                                                                 STD_OFF  /**< Deactivateable: 'PduR_RxTp2Dest.RmSrcRomIdx' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RXTP2SRC                                                                               STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_INVALIDHNDOFRXTP2SRC                                                                   STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src.InvalidHnd' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' and Deactivateable: 'PduR_RxTp2Src.InvalidHnd' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_PARTITIONINDEXOFCSLSTRINGSNVOFRXTP2SRC                                                 STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src.PartitionIndexOfCslStringSNV' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_RMDESTROMIDXOFRXTP2SRC                                                                 STD_OFF  /**< Deactivateable: 'PduR_RxTp2Src.RmDestRomIdx' Reason: '(No PduRBswModule configured which uses the CancelReceive API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelReceive) && (No PduRBswModule configured which uses the ChangeParameter API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRChangeParameterRequestApi)' */
#define PDUR_SINGLEBUFFERARRAYRAM                                                                   STD_OFF  /**< Deactivateable: 'PduR_SingleBufferArrayRam' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERINITVALUESROM                                                              STD_OFF  /**< Deactivateable: 'PduR_SingleBufferInitValuesRom' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERRAM                                                                        STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRam' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_ACTUALLENGTHOFSINGLEBUFFERRAM                                                          STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRam.ActualLength' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
#define PDUR_SINGLEBUFFERROM                                                                        STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom' Reason: 'the struct is deactivated because all elements are deactivated.' */
#define PDUR_RMDESTROMIDXOFSINGLEBUFFERROM                                                          STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.RmDestRomIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERARRAYRAMENDIDXOFSINGLEBUFFERROM                                            STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferArrayRamEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERARRAYRAMLENGTHOFSINGLEBUFFERROM                                            STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferArrayRamLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERARRAYRAMSTARTIDXOFSINGLEBUFFERROM                                          STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferArrayRamStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERINITVALUESROMENDIDXOFSINGLEBUFFERROM                                       STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferInitValuesRomEndIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERINITVALUESROMLENGTHOFSINGLEBUFFERROM                                       STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferInitValuesRomLength' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SINGLEBUFFERINITVALUESROMSTARTIDXOFSINGLEBUFFERROM                                     STD_OFF  /**< Deactivateable: 'PduR_SingleBufferRom.SingleBufferInitValuesRomStartIdx' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_SIZEOFDESTAPPLICATIONMANAGERROM                                                        STD_ON
#define PDUR_SIZEOFEXCLUSIVEAREAROM                                                                 STD_ON
#define PDUR_SIZEOFGENERALPROPERTIESROM                                                             STD_ON
#define PDUR_SIZEOFLOCKROM                                                                          STD_ON
#define PDUR_SIZEOFMMROM                                                                            STD_ON
#define PDUR_SIZEOFMMROMIND                                                                         STD_ON
#define PDUR_SIZEOFPARTITIONIDENTIFIERS                                                             STD_ON
#define PDUR_SIZEOFRMDESTROM                                                                        STD_ON
#define PDUR_SIZEOFRMGDESTROM                                                                       STD_ON
#define PDUR_SIZEOFRMSRCROM                                                                         STD_ON
#define PDUR_SIZEOFRMTRANSMITFCTPTR                                                                 STD_ON
#define PDUR_SIZEOFRXIF2DEST                                                                        STD_ON
#define PDUR_SIZEOFSRCAPPLICATIONROM                                                                STD_ON
#define PDUR_SIZEOFTX2LO                                                                            STD_ON
#define PDUR_SIZEOFTXIF2UP                                                                          STD_ON
#define PDUR_SMDATAPLANEROM                                                                         STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMENDIDXOFSMDATAPLANEROM                                                         STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamEndIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMSTARTIDXOFSMDATAPLANEROM                                                       STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamStartIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAMUSEDOFSMDATAPLANEROM                                                           STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmFibRamUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROMIDXOFSMDATAPLANEROM                                STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmLinearTaToSaCalculationStrategyRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROMUSEDOFSMDATAPLANEROM                               STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmLinearTaToSaCalculationStrategyRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROMIDXOFSMDATAPLANEROM                            STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmSaTaFromMetaDataCalculationStrategyRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROMUSEDOFSMDATAPLANEROM                           STD_OFF  /**< Deactivateable: 'PduR_SmDataPlaneRom.SmSaTaFromMetaDataCalculationStrategyRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMFIBRAM                                                                               STD_OFF  /**< Deactivateable: 'PduR_SmFibRam' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_LEARNEDCONNECTIONIDOFSMFIBRAM                                                          STD_OFF  /**< Deactivateable: 'PduR_SmFibRam.LearnedConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTFILTERFCTPTR                                                                    STD_OFF  /**< Deactivateable: 'PduR_SmGDestFilterFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTROM                                                                             STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_CONNECTIONIDOFSMGDESTROM                                                               STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.ConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_METADATALENGTHOFSMGDESTROM                                                             STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.MetaDataLength' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMDATAPLANEROMIDXOFSMGDESTROM                                                          STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.SmDataPlaneRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMGDESTFILTERFCTPTRIDXOFSMGDESTROM                                                     STD_OFF  /**< Deactivateable: 'PduR_SmGDestRom.SmGDestFilterFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTR                                           STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyGetSaFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYROM                                                   STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_MASKOFSMLINEARTATOSACALCULATIONSTRATEGYROM                                             STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom.Mask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_OFFSETOFSMLINEARTATOSACALCULATIONSTRATEGYROM                                           STD_OFF  /**< Deactivateable: 'PduR_SmLinearTaToSaCalculationStrategyRom.Offset' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSATAFROMMETADATACALCULATIONSTRATEGYROM                                               STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SAMASKOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM                                       STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.SaMask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SASTARTBITOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM                                   STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.SaStartBit' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_TAMASKOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM                                       STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.TaMask' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_TASTARTBITOFSMSATAFROMMETADATACALCULATIONSTRATEGYROM                                   STD_OFF  /**< Deactivateable: 'PduR_SmSaTaFromMetaDataCalculationStrategyRom.TaStartBit' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCFILTERFCTPTR                                                                      STD_OFF  /**< Deactivateable: 'PduR_SmSrcFilterFctPtr' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCROM                                                                               STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_CONNECTIONIDOFSMSRCROM                                                                 STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.ConnectionId' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_METADATALENGTHOFSMSRCROM                                                               STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.MetaDataLength' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMDATAPLANEROMIDXOFSMSRCROM                                                            STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmDataPlaneRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTRIDXOFSMSRCROM                              STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmLinearTaToSaCalculationStrategyGetSaFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMLINEARTATOSACALCULATIONSTRATEGYGETSAFCTPTRUSEDOFSMSRCROM                             STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmLinearTaToSaCalculationStrategyGetSaFctPtrUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SMSRCFILTERFCTPTRIDXOFSMSRCROM                                                         STD_OFF  /**< Deactivateable: 'PduR_SmSrcRom.SmSrcFilterFctPtrIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSwitching] is configured to 'false'' */
#define PDUR_SPINLOCKRAM                                                                            STD_OFF  /**< Deactivateable: 'PduR_SpinlockRam' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_COUNTEROFSPINLOCKRAM                                                                   STD_OFF  /**< Deactivateable: 'PduR_SpinlockRam.Counter' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_LOCKVARIABLEOFSPINLOCKRAM                                                              STD_OFF  /**< Deactivateable: 'PduR_SpinlockRam.LockVariable' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_SRCAPPLICATIONROM                                                                      STD_ON
#define PDUR_DEFERREDEVENTCACHEROMIDXOFSRCAPPLICATIONROM                                            STD_OFF  /**< Deactivateable: 'PduR_SrcApplicationRom.DeferredEventCacheRomIdx' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_DEFERREDEVENTCACHEROMUSEDOFSRCAPPLICATIONROM                                           STD_OFF  /**< Deactivateable: 'PduR_SrcApplicationRom.DeferredEventCacheRomUsed' Reason: 'No Deferred Event Cache is configured' */
#define PDUR_MCQBUFFERROMIDXOFSRCAPPLICATIONROM                                                     STD_OFF  /**< Deactivateable: 'PduR_SrcApplicationRom.McQBufferRomIdx' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_MCQBUFFERROMUSEDOFSRCAPPLICATIONROM                                                    STD_OFF  /**< Deactivateable: 'PduR_SrcApplicationRom.McQBufferRomUsed' Reason: '/ActiveEcuC/PduR/PduRGeneral[0:PduRSupportMulticore] is configured to 'false'' */
#define PDUR_PARTITIONINDEXOFCSLOFSRCAPPLICATIONROM                                                 STD_ON
#define PDUR_TX2LO                                                                                  STD_ON
#define PDUR_BSWMPDURTRANSMITCALLBACKOFTX2LO                                                        STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.BswMPduRTransmitCallback' Reason: 'Callback Support is not active' */
#define PDUR_CANCELTRANSMITUSEDOFTX2LO                                                              STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.CancelTransmitUsed' Reason: 'No PduRBswModule configured which uses the CancelTransmit API.. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRCancelTransmit' */
#define PDUR_INVALIDHNDOFTX2LO                                                                      STD_OFF  /**< Deactivateable: 'PduR_Tx2Lo.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTx2Lo is always 'false' due to this, the array is deactivated.' and Deactivateable: 'PduR_Tx2Lo.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTx2Lo is always 'false' due to this, the array is deactivated.' */
#define PDUR_PARTITIONINDEXOFCSLOFTX2LO                                                             STD_ON
#define PDUR_RMSRCROMIDXOFTX2LO                                                                     STD_ON
#define PDUR_RMSRCROMUSEDOFTX2LO                                                                    STD_ON
#define PDUR_RMTRANSMITFCTPTRIDXOFTX2LO                                                             STD_ON
#define PDUR_TXIF2UP                                                                                STD_ON
#define PDUR_BSWMPDURTXCONFIRMATIONCALLBACKOFTXIF2UP                                                STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.BswMPduRTxConfirmationCallback' Reason: 'Callback Support is not active' */
#define PDUR_INVALIDHNDOFTXIF2UP                                                                    STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTxIf2Up is always 'false' due to this, the array is deactivated.' and Deactivateable: 'PduR_TxIf2Up.InvalidHnd' Reason: 'the value of PduR_InvalidHndOfTxIf2Up is always 'false' due to this, the array is deactivated.' */
#define PDUR_PARTITIONINDEXOFCSLOFTXIF2UP                                                           STD_ON
#define PDUR_RMGDESTROMIDXOFTXIF2UP                                                                 STD_ON
#define PDUR_TXCONFIRMATIONUSEDOFTXIF2UP                                                            STD_OFF  /**< Deactivateable: 'PduR_TxIf2Up.TxConfirmationUsed' Reason: 'No tx confirmation PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTxConfirmation' */
#define PDUR_TXTP2SRC                                                                               STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_BSWMPDURTPTXCONFIRMATIONCALLBACKOFTXTP2SRC                                             STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.BswMPduRTpTxConfirmationCallback' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_INVALIDHNDOFTXTP2SRC                                                                   STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' and Deactivateable: 'PduR_TxTp2Src.InvalidHnd' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_PARTITIONINDEXOFCSLSTRINGSNVOFTXTP2SRC                                                 STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.PartitionIndexOfCslStringSNV' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_RMGDESTROMIDXOFTXTP2SRC                                                                STD_OFF  /**< Deactivateable: 'PduR_TxTp2Src.RmGDestRomIdx' Reason: 'No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol' */
#define PDUR_PCCONFIG                                                                               STD_ON
#define PDUR_FINALMAGICNUMBEROFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'PduR_PCConfig.FinalMagicNumber' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_INITDATAHASHCODEOFPCCONFIG                                                             STD_OFF  /**< Deactivateable: 'PduR_PCConfig.InitDataHashCode' Reason: 'the module configuration does not support flashing of data.' */
#define PDUR_PCPARTITIONCONFIGOFPCCONFIG                                                            STD_ON
#define PDUR_PARTITIONIDENTIFIERSOFPCCONFIG                                                         STD_ON
#define PDUR_SIZEOFPARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define PDUR_PCPARTITIONCONFIG                                                                      STD_ON
#define PDUR_CONFIGIDOFPCPARTITIONCONFIG                                                            STD_ON
#define PDUR_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                           STD_ON
#define PDUR_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                                STD_ON
#define PDUR_INITIALIZEDOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_LOCKROMOFPCPARTITIONCONFIG                                                             STD_ON
#define PDUR_MMROMINDOFPCPARTITIONCONFIG                                                            STD_ON
#define PDUR_MMROMOFPCPARTITIONCONFIG                                                               STD_ON
#define PDUR_RMDESTROMOFPCPARTITIONCONFIG                                                           STD_ON
#define PDUR_RMGDESTROMOFPCPARTITIONCONFIG                                                          STD_ON
#define PDUR_RMSRCROMOFPCPARTITIONCONFIG                                                            STD_ON
#define PDUR_RMTRANSMITFCTPTROFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_RXIF2DESTOFPCPARTITIONCONFIG                                                           STD_ON
#define PDUR_SIZEOFDESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                     STD_ON
#define PDUR_SIZEOFEXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_SIZEOFGENERALPROPERTIESROMOFPCPARTITIONCONFIG                                          STD_ON
#define PDUR_SIZEOFLOCKROMOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_SIZEOFMMROMINDOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_SIZEOFMMROMOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_SIZEOFRMDESTROMOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_SIZEOFRMGDESTROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_SIZEOFRMSRCROMOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_SIZEOFRMTRANSMITFCTPTROFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_SIZEOFRXIF2DESTOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_SIZEOFSRCAPPLICATIONROMOFPCPARTITIONCONFIG                                             STD_ON
#define PDUR_SIZEOFTX2LOOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_SIZEOFTXIF2UPOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                                   STD_ON
#define PDUR_TX2LOOFPCPARTITIONCONFIG                                                               STD_ON
#define PDUR_TXIF2UPOFPCPARTITIONCONFIG                                                             STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCNoReferenceDefines  PduR No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/ 
#define PDUR_NO_MMROMINDENDIDXOFDESTAPPLICATIONMANAGERROM                                           255u
#define PDUR_NO_MMROMINDSTARTIDXOFDESTAPPLICATIONMANAGERROM                                         255u
#define PDUR_NO_EXCLUSIVEAREAROMIDXOFLOCKROM                                                        255u
#define PDUR_NO_RMGDESTROMENDIDXOFMMROM                                                             255u
#define PDUR_NO_RMGDESTROMSTARTIDXOFMMROM                                                           255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFRMDESTROM                                                      255u
#define PDUR_NO_DESTHNDOFRMGDESTROM                                                                 255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFRMGDESTROM                                                     255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFRMSRCROM                                                       255u
#define PDUR_NO_SRCHNDOFRMSRCROM                                                                    255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFRXIF2DEST                                                      255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFSRCAPPLICATIONROM                                              255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFTX2LO                                                          255u
#define PDUR_NO_RMSRCROMIDXOFTX2LO                                                                  255u
#define PDUR_NO_PARTITIONINDEXOFCSLOFTXIF2UP                                                        255u
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEnumExistsDefines  PduR Enum Exists Defines (PRE_COMPILE)
  \brief  These defines can be used to deactivate enumeration based code sequences if the enumeration value does not exist in the configuration data.
  \{
*/ 
#define PDUR_EXISTS_SINGLE_BUFFER_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM               STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.ImplementationType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_SIMPLE_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM                 STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.ImplementationType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_SHARED_FIFO_QUEUE_IMPLEMENTATIONTYPEOFRMBUFFEREDIFPROPERTIESROM                 STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.ImplementationType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_DIRECT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM                        STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueDataProvisionType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_TRIGGER_TRANSMIT_QUEUEDATAPROVISIONTYPEOFRMBUFFEREDIFPROPERTIESROM              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueDataProvisionType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_SINGLE_BUFFER_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                              STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_FIFO_QUEUETYPEOFRMBUFFEREDIFPROPERTIESROM                                       STD_OFF  /**< Deactivateable: 'PduR_RmBufferedIfPropertiesRom.QueueType' Reason: 'the array is deactivated because the size is 0 and the piece of data is in the configuration class: PRE_COMPILE' */
#define PDUR_EXISTS_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                    STD_OFF
#define PDUR_EXISTS_DISCARD_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                    STD_OFF
#define PDUR_EXISTS_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                     STD_ON
#define PDUR_EXISTS_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                     STD_OFF
#define PDUR_EXISTS_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 STD_ON
#define PDUR_EXISTS_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 STD_ON
#define PDUR_EXISTS_IF_NOBUFFER_GATEWAY_ROUTINGTYPEOFRMDESTROM                                      STD_OFF
#define PDUR_EXISTS_IF_BUFFERED_ROUTINGTYPEOFRMDESTROM                                              STD_OFF
#define PDUR_EXISTS_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 STD_OFF  /**< No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol */
#define PDUR_EXISTS_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                 STD_OFF  /**< No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol */
#define PDUR_EXISTS_TP_BUFFERED_ROUTINGTYPEOFRMDESTROM                                              STD_OFF  /**< No transport protocol PduRBswModule configured. Evaluated DefinitionRef: /MICROSAR/PduR/PduRBswModules/PduRTransportProtocol */
#define PDUR_EXISTS_RX_DIRECTIONOFRMGDESTROM                                                        STD_ON
#define PDUR_EXISTS_TX_DIRECTIONOFRMGDESTROM                                                        STD_ON
#define PDUR_EXISTS_DEFERRED_PDURDESTPDUPROCESSINGOFRMGDESTROM                                      STD_OFF  /**< /ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredReception] and /ActiveEcuC/PduR/PduRGeneral[0:PduREnableDeferredTransmission] are both disabled. */
#define PDUR_EXISTS_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM                                     STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEnumDefines  PduR Enum Defines (PRE_COMPILE)
  \brief  These defines are the enumeration values of enumeration based CONST and VAR data.
  \{
*/ 
#define PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                            0x02u
#define PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x00u
#define PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM                                        0x01u
#define PDUR_RX_DIRECTIONOFRMGDESTROM                                                               0x00u
#define PDUR_TX_DIRECTIONOFRMGDESTROM                                                               0x01u
#define PDUR_IMMEDIATE_PDURDESTPDUPROCESSINGOFRMGDESTROM                                            0x01u
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCMaskedBitDefines  PduR Masked Bit Defines (PRE_COMPILE)
  \brief  These defines are masks to extract packed boolean data.
  \{
*/ 
#define PDUR_LOIFOFMMROM_MASK                                                                       0x04u
#define PDUR_RMGDESTROMUSEDOFMMROM_MASK                                                             0x02u
#define PDUR_UPIFOFMMROM_MASK                                                                       0x01u
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCIsReducedToDefineDefines  PduR Is Reduced To Define Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define is STD_ON else STD_OFF.
  \{
*/ 
#define PDUR_ISDEF_MMROMINDENDIDXOFDESTAPPLICATIONMANAGERROM                                        STD_OFF
#define PDUR_ISDEF_MMROMINDSTARTIDXOFDESTAPPLICATIONMANAGERROM                                      STD_OFF
#define PDUR_ISDEF_MMROMINDUSEDOFDESTAPPLICATIONMANAGERROM                                          STD_OFF
#define PDUR_ISDEF_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                               STD_OFF
#define PDUR_ISDEF_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                             STD_OFF
#define PDUR_ISDEF_LOCKOFEXCLUSIVEAREAROM                                                           STD_OFF
#define PDUR_ISDEF_UNLOCKOFEXCLUSIVEAREAROM                                                         STD_OFF
#define PDUR_ISDEF_HASIFROUTINGOFGENERALPROPERTIESROM                                               STD_OFF
#define PDUR_ISDEF_EXCLUSIVEAREAROMIDXOFLOCKROM                                                     STD_OFF
#define PDUR_ISDEF_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                    STD_OFF
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMIDXOFMMROM                                              STD_OFF
#define PDUR_ISDEF_LOIFOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_LOIFTRANSMITFCTPTROFMMROM                                                        STD_OFF
#define PDUR_ISDEF_MASKEDBITSOFMMROM                                                                STD_OFF
#define PDUR_ISDEF_RMGDESTROMENDIDXOFMMROM                                                          STD_OFF
#define PDUR_ISDEF_RMGDESTROMSTARTIDXOFMMROM                                                        STD_OFF
#define PDUR_ISDEF_RMGDESTROMUSEDOFMMROM                                                            STD_OFF
#define PDUR_ISDEF_UPIFOFMMROM                                                                      STD_OFF
#define PDUR_ISDEF_UPIFRXINDICATIONFCTPTROFMMROM                                                    STD_OFF
#define PDUR_ISDEF_UPIFTRIGGERTRANSMITFCTPTROFMMROM                                                 STD_OFF
#define PDUR_ISDEF_MMROMIND                                                                         STD_OFF
#define PDUR_ISDEF_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                       STD_OFF
#define PDUR_ISDEF_PARTITIONSNVOFPARTITIONIDENTIFIERS                                               STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFRMDESTROM                                                   STD_OFF
#define PDUR_ISDEF_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                             STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFRMDESTROM                                                         STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRMDESTROM                                                           STD_OFF
#define PDUR_ISDEF_ROUTINGTYPEOFRMDESTROM                                                           STD_OFF
#define PDUR_ISDEF_DESTHNDOFRMGDESTROM                                                              STD_OFF
#define PDUR_ISDEF_DIRECTIONOFRMGDESTROM                                                            STD_OFF
#define PDUR_ISDEF_LOCKROMIDXOFRMGDESTROM                                                           STD_OFF
#define PDUR_ISDEF_MAXPDULENGTHOFRMGDESTROM                                                         STD_OFF
#define PDUR_ISDEF_MMROMIDXOFRMGDESTROM                                                             STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFRMGDESTROM                                                  STD_OFF
#define PDUR_ISDEF_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                STD_OFF
#define PDUR_ISDEF_RMDESTROMIDXOFRMGDESTROM                                                         STD_OFF
#define PDUR_ISDEF_TXIF2UPIDXOFRMGDESTROM                                                           STD_OFF
#define PDUR_ISDEF_LOCKROMIDXOFRMSRCROM                                                             STD_OFF
#define PDUR_ISDEF_MMROMIDXOFRMSRCROM                                                               STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFRMSRCROM                                                    STD_OFF
#define PDUR_ISDEF_RMDESTROMENDIDXOFRMSRCROM                                                        STD_OFF
#define PDUR_ISDEF_RMDESTROMLENGTHOFRMSRCROM                                                        STD_OFF
#define PDUR_ISDEF_RMDESTROMSTARTIDXOFRMSRCROM                                                      STD_OFF
#define PDUR_ISDEF_SRCHNDOFRMSRCROM                                                                 STD_OFF
#define PDUR_ISDEF_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                               STD_OFF
#define PDUR_ISDEF_RMTRANSMITFCTPTR                                                                 STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFRXIF2DEST                                                   STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFRXIF2DEST                                                           STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFSRCAPPLICATIONROM                                           STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFTX2LO                                                       STD_OFF
#define PDUR_ISDEF_RMSRCROMIDXOFTX2LO                                                               STD_OFF
#define PDUR_ISDEF_RMSRCROMUSEDOFTX2LO                                                              STD_OFF
#define PDUR_ISDEF_RMTRANSMITFCTPTRIDXOFTX2LO                                                       STD_OFF
#define PDUR_ISDEF_PARTITIONINDEXOFCSLOFTXIF2UP                                                     STD_OFF
#define PDUR_ISDEF_RMGDESTROMIDXOFTXIF2UP                                                           STD_OFF
#define PDUR_ISDEF_PCPARTITIONCONFIGOFPCCONFIG                                                      STD_ON
#define PDUR_ISDEF_PARTITIONIDENTIFIERSOFPCCONFIG                                                   STD_ON
#define PDUR_ISDEF_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                     STD_ON
#define PDUR_ISDEF_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_ISDEF_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                          STD_ON
#define PDUR_ISDEF_INITIALIZEDOFPCPARTITIONCONFIG                                                   STD_OFF
#define PDUR_ISDEF_LOCKROMOFPCPARTITIONCONFIG                                                       STD_ON
#define PDUR_ISDEF_MMROMINDOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_ISDEF_MMROMOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_ISDEF_RMDESTROMOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_ISDEF_RMGDESTROMOFPCPARTITIONCONFIG                                                    STD_ON
#define PDUR_ISDEF_RMSRCROMOFPCPARTITIONCONFIG                                                      STD_ON
#define PDUR_ISDEF_RMTRANSMITFCTPTROFPCPARTITIONCONFIG                                              STD_ON
#define PDUR_ISDEF_RXIF2DESTOFPCPARTITIONCONFIG                                                     STD_ON
#define PDUR_ISDEF_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                             STD_ON
#define PDUR_ISDEF_TX2LOOFPCPARTITIONCONFIG                                                         STD_ON
#define PDUR_ISDEF_TXIF2UPOFPCPARTITIONCONFIG                                                       STD_ON
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCEqualsAlwaysToDefines  PduR Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/ 
#define PDUR_EQ2_MMROMINDENDIDXOFDESTAPPLICATIONMANAGERROM                                          
#define PDUR_EQ2_MMROMINDSTARTIDXOFDESTAPPLICATIONMANAGERROM                                        
#define PDUR_EQ2_MMROMINDUSEDOFDESTAPPLICATIONMANAGERROM                                            
#define PDUR_EQ2_SRCAPPLICATIONROMENDIDXOFDESTAPPLICATIONMANAGERROM                                 
#define PDUR_EQ2_SRCAPPLICATIONROMSTARTIDXOFDESTAPPLICATIONMANAGERROM                               
#define PDUR_EQ2_LOCKOFEXCLUSIVEAREAROM                                                             
#define PDUR_EQ2_UNLOCKOFEXCLUSIVEAREAROM                                                           
#define PDUR_EQ2_HASIFROUTINGOFGENERALPROPERTIESROM                                                 
#define PDUR_EQ2_EXCLUSIVEAREAROMIDXOFLOCKROM                                                       
#define PDUR_EQ2_EXCLUSIVEAREAROMUSEDOFLOCKROM                                                      
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMIDXOFMMROM                                                
#define PDUR_EQ2_LOIFOFMMROM                                                                        
#define PDUR_EQ2_LOIFTRANSMITFCTPTROFMMROM                                                          
#define PDUR_EQ2_MASKEDBITSOFMMROM                                                                  
#define PDUR_EQ2_RMGDESTROMENDIDXOFMMROM                                                            
#define PDUR_EQ2_RMGDESTROMSTARTIDXOFMMROM                                                          
#define PDUR_EQ2_RMGDESTROMUSEDOFMMROM                                                              
#define PDUR_EQ2_UPIFOFMMROM                                                                        
#define PDUR_EQ2_UPIFRXINDICATIONFCTPTROFMMROM                                                      
#define PDUR_EQ2_UPIFTRIGGERTRANSMITFCTPTROFMMROM                                                   
#define PDUR_EQ2_MMROMIND                                                                           
#define PDUR_EQ2_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                         
#define PDUR_EQ2_PARTITIONSNVOFPARTITIONIDENTIFIERS                                                 
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFRMDESTROM                                                     
#define PDUR_EQ2_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM                                               
#define PDUR_EQ2_RMGDESTROMIDXOFRMDESTROM                                                           
#define PDUR_EQ2_RMSRCROMIDXOFRMDESTROM                                                             
#define PDUR_EQ2_ROUTINGTYPEOFRMDESTROM                                                             
#define PDUR_EQ2_DESTHNDOFRMGDESTROM                                                                
#define PDUR_EQ2_DIRECTIONOFRMGDESTROM                                                              
#define PDUR_EQ2_LOCKROMIDXOFRMGDESTROM                                                             
#define PDUR_EQ2_MAXPDULENGTHOFRMGDESTROM                                                           
#define PDUR_EQ2_MMROMIDXOFRMGDESTROM                                                               
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFRMGDESTROM                                                    
#define PDUR_EQ2_PDURDESTPDUPROCESSINGOFRMGDESTROM                                                  
#define PDUR_EQ2_RMDESTROMIDXOFRMGDESTROM                                                           
#define PDUR_EQ2_TXIF2UPIDXOFRMGDESTROM                                                             
#define PDUR_EQ2_LOCKROMIDXOFRMSRCROM                                                               
#define PDUR_EQ2_MMROMIDXOFRMSRCROM                                                                 
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFRMSRCROM                                                      
#define PDUR_EQ2_RMDESTROMENDIDXOFRMSRCROM                                                          
#define PDUR_EQ2_RMDESTROMLENGTHOFRMSRCROM                                                          
#define PDUR_EQ2_RMDESTROMSTARTIDXOFRMSRCROM                                                        
#define PDUR_EQ2_SRCHNDOFRMSRCROM                                                                   
#define PDUR_EQ2_TRIGGERTRANSMITSUPPORTEDOFRMSRCROM                                                 
#define PDUR_EQ2_RMTRANSMITFCTPTR                                                                   
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFRXIF2DEST                                                     
#define PDUR_EQ2_RMSRCROMIDXOFRXIF2DEST                                                             
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFSRCAPPLICATIONROM                                             
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFTX2LO                                                         
#define PDUR_EQ2_RMSRCROMIDXOFTX2LO                                                                 
#define PDUR_EQ2_RMSRCROMUSEDOFTX2LO                                                                
#define PDUR_EQ2_RMTRANSMITFCTPTRIDXOFTX2LO                                                         
#define PDUR_EQ2_PARTITIONINDEXOFCSLOFTXIF2UP                                                       
#define PDUR_EQ2_RMGDESTROMIDXOFTXIF2UP                                                             
#define PDUR_EQ2_PCPARTITIONCONFIGOFPCCONFIG                                                        PduR_PCPartitionConfig
#define PDUR_EQ2_PARTITIONIDENTIFIERSOFPCCONFIG                                                     PduR_PartitionIdentifiers
#define PDUR_EQ2_DESTAPPLICATIONMANAGERROMOFPCPARTITIONCONFIG                                       PduR_DestApplicationManagerRom
#define PDUR_EQ2_EXCLUSIVEAREAROMOFPCPARTITIONCONFIG                                                PduR_ExclusiveAreaRom
#define PDUR_EQ2_GENERALPROPERTIESROMOFPCPARTITIONCONFIG                                            PduR_GeneralPropertiesRom
#define PDUR_EQ2_INITIALIZEDOFPCPARTITIONCONFIG                                                     
#define PDUR_EQ2_LOCKROMOFPCPARTITIONCONFIG                                                         PduR_LockRom
#define PDUR_EQ2_MMROMINDOFPCPARTITIONCONFIG                                                        PduR_MmRomInd
#define PDUR_EQ2_MMROMOFPCPARTITIONCONFIG                                                           PduR_MmRom
#define PDUR_EQ2_RMDESTROMOFPCPARTITIONCONFIG                                                       PduR_RmDestRom
#define PDUR_EQ2_RMGDESTROMOFPCPARTITIONCONFIG                                                      PduR_RmGDestRom
#define PDUR_EQ2_RMSRCROMOFPCPARTITIONCONFIG                                                        PduR_RmSrcRom
#define PDUR_EQ2_RMTRANSMITFCTPTROFPCPARTITIONCONFIG                                                PduR_RmTransmitFctPtr
#define PDUR_EQ2_RXIF2DESTOFPCPARTITIONCONFIG                                                       PduR_RxIf2Dest
#define PDUR_EQ2_SRCAPPLICATIONROMOFPCPARTITIONCONFIG                                               PduR_SrcApplicationRom
#define PDUR_EQ2_TX2LOOFPCPARTITIONCONFIG                                                           PduR_Tx2Lo
#define PDUR_EQ2_TXIF2UPOFPCPARTITIONCONFIG                                                         PduR_TxIf2Up
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCSymbolicNonDereferenciateablePointers  PduR Symbolic Non Dereferenciateable Pointers (PRE_COMPILE)
  \brief  Symbolic non dereferenciateable pointers to be used if all values are optimized to a defined and to return a correct value for has macros in variants.
  \{
*/ 
#define PduR_DestApplicationManagerRom                                                              ((PduR_DestApplicationManagerRomPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_LockRom                                                                                ((PduR_LockRomPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_MmRomInd                                                                               ((PduR_MmRomIndPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_RxIf2Dest                                                                              ((PduR_RxIf2DestPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_SrcApplicationRom                                                                      ((PduR_SrcApplicationRomPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_Tx2Lo                                                                                  ((PduR_Tx2LoPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
#define PduR_TxIf2Up                                                                                ((PduR_TxIf2UpPtrType)(&(PduR_PCPartitionConfig)))  /**< Non derefenciateable valid pointer */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCSymbolicInitializationPointers  PduR Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/ 
#define PduR_Config_Ptr                                                                             NULL_PTR  /**< symbolic identifier which shall be used to initialize 'PduR' */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCInitializationSymbols  PduR Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function. Please note, that the defined value can be a 'NULL_PTR' and the address operator is not usable.
  \{
*/ 
#define PduR_Config                                                                                 NULL_PTR  /**< symbolic identifier which could be used to initialize 'PduR */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGeneral  PduR General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/ 
#define PDUR_CHECK_INIT_POINTER                                                                     STD_OFF  /**< STD_ON if the init pointer shall not be used as NULL_PTR and a check shall validate this. */
#define PDUR_FINAL_MAGIC_NUMBER                                                                     0x331Eu  /**< the precompile constant to validate the size of the initialization structure at initialization time of PduR */
#define PDUR_INDIVIDUAL_POSTBUILD                                                                   STD_OFF  /**< the precompile constant to check, that the module is individual postbuildable. The module 'PduR' is not configured to be postbuild capable. */
#define PDUR_INIT_DATA                                                                              PDUR_CONST  /**< CompilerMemClassDefine for the initialization data. */
#define PDUR_INIT_DATA_HASH_CODE                                                                    -863935689  /**< the precompile constant to validate the initialization structure at initialization time of PduR with a hashcode. The seed value is '0x331Eu' */
#define PDUR_USE_ECUM_BSW_ERROR_HOOK                                                                STD_OFF  /**< STD_ON if the EcuM_BswErrorHook shall be called in the ConfigPtr check. */
#define PDUR_USE_INIT_POINTER                                                                       STD_OFF  /**< STD_ON if the init pointer PduR shall be used. */
#define partitionIndexOfCSLForCommonSharedMemory                                                    0u  /**< internal partition index of the ComStackLib for the partition CommonSharedMemory */
/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/** 
  \defgroup  PduRLTDataSwitches  PduR Data Switches  (LINK)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/ 
#define PDUR_LTCONFIG                                                                               STD_OFF  /**< Deactivateable: 'PduR_LTConfig' Reason: 'deactivated because PartitionConfig is deactivated.' */
#define PDUR_LTPARTITIONCONFIGOFLTCONFIG                                                            STD_OFF  /**< Deactivateable: 'PduR_LTConfig.LTPartitionConfig' Reason: 'deactivated because PartitionConfig is deactivated.' */
#define PDUR_LTPARTITIONCONFIG                                                                      STD_OFF  /**< Deactivateable: 'PduR_LTPartitionConfig' Reason: 'the struct is deactivated because all elements are deactivated in all variants.' */
/** 
  \}
*/ 



/** BroadcastDummy */

#define PDUR_MAX_TRIGGER_TRANSMIT_PDU_SIZE 7

/**********************************************************************************************************************
 * GLOBAL FUNCTION MACROS
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
  \defgroup  PduRPCGetRootDataMacros  PduR Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/ 
#define PduR_GetInitializedOfPCPartitionConfig(partitionIndex)                                      PduR_GetPCPartitionConfigOfPCConfig()[(partitionIndex)].InitializedOfPCPartitionConfig
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetConstantDuplicatedRootDataMacros  PduR Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/ 
#define PduR_GetPCPartitionConfigOfPCConfig()                                                       PduR_PCPartitionConfig  /**< the pointer to PduR_PCPartitionConfig */
#define PduR_GetPartitionIdentifiersOfPCConfig()                                                    PduR_PartitionIdentifiers  /**< the pointer to PduR_PartitionIdentifiers */
#define PduR_GetSizeOfPartitionIdentifiersOfPCConfig()                                              1u  /**< the number of accomplishable value elements in PduR_PartitionIdentifiers */
#define PduR_GetConfigIdOfPCPartitionConfig(partitionIndex)                                         0u  /**< DefinitionRef: /MICROSAR/PduR/PduRRoutingTables/PduRConfigurationId */
#define PduR_GetDestApplicationManagerRomOfPCPartitionConfig()                                      PduR_DestApplicationManagerRom  /**< the pointer to PduR_DestApplicationManagerRom */
#define PduR_GetExclusiveAreaRomOfPCPartitionConfig()                                               PduR_ExclusiveAreaRom  /**< the pointer to PduR_ExclusiveAreaRom */
#define PduR_GetGeneralPropertiesRomOfPCPartitionConfig()                                           PduR_GeneralPropertiesRom  /**< the pointer to PduR_GeneralPropertiesRom */
#define PduR_GetLockRomOfPCPartitionConfig()                                                        PduR_LockRom  /**< the pointer to PduR_LockRom */
#define PduR_GetMmRomIndOfPCPartitionConfig()                                                       PduR_MmRomInd  /**< the pointer to PduR_MmRomInd */
#define PduR_GetMmRomOfPCPartitionConfig()                                                          PduR_MmRom  /**< the pointer to PduR_MmRom */
#define PduR_GetRmDestRomOfPCPartitionConfig()                                                      PduR_RmDestRom  /**< the pointer to PduR_RmDestRom */
#define PduR_GetRmGDestRomOfPCPartitionConfig()                                                     PduR_RmGDestRom  /**< the pointer to PduR_RmGDestRom */
#define PduR_GetRmSrcRomOfPCPartitionConfig()                                                       PduR_RmSrcRom  /**< the pointer to PduR_RmSrcRom */
#define PduR_GetRmTransmitFctPtrOfPCPartitionConfig()                                               PduR_RmTransmitFctPtr  /**< the pointer to PduR_RmTransmitFctPtr */
#define PduR_GetRxIf2DestOfPCPartitionConfig()                                                      PduR_RxIf2Dest  /**< the pointer to PduR_RxIf2Dest */
#define PduR_GetSizeOfDestApplicationManagerRomOfPCPartitionConfig()                                1u  /**< the number of accomplishable value elements in PduR_DestApplicationManagerRom */
#define PduR_GetSizeOfExclusiveAreaRomOfPCPartitionConfig()                                         1u  /**< the number of accomplishable value elements in PduR_ExclusiveAreaRom */
#define PduR_GetSizeOfGeneralPropertiesRomOfPCPartitionConfig()                                     1u  /**< the number of accomplishable value elements in PduR_GeneralPropertiesRom */
#define PduR_GetSizeOfLockRomOfPCPartitionConfig()                                                  1u  /**< the number of accomplishable value elements in PduR_LockRom */
#define PduR_GetSizeOfMmRomIndOfPCPartitionConfig()                                                 2u  /**< the number of accomplishable value elements in PduR_MmRomInd */
#define PduR_GetSizeOfMmRomOfPCPartitionConfig()                                                    2u  /**< the number of accomplishable value elements in PduR_MmRom */
#define PduR_GetSizeOfRmDestRomOfPCPartitionConfig()                                                2u  /**< the number of accomplishable value elements in PduR_RmDestRom */
#define PduR_GetSizeOfRmGDestRomOfPCPartitionConfig()                                               2u  /**< the number of accomplishable value elements in PduR_RmGDestRom */
#define PduR_GetSizeOfRmSrcRomOfPCPartitionConfig()                                                 2u  /**< the number of accomplishable value elements in PduR_RmSrcRom */
#define PduR_GetSizeOfRmTransmitFctPtrOfPCPartitionConfig()                                         1u  /**< the number of accomplishable value elements in PduR_RmTransmitFctPtr */
#define PduR_GetSizeOfRxIf2DestOfPCPartitionConfig()                                                1u  /**< the number of accomplishable value elements in PduR_RxIf2Dest */
#define PduR_GetSizeOfSrcApplicationRomOfPCPartitionConfig()                                        1u  /**< the number of accomplishable value elements in PduR_SrcApplicationRom */
#define PduR_GetSizeOfTx2LoOfPCPartitionConfig()                                                    1u  /**< the number of accomplishable value elements in PduR_Tx2Lo */
#define PduR_GetSizeOfTxIf2UpOfPCPartitionConfig()                                                  1u  /**< the number of accomplishable value elements in PduR_TxIf2Up */
#define PduR_GetSrcApplicationRomOfPCPartitionConfig()                                              PduR_SrcApplicationRom  /**< the pointer to PduR_SrcApplicationRom */
#define PduR_GetTx2LoOfPCPartitionConfig()                                                          PduR_Tx2Lo  /**< the pointer to PduR_Tx2Lo */
#define PduR_GetTxIf2UpOfPCPartitionConfig()                                                        PduR_TxIf2Up  /**< the pointer to PduR_TxIf2Up */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetDataMacros  PduR Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/ 
#define PduR_GetLockOfExclusiveAreaRom(Index)                                                       (PduR_GetExclusiveAreaRomOfPCPartitionConfig()[(Index)].LockOfExclusiveAreaRom)
#define PduR_GetUnlockOfExclusiveAreaRom(Index)                                                     (PduR_GetExclusiveAreaRomOfPCPartitionConfig()[(Index)].UnlockOfExclusiveAreaRom)
#define PduR_IshasIfRoutingOfGeneralPropertiesRom(Index)                                            ((PduR_GetGeneralPropertiesRomOfPCPartitionConfig()[(Index)].hasIfRoutingOfGeneralPropertiesRom) != FALSE)
#define PduR_IsInitialized(partitionIndex)                                                          (((*(PduR_GetInitializedOfPCPartitionConfig(partitionIndex)))) != FALSE)
#define PduR_GetDestApplicationManagerRomIdxOfMmRom(Index)                                          (PduR_GetMmRomOfPCPartitionConfig()[(Index)].DestApplicationManagerRomIdxOfMmRom)
#define PduR_GetLoIfTransmitFctPtrOfMmRom(Index)                                                    (PduR_GetMmRomOfPCPartitionConfig()[(Index)].LoIfTransmitFctPtrOfMmRom)
#define PduR_GetMaskedBitsOfMmRom(Index)                                                            (PduR_GetMmRomOfPCPartitionConfig()[(Index)].MaskedBitsOfMmRom)
#define PduR_GetUpIfRxIndicationFctPtrOfMmRom(Index)                                                (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfRxIndicationFctPtrOfMmRom)
#define PduR_GetUpIfTriggerTransmitFctPtrOfMmRom(Index)                                             (PduR_GetMmRomOfPCPartitionConfig()[(Index)].UpIfTriggerTransmitFctPtrOfMmRom)
#define PduR_GetPartitionSNVOfPartitionIdentifiers(Index)                                           (PduR_GetPartitionIdentifiersOfPCConfig()[(Index)].PartitionSNVOfPartitionIdentifiers)
#define PduR_GetPduLengthHandlingStrategyOfRmDestRom(Index)                                         (PduR_GetRmDestRomOfPCPartitionConfig()[(Index)].PduLengthHandlingStrategyOfRmDestRom)
#define PduR_GetLockRomIdxOfRmGDestRom(Index)                                                       (PduR_GetRmGDestRomOfPCPartitionConfig()[(Index)].LockRomIdxOfRmGDestRom)
#define PduR_GetMmRomIdxOfRmSrcRom(Index)                                                           (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].MmRomIdxOfRmSrcRom)
#define PduR_GetPartitionIndexOfCslOfRmSrcRom(Index)                                                (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].PartitionIndexOfCslOfRmSrcRom)
#define PduR_GetSrcHndOfRmSrcRom(Index)                                                             (PduR_GetRmSrcRomOfPCPartitionConfig()[(Index)].SrcHndOfRmSrcRom)
#define PduR_GetRmTransmitFctPtr(Index)                                                             (PduR_GetRmTransmitFctPtrOfPCPartitionConfig()[(Index)])
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetBitDataMacros  PduR Get Bit Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read bitcoded data elements.
  \{
*/ 
#define PduR_IsUpIfOfMmRom(Index)                                                                   (PDUR_UPIFOFMMROM_MASK == (PduR_GetMaskedBitsOfMmRom(Index) & PDUR_UPIFOFMMROM_MASK))  /**< Is the module a upper communication interface module. */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCGetDeduplicatedDataMacros  PduR Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/ 
#define PduR_GetConfigId(partitionIndex)                                                            PduR_GetConfigIdOfPCPartitionConfig(partitionIndex)
#define PduR_GetMmRomIndEndIdxOfDestApplicationManagerRom(Index)                                    ((PduR_MmRomIndEndIdxOfDestApplicationManagerRomType)((((PduR_MmRomIndEndIdxOfDestApplicationManagerRomType)(Index)) + 2u)))  /**< the end index of the 0:n relation pointing to PduR_MmRomInd */
#define PduR_GetMmRomIndStartIdxOfDestApplicationManagerRom(Index)                                  ((PduR_MmRomIndStartIdxOfDestApplicationManagerRomType)((Index)))  /**< the start index of the 0:n relation pointing to PduR_MmRomInd */
#define PduR_IsMmRomIndUsedOfDestApplicationManagerRom(Index)                                       (((boolean)(PduR_GetMmRomIndStartIdxOfDestApplicationManagerRom(Index) != PDUR_NO_MMROMINDSTARTIDXOFDESTAPPLICATIONMANAGERROM)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to PduR_MmRomInd */
#define PduR_GetSrcApplicationRomEndIdxOfDestApplicationManagerRom(Index)                           ((PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType)((((PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType)(Index)) + 1u)))  /**< the end index of the 1:n relation pointing to PduR_SrcApplicationRom */
#define PduR_GetSrcApplicationRomStartIdxOfDestApplicationManagerRom(Index)                         ((PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRomType)((Index)))  /**< the start index of the 1:n relation pointing to PduR_SrcApplicationRom */
#define PduR_GetExclusiveAreaRomIdxOfLockRom(Index)                                                 ((PduR_ExclusiveAreaRomIdxOfLockRomType)((Index)))  /**< the index of the 0:1 relation pointing to PduR_ExclusiveAreaRom */
#define PduR_IsExclusiveAreaRomUsedOfLockRom(Index)                                                 (((boolean)(PduR_GetExclusiveAreaRomIdxOfLockRom(Index) != PDUR_NO_EXCLUSIVEAREAROMIDXOFLOCKROM)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to PduR_ExclusiveAreaRom */
#define PduR_IsLoIfOfMmRom(Index)                                                                   (((!(PduR_IsUpIfOfMmRom(Index)))) != FALSE)  /**< Is the module a lower communication interface module. */
#define PduR_GetRmGDestRomEndIdxOfMmRom(Index)                                                      ((PduR_RmGDestRomEndIdxOfMmRomType)((((PduR_RmGDestRomEndIdxOfMmRomType)(Index)) + 1u)))  /**< the end index of the 0:n relation pointing to PduR_RmGDestRom */
#define PduR_GetRmGDestRomStartIdxOfMmRom(Index)                                                    ((PduR_RmGDestRomStartIdxOfMmRomType)((Index)))  /**< the start index of the 0:n relation pointing to PduR_RmGDestRom */
#define PduR_IsRmGDestRomUsedOfMmRom(Index)                                                         (((boolean)(PduR_GetRmGDestRomStartIdxOfMmRom(Index) != PDUR_NO_RMGDESTROMSTARTIDXOFMMROM)) != FALSE)  /**< TRUE, if the 0:n relation has 1 relation pointing to PduR_RmGDestRom */
#define PduR_GetMmRomInd(Index)                                                                     ((PduR_MmRomIndType)((Index)))  /**< the indexes of the 1:1 sorted relation pointing to PduR_MmRom */
#define PduR_GetPCPartitionConfigIdxOfPartitionIdentifiers(Index)                                   ((PduR_PCPartitionConfigIdxOfPartitionIdentifiersType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_PCPartitionConfig */
#define PduR_GetPartitionIndexOfCslOfRmDestRom(Index)                                               ((PduR_PartitionIndexOfCslOfRmDestRomType)((PduR_GetPduLengthHandlingStrategyOfRmDestRom(Index) - 0x02u)))
#define PduR_GetRmGDestRomIdxOfRmDestRom(Index)                                                     ((PduR_RmGDestRomIdxOfRmDestRomType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmGDestRom */
#define PduR_GetRmSrcRomIdxOfRmDestRom(Index)                                                       ((PduR_RmSrcRomIdxOfRmDestRomType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmSrcRom */
#define PduR_GetRoutingTypeOfRmDestRom(Index)                                                       ((PduR_RoutingTypeOfRmDestRomType)((Index)))  /**< Type of the Routing (API Forwarding, Gateway). */
#define PduR_GetDestHndOfRmGDestRom(Index)                                                          PduR_GetLockRomIdxOfRmGDestRom(Index)  /**< handle to be used as parameter for the StartOfReception, CopyRxData, Transmit or RxIndication function call. */
#define PduR_GetDirectionOfRmGDestRom(Index)                                                        ((PduR_DirectionOfRmGDestRomType)((Index)))  /**< Direction of this Pdu: Rx or Tx */
#define PduR_GetMaxPduLengthOfRmGDestRom(Index)                                                     ((PduR_MaxPduLengthOfRmGDestRomType)((PduR_GetLockRomIdxOfRmGDestRom(Index) + 7u)))  /**< Configured PduLength + metadata length. */
#define PduR_GetMmRomIdxOfRmGDestRom(Index)                                                         ((PduR_MmRomIdxOfRmGDestRomType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_MmRom */
#define PduR_GetPartitionIndexOfCslOfRmGDestRom(Index)                                              PduR_GetLockRomIdxOfRmGDestRom(Index)
#define PduR_GetPduRDestPduProcessingOfRmGDestRom(Index)                                            ((PduR_PduRDestPduProcessingOfRmGDestRomType)((PduR_GetLockRomIdxOfRmGDestRom(Index) + 1u)))  /**< Is Processing Type of destination PDU. */
#define PduR_GetRmDestRomIdxOfRmGDestRom(Index)                                                     ((PduR_RmDestRomIdxOfRmGDestRomType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmDestRom */
#define PduR_GetTxIf2UpIdxOfRmGDestRom(Index)                                                       PduR_GetLockRomIdxOfRmGDestRom(Index)  /**< TxIf2Up index. */
#define PduR_GetLockRomIdxOfRmSrcRom(Index)                                                         PduR_GetPartitionIndexOfCslOfRmSrcRom(Index)  /**< the index of the 1:1 relation pointing to PduR_LockRom */
#define PduR_GetRmDestRomEndIdxOfRmSrcRom(Index)                                                    ((PduR_RmDestRomEndIdxOfRmSrcRomType)((((PduR_RmDestRomEndIdxOfRmSrcRomType)(Index)) + 1u)))  /**< the end index of the 1:n relation pointing to PduR_RmDestRom */
#define PduR_GetRmDestRomLengthOfRmSrcRom(Index)                                                    ((PduR_RmDestRomLengthOfRmSrcRomType)((PduR_GetPartitionIndexOfCslOfRmSrcRom(Index) + 1u)))  /**< the number of relations pointing to PduR_RmDestRom */
#define PduR_GetRmDestRomStartIdxOfRmSrcRom(Index)                                                  ((PduR_RmDestRomStartIdxOfRmSrcRomType)((Index)))  /**< the start index of the 1:n relation pointing to PduR_RmDestRom */
#define PduR_IsTriggerTransmitSupportedOfRmSrcRom(Index)                                            (((boolean)(PduR_GetMmRomIdxOfRmSrcRom(Index) == 0u)) != FALSE)
#define PduR_GetPartitionIndexOfCslOfRxIf2Dest(Index)                                               ((PduR_PartitionIndexOfCslOfRxIf2DestType)((Index)))
#define PduR_GetRmSrcRomIdxOfRxIf2Dest(Index)                                                       ((PduR_RmSrcRomIdxOfRxIf2DestType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmSrcRom */
#define PduR_GetSizeOfDestApplicationManagerRom()                                                   PduR_GetSizeOfDestApplicationManagerRomOfPCPartitionConfig()
#define PduR_GetSizeOfExclusiveAreaRom()                                                            PduR_GetSizeOfExclusiveAreaRomOfPCPartitionConfig()
#define PduR_GetSizeOfGeneralPropertiesRom()                                                        PduR_GetSizeOfGeneralPropertiesRomOfPCPartitionConfig()
#define PduR_GetSizeOfLockRom()                                                                     PduR_GetSizeOfLockRomOfPCPartitionConfig()
#define PduR_GetSizeOfMmRom()                                                                       PduR_GetSizeOfMmRomOfPCPartitionConfig()
#define PduR_GetSizeOfMmRomInd()                                                                    PduR_GetSizeOfMmRomIndOfPCPartitionConfig()
#define PduR_GetSizeOfPartitionIdentifiers()                                                        PduR_GetSizeOfPartitionIdentifiersOfPCConfig()
#define PduR_GetSizeOfRmDestRom()                                                                   PduR_GetSizeOfRmDestRomOfPCPartitionConfig()
#define PduR_GetSizeOfRmGDestRom()                                                                  PduR_GetSizeOfRmGDestRomOfPCPartitionConfig()
#define PduR_GetSizeOfRmSrcRom()                                                                    PduR_GetSizeOfRmSrcRomOfPCPartitionConfig()
#define PduR_GetSizeOfRmTransmitFctPtr()                                                            PduR_GetSizeOfRmTransmitFctPtrOfPCPartitionConfig()
#define PduR_GetSizeOfRxIf2Dest()                                                                   PduR_GetSizeOfRxIf2DestOfPCPartitionConfig()
#define PduR_GetSizeOfSrcApplicationRom()                                                           PduR_GetSizeOfSrcApplicationRomOfPCPartitionConfig()
#define PduR_GetSizeOfTx2Lo()                                                                       PduR_GetSizeOfTx2LoOfPCPartitionConfig()
#define PduR_GetSizeOfTxIf2Up()                                                                     PduR_GetSizeOfTxIf2UpOfPCPartitionConfig()
#define PduR_GetPartitionIndexOfCslOfSrcApplicationRom(Index)                                       ((PduR_PartitionIndexOfCslOfSrcApplicationRomType)((Index)))
#define PduR_GetPartitionIndexOfCslOfTx2Lo(Index)                                                   ((PduR_PartitionIndexOfCslOfTx2LoType)((Index)))
#define PduR_GetRmSrcRomIdxOfTx2Lo(Index)                                                           ((PduR_RmSrcRomIdxOfTx2LoType)((((PduR_RmSrcRomIdxOfTx2LoType)(Index)) + 1u)))  /**< the index of the 0:1 relation pointing to PduR_RmSrcRom */
#define PduR_IsRmSrcRomUsedOfTx2Lo(Index)                                                           (((boolean)(PduR_GetRmSrcRomIdxOfTx2Lo(Index) != PDUR_NO_RMSRCROMIDXOFTX2LO)) != FALSE)  /**< TRUE, if the 0:1 relation has minimum 1 relation pointing to PduR_RmSrcRom */
#define PduR_GetRmTransmitFctPtrIdxOfTx2Lo(Index)                                                   ((PduR_RmTransmitFctPtrIdxOfTx2LoType)((Index)))  /**< the index of the 1:1 relation pointing to PduR_RmTransmitFctPtr */
#define PduR_GetPartitionIndexOfCslOfTxIf2Up(Index)                                                 ((PduR_PartitionIndexOfCslOfTxIf2UpType)((Index)))
#define PduR_GetRmGDestRomIdxOfTxIf2Up(Index)                                                       ((PduR_RmGDestRomIdxOfTxIf2UpType)((((PduR_RmGDestRomIdxOfTxIf2UpType)(Index)) + 1u)))  /**< the index of the 1:1 relation pointing to PduR_RmGDestRom */
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCSetDataMacros  PduR Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/ 
#define PduR_SetInitialized(Value, partitionIndex)                                                  (*(PduR_GetInitializedOfPCPartitionConfig(partitionIndex))) = (Value)
/** 
  \}
*/ 

/** 
  \defgroup  PduRPCHasMacros  PduR Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information. TRUE in the CONFIGURATION_VARIANT PRE-COMPILE, TRUE or FALSE in the CONFIGURATION_VARIANT POST-BUILD.
  \{
*/ 
#define PduR_HasConfigId(partitionIndex)                                                            (TRUE != FALSE)
#define PduR_HasDestApplicationManagerRom()                                                         (TRUE != FALSE)
#define PduR_HasMmRomIndEndIdxOfDestApplicationManagerRom()                                         (TRUE != FALSE)
#define PduR_HasMmRomIndStartIdxOfDestApplicationManagerRom()                                       (TRUE != FALSE)
#define PduR_HasMmRomIndUsedOfDestApplicationManagerRom()                                           (TRUE != FALSE)
#define PduR_HasSrcApplicationRomEndIdxOfDestApplicationManagerRom()                                (TRUE != FALSE)
#define PduR_HasSrcApplicationRomStartIdxOfDestApplicationManagerRom()                              (TRUE != FALSE)
#define PduR_HasExclusiveAreaRom()                                                                  (TRUE != FALSE)
#define PduR_HasLockOfExclusiveAreaRom()                                                            (TRUE != FALSE)
#define PduR_HasUnlockOfExclusiveAreaRom()                                                          (TRUE != FALSE)
#define PduR_HasGeneralPropertiesRom()                                                              (TRUE != FALSE)
#define PduR_HashasIfRoutingOfGeneralPropertiesRom()                                                (TRUE != FALSE)
#define PduR_HasInitialized(partitionIndex)                                                         (PduR_GetInitializedOfPCPartitionConfig(partitionIndex) != NULL_PTR)
#define PduR_HasLockRom()                                                                           (TRUE != FALSE)
#define PduR_HasExclusiveAreaRomIdxOfLockRom()                                                      (TRUE != FALSE)
#define PduR_HasExclusiveAreaRomUsedOfLockRom()                                                     (TRUE != FALSE)
#define PduR_HasMmRom()                                                                             (TRUE != FALSE)
#define PduR_HasDestApplicationManagerRomIdxOfMmRom()                                               (TRUE != FALSE)
#define PduR_HasLoIfOfMmRom()                                                                       (TRUE != FALSE)
#define PduR_HasLoIfTransmitFctPtrOfMmRom()                                                         (TRUE != FALSE)
#define PduR_HasMaskedBitsOfMmRom()                                                                 (TRUE != FALSE)
#define PduR_HasRmGDestRomEndIdxOfMmRom()                                                           (TRUE != FALSE)
#define PduR_HasRmGDestRomStartIdxOfMmRom()                                                         (TRUE != FALSE)
#define PduR_HasRmGDestRomUsedOfMmRom()                                                             (TRUE != FALSE)
#define PduR_HasUpIfOfMmRom()                                                                       (TRUE != FALSE)
#define PduR_HasUpIfRxIndicationFctPtrOfMmRom()                                                     (TRUE != FALSE)
#define PduR_HasUpIfTriggerTransmitFctPtrOfMmRom()                                                  (TRUE != FALSE)
#define PduR_HasMmRomInd()                                                                          (TRUE != FALSE)
#define PduR_HasPartitionIdentifiers()                                                              (TRUE != FALSE)
#define PduR_HasPCPartitionConfigIdxOfPartitionIdentifiers()                                        (TRUE != FALSE)
#define PduR_HasPartitionSNVOfPartitionIdentifiers()                                                (TRUE != FALSE)
#define PduR_HasRmDestRom()                                                                         (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfRmDestRom()                                                    (TRUE != FALSE)
#define PduR_HasPduLengthHandlingStrategyOfRmDestRom()                                              (TRUE != FALSE)
#define PduR_HasRmGDestRomIdxOfRmDestRom()                                                          (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfRmDestRom()                                                            (TRUE != FALSE)
#define PduR_HasRoutingTypeOfRmDestRom()                                                            (TRUE != FALSE)
#define PduR_HasRmGDestRom()                                                                        (TRUE != FALSE)
#define PduR_HasDestHndOfRmGDestRom()                                                               (TRUE != FALSE)
#define PduR_HasDirectionOfRmGDestRom()                                                             (TRUE != FALSE)
#define PduR_HasLockRomIdxOfRmGDestRom()                                                            (TRUE != FALSE)
#define PduR_HasMaxPduLengthOfRmGDestRom()                                                          (TRUE != FALSE)
#define PduR_HasMmRomIdxOfRmGDestRom()                                                              (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfRmGDestRom()                                                   (TRUE != FALSE)
#define PduR_HasPduRDestPduProcessingOfRmGDestRom()                                                 (TRUE != FALSE)
#define PduR_HasRmDestRomIdxOfRmGDestRom()                                                          (TRUE != FALSE)
#define PduR_HasTxIf2UpIdxOfRmGDestRom()                                                            (TRUE != FALSE)
#define PduR_HasRmSrcRom()                                                                          (TRUE != FALSE)
#define PduR_HasLockRomIdxOfRmSrcRom()                                                              (TRUE != FALSE)
#define PduR_HasMmRomIdxOfRmSrcRom()                                                                (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfRmSrcRom()                                                     (TRUE != FALSE)
#define PduR_HasRmDestRomEndIdxOfRmSrcRom()                                                         (TRUE != FALSE)
#define PduR_HasRmDestRomLengthOfRmSrcRom()                                                         (TRUE != FALSE)
#define PduR_HasRmDestRomStartIdxOfRmSrcRom()                                                       (TRUE != FALSE)
#define PduR_HasSrcHndOfRmSrcRom()                                                                  (TRUE != FALSE)
#define PduR_HasTriggerTransmitSupportedOfRmSrcRom()                                                (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtr()                                                                  (TRUE != FALSE)
#define PduR_HasRxIf2Dest()                                                                         (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfRxIf2Dest()                                                    (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfRxIf2Dest()                                                            (TRUE != FALSE)
#define PduR_HasSizeOfDestApplicationManagerRom()                                                   (TRUE != FALSE)
#define PduR_HasSizeOfExclusiveAreaRom()                                                            (TRUE != FALSE)
#define PduR_HasSizeOfGeneralPropertiesRom()                                                        (TRUE != FALSE)
#define PduR_HasSizeOfLockRom()                                                                     (TRUE != FALSE)
#define PduR_HasSizeOfMmRom()                                                                       (TRUE != FALSE)
#define PduR_HasSizeOfMmRomInd()                                                                    (TRUE != FALSE)
#define PduR_HasSizeOfPartitionIdentifiers()                                                        (TRUE != FALSE)
#define PduR_HasSizeOfRmDestRom()                                                                   (TRUE != FALSE)
#define PduR_HasSizeOfRmGDestRom()                                                                  (TRUE != FALSE)
#define PduR_HasSizeOfRmSrcRom()                                                                    (TRUE != FALSE)
#define PduR_HasSizeOfRmTransmitFctPtr()                                                            (TRUE != FALSE)
#define PduR_HasSizeOfRxIf2Dest()                                                                   (TRUE != FALSE)
#define PduR_HasSizeOfSrcApplicationRom()                                                           (TRUE != FALSE)
#define PduR_HasSizeOfTx2Lo()                                                                       (TRUE != FALSE)
#define PduR_HasSizeOfTxIf2Up()                                                                     (TRUE != FALSE)
#define PduR_HasSrcApplicationRom()                                                                 (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfSrcApplicationRom()                                            (TRUE != FALSE)
#define PduR_HasTx2Lo()                                                                             (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfTx2Lo()                                                        (TRUE != FALSE)
#define PduR_HasRmSrcRomIdxOfTx2Lo()                                                                (TRUE != FALSE)
#define PduR_HasRmSrcRomUsedOfTx2Lo()                                                               (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtrIdxOfTx2Lo()                                                        (TRUE != FALSE)
#define PduR_HasTxIf2Up()                                                                           (TRUE != FALSE)
#define PduR_HasPartitionIndexOfCslOfTxIf2Up()                                                      (TRUE != FALSE)
#define PduR_HasRmGDestRomIdxOfTxIf2Up()                                                            (TRUE != FALSE)
#define PduR_HasPCConfig()                                                                          (TRUE != FALSE)
#define PduR_HasPCPartitionConfigOfPCConfig()                                                       (TRUE != FALSE)
#define PduR_HasPartitionIdentifiersOfPCConfig()                                                    (TRUE != FALSE)
#define PduR_HasSizeOfPartitionIdentifiersOfPCConfig()                                              (TRUE != FALSE)
#define PduR_HasPCPartitionConfig()                                                                 (TRUE != FALSE)
#define PduR_HasConfigIdOfPCPartitionConfig(partitionIndex)                                         (TRUE != FALSE)
#define PduR_HasDestApplicationManagerRomOfPCPartitionConfig()                                      (TRUE != FALSE)
#define PduR_HasExclusiveAreaRomOfPCPartitionConfig()                                               (TRUE != FALSE)
#define PduR_HasGeneralPropertiesRomOfPCPartitionConfig()                                           (TRUE != FALSE)
#define PduR_HasInitializedOfPCPartitionConfig(partitionIndex)                                      (TRUE != FALSE)
#define PduR_HasLockRomOfPCPartitionConfig()                                                        (TRUE != FALSE)
#define PduR_HasMmRomIndOfPCPartitionConfig()                                                       (TRUE != FALSE)
#define PduR_HasMmRomOfPCPartitionConfig()                                                          (TRUE != FALSE)
#define PduR_HasRmDestRomOfPCPartitionConfig()                                                      (TRUE != FALSE)
#define PduR_HasRmGDestRomOfPCPartitionConfig()                                                     (TRUE != FALSE)
#define PduR_HasRmSrcRomOfPCPartitionConfig()                                                       (TRUE != FALSE)
#define PduR_HasRmTransmitFctPtrOfPCPartitionConfig()                                               (TRUE != FALSE)
#define PduR_HasRxIf2DestOfPCPartitionConfig()                                                      (TRUE != FALSE)
#define PduR_HasSizeOfDestApplicationManagerRomOfPCPartitionConfig()                                (TRUE != FALSE)
#define PduR_HasSizeOfExclusiveAreaRomOfPCPartitionConfig()                                         (TRUE != FALSE)
#define PduR_HasSizeOfGeneralPropertiesRomOfPCPartitionConfig()                                     (TRUE != FALSE)
#define PduR_HasSizeOfLockRomOfPCPartitionConfig()                                                  (TRUE != FALSE)
#define PduR_HasSizeOfMmRomIndOfPCPartitionConfig()                                                 (TRUE != FALSE)
#define PduR_HasSizeOfMmRomOfPCPartitionConfig()                                                    (TRUE != FALSE)
#define PduR_HasSizeOfRmDestRomOfPCPartitionConfig()                                                (TRUE != FALSE)
#define PduR_HasSizeOfRmGDestRomOfPCPartitionConfig()                                               (TRUE != FALSE)
#define PduR_HasSizeOfRmSrcRomOfPCPartitionConfig()                                                 (TRUE != FALSE)
#define PduR_HasSizeOfRmTransmitFctPtrOfPCPartitionConfig()                                         (TRUE != FALSE)
#define PduR_HasSizeOfRxIf2DestOfPCPartitionConfig()                                                (TRUE != FALSE)
#define PduR_HasSizeOfSrcApplicationRomOfPCPartitionConfig()                                        (TRUE != FALSE)
#define PduR_HasSizeOfTx2LoOfPCPartitionConfig()                                                    (TRUE != FALSE)
#define PduR_HasSizeOfTxIf2UpOfPCPartitionConfig()                                                  (TRUE != FALSE)
#define PduR_HasSrcApplicationRomOfPCPartitionConfig()                                              (TRUE != FALSE)
#define PduR_HasTx2LoOfPCPartitionConfig()                                                          (TRUE != FALSE)
#define PduR_HasTxIf2UpOfPCPartitionConfig()                                                        (TRUE != FALSE)
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


#define PduR_IsPreInitialized()                     (PduR_PreInitialized != FALSE)
#define PduR_SetPreInitialized(Value)               (PduR_IsPreInitialized()) = (Value)

#define CommonSharedMemory  0u /* Dummy symbolic name value for the shared memory memory section */

/**********************************************************************************************************************
 * GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef P2FUNC(void, PDUR_CODE, PduR_LockFunctionType) (void);    /* PRQA S 1336 */ /* MD_PduR_1336 */

/* Communication Interface APIs */

typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TransmitFctPtrType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_TriggerTransmitFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfRxIndicationType) (PduIdType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void, PDUR_APPL_CODE, PduR_IfTxConfirmationFctPtrType) (PduIdType);    /* PRQA S 1336 */ /* MD_PduR_1336 */

/* Transport Protocol APIs */
typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_StartOfReceptionFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduLengthType, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyRxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef P2FUNC(BufReq_ReturnType, PDUR_APPL_CODE, PduR_CopyTxDataFctPtrType) (PduIdType, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpRxIndicationFctPtrType) (PduIdType, Std_ReturnType);    /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef P2FUNC(void, PDUR_APPL_CODE, PduR_TpTxConfirmationFctPtrType) (PduIdType, Std_ReturnType);    /* PRQA S 1336 */ /* MD_PduR_1336 */


#if ((PDUR_IFCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON) || (PDUR_TPCANCELTRANSMITSUPPORTEDOFMMROM == STD_ON))
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelTransmitFctPtrType)(PduIdType);    /* PRQA S 1336 */ /* MD_PduR_1336 */
#endif
#if (PDUR_CANCELRECEIVESUPPORTEDOFMMROM == STD_ON)
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_CancelReceiveFctPtrType) (PduIdType);    /* PRQA S 1336 */ /* MD_PduR_1336 */
#endif
#if (PDUR_CHANGEPARAMETERSUPPORTEDOFMMROM == STD_ON)
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_ChangeParameterFctPtrType) (PduIdType, TPParameterType, uint16);    /* PRQA S 1336 */ /* MD_PduR_1336 */
#endif


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCIterableTypes  PduR Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/ 
/**   \brief  type used to iterate PduR_DestApplicationManagerRom */
typedef uint8_least PduR_DestApplicationManagerRomIterType;

/**   \brief  type used to iterate PduR_ExclusiveAreaRom */
typedef uint8_least PduR_ExclusiveAreaRomIterType;

/**   \brief  type used to iterate PduR_GeneralPropertiesRom */
typedef uint8_least PduR_GeneralPropertiesRomIterType;

/**   \brief  type used to iterate PduR_LockRom */
typedef uint8_least PduR_LockRomIterType;

/**   \brief  type used to iterate PduR_MmRom */
typedef uint8_least PduR_MmRomIterType;

/**   \brief  type used to iterate PduR_MmRomInd */
typedef uint8_least PduR_MmRomIndIterType;

/**   \brief  type used to iterate PduR_PartitionIdentifiers */
typedef uint8_least PduR_PartitionIdentifiersIterType;

/**   \brief  type used to iterate PduR_RmDestRom */
typedef uint8_least PduR_RmDestRomIterType;

/**   \brief  type used to iterate PduR_RmGDestRom */
typedef uint8_least PduR_RmGDestRomIterType;

/**   \brief  type used to iterate PduR_RmSrcRom */
typedef uint8_least PduR_RmSrcRomIterType;

/**   \brief  type used to iterate PduR_RmTransmitFctPtr */
typedef uint8_least PduR_RmTransmitFctPtrIterType;

/**   \brief  type used to iterate PduR_RxIf2Dest */
typedef uint8_least PduR_RxIf2DestIterType;

/**   \brief  type used to iterate PduR_SrcApplicationRom */
typedef uint8_least PduR_SrcApplicationRomIterType;

/**   \brief  type used to iterate PduR_Tx2Lo */
typedef uint8_least PduR_Tx2LoIterType;

/**   \brief  type used to iterate PduR_TxIf2Up */
typedef uint8_least PduR_TxIf2UpIterType;

/**   \brief  type used to iterate PduR_PCPartitionConfig */
typedef uint8_least PduR_PCPartitionConfigIterType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCValueTypes  PduR Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/ 
/**   \brief  value based type definition for PduR_ConfigId */
typedef uint8 PduR_ConfigIdType;

/**   \brief  value based type definition for PduR_MmRomIndEndIdxOfDestApplicationManagerRom */
typedef uint8 PduR_MmRomIndEndIdxOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_MmRomIndStartIdxOfDestApplicationManagerRom */
typedef uint8 PduR_MmRomIndStartIdxOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_MmRomIndUsedOfDestApplicationManagerRom */
typedef boolean PduR_MmRomIndUsedOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRom */
typedef uint8 PduR_SrcApplicationRomEndIdxOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRom */
typedef uint8 PduR_SrcApplicationRomStartIdxOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_hasIfRoutingOfGeneralPropertiesRom */
typedef boolean PduR_hasIfRoutingOfGeneralPropertiesRomType;

/**   \brief  value based type definition for PduR_Initialized */
typedef boolean PduR_InitializedType;

/**   \brief  value based type definition for PduR_ExclusiveAreaRomIdxOfLockRom */
typedef uint8 PduR_ExclusiveAreaRomIdxOfLockRomType;

/**   \brief  value based type definition for PduR_ExclusiveAreaRomUsedOfLockRom */
typedef boolean PduR_ExclusiveAreaRomUsedOfLockRomType;

/**   \brief  value based type definition for PduR_DestApplicationManagerRomIdxOfMmRom */
typedef uint8 PduR_DestApplicationManagerRomIdxOfMmRomType;

/**   \brief  value based type definition for PduR_LoIfOfMmRom */
typedef boolean PduR_LoIfOfMmRomType;

/**   \brief  value based type definition for PduR_MaskedBitsOfMmRom */
typedef uint8 PduR_MaskedBitsOfMmRomType;

/**   \brief  value based type definition for PduR_RmGDestRomEndIdxOfMmRom */
typedef uint8 PduR_RmGDestRomEndIdxOfMmRomType;

/**   \brief  value based type definition for PduR_RmGDestRomStartIdxOfMmRom */
typedef uint8 PduR_RmGDestRomStartIdxOfMmRomType;

/**   \brief  value based type definition for PduR_RmGDestRomUsedOfMmRom */
typedef boolean PduR_RmGDestRomUsedOfMmRomType;

/**   \brief  value based type definition for PduR_UpIfOfMmRom */
typedef boolean PduR_UpIfOfMmRomType;

/**   \brief  value based type definition for PduR_MmRomInd */
typedef uint8 PduR_MmRomIndType;

/**   \brief  value based type definition for PduR_PCPartitionConfigIdxOfPartitionIdentifiers */
typedef uint8 PduR_PCPartitionConfigIdxOfPartitionIdentifiersType;

/**   \brief  value based type definition for PduR_PartitionSNVOfPartitionIdentifiers */
typedef uint32 PduR_PartitionSNVOfPartitionIdentifiersType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfRmDestRom */
typedef uint8 PduR_PartitionIndexOfCslOfRmDestRomType;

/**   \brief  value based type definition for PduR_PduLengthHandlingStrategyOfRmDestRom */
typedef uint8 PduR_PduLengthHandlingStrategyOfRmDestRomType;

/**   \brief  value based type definition for PduR_RmGDestRomIdxOfRmDestRom */
typedef uint8 PduR_RmGDestRomIdxOfRmDestRomType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfRmDestRom */
typedef uint8 PduR_RmSrcRomIdxOfRmDestRomType;

/**   \brief  value based type definition for PduR_RoutingTypeOfRmDestRom */
typedef uint8 PduR_RoutingTypeOfRmDestRomType;

/**   \brief  value based type definition for PduR_DestHndOfRmGDestRom */
typedef uint8 PduR_DestHndOfRmGDestRomType;

/**   \brief  value based type definition for PduR_DirectionOfRmGDestRom */
typedef uint8 PduR_DirectionOfRmGDestRomType;

/**   \brief  value based type definition for PduR_LockRomIdxOfRmGDestRom */
typedef uint8 PduR_LockRomIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_MaxPduLengthOfRmGDestRom */
typedef uint8 PduR_MaxPduLengthOfRmGDestRomType;

/**   \brief  value based type definition for PduR_MmRomIdxOfRmGDestRom */
typedef uint8 PduR_MmRomIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfRmGDestRom */
typedef uint8 PduR_PartitionIndexOfCslOfRmGDestRomType;

/**   \brief  value based type definition for PduR_PduRDestPduProcessingOfRmGDestRom */
typedef uint8 PduR_PduRDestPduProcessingOfRmGDestRomType;

/**   \brief  value based type definition for PduR_RmDestRomIdxOfRmGDestRom */
typedef uint8 PduR_RmDestRomIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_TxIf2UpIdxOfRmGDestRom */
typedef uint8 PduR_TxIf2UpIdxOfRmGDestRomType;

/**   \brief  value based type definition for PduR_LockRomIdxOfRmSrcRom */
typedef uint8 PduR_LockRomIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_MmRomIdxOfRmSrcRom */
typedef uint8 PduR_MmRomIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfRmSrcRom */
typedef uint8 PduR_PartitionIndexOfCslOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomEndIdxOfRmSrcRom */
typedef uint8 PduR_RmDestRomEndIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomLengthOfRmSrcRom */
typedef uint8 PduR_RmDestRomLengthOfRmSrcRomType;

/**   \brief  value based type definition for PduR_RmDestRomStartIdxOfRmSrcRom */
typedef uint8 PduR_RmDestRomStartIdxOfRmSrcRomType;

/**   \brief  value based type definition for PduR_SrcHndOfRmSrcRom */
typedef uint8 PduR_SrcHndOfRmSrcRomType;

/**   \brief  value based type definition for PduR_TriggerTransmitSupportedOfRmSrcRom */
typedef boolean PduR_TriggerTransmitSupportedOfRmSrcRomType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfRxIf2Dest */
typedef uint8 PduR_PartitionIndexOfCslOfRxIf2DestType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfRxIf2Dest */
typedef uint8 PduR_RmSrcRomIdxOfRxIf2DestType;

/**   \brief  value based type definition for PduR_SizeOfDestApplicationManagerRom */
typedef uint8 PduR_SizeOfDestApplicationManagerRomType;

/**   \brief  value based type definition for PduR_SizeOfExclusiveAreaRom */
typedef uint8 PduR_SizeOfExclusiveAreaRomType;

/**   \brief  value based type definition for PduR_SizeOfGeneralPropertiesRom */
typedef uint8 PduR_SizeOfGeneralPropertiesRomType;

/**   \brief  value based type definition for PduR_SizeOfLockRom */
typedef uint8 PduR_SizeOfLockRomType;

/**   \brief  value based type definition for PduR_SizeOfMmRom */
typedef uint8 PduR_SizeOfMmRomType;

/**   \brief  value based type definition for PduR_SizeOfMmRomInd */
typedef uint8 PduR_SizeOfMmRomIndType;

/**   \brief  value based type definition for PduR_SizeOfPartitionIdentifiers */
typedef uint8 PduR_SizeOfPartitionIdentifiersType;

/**   \brief  value based type definition for PduR_SizeOfRmDestRom */
typedef uint8 PduR_SizeOfRmDestRomType;

/**   \brief  value based type definition for PduR_SizeOfRmGDestRom */
typedef uint8 PduR_SizeOfRmGDestRomType;

/**   \brief  value based type definition for PduR_SizeOfRmSrcRom */
typedef uint8 PduR_SizeOfRmSrcRomType;

/**   \brief  value based type definition for PduR_SizeOfRmTransmitFctPtr */
typedef uint8 PduR_SizeOfRmTransmitFctPtrType;

/**   \brief  value based type definition for PduR_SizeOfRxIf2Dest */
typedef uint8 PduR_SizeOfRxIf2DestType;

/**   \brief  value based type definition for PduR_SizeOfSrcApplicationRom */
typedef uint8 PduR_SizeOfSrcApplicationRomType;

/**   \brief  value based type definition for PduR_SizeOfTx2Lo */
typedef uint8 PduR_SizeOfTx2LoType;

/**   \brief  value based type definition for PduR_SizeOfTxIf2Up */
typedef uint8 PduR_SizeOfTxIf2UpType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfSrcApplicationRom */
typedef uint8 PduR_PartitionIndexOfCslOfSrcApplicationRomType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfTx2Lo */
typedef uint8 PduR_PartitionIndexOfCslOfTx2LoType;

/**   \brief  value based type definition for PduR_RmSrcRomIdxOfTx2Lo */
typedef uint8 PduR_RmSrcRomIdxOfTx2LoType;

/**   \brief  value based type definition for PduR_RmSrcRomUsedOfTx2Lo */
typedef boolean PduR_RmSrcRomUsedOfTx2LoType;

/**   \brief  value based type definition for PduR_RmTransmitFctPtrIdxOfTx2Lo */
typedef uint8 PduR_RmTransmitFctPtrIdxOfTx2LoType;

/**   \brief  value based type definition for PduR_PartitionIndexOfCslOfTxIf2Up */
typedef uint8 PduR_PartitionIndexOfCslOfTxIf2UpType;

/**   \brief  value based type definition for PduR_RmGDestRomIdxOfTxIf2Up */
typedef uint8 PduR_RmGDestRomIdxOfTxIf2UpType;

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_RmTransmitFctPtrType) (PduR_RmSrcRomIterType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */

/* Queue abstraction layer */
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_QAL_PutFctPtrType)          (PduR_RmGDestRomIterType, PduR_RmDestRomIterType, PduLengthType, SduDataPtrType);    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(Std_ReturnType, PDUR_APPL_CODE, PduR_QAL_GetFctPtrType)          (PduR_RmGDestRomIterType, P2VAR(PduR_RmDestRomIterType, AUTOMATIC, PDUR_APPL_DATA), P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void,           PDUR_APPL_CODE, PduR_QAL_RemoveFctPtrType)       (PduR_RmGDestRomIterType);    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(uint16,         PDUR_APPL_CODE, PduR_QAL_GetFillLevelFctPtrType) (PduR_RmGDestRomIterType);    /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void,           PDUR_APPL_CODE, PduR_QAL_FlushFctPtrType)        (PduR_RmGDestRomIterType);    /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef P2FUNC(void, PDUR_CODE, PduR_RmIf_TxConfirmation_StateHandler_FctPtrType) (PduR_RmGDestRomIterType);  /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void, PDUR_CODE, PduR_RmIf_FifoHandling_StateHandler_FctPtrType) (PduR_RmDestRomIterType, PduR_RmGDestRomIdxOfRmDestRomType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA));  /* PRQA S 1336 */ /* MD_PduR_1336 */

typedef uint8 PduR_MemIdxType;

#if(PDUR_SMDATAPLANEROM == STD_ON)
typedef uint8 PduR_FilterReturnType;
# define PDUR_FILTER_PASS  0u
# define PDUR_FILTER_BLOCK 1u

typedef uint32 PduR_SmSaType;
typedef uint32 PduR_SmTaType;

#define PDUR_SM_UNLEARNED_CONNECTION 0u
typedef P2FUNC(PduR_SmSaType, PDUR_CODE, PduR_Sm_LinearTaToSaCalculationStrategy_GetSaFctPtrType) (PduR_SmLinearTaToSaCalculationStrategyRomIterType, uint32, PduR_MemIdxType);  /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(void, PDUR_CODE, PduR_Sm_SrcFilterFctPtrType) (PduR_SmSrcRomIdxOfRmSrcRomType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduR_MemIdxType);  /* PRQA S 1336 */ /* MD_PduR_1336 */
typedef P2FUNC(PduR_FilterReturnType, PDUR_CODE, PduR_Sm_DestFilterFctPtrType) (PduR_SmGDestRomIdxOfRmGDestRomType, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA), PduR_MemIdxType);  /* PRQA S 1336 */ /* MD_PduR_1336 */
#endif

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/** 
  \defgroup  PduRPCStructTypes  PduR Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/ 
/**   \brief  type used in PduR_DestApplicationManagerRom */
typedef struct sPduR_DestApplicationManagerRomType
{
  uint8 PduR_DestApplicationManagerRomNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_DestApplicationManagerRomType;

/**   \brief  type used in PduR_ExclusiveAreaRom */
typedef struct sPduR_ExclusiveAreaRomType
{
  PduR_LockFunctionType LockOfExclusiveAreaRom;  /**< Lock function */
  PduR_LockFunctionType UnlockOfExclusiveAreaRom;  /**< Unlock function */
} PduR_ExclusiveAreaRomType;

/**   \brief  type used in PduR_GeneralPropertiesRom */
typedef struct sPduR_GeneralPropertiesRomType
{
  PduR_hasIfRoutingOfGeneralPropertiesRomType hasIfRoutingOfGeneralPropertiesRom;
} PduR_GeneralPropertiesRomType;

/**   \brief  type used in PduR_LockRom */
typedef struct sPduR_LockRomType
{
  uint8 PduR_LockRomNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_LockRomType;

/**   \brief  type used in PduR_MmRom */
typedef struct sPduR_MmRomType
{
  PduR_DestApplicationManagerRomIdxOfMmRomType DestApplicationManagerRomIdxOfMmRom;  /**< the index of the 1:1 relation pointing to PduR_DestApplicationManagerRom */
  PduR_MaskedBitsOfMmRomType MaskedBitsOfMmRom;  /**< contains bitcoded the boolean data of PduR_LoIfOfMmRom, PduR_RmGDestRomUsedOfMmRom, PduR_UpIfOfMmRom */
  PduR_IfRxIndicationType UpIfRxIndicationFctPtrOfMmRom;  /**< Upper layer communication interface Rx indication function pointers. */
  PduR_TransmitFctPtrType LoIfTransmitFctPtrOfMmRom;  /**< Lower layer If transmit function pointers */
  PduR_TriggerTransmitFctPtrType UpIfTriggerTransmitFctPtrOfMmRom;  /**< Upper layer trigger transmit function pointers */
} PduR_MmRomType;

/**   \brief  type used in PduR_PartitionIdentifiers */
typedef struct sPduR_PartitionIdentifiersType
{
  PduR_PartitionSNVOfPartitionIdentifiersType PartitionSNVOfPartitionIdentifiers;
} PduR_PartitionIdentifiersType;

/**   \brief  type used in PduR_RmDestRom */
typedef struct sPduR_RmDestRomType
{
  PduR_PduLengthHandlingStrategyOfRmDestRomType PduLengthHandlingStrategyOfRmDestRom;  /**< The strategy how larger than configured If Pdus are handled. */
} PduR_RmDestRomType;

/**   \brief  type used in PduR_RmGDestRom */
typedef struct sPduR_RmGDestRomType
{
  PduR_LockRomIdxOfRmGDestRomType LockRomIdxOfRmGDestRom;  /**< the index of the 1:1 relation pointing to PduR_LockRom */
} PduR_RmGDestRomType;

/**   \brief  type used in PduR_RmSrcRom */
typedef struct sPduR_RmSrcRomType
{
  PduR_MmRomIdxOfRmSrcRomType MmRomIdxOfRmSrcRom;  /**< the index of the 1:1 relation pointing to PduR_MmRom */
  PduR_PartitionIndexOfCslOfRmSrcRomType PartitionIndexOfCslOfRmSrcRom;
  PduR_SrcHndOfRmSrcRomType SrcHndOfRmSrcRom;  /**< handle to be used as parameter for the TxConfirmation or TriggerTransmit function call. */
} PduR_RmSrcRomType;

/**   \brief  type used in PduR_RxIf2Dest */
typedef struct sPduR_RxIf2DestType
{
  uint8 PduR_RxIf2DestNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_RxIf2DestType;

/**   \brief  type used in PduR_SrcApplicationRom */
typedef struct sPduR_SrcApplicationRomType
{
  uint8 PduR_SrcApplicationRomNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_SrcApplicationRomType;

/**   \brief  type used in PduR_Tx2Lo */
typedef struct sPduR_Tx2LoType
{
  uint8 PduR_Tx2LoNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_Tx2LoType;

/**   \brief  type used in PduR_TxIf2Up */
typedef struct sPduR_TxIf2UpType
{
  uint8 PduR_TxIf2UpNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_TxIf2UpType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCRootPointerTypes  PduR Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config root to symbol instances.
  \{
*/ 
/**   \brief  type used to point to PduR_DestApplicationManagerRom */
typedef P2CONST(PduR_DestApplicationManagerRomType, TYPEDEF, PDUR_CONST) PduR_DestApplicationManagerRomPtrType;

/**   \brief  type used to point to PduR_ExclusiveAreaRom */
typedef P2CONST(PduR_ExclusiveAreaRomType, TYPEDEF, PDUR_CONST) PduR_ExclusiveAreaRomPtrType;

/**   \brief  type used to point to PduR_GeneralPropertiesRom */
typedef P2CONST(PduR_GeneralPropertiesRomType, TYPEDEF, PDUR_CONST) PduR_GeneralPropertiesRomPtrType;

/**   \brief  type used to point to PduR_Initialized */
typedef P2VAR(PduR_InitializedType, TYPEDEF, PDUR_VAR_ZERO_INIT) PduR_InitializedPtrType;

/**   \brief  type used to point to PduR_LockRom */
typedef P2CONST(PduR_LockRomType, TYPEDEF, PDUR_CONST) PduR_LockRomPtrType;

/**   \brief  type used to point to PduR_MmRom */
typedef P2CONST(PduR_MmRomType, TYPEDEF, PDUR_CONST) PduR_MmRomPtrType;

/**   \brief  type used to point to PduR_MmRomInd */
typedef P2CONST(PduR_MmRomIndType, TYPEDEF, PDUR_CONST) PduR_MmRomIndPtrType;

/**   \brief  type used to point to PduR_PartitionIdentifiers */
typedef P2CONST(PduR_PartitionIdentifiersType, TYPEDEF, PDUR_CONST) PduR_PartitionIdentifiersPtrType;

/**   \brief  type used to point to PduR_RmDestRom */
typedef P2CONST(PduR_RmDestRomType, TYPEDEF, PDUR_CONST) PduR_RmDestRomPtrType;

/**   \brief  type used to point to PduR_RmGDestRom */
typedef P2CONST(PduR_RmGDestRomType, TYPEDEF, PDUR_CONST) PduR_RmGDestRomPtrType;

/**   \brief  type used to point to PduR_RmSrcRom */
typedef P2CONST(PduR_RmSrcRomType, TYPEDEF, PDUR_CONST) PduR_RmSrcRomPtrType;

/**   \brief  type used to point to PduR_RmTransmitFctPtr */
typedef P2CONST(PduR_RmTransmitFctPtrType, TYPEDEF, PDUR_CONST) PduR_RmTransmitFctPtrPtrType;

/**   \brief  type used to point to PduR_RxIf2Dest */
typedef P2CONST(PduR_RxIf2DestType, TYPEDEF, PDUR_CONST) PduR_RxIf2DestPtrType;

/**   \brief  type used to point to PduR_SrcApplicationRom */
typedef P2CONST(PduR_SrcApplicationRomType, TYPEDEF, PDUR_CONST) PduR_SrcApplicationRomPtrType;

/**   \brief  type used to point to PduR_Tx2Lo */
typedef P2CONST(PduR_Tx2LoType, TYPEDEF, PDUR_CONST) PduR_Tx2LoPtrType;

/**   \brief  type used to point to PduR_TxIf2Up */
typedef P2CONST(PduR_TxIf2UpType, TYPEDEF, PDUR_CONST) PduR_TxIf2UpPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCPartitionRootPointer  PduR Partition Root Pointer (PRE_COMPILE)
  \brief  This type definitions are used for partition specific instance.
  \{
*/ 
/**   \brief  type used in PduR_PCPartitionConfig */
typedef struct sPduR_PCPartitionConfigType
{
  PduR_InitializedPtrType InitializedOfPCPartitionConfig;  /**< the pointer to PduR_Initialized */
} PduR_PCPartitionConfigType;

/**   \brief  type used to point to PduR_PCPartitionConfig */
typedef P2CONST(PduR_PCPartitionConfigType, TYPEDEF, PDUR_CONST) PduR_PCPartitionConfigPtrType;

/** 
  \}
*/ 

/** 
  \defgroup  PduRPCRootValueTypes  PduR Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/ 
/**   \brief  type used in PduR_PCConfig */
typedef struct sPduR_PCConfigType
{
  uint8 PduR_PCConfigNeverUsed;  /**< dummy entry for the structure in the configuration variant precompile which is not used by the code. */
} PduR_PCConfigType;

typedef PduR_PCConfigType PduR_PBConfigType;  /**< A structure type is present for data in each configuration class. This typedef redefines the probably different name to the specified one. */

/** 
  \}
*/ 


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
 * GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
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
extern CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1];
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
extern CONST(PduR_GeneralPropertiesRomType, PDUR_CONST) PduR_GeneralPropertiesRom[1];
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
extern CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[2];
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
extern CONST(PduR_PartitionIdentifiersType, PDUR_CONST) PduR_PartitionIdentifiers[1];
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
extern CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[2];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
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
extern CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[2];
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
extern CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[2];
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
extern CONST(PduR_RmTransmitFctPtrType, PDUR_CONST) PduR_RmTransmitFctPtr[1];
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
extern VAR(PduR_InitializedType, PDUR_VAR_ZERO_INIT) PduR_Initialized;
#define PDUR_STOP_SEC_VAR_ZERO_INIT_8BIT
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */

/**********************************************************************************************************************
  PduR_PCPartitionConfig
**********************************************************************************************************************/
/** 
  \var    PduR_PCPartitionConfig
  \details
  Element        Description
  Initialized    the pointer to PduR_Initialized
*/ 
#define PDUR_START_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */
extern CONST(PduR_PCPartitionConfigType, PDUR_CONST) PduR_PCPartitionConfig[1];
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
/*lint -save -esym(961, 19.1) */
#include "PduR_MemMap.h"  /* PRQA S 5087 */  /* MD_MSR_MemMap */
/*lint -restore */


/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/


#define PDUR_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#if(PDUR_USE_INIT_POINTER == STD_ON)
extern P2CONST(PduR_PBConfigType, PDUR_VAR_ZERO_INIT, PDUR_PBCFG) PduR_ConfigDataPtr;
#endif

#define PDUR_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

#define PDUR_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

extern VAR(boolean, PDUR_VAR_NOINIT) PduR_PreInitialized;

#define PDUR_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "PduR_MemMap.h"    /* PRQA S 5087 */        /* MD_MSR_MemMap */

/**********************************************************************************************************************
 * GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/

/**********************************************************************************************************************
  CONFIGURATION CLASS: LINK
  SECTION: GLOBAL FUNCTION PROTOTYPES
**********************************************************************************************************************/


/**********************************************************************************************************************
 * LOCAL GEN FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * LOCAL GEN FUNCTIONS
 *********************************************************************************************************************/

#endif  /* PDUR_LCFG_H */
/**********************************************************************************************************************
 * END OF FILE: PduR_Lcfg.h
 *********************************************************************************************************************/

