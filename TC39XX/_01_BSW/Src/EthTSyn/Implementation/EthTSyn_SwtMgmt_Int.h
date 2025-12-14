/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthTSyn_SwtMgmt_Int.h
 *        \brief  EthTSyn Switch Management internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn (for Switch Management) only
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined(ETHTSYN_SWT_MGMT_INT_H)
# define ETHTSYN_SWT_MGMT_INT_H


/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Types.h"

# if (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#  define ETHTSYN_START_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Init
 *********************************************************************************************************************/
/*! \brief        Initializes the EthTSyn switch management parts.
 *  \details      Initializes all component variables directly related to the SwtMgmt sub-module.
 *  \pre          EthTSyn_Slave_Init() was called
 *  \context      TASK|ISR2
 *  \reentrant    TRUE
 *  \note         This function must be called before using the module
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj
 *********************************************************************************************************************/
/*! \brief          Marks all pending switch management objects of the passed EthTSyn controller as to be released.
 *  \details        -
 *  \param[in]      EthTSynCtrlIdx   Index of the EthTSyn controller
 *                  [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *  \note           In case a 'LINK_DOWN' is reported while some switch management objects are used by the EthTSyn,
 *                  these switch management objects have to be released by the EthTSyn when ownership changes to
 *                  ETHSWT_MGMT_OBJ_OWNED_BY_UPPER_LAYER
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_ReleasePendingSwtMgmtObj(
  EthTSyn_IntCtrlIdxType EthTSynCtrlIdx);

/**********************************************************************************************************************
 *  RX
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Rx_HndlMsgReception
 *********************************************************************************************************************/
/*! \brief        Processing of received EthTSyn frames on an EthTSyn Bridge Port.
 *  \details      By this API service the EthTSyn Switch management gets an indication and the data of a received frame.
 *                The Service is called by the main RxIndication of the EthTSyn module.
 *  \param[in]    DataPtr               Pointer to payload of the received Ethernet frame
 *                                      (i.e. Ethernet header is not provided)
 *  \param[in]    LenByte               Length of received data
 *  \param[in]    EthTSynCtrlIdx        Index of the EthTSyn controller
 *                                      [range: EthTSynCtrlIdx < EthTSyn_GetSizeOfCtrl()]
 *  \param[in]    IngressIntVltMgmtPtr  The ingress timestamp of the Host controller as internal virtual local time
 *                                      and its validity info
 *  \return       ETHTSYN_E_NO_ERROR - Message was received and stored in an EthTSyn message buffer
 *  \return       other values - Message could not be received. Corresponding error id is returned
 *  \pre          -
 *  \context      TAKSE|ISR2
 *  \reentrant    TRUE for different EthTSynCtrl indices
 *  \note         This RxIndication function is wrapped by the main EthTSyn_RxIndication. Thats why the parameters
 *                differ from the regular RxIndication
 *********************************************************************************************************************/
FUNC(uint8, ETHTSYN_CODE) EthTSyn_SwtMgmt_Rx_HndlMsgReception(
  ETHTSYN_P2CONST(uint8)                  DataPtr,
                  uint16                  LenByte,
                  EthTSyn_IntCtrlIdxType  EthTSynCtrlIdx,
  ETHTSYN_P2CONST(EthTSyn_IntVltMgmtType) IngressIntVltMgmtPtr);

/**********************************************************************************************************************
 *  TX
 *********************************************************************************************************************/
#  if (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj
 *********************************************************************************************************************/
/*! \brief          Sets up a new TxMgmtObject
 *  \details        Gets and locks a free EthTSyn TxMgmtObject as well as a switch TxMgmtObject via
 *                  EthIf_GetTxMgmtObject(). Links the switch TxMgmtObject and the passed state machine timestamps
 *                  to the EthTSyn TxMgmtObject.
 *  \param[in]      EthIfCtrlIdx      Index of the EthIf controller
 *  \param[in]      BufIdx            Index of the Ethernet Tx buffer
 *  \param[in]      IngressTsMgmtPtr  Pointer to the ingress timestamp management of the state machine. NULL_PTR in
 *                                    case ingress timestamp is not required.
 *  \param[in]      EgressTsMgmtPtr   Pointer to the egress timestamp management of the state machine. NULL_PTR in
 *                                    case egress timestamp is not required.
 *  \pre            Has to be called in the context of the EthTSyn_TxConfirmation().
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_Tx_SetupTxMgmtObj(
                uint8                     EthIfCtrlIdx,
                uint8                     BufIdx,
  ETHTSYN_P2VAR(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
  ETHTSYN_P2VAR(EthTSyn_TsMgmtStructType) EgressTsMgmtPtr);
#  endif /* (ETHTSYN_SWT_MGMT_SWT_TIMESTAMP_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 *  SITE SYNC SYNC STATE MACHINE
 *********************************************************************************************************************/
#  if (ETHTSYN_SITESYNCSYNCSM == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_ProcSm
 *********************************************************************************************************************/
/*! \brief      Processing of the Site Sync Sync state-machine.
 *  \details    -
 *  \param[in]  TimeDomainIdx    Index of the TimeDomain that should be processed
 *                               [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_ProcSm(
  EthTSyn_TimeDomainIterType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout
 *********************************************************************************************************************/
/*! \brief      Handles a detected sync timeout.
 *  \details    -
 *  \param[in]  TimeDomainIdx   Index of the TimeDomain the SiteSyncSync state machine is processed for
 *                              [range: TimeDomainIdx < EthTSyn_GetSizeOfTimeDomain()]
 *  \pre        EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(TimeDomainIdx) == TRUE
 *  \pre        Interrupts are disabled
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different TimeDomain indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_HndlSyncTimeout(
  EthTSyn_IntTimeDomainIdxType TimeDomainIdx);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CpySync
 *********************************************************************************************************************/
 /*! \brief       Copies the Sync message from the SiteSyncSync state machine to the provided TxBuffer.
  *  \details     -
  *  \param[in]   PortIdx     Index of the Port the Sync message should be transmitted on
  *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
  *  \param[out]  BufferPtr   Pointer to the Ethernet Tx-Buffer. The Sync message will be copied here
  *  \pre         EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(PortIdx)) == TRUE
  *  \context     TASK|ISR2
  *  \reentrant   TRUE
  *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CpySync(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           BufferPtr);

/**********************************************************************************************************************
 *  EthTSyn_SwtMgmt_SiteSyncSync_CpyFup
 *********************************************************************************************************************/
 /*! \brief       Copies the FollowUp message from the SiteSyncSync state machine to the provided TxBuffer.
  *  \details     -
  *  \param[in]   PortIdx     Index of the Port the FollowUp message should be transmitted on
  *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
  *  \param[out]  BufferPtr   Pointer to the Ethernet Tx-Buffer. The FollowUp message will be copied here
  *  \param[in]   LenByte     Length of the FollowUp message in Byte.
  *  \pre         EthTSyn_IsSiteSyncSyncSmUsedOfTimeDomain(EthTSyn_GetTimeDomainIdxOfPort(PortIdx)) == TRUE
  *  \context     TASK|ISR2
  *  \reentrant   TRUE
  *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_SwtMgmt_SiteSyncSync_CpyFup(
                EthTSyn_PortIdxOfMasterPortType  PortIdx,
  ETHTSYN_P2VAR(uint8)                           BufferPtr,
                uint16                           LenByte);
#  endif /* (ETHTSYN_SITESYNCSYNCSM == STD_ON) */

#  define ETHTSYN_STOP_SEC_CODE
#  include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# endif /* (ETHTSYN_SWT_MGMT_SUPPORT == STD_ON) */
#endif /* ETHTSYN_SWT_MGMT_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_SwtMgmt_Int.h
 *********************************************************************************************************************/
