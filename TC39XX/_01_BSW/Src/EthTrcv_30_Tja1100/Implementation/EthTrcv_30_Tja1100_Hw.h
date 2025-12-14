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
/*         \file  EthTrcv_30_Tja1100_Hw.h
 *        \brief  Ethernet transceiver driver header for hardware access
 *
 *      \details  Header file containing the public function declarationss of the Ethernet Transceiver driver hardware
 *                access sub-module
 *
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK in the module's header file
 *********************************************************************************************************************/
#if !defined (ETHTRCV_30_TJA1100_HW_H)
# define ETHTRCV_30_TJA1100_HW_H
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_IntDef.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* ----- API service IDs ----- */
# define ETHTRCV_30_TJA1100_SID_READ_TRCV_REG                         (0x17U) /*!< Service ID: EthTrcv_30_Tja1100_ReadTrcvReg() */
# define ETHTRCV_30_TJA1100_SID_WRITE_TRCV_REG                        (0x18U) /*!< Service ID: EthTrcv_30_Tja1100_WriteTrcvReg() */
# define ETHTRCV_30_TJA1100_SID_READ_CL45_TRCV_REG                    (0x19U) /*!< Service ID: EthTrcv_30_Tja1100_ReadCl45TrcvReg() */
# define ETHTRCV_30_TJA1100_SID_WRITE_CL45_TRCV_REG                   (0x20U) /*!< Service ID: EthTrcv_30_Tja1100_WriteCl45TrcvReg() */
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReadTrcvReg()
 *********************************************************************************************************************/
/*! \brief         Retrieves the value of a register of the transceiver with index TrcvIdx
 *  \details       -
 *  \param[in]     TrcvIdx    Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                            instances minus one.
 *  \param[in]     RegAddr    Address of the register to be read
 *  \param[out]    RegValPtr  Pointer to the address of the read register value
 *  \return        RetVal     E_OK: Operation successful
 *                            E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \trace         CREQ-170739
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_WriteTrcvReg()
 *********************************************************************************************************************/
/*! \brief         Writes a given value to a register of the transceiver with index TrcvIdx
 *  \details       -
 *  \param[in]     TrcvIdx  Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                          instances minus one.
 *  \param[in]     RegAddr  Address of the register to be read
 *  \param[in]     RegVal   Value to be written to the register
 *  \return        RetVal   E_OK: Operation successful
 *                          E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \trace         CREQ-170740
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_WriteTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 RegVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_ReadCl45TrcvReg()
 *********************************************************************************************************************/
/*! \brief         Retrieves the value of a IEEE 802.3 Clause 45 register of the transceiver with index TrcvIdx over
 *                 the Clause 22 registers MMD_ACCESS_CONTROL and MMD_ACCESS_ADDRESS_DATA as described in IEEE 802.3
 *                 Annex 22D
 *  \details       -
 *  \param[in]     TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                                instances minus one.
 *  \param[in]     DeviceAddr     Address of the MMD
 *  \param[in]     RegAddr        Address of the register to be read
 *  \param[out]    RegValPtr      Pointer to the address of the read register value
 *  \return        RetVal         E_OK: Operation successful
 *                                E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \trace         CREQ-170741
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_ReadCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_WriteCl45TrcvReg()
 *********************************************************************************************************************/
/*! \brief         Writes a given value to a IEEE 802.3 Clause 45 register of the transceiver with index TrcvIdx over
 *                 the Clause 22 registers MMD_ACCESS_CONTROL and MMD_ACCESS_ADDRESS_DATA as described in IEEE 802.3
 *                 Annex 22D
 *  \details       -
 *  \param[in]     TrcvIdx        Zero based index of the transceiver. Range: 0 to number of configured transceiver
 *                                instances minus one.
 *  \param[in]     DeviceAddr     Address of the MMD
 *  \param[in]     RegAddr        Address of the register to be read
 *  \param[in]     RegVal         Value to be written to the register
 *  \return        RetVal         E_OK: Operation successful
 *                                E_NOT_OK: Operation not successful
 *  \context       TASK
 *  \reentrant     TRUE
 *  \synchronous   TRUE
 *  \pre           Module is initialized.
 *  \trace         CREQ-170742
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_WriteCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 RegVal);

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif /* ETHTRCV_30_TJA1100_HW_H */
