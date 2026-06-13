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
/*!        \file  EthTSyn_Pdelay_Int.h
 *        \brief  EthTSyn Path Delay internal header file
 *      \details  Contains internal definitions and declarations used by EthTSyn (Path Delay) only
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

#if !defined(ETHTSYN_PDELAY_INT_H)
# define ETHTSYN_PDELAY_INT_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTSyn_Util_Int.h"

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

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Pdelay sub-module
 *  \details    Initializes all component variables directly related to the Pdelay sub module.
 *  \pre        -
 *  \context    TAKS|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_Init(void);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_Init
 *********************************************************************************************************************/
/*! \brief      Initializes the Pdelay of the passed port.
 *  \details    Initializes all component variables directly related to the Pdelay of the passed port, if the passed
 *              port is an active Pdelay port.
 *  \param[in]  PortIdx  Index of the Port
 *                       [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_InitPdelayOfPort(
  EthTSyn_PortIterType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_GetCurrentPdelay
 *********************************************************************************************************************/
/*! \brief      Gets the current Pdelay of the passed port.
 *  \details    Checks if Pdelay is used for the given port and returns its current value.
 *  \param[in]  PortIdx    Index of the port the Pdelay is requested for
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \return     0 - Pdelay could not be retrieved or is currently 0
 *  \return     other values - The current value of Pdelay in nanoseconds
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE
 *********************************************************************************************************************/
FUNC(EthTSyn_PdelayType, ETHTSYN_CODE) EthTSyn_Pdelay_GetCurrentPdelay(
  EthTSyn_IntPortIdxType PortIdx);

# if ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) )
/**********************************************************************************************************************
 *  EthTSyn_Pdelay_HandleCyclicTasks
 *********************************************************************************************************************/
/*! \brief      Handles cyclic Pdelay tasks.
 *  \details    -
 *  \pre        -
 *  \context    TASK
 *  \reentrant  FALSE
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_HandleCyclicTasks(void);
# endif /* ( (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) || (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) ) */

# if (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY INITIATOR
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdReq
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the Path Delay Request state-machine for the passed Port.
 *  \details    -
 *  \param[in]  PortIdx     Index of the Port which state-machine should be processed
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        The Port referenced by PortIdx has to be a valid active pdelay port with activated pdelay initiator:
 *              EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *              EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *              EthTSyn_IsPdelayInitiatorUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdReq(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Pdelay response message.
 *  \details    -
 *  \param[in]  MsgPtr            Pointer to the message
 *  \param[in]  IngressTsMgmtPtr  The ingress timestamp and its state
 *  \param[in]  PortIdx           Index of the Port the message was received on
 *                                [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespMsg(
  ETHTSYN_P2CONST(uint8)                    MsgPtr,
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
                  EthTSyn_IntPortIdxType    PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdRespFupMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Pdelay response FollowUp message.
 *  \details    -
 *  \param[in]  MsgPtr      Pointer to the message
 *  \param[in]  PortIdx     Index of the Port the message was received on
 *                          [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdRespFupMsg(
  ETHTSYN_P2CONST(uint8)                  MsgPtr,
                  EthTSyn_IntPortIdxType  PortIdx);

/**********************************************************************************************************************
 *  END: PDELAY INITIATOR
 *********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_INITIATOR_SUPPORT == STD_ON) */

# if (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON)
/**********************************************************************************************************************
 *  PDELAY RESPONDER
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcSmPdResp
 *********************************************************************************************************************/
/*! \brief      Handles the processing of the given Path Delay Response state-machine.
 *  \details    -
 *  \param[in]  PortIdx    Index of the Port the state machine should be processed for
 *                         [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        The Port referenced by PortIdx has to be a valid active pdelay port with activated pdelay responder:
 *              EthTSyn_IsPdelayConfigUsedOfPort() == TRUE &&
 *              EthTSyn_GetPortIdxOfPdelayConfig() == PortIdx &&
 *              EthTSyn_IsPdelayResponderUsedOfPdelayConfig() == TRUE
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcSmPdResp(
  EthTSyn_IntPortIdxType PortIdx);

/**********************************************************************************************************************
 *  EthTSyn_Pdelay_ProcRcvdReqMsg
 *********************************************************************************************************************/
/*! \brief      Processing of a received Pdelay request message.
 *  \details    -
 *  \param[in]  RxBufPtr          Pointer to the Ethernet reception buffer of the received Pdelay_Req message
 *  \param[in]  IngressTsMgmtPtr  The ingress timestamp and its state
 *  \param[in]  PortIdx           Index of the Port the message was received on
 *                                [range: PortIdx < EthTSyn_GetSizeOfPort()]
 *  \pre        -
 *  \context    TASK|ISR2
 *  \reentrant  TRUE for different Port indices
 *********************************************************************************************************************/
FUNC(void, ETHTSYN_CODE) EthTSyn_Pdelay_ProcRcvdReqMsg(
  ETHTSYN_P2CONST(uint8)                    RxBufPtr,
  ETHTSYN_P2CONST(EthTSyn_TsMgmtStructType) IngressTsMgmtPtr,
                  EthTSyn_IntPortIdxType    PortIdx);

/**********************************************************************************************************************
 *  END: PDELAY RESPONDER
 *********************************************************************************************************************/
# endif /* (ETHTSYN_PDELAY_RESPONDER_SUPPORT == STD_ON) */

# define ETHTSYN_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHTSYN_PDELAY_INT_H */

/**********************************************************************************************************************
 *  END OF FILE: EthTSyn_Pdelay_Int.h
 *********************************************************************************************************************/
