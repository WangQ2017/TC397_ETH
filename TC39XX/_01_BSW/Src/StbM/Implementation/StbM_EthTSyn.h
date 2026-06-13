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
/*!        \file  StbM_EthTSyn.h
 *        \brief  Vector AUTOSAR EthTSyn-StbM header file
 *
 *      \details  This is the EthTSyn TimeValidation header file of the Vector AUTOSAR module StbM.

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

#if !defined (STBM_ETHTSYN_H)
# define STBM_ETHTSYN_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

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
# define STBM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

# if (STBM_CONFIG_TIME_VALIDATION_ETH_MASTER == STD_ON)
/**********************************************************************************************************************
 *  StbM_EthSetMasterTimingData
 *********************************************************************************************************************/
/*! \brief       Time Validation interface for Ethernet Timesync Master timing data.
 *  \details     Allows the EthSyn Module to forward Ethernet specific timing data to the StbM.
 *  \param[in]   timeBaseId              The synchronized time-base, whose timing data is set.
 *  \param[in]   measureDataPtr          Pointer to measureData.
 *  \return      E_OK     - successful forwarding of master timing data.
 *  \return      E_NOT_OK - error during data transition.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_VALIDATION_ETH_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetMasterTimingData(StbM_SynchronizedTimeBaseType timeBaseId,
        P2CONST(StbM_EthTimeMasterMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);

/**********************************************************************************************************************
 *  StbM_EthSetPDelayResponderData
 *********************************************************************************************************************/
/*! \brief       Time Validation interface for Ethernet Timesync Master pdelay data.
 *  \details     Allows the EthSyn Module to forward Ethernet specific timing data to the StbM.
 *  \param[in]   timeBaseId              The synchronized time-base, whose timing data is set.
 *  \param[in]   measureDataPtr          Pointer to measureData.
 *  \return      E_OK     - successful forwarding of pDelay responder data.
 *  \return      E_NOT_OK - error during data transition.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_VALIDATION_ETH_MASTER
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetPdelayResponderData(StbM_SynchronizedTimeBaseType timeBaseId,
        P2CONST(StbM_PdelayResponderMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);
# endif /* (STBM_CONFIG_TIME_VALIDATION_ETH_MASTER == STD_ON) */

# if (STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE == STD_ON)
/**********************************************************************************************************************
 *  StbM_EthSetSlaveTimingData
 *********************************************************************************************************************/
/*! \brief       Time Validation interface for Ethernet Timesync Slave timing data.
 *  \details     Allows the EthSyn Module to forward Ethernet specific timing data to the StbM.
 *  \param[in]   timeBaseId              The synchronized time-base, whose timing data is set.
 *  \param[in]   measureDataPtr          Pointer to measureData.
 *  \return      E_OK     - successful forwarding of slave timing data.
 *  \return      E_NOT_OK - error during data transition.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetSlaveTimingData(StbM_SynchronizedTimeBaseType timeBaseId,
        P2CONST(StbM_EthTimeSlaveMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);

/**********************************************************************************************************************
 *  StbM_EthSetPDelayInitiatorData
 *********************************************************************************************************************/
/*! \brief       Time Validation interface for Ethernet Timesync Slave pdelay data.
 *  \details     Allows the EthSyn Module to forward Ethernet specific timing data to the StbM.
 *  \param[in]   timeBaseId              The synchronized time-base, whose timing data is set.
 *  \param[in]   measureDataPtr          Pointer to measureData.
 *  \return      E_OK     - successful forwarding of pDelay initiator data.
 *  \return      E_NOT_OK - error during data transition.
 *  \pre         -
 *  \context     TASK|ISR2
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \config      STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE
 *********************************************************************************************************************/
FUNC(Std_ReturnType, STBM_CODE) StbM_EthSetPdelayInitiatorData(StbM_SynchronizedTimeBaseType timeBaseId,
        P2CONST(StbM_PdelayInitiatorMeasurementType, AUTOMATIC, STBM_APPL_DATA) measureDataPtr);
# endif /* (STBM_CONFIG_TIME_VALIDATION_ETH_SLAVE == STD_ON) */

# define STBM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* STBM_ETHTSYN_H */

/**********************************************************************************************************************
 *  END OF FILE: StbM_EthTSyn.h
 *********************************************************************************************************************/
