/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2020 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*         \file  EthTrcv_30_Tja1100.h
 *        \brief  Ethernet transceiver driver header file
 *
 *      \details  Module header providing access to AUTOSAR APIs of the Ethernet transceiver driver
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  David Roeder                  visdrr        Vector Informatik GmbH
 *  Amr Abdelhady                 visaay        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2017-02-28  visdrr  -             Initial creation
 *            2017-03-02  visdrr  FEATC-944     FEAT-1824: Support a component-specific SafeBSW configuration switch
 *  01.01.00  2017-03-14  visdrr  FEATC-676     FEAT-2234: Ethernet Link Quality Monitoring
 *  01.02.00  2017-05-03  visdrr  ESCAN00095009 Support Marvell 88Q1010 Ethernet Transceivers
 *            2017-06-01  visdrr  ESCAN00095381 Compiler error: error #137 expression must be a modifiable lvalue,  
 *                                              error #120: return value type does not match the function type
 *  01.02.01  2017-07-21  visdrr  ESCAN00096003 GetVersionInfo() returns version of core files while it should return
 *                                              the lower layer implementation version
 *  01.03.00  2017-10-11  visdrr  STORYC-178    FEAT-2465: Release of Wakeup - Activation Line EthTrcv
 *  02.00.00  2018-06-04  visdrr  ESCAN00096617 Plausibility check (Development Error Check) for
 *                                              transceiver hardware initialization is missing in wakeup-related
 *                                              function
 *                                ESCAN00097286 MISRA deviation: MISRA-C:2004 Rule 19.7 wrong
 *                                              justification: MarkerRef not found in marker list
 *  03.00.00  2018-06-13  visdrr  STORYC-429:   [SAFE] SafeBSW for EthTrcv(Core) (ASIL B)
 *  03.00.01  2018-08-02  visdrr  ESCAN00100278 Compiler error: syntax error - token "," inserted before "*",
 *                                              ETHTRCV_30_TJA1100_APPL_DATA define missing in
 *                                              EthTrcv_30_Tja1100_Compiler_Cfg.inc
 *  03.01.00  2018-10-02  visdrr  STORYC-6117   Provide IEEE 802.3 clause 45 access over clause 22 registers:
 *                                              Implementation and Testing
 *  04.00.00  2019-01-17  visaay  STORYC-6354   Cyclic hardware access check
 *                                STORYC-10621  Link down counter measure for hardware access failure implementation 
 *                                              and testing
 *                                STORY-11197   Hardware access failure error reporting improvement 
 *                                              (DEM reporting mitigation)
 *                                STORY-11192   Hardware access failure error reporting improvement
 *                                              (Error reporting mitigation)
 *  04.00.01  2019-09-17  visdrr  ESCAN00103494 Silent Analysis: Silent justifications for ComStackLib-config access
 *                                              write functions missing
 *  05.00.00  2020-01-09  visaay  ETH-1326      Introduce user-callout before each SMI read/write access: CRS, CAD,
 *                                              GEN + CDD
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_TJA1100_H)
# define ETHTRCV_30_TJA1100_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Wakeup.h"
# include "EthTrcv_30_Tja1100_Hw.h"
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/* PRQA S 0857 EOF */ /* MD_MSR_1.1_857  */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777  */
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779  */
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* AUTOSAR 4.x Software Specification Version Information */
# define ETHTRCV_30_TJA1100_AR_RELEASE_MAJOR_VERSION                  (0x04U)
# define ETHTRCV_30_TJA1100_AR_RELEASE_MINOR_VERSION                  (0x01U)
# define ETHTRCV_30_TJA1100_AR_RELEASE_REVISION_VERSION               (0x01U)

/* Vector ID */
# define ETHTRCV_30_TJA1100_VENDOR_ID                                 (30U)

/* ETHTRCV ModuleId */
# define ETHTRCV_30_TJA1100_MODULE_ID                                 (73U)

/* ----- API service IDs ----- */
# define ETHTRCV_30_TJA1100_SID_INIT                                  (0x01U) /*!< Service ID: EthTrcv_30_Tja1100_Init() */
# define ETHTRCV_30_TJA1100_SID_TRANSCEIVER_INIT                      (0x02U) /*!< Service ID: EthTrcv_30_Tja1100_TransceiverInit() */
# define ETHTRCV_30_TJA1100_SID_SET_TRANSCEIVER_MODE                  (0x03U) /*!< Service ID: EthTrcv_30_Tja1100_SetTransceiverMode() */
# define ETHTRCV_30_TJA1100_SID_GET_TRANSCEIVER_MODE                  (0x04U) /*!< Service ID: EthTrcv_30_Tja1100_GetTransceiverMode() */
# define ETHTRCV_30_TJA1100_SID_START_AUTO_NEG                        (0x05U) /*!< Service ID: EthTrcv_30_Tja1100_StartAutoNegotiation() */
# define ETHTRCV_30_TJA1100_SID_GET_LINK_STATE                        (0x06U) /*!< Service ID: EthTrcv_30_Tja1100_GetLinkState() */
# define ETHTRCV_30_TJA1100_SID_GET_BAUD_RATE                         (0x07U) /*!< Service ID: EthTrcv_30_Tja1100_GetBaudRate() */
# define ETHTRCV_30_TJA1100_SID_GET_DUPLEX_MODE                       (0x08U) /*!< Service ID: EthTrcv_30_Tja1100_GetDuplexMode() */
# define ETHTRCV_30_TJA1100_SID_GET_VERSION_INFO                      (0x0BU) /*!< Service ID: EthTrcv_30_Tja1100_GetVersionInfo() */
# define ETHTRCV_30_TJA1100_SID_MAIN_FUNCTION                         (0x0CU) /*!< Service ID: EthTrcv_30_Tja1100_MainFunction() */
# define ETHTRCV_30_TJA1100_SID_GET_PHY_SIGNAL_QUALITY                (0x10U) /*!< Service ID: EthTrcv_30_Tja1100_GetPhySignalQuality() */
# define ETHTRCV_30_TJA1100_SID_SET_PHY_TEST_MODE                     (0x11U) /*!< Service ID: EthTrcv_30_Tja1100_SetPhyTestMode() */
# define ETHTRCV_30_TJA1100_SID_SET_PHY_LOOPBACK_MODE                 (0x12U) /*!< Service ID: EthTrcv_30_Tja1100_SetPhyLoopbackMode() */
# define ETHTRCV_30_TJA1100_SID_SET_PHY_TX_MODE                       (0x13U) /*!< Service ID: EthTrcv_30_Tja1100_SetPhyTxMode() */
# define ETHTRCV_30_TJA1100_SID_GET_CABLE_DIAGNOSTICS_RESULT          (0x14U) /*!< Service ID: EthTrcv_30_Tja1100_GetCableDiagnosticsResult() */
# define ETHTRCV_30_TJA1100_SID_GET_PHY_IDENTIFIER                    (0x15U) /*!< Service ID: EthTrcv_30_Tja1100_GetPhyIdentifier() */
# define ETHTRCV_30_TJA1100_SID_MAIN_FUNCTION_LINK_HANDLING           (0x16U) /*!< Service ID: EthTrcv_30_Tja1100_MainFunctionLinkHandling() */

/* ETHTRCV DET errors */
# define ETHTRCV_30_TJA1100_E_NO_ERROR                                (0x00U) /*!< No Error occurred */
# define ETHTRCV_30_TJA1100_E_INV_TRCV_IDX                            (0x01U) /*!< Error code: API service has been called with invalid transceiver index */
# define ETHTRCV_30_TJA1100_E_NOT_INITIALIZED                         (0x02U) /*!< Error code: API service used without module initialization */
# define ETHTRCV_30_TJA1100_E_INV_POINTER                             (0x03U) /*!< Error code: API service used with invalid pointer parameter */
# define ETHTRCV_30_TJA1100_E_INV_PARAM                               (0x04U) /*!< Error code: API service used with invalid value for parameter */
# define ETHTRCV_30_TJA1100_E_NOT_SUPPORTED                           (0x05U) /*!< Error code: API service not supported by the hardware */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  EthTrcv_30_Tja1100_InitMemory()
 **********************************************************************************************************************/
/*! \brief       Function for *_INIT_*-variable initialization
 *  \details     Service to initialize module global variables at power up. This function initializes the
 *               variables in *_INIT_* sections. Used in case they are not initialized by the startup code.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_InitMemory(
    void);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Init()
 *********************************************************************************************************************/
/*! \brief       Initialization function
 *  \details     This function initializes the module EthTrcv_30_Tja1100. It initializes all variables and sets the
 *               module state to initialized.
 *  \param[in]   CfgPtr  Configuration structure for initializing the module
 *  \pre         Module is uninitialized.
 *  \pre         EthTrcv_30_Tja1100_InitMemory has been called unless EthTrcv_30_Tja1100_ModuleInitialized is
 *               initialized by start-up code.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Specification of module initialization
 *  \trace       CREQ-137828
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Init(
    P2CONST(EthTrcv_30_Tja1100_ConfigType, AUTOMATIC, ETHTRCV_30_TJA1100_INIT_DATA) CfgPtr);


/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_TransceiverInit()
 ************** *******************************************************************************************************/
/*! \brief       Initializes an Ethernet transceiver (register configuration)
 *  \details     This function initializes the transceiver's registers to realize its functionality according to the
 *               configuration.
 *  \param[in]   TrcvIdx  Zero based index of the transceiver
 *  \param[in]   CfgIdx   Configuration index
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137828
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_TransceiverInit(
    uint8 TrcvIdx,
    uint8 CfgIdx);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief       Sets the transceiver's mode
 *  \details     This function sets the transceiver to active or down.
 *  \param[in]   TrcvIdx   Zero based index of the transceiver
 *  \param[in]   TrcvMode  Transceiver mode to set:
 *               ETHTRCV_MODE_DOWN - shut down the Ethernet transceiver
 *               ETHTRCV_MODE_ACTIVE - activate the Ethernet transceiver
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetTransceiverMode(
    uint8 TrcvIdx,
    EthTrcv_ModeType TrcvMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's mode
 *  \details     This function returns the transceiver's current mode.
 *  \param[in]   TrcvIdx      Zero based index of the transceiver.
 *  \param[out]  TrcvModePtr  Pointer for retrieved transceiver mode:
 *               ETHTRCV_MODE_DOWN - transceiver is turned off
 *               ETHTRCV_MODE_ACTIVE - transceiver is active
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) TrcvModePtr);

# if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_StartAutoNegotiation()
 *********************************************************************************************************************/
/*! \brief       Starts automatic negotiation
 *  \details     This function starts the process to automatically negotiate the transceivers master-slave role,
 *               duplex mode and link speed, if available.
 *  \param[in]   TrcvIdx  Zero based index of the transceiver.
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137984
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_StartAutoNegotiation(
    uint8 TrcvIdx);
# endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetLinkState()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's link state
 *  \details     This function returns the transceiver's current link state. It is called by the EthIf_MainFunctionState
 *               with a deterministic polling cycle time and and shall not be called directly to avoid side-effects
 *  \param[in]   TrcvIdx       Zero based index of the transceiver.
 *  \param[out]  LinkStatePtr  Pointer for the retrieved link state value:
 *               ETHTRCV_LINK_STATE_DOWN - link is down
 *               ETHTRCV_LINK_STATE_ACTIVE - link is up
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) LinkStatePtr);

# if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetBaudRate()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's baud rate
 *  \details     This function returns the transceiver's current baud rate.
 *  \param[in]   TrcvIdx      Zero based index of the transceiver.
 *  \param[out]  BaudRatePtr  Pointer for the retrieved baud rate value:
 *               ETHTRCV_BAUD_RATE_10MBIT   - Linkspeed  10 Mbit/s
 *               ETHTRCV_BAUD_RATE_100MBIT  - Linkspeed: 100 Mbit/s
 *               ETHTRCV_BAUD_RATE_1000MBIT - Linkspeed: 1Gb/s
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137986
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) BaudRatePtr);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

# if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetDuplexMode()
 *********************************************************************************************************************/
/*! \brief       Gets the transceiver's duplex mode
 *  \details     This function returns the transceiver's current duplex mode.
 *  \param[in]   TrcvIdx        Zero based index of the transceiver
 *  \param[out]  DuplexModePtr  Pointer for the retrieved duplex mode value:
 *               ETHTRCV_DUPLEX_MODE_HALF - transceiver operates in half duplex mode
 *               ETHTRCV_DUPLEX_MODE_FULL - transceiver operates in full duplex mode
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137987
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetDuplexMode(
  uint8 TrcvIdx,
  P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) DuplexModePtr);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyTestMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy test mode
 *  \details     This function activates the given phy test mode
 *  \param[in]   TrcvIdx   Zero based index of the transceiver
 *  \param[in]   TestMode  Test mode to be activated
 *               ETHTRCV_PHYTESTMODE_NONE - Normal operation
 *               ETHTRCV_PHYTESTMODE_1 - Test transmitter drop
 *               ETHTRCV_PHYTESTMODE_2 - Test master timing jitter
 *               ETHTRCV_PHYTESTMODE_3 - Test slave timing jitter
 *               ETHTRCV_PHYTESTMODE_4 - Test transmitter distortion
 *               ETHTRCV_PHYTESTMODE_5 - Test power spectral density
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyLoopbackMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy loopback mode
 *  \details     This function activates the given phy loopback mode
 *  \param[in]   TrcvIdx       Zero based index of the transceiver
 *  \param[in]   LoopbackMode  Loopback mode to be activated
 *               ETHTRCV_PHYLOOPBACK_NONE - Normal operation
 *               ETHTRCV_PHYLOOPBACK_INTERNAL - Internal Loopback
 *               ETHTRCV_PHYLOOPBACK_EXTERNAL - External Loopback
 *               ETHTRCV_PHYLOOPBACK_REMOTE - Remote loopback
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetPhySignalQuality()
 *********************************************************************************************************************/
/*! \brief       Gets the signal quality
 *  \details     This function obtains the current signal quality of the link of the indexed transceiver
 *  \param[in]   TrcvIdx           Zero based index of the transceiver
 *  \param[out]  SignalQualityPtr  Pointer to the memory where the signal quality in percent shall be stored
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137990
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhySignalQuality(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) SignalQualityPtr);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_SetPhyTxMode()
 *********************************************************************************************************************/
/*! \brief       Activates a given Tx Mode
 *  \details     This function activates the given transmission mode
 *  \param[in]   TrcvIdx  Zero based index of the transceiver
 *  \param[in]   TxMode   Transmission mode to be activated
 *               ETHTRCV_PHYTXMODE_NORMAL        Normal Operation
 *               ETHTRCV_PHYTXMODE_TX_OFF        Transmitter disabled
 *               ETHTRCV_PHYTXMODE_SCRAMBLER_OFF Scrambler disabled
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre         The transmission mode to be activated is supported by the hardware
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetCableDiagnosticsResult()
 *********************************************************************************************************************/
/*! \brief       Retrieves cable diagnostics result
 *  \details     This function retrieves the cable diagnostics result of a given transceiver
 *  \param[in]   TrcvIdx             Zero based index of the transceiver
 *  \param[out]  CableDiagResultPtr  Pointer to the memory where the signal quality in percent shall be stored
 *               ETHTRCV_CABLEDIAG_OK: Cable diagnostics result was OK
 *               ETHTRCV_CABLEDIAG_ERROR: Cable diagnostics failed
 *               ETHTRCV_CABLEDIAG_SHORT: Cable diagnostics detected a short on the MDI
 *               ETHTRCV_CABLEDIAG_OPEN: Cable diagnostics detected an open on the MDI
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetCableDiagnosticsResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) CableDiagResultPtr);

/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetPhyIdentifier()
 *********************************************************************************************************************/
/*! \brief       Obtains PHY identifier
 *  \details     This function obtains the PHY identifier of the Ethernet Transceiver according to IEEE 802.3-2015 chapter
 *               22.2.4.3.1 PHY Identifier.
 *  \param[in]   TrcvIdx         Zero based index of the transceiver
 *  \param[out]  OrgUniqueIdPtr  Pointer to the memory where the Organizational Unique Identifier shall be stored
 *  \param[out]  ModelNrPtr      Pointer to the memory where the Manufacturer's Model Number shall be stored
 *  \param[out]  RevisionNrPtr   Pointer to the memory where the Revision Number shall be stored
 *  \return      E_OK     - success
 *  \return      E_NOT_OK - Function has been called with invalid parameter or at least one of the hardware operations
 *                          (read/write) has failed.
 *  \pre         Module is initialized.
 *  \pre         EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137992
*/
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetPhyIdentifier(
    uint8 TrcvIdx,
    P2VAR(uint32, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) OrgUniqueIdPtr,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) ModelNrPtr,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) RevisionNrPtr);

# if ( ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_GetVersionInfo
 *********************************************************************************************************************/
/*! \brief       Returns the version information
 *  \details     EthTrcv_30_Tja1100() returns version information, vendor ID and AUTOSAR module ID of the component.
 *  \param[out]  VersionInfoPtr  Pointer to where to store the version information. Parameter must not be NULL.
 *  \pre         -
 *  \context     ANY
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-137829
 */
FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_GetVersionInfo(
    P2VAR(Std_VersionInfoType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_DATA) VersionInfoPtr);
# endif /* ETHTRCV_30_TJA1100_VERSION_INFO_API == STD_ON */


/**********************************************************************************************************************
 *  EthTrcv_30_Tja1100_MainFunction
 *********************************************************************************************************************/
/*! \brief          Main Function
 *  \details        Main function to handle cyclical tasks of the Ethernet transceiver driver
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            Module is initialized.
 */
/* Function declaration is provided by SchM */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_MainFunctionLinkHandling
 *********************************************************************************************************************/
/*! \brief         Main function implementation which is used for link handling and link startup.
 *  \details       This function is used to perform timing relevant initialization and link startup and/or link
 *                 handling tasks.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 */
/* Function declaration is provided by SchM */

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */

/*!
 * \exclusivearea ETHTRCV_30_TJA1100_EXCLUSIVE_AREA_SEQUENCE
 * Protects the consistency of states and sequences used in the Ethernet transceiver driver
 * \protects EthTrcv_30_Tja1100_TrcvMode (read/write), register read/write sequences
 * \usedin   EthTrcv_30_Tja1100_TransceiverInit, EthTrcv_30_Tja1100_SetTransceiverMode, EthTrcv_30_Tja1100_GetTransceiverMode, EthTrcv_30_Tja1100_StartAutoNegotiation, EthTrcv_30_Tja1100_SetPhyTestMode,
 *           EthTrcv_30_Tja1100_GetDuplexMode, EthTrcv_30_Tja1100_GetBaudRate, EthTrcv_30_Tja1100_GetLinkState, EthTrcv_30_Tja1100_MainFunctionLinkHandling, EthTrcv_30_Tja1100_SetPhyLoopbackMode,
 *           EthTrcv_30_Tja1100_GetPhySignalQuality, EthTrcv_30_Tja1100_SetPhyTxMode, EthTrcv_30_Tja1100_GetCableDiagnosticsResult
 * \exclude  Concurrent calls to the "usedin" functions.
 * \length MEDIUM Register write/read sequences and state handling .
 * \endexclusivearea
 *
 */

#endif /* ETHTRCV_30_TJA1100_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100.h
 *********************************************************************************************************************/
