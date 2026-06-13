/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2021 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  EthIf_EthTrcv.h
 *        \brief  EthIf EthTrcv public API header
 *
 *      \details  Provides access to the public API of the sub-module EthTrcv of EthIf.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (ETHIF_ETHTRCV_H)
# define ETHIF_ETHTRCV_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

/*********************************************************************************************************
 * Predefined file includes based on \trace DSGN-EthIfDiag1975
 *********************************************************************************************************/
# include "EthIf_EthTrcv_Types.h"

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

# define ETHIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

# if ( ETHIF_WAKEUP_SUPPORT == STD_ON )
/**********************************************************************************************************************
 * EthIf_SetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Changes the wakeup mode of the related hardware driver
 *  \details        Function allows to change the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource  EcuM wakeup source
 *  \param[in]      WakeupMode    Wakeup mode to set
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393948, SPEC-2393863
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetTransceiverWakeupMode(
  EcuM_WakeupSourceType   WakeupSource,
  EthTrcv_WakeupModeType  WakeupMode);

/**********************************************************************************************************************
 * EthIf_GetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Retrieves the wakeup mode of the related hardware driver
 *  \details        Function allows to retrieve the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource   EcuM wakeup source
 *  \param[out]     WakeupModePtr  Pointer pointing to variable where the wakeup mode is stored to
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393950, SPEC-2393867
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTransceiverWakeupMode(
        EcuM_WakeupSourceType                               WakeupSource,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr);

/**********************************************************************************************************************
 * EthIf_CheckWakeup
 **********************************************************************************************************************/
/*! \brief          Initiates the wakeup check
 *  \details        Function allows to initiate the wakeup check of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      WakeupSource    EcuM wakeup source
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          SPEC-2393868, SPEC-2393871
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_CheckWakeup(
  EcuM_WakeupSourceType  WakeupSource);

/**********************************************************************************************************************
 * EthIf_VSetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Changes the wakeup mode of the related hardware drivers
 *  \details        Function allows to change the wakeup mode of the related hardware drivers by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      CtrlIdx     EthIf controller index
 *  \param[in]      WakeupMode  Wakeup mode to set
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VSetTransceiverWakeupMode(
  uint8                   CtrlIdx,
  EthTrcv_WakeupModeType  WakeupMode);

/**********************************************************************************************************************
 * EthIf_VGetTransceiverWakeupMode
 **********************************************************************************************************************/
/*! \brief          Retrieves the wakeup mode of the related hardware driver
 *  \details        Function allows to retrieve the wakeup mode of the related hardware driver by redirecting the call
 *                  depending on the passed EcuM wakeup source.
 *  \param[in]      CtrlIdx        EthIf controller index
 *  \param[out]     WakeupModePtr  Pointer pointing to variable where the wakeup mode is stored to
 *  \return         E_OK - success
 *  \return         E_NOT_OK - function has been called with invalid parameters
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_VGetTransceiverWakeupMode(
        uint8                                               CtrlIdx,
  P2VAR(EthTrcv_WakeupModeType, AUTOMATIC, ETHIF_APPL_VAR)  WakeupModePtr);

/**********************************************************************************************************************
 * EthIf_VCheckWakeup
 **********************************************************************************************************************/
/*! \brief          Initiates the wakeup check
 *  \details        Function allows to initiate the wakeup check of the related hardware drivers by redirecting the call
 *                  depending on the passed EthIf controller index.
 *  \param[in]      CtrlIdx  EthIf controller index
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \config         ETHIF_WAKEUP_SUPPORT
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_VCheckWakeup(
  uint8  CtrlIdx);

# endif /* ETHIF_WAKEUP_SUPPORT */

/**********************************************************************************************************************
 * EthIf_SetPhyTxMode
 **********************************************************************************************************************/
/*! \brief          Activates a given transmission mode of the related hardware driver
 *  \details        Function allows to activate a given transmission mode of the related hardware driver by redirecting
 *                  the call depending on the passed transceiver index.
 *  \param[in]      TrcvIdx  Index of the transceiver within the context of the Ethernet Interface.
 *  \param[in]      Mode     Transmission mode to be activated.
 *  \return         E_OK - The request has been accepted
 *  \return         E_NOT_OK - The request has not been accepted
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2954402
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetPhyTxMode(
  uint8                  TrcvIdx,
  EthTrcv_PhyTxModeType  Mode);

/**********************************************************************************************************************
 * EthIf_GetCableDiagnosticsResult
 **********************************************************************************************************************/
/*! \brief          Retrieves the cable diagnostics result of a given transceiver.
 *  \details        Function allows to retrieve the cable diagnostics result of the related hardware driver by
 *                  redirecting the call depending on the passed transceiver index.
 *  \param[in]      TrcvIdx    Index of the transceiver within the context of the Ethernet Interface.
 *  \param[out]     ResultPtr  Pointer to the location where the cable diagnostics result shall be stored.
 *  \return         E_OK - The request has been accepted
 *  \return         E_NOT_OK - The request has not been accepted
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2954406
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetCableDiagnosticsResult (
        uint8                                                    TrcvIdx,
  P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHIF_APPL_VAR)  ResultPtr);

/**********************************************************************************************************************
 * EthIf_SetPhyTestMode
 **********************************************************************************************************************/
/*! \brief          Activates a given test mode of the related hardware driver
 *  \details        Function allows to activate a given test mode of the related hardware driver by redirecting
 *                  the call depending on the passed transceiver index.
 *  \param[in]      TrcvIdx  Index of the transceiver within the context of the Ethernet Interface.
 *  \param[in]      Mode     Test mode to be activated.
 *  \return         E_OK - The request has been accepted
 *  \return         E_NOT_OK - The request has not been accepted
 *  \pre            -
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-2954394
 *  \trace          DSGN-EthIf22934
 **********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_SetPhyTestMode(
  uint8                    TrcvIdx,
  EthTrcv_PhyTestModeType  Mode);

# if ( ETHIF_ENABLE_SIGNAL_QUALITY_API == STD_ON )
/**********************************************************************************************************************
*  EthIf_GetTrcvSignalQuality
*********************************************************************************************************************/
/*! \brief          Retrieves the signal quality of the link of the given Ethernet transceiver and update the   
 *                  measured signal quality stored in EthIf.
 *  \details        Function allows to retrieve the signal quality of the link of the given Ethernet transceiver by  
 *                  redirecting the call depending on the passed transceiver index. The highest signal quality and  
 *                  the lowest signal quality will be updated depending on the currently retrieved signal quality. 
 *                  Function is reentrant for different TrcvIdx and non reentrant for the same TrcvIdx.  
 *  \param[in]      TrcvIdx      Index of the transceiver within the context of the Ethernet Interface
 *  \param[out]     ResultPtr    Pointer to the memory where the signal quality in percent shall be stored
 *  \return         E_OK - success
 *  \return         E_NOT_OK - The signal quality not retrieved successfully
 *  \pre            EthIf is initialized
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-8002637
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_GetTrcvSignalQuality(
        uint8 TrcvIdx,
  P2VAR(EthIf_SignalQualityResultType, AUTOMATIC, ETHIF_APPL_VAR) ResultPtr);

/**********************************************************************************************************************
*  EthIf_ClearTrcvSignalQuality
*********************************************************************************************************************/
/*! \brief          Clear the stored signal quality of the link of the given Ethernet transceiver.
 *  \details        Function clears in Ethernet interface stored signal quality of the link of the given Ethernet 
 *                  transceiver. Function is reentrant for different TrcvIdx and non reentrant for the same TrcvIdx.
 *  \param[in]      TrcvIdx      Index of the transceiver within the context of the Ethernet Interface
 *  \return         E_OK - success
 *  \return         E_NOT_OK - The signal quality not cleared successfully
 *  \pre            EthIf is initialized
 *  \context        ANY
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \trace          SPEC-8002647
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ETHIF_CODE) EthIf_ClearTrcvSignalQuality(
  uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthIf_PollTrcvSignalQualities
 *********************************************************************************************************************/
/*! \brief          Poll the signal quality of Ethernet transceivers
 *  \details        This function polls the signal quality of the Ethernet transceivers by utilizing the respective
 *                  hardware driver.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_PollTrcvSignalQualities( void );

/**********************************************************************************************************************
 *  EthIf_TrcvSignalQualityList_Init
 *********************************************************************************************************************/
/*! \brief          Initialization of the signal quality of all transceivers
 *  \details        Initialization of the signal quality of all transceivers. The values of the signal qualities are
 *                  stored in the Ethernet interface as a list. The index of the list is the transceiver index within
 *                  the context of Ethernet interface.
 *  \pre            -
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    FALSE
 *********************************************************************************************************************/
FUNC(void, ETHIF_CODE) EthIf_TrcvSignalQualityList_Init( void );
# endif /* ETHIF_ENABLE_SIGNAL_QUALITY_API */

# define ETHIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */  /* MD_MSR_MemMap */

#endif /* ETHIF_ETHTRCV_H */

/**********************************************************************************************************************
 *  END OF FILE: EthIf_EthTrcv.h
 *********************************************************************************************************************/

