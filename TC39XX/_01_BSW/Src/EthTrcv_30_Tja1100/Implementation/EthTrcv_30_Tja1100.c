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
/*         \file  EthTrcv_30_Tja1100.c
 *        \brief  Source file containing the core implementation of the Ethernet transceiver driver
 *
 *      \details  The file EthTrcv_30_Tja1100.c is the source file which contains the hardware independent parts of
 *                the implementation of the Ethernet transceiver driver.
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
#define ETHTRCV_30_TJA1100_SOURCE
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "EthTrcv_30_Tja1100.h"
#include "EthTrcv_30_Tja1100_LL.h"
#include "EthTrcv_30_Tja1100_Wakeup_Int.h"
#include "EthTrcv_30_Tja1100_Wakeup_UsrIfc.h"
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* Check the version of the configuration header file */
#if (  (ETHTRCV_30_TJA1100_CFG_MAJOR_VERSION != (4u)) \
    || (ETHTRCV_30_TJA1100_CFG_MINOR_VERSION != (0u)) )
# error "Version numbers of EthTrcv_30_Tja1100.c and EthTrcv_30_Tja1100_Cfg.h are inconsistent!"
#endif
/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#if !defined(ETHTRCV_30_TJA1100_LOCAL)                                                                                  /* COV_ETHTRCV_COMPATIBILITY */
# define ETHTRCV_30_TJA1100_LOCAL                                     static
#endif

#if !defined(ETHTRCV_30_TJA1100_LOCAL_INLINE)                                                                           /* COV_ETHTRCV_COMPATIBILITY */
# define ETHTRCV_30_TJA1100_LOCAL_INLINE                              LOCAL_INLINE
#endif
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
#define ETHTRCV_30_TJA1100_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
VAR(EthTrcv_StateType, ETHTRCV_30_TJA1100_VAR_ZERO_INIT) EthTrcv_30_Tja1100_ModuleState = ETHTRCV_STATE_UNINIT;
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
#define ETHTRCV_30_TJA1100_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define ETHTRCV_30_TJA1100_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_TransceiverInit()
 ************** *******************************************************************************************************/
/*! \brief       Initializes an Ethernet transceiver (register configuration)
 *  \details     This function initializes the transceiver's registers to realize its functionality according to the
 *               configuration.
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.

 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_TransceiverInit(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ConfigureMiiInterface()
 ************** *******************************************************************************************************/
/*! \brief       Initializes an Ethernet transceiver (register configuration, Controller interface part)
 *  \details     This function initializes the transceiver's registers to realize its functionality according to the
 *               configuration. This part of the initialization is performing the Mii Interface configuration
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ConfigureMiiInterface(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_PerformSoftwareReset()
 ************** *******************************************************************************************************/
/*! \brief       Performs a software reseet
 *  \details     This function performs a software reset on the transceiver with index TrcvIdx if it is enabled
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_PerformSoftwareReset(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_EnableTransceiver()
 ************** *******************************************************************************************************/
/*! \brief       Enables the transceiver with index TrcvIdx
 *  \details     This function enables the transceiver hardware
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_EnableTransceiver(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_DisableTransceiver()
 ************** *******************************************************************************************************/
/*! \brief       Disables the transceiver with index TrcvIdx
 *  \details     This function disables the transceiver hardware
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_DisableTransceiver(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief       Sets the transceiver's mode
 *  \details     This function sets the transceiver to active or down. Note: Even if the transceiver is already in mode
 *               active, the link startup procedure is executed again which might result in a short period with no link
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TrcvMode   Transceiver mode to set:
 *                          ETHTRCV_MODE_DOWN - shut down the Ethernet transceiver
 *                          ETHTRCV_MODE_ACTIVE - activate the Ethernet transceiver
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetTransceiverMode(
    uint8 TrcvIdx,
    EthTrcv_ModeType TrcvMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's mode
 *  \details     This function returns the transceiver's current mode.
 *  \param[in]   TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]  TrcvModePtr  Pointer for retrieved transceiver mode:
 *                            ETHTRCV_MODE_DOWN - transceiver is turned off
 *                            ETHTRCV_MODE_ACTIVE - transceiver is active
 *  \return      E_OK       - success
 *  \return      E_NOT_OK   - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvModePtr);

#if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_StartAutoNegotiation()
 *********************************************************************************************************************/
/*! \brief       Starts automatic negotiation
 *  \details     This function starts the process to automatically negotiate the transceivers master-slave role,
 *               duplex mode and link speed, if available.
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_StartAutoNegotiation(
    uint8 TrcvIdx);
#endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetLinkState()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's link state
 *  \details     This function returns the transceiver's current link state
 *  \param[in]   TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                             minus one.
 *  \param[out]  LinkStatePtr  Pointer for the retrieved link state value:
 *                             ETHTRCV_LINK_STATE_DOWN - link is down
 *                             ETHTRCV_LINK_STATE_ACTIVE - link is up
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - Function has been called with invalid parameter or at least one of the hardware operations
 *                             (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) LinkStatePtr);

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetBaudRate()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's baud rate
 *  \details     This function returns the transceiver's current baud rate.
 *  \param[in]   TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]  BaudRatePtr  pointer for the retrieved baud rate value:
 *                            ETHTRCV_BAUD_RATE_10MBIT - Link speed is 10 Mbit/s
 *                            ETHTRCV_BAUD_RATE_100MBIT - Link speed is 100 Mbit/s
 *                            ETHTRCV_BAUD_RATE_1000MBIT - Link speed is 1000 Mbit/s
 *  \return      E_OK       - success
 *  \return      E_NOT_OK   - Function has been called with invalid parameter or at least one of the hardware operations
 *                            (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) BaudRatePtr);
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetDuplexMode()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's duplex mode
 *  \details     This function returns the transceiver's current duplex mode.
 *  \param[in]   TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                             minus one.
 *  \param[out]  DuplexModePtr Pointer for the retrieved duplex mode value:
 *                             ETHTRCV_DUPLEX_MODE_HALF - transceiver operates in half duplex mode
 *                             ETHTRCV_DUPLEX_MODE_FULL - transceiver operates in full duplex mode
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - Function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetDuplexMode(
  uint8 TrcvIdx,
  P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) DuplexModePtr);
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyTestMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy test mode
 *  \details     This function activates the given phy test mode
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TestMode   Test mode to be activated
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy loopback mode
 *  \details     This function activates the given phy loopback mode
 *  \param[in]   TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                             minus one.
 *  \param[in]   LoopbackMode  Loopback mode to be activated
 *  \return      E_OK        - success
 *  \return      E_NOT_OK    - Function has been called with invalid parameter or at least one of the hardware operations
 *                             (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetPhySignalQuality()
 *********************************************************************************************************************/
/*! \brief       Gets the signal quality
 *  \details     This function obtains the current signal quality of the link of the indexed transceiver
 *  \param[in]   TrcvIdx           Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                                 minus one.
 *  \param[out]  SignalQualityPtr  Pointer to the memory where the signal quality in percent shall be stored
 *  \return      E_OK            - success
 *  \return      E_NOT_OK        - Function has been called with invalid parameter or at least one of the hardware operations
 *                                 (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetPhySignalQuality(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) SignalQualityPtr);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyTxMode()
 *********************************************************************************************************************/
/*! \brief       Activates a given Tx Mode
 *  \details     This function activates the given transmission mode
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TxMode     Transmission mode to be activated
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult()
 *********************************************************************************************************************/
/*! \brief       Retrieves cable diagnostics result
 *  \details     This function retrieves the cable diagnostics result of a given transceiver
 *  \param[in]   TrcvIdx             Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                                   minus one.
 *  \param[out]  CableDiagResultPtr  Pointer to the memory where the cable diagnostic result shall be stored
 *  \return      E_OK              - success
 *  \return      E_NOT_OK          - Function has been called with invalid parameter or at least one of the hardware operations
 *                                   (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) CableDiagResultPtr);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetPhyIdentifier()
 *********************************************************************************************************************/
/*! \brief       Obtains PHY identifier
 *  \details     This function obtains the PHY identifier of the Ethernet Transceiver according to IEEE 802.3-2015 chapter
 *               22.2.4.3.1 PHY Identifier.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \param[out]  OrgUniqueIdPtr  Pointer to the memory where the Organizational Unique Identifier shall be stored
 *  \param[out]  ModelNrPtr      Pointer to the memory where the Manufacturer's Model Number shall be stored
 *  \param[out]  RevisionNrPtr   Pointer to the memory where the Revision Number shall be stored
 *  \return      E_OK          - success
 *  \return      E_NOT_OK      - Function has been called with invalid parameter or at least one of the hardware operations
 *                               (read/write) has failed.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetPhyIdentifier(
    uint8 TrcvIdx,
    P2VAR(uint32, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) OrgUniqueIdPtr,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) ModelNrPtr,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) RevisionNrPtr);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Performs the cyclic tasks of the Ethernet transceiver driver
 *  \details     -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_MainFunction( void );

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_HwAccessMonitor()
 *********************************************************************************************************************/
/*! \brief       Performs the hardware access monitor
 *  \details     -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_HwAccessMonitor( void );

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_HwAccessMonitorHandling()
 *********************************************************************************************************************/
/*! \brief       Performs the hardware access monitor handling
 *  \details     -
 *  \param[in]   TrcvIdx         Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_HwAccessMonitorHandling(
    uint8 TrcvIdx );

#if ( ETHTRCV_WAKEUP_BY_POLLING == ETHTRCV_30_TJA1100_WAKEUP_TYPE)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck()
 *********************************************************************************************************************/
/*! \brief       Performs the wake up reason check
 *  \details     -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck( void );
#endif

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling()
 *********************************************************************************************************************/
/*! \brief       Performs the cyclic tasks of the Ethernet transceiver driver concerning link handling
 *  \details     -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling( void );

#if ( ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     Returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfoPtr  Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137829
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetVersionInfo(
    P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) VersionInfoPtr);
#endif /* ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON */

/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION DEFINITIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_ConfigureMiiInterface
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ConfigureMiiInterface(
    uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_30_Tja1100_MiiModeOfEthTrcvType miiMode = EthTrcv_30_Tja1100_GetMiiModeOfEthTrcv(TrcvIdx);
  /* ----- Implementation ----------------------------------------------- */

    /* #10 Clear the current interface settings */
  retVal |= EthTrcv_30_Tja1100_LL_ClearMiiModeSettings(TrcvIdx, retVal);

  switch(miiMode)
  {
    /* #20 The MII mode shall be configured to Light MII */
    case ETHTRCV_30_TJA1100_LIGHT_MII_MODE_MIIMODEOFETHTRCV:
      /* #210 Call the hardware dependent function to configure the controller interface to Light MII mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToLightMiiMode(TrcvIdx, retVal); /*lint !e522 */
      break;
    /* #30 The MII mode shall be configured to RMII */
    case ETHTRCV_30_TJA1100_RMII_MODE_MIIMODEOFETHTRCV:
      /* #310 Call the hardware dependent function to configure the controller interface to RMII mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode(TrcvIdx, retVal); /*lint !e522 */
      break;
    /* #40 The MII mode shall be configured to RMII-XTAL */
    case ETHTRCV_30_TJA1100_RMII_XTAL_MODE_MIIMODEOFETHTRCV:
      /* #410 Call the hardware dependent function to configure the controller interface to RMII-XTAL mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiXtalMode(TrcvIdx, retVal); /*lint !e522 */
      break;
    /* #50 The MII mode shall be configured to GMII */
    case ETHTRCV_30_TJA1100_GMII_MODE_MIIMODEOFETHTRCV:
      /* #510 Call the hardware dependent function to configure the controller interface to GMII mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToGmiiMode(TrcvIdx, retVal); /*lint !e522 */
      break;
    /* #60 The MII mode shall be configured to RGMII */
    case ETHTRCV_30_TJA1100_RGMII_MODE_MIIMODEOFETHTRCV:
      /* #610 Call the hardware dependent function to configure the controller interface to RGMII mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiMode(TrcvIdx, retVal); /*lint !e522 */
      break;
    /* #70 The MII mode shall be configured to RGMII-XTAL */
    case ETHTRCV_30_TJA1100_RGMII_XTAL_MODE_MIIMODEOFETHTRCV:
      /* #710 Call the hardware dependent function to configure the controller interface to RGMII-XTAL mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiXtalMode(TrcvIdx, retVal); /*lint !e522 */
      break;
      /* #80 The MII mode shall be configured to normal MII */
    default:
      /* #810 Call the hardware dependent function to configure the controller interface to MII mode */
      retVal |= EthTrcv_30_Tja1100_LL_SetMiiInterfaceToMiiMode(TrcvIdx, retVal); /*lint !e522 */
      break;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_ConfigureMiiInterface() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_PerformSoftwareReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_PerformSoftwareReset(
    uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  /* ----- Implementation --------------------------------------------- */
  if(EthTrcv_30_Tja1100_IsSoftResetOnInitEnabledOfEthTrcv(TrcvIdx) == TRUE)
  {
    EthTrcv_30_Tja1100_SoftResetWaitCyclesOfEthTrcvType swResetCt;
    boolean isSwResetFinished;

    retVal |= EthTrcv_30_Tja1100_LL_PerformSwReset(TrcvIdx, retVal);

    swResetCt = 0;
    do
    {
      swResetCt++;
      retVal |= EthTrcv_30_Tja1100_LL_CheckSwReset(TrcvIdx, &isSwResetFinished, retVal);                                /* SBSW_ETHTRCV_REF_OF_STACK_VAR */
    }
    while ( (swResetCt < EthTrcv_30_Tja1100_GetSoftResetWaitCyclesOfEthTrcv(TrcvIdx)) &&
            (isSwResetFinished == FALSE) &&
            (retVal == E_OK));

    if ( isSwResetFinished == FALSE )
    {
      /* The software reset could not be finished */
      retVal = E_NOT_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  return retVal;
} /* EthTrcv_30_Tja1100_PerformSoftwareReset() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_EnableTransceiver
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_EnableTransceiver(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal = E_OK;
  /* #10 Set the transceiver mode to ACTIVE */
  retVal |= EthTrcv_30_Tja1100_LL_SetTransceiverModeActive(TrcvIdx, retVal);

  /* #20 If necessary Wait before the LINK_CONTROL bit is enabled */
  EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(TrcvIdx); /*lint !e522 */

  /* #30 If wakeup mode is configured and enabled, disable ICU notification */
#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
  if( EthTrcv_30_Tja1100_GetWakeupMode(TrcvIdx) == ETHTRCV_WUM_ENABLE )
  {
    EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType wakeupIdx = EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(TrcvIdx);
    EthTrcv_30_Tja1100_IcuChannelOfWakeupType icuChannel = EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(wakeupIdx);
    Icu_DisableNotification(EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(icuChannel));
  }
#endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */

  EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_ACTIVE);                                                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

  return retVal;
}

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_DisableTransceiver
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_DisableTransceiver(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal = E_OK;
  /* #10 Set the transceiver mode to DOWN */
  retVal |= EthTrcv_30_Tja1100_LL_SetTransceiverModeDown(TrcvIdx, retVal);

  /* #20 If wakeup mode is configured and enabled, enable ICU notification */
#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
  if( EthTrcv_30_Tja1100_GetWakeupMode(TrcvIdx) == ETHTRCV_WUM_ENABLE )
  {
    EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType wakeupIdx = EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(TrcvIdx);
    EthTrcv_30_Tja1100_IcuChannelOfWakeupType icuChannel = EthTrcv_30_Tja1100_GetIcuChannelOfWakeup(wakeupIdx);
    Icu_EnableNotification(icuChannel);
  }
#endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */

  EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_DOWN);                                                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

  return retVal;
}

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_TransceiverInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_TransceiverInit(
    uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_30_Tja1100_HwAccessLoopCountType loopCount;
  EthTrcv_30_Tja1100_MiiModeOfEthTrcvType miiMode;
  /* ----- Implementation --------------------------------------------- */

  /* #10 Perform user callouts before transceiver init */
  if(EthTrcv_30_Tja1100_GetPreInitUserCalloutOfUserInitCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX) != NULL_PTR)
  {
    EthTrcv_30_Tja1100_GetPreInitUserCalloutOfUserInitCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX)(TrcvIdx);           /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL01 */
  }
  /* #20 Perform wait until hardware reset is finished */
  for(loopCount = 0; loopCount < EthTrcv_30_Tja1100_GetHwAccessLoopCount(); loopCount++) /*lint !e522 */
  {
    if(EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk(TrcvIdx) == TRUE)
    {
      break;
    }
  }

  /* #30 The register value of the identifier register was plausible */
  if ( (EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk(TrcvIdx) == TRUE) ) /*lint !e522 */
  {
    /* #310 If necessary, perform a soft-reset */
    retVal |= EthTrcv_30_Tja1100_PerformSoftwareReset(TrcvIdx);

    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #320 Run vendor specific initialization script if available */
    EthTrcv_30_Tja1100_LL_RunVendorSpecificInitScripts(TrcvIdx); /*lint !e522 */

    /* #330 Enable the access to Transceiver Registers in order to perform the configuration of the device */
    retVal |= EthTrcv_30_Tja1100_LL_EnableConfigAccess(TrcvIdx, retVal); /*lint !e522 */

    /* #340 Write the generated basic control register value to the transceiver */
    retVal |= EthTrcv_30_Tja1100_LL_SetBasicConfigurationRegister(TrcvIdx, retVal);

    /* #350 Set the interface options between the Ethernet controller and transceiver */
    miiMode = EthTrcv_30_Tja1100_GetMiiModeOfEthTrcv(TrcvIdx);

    if(miiMode != ETHTRCV_30_TJA1100_DONT_CARE_MIIMODEOFETHTRCV)
    {
      retVal |= EthTrcv_30_Tja1100_ConfigureMiiInterface(TrcvIdx);
    }
    /* #360 Perform additional hardware dependent configuration steps */
    retVal |= EthTrcv_30_Tja1100_LL_ApplyAdditionalConfigSteps(TrcvIdx, retVal);

    /* #370 Set transceiver mode to down */
    retVal |= EthTrcv_30_Tja1100_LL_SetTransceiverModeDown(TrcvIdx, retVal);

    /* #380 Perform user callouts after transceiver init */
    if(EthTrcv_30_Tja1100_GetPostInitUserCalloutOfUserInitCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX) != NULL_PTR)
    {
      EthTrcv_30_Tja1100_GetPostInitUserCalloutOfUserInitCallouts(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX)(TrcvIdx);        /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL01 */
    }

    /* #390 Disable the configuration access */
    retVal |= EthTrcv_30_Tja1100_LL_DisableConfigAccess(TrcvIdx, retVal); /*lint !e522 */

    /* #400 Set the hardware accessibility to ACCESSIBILITY_OK */
    EthTrcv_30_Tja1100_SetTrcvHwAccessibility(TrcvIdx, ETHTRCV_30_TJA1100_ACCESSIBILITY_OK);                            /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* #40 The register value of the identifier register was not plausible */
  else
  {
    /* #410 DEM error because no access to transceiver */
    ETHTRCV_30_TJA1100_DEM_REPORT_ERROR_STATUS_ETHTRCV_E_ACCESS(TrcvIdx);

    /* #420 Set the hardware accessibility to ACCESSIBILITY_NOT_OK */
    EthTrcv_30_Tja1100_SetTrcvHwAccessibility(TrcvIdx, ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK);                        /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

    retVal |= E_NOT_OK;
  }

  /* #50 If the previous operations were successful */
  if(retVal == E_OK)
  {
    /* #510 Set state variables */
    EthTrcv_30_Tja1100_SetTrcvState(TrcvIdx, ETHTRCV_STATE_INIT);                                                       /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

    EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_DOWN);                                                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

    EthTrcv_30_Tja1100_SetTrcvLinkState(TrcvIdx, ETHTRCV_LINK_STATE_DOWN);                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_TransceiverInit() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetTransceiverMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetTransceiverMode(
    uint8 TrcvIdx,
    EthTrcv_ModeType TrcvMode)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType   retVal = E_OK;
  EthTrcv_ModeType currentMode;

  /* ----- Implementation ----------------------------------------------- */
  currentMode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);

  /* #10 The transceiver is not currently in a diagnostic mode */
  if((currentMode == ETHTRCV_MODE_ACTIVE) || (currentMode == ETHTRCV_MODE_DOWN))
  {
    /* #110 The transceiver mode should be set to ACTIVE */
    if ( TrcvMode == ETHTRCV_MODE_ACTIVE )
    {
#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
      EthTrcv_30_Tja1100_WakeupIdxOfEthTrcvType       wakeupIdx        = EthTrcv_30_Tja1100_GetWakeupIdxOfEthTrcv(TrcvIdx);
      EthTrcv_30_Tja1100_WakeupCalloutIdxOfWakeupType wakeupCalloutIdx = EthTrcv_30_Tja1100_GetWakeupCalloutIdxOfWakeup(wakeupIdx);
#endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */
      /* #1110 Set the transceiver mode to ACTIVE */
      retVal |= EthTrcv_30_Tja1100_EnableTransceiver(TrcvIdx);

      /* #1120 Call wakeup callout user code if wakup is supported and callout functions are configured */
#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
      /* call user code */
      if( EthTrcv_30_Tja1100_GetWakeupCallout(wakeupCalloutIdx) != NULL_PTR )
      {
        EthTrcv_30_Tja1100_GetWakeupCallout(wakeupCalloutIdx)(TrcvIdx);                                                 /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL03 */
      }
#endif /* ETHTRCV_WAKEUP_NOT_SUPPORTED != ETHTRCV_30_TJA1100_WAKEUP_TYPE */
    }
    /* #120 The transceiver mode should be set to DOWN */
    else
    {
      /* #1210 Set the transceiver mode to DOWN */
      retVal |= EthTrcv_30_Tja1100_DisableTransceiver(TrcvIdx);
    }
  }
  /* #20 The transceiver is currently in a diagnostic mode */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_SetTransceiverMode() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetTransceiverMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_ModeType mode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);
  /* ----- Implementation ----------------------------------------------- */
  /*  #10 The transceiver is currently not in a diagnostic mode */
  if((mode == ETHTRCV_MODE_ACTIVE) || (mode == ETHTRCV_MODE_DOWN))
  {
    /* #110 Read transceiver mode from the transceiver */
    retVal |= EthTrcv_30_Tja1100_LL_GetTransceiverMode(TrcvIdx, TrcvModePtr, retVal);                                   /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */
  }
  /* #20 The transceiver is currently in a diagnostic mode */
  else
  {
    /* #210 Return ETHTRCV_MODE_DOWN */
    *TrcvModePtr = ETHTRCV_MODE_DOWN;                                                                                   /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetTransceiverMode() */ /* PRQA S 2006, 6010, 6050, 6080 */ /* MD_MSR_14.7, MD_MSR_STPTH, MD_MSR_STCAL, MD_MSR_STMIF */

#if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_StartAutoNegotiation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_StartAutoNegotiation(
    uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The transceiver mode is active */
  if(EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx) == ETHTRCV_MODE_ACTIVE)
  {
    /* #110 Enable the auto negotiation process */
    retVal |= EthTrcv_30_Tja1100_LL_EnableStartAutoNegotiation(TrcvIdx, retVal);
  }
  /* #20 The transceiver mode is not active */
  else
  {
    /* #210 Leave the API with E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_StartAutoNegotiation() */
#endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetLinkState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) LinkStatePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_ModeType trcvMode;
  EthTrcv_30_Tja1100_HardwareAccessibilityType hwAccessibility;
  /* ----- Implementation ----------------------------------------------- */

  trcvMode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);
  hwAccessibility = EthTrcv_30_Tja1100_GetTrcvHwAccessibility(TrcvIdx);

  /* #10 The transceiver mode is active and the transceiver hardware is accessible */
  if((trcvMode        == ETHTRCV_MODE_ACTIVE) &&
     (hwAccessibility == ETHTRCV_30_TJA1100_ACCESSIBILITY_OK))
  {
    /* #110 Read the link state from the transceiver */
    retVal |= EthTrcv_30_Tja1100_LL_GetLinkState(TrcvIdx, LinkStatePtr, retVal);                                        /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */
  }
  /* #20 The transceiver mode is down or the transceiver hardware is not accessible */
  else
  {
    /* #210 Report the link state is DOWN */
    *LinkStatePtr = ETHTRCV_LINK_STATE_DOWN;                                                                            /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 Save the link state */
  EthTrcv_30_Tja1100_SetTrcvLinkState(TrcvIdx, *LinkStatePtr);                                                          /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetLinkState */

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetBaudRate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) BaudRatePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The link state is active */
  if(EthTrcv_30_Tja1100_GetTrcvLinkState(TrcvIdx) == ETHTRCV_LINK_STATE_ACTIVE)
  {
    /* #110 Read the baud rate from the transceiver */
    retVal |= EthTrcv_30_Tja1100_LL_GetBaudRate(TrcvIdx, BaudRatePtr, retVal); /*lint !e522 */                          /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */
  }
  /* #20 The link state is down*/
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetBaudRate() */ /* PRQA S 2006, 6010, 6050, 6080 */ /* MD_MSR_14.7, MD_MSR_STPTH, MD_MSR_STCAL, MD_MSR_STMIF */
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetDuplexMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) DuplexModePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 The link state is active */
  if(EthTrcv_30_Tja1100_GetTrcvLinkState(TrcvIdx) == ETHTRCV_LINK_STATE_ACTIVE)
  {
    /* #110 Read the duplex mode from the transceiver */
    retVal |= EthTrcv_30_Tja1100_LL_GetDuplexMode(TrcvIdx, DuplexModePtr, retVal);                                      /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */
  }
  /* #20 The link state is down */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetDuplexMode() */
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyTestMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_ModeType mode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Setting PHY test modes is available on the hardware */
  if(EthTrcv_30_Tja1100_LL_IsSetTestModeAvailable(TrcvIdx) == TRUE)
  {
    /* #110 The Ehternet transceiver driver is either in mode ACTIVE or a diagnostic test mode is already enabled */
    if((mode == ETHTRCV_MODE_ACTIVE) || (mode == ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TEST_MODE))
    {
      /* #1110 Normal operation shall be resumed */
      if(TestMode == ETHTRCV_PHYTESTMODE_NONE)
      {
        /* #11110 Exit the diagnostic state for PHY test modes */
        EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_ACTIVE);                                                   /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      }
      /* #1120 A PHY test mode shall be enabled */
      else
      {
        /* #11210 Enter the diagnostic state for PHY test modes */
        EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TEST_MODE);                          /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      }
      /* #1130 Set the given test mode on the hardware */
      retVal |= EthTrcv_30_Tja1100_LL_SetPhyTestMode(TrcvIdx, TestMode, retVal); /*lint !e522 */
    }
    /* #120 The Ethernet transceiver driver is either in mode DOWN or another diagnostic mode is enabled */
    else
    {
      /* #1210 Return E_NOT_OK */
      retVal = E_NOT_OK;
    }
  }
  /* #20 Setting PHY test modes is not available on the hardware */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_SetPhyTestMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_ModeType mode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);
  /* ----- Implementation ----------------------------------------------- */
  /* #10 The Ethernet transceiver driver is either in mode ACTIVE or a loopback diagnostic mode is enabled already */
  if((mode == ETHTRCV_MODE_ACTIVE) || (mode == ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_LOOPBACK_MODE))
  {
    /* #110 Normal operation shall be resumed */
    if(LoopbackMode == ETHTRCV_PHYLOOPBACK_NONE)
    {
      /* #1110 Exit the diagnostic state for PHY loopback modes */
      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_ACTIVE);                                                     /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #120 A PHY loopback mode shall be enabled */
    else
    {
      /* #1210 Enter the diagnostic state for PHY loopback modes */
      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_LOOPBACK_MODE);                        /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #130 Set the given loopback mode */
    retVal |= EthTrcv_30_Tja1100_LL_SetPhyLoopbackMode(TrcvIdx, LoopbackMode, retVal);
  }
  /* #20 The Ethernet transceiver driver is in mode DOWN or in any other diagnostic state */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetPhySignalQuality
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetPhySignalQuality(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) SignalQualityPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  uint8                                                signalQualityValue;
  uint32                                               signalQualityValueSum;
  EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType signalQualityValueIndex;
  EthTrcv_30_Tja1100_PhySignalQualityMeanOfEthTrcvType meanLength;
  Std_ReturnType                                       retVal = E_OK;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 The transceiver mode is ACTIVE */
  if(EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx) == ETHTRCV_MODE_ACTIVE)
  {
    /* #110 The signal quality of the transceiver can be obtained */
    if(EthTrcv_30_Tja1100_LL_IsSignalQualityAvailable(TrcvIdx) == TRUE)
    {
      /* #1110 The transceiver link state is ACTIVE */
      if(EthTrcv_30_Tja1100_GetTrcvLinkState(TrcvIdx) == ETHTRCV_LINK_STATE_ACTIVE)
      {
        /* #11110 Prepare the signal quality measurement */
        retVal |= EthTrcv_30_Tja1100_LL_PrepareSignalQualityMeasurement(TrcvIdx, retVal);

        /* #11120 Retrieve the mean length to be used to calculate the average signal quality value */
        meanLength = EthTrcv_30_Tja1100_GetPhySignalQualityMeanOfEthTrcv(TrcvIdx);

        signalQualityValueSum = 0;
        /* #11130 Summarize the data points for the signal quality until the mean length is reached */
        for(signalQualityValueIndex = 0; signalQualityValueIndex < meanLength; signalQualityValueIndex++)
        {
          retVal |= EthTrcv_30_Tja1100_LL_GetPhySignalQualityValueInPercent(TrcvIdx, &signalQualityValue, retVal);      /* SBSW_ETHTRCV_REF_OF_STACK_VAR */
          signalQualityValueSum += signalQualityValue;
        }

        /* #11140 Finalize the signal quality measurement */
        retVal |= EthTrcv_30_Tja1100_LL_FinalizeSignalQualityMeasurement(TrcvIdx, retVal);

        /* #11150 Return the average of the obtained data points for the signal quality in percent */
        *SignalQualityPtr = (uint8)(signalQualityValueSum / meanLength);                                                /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      }
      /* #1120 The transceiver link state is DOWN */
      else
      {
        /* #11210 The transceiver's signal quality is 0 percent */
        *SignalQualityPtr = 0;                                                                                          /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      }
    }
    /* #120 The signal quality of the transceiver cannot be obtained */
    else
    {
      /* #1210 Return E_NOT_OK */
      retVal = E_NOT_OK;
    }
  }
  /* #20 The transceiver mode is DOWN or a diagnostic mode is enabled */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetPhySignalQuality() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_SetPhyTxMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal = E_OK;
  EthTrcv_ModeType mode = EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx);
  /* ----- Implementation ----------------------------------------------- */
  /* #10 The Ethernet transceiver driver is in mode ACTIVE or a diagnostic TX-mode is already enabled */
  if((mode == ETHTRCV_MODE_ACTIVE) || (mode == ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TX_MODE))
  {
    /* #110 Normal operation shall be resumed */
    if(TxMode == ETHTRCV_PHYTXMODE_NORMAL)
    {
      /* #1110 Exit the diagnostic state for PHY tx modes */
      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_ACTIVE);                                                     /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #120 A PHY tx mode shall be enabled */
    else
    {
      /* #1210 Enter the diagnostic state for PHY tx modes */
      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_TX_MODE);                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #130 Set the given tx mode on the hardware */
    retVal |= EthTrcv_30_Tja1100_LL_SetPhyTxMode(TrcvIdx, TxMode, retVal);
  }
  /* #20 The Ethernet transceiver driver is in mode DOWN or another diagnostic mode is enabled */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_SetPhyTxMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) CableDiagResultPtr)
{
  /* ----- Local variables ---------------------------------------------- */

  EthTrcv_30_Tja1100_CableDiagLoopCyclesType timeoutCounter;
  Std_ReturnType                             retVal = E_OK;

  /* #10 The transceiver is in mode ACTIVE */
  if(EthTrcv_30_Tja1100_GetTrcvMode(TrcvIdx) == ETHTRCV_MODE_ACTIVE)
  {
    /* #110 The transceiver supports cable diagnostics */
    if(EthTrcv_30_Tja1100_LL_IsCableDiagAvailable(TrcvIdx) == TRUE)
    {
      boolean preparedResult;
      boolean finishedResult;

      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_30_TJA1100_DIAGNOSTIC_MODE_CABLE_DIAG);                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

      *CableDiagResultPtr = ETHTRCV_CABLEDIAG_ERROR;                                                                    /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

      /* #1110 Prepare the cable diagnostic */
      retVal |= EthTrcv_30_Tja1100_LL_PrepareCableDiag(TrcvIdx, retVal);

      /* #1120 Wait until the cable diagnostic is prepared and the sequence can be started */
      for(timeoutCounter = 0; timeoutCounter <= EthTrcv_30_Tja1100_GetCableDiagLoopCycles(); timeoutCounter++)
      {
        retVal |= EthTrcv_30_Tja1100_LL_IsCableDiagPrepared(TrcvIdx, &preparedResult, retVal);                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

        if(preparedResult == TRUE)
        {
          break;
        }
      }
      /* #1130 Enable the diagnostic measurement */
      retVal |= EthTrcv_30_Tja1100_LL_EnableDiagnosticSequence(TrcvIdx, retVal);

      /* #1140 Wait until the measurement has finished */
      for(timeoutCounter = 0; timeoutCounter <= EthTrcv_30_Tja1100_GetCableDiagLoopCycles(); timeoutCounter++)
      {
        retVal |= EthTrcv_30_Tja1100_LL_IsCableDiagFinished(TrcvIdx, &finishedResult, retVal);                          /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

        if(finishedResult == TRUE)
        {
          break;
        }
      }

      /* #1150 Wait until the result is available */
      for(timeoutCounter = 0; timeoutCounter <= EthTrcv_30_Tja1100_GetCableDiagLoopCycles(); timeoutCounter++)
      {
        /* #1160 Report the returned cable diagnostic result */
        retVal |= EthTrcv_30_Tja1100_LL_CheckCableDiagResult(TrcvIdx, CableDiagResultPtr, retVal);                      /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */

        if( *CableDiagResultPtr != ETHTRCV_CABLEDIAG_ERROR)
        {
          break;
        }
      }
      /* #1170 Perform additional steps after the cable diagnostics */
      retVal |= EthTrcv_30_Tja1100_LL_AdditionalStepsAfterCableDiag(TrcvIdx, retVal);
      /* #1180 Return to active mode in order to allow the trigger of a new test sequence */
      EthTrcv_30_Tja1100_SetTrcvMode(TrcvIdx, ETHTRCV_MODE_ACTIVE);                                                     /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #120 The transceiver does not support cable diagnostics */
    else
    {
      /* #1210 Return E_NOT_OK */
      retVal = E_NOT_OK;
    }
  }
  /* #20 The transceiver is not in mode ACTIVE */
  else
  {
    /* #210 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult() */ /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetPhyIdentifier
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetPhyIdentifier(
    uint8 TrcvIdx,
    P2VAR(uint32, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) OrgUniqueIdPtr,
    P2VAR(uint8,  AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) ModelNrPtr,
    P2VAR(uint8,  AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) RevisionNrPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  uint16         idRegVal1;
  uint16         idRegVal2;
  Std_ReturnType retVal = E_OK;

  /* #10 Read the transceiver's registers */

  retVal |= EthTrcv_30_Tja1100_LL_ReadIdentifier1Register(TrcvIdx, &idRegVal1, retVal);                                 /* SBSW_ETHTRCV_REF_OF_STACK_VAR */
  retVal |= EthTrcv_30_Tja1100_LL_ReadIdentifier2Register(TrcvIdx, &idRegVal2, retVal);                                 /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Retrieve the organizational unique identifier */
  *OrgUniqueIdPtr = (((uint32)(idRegVal1 & ETHTRCV_30_TJA1100_REG_PHYIDR1_OUI_MASK)) << ETHTRCV_30_TJA1100_PHYIDR1_TO_OUIPTR_SHIFT_LEFT) | /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
                    (((uint32)(idRegVal2 & ETHTRCV_30_TJA1100_REG_PHYIDR2_OUI_MASK)) >> ETHTRCV_30_TJA1100_PHYIDR2_TO_OUIPTR_SHIFT_RIGHT);

  /* #30 Retrieve the model number */
  *ModelNrPtr = (uint8)((idRegVal2 & ETHTRCV_30_TJA1100_REG_PHYIDR2_TYPE_NR_MASK) >> ETHTRCV_30_TJA1100_PHYIDR2_TO_MODELPTR_SHIFT_RIGHT); /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  /* #40 Retrieve the revision number */
  *RevisionNrPtr = (uint8)(idRegVal2 & ETHTRCV_30_TJA1100_REG_PHYIDR2_REV_NR_MASK);                                     /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  return retVal;
} /* EthTrcv_30_Tja1100_Internal_GetPhyIdentifier() */


/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_MainFunction( void )
{
#if ( ETHTRCV_WAKEUP_BY_POLLING == ETHTRCV_30_TJA1100_WAKEUP_TYPE)
  /* #10 Perform the wake up reason check if the wake up check type is polling */
  EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck();
#endif

  /* #20 Perform the hardware access monitor check */
  EthTrcv_30_Tja1100_Internal_HwAccessMonitor();

} /* EthTrcv_30_Tja1100_Internal_MainFunction() */

#if ( ETHTRCV_WAKEUP_BY_POLLING == ETHTRCV_30_TJA1100_WAKEUP_TYPE)
/**********************************************************************************************************************
*  EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck
*********************************************************************************************************************/
/*!
* Internal comment removed.
 *
 *
 *
 *
 *
 *
*/
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck( void )
{
  /* ----- Local variables ---------------------------------------------- */
  EthTrcv_30_Tja1100_EthTrcvIterType trcvIdx;

  /* #10 Increment the wake up reason check waiting counter */
  EthTrcv_30_Tja1100_IncWakeupReasonCycleCounter();                                                                     /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */

  /* #20 When the configured wake up reason check period is realized by the counter value proceed to the wake up reason evaluation */
  if(EthTrcv_30_Tja1100_GetWakeupReasonCycleCounter() == EthTrcv_30_Tja1100_GetWakeupReasonLoopLimiter())
  {
    /* #210 Iterate over all configured transceivers */
    for(trcvIdx = 0; trcvIdx < EthTrcv_30_Tja1100_GetSizeOfEthTrcv(); trcvIdx++)
    {
      /* #2110 Check for wake up events and handle them */
      if( EthTrcv_30_Tja1100_InspectWakeupReasons(trcvIdx) == E_OK )
      {
        EthTrcv_30_Tja1100_ReportWakeup(trcvIdx);
      }
    }
    /* #220 Reset the wake up reason check waiting counter */
    EthTrcv_30_Tja1100_SetWakeupReasonCycleCounter(0);                                                                  /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */
  }
} /* EthTrcv_30_Tja1100_Internal_WakeUpReasonCheck() */
#endif /* ETHTRCV_WAKEUP_BY_POLLING == ETHTRCV_30_TJA1100_WAKEUP_TYPE */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_HwAccessMonitor
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_HwAccessMonitor( void )
{
  /* ----- Local variables ---------------------------------------------- */
  EthTrcv_30_Tja1100_EthTrcvIterType trcvIdx;

  /* #10 Increment the hardware access monitor waiting counter */
  EthTrcv_30_Tja1100_IncHwAccessMonitorCycleCounter();                                                                  /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */

  /* #20 When the configured hardware access monitor period is realized by the counter value proceed to the hardware access check */
  if(EthTrcv_30_Tja1100_GetHwAccessMonitorCycleCounter() == EthTrcv_30_Tja1100_GetHwAccessMonitorLoopLimiter())
  {
    /* #210 Iterate over all configured transceivers */
    for(trcvIdx = 0; trcvIdx < EthTrcv_30_Tja1100_GetSizeOfEthTrcv(); trcvIdx++)
    {
      /* #2110 If the Ethernet transceiver hardware is already initialized */
      if(EthTrcv_30_Tja1100_GetTrcvState(trcvIdx) == ETHTRCV_STATE_INIT)
      {
        /* #21110 Call the hardware access monitor handling service */
        EthTrcv_30_Tja1100_Internal_HwAccessMonitorHandling((uint8)trcvIdx);
      }
    }
    /* #220 Reset the hardware access monitor counter to re-realize the Hw access monitor period for the next evaluation */
    EthTrcv_30_Tja1100_SetHwAccessMonitorCycleCounter(0);                                                               /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */
  }
} /* EthTrcv_30_Tja1100_Internal_HwAccessMonitor */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_HwAccessMonitorHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_HwAccessMonitorHandling( uint8 TrcvIdx )
{
  /* #10 If the hardware dependent interface to check hardware access indicates that the transceiver hardware is inaccessible */
  if (EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk(TrcvIdx) == FALSE)
  {
    /* #110 If the hardware accessibility's previous state is ETHTRCV_30_TJA1100_ACCESSIBILITY_OK */
    if(EthTrcv_30_Tja1100_GetTrcvHwAccessibility(TrcvIdx) == ETHTRCV_30_TJA1100_ACCESSIBILITY_OK)
    {
      /* #1110 Hardware access failure debouncing is completed. Start error reaction. */
      if(EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceCounter(TrcvIdx) == EthTrcv_30_Tja1100_GetHwAccessMonitorFailureDebounceLimiter())
      {
        /* #11110 Set the hardware accessibility to ACCESSIBILITY_NOT_OK */
        EthTrcv_30_Tja1100_SetTrcvHwAccessibility(TrcvIdx, ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK);                    /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

        /* #11120 DEM error because there is no access to the transceiver */
        ETHTRCV_30_TJA1100_DEM_REPORT_ERROR_STATUS_ETHTRCV_E_ACCESS(TrcvIdx);

        /* #11130 Call the hardware access failure user callout */
        if(EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCallout(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX) != NULL_PTR)
        {
          EthTrcv_30_Tja1100_GetHwAccessMonitorFailureCallout(ETHTRCV_30_TJA1100_USER_CALLOUT_IDX)(TrcvIdx);            /* SBSW_ETHTRCV_FCT_PTR_OPT_CSL01 */
        }
      }
      /* #1120 If the hardware access failure debouncing is not completed */
      else
      {
        /* #11210 Increment the hardware access failure debounce counter */
        EthTrcv_30_Tja1100_IncHwAccessMonitorFailureDebounceCounter(TrcvIdx);                                           /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */
      }
    }
    /* #120 Unsuccessful hardware access check occurrence. Reset the hardware access failure recovery debounce counter */
    EthTrcv_30_Tja1100_SetHwAccessMonitorRecoveryDebounceCounter(TrcvIdx, 0);                                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
  /* #20 If the hardware dependent interface to check the hardware access indicates that the transceiver hardware is accessible */
  else
  {
    /* #210 If the hardware accessibility's previous state is ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK */
    if(EthTrcv_30_Tja1100_GetTrcvHwAccessibility(TrcvIdx) == ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK)
    {
      /* #2110 Hardware access failure recovery debouncing is completed. Start recovery reaction */
      if(EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceCounter(TrcvIdx) == EthTrcv_30_Tja1100_GetHwAccessMonitorRecoveryDebounceLimiter())
      {
        /* #21110 Set the hardware accessibility to ACCESSIBILITY_OK */
        EthTrcv_30_Tja1100_SetTrcvHwAccessibility(TrcvIdx, ETHTRCV_30_TJA1100_ACCESSIBILITY_OK);                        /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

        /* #21120 DEM success because the transceiver is accessible */
        ETHTRCV_30_TJA1100_DEM_REPORT_PASSED_STATUS_ETHTRCV_E_ACCESS(TrcvIdx);
      }
      /* #2120 If the hardware access failure recovery debouncing is not completed */
      else
      {
        /* #21210 Increment the hardware access failure recovery debounce counter */
        EthTrcv_30_Tja1100_IncHwAccessMonitorRecoveryDebounceCounter(TrcvIdx);                                          /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION */
      }
    }
    /* 220 Successful hardware access check occurrence. Reset the hardware access failure debounce counter */
    EthTrcv_30_Tja1100_SetHwAccessMonitorFailureDebounceCounter(TrcvIdx, 0);                                            /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
} /* EthTrcv_30_Tja1100_Internal_HwAccessMonitorFailureHandling() */ /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling( void )
{
  /* ----- Local variables ---------------------------------------------- */
  EthTrcv_30_Tja1100_EthTrcvIterType trcvIdx;

  /* #10 Iterate over all configured transceivers */
  for(trcvIdx = 0; trcvIdx < EthTrcv_30_Tja1100_GetSizeOfEthTrcv(); trcvIdx++)
  {

    /* #110 Check that the transceiver is active and not currently in a diagnostic mode  */
    if(EthTrcv_30_Tja1100_GetTrcvMode(trcvIdx) == ETHTRCV_MODE_ACTIVE)
    {
      /* #1110 Perform additional link handling actions */
      EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling((uint8)trcvIdx);  /*lint !e522 */
    }
  }
} /* EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling() */

#if (ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Internal_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */

ETHTRCV_30_TJA1100_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) VersionInfoPtr)
{
  /* ----- Implementation ----------------------------------------------- */

  /* #10 Report the module's version info */
  VersionInfoPtr->vendorID = ETHTRCV_30_TJA1100_VENDOR_ID;                                                              /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  VersionInfoPtr->moduleID = ETHTRCV_30_TJA1100_MODULE_ID;                                                              /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  VersionInfoPtr->sw_major_version = ETHTRCV_30_TJA1100_SW_MAJOR_VERSION;                                               /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  VersionInfoPtr->sw_minor_version = ETHTRCV_30_TJA1100_SW_MINOR_VERSION;                                               /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  VersionInfoPtr->sw_patch_version = ETHTRCV_30_TJA1100_SW_PATCH_VERSION;                                               /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

} /* EthTrcv_30_Tja1100_Internal_GetVersionInfo */
#endif /* ETHTRCV_30_TJA1100_VERSION_INFO_API */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_InitMemory
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_InitMemory(
    void)
{
  /* ----- Local Variables ---------------------------------------------- */

  /* ----- Implementation ----------------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  EthTrcv_30_Tja1100_ModuleState = ETHTRCV_STATE_UNINIT;
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
} /* EthTrcv_30_Tja1100_InitMemory() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_Init
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Init(
  P2CONST(EthTrcv_30_Tja1100_ConfigType, AUTOMATIC, ETHTRCV_30_TJA1100_INIT_DATA) CfgPtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  /* #10 Check plausibility of input parameter */
  if(CfgPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
    EthTrcv_30_Tja1100_EthTrcvIterType trcvIdx;

    EthTrcv_30_Tja1100_ConfigDataPtr = CfgPtr;

    /* #20 Initialize the hardware access cycle counter */
    EthTrcv_30_Tja1100_SetHwAccessMonitorCycleCounter(0);                                                               /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_PREV_INIT_CALLED */

#if ( ETHTRCV_WAKEUP_BY_POLLING == ETHTRCV_30_TJA1100_WAKEUP_TYPE)
    /* #30 Initialize the wakeup reason counter */
    EthTrcv_30_Tja1100_SetWakeupReasonCycleCounter(0);                                                                  /* SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_PREV_INIT_CALLED */
#endif

    /* #40 Loop over all available transceivers */
    for( trcvIdx = 0; trcvIdx < EthTrcv_30_Tja1100_GetSizeOfEthTrcv(); trcvIdx++ )
    {
      /* #410 Set the transceiver's init state to uninit */
      EthTrcv_30_Tja1100_SetTrcvState(trcvIdx, ETHTRCV_STATE_UNINIT);                                                   /* SBSW_ETHTRCV_COMMON_CSL01 */

      /* #420 Set the transceiver mode to down */
      EthTrcv_30_Tja1100_SetTrcvMode(trcvIdx, ETHTRCV_MODE_DOWN);                                                       /* SBSW_ETHTRCV_COMMON_CSL01 */

      /* #430 Initialize Hardware access monitor related counters and state variables */
      EthTrcv_30_Tja1100_SetTrcvHwAccessibility(trcvIdx, ETHTRCV_30_TJA1100_ACCESSIBILITY_NOT_OK);                      /* SBSW_ETHTRCV_COMMON_CSL01 */
      EthTrcv_30_Tja1100_SetHwAccessMonitorRecoveryDebounceCounter(trcvIdx, 0);                                         /* SBSW_ETHTRCV_COMMON_CSL01 */
      EthTrcv_30_Tja1100_SetHwAccessMonitorFailureDebounceCounter(trcvIdx, 0);                                          /* SBSW_ETHTRCV_COMMON_CSL01 */

      /* #440 Initialize additional global variables */
      EthTrcv_30_Tja1100_LL_InitGlobalVariables((uint8)trcvIdx); /*lint !e522 */

#if ( ETHTRCV_30_TJA1100_WAKEUP_TYPE != ETHTRCV_WAKEUP_NOT_SUPPORTED )
      /* #450 Initialize wakeup related state variables */
      EthTrcv_30_Tja1100_SetWakeupMode(trcvIdx, ETHTRCV_WUM_ENABLE);                                                    /* SBSW_ETHTRCV_COMMON_CSL01 */
      EthTrcv_30_Tja1100_ClearWakeupReasons(trcvIdx);

      /* #460 Check for wakeup events */
      (void)EthTrcv_30_Tja1100_InspectWakeupReasons(trcvIdx);

      /* #470 Check if any wakeup reason was set */
      if( EthTrcv_30_Tja1100_IsWakeupReasonPending(trcvIdx) == FALSE )
      {
        /* #4710 No wakeup reason set -> default during initialization is RESET */
        EthTrcv_30_Tja1100_SetWakeupReasonToReset(trcvIdx);
      }
      /* #480 report wakeup events */
      EthTrcv_30_Tja1100_ReportWakeup(trcvIdx);
#endif
    }
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
    /* #50 Initialize state variable */
    EthTrcv_30_Tja1100_ModuleState = ETHTRCV_STATE_INIT;
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, 0, ETHTRCV_30_TJA1100_SID_INIT, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif
} /* EthTrcv_30_Tja1100_Init() */ /* PRQA S 2006, 6050 */ /* MD_MSR_14.7, MD_MSR_STCAL */ /*lint !e438 */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_TransceiverInit
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_TransceiverInit(
    uint8 TrcvIdx,
    uint8 CfgIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(CfgIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(CfgIdx >= ETHTRCV_30_TJA1100_MAX_CFGS_TOTAL)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
#endif
  {
    /* ----- Implementation --------------------------------------------- */
    /* #20 Trigger start of runtime measurement */
    EthTrcv_30_Tja1100_Rtm_Start(TransceiverInit);

    /* #30 Call internal TransceiverInit */
    retVal = EthTrcv_30_Tja1100_Internal_TransceiverInit(TrcvIdx);

    /* #40 Trigger stop of runtime measurement */
    EthTrcv_30_Tja1100_Rtm_Stop(TransceiverInit);
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_TRANSCEIVER_INIT, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_TransceiverInit() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetTransceiverMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTransceiverMode(
    uint8 TrcvIdx,
    EthTrcv_ModeType TrcvMode)
{
  /* ----- Local Variables ----------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks -------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if((TrcvMode != ETHTRCV_MODE_DOWN) && (TrcvMode != ETHTRCV_MODE_ACTIVE))
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_PARAM;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    retVal = EthTrcv_30_Tja1100_Internal_SetTransceiverMode(TrcvIdx, TrcvMode);

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_SET_TRANSCEIVER_MODE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_SetTransceiverMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetTransceiverMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvModePtr)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvModePtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* ----- Implementation ----------------------------------------------- */
    retVal = EthTrcv_30_Tja1100_Internal_GetTransceiverMode(TrcvIdx, TrcvModePtr);                                      /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_TRANSCEIVER_MODE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetTransceiverMode() */

#if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_StartAutoNegotiation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_StartAutoNegotiation(
    uint8 TrcvIdx)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */

    /* #20 Call internal StartAutoNegotiation */
    retVal = EthTrcv_30_Tja1100_Internal_StartAutoNegotiation(TrcvIdx);

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_START_AUTO_NEG, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_StartAutoNegotiation() */
#endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetLinkState
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) LinkStatePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_GetTrcvState(TrcvIdx) == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(LinkStatePtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal GetLinkState */
    retVal = EthTrcv_30_Tja1100_Internal_GetLinkState(TrcvIdx, LinkStatePtr);                                           /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_LINK_STATE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetLinkState */

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetBaudRate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) BaudRatePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(BaudRatePtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal GetBaudRate */
    retVal = EthTrcv_30_Tja1100_Internal_GetBaudRate(TrcvIdx, BaudRatePtr);                                             /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_BAUD_RATE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetBaudRate() */
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

#if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetDuplexMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) DuplexModePtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(DuplexModePtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal GetDuplexMode */
    retVal = EthTrcv_30_Tja1100_Internal_GetDuplexMode(TrcvIdx, DuplexModePtr);                                         /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_DUPLEX_MODE, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetDuplexMode() */
#endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyTestMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode)
{
  /* ----- Local variables ---------------------------------------------- */

  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_LL_IsTestmodeSupportedByHw(TrcvIdx, TestMode) == FALSE)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_SUPPORTED;
  }
  else
#endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal SetPhyTestMode */
    retVal = EthTrcv_30_Tja1100_Internal_SetPhyTestMode(TrcvIdx, TestMode);

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_SET_PHY_TEST_MODE, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_SetPhyTestMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyLoopbackMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode)
{
  /* ----- Local variables ---------------------------------------------- */

  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_LL_IsLoopbackmodeSupportedByHw(TrcvIdx, LoopbackMode) == FALSE)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_SUPPORTED;
  }
  else
#endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal SetPhyLoopbackMode */
    retVal = EthTrcv_30_Tja1100_Internal_SetPhyLoopbackMode(TrcvIdx, LoopbackMode);

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_SET_PHY_LOOPBACK_MODE, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_SetPhyLoopbackMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetPhySignalQuality
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhySignalQuality(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) SignalQualityPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(SignalQualityPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
#endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal GetPhySignalQuality */
    retVal = EthTrcv_30_Tja1100_Internal_GetPhySignalQuality(TrcvIdx, SignalQualityPtr);                                /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_PHY_SIGNAL_QUALITY, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetPhySignalQuality() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyTxMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode)
{
  /* ----- Local variables ---------------------------------------------- */

  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(EthTrcv_30_Tja1100_LL_IsTxmodeSupportedByHw(TrcvIdx, TxMode) == FALSE)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_SUPPORTED;
  }
  else
#endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal SetPhyTxMode */
    retVal = EthTrcv_30_Tja1100_Internal_SetPhyTxMode(TrcvIdx, TxMode);

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
  /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_SET_PHY_TX_MODE, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_SetPhyTxMode() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetCableDiagnosticsResult
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetCableDiagnosticsResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) CableDiagResultPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if(CableDiagResultPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
#endif
  {
    ETHTRCV_30_TJA1100_BEGIN_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
    /* #20 Call internal GetCableDiagnosticsResult */
    retVal = EthTrcv_30_Tja1100_Internal_GetCableDiagnosticsResult(TrcvIdx, CableDiagResultPtr);                        /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */

    ETHTRCV_30_TJA1100_END_CRITICAL_SECTION_SEQUENCE(); /* PRQA S 3109 */ /* MD_MSR_14.3 */
  }
    /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_CABLE_DIAGNOSTICS_RESULT, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetCableDiagnosticsResult() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetPhyIdentifier
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhyIdentifier(
    uint8 TrcvIdx,
    P2VAR(uint32, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) OrgUniqueIdPtr,
    P2VAR(uint8,  AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) ModelNrPtr,
    P2VAR(uint8,  AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) RevisionNrPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint8          errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  retVal  = E_NOT_OK;
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else if(TrcvIdx >= EthTrcv_30_Tja1100_GetSizeOfEthTrcv())
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_TRCV_IDX;
  }
  else if((OrgUniqueIdPtr == NULL_PTR) ||
          (ModelNrPtr     == NULL_PTR) ||
          (RevisionNrPtr  == NULL_PTR))
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
#endif
  {
    /* #20 Call internal GetPhyIdentifier */
    retVal = EthTrcv_30_Tja1100_Internal_GetPhyIdentifier(TrcvIdx, OrgUniqueIdPtr, ModelNrPtr, RevisionNrPtr);          /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */
  }
    /* ----- Development Error Report --------------------------------------*/
#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, TrcvIdx, ETHTRCV_30_TJA1100_SID_GET_PHY_IDENTIFIER, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif

  return retVal;
} /* EthTrcv_30_Tja1100_GetPhyIdentifier() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_MainFunction
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_MainFunction( void )
{
  /* ----- Local variables ---------------------------------------------- */
  uint8 errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */

#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
  {
    /* #20 Call internal MainFunction */
    EthTrcv_30_Tja1100_Internal_MainFunction(); /*lint !e522 */
  }

#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, 0, ETHTRCV_30_TJA1100_SID_MAIN_FUNCTION, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_REPORT */
} /* EthTrcv_30_Tja1100_MainFunction() */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_MainFunctionLinkHandling
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_MainFunctionLinkHandling( void )
{
  /* ----- Local variables ---------------------------------------------- */
  uint8 errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;
  /* ----- Development Error Checks ------------------------------------- */

#if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                   /* COV_ETHTRCV_SAFE_FEAT */
  /* #10 Check plausibility of input parameters and initialization state */
  if(EthTrcv_30_Tja1100_ModuleState == ETHTRCV_STATE_UNINIT)
  {
    errorId = ETHTRCV_30_TJA1100_E_NOT_INITIALIZED;
  }
  else
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */
  {
    /* #20 Call internal MainFunctionLinkHandling */
    EthTrcv_30_Tja1100_Internal_MainFunctionLinkHandling(); /*lint !e522 */
  }

#if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, 0, ETHTRCV_30_TJA1100_SID_MAIN_FUNCTION_LINK_HANDLING, errorId);
  }
#else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
#endif /* ETHTRCV_30_TJA1100_DEV_ERROR_REPORT */
} /* EthTrcv_30_Tja1100_MainFunctionLinkHandling() */

#if (ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetVersionInfo
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */

FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) VersionInfoPtr)
{
  /* ----- Local variables ---------------------------------------------- */
  uint8 errorId = ETHTRCV_30_TJA1100_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )                                                                  /* COV_ETHTRCV_SAFE_FEAT */
  /* #10 Check plausibility of input parameter */
  if(VersionInfoPtr == NULL_PTR)
  {
    errorId = ETHTRCV_30_TJA1100_E_INV_POINTER;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    /*  #20 Call internal GetVersionInfo */
    EthTrcv_30_Tja1100_Internal_GetVersionInfo(VersionInfoPtr);                                                         /* SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS */
  }
  /* ----- Development Error Report --------------------------------------*/
# if ( ETHTRCV_30_TJA1100_DEV_ERROR_REPORT == STD_ON )
  if (errorId != ETHTRCV_30_TJA1100_E_NO_ERROR)
  {
    (void)Det_ReportError(ETHTRCV_30_TJA1100_MODULE_ID, 0, ETHTRCV_30_TJA1100_SID_GET_VERSION_INFO, errorId);
  }
# else
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(errorId); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
# endif
} /* EthTrcv_30_Tja1100_GetVersionInfo */
#endif /* ETHTRCV_30_TJA1100_VERSION_INFO_API */

#define ETHTRCV_30_TJA1100_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/* module specific MISRA deviations:

  MD_EthTrcv_30_Tja1100_3219:
    Reason:     This function is inlined and therefore it has to be implemented here. The function is not used
                by all implementation files which include this header file.
    Risk:       None.
    Prevention: None.

  MD_EthTrcv_30_Tja1100_0612:
    Reason:     Firmware file content can exceed the conforming object size of 32767 bytes.
    Risk:       There is no risk because the compilers used can handle the object size.
    Prevention: None.

*/


/* COV_JUSTIFICATION_BEGIN

  \ID COV_ETHTRCV_COMPATIBILITY
    \ACCEPT XF xf
    \ACCEPT TX tx
    \REASON [MSR_COV_COMPATIBILITY]

  \ID COV_ETHTRCV_TEST_SUITE_UNIT_TESTS
    \ACCEPT TX
    \REASON This code is only deactivated by ETHTRCV test suite for unit testing purpose.

  \ID COV_ETHTRCV_SAFE_FEAT
    \ACCEPT TX
    \REASON Feature must be enabled for an ASIL qualified configuration. MSSV plugin ensures that feature is turned on.

 COV_JUSTIFICATION_END*/

/* SBSW_JUSTIFICATION_BEGIN

   \ID SBSW_ETHTRCV_COMMON_CSL01
     \DESCRIPTION Access of generated data by usage of index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETHTRCV_CSL01]

   \ID SBSW_ETHTRCV_COMMON_CSL03
     \DESCRIPTION Access of generated data by usage of indirection index defined by ComStackLib using ComStackLib.
     \COUNTERMEASURE \N [CM_ETHTRCV_CSL03]

   \ID SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_CALLER_VERIFICATION
     \DESCRIPTION Access of variable through configuration pointer.
     \COUNTERMEASURE \N Accessing the variable through configuration pointer is only called after
                        callers have checked that module has been initialized, which indicates that configuration
                        pointer is valid.

   \ID SBSW_ETHTRCV_COMMON_CFG_PTR_INT_FCT_PREV_INIT_CALLED
     \DESCRIPTION Access of variable through configuration pointer.
     \COUNTERMEASURE \R Accessing the variable through configuration pointer is only called after
                        callers have checked that module has been initialized, which indicates that configuration
                        pointer is valid. This is previously checked during runtime or the initialization is done in
                        the same function.

   \ID SBSW_ETHTRCV_INT_FCT_IDX_PASS
     \DESCRIPTION Write access to data using index passed as function argument during call of a internal function.
     \COUNTERMEASURE \N Check for validity of a index with respect to the value range defined in CDD is done before the
                        function is called and the index is passed according to [CM_ETHTRCV_CSL01] or [CM_ETHTRCV_CSL03].

   \ID SBSW_ETHTRCV_REF_OF_STACK_VAR
     \DESCRIPTION Pointer to stack variable passed as function argument.
     \COUNTERMEASURE \N Pointer is generated by referencing a stack variable by the address operator.

   \ID SBSW_ETHTRCV_PUB_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to a public API.
     \COUNTERMEASURE \R Parameter pointer provided to public API is checked for not being NULL pointer before usage.

   \ID SBSW_ETHTRCV_INT_FCT_PUB_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a public function as parameter to an internal function.
     \COUNTERMEASURE \R Parameter pointer provided to public API is checked for not being NULL pointer before passing.

   \ID SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE
     \DESCRIPTION Write access to an object referenced by a function parameter passed to an internal function.
     \COUNTERMEASURE \N The caller of the function performing the write access ensures that the pointer passed is valid.

   \ID SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS
     \DESCRIPTION Passing a pointer provided during a call to a function as parameter to an internal function.
     \COUNTERMEASURE \N The caller of the function passing the pointer to the other function ensures that the pointer
                        is valid.

   \ID SBSW_ETHTRCV_DRVAPI_FCT_PTR_MAN_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib.
     \COUNTERMEASURE \R Index used according to [CM_ETHTRCV_CSL03] to resolve respective function-pointer.
                        Signature of the function used to define function-pointer checked by compiler. The User has
                        to check generated function-pointer according to SMI-8.

      \ID SBSW_ETHTRCV_DRVAPI_FCT_PTR_PARAM_PTR_PASS_MAN_CSL03
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib and passing a
                  pointer passed to the function as parameter.
     \COUNTERMEASURE \R Index used according to [CM_ETHTRCV_CSL03] to resolve respective function-pointer.
                        Signature of the function used to define function-pointer checked by compiler. The User has
                        to check generated function-pointer according to SMI-8. The caller of the function has to ensure
                        that the pointer parameter passed is valid.

   \ID SBSW_ETHTRCV_DRVAPI_FCT_PTR_MAN_CSL03_REF_OF_STACK_VAR
     \DESCRIPTION Access of a mandatory function pointer of driver API abstraction using ComStackLib passing a pointer
                  to a stack variable
     \COUNTERMEASURE \N Index used according to [CM_ETHTRCV_CSL03] to resolve respective function-pointer.
                        Signature of the function used to define function-pointer checked by compiler. The User has
                        to check generated function-pointer according to SMI-8. Passed pointer is generated by
                        referencing a stack variable by the address operator.

   \ID SBSW_ETHTRCV_FCT_PTR_OPT_CSL01
     \DESCRIPTION Access of optional function pointer using ComStackLib.
     \COUNTERMEASURE \R Index used according to [CM_ETHTRCV_CSL01] to resolve respective function-pointer, additional
                        runtime check for NULL_PTR performed. Signature of the function used to define function-pointer
                        checked by compiler. The User has to check generated function-pointer according to SMI-8. Due to
                        CSL limitation a workaround is applied to generate an array of size one for this structure.
                        There fore the index is fixed to 0 and defined as constant macro.

   \ID SBSW_ETHTRCV_FCT_PTR_OPT_CSL03
     \DESCRIPTION Access of optional function pointer using ComStackLib.
     \COUNTERMEASURE \R Index used according to [CM_ETHTRCV_CSL03] to resolve respective function-pointer, additional
                        runtime check for NULL_PTR performed. Signature of the function used to define function-pointer
                        checked by compiler. The User has to check generated function-pointer according to SMI-8.

   SBSW_JUSTIFICATION_END */

/*

  \CM CM_ETHTRCV_CSL01 Qualified use-case CSL01 of ComStackLib.
  \CM CM_ETHTRCV_CSL03 Qualified use-case CSL03 of ComStackLib.

 */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100.c
 *********************************************************************************************************************/
