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
/*         \file  EthTrcv_30_Tja1100_Hw_Int.h
 *        \brief  Ethernet transceiver driver header for hardware access internal declaration and implementation
 *
 *      \details  Header file containing the public function declarations of the Ethernet Transceiver driver hardware
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
#if !defined (ETHTRCV_30_TJA1100_HW_INT_H)
# define ETHTRCV_30_TJA1100_HW_INT_H
/* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */
/* PRQA S 0777 EOF */ /* MD_MSR_5.1_777 */
/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "EthTrcv_30_Tja1100_Hw.h"
# include "EthTrcv_30_Tja1100_Lcfg.h"
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
# if !defined(ETHTRCV_30_TJA1100_HW_LOCAL)                                                                              /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_HW_LOCAL                                 static
# endif

# if !defined(ETHTRCV_30_TJA1100_HW_LOCAL_INLINE)                                                                       /* COV_ETHTRCV_COMPATIBILITY */
#  define ETHTRCV_30_TJA1100_HW_LOCAL_INLINE                          LOCAL_INLINE
# endif

/*! Address operation code for IEEE 802.3 Clause 45 management access */
# define ETHTRCV_30_TJA1100_CL45_ADDRESS_OP                           (0x0000u)
/*! Operation code for data access without incrementing the address afterwards */
# define ETHTRCV_30_TJA1100_CL45_DATA_NO_POST_INCREMENT_OP            (0x4000u)
/*! IEEE 802.3 Clause 45 MMD Access Control Register Address */
# define ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_CONTROL                   (0x0Du)
/*! IEEE 802.3 Clause 45 MMD Access Address and Data Register Address */
# define ETHTRCV_30_TJA1100_CL45_MMD_ACCESS_ADDRESS_DATA              (0x0Eu)
/**********************************************************************************************************************
 *  LOCAL INLINE FUNCTION PROTOTYPES
 *********************************************************************************************************************/
# define ETHTRCV_30_TJA1100_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_ReadTrcvReg()
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
 *  \pre           -
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_ReadTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_WriteTrcvReg()
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
 *  \pre           -
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WriteTrcvReg(
    uint8 TrcvIdx,
    uint8 RegAddr,
    uint16 RegVal);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg()
 *********************************************************************************************************************/
/*! \brief         Retrieves the value of a IEEE 802.3 Clause 45 register of the transceiver with index TrcvIdx over
 *                 the Clause 22 registers MMD_ACCESS_CONTROl and MMD_ACCESS_ADDRESS_DATA as described in IEEE 802.3
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
 *  \pre           -
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_ReadCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    P2VAR(uint16, AUTOMATIC, ETHTRCV_30_TJA1100_APPL_VAR) RegValPtr);

/**********************************************************************************************************************
 * EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg()
 *********************************************************************************************************************/
/*! \brief         Writes a given value to a IEEE 802.3 Clause 45 register of the transceiver with index TrcvIdx over
 *                 the Clause 22 registers MMD_ACCESS_CONTROl and MMD_ACCESS_ADDRESS_DATA as described in IEEE 802.3
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
 *  \pre           -
 */
FUNC(Std_ReturnType, ETHTRCV_30_TJA1100_CODE) EthTrcv_30_Tja1100_Internal_WriteCl45TrcvReg(
    uint8 TrcvIdx,
    uint8 DeviceAddr,
    uint16 RegAddr,
    uint16 RegVal);

# define ETHTRCV_30_TJA1100_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#endif /* ETHTRCV_30_TJA1100_HW_INT_H */
