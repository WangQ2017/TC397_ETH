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
/*!        \file  EthTrcv_30_Tja1100_LL.h
 *        \brief  Ethernet Transceiver Driver Lower Layer Implementation
 *      \details  Hardware dependent implementation for NXP TJA110x Ethernet transceivers for x=0,1,2
 *
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  David Fessler                 visfer        Vector Informatik GmbH
 *  David Walther                 visdrr        Vector Informatik GmbH
 *  Amr Abdelhady                 visaay        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2015-01-29  visfer  -             Initial creation
 *  01.01.00  2015-03-30  visfer  ESCAN00082159 FEAT-705: Ethernet wakeup based on Activation Line [AR4-1006]
 *  01.01.01  2015-04-29  visfer  ESCAN00082746 Compiler error when wakeup is enabled
 *  01.01.02  2015-06-02  visfer  ESCAN00083237 Compiler error when more than one Tja1100 Transceiver is used
 *  01.01.03  2015-08-10  visfer  ESCAN00084434 Compiler error when DET is disabled
 *  01.01.04  2015-12-08  visfer  ESCAN00085848 Link is reported as active although cable is not connected
 *                                ESCAN00086588 Compiler error: declaration may not appear after executable statement in block
 *  01.01.05  2015-02-26  visfer  ESCAN00088599 Duplicate configuration structure for Mii mode is generated
 *  01.02.00  2016-04-26  visfer  ESCAN00089734 Remove distinction between single and multiple transceiver generation
 *                                              to reduce component complexity / variants
 *  01.03.00  2016-06-23  visfer  ESCAN00090726 Link is not reestablished after a loss of link
 *  01.04.00  2016-08-04  visfer  ESCAN00091330 Add support for Tja1102
 *                                ESCAN00091389 Wrong api switch in EthTrcv_30_Tja1100.c
 *                                              (used ENABLE_GET_BAUD_RATE instead of ENABLE_GET_DUPLEX_MODE)
 *  01.04.01  2016-09-01  visfer  ESCAN00091704 Compiler error:"ETHTRCV_30_TJA1100_DERIVATIVE_TJA1100" is undefined
 *  01.04.02  2016-11-07  visdrr  ESCAN00092046 Variable in ZERO_INIT section has no value assignment
 *  01.04.03  2016-12-14  visfer  ESCAN00092405 Link startup behaviour is not implemented according to NXP
 *                                              ApplicationHints_v12. Link startup and ethernet communication may fail
 *  02.00.00  2017-02-16  visdrr  ESCAN00094037 Ethernet transceiver driver core introduced
 *  02.01.00  2017-03-14  visdrr  FEATC-676     FEAT-2234: Ethernet Link Quality Monitoring
 *  02.01.01  2017-04-27  visdrr  ESCAN00092405 Link startup behaviour is not implemented according to NXP
 *                                              ApplicationHints_v12. Link startup and ethernet communication may fail.
 *                                ESCAN00094672 Support TxMode Off and Scrambler Off
 *  02.02.00  2017-05-09  visdrr  ESCAN00095078 Update to newest core version
 *            2017-06-01  visdrr  ESCAN00095386 Compiler error: error #137 expression must be a modifiable lvalue,
 *                                              error #120: return value type does not match the function type
 *  02.02.01  2017-07-21  visdrr  ESCAN00095878 Tx Amplitude is set to 500mV instead of default value 1000 mV
 *                                ESCAN00095981 If the management interface is provided by a switch, the MII-Mode
 *                                              strapping cannot be overwritten by the configuration
 *  02.03.00  2017-09-25  visdrr  STORYC-2619   Update to newest core version
 *                                STORYC-2620   Add derivative Tja1101 to supported derivatives
 *  02.04.00  2017-10-11  visdrr  STORYC-2768   Update to Ethernet transceiver core version 01.03.00
 *  03.00.00  2018-01-19  visdrr  STORYC-582    FEAT-2877S648 [SAFE] SafeBSW for EthTrcv(Tja1100) (ASIL B)
 *            2018-05-08  visdrr  ESCAN00096430 Software reset is performed even if link-down is
 *                                              initiated in a testing context, e.g. during the use of the
 *                                              SetPhyTestMode()-API
 *                                ESCAN00095856 Cable diagnostics sequence is enabled early after link
 *                                              shutdown, retrieved link diagnostic results can be wrong
 *            2018-06-28          ESCAN00099831 Return value is E_OK and initialization / activation is continued even
 *                                              if management access is not available
 *  03.00.01  2018-08-02  visdrr  STORYC-6185   Update to DrvTrans__coreEthAsr v. 3.00.01
 *  03.01.00  2018-11-05  visdrr  STORYC-6944   Provide IEEE 802.3 clause 22 access as public interface on
 *                                              DrvTrans_Tja1100EthAsr
 *  04.00.00  2019-01-17  visaay  STORY-12599   Release of DrvTrans__coreEthAsr & DrvTrans_Tja1100EthAsr (ASIL-D) 
 *                                              [FUp STORY-11782]
 *  05.00.00  2020-01-23  visaay  ETH-1342      ASIL-D Release of DrvTrans_Tja1100EthAsr with pre-SMI user callouts
 *  05.00.01  2020-02-05  visdrr  ESCAN00101731 Strapping pin configuration isn't overriden by the driver for all
 *                                              parameters where it might be necessary on TJA1102
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_TJA1100_LL_H)
# define ETHTRCV_30_TJA1100_LL_H
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/*lint -e451 */ /* Suppress ID451 because MemMap.h cannot use a include guard */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Int.h"
# include "EthTrcv_30_Tja1100_LL_Regs.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_TJA1100_LL_LOCAL)                                                                              /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_LL_LOCAL                                 static
# endif

# if !defined(ETHTRCV_30_TJA1100_LL_LOCAL_INLINE)                                                                       /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_LL_LOCAL_INLINE                          LOCAL_INLINE
# endif

# define ETHTRCV_30_TJA1100_SW_MAJOR_VERSION                          (5u)
# define ETHTRCV_30_TJA1100_SW_MINOR_VERSION                          (0u)
# define ETHTRCV_30_TJA1100_SW_PATCH_VERSION                          (1u)

/*! The link startup delay counter is disabled */
# define ETHTRCV_30_TJA1100_NO_LINK_STARTUP                           (0xFFu) 
/*! Timer value in milliseconds after which the link state is checked if extended link state checking is enabled */
# define ETHTRCV_30_TJA1100_LINK_STATE_DELAY_MS                       (100u)
/*! Timeout value for the link state check */
# define ETHTRCV_30_TJA1100_LINK_STATE_DELAY_TIMEOUT_MS               (200u)
/*! No link startup required */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_0                      (0x00u)
/*! Link startup required, enable link startup delay */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_1                      (0x01u)
/*! Link startup delay passed, enable LINK_CONTROL */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_2                      (0x02u)
/*! Read link state. If up and stable --> State 4. If down, restart after timeout  */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_3                      (0x03u)
/*! Wait 100ms, read link state. If up and stable --> State 5. If down, restart after timeout */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_4                      (0x04u)
/*! Link up and stable, normal operation */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_5                      (0x05u)
/*! Link fail counter overflow or timeout --> SW Reset */
# define ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_6                      (0x06u) 
/*! Maximum signal quality value in percent */
# define ETHTRCV_30_TJA1100_MAXIMUM_SIGNAL_QUALITY_PERCENTAGE          (100u)
/*! Number of different possible signal quality values (resolution) */
# define ETHTRCV_30_TJA1100_SIGNAL_QUALITY_BORDERS                       (7u) 

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_ClearMiiModeSettings()
 *********************************************************************************************************************/
/*! \brief         Clears the controller interface settings.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ClearMiiModeSettings(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToMiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Mii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToLightMiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Light Mii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToLightMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiXtalMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rmii Xtal Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToGmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Gmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToGmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rgmii Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiXtalMode()
 *********************************************************************************************************************/
/*! \brief         Sets the controller interface to Rgmii Xtal Mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetBasicConfigurationRegister()
 *********************************************************************************************************************/
/*! \brief         Sets the basic configuration register value.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetBasicConfigurationRegister(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk()
 *********************************************************************************************************************/
/*! \brief         Checks if the transciever's registers are accessible.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \return        TRUE - Transceiver registers can be read/written
 *  \return        FALSE - Transceiver registers cannot be read/written
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_ApplyAdditionalConfigSteps()
 *********************************************************************************************************************/
/*! \brief         Applies additional configuration steps if necessary
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ApplyAdditionalConfigSteps(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetClkMode
 *********************************************************************************************************************/
/*! \brief         Sets the clock mode configuration, if the strapping configuration must be overwritten.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Only allowed to be called for the configured derivatives TJA1101 and TJA1102.
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetClkMode(
    uint8 TrcvIdx);

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetLdoMode
 *********************************************************************************************************************/
/*! \brief         Sets the LDO mode configuration, if the strapping configuration must be overwritten.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Only allowed to be called for the configured derivatives TJA1101 and TJA1102.
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetLdoMode(
    uint8 TrcvIdx);

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetRevMiiMode
 *********************************************************************************************************************/
/*! \brief         Sets the internal reverse MII mode configuration, if the strapping configuration must be overwritten.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Only allowed to be called for the configured derivative TJA1102.
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetRevMiiMode(
    uint8 TrcvIdx);

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetPhyEnable
 *********************************************************************************************************************/
/*! \brief         Sets the PHY_ENABLE configuration, if the strapping configuration must be overwritten.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Only allowed to be called for the configured derivative TJA1102.
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyEnable(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_GetLinkState()
 *********************************************************************************************************************/
/*! \brief         Gets the current link state from the transceiver
 *  \details       Retrieves the current link state from the transceiver hardware and resets the link fail counter if
 *                 the link is reported to be ACTIVE and increments the link fail counter in case the link is reported
 *                 to be DOWN.
 *  \param[in]     TrcvIdx       Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                               minus one.
 *  \param[out]    LinkStatePtr  Pointer to the memory address where the read link state value is stored. Values:
 *                               ETHTRCV_LINK_STATE_ACTIVE, ETHTRCV_LINK_STATE_DOWN
 *  \param[in]     RetVal        State of success of the previous operations before the call of this function:
 *                               E_OK     - The previous operations were successful
 *                               E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK        - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK    - Function has been called with invalid parameters or at least one of the hardware operations
 *                               (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) LinkStatePtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetTransceiverModeActive()
 *********************************************************************************************************************/
/*! \brief         Sets the transceiver's mode to active
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetTransceiverModeActive(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetTransceiverModeDown()
 *********************************************************************************************************************/
/*! \brief         Sets the transceiver's mode to down
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetTransceiverModeDown(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_GetTransceiverMode()
 *********************************************************************************************************************/
/*! \brief         Gets the transceiver's mode
 *  \details       -
 *  \param[in]     TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[out]    TrcvModePtr  Pointer to the memory address where the read transceiver mode value is stored. Values:
 *                              ETHTRCV_MODE_DOWN, ETHTRCV_MODE_ACTIVE
 *  \param[in]     RetVal       State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK       - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK   - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) TrcvModePtr,
    Std_ReturnType RetVal);

# if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_GetDuplexMode()
 *********************************************************************************************************************/
/*! \brief         Reads the duplex mode from the transciver.
 *  \details       -
 *  \param[in]     TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                                minus one.
 *  \param[out]    DuplexModePtr  Pointer to the memory address where the read duplex mode value is stored. Values:
 *                                ETHTRCV_DUPLEX_MODE_FULL, ETHTRCV_DUPLEX_MODE_HALF
 *  \param[in]     RetVal         State of success of the previous operations before the call of this function:
 *                                E_OK     - The previous operations were successful
 *                                E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK         - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK     - Function has been called with invalid parameters or at least one of the hardware operations
 *                                (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) DuplexModePtr,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsSetTestModeAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports to set the test mode
 *  \details     -
 *  \param[in]   TrcvIdx Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                       minus one.
 *  \return      TRUE  - Transceiver supports to set the test mode
 *  \return      FALSE - Transceiver does not support to set the test mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsSetTestModeAvailable(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsSignalQualityAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports the retrieval of the signal quality
 *  \details     -
 *  \param[in]   TrcvIdx  Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                        minus one.
 *  \return      TRUE   - Transceiver supports the retrieval of the signal quality
 *  \return      FALSE  - Transceiver does not support the retrieval
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsSignalQualityAvailable(
    uint8 TrcvIdx);

# if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsTestmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given test mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TestMode   Test mode to check. Values:
 *                          ETHTRCV_PHYTESTMODE_NONE - Normal operation
 *                          ETHTRCV_PHYTESTMODE_1 - Test transmitter drop
 *                          ETHTRCV_PHYTESTMODE_2 - Test master timing jitter
 *                          ETHTRCV_PHYTESTMODE_3 - Test slave timing jitter
 *                          ETHTRCV_PHYTESTMODE_4 - Test transmitter distortion
 *                          ETHTRCV_PHYTESTMODE_5 - Test power spectral density
 *  \return      TRUE     - Transceiver supports the given test mode
 *  \return      FALSE    - Transceiver does not support the given test mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsTestmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsLoopbackmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given loopback mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[in]   LoopbackMode   Loopback mode to check. Values:
 *                              ETHTRCV_PHYLOOPBACK_NONE - Normal operation
 *                              ETHTRCV_PHYLOOPBACK_INTERNAL - Internal Loopback
 *                              ETHTRCV_PHYLOOPBACK_EXTERNAL - External Loopback
 *                              ETHTRCV_PHYLOOPBACK_REMOTE - Remote loopback
 *  \return      TRUE         - Transceiver supports the given loopback mode
 *  \return      FALSE        - Transceiver does not support the given loopback mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsLoopbackmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsTxmodeSupportedByHw()
 *********************************************************************************************************************/
/*! \brief       Checks if a given transmission mode is supported by the hardware
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \param[in]   TxMode     Transmission mode to check. Values:
 *                          ETHTRCV_PHYTXMODE_NORMAL        Normal Operation
                            ETHTRCV_PHYTXMODE_TX_OFF        Transmitter disabled
                            ETHTRCV_PHYTXMODE_SCRAMBLER_OFF Scrambler disabled
 *  \return      TRUE     - Transceiver supports the given transmission mode
 *  \return      FALSE    - Transceiver does not support the given transmission mode
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_LL_IsTxmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode);
# endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsCableDiagAvailable()
 *********************************************************************************************************************/
/*! \brief       Checks if the transceiver supports cable diagnostics
 *  \details     -
 *  \param[in]   TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                          minus one.
 *  \return      TRUE     - Transceiver supports cable diagnostics
 *  \return      FALSE    - Transceiver does not support cable diagnostics
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagAvailable(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsCableDiagFinished()
 *********************************************************************************************************************/
/*! \brief         Checks if the transceiver's cable diagnostics has finished
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the Cable diagnostic has
 *                            finished is stored:
 *                            TRUE: Cable diagnostic has finished
 *                            FALSE: Cable diagnostic has not yet finished
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagFinished(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_IsCableDiagPrepared()
 *********************************************************************************************************************/
/*! \brief         Checks if the transceiver's cable diagnostics has been prepared
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the Cable diagnostic has
 *                            been prepared is stored:
 *                            TRUE: Cable diagnostic is prepared
 *                            FALSE: Cable diagnostic is not yet prepared
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagPrepared(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_CheckSwReset()
 *********************************************************************************************************************/
/*! \brief         Checks if the software reset has finished
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where value of the decision, if the SW-Reset has finished
 *                            is stored:
 *                            TRUE: SW-Reset has finished
 *                            FALSE: SW-Reset has not yet finished
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_CheckSwReset(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_GetPhySignalQualityValueInPercent()
 *********************************************************************************************************************/
/*! \brief         Retrieves the signal quality from the transceiver hardware and stores the value in percent.
 *  \details       This function reads the signal quality from the transceiver hardware and performs the necessary
 *                 calculations to retrieve the value in percent. 0 percent corresponds to the worst and 100 percent 
 *                 corresponds to the best signal quality value that can be read from the transceiver.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    ResultPtr  Pointer to the memory address where the read signal quality value in percent is stored.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetPhySignalQualityValueInPercent(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_PerformSwReset()
 *********************************************************************************************************************/
/*! \brief         Performs a software reset.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PerformSwReset(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_InitGlobalVariables()
 *********************************************************************************************************************/
/*! \brief         Initializes global variables.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_InitGlobalVariables(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay()
 *********************************************************************************************************************/
/*! \brief         Enables a delay before link startup.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_RunVendorSpecificInitScripts()
 *********************************************************************************************************************/
/*! \brief         Runs given vendor specific initializations scripts.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_RunVendorSpecificInitScripts(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_EnableConfigAccess()
 *********************************************************************************************************************/
/*! \brief         Enables the configuration access of the transceiver.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_DisableConfigAccess()
 *********************************************************************************************************************/
/*! \brief         Disables the configuration access of the transceiver.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_DisableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

# if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_EnableStartAutoNegotiation()
 *********************************************************************************************************************/
/*! \brief         Enables the auto negotiation.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableStartAutoNegotiation(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

# if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_CheckBaudRate()
 *********************************************************************************************************************/
/*! \brief         Retrieves the baud rate out of the read register value.
 *  \details       -
 *  \param[in]     TrcvIdx      Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[out]    BaudRatePtr  Pointer to the memory address where the retrieved baud rate is stored. Values:
 *                              ETHTRCV_BAUD_RATE_10MBIT   - Linkspeed  10 Mbit/s
 *                              ETHTRCV_BAUD_RATE_100MBIT  - Linkspeed: 100 Mbit/s
 *                              ETHTRCV_BAUD_RATE_1000MBIT - Linkspeed: 1Gb/s
 *  \param[in]     RetVal       State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK       - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK   - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) BaudRatePtr,
    Std_ReturnType RetVal);
# endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_PrepareSignalQualityMeasurement()
 *********************************************************************************************************************/
/*! \brief         Prepares the signal quality measurement.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PrepareSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetTestMode()
 *********************************************************************************************************************/
/*! \brief         Sets the phy into the given test mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     TestMode   Test mode to set. Values:
 *                            ETHTRCV_PHYTESTMODE_NONE - Normal operation
 *                            ETHTRCV_PHYTESTMODE_1 - Test transmitter drop
 *                            ETHTRCV_PHYTESTMODE_2 - Test master timing jitter
 *                            ETHTRCV_PHYTESTMODE_3 - Test slave timing jitter
 *                            ETHTRCV_PHYTESTMODE_4 - Test transmitter distortion
 *                            ETHTRCV_PHYTESTMODE_5 - Test power spectral density
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetPhyLoopbackMode()
 *********************************************************************************************************************/
/*! \brief       Sets the phy into the given loopback mode.
 *  \details     -
 *  \param[in]   TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                              minus one.
 *  \param[in]   LoopbackMode   Loopback mode to set. Values:
 *                              ETHTRCV_PHYLOOPBACK_NONE - Normal operation
 *                              ETHTRCV_PHYLOOPBACK_INTERNAL - Internal Loopback
 *                              ETHTRCV_PHYLOOPBACK_EXTERNAL - External Loopback
 *                              ETHTRCV_PHYLOOPBACK_REMOTE - Remote loopback
 *  \param[in]   RetVal         State of success of the previous operations before the call of this function:
 *                              E_OK     - The previous operations were successful
 *                              E_NOT_OK - At least one of the previous operations has failed
 *  \return      E_OK         - The operations in this function and the previous operations were successful
 *  \return      E_NOT_OK     - Function has been called with invalid parameters or at least one of the hardware operations
 *                              (read/write) in this function or the previous functions has failed
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \pre         -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_SetPhyTxMode()
 *********************************************************************************************************************/
/*! \brief         Sets the phy into the given transmission mode.
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     TxMode     Transmission mode to set. Values:
 *                            ETHTRCV_PHYTXMODE_NORMAL        Normal Operation
 *                            ETHTRCV_PHYTXMODE_TX_OFF        Transmitter disabled
 *                            ETHTRCV_PHYTXMODE_SCRAMBLER_OFF Scrambler disabled
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_FinalizeSignalQualityMeasurement()
 *********************************************************************************************************************/
/*! \brief         Performs configuration which is necessary after a signal quality measurement to resume normal operation
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_FinalizeSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_PrepareCableDiag()
 *********************************************************************************************************************/
/*! \brief         Prepares the transceiver for the retrieval of the cable diagnostics result, for example turning down
 *                 the link
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PrepareCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_EnableDiagnosticSequence()
 *********************************************************************************************************************/
/*! \brief         Enables the transceiver's cable diagnostic measurement sequence
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableDiagnosticSequence(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_CheckCableDiagResult()
 *********************************************************************************************************************/
/*! \brief         Retrieves the result of the cable diagnostics measurement.
 *  \details       -
 *  \param[in]     TrcvIdx             Zero based index of the transceiver. Range: 0 to number of configured
 *                                     transceiver instances minus one.
 *  \param[out]    CableDiagResultPtr  Pointer to the memory address where the result of the cable diagnosis is stored:
 *                                     ETHTRCV_CABLEDIAG_OK: Cable diagnostics result was OK
 *                                     ETHTRCV_CABLEDIAG_ERROR: Cable diagnostics failed
 *                                     ETHTRCV_CABLEDIAG_SHORT: Cable diagnostics detected a short on the MDI
 *                                     ETHTRCV_CABLEDIAG_OPEN: Cable diagnostics detected an open on the MDI
 *  \param[in]     RetVal              State of success of the previous operations before the call of this function:
 *                                     E_OK     - The previous operations were successful
 *                                     E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK              - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK          - Function has been called with invalid parameters or at least one of the hardware
 *                                     operations (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_CheckCableDiagResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) CableDiagResultPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_AdditionalStepsAfterCableDiag()
 *********************************************************************************************************************/
/*! \brief         Performs configuration which is necessary after a cable diagnostics measurement to resume normal
 *                 operation
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_AdditionalStepsAfterCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_ReadIdentifier1Register()
 *********************************************************************************************************************/
/*! \brief         Reads the first identifier register of the transceiver
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    RegValPtr  Pointer to the memory where the content of the first identifier register of the
 *                            transceiver is stored
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ReadIdentifier1Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_ReadIdentifier2Register()
 *********************************************************************************************************************/
/*! \brief         Reads the second identifier register of the transceiver
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \param[out]    RegValPtr  Pointer to the memory where the content of the second identifier register of the
 *                            transceiver is stored
 *  \param[in]     RetVal     State of success of the previous operations before the call of this function:
 *                            E_OK     - The previous operations were successful
 *                            E_NOT_OK - At least one of the previous operations has failed
 *  \return        E_OK     - The operations in this function and the previous operations were successful
 *  \return        E_NOT_OK - Function has been called with invalid parameters or at least one of the hardware operations
 *                            (read/write) in this function or the previous functions has failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ReadIdentifier2Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling()
 *********************************************************************************************************************/
/*! \brief         Main function lower layer implementation which is used for link handling and link startup.
 *  \details       This function is used to perform timing relevant initialization and link startup and/or link
 *                 handling tasks.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES DERIVATIVE SPECIFIC
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_EnableLinkStateDelay()
 *********************************************************************************************************************/
/*! \brief         Enables a delay before link state is reported valid.
 *  \details       The report of a valid link state ACTIVE is delayed by 100ms with a time-out of 200ms if the extended
 *                 link state check is enabled. This function is used to enable the delay by setting the counters.
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           -
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableLinkStateDelay(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1()
 *********************************************************************************************************************/
/*! \brief         Main function sub function which is used for link handling and link startup
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2()
 *********************************************************************************************************************/
/*! \brief         Main function sub function which is used for link handling and link startup
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 *  \pre           EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1() has been called for the transceiver with index
 *                 TrcvIdx
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3()
 *********************************************************************************************************************/
/*! \brief         Main function sub function which is used for link handling and link startup
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 *  \pre           EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1() and
 *                 EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2() have been called for the transceiver with index
 *                 TrcvIdx
 *  \pre           Extended link state check is enabled
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_4()
 *********************************************************************************************************************/
/*! \brief         Main function sub function which is used for link handling and link startup
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 *  \pre           EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1() and
 *                 EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2() and
 *                 EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3() have been called for the transceiver with index
 *                 TrcvIdx
 *  \pre           Extended link state check is enabled
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_4(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_6()
 *********************************************************************************************************************/
/*! \brief         Main function sub function which is used for link handling and link startup
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver instances
 *                            minus one.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   TRUE
 *  \pre           EthTrcv_30_Tja1100_TransceiverInit() has been called for the transceiver with index TrcvIdx
 *  \pre           EthTrcv_30_Tja1100_SetTransceiverMode() has been called for the transceiver with index TrcvIdx with
 *                 mode ACTIVE
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_6(
    uint8 TrcvIdx);

/**********************************************************************************************************************
 *  LOCAL FUNCTION DEFINITION
 **********************************************************************************************************************/
# if !defined(ETHTRCV_30_TJA1100_UNIT_TEST) /* COV_ETHTRCV_TEST_SUITE_UNIT_TESTS */
/**********************************************************************************************************************
 *  START SET MII INTERFACE
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_ClearMiiModeSettings
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ClearMiiModeSettings(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Mii Mode is controlled by generator implementation */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToLightMiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToLightMiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiXtalMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToGmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToGmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiXtalMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetMiiInterfaceToRgmiiXtalMode(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do due to generator */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}
/**********************************************************************************************************************
 *  END SET MII INTERFACE
 *********************************************************************************************************************/
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetBasicConfigurationRegister
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetBasicConfigurationRegister(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  uint16 regVal = EthTrcv_30_Tja1100_GetBasicCtrlRegValOfEthTrcv(TrcvIdx);

  /* #10 Write the configuration 1 register with the configured value since the BCMR is not relevant here */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_CFG1,
      regVal);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_PerformSwReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PerformSwReset(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Enable the software reset in the basic control register */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
      ETHTRCV_30_TJA1100_REG_BMCR_RESET);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_InitGlobalVariables
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_InitGlobalVariables(
    uint8 TrcvIdx)
{
  /* #10 Initialize the link startup state */
  EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_0);                             /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  /* #20 Initialize the link startup delay counter */
  EthTrcv_30_Tja1100_SetLinkStartupDelayCounter(TrcvIdx, ETHTRCV_30_TJA1100_NO_LINK_STARTUP);                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  /* #30 Initialize the link state delay counter */
  EthTrcv_30_Tja1100_SetLinkStateDelayCounter(TrcvIdx, 0);                                                              /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  /* #40 Initialize the link fail counter */
  EthTrcv_30_Tja1100_SetLinkFailCounter(TrcvIdx, 0);                                                                    /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  /* #50 Initialize the link state timeout counter */
  EthTrcv_30_Tja1100_SetLinkStateTimeoutCounter(TrcvIdx, 0);                                                            /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(
    uint8 TrcvIdx)
{
  /* #10 Enter link startup state 1 */
  EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_1);                             /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  /* #20 Set the link startup delay counter to a value that corresponds to 2 ms of delay */
  EthTrcv_30_Tja1100_SetLinkStartupDelayCounter(TrcvIdx,                                                                /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      (EthTrcv_30_Tja1100_GetLinkStartupDelayOfEthTrcvTja1100(TrcvIdx) / EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMs()) + 1);
  /* #50 Reset the link fail counter */
  EthTrcv_30_Tja1100_SetLinkFailCounter(TrcvIdx, 0);                                                                    /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_EnableLinkStateDelay
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableLinkStateDelay(
    uint8 TrcvIdx)
{
  /* #10 Set the link state delay counter to a value that corresponds to 100 ms of delay */
  EthTrcv_30_Tja1100_SetLinkStateDelayCounter(TrcvIdx,                                                                  /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      (uint32)(ETHTRCV_30_TJA1100_LINK_STATE_DELAY_MS / EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMs()));
  /* #20 Set the link state timeout counter to a value that corresponds to 200 ms of delay */
  EthTrcv_30_Tja1100_SetLinkStateTimeoutCounter(TrcvIdx,                                                                 /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      (uint32)((ETHTRCV_30_TJA1100_LINK_STATE_DELAY_TIMEOUT_MS) / EthTrcv_30_Tja1100_GetMainFunctionLinkHandlingMs()));
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsTransceiverAccessOk(
    uint8 TrcvIdx)
{

  Std_ReturnType                                    retVal;
  boolean                                           retValDecision;
  uint16                                            regVal = 0;
  EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type derivative = EthTrcv_30_Tja1100_GetDerivativeOfEthTrcvTja1100(TrcvIdx);

  /* #10 The configured derivative is a Tja1100 */
  if(derivative == ETHTRCV_30_TJA1100_TJA1100_DERIVATIVEOFETHTRCVTJA1100)
  {
    /* #110 Read the first PHY identifier register */
    retVal = EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR1,
        &regVal);                                                                                                       /* SBSW_ETHTRCV_REF_OF_STACK_VAR */
  }
  /* #20 The configured derivative is either Tja1101 or Tja1102 */
  else if((derivative == ETHTRCV_30_TJA1100_TJA1102_DERIVATIVEOFETHTRCVTJA1100) ||
          (derivative == ETHTRCV_30_TJA1100_TJA1101_DERIVATIVEOFETHTRCVTJA1100))
  {
    EthTrcv_30_Tja1100_P0MiiAddressOfEthTrcvTja1100Type p0MiiAddress = EthTrcv_30_Tja1100_GetP0MiiAddressOfEthTrcvTja1100(TrcvIdx);
    EthTrcv_30_Tja1100_AccessEntityFctsIdxOfEthTrcvType accessEntityFctsIdx = EthTrcv_30_Tja1100_GetAccessEntityFctsIdxOfEthTrcv(TrcvIdx);

    /* #210 The PHY is managed by a switch */
    if(p0MiiAddress == ETHTRCV_30_TJA1100_NO_P0MIIADDRESSOFETHTRCVTJA1100)
    {
      EthTrcv_30_Tja1100_P0SwitchSnvOfEthTrcvTja1100Type switchSnv = EthTrcv_30_Tja1100_GetP0SwitchSnvOfEthTrcvTja1100(TrcvIdx);
      EthTrcv_30_Tja1100_P0PortSnvOfEthTrcvTja1100Type   portSnv = EthTrcv_30_Tja1100_GetP0PortSnvOfEthTrcvTja1100(TrcvIdx);
      /* #2110 Read the first identifier register of the PHY P0 over the switch interface */
      retVal = EthTrcv_30_Tja1100_GetReadTrcvRegOfAccessEntityFcts(accessEntityFctsIdx)(
        switchSnv,
        portSnv,
        ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR1,
        &regVal);                                                                                                       /* SBSW_ETHTRCV_DRVAPI_FCT_PTR_MAN_CSL03_REF_OF_STACK_VAR */
    }
    /* #220 The PHY is managed via a MII management interface */
    else
    {
      EthTrcv_30_Tja1100_AccessEntitySnvOfEthTrcvType accessSnv = EthTrcv_30_Tja1100_GetAccessEntitySnvOfEthTrcv(TrcvIdx);
      /* #2210 Read the first identifier register of the P0-PHY */
      retVal = EthTrcv_30_Tja1100_GetReadTrcvRegOfAccessEntityFcts(accessEntityFctsIdx)(
          accessSnv,
          p0MiiAddress,
          ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR1,
          &regVal);                                                                                                     /* SBSW_ETHTRCV_DRVAPI_FCT_PTR_MAN_CSL03_REF_OF_STACK_VAR */
    }
  }
  /* #30 The derivative is not supported */
  else
  {
    /* #310 Return E_NOT_OK */
    retVal = E_NOT_OK;
  }
  /* #40 No previous operation has failed and the read register value is correct */
  if((retVal == E_OK) && (regVal == ETHTRCV_30_TJA1100_REG_PHYIDR1_NXP_OUI_MSB))
  {
    /* #410 The transceiver management access is working */
    retValDecision = TRUE;
  }
  /* #50 At least one previous operation has failed or the read register value is not correct */
  else
  {
    /* #510 The transceiver management access is not working */
    retValDecision = FALSE;
  }
  return retValDecision;
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_ApplyAdditionalConfigSteps
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ApplyAdditionalConfigSteps(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  EthTrcv_30_Tja1100_DerivativeOfEthTrcvTja1100Type derivative = EthTrcv_30_Tja1100_GetDerivativeOfEthTrcvTja1100(TrcvIdx);
  Std_ReturnType retVal = RetVal;

  /* #10 The derivative is either configured to be a Tja1101 or Tja1102 */
  if((derivative == ETHTRCV_30_TJA1100_TJA1102_DERIVATIVEOFETHTRCVTJA1100) ||
     (derivative == ETHTRCV_30_TJA1100_TJA1101_DERIVATIVEOFETHTRCVTJA1100))
  {
    /* #110 Disable autonomous operation in the common configuration register */
    retVal |=  EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        ETHTRCV_30_TJA1100_REG_COMMON_CFG_AUTO_OP_TJA1102);

    /* #120 Set the configuration for the Clock Mode. */
    EthTrcv_30_Tja1100_LL_SetClkMode(TrcvIdx);

    /* #130 Set the configuration for the LDO mode. */
    EthTrcv_30_Tja1100_LL_SetLdoMode(TrcvIdx);

    /* #140 If the derivative is a TJA1102 */
    if(derivative == ETHTRCV_30_TJA1100_TJA1102_DERIVATIVEOFETHTRCVTJA1100)
    {
      /* #1410 Set the configuration for the internal reverse MII mode */
      EthTrcv_30_Tja1100_LL_SetRevMiiMode(TrcvIdx);

      /* #1420 Set the PHY_ENABLE configuration. */
      EthTrcv_30_Tja1100_LL_SetPhyEnable(TrcvIdx);
    }
  }
  /* #20 Another derivative is configured */
  /* #210 Nothing to do */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetClkMode
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetClkMode(
    uint8 TrcvIdx)
{
  EthTrcv_30_Tja1100_ClkModeOfEthTrcvTja1100Type clkMode;
  clkMode = EthTrcv_30_Tja1100_GetClkModeOfEthTrcvTja1100(TrcvIdx);

  /* #10 If the strapping configuration of the clock mode should be overwritten. */
  if(clkMode != ETHTRCV_30_TJA1100_INVALID_CLOCK_MODE_CLKMODEOFETHTRCVTJA1100)
  {
    uint16 regVal;

    /* #110 Read the common configuration register. */
    (void)EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        &regVal);                                                                                                       /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

    /* #120 Clear the current clock mode setting. */
    regVal &= (uint16)(~(uint32)ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_MODE_MASK_TJA1102);

    /* #130 If the clock mode should be set to 25MHz XTAL, with clock output at CLK_IN_OUT. */
    if(clkMode == ETHTRCV_30_TJA1100_ETHTRCV_25_MHZ_XTAL_CLOCK_OUTPUT_CLKMODEOFETHTRCVTJA1100)
    {
      /* #1310 Set the register value accordingly. */
      regVal |= ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_25MHZ_XTAL_OUT_TJA1102;
    }
    /* #140 If the clock mode should be set to 25MHz external clock input at CLK_IN_OUT. */
    else if(clkMode == ETHTRCV_30_TJA1100_ETHTRCV_25_MHZ_EXT_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100)
    {
      /* #1410 Set the register value accordingly. */
      regVal |= ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_25MHZ_EXT_CLK_TJA1102;
    }
    /* #150 If the clock mode should be set to 50 MHz REF clock input at CLK_IN_OUT. */
    else if(clkMode == ETHTRCV_30_TJA1100_ETHTRCV_50_MHZ_REF_CLOCK_INPUT_CLKMODEOFETHTRCVTJA1100)
    {
      /* #1510 Set the register value accordingly. */
      regVal |= ETHTRCV_30_TJA1100_REG_COMMON_CFG_CLK_50MHZ_REF_CLK_TJA1102;
    }
    /* #160 Otherwise, i.e. the clock mode should be set to 25MHz XTAL, no clock at CLK_IN_OUT. . */
    else
    {
      /* #1610 No action necessary, clock mode already set correctly due to the clearing. */
    }

    /* #170 Write the common configuration register with the set register value. */
    (void)EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        regVal);
  }
} /* EthTrcv_30_Tja1100_LL_SetClkMode() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetLdoMode
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetLdoMode(
    uint8 TrcvIdx)
{
  EthTrcv_30_Tja1100_LdoModeOfEthTrcvTja1100Type ldoMode;
  ldoMode = EthTrcv_30_Tja1100_GetLdoModeOfEthTrcvTja1100(TrcvIdx);

  /* #10 If the strapping configuration of the LDO mode should be overwritten by enabling the internal LDO. */
  if(ldoMode == ETHTRCV_30_TJA1100_LDO_ENABLED_LDOMODEOFETHTRCVTJA1100)
  {
    /* #110 Clear the LDO mode bit in the common configuration register. */
    (void)EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        ETHTRCV_30_TJA1100_REG_COMMON_CFG_LDO_MODE_DISABLED);

  }
  /* #20 If the strapping configuration of the LDO mode should be overwritten by disabling the internal LDO. */
  else if(ldoMode == ETHTRCV_30_TJA1100_LDO_DISABLED_LDOMODEOFETHTRCVTJA1100)
  {
    /* #210 Set the LDO mode bit in the common configuration register. */
    (void)EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        ETHTRCV_30_TJA1100_REG_COMMON_CFG_LDO_MODE_DISABLED);
  }
  /* #30 If the strapping configuration of the LDO mode should not be overwritten. */
  else
  {
    /* #310 Perform no action. */
  }
} /* EthTrcv_30_Tja1100_LL_SetLdoMode() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetRevMiiMode
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetRevMiiMode(
    uint8 TrcvIdx)
{
  EthTrcv_30_Tja1100_IntRevMiiOfEthTrcvTja1100Type intRevMiiMode;
  intRevMiiMode = EthTrcv_30_Tja1100_GetIntRevMiiOfEthTrcvTja1100(TrcvIdx);

  /* #10 If the strapping configuration of the internal reverse MII mode should be overwritten by enabling the internal
   *     reverse MII mode. */
  if(intRevMiiMode == ETHTRCV_30_TJA1100_INT_REV_MII_ENABLED_INTREVMIIOFETHTRCVTJA1100)
  {
    /* #110 Set the internal reverse MII mode bit in the common configuration register. */
    (void)EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        ETHTRCV_30_TJA1100_REG_COMMON_CFG_INT_REV_MII_ENABLED);

  }
  /* #20 If the strapping configuration of the internal reverse MII mode should be overwritten by disabling the internal
   *     reverse MII mode. */
  else if(intRevMiiMode == ETHTRCV_30_TJA1100_INT_REV_MII_DISABLED_INTREVMIIOFETHTRCVTJA1100)
  {
    /* #210 Clear the internal reverse MII mode bit in the common configuration register. */
    (void)EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COMMON_CFG,
        ETHTRCV_30_TJA1100_REG_COMMON_CFG_INT_REV_MII_ENABLED);
  }
  /* #30 If the strapping configuration of the internal reverse MII mode should not be overwritten. */
  else
  {
    /* #310 Perform no action. */
  }
} /* EthTrcv_30_Tja1100_LL_SetRevMiiMode() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetPhyEnable
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyEnable(
    uint8 TrcvIdx)
{
  EthTrcv_30_Tja1100_PhyEnableOfEthTrcvTja1100Type phyEnable;
  phyEnable = EthTrcv_30_Tja1100_GetPhyEnableOfEthTrcvTja1100(TrcvIdx);

  /* #10 If the strapping configuration of the PHY_ENABLE should be overwritten by enabling the PHY. */
  if(phyEnable == ETHTRCV_30_TJA1100_PHY_ENABLED_PHYENABLEOFETHTRCVTJA1100)
  {
    /* #110 Set the PHY_ENABLE bit in the configuration 3 register. */
    (void)EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_CFG_3,
        ETHTRCV_30_TJA1100_REG_CFG_3_PHY_EN);

  }
  /* #20 If the strapping configuration of the PHY_ENABLE should be overwritten by disabling the PHY. */
  else if(phyEnable == ETHTRCV_30_TJA1100_PHY_DISABLED_PHYENABLEOFETHTRCVTJA1100)
  {
    /* #210 Clear the PHY_ENABLE bit in the configuration 3 register. */
    (void)EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_CFG_3,
        ETHTRCV_30_TJA1100_REG_CFG_3_PHY_EN);
  }
  /* #30 If the strapping configuration of the PHY_ENABLE should not be overwritten. */
  else
  {
    /* #310 Perform no action. */
  }
} /* EthTrcv_30_Tja1100_LL_SetPhyEnable() */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsSetTestModeAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsSetTestModeAvailable(
    uint8 TrcvIdx)
{
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Return that setting the test mode is available */
  return TRUE;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsSignalQualityAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsSignalQualityAvailable(
    uint8 TrcvIdx)
{
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Return that getting the signal quality is available */
  return TRUE;
}

#  if ( ETHTRCV_30_TJA1100_DEV_ERROR_DETECT == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsTestmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsTestmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode)
{
  boolean retValDecision;
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 The TestMode parameter corresponds to a supported test mode */
  if((TestMode == ETHTRCV_PHYTESTMODE_NONE)||
     (TestMode == ETHTRCV_PHYTESTMODE_1)   ||
     (TestMode == ETHTRCV_PHYTESTMODE_2)   ||
     (TestMode == ETHTRCV_PHYTESTMODE_3)   ||
     (TestMode == ETHTRCV_PHYTESTMODE_4)   ||
     (TestMode == ETHTRCV_PHYTESTMODE_5)   ||
     (TestMode == ETHTRCV_30_TJA1100_PHY_TEST_MODE_6))
  {
    /* #110 Return that the test mode is supported by the hardware */
    retValDecision = TRUE;
  }
  /* #20 The TestMode parameter does not correspond to a supported test mode */
  else
  {
    /* #210 Return that the test mode is not supported by the hardware */
    retValDecision = FALSE;
  }
  return retValDecision;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsLoopbackmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsLoopbackmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode)
{
  boolean retValDecision;
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 The LoopbackMode parameter corresponds to a supported loopback mode */
  if((LoopbackMode == ETHTRCV_PHYLOOPBACK_NONE)     ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_INTERNAL) ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_EXTERNAL) ||
     (LoopbackMode == ETHTRCV_PHYLOOPBACK_REMOTE))
  {
    /* #110 Return that the loopback mode is supported by the hardware */
    retValDecision = TRUE;
  }
  /* #20 The LoopbackMode parameter does not correspond to a supported loopback mode*/
  else
  {
    /* #210 Return that the loopback mode is not supported by the hardware */
    retValDecision = FALSE;
  }

  return retValDecision;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsTxmodeSupportedByHw
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE)  EthTrcv_30_Tja1100_LL_IsTxmodeSupportedByHw(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode)
{
  boolean retValDecision;
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 The TxMode parameter corresponds to a supported Tx mode */
  if((TxMode == ETHTRCV_PHYTXMODE_NORMAL) ||
     (TxMode == ETHTRCV_PHYTXMODE_TX_OFF) ||
     (TxMode == ETHTRCV_PHYTXMODE_SCRAMBLER_OFF))
  {
    /* #110 Return that the Tx mode is supported by the hardware */
    retValDecision = TRUE;
  }
  /* #20 The TxMode parameter does not correspond to a supported Tx mode */
  else
  {
    /* #210 Return that the Tx mode is not supported by the hardware */
    retValDecision = FALSE;
  }
  return retValDecision;
}
#  endif /* ETHTRCV_30_TJA1100_DEV_ERROR_DETECT */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsCableDiagAvailable
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(boolean, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagAvailable(
    uint8 TrcvIdx)
{
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Return that getting the cable diagnostics results is available */
  return TRUE;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsCableDiagFinished
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagFinished(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  boolean stillRunning;

  retVal |= EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CABLE_TEST_ENABLE,
      &stillRunning);                                                                                                   /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  if(stillRunning == TRUE)
  {
    *ResultPtr = FALSE;                                                                                                 /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  else
  {
    *ResultPtr = TRUE;                                                                                                  /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_IsCableDiagPrepared
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_IsCableDiagPrepared(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  boolean result        = FALSE;

  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Return FALSE to keep waiting until both link partners stop sending symbols on the MDI */
  *ResultPtr = result;                                                                                                   /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_CheckSwReset
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_CheckSwReset(
    uint8 TrcvIdx,
    P2VAR(boolean, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  boolean isSwResetFinished;
  Std_ReturnType retVal = RetVal;

  /* #10 Read the basic control register and return FALSE if the software reset bit is already cleared */
  retVal |= EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
      ETHTRCV_30_TJA1100_REG_BMCR_RESET,
      &isSwResetFinished);                                                                                              /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Return the inverse of the previous check to indicate if the reset has already finished */
  if(isSwResetFinished == FALSE)
  {
    *ResultPtr = TRUE;                                                                                                  /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  else
  {
    *ResultPtr = FALSE;                                                                                                 /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_GetTransceiverMode
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetTransceiverMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) TrcvModePtr,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Read the extended control register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      &regVal);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 The mode bits are set to normal mode */
  if((regVal & ETHTRCV_30_TJA1100_REG_EXTCTRL_MODE_MASK) == ETHTRCV_30_TJA1100_REG_EXTCTRL_NORMAL_MODE)
  {
    /* #210 Report the transceiver mode to be ACTIVE */
    *TrcvModePtr = ETHTRCV_MODE_ACTIVE;                                                                                 /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  /* #30 The mode bits are not set to normal mode */
  else
  {
    /* #220 Report the transceiver mode to be DOWN */
    *TrcvModePtr = ETHTRCV_MODE_DOWN;                                                                                   /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }
  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_GetLinkState
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetLinkState(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) LinkStatePtr,
    Std_ReturnType RetVal)
{
  boolean        result;
  Std_ReturnType retVal = RetVal;

  /* #10 Currently no link startup is performed */
  if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_5)
  {
    /* #110 Check if the link state bits are set in the communication status register */
    retVal |= EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT,
        ETHTRCV_30_TJA1100_REG_COM_STAT_LINK_STATE_UP_MASK,
        &result);                                                                                                       /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

    /* #120 All link state bits are set in the communication status register */
    if(result ==  TRUE)
    {
      /* #1210 Reset the link fail counter */
      EthTrcv_30_Tja1100_SetLinkFailCounter(TrcvIdx, 0);                                                                /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      /* #1220 Report the link state to be ACTIVE */
      *LinkStatePtr = ETHTRCV_LINK_STATE_ACTIVE;                                                                        /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
    }
    /* #130 At least one link state bit is not set in the communication status register */
    else
    {
      /* #1310 Increment the link fail counter, no error processing is performed in case of overflow */
      EthTrcv_30_Tja1100_IncLinkFailCounter(TrcvIdx);                                                                   /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
      /* #1320 Report the link state to be DOWN */
      *LinkStatePtr = ETHTRCV_LINK_STATE_DOWN;                                                                          /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
    }
  }
  /* #20 Currently a link startup is performed */
  else
  {
    /* #210 Report the link state to be DOWN */
    *LinkStatePtr = ETHTRCV_LINK_STATE_DOWN;                                                                            /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
}

#  if ( ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_GetDuplexMode
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetDuplexMode(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) DuplexModePtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Report that the duplex mode is full duplex */
  *DuplexModePtr = ETHTRCV_DUPLEX_MODE_FULL;                                                                            /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  return retVal;
}
#  endif /* ETHTRCV_30_TJA1100_ENABLE_GET_DUPLEX_MODE */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_GetPhySignalQualityValueInPercent
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetPhySignalQualityValueInPercent(
    uint8 TrcvIdx,
    P2VAR(uint8, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) ResultPtr,
    Std_ReturnType RetVal)
{
  uint8          signalQualityValue;
  uint16         regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Read the communication status register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT,
      &regVal);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 Calculate the signal quality in percent */
  signalQualityValue = (uint8)((regVal & ETHTRCV_30_TJA1100_REG_COM_STAT_SIGNAL_QUALITY_MASK)
                                       >> ETHTRCV_30_TJA1100_REG_COM_STAT_SIGNAL_QUALITY_SHIFT);

  signalQualityValue = (uint8)(((uint16)signalQualityValue * ETHTRCV_30_TJA1100_MAXIMUM_SIGNAL_QUALITY_PERCENTAGE)
      / ETHTRCV_30_TJA1100_SIGNAL_QUALITY_BORDERS);

  /* #30 Return the result */
  *ResultPtr = signalQualityValue;                                                                                      /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_RunVendorSpecificInitScripts
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_RunVendorSpecificInitScripts(
    uint8 TrcvIdx)
{
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */
  /* #10 Nothing to do */
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_EnableConfigAccess
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Enable the configuration access in the extended control register */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CONFIG_EN);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_DisableConfigAccess
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_DisableConfigAccess(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Disable the configuration access in the extended control register */
  retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CONFIG_EN);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetTransceiverModeActive
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetTransceiverModeActive(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Clear the power down bit in the basic control register */
  retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
      ETHTRCV_30_TJA1100_REG_BMCR_POWER_DOWN);

  /* #20 Read the extended control register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      &regVal);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #30 Clear the mode and link control bits */
  regVal &= (uint16)(~(uint32)(ETHTRCV_30_TJA1100_REG_EXTCTRL_MODE_MASK | ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL));

  /* #40 Set the mode bits to normal mode */
  regVal |= ETHTRCV_30_TJA1100_REG_EXTCTRL_NORMAL_MODE;

  /* #50 Write the extended control register */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      regVal);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetTransceiverModeDown
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetTransceiverModeDown(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Set the power down bit in the basic control register */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
      ETHTRCV_30_TJA1100_REG_BMCR_POWER_DOWN);

  return retVal;
}

#  if ( ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_EnableStartAutoNegotiation
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableStartAutoNegotiation(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}
#  endif /* ETHTRCV_30_TJA1100_ENABLE_START_AUTO_NEG */

#  if ( ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE == STD_ON )
/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_GetBaudRate
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_GetBaudRate(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) BaudRatePtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  /* #10 Report that the baud rate is 100 Mbit/s */
  *BaudRatePtr = ETHTRCV_BAUD_RATE_100MBIT;                                                                             /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */

  return retVal;
}
#  endif /* ETHTRCV_30_TJA1100_ENABLE_GET_BAUD_RATE */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_PrepareSignalQualityMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PrepareSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;
  /* #10 Nothing to do */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetPhyTestMode
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyTestMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTestModeType TestMode,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Enable the configuration access */
  retVal |= EthTrcv_30_Tja1100_LL_EnableConfigAccess(TrcvIdx, RetVal);

  /* #20 Clear the current test mode settings */
  retVal |=  EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_TEST_MODE_MASK);

  /* #30 The PHY shall be put in a test mode */
  if((TestMode == ETHTRCV_PHYTESTMODE_1) ||
     (TestMode == ETHTRCV_PHYTESTMODE_2) ||
     (TestMode == ETHTRCV_PHYTESTMODE_3) ||
     (TestMode == ETHTRCV_PHYTESTMODE_4) ||
     (TestMode == ETHTRCV_PHYTESTMODE_5) ||
     (TestMode == ETHTRCV_30_TJA1100_PHY_TEST_MODE_6))
  {
    /* #310 Set up chosen test mode */
    regVal = (uint16)((uint32)TestMode << (uint32)ETHTRCV_30_TJA1100_REG_EXTCTRL_TEST_MODE_SHIFT);

    /* #320 Write test mode setting */
    retVal |=  EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
        regVal);

    /* #330 Disable link control */
    retVal |=  EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
        ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);
  }
  /* #40 The PHY shall not be put in a test mode */
  else
  {
    /* #410 Enable link control */
    retVal |=  EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
        ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);
  }

  /* #50 Disable the configuration access */
  retVal |= EthTrcv_30_Tja1100_LL_DisableConfigAccess(TrcvIdx, RetVal);

  return retVal;
} /*lint !e438 */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetPhyLoopbackMode
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyLoopbackMode(
    uint8 TrcvIdx,
    EthTrcv_PhyLoopbackModeType LoopbackMode,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Disable link control */
  retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

  /* #20 Read the extended control register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      &regVal);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #30 Clear the current loopback mode settings */
  regVal &= (uint16)ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_CLEAR;

  /* #40 The external loopback mode shall be enabled */
  if(LoopbackMode == ETHTRCV_PHYLOOPBACK_EXTERNAL)
  {
    /* #410 Set external loopback mode bit in the register value */
    regVal |= (uint16)ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_EXT;
  }
  /* #50 The remote loopback mode shall be enabled */
  else if(LoopbackMode == ETHTRCV_PHYLOOPBACK_REMOTE)
  {
    /* #510 Set the remote loopback mode bit in the register value */
    regVal |= (uint16)ETHTRCV_30_TJA1100_REG_EXTCTRL_LOOPBACK_MODE_REM;
  }
  /* #60 Neither external nor remote loopback mode shall be enabled */
  else
  {
    /* #610 Nothing to do */
  }

  /* #70 Write the loopback mode configuration register */
  retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      regVal);

  /* #80 No loopback mode shall be enabled */
  if(LoopbackMode == ETHTRCV_PHYLOOPBACK_NONE)
  {
    /* #810 Disable loopback operation in basic control register */
    retVal |=  EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
        ETHTRCV_30_TJA1100_REG_BMCR_LOOPBACK);
  }
  /* #90 Loopback operation is requested */
  else
  {
    /* #910 Enable loopback operation in Basic Control Register */
    retVal |=  EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
        ETHTRCV_30_TJA1100_REG_BMCR_LOOPBACK);
  }
  /* #100 Enable link control */
  retVal |=  EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_FinalizeSignalQualityMeasurement
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_FinalizeSignalQualityMeasurement(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Nothing to do */
  ETHTRCV_30_TJA1100_DUMMY_STATEMENT(TrcvIdx); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /*lint !e438 */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_PrepareCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_PrepareCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Disable link control */
  retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_PrepareCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_EnableDiagnosticSequence(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Enable the cable diagnostics test sequence */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CABLE_TEST_ENABLE);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_CheckCableDiagResult
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_CheckCableDiagResult(
    uint8 TrcvIdx,
    P2VAR(EthTrcv_CableDiagResultType, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) CableDiagResultPtr,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Read cable diag status register */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXT_STAT,
      &regVal);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 The cable diag status register could be read successfully */
  if(retVal == E_OK)
  {
    uint16 cableDiagResult = (uint16)((uint32)regVal & (uint32)ETHTRCV_30_TJA1100_REG_EXT_STAT_CABLE_DIAG_RESULT_MASK);

    /* #210 Report the result of the cable diagnostic */
    switch(cableDiagResult)
    {
    case ETHTRCV_30_TJA1100_REG_EXT_STAT_OK:
      *CableDiagResultPtr = ETHTRCV_CABLEDIAG_OK;                                                                       /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      break;
    case ETHTRCV_30_TJA1100_REG_EXT_STAT_SHORT_DETECT:
      *CableDiagResultPtr = ETHTRCV_CABLEDIAG_SHORT;                                                                    /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      break;
    case ETHTRCV_30_TJA1100_REG_EXT_STAT_OPEN_DETECT:
      *CableDiagResultPtr = ETHTRCV_CABLEDIAG_OPEN;                                                                     /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      break;
    default:
      *CableDiagResultPtr = ETHTRCV_CABLEDIAG_ERROR;                                                                    /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
      break;
    }
  }
  /* #30 The cable diag status register could not be read successfully */
  else
  {
    /* #310 Report that the cable diagnostic failed  */
    *CableDiagResultPtr = ETHTRCV_CABLEDIAG_ERROR;                                                                      /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_WRITE */
  }

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_AdditionalStepsAfterCableDiag
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_AdditionalStepsAfterCableDiag(
    uint8 TrcvIdx,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Enable link control to resume normal operation */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_SetPhyTxMode
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_SetPhyTxMode(
    uint8 TrcvIdx,
    EthTrcv_PhyTxModeType TxMode,
    Std_ReturnType RetVal)
{
  uint16 regVal;
  Std_ReturnType retVal = RetVal;

  /* #10 Enable configuration access */
  retVal |= EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CONFIG_EN);

  switch(TxMode)
  {
    /* #20 The Tx mode shall be set to normal */
    case ETHTRCV_PHYTXMODE_NORMAL:
      /* #210 Read the communication status register */
      retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT,
          &regVal);                                                                                                     /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

      /* #220 Transmission mode is not normal */
      if((regVal & ETHTRCV_30_TJA1100_REG_COM_STAT_TX_MODE_MASK) != ETHTRCV_30_TJA1100_REG_COM_STAT_TX_MODE_SEND_N)
      {
        /* #2210 Perform software reset in next main function */
        EthTrcv_30_Tja1100_SetLinkFailCounter(TrcvIdx,                                                                  /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
            EthTrcv_30_Tja1100_GetLinkFailCounterResetValOfEthTrcvTja1100(TrcvIdx));
      }

      /* #230 Resume master/slave setting */
      retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_CFG1,
          &regVal);                                                                                                     /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

      if(EthTrcv_30_Tja1100_GetConnectionNegOfEthTrcv(TrcvIdx) == ETHTRCV_30_TJA1100_CONN_NEG_MASTER_CONNECTIONNEGOFETHTRCV)
      {
        regVal |= ETHTRCV_30_TJA1100_REG_CFG1_MASTER_SLAVE;
      }
      else
      {
        regVal &= (uint16)(~(uint32)ETHTRCV_30_TJA1100_REG_CFG1_MASTER_SLAVE);
      }

      retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_CFG1,
          regVal);

      break;

    /* #30 The Tx mode shall be set to Tx off */
    case ETHTRCV_PHYTXMODE_TX_OFF:
      /* #310 Disable Link Control */
      retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
          ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);
      break;

    /* #40 The Tx mode shall be set to scrambler off */
    case ETHTRCV_PHYTXMODE_SCRAMBLER_OFF:
      /* #410 Set the transceiver to slave and enable link control */
      retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_CFG1,
          &regVal);                                                                                                     /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

      if((regVal & ETHTRCV_30_TJA1100_REG_CFG1_MASTER_SLAVE) != 0)
      {
        regVal &= (uint16)(~(uint32)ETHTRCV_30_TJA1100_REG_CFG1_MASTER_SLAVE);
      }

      retVal |= EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
          TrcvIdx,
          ETHTRCV_30_TJA1100_REG_OFFS_CFG1,
          regVal);

      break;
    default:
      retVal = E_NOT_OK;
  }
  /* #50 Disable config access */
  retVal |= EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_CONFIG_EN);

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling(
    uint8 TrcvIdx)
{
  /* #10 Current state is STATE 1: Link down, transceiver mode active */
  if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_1)
  {
    EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1(TrcvIdx);
  }
  /* #20 Current state is STATE 2: Link control can now be enabled */
  else if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_2)
  {
    EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2(TrcvIdx);
  }
  /* #30 Current state is STATE 3: Extended link state check is necessary */
  else if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_3)
  {
    /* #310 Call MainFunctionLinkHandling_State_3 */
    EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3(TrcvIdx);
  }
  /* #40 Current state is STATE 4: Exdended link state check is ongoing */
  else if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_4)
  {
    /* #410 Call MainFunctionLinkHandling_State_4 */
    EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_4(TrcvIdx);
  }
  /* #50 Current state is STATE 6: A software reset is required */
  else if(EthTrcv_30_Tja1100_GetLinkStartupState(TrcvIdx) == ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_6)
  {
    /* #510 Call MainFunctionLinkHandling_State_6 */
    EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_6(TrcvIdx);
  }
  /* #60 Current state is STATE 5: The link is active and can be reported as active */
  else
  {
    /* #610 Link state active, nothing to do */
  }
  /* #70 Check the link fail counter for an overflow and set the state to STATE 6 in this case */
  if(EthTrcv_30_Tja1100_GetLinkFailCounter(TrcvIdx) >= EthTrcv_30_Tja1100_GetLinkFailCounterResetValOfEthTrcvTja1100(TrcvIdx))
  {
    EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_6);                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
} /* PRQA S 6050, 6080 */ /* MD_MSR_STCAL, MD_MSR_STMIF */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_1(
    uint8 TrcvIdx)
{
  /* #10 A link startup is required, and a delay (> 2ms) has passed */
  if(EthTrcv_30_Tja1100_GetLinkStartupDelayCounter(TrcvIdx) == 0)
  {
    /* #110 Proceed to STATE 2 */
    EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_2);                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
  /* #20 The startup delay has not yet passed */
  else
  {
    /* #210 Decrement the link startup delay counter */
    EthTrcv_30_Tja1100_DecLinkStartupDelayCounter(TrcvIdx);                                                             /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_2(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal;
  /* #10 Enable link control */
  retVal = EthTrcv_30_Tja1100_ReadSetBitMaskWrite(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
      ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

  /* #20 Link control could be enabled successfully */
  if(retVal == E_OK)
  {
    /* #210 Disable startup delay counter until next startup is required */
    EthTrcv_30_Tja1100_SetLinkStartupDelayCounter(TrcvIdx, ETHTRCV_30_TJA1100_NO_LINK_STARTUP);                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */

    /* #220 An extended link state check is necessary */
    if(EthTrcv_30_Tja1100_IsExtLinkStateCheckEnabledOfEthTrcvTja1100(TrcvIdx) == TRUE)
    {
      EthTrcv_30_Tja1100_LL_EnableLinkStateDelay(TrcvIdx);
      /* #2210 Proceed to STATE 3 and perform an extended link state check */
      EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_3);                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #230 An extended link state check is not necessary */
    else
    {
      /* #2310 Proceed to state 5 and skip the link state check */
      EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_5);                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
  }
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3
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
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_3(
    uint8 TrcvIdx)
{
  boolean result;
  /* #10 Check the current link state on the hardware */
  (void)EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT,
      ETHTRCV_30_TJA1100_REG_COM_STAT_LINK_STATE_UP_MASK,
      &result);                                                                                                         /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

  /* #20 The link is stable and up according to the hardware */
  if(result == TRUE)
  {
    /* #210 Enable a 100ms delay until the link is checked again */
    EthTrcv_30_Tja1100_LL_EnableLinkStateDelay(TrcvIdx);
    /* #220 Leave the state and proceed to STATE 4 */
    EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_4);                           /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
  /* #30 The link is not stable and the link state timeout counter is at its timeout value */
  else if(EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(TrcvIdx) == 0 )
  {
    /* #310 Disable the link and restart the link-up procedure */
    (void)EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
        ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

    EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(TrcvIdx);
  }
  /* #40 The link is not stable yet and the timeout counter is not yet at its timeout value */
  else
  {
    /* #410 Stay in the same state */
  }

  /* #50 Decrement link state timeout counter */
  if(EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(TrcvIdx) > 0)
  {
    EthTrcv_30_Tja1100_DecLinkStateTimeoutCounter(TrcvIdx);                                                             /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_4
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
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_4(
    uint8 TrcvIdx)
{
  boolean result;

  /* #10 The link state delay counter has reached the value meaning that 100ms have passed */
  if(EthTrcv_30_Tja1100_GetLinkStateDelayCounter(TrcvIdx) == 0)
  {
    /* #110 Check the current link state on the hardware */
    (void)EthTrcv_30_Tja1100_ReadAndCompareToBitMask(
        TrcvIdx,
        ETHTRCV_30_TJA1100_REG_OFFS_COM_STAT,
        ETHTRCV_30_TJA1100_REG_COM_STAT_LINK_STATE_UP_MASK,
        &result);                                                                                                       /* SBSW_ETHTRCV_REF_OF_STACK_VAR */

    /* #120 The current link state on the hardware is up and stable */
    if(result == TRUE)
    {
      /* #1210 Leave the state and proceed to STATE 5. The link can now be reported to other modules as being stable and up */
      EthTrcv_30_Tja1100_SetLinkStartupState(TrcvIdx, ETHTRCV_30_TJA1100_LINK_STARTUP_STATE_5);                         /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
    }
    /* #130 The current link state on the hardware is down or unstable */
    else
    {
      /* #1310 The link state timeout counter has reached its timeout value */
      if(EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(TrcvIdx) == 0 )
      {
        /* #13110 Disable the link and restart the link startup procedure */
        (void)EthTrcv_30_Tja1100_ReadClearBitMaskWrite(
            TrcvIdx,
            ETHTRCV_30_TJA1100_REG_OFFS_EXCTRL,
            ETHTRCV_30_TJA1100_REG_EXTCTRL_LINK_CONTROL);

        EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(TrcvIdx);
      }
    }
  }
  /* #20 Decrement link state delay and timeout counters */
  if(EthTrcv_30_Tja1100_GetLinkStateDelayCounter(TrcvIdx) > 0)
  {
    EthTrcv_30_Tja1100_DecLinkStateDelayCounter(TrcvIdx);                                                               /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
  if(EthTrcv_30_Tja1100_GetLinkStateTimeoutCounter(TrcvIdx) > 0)
  {
    EthTrcv_30_Tja1100_DecLinkStateTimeoutCounter(TrcvIdx);                                                             /* SBSW_ETHTRCV_INT_FCT_IDX_PASS */
  }
} /* PRQA S 6050 */ /* MD_MSR_STCAL */

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_6
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(void, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_MainFunctionLinkHandling_State_6(
    uint8 TrcvIdx)
{
  Std_ReturnType retVal;

  /* #10 Perfowm a soft reset */
  retVal = EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_BMCR,
      ETHTRCV_30_TJA1100_REG_BMCR_RESET);

  /* #20 The soft reset could be performed successfully */
  if(retVal == E_OK)
  {
    /* #210 Repeat link startup procedure */
    EthTrcv_30_Tja1100_LL_EnableLinkStartupDelay(TrcvIdx);
  }
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_ReadIdentifier1Register
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ReadIdentifier1Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  /* #10 Read the first identifier register of the PHY and report its value */
  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR1,
      RegValPtr);                                                                                                       /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */

  return retVal;
}

/*********************************************************************************************************************
 *  EthTrcv_30_Tja1100_LL_ReadIdentifier2Register
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
ETHTRCV_30_TJA1100_LL_LOCAL_INLINE FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_LL_ReadIdentifier2Register(
    uint8 TrcvIdx,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr,
    Std_ReturnType RetVal)
{
  Std_ReturnType retVal = RetVal;

  retVal |= EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
      TrcvIdx,
      ETHTRCV_30_TJA1100_REG_OFFS_PHYIDR2,
      RegValPtr);                                                                                                       /* SBSW_ETHTRCV_INT_FCT_PARAM_PTR_PASS */

  return retVal;
}
# endif /* ETHTRCV_30_TJA1100_UNIT_TEST */
#endif /* ETHTRCV_30_TJA1100_LL_H */
/**********************************************************************************************************************
 *  END OF FILE: EthTrcv_30_Tja1100_LL.h
 *********************************************************************************************************************/
