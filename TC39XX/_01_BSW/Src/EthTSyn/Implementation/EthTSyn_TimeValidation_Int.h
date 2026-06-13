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
/*!        \file  EthTSyn_TimeValidation_Int.h
 *        \brief  EthTSyn TimeValidation internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn
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

#if !defined(ETHTSYN_TIME_VALIDATION_INT_H)
# define ETHTSYN_TIME_VALIDATION_INT_H

/* PRQA S 3219 EOF */ /* MD_MSR_Unreachable */

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Types_Int.h"

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

# define ETHTSYN_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_Init
 *********************************************************************************************************************/
/*! \brief          Initializes the time validation unit
 *  \details        Initializes all component variables directly related to the time validation unit
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MainFunction
 *********************************************************************************************************************/
/*! \brief          Processes cyclic tasks of the time validation unit
 *  \details        -
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MainFunction(void);
# endif /* ( (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) || (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) ) */

/**********************************************************************************************************************
 * MASTER DATA REPORTING
 *********************************************************************************************************************/
# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterStartCycle
 *********************************************************************************************************************/
/*! \brief          Starts a new Master sync cycle.
 *  \details        Reports the 'old' Master sync cycle data to the StbM, in case all required information are
 *                  available. Starts a new Master sync cycle afterwards.
 *  \param[in]      PortIdx     Index of the EthTSyn port the new master sync cycle shall be started on
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      SequenceId  The sequence id of the new master sync cycle
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterProvideSyncEgressTs
 *********************************************************************************************************************/
 /*! \brief          Provides the sync egress timestamp of a transmitted sync message to the time validation unit
  *  \details        -
  *  \param[in]      PortIdx        Index of the EthTSyn port
  *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
  *  \param[in]      SyncEgressVlt  The egress timestamp of the transmitted sync message as internal virtual local time
  *  \pre            -
  *  \context        TASK|ISR2
  *  \reentrant      FALSE
  *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterProvideSyncEgressTs(
  EthTSyn_IntPortIdxType PortIdx,
  EthTSyn_IntVltType     SyncEgressVlt);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterProvideFupData
 *********************************************************************************************************************/
/*! \brief          Provides all required master data to the time validation unit
 *  \details        -
 *  \param[in]      PortIdx        Index of the EthTSyn port
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      PotPtr         The precise origin timestamp transmitted in the FollowUp message
 *  \param[in]      CorrField      The value of the correction field transmitted in the FollowUp message
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterProvideFupData(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PotPtr,
                  sint64                       CorrField);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_MasterFollowUpSent
 *********************************************************************************************************************/
/*! \brief          Informs the time validation unit about the successful transmission of the FollowUp message
 *  \details        -
 *  \param[in]      PortIdx        Index of the EthTSyn port
 *                                 [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_MasterFollowUpSent(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * SLAVE DATA REPORTING
 *********************************************************************************************************************/
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveStartCycle
 *********************************************************************************************************************/
/*! \brief          Starts a new Slave sync cycle.
 *  \details        Reports the 'old' Slave sync cycle data to the StbM, in case all required information are
 *                  available. Starts a new Slave sync cycle afterwards.
 *  \param[in]      PortIdx     Index of the EthTSyn port the new slave sync cycle shall be started on
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      SequenceId  The sequence id of the new slave sync cycle
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideSyncIngressData
 *********************************************************************************************************************/
/*! \brief          Provides the required slave data of a received Sync message to the time validation unit
 *  \details        -
 *  \param[in]      PortIdx         Index of the EthTSyn port
 *                                  [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      SrcPortIdPtr    The source port identity of the master received with the sync message
 *  \param[in]      SyncIngressVlt  The ingress timestamp of the received sync message as internal virtual local time
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideSyncIngressData(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) SrcPortIdPtr,
                  EthTSyn_IntVltType        SyncIngressVlt);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideFollowUpData
 *********************************************************************************************************************/
/*! \brief          Provides the required slave data of a received FollowUp message to the time validation unit
 *  \details        -
 *  \param[in]      PortIdx    Index of the EthTSyn port
 *                             [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      PotPtr     The precise origin timestamp received with the FollowUp message
 *  \param[in]      CorrField  The value of the correction field received with the FollowUp message
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideFollowUpData(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PotPtr,
                  sint64                       CorrField);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveProvideCurrPdelay
 *********************************************************************************************************************/
/*! \brief          Provides the current Pdelay of the slave port to the time validation unit
 *  \details        -
 *  \param[in]      PortIdx     Index of the EthTSyn port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      CurrPdelay  The current Pdelay
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *  \note           CurrPdelay has to be the Pdelay provided to the StbM via StbM_BusSetGlobalTime()
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveProvideCurrPdelay(
  EthTSyn_IntPortIdxType PortIdx,
  EthTSyn_PdelayType     CurrPdelay);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled
 *********************************************************************************************************************/
/*! \brief          Informs the time validation unit about invocation of the StbM_BusSetGlobalTime() API
 *  \details        -
 *  \param[in]      PortIdx  Index of the EthTSyn port
 *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_SlaveBusSetGlobalTimeCalled(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY INITIATOR DATA REPORTING
 *********************************************************************************************************************/
# if (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqStartCycle
 *********************************************************************************************************************/
/*! \brief          Starts a new Pdelay measurement cycle as initiator
 *  \details        Reports the 'old' Pdelay cycle data to the StbM, in case all required information are
 *                  available. Starts a new Pdelay measurement cycle afterwards.
 *  \param[in]      PortIdx     Index of the EthTSyn port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      SequenceId  The sequence id of the new Pdelay cycle
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqTakeRefTimes
 *********************************************************************************************************************/
/*! \brief          Triggers the time validation unit to retrieve and store the Pdelay initiator reference time tuple
 *  \details        -
 *  \param[in]      PortIdx  Index of the EthTSyn port
 *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqTakeRefTimes(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdReqCopyDataFromSm
 *********************************************************************************************************************/
/*! \brief          Copies required Pdelay initiator information from the pdelay request state machine for later
 *                  reporting to the StbM.
 *  \details        -
 *  \param[in]      PortIdx     Index of the EthTSyn port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      PdReqSmPtr  The pdelay request state machine
 *  \param[in]      CurrPdelay  The current valid path delay value
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdReqCopyDataFromSm(
                  EthTSyn_IntPortIdxType   PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PdelayReqSmType) PdReqSmPtr,
                  uint32                   CurrPdelay);
# endif /* (ETHTSYN_SLAVE_TIME_VALIDATION_SUPPORT == STD_ON) */

/**********************************************************************************************************************
 * PDELAY RESPONDER DATA REPORTING
 *********************************************************************************************************************/
# if (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespStartCycle
 *********************************************************************************************************************/
/*! \brief          Starts a new Pdelay measurement cycle as responder
 *  \details        Reports the 'old' Pdelay cycle data to the StbM, in case all required information are
 *                  available. Starts a new Pdelay measurement cycle afterwards.
 *  \param[in]      PortIdx     Index of the EthTSyn port
 *                              [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      SequenceId  The sequence id of the new Pdelay cycle
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespStartCycle(
  EthTSyn_IntPortIdxType PortIdx,
  uint16                 SequenceId);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespTakeRefTimes
 *********************************************************************************************************************/
/*! \brief          Triggers the time validation unit to retrieve and store the Pdelay responder reference time tuple
 *  \details        -
 *  \param[in]      PortIdx  Index of the EthTSyn port
 *                           [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespTakeRefTimes(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespProvidePdReqData
 *********************************************************************************************************************/
/*! \brief          Provides all required data of a received Pdelay_Req message
 *  \details        -
 *  \param[in]      PortIdx          Index of the EthTSyn port
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      PdReqPortIdPtr   The port identity of the Pdelay initiator received with the Pdelay_Req
 *  \param[in]      PdReqIngressVlt  The ingress timestamp of the received Pdelay_Req as internal virtual local time
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespProvidePdReqData(
                  EthTSyn_IntPortIdxType    PortIdx,
  ETHTSYN_P2CONST(EthTSyn_PortIdentityType) PdReqPortIdPtr,
                  EthTSyn_IntVltType        PdReqIngressVlt);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespProvidePdRespEgressTs
 *********************************************************************************************************************/
/*! \brief          Provides the Pdelay_Resp egress timestamp
 *  \details        -
 *  \param[in]      PortIdx            Index of the EthTSyn port
 *                                     [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \param[in]      PdRespEgressTsPtr  The Pdelay_Resp egress timestamp
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespProvidePdRespEgressTs(
                  EthTSyn_IntPortIdxType       PortIdx,
  ETHTSYN_P2CONST(EthTSyn_GlobalTimestampType) PdRespEgressTsPtr);

/**********************************************************************************************************************
 *  EthTSyn_TimeValid_PdRespPdRespFupSent
 *********************************************************************************************************************/
/*! \brief          Informs the time validation unit about the successful transmission of the Pdelay_Resp_Fup
 *  \details        -
 *  \param[in]      PortIdx          Index of the EthTSyn port
 *                                   [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre            -
 *  \context        TASK|ISR2
 *  \reentrant      FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_TimeValid_PdRespPdRespFupSent(
  EthTSyn_IntPortIdxType PortIdx);
# endif /* (ETHTSYN_MASTER_TIME_VALIDATION_SUPPORT == STD_ON) */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHTSYN_TIME_VALIDATION_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_TimeValidation_Int.h
 *********************************************************************************************************************/
